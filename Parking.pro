QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    form2.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    tableviewbase.cpp \
    tableviewfactory.cpp \
    tableviewlotA20.cpp

HEADERS += \
    dialog.h \
    form2.h \
    login.h \
    mainwindow.h \
    tableviewbase.h \
    tableviewfactory.h \
    tableviewlotA20.h

FORMS += \
    dialog.ui \
    form2.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
