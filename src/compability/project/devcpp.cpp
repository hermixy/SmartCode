#include "devcpp.h"
#include <project.h>
#include <bases.h>
#include <core_constants.h>

DevCpp::DevCpp(QObject *parent) :
    QObject(parent)
{

}
void DevCpp::import(const QString &fileName)
{
    QHash<QString ,QVariant> smcProject;

    QString sec,key,value,proName;
    QStringList incs,libs,src,headers;

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
        return;

    while(!file.atEnd())
    {
        QString line = file.readLine();

        if(line.startsWith("[") )
        {
            line.remove("[");line.remove("]");
            sec = line;

        }
        else {
            key = line.left(line.indexOf("="));

            value=line.remove(key);
            value=line.remove("=");


            if(!key.isEmpty())
            {

                item.insert(sec.trimmed()+"/"+key.trimmed(),value.trimmed());
            }
        }

    }
    proName = QFileInfo(fileName).path()+"/"+item.value("Project/Name");

    incs = item.value("Project/Includes").split(";");
    libs = item.value("Project/Libs").split(";");

    foreach(const QString &key,item.keys())
    {
        if(key.contains("Unit"))
        {
            if(item.value(key).contains(Bases::sourceFilesReg()))
                src<<item.value(key);

            else if (item.value(key).contains(Bases::headerFilesReg()))
                headers<<item.value(key);
        }
    }

    smcProject.insert(Core::Project::SOURCES,src);
    smcProject.insert(Core::Project::HEADERS,headers);
    smcProject.insert(Core::Project::INCLUDES,incs);
    smcProject.insert(Core::Project::LIBS,libs);

//    Project::writeProject(proName,smcProject);

}


