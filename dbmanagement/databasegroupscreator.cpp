#include "databasegroupscreator.h"

DatabaseGroupsCreator::DatabaseGroupsCreator(QObject *parent)
    : DatabaseController{parent}
{}

void DatabaseGroupsCreator::createNewGroup(const GroupData &groupData)
{
    openDatabase();
    QSqlQuery query;
    query.prepare("INSERT INTO groups (group_name, other_notes)"
                  " VALUES (:groupName, :otherNotes)");
    query.bindValue(":groupName", groupData.groupName);
    query.bindValue(":otherNotes", groupData.otherNotes);
    query.exec();
    closeDatabase();
}
