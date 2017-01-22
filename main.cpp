#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

#include <SDL.h>


using namespace std;


//structures -----------
struct snakePiece {
    int x;
    int y;
    SDL_Point direction;
};

// -------------



//constants -----------
const int head = 0;
const int pieceSize = 20;
const int screenWidth = 640;
const int screenHeight = 640;
const int numTilesInWidth = screenWidth / pieceSize;
const int numTilesInHeight = screenHeight / pieceSize;

//timing constants ---
const int framesPerSecond = 60;
const int frameTime = 1000 / framesPerSecond;
//----------------


//function declerations --------
void initSdl();
void setup();
void handleInput();
void logic();
void draw();
void clean();


//some utility functions---------
SDL_Point screenCoordinates(int tileX, int tileY);
SDL_Point getRandomTile();
// ----------



//variables ------------
SDL_Window * window;
SDL_Renderer * renderer;
vector<snakePiece> snakeBody;
bool running;

//snake speed in milliseconds
Uint32 snakeSpeed;



//-----------------




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
    const SDL_Point randomTile = getRandomTile();
    snakeBody.push_back({randomTile.x,randomTile.y,{-1,0}});
    
    //set initial snake speed to 1 second
    snakeSpeed = 1000;
    
}

void handleInput () {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            
            break;
        default:
            break;
        }
    }
    
}

void logic() {
    for(int i = 0 ; i < snakeBody.size();i++) {
        //move the snake body
        snakeBody[i].x += snakeBody[i].direction.x;
        snakeBody[i].y += snakeBody[i].direction.y;
        
        //wrap the snake position to other side
        if(snakeBody[i].x < 0){
            snakeBody[i].x = numTilesInWidth - 1;
        }
        if(snakeBody[i].y < 0){
            snakeBody[i].y = numTilesInHeight - 1;
        }
        snakeBody[i].x %= numTilesInWidth;
        snakeBody[i].y %= numTilesInHeight;
        
        
    }

}

void draw() {
    //draw black background
    SDL_SetRenderDrawColor(renderer,10,10,10,255);
    SDL_RenderClear(renderer);
    
    //draw snake pieces in white
    SDL_SetRenderDrawColor(renderer,250,250,250,255);
    SDL_Point drawnPiecePos;
    SDL_Rect drawnPieceRect;
    for(int i = 0 ; i < snakeBody.size(); i++) {
        drawnPiecePos = screenCoordinates(snakeBody[i].x,snakeBody[i].y);
        drawnPieceRect.x = drawnPiecePos.x;
        drawnPieceRect.y = drawnPiecePos.y;
        drawnPieceRect.h = drawnPieceRect.w = pieceSize -1;
        SDL_RenderDrawRect(renderer,&drawnPieceRect);
    }
    
    SDL_RenderPresent(renderer);
    
}

void clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
}


SDL_Point screenCoordinates(int tileX, int tileY) {
    return SDL_Point{tileX * pieceSize, tileY * pieceSize};
}


SDL_Point getRandomTile() {
    return SDL_Point{rand() % numTilesInWidth, rand() % numTilesInHeight};
    
}



int main(int argc, char *argv[])
{
    
    setup();
    Uint32 tempFrames = 0; 
    
    while(running) {
        Uint32 loopTime = SDL_GetTicks();
        tempFrames++;
        handleInput();
        
        //move snake only if time ellapsed equals snake speed
        if(tempFrames * frameTime >= snakeSpeed) {
            tempFrames = 0;
            logic();
                       
        }
        draw();
        
        loopTime = SDL_GetTicks() - loopTime;
        if(loopTime < frameTime) {
            SDL_Delay(frameTime - loopTime);
        }
        
    }
    
    clean();
    
    
    return EXIT_SUCCESS;
}








