#include "texteditarea.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QStandardItem>
#include <QLabel>
#include <QDebug>
#include "textedit.h"
#include "texteditmanager.h"
#include "classparser.h"

TextEditArea::TextEditArea(const QString &fileName , DataType dataType, QWidget *parent) :
  QWidget(parent)
{
  switch(dataType)
    {
    case Text:
      createTextArea(fileName);
      break;
    case Image:
      createImageArea(fileName);
      break;
    }
}

void TextEditArea::setFileItem(QStandardItem * item)
{
  fileItem = item;

  QStringList list;

  parseItem(fileItem,fileItem,list);

  upadteNmcClsStrList(list);
}

void TextEditArea::createTextArea(const QString &fileName)
{
  QHBoxLayout * hLayout = new QHBoxLayout;
  QVBoxLayout * vLayout = new QVBoxLayout;

  textEdit = new TextEdit;

  textEdit->setFileName(fileName);

  nmcClsStrList = new QComboBox;
  methodsVarsList = new QComboBox;

  hLayout->addWidget(nmcClsStrList);
  hLayout->addWidget(methodsVarsList);


  hLayout->setSpacing(0);

  vLayout->addLayout(hLayout);
  vLayout->addWidget(textEdit);

  vLayout->setContentsMargins(0,0,0,0);
  vLayout->setSpacing(0);

  connect(nmcClsStrList,SIGNAL(activated(QString)),this,SLOT(upadteMethodsVarsList(QString)));
  setLayout(vLayout);
}

void TextEditArea::createImageArea(const QString &fileName)
{
  auto label = new QLabel;
  label->setPixmap(QPixmap(fileName));

  QHBoxLayout * hLayout = new QHBoxLayout;
  hLayout->setAlignment(Qt::AlignHCenter);

  setLayout(hLayout);

}

void TextEditArea::upadteNmcClsStrList(const QStringList &items)
{
  nmcClsStrList->clear();
  nmcClsStrList->addItems(items);
}

void TextEditArea::upadteMethodsVarsList(const QString &context)
{
  methodsVarsList->clear();
  methodsVarsList->addItems(TextEditManager::classParer()->findTypeItems(context.split("::"),fileItem));
}

void TextEditArea::parseItem(QStandardItem *item,const QStandardItem *fileItem,QStringList &list)
{

  if(item->data() == "class" )
    {

      QStringList context;

      QStandardItem * curItem = item;

      while(curItem != fileItem)
        {
          context.prepend(curItem->text());

          curItem = curItem->parent();
        }

      list.append(context.join("::"));
    }

  for(int row = 0 ; row < item->rowCount() ;++ row)
    {
      parseItem(item->child(row),fileItem,list);
    }


}


