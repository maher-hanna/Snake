#pragma once
#include <SDL.h>
#include <vector>

namespace snake {


//enums --------
enum class TurnDirection { Right, Up, Left, Down};
enum class Shape { Square , Circle };
//---------

//variables declaration-------------

//position represents the snake head
extern SDL_Point position;

extern SDL_Point direction;
extern std::vector<SDL_Point> tale;
extern TurnDirection turn;

//--------------

//constants -----------
const int pieceSize = 20;
// --------------


//time to move the snake in milliseconds
extern Uint32 timeToMove;

//functions --------
void turnDirection(TurnDirection dir);
void drawTale();
void drawSnake();
void grow();
void update();
void wrap();
bool checkSelfCollision();
bool eatTarget();
//---------

}

