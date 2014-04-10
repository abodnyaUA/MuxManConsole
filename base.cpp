#include "base.h"
#include <QDebug>

void printError()
{
    qDebug() << "invalid arguments\n";
    exit(0);
}
