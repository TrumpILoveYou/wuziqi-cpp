//
// Created by ld on 2024/3/31.
//
#include "Chess.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cmath>

void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
    // 变量初始化
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
    int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
    int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
    int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
    int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
    int dstX = 0;    //在显存里像素的角标

    // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //在显存里像素的角标
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
            int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
                             | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
                             | (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
            }
        }
    }
}
Chess::Chess(int gradSize, int margin_x, int margin_y, int chessSize) {
    this->gradSize=gradSize;
    this->margin_x=margin_x;
    this->margin_y=margin_y;
    this->chessSize=chessSize;
    this->flag=CHESS_BLACK;
    for(int i=0;i<gradSize;i++){
        vector<ChessKind> row;
        for(int j=0;j<gradSize;j++){
            row.push_back(NANCHESS);
        }
        chessMap.push_back(row);
    }

}
void Chess::init() {
    initgraph(718,718,EW_SHOWCONSOLE);

    //显示棋盘
    loadimage(nullptr,R"(..\res\board2.jpg)",718,718,true);

    //加载黑棋和白棋图片
    loadimage(&chessBlackImg,R"(..\res/black.png)", chessSize,chessSize,true);
    loadimage(&chessWhiteImg,R"(..\res/white.png)",chessSize,chessSize,true);

    //清理棋盘
    for(int i=0;i<gradSize;i++){
        for(int j=0;j<gradSize;j++){
            chessMap[i][j]=NANCHESS;
        }
    }

    flag=true;
}//初始化棋盘

//判断点击位置合理性
bool Chess::clickPos_To_Coordinate(int x,int y,ChessPos* pos){
    int col=round(1.0*(x-margin_x)/chessSize);
    int row=round(1.0*(y-margin_y)/chessSize);
    int leftTopPosX=margin_x+chessSize*col;
    int leftTopPosY=margin_y+chessSize*row;
    int offset=(int)((chessSize*0.3)*(chessSize*0.3));
    bool ret= false;
    int distanceSQU;
    for (int i = 0; i <=1; ++i) {
        for (int j = 0; j <=1; ++j) {
            distanceSQU=((x-leftTopPosX-i*chessSize)*(x-leftTopPosX-i*chessSize)+(y-leftTopPosY-j*chessSize)*(y-leftTopPosY-j*chessSize));
            if(distanceSQU<offset){
                pos->col=col+i;
                pos->row=row+j;
                if(chessMap[pos->row][pos->col]==0){
                    ret=true;
                }
                break;
            }
        }

    }
    return ret;
}

//下棋操作
void Chess::chessDown(ChessPos *pos,ChessKind kind){
    if(chessMap[pos->row][pos->col]!=NANCHESS)return;
    int x=margin_x+(chessSize*pos->col)-(int)(0.5*chessSize);
    int y=margin_y+(chessSize*pos->row)-(int)(0.5*chessSize);
    if(kind==CHESS_WHITE){
        putimagePNG(x,y,&chessWhiteImg);
    } else if(kind==CHESS_BLACK){
        putimagePNG(x,y,&chessBlackImg);
    }
    updateChessMap(pos);


}
int  Chess::getGradSize(){
    return gradSize;

}
bool Chess::checkGameOver(){
    if(checkWin()){
        Sleep(1500);
        if(!flag){
            //刚刚是黑棋走完，棋手胜利
            loadimage(nullptr,R"(..\res\胜利.jpg)",600,600,true);
        } else{
            loadimage(nullptr,R"(..\res\失败.jpg)",600,600,true);
        }
        _getch();   //暂停
        return true;
    }


    return false;

}//检查游戏是否结束
ChessKind Chess::getChessData(int row,int col){
    return chessMap[row][col];
}
void Chess::updateChessMap(ChessPos *pos) {
    lastPos=*pos;
    chessMap[pos->row][pos->col]=flag?CHESS_BLACK:CHESS_WHITE;
    flag=!flag;
}
Chess::~Chess() {
    delete &this->chessBlackImg;
    delete &this->chessWhiteImg;
    delete &chessMap;

}
bool Chess::checkWin()
{
    // 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
    // 水平方向
    int row = lastPos.row;
    int col = lastPos.col;

    for (int i = 0; i < 5; i++)
    {
        // 往左5个，往右匹配4个子，20种情况
        if (col - i >= 0 &&
            col - i + 4 < getGradSize() &&
            chessMap[row][col - i] == chessMap[row][col - i + 1] &&
            chessMap[row][col - i] == chessMap[row][col - i + 2] &&
            chessMap[row][col - i] == chessMap[row][col - i + 3] &&
            chessMap[row][col - i] == chessMap[row][col - i + 4])
            return true;
    }

    // 竖直方向(上下延伸4个)
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 &&
            row - i + 4 < getGradSize() &&
            chessMap[row - i][col] == chessMap[row - i + 1][col] &&
            chessMap[row - i][col] == chessMap[row - i + 2][col] &&
            chessMap[row - i][col] == chessMap[row - i + 3][col] &&
            chessMap[row - i][col] == chessMap[row - i + 4][col])
            return true;
    }

    // “/"方向
    for (int i = 0; i < 5; i++)
    {
        if (row + i < getGradSize() &&
            row + i - 4 >= 0 &&
            col - i >= 0 &&
            col - i + 4 < getGradSize() &&
            // 第[row+i]行，第[col-i]的棋子，与右上方连续4个棋子都相同
            chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
            chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
            chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
            chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
            return true;
    }

    // “\“ 方向
    for (int i = 0; i < 5; i++)
    {
        // 第[row+i]行，第[col-i]的棋子，与右下方连续4个棋子都相同
        if (row - i >= 0 &&
            row - i + 4 < getGradSize() &&
            col - i >= 0 &&
            col - i + 4 < getGradSize() &&
            chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
            chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
            chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
            chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
            return true;
    }

    return false;
}

bool Chess::checkPosValid(int row, int col) {
    return row>=0&&row<this->getGradSize()&&col>=0&&col<this->getGradSize();
}





