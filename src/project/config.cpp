#include "config.h"
#include <core_constants.h>
#include <compiler/compiler.h>
#include <buildvariables.h>
#include <environment.h>
#include <QVariant>
class ConfigPrivate
{
public:
  ConfigPrivate();

  QString m_name;
  QString m_destDir;
  QString m_target;
  QString m_objectsDir;

  QStringList m_libs;
  QStringList m_executables;
  QStringList m_includes;
  QStringList m_includeLibs;
  QStringList m_resCompiler;

  int m_template;

  BuildVariables *m_buildVariables;
  Environment * m_env;


};

Config::Config(const QString &name) : SettingsManager(name)
{

}

Config::~Config()
{

}

void Config::fromMap(const QVariantMap &map)
{
  BuildVariables * buildVars = new BuildVariables;
  buildVars->fromList(map.value(QLatin1String(Core::Project::BUILD_VARIABLES)).toStringList());
  d->m_buildVariables =  buildVars;

  Environment * env = new Environment;
  env->fromList( map.value(QLatin1String(Core::Project::ENVIRONMENT)).toStringList());
  d->m_env = env;

  d->m_target = map.value(QLatin1String(Core::Project::TARGET)).toString();
  d->m_destDir = map.value(QLatin1String(Core::Project::DESTDIR)).toString();
  d->m_objectsDir = map.value(QLatin1String(Core::Project::OBJECTSDIR)).toString();
  d->m_template = map.value(QLatin1String(Core::Project::TEMPLATE)).toInt();

  d->m_executables = map.value(QLatin1String(Core::Project::EXECUTABLES)).toStringList();
  d->m_includeLibs = map.value(QLatin1String(Core::Project::INCLUDELIBS)).toStringList();
  d->m_includes = map.value(QLatin1String(Core::Project::INCLUDES)).toStringList();
  d->m_libs = map.value(QLatin1String(Core::Project::LIBS)).toStringList();
  d->m_resCompiler = map.value(QLatin1String(Core::Project::RESCOMPILER)).toStringList();

}


BuildVariables *Config::buildVariables() const
{
  return d->m_buildVariables;
}

Environment *Config::environment() const
{
  return d->m_env;
}

QVariantMap Config::toMap()
{
  QVariantMap map;

  map.insert(Core::Project::TARGET,d->m_target);
  map.insert(Core::Project::DESTDIR,d->m_destDir);
  map.insert(Core::Project::OBJECTSDIR,d->m_objectsDir);
  map.insert(Core::Project::TEMPLATE,d->m_template);

  map.insert(Core::Project::EXECUTABLES,d->m_executables);
  map.insert(Core::Project::INCLUDELIBS,d->m_includeLibs);
  map.insert(Core::Project::INCLUDES,d->m_includes);
  map.insert(Core::Project::LIBS,d->m_libs);

  map.insert(Core::Project::BUILD_VARIABLES,d->m_buildVariables->toList());
  map.insert(Core::Project::ENVIRONMENT,d->m_env->toList());

  return map;

}

QString Config::destDirTarget() const
{
  return "$(DESTDIR)/$(TARGET)." + ext();
}

QString Config::ext() const
{
  switch(d->m_template)
    {
    case App:
#if defined (Q_OS_WIN32)
      return "exe";
#elif defined  (Q_OS_LINUX)
      return "run";
#elif defined (Q_OS_MAC)
      return "app";
#endif
      break;
    case Lib:
      return "a";
    case SharedLib:
#ifdef Q_OS_WIN32
      return "dll";
#endif
#ifdef Q_OS_LINUX
      return "so";
#endif
#ifdef Q_OS_MAC
      return "dylib";

#endif

    }

  return QString();

}

