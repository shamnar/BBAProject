#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <QThread>

#include "udprxer.h"
#include "udpsender.h"
#include "processpacket.h"

class ThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit ThreadManager(QObject *parent = nullptr);
    ~ThreadManager();
    UdpSender* getUdpSender();
    ProcessPacket* getPacketProcessor();

signals:

private:
    QThread txThread;
    QThread rxThread;
    QThread processThread;

    UdpSender* myUdpSender;
    UdpRxer* myUdpRxr;
    ProcessPacket *pktProc;






};

#endif // THREADMANAGER_H
