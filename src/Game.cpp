#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game():
    window(nullptr),
    renderer(nullptr),
    ticksCount(0),
    isRunning(true),
    paddleDir(0)
{ }

bool Game::initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Error while initializing SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "Pong!",
        100,
        100,
        1024,
        768,
        0
    );

    if (!window) {
        SDL_Log("Error when creating window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        SDL_Log("Error when creating renderer: %s", SDL_GetError());
        return false;
    }

    paddlePos.x = 10.0f;
    paddlePos.y = 768.0f/2.0f;
    paddleSpeed = 300.0f;
    ballPos.x = 1024.0f/2.0f;
    ballPos.y = 768.0f/2.0f;
    ballVel.x = -200.0f;
    ballVel.y = 235.0f;

    return true;
}

void Game::runLoop() {
    while (isRunning) {
        processInput();
        updateGame();
        generateOutput();
    }
}

void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        isRunning = false; 
    }

    paddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        paddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        paddleDir += 1;
    }
}

void Game::updateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16)) { ; }

    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

    if (deltaTime > 0.05f) {
        deltaTime = 0.0f;
    }

    ticksCount = SDL_GetTicks();

    if (paddleDir != 0) {
        paddlePos.y += paddleDir * paddleSpeed * deltaTime;
        if (paddlePos.y < (paddleH/2.0f + thickness)) {
            paddlePos.y = paddleH/2.0f + thickness;
        }
        else if (paddlePos.y > (768.0f - paddleH/2.0f - thickness)) {
            paddlePos.y = 768.0f - paddleH/2.0f - thickness;
        }
    }

    ballPos.x += ballVel.x * deltaTime;
    ballPos.y += ballVel.y * deltaTime;

    float diff = paddlePos.y - ballPos.y;
    diff = (diff > 0.0f) ? diff : -diff;

    if (
        diff <= paddleH / 2.0f &&
        ballPos.x <= 25.0f && ballPos.x >= 20.0f &&
        ballVel.x < 0.0f
    ) {
        ballVel.x *= -1.0f;
    }
    else if (ballPos.x <= 0.0f) {
        isRunning = false;
    }
    else if (ballPos.x >= (1024.0f - thickness) && ballVel.x > 0.0f) {
        ballVel.x *= -1.0f;
    }

    if (ballPos.y <= thickness && ballVel.y < 0.0f) {
        ballVel.y *= -1;
    }
    else if (ballPos.y >= (768 - thickness) && ballVel.y > 0.0f) {
        ballVel.y *= -1;
    }
}

void Game::generateOutput() {
    SDL_SetRenderDrawColor(
        renderer,
        0,
        0,
        255,
        255
        );

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect wall{
        0,
        0,
        1024,
        thickness
    };
    SDL_RenderFillRect(renderer, &wall);

    wall.y = 768 - thickness;
    SDL_RenderFillRect(renderer, &wall);

    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect(renderer, &wall);

    SDL_Rect paddle{
        static_cast<int>(paddlePos.x),
        static_cast<int>(paddlePos.y - paddleH/2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(renderer, &paddle);

    SDL_Rect ball{
        static_cast<int>(ballPos.x - thickness/2),
        static_cast<int>(ballPos.y - thickness/2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(renderer, &ball);

    SDL_RenderPresent(renderer);
}


void Game::shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

