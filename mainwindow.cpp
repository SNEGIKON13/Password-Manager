#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _dbc = new DataBaseController(this);

    //Создание ui-форм
    _welcomeWidget = new WelcomeWidget(this);
    _welcomeWidget->showRecentDatabases();
    _unlockBaseWidget = new UnlockBaseWindow(this);
    _createBaseWidget = new CreateBaseWidget(_dbc, this);
    _addNewEntryWidget = new AddNewEntryWidget(this);

    //Добавление виджетов в стэк виджетов
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(1, _welcomeWidget);
    ui->stackedWidget->insertWidget(2, _addNewEntryWidget);
    ui->stackedWidget->setCurrentIndex(IndexWelcomeWidget);

    //Коннект QAction
    connect(ui->actionCreateBase, &QAction::triggered,
            this, &MainWindow::actionCreateBase);
    connect(ui->actionChooseUnlockingBase, &QAction::triggered,
            this, &MainWindow::actionChooseUnlockingBase);
    connect(ui->actionAddNewEntry, &QAction::triggered,
            this, &MainWindow::actionAddNewEntry);

    //Коннект Push_Buttons
    connect(_welcomeWidget, &WelcomeWidget::transmitChangeToUnlockBase,
            this, &MainWindow::changeStackedWidgetIndex);
    connect(_welcomeWidget, &WelcomeWidget::transmitChangeToCreateBase,
            this, &MainWindow::activatePopUpWidget);
    connect(_welcomeWidget, &WelcomeWidget::transmitChangeToUnlockBase,
            this, &MainWindow::activatePopUpWidget);
    connect(_dbc, &DataBaseController::transmitChangeToMainWindow,
            this, &MainWindow::changeStackedWidgetIndex);
    connect(_unlockBaseWidget, &UnlockBaseWindow::transmitChangeToMainWindow,
            this, &MainWindow::changeStackedWidgetIndex);

    //Другие коннекты
    connect(_welcomeWidget, &WelcomeWidget::transmitFilePath,
            this, &MainWindow::receivePossibleFilePath);
    connect(_unlockBaseWidget, &UnlockBaseWindow::transmitDataBasePath,
                this, &MainWindow::receiveFilePath);
    connect(_dbc, &DataBaseController::transmitFilePath,
            this, &MainWindow::receiveFilePath);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStackedWidgetIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::createBase()
{
    _createBaseWidget->show();
}

void MainWindow::activatePopUpWidget(int index)
{
    switch (index) {
    case IndexСreateBaseWidget:
        createBase();
        break;
    case IndexUnlockBaseWidget:
        unlockBase();
        break;
    default:
        break;
    }
}

void MainWindow::actionCreateBase()
{
     _createBaseWidget->show();
}

void MainWindow::unlockBase()
{
    _unlockBaseWidget->receiveFilePath(possibleFilePath);
    _unlockBaseWidget->show();
}

void MainWindow::actionChooseUnlockingBase()
{
    changeStackedWidgetIndex(IndexWelcomeWidget);
}

void MainWindow::receivePossibleFilePath(const QString &fp)
{
    possibleFilePath = fp;
}

void MainWindow::receiveFilePath(const QString &fp)
{
    filePath = fp;
    ui->baseName->setText(filePath);

    QFont font;
    font.setPointSize(12);
    ui->baseName->setFont(font);
    //работа с БД
    if (!filePath.isEmpty() && !recentDatabases.contains(filePath))
    {
        recentDatabases.prepend(filePath);
        filePath.clear();
        SettingsManager::saveRecentDatabases(recentDatabases);
        _welcomeWidget->showRecentDatabases();
    }
}

void MainWindow::actionAddNewEntry()
{
    changeStackedWidgetIndex(IndexAddNewEntryWidget);
}


