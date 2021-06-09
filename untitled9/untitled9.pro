QT       += core gui
QT       += core gui charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brushtool.cpp \
    customslice.cpp \
    main.cpp \
    mainwindow.cpp \
    pentool.cpp\
    stringlib.cpp\
    messagewindow.cpp\
    dataset.cpp\
    field.cpp \
    rng.cpp\
    chartview.cpp

HEADERS += \
    brushtool.h \
    customslice.h \
    mainwindow.h \
    pentool.h \
    stringlib.h\
    messagewindow.h\
    dataset.h\
    field.h\
    rng.h\
    chartview.ht

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=img/img.qrc
