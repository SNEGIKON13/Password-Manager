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
        AES256 aes(tryPassword.toStdString());

        std::string decryptedData;
        try {
            decryptedData = aes.decrypt(databaseContent.toStdString());
        } catch (const std::invalid_argument& e) {
            return false;
        }
        QByteArray decryptedDataArray = QByteArray::fromStdString(decryptedData);
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
