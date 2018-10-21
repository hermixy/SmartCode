#ifndef PROJECT_H
#define PROJECT_H

#include "project_global.h"
#include <QObject>


class RunConfig;
class ProjectPrivate;
class Config;

class PROJECTSHARED_EXPORT Project
{

public:

  Project(const QString &projectName);

  QString name() const;
  QString makeFile()  const;

  Config* currentConfiguration() const;
  Config* config(int index) const;

  bool addSubProject(Project *subProject);
  void removeSubProject(Project *subProject);
  bool hasSubProjects() const;

  Project * subProject(const QString& subProjectName);

  QStringList toFiles() const;

  QList<Project *> subProjects() const;

  QList<RunConfig*> runConfigurations() const;

  QList<Config *> configs() const;

  QStringList configsNames() const;

  void addConfig(Config *config);
  void addConfigs(const QList<Config*> & configs);
  void cloneConfig(int index, const QString &newConfigName);
  void removeConfig(int index);
  void renameConfig(int index, const QString &newConfigName);

  RunConfig *currentRunConfig() const;

  void addRunConfig(RunConfig * runConfig);
  void cloneRunConfig(int index, const QString &newRunConfigName);
  void removeRunConfig(int index);
  void renameRunConfig(int index, const QString &newRunConfigName);

  static QStringList filesSettings() ;

  bool load();
  bool save();

  void fromMap(const QVariantMap &map);
  QVariantMap toMap();

protected:

private:
  QString _name;
  ProjectPrivate * d;

};

#endif // PROJECT_H
