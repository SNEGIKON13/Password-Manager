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

void EditExistGroupWidget::on_buttonBox_accepted()
{
    // databaseGroupEditor->selectNoteData(nd, 1);
    // ui->groupName->setText(gd.groupName);
    // ui->otherNotesForGroup->setText(gd.otherNotes);
}


void EditExistGroupWidget::on_buttonBox_rejected()
{

}

void EditExistGroupWidget::clearAll()
{

}

void EditExistGroupWidget::toFillFields()
{

}
