#include "classparsermanager.h"
#include <projectexplorer.h>
#include <QDir>
#include <QDirIterator>
#include <core_constants.h>
#include <bases.h>
#include <QDebug>
#include <QDomElement>

#include <classparser.h>

ClassParserManager::ClassParserManager(ProjectExplorer * explorer ,QObject *parent) :
    QObject(parent)

{
    pExplorer = explorer;

}

void ClassParserManager::setClassParser(ClassParser * parser)
{
    classParserModel = parser;

    connect(pExplorer,SIGNAL(projectAdded()),this,SLOT(load()));
//    connect(pExplorer,SIGNAL(projectClosed()),this,SLOT(save()));

    connect(pExplorer,SIGNAL(fileAdded(QString)),this,SLOT(setupClassModel(QString)));
}

void ClassParserManager::parse()
{
    const QString path = "C:/smart";

    QStringList files;

    QDirIterator it(path,QStringList() << "*.h",QDir::Files |QDir::AllDirs|QDir::NoDotAndDotDot
                    , QDirIterator::Subdirectories);

    while(it.hasNext())
    {
        files<< it.next();
    }

    //    QStandardItem * incs , *item;

    //    incs = new QStandardItem;

    //    item = new QStandardItem(path);

    //    incs->setText("Includes");
    //    incs->appendRow(item);

    //    pExplorer->h.insert(incs,"C:/smart/includes");
    //    pExplorer->fileName.insert(incs,"C:/smart/includes");

    //    pExplorer->h.insert(item,"C:/smart/includes/"+ path);
    //    pExplorer->fileName.insert(item,path);

    //    pExplorer->fileName.key("C:/smart/smart.smc")->appendRow(incs);

    //    pExplorer->printFiles("C:/smart/includes",files,path);

    //    qDebug() <<  pExplorer->fileName.values();

    //    pExplorer->addParentItem(pExplorer->currentProjectName(),Core::Project::ProjectIncludes,files);

    //    foreach(QString file ,files)
    //    {
    //        if(QFileInfo(file).isFile())
    //            classParserModel->parseFile(file,pExplorer->fileName.key(file));
    //    }
}

void ClassParserManager::setupClassModel(const QString &fileName)
{
    const QString fileType = pExplorer->fileType(fileName);

    if( fileType == Core::Project::SOURCES || fileType == Core::Project::HEADERS)
        classParserModel->parseFile(fileName,pExplorer->fileNameItem(fileName));

}

void ClassParserManager::updateClassModel(const QString &var)
{
    //    QString fileName = editor->currentTabFilePath();

    //    if(fileType(fileName) == Core::Project::HEADERS)
    //        fileName = ClassParser::swapHeaderSource(fileName);

    //    QStandardItem * p = this->fileName.key(fileName);

    //    //    if(p)
    //    //        classParserModel->addItem(var,p);

}


