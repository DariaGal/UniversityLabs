#include "gamescene.h"
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QApplication>
GameScene::GameScene(QObject *parent) : QGraphicsScene(parent)
{
    draw_back();
    Finish=new finish();
    Finish->setPos(0,0);
    Finish->setData(0,"Finish");
    addItem(Finish);
    Frog = new frog();
    Frog->setPos(270,495);
    Frog->setData(0,"Frog");
    addItem(Frog);
    end=false;
    n=0;
    m=0;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(StartCar()));
    timer->start(900);

    QTimer *timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(StartCar1()));
    timer1->start(1000);

    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(StartCar2()));
    timer2->start(1200);

    QTimer *timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(CheckCollides()));
    timer3->start(100);
}

void GameScene::draw_back()
{
    QPixmap grass("C:\\qt project\\lab7\\grass.jpg");
    QPixmap road("C:\\qt project\\lab7\\road.jpg");
    addPixmap(grass.scaled(600,560,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    QGraphicsPixmapItem *r[3];
    for(int i=0;i<3;i++)
    {
        r[i]=new QGraphicsPixmapItem(road.scaled(600,140,Qt::IgnoreAspectRatio,Qt::FastTransformation));
        r[i]->setPos(0,i*140+70);
        addItem(r[i]);
    }
}
void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(!end)
    {
    QPointF move;
    switch(event->key())
    {
        case Qt::Key_Up:{
             move.setY(-70);
             Frog->setImg(1);
             break;}
        case Qt::Key_Down:{
            move.setY(70);
            Frog->setImg(2);
            break;}
        case Qt::Key_Left:{
             move.setX(-35);
             Frog->setImg(3);
             break;}
        case Qt::Key_Right:{
             move.setX(35);
             Frog->setImg(4);
             break;}
    }

    QTransform t = Frog->transform();
     t.translate(move.x(),move.y());
    Frog->setTransform(t);
    }

}
void GameScene::StartCar()
{

    Car[n][m] = new car(n,m,20);
    Car[n][m]->setData(0,"Car");
    if(m%2==0) Car[n][m]->setPos(600,425);
    else Car[n][m]->setPos(-120,355);
    Car[n][m]->setZValue(10);
    addItem(Car[n][m]);
    m++;
    if(n==0 && m==4){m=0;n=1;}
    if(n==1 && m==4){n=0;m=0;}
}
void GameScene::StartCar1()
{

    Car[n][m] = new car(n,m,15);
    Car[n][m]->setData(0,"Car");
    if(m%2==0) Car[n][m]->setPos(600,215);
    else Car[n][m]->setPos(-120,285);
    Car[n][m]->setZValue(10);
    addItem(Car[n][m]);
    m++;
    if(n==0 && m==4){m=0;n=1;}
    if(n==1 && m==4){n=0;m=0;}
}
void GameScene::StartCar2()
{

    Car[n][m] = new car(n,m,30);
    Car[n][m]->setData(0,"Car");
    if(m%2==0) Car[n][m]->setPos(600,145);
    else Car[n][m]->setPos(-120,75);
    Car[n][m]->setZValue(10);
    addItem(Car[n][m]);
    m++;
    if(n==0 && m==4){m=0;n=1;}
    if(n==1 && m==4){n=0;m=0;}
}


void GameScene::restart()
{
    removeItem(Frog);
    delete Frog;
    Frog = new frog();
    Frog->setPos(270,495);
    addItem(Frog);
    end=false;
}

QGraphicsItem *GameScene::itemCollidesWith(QGraphicsItem * item)
{
    QList<QGraphicsItem*> collisions = collidingItems(item);
    foreach(QGraphicsItem * it,collisions){
        if(it == item)
            continue;
        return it;
    }
    return NULL;
}
void GameScene::CheckCollides()
{
    QGraphicsItem *obstacle = itemCollidesWith(Frog);
    if(obstacle)
    {
        if(obstacle->data(0)=="Car") {end=true; emit stop(1);}
        if(obstacle->data(0)=="Finish") {end=true; emit stop(0);}
    }

}

GameScene::~GameScene()
{

}
