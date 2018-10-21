#ifndef RUNCONFIG_H
#define RUNCONFIG_H

#include "project_global.h"

class PROJECTSHARED_EXPORT RunConfig : public SettingsManager
{

public:
  explicit RunConfig(const QString &name);

  void fromMap(const QVariantMap &map);
  void toMap(QVariantMap &map);

private:

  QString m_execPath;
  QString m_args;
  QString m_workingDir;
};

#endif // RUNCONFIG_H
