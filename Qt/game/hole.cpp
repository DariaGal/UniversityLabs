#include "hole.h"
#include <QDebug>
Hole::Hole(): QObject(),QGraphicsItem()
{

}
void Hole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap hole("C:\\qt project\\lab7\\h.png");
    painter->setPen(QPen(Qt::NoPen));
    painter->drawPixmap(0,0,50,50,hole);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
QRectF Hole::boundingRect() const
{
    return QRectF (0,0,50,50);
}
void Hole::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"hole x:"<<x<<" y:"<<y;
    emit onHoleClickedSignal(x,y);

}
void Hole::setPosition(int x,int y)
{
    this->x=x;
    this->y=y;
}
int Hole::getX()
{
    return x;
}
int Hole::getY()
{
    return y;
}

Hole::~Hole()
{
}
