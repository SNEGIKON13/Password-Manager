#include "addnewentrywidget.h"
#include "ui_addnewentrywidget.h"

AddNewEntryWidget::AddNewEntryWidget(DataBaseController *dbc, QWidget *parent)
    : QDialog(parent), ui(new Ui::AddNewEntryWidget), dbc(dbc)    
{
    ui->setupUi(this);
}

AddNewEntryWidget::~AddNewEntryWidget()
{
    delete ui;
}

void AddNewEntryWidget::on_buttonBox_rejected()
{
    emit transmitChangeToMainWindow(IndexMainWindow);
}

void AddNewEntryWidget::on_buttonBox_accepted()
{
    if (ui->passwordEntry->text().isEmpty() && ui->noteName->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Ввод названия записи и пароля обязателен!");
        return;
    }

    if (!ui->noteName->text().isEmpty()) {
        nd.noteName = ui->noteName->text();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Ввод пароля обязателен!");
        return;
    }
    if (!ui->passwordEntry->text().isEmpty()) {
        nd.passwordEntry = ui->passwordEntry->text();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Ввод названия записи обязателен!");
        return;
    }
    if (!ui->userName->text().isEmpty()) {
        nd.userName = ui->userName->text();
    } else {
        nd.userName = "";
    }

    if (!ui->url->text().isEmpty()) {
        nd.url = ui->url->text();
    } else {
        nd.url = "";
    }

    if (!ui->otherNotes->toPlainText().isEmpty()) {
        nd.otherNotes = ui->otherNotes->toPlainText();
    } else {
        nd.otherNotes = "";
    }

    dbc->createNewNote(nd);
    emit transmitChangeToMainWindow(IndexMainWindow);
}

