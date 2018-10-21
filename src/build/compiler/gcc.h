#ifndef GCC_H
#define GCC_H

#include "compiler.h"

class QRegularExpression;

class Gcc : public Compiler
{
public:
  Gcc();
  QString name() const;

  void autoDetecte(const QString &compiler);
  QString make() const;
  virtual QList<CompilerOptionsCategory*> flags();

  void parse(const QString &line) const;
private:
  QRegularExpression  regExp,regExpIncluded,regExpGccNames;
  void newMessage(const QString &type, const QString &description
                  , const QString &fileName = QString, int lineno = -1);
  Message _currentMessage;
  void doFlush();
  void expandDescription(const QString &desc);
};

class Mingw : public Gcc
{
public:
  QString name() const;
  QString make() const;
private:

};

#endif // GCC_H
