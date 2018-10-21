#include "bases.h"

#include <QFile>
#include <QTextStream>

Bases::Bases()
{

}

Bases::~Bases()
{

}

bool Bases::out(const QString &fileName,const QString &text)
{
  QFile file(fileName);

  if(!file.open(QFile::WriteOnly))
    return false;

  QTextStream out(&file);
  out << text;
  file.close();
  return true;
}


bool Bases::isSourceFile(const QString &fileName)
{
  return  fileName.contains(sourceFilesReg());
}

bool Bases::isHeaderFile(const QString &fileName)
{
    return  fileName.contains(headerFilesReg());
}

bool Bases::isResourceFile(const QString &fileName)
{
    return  fileName.contains(resourceFilesReg());
}

bool Bases::isOtherFile(const QString &fileName)
{
    return  fileName.contains(otherFilesReg());
}

QString Bases::headerSource(const QString &fileName)
{
  if(fileName.contains(sourceFilesReg()))
    {
      QRegExp rx("*.*");
      rx.setPatternSyntax(QRegExp::Wildcard);


    }
}

QRegExp Bases::sourceFilesReg()
{
  return QRegExp("[^\\.]\\.(cpp|cxx|c|cc)$");
}

QRegExp Bases::headerFilesReg()
{
  return QRegExp("[^\\.]\\.(h|hxx)$");
}

QRegExp Bases::resourceFilesReg()
{
  return QRegExp("[^\\.]\\.(rc|qrc|png|ico|jpeg|jpg)$");
}

QRegExp Bases::otherFilesReg()
{
  return QRegExp("*.*",Qt::CaseSensitive,QRegExp::Wildcard);
}



