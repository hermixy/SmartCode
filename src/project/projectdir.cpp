#include "projectdir.h"
#include "ui_projectdir.h"

#include <QDir>
#include <QFileDialog>
#include <QDebug>


ProjectDir::ProjectDir(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::ProjectDir)
{

  ui->setupUi(this);
  ui->errorLabel->setVisible(false);

  registerField(tr("ProjectName"),ui->NameEdit);
  registerField(tr("ProjectDir"),ui->DirEdit);

  ui->NameEdit->setText(tr("Untitled"));

#ifdef Q_OS_WIN32
    ui->DirEdit->setText(QDir::homePath()+"/Documents");
#else
    ui->DirEdit->setText(QDir::homePath());
#endif

  connect(ui->NameEdit,SIGNAL(textChanged(QString)),this,SLOT(checkProjectDir(QString)));
  connect(ui->DirEdit, SIGNAL(textChanged(QString)),this,SLOT(hasError(QString)));

}

ProjectDir::~ProjectDir()
{
  delete ui;
}


void ProjectDir::checkProjectDir(const QString &projectName)
{
  if(projectName.isEmpty())
    showError(tr("FileName is empty"),error);

  else if(!projectAlreadyExsits(ui->DirEdit->text(),projectName))
    {
      hideError();
    }
}

bool ProjectDir::projectAlreadyExsits(const QString &dir ,const QString &projectName)
{
  bool exists = QFileInfo(QDir(dir)
                          .absoluteFilePath(projectName + "/"+ projectName+ ".smc")).exists();

  if(exists)
    showError(tr("Project already exsits"),warning);

  return exists;
}

void ProjectDir::setProjectDir(const QString &dir)
{
  ui->DirEdit->setText(dir);
}

void ProjectDir::hasError(const QString &dir)
{
  if(projectAlreadyExsits(dir,ui->NameEdit->text()))
    return;

  if(!QFileInfo(dir).isDir())
    {
      showError(tr("Directory non valid"),error);
    }
  else
    hideError();
}

void ProjectDir::on_pushButton_clicked()
{
  QString path=QFileDialog::getExistingDirectory(this,tr("Select Directory"));
  ui->DirEdit->setText(path);
}

void ProjectDir::showError(const QString &text ,Message msgType)
{
  this->wizard()->button(QWizard::NextButton)->setEnabled(false);

  switch(msgType)
    {
    case error:
      ui->errorLabel->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255)");

      break;
    case warning:
      ui->errorLabel->setStyleSheet("background-color: rgb(255, 255, 127)");
      break;
    }

  ui->errorLabel->setVisible(true);
  ui->errorLabel->setText(text);
}

void ProjectDir::hideError()
{
  this->wizard()->button(QWizard::NextButton)->setEnabled(true);
  ui->errorLabel->setVisible(false);
}
