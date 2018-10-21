#include "insertfunctionswidget.h"
#include "ui_insertfunctionswidget.h"

#include <QListWidgetItem>
#include <QDebug>

#include "classparser.h"

InsertFunctionsWidget::InsertFunctionsWidget(ClassParser *classParser,const QString &fileName ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertFunctionsWidget)
{
    ui->setupUi(this);

    clParser = classParser;
    QString header = clParser->swapHeaderSource(fileName);
    QStringList classes = clParser->findFileClasses(header);

    ui->classes->addItems(classes);
}

InsertFunctionsWidget::~InsertFunctionsWidget()
{
    delete ui;
}

void InsertFunctionsWidget::on_methods_itemActivated(QListWidgetItem *item)
{

}

void InsertFunctionsWidget::on_classes_itemClicked(QListWidgetItem *item)
{
    QString className = item->text();

    QString header = "";/*clParser->findClassHeader(className)*/
    QStringList list ;//= clParser->funcsListFromFile(header,className);

    QListWidgetItem *method;

    foreach(QString function, list)
    {
        method = new QListWidgetItem(clParser->regularFunction(function,className)) ;
        method->setCheckState(Qt::Unchecked);

        ui->methods->addItem(method);
    }

}

void InsertFunctionsWidget::accept()
{
    QStringList methods;

    for(int i=0;i<ui->methods->count();i++)
    {
        QListWidgetItem *item;
        item =  ui->methods->item(i);

        if(item->checkState() == Qt::Checked)
        {
            QString method = item->text();
            methods<<method;
        }
    }

    QDialog::accept();

    emit methodsSelected(methods);
}
