#include "drivercard.h"
#include <QHBoxLayout>
#include "ui/stypehelper.hpp"

DriverCard::DriverCard(int pos, QString name, QString team, int points, QWidget *parent)
    : QWidget(parent)
{
    setObjectName("DriverCard");
    setStyleSheet(StyleHelper::getDriverCardStyle());
    setFixedHeight(30);

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 6, 10, 6);
    layout->setSpacing(8);

    auto *lblPos  = new QLabel(QString::number(pos));
    auto *lblName = new QLabel(name);
    auto *lblTeam = new QLabel(team);
    auto *lblPts  = new QLabel(QString::number(points) + " pts");

    lblPos->setFixedWidth(24);
    lblPos->setStyleSheet("color: rgba(255,255,255,180); font-size: 13px; font-weight: bold;");
    lblName->setStyleSheet("color: white; font-size: 12px;");
    lblTeam->setStyleSheet("color: rgba(255,255,255,100); font-size: 11px;");
    lblPts->setStyleSheet("color: rgba(255,255,255,180); font-size: 12px;");

    layout->addWidget(lblPos);
    layout->addWidget(lblName);
    layout->addWidget(lblTeam);
    layout->addStretch();
    layout->addWidget(lblPts);
}