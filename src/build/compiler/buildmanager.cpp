#include "buildmanager.h"

#include "compilersetting.h"
#include <bases.h>

const char luncher[] = "consoleluncher.exe";

BuildManager::BuildManager(CompilerSetting * s,QObject *parent) :
  QObject(parent)
{
  setting = s;
  procss = new QProcess;

  if(!s->isInEnvironmentPath())
    {
      QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
      env.insert("PATH", env.value("Path") + ";" + setting->path());
      procss->setProcessEnvironment(env);
    }

  connect(procss,SIGNAL(readyReadStandardError()),this,SLOT(standardError()));
  connect(procss,SIGNAL(readyReadStandardOutput()),this,SLOT(standardOutput()));
}

void BuildManager::setMakeFile(const QString &makefile)
{
  makeFile = makefile;
}

void BuildManager::setSourceFile(const QString &sourceFile)
{
  _sourceFile = sourceFile;
}

bool BuildManager::build()
{
  getError = false;

  if(_sourceFile.isNull())
    {
      procss->start(setting->toMake(), QStringList()<< setting->toMakeCommand() <<makeFile);
    }
  else
    {
      if(Bases::fileSuffix(_sourceFile) == "c")
        procss->start(setting->toCC(),QStringList()<<  _sourceFile);
      else
        procss->start(setting->toCXX(), QStringList()<< _sourceFile);

      _sourceFile.clear();
    }

  if(procss->waitForFinished())
    return !getError;

  return false;
}

QProcess *BuildManager::process() const
{
  return procss;
}

bool BuildManager::hasError()
{
  return getError;
}

void BuildManager::standardError()
{
  QByteArray error = procss->readAllStandardError();

  if(!error.isEmpty())
    {
      newStandardError(QString::fromUtf8(error).trimmed());
      getError = true;
    }
}

void BuildManager::standardOutput()
{
  QByteArray out = procss->readAllStandardOutput();

  if(!out.isEmpty())
    newStandardOutput(QString::fromUtf8(out).trimmed());
}
bool BuildManager::useShadowBuild() const
{
  return _useShadowBuild;
}

void BuildManager::setUseShadowBuild(bool useShadowBuild)
{
  _useShadowBuild = useShadowBuild;
}


void BuildManager::abort(const QString &exeName)
{

#ifdef Q_OS_WIN32
  procss->start("TASKKILL",QStringList()<<"/F"<<"/IM"<<luncher);
#else
  procss->start("pidof",QStringList()<<luncher);

  procss->waitForFinished();
  //pid = procss->readAllStandardOutput()
  procss->start("kill",QStringList()<<"-9"<< procss->readAllStandardOutput());
#endif

}

bool BuildManager::programCompiled(const QString &destDirTarget) const
{
  return QFileInfo(destDirTarget).exists();
}


bool BuildManager::executeProgram(const QString &program,const QString &arguments,const QString& workingDir,
                              bool runInTerminal)
{
  if(!QFileInfo(program).exists())
    return false;

  procss->setWorkingDirectory(workingDir);

  if(runInTerminal)
    procss->start(luncher, QStringList()<<program<<arguments);
  else
    procss->start(program, QStringList()<<arguments);

  connect(procss,SIGNAL(finished(int)),this,SLOT(getProgramExitCode(int)));
}

void BuildManager::getProgramExitCode(int exitCode)
{
  emit programFinished(tr("Program exit with code") + " " + QString::number(exitCode));
}

void BuildManager::clean()
{
  procss->start(setting->toMake(), QStringList()<< setting->toMakeCommand() <<makeFile<<"clean");
}

CompilerSetting *BuildManager::Setting() const
{
  return setting;
}
