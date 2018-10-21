#ifndef AUTOSAVE_H
#define AUTOSAVE_H

#include "core_global.h"
#include <QObject>

class CORESHARED_EXPORT AutoSave : public QObject
{
    Q_OBJECT
public:
    explicit AutoSave(QObject *parent = 0);

signals:
    
public slots:
    void doSave(const QString &fileName, const QString &context);
};

#endif // AUTOSAVE_H
