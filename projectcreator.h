#ifndef PROJECTCREATOR_H
#define PROJECTCREATOR_H

#include <QStringList>

class ProjectCreator
{
public:
    ProjectCreator();
    void createProject(QString video, int FPS, QStringList audioFileNames, QList<int> audioFileSizes, QStringList subs, QStringList celltimes, QString sourceFolder, QString destinationFolder);

};

#endif // PROJECTCREATOR_H
