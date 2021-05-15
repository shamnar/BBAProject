#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>

class UdpSender : public QObject
{
    Q_OBJECT
public:
    explicit UdpSender(QObject *parent = nullptr);
    ~UdpSender();

    void sendData();

public slots:
    void slotSendData(char* data, int len);

signals:
    void hasDataToSend(char*, int);

private:
    QUdpSocket *socket;

};

#endif // UDPSENDER_H
