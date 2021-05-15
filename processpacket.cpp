#include "processpacket.h"
#include "NetworkCommon.h"
#include <QDebug>

ProcessPacket::ProcessPacket(QObject *parent) : QObject(parent)
{

}

void ProcessPacket::doProcessing(char *data, int len)
{
    HeaderInfo header;
    memcpy(&header, data, sizeof(HeaderInfo));
    qDebug()<<"Cat "<<header.category <<" SubCat " <<header.subitem <<" Came to proccess thread with Len " <<len;
    if (header.category==CAT_SAMPLE && header.subitem==SUBCAT_SAMPLE)
    {
        emit sigHealthData(data, len);
    }
}
