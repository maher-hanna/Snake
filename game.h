#pragma once
#include <string>
#include "snake.h"
#include "grid.h"
namespace game {



//timing constants ---
const int framesPerSecond = 60;
const int frameTime = 1000 / framesPerSecond;
//----------------

//constants ------------
const int screenWidth = grid::width * snake::pieceSize;
const int screenHeight = grid::height * snake::pieceSize;
//----------------

void initSdl();
void start();
void setup();
void handleInput();
void logic(bool & moveSnake);
void draw();
void clean();
void pause();
void resume();
void destroy();
void drawPiece(SDL_Point tilePos,SDL_Color color);
void drawTarget();
std::string scoreAsString();
std::string getTitle();
//some utility functions---------
SDL_Point screenCoordinate(SDL_Point tileCordinate);
void initGrid();
SDL_Point createTarget();
SDL_Point createTarget();


// ----------



//variables declaration ------------
extern SDL_Window * window;
extern SDL_Renderer * renderer;
extern SDL_Point target;
extern bool running;
extern bool close;
extern bool paused;
extern int score;
extern Uint32 moveSnakeTimer;
// -------------


}

