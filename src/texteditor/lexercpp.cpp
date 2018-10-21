#include "lexercpp.h"

#include <Qsci/qsciscintilla.h>
#include "lexerstyle.h"

#include <QDebug>

using namespace TextEditor;

LexerCPP::LexerCPP(LexerStyle *lexStyle,QObject *parent, bool caseInsensitiveKeywords) :
    QsciLexerCPP(parent,caseInsensitiveKeywords),classes(""),globalVars("")
{
    lexerStyle = lexStyle;

    connect(lexerStyle,SIGNAL(foregroundColorChanged(QColor,int)),this,SIGNAL(colorChanged(QColor,int)));
    connect(lexerStyle,SIGNAL(backgroundColorChanged(QColor,int)),this,SIGNAL(paperChanged(QColor,int)));

    connect(lexerStyle,SIGNAL(fontChanged(QFont,int)),this,SIGNAL(fontChanged(QFont,int)));
}

QColor LexerCPP::defaultColor(int style) const
{
    return lexerStyle->foregroundColor(style);
}

QColor LexerCPP::defaultPaper(int style) const
{
    //    if(style == QsciScintillaBase::STYLE_DEFAULT)
    //    {
    return QsciLexer::defaultPaper(style);
    //    }

    // return lexerStyle->backgroundColor(style);
}

QFont LexerCPP::defaultFont(int style) const
{
    return lexerStyle->font(style);
}

void LexerCPP::updateClasses(const QStringList &_classes)
{

    classes = data(_classes);

}

void LexerCPP::updateGlobalVariables(const QStringList &vars)
{
    globalVars = data(vars);
}

const char* LexerCPP::data(const QStringList &list)
{
    if(!list.isEmpty())
    {
        if(editor()->isUtf8())
            return list.join(" ").toUtf8();
        else
            return list.join(" ").toLatin1();
    }

    return 0;
}

const char *LexerCPP::keywords(int set) const
{

    if(set == 2)
    {
        return globalVars;

    }
    if(set == 4)
    {
        return classes;
    }

    return QsciLexerCPP::keywords(set);
}

LexerStyle *LexerCPP::style()
{
    return lexerStyle;
}
