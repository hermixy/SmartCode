#include "runconfig.h"
#include <QVariant>
#include <core_constants.h>

RunConfig::RunConfig(const QString &name) :
  SettingsManager(name)
{

}

void RunConfig::fromMap(const QVariantMap &map)
{
  m_execPath = map.value(QLatin1String(Core::Project::RUNEXEC)).toString();
  m_args = map.value(QLatin1String(Core::Project::RUNARGS)).toString();
  m_workingDir = map.value(QLatin1String(Core::Project::WORKINGDIR)).toString();
}

void RunConfig::toMap(QVariantMap &map)
{
  map.insert(QLatin1String(Core::Project::RUNEXEC), m_execPath);
  map.insert(QLatin1String(Core::Project::RUNARGS),  m_args );
  map.insert(QLatin1String(Core::Project::WORKINGDIR), m_workingDir);
}
