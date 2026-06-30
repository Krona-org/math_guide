#include "mainwindow.h"

#include <QFontDatabase>
#include <qapplication.h>
#include <qfile.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

 int fontId = QFontDatabase::addApplicationFont(":/res/fonts/saira-condensed-black.ttf");
    if (fontId == -1) {
        qWarning() << "Шрифт не загружен";
    } else {
        qDebug() << "Семейства:" << QFontDatabase::applicationFontFamilies(fontId);
        // запомни точное имя из вывода — оно понадобится в drivercard.cpp
    }

    MainWindow w;
    w.show();

    return a.exec();
}