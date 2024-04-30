#include "addnewentrywidget.h"
#include "ui_addnewentrywidget.h"

AddNewEntryWidget::AddNewEntryWidget(DataBaseController *dbc, QWidget *parent)
    : QDialog(parent), ui(new Ui::AddNewEntryWidget), dbc(dbc)    
{
    ui->setupUi(this);
}

AddNewEntryWidget::~AddNewEntryWidget()
{
    delete ui;
}

void AddNewEntryWidget::on_buttonBox_accepted()
{
    clearStruct();

    if (ui->passwordEntry->text().isEmpty() && ui->noteName->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Ввод названия записи и пароля обязателен!");
        return;
    }

    if (!ui->noteName->text().isEmpty()) {
        nd.noteName = ui->noteName->text();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Ввод пароля обязателен!");
        return;
    }
    if (!ui->passwordEntry->text().isEmpty()) {
        nd.passwordEntry = ui->passwordEntry->text();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Ввод названия записи обязателен!");
        return;
    }
    if (!ui->userName->text().isEmpty()) {
        nd.userName = ui->userName->text();
    } else {
        nd.userName = "";
    }

    if (!ui->url->text().isEmpty()) {
        nd.url = ui->url->text();
    } else {
        nd.url = "";
    }

    if (!ui->otherNotes->toPlainText().isEmpty()) {
        nd.otherNotes = ui->otherNotes->toPlainText();
    } else {
        nd.otherNotes = "";
    }

    nd.group_id = ui->chooseGroup->currentIndex() + 1;

    if (nd.group_id == 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите группу!");
        return;
    }

    dbc->createNewNote(nd);

    clearAll();
    emit transmitChangeToMainWindow(IndexMainWindow);
}

void AddNewEntryWidget::on_buttonBox_rejected()
{
    clearAll();
    emit transmitChangeToMainWindow(IndexMainWindow);
}

void AddNewEntryWidget::populateGroupComboBox()
{
    ui->chooseGroup->clear();
    QMap<int, QString> groupNames = dbc->getGroupNames();
    for (auto it = groupNames.begin(); it != groupNames.end(); ++it) {
        int groupId = it.key();
        QString groupName = it.value();
        ui->chooseGroup->insertItem(groupId, groupName);
    }
    ui->chooseGroup->setCurrentIndex(0);
}

void AddNewEntryWidget::clearUiText()
{
    ui->noteName->clear();
    ui->passwordEntry->clear();
    ui->url->clear();
    ui->userName->clear();
    ui->otherNotes->clear();
}

void AddNewEntryWidget::clearStruct()
{
    nd.noteName.clear();
    nd.userName.clear();
    nd.url.clear();
    nd.passwordEntry.clear();
    nd.otherNotes.clear();
    nd.group_id = 1;
}

void AddNewEntryWidget::clearAll()
{
    clearStruct();
    clearUiText();
}


void AddNewEntryWidget::on_chooseGroup_currentIndexChanged(int index)
{
    nd.group_id = index;
}

