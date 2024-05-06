#include "databasedecryptor.h"

DatabaseDecryptor::DatabaseDecryptor(QObject *parent)
    : DatabaseController{parent}
{}

bool DatabaseDecryptor::decryptDatabase()
{
    QFile databaseFile(filePath);
    if (databaseFile.open(QIODevice::ReadOnly))
    {
        QByteArray databaseContent = databaseFile.readAll();
        databaseFile.close();

        // Создание объекта AES256 с паролем
        AES256 aes(tryPassword.toStdString()); // Преобразование QString в std::string

        std::string decryptedData;
        // Расшифровка данных базы данных
        try {
            decryptedData = aes.decrypt(databaseContent.toStdString());
            // Дополнительный код для обработки расшифрованных данных
        } catch (const std::invalid_argument& e) {
            // Обработка исключения std::invalid_argument
            // В этом блоке вы можете выполнить необходимые действия при возникновении исключения
            // Например, вывести сообщение об ошибке или выполнить другие действия восстановления
            return false;
        }

        // Преобразование std::string в QByteArray
        QByteArray decryptedDataArray = QByteArray::fromStdString(decryptedData);

        // Запись расшифрованных данных обратно в базу данных
        if (databaseFile.open(QIODevice::WriteOnly))
        {
            databaseFile.write(decryptedDataArray);
            databaseFile.close();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
