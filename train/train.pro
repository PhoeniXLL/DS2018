#-------------------------------------------------
#
# Project created by QtCreator 2018-06-04T16:57:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = train
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


SOURCES += \
        main.cpp \
        initialdialog.cpp \
    registerdialog.cpp \
    logindialog.cpp \
    userdialog.cpp \
    administratordialog.cpp \
    modifyprofiledialog.cpp \
    modifyprivilegedialog.cpp \
    buyticketdialog.cpp \
    refundticketdialog.cpp \
    saletraindialog.cpp \
    deletetraindialog.cpp \
    querytransferdialog.cpp \
    addtraindialog.cpp \
    pricedialog.cpp \
    stationdialog.cpp \
    querytraindialog.cpp \
    queryorderdialog.cpp \
    queryticketdialog.cpp \
    modifytraindialog.cpp

HEADERS += \
        initialdialog.h \
    registerdialog.h \
    logindialog.h \
    userdialog.h \
    administratordialog.h \
    modifyprofiledialog.h \
    modifyprivilegedialog.h \
    buyticketdialog.h \
    refundticketdialog.h \
    saletraindialog.h \
    deletetraindialog.h \
    querytransferdialog.h \
    addtraindialog.h \
    pricedialog.h \
    stationdialog.h \
    querytraindialog.h \
    queryorderdialog.h \
    queryticketdialog.h \
    modifytraindialog.h

FORMS += \
        initialdialog.ui \
    registerdialog.ui \
    logindialog.ui \
    userdialog.ui \
    administratordialog.ui \
    modifyprofiledialog.ui \
    modifyprivilegedialog.ui \
    buyticketdialog.ui \
    refundticketdialog.ui \
    saletraindialog.ui \
    deletetraindialog.ui \
    querytransferdialog.ui \
    addtraindialog.ui \
    pricedialog.ui \
    stationdialog.ui \
    querytraindialog.ui \
    queryorderdialog.ui \
    queryticketdialog.ui \
    modifytraindialog.ui

RC_ICONS = icon.ico
