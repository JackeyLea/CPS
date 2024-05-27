QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET  = ITPMPS
DESTDIR = ../../bin
MOC_DIR = moc
RCC_DIR = rcc
UI_DIR  = ui
OBJECTS_DIR = objs

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/chapterexercise.cpp \
    src/chapterexercisesetup.cpp \
    src/dbhandler.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/widgetlogin.cpp \
    src/sha512.cpp

HEADERS += \
    include/chapterexercise.h \
    include/chapterexercisesetup.h \
    include/dbhandler.h \
    include/mainwindow.h \
    include/widgetlogin.h \
    include/sha512.h

FORMS += \
    ui/chapterexercise.ui \
    ui/chapterexercisesetup.ui \
    ui/mainwindow.ui \
    ui/widgetlogin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
