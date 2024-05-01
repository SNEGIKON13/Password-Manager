#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>

#include "welcomewidget.h"
#include "unlockbasewidget.h"
#include "createbasewidget.h"
#include "addnewentrywidget.h"
#include "editexistentrywidget.h"
#include "addnewgroupwidget.h"
#include "editexistgroupwidget.h"
#include "settingsmanager.h"

#include "dbmanagement/databasecontroller.h"
#include "dbmanagement/databasecreator.h"
#include "dbmanagement/databasenotescreator.h"
#include "dbmanagement/databasenoteseditor.h"
#include "dbmanagement/databasegroupscreator.h"
#include "dbmanagement/databasegroupseditor.h"
#include "dbmanagement/databasedisplay.h"
#include "dbmanagement/databasenotesremover.h"
#include "dbmanagement/databasegroupsremover.h"


#include "EnumWidgets.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void extracted();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void changeStackedWidgetIndex(int index);
    void activatePopUpWidget(int index);
    void actionCreateDatabase();
    void actionChooseUnlockingBase();
    void actionCreateNewNote();
    void actionChangeNote();
    void actionDeleteNote();
    void actionCreateGroup();
    void actionChangeGroup();
    void actionDeleteGroup();
    void actionSort();
    void actionQuit();
    void receiveNewNameOfGroup(const QString &gn);
    void receiveFilePath(const QString &fp);
    void receivePossibleFilePath(const QString &fp);
    void unlockBase();

private slots:
    void createBase();
    void saveNewFilePath();
    void showDatabasesGroups();
    void adjustTableWidget();
    void setDatabaseNameText();
    void ifMainWindowActivated();

    void MWC_ConnectOfQActions();
    void MWC_InsertStackedWidgets();
    void MWC_CreationOfUiForms();
    void MWC_ConnectOfPushButtons();
    void MWC_ConnectsOther();
    void MWC_CreationOfToolBar();

    void on_groupListWidget_itemClicked(QListWidgetItem *item);
    void setIndexOfNewNameGroup();
    void setDefaultGroupNameOnStart();
    void firstStartOfMainWindow();

    QString selectedTableItem();
    QString selectedListItem();

    void MWC_CreationOfDatabaseControllers();

private:
    Ui::MainWindow *ui;
    WelcomeWidget *_welcomeWidget;
    UnlockBaseWindow *_unlockBaseWidget;
    CreateBaseWidget *_createBaseWidget;
    AddNewEntryWidget *_addNewEntryWidget;
    EditExistEntryWidget *_editExistEntryWidget;
    AddNewGroupWidget *_addNewGroupWidget;
    EditExistGroupWidget *_editExistGroupWidget;

    DatabaseController *_dbc;
    DatabaseCreator *_databaseCreator;
    DatabaseNotesCreator *_databaseNotesCreator;
    DatabaseNotesEditor *_databaseNotesEditor;
    DatabaseGroupsCreator *_databaseGroupsCreator;
    DatabaseGroupsEditor *_databaseGroupsEditor;
    DatabaseDisplay *_databaseDisplay;
    DatabaseNotesRemover *_databaseNotesRemover;
    DatabaseGroupsRemover *_databaseGroupsRemover;

    QString filePath, possibleFilePath;
    QStringList recentDatabases;
    QToolBar *_toolbar;
    QStringList headerLabels
        = {"Название записи", "Имя пользователя", "URL-адрес", "Заметки", "Время изменения"};
    QString groupName = "PasswordManager";
    int counterOfMWActivations = 0;

};
#endif // MAINWINDOW_H
