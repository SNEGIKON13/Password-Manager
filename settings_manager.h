#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

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

#endif // SETTINGS_MANAGER_H
