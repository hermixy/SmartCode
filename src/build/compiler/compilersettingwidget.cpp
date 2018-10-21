#include "compilersettingwidget.h"
#include "ui_compilersettingwidget.h"

#include <QMessageBox>

#include "compiler/compilersetting.h"
#include <tabsettingmanager.h>
#include "compiler.h"
#include "gcc.h"

#include <QComboBox>
#include <QFileDialog>
#include <QMenu>
#include <QFormLayout>
#include <bases.h>

using namespace Core::Compiler;

CompilerSettingWidget::CompilerSettingWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CompilerSettingWidget)
{
  ui->setupUi(this);

  setup();

  connect(ui->compilers,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(activeCompiler(QTreeWidgetItem*,int)));
  ui->compilerProgramsGroup->setVisible(false);
}

CompilerSettingWidget::~CompilerSettingWidget()
{
  delete ui;
}


void CompilerSettingWidget::setupCompilerOptions(QWidget *widget)
{
  ui->compilerOptionsLayout->addWidget(widget);
}

void CompilerSettingWidget::autoDetecteCompilers()
{
  autoDetecteGCC();
}


void CompilerSettingWidget::setup()
{
  QMenu * addCompilerButtonMenu = new QMenu;

  QList<QPushButton *> compilerGroupButtons = ui->CompilersWidget->findChildren<QPushButton *>(QRegExp("^pushButton"));

  foreach(QPushButton * button,compilerGroupButtons)
    connect(button,SIGNAL(clicked()),this,SLOT(setProgramPath()));

  addCompilerButtonMenu->addAction("GCC");

  connect(addCompilerButtonMenu,SIGNAL(triggered(QAction*)),this,SLOT(addCompiler(QAction*)));
  ui->addCompilerButton->setMenu(addCompilerButtonMenu);

  connect(ui->compilerName,SIGNAL(textChanged(QString)),this,SLOT(updateCurrentCompilerName(QString)));

  tabSettingManager = new TabSettingManager();

  ui->linkerLayout->addWidget(tabSettingManager->tabSetting(TabSettingManager::Linker));
  ui->searchPathsLayout->addWidget(tabSettingManager->tabSetting(TabSettingManager::SearchPaths));
  ui->macrosLayout->addWidget(tabSettingManager->tabSetting(TabSettingManager::BuildEnvironment));

  autoDetecteCompilers();
}

void CompilerSettingWidget::loadSetting(CompilerSetting *compilerSetting)
{
  ui->cc->setText(compilerSetting->string(CC));
  ui->cxx->setText(compilerSetting->string(CXX));
  ui->make->setText(compilerSetting->string(MAKE));
  ui->dll->setText(compilerSetting->string(SHAREDLIB));
  ui->lib->setText(compilerSetting->string(LIB));
  ui->res->setText(compilerSetting->string(RES));
  ui->dbg->setText(compilerSetting->string(DBG));

  tabSettingManager->load(compilerSetting);

}

void CompilerSettingWidget::setToolChains(const ToolChains &toolChains)
{
  _toolChains = toolChains;

  loadSetting(_toolChains.at(0));
}


//void CompilerSettingWidget::on_Compiler_activated(const QString &arg1)
//{

//    compilerSetting->setCompiler( arg1 + ".xml");
//    compilerSetting->load();

//    loadSetting();

//}


void CompilerSettingWidget::setProgramPath()
{
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Choose Executable"), QDir::currentPath(), tr("All files(*.*)"));

  QList<QLineEdit *> compilerGroupEdits = ui->CompilersWidget->findChildren<QLineEdit *>(QRegExp("^lineEdit"));

  QPushButton *button = (QPushButton *)sender();

  QString buttonName = button->objectName();
  int index = buttonName.at(buttonName.count() - 1).digitValue();

  for(int i = 0 ; i<compilerGroupEdits.count() ; i++)
    {
      const QString objectName= compilerGroupEdits[i]->objectName();
      int currentEditIndex = objectName.at(objectName.count() - 1).digitValue();

      if(currentEditIndex == index)
        {
          compilerGroupEdits[i]->setText(fileName);
          break;
        }
    }
}

void CompilerSettingWidget::createCompiler(const QString &compilerName,Compiler::ToolChain toolchain)
{
  CompilerSetting * toolChain = new CompilerSetting(compilerName + ".xml");
  Compiler * compiler ;

  switch(toolchain)
    {
    case Compiler::GCC:
      compiler = new Gcc;
    case Compiler::MinGW:
      compiler = new Mingw;
    }

  toolChain->setCompiler(compiler);

  _toolChains<< toolChain;
}

void CompilerSettingWidget::addCompiler(QAction * action)
{
  QString compilerName = action->text() ;
  QTreeWidgetItem *compilerItem  = new QTreeWidgetItem(QStringList()<<action->text()<<action->text());
  ui->compilers->addTopLevelItem(compilerItem);

  createCompiler(compilerName,this);
}

void CompilerSettingWidget::cloneCompiler()
{
  QTreeWidgetItem * currentItem = ui->compilers->currentItem();
  QString compilerName = currentItem->text();

  ui->compilers->addTopLevelItem(new QTreeWidgetItem( QStringList()<<currentItem->text(0)
                                                      <<currentItem->text(1)));

  createCompiler(compilerName);


}

void CompilerSettingWidget::removeCompiler()
{
  int index = ui->compilers->currentIndex().row();

  _toolChains.takeAt(index);
  ui->compilers->takeTopLevelItem(index);
}

void CompilerSettingWidget::updateCurrentCompilerName(const QString &compilerName)
{
  ui->compilers->currentItem()->setText(0,compilerName);
}

void CompilerSettingWidget::activeCompiler(QTreeWidgetItem * compilerItem, int col)
{
  ui->compilerProgramsGroup->setVisible(true);
  ui->compilerName->setText(compilerItem->text(col));
}

void CompilerSettingWidget::on_cloneCompilerButton_clicked()
{

}

void CompilerSettingWidget::on_removeCompilerButton_clicked()
{

}
