#include "databaseencryptor.h"

DatabaseEncryptor::DatabaseEncryptor(QObject *parent)
    : DatabaseController{parent}
{}

void DatabaseEncryptor::encryptDatabase()
{
    QFile databaseFile(filePath);
    if (databaseFile.open(QIODevice::ReadOnly))
    {
        QByteArray databaseContent = databaseFile.readAll();
        databaseFile.close();

        // Создание объекта AES256 с паролем
        AES256 aes(password.toStdString()); // Преобразование QString в std::string

        // Шифрование данных базы данных
        std::string encryptedData = aes.encrypt(databaseContent.toStdString());

        // Преобразование std::string в QByteArray
        QByteArray encryptedDataArray = QByteArray::fromStdString(encryptedData);

        // Запись зашифрованных данных обратно в базу данных
        if (databaseFile.open(QIODevice::WriteOnly))
        {
            databaseFile.write(encryptedDataArray);
            databaseFile.close();
        }
        else
        {
            // Обработка ошибки записи данных
        }
    }
    else
    {
        // Обработка ошибки чтения данных
    }
}
