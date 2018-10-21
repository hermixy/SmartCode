#ifndef COMPILERSETTING_H
#define COMPILERSETTING_H

#include "build_global.h"

#include <settingsdocument.h>
#include <QtXml>
#include <QHash>

class Compiler;

class BUILDSHARED_EXPORT CompilerSetting : public SettingsDocument
{

public:
  explicit CompilerSetting(const QString &name);

  bool isInEnvironmentPath();

  bool load();

  Compiler *compiler() const;
  void setCompiler(Compiler *compiler);

protected:

private:

  Compiler * _compiler;
};

#endif // COMPILERSETTING_H
