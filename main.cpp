#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "game.h"
using namespace std;
bool userRespondeReplay();


int main(int argc, char *argv[])
{
    do{
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
    } while (userRespondeReplay());
    
    
    return EXIT_SUCCESS;
}




bool userRespondeReplay(){
    std::string title = "Your score is";
    std::string message = "Do you want to restart the game" ;
    title.append(game::scoreAsString());
    const SDL_MessageBoxButtonData buttons[] = {
            { /* .flags, .buttonid, .text */        0, 0, "no" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
        };
        const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                { 10,   10,   10 },
                /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                {   250, 250,   250 },
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                { 250, 250,   250 },
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                {   10,   10, 10 },
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                { 50,   50, 50 }
            }
        };
        const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, /* .flags */
            NULL, /* .window */
            title.c_str(), /* .title */
            message.c_str(), /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
        };
        int buttonid;
        if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
            SDL_Log("error displaying message box");
            return false;
        }
        if (buttonid == -1) {
            SDL_Log("no selection");
            return false;
        } else {
            switch(buttonid){
            case 0:
                return false;
                break;
            case 1:
                return true;
                break;
            }

        }

}
