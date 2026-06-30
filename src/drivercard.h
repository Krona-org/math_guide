#pragma once
#include <QWidget>
#include <QLabel>

class DriverCard : public QWidget {
    Q_OBJECT
public:
    DriverCard(int pos, QString name, QString team, int points, QWidget *parent = nullptr);
};