#include <qmainwindow.h>
#include <qtabbar.h>
#include <qdebug.h>
#include <qpixmap.h>
#include <qgroupbox.h>
#include <qpainter.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stypehelper.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_originalPixmap = QPixmap(":/res/image/kot_v_vode.png"); // грузим один раз
    updateBackground();
}

void MainWindow::updateBackground()
{
    QPixmap pm = m_originalPixmap.scaled(ui->centralwidget->size(),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation);
    QPainter painter(&pm);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.fillRect(pm.rect(), QColor(0, 0, 0, 150));
    painter.end();

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(pm));
    ui->centralwidget->setPalette(palette);
    ui->centralwidget->setAutoFillBackground(true);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event); // обязательно вызвать родительский
    updateBackground();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton()
{
    // пока пусто
}

void MainWindow::q_groupBox()
{

}