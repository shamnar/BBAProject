#ifndef UDPRXER_H
#define UDPRXER_H

#include <QObject>
#include <QUdpSocket>
#include "NetworkCommon.h"

class UdpRxer : public QObject
{
    Q_OBJECT
public:
    explicit UdpRxer(QObject *parent = nullptr);
    ~UdpRxer();
    bool doValidation(char*);

signals:
    void rxdValidData(char*, int);

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
    char* tempbuff;

};

#endif // UDPRXER_H
