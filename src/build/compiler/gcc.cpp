#include "gcc.h"
#include "compileroptionscategory.h"
#include "compileroption.h"
#include "message.h"
#include <QRegularExpression>
#include <host.h>
#include <QProcess>
#include "environment.h"
#include <bases.h>

Gcc::Gcc()
{
  const char FILE_PATTERN[] = "(<command[ -]line>|([A-Za-z]:)?[^:]+):";
  const char COMMAND_PATTERN[] = "^(.*?[\\\\/])?([a-z0-9]+-[a-z0-9]+-[a-z0-9]+-)?(gcc|g\\+\\+)(-[0-9\\.]+)?(\\.exe)?: ";

  regExp.setPattern(QLatin1Char('^') + QLatin1String(FILE_PATTERN)
                    + QLatin1String("(\\d+):(\\d+:)?\\s+((fatal |#)?(warning|error|note):?\\s)?([^\\s].+)$"));

  regExpIncluded.setPattern(QString::fromLatin1("\\bfrom\\s") + QLatin1String(FILE_PATTERN)
                            + QLatin1String("(\\d+)(:\\d+)?[,:]?$"));

  regExpGccNames.setPattern(QLatin1String(COMMAND_PATTERN));
}

QString Gcc::name() const
{
  return "GCC";
}

void Gcc::autoDetecte(const QString &compiler)
{
  Environment env = Environment::systemEnvironment();

  QString compilerPath = env.searchInPath(compiler);

  if(!compilerPath.isEmpty())
    {
  env.appendOrSetPath(Bases::path(compilerPath));

  QProcess process;
  process.setEnvironment(env.toList());

  process.start("g++",QStringList()<<"-dumpversion");
  process.waitForFinished();

  QString version = p.readAllStandardOutput().trimmed();
    }

}

QString Gcc::make() const
{
  QString make = QLatin1String("make");
  QString tmp = environment.searchInPath(make);
  return tmp.isEmpty() ? make : tmp.toString();
}

QList<CompilerOptionsCategory *> Gcc::flags()
{
  CompilerOptionsCategory *category;
  CompilerOption * option;

  category = new CompilerOptionsCategory(tr("C Options"));

  option = new CompilerOption(tr("support all ANSI standard C programs"));
  option->addBoolFlags("-ansi");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Do not recognize asm, inline or typeof as a keyword"));
  option->addBoolFlags("-fno-asm");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("support some aspects of traditional C compilers"));
  option->addBoolFlags("-traditional");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("support some aspects of traditional C preprocessors"));
  option->addBoolFlags("-traditional-cpp");
  category->addCompilerOption(option);


  category = new CompilerOptionsCategory(tr("Preprocessor"));

  option = new CompilerOption("Do not search system directories");
  option->addBoolFlags("-nostdinc");
  category->addCompilerOption(option);

  option = new CompilerOption("Preprocess only");
  option->addBoolFlags("-E");
  category->addCompilerOption(option);

  category = new CompilerOptionsCategory(tr("Debugging"));

  option = new CompilerOption;
  option->setText("Debug level");
  option->addEmptyFlag();
  option->addFlag("Minimum","-g1");
  option->addFlag("Regular","-g");
  option->addFlag("Maximum","-g3");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Generate prof information"));
  option->addBoolFlags("-p");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Generate gprof information"));
  option->addBoolFlags("-pg");
  category->addCompilerOption(option);

  category = new CompilerOptionsCategory(tr("Warnings"));

  option = new CompilerOption("Check syntax only");
  option->addBoolFlags("-fsyntax-only");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Warning messages level"));
  option->addEmptyFlag();
  option->addFlag(tr("Inhibit"),"-w");
  option->addFlag(tr("All"),"-Wall");
  option->addFlag(tr("Extra"),"-Wextra");
  category->addCompilerOption(option);

  option = new CompilerOption("Issue all the warnings\errors demanded by strict ISO C");
  option->addEmptyFlag();
  option->addFlag("warnings","-pedantic");
  option->addFlag("errors","-pedantic-errors");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Stop compiling after first error"));
  option->addBoolFlags("-Wfatal-errors");
  category->addCompilerOption(option);

  option = new CompilerOption("Make all warnings into errors");
  option->addBoolFlags("-Werror");
  category->addCompilerOption(option);

  option = new CompilerOption("Implicit conversion warnings");
  option->addBoolFlags("-Wconversion");
  category->addCompilerOption(option);

  category = new CompilerOptionsCategory(tr("Optimization"));
  option = new CompilerOption;
  option->setText("optimization level");

  option->addEmptyFlag();
  option->addFlag("Basic","-O");
  option->addFlag("Medium","-O2");
  option->addFlag("High","-O3");
  option->addFlag("Size","-Os");

  category->addCompilerOption(option);
}

void Gcc::parse(const QString &line) const
{
  QString lne = line.trimmed();

  if (lne.startsWith(QLatin1String("ERROR:")) ||
      lne == QLatin1String("* cpp failed")) {

      newMessage(Message::Error,lne);
      return;
    }

  QRegularExpressionMatch match;

  match = m_regExpGccNames.match(lne);
  if (match.hasMatch()) {
      QString description = lne.mid(match.capturedLength());
      Message::MessageType type = Message::Error;
      if (description.startsWith(QLatin1String("warning: "))) {
          type = Message::Warning;
          description = description.mid(9);
        } else if (description.startsWith(QLatin1String("fatal: ")))  {
          description = description.mid(7);
        }
      newMessage(type, description);
      return;
    }

  match = regExp.match(lne);

  if (match.hasMatch()) {
      int lineno = match.captured(3).toInt();
      Message::MessageType type = Message::Unknown;
      QString description = match.captured(8);
      if (match.captured(7) == QLatin1String("warning"))
        type = Message::Warning;
      else if (match.captured(7) == QLatin1String("error") ||
               description.startsWith(QLatin1String("undefined reference to")) ||
               description.startsWith(QLatin1String("multiple definition of")))
        type = Message::Error;

      if (match.captured(5).startsWith(QLatin1Char('#')))
        description = match.captured(5) + description;

      newMessage(type, description, filename, lineno);
      return;

    }

  match = regExpIncluded.match(lne);
  if (match.hasMatch()) {
      newMessage(Message::Unknown,
                 lne.trimmed() /* description */,
                 match.captured(1) /* filename */,
                 match.captured(3).toInt() /* linenumber */,
                 );
      return;

    } else if (lne.startsWith(QLatin1Char(' '))) {
      expandDescription(lne);
      return;
    }

  newMessage(Message::Unknown,lne);
}


QString Mingw::name() const
{
  return "Mingw";
}

QString Mingw::make() const
{

}

void Gcc::doFlush()
{
  if (_currentMessage.isNull())
    return;
  Message msg = _currentMessage;
  //     m_currentTask.clear();
  emit addMessage(msg);
}

void Gcc::newMessage(const QString &type,const QString &description
                     ,const QString &fileName,int lineno)
{
  doFlush();
  Message msg(type,description,fileName,lineno);
  _currentMessage = msg;
}

void Gcc::expandDescription(const QString &desc )
{
  if (_currentMessage.isNull())
    return;

  _currentMessage.info.append(QLatin1Char('\n'));
  _currentMessage.info.append(desc);
}
