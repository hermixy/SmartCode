#include "document.h"
#include "documentdiagnosticclient.h"

#include <cplusplus/TranslationUnit.h>
#include <cplusplus/Literals.h>
#include <cplusplus/Control.h>
#include <cplusplus/Bind.h>
#include <cplusplus/ASTVisitor.h>
#include <cplusplus/AST.h>
#include <CPlusPlus/Symbols.h>
#include <CPlusPlus/CoreTypes.h>

#include <QFile>
#include <QStringList>

using namespace CPlusPlus;

Document::Document(const QString &fileName)
  :_fileName(fileName)
{
  _control = new Control();

  _control->setDiagnosticClient(new DocumentDiagnosticClient());

  const QByteArray localFileName = fileName.toUtf8();
  const StringLiteral *fileId = _control->stringLiteral(localFileName.constData(),
                                                        localFileName.size());
  _translationUnit = new TranslationUnit(_control, fileId);
  _translationUnit->setLanguageFeatures(LanguageFeatures::defaultFeatures());

  (void) _control->switchTranslationUnit(_translationUnit);

  setFileName(fileName);
}

bool Document::parse()
{
  if(_translationUnit->parse())
    {
      _globalNamespace = _control->newNamespace(0);

      Bind semantic(_translationUnit);

      if (! _translationUnit->ast())
        return false; // nothing to do.

      TranslationUnitAST *ast = _translationUnit->ast()->asTranslationUnit();
      semantic(ast, _globalNamespace);

      return true;
    }
  else
    return false;
}

void Document::setSource(const QByteArray &source)
{
  _source = source;
  _translationUnit->setSource(source.constBegin(),source.size());
}

QByteArray Document::source() const
{
  return _source;
}

QString Document::fileName() const
{
  return _fileName;
}

void Document::setFileName(const QString &fileName)
{
  _fileName =  fileName;

  QFile f(_fileName);

  if (f.open(QFile::ReadOnly))
    setSource(f.readAll());
}

Control *Document::control() const
{
  return _control;
}

TranslationUnit *Document::translationUnit() const
{
  return _translationUnit;
}

Namespace *Document::globalNamespace() const
{
  return _globalNamespace;
}

QString Document::findFieldType(const QStringList &context,int line,int column)
{
  QString type,field;

  int length = context.length();
  field = context[0];


  if(length == 1)
    {

      ScopeFinder scopeFinder(_globalNamespace);

      Scope * scope = scopeFinder.scopeAt(line,column);

      Symbol * symbol = 0;

      while(!symbol && scope)
        {
          symbol = scope->find(_control->findIdentifier(field.toLatin1(),field.length()));
          scope = scope->enclosingScope();
        }

      if(symbol)
        {
          return typeToString(symbol->type().type());
        }

    }
  else
    {
      int i = 1;

      type = findFieldType(QStringList()<<field,line,column);


    }
}

QString Document::typeToString(Type * t,QString end)
{
  QString str;

  if(NamedType *namedType = t->asNamedType())
    {
      str = nameToString(namedType->name());
    }

  if(PointerType *pointerType = t->asPointerType())
    {
      end += "*";
      return typeToString(pointerType->elementType().type(),end);
    }

  if(ReferenceType * refType = t->asReferenceType())
    {
      end += "&";
      return typeToString(refType->elementType().type(),end);
    }

  if(ArrayType *arrayType = t->asArrayType())
    {
      end += "[]";
      return typeToString(arrayType->elementType().type(),end);
    }

  if(t->isIntegerType())
    str = "int";

  if(t->isFloatType())
    str = "float";

  if(t->isVoidType())
    str = "void";

  if(t->isTemplateType())
    str = "T";

  return str + end;
}

QString Document::symbolName(Symbol *s)
{
  return nameToString(s->name());
}

QString Document::nameToString(const Name *name)
{
  return name->identifier()->chars();
}
