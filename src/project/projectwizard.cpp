#include "projectwizard.h"

#include "projectdir.h"
#include "configwizard.h"

#include "classgenerator.h"
#include "newfilewizard.h"

#include "projectsummarywizard.h"

#include "project.h"
#include "projectexplorer.h"
#include "projecttemplate.h"

#include <QApplication>
#include <configmanager.h>
#include "runconfig.h"
#include <core_constants.h>

ProjectWizard::ProjectWizard(ProjectExplorer * projectManager,QWidget *parent) :
  QWizard(parent),pManager(projectManager)
{
  connect(this,SIGNAL(accepted()),SLOT(addProject()));

  setWizardStyle(QWizard::ModernStyle);
  //setPixmap(QWizard::BannerPixmap,QPixmap(":/images/intro.png"));
}

QString ProjectWizard::projectPath()
{
  const QString projectName = field("ProjectName").toString();
  return field("ProjectDir").toString()+"/"+ projectName + "/" + projectName+ ".smc";
}

void ProjectWizard::addProject()
{
  QStringList srcFiles = t->toSourceFiles();

  const QString projectName = field("ProjectName").toString();

  QString projectDir = field("ProjectDir").toString() + "/" + projectName;

  QDir dir;
  dir.mkdir(projectDir);

  QString proPath = projectPath() ;

  Project * project = new Project(proPath);

  project->addSetting(Core::Project::CURRENT_CONFIG,0);
  project->addSetting(Core::Project::CURRENT_RUNCONFIG,0);
  project->addSetting(Core::Project::SOURCES,srcFiles);

  project->write();

  ConfigWizard * projectConfg = qobject_cast<ConfigWizard*>(page(1));
  project->addConfigs(projectConfg->configs());

  RunConfig *runConfig = new RunConfig(projectName);

  runConfig->addSetting(Core::Project::RUNEXEC,"");
  runConfig->addSetting(Core::Project::RUNARGS,"");
  runConfig->addSetting(Core::Project::WORKINGDIR,projectDir);

  project->addRunConfig(runConfig);

  int projectParentIndex = field("projects").toInt();

  QString projectParent;

  if(projectParentIndex > 0)
    projectParent = projects[projectParentIndex - 1];

  if(projectParent.isNull())
    pManager->addProject(proPath);
  else
    {
      pManager->newProject(proPath,projectParent);

      Project * parent = pManager->project(projectParent);
      parent->addSubProject(proPath);
    }

  QDir::setCurrent(QApplication::applicationDirPath());

  QFile f;

  foreach(QString file,srcFiles)
    f.copy(templateDir + file, projectDir + "/" + file);

}

void ProjectWizard::setTemplate(const QString &templat)
{
  templateDir = QFileInfo(templat).path() + "/";

  //const QString banner = templateDir + "/banner.png";

  t = new ProjectTemplate;

  t->readTemplate(templat);

  QStringList pages = t->toWizardPages();

  if(pages.contains("ProjectDir"))
    {
      ProjectDir  * projectDir = new ProjectDir;
      addPage(projectDir);
    }

  if(pages.contains("ProjectConfg"))
    {
      ConfigManager * configManager = parentWidget()->findChild<ConfigManager*>("ConfigManager");
      ConfigWizard * projectConfg  = new ConfigWizard(configManager);
      addPage(projectConfg);
    }

  if(pages.contains("ClassGenerator"))
    {
      ClassGenerator * classG = new ClassGenerator;

      classG->setClassPath(pManager->projectPathFromItem());

      addPage(classG);

      connect(this,SIGNAL(accepted()),classG,SLOT(OnAccept()));
      connect(classG,SIGNAL(newClass(QStringList)),pManager,SLOT(addFiles(QStringList)));
    }

  if(pages.contains("NewFile"))
    {
      const QString option = t->pageOption("NewFile");

      NewFileWizard::FileType fileType =  NewFileWizard::TextFile;

      if(option == "SourceFile")
        fileType = NewFileWizard::SourceFile;
      else if(option == "HeaderFile")
        fileType = NewFileWizard::HeaderFile;
      else if(option == "TextFile")
        fileType = NewFileWizard::TextFile;
      else if(option == "XMLFile")
        fileType = NewFileWizard::XMLFile;

      NewFileWizard * newFileWizard = new NewFileWizard(fileType , pManager->projectPathFromItem());

      connect(newFileWizard,SIGNAL(newFileAdded(QStringList)),pManager,SLOT(addFiles(QStringList)));

      addPage(newFileWizard);
    }

  ProjectSummaryWizard * summary = new ProjectSummaryWizard;

  foreach(QString projectName , pManager->Projects())
    {
      if(t->templateType() == "project")
        {
          if(pManager->project(projectName)->hasSubProjects())
            projects << projectName;

          summary->setupProjects(projects,true);

        }
      else if(t->templateType() == "file")
        {
          if(!pManager->project(projectName)->hasSubProjects())
            projects << projectName;

          summary->setupProjects(projects,false);
        }

    }

  summary->selectProject(pManager->projectNameFromItem());

  addPage(summary);

}
