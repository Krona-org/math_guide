#include "drivercard.h"
#include "positionbadge.h"   // <-- полный include нужен здесь, т.к. тут создаём объект
#include <QHBoxLayout>
#include "ui/stypehelper.hpp"

DriverCard::DriverCard(int pos, QString name, QString team, int points, QWidget *parent)
    : QWidget(parent)
    , m_pos(pos)
    , m_name(name)
    , m_team(team)
    , m_points(points)
{
    setObjectName("DriverCard");
    setStyleSheet(StyleHelper::getDriverCardStyle());

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 4, 10, 4);
    layout->setSpacing(8);

    auto *posBadge = new PositionBadge(pos);
    auto *lblName  = new QLabel(name);
    auto *lblTeam  = new QLabel(team);
    auto *lblPts   = new QLabel(QString::number(points) + " pts");

    lblName->setStyleSheet("color: white; font-size: 12px;");
    lblTeam->setStyleSheet("color: rgba(255,255,255,100); font-size: 11px;");
    lblPts->setStyleSheet("color: rgba(255,255,255,180); font-size: 12px;");

    layout->addWidget(posBadge);
    layout->addWidget(lblName);
    layout->addWidget(lblTeam);
    layout->addStretch();
    layout->addWidget(lblPts);

    setFixedHeight(qMax(34, posBadge->sizeHint().height() + 8));
}