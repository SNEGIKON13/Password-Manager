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
#include "databasecontroller.h"
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

private:
    Ui::MainWindow *ui;
    WelcomeWidget *_welcomeWidget;
    UnlockBaseWindow *_unlockBaseWidget;
    CreateBaseWidget *_createBaseWidget;
    AddNewEntryWidget *_addNewEntryWidget;
    EditExistEntryWidget *_editExistEntryWidget;
    AddNewGroupWidget *_addNewGroupWidget;
    EditExistGroupWidget *_editExistGroupWidget;

    DataBaseController *_dbc;
    QString filePath, possibleFilePath;
    QStringList recentDatabases;
    QToolBar *_toolbar;
    QStringList headerLabels
        = {"Название записи", "Имя пользователя", "URL-адрес", "Заметки", "Время изменения"};
    QString groupName = "PasswordManager";

};
#endif // MAINWINDOW_H
