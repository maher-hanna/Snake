#include "snake.h"
#include "game.h"
namespace snake {

//variables -------------
SDL_Point position;
SDL_Point direction;
std::vector<SDL_Point> tale;
TurnDirection turn = TurnDirection::Right;
//--------------


//time to move the snake in milliseconds
Uint32 timeToMove;



void drawTale() {
    for(int i = 0 ; i < tale.size();i++) {
        game::drawPiece(tale[i],SDL_Color{150,150,150,255});
        
    }
}

void drawSnake() {
    //draw head
    game::drawPiece(position,SDL_Color{250,250,250,255});
    
    drawTale();
}

void grow() {
    tale.push_back({position.x,position.y});
    grid::setTileState(position,true);
    position.x += direction.x;
    position.y += direction.y;
    grid::removeValidTarget(position);
}

void update() {
    auto size = tale.size();
    
    //update tale
    if(size) {
        //update grid block behind the tale
        grid::setTileState(tale[0],false);
        grid::addValidTarget(tale[0]);
                
        for(int i = 0 ; i < tale.size() - 1; i++) {
            tale[i] = tale[i + 1];
        }
        tale.back().x = position.x;
        tale.back().y = position.y;
        grid::setTileState(tale.back(),true);
        grid::removeValidTarget(tale.back());
        
        
    }
    
    
    //update head
    position.x += direction.x;
    position.y += direction.y;
    
    
}

void turnDirection(TurnDirection dir) {
    switch (dir) {
    case snake::TurnDirection::Down:
        if(!snake::direction.y) { 
            direction.x = 0;
            direction.y = 1;
            
        }        
        break;
    case snake::TurnDirection::Up:
        if(!snake::direction.y) {
            direction.x = 0;
            direction.y = -1;         }
        break;
    case snake::TurnDirection::Right:
        if(!snake::direction.x) {
            direction.x = 1;
            direction.y = 0;        
            
        }
        break;
    case snake::TurnDirection::Left:
        if(!snake::direction.x) {
            direction.x = -1;
            direction.y = 0;        
        }
        break;
        
    }

}

bool checkSelfCollision() {
    if(grid::getTileState(position)) {
        return true;
    } else {
        return false;
    }
    
}
}
