#include "grid.h"

namespace grid {

//variable definitions -------------
std::vector<int> possibleTarget;
int stateGrid[grid::height][grid::width] = {};
//---------------------

void setTile(const SDL_Point &cell, bool filled) {
    stateGrid[cell.y][cell.x] = int(filled);
    
}
bool getTile(const SDL_Point & cell) {
    return bool(stateGrid[cell.y][cell.x]);
    
}

void removeValidTarget(const SDL_Point &tile){
    int index = toIndex(tile);
    auto i = std::find(possibleTarget.begin(),possibleTarget.end(),index);
    if(i != possibleTarget.end()) {
        possibleTarget.erase(i);
    }
    
}
int toIndex(const SDL_Point &tile) {
    return tile.x + tile.y * width;
}
SDL_Point toPoint(int index){
    return SDL_Point{index % width,index / width};
}
void clear(){
    for(int y = 0; y < height;y++) {
        for(int x = 0 ; x < width; x++) {
            setTile({x,y},false);
        }
    }
}

}
