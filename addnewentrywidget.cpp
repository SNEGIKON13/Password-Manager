#include "addnewentrywidget.h"
#include "ui_addnewentrywidget.h"

AddNewEntryWidget::AddNewEntryWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddNewEntryWidget)
{
    ui->setupUi(this);
}

AddNewEntryWidget::~AddNewEntryWidget()
{
    delete ui;
}
