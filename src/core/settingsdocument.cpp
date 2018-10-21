#include "settingsdocument.h"
#include "bases.h"
#include "core_constants.h"

#include <QCoreApplication>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDateTime>
#include <QRect>
#include <QStack>
#include "filemanager.h"

const char PROPRETY[] = "proprety";
const char PROPRETYLIST[] = "propretyList" ;
const char PROPRETYMAP[] = "propretyMap";

static QString rectToString(const QRect &r)
{
  QString result;
  QTextStream(&result) << r.width() << 'x' << r.height() << forcesign << r.x() << r.y();
  return result;
}

static QRect stringToRect(const QString &v)
{
  static QRegExp pattern(QLatin1String("(\\d+)x(\\d+)([-+]\\d+)([-+]\\d+)"));
  Q_ASSERT(pattern.isValid());
  return pattern.exactMatch(v) ?
        QRect(QPoint(pattern.cap(3).toInt(), pattern.cap(4).toInt()),
              QSize(pattern.cap(1).toInt(), pattern.cap(2).toInt())) :
        QRect();
}

class Proprety
{
public:

  Proprety(const QString &k,QVariant::Type t)
    :key(k),type(t)
  {

  }

  Proprety(const QString &k,const QVariant &v)
    :key(k),type(v.type()),simpleProprety(v)
  {
  }

  QVariant value() const
  {
    switch (type) {
      case QVariant::Invalid:
        return QVariant();
      case QVariant::Map:
        return QVariant(propretyMap);
      case QVariant::List:
        return QVariant(propretyList);
      default:
        break;
      }
    return simpleProprety;
  }

  void addPropretyChild(const QString &key,const QVariant &v)
  {
    switch (type) {
      case QVariant::Map:
        propretyMap.insert(key, v);
        break;
      case QVariant::List:
        propretyList.push_back(v);
        break;
      default:
        qWarning() << "Variant::Internal error adding " << key << v << " to "
                   << QVariant::typeToName(type) << value();
        break;
      }
  }

private:
  QString key;
  QVariant::Type type;

  QVariant simpleProprety;
  QVariantList propretyList;
  QVariantMap propretyMap;
};

QVariant SettingsDocumentReader::value(const QString &key) const
{
  return _values.value(key);
}

QVariantMap SettingsDocumentReader::values() const
{
  return _values;
}

bool SettingsDocumentReader::load(const QString &fileName)
{
  _values.clear();

  QFile file(fileName);

  if(!file.open(QFile::ReadOnly))
    return false;

  SettingsDocumentParser parser;
  _values = parser.parse(file);

  file.close();

  return true;
}

class SettingsDocumentParser
{
public:
  enum PropretyElement{PropretyDocument,SimpleProprety,PropretyList,PropretyMap};

  QVariantMap parse(QFile &file);
  PropretyElement element(const QStringRef &r) const;
  bool processStartElement(QXmlStreamReader &reader);
  bool processEndElement(const QStringRef &name);

private:
  bool isValueElement( PropretyElement element);

  QVariantMap _result;
  QStack<Proprety> _valuesStack;
  QString _currentVariableName;
};

QVariantMap SettingsDocumentParser::parse(QFile &file)
{
  QXmlStreamReader reader(file);

  _result.clear();

  while (!reader.atEnd()) {

      switch(reader.tokenType())
        {
        case QXmlStreamReader::StartElement:
          if(processStartElement(reader))
            return _result;
        case QXmlStreamReader::EndElement:
          if(processEndElement(reader))
            return _result;
        default:
          break;
        }
    }

  return _result;
}

SettingsDocumentParser::PropretyElement SettingsDocumentParser::element(const QStringRef &r) const
{
  if(name == PROPRETY)
    return SimpleProprety;
  if(name == PROPRETYLIST)
    return PropretyList;
  if(name == PROPRETYMAP)
    return PropretyMap;

  return PropretyDocument;
}

bool SettingsDocumentParser::processStartElement(QXmlStreamReader &reader)
{
  QStringRef name = reader.name();

  const PropretyElement e = element(name);
  const QXmlStreamAttributes attributes = r.attributes();
  _currentVariableName = attributes.value(Core::Project::NAME).toString();

  switch(e)
    {
    case SimpleProprety:
      QVariant variant;
      variant.setValue(attributes.value(Core::Project::VALUE).toString());
      _valuesStack.push_back(Proprety(_currentVariableName,variant));
      return processEndElement(reader);
      break;
    case PropretyList:
      _valuesStack.push_back(Proprety(_currentVariableName,QVariant::List));
      break;
    case PropretyMap:
      _valuesStack.push_back(Proprety(_currentVariableName,QVariant::Map));
      break;
    }

  return false;
}

bool SettingsDocumentParser::processEndElement(const QStringRef &name)
{
  const PropretyElement e = element(name);

  if (isValueElement(e)) {
      if(_valuesStack.isEmpty())
        return true;
      const Proprety top = _valuesStack.pop();
      if (_valuesStack.isEmpty()) {
          if( _currentVariableName.isEmpty())
            return true;

          _result.insert(_currentVariableName, top.value());
          _currentVariableName.clear();
          return false;
        }
      _valuesStack.top().addPropretyChild(top.key, top.value());
    }

  return e == PropretyDocument;
}

bool SettingsDocumentParser::isValueElement(SettingsDocumentParser::PropretyElement element)
{
  return (element == SimpleProprety)|| (element == PropretyList)|| (element == PropretyMap);
}

SettingsDocumentWriter::SettingsDocumentWriter(const QString &fileName, const QString &doc)
  :_fileName(fileName),_doc(doc)
{

}

bool SettingsDocumentWriter::save(const QVariantMap &data)
{
  if(_savedData == data)
    return true;

  return write(data);
}



bool SettingsDocumentWriter::write(const QVariantMap &data)
{
  FileManager saver(_fileName,FileManager::Write);

  QXmlStreamWriter writer(saver.file());

  writer.setAutoFormatting(true);
  writer.setAutoFormattingIndent(1);
  writer.writeStartDocument();
  writer.writeDTD(QLatin1String("<!DOCTYPE ") + _doc + QLatin1Char('>'));
  writer.writeComment(QString::fromLatin1(" Written by %1 %2, %3. ").
                      arg(QCoreApplication::applicationName(),
                          QCoreApplication::applicationVersion(),
                          QDateTime::currentDateTime().toString(Qt::ISODate)));
  writer.writeStartElement(_doc);

  foreach (const QString &key,data.keys()) {
      writeVariant(writer,data.value(key),key);
    }

  writer.writeEndDocument();

  _savedData = data;

  return true;
}

void SettingsDocumentWriter::writeVariant(QXmlStreamWriter &w,
                                          const QVariant &variant , const QString &key)
{
  switch(variant.type())
    {
    case QVariant::List:
    case QVariant::StringList:
      w.writeStartElement(PROPRETYLIST);

      if(!key.isEmpty())
        w.writeAttribute("name",key);

      QList<QVariant> list = variant.toList();

      foreach(const QVariant &var ,list)
        {
          writeVariant(w,var);
        }

      w.writeEndElement();
      break;
    case QVariant::Map:{

        w.writeStartElement(PROPRETYMAP);

        if(!key.isEmpty())
          w.writeAttribute("name",key);

        const QVariantMap varMap = variant.toMap();

        foreach(const QString &key,varMap.keys())
          {
            writeVariant(w,varMap.value(key),key);
          }

        w.writeEndElement();
      }
      break;
    default:
      w.writeStartElement(PROPRETY);
      w.writeAttribute("name",key);
      w.writeAttribute("value",variant.toString());
      w.writeEndElement();
      break;

    }
}

