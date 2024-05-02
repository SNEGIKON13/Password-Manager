#include "databasenotesremover.h"

DatabaseNotesRemover::DatabaseNotesRemover(QObject *parent)
    : DatabaseController{parent}
{}

void DatabaseNotesRemover::deleteNote(const int noteId)
{
    openDatabase();
    QSqlQuery query;
    query.prepare("DELETE FROM notes WHERE id = :id");
    query.bindValue(":id", noteId);
    if (query.exec()) {
        // Запись успешно удалена
    } else {
        closeDatabase();  // Закрыть соединение с базой данных перед выбросом исключения
        throw std::runtime_error("Ошибка при удалении записи");  // Бросить исключение
    }
    closeDatabase();
}
