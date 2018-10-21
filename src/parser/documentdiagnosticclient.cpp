#include "documentdiagnosticclient.h"

DiagnosticMessage::DiagnosticMessage(int level, const QString &msg
                                     , const QString &fileName, int line):
  _level(level),_msg(msg),_fileName(fileName),_line(line)
{

}

bool DiagnosticMessage::isWarning() const
{
  return (level == Warning);
}

bool DiagnosticMessage::isError()
{
  return (level == Error);
}

QString DiagnosticMessage::msg() const
{
  return _msg;
}

QString DiagnosticMessage::fileName() const
{
  return _fileName;
}

int DiagnosticMessage::line() const
{
  return _line;
}

DocumentDiagnosticClient::DocumentDiagnosticClient()
{


}

void DocumentDiagnosticClient::report(int level, const StringLiteral *fileName
                                      , unsigned line, unsigned column, const char *format, va_list ap)
{
  Q_UNUSED(column);

  QString tmp;

  emit newMessage(DiagnosticMessage(level,tmp.vsprintf(format,ap),
                                    QString::fromUtf8(fileName->chars(), fileName->size())
                                    ,line));
}



