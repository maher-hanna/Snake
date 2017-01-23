#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "game.h"
using namespace std;


int main(int argc, char *argv[])
{
    
    game::setup();
    
    Uint32 totalTime = 0;
    bool moveSnake = false;
    
    while(game::running) {
        Uint32 gameHandlingTime = 0;
        Uint32 loopStart = SDL_GetTicks();
        
        game::handleInput();
        
        if(moveSnake) {
            game::logic();
            moveSnake = false;
           
        }
          
        game::draw();
        
        gameHandlingTime = SDL_GetTicks() - loopStart;
        if(gameHandlingTime < game::frameTime) {
            SDL_Delay(game::frameTime - gameHandlingTime);
        }
        //total time = game handling time + delay
        totalTime += SDL_GetTicks() - loopStart;
        if(totalTime >= snake::timeToMove) {
            moveSnake = true;
            totalTime = 0;
        }
        
    }
    
    game::clean();
    
    
    return EXIT_SUCCESS;
}




