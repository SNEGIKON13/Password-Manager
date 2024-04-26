#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>

#include "EnumWidgets.h"
#include "NodeData.h"

class DataBaseController : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseController(QObject *parent = nullptr);
    void createDatabase(const QString &filePath);
    void createQueryNotesTable();
    void showDatabase(QListWidget *list);
    void createNewNote(const NoteData &noteData);
    void setFilePath(const QString &filePath);
    bool openDatabase();
    bool isEmptyFilePath();

signals:
    // void transmitUnlockDataBase();
    void transmitFilePath(const QString &filePath);
    void transmitChangeToMainWindow(int index);

private:
    QString filePath;
    QSqlDatabase db;
    QWidget *parentWidget;

};

#endif // DATABASECONTROLLER_H
