#include "project.h"
#include "runconfig.h"
#include <bases.h>
#include <core_constants.h>
#include "config.h"

#include <settingsdocument.h>

const char CONFIGURATIONS[] = "Configurations";
const char RUNCONFIGURATIONS[] = "RunConfigurations";

using namespace Core::Project;

class ProjectPrivate
{
public:
  ProjectPrivate(Project * project);

  QStringList m_sources;
  QStringList m_headers;
  QStringList m_resourceFiles;
  QStringList m_otherFiles;
  QStringList m_dependencies;

  QList<Project*> m_subProjects;

  QList<Config*>  m_configs;
  Config * m_currentConfig;
  QList<RunConfig*>  m_runConfigs;
  RunConfig * m_runConfig;
};

Project::Project(const QString &projectName) :
  _name(projectName),d(new ProjectPrivate)
{

}

QString Project::name() const
{
  return _name;
}

bool Project::addSubProject(Project * subProject)
{  
  d->m_subProjects.append(subProject);
}

void Project::removeSubProject(Project * subProject)
{
  d->m_subProjects.removeOne(subProject(subProjectName));
}

Project * Project::subProject(const QString& subProjectName)
{
  foreach(Project * pro,_subProjects)
    {
      if(pro->name() == subProjectName)
        return pro;
    }

  return 0;
}

QString Project::makeFile()  const
{
  QString customMakeFile = string(Core::Project::MAKEFILE);

  if(customMakeFile.isEmpty())
    return baseName() + "." +currentConfiguration()->name();
  else
    return customMakeFile;
}


Config *Project::currentConfiguration() const
{
  return _configs[toInt(CURRENT_CONFIG)];
}

Config *Project::config(int index) const
{
  return _configs[index];
}

bool Project::load()
{
  SettingsDocumentReader reader();
}

bool Project::save()
{
  SettingsDocumentWriter writer;

  return writer.save(toMap);
}

void Project::fromMap(const QVariantMap &map)
{
  d->m_sources = map.value(QLatin1String(Core::Project::SOURCES)).toStringList();
  d->m_headers = map.value(QLatin1String(Core::Project::HEADERS)).toStringList();
  d->m_resourceFiles = map.value(QLatin1String(Core::Project::RESOURCES)).toStringList();
  d->m_otherFiles = map.value(QLatin1String(Core::Project::OTHERFILES)).toStringList();

  QVariantList configsList = map.value(QLatin1String(CONFIGURATIONS)).toList();

  foreach(const QVariantMap &configMap,configsList)
    {
      Config * config = new Config;
      config->fromMap(configMap);

      d->m_configs.append(config);
    }

  QVariantList runConfigsList = map.value(QLatin1String(RUNCONFIGURATIONS)).toList();

  foreach(const QVariantMap &runConfigMap,runConfigsList)
    {
      RunConfig * rConfig = new RunConfig;
      rConfig->fromMap(runConfigMap);

      d->m_runConfigs.append(rConfig);
    }

}

QVariantMap Project::toMap()
{
  QVariantMap map;

  map.insert(Core::Project::SOURCES,d->m_sources);
  map.insert(Core::Project::HEADERS,d->m_headers);
  map.insert(Core::Project::RESOURCES,d->m_resourceFiles);
  map.insert(Core::Project::OTHERFILES,d->m_otherFiles);

  QVariantList configsMap;

  foreach(Config * config,d->m_configs)
    {
      configsMap.append(config->toMap());
    }

  map.insert(CONFIGURATIONS,configsMap);

  QVariantList runConfigsMap;

  foreach(Config * runConfig,d->m_runConfigs)
    {
      runConfigsMap.append(runConfig->toMap());
    }

  map.insert(RUNCONFIGURATIONS,runConfigsMap);


  return map;
}


void Project::replaceConfigSetting(const QString &settingName,const QString &value)
{
  currentConfiguration()->addSetting(settingName,value);

  QDomElement item = settingsFirstChild(currentConfiguration());
  renameItem(item,settingName,value);
}


bool Project::hasSubProjects() const
{
  return !(d->m_subProjects.isEmpty());
}

// return name() stringList(SOURCES) ,headerfiles,resourcefiles and otherfiles
// does not return searchdirs or something like that

QStringList Project::toFiles() const
{
  QStringList files ;

  foreach(QString filesSetting ,filesSettings())
    {
      files<<stringList(filesSetting);
    }

  return files;
}

QList<Project *> Project::subProjects() const
{
  return d->m_subProjects;
}

QList<RunConfig *> Project::runConfigurations() const
{
  return d->m_runConfigs;
}

RunConfig *Project::currentRunConfig() const
{
  return d->m_runConfigs[toInt(CURRENT_RUNCONFIG)];
}

void Project::addRunConfig(RunConfig * runConfig)
{
  d->m_runConfigs << runConfig;
  //  saveSettings(runConfig);
}

void Project::cloneRunConfig(int index, const QString &newRunConfigName)
{
  RunConfig * clonedRConfig = _runConfigs[index];
  clonedRConfig->setName(newRunConfigName);

  addRunConfig(clonedRConfig);
}

void Project::removeRunConfig(int index)
{
  QString rConfigName = _runConfigs[index]->name();

  _runConfigs.removeAt(index);

  QDomElement item = rootFirstChild();

  if(removeItem(item,Core::Project::RUNCONFIG,rConfigName))
    Bases::out(name(),document().toString());
}

void Project::renameRunConfig(int index, const QString &newRunConfigName)
{
  RunConfig * rConfig = _runConfigs[index];

  QDomElement item = rootFirstChild();
  renameAttribute(item,Core::Project::RUNCONFIG,Core::Project::NAME,rConfig->name(),newRunConfigName);
  rConfig->setName(newRunConfigName);

}

QList<Config *> Project::configs() const
{
  return _configs;
}

QStringList Project::configsNames() const
{
  QStringList configs_names;

  foreach(Config * config,configs())
    configs_names<< config->name();

  return configs_names;
}

void Project::addConfig(Config * config)
{
  _configs<<config;
  //  saveSettings(config);
}

void Project::addConfigs(const QList<Config *> &configs)
{
  foreach (Config * config, configs) {
      addConfig(config);
    }
}

void Project::cloneConfig(int index,const QString &newConfigName)
{
  Config * clonedConfig = _configs[index];
  clonedConfig->setName(newConfigName);

  addConfig(clonedConfig);
}

void Project::removeConfig(int index)
{
  QString configName = _configs[index]->name();

  _configs.removeAt(index);

  QDomElement item = rootFirstChild();

  if(removeItem(item,Core::Project::CONFIG,configName))
    Bases::out(name(),document().toString());
}

void Project::renameConfig(int index , const QString &newConfigName)
{
  Config * config = _configs[index];

  QDomElement item = rootFirstChild();
  renameAttribute(item,Core::Project::CONFIG,Core::Project::NAME,config->name(),newConfigName);
  config->setName(newConfigName);
}

QStringList Project::filesSettings()
{
  return QStringList()<< Core::Project::SOURCES
                      <<Core::Project::HEADERS
                     <<Core::Project::RESOURCES
                    <<Core::Project::OTHERFILES;
}






