#ifndef FROG_H
#define FROG_H
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
class frog : public QObject,public QGraphicsItem
{
public:
    frog();
    ~frog();

    void setImg(int n);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    int img;

};

#endif // FROG_H
