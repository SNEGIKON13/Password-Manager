#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QComboBox>

#include "EnumWidgets.h"
#include "NodeData.h"
#include "GroupData.h"

class DataBaseController : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseController(QObject *parent = nullptr);
    void createDatabase();

    void createQueryNotesTable();
    void createQueryGroupsTable();
    void createNewNote(const NoteData &noteData);
    void createNewGroup(const GroupData &groupData);

    void showDatabasesGroups(QListWidget *list);
    void showNotesByGroupName(QTableWidget *table, const QString &groupName);
    void selectNoteData(NoteData &noteData, const QString &noteName, const QString &groupName);
    void updateNote(NoteData &noteData);
    void selectGroupData(GroupData &groupData);

    void setFilePath(const QString &filePath);

    bool openDatabase();
    void closeDatabase();
    bool isEmptyFilePath();
    QMap<int, QString> getGroupNames();

    // void sortGroup();
    // void sortNotes();

    // void editExistGroup();
    // void editExistNote();

    // void encryptDatabase();
    // void decryptDatabase();

signals:
    void transmitFilePath(const QString &filePath);
    void transmitChangeToMainWindow(int index);

private slots:
    GroupData creatingStandartGroup();

private:
    QString filePath;
    QSqlDatabase db;
    QWidget *parentWidget;

};

#endif // DATABASECONTROLLER_H
