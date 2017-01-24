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
void start();
void setup();
void handleInput();
void logic();
void draw();
void stop();
void clean();
void drawPiece(SDL_Point tilePos,SDL_Color color);

void drawTarget();

//some utility functions---------
SDL_Point screenCoordinate(SDL_Point tileCordinate);
void initGrid();
SDL_Point createTarget();
void setGridCell(const SDL_Point &cell, bool filled);
bool getGridCell(const SDL_Point &cell);


// ----------



//variables declaration ------------
extern SDL_Window * window;
extern SDL_Renderer * renderer;
extern SDL_Point target;
extern bool running;
//emptyTiles is used for avoiding putting the target on 
//a tile that is occupied by the snake
extern std::vector<int> emptyTiles;
//gridState is used for snake self collision detection
extern int stateGrid[numTilesInHeight][numTilesInWidth];
// -------------


}

