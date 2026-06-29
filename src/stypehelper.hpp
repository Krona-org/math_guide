#pragma once
#include <qstring.h>

class StyleHelper
{
public:
    static inline QString getMainWidgetStyle();
    static inline QString getGlassStyle();
};

// Стиль для главного виджета
QString StyleHelper::getMainWidgetStyle() {
    return R"(
        QWidget#centralwidget {
            border-image: url(:/res/image/kot_v_vode.png) 0 0 0 0 stretch stretch;
        }
    )";
}

QString StyleHelper::getGlassStyle()
{
    return R"( 
        QGroupBox {
          background-color: rgba(255, 255, 255, 30);   /* полупрозрачный белый */
          border: 1px solid rgba(255, 255, 255, 80);   /* полупрозрачная рамка */
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