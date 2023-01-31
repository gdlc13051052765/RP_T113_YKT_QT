#-------------------------------------------------
#
# Project created by QtCreator 2019-12-24T23:43:26
#
#-------------------------------------------------

QT       += core gui sql network
QT += texttospeech
QT += testlib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = posAppQT
TEMPLATE = app
#QT       += multimedia
QT       += sql

LIBS +=-L/usr/lib -lasound 
INCLUDEPATH += ./
#LIBS += ./libsqlite3.so

SOURCES += main.cpp\
    MC_multimedia.cpp \
    cJSON.c \
    key_thread.cpp \
    modifysystimeui.cpp \
    play.cpp \
    setup.cpp \
    ipinformation.cpp \
    devmsg.cpp \
    setconsumemode.cpp \
    queryconsumerecord.cpp \
    querydayconsumemoney.cpp \
    dialog.cpp \
    mainconsumeinterface.cpp \
    sqlite3Qt.cpp \
    widget.cpp

HEADERS  += \
    CalucationFile.H \
    Delay.h \
    ISO7816.H \
    MC_multimedia.h \
    dialog.h \
    key_thread.h \
    modifysystimeui.h \
    readWriteCard.h \
    rfal_thread.h \
    setup.h \
    ipinformation.h \
    sqlite3.h \
    devmsg.h \
    setconsumemode.h \
    queryconsumerecord.h \
    querydayconsumemoney.h \
    mainconsumeinterface.h \
    sqlite3Qt.h \
    widget.h

FORMS    += \
    mainconsumewindow.ui \
    setup.ui \
    ipinformation.ui \
    devmsg.ui \
    setconsumemode.ui \
    queryconsumerecord.ui \
    querydayconsumemoney.ui \
    dialog.ui \
    mainconsumeinterface.ui \
    udpsocketdialog.ui \
    widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lsqlite3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lsqlite3
else:unix: LIBS += -L$$PWD/./ -lsqlite3

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
