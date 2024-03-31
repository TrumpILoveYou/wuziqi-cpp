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
    CHESS_WHITE=-1,//����   chess
    NANCHESS=0,
    CHESS_BLACK=1
}ChessKind;
void putimagePNG(int x, int y, IMAGE* picture);
class Chess{
public:
    Chess(int gradSize,int margin_x,int margin_y,int chessSize);
    void init();//��ʼ������
    bool clickPos_To_Coordinate(int x,int y,ChessPos* pos);
    void chessDown(ChessPos *pos,ChessKind kind);
    int  getGradSize();
    bool checkGameOver();//�����Ϸ�Ƿ����
    ChessKind getChessData(int row,int col);
    ~Chess();
    bool checkPosValid(int row, int col);

    //����ͼ�ο⣬�������̣�����
private:
    IMAGE chessBlackImg;
    IMAGE chessWhiteImg;
    int gradSize;//���̴�С
    int margin_x;//�������߽�
    int margin_y;//���̶����߽�
    int chessSize;//Ҳ�������Ӵ�С

    //�洢��ǰ��֣�0���հף�1�����ӣ�-1������
    //chessMap[3][5]��ʾ���̵�3��5�����
    vector<vector<ChessKind >> chessMap;


    //
    bool flag;//true��ʾ������,false��ʾ��������
    void updateChessMap(ChessPos* pos);
    bool checkWin();
    ChessPos lastPos;//��������ӵ�
};
#endif //UNTITLED_CHESS_H
