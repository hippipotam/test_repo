#include "client2.h"
#include <QDebug>
#include "../common.h"

#include "eyetracker_adaptor.h"

Client2::Client2(QObject *parent) :
    QObject(parent),
    m_cnt(0)
{
//    car = new org::example::Examples::CarInterface2("org.example.CarExample", "/Car2",
//            QDBusConnection::sessionBus(), this);

    qDebug() << this->metaObject()->className() << " CONSTRUCTOR";

    // add our D-Bus interface and connect to D-Bus    
    new KeyboardAdaptor(this);

#ifndef EMPTY_NAMES
    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME))
        fprintf(stderr, "%s\n",
                qPrintable(QDBusConnection::sessionBus().lastError().message()));
    else qDebug() << "Service \"" SERVICE_NAME "\" registered";
#endif

    if (!QDBusConnection::sessionBus().registerObject(OBJECT_PATH_KEY, this))
        qDebug() << "Cannot register object";
    else qDebug() << "Object path \"" OBJECT_PATH_KEY "\" registered";

#ifndef EMPTY_NAMES
    iface = new org::example::keyboard(SERVICE_NAME, OBJECT_PATH_KEY, QDBusConnection::sessionBus(), this); //"org.example.chat",
#else
    iface = new org::example::chat(QString(), QString(), QDBusConnection::sessionBus(), this); //"org.example.chat",
#endif

    if (!iface) qDebug() << "IFACE is NOT valid";

    qDebug() << "Create interface:";
    qDebug() << "   Service:" << iface->service();
    qDebug() << "   Path:" << iface->path();
    qDebug() << "   Interface" << iface->interface();

#ifndef EMPTY_NAMES
    QDBusConnection::sessionBus().connect(SERVICE_NAME, OBJECT_PATH_KEY, "org.example.keyboard", "message1", this, SLOT(messageSlot(QString,QString)));
#else
    QDBusConnection::sessionBus().connect(QString(), QString(), "org.example.chat", "message", this, SLOT(messageSlot(QString,QString)));
#endif
//    connect(iface, SIGNAL(message1(QString,QString)), this, SLOT(messageSlot(QString,QString)));
    connect(iface, SIGNAL(action1(QString,QString)), this, SLOT(actionSlot(QString,QString)));

//    m_name = "Client2name";
//    emit action1(m_name, QLatin1String("Hahaha"));

//    startTimer(2000);
}

void Client2::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    emit message1(m_name, QLatin1String("BalBlaBla"));

//    if (iface->isValid()) {
//        qDebug() << "connected " << m_cnt++;
//    } else {
//        qDebug() << "disconnected " << m_cnt++;
//    }
}

void Client2::turnRight()
{
    qDebug() << this->metaObject()->className() << " turnRight";
}

void Client2::messageSlot(const QString &nickname, const QString &text)
{
    qDebug() << nickname << "message1 slot " << text;
}

void Client2::actionSlot(const QString &nickname, const QString &text)
{
    qDebug() << nickname << "action1 slot " << text;
}

void Client2::exiting()
{
    emit action1(m_name, QLatin1String("leaves the chat"));
}

//void Client2::on_left_clicked()
//{
//    car->turnLeft();
//}
