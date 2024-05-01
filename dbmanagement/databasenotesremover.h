#ifndef DATABASENOTESREMOVER_H
#define DATABASENOTESREMOVER_H

#include "databasecontroller.h"

class DatabaseNotesRemover : public DatabaseController
{
public:
    explicit DatabaseNotesRemover(QObject *parent = nullptr);
    void deleteNote();
};

#endif // DATABASENOTESREMOVER_H
