#ifndef CREATEBASEWIDGET_H
#define CREATEBASEWIDGET_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "EnumWidgets.h"
#include "databasecontroller.h"

namespace Ui {
class CreateBaseWidget;
}

class CreateBaseWidget : public QDialog
{
    Q_OBJECT

public:
     CreateBaseWidget(DataBaseController* dbc, QWidget* parent = nullptr);
    ~CreateBaseWidget();

private slots:
    void on_buttonBox_accepted();
    void clear_all();
    void on_buttonBox_rejected();

private:
    Ui::CreateBaseWidget *ui;
    QString baseName, basePassword, queryRequest;
    DataBaseController *dbc;

};

#endif // CREATEBASEWIDGET_H
