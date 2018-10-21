#include "modules.h"

Modules::Modules(QWidget *parent) : DebuggerClient(parent)
{

}

Modules::~Modules()
{

}

QStringList Modules::headers() const
{
    return QStringList()<<"Start Address"<<"To"<<"Symbols Read"<<"Module";
}

QString Modules::cmd() const
{
    return QLatin1String("info sharedlibrary");
}

int Modules::linesToBeRemoved() const
{
   return TakeFirstLine;
}

QString Modules::outputFormat() const
{
    return QLatin1String("(\\S+)\\s+(\\S+)\\s+(\\w+)\\s+\\W+\\s+(\\S+)");
}



