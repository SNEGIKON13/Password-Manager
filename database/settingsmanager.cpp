#include "database/settingsmanager.h"

QSettings SettingsManager::settings("config.ini", QSettings::IniFormat);

QString SettingsManager::recentDatabasesKey = "recentDatabases";

QString SettingsManager::getRecentDatabasesKey()
{
    return recentDatabasesKey;
}

QStringList SettingsManager::loadRecentDatabases()
{
    return settings.value(getRecentDatabasesKey()).toStringList();
}

void SettingsManager::saveRecentDatabases(const QStringList &databases)
{
    settings.setValue(getRecentDatabasesKey(), databases);
}

QStringList SettingsManager::deleteOneListItem(const QString &fp)
{
    QStringList recentDatabases = SettingsManager::loadRecentDatabases();
    recentDatabases.removeOne(fp);
    SettingsManager::saveRecentDatabases(recentDatabases);
    return loadRecentDatabases();
}

void SettingsManager::savePasswordHash(const QString& dbName, const QString& password)
{
    QByteArray passwordHash = hashPassword(password);
    QString hashKey = dbName + "_hash";
    settings.setValue(hashKey, passwordHash);
}

bool SettingsManager::comparePasswordHash(const QString& filePath, const QString& enteredPassword)
{
    QString hashKey = creatingNewRecordName(filePath);
    QByteArray savedHash = settings.value(hashKey).toByteArray();
    QByteArray enteredHash = hashPassword(enteredPassword);
    return savedHash == enteredHash;
}

QByteArray SettingsManager::hashPassword(const QString& password)
{
    QByteArray passwordData = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256);
    return hash;
}

QString SettingsManager::creatingNewRecordName(const QString &oldFilePath)
{
    QFileInfo fileInfo(oldFilePath);
    QString dbName = fileInfo.baseName();
    QString oldHashKey = dbName + "_hash";

    return oldHashKey;
}

void SettingsManager::removeOldHashRecord(const QString &oldFilePath, const QString &newName)
{
    QString oldHashKey = creatingNewRecordName(oldFilePath);
    if (oldHashKey == newName) {
        return;
    }
    settings.remove(oldHashKey);
}
