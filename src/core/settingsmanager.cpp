#include "settingsmanager.h"

SettingsManager::SettingsManager(const QString &name)
{
  setName(name);
}

SettingsManager::SettingsManager(const SettingsManager *other)
{
  foreach(QString settingName,other->allSettingsNames())
    {
      addSetting(settingName,other->setting(settingName));
    }
}

void SettingsManager::addSetting(const QString &name, const QVariant &value)
{
  settings.insert(name,value);
}

void SettingsManager::clearSetting(const QString &name)
{
  settings.remove(name);
}

QStringList SettingsManager::allSettingsNames() const
{
  return settings.keys();
}

QVariant SettingsManager::setting(const QString &name) const
{
  return settings.value(name);
}

void SettingsManager::setName(const QString &name)
{
  addSetting(Core::Project::NAME,name);
}

QString SettingsManager::name() const
{
  return string(Core::Project::NAME);
}

QString SettingsManager::type() const
{
  return QString();
}



