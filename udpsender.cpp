#include "udpsender.h"

UdpSender::UdpSender(QObject *parent) : QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);
    connect(this, SIGNAL(hasDataToSend(char*, int)), this, SLOT(slotSendData(char*, int)));
}

UdpSender::~UdpSender()
{
    delete socket;
}

void UdpSender::sendData()
{
    QByteArray Data;
    Data.append("Hello from UDP");
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
}

void UdpSender::slotSendData(char *data, int len)
{
    socket->writeDatagram(data, len, QHostAddress::LocalHost, 1234);
    qDebug()<<"Data sent";
}
