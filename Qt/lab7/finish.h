#ifndef FINISH_H
#define FINISH_H
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
class finish: public QObject,public QGraphicsItem
{
public:
    finish();
    ~finish();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

};

#endif // FINISH_H
