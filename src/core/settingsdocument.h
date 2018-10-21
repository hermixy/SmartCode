#ifndef SETTINGSDOCUMENT_H
#define SETTINGSDOCUMENT_H

#include <core_global.h>
#include <QVariant>

class QFile;
class QXmlStreamReader;
class QXmlStreamWriter;
class QDomElement;

class CORESHARED_EXPORT SettingsDocumentReader
{
public:

  SettingsDocumentReader();
  QVariant value(const QString &key) const;
  QVariantMap values() const;
  bool load(const QString &fileName);
private:

  QMap<QString, QVariant> _values;
};


class CORESHARED_EXPORT SettingsDocumentWriter
{
public:
  SettingsDocumentWriter(const QString &fileName,const QString &doc);
  bool save(const QVariantMap &data);
private:
  bool write(const QVariantMap &data);
  void writeVariant(QXmlStreamWriter &w,
                    const QVariant &variant,const QString &key = QString());

  QMap<QString, QVariant> _savedData;

  QString _fileName;
  QString _doc;
};

#endif // SETTINGSDOCUMENT_H
