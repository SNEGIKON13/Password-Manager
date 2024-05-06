#include "databaseeditor.h"

DatabaseEditor::DatabaseEditor(QObject *parent)
    : DatabaseController{parent}
{}

void DatabaseEditor::updateDatabaseName(CheckIfDatabaseExistWarning *checkIfDatabaseExistWarning, QString newBaseName, bool deleleAndRename)
{
    if (!newBaseName.isEmpty()) {
        QString filePath = DatabaseController::getFilePath();
        QFileInfo fileInfo(filePath);
        QString newFilePath = fileInfo.path() + '/' + newBaseName + "." + fileInfo.suffix();
        // Проверка, существует ли файл базы данных с новым именем
        if (QFile::exists(newFilePath)) {
            checkIfDatabaseExistWarning->show();
            if (deleleAndRename) {
                bool removeSuccess = QFile::remove(newFilePath);
                if (!removeSuccess) {
                    QMessageBox::warning(widget, "Ошибка", "Ошибка при удалении существующего файла базы данных");
                    return; // Прерывание операции, если удаление не удалось
                }
                bool success = QFile::rename(filePath, newFilePath);
                if (success) {
                    setFilePath(newFilePath);
                } else {
                    QMessageBox::warning(widget, "Ошибка", "Ошибка при переименовании файла базы данных");
                }
            }
        } else {
            bool success = QFile::rename(filePath, newFilePath);
            if (success) {
                setFilePath(newFilePath);
            } else {
                QMessageBox::warning(widget, "Ошибка", "Ошибка при переименовании файла базы данных");
            }
        }
    }
}

void DatabaseEditor::updateDatabasePassword(QString newBasePassword)
{
    if (!newBasePassword.isEmpty()) {
        setPassword(newBasePassword);
    }
    else {
        QMessageBox::warning(widget, "Ошибка", "Введите новый пароль базы данных!");
    }
}
