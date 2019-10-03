#ifndef GAME_H
#define GAME_H
#include "peg.h"
#include "hole.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>
namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

private:
    Ui::Game *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *Holes[33];
    Peg *peg[33];
    Hole *hole[7][7];
    int checkX;
    int checkY;
    int checkN;
    int stepNumber;
    QLabel *step;
    QGraphicsProxyWidget *label;
    void draw_back();
    void MovePeg(int x, int y,int delX,int delY);
    bool checkFail();
    bool checkWin();
private slots:
    void CheckPeg(int x,int y,int n);
    void ChangeField(int x,int y);
};

#endif // GAME_H
