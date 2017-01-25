#pragma once

#include <vector>
#include <SDL.h>

namespace grid {
//constants -------
const int width = 32;
const int height = 24;
//------------

//variable declerations -----------
extern std::vector<int> possibleTarget;
//gridState is used for snake self collision detection
extern int stateGrid[grid::height][grid::width];
//-----------------------


int toIndex(const SDL_Point &tile);
SDL_Point toPoint(int index);


void setTile(const SDL_Point &cell, bool filled);
bool getTile(const SDL_Point &cell);

void removeValidTarget(const SDL_Point & tile);
void clear();

}
