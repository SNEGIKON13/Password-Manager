#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

void WelcomeWidget::on_openExistBaseButton_clicked()
{
    emit trasmitUnlockBase(IndexUnlockBaseWidget);
}


void WelcomeWidget::on_createBaseButton_clicked()
{
    emit trasmitCreateBase(IndexСreateBaseWidget);
}

