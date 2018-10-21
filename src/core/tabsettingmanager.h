#ifndef TABSETTINGMANAGER_H
#define TABSETTINGMANAGER_H

#include <tabsetting.h>
#include <QList>

class TabSettingManager
{
public:
  enum Content
  {
    Linker,
    SearchPaths,
    BuildEnvironment
  };

  TabSettingManager();

  void load(SettingsManager *settings);
  void save(SettingsManager *settings);

  TabSetting * tabSetting(int index) const;
private:
  QList<TabSetting*> tabsSettings;
};

#endif // TABSETTINGMANAGER_H
