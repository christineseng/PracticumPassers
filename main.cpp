#include "newGame.h"

int main(){
    SDL_Plotter gameWindow(1000, 1000);
    Game gameObject(gameWindow);
    gameObject.run();
    return 0;
}