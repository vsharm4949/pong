#include <iostream>

#include "Game.h"

int main() {
    Game game;
    bool success = game.initialize();
    if (success) {
        game.runLoop();
    }
    game.shutdown();

    return 0;
}

