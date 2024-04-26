#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QStringList>
#include <QFile>
#include <QSettings>

class SettingsManager
{
public:
    static QString getRecentDatabasesKey();
    static QStringList loadRecentDatabases();
    static void saveRecentDatabases(const QStringList& databases);
    static QStringList deleteOneListItem(const QString &fp);

private:
    static QString recentDatabasesKey;
    static QSettings settings;
    // static QStringList recentDatabases;
};

#endif // SETTINGSMANAGER_H
