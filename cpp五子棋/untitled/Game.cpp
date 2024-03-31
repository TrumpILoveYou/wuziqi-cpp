//
// Created by ld on 2024/3/31.
//
#include "Game.h"
#include "Player.h"
Game::Game(Player *player, AI *ai, Chess *chess) {
    this->player=player;
    this->ai=ai;
    this->chess=chess;
    player->init(chess);
    ai->init(chess);

}
//�Ծֿ�ʼ
void Game::startGame() {
    chess->init();

    while (1){
        //�����������
        player->go();
        if(chess->checkGameOver()){
            chess->init();
            continue;
        }
        ai->go();
        if(chess->checkGameOver()){
            chess->init();
            continue;
        }
    }
}
