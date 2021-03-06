#-------------------------------------------------
#
# Project created by QtCreator 2013-11-28T17:45:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurveEditor
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    algorithms.cpp \
    curve.cpp \
    mycanvas.cpp \
    canvascore.cpp \
    styledialog.cpp \
    myfile.cpp

HEADERS  += \
    mainwindow.h \
    algorithms.h \
    curve.h \
    mycanvas.h \
    canvascore.h \
    styledialog.h \
    myfile.h

FORMS    += \
    mainwindow.ui \
    styledialog.ui
