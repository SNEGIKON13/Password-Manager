#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QStringList>
#include <QFileInfo>
#include <QFile>
#include <QSettings>
#include <QCryptographicHash>
#include <QRandomGenerator>

class SettingsManager
{
public:
    static QString getRecentDatabasesKey();
    static QStringList loadRecentDatabases();
    static void saveRecentDatabases(const QStringList& databases);
    static QStringList deleteOneListItem(const QString &fp);

    static void removeOldHashRecord(const QString &oldFilePath, const QString &newName);
    static bool comparePasswordHash(const QString& dbName, const QString& enteredPassword);
    static void savePasswordHash(const QString &dbName, const QString &password);

private slots:
    static QByteArray hashNewPassword(const QString &password);
    static QString creatingNewRecordName(const QString &oldFilePath);
    static QByteArray generateSalt();
    static QByteArray hashPasswordEntry(const QString& password, const QByteArray& salt);

private:
    static QString recentDatabasesKey;
    static QSettings settings;
    static const int kSaltLength = 16;
};

#endif // SETTINGSMANAGER_H
