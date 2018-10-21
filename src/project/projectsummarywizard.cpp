#include "projectsummarywizard.h"
#include "ui_projectsummarywizard.h"

ProjectSummaryWizard::ProjectSummaryWizard(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ProjectSummaryWizard)
{
    ui->setupUi(this);

    registerField("projects",ui->projects);
}

ProjectSummaryWizard::~ProjectSummaryWizard()
{
    delete ui;
}

void ProjectSummaryWizard::setupProjects(const QStringList & projects , bool templateIsProject)
{
    if(templateIsProject)
        ui->projectLabel->setText(tr("Add to subproject"));
    else
        ui->projectLabel->setText(tr("Add to project"));

    ui->projects->addItems(projects);
}

void ProjectSummaryWizard::selectProject(const QString &project)
{
    for(int i = 0; i <  ui->projects->count(); i++)
    {
        if(ui->projects->itemText(i) == project)
            ui->projects->setCurrentIndex(i);
    }
}
