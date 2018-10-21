#include "buildvariables.h"
#include <QFileInfo>

BuildVariables::BuildVariables()
{

}

bool BuildVariables::evaluateCondition(const QString &exp)
{
  QRegExp rx("^(equal|greatherThen|lessThen|contains)\\(([^\\,].+),([^\\)].+)\\)$");
  rx.indexIn(exp);

  enum { OPERATOR, VARIABLE, VALUE} ;

  return resolveCondition(rx.cap(OPERATOR),rx.cap(VARIABLE),rx.cap(VALUE));
}

bool BuildVariables::resolveCondition(const QString &exp, const QString &var, const QString &value)
{
  if(exp ==  QLatin1String("equals"))
    return evaluateExpression(var) == evaluateExpression(value);
  else if(exp ==  QLatin1String("greatherThen"))
    return evaluateExpression(var) > evaluateExpression(value);
  else if(exp ==  QLatin1String("lessThen"))
    return evaluateExpression(var) < evaluateExpression(value);
  else if(exp == QLatin1String("contains"))
    {
      QStringList list = evaluateExpression(var).split(QLatin1Char(';'));
      return list.contains(evaluateExpression(value));
    }

  return false;
}

