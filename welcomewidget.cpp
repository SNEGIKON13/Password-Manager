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
    filePath = QFileDialog::getOpenFileName(this, "Открыть базу данных",
            QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), "База данных (*.db)");
    if (!filePath.isEmpty()) {
        emit transmitFilePath(filePath);
        emit transmitChangeToUnlockBase(IndexUnlockBaseWidget);
    }
}

void WelcomeWidget::on_createBaseButton_clicked()
{
    emit transmitChangeToCreateBase(IndexСreateBaseWidget);
}

void WelcomeWidget::changeRecentDatabasesStatusText()
{
    if (!recentDatabases.isEmpty()) {
        QString text = "Ранее использованные базы данных:";

        QFont font;
        font.setPointSize(14);
        font.setWeight(QFont::Bold);

        ui->dbstatus->setText(text);
        ui->dbstatus->setFont(font);
        ui->dbstatus->setAlignment(Qt::AlignCenter);
    }
}

void WelcomeWidget::showRecentDatabases()
{
    recentDatabases = SettingsManager::loadRecentDatabases();
    ui->listWidget->clear();
    ui->listWidget->addItems(recentDatabases);
    changeRecentDatabasesStatusText();
}

void WelcomeWidget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    filePath = item->text();
    QFile databaseFile(filePath);
    if (databaseFile.exists()) {
        emit transmitFilePath(filePath);
        emit transmitChangeToUnlockBase(IndexUnlockBaseWidget);
    }
    else {
        QMessageBox::warning(this, "Базы данных нет!", "К сожалению, на данный момент по указанному"
                                                       " адресу база данных отсутствует");
        recentDatabases = SettingsManager::deleteOneListItem(filePath);
        ui->listWidget->clear();
        ui->listWidget->addItems(recentDatabases);
    }
}

void WelcomeWidget::on_deleteAllNonExistDb_clicked()
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QString itemText = ui->listWidget->item(i)->text();
        QFile databaseFile(itemText);
        if (!databaseFile.exists()) {
            recentDatabases = SettingsManager::deleteOneListItem(itemText);
            ui->listWidget->clear();
            ui->listWidget->addItems(recentDatabases);
        }
    }
}

