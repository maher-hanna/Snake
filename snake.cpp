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
    grid::setTile(position,true);
    position.x += direction.x;
    position.y += direction.y;
    grid::removeValidTarget(position);
}

void update() {
    auto size = tale.size();
    
    //update tale
    if(size) {
        //update grid block behind the tale
        grid::setTile(tale[0],false);
                
        for(int i = 0 ; i < tale.size() - 1; i++) {
            tale[i] = tale[i + 1];
        }
        tale.back().x = position.x;
        tale.back().y = position.y;
        grid::setTile(tale.back(),true);
        
        
    }
    
    
    //update head
    position.x += direction.x;
    position.y += direction.y;
    
}

void setDirection(TurnDirection dir) {
    switch (dir) {
    case TurnDirection::Right:
        direction.x = 1;
        direction.y = 0;        
        break;
    case TurnDirection::Down:
        direction.x = 0;
        direction.y = 1;        
        break;
    case TurnDirection::Left:
        direction.x = -1;
        direction.y = 0;        
        break;
    case TurnDirection::Up:
        direction.x = 0;
        direction.y = -1;        
        break;
        
    default:
        break;
    }
}

bool checkSelfCollision() {
    if(grid::stateGrid[position.y][position.x] == 1) {
        return true;
    } else {
        return false;
    }
    
}
}
