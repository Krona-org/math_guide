#pragma once
#include <QWidget>
#include <QPixmap>
#include <QColor>

class PositionBadge : public QWidget {
    Q_OBJECT
public:
    explicit PositionBadge(int position, QWidget *parent = nullptr);
    void setPosition(int position);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap coloredPixmap() const;

    int m_position = 0;
    QPixmap m_cached; // пересчитывается только при смене позиции, не при каждой отрисовке

    static constexpr int kTargetHeight = 22; // высота цифры в px, подгони под свою карточку
};