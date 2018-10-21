#include "compilersetting.h"

#include <bases.h>
#include <core_constants.h>

#include "gcc.h"

using namespace Core::Compiler;
CompilerSetting::CompilerSetting(const QString &name) :
  SettingsDocument(name)
{

}

bool CompilerSetting::isInEnvironmentPath()
{
  return true;
}

bool CompilerSetting::load()
{
  SettingsDocument::load();

  QString compilerType = string("type");

  if(compilerType == "Gcc")
    _compiler = new Gcc();
  else if(compilerType == "Mingw")
    _compiler = new Mingw();
}
Compiler *CompilerSetting::compiler() const
{
  return _compiler;
}

void CompilerSetting::setCompiler(Compiler *compiler)
{
  _compiler = compiler;

  addSetting(CC,compiler->CC());
  addSetting(CXX,compiler->CXX());
  addSetting(SHAREDLIB,compiler->dynamicLibLinker());
  addSetting(LIB,compiler->staticLibLinker());
  addSetting(DBG,compiler->debugger());
  addSetting(RES,compiler->resourceCompiler());
  addSetting(MAKE,compiler->make());
}

