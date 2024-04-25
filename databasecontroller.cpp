#include "databasecontroller.h"

DataBaseController::DataBaseController(QObject *parent)
    : QObject{parent}
{}

void DataBaseController::createDatabase(const QString& filePath) {
    if (!filePath.isEmpty()) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(filePath);
        if (db.open()) {
            createNotesTable();
            emit transmitFilePath(filePath);
            emit transmitChangeToMainWindow(IndexMainWindow);
            db.close();
        } else {
            QMessageBox::warning(parentWidget, "Ошибка", "Ошибка при открытии базы данных");
        }
    } else {
        QMessageBox::warning(parentWidget, "Ошибка", "Ошибка при создании базы данных: ");
    }
}

void DataBaseController::createNotesTable() {
    QSqlQuery query;
    QString queryRequest = "CREATE TABLE notes ("
                           "id serial PRIMARY KEY,"
                           "note_name VARCHAR(64) NOT NULL,"
                           "login VARCHAR(64),"
                           "url VARCHAR(64),"
                           "password VARCHAR(64) NOT NULL,"
                           "other_notes VARCHAR(500),"
                           "last_modified TIMESTAMP"
                           ")";
    query.exec(queryRequest);
}
