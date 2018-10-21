#include "classgenerator.h"
#include "ui_classgenerator.h"

#include <bases.h>
#include <QFileDialog>

ClassGenerator::ClassGenerator(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ClassGenerator)
{

    ui->setupUi(this);
    connect(ui->classname,SIGNAL(textChanged(QString)),this,SLOT(update()));
}

ClassGenerator::~ClassGenerator()
{
    delete ui;
}

void ClassGenerator::setClassPath(const QString &path)
{
    ui->path->setText(path);
}

void ClassGenerator::update()
{

    ui->sourcefile->setText(ui->classname->text().toLower()+".cpp");
    ui->header->setText(ui->classname->text().toLower()+".h");
}

void ClassGenerator::on_toolButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,"Choose Directory");
    ui->path->setText(path);
}

void ClassGenerator::OnAccept()
{
    QString stext;
    QString htext;
    QString className=ui->classname->text();
    QString classParent=ui->classparent->text();

    QString sourceFile=ui->sourcefile->text();
    QString header=ui->header->text();
    QString path=ui->path->text();
    QString srcFile=path+"/"+sourceFile;
    QString hFile=path+"/"+header;


    QString cName = "class " + className;

    if(!classParent.isEmpty())
    {
        QString parentHeader = classParent.toLower() + ".h";

        htext+="#include \""+ parentHeader+"\"";
        htext+="\n";

        QString parent=" : pubic "+classParent;
        htext+=cName+parent;
    }
    else
        htext+=cName;

    htext+="\n{\n";
    htext+="public:\n";
    htext+=className+"();\n";
    htext+="private:\n";
    htext+=  "};";

    stext+="#include \"";
    stext+=header+"\"";
    stext+="\n";
    stext+=className+"::"+ className+"()";
    stext+="\n";
    stext+="{\n}\n";
    //export the texts

    Bases::out(srcFile,stext);
    Bases::out(hFile,htext);

    newClass(QStringList() << srcFile << hFile);
}

bool ClassGenerator::classNameIsValid()
{
    return !ui->classname->text().isEmpty()&&
            !ui->classname->text().contains(" ") &&
            !ui->header->text().isEmpty()&&
            !ui->header->text().contains(" ")&&
            !ui->sourcefile->text().isEmpty()
            && ! ui->sourcefile->text().contains(" ") && QFileInfo(ui->path->text()).exists();

}

bool ClassGenerator::validatePage()
{
    return classNameIsValid();
}
