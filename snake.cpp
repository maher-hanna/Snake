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


void drawPiece(SDL_Point tilePos, SDL_Color color) {
    SDL_SetRenderDrawColor(game::renderer,
                           color.r,color.g,color.b,color.a);
    SDL_Point drawnPiecePos;
    SDL_Rect drawnPieceRect;
    //draw head
    drawnPiecePos = game::screenCoordinate(tilePos);
    drawnPieceRect.x = drawnPiecePos.x;
    drawnPieceRect.y = drawnPiecePos.y;
    drawnPieceRect.h = drawnPieceRect.w = snake::pieceSize -1;
    SDL_RenderFillRect(game::renderer,&drawnPieceRect);
    
}


void drawTale() {
    for(int i = 0 ; i < tale.size();i++) {
        drawPiece(tale[i],SDL_Color{150,150,150,255});
        
    }
}

void drawSnake() {
    //draw head
    drawPiece(position,SDL_Color{250,250,250,255});
    
    drawTale();
}

void grow() {
    tale.push_back({position.x,position.y});
    position.x += direction.x;
    position.y += direction.y;
}

void update() {
    auto size = tale.size();
    
    //update tale
    if(size) {
        for(int i = 0 ; i < tale.size() - 1; i++) {
            tale[i] = tale[i + 1];
        }
        tale.back().x = position.x;
        tale.back().y = position.y;
    }
    
    //update head
    position.x += direction.x;
    position.y += direction.y;
}


}
