#include "createbasewidget.h"
#include "ui_createbasewidget.h"

CreateBaseWidget::CreateBaseWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateBaseWidget)
{
    ui->setupUi(this);
}

CreateBaseWidget::~CreateBaseWidget()
{
    delete ui;
}

void CreateBaseWidget::on_buttonBox_accepted()
{

    baseName = ui->baseName->text();
    basePassword = ui->basePassword->text();
    if (!baseName.isEmpty() && !basePassword.isEmpty()) {
        emit trasmitMainWindow(IndexMainWindow);
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(baseName + ".db");
        db.open();
        queryRequest = "CREATE TABLE notes ("
                       "id serial PRIMARY KEY,"
                       "note_name VARCHAR(64) NOT NULL,"
                       "login VARCHAR(64),"
                       "url VARCHAR(64),"
                       "password VARCHAR(64) NOT NULL,"
                       "other_notes VARCHAR(500),"
                       "last_modified TIMESTAMP"
                       ")";
        QSqlQuery query;
        query.exec(queryRequest);
        db.close();
        close();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Ошибка при создании базы данных!"
                                             " Проверьте ввод!");
    }
}
