#include "compileroption.h"

CompilerOption::CompilerOption(const QString &text, int defaultFlag, QObject *parent)
  :QObject(parent),_defaultFlag(defaultFlag)
{
  _text = text;
  _currentFlag = _defaultFlag;
}

void CompilerOption::setText(const QString &text)
{
  _text =  text;
}

void CompilerOption::addFlag(const QString &description, const QString &arg)
{
  _flags << new Flag(description,arg);
}

void CompilerOption::addBoolFlags(const QString &yesArg,const QString &noArg)
{
  Flag *f ;
  f = new Flag(tr("No"),noArg);
  _flags << f;
  f = new Flag(tr("Yes"),yesArg);
  _flags <<  f;
}

void CompilerOption::addEmptyFlag()
{
  addFlag(tr("None"),QString());
}

QString CompilerOption::text() const
{
  return _text;
}

QList<Flag*> CompilerOption::flags() const
{
  return _flags;
}

int CompilerOption::defaultFlag() const
{
  return _defaultFlag;
}
int CompilerOption::currentFlag() const
{
  return _currentFlag;
}

void CompilerOption::setCurrentFlag(int currentFlag)
{
  _currentFlag = currentFlag;
}



