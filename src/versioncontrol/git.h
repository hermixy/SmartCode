#ifndef GIT_H
#define GIT_H

#include "versioncontrol_global.h"

#include "versioncontrol.h"

class VERSIONCONTROLSHARED_EXPORT Git : public VersionControl
{

public:
    Git();

    QString name() const;
    QString blame(const QString &fileName);


protected:
    
};

#endif // GIT_H
