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
