#include "frog.h"
#include <QStyleOptionGraphicsItem>
#include <windows.h>
frog::frog() : QObject(), QGraphicsItem()
{
    img=1;
}
QRectF frog::boundingRect() const
{
    return QRectF (0,0,60,60);
}
void frog::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPixmap pix;
    painter->setClipRect( option->exposedRect );
    if(img==1)
    {
        pix.load("C:\\qt project\\lab7\\frogUp.png");
    }
    if(img==2)
    {
        pix.load("C:\\qt project\\lab7\\frogDown.png");
    }
    if(img==3)
    {
        pix.load("C:\\qt project\\lab7\\frogLeft.png");
    }
    if(img==4)
    {
        pix.load("C:\\qt project\\lab7\\frogRight.png");
    }
    painter->setPen(QPen(Qt::NoPen));
    painter->drawPixmap(0,0,60,60,pix);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
void frog::setImg(int n)
{
    img=n;
}
frog::~frog()
{

}
