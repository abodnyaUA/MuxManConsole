#include "projectcreator.h"
#include <QFile>
#include <QTextStream>
#include "base.h"

ProjectCreator::ProjectCreator()
{
}

void ProjectCreator::createProject(QString video, int FPS, QStringList audioFileNames, QList<int> audioFileSizes, QStringList subtitles, QStringList celltimes, QString sourceFolder, QString destinationFolder)
{
    QFile file_project("temp.mxp");
    if (!file_project.open(QIODevice::WriteOnly | QIODevice::Text)) printError();

    QTextStream out(&file_project);
    out << "mxp Section=Settings" << "\n";
    out << "{" << "\n";
    out << "	Project Name=" << "\n";
    out << "	Provider ID=MPUCODER" << "\n";
    out << "	Destination Folder=" << destinationFolder << "\n";
    out << "	Portfolio=C:\\MuxManTemp" << "\n";
    out << "	Region Mask=00" << "\n";
    out << "	Volume=1" << "\n";
    out << "	Number of Volumes=1" << "\n";
    out << "	Side=1" << "\n";
    out << "	Create Default Nav=Yes" << "\n";
    out << "	Default Btn Self=No" << "\n";
    out << "	Item=Palette" << "\n";
    out << "	{" << "\n";
    out << "		Name=DefaultPalette" << "\n";
    out << "		Color 0=0, 0, 255" << "\n";
    out << "		Color 1=255, 0, 0" << "\n";
    out << "		Color 2=0, 0, 0" << "\n";
    out << "		Color 3=255, 255, 255" << "\n";
    out << "		Color 4=0, 255, 0" << "\n";
    out << "		Color 5=255, 0, 255" << "\n";
    out << "		Color 6=255, 255, 0" << "\n";
    out << "		Color 7=0, 125, 125" << "\n";
    out << "		Color 8=125, 125, 125" << "\n";
    out << "		Color 9=225, 225, 225" << "\n";
    out << "		Color 10=125, 0, 0" << "\n";
    out << "		Color 11=0, 125, 0" << "\n";
    out << "		Color 12=0, 0, 125" << "\n";
    out << "		Color 13=222, 0, 255" << "\n";
    out << "		Color 14=222, 125, 0" << "\n";
    out << "		Color 15=125, 0, 125" << "\n";
    out << "	}" << "\n";
    out << "}" << "\n";
    out << "Section=Content" << "\n";
    out << "{" << "\n";
    out << "	Item=Segment" << "\n";
    out << "	{" << "\n";
    out << "		Name=Segment_1" << "\n";
    out << "		Display Mode=none" << "\n";
    out << "		Resolution=none" << "\n";
    out << "		Force=No" << "\n";
    out << "		Item=Video Stream" << "\n";
    out << "		{" << "\n";
    out << "			Coding Mode=Mpeg-2" << "\n";
    out << "			Standard=";
    if (FPS == 25) out << "PAL\n";
    else out << "NTSC\n";
    out << "			CC Field 1=Yes" << "\n";
    out << "			CC Field 2=No" << "\n";
    out << "			Item=Video Play" << "\n";
    out << "			{" << "\n";
    out << "				File=" << sourceFolder << '\\' << video << "\n";
    out << "				Duration=Actual" << "\n";
    out << "			}" << "\n";
    out << "		}" << "\n";

    for (int i=0;i<audioFileNames.count();i++)
    {
        out << "		Item=Audio Stream" << "\n";
        out << "		{" << "\n";
        out << "			Stream Number=" << (i+1) << "\n";
        out << "			Language Extension=1" << "\n";
        out << "			Delay=0" << "\n";
        out << "			Type=04c1" << "\n";
        out << "			Frame Size=" << 768 << "\n";
        out << "			Item=Audio Play" << "\n";
        out << "			{" << "\n";
        out << "				File=" << sourceFolder << SLASH << audioFileNames [i] << "\n";
        out << "				Size=" << audioFileSizes[i] << "\n";
        out << "			}" << "\n";
        out << "		}" << "\n";
    }
    out << "		Item=Scene List" << "\n";
    out << "		{" << "\n";

    out << "			Item=Scene" << "\n";
    out << "			{" << "\n";
    out << "				Name=Segment_1_scn" << (1) << "\n";
    out << "				Scene Time=" << "00" << ":" << "00" << ":" << "00" << ":" << "00" << "\n";
    out << "				Uop=00000000" << "\n";
    out << "			}" << "\n";

    for (int i=0;i<subtitles.count();i++)
    {
        out << "		Item=Sub-Picture Stream" << "\n";
        out << "		{" << "\n";
        out << "			Stream Number=" << (i+1) << "\n";
        out << "			Language=en" << "\n";
        out << "			Language Extension=1" << "\n";
        out << "			Display Mode=unspecified" << "\n";
        out << "			Item=Sub-Picture Play" << "\n";
        out << "			{" << "\n";
        out << "				File=" << sourceFolder << SLASH << subtitles [i] << "\n";
        out << "				Time Code=";
        if (FPS == 25) out << "PAL\n";
        else out << "NTSC\n";
        out << "				Start=00:00:00:00" << "\n";
        out << "				Display=00:00:00:00" << "\n";
        out << "				Duration=00:00:00:00" << "\n";
        out << "			}" << "\n";
        out << "		}" << "\n";
    }

    for (int i=0;i<celltimes.count();i++)
    {
        out << "			Item=Scene" << "\n";
        out << "			{" << "\n";
        out << "				Name=Segment_1_scn" << (i+2) << "\n";
        out << "				Scene Time=" << celltimes[i] << "\n";
        out << "				Uop=00000000" << "\n";
        out << "			}" << "\n";
    }

    out << "		}" << "\n";
    out << "	}" << "\n";
    out << "}" << "\n";

    out << "Section=Navigation" << "\n";
    out << "{" << "\n";
    out << "	Item=First PGC" << "\n";
    out << "	{" << "\n";
    out << "		Name=FP" << "\n";
    out << "		Menu ID=No Menu" << "\n";
    out << "		Uop=00000000" << "\n";
    out << "		PG Playback Mode=Sequential Playback" << "\n";
    out << "		Repeat Times=0" << "\n";
    out << "		PGC Still Time=0" << "\n";
    out << "		Palette=DefaultPalette" << "\n";
    out << "		Item=Pre Commands" << "\n";
    out << "		{" << "\n";
    out << "				JumpTT VTS01_TTL01" << "\n";
    out << "		}" << "\n";
    out << "		Item=Post Commands" << "\n";
    out << "		{" << "\n";
    out << "		}" << "\n";
    out << "		Item=Cell Commands" << "\n";
    out << "		{" << "\n";
    out << "		}" << "\n";
    out << "		Item=Program List" << "\n";
    out << "		{" << "\n";
    out << "		}" << "\n";
    out << "	}" << "\n";

    out << "	Item=VMG" << "\n";
    out << "	{" << "\n";
    out << "		Item=Language" << "\n";
    out << "		{" << "\n";
    out << "			Name=Unspecified_0" << "\n";
    out << "			Language=unspecified" << "\n";
    out << "			Item=PGC" << "\n";
    out << "			{" << "\n";
    out << "				Name=Unspecified_title" << "\n";
    out << "				Menu ID=Title Menu" << "\n";
    out << "				Uop=00000000" << "\n";
    out << "				Next PGC=" << "\n";
    out << "				GoUp PGC=" << "\n";
    out << "				PG Playback Mode=Sequential Playback" << "\n";
    out << "				Repeat Times=0" << "\n";
    out << "				PGC Still Time=0" << "\n";
    out << "				Palette=DefaultPalette" << "\n";
    out << "				Item=Pre Commands" << "\n";
    out << "				{" << "\n";
    out << "						JumpTT VTS01_TTL01" << "\n";
    out << "				}" << "\n";
    out << "				Item=Post Commands" << "\n";
    out << "				{" << "\n";
    out << "				}" << "\n";
    out << "				Item=Cell Commands" << "\n";
    out << "				{" << "\n";
    out << "				}" << "\n";
    out << "				Item=Program List" << "\n";
    out << "				{" << "\n";
    out << "				}" << "\n";
    out << "			}" << "\n";
    out << "		}" << "\n";
    out << "	}" << "\n";
    out << "	Item=VTS01" << "\n";
    out << "	{" << "\n";
    out << "		Category=Not Specified" << "\n";
    out << "		Item=Language" << "\n";
    out << "		{" << "\n";
    out << "			Name=Unspecified_1" << "\n";
    out << "			Language=unspecified" << "\n";
    out << "			Item=PGC" << "\n";
    out << "			{" << "\n";
    out << "				Name=Unspecified_root" << "\n";
    out << "				Menu ID=Root Menu" << "\n";
    out << "				Uop=00000000" << "\n";
    out << "				Next PGC=" << "\n";
    out << "				GoUp PGC=" << "\n";
    out << "				PG Playback Mode=Sequential Playback" << "\n";
    out << "				Repeat Times=0" << "\n";
    out << "				PGC Still Time=0" << "\n";
    out << "				Palette=DefaultPalette" << "\n";
    out << "				Item=Pre Commands" << "\n";
    out << "				{" << "\n";
    out << "						JumpVTS_TT VTS01_TTL01" << "\n";
    out << "				}" << "\n";
    out << "				Item=Post Commands" << "\n";
    out << "				{" << "\n";
    out << "				}" << "\n";
    out << "				Item=Cell Commands" << "\n";
    out << "				{" << "\n";
    out << "				}" << "\n";
    out << "				Item=Program List" << "\n";
    out << "				{" << "\n";
    out << "				}" << "\n";
    out << "			}" << "\n";
    out << "		}" << "\n";
    out << "		Item=Title" << "\n";
    out << "		{" << "\n";
    out << "			Name=VTS01_TTL01" << "\n";
    out << "			Uop=0" << "\n";
    out << "			Item=PGC" << "\n";
    out << "			{" << "\n";
    out << "				Name=VTS01_TTL01_PGC1" << "\n";
    out << "				Menu ID=Title Entry" << "\n";
    out << "				Uop=00000000" << "\n";
    out << "				Next PGC=" << "\n";
    out << "				Prev PGC=" << "\n";
    out << "				GoUp PGC=" << "\n";
    out << "				PG Playback Mode=Sequential Playback" << "\n";
    out << "				Repeat Times=0" << "\n";
    out << "				PGC Still Time=0" << "\n";
    out << "				Palette=DefaultPalette" << "\n";
    out << "				Item=Pre Commands" << "\n";
    out << "				{" << "\n";
    out << "				}" << "\n";
    out << "				Item=Post Commands" << "\n";
    out << "				{" << "\n";
    out << "				}" << "\n";
    out << "				Item=Cell Commands" << "\n";
    out << "				{" << "\n";
    out << "				}" << "\n";
    out << "				Item=Program List" << "\n";
    out << "				{" << "\n";

    for (int i=0;i<=celltimes.count();i++)
    {
        out << "					Item=Program" << "\n";
        out << "					{" << "\n";
        out << "						Name=VTS01_TTL01_pg" << (i+1) << "\n";
        out << "						Item=Cell" << "\n";
        out << "						{" << "\n";
        out << "							Name=VTS01_TTL01_cell" << (i+1) << "\n";
        out << "							Linked Scene=Segment_1_scn" << (i+1) << "\n";
        out << "							Command=" << "\n";
        out << "							Cell Still Time=0" << "\n";
        out << "							VOBU Still Flag=False" << "\n";
        out << "							Access Restriction Flag=Permitted" << "\n";
        out << "							Cell Type=0" << "\n";
        out << "							Seamless Flag=default" << "\n";
        out << "						}" << "\n";
        out << "					}" << "\n";
    }

    out << "				}" << "\n";
    out << "			}" << "\n";
    out << "			Item=Part of Title List" << "\n";
    out << "			{" << "\n";

    for (int i=0; i<=celltimes.count();i++)
    {
        out << "				Item=VTS01_TTL01_pg" << (i+1) <<  "\n";
    }

    out << "			}" << "\n";
    out << "		}" << "\n";
    out << "	}" << "\n";
    out << "}" << "\n";

    file_project.close();
}
