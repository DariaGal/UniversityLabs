#ifndef PEG_H
#define PEG_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPainter>
class Peg: public QObject,public QGraphicsItem
{
public:
    Peg(int number);
    ~Peg();
    void setPosition(int x,int y);
    int getX();
    int getY();
    int getN();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    int x;
    int y;
    int n;
    Q_OBJECT
signals:
   void onPegClickedSignal(int,int,int);
};

#endif // PEG_H
