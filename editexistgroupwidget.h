#ifndef EDITEXISTGROUPWIDGET_H
#define EDITEXISTGROUPWIDGET_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

#include "EnumWidgets.h"
#include "GroupData.h"
#include "dbmanagement/databasegroupseditor.h"

namespace Ui {
class EditExistGroupWidget;
}

class EditExistGroupWidget : public QDialog
{
    Q_OBJECT

public:
    explicit EditExistGroupWidget(DatabaseGroupsEditor *databaseGroupEditor, QWidget *parent = nullptr);
    ~EditExistGroupWidget();
    void setGroupName(const QString &groupName);
    void toFillFields();

signals:
    void transmitChangeToMainWindow(int index);
    void transmitChangedGroupName(QString newName);

private slots:
    void clearAllExceptId();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::EditExistGroupWidget *ui;
    DatabaseGroupsEditor *databaseGroupEditor;
    GroupData gd;
    QString groupName;

};

#endif // EDITEXISTGROUPWIDGET_H
