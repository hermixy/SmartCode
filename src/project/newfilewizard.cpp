#include "newfilewizard.h"
#include "ui_newfilewizard.h"

#include <bases.h>

NewFileWizard::NewFileWizard(FileType _fileType ,const QString &path,QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::NewFileWizard),
    fileType(_fileType)
{
    ui->setupUi(this);


    ui->path->setText(path);

    connect(wizard(),SIGNAL(accepted()),this,SLOT(OnAccept()));
}

NewFileWizard::~NewFileWizard()
{
    delete ui;
}

void NewFileWizard::onAccept()
{
    QString text;

    QString filePath = ui->path->text() + "/" + ui->fileName->text() ;

    if(fileType == SourceFile)
    {
        if(hasNotSuffix(ui->fileName->text()))
        {
            filePath += ".cpp" ;
        }

    }
    else if(fileType == HeaderFile)
    {
        QString headerNameUpper = Bases::baseName(filePath) + "_";

        if(hasNotSuffix(ui->fileName->text()))
        {
            filePath += ".h" ;
            headerNameUpper += "H" ;
        }

        else
        {
            headerNameUpper += Bases::fileSuffix(ui->fileName->text()).toUpper() ;
        }

        text += "#ifndef " + headerNameUpper;
        text += "#define " + headerNameUpper;
        text += "\n";
        text += "#endif // " + headerNameUpper;

    }

    else if(fileType == TextFile)
    {
        if(hasNotSuffix(ui->fileName->text()))
        {
            filePath += ".txt" ;
        }
    }

    else if(fileType == XMLFile)
    {
        if(hasNotSuffix(ui->fileName->text()))
        {
            filePath += ".xml" ;
        }
    }

    Bases::out(filePath , text);
    emit newFileAdded(QStringList() << filePath);
}

bool NewFileWizard::hasNotSuffix(const QString &fileName)
{
    return Bases::fileSuffix(fileName).isEmpty();
}
