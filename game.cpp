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
    snake::turn = snake::TurnDirection::Right;
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
                snake::turn = snake::TurnDirection::Down;
                break;
            case SDLK_UP:
            case SDLK_w:
                snake::turn = snake::TurnDirection::Up;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                snake::turn = snake::TurnDirection::Right;
                break;
            case SDLK_LEFT:
                snake::turn = snake::TurnDirection::Left;
                
            case SDLK_a:
                break;
            case SDLK_SPACE:
                snake::eat = true;
                break;
            }
            
            
        }
    }
    
}

void logic() {
    switch (snake::turn) {
    case snake::TurnDirection::Down:
        if(!snake::direction.y) { 
            snake::direction.y = 1;                
            snake::direction.x = 0;                
            
        }        
        break;
    case snake::TurnDirection::Up:
        if(!snake::direction.y) {
            snake::direction.y = -1;
            snake::direction.x = 0; 
        }
        break;
    case snake::TurnDirection::Right:
        if(!snake::direction.x) {
            snake::direction.x = 1;
            snake::direction.y = 0;
            
        }
        break;
    case snake::TurnDirection::Left:
        if(!snake::direction.x) {
            snake::direction.x = -1;
            snake::direction.y = 0;
        }
        break;
        
    }
    
    
    if(snake::eat)
    {
        snake::grow();
        snake::eat = false;
    } else {
        snake::update();
    }
    
    
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
    
    
    snake::drawSnake();
    
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
