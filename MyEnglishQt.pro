#-------------------------------------------------
#
# Project created by QtCreator 2019-04-06T16:00:41
#
#-------------------------------------------------

QT += core gui sql texttospeech

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyEnglishQt
VERSION = 2.2
RC_ICONS += MyEnglishQt.ico
QMAKE_TARGET_PRODUCT = "MyEnglishQt"
QMAKE_TARGET_DESCRIPTION = "MyEnglishQt is a simple program to learn English"
QMAKE_TARGET_COMPANY = "Juanra Goti"
QMAKE_TARGET_COPYRIGHT = "GNU General Public License"
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    dialogalfabeto.cpp \
        main.cpp \
    dialogedittest.cpp \
    dialogexamen.cpp \
    mainwindow.cpp

HEADERS += \
    dialogalfabeto.h \
    dialogedittest.h \
    dialogexamen.h \
    mainwindow.h

FORMS += \
    dialogalfabeto.ui \
    dialogedittest.ui \
    dialogexamen.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    COPYING \
    README

RESOURCES += \
    images.qrc
