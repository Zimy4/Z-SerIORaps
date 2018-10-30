#include <QCoreApplication>
#include <QThread>
#include "rpi3server.h"
#include "cstartserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QThread thread1;
    CStartServer serv(1);

    QObject::connect(&thread1,SIGNAL(started()),&serv,SLOT(run()));
    QObject::connect(&serv,SIGNAL(finished()),&thread1,SLOT(terminate()));

    serv.moveToThread(&thread1);

    thread1.start();
    while(  getchar() != 'n' )
    {

    }
    thread1.terminate();
    qDebug() << "Terminate";
/*    CRpi3Server serv;
    serv.doStartServer(QHostAddress::Any, 8080);

    while(  getchar() != 'n' )
    {

    }
    serv.doStopServer();
*/
//    MyThread th;

//    th.run();

    return a.exec();
}
