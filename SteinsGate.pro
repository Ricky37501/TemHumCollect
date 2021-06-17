QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chartwindow.cpp \
    collectwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    settingwindow.cpp \
    tool.cpp

HEADERS += \
    chartwindow.h \
    collectwindow.h \
    mainwindow.h \
    settingwindow.h \
    tool.h

FORMS += \
    chartwindow.ui \
    collectwindow.ui \
    mainwindow.ui \
    settingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
