//
// Created by ld on 2024/3/31.
//
#include "Player.h"
void Player::init(Chess* nchess)
{
    this->chess = nchess;
}
void Player::go(){
    // 等待棋士有效落子
    MOUSEMSG msg{};
    ChessPos pos;
    while (1) {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN && chess->clickPos_To_Coordinate(msg.x, msg.y, &pos)) {
            break;
        }
    }

    // 落子
    chess->chessDown(&pos, CHESS_BLACK);
}
