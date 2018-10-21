#include "codeblocks.h"
#include <QtXml>
#include <project.h>


CodeBlocks::CodeBlocks(QObject *parent) :
    QObject(parent)
{
}

void CodeBlocks::import(const QString &cbp)
{
    QHash<QString , QVariant> smcProject;

    QString smcProjectName;
    QFile file(cbp);

    if(!file.open(QFile::ReadOnly))
        return ;

    QDomDocument doc;
    doc.setContent(&file);

    QDomElement root = doc.documentElement();

    QDomElement project = root.firstChildElement("Project");

    QDomElement item = project.firstChild().toElement();

    while(!item.isNull())
    {
        if(item.tagName() == "Option")
        {
            if(!item.attribute("title").isNull())
                smcProjectName = item.attribute("title");


        }

        if(item.tagName() == "Build")
        {
            QDomElement target = item.firstChild().toElement();

            while(!target.isNull())
            {
                target = target.nextSibling().toElement();

                if(item.tagName() == "Option")
                {
                    if(!item.attribute("title").isNull())
                        smcProjectName = item.attribute("title");

                    else if(!item.attribute("object_output").isNull())
                        smcProject.insert(Core::Project::OBJECTSDIR,item.attribute("object_output"));

                }

            }


        }

        item = item.nextSibling().toElement();
    }


}
