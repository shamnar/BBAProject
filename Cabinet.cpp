#include <Cabinet.h>
#include <QDebug>

Cabinet::Cabinet(int id, int width, int height, int iNumberOfLevels, QWidget *parent):QWidget(parent)
{
    this->id = id;
    cabWidth =  width;
    cabHeight = height;
    if (iNumberOfLevels >0)
        this->iNumberOfLevels = iNumberOfLevels;
    else
        this->iNumberOfLevels=1;
    fillColor = QColor(Qt::black);
    lineColor = QColor(Qt::blue);
    resize(cabWidth, cabHeight);

}

Cabinet::~Cabinet()
{
    QHashIterator<int, Card*> i(cardHashTable);
    while (i.hasNext())
    {
        i.next();
        Card* temp = i.value();
        if (temp!=NULL)
            delete (temp);
    }
}

void
Cabinet::setLineColor(QColor color)
{
    lineColor = color;
}

void
Cabinet::setFillColor(QColor color)
{
    fillColor=color;
}

void
Cabinet::setNumberOfLevels(int iVal)
{
    if (iVal>0)
        iNumberOfLevels=iVal;
    else
        iNumberOfLevels=1;

}

void
Cabinet::addPCB(int id, int levelid, int width, int height)
{
    Card* myCard;
    QColor lightyellow = QColor(255, 255, 150, 127);
    myCard = new Card(id, levelid, width,height,this);
    myCard->setFillColor(lightyellow);
    cardHashTable[id]=myCard;
}

void
Cabinet::movePCB(int id, int xpos, int ypos)
{
    int yoffset =  (int)(cabHeight / (iNumberOfLevels));
    Card* myCard = cardHashTable[id];
    yoffset = (myCard->getLevelId()-1)*yoffset;
    myCard->move(xpos, ypos + yoffset);
}


void
Cabinet::paintEvent(QPaintEvent *)
{
    int iOffset;
    int ypos =0;
    QPainter rectpainter(this);
    QBrush brush(fillColor,Qt::SolidPattern);

    rectpainter.setBrush(brush);
    QPen pen;

    pen.setColor(lineColor);
    pen.setWidth(2);

    rectpainter.setPen(pen);
    rectpainter.drawRect(QRect(0,0,cabWidth,cabHeight));

    iOffset = (int)(cabHeight / (iNumberOfLevels));

    for (int i=0;i<iNumberOfLevels-1; i++)
    {
        ypos = ypos + iOffset;
        rectpainter.drawLine(QLine(0,ypos,cabWidth,ypos));
    }
}
