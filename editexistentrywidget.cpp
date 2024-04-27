#include "editexistentrywidget.h"
#include "ui_editexistentrywidget.h"

EditExistEntryWidget::EditExistEntryWidget(DataBaseController *dbc, QWidget *parent)
    : QDialog(parent), ui(new Ui::EditExistEntryWidget), dbc(dbc)
{
    ui->setupUi(this);
    toFillFields();
}

EditExistEntryWidget::~EditExistEntryWidget()
{
    delete ui;
}

void EditExistEntryWidget::toFillFields()
{
    QString noteId = "your_note_id"; // Идентификатор записи, которую вы хотите получить

    QString queryStr = "SELECT noteName, userName, url, passwordEntry, otherNotes "
                       "FROM YourTableName "
                       "WHERE noteId = :noteId";

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":noteId", noteId);
    if (query.exec() && query.next()) {
        nd.noteName = query.value("noteName").toString();
        nd.userName = query.value("userName").toString();
        nd.url = query.value("url").toString();
        nd.passwordEntry = query.value("passwordEntry").toString();
        nd.otherNotes = query.value("otherNotes").toString();

        // Используйте nd в вашем коде
    } else {
        // Обработка ошибки запроса или записи не найдена
    }
}
