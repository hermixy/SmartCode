#include "classview.h"
#include <CPlusPlus/Literals.h>
#include <CPlusPlus/Symbols.h>
#include <CPlusPlus/Bind.h>
#include <CPlusPlus/CoreTypes.h>
#include <CPlusPlus/FullySpecifiedType.h>
#include <document.h>
#include <core_constants.h>

using namespace CPlusPlus;

ClassView::ClassView()
{

}

void ClassView::parse(Document *doc, QStandardItem *parent)
{
  items.clear();

  if(doc->parse())
    accept(doc->globalNamespace());

  items << parent;
}

bool ClassView::preVisit(Symbol *s)
{
  IconType iconType;

  QString text;

  text = Document::symbolName(s);

  if(Function *f = s->asFunction())
    {
      text +=" (";

      for(unsigned int i = 0;i<f->argumentCount();i++)
        {
          text += Document::typeToString(f->argumentAt(i)->asArgument()->type().type());

          if(i != f->argumentCount() - 1)
            text += ",";
        }

      text += ")";
      text + " : ";
      text += Document::typeToString(f->returnType().type());

      switch(f->visibility())
        {
        case Symbol::Public:
          iconType = PublicFunctionIcon;
          break;
        case Symbol::Protected:
          iconType = ProtectedFunctionIcon;
          break;
        case Symbol::Private:
          iconType = PrivateFunctionIcon;
          break;
        }
    }

  if(Declaration *d = s->asDeclaration())
    {

      if(d->asEnumeratorDeclarator())
        {
          iconType = EnumIcon;
        }
      else
        {
          text + " : ";
          text += Document::typeToString(d->type().type());

          switch(d->visibility())
            {
            case Symbol::Public:
              iconType = PublicDeclarationIcon;
              break;
            case Symbol::Protected:
              iconType = ProtectedDeclarationIcon;
              break;
            case Symbol::Private:
              iconType = PrivateDeclarationIcon;
              break;
            }
        }

    }

  if(s->isUsingNamespaceDirective())
    iconType = UsingNamespaceDirectiveIcon;

  if(s->isEnum())
    {
      switch(s->visibility())
        {
        case Symbol::Public:
          iconType = PublicEnumIcon;
          break;
        case Symbol::Protected:
          iconType = ProtectedEnumIcon;
          break;
        case Symbol::Private:
          iconType = PrivateEnumIcon;
          break;
        }

    }

  if(Class * klass = s->asClass())
    {
      switch(klass->classKey())
        {
        case Class::ClassKey:
          iconType = ClassIcon;
          break;
        case Class::StructKey:
          iconType = StructIcon;
          break;
        case Class::UnionKey:
          iconType = UnionIcon;
          break;
        }

    }

  if(s->isNamespace())
    {
      iconType =  NamespaceIcon;

    }

  QStandardItem * item = new QStandardItem(itemIcon(iconType),text);
  items.last()->appendRow(item);

  if(s->isClass() || s->isNamespace() || s->isEnum())
    items.append(item);

  return true;
}

void ClassView::postVisit(Symbol * s)
{
  if(s->isClass() || s->isNamespace() || s->isEnum())
    {
      items.pop_back();
    }
}

QIcon ClassView::itemIcon(IconType type)
{
  switch(type)
    {
    case NamespaceIcon:
      return QIcon(Core::Icon::NAMESPACE);
      break;
    case ClassIcon:
      return QIcon(Core::Icon::CLASS);
      break;
    case StructIcon:
      return QIcon(Core::Icon::STRUCTURE);
      break;
    case UnionIcon:
      return QIcon(Core::Icon::UNION);
      break;
    case TemplateIcon:
      return QIcon(Core::Icon::TEMPLATE);
      break;
    case PublicFunctionIcon:
      return QIcon(Core::Icon::METHOD_PUBLIC);
      break;
    case ProtectedFunctionIcon:
      return QIcon(Core::Icon::METHOD_PROTECETED);
      break;
    case PrivateFunctionIcon:
      return QIcon(Core::Icon::METHOD_PRIVATE);
      break;

    case PublicDeclarationIcon:
      return QIcon(Core::Icon::VAR_PUBLIC);
      break;
    case ProtectedDeclarationIcon:
      return QIcon(Core::Icon::VAR_PROTECETED);
      break;
    case PrivateDeclarationIcon:
      return QIcon(Core::Icon::VAR_PRIVATE);
      break;

    case EnumIcon:
      return QIcon(Core::Icon::ENUM);
      break;
    case PublicEnumIcon:
      return QIcon(Core::Icon::ENUM_PUBLIC);
      break;
    case ProtectedEnumIcon:
      return QIcon(Core::Icon::ENUM_PROTECTED);
      break;
    case PrivateEnumIcon:
      return QIcon(Core::Icon::ENUM_PRIVATE);
      break;
    default:
      return QIcon();
    }
}

