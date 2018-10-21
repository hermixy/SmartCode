#include "autosave.h"
#include "bases.h"

AutoSave::AutoSave(QObject *parent) :
    QObject(parent)
{
}
void AutoSave::doSave(const QString &fileName,const QString &context)
{
  Bases::out(Bases::baseNamePath(fileName)+".bak",context);
}


