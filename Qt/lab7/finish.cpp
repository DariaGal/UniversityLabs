#include "finish.h"
#include <QStyleOptionGraphicsItem>

finish::finish(): QObject(), QGraphicsItem()
{
}

QRectF finish::boundingRect() const
{
    return QRectF (0,0,600,70);
}
void finish::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipRect( option->exposedRect );
    painter->drawRect(0,0,600,70);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
finish::~finish()
{

}
