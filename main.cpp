#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "game.h"
using namespace std;

bool userRespondeReplay();
bool userRespondeExit();


int main(int argc, char *argv[])
{

    game::setup();
    game::start();

    game::moveSnakeTimer = 0;
    bool moveSnake = false;

    do {

        Uint32 gameHandlingTime = 0;
        Uint32 loopStart = SDL_GetTicks();

        game::handleInput();

        game::logic(moveSnake);

        game::draw();


        gameHandlingTime = SDL_GetTicks() - loopStart;
        if(gameHandlingTime < game::frameTime) {
            SDL_Delay(game::frameTime - gameHandlingTime);
        }
        //total time = game handling time + delay
        game::moveSnakeTimer += SDL_GetTicks() - loopStart;
        if(game::moveSnakeTimer >= snake::timeToMove) {
            moveSnake = true;
            game::moveSnakeTimer = 0;
        }

        //ask the user if he want to exit the game when
        //hitting close button on the window
        if(game::close){
            game::pause();

            if(userRespondeExit()){


            } else {
                game::resume();
                game::close = false;
            }
        }

        //ask the user if he want to restart the game when
        //lossing
        if(!game::running){
            if(userRespondeReplay()){
                game::clean();
                game::start();
            }

        }

    }while(game::running && (!game::close));


    game::destroy();

    
    
    return EXIT_SUCCESS;
}




bool userRespondeReplay(){
    std::string title = "Your score is ";
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



bool userRespondeExit(){
    std::string title = "Exit!!";
    std::string message = "Do you want realy to exit the game" ;
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
