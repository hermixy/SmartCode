#ifndef DOCUMENTDIAGNOSTICCLIENT_H
#define DOCUMENTDIAGNOSTICCLIENT_H

#include <cplusplus/DiagnosticClient.h>

class DiagnosticMessage
{
public:
  DiagnosticMessage(int level ,const QString &msg,
                    const QString &fileName ,int line);
  
  enum Level
  {
    Warning,
    Error
  };

  bool isWarning();
  bool isError();

  QString msg() const;
  QString fileName() const;

  int line() const;

private:
  QString _msg;
  QString _fileName;

  Level _level;
  int _line;
};

class DocumentDiagnosticClient : public CPlusPlus::DiagnosticClient,QObject
{
  Q_OBJECT
public:
  DocumentDiagnosticClient();

  void report(int level, const StringLiteral *fileName,
              unsigned line, unsigned column, const char *format, va_list ap);

signals:
  void newMessage(DiagnosticMessage msg);
};

#endif // DOCUMENTDIAGNOSTICCLIENT_H
