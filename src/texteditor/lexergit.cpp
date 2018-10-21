#include "lexergit.h"
#include <Qsci/qsciscintilla.h>
#include <QDebug>

using namespace TextEditor;

LexerGit::LexerGit(QObject *parent) :
    QsciLexerCustom(parent)
{

}

QColor LexerGit::defaultColor(int style) const
{
    switch(style)
    {
    case normal:
        return QColor(Qt::black);
    case plus:
        return QColor(Qt::green);
    case minus:
        return QColor(Qt::red);
    case arobaz:
        return QColor(Qt::blue);
    }

    return QsciLexer::defaultColor(style);
}

void LexerGit::styleText(int start, int end)
{
    while(start < end)
    {
        char ch = editor()->SendScintilla(QsciScintilla::SCI_GETCHARAT,start);

        int line = editor()->SendScintilla(QsciScintilla::SCI_LINEFROMPOSITION,start);
        int lineCount = editor()->SendScintilla(QsciScintilla::SCI_LINELENGTH,line);

        switch(ch)
        {
        case '+':
            startStyling(start);
            setStyling(lineCount,plus);

            break;
        case '-':
            startStyling(start);
            setStyling(lineCount,minus);
            break;
        case '@':
            startStyling(start);
            setStyling(lineCount,arobaz);
            break;
        default:
            startStyling(start);
            setStyling(lineCount,normal);

        }
        start += lineCount;
    }
}

const char * LexerGit::language() const
{
    return "Git";
}

QString LexerGit::description(int style) const
{
    switch(style)
    {
    case normal:
        return "normale";
    case plus:
        return "plus";
    case minus:
        return "minus";
    case arobaz:
        return "arobaz";
    }

    return QString();
}
