#ifndef BUILDVARIABLES_H
#define BUILDVARIABLES_H

#include "make_global.h"

#include <settingsmanager.h>

class MAKESHARED_EXPORT BuildEnvironment : public SettingsManager
{
    Q_OBJECT
public:
    explicit BuildEnvironment();
    ~BuildEnvironment();


    bool evaluateCondition(const QString &exp, const QString &var, const QVariant &value);

    QVariant evaluateExpression(const QVariant &expression) ;
    QVariant evaluateVariable(const QString &var);
private:
    void getSystemEnvironment();
};

#endif // BUILDVARIABLES_H
