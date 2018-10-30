#include "cstartserver.h"

CStartServer::CStartServer(int i)
{
  num=i;
}

void CStartServer::run() {
    for (int i=0; i< 5000; ++i) {
        qDebug()<<"from "<<num;
    }
    emit finished();
}
