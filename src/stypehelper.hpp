#pragma once
#include <qstring.h>

class StyleHelper
{
public:
    static inline QString getMainWidgetStyle(const QString &imagePath);
    static inline QString getGlassStyle();
};


// Стиль для главного виджета
QString StyleHelper::getMainWidgetStyle(const QString &imagePath) {
    return QString(R"(
        QWidget#centralwidget {
            border-image: url(%1) 0 0 0 0 stretch stretch;
        }
    )").arg(imagePath);
}

QString StyleHelper::getGlassStyle(){
    return R"( 
        QWidget, QGroupBox {
          background-color: rgba(255, 255, 255, 20);   /* полупрозрачный белый */
          border: 1px solid rgba(255, 255, 255, 40);   /* полупрозрачная рамка */
          border-radius: 12px;                         /* скруглённые углы */
          color: white;
          margin-top: 8px;
        }
        QGroupBox::title {
          subcontrol-origin: margin;
          left: 10px;
          color: rgba(255, 255, 255, 200);
        }
    )";

}