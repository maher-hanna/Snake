#pragma once
#include "snake.h"

namespace game {

//timing constants ---
const int framesPerSecond = 60;
const int frameTime = 1000 / framesPerSecond;
//----------------

//constants ------------
const int numTilesInWidth = 32;
const int numTilesInHeight = 24;
const int screenWidth = numTilesInWidth * snake::pieceSize;
const int screenHeight = numTilesInHeight * snake::pieceSize;
//----------------

void initSdl();
void setup();
void handleInput();
void logic();
void draw();
void clean();


//some utility functions---------
SDL_Point screenCoordinate(SDL_Point tileCordinate);
SDL_Point getRandomTile();
// ----------



//variables declaration ------------
extern SDL_Window * window;
extern SDL_Renderer * renderer;
extern bool running;
// -------------


}

