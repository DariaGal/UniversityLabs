#include "game.h"
#include "ui_game.h"
#include <QDebug>
#include <QMessageBox>
int nP;
int field[7][7]={{9,9,1,1,1,9,9},
                 {9,9,1,1,1,9,9},
                 {1,1,1,1,1,1,1},
                 {1,1,1,0,1,1,1},
                 {1,1,1,1,1,1,1},
                 {9,9,1,1,1,9,9},
                 {9,9,1,1,1,9,9}};
               /* {{9,9,0,0,0,9,9},
                 {9,9,0,0,0,9,9},
                 {0,0,0,0,0,0,0},
                 {0,1,1,0,0,0,0},
                 {0,0,0,0,0,0,0},
                 {9,9,0,0,0,9,9},
                 {9,9,0,0,0,9,9}};*/

Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 500, 500);
    ui->graphicsView->setScene(scene);
    draw_back();
    stepNumber=0;
    step = new QLabel("Ход: 0");
    step->setGeometry(5, 5, 90, 50);
    step->setStyleSheet("background-color:transparent;font: bold 15pt Constantia; color: #093a94");
    label = scene->addWidget(step);
}

void Game::draw_back()
{
    QPixmap back("C:\\qt project\\lab7\\i.jpg");
    QPixmap table("C:\\qt project\\lab7\\t.jpg");
    scene->addPixmap(back.scaled(500,500,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    QGraphicsPixmapItem *c[7][7];
    int t=0;
    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++)
        {

            if(field[i][j]==1||field[i][j]==0)
            {
                c[i][j]=new QGraphicsPixmapItem(table.scaled(70,70,Qt::IgnoreAspectRatio,Qt::FastTransformation));
                c[i][j]->setPos(i*70+4,j*70+4);
                scene->addItem(c[i][j]);
                hole[i][j] = new Hole();
                hole[i][j]->setPosition(i,j);
                hole[i][j]->setPos(i*70+14,j*70+14);
                scene->addItem(hole[i][j]);
                connect(hole[i][j], SIGNAL(onHoleClickedSignal(int,int)),this, SLOT(ChangeField(int,int)));
                if(field[i][j]==1)
                {
                    peg[t] = new Peg(t);
                    peg[t]->setPosition(i,j);
                    peg[t]->setPos(i*70+21,j*70+21);
                    scene->addItem(peg[t]);
                    connect(peg[t], SIGNAL(onPegClickedSignal(int,int,int)),this, SLOT(CheckPeg(int,int,int)));

                    t++;

                }
            }

        }
    nP=t;
}
void Game::CheckPeg(int x,int y,int n)
{
    checkX=x;
    checkY=y;
    checkN=n;
    qDebug()<<"connect peg  x="<<x<<"  y="<<y<<"\n";

}
void Game::ChangeField(int x,int y)
{
    int delX,delY;
    qDebug()<<"newX="<<x<<" newY="<<y;
    qDebug()<<"checkX="<<checkX<<" checkY="<<checkY;

    if(field[x][y]==0)
    {
        if(checkX==x)
        {
            if(checkY-y==-2)
            {
                if(field[x][y-1]==1)
                {
                    field[checkX][checkY]=0;
                    field[x][y]=1;
                    field[x][y-1]=0;
                    delX=x; delY=y-1;
                    MovePeg(x,y,delX,delY);
                }
            }
            if(checkY-y==2)
            {
                if(field[x][y+1]==1)
                {
                   field[checkX][checkY]=0;
                   field[x][y]=1;
                   field[x][y+1]=0;
                   delX=x; delY=y+1;
                   MovePeg(x,y,delX,delY);
                }
            }
        }
        else if(checkY==y)
        {
            if(checkX-x==-2)
            {
                if(field[x-1][y]==1)
                {
                    field[checkX][checkY]=0;
                    field[x][y]=1;
                    field[x-1][y]=0;
                    delX=x-1; delY=y;
                    MovePeg(x,y,delX,delY);
                }
            }
            if(checkX-x==2)
            {
                if(field[x+1][y]==1)
                {
                 field[checkX][checkY]=0;
                 field[x][y]=1;
                 field[x+1][y]=0;
                 delX=x+1; delY=y;
                 MovePeg(x,y,delX,delY);
                }
            }
        }
    }
    qDebug()<<"connect hole  x="<<x<<"  y="<<y<<"\n";
}
void Game::MovePeg(int x, int y,int delX, int delY)
{
    qDebug()<<"Move";
    stepNumber++;
    QString str;
    QTextStream (&str)<<stepNumber;
    step->setText("Ход: ");
    step->setText(step->text()+str);
    peg[checkN]->setPosition(x,y);
    peg[checkN]->setPos(x*70+21,y*70+21);
    peg[checkN]->setZValue(100);
    for(int i=0;i<nP;i++)
    {

        if(peg[i]->getX()==delX && peg[i]->getY()==delY)
        {
            scene->removeItem(peg[i]);
        }

    }
    bool f=checkFail();
    bool w=checkWin();
    if(w)
    {
        QMessageBox::information(0,"Конец игры","Вы выиграли");
        close();
    }else
    if(f)
    {
        QMessageBox::information(0,"Конец игры","Вы проиграли");
        close();
    }
    qDebug()<<"fail="<<f;

}
bool Game::checkFail()
{
    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++)
        {
            if(field[i][j]==1)
            {
                if(i-1>=0 && field[i-1][j]==1)
                {
                    if(i-2>=0 && field[i-2][j]==0)
                    {
                        return false;
                    }
                }
                if(i+1<7 && field[i+1][j]==1)
                {
                    if(i+2<7 && field[i+2][j]==0)
                    {
                       return false;
                    }
                }
                if(j+1<7 && field[i][j+1]==1)
                {
                    if(j+2<7 && field[i][j+2]==0)
                    {
                        return false;
                    }
                }
                if(j-1>=0 && field[i][j-1]==1)
                {
                    if(j-2>=0 && field[i][j-2]==0)
                    {
                        return false;
                    }
                }
            }
        }
    return true;
}
bool Game::checkWin()
{
    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++)
        {
            if(field[i][j]==1)
            {
                if(i==3 && j==3)
                {
                    return true;
                }

                else return false;
            }


        }
}

Game::~Game()
{
    delete ui;
}
