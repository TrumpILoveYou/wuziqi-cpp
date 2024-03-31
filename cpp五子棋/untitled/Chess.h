//
// Created by ld on 2024/3/31.
//

#ifndef UNTITLED_CHESS_H
#define UNTITLED_CHESS_H
#include <graphics.h>

#include <vector>
using namespace std;

typedef struct ChessPos{
    int row;
    int col;
    explicit ChessPos(int r=0,int c=0):row(r),col(c){}
}ChessPos;

typedef enum{
    CHESS_WHITE=-1,//白棋   chess
    NANCHESS=0,
    CHESS_BLACK=1
}ChessKind;
void putimagePNG(int x, int y, IMAGE* picture);
class Chess{
public:
    Chess(int gradSize,int margin_x,int margin_y,int chessSize);
    void init();//初始化棋盘
    bool clickPos_To_Coordinate(int x,int y,ChessPos* pos);
    void chessDown(ChessPos *pos,ChessKind kind);
    int  getGradSize();
    bool checkGameOver();//检查游戏是否结束
    ChessKind getChessData(int row,int col);
    ~Chess();
    bool checkPosValid(int row, int col);

    //利用图形库，加载棋盘，棋子
private:
    IMAGE chessBlackImg;
    IMAGE chessWhiteImg;
    int gradSize;//棋盘大小
    int margin_x;//棋盘左侧边界
    int margin_y;//棋盘顶部边界
    int chessSize;//也就是棋子大小

    //存储当前棋局，0：空白，1：黑子，-1：白子
    //chessMap[3][5]表示棋盘第3行5列情况
    vector<vector<ChessKind >> chessMap;


    //
    bool flag;//true表示黑子走,false表示白棋先走
    void updateChessMap(ChessPos* pos);
    bool checkWin();
    ChessPos lastPos;//最近的落子点
};
#endif //UNTITLED_CHESS_H
