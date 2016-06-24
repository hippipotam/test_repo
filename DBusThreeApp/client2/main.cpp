#include <QCoreApplication>
#include "client2.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client2 cli;

    return a.exec();
}
