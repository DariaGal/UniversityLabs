#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "frog.h"
#include "car.h"
#include "gamescene.h"
#include "finish.h"
#include <QKeyEvent>
class GameScene : public QGraphicsScene
{
     Q_OBJECT
public:
    GameScene();
    GameScene(QObject *parent = 0);
    void restart();
    ~GameScene();
private:
    void draw_back();
    void keyPressEvent(QKeyEvent *event);
    frog *Frog;
    car *Car[2][4];
    car *Car1[2][4];
    car *Car2[2][4];
    int n;
    int m;
    finish *Finish;
    QGraphicsItem *itemCollidesWith(QGraphicsItem *item);
    bool end;
signals:
    void stop(int);
private slots:
    void StartCar();
    void StartCar1();
    void StartCar2();
    void CheckCollides();


};

#endif // GAMESCENE_H
