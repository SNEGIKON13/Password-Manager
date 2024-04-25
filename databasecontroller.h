#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "EnumWidgets.h"

class DataBaseController : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseController(QObject *parent = nullptr);
    void createDatabase(const QString& filePath);
    void createNotesTable();

signals:
    // void transmitUnlockDataBase();
    void transmitFilePath(const QString &filePath);
    void transmitChangeToMainWindow(int index);

private:
    QSqlDatabase db;
    QWidget *parentWidget;

};

#endif // DATABASECONTROLLER_H
