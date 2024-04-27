#include "databasecontroller.h"

DataBaseController::DataBaseController(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

void DataBaseController::createDatabase(const QString& filePath) {
    if (!filePath.isEmpty()) {
        if (openDatabase()) {
            createQueryNotesTable();
            emit transmitFilePath(filePath);
            emit transmitChangeToMainWindow(IndexMainWindow);
            db.close();
        } else {
            QMessageBox::warning(parentWidget, "Ошибка", "Ошибка при открытии базы данных");
        }
    } else {
        QMessageBox::warning(parentWidget, "Ошибка", "Ошибка при создании базы данных: ");
    }
}

void DataBaseController::createQueryNotesTable() {
    QSqlQuery query;
    QString queryRequest = "CREATE TABLE notes ("
                           "id serial PRIMARY KEY,"
                           "note_name VARCHAR(64) NOT NULL,"
                           "login VARCHAR(64),"
                           "url VARCHAR(64),"
                           "password VARCHAR(64) NOT NULL,"
                           "other_notes VARCHAR(500),"
                           "last_modified TIMESTAMP DEFAULT CURRENT_TIMESTAMP,,"
                           "group_id INTEGER"
                           ")";
}

void DataBaseController::showDatabasesGroups(QListWidget *list)
{
    if (!openDatabase()) {
        return;
    }

    QSqlQuery query("SELECT group_id FROM notes", db);

    while (query.next()) {
        QString noteName = query.value(0).toString();
        list->addItem(noteName);
    }

    db.close();
}

void DataBaseController::createNewNote(const NoteData &noteData)
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
    db.close();
}

void DataBaseController::setFilePath(const QString &filePath)
{
    this->filePath = filePath;
}

bool DataBaseController::openDatabase()
{
    db = QSqlDatabase::database();
    db.setDatabaseName(filePath);
    return db.open();
}

bool DataBaseController::isEmptyFilePath()
{
    if (filePath.isEmpty()) {
        return true;
    }
    else {
        return false;
    }
}

