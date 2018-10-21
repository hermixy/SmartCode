#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <core_global.h>

class QFile;

class CORESHARED_EXPORT FileManager
{
public:
 enum OpenMode
 {
   Read,
   Write,
   ReadWrite
 };
    FileManager(const QString &fileName,OpenMode openMode);
    QFile *file() const;
private:
    QFile * _file;
};

#endif // FILEMANAGER_H
