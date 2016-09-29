#-------------------------------------------------
#
# Project created by QtCreator 2016-06-07T09:51:27
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets sql websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Halvarsson_server
TEMPLATE = app
CONFIG += c++14


SOURCES += main.cpp\
        orderserver.cpp \
    server.cpp \
    databasemanager.cpp \
    attribute.cpp \
    order.cpp \
    table.cpp \
    clickablelabel.cpp

HEADERS  += orderserver.h \
    server.h \
    databasemanager.h \
    attribute.h \
    order.h \
    table.h \
    clickablelabel.h

FORMS    += orderserver.ui \
    attribute.ui \
    order.ui \
    table.ui

RESOURCES += icons.qrc
