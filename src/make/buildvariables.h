#ifndef BUILDVARIABLES_H
#define BUILDVARIABLES_H

#include "make_global.h"

#include <QObject>
#include <QHash>

class QStringList;

class MAKESHARED_EXPORT BuildVariables : public QObject
{
  Q_OBJECT
public:
  explicit BuildVariables(QObject *parent = 0);
  ~BuildVariables();

  QVariant value(const QString &var) const;

  QString valueString(const QString &var) const;

  QStringList variables() const;

  bool evaluateCondition(const QString &exp, const QString &var, const QVariant &value);

  QVariant evaluateExpression(const QVariant &expression) ;
  QVariant evaluateVariable(const QString &var);

  QStringList projectVariables() const;
signals:

public slots:
  void addVariable(const QString &key, const QVariant &value);
private:
  QHash<QString,QVariant> globalVars;
};

#endif // BUILDVARIABLES_H
