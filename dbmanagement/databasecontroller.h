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

class DatabaseController : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseController(QObject *parent = nullptr);

    QMap<int, QString> getGroupNames();
    static void setFilePath(const QString &filePath);
    bool openDatabase();
    void closeDatabase();
    bool isEmptyFilePath();

    // void sortGroup();
    // void sortNotes();

    // void editExistGroup();
    // void editExistNote();

    // void encryptDatabase();
    // void decryptDatabase();

signals:
    void transmitFilePath(const QString &filePath);
    void transmitChangeToMainWindow(int index);

protected:
    static QString filePath;
    QWidget *parentWidget;
    QSqlDatabase db;

};

#endif // DATABASECONTROLLER_H
