#-------------------------------------------------
#
# Project created by Jose Eduardo Hernandez 2013-12-01T20:11:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Monopolio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    jugador.cpp \
    propiedad.cpp \
    propiedadnormal.cpp \
    railroad.cpp \
    servicio.cpp \
    chancedialog.cpp \
    communitychestdialog.cpp \
    communitychest.cpp \
    chance.cpp \
    subastardialog.cpp \
    propiedadesdialog.cpp \
    hipotecardialog.cpp \
    construirdialog.cpp

HEADERS  += mainwindow.h \
    jugador.h \
    propiedad.h \
    propiedadnormal.h \
    railroad.h \
    servicio.h \
    chancedialog.h \
    communitychestdialog.h \
    communitychest.h \
    chance.h \
    subastardialog.h \
    propiedadesdialog.h \
    hipotecardialog.h \
    construirdialog.h

FORMS    += mainwindow.ui \
    chancedialog.ui \
    communitychestdialog.ui \
    comprardialog.ui \
    subastardialog.ui \
    propiedadesdialog.ui \
    hipotecardialog.ui \
    construirdialog.ui

RESOURCES += \
    MonopolioRecursos.qrc
