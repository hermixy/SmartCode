#include "filemanager.h"
#include <QFile>

FileManager::FileManager(const QString &fileName,FileManager::OpenMode openMode)
{
  _file = new QFile(fileName);
  _file->open(openMode);
}

QFile *FileManager::file() const
{
  return _file;
}

