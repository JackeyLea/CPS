#include <QApplication>

#include "widgetlogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WidgetLogin loginWidget;
    loginWidget.show();

    return a.exec();
}
