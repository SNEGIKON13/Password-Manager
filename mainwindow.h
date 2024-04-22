#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

#include "welcomewidget.h"
#include "unlockbasewidget.h"
#include "createbasewidget.h"
#include "addnewentrywidget.h"
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

    void actionCreateBase();
    void actionUnlockBase();
    void actionAddNewEntry();

private:
    Ui::MainWindow *ui;
    WelcomeWidget *_welcomeWidget;
    UnlockBaseWindow *_unlockBaseWidget;
    CreateBaseWidget *_createBaseWidget;
    AddNewEntryWidget *_addNewEntryWidget;

};
#endif // MAINWINDOW_H
