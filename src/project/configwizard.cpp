#include "configwizard.h"
#include "ui_configwizard.h"

#include <QDir>
#include "configmanager.h"
#include "config.h"

ConfigWizard::ConfigWizard(ConfigManager *cManager, QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::ConfigWizard)
{
  ui->setupUi(this);

  configManager = cManager;

}

ConfigWizard::~ConfigWizard()
{
  delete ui;
}

void  ConfigWizard::initializePage()
{
  const QString projectPath = field("ProjectDir").toString() + "/" + field("ProjectName").toString() + "/";

  ui->debugOutputDir->setText( projectPath  + "debug");
  ui->releaseOutputdir->setText( projectPath + "release");

  ui->debugObjOutputdir->setText( projectPath   + "debug/obj");
  ui->releaseObjOutputdir->setText( projectPath + "release/obj");

}

bool ConfigWizard::validatePage()
{
  return ui->debugConfig->isChecked() || ui->releaseConfig->isChecked();
}



QList<Config *> ConfigWizard::configs()
{
  QList<Config *> _configs;

  if(ui->debugConfig->isChecked())
    {
      Config * debug = configManager->addDebugConfig();
      _configs << debug;
    }


  if(ui->releaseConfig->isChecked())
    {
      Config * release = configManager->addReleaseConfig();
      _configs <<release;
    }


  return _configs;
}

