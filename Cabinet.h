#ifndef CABINET_H
#define CABINET_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>

#include <Card.h>

class Cabinet : public QWidget
{
    Q_OBJECT

public:
    Cabinet(int id, int width=100, int height=100, int iNumberOfLevels=5, QWidget *parent = nullptr);
    ~Cabinet();
    void setLineColor(QColor color);
    void setFillColor(QColor color);
    void setNumberOfLevels(int iVal);
    void addPCB(int id, int levelid, int width, int height);
    void movePCB(int id, int xpos, int ypos);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int cabWidth;
    int cabHeight;
    int id;

    int iNumberOfLevels;

    QColor lineColor;
    QColor fillColor;

    QHash<int, Card*> cardHashTable;
};

#endif // CABINET_H
