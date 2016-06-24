#ifndef CLIENT2_H
#define CLIENT2_H

#include <QObject>
#include "eyetracker_interface.h"

class Client2 : public QObject
{
    Q_OBJECT
public:
    explicit Client2(QObject *parent = 0);

signals:
    Q_SCRIPTABLE void message1(const QString &nickname, const QString &text);
    Q_SCRIPTABLE void action1(const QString &nickname, const QString &text);

public slots:
    void turnRight();

private slots:
    void messageSlot(const QString &nickname, const QString &text);
    void actionSlot(const QString &nickname, const QString &text);
    void exiting();

protected:
    void timerEvent(QTimerEvent *event);

private:
    QString m_name;
    int m_cnt;
    org::example::keyboard *iface;
//    org::example::chat *iface;
};

//class Client2 : public QObject
//{
//    Q_OBJECT
//public:
//    explicit Client2(QObject *parent = 0);
//    void on_left_clicked();

//protected:
//    void timerEvent(QTimerEvent *event);

////private slots:
////    void onReadD(int bytes);

//private:
//    org::example::Examples::CarInterface2 *car;
//    int m_cnt;
////    QFile *in;
////    QSocketNotifier notifier;
//};

//class Client2 : public QObject
//{
//    Q_OBJECT
//public:
//    explicit Client2(QObject *parent = 0);
//    ~Client2();

//signals:

//public slots:
//};

#endif // CLIENT2_H
