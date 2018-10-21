#ifndef CONFIG_H
#define CONFIG_H

#include "project_global.h"

class Compiler;
class QVariantMap;
class ConfigPrivate;
class BuildVariables;
class Environment;

class PROJECTSHARED_EXPORT Config : public SettingsManager
{

public:
  enum Template {App,Lib,SharedLib};

  Config(const QString &name);
  ~Config();

  void fromMap(const QVariantMap &map);
  QVariantMap toMap();

  BuildVariables *buildVariables() const;
  Environment *environment() const;

  QString destDirTarget() const;
  QString ext() const;

private:
  ConfigPrivate * d;
};

#endif // CONFIG_H
