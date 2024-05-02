#include "notes/editexistnotewidget.h"
#include "ui_editexistnotewidget.h"

EditExistNoteWidget::EditExistNoteWidget(DatabaseNotesEditor *databaseNotesEditor, QWidget *parent)
    : QDialog(parent), ui(new Ui::EditExistNoteWidget), databaseNotesEditor(databaseNotesEditor)
{
    ui->setupUi(this);
}

EditExistNoteWidget::~EditExistNoteWidget()
{
    delete ui;
}

void EditExistNoteWidget::toFillFields()
{
    databaseNotesEditor->selectNoteData(nd, id);
    ui->noteName->setText(nd.noteName);
    ui->userName->setText(nd.userName);
    ui->url->setText(nd.url);
    ui->passwordEntry->setText(nd.passwordEntry);
    ui->otherNotes->setText(nd.otherNotes);
    ui->chooseGroup->setCurrentIndex(nd.group_id - 1);
}

void EditExistNoteWidget::on_buttonBox_accepted()
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

    databaseNotesEditor->updateNote(nd);
    clearAllExceptId();
    emit transmitChangeToMainWindow(IndexMainWindow);
}


void EditExistNoteWidget::on_buttonBox_rejected()
{
    clearAllExceptId();
    emit transmitChangeToMainWindow(IndexMainWindow);
}

void EditExistNoteWidget::setNoteId(const int noteId)
{
    this->id = noteId;
}

void EditExistNoteWidget::populateGroupComboBox()
{
    ui->chooseGroup->clear();
    QMap<int, QString> groupNames = databaseNotesEditor->getGroupNames();
    for (auto it = groupNames.begin(); it != groupNames.end(); ++it) {
        int groupId = it.key();
        QString groupName = it.value();
        ui->chooseGroup->insertItem(groupId, groupName);
    }
    ui->chooseGroup->setCurrentIndex(0);
}

void EditExistNoteWidget::clearAllExceptId()
{
    nd.noteName.clear();
    nd.userName.clear();
    nd.url.clear();
    nd.passwordEntry.clear();
    nd.otherNotes.clear();
    nd.group_id = 1;
}
