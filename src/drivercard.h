#pragma once
#include <QWidget>
#include <QLabel>

class PositionBadge; // forward declaration, полный include не нужен в заголовке

class DriverCard : public QWidget {
    Q_OBJECT
public:
    DriverCard(int pos, QString name, QString team, int points, QWidget *parent = nullptr);

    int points() const { return m_points; }
    int position() const { return m_pos; }
    QString driverName() const { return m_name; }
    QString team() const { return m_team; }

private:
    int m_pos;
    QString m_name;
    QString m_team;
    int m_points;
};