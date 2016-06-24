#include "client1.h"
#include <QDebug>
#include "eyetracker_adaptor.h"
#include "eyetracker_interface.h"

//#include <QTextStream>
#include <unistd.h>
#include "../common.h"


Client1::Client1(QObject *parent) :
    QObject(parent),
    m_cnt(0),
    iface(NULL)
{
//    car = new org::example::Examples::CarInterface2("org.example.CarExample", "/Car2",
//            QDBusConnection::sessionBus(), this);

    qDebug() << this->metaObject()->className() << " CONSTRUCTOR";

    // add our D-Bus interface and connect to D-Bus
    new ChatAdaptor(this);

#ifndef EMPTY_NAMES
    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME))
        qDebug() << "Service already registered";
    else qDebug() << "Service \"" SERVICE_NAME "\" registered";
#endif

    if (!QDBusConnection::sessionBus().registerObject(OBJECT_PATH_EYE, this))
        qDebug() << "Cannot register object";
    else qDebug() << "Object path \"" OBJECT_PATH_EYE "\" registered";

#ifndef EMPTY_NAMES
    iface = new org::example::chat(SERVICE_NAME, OBJECT_PATH_EYE, QDBusConnection::sessionBus(), this); //"org.example.chat",
#else
    iface = new org::example::chat(QString(), QString(), QDBusConnection::sessionBus(), this); //"org.example.chat",
#endif

    if (!iface) qDebug() << "IFACE is NOT valid";

    qDebug() << "Create interface:";
    qDebug() << "   Service:" << iface->service();
    qDebug() << "   Path:" << iface->path();
    qDebug() << "   Interface" << iface->interface();

#ifndef EMPTY_NAMES
//    QDBusConnection::sessionBus().connect(SERVICE_NAME, OBJECT_PATH, "org.example.chat", "message", this, SLOT(messageSlot(QString,QString)));
#else
    QDBusConnection::sessionBus().connect(QString(), QString(), "org.example.chat", "message", this, SLOT(messageSlot(QString,QString)));
#endif
    connect(iface, SIGNAL(action(QString,QString)), this, SLOT(actionSlot(QString,QString)));

    m_name = "Client1";
    emit action(m_name, QLatin1String("Yeah!"));

    qDebug() << "Start timer";

    startTimer(1000);
}

void Client1::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QPoint xy(10,10);
    qDebug() << "Hi";

//    emit message(m_name, QLatin1String("HelloThere"));

    emit message(m_name, QString("Position [ %1, %2 ]").arg(xy.x()).arg(xy.y()));

//    if (iface->isValid()) {
//        qDebug() << "connected " << m_cnt++;
//    } else {
//        qDebug() << "disconnected " << m_cnt++;
//    }
}

void Client1::turnRight()
{
    qDebug() << this->metaObject()->className() << " turnRight";
}

void Client1::messageSlot(const QString &nickname, const QString &text)
{
    qDebug() << nickname << "message slot";
}

void Client1::actionSlot(const QString &nickname, const QString &text)
{
    qDebug() << nickname << "action slot " << text;
}

void Client1::exiting()
{
    emit action(m_name, QLatin1String("leaves the chat"));
}

//client1::client1(QObject *parent) :
//    QObject(parent),
//    m_cnt(0),
//    notifier(STDIN_FILENO, QSocketNotifier::Read)
//{
////    car = new org::example::Examples::CarInterface("org.example.CarExample", "/Car",
////                                                   QDBusConnection::sessionBus(), this);

////    in = new QFile;
////    in->open(stdin, QIODevice::ReadOnly);
////    connect(&notifier, SIGNAL(activated(int)), this, SLOT(onReadD(int)));

////    connect(in, SIGNAL(bytesWritten(qint64)), this, SLOT(onReadD(qint64)));

////    startTimer(2000);
//}

//void client1::timerEvent(QTimerEvent *event)
//{
//    Q_UNUSED(event);

////    if (car->isValid()) {
////        qDebug() << "connected " << m_cnt++;
////    } else {
////        qDebug() << "disconnected " << m_cnt++;
////    }
//}

//void client1::on_right_clicked()
//{
////    car->turnRight();
//}

void Client1::onReadD(int bytes)
{
    QTextStream qin(stdin);
    QString line = qin.readLine();
    qDebug() << line;
    if (line.trimmed() == "turn") {
//        on_right_clicked();
    }
}
