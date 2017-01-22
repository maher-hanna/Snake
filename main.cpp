#include <cstdio>
#include <cstdlib>
#include <SDL.h>
#include <vector>

using namespace std;


//Game enums -----------
enum class Direction { Right , Up , Left , Down };
//---------------

//Game structures -----------
struct snakePiece {
    int x;
    int y;
    Direction direction;
};

// -------------



//Game constants -----------
const int pieceSize = 20;
//----------------

//Game variables ------------
SDL_Window * window;
SDL_Renderer * renderer;
vector<snakePiece> snakeBody;
bool finished;


//-----------------




void initSdl() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
        
    }

    window = SDL_CreateWindow("Test",SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,640,480,0);
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

    initSdl();
    //initialize snake with the head
    snakeBody.push_back({0,0,Direction::Right});
    
}

void logic() {

}

void draw() {
    
}

void destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
}

int main(int argc, char *argv[])
{
    setup();
    while(!finished) {
        
        logic();
        draw();
        
    }
    
    destroy();
    
    
    return EXIT_SUCCESS;
}








