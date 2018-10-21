#include "compiler.h"
#include "message.h"

#include <QVariant>
#include <core_constants.h>

const char DEFAULT_CC[] = "gcc";
const char DEFAULT_CXX[] = "g++";
const char DEFAULT_MAKE[] = "";
const char DEFAULT_RES[] = ;
const char DEFAULT_DBG[] = ;
const char DEFAULT_RESCOMPILER[] = ;

const char DETECTION[] = "Detection";
const char TOOLCHAIN[] = "Toolchain";
class CompilerPrivate
{
public:
  CompilerPrivate();

  Compiler::Detection m_detection;
  Compiler::ToolChain m_toolchain;
  QString m_name;
  QString m_version;

  QString m_cc;
  QString m_cxx;
  QString m_make;
  QString m_debugger;
  QString m_resourceCompiler;


private:
};

Compiler::Compiler():
  d(new CompilerPrivate())
{

}

Compiler::Compiler(const Compiler *other)
{

}

void Compiler::parse(const QString &) const
{

}

void Compiler::autoDetecte(const QString &)
{

}

bool Compiler::load()
{

}

bool Compiler::save()
{

}


void Compiler::fromMap(const QVariantMap &map)
{
  d->m_name = map.value(QLatin1String(Core::NAME)).toString();
  d->m_detection = map.value(QLatin1String(DETECTION)).toInt();
  d->m_version = map.value(QLatin1String(Core::VERSION)).toString();
  d->m_toolchain = map.value(QLatin1String(TOOLCHAIN)).toInt();

  d->m_cc = map.value(QLatin1String(Core::Compiler::CC)).toString();
  d->m_cxx = map.value(QLatin1String(Core::Compiler::CXX)).toString();
  d->m_make = map.value(QLatin1String(Core::Compiler::MAKE)).toString();
  d->m_debugger = map.value(QLatin1String(Core::Compiler::DBG)).toString();
  d->m_resourceCompiler = map.value(QLatin1String(Core::Compiler::RES)).toString();
}

QVariantMap Compiler::toMap()
{
  QVariantMap map;

  map.insert(QLatin1String(Core::NAME),d->m_name);
  map.insert(QLatin1String(Core::VERSION),d->m_version);
  map.insert(QLatin1String(DETECTION),d->m_detection);


  map.insert(Core::Compiler::CC,d->m_cc);
  map.insert(Core::Compiler::CXX,d->m_cxx);
  map.insert(Core::Compiler::MAKE,d->m_make);
  map.insert(Core::Compiler::DBG,d->m_debugger);
  map.insert(Core::Compiler::RES,d->m_resourceCompiler);


  return map;
}

