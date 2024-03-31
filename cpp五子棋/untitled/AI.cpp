//
// Created by ld on 2024/3/31.
//
#include <ctime>
#include "AI.h"
#include "Consts.h"
using namespace defend_middle;
//初始版AI判断8个方向的价值综合
void AI::init(Chess *a_chess) {
    this->chess=a_chess;
    for (int i = 0; i < chess->getGradSize(); ++i) {
        vector<int> row;
        for (int j = 0; j < chess->getGradSize(); ++j) {
            row.push_back(0);
        }
        scoreMap.push_back(row);
    }
}
void AI::go() {
    ChessPos newPos=think();
    Sleep(1000);
    chess->chessDown(&newPos,CHESS_WHITE);

}

int AI::caculateScore() {
    int size=scoreMap.size();
    for (int i = 0; i <size ; ++i) {
        for (int j = 0; j < size; ++j) {
            scoreMap[i][j]=0;
        }
    }
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if(chess->getChessData(row,col)==NANCHESS){
                scoreMap[row][col]=soloPosScore(row,col);

            }
        }
    }
    return 0;
}

int AI::soloPosScore(int row, int col) {
    int soloTotalScore=0;
    int size=chess->getGradSize();

    //各方在某个方向棋子数目
    int playerNum=0;
    int aiNum=0;
    int emptyNum=0;//方向空白位个数

    for (int y = -1; y <=0 ; ++y) {
        for (int x = -1; x <=1; ++x) {
            if(y==0&&x==0)continue;
            if(y==0&&x!=1)continue;
            playerNum=0;
            aiNum=0;
            emptyNum=0;//方向空白位个数

            //黑棋计算
            for (int dex = 1; dex <= 4; ++dex) {
                int curRow=row+dex*y;
                int curCol=col+dex*x;
                if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==1){
                    playerNum++;
                }else if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==0){
                    emptyNum++;
                    break;
                }else if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==-1){
                    aiNum++;
                    break;
                }else{
                    break;
                }
            }
            for (int dex = 1; dex <= 4; ++dex) {
                int curRow=row-dex*y;
                int curCol=col-dex*x;
                if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==1){
                    playerNum++;
                }else if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==0){
                    emptyNum++;
                    break;
                }else if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==-1){
                    aiNum++;
                    break;
                }else{
                    break;
                }
            }
            if(playerNum==1){//连2
                soloTotalScore+=dfpara1;
            } else if(playerNum==2){
                if(emptyNum==1)soloTotalScore+=dfpara2;
                if(emptyNum==2)soloTotalScore+=dfpara3;
            }else if(playerNum==3){
                if(emptyNum==1)soloTotalScore+=dfpara4;
                if(emptyNum==2)soloTotalScore+=dfpara5;
            }else if(playerNum==4){
                soloTotalScore+=dfpara6;
            }

            //白棋计算
            emptyNum=0;
            playerNum=0;
            aiNum=0;
            //黑棋计算
            for (int dex = 1; dex <= 4; ++dex) {
                int curRow=row+dex*y;
                int curCol=col+dex*x;
                if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==-1){
                    aiNum++;
                }else if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==0){
                    emptyNum++;
                    break;
                }else if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==-1){
                    playerNum++;
                    break;
                }else{
                    break;
                }
            }
            for (int dex = 1; dex <= 4; ++dex) {
                int curRow=row-dex*y;
                int curCol=col-dex*x;
                if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==-1){
                    aiNum++;
                }else if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==0){
                    emptyNum++;
                    break;
                }else if(chess->checkPosValid(curRow,curCol)&&chess->getChessData(curRow,curCol)==1){
                    playerNum++;
                    break;
                }else{
                    break;
                }
            }
            if(aiNum==0)soloTotalScore+=5;
            if(aiNum==1){//连2
                soloTotalScore+=10;
            } else if(aiNum==2){
                if(emptyNum==1)soloTotalScore+=25;
                if(emptyNum==2)soloTotalScore+=50;
            }else if(aiNum==3){
                if(emptyNum==1)soloTotalScore+=55;
                if(emptyNum==2)soloTotalScore+=10000;
            }else if(aiNum==4){
                soloTotalScore+=30000;
            }

        }
    }
    return soloTotalScore;
}

ChessPos AI::think() {
    caculateScore();
    int size=chess->getGradSize();
    int max=-1;
    vector<ChessPos> maxPoint;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(!chess->getChessData(i,j)){
                if(scoreMap[i][j]>max){
                    maxPoint.clear();
                    max=scoreMap[i][j];
                    ChessPos newPos;
                    newPos.col=j;
                    newPos.row=i;
                    maxPoint.push_back(newPos);
                } else if(scoreMap[i][j]==max){
                    ChessPos newPos;
                    newPos.col=j;
                    newPos.row=i;
                    maxPoint.push_back(newPos);
                }
            }
        }
    }
    srand((unsigned) time(NULL));

    int index=rand()%maxPoint.size();
    return maxPoint[index];
}
