// Copyright (C) 2014 Achrouf corporation
// Auteur Achrouf Abdenour

// This File is part of SmartCode

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program. If not, see http://www.gnu.org/licenses/.

#include "versioncontrol.h"

#include <QDebug>

VersionControl::VersionControl()
{

}

QString VersionControl::diff(const QString &fileName)
{
  return readFromProcess(commandString(Diff),fileName);
}

QString VersionControl::log(const QString &fileName)
{
  return readFromProcess(commandString(Log),fileName);
}

QString VersionControl::readFromProcess(const QString &cmd,const QString &fileName)
{
  execute(QStringList()<<cmd,fileName);

  if(process.waitForFinished())
    return process.readAllStandardOutput();

  return QString();
}

QString VersionControl::name() const
{
  return QString();
}

void VersionControl::addFile(const QString &fileName,const QString &workingDir)
{
  QStringList args;
  args << commandString(Add)<< fileName;

  execute(args,workingDir);
}

void VersionControl::removeFile(const QString &fileName, const QString &workingDir)
{
  QStringList args;
  args << commandString(Remove)<< fileName;

  execute(args,workingDir);
}

void VersionControl::addRepository(const QString &workingDir)
{
  execute(QStringList()<<commandString(CreateRepository),workingDir);
}

void VersionControl::cloneRepository(const QString &source,const QString &destination
                                     ,const QString &workingDir)
{
  QStringList args;

  args <<commandString(Clone)<<source<<destination;

  execute(args,workingDir);
}

void VersionControl::commit(const QString &repository,
                            const QStringList &files,
                            const QString &commitMessageFile)
{
  QStringList args;
  args<<commandString(Commit)<<files;

  execute(args,repository);
}

void VersionControl::execute(const QStringList &args,const QString &workingDir)
{
  process.setWorkingDirectory(workingDir);
  process.start(name(),args);
}

QString VersionControl::commandString(VcsCommand cmd)
{
  switch (cmd) {
    case CreateRepository: return QLatin1String("init");
    case Clone: return QLatin1String("clone");
    case Add: return QLatin1String("add");
    case Remove: return QLatin1String("remove");
    case Move: return QLatin1String("rename");
    case Pull: return QLatin1String("pull");
    case Push: return QLatin1String("push");
    case Commit: return QLatin1String("commit");
    case Import: return QLatin1String("import");
    case Update: return QLatin1String("update");
    case Revert: return QLatin1String("revert");
    case Annotate: return QLatin1String("annotate");
    case Diff: return QLatin1String("diff");
    case Log: return QLatin1String("log");
    case Status: return QLatin1String("status");
    }
  return QString();
}



