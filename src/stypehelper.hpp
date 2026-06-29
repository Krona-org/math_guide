#pragma once
#include <qstring.h>

class StyleHelper
{
public:
    static inline QString getMainWidgetStyle();
};

// Стиль для главного виджета
QString StyleHelper::getMainWidgetStyle() {
    return R"(
        QWidget#centralwidget {
            border-image: url(:/res/image/kot_v_vode.png) 0 0 0 0 stretch stretch;
        }
    )";
}