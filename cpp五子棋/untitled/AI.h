//
// Created by ld on 2024/3/31.
//

#ifndef UNTITLED_AI_H
#define UNTITLED_AI_H
#include "Chess.h"
#include <ctime>
class AI
{
public:
    void init(Chess *chess);
    void go();

private:
    Chess* chess;
    vector<vector<int>> scoreMap;
    int caculateScore();
    int soloPosScore(int row,int col);
    ChessPos think();
};
#endif //UNTITLED_AI_H
