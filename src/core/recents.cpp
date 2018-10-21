#include "recents.h"
#include <QDebug>
Recents::Recents(QObject *parent ) :
    QObject(parent)
{


}
void Recents::setKey(const QString &newKey)
{
    key = newKey;
}

void Recents::remove(const QString &recent)
{
    QSettings settings;

    QStringList recents = settings.value(key).toStringList();
    recents.removeOne(recent);

    settings.setValue(key, recents);
    updateRecentActions();
}

void Recents::set(QMenu * m)
{
    menu = m;

    for (int i = 0; i < MaxRecents; ++i)
    {
        recentActs[i] = new QAction(this);
    }

    for (int i = 0; i < MaxRecents; ++i)
        menu->addAction(recentActs[i]);

    menu->addSeparator();

    clearMenuAct = menu->addAction("Clear Menu",this,SLOT(clear()));

    updateRecentActions();
}
void Recents::setCurrentRecent(const QString &recentName)
{
    curRecent = recentName;

    QSettings settings;

    QStringList recents = settings.value(key).toStringList();

    recents.removeAll(curRecent);
    recents.prepend(curRecent);

    while (recents.size() > MaxRecents)
        recents.removeLast();

    settings.setValue(key, recents);

    updateRecentActions();
}
void Recents::updateRecentActions()
{
    QSettings settings;

    QStringList recents = settings.value(key).toStringList();

    int numRecents = qMin(recents.size(), (int)MaxRecents);

    for (int i = 0; i < numRecents; ++i) {

        recentActs[i]->setText(recents[i]);
        recentActs[i]->setVisible(true);
    }

    for (int j = numRecents; j < MaxRecents; ++j)
        recentActs[j]->setVisible(false);

    clearMenuAct->setVisible(numRecents > 0);
}

void Recents::clear()
{
    QSettings settings;
    settings.remove(key);

    menu->clear();
}
