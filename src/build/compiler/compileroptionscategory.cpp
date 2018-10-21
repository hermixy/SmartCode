#include "compileroptionscategory.h"
#include "compileroption.h"
#include <QList>

CompilerOptionsCategory::CompilerOptionsCategory(const QString &name, QObject *parent)
 :QObject(parent)
{
_name = name;
}


void CompilerOptionsCategory::addCompilerOption(CompilerOption *option)
{
    compilerOptions << option;
}

QList<CompilerOption*> CompilerOptionsCategory::toCompilerOptions()
{
    return compilerOptions;
}

QString CompilerOptionsCategory::name() const
{
    return _name;
}


