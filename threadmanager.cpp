#include "threadmanager.h"

ThreadManager::ThreadManager(QObject *parent) : QObject(parent)
{
   myUdpRxr = new UdpRxer();
   myUdpSender = new UdpSender();
   pktProc = new ProcessPacket();


   myUdpRxr->moveToThread(&rxThread);
   myUdpSender->moveToThread(&txThread);
   pktProc->moveToThread(&processThread);


   connect(&rxThread, SIGNAL(finished()), myUdpRxr, SLOT(deleteLater()));
   connect(&txThread, SIGNAL(finished()), myUdpSender, SLOT(deleteLater()));
   connect(&processThread, SIGNAL(finished()), pktProc, SLOT(deleteLater()));

   connect(myUdpRxr, SIGNAL(rxdValidData(char*, int)), pktProc, SLOT(doProcessing(char*, int)));

   rxThread.start();
   txThread.start();
   processThread.start();
}




ThreadManager::~ThreadManager()
{

    rxThread.quit();
    rxThread.wait();

    txThread.quit();
    txThread.wait();

    processThread.quit();
    processThread.wait();
}

UdpSender*
ThreadManager::getUdpSender()
{
    return myUdpSender;
}

ProcessPacket*
ThreadManager::getPacketProcessor()
{
    return pktProc;
}

