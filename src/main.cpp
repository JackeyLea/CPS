#include <QApplication>

#include "widgetlogin.h"
#include "chapterexercisesetup.h"
#include "addquestion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WidgetLogin loginWidget;
    loginWidget.show();

    // AddQuestion aq;
    // aq.show();

    return a.exec();
}
