#include "testobject.h"
#include <QDebug>
#include "../common.h"

#include "eyetracker_adaptor.h"

TestObject::TestObject(QString &name, QObject *parent) :
    QObject(parent),
    m_name(name.trimmed())
{
    qDebug() << this->metaObject()->className() << " CONSTRUCTOR";

//    QDBusConnection conn = QDBusConnection::sessionBus();

    new ChatAdaptor(this);
    new KeyboardAdaptor(this);

    QDBusConnection connection = QDBusConnection::sessionBus();

#ifndef EMPTY_NAMES
    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME))
        fprintf(stderr, "Cannot register service \"" SERVICE_NAME "\". %s\n",
                qPrintable(QDBusConnection::sessionBus().lastError().message()));    
    else qDebug() << "Service \"" SERVICE_NAME "\" registered";
#endif

    //First obj
    if (!QDBusConnection::sessionBus().registerObject(OBJECT_PATH_EYE, this)) //, QDBusConnection::ExportAllContents)) //
        fprintf(stderr, "%s\n",
                qPrintable(QDBusConnection::sessionBus().lastError().message()));
    else qDebug() << "Object path \"" OBJECT_PATH_EYE "\" registered";

    //Second object
    if (!QDBusConnection::sessionBus().registerObject(OBJECT_PATH_KEY, this)) //, QDBusConnection::ExportAllContents)) //
        fprintf(stderr, "%s\n",
                qPrintable(QDBusConnection::sessionBus().lastError().message()));
    else qDebug() << "Object path \"" OBJECT_PATH_KEY "\" registered";

#ifndef EMPTY_NAMES
    iface_chat = new org::example::chat(SERVICE_NAME, OBJECT_PATH_EYE, QDBusConnection::sessionBus(), this);
    iface_key = new org::example::keyboard(SERVICE_NAME, OBJECT_PATH_KEY, QDBusConnection::sessionBus(), this);
#else
    iface = new org::example::chat(QString(), QString(), QDBusConnection::sessionBus(), this);
#endif
    if (!iface_chat) qDebug() << "IFACE CHAT  is NOT valid";
    if (!iface_key) qDebug() << "IFACE KEY is NOT valid";

    qDebug() << "Create interface eye:";
    qDebug() << "   Service:" << iface_chat->service();
    qDebug() << "   Path:" << iface_chat->path();
    qDebug() << "   Interface" << iface_chat->interface();
    qDebug() << "Create interface key:";
    qDebug() << "   Service:" << iface_key->service();
    qDebug() << "   Path:" << iface_key->path();
    qDebug() << "   Interface" << iface_key->interface();

#ifndef EMPTY_NAMES
    QDBusConnection::sessionBus().connect(SERVICE_NAME, OBJECT_PATH_EYE, "org.example.chat", "message", this, SLOT(messageSlot(QString,QString)));
//    QDBusConnection::sessionBus().connect(SERVICE_NAME, OBJECT_PATH_KEY, "org.example.keyboard", "message1", this, SLOT(message1Slot(QString,QString)));
#else
    QDBusConnection::sessionBus().connect(QString(), QString(), "org.example.chat", "message", this, SLOT(messageSlot(QString,QString)));
#endif
    connect(iface_chat, SIGNAL(action(QString,QString)), this, SLOT(actionSlot(QString,QString)));
//    m_name = "Server1";
//    emit action(m_name, QLatin1String("Hello"));

//    startTimer(1000);
}

TestObject::~TestObject()
{
    qDebug() << this->metaObject()->className() << " DESTRUCTOR";
}

void TestObject::timerEvent(QTimerEvent *event)
{
    QPoint xy(10,10);
    qDebug() << "Hi";

    SendSignal();

//    emit message1(m_name, QLatin1String("HelloThere"));
}

void TestObject::turnRight()
{
    qDebug() << this->metaObject()->className() << " turnRight";
}

void TestObject::messageSlot(const QString &nickname, const QString &text)
{
    qDebug() << nickname << "message slot" << text;
    QString str = nickname;
    str += " ";
    str += m_name;
    SendSignal();
//    emit message1(str, text);
}

void TestObject::message1Slot(const QString &nickname, const QString &text)
{
    qDebug() << nickname << "message1 slot" << text;
}

void TestObject::actionSlot(const QString &nickname, const QString &text)
{
    qDebug() << nickname << "action slot " << text;
}

void TestObject::exiting()
{
    emit action(m_name, QLatin1String("leaves the chat"));
}

void TestObject::SendSignal()
{
    qDebug() << "test1 message1 slot HelloThereFromSendSignal";
    emit message1(m_name, QLatin1String("HelloThereFromSendSignal"));
}

//TestObject2::TestObject2(QObject *parent, TestObject *object) :
//    QObject(parent),
//    obj(object)
//{
//    qDebug() << this->metaObject()->className() << " CONSTRUCTOR";
//}

//TestObject2::~TestObject2()
//{
//    qDebug() << this->metaObject()->className() << " DESTRUCTOR";
//}

//void TestObject2::turnLeft()
//{
//    qDebug() << this->metaObject()->className() << " turnLeft";

//}

