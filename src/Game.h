#ifndef __GAME_H__
#define __GAME_H__

#include "SDL2/SDL.h"

struct Vector2 {
    float x;
    float y;
};

class Game {
public:
    Game();
    bool initialize();
    void runLoop();
    void shutdown();

private:
    void processInput();
    void updateGame();
    void generateOutput();

    SDL_Window* window;
    SDL_Renderer* renderer;
    Uint32 ticksCount;
    bool isRunning;

    int paddleDir;
    float paddleSpeed;
    Vector2 paddlePos;
    Vector2 ballPos;
    Vector2 ballVel;
};

#endif
