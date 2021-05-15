#ifndef PROCESSPACKET_H
#define PROCESSPACKET_H

#include <QObject>

class ProcessPacket : public QObject
{
    Q_OBJECT
public:
    explicit ProcessPacket(QObject *parent = nullptr);

public slots:
    void doProcessing(char*, int);
signals:
    void sigHealthData(char*, int);
};

#endif // PROCESSPACKET_H
