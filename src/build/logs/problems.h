#ifndef PROBLEMS_H
#define PROBLEMS_H

#include <QTreeWidget>

class Compiler;
class BuildManager;

class  Problems : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Problems(BuildManager *buildManager, QWidget *parent = 0);
signals:
    void openFile(const QString &fileName,int line,int index);
public slots:
    void addError(const QString &data);
    void findErrorLineNumber(QTreeWidgetItem*item, int);
    void showMessage(const QString &text, const QIcon &icon);
private slots:
    void showMenu();
    void copy();
    void showOutput();
    void addItemMessage(const Message &msg);
private:
    BuildManager *_buildManager;
};

#endif //  PROBLEMS_H
