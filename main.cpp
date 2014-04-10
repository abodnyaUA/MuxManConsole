#include <QtCore/QCoreApplication>
#include <QDebug>
#include <string.h>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QStringList>
#include <QDir>
#include "base.h"
#include "projectcreator.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    if (args.count() < 4)
    {
        printError();
    }

    QString sourceFolder = args.at(1);
    qDebug() << "Sorce Folder: " << sourceFolder << "\n";
    QDir dir(sourceFolder);

    //VIDEO
    int FPS = args.at(2).toInt();
    if (FPS != 25 && FPS != 30)
    {
        printError();
    }

    QString video = dir.entryList(QStringList("*.m2v")).at(0);
    qDebug() << "video: " << video << "\n";

    //AUDIO
    QStringList audio = dir.entryList(QStringList("*.ac3"));
    QList<int> audio_sizes;

    if (audio.last() != "Untitled.ac3")
    {
        qDebug() << "Missed Untitled.ac3 file";
        exit(0);
    }
    audio.removeLast();
    audio.insert(0,"Untitled.ac3");

    for (int i=0;i<audio.count();i++)
    {
        // Rest files //
        QFileInfo info(sourceFolder + SLASH + audio.at(i));
        audio_sizes.append(info.size());
        qDebug() << "audio: " << audio.at(i) << "; size = " << audio_sizes.at(i) << "\n";
    }

    //SUBS
    QStringList subtitles = dir.entryList(QStringList("*.sup"));

    for (int i=0;i<subtitles.count();i++)
    {
        qDebug() << "subs: " << subtitles.at(i) << "\n";
    }

    //CELLTIMES
    QString celltimesFile = QString("Celltimes.txt");
    qDebug() << "Celltimes: " << celltimesFile << "\n";

    QFile file(sourceFolder + SLASH + celltimesFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) printError();

    QStringList celltimes;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        int times = line.toInt();

        int hours = times / (FPS * 60 * 60);
        times = times - hours * 60 * 60 * FPS;

        int min = times / (FPS * 60);
        times = times - min * 60 * FPS;

        int sec = times / FPS;
        times = times - sec * FPS;

        int frames = times;

        QString time_format;
        if (hours < 10) time_format += "0";
        time_format += (QString::number(hours)+":");
        if (min < 10) time_format += "0";
        time_format += (QString::number(min)+":");
        if (sec < 10) time_format += "0";
        time_format += (QString::number(sec)+":");
        if (frames < 10) time_format += "0";
        time_format += (QString::number(frames));

        qDebug() << time_format;
        celltimes.append(time_format);
    }

    //DESTINATION FOLDER
    QString destination = args.at(3);
    qDebug() << "destination: " << destination;

    ProjectCreator creator;
    creator.createProject(video, FPS, audio, audio_sizes, subtitles, celltimes, sourceFolder, destination);

    QString muxman = QString("muxman temp.mxp -d ") + destination + QString(" -run");
    system(muxman.toAscii());
}
