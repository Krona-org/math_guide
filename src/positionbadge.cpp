#include "positionbadge.h"
#include <QPainter>

PositionBadge::PositionBadge(int position, QWidget *parent)
    : QWidget(parent), m_position(position)
{
    m_cached = coloredPixmap();
    setMinimumSize(sizeHint());
}

void PositionBadge::setPosition(int position)
{
    m_position = position;
    m_cached = coloredPixmap();
    updateGeometry();
    update();
}

QPixmap PositionBadge::coloredPixmap() const
{
    int clamped = qBound(1, m_position, 30);
   QPixmap src(QString(":/numbers/res/numbers/%1.png").arg(clamped));
    if (src.isNull()) {
        qWarning() << "Не найдена картинка для позиции" << clamped
                    << "— проверь .qrc и путь resources/numbers/";
        return src;
    }

    QPixmap scaled = src.scaledToHeight(kTargetHeight, Qt::SmoothTransformation);

    QColor tint;
    switch (m_position) {
        case 1: tint = QColor("#FFD700"); break;
        case 2: tint = QColor("#C0C0C0"); break;
        case 3: tint = QColor("#CD7F32"); break;
        default: return scaled; // остальные остаются белыми как в исходнике
    }

    QPixmap result(scaled.size());
    result.fill(Qt::transparent);
    QPainter p(&result);
    p.drawPixmap(0, 0, scaled);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.fillRect(result.rect(), tint);
    p.end();

    return result;
}

QSize PositionBadge::sizeHint() const
{
    if (m_cached.isNull())
        return QSize(30, kTargetHeight + 8);
    return m_cached.size() + QSize(8, 8); // небольшой запас по краям
}

void PositionBadge::paintEvent(QPaintEvent *)
{
    if (m_cached.isNull()) return;

    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    // центрируем картинку внутри виджета
    int x = (width() - m_cached.width()) / 2;
    int y = (height() - m_cached.height()) / 2;
    p.drawPixmap(x, y, m_cached);
}