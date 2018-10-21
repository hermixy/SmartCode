#ifndef COMPILER_H
#define COMPILER_H

#include "build_global.h"
#include <QObject>

class CompilerOptionsCategory;
class Message;
class CompilerPrivate;

class BUILDSHARED_EXPORT Compiler : public QObject
{
  Q_OBJECT
public:
  enum Detection
  {
    AutoDetection,
    ManualDetection,
    AutoDetectionFromSettings
  };

  enum ToolChain
  {
    GCC,
    MinGW,
    MSVC
  };

  Compiler();

  virtual QString name() const ;

  virtual QList<CompilerOptionsCategory*> flags() const;

  virtual void parse(const QString &) const;

  virtual void autoDetecte (const QString &);

  void fromMap(const QVariantMap &map);
  QVariantMap toMap();

  void wx(QVariantMap map);

  bool load();
  bool save();

signals:
  void addMessage(const Message &msg);
private:

  Message newMessage(const QString &type, const QString &description, fileName, lineno);
  CompilerPrivate * d;

};

#endif // COMPILER_H
