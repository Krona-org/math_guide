#include <qmainwindow.h>
#include <qnamespace.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <QWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stypehelper.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setBackgroundImage(":/res/image/kot_v_vode.png"); // дефолтная картинка
    ui->widgetDriverList->setStyleSheet(StyleHelper::getGlassStyle());
    ui->widgetDiagrama->setStyleSheet(StyleHelper::getGlassStyle());
    updateBackground();
}

void MainWindow::setBackgroundImage(const QString &path)
{
    m_originalPixmap = QPixmap(path);
    updateBackground();
}

void MainWindow::updateBackground()
{
    if (m_originalPixmap.isNull())
        return; // на случай если путь неверный

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