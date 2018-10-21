#include "tabsettingmanager.h"
#include "tabsetting.h"
#include "core_constants.h"

#include <QTabWidget>
#include <QTreeWidget>
#include <buildvariables.h>


TabSettingManager::TabSettingManager()
{
//  TabSetting *tabSetting;
//  tabSetting =  new TabSetting;
//  tabSetting->addContent(QObject::tr("Libs"),Core::Project::LIBS);

//  tabsSettings.append(tabSetting);

//  tabSetting = new TabSetting;
//  tabSetting->addContent(QObject::tr("Executable Directories"),Core::Project::EXECUTABLES);
//  tabSetting->addContent(QObject::tr("Compiler"),Core::Project::INCLUDES);
//  tabSetting->addContent(QObject::tr("Linker"),Core::Project::INCLUDELIBS);
//  tabSetting->addContent(QObject::tr("Resource compiler"),Core::Project::RESCOMPILER);

//  tabsSettings.append(tabSetting);

//  tabSetting =  new TabSetting;
//  tabSetting->createAddButtonMenu();
//  tabSetting->addContent(QObject::tr("Custom Variables"),Core::Project::CUSTOMVARIABLES,false);
//  tabSetting->setCurrentListHeaderLabels(QStringList()<<"Key"<<"Value");


//  tabsSettings.append(tabSetting);
}

void TabSettingManager::load(SettingsManager * settings)
{
//  foreach (TabSetting *tabSetting, tabsSettings) {

//      tabSetting->clearAll();

//      for(int i = 0; i < tabSetting->tabWidget()->count() ;i++)
//        {
//          QString elem = tabSetting->tabElement(i);

//          if(tabSetting->currentList()->columnCount() == 1)
//            tabSetting->addItems(settings->stringList(elem),i);
//          else
//            {
//              BuildVariables * buildVariables = new BuildVariables;
//              buildVariables->fromList(settings->stringList(elem));

//              foreach(QString var,buildVariables->variables())
//                {
//                  tabSetting->addItem(QStringList()<<var<<buildVariables->value(var));
//                }

//              delete buildVariables;
//            }
//        }
//    }
//}

//void TabSettingManager::save(SettingsManager *settings)
//{
//  foreach (TabSetting *tabSetting, tabsSettings) {

//      for(int i = 0; i < tabSetting->tabWidget()->count() ;i++)
//        {
//          QString elem = tabSetting->tabElement(i);

//          if(tabSetting->currentList()->columnCount() == 1)
//            settings->addSetting(elem,tabSetting->itemsText(i));
//          else
//            {

//              BuildVariables * buildVariables = new BuildVariables;

//              for(int row = 0; row< tabSetting->listCount(i);row++)
//                {
//                  buildVariables->addVariable(tabSetting->itemText(row,0),tabSetting->itemText(row,1));

//                }

//              settings->addSetting(elem,buildVariables->toList());

//              delete buildVariables;
//            }
//        }
//    }
}



TabSetting *TabSettingManager::tabSetting(int index) const
{
  return tabsSettings.at(index);
}

