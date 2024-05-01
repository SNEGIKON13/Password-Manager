#ifndef ADDNEWGROUPWIDGET_H
#define ADDNEWGROUPWIDGET_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

#include "EnumWidgets.h"
#include "GroupData.h"
#include "dbmanagement/databasegroupscreator.h"

namespace Ui {
class AddNewGroupWidget;
}

class AddNewGroupWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewGroupWidget(DatabaseGroupsCreator *databaseGroupCreator, QWidget *parent = nullptr);
    ~AddNewGroupWidget();

signals:
    void transmitChangeToMainWindow(int index);

private slots:
    void on_buttonBox_accepted();
    void clearAll();
    void on_buttonBox_rejected();

private:
    Ui::AddNewGroupWidget *ui;
    DatabaseGroupsCreator *databaseGroupCreator;
    GroupData gd;
};

#endif // ADDNEWGROUPWIDGET_H
