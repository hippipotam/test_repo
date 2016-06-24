#ifndef CLIENT1_H
#define CLIENT1_H

#include <QObject>
#include <QSocketNotifier>
#include "eyetracker_interface.h"

class Client1 : public QObject
{
    Q_OBJECT
public:
    explicit Client1(QObject *parent = 0);

signals:
    void message(const QString &nickname, const QString &text);
    void action(const QString &nickname, const QString &text);

public slots:
    void turnRight();

private slots:
    Q_SCRIPTABLE void messageSlot(const QString &nickname, const QString &text);
    Q_SCRIPTABLE void actionSlot(const QString &nickname, const QString &text);
    void onReadD(int bytes);
    void exiting();

protected:
    void timerEvent(QTimerEvent *event);

private:
    QString m_name;
    int m_cnt;
    org::example::chat *iface;
};

//class client1 : public QObject
//{
//    Q_OBJECT
//public:
//    explicit client1(QObject *parent = 0);
//    void on_right_clicked();

//signals:
//    void message(const QString &nickname, const QString &text);
//    void action(const QString &nickname, const QString &text);

//protected:
//    void timerEvent(QTimerEvent *event);

//private slots:
//    void onReadD(int bytes);


//private:
////    org::example::Examples::CarInterface *car;
//    int m_cnt;
////    QFile *in;
//    QSocketNotifier notifier;
//};

#endif // CLIENT1_H
