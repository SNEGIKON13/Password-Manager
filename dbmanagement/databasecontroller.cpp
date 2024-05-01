#include "databasecontroller.h"

DatabaseController::DatabaseController(QObject *parent)
    : QObject{parent}
{}

QString DatabaseController::filePath;

QMap<int, QString> DatabaseController::getGroupNames()
{
    openDatabase();
    QMap<int, QString> groupMap;

    QSqlQuery query;
    query.exec("SELECT id, group_name FROM groups");

    while (query.next())
    {
        int groupId = query.value("id").toInt();
        QString groupName = query.value("group_name").toString();
        groupMap.insert(groupId, groupName);
    }
    closeDatabase();
    return groupMap;
}


void DatabaseController::setFilePath(const QString &filePath)
{
    DatabaseController::filePath = filePath;
}

bool DatabaseController::openDatabase()
{
    if (!db.isOpen()) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(filePath);
        return db.open();
    }
    else {
        return true;
    }
}

void DatabaseController::closeDatabase()
{
    if (db.isOpen())
    {
        db.close();
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
}

bool DatabaseController::isEmptyFilePath()
{
    if (filePath.isEmpty()) {
        return true;
    }
    else {
        return false;
    }
}

