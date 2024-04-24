#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //Создание ui-форм
    _welcomeWidget = new WelcomeWidget(this);
    _unlockBaseWidget = new UnlockBaseWindow(this);
    _createBaseWidget = new CreateBaseWidget(this);
    _addNewEntryWidget = new AddNewEntryWidget(this);

    //Добавление виджетов в стэк виджетов
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(1, _welcomeWidget);
    ui->stackedWidget->insertWidget(2, _addNewEntryWidget);
    ui->stackedWidget->setCurrentIndex(IndexWelcomeWidget);

    //Коннект QAction
    connect(ui->actionCreateBase, &QAction::triggered,
            this, &MainWindow::actionCreateBase);
    connect(ui->actionUnlockBase, &QAction::triggered,
            this, &MainWindow::actionUnlockBase);
    connect(ui->actionAddNewEntry, &QAction::triggered,
            this, &MainWindow::actionAddNewEntry);

    //Коннект Push_Buttons
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
    switch (index) {
    case IndexСreateBaseWidget:
        actionCreateBase();
        break;
    case IndexUnlockBaseWidget:
        actionUnlockBase();
        break;
    default:
        ui->stackedWidget->setCurrentIndex(index);
        break;
    }
}

void MainWindow::actionCreateBase()
{
     _createBaseWidget->show();
}

void MainWindow::actionUnlockBase()
{
    _unlockBaseWidget->show();
}

void MainWindow::actionAddNewEntry()
{
    changeStackedWidgetIndex(IndexAddNewEntryWidget);
}
