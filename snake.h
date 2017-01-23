#pragma once
#include <SDL.h>
#include <vector>

namespace snake {


//variables declaration-------------
extern SDL_Point position;
extern SDL_Point direction;
extern std::vector<SDL_Rect> snakeTale;
//--------------

//constants -----------
const int pieceSize = 20;
// --------------

//time to move the snake in milliseconds
extern Uint32 timeToMove;



}

