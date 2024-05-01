#include "dbmanagement/databasenoteseditor.h"

DatabaseNotesEditor::DatabaseNotesEditor(QObject *parent)
    : DatabaseController{parent}
{}

void DatabaseNotesEditor::selectNoteData(NoteData &noteData, const QString &noteName, const QString &groupName)
{
    openDatabase();

    QSqlQuery query;
    QString queryRequest = "SELECT id, note_name, login, url, password, other_notes,"
                           " group_id FROM notes WHERE note_name = :noteName AND group_id ="
                           " (SELECT id FROM groups WHERE group_name = :groupName)";
    query.prepare(queryRequest);
    query.bindValue(":noteName", noteName);
    query.bindValue(":groupName", groupName);

    if (query.exec())
    {
        if (query.next())
        {
            noteData.id = query.value("id").toInt();
            noteData.noteName = query.value("note_name").toString();
            noteData.userName = query.value("login").toString();
            noteData.url = query.value("url").toString();
            noteData.passwordEntry = query.value("password").toString();
            noteData.otherNotes = query.value("other_notes").toString();
            noteData.group_id = query.value("group_id").toInt();
        }
        else
        {
            qDebug() << "Record not found.";
        }
    }
    else
    {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    closeDatabase();
}

void DatabaseNotesEditor::updateNote(NoteData &noteData)
{
    openDatabase();

    QSqlQuery query;
    QString queryRequest = "UPDATE notes SET note_name = :noteName, group_id = :groupId,"
                           " login = :login, url = :url, password = :password, other_notes = :otherNotes WHERE id = :noteId";
    query.prepare(queryRequest);
    query.bindValue(":noteName", noteData.noteName);
    query.bindValue(":groupId", noteData.group_id);
    query.bindValue(":login", noteData.userName);
    query.bindValue(":url", noteData.url);
    query.bindValue(":password", noteData.passwordEntry);
    query.bindValue(":otherNotes", noteData.otherNotes);
    query.bindValue(":noteId", noteData.id);

    if (query.exec())
    {
        qDebug() << "Record updated successfully.";
    }
    else
    {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    closeDatabase();
}
