#include "databasedisplay.h"

DatabaseDisplay::DatabaseDisplay(QObject *parent)
    : DatabaseController{parent}
{}

void DatabaseDisplay::showDatabasesGroups(QListWidget *list)
{

    openDatabase();
    QSqlQuery query;
    query.exec("SELECT group_name FROM groups");
    while (query.next()) {
        QString groupName = query.value(0).toString();
        list->addItem(groupName);
    }
    closeDatabase();
}

void DatabaseDisplay::showNotesByGroupName(QTableWidget *table, const QString& groupName)
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
        qDebug() << "Error executing query: " << query.lastError().text();
    }
    closeDatabase();
}
