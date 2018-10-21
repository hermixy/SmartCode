#include "variables.h"

Variables::Variables()
{

}

void Variables::addVariable(const QString &varName, const QString &value)
{
  _values.insert(varName,value);
}

void Variables::unset(const QString &varName)
{
  _values.remove(varName);
}

QStringList Variables::variables()
{
  return _values.keys();
}

QString Variables::value(const QString &varName)
{
  return _values.key(varName);
}

void Variables::clear()
{
  _values.clear();
}

QString Variables::evaluateExpression(QString expr)
{
  QRegExp exprReg("\\$\\((\\w+)\\)");

  while(exprReg.indexIn(expr,0) != -1)
    {
      QString var = exprReg.cap(1);
      expr.replace(exprReg.cap(0),value(var));
    }

  return expr;
}

QString Variables::evaluateVariable(const QString &var)
{
  return evaluateExpression(value(var));
}


void Variables::fromList(const QStringList &list)
{
  foreach (const QString &str, list) {
      int pos = str.indexOf(QLatin1Char('='), 1);
      if (pos == -1) {
          addVariable(str,QString());
        } else {
          addVariable(str.left(pos), str.mid(pos+1));
        }
    }
}


QStringList Variables::toList()
{
  QStringList list;

  foreach (const QString &var, variables()) {
      if (value(var).isNull())
        list << QString(var);
      else
        list << QString(var + QLatin1Char('=') + value(var));
    }

  return list;
}


