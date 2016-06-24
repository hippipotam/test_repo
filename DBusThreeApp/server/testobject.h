#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>
#include "eyetracker_interface.h"

class TestObject : public QObject
{
    Q_OBJECT
public:
    explicit TestObject(QString &name, QObject *parent = 0);
    ~TestObject();

signals:
    void message(const QString &nickname, const QString &text);
    void action(const QString &nickname, const QString &text);
    void message1(const QString &nickname, const QString &text);
    void action1(const QString &nickname, const QString &text);

public slots:
    void turnRight();

private slots:
    void messageSlot(const QString &nickname, const QString &text);
    void actionSlot(const QString &nickname, const QString &text);
    void message1Slot(const QString &nickname, const QString &text);
    void exiting();

protected:
    void timerEvent(QTimerEvent *event);

private:
    QString m_name;
    org::example::chat *iface_chat;
    org::example::keyboard *iface_key;

    void SendSignal();
};

//class TestObject2 : public QObject
//{
//    Q_OBJECT
//public:
//    explicit TestObject2(QObject *parent = 0, TestObject *object = 0);
//    ~TestObject2();

//signals:

//public slots:
//    void turnLeft();

//private:
//    TestObject *obj;
//};

#endif // TESTOBJECT_H
