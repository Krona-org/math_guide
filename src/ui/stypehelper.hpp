#pragma once
#include <qstring.h>

class StyleHelper
{
public:
    static inline QString getMainWidgetStyle();
    static inline QString getGlassStyle();
    static inline QString getStyleButtonGlass();
    static inline QString getDriverCardStyle();
};

// Стиль для главного виджета
QString StyleHelper::getMainWidgetStyle() {
    return R"(
        QWidget#centralwidget {
            border-image: url(:/res/image/kot_v_vode.png) 0 0 0 0 stretch stretch;
        }
    )";
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

QString StyleHelper::getStyleButtonGlass(){
    return R"(
        QPushButton { 
            background-color: rgba(255,255,255,40);
            border-radius: 8px;
            color: white; padding: 6px;
            border: 1px solid rgba(255,255,255,80);
        }
        QPushButton:hover { 
            background-color: rgba(255,255,255,70);
        }
    )";
}

QString StyleHelper::getDriverCardStyle() {
    return R"(
        QWidget#DriverCard {
            background-color: rgba(30, 30, 40, 220);
            border: 1px solid rgba(255, 255, 255, 20);
            border-radius: 8px;
        }
        QWidget#DriverCard QLabel {
            background: transparent;
            border: none;
            border-radius: 0px;
        }
    )";
}