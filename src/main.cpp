#include <QApplication>

#include "widgetlogin.h"
#include "mainwindow.h"
#include "chapterexercisesetup.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // WidgetLogin loginWidget;
    // loginWidget.show();

    // MainWindow w;
    // w.show();

    ChapterExerciseSetup setup;
    setup.show();

    return a.exec();
}
