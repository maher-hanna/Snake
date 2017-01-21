#include <cstdio>
#include <SDL.h>
#include <vector>

using namespace std;

//Game variables ------------
SDL_Window * window;
SDL_Renderer * renderer;
vector<SDL_Rect> snakeBody;
bool finish;

//-----------------

void setup() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
        
    }

    window = SDL_CreateWindow("Test",SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,640,480,0);
    if(!window)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_ShowWindow(window);
    
}

void logic() {

}

void draw() {
    
}

void destroy() {
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
    
    
    return 0;
}
