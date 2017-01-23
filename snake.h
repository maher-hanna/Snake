#pragma once
#include <SDL.h>
#include <vector>

namespace snake {


//enums --------
enum class TurnDirection { Right, Up, Left, Down};
enum class Shape { Square , Circle };
//---------

//variables declaration-------------
extern SDL_Point position;
extern SDL_Point direction;
extern std::vector<SDL_Point> tale;
extern bool eat;
extern TurnDirection turn;

//--------------

//constants -----------
const int pieceSize = 20;
// --------------


//time to move the snake in milliseconds
extern Uint32 timeToMove;

//functions --------
void drawPiece(SDL_Point tilePos,SDL_Color color);
void drawTale();
void drawSnake();
void grow();
void update();
//---------

}

