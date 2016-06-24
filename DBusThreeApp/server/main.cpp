#include <QCoreApplication>
#include "testobject.h"
//#include "eyetracker_adaptor.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString name = "test1";

//    TestObject2 *tobj2 = new TestObject2();
    TestObject *tobj = new TestObject(name); //(NULL, tobj2);
    Q_UNUSED(tobj);


//    new CarInterfaceAdaptor(tobj);
//    new CarInterface2Adaptor(tobj2);

//    QDBusConnection connection = QDBusConnection::sessionBus();
//    connection.registerObject("/Car", tobj);
//    connection.registerObject("/Car2", tobj2);
//    connection.registerService("org.example.CarExample");

    return a.exec();
}
