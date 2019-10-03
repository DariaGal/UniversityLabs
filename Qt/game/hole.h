#ifndef HOLE_H
#define HOLE_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPainter>
class Hole : public QObject,public QGraphicsItem
{
public:
    Hole();
    ~Hole();
    void setPosition(int x,int y);
    int getX();
    int getY();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    int x;
    int y;
    Q_OBJECT
signals:
   void onHoleClickedSignal(int,int);
};

#endif // HOLE_H
