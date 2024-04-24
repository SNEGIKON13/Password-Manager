#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>

class db_controller : public QObject
{
    Q_OBJECT
public:
    explicit db_controller(QObject *parent = nullptr);
    void connectToStandartDataBase();
    void closeDataBase();

signals:

private:
    QSqlDatabase db;
};

#endif // DB_CONTROLLER_H
