#include <QCoreApplication>
#include <control.h>
#include <TranslationUnit.h>
#include <DiagnosticClient.h>
#include <QFile>
#include <QDebug>
#include <Literals.h>
#include <AST.h>
#include <Symbols.h>
#include <SymbolVisitor.h>
#include <ASTVisitor.h>
#include <Bind.h>
#include <typeinfo>
#include <CoreTypes.h>
#include <FullySpecifiedType.h>
#include <Lexer.h>
#include <QDebug>

#include <iostream>

using namespace std;
using namespace CPlusPlus;

class Find: public SymbolVisitor
{
    Namespace *root;
    unsigned line;
    unsigned column;
    Block *symbol;

public:
    Find(int line,int column)
        : line(line), column(column), symbol(0) {}

    Block * getBlock()
    {
        return symbol;
    }

    bool visit(Block *s)
    {
        if(((s->line() < line) || (s->line() == line && s->column() <= column)))
        {
            cout<<s->startOffset()<<":"<<s->endOffset()<<endl;
            symbol = s;

            return true;
        }

        return false;
    }
};
class MkVisitor: public SymbolVisitor
{
public:
    MkVisitor():is(false)
    {

    }
    bool visit(Namespace *n)
    {

        if(n->name())
            cout<< n->name()->identifier()->chars()<<endl;

        return true;
    }

    bool visit(Template *t)
    {
        cout<< "T []";
        cout<< t->name()->identifier()->chars()<<endl;

        return true;
    }
    //    bool visit(NamespaceAlias * N) {   cout<< N->name()->identifier()->chars()<<endl;
    //                                       return true; }
    bool visit(UsingNamespaceDirective * d) {   cout<< d->name()->identifier()->chars()<<endl;
                                                return true; }
    //    bool visit(UsingDeclaration * u)
    //    {
    //        cout<< u->name()->identifier()->chars()<<endl;
    //        return true;
    //    }

    bool visit(Declaration *d)
    {
        if(d->asEnumeratorDeclarator())
        {
            cout<<"enum:";
        }


        cout<< d->name()->identifier()->chars()<<endl;

        return true;
    }

    bool visit(Enum *e)
    {
        switch(e->visibility())
        {
        case Symbol::Public:
            cout<<"public:";
            break;
        case Symbol::Private:
            cout<<"private:";
            break;
        }

        cout<<"enum{";
        return true;
    }

    bool visitArg(Argument * arg) {

        if(arg->type().type()->isNamedType())
            cout<<arg->type().type()->asNamedType()->name()->identifier()->chars();


        return true;

    }

    void getType(Type * t,int &nbrp)
    {
        if(t->isNamedType())
        {
            const Identifier * n = t->asNamedType()->name()->identifier();

            cout<<n->chars();
        }
        if(t->isPointerType())
        {
            nbrp += 1;
            getType(t->asPointerType()->elementType().type(),nbrp);
        }

        if(t->isIntegerType())
            cout<<"int";

        if(t->isUndefinedType())
            cout<<"T";



    }

    bool visit(Function *f)
    {
        QStringList list;
        list.prepend(f->name()->identifier()->chars());

        const QualifiedNameId * n = f->name()->asQualifiedNameId();

        while(n)
        {
            list.prepend(n->base()->identifier()->chars());
            n = n->base()->asQualifiedNameId();
        }


        cout<<list.join("::").toLatin1().constData()<<"\n";

//        cout <<":";
//        int nbrp = 0;

//        getType(f->returnType().type(),nbrp);

//        for(int i=0;i<nbrp;i++)
//            cout<<"*";

//        cout<<endl;


        //    for(unsigned int i = 0;i<f->argumentCount();i++)
        //      {
        //        visit(f->argumentAt(i)->asArgument());

        //        if(i != f->argumentCount() - 1)
        //          cout<<",";
        //      }


        return true;
    }

    bool visit(Class *klass)
    {
        cout<<klass->name()->identifier()->chars()<<endl;
        cout <<"{"<<endl;
        return true;
    }

    void postVisit(Symbol * s)
    {
        if(s->isClass() || s->isEnum())
        {
            cout<<"}"<<endl;
        }
    }

private:
    bool is;
};

class DCleint : public DiagnosticClient
{
public:
    void report(int level, const StringLiteral *fileName, unsigned line, unsigned column, const char *format, va_list ap)
    {
        const QString file = QString::fromUtf8(fileName->chars(), fileName->size());

        QString a;

        if (level == Error) {
            qDebug()<<"error at line :"<<file<<":"<<line<<":"<<column<<" :"<<a.vsprintf(format,ap);


        }
    }
};

static void allNamespaces()
{QStringList m_namespaces;
    m_namespaces<<"Core"<<"Plugin"<<"Compiler"<<"Debugger";
    QStringList result;

    int count = m_namespaces.count();

    QStringList qualifiedNamespace;

    for(int i = 0; i< count ;i++)
    {
        qualifiedNamespace.clear();
        qualifiedNamespace.append(m_namespaces[i]);
        result << m_namespaces[i];
        for(int j = i + 1;j < count;j++)
        {
            qualifiedNamespace.append(m_namespaces[j]);
            result.append( qualifiedNamespace.join(QLatin1String("::")));

        }
    }


    qDebug()<<result;
}


int main(int argc, char *argv[])
{

    DCleint *d = new DCleint;
    QCoreApplication a(argc, argv);

    Control * _control;
    _control = new Control;
    //    _control->setDiagnosticClient(d);

    TranslationUnit *_translationUnit;
    QString fileName = "main.c";
    const QByteArray localFileName = fileName.toUtf8();
    const StringLiteral *fileId = _control->stringLiteral(localFileName.constData(),
                                                          localFileName.size());
    _translationUnit = new TranslationUnit(_control, fileId);

    QFile f(fileName);

    if (!f.open(QFile::ReadOnly|QFile::Text))
        return 1;


    QByteArray source = f.readAll();

    _translationUnit->setLanguageFeatures(LanguageFeatures::defaultFeatures());
    (void) _control->switchTranslationUnit(_translationUnit);
    _translationUnit->setSkipFunctionBody(true);


    _translationUnit->setSource(source.constBegin(),source.size());

    _translationUnit->parse();

    Namespace *_globalNamespace = _control->newNamespace(0);

    Bind semantic(_translationUnit);

    TranslationUnitAST *ast = _translationUnit->ast()->asTranslationUnit();
    semantic(ast, _globalNamespace);

    MkVisitor *mk = new MkVisitor;
    mk->accept(_globalNamespace);

    //    Namespace * n = _globalNamespace->find(_control->findIdentifier("boo",3))->asNamespace();

    Symbol * fu = _globalNamespace->find(_control->findIdentifier("main",4));



    //    Find *find = new Find(40,11);
    //    Block *b;

    //    find->accept(_globalNamespace);


    //    if(b = find->getBlock())
    //    {

    //        cout <<b->line();
    //        Declaration * dec = b->find(_control->findIdentifier("link",4))->asDeclaration();

    //        cout<<dec->type().type()->asNamedType()->name()->identifier()->chars();
    //    }

    //      Function * fu = _globalNamespace->find(_control->findIdentifier("unit",4))->asFunction();


    //        QString text = source;

    //        const QByteArray bytes = text.toUtf8();
    //        const char *firstChar = bytes.constData();
    //        const char *lastChar = firstChar + bytes.size();

    //        Lexer lex(firstChar, lastChar);
    //        lex.setLanguageFeatures(LanguageFeatures::defaultFeatures());
    //        lex.setPreprocessorMode(false);
    //        lex.setScanAngleStringLiteralTokens(true);

    //        bool inPreproc = false;
    //        bool scan;
    //        QVector<Token> tokens;

    //        for (;;) {
    //            Token tk;
    //            lex(&tk);

    //            if(tk.is(T_EOF_SYMBOL))
    //                break;

    //            QString spell = text.mid(tk.bytesBegin(), tk.bytes());

    //            QString fileName = spell.mid(1,spell.length() - 2);
    //            if(scan)
    //                qDebug()<<fileName;

    //            scan = false;
    //            lex.setScanAngleStringLiteralTokens(false);


    //            if (tk.newline() && tk.is(T_POUND))
    //                inPreproc = true;
    //            else if (inPreproc  && tk.is(T_IDENTIFIER) &&
    //                     spell == QLatin1String("include"))
    //            {
    //                scan =true;
    //                lex.setScanAngleStringLiteralTokens(true);
    //            }


    //            tokens.append(tk);

    //        }

allNamespaces();
    return a.exec();
}

