#ifndef CSTARTSERVER_H
#define CSTARTSERVER_H

#include <QObject>
#include <QDebug>

class CStartServer : public QObject
{
    Q_OBJECT
    public:
        CStartServer(int);
    private:
        int num;
    public slots:
        void run();
    signals:
        void finished();
};


#endif // CSTARTSERVER_H
