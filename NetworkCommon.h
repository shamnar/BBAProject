#ifndef NETWORKCOMMON_H
#define NETWORKCOMMON_H
#include <iostream>


const int CAT_SAMPLE = 100;
const int SUBCAT_SAMPLE=1;

typedef struct
{
    int src;
    int dest;
    int category;
    int subitem;

}HeaderInfo;

typedef struct
{
    HeaderInfo header;
    int id;
    int temp;
}SamplePacket;

const int MAX_NW_DATA_SIZE = sizeof(SamplePacket);

#endif // NETWORKCOMMON_H
