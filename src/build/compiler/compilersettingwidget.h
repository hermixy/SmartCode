#ifndef COMPILERSETTINGWIDGET_H
#define COMPILERSETTINGWIDGET_H

#include "BUILD_global.h"

#include <QDialog>
#include <QDir>
#include <QHash>

class CompilerSetting;
class TabSettingManager;
class QListWidgetItem;
class QTreeWidgetItem ;
class Compiler;

namespace Ui {
  class CompilerSettingWidget;
}

typedef QList<CompilerSetting*> ToolChains;

class BUILDSHARED_EXPORT CompilerSettingWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CompilerSettingWidget(QWidget *parent = 0);

  ~CompilerSettingWidget();

  QStringList Libs();

  void setupCompilerOptions(QWidget * widget);

  void setToolChains(const ToolChains &toolChains);

signals:

private slots:
  //    void on_autoDetecte_clicked();
  void setProgramPath();

  void createCompiler(const QString &compilerName, Compiler::ToolChain toolchain);
  void addCompiler(QAction *action);

  void cloneCompiler();
  void removeCompiler();

  void updateCurrentCompilerName(const QString &compilerName);
  void activeCompiler(QTreeWidgetItem * compilerItem, int col);

  void on_cloneCompilerButton_clicked();

  void on_removeCompilerButton_clicked();

private:

  int currentButtonClicked;

  void setup();
  void loadSetting(CompilerSetting *compilerSettings);

  Ui::CompilerSettingWidget *ui;
  TabSettingManager *tabSettingManager;


  ToolChains _toolChains;

  void autoDetecteCompilers();
};

#endif // COMPILERSETTINGWIDGET_H
