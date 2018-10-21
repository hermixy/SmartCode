#include "preprocessor.h"
#include "document.h"
#include <cplusplus/Lexer.h>
#include <QVector>

using namespace CPlusPlus;

Preprocessor::Preprocessor()
{

}

void Preprocessor::relativeInclude()
{

}

void Preprocessor::includes(Document *doc)
{
      const QByteArray bytes = doc->source();
      const char *firstChar = bytes.constData();
      const char *lastChar = firstChar + bytes.size();

      Lexer lex(firstChar, lastChar);
      lex.setLanguageFeatures(LanguageFeatures::defaultFeatures());
      lex.setPreprocessorMode(false);
      lex.setScanAngleStringLiteralTokens(true);

      bool inPreproc = false;

      QVector<Token> tokens;

//      for (;;) {
//          Token tk;
//          lex(&tk);

//          if (tk.is(T_EOF_SYMBOL)) {
//              _endedJoined = tk.joined();
//              break;
//          }

//         QStringRef spell = text.midRef(tk.bytesBegin(), tk.bytes());
//         qDebug()<<spell;
//         tokens.append(tk);

//      }
}

