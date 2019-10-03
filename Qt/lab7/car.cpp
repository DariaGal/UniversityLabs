#include "car.h"
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsItem>

car::car(int n, int m, int v): QObject(), QGraphicsItem()
{
    this->n=n;
    this->m=m;
    color=qrand()%5+1;
    timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &car::slotGameTimer);
        timer->start(v);
}
QRectF car::boundingRect() const
{
    return QRectF (0,0,120,60);
}
void car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipRect( option->exposedRect );
    QPixmap pix;
    if(m%2==0)
    switch(color)
        {
            case 1:pix.load("C:\\qt project\\lab7\\Car1.png");break;
            case 2:pix.load("C:\\qt project\\lab7\\Car6.png");break;
            case 3:pix.load("C:\\qt project\\lab7\\Car3.png");break;
            case 4:pix.load("C:\\qt project\\lab7\\Car4.png");break;
            case 5:pix.load("C:\\qt project\\lab7\\Car5.png");break;
        }
    else switch(color)
    {
        case 1:pix.load("C:\\qt project\\lab7\\Car12.png");break;
        case 2:pix.load("C:\\qt project\\lab7\\Car62.png");break;
        case 3:pix.load("C:\\qt project\\lab7\\Car32.png");break;
        case 4:pix.load("C:\\qt project\\lab7\\Car42.png");break;
        case 5:pix.load("C:\\qt project\\lab7\\Car52.png");break;
    }


    painter->setPen(QPen(Qt::NoPen));
    painter->drawPixmap(0,0,120,60,pix);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
void car::slotGameTimer()
{
    if(m%2==0) setPos(mapToParent(-5, 0));
    else setPos(mapToParent(5, 0));

}
car::~car()
{

}
