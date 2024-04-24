#include "db_controller.h"

db_controller::db_controller(QObject *parent)
    : QObject{parent}
{}

void db_controller::connectToStandartDataBase()
{

}

void db_controller::closeDataBase()
{
    db.close();
}
