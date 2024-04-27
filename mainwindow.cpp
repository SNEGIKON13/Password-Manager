#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _dbc = new DataBaseController(this);
    _toolbar = new QToolBar(this);
    addToolBar(_toolbar);

    //Создание ui-форм
    _welcomeWidget = new WelcomeWidget(this);
    _welcomeWidget->showRecentDatabases();
    _unlockBaseWidget = new UnlockBaseWindow(this);
    _createBaseWidget = new CreateBaseWidget(_dbc, this);
    _addNewEntryWidget = new AddNewEntryWidget(_dbc, this);
    _editExistEntryWidget = new EditExistEntryWidget(_dbc, this);

    //Добавление виджетов в стэк виджетов
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(1, _welcomeWidget);
    ui->stackedWidget->insertWidget(2, _addNewEntryWidget);
    ui->stackedWidget->insertWidget(3, _editExistEntryWidget);
    ui->stackedWidget->setCurrentIndex(IndexWelcomeWidget);

    //Коннект QAction
    connect(ui->actionCreateBase, &QAction::triggered,
            this, &MainWindow::actionCreateBase);
    connect(ui->actionChooseUnlockingBase, &QAction::triggered,
            this, &MainWindow::actionChooseUnlockingBase);
    connect(ui->actionAddNewEntry, &QAction::triggered,
            this, &MainWindow::actionAddNewEntry);
    connect(ui->actionQuit, &QAction::triggered,
            this, &MainWindow::actionQuit);
    connect(ui->actionChangeNote, &QAction::triggered,
            this, &MainWindow::actionChangeNote);

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
    connect(_addNewEntryWidget, &AddNewEntryWidget::transmitChangeToMainWindow,
            this, &MainWindow::changeStackedWidgetIndex);

    //Добавление QAction в toolbar и их настройка
    ui->actionAddNewEntry->setIcon(QIcon("://Images/CreateNewNote.png"));
    ui->actionQuit->setIcon(QIcon("://Images/Quit.png"));
    ui->actionChangeNote->setIcon(QIcon("://Images/ChangeExistNote.png"));
    _toolbar->addAction(ui->actionAddNewEntry);
    _toolbar->addAction(ui->actionQuit);
    _toolbar->addAction(ui->actionChangeNote);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStackedWidgetIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    ifMainWindowActivated();
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

void MainWindow::unlockBase()
{
    _unlockBaseWidget->receiveFilePath(possibleFilePath);
    _unlockBaseWidget->show();
}

void MainWindow::createBase()
{
    _createBaseWidget->show();
}

void MainWindow::showDatabasesGroups()
{
    ui->listWidget->clear();
    _dbc->showDatabasesGroups(ui->listWidget);
}

void MainWindow::receivePossibleFilePath(const QString &fp)
{
    possibleFilePath = fp;
}

void MainWindow::saveNewFilePath()
{
    recentDatabases = SettingsManager::loadRecentDatabases();
    if (!filePath.isEmpty() && !recentDatabases.contains(filePath))
    {
        recentDatabases.prepend(filePath);
        filePath.clear();
        SettingsManager::saveRecentDatabases(recentDatabases);
        _welcomeWidget->showRecentDatabases();
    }
}

void MainWindow::setDatabaseNameText()
{
    ui->baseName->setText(filePath);
    QFont font;
    font.setPointSize(12);
    ui->baseName->setFont(font);
}

void MainWindow::ifMainWindowActivated()
{
    showDatabasesGroups();
}

void MainWindow::receiveFilePath(const QString &fp)
{
    filePath = fp;
    setDatabaseNameText();
    saveNewFilePath();
    _dbc->setFilePath(fp);
}

void MainWindow::actionAddNewEntry()
{
    if (_dbc->isEmptyFilePath()) {
        QMessageBox::warning(this, "Ошибка", "Cначала войдите в базу данных!");
    }
    else {
        changeStackedWidgetIndex(IndexAddNewEntryWidget);
    }
}

void MainWindow::actionChangeNote()
{
    if (_dbc->isEmptyFilePath()) {
        QMessageBox::warning(this, "Ошибка", "Cначала войдите в базу данных!");
    }
    else {
        changeStackedWidgetIndex(IndexEditExistEntryWidget);
    }
}

void MainWindow::actionCreateBase()
{
    _createBaseWidget->show();
}

void MainWindow::actionChooseUnlockingBase()
{
    changeStackedWidgetIndex(IndexWelcomeWidget);
    _welcomeWidget->showRecentDatabases();
}

void MainWindow::actionQuit()
{
    close();
}
