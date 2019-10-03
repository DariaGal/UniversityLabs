#include "game.h"
#include "ui_game.h"
#include "gamescene.h"
#include <QDebug>
#include <QMessageBox>
game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    scene = new GameScene(this);
    scene->setSceneRect(0, 0, 600, 560);
    ui->graphicsView->setScene(scene);
    connect(scene, SIGNAL(stop(int)),this, SLOT(endGame(int)));
}

void game::endGame(int f)
{
    QMessageBox::StandardButton reply;
    if(f) reply = QMessageBox::question(this, "Вы проиграли", "Заново?",
                                   QMessageBox::Yes|QMessageBox::No);
    else reply = QMessageBox::question(this, "Вы выиграли", "Заново?",
                                       QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {
       scene->restart();

     } else {
       close();
     }

}
game::~game()
{
    delete ui;
}
