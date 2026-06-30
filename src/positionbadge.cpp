#include "positionbadge.h"
#include <QPainter>
#include <QFontMetrics>
#include <QRandomGenerator>
#include <QtMath>

PositionBadge::PositionBadge(int position, QWidget *parent)
    : QWidget(parent), m_position(position)
{
    m_font = QFont("Saira Condensed", 16, QFont::Black, /*italic=*/true);
    setMinimumSize(sizeHint());
}

void PositionBadge::setPosition(int position)
{
    m_position = position;
    updateGeometry();
    update();
}

QColor PositionBadge::badgeColor() const
{
    switch (m_position) {
        case 1: return QColor("#FFD700");
        case 2: return QColor("#C0C0C0");
        case 3: return QColor("#CD7F32");
        default: return Qt::white;
    }
}

// Строит контур цифры так, чтобы его реальный bounding box (с учётом
// наклона италика в обе стороны) гарантированно помещался в [margin..w-margin].
QPainterPath PositionBadge::buildDigitPath() const
{
    QString text = QString::number(m_position);
    QFontMetrics fm(m_font);

    // черновой путь в (0, ascent), чтобы узнать реальные границы глифа
    QPainterPath raw;
    raw.addText(QPointF(0, fm.ascent()), m_font, text);
    QRectF rb = raw.boundingRect();

    // сдвигаем так, чтобы левый-верхний угол реального контура был в (margin, margin)
    QPainterPath path;
    path.addText(QPointF(kMargin - rb.left(), kMargin - rb.top() + fm.ascent()), m_font, text);
    return path;
}

// Строит область "среза" с рваным неровным верхним краем (зигзаг),
// которая идёт от ~55-70% высоты цифры до самого низа.
// Используется как доп. клип поверх контура цифры.
QPainterPath PositionBadge::buildTornEdgePath(const QRectF &b) const
{
    // фиксированный сид на позицию — край рваный, но не "дёргается" при каждой перерисовке
    QRandomGenerator rng(quint32(m_position * 7919 + 17));

    qreal left   = b.left() - b.height();
    qreal right  = b.right() + b.height();
    qreal bottom = b.bottom() + 6;
    qreal baseY  = b.top() + b.height() * 0.6; // средняя линия среза

    qreal amplitude = b.height() * 0.16; // насколько сильно "рвётся" край
    qreal step = qMax(4.0, b.height() * 0.10); // шаг по X между точками зигзага

    QPainterPath torn;
    bool first = true;
    for (qreal x = left; x <= right; x += step) {
        qreal jitter = (rng.generateDouble() - 0.5) * 2.0 * amplitude;
        qreal y = baseY + jitter;
        if (first) {
            torn.moveTo(x, y);
            first = false;
        } else {
            torn.lineTo(x, y);
        }
    }
    // замыкаем контур вниз и обратно — получаем область от рваной линии до низа
    torn.lineTo(right, bottom);
    torn.lineTo(left, bottom);
    torn.closeSubpath();

    return torn;
}

QSize PositionBadge::sizeHint() const
{
    QPainterPath path = buildDigitPath();
    QRectF b = path.boundingRect();
    return QSize(qCeil(b.right() + kMargin), qCeil(b.bottom() + kMargin));
}

void PositionBadge::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QPainterPath digitPath = buildDigitPath();
    QRectF b = digitPath.boundingRect();
    if (b.isEmpty()) return;

    // 1. базовая заливка всей цифры
    p.fillPath(digitPath, badgeColor());

    // 2. рваная область среза (нижняя часть с неровным краем)
    QPainterPath tornArea = buildTornEdgePath(b);

    p.save();
    p.setClipPath(digitPath);             // не выходим за форму цифры
    p.setClipPath(tornArea, Qt::IntersectClip); // только рваная нижняя зона

    // тёмная подложка под штриховкой — создаёт ощущение "вырванного" куска
    p.fillPath(digitPath, QColor("#1a1a1a"));

    // диагональные штрихи поверх тёмной зоны
    QPen pen(QColor(255, 255, 255, 60), qMax(1.0, b.height() * 0.05));
    p.setPen(pen);
    qreal hstep = qMax(3.0, b.height() * 0.14);
    for (qreal x = b.left() - b.height(); x < b.right() + b.height(); x += hstep) {
        p.drawLine(QPointF(x, b.bottom() + 6),
                   QPointF(x + b.height() * 0.5, b.top() - 6));
    }
    p.restore();
}