#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "gamescene.h"
namespace Ui {
class game;
}

class game : public QMainWindow
{

    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    ~game();

private:
    Ui::game *ui;
    GameScene *scene;

private slots:
    void endGame(int);
};

#endif // GAME_H
