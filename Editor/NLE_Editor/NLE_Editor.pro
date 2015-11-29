#-------------------------------------------------
#
# Project created by QtCreator 2015-11-27T23:57:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NLE_Editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nl_qtinputmap.cpp \
    displaywindow.cpp

HEADERS  += mainwindow.h \
    nl_qtinputmap.h \
    displaywindow.h

FORMS    += mainwindow.ui \
    displaywindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../bin64/NonLinearEngine/lib/ -lNLE_
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../bin64/NonLinearEngine/lib/ -lNLE_d

INCLUDEPATH += $$PWD/../../bin64/NonLinearEngine/include
DEPENDPATH += $$PWD/../../bin64/NonLinearEngine/include
