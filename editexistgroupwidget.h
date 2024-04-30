#ifndef EDITEXISTGROUPWIDGET_H
#define EDITEXISTGROUPWIDGET_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

#include "EnumWidgets.h"
#include "GroupData.h"
#include "databasecontroller.h"

namespace Ui {
class EditExistGroupWidget;
}

class EditExistGroupWidget : public QDialog
{
    Q_OBJECT

public:
    explicit EditExistGroupWidget(DataBaseController *dbc, QWidget *parent = nullptr);
    ~EditExistGroupWidget();

signals:
    void transmitChangeToMainWindow(int index);

private slots:
    void toFillFields();
    void clearAll();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::EditExistGroupWidget *ui;
    DataBaseController *dbc;
    GroupData gd;

};

#endif // EDITEXISTGROUPWIDGET_H
