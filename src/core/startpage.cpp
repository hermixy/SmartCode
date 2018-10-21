#include "startpage.h"
#include "ui_startpage.h"

#include <QSettings>
StartPage::StartPage(QWidget *parent) :
  QScrollArea(parent),
  ui(new Ui::StartPage)
{

  ui->setupUi(this);

  connect(ui->newproject,SIGNAL(clicked()),this,SIGNAL(newProject()));
  connect(ui->openproject,SIGNAL(clicked()),this,SIGNAL(openProject()));

  setupRecentProjectList();
}

StartPage::~StartPage()
{
  delete ui;
}

QListWidget *StartPage::list() const
{
  return ui->listWidget;
}

void StartPage::setupRecentProjectList()
{
  QSettings settings;


  addItems(ui->listWidget,settings.value("Recents projects").toStringList());

}

void StartPage::addItems(QListWidget *listWidget,QStringList texts)
{
  QListWidgetItem *listWidgetItem;

  foreach(QString text,texts)
    {
      listWidgetItem = new QListWidgetItem;

      listWidgetItem->setText(QFileInfo(text).baseName());
      listWidgetItem->setToolTip(text);

      listWidget->addItem(listWidgetItem);
    }
}


void StartPage::on_listWidget_itemClicked(QListWidgetItem *item)
{
  recentClicked(item->toolTip());
}
