#include <Card.h>
#include <QDebug>

Card::Card(int cardId, int levelId, int width, int height, QWidget *parent):QWidget(parent)
{
    cardWidth =  width;
    cardHeight = height;
    this->cardId = cardId;
    this->levelId = levelId;
    fillColor = QColor(Qt::black);
    lineColor = QColor(Qt::blue);
    resize(cardWidth, cardHeight);
}



void
Card::setLineColor(QColor color)
{
    lineColor = color;
}

void
Card::setFillColor(QColor color)
{
    fillColor=color;
}

int
Card::getLevelId()
{
    return (this->levelId);
}


void
Card::paintEvent(QPaintEvent *)
{
    QPainter rectpainter(this);
    QBrush brush(fillColor,Qt::SolidPattern);

    rectpainter.setBrush(brush);
    QPen pen;

    pen.setColor(lineColor);
    pen.setWidth(2);

    rectpainter.setPen(pen);

    rectpainter.setRenderHint(QPainter::Antialiasing,true);

    QPainterPath rounded_rect;
    int radius = 5;
    rounded_rect.addRoundedRect(QRect(0,0,cardWidth,cardHeight), radius, radius);
    rectpainter.setClipPath(rounded_rect);
    rectpainter.fillPath(rounded_rect,rectpainter.brush());
    rectpainter.drawPath(rounded_rect);
}
