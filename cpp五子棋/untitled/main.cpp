
#include "Chess.h"
#include "Player.h"
#include "AI.h"
#include "Game.h"
int main() {

    Chess chess(13,36,36,54);
    Player player{};

    AI ai;
    Game game(&player,&ai,&chess);
    game.startGame();
    return 0;
}