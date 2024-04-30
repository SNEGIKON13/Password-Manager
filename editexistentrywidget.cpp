#include "editexistentrywidget.h"
#include "ui_editexistentrywidget.h"

EditExistEntryWidget::EditExistEntryWidget(DataBaseController *dbc, QWidget *parent)
    : QDialog(parent), ui(new Ui::EditExistEntryWidget), dbc(dbc)
{
    ui->setupUi(this);
}

EditExistEntryWidget::~EditExistEntryWidget()
{
    delete ui;
}

void EditExistEntryWidget::toFillFields()
{
    dbc->selectNoteData(nd, noteName, groupName);
    ui->noteName->setText(nd.noteName);
    ui->userName->setText(nd.userName);
    ui->url->setText(nd.url);
    ui->passwordEntry->setText(nd.passwordEntry);
    ui->otherNotes->setText(nd.otherNotes);
    ui->chooseGroup->setCurrentIndex(nd.group_id - 1);
}

void EditExistEntryWidget::on_buttonBox_accepted()
{
    clearAllExceptId();

    if (!ui->noteName->text().isEmpty()) {
        if (ui->noteName->text() != nd.noteName) {
            nd.noteName = ui->noteName->text();
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Ввод названия записи обязателен!");
        return;
    }

    if (!ui->passwordEntry->text().isEmpty()) {
        if (ui->passwordEntry->text() != nd.passwordEntry) {
            nd.passwordEntry = ui->passwordEntry->text();
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Ввод пароля обязателен!");
        return;
    }

    if (!ui->userName->text().isEmpty()) {
        if (ui->userName->text() != nd.userName) {
            nd.userName = ui->userName->text();
        }
    } else {
        nd.userName = "";
    }

    if (!ui->url->text().isEmpty()) {
        if (ui->url->text() != nd.url) {
            nd.url = ui->url->text();
        }
    } else {
        nd.url = "";
    }

    if (!ui->otherNotes->toPlainText().isEmpty()) {
        if (ui->otherNotes->toPlainText() != nd.otherNotes) {
            nd.otherNotes = ui->otherNotes->toPlainText();
        }
    } else {
        nd.otherNotes = "";
    }

    dbc->updateNote(nd);
    clearAllExceptId();
    emit transmitChangeToMainWindow(IndexMainWindow);
}


void EditExistEntryWidget::on_buttonBox_rejected()
{
    clearAllExceptId();
    emit transmitChangeToMainWindow(IndexMainWindow);
}

void EditExistEntryWidget::clearAllExceptId()
{
    nd.noteName.clear();
    nd.userName.clear();
    nd.url.clear();
    nd.passwordEntry.clear();
    nd.otherNotes.clear();
    nd.group_id = 1;
}

void EditExistEntryWidget::setNoteName(const QString &noteName, const QString &groupName)
{
    this->noteName = noteName;
    this->groupName = groupName;
}

void EditExistEntryWidget::populateGroupComboBox()
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

