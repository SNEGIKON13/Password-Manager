#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _welcomeWidget = new WelcomeWidget(this);
    _unlockBaseWidget = new UnlockBaseWindow(this);
    _createBaseWidget = new CreateBaseWidget(this);
    ui->setupUi(this);
    ui->stackedWidget->addWidget(_welcomeWidget);
    ui->stackedWidget->addWidget(_unlockBaseWidget);
    ui->stackedWidget->addWidget(_createBaseWidget);
    ui->stackedWidget->setCurrentIndex(IndexWelcomeWidget);
    connect(_welcomeWidget, &WelcomeWidget::trasmitUnlockBase,
            this, &MainWindow::changeStackedWidgetIndex);
    connect(_welcomeWidget, &WelcomeWidget::trasmitCreateBase,
            this, &MainWindow::changeStackedWidgetIndex);
    connect(_createBaseWidget, &CreateBaseWidget::trasmitMainWindow,
            this, &MainWindow::changeStackedWidgetIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStackedWidgetIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}



