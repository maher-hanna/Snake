#include "game.h"
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
namespace game {



//variables definition ------------
SDL_Window * window;
SDL_Renderer * renderer;
SDL_Point target;
bool running;
bool close;
bool paused;
int score;
Uint32 moveSnakeTimer;

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
    SDL_SetWindowTitle(window,"Snake");
    
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
    srand(unsigned(time(nullptr)));
    initSdl();
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"About",
                             "This game is programmed by \n"
                             "          Maher Hanna     \n"
                             "from Syria,Hama,Maharda\n"
                             "maher.hn802@gmail.com",window);
}

void handleInput () {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            close = true;
            
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
            case SDLK_a:
                
                snake::turn = snake::TurnDirection::Left;
                break;
            case SDLK_SPACE:
                if(game::paused){
                    game::resume();
                } else {
                    game::pause();
                }
                
                break;
                
            }
            
            
        }
    }
    
}

void logic(bool &moveSnake) {
    static bool needsToGrow = false;
    if(paused){
        return;
    }
    if(moveSnake){
        snake::turnDirection(snake::turn);
        
        
        if(needsToGrow){
            snake::grow();
            score++;
            
            SDL_SetWindowTitle(window,getTitle().c_str());
            scoreAsString();
            snake::speedup();
            
            needsToGrow = false;
        }else {
            snake::update();
            
        }
        if(snake::eatTarget()) {
            //check if player has won the game
            if(snake::tale.size() == (grid::width * grid::height) - 2){
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Congratulation",
                                         "You Win the game",window);
                running = false;
                destroy();
                std::exit(EXIT_SUCCESS);
            }
            
            
            needsToGrow = true;
            target = game::createTarget();
        }
        
        
        if(snake::checkSelfCollision()) {
            game::running = false;
            
        }
        
        
        moveSnake = false;
        
    }
    
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
    snake::tale.clear();
    grid::possibleTarget.clear();
    grid::clear();
    game::running = true;
    game::close = false;
    
    
    
}



void destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void pause(){
    paused = true;
    SDL_SetWindowTitle(window,"Paused");
    
}

void resume(){
    paused = false;
    game::moveSnakeTimer = 0;
    SDL_SetWindowTitle(window,getTitle().c_str());
}

SDL_Point screenCoordinate(SDL_Point tileCoordinate) {
    return SDL_Point{tileCoordinate.x * snake::pieceSize,
                tileCoordinate.y * snake::pieceSize};
}



void start() {
    running = true;
    close = false;
    paused = false;
    score = 0;
    //initialize snake with random head and give it direction
    snake::position.x = 10;
    snake::position.y = 10;
    snake::turnDirection(snake::TurnDirection::Right);
    game::initGrid();
    
    snake::grow();
    snake::grow();
    game::target = game::createTarget();
    
    
    
    //set initial snake speed to 1 second
    snake::timeToMove = 600;
    
    
}


//make every grid block that contains a snake piece eqauls 1 
void initGrid() {
    //add all cells to emptyTiles
    for(int y = 0 ; y < grid::height; y++) {
        for(int x = 0 ; x < grid::width;x++) {
            grid::possibleTarget.push_back(grid::toIndex({x,y}));
        }
        
    }
    
    //remove head from emptyTiles
    grid::removeValidTarget(snake::position);
    
    
    
}

SDL_Point createTarget() {
    SDL_Point target;
    int random = rand() % (grid::possibleTarget.size());
    int index = grid::possibleTarget[random];
    target = grid::toPoint(index);
    return target;
    
    
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

std::string scoreAsString(){
    std::string scoreToString;
    std::stringstream oss;
    oss << score;
    scoreToString = oss.str();
    return scoreToString;
    
}

std::string getTitle()
{
    std::string title = "Score ";
    title += scoreAsString();
    return title;
}


}
