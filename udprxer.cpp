#include "udprxer.h"
#include "NetworkCommon.h"
UdpRxer::UdpRxer(QObject *parent) : QObject(parent)
{
    // create a QUDP socket
        socket = new QUdpSocket(this);
        tempbuff = new char(MAX_NW_DATA_SIZE);

        // The most common way to use QUdpSocket class is
        // to bind to an address and port using bind()
        // bool QAbstractSocket::bind(const QHostAddress & address,
        //     quint16 port = 0, BindMode mode = DefaultForPlatform)
        socket->bind(QHostAddress::LocalHost, 1234);

        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

UdpRxer::~UdpRxer()
{
    delete socket;
    delete tempbuff;
}

bool
UdpRxer::doValidation(char *data)
{
    HeaderInfo header;
    memcpy(&header, data, sizeof(HeaderInfo));

    if (header.category==CAT_SAMPLE && header.subitem==SUBCAT_SAMPLE)
    {
        return true;
    }
    else
    {
        return false;
    }
}



void
UdpRxer::readyRead()
{
    // when data comes in
    QByteArray buffer;
    int len;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    len = buffer.size();
    memcpy(tempbuff,buffer.data(),len);
    if (doValidation(tempbuff))
        emit rxdValidData(tempbuff, len);
}

