#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "game.h"
using namespace std;


int main(int argc, char *argv[])
{
    
    game::setup();
    Uint32 tempFrames = 0; 
    
    while(game::running) {
        Uint32 loopTime = SDL_GetTicks();
        tempFrames++;
        game::handleInput();
        
        //move snake only if time ellapsed equals snake speed
        if(tempFrames * game::frameTime >= snake::timeToMove) {
            tempFrames = 0;
            game::logic();
            
        }
        game::draw();
        
        loopTime = SDL_GetTicks() - loopTime;
        if(loopTime < game::frameTime) {
            SDL_Delay(game::frameTime - loopTime);
        }
        
    }
    
    game::clean();
    
    
    return EXIT_SUCCESS;
}




