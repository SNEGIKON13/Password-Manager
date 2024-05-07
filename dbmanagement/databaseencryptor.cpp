#include "databaseencryptor.h"

DatabaseEncryptor::DatabaseEncryptor(QObject *parent)
    : DatabaseController{parent}
{}

void DatabaseEncryptor::encryptDatabase()
{
    QFile databaseFile(filePath);
    if (databaseFile.open(QIODevice::ReadOnly))
    {
        //
        QByteArray databaseContent = databaseFile.readAll();
        databaseFile.close();
        AES256 aes(password.toStdString());
        std::string encryptedData = aes.encrypt(databaseContent.toStdString());
        QByteArray encryptedDataArray = QByteArray::fromStdString(encryptedData);
        if (databaseFile.open(QIODevice::WriteOnly))
        {
            databaseFile.write(encryptedDataArray);
            databaseFile.close();
        }
        else
        {
            throw std::runtime_error("ERRORENCRYPTOR");
        }
    }
    else
    {
        throw std::runtime_error("ERRORENCRYPTOR");
    }
}
