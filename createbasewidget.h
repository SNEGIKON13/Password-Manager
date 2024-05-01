#ifndef CREATEBASEWIDGET_H
#define CREATEBASEWIDGET_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>

#include "EnumWidgets.h"
#include "dbmanagement/databasecreator.h"

namespace Ui {
class CreateBaseWidget;
}

class CreateBaseWidget : public QDialog
{
    Q_OBJECT

public:
     CreateBaseWidget(DatabaseCreator* databaseCreator, QWidget* parent = nullptr);
    ~CreateBaseWidget();

private slots:
    void on_buttonBox_accepted();
    void clear_all();
    void on_buttonBox_rejected();

private:
    Ui::CreateBaseWidget *ui;
    QString baseName, basePassword, queryRequest;
    DatabaseCreator *databaseCreator;

};

#endif // CREATEBASEWIDGET_H
