#include "game.h"

#include <algorithm>
#include <ctime>

namespace game {



//variables definition ------------
SDL_Window * window;
SDL_Renderer * renderer;
SDL_Point target;
bool running;
std::vector<int> emptyTiles;
int stateGrid[numTilesInHeight][numTilesInWidth] = {};

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
    start();    
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
            snake::setDirection(snake::TurnDirection::Down);
            
        }        
        break;
    case snake::TurnDirection::Up:
        if(!snake::direction.y) {
            snake::setDirection(snake::TurnDirection::Up);
        }
        break;
    case snake::TurnDirection::Right:
        if(!snake::direction.x) {
            snake::setDirection(snake::TurnDirection::Right);
            
        }
        break;
    case snake::TurnDirection::Left:
        if(!snake::direction.x) {
            snake::setDirection(snake::TurnDirection::Left);
        }
        break;
        
    }
    
    
    if(snake::eat)
    {
        snake::grow();
        snake::eat = false;
        game::createTarget();
    } else {
        snake::update();
    }
    
    if(snake::checkSelfCollision()) {
        game::running = false;
        
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
    game::drawTarget();
    
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



void start() {
    running = true;
    
    //initialize snake with random head and give it direction
    snake::position.x = 10;
    snake::position.y = 10;
    snake::setDirection(snake::TurnDirection::Right);
    game::initGrid();
    game::target = game::createTarget();
    snake::grow();
    snake::grow();
    
    //set initial snake speed to 1 second
    snake::timeToMove = 100;
    
    
}
void stop() {
    
}

//make every grid block that contains a snake piece eqauls 1 
void initGrid() {
    setGridCell(snake::position,true);
    for(int i = 0 ; i < snake::tale.size(); i++) {
        setGridCell(snake::tale[i],true);
    }
    //add empty cells to emptyTiles    
    bool empty = true;
    for(int y = 0 ; y < numTilesInWidth;y++) {
        for(int x = 0 ; x < numTilesInHeight; x++) {
            
            if(game::getGridCell(SDL_Point{x,y}) == true) {
                game::emptyTiles.push_back(x + y * numTilesInWidth);
            }
            if(empty) {
                game::emptyTiles.push_back(x + y * numTilesInWidth);
                empty = true;
            }
            
        }
        
    }
    
}

SDL_Point createTarget() {
    SDL_Point target;
    int random = rand() % (emptyTiles.size());
    int index = emptyTiles[random];
    target.x = index % numTilesInWidth;
    target.y = index / numTilesInHeight;
    return target;
    
    
}
void setGridCell(const SDL_Point &cell, bool filled) {
    stateGrid[cell.y][cell.x] = int(filled);
    int index = cell.x + cell.y * numTilesInWidth;
    auto i = std::find(emptyTiles.begin(),emptyTiles.end(),index);
    if(i != emptyTiles.end()) {
        emptyTiles.erase(i);
    }
    
}
bool getGridCell(const SDL_Point & cell) {
    return stateGrid[cell.y][cell.x];
    
}
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


void drawTarget() {
    drawPiece(target,SDL_Color{255,105,180});
    
    
}
}
