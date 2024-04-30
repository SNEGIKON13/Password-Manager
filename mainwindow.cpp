#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::MWC_ConnectOfQActions()
{
    connect(ui->actionCreateDatabase, &QAction::triggered,
            this, &MainWindow::actionCreateDatabase);
    connect(ui->actionChooseUnlockingBase, &QAction::triggered,
            this, &MainWindow::actionChooseUnlockingBase);
    connect(ui->actionCreateNewNote, &QAction::triggered,
            this, &MainWindow::actionCreateNewNote);
    connect(ui->actionChangeNote, &QAction::triggered,
            this, &MainWindow::actionChangeNote);
    connect(ui->actionDeleteNote, &QAction::triggered,
            this, &MainWindow::actionDeleteNote);
    connect(ui->actionCreateGroup, &QAction::triggered,
            this, &MainWindow::actionCreateGroup);
    connect(ui->actionChangeGroup, &QAction::triggered,
            this, &MainWindow::actionChangeGroup);
    connect(ui->actionDeleteGroup, &QAction::triggered,
            this, &MainWindow::actionDeleteGroup);
    connect(ui->actionSort, &QAction::triggered,
            this, &MainWindow::actionSort);
    connect(ui->actionQuit, &QAction::triggered,
            this, &MainWindow::actionQuit);
}

void MainWindow::MWC_InsertStackedWidgets()
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(1, _welcomeWidget);
    ui->stackedWidget->insertWidget(2, _addNewEntryWidget);
    ui->stackedWidget->insertWidget(3, _editExistEntryWidget);
    ui->stackedWidget->insertWidget(4, _addNewGroupWidget);
    ui->stackedWidget->insertWidget(5, _editExistGroupWidget);
    ui->stackedWidget->setCurrentIndex(IndexWelcomeWidget);
}

void MainWindow::MWC_CreationOfUiForms()
{
    _dbc = new DataBaseController(this);
    _welcomeWidget = new WelcomeWidget(this);
    _welcomeWidget->showRecentDatabases();
    _unlockBaseWidget = new UnlockBaseWindow(this);
    _createBaseWidget = new CreateBaseWidget(_dbc, this);
    _addNewEntryWidget = new AddNewEntryWidget(_dbc, this);
    _editExistEntryWidget = new EditExistEntryWidget(_dbc, this);
    _addNewGroupWidget = new AddNewGroupWidget(_dbc, this);
    _editExistGroupWidget = new EditExistGroupWidget(_dbc, this);
}

void MainWindow::MWC_ConnectOfPushButtons()
{
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
}

void MainWindow::MWC_ConnectsOther()
{
    connect(_welcomeWidget, &WelcomeWidget::transmitFilePath,
            this, &MainWindow::receivePossibleFilePath);
    connect(_unlockBaseWidget, &UnlockBaseWindow::transmitDataBasePath,
            this, &MainWindow::receiveFilePath);
    connect(_dbc, &DataBaseController::transmitFilePath,
            this, &MainWindow::receiveFilePath);
    connect(_addNewEntryWidget, &AddNewEntryWidget::transmitChangeToMainWindow,
            this, &MainWindow::changeStackedWidgetIndex);
    connect(_editExistEntryWidget, &EditExistEntryWidget::transmitChangeToMainWindow,
            this, &MainWindow::changeStackedWidgetIndex);
    connect(_addNewGroupWidget, &AddNewGroupWidget::transmitChangeToMainWindow,
            this, &MainWindow::changeStackedWidgetIndex);
    connect(_editExistGroupWidget, &EditExistGroupWidget::transmitChangeToMainWindow,
            this, &MainWindow::changeStackedWidgetIndex);
}

void MainWindow::MWC_CreationOfToolBar()
{
    _toolbar = new QToolBar(this);
    QSize iconSize(48, 48);
    addToolBar(_toolbar);
    _toolbar->setIconSize(iconSize);
    _toolbar->setMovable(false);

    _toolbar->addAction(ui->actionCreateDatabase);
    ui->actionCreateDatabase->setIcon(QIcon("://Images/CreateDatabase.png"));
    _toolbar->addAction(ui->actionChooseUnlockingBase);
    ui->actionChooseUnlockingBase->setIcon(QIcon("://Images/UnlockDatabase.png"));
    _toolbar->addAction(ui->actionLockDatabase_2);
    ui->actionLockDatabase_2->setIcon(QIcon("://Images/LockDatabase.png"));

    _toolbar->addAction(ui->actionCreateNewNote);
    ui->actionCreateNewNote->setIcon(QIcon("://Images/CreateNewNote.png"));
    _toolbar->addAction(ui->actionChangeNote);
    ui->actionChangeNote->setIcon(QIcon("://Images/ChangeExistNote.png"));
    _toolbar->addAction(ui->actionDeleteNote);
    ui->actionDeleteNote->setIcon(QIcon("://Images/DeleteNote.png"));

    _toolbar->addAction(ui->actionCreateGroup);
    ui->actionCreateGroup->setIcon(QIcon("://Images/CreateGroup.png"));
    _toolbar->addAction(ui->actionChangeGroup);
    ui->actionChangeGroup->setIcon(QIcon("://Images/ChangeGroup.png"));
    _toolbar->addAction(ui->actionDeleteGroup);
    ui->actionDeleteGroup->setIcon(QIcon("://Images/DeleteGroup.png"));
    _toolbar->addAction(ui->actionSort);
    ui->actionSort->setIcon(QIcon("://Images/Sort.png"));

    _toolbar->addAction(ui->actionAboutProgram);
    ui->actionAboutProgram->setIcon(QIcon("://Images/About.png"));
    _toolbar->addAction(ui->actionQuit);
    ui->actionQuit->setIcon(QIcon("://Images/Quit.png"));

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MWC_CreationOfUiForms();
    MWC_InsertStackedWidgets();
    MWC_ConnectOfQActions();
    MWC_ConnectOfPushButtons();
    MWC_ConnectsOther();
    MWC_CreationOfToolBar();
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
    ui->groupListWidget->clear();
    _dbc->showDatabasesGroups(ui->groupListWidget);
}

void MainWindow::adjustTableWidget()
{
    ui->notesTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->notesTableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->notesTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->notesTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->notesTableWidget->verticalHeader()->setVisible(false);
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
    if (ui->stackedWidget->currentIndex() == IndexMainWindow) {
        showDatabasesGroups();
        adjustTableWidget();
        _dbc->showNotesByGroupName(ui->notesTableWidget, groupName);
        _addNewEntryWidget->populateGroupComboBox();
        _editExistEntryWidget->populateGroupComboBox();
    }
}

void MainWindow::receiveFilePath(const QString &fp)
{
    filePath = fp;
    setDatabaseNameText();
    saveNewFilePath();
    _dbc->setFilePath(fp);
}






void MainWindow::actionCreateNewNote()
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
    QList<QTableWidgetItem*> selectedItems = ui->notesTableWidget->selectedItems();
    if (!selectedItems.isEmpty()) {
        QTableWidgetItem* selectedItem = selectedItems.first();
        QString itemName = selectedItem->text();
        _editExistEntryWidget->setNoteName(itemName, groupName);
        _editExistEntryWidget->toFillFields();
        changeStackedWidgetIndex(IndexEditExistEntryWidget);
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Выберите запись для изменения!");
    }
}

void MainWindow::actionDeleteNote()
{
    if (_dbc->isEmptyFilePath()) {
        QMessageBox::warning(this, "Ошибка", "Cначала войдите в базу данных!");
        //TODO
    }
}

void MainWindow::actionCreateGroup()
{
    if (_dbc->isEmptyFilePath()) {
        QMessageBox::warning(this, "Ошибка", "Cначала войдите в базу данных!");
    }
    else {
        changeStackedWidgetIndex(IndexAddNewGroupWidget);
    }
}

void MainWindow::actionChangeGroup()
{
    if (_dbc->isEmptyFilePath()) {
        QMessageBox::warning(this, "Ошибка", "Cначала войдите в базу данных!");
    }
    else {
        changeStackedWidgetIndex(IndexEditExistGroupWidget);
    }
}

void MainWindow::actionDeleteGroup()
{
    if (_dbc->isEmptyFilePath()) {
        QMessageBox::warning(this, "Ошибка", "Cначала войдите в базу данных!");
        //TODO
    }
}

void MainWindow::actionSort()
{
    if (_dbc->isEmptyFilePath()) {
        QMessageBox::warning(this, "Ошибка", "Cначала войдите в базу данных!");
        //TODO
    }
}

void MainWindow::actionCreateDatabase()
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


void MainWindow::on_groupListWidget_itemClicked(QListWidgetItem *item)
{
    groupName = item->text();
    _dbc->showNotesByGroupName(ui->notesTableWidget, groupName);
}

