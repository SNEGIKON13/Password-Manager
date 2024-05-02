QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database/welcomewidget.cpp \
    database/createbasewidget.cpp \
    database/unlockbasewidget.cpp \
    database/settingsmanager.cpp \
    notes/addnewnotewidget.cpp \
    groups/addnewgroupwidget.cpp \
    groups/editexistgroupwidget.cpp \
    dbmanagement/databasecontroller.cpp \
    dbmanagement/databasecreator.cpp \
    dbmanagement/databasedisplay.cpp \
    dbmanagement/databasegroupscreator.cpp \
    dbmanagement/databasegroupseditor.cpp \
    dbmanagement/databasegroupsremover.cpp \
    dbmanagement/databasenotescreator.cpp \
    dbmanagement/databasenoteseditor.cpp \
    dbmanagement/databasenotesremover.cpp \
    main.cpp \
    mainwindow.cpp \
    notes/editexistnotewidget.cpp


HEADERS += \
    notes/addnewnotewidget.h \
    notes/editexistnotewidget.h \
    structures/EnumWidgets.h \
    structures/GroupData.h \
    structures/NodeData.h \
    database/welcomewidget.h \
    database/createbasewidget.h \
    database/unlockbasewidget.h \
    database/settingsmanager.h \
    groups/addnewgroupwidget.h \
    groups/editexistgroupwidget.h \
    dbmanagement/databasecontroller.h \
    dbmanagement/databasecreator.h \
    dbmanagement/databasedisplay.h \
    dbmanagement/databasegroupscreator.h \
    dbmanagement/databasegroupseditor.h \
    dbmanagement/databasegroupsremover.h \
    dbmanagement/databasenotescreator.h \
    dbmanagement/databasenoteseditor.h \
    dbmanagement/databasenotesremover.h \
    mainwindow.h

FORMS += \
    addnewgroupwidget.ui \
    addnewnotewidget.ui \
    createbasewidget.ui \
    editexistgroupwidget.ui \
    editexistnotewidget.ui \
    mainwindow.ui \
    unlockbasewidget.ui \
    welcomewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    toolBarImages.qrc
