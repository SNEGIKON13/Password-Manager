#ifndef CREATEBASEWIDGET_H
#define CREATEBASEWIDGET_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "EnumWidgets.h"
#include "db_controller.h"

namespace Ui {
class CreateBaseWidget;
}

class CreateBaseWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CreateBaseWidget(QWidget *parent = nullptr);
    ~CreateBaseWidget();

signals:
    void trasmitMainWindow(int index);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CreateBaseWidget *ui;
    QString baseName, basePassword, queryRequest;
    QSqlDatabase db;

};

#endif // CREATEBASEWIDGET_H
