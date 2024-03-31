//
// Created by ld on 2024/3/31.
//
#include "Chess.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cmath>

void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
    // ������ʼ��
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
    int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
    int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
    int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
    int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
    int dstX = 0;    //���Դ������صĽǱ�

    // ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
            int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
                             | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
                             | (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
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

    //��ʾ����
    loadimage(nullptr,R"(..\res\board2.jpg)",718,718,true);

    //���غ���Ͱ���ͼƬ
    loadimage(&chessBlackImg,R"(..\res/black.png)", chessSize,chessSize,true);
    loadimage(&chessWhiteImg,R"(..\res/white.png)",chessSize,chessSize,true);

    //��������
    for(int i=0;i<gradSize;i++){
        for(int j=0;j<gradSize;j++){
            chessMap[i][j]=NANCHESS;
        }
    }

    flag=true;
}//��ʼ������

//�жϵ��λ�ú�����
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

//�������
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
            //�ո��Ǻ������꣬����ʤ��
            loadimage(nullptr,R"(..\res\ʤ��.jpg)",600,600,true);
        } else{
            loadimage(nullptr,R"(..\res\ʧ��.jpg)",600,600,true);
        }
        _getch();   //��ͣ
        return true;
    }


    return false;

}//�����Ϸ�Ƿ����
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
    // ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
    // ˮƽ����
    int row = lastPos.row;
    int col = lastPos.col;

    for (int i = 0; i < 5; i++)
    {
        // ����5��������ƥ��4���ӣ�20�����
        if (col - i >= 0 &&
            col - i + 4 < getGradSize() &&
            chessMap[row][col - i] == chessMap[row][col - i + 1] &&
            chessMap[row][col - i] == chessMap[row][col - i + 2] &&
            chessMap[row][col - i] == chessMap[row][col - i + 3] &&
            chessMap[row][col - i] == chessMap[row][col - i + 4])
            return true;
    }

    // ��ֱ����(��������4��)
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

    // ��/"����
    for (int i = 0; i < 5; i++)
    {
        if (row + i < getGradSize() &&
            row + i - 4 >= 0 &&
            col - i >= 0 &&
            col - i + 4 < getGradSize() &&
            // ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
            chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
            chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
            chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
            chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
            return true;
    }

    // ��\�� ����
    for (int i = 0; i < 5; i++)
    {
        // ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
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





