#include "database/unlockbasewidget.h"
#include "ui_unlockbasewidget.h"

UnlockBaseWindow::UnlockBaseWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UnlockBaseWindow)
{
    ui->setupUi(this);
}

UnlockBaseWindow::~UnlockBaseWindow()
{
    delete ui;
}

void UnlockBaseWindow::clear_all()
{
    passwordEntry.clear();
    ui->passwordEntryField->clear();
}

void UnlockBaseWindow::on_unlockBaseButton_clicked()
{
    passwordEntry = ui->passwordEntryField->text();
    if (!passwordEntry.isEmpty()) {
        if (/*Если пароль верен filepath_db*/true) {
            emit transmitDataBasePath(filePath);
            emit transmitChangeToMainWindow(IndexMainWindow);
            clear_all();
            close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный пароль!");
        }
    }
}

void UnlockBaseWindow::receiveFilePath(const QString &fp)
{
    filePath = fp;
    ui->baseName->setText(filePath);
}

