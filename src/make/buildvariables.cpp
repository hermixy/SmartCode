#include "buildvariables.h"

#include <QStringList>
#include <QVariant>

BuildVariables::BuildVariables(QObject *parent) : QObject(parent)
{

}

BuildVariables::~BuildVariables()
{

}

void BuildVariables::addVariable(const QString & key ,const QVariant & value)
{
  globalVars.insert(key,value);
}

bool BuildVariables::evaluateCondition(const QString &exp, const QString &var, const QVariant &value)
{
  if(exp ==  "equals")
    return evaluateExpression(var) == evaluateExpression(value);
  else if(exp == "greather")
    return evaluateExpression(var) > evaluateExpression(value);
  else if(exp == "less")
    return evaluateExpression(var) < evaluateExpression(value);

  return false;
}

QVariant BuildVariables::evaluateExpression(const QVariant &expression)
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

QVariant BuildVariables::evaluateVariable(const QString &var)
{
  return evaluateExpression(value(var));
}

QStringList BuildVariables::projectVariables() const
{
  return QStringList()<<"DESTDIR_TARGET"<<"OBJECTS_DIR";
}

QStringList BuildVariables::variables() const
{
  return globalVars.keys();
}

QVariant BuildVariables::value(const QString &var) const
{
  return globalVars.value(var);
}

QString BuildVariables::valueString(const QString &var) const
{
  return value(var).toString();
}
