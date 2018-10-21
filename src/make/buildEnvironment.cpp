#include "buildenvironment.h"

#include <QStringList>
#include <QVariant>
#include <QProcess>

BuildEnvironment::BuildEnvironment():SettingsManager()
{

}

BuildEnvironment::~BuildEnvironment()
{

}

void BuildEnvironment::getSystemEnvironment()
{
  QStringList vars = QProcess::systemEnvironment();

  foreach(QString var,vars)
    {
      addSetting(var.left(var.indexOf("=")),var.mid(var.indexOf("=") + 1));
    }
}

bool BuildEnvironment::evaluateCondition(const QString &exp, const QString &var, const QVariant &value)
{
  if(exp ==  "equals")
    return evaluateExpression(var) == evaluateExpression(value);
  else if(exp == "greather")
    return evaluateExpression(var) > evaluateExpression(value);
  else if(exp == "less")
    return evaluateExpression(var) < evaluateExpression(value);

  return false;
}

QVariant BuildEnvironment::evaluateExpression(const QVariant &expression)
{
  QString expr = expression.toString();

  QRegExp exprReg("\\$\\((\\w+)\\)");

  while(exprReg.indexIn(expr,0) != -1)
    {
      QString var = exprReg.cap(1);
      expr.replace(exprReg.cap(0),value(var).toString());
    }

  return QVariant(expr);
}

QVariant BuildEnvironment::evaluateVariable(const QString &var)
{
  return evaluateExpression(value(var));
}
