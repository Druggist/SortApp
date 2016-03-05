#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T16:04:00
#
#-------------------------------------------------

QT       += core gui concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SortApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generatesequence.cpp \
    qcustomplot.cpp \
    progressdialog.cpp \
    sort.cpp \
    loop.cpp

HEADERS  += mainwindow.h \
    generatesequence.h \
    qcustomplot.h \
    progressdialog.h \
    sort.h \
    loop.h

FORMS    += mainwindow.ui \
    progressdialog.ui
