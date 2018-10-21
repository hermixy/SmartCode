#include "configmanager.h"

#include "config.h"
#include <compiler/compilersetting.h>
#include <core_constants.h>

ConfigManager::ConfigManager(CompilerSetting *_compilerSetting, QObject *parent) : QObject(parent)
{
  compilerSetting = _compilerSetting;
}

ConfigManager::~ConfigManager()
{

}

Config * ConfigManager::addDefaultConfig(const QString &configName)
{
  Config * config = new Config(configName);

  config->addSetting(Core::Project::DESTDIR,"$(PROJECTDIR)\\$(CONFIG)");
  config->addSetting(Core::Project::OBJECTSDIR,"$(CONFIG)");
  config->addSetting(Core::Project::TARGET,"$(PROJECTNAME)");

  return config;
}

Config *ConfigManager::addDebugConfig(const QString &name)
{
  Config * debug = addDefaultConfig(name);
  debug->addSetting(Core::BuildManager::CXXFLAGS,compilerSetting->CXXFlagsDebug());

  return debug;
}

Config *ConfigManager::addReleaseConfig(const QString &name)
{
  Config * release = addDefaultConfig(name);
  release->addSetting(Core::BuildManager::CXXFLAGS,compilerSetting->CXXFlagsRelease());

  return release;
}

