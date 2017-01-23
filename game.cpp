#include "game.h"

#include <ctime>

namespace game {



//variables definition ------------
SDL_Window * window;
SDL_Renderer * renderer;
bool running;
// -------------


void initSdl() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
        
    }
    
    window = SDL_CreateWindow("Test",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screenWidth,screenHeight,0);
    if(!window)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    renderer = SDL_CreateRenderer(window,-1,0);
    if(!window)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void setup() {
    srand(time(nullptr));
    initSdl();
    
    running = true;
    
    //initialize snake with random head and give it direction
    snake::position = getRandomTile();
    snake::direction.x = 1;
    snake::direction.y = 0;    
    //set initial snake speed to 1 second
    snake::timeToMove = 1000;
    
}

void handleInput () {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_DOWN:
            case SDLK_s:
                if(!snake::direction.y) { 
                    snake::direction.y = 1;                
                    snake::direction.x = 0;                
                    
                }
                break;
            case SDLK_UP:
            case SDLK_w:
                if(!snake::direction.y) {
                    snake::direction.y = -1;
                    snake::direction.x = 0; 
                }
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                if(!snake::direction.x) {
                    snake::direction.x = 1;
                    snake::direction.y = 0;
                    
                }
                break;
            case SDLK_LEFT:
            case SDLK_a:
                if(!snake::direction.x) {
                    snake::direction.x = -1;
                    snake::direction.y = 0;
                }
                break;
            }
            
        }
    }
    
}

void logic() {
    //move the snake body
    snake::position.x += snake::direction.x;
    snake::position.y += snake::direction.y;
    
    //wrap the snake position to other side
    if(snake::position.x < 0){
        snake::position.x = numTilesInWidth - 1;
    }
    if(snake::position.y < 0){
        snake::position.y = numTilesInHeight - 1;
    }
    snake::position.x %= numTilesInWidth;
    snake::position.y %= numTilesInHeight;
    
    
    
}

void draw() {
    //draw black background
    SDL_SetRenderDrawColor(renderer,10,10,10,255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer,250,250,250,255);
    SDL_Point drawnPiecePos;
    SDL_Rect drawnPieceRect;
    //draw head
    drawnPiecePos = screenCoordinate(snake::position);
    drawnPieceRect.x = drawnPiecePos.x;
    drawnPieceRect.y = drawnPiecePos.y;
    drawnPieceRect.h = drawnPieceRect.w = snake::pieceSize -1;
    
//    for(int i = 0 ; i < snakeBody.size(); i++) {
//        drawnPiecePos = screenCoordinates(snakeBody[i].x,snakeBody[i].y);
//        drawnPieceRect.x = drawnPiecePos.x;
//        drawnPieceRect.y = drawnPiecePos.y;
//        drawnPieceRect.h = drawnPieceRect.w = pieceSize -1;
//        SDL_RenderDrawRect(renderer,&drawnPieceRect);
//    }
    SDL_RenderDrawRect(renderer,&drawnPieceRect);
    
    SDL_RenderPresent(renderer);
    
}

void clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
}




SDL_Point screenCoordinate(SDL_Point tileCoordinate) {
    return SDL_Point{tileCoordinate.x * snake::pieceSize,
                tileCoordinate.y * snake::pieceSize};
}


SDL_Point getRandomTile() {
    return SDL_Point{rand() % numTilesInWidth, rand() % numTilesInHeight};
    
}


}
