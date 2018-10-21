#include "environment.h"
#include "host.h"
#include <QDir>
#include <QProcess>

Environment::Environment()
{

}


QString Environment::searchInPath(const QString &fileName)
{
  QStringList paths = value(QLatin1String("PATH")).split(pathListSeparator());

  foreach(QString path,paths)
    {
      QString pathFileName = path + QLatin1Char('/') + fileName;

      QFileInfo info(pathFileName);

      if(info.exists() && info.isFile() && info.isExecutable())
        return pathFileName;
    }

  return QString();
}

QChar Environment::pathListSeparator()
{
  if(Host::isWindowsHost())
    return QLatin1Char(';');
  else if(Host::isLinuxHost())
    return QLatin1Char(':');

  return QChar();
}

Environment Environment::systemEnvironment()
{
  Environment env ;
  env.fromList(QProcess::systemEnvironment());
  return env;
}

void Environment::appendOrSet(const QString &key, const QString &value, const QString &sep)
{
    const QString &_key = (Host::isWindowsHost() ? key.toUpper() : key);
    QMap<QString, QString>::iterator it = _values.find(_key);
    if (it == m_values.end()) {
       _values.insert(_key, value);
    } else {
        // Append unless it is already there
        const QString toAppend = sep + value;
        if (!it.value().endsWith(toAppend))
            it.value().append(toAppend);
    }
}

void Environment::prependOrSet(const QString&key, const QString &value, const QString &sep)
{
    const QString &_key = (Host::isWindowsHost() ? key.toUpper() : key);
    QMap<QString, QString>::iterator it = _values.find(_key);
    if (it == m_values.end()) {
        _values.insert(_key, value);
    } else {
        // Prepend unless it is already there
        const QString toPrepend = value + sep;
        if (!it.value().startsWith(toPrepend))
            it.value().prepend(toPrepend);
    }
}

void Environment::appendOrSetPath(const QString &value)
{
    appendOrSet(QLatin1String("PATH"), QDir::toNativeSeparators(value),
            QString(pathListSeparator()));
}

void Environment::prependOrSetPath(const QString &value)
{
    prependOrSet(QLatin1String("PATH"), QDir::toNativeSeparators(value),
            QString(pathListSeparator()));
}
