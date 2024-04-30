#include "databasecontroller.h"

DataBaseController::DataBaseController(QObject *parent)
    : QObject{parent}
{}

GroupData DataBaseController::creatingStandartGroup()
{
    GroupData gd;
    gd.groupName = "PasswordManager";
    gd.otherNotes = "Группа по умолчанию.";
    return gd;
}

void DataBaseController::createDatabase() {
    if (!filePath.isEmpty()) {
        if (openDatabase()) {
            createQueryNotesTable();
            createQueryGroupsTable();
            GroupData gd = creatingStandartGroup();
            createNewGroup(gd);
            emit transmitFilePath(filePath);
            emit transmitChangeToMainWindow(IndexMainWindow);
            closeDatabase();
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
                           "id INTEGER PRIMARY KEY,"
                           "group_id INTEGER,"
                           "note_name VARCHAR(64) NOT NULL,"
                           "login VARCHAR(64),"
                           "url VARCHAR(64),"
                           "password VARCHAR(64) NOT NULL,"
                           "other_notes VARCHAR(500),"
                           "last_modified TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                           "FOREIGN KEY (group_id) REFERENCES groups(id)"
                           ")";
    query.exec(queryRequest);
}

void DataBaseController::createQueryGroupsTable()
{
    QSqlQuery query;
    QString queryRequest = "CREATE TABLE groups ("
                           "id INTEGER PRIMARY KEY,"
                           "group_name VARCHAR(64) NOT NULL,"
                           "other_notes VARCHAR(500)"
                           ")";
    query.exec(queryRequest);
}

void DataBaseController::showDatabasesGroups(QListWidget *list)
{

    openDatabase();
    QSqlQuery query;
    QString queryRequest = "SELECT group_name FROM groups";
    query.prepare(queryRequest);
    query.exec();

    while (query.next()) {
        QString groupName = query.value(0).toString();
        list->addItem(groupName);
    }
    closeDatabase();
}

QMap<int, QString> DataBaseController::getGroupNames()
{
    openDatabase();
    QMap<int, QString> groupMap;

    QSqlQuery query;
    QString queryRequest = "SELECT id, group_name FROM groups";
    query.exec(queryRequest);

    while (query.next())
    {
        int groupId = query.value("id").toInt();
        QString groupName = query.value("group_name").toString();
        groupMap.insert(groupId, groupName);
    }
    closeDatabase();
    return groupMap;
}

void DataBaseController::selectNoteData(NoteData &noteData, const QString &noteName, const QString &groupName)
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

void DataBaseController::updateNote(NoteData &noteData)
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

void DataBaseController::selectGroupData(GroupData &groupData)
{

}

void DataBaseController::showNotesByGroupName(QTableWidget *table, const QString& groupName)
{

    openDatabase();
    QSqlQuery query;
    QString queryRequest = "SELECT notes.note_name, notes.login, notes.url, notes.other_notes, notes.last_modified "
                           "FROM notes "
                           "JOIN groups ON notes.group_id = groups.id "
                           "WHERE groups.group_name = " + QString("'%1'").arg(groupName);

    query.prepare(queryRequest);
    query.bindValue(":groupName", groupName);

    if (query.exec())
    {
        table->clearContents();
        table->setRowCount(0);
        int row = 0;
        while (query.next())
        {
            table->insertRow(row);

            for (int col = 0; col < 5; ++col)
            {
                QTableWidgetItem* item = new QTableWidgetItem(query.value(col).toString());
                table->setItem(row, col, item);
            }

            ++row;
        }
    }
    else
    {
        // Обработка ошибки выполнения запроса
        qDebug() << "Error executing query: " << query.lastError().text();
    }
    closeDatabase();
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
    closeDatabase();
}

void DataBaseController::createNewGroup(const GroupData &groupData)
{
    openDatabase();
    QSqlQuery query;
    query.prepare("INSERT INTO groups (group_name, other_notes) VALUES (:groupName, :otherNotes)");
    query.bindValue(":groupName", groupData.groupName);
    query.bindValue(":otherNotes", groupData.otherNotes);
    query.exec();
    closeDatabase();
}

void DataBaseController::setFilePath(const QString &filePath)
{
    this->filePath = filePath;
}

//Простые взаимодействия

bool DataBaseController::openDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filePath);
    return db.open();
}

void DataBaseController::closeDatabase()
{
    if (db.isOpen())
    {
        db.close();
    }
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
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

