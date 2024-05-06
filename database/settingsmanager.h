#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QStringList>
#include <QFileInfo>
#include <QFile>
#include <QSettings>
#include <QCryptographicHash>

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
    static QByteArray hashPassword(const QString &password);

    static QString creatingNewRecordName(const QString &oldFilePath);

private:
    static QString recentDatabasesKey;
    static QSettings settings;
    // static QStringList recentDatabases;
};

#endif // SETTINGSMANAGER_H
