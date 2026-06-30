#pragma once
#include <QWidget>
#include <QFont>
#include <QColor>
#include <QPainterPath>

class PositionBadge : public QWidget {
    Q_OBJECT
public:
    explicit PositionBadge(int position, QWidget *parent = nullptr);
    void setPosition(int position);
    QSize sizeHint() const override;   // <-- перенесено сюда, теперь public

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor badgeColor() const;
    QPainterPath buildDigitPath() const;
    QPainterPath buildTornEdgePath(const QRectF &b) const;

    int m_position = 0;
    QFont m_font;

    static constexpr int kMargin = 6;
};