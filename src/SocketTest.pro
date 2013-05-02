#-------------------------------------------------
#
# Project created by QtCreator 2012-08-13T14:58:59
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = SocketTest
TEMPLATE = app

TRANSLATIONS = socket-test.cn.ts

SOURCES += main.cpp\
        sockettestwindow.cpp \
    qtcpworker.cpp \
    socketbase.cpp \
    qlogprovider.cpp \
    qlogbase.cpp \
    qfilelog.cpp \
    qconfig.cpp \
    qnulllog.cpp \
    qscreenlog.cpp \
    qudpworker.cpp

HEADERS  += sockettestwindow.h \
    qtcpworker.h \
    socketbase.h \
    qlogprovider.h \
    qlogbase.h \
    qfilelog.h \
    qconfig.h \
    qnulllog.h \
    qscreenlog.h \
    qudpworker.h

FORMS    += sockettestwindow.ui
