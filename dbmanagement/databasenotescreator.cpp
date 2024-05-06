    #include "dbmanagement/databasenotescreator.h"

DatabaseNotesCreator::DatabaseNotesCreator(QObject *parent)
    : DatabaseController{parent}
{}

void DatabaseNotesCreator::createNewNote(const NoteData &noteData)
{
    openDatabase();
    QSqlQuery query;
    QString insertQuery = "INSERT INTO notes (note_name, login, url, password, other_notes, group_id)"
                          " VALUES (:noteName, :login, :url, :password, :otherNotes, :groupid)";
    query.prepare(insertQuery);
    query.bindValue(":noteName", noteData.noteName);
    query.bindValue(":login", noteData.userName);
    query.bindValue(":url", noteData.url);
    query.bindValue(":password", noteData.passwordEntry);
    query.bindValue(":otherNotes", noteData.otherNotes);
    query.bindValue(":groupid", noteData.group_id);
    query.exec();
    closeDatabase();
}
