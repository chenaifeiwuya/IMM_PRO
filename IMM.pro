#-------------------------------------------------
#
# Project created by QtCreator 2023-08-01T14:00:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FeiQ
TEMPLATE = app

include(./sqlapi/sqlapi.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    mediator/INetMediator.cpp \
    mediator/tcpClientMediator.cpp \
    ckernel.cpp \
    net/tcpClient.cpp \
    cfriendlist.cpp \
    cfrienditem.cpp \
    chatdialog.cpp \
    md5.cpp \
    mytablewidget.cpp \
    cgroupchat.cpp \
    cchatgroupitem.cpp

HEADERS  += mainwindow.h \
    pakdef.h \
    mediator/INetMediator.h \
    net/INet.h \
    ckernel.h \
    mediator/tcpClientMediator.h \
    net/tcpClient.h \
    cfriendlist.h \
    cfrienditem.h \
    chatdialog.h \
    md5.h \
    mytablewidget.h \
    cgroupchat.h \
    cchatgroupitem.h

INCLUDEPATH += ./net  \
                ./mediator \
                ./sqlapi   \
                ./

LIBS += -lws2_32

FORMS    += mainwindow.ui \
    cfriendlist.ui \
    cfrienditem.ui \
    chatdialog.ui \
    cgroupchat.ui \
    cchatgroupitem.ui

RESOURCES += \
    source.qrc

DISTFILES +=
