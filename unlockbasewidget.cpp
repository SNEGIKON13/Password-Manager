#include "unlockbasewidget.h"
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

void UnlockBaseWindow::on_unlockBaseButton_clicked()
{
    emit transmitMainWindow(IndexMainWindow);
}

