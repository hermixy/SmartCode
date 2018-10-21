#ifndef VERSIONCONTROL_H
#define VERSIONCONTROL_H

#include "versioncontrol_global.h"

#include <QProcess>

class VERSIONCONTROLSHARED_EXPORT VersionControl
{

public:
  enum VcsCommand
  {
    CreateRepository,
    Clone,
    Add,
    Remove,
    Move,
    Pull,
    Push,
    Commit,
    Import,
    Update,
    Revert,
    Annotate,
    Diff,
    Log,
    Status
  };

  VersionControl();

  void addFile(const QString &fileName, const QString &workingDir);
  void removeFile(const QString &fileName, const QString &workingDir);
  void addRepository(const QString &workingDir);
  void cloneRepository(const QString &source, const QString &destination, const QString &workingDir);
  void commit(const QString &repository, const QStringList &files, const QString &commitMessageFile);

  void execute(const QStringList &args,const QString &workingDir);

  QString diff(const QString & fileName);
  QString log(const QString &fileName);

  virtual QString name() const;
protected:
  QString readFromProcess(const QString &cmd, const QString &fileName);
private:


  QProcess process;

  QString commandString(VcsCommand cmd);
};

#endif // VERSIONCONTROL_H
