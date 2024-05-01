#include "databasegroupseditor.h"

DatabaseGroupsEditor::DatabaseGroupsEditor(QObject *parent)
    : DatabaseController{parent}
{}

void DatabaseGroupsEditor::selectGroupData(GroupData &groupData, QString groupName)
{
    openDatabase();
    QSqlQuery query;
    QString selectQuery = "SELECT * FROM groups WHERE group_name = :groupName";
    query.prepare(selectQuery);
    query.bindValue(":groupName", groupName);
    query.exec();

    while (query.next()) {
        groupData.id = query.value(0).toInt();
        groupData.groupName = query.value(1).toString();
        groupData.otherNotes = query.value(2).toString();
    }
    closeDatabase();
}

void DatabaseGroupsEditor::updateGroup(GroupData &groupData)
{
    openDatabase();
    QSqlQuery query;
    QString updateQuery = "UPDATE groups SET group_name = :groupName, other_notes = :otherNotes WHERE id = :groupId";
    query.prepare(updateQuery);
    query.bindValue(":groupName", groupData.groupName);
    query.bindValue(":otherNotes", groupData.otherNotes);
    query.bindValue(":groupId", groupData.id);
    query.exec();
        closeDatabase();
}
