#include "texteditmanager.h"

#include "analyzer.h"
#include "autocompleter.h"
#include "classparser.h"

#include "lexerstyle.h"

using namespace TextEditor;

static LexerCPP * CPPLexer;
static LexerGit * GitLexer;
static ClassParser * clParser;

TextEditManager::TextEditManager(QObject *parent) :
    QObject(parent)
{
    setupLexers();
}

void TextEditManager::setupLexers()
{
    LexerStyle * lexStyle = new LexerStyle;

    lexStyle->load("style/default");

    CPPLexer = new LexerCPP(lexStyle);

    clParser = new ClassParser;

    AutoCompleter* completer = new AutoCompleter(CPPLexer);
    completer->setClassParser(clParser);

    GitLexer = new LexerGit;
}

LexerCPP * TextEditManager::lexerCPP()
{
    return CPPLexer;
}

LexerGit * TextEditManager::lexerGit()
{
    return GitLexer;
}

ClassParser * TextEditManager::classParer()
{
    return clParser;
}

void TextEditManager::setTopLevelItem(QStandardItem * item)
{
   classParer()->topLevelItem = item;
}

