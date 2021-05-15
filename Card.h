#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPainterPath>

class Card : public QWidget
{
    Q_OBJECT

public:
    Card(int cardId, int levelId, int width=100, int height=100, QWidget *parent = nullptr);

    void setLineColor(QColor color);
    void setFillColor(QColor color);
    int getLevelId();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int cardWidth;
    int cardHeight;
    int cardId;
    int levelId;

    QColor lineColor;
    QColor fillColor;
};

#endif // CARD_H
