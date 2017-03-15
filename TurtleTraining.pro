#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T14:02:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TurtleTraining
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../OpenCV-3.2.0/opencv/build/x64/vc14/lib/ -lopencv_world320
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../OpenCV-3.2.0/opencv/build/x64/vc14/lib/ -lopencv_world320d
else:unix: LIBS += -L$$PWD/../../../../OpenCV-3.2.0/opencv/build/x64/vc14/lib/ -lopencv_world320

INCLUDEPATH += $$PWD/../../../../OpenCV-3.2.0/opencv/build/include
DEPENDPATH += $$PWD/../../../../OpenCV-3.2.0/opencv/build/include

SOURCES += main.cpp\
        mainwindow.cpp \
    opencvplayer.cpp

HEADERS  += mainwindow.h \
    opencvplayer.h

FORMS    += mainwindow.ui


