#include "editexistgroupwidget.h"
#include "ui_editexistgroupwidget.h"

EditExistGroupWidget::EditExistGroupWidget(DatabaseGroupsEditor *databaseGroupEditor, QWidget *parent)
    : QDialog(parent), ui(new Ui::EditExistGroupWidget), databaseGroupEditor(databaseGroupEditor)
{
    ui->setupUi(this);
}

EditExistGroupWidget::~EditExistGroupWidget()
{
    delete ui;
}

void EditExistGroupWidget::setGroupName(const QString &groupName)
{
    this->groupName = groupName;
}

void EditExistGroupWidget::on_buttonBox_accepted()
{
    clearAllExceptId();
    if (ui->groupName->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Ввод названия группы обязателен");
        return;
    }
    else {
        gd.groupName = ui->groupName->text();
    }

    if (!ui->otherNotesForGroup->toPlainText().isEmpty()) {
        gd.otherNotes = ui->otherNotesForGroup->toPlainText();
    } else {
        gd.otherNotes = "";
    }

    databaseGroupEditor->updateGroup(gd);
    emit transmitChangedGroupName(gd.groupName);
    emit transmitChangeToMainWindow(IndexMainWindow);
    clearAllExceptId();

}


void EditExistGroupWidget::on_buttonBox_rejected()
{
    clearAllExceptId();
    emit transmitChangeToMainWindow(IndexMainWindow);
}

void EditExistGroupWidget::clearAllExceptId()
{
    gd.groupName.clear();
    gd.otherNotes.clear();
}

void EditExistGroupWidget::toFillFields()
{
    databaseGroupEditor->selectGroupData(gd, groupName);
    ui->groupName->setText(gd.groupName);
    ui->otherNotesForGroup->setText(gd.otherNotes);
}
