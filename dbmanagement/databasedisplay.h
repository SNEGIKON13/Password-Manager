#ifndef DATABASEDISPLAY_H
#define DATABASEDISPLAY_H

#include "databasecontroller.h"

class DatabaseDisplay : public DatabaseController
{
public:
    explicit DatabaseDisplay(QObject *parent = nullptr);
    void showDatabasesGroups(QListWidget *list);
    void showNotesByGroupName(QTableWidget *table, const QString &groupName);
};

#endif // DATABASEDISPLAY_H
