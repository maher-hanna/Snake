#include "snake.h"
#include "game.h"
namespace snake {

//variables -------------
SDL_Point position;
SDL_Point direction;
std::vector<SDL_Point> tale;
bool eat;
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
    game::setGridCell(position,true);
    position.x += direction.x;
    position.y += direction.y;
}

void update() {
    auto size = tale.size();
    
    //update tale
    if(size) {
        //update grid block behind the tale
        game::stateGrid[tale[0].y][tale[0].x] = 0;
        
        for(int i = 0 ; i < tale.size() - 1; i++) {
            tale[i] = tale[i + 1];
        }
        tale.back().x = position.x;
        tale.back().y = position.y;
        game::stateGrid[tale.back().y][tale.back().x] = 1;
        
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
    if(game::stateGrid[position.y][position.x] == 1) {
        return true;
    } else {
        return false;
    }
    
}
}
