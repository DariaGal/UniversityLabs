#ifndef CAR_H
#define CAR_H
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QTimer>
class car: public QObject,public QGraphicsItem
{
public:
     car(int n,int m,int v);
    ~car();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QTimer *timer;
    int m;
    int n;
    int color;
    Q_OBJECT
signals:
     void destroyCar(int,int);

private slots:
    void slotGameTimer();

};

#endif // CAR_H
