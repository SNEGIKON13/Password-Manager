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
    emit trasmitMainWindow(IndexMainWindow);
}

