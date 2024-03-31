//
// Created by ld on 2024/3/31.
//

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H
#include "Chess.h"
#include <mmsystem.h>
#include <graphics.h>
#pragma comment(lib, "winmm.lib")
class Player{
public:
    void init(Chess* chess);
    void go();
private:
    Chess* chess;
};
#endif //UNTITLED_PLAYER_H
