#include <QCoreApplication>
#include <QFile>
#include "client1.h"
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client1 cli;

//    QFile in;
//    in.open(stdin, QIODevice::ReadWrite);
//    while (true) {
//        std::cout << "please enter string: ";
//        QString line = in.readLine();
//        qDebug() << line;
//        if (line.trimmed() == "click") {
//            qDebug() << "click";
//            cli.on_right_clicked();
//        } else if (line.trimmed() == "quit") {
//            qDebug() << "enter quit";
//            break;
//        }
//    }
//    in.close();

    return a.exec();
}
