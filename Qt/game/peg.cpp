#include "peg.h"
#include <QCursor>
#include <QApplication>
#include <QDebug>
Peg::Peg(int number): QObject(),QGraphicsItem()
{
    n=number;
}
void Peg::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    QPixmap peg("C:\\qt project\\lab7\\p2.png");
    painter->setPen(QPen(Qt::NoPen));
    painter->drawPixmap(0,0,35,35,peg);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
QRectF Peg::boundingRect() const
{
    return QRectF (0,0,35,35);
}
void Peg::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"peg x:"<<x<<" y:"<<y;
    emit onPegClickedSignal(x,y,n);

}
void Peg::setPosition(int x,int y)
{
    this->x=x;
    this->y=y;
}
int Peg::getX()
{
    return x;
}
int Peg::getY()
{
    return y;
}
int Peg::getN()
{
    return n;
}
Peg::~Peg()
{
}
