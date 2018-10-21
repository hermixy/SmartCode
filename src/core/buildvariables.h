#ifndef BUILDVARIABLES_H
#define BUILDVARIABLES_H

#include "variables.h"


class BuildVariables : public Variables
{
public:
    BuildVariables();

 bool evaluateCondition(const QString &exp);
 bool resolveCondition(const QString &exp, const QString &var, const QString &value);


private:


};

#endif // BUILDVARIABLES_H
