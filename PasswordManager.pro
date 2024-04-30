QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addnewentrywidget.cpp \
    addnewgroupwidget.cpp \
    createbasewidget.cpp \
    databasecontroller.cpp \
    editexistentrywidget.cpp \
    editexistgroupwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsmanager.cpp \
    unlockbasewidget.cpp \
    welcomewidget.cpp    

HEADERS += \
    EnumWidgets.h \
    GroupData.h \
    NodeData.h \
    addnewentrywidget.h \
    addnewgroupwidget.h \
    createbasewidget.h \
    databasecontroller.h \
    editexistentrywidget.h \
    editexistgroupwidget.h \
    mainwindow.h \
    settingsmanager.h \
    unlockbasewidget.h \
    welcomewidget.h

FORMS += \
    addnewentrywidget.ui \
    addnewgroupwidget.ui \
    createbasewidget.ui \
    editexistentrywidget.ui \
    editexistgroupwidget.ui \
    mainwindow.ui \
    unlockbasewidget.ui \
    welcomewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    toolBarImages.qrc
