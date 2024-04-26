#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>

#include "welcomewidget.h"
#include "unlockbasewidget.h"
#include "createbasewidget.h"
#include "addnewentrywidget.h"
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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void changeStackedWidgetIndex(int index);
    void activatePopUpWidget(int index);
    void actionCreateBase();
    void actionChooseUnlockingBase();
    void actionAddNewEntry();
    void actionQuit();
    void receiveFilePath(const QString &fp);
    void receivePossibleFilePath(const QString &fp);
    void unlockBase();

private slots:
    void createBase();
    void saveNewFilePath();
    void showDatabase();
    void setDatabaseNameText();
    void ifMainWindowActivated();

private:
    Ui::MainWindow *ui;
    WelcomeWidget *_welcomeWidget;
    UnlockBaseWindow *_unlockBaseWidget;
    CreateBaseWidget *_createBaseWidget;
    AddNewEntryWidget *_addNewEntryWidget;
    DataBaseController *_dbc;
    QString filePath, possibleFilePath;
    QStringList recentDatabases;
    QToolBar *_toolbar;


};
#endif // MAINWINDOW_H
