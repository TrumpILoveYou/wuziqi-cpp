//
// Created by ld on 2024/3/31.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H
#include "Player.h"
#include "AI.h"
#include "Chess.h"
#include <graphics.h>

class Game{
public:
    Game( Player *player,AI *ai,Chess *chess);
    void startGame();//¿ªÊ¼ÓÎÏ·
private:
    Player *player;
    AI *ai;
    Chess *chess;
};

#endif //UNTITLED_GAME_H
