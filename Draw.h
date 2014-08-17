#ifndef DRAW_H
#define DRAW_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Board.h"

#define START_X  54
#define START_Y  58
#define TILE  72

class Draw
{
private:
    bool Running;
    SDL_Surface* Surf_Display;
    SDL_Surface* Surf_Puzzle;

public:
    Draw();
    int OnExecute(std::forward_list<Board*>);
    bool OnInit();
    void OnLoop(Board* b);
    void OnExit(SDL_Event* Event);
    void OnCleanup();
};

#endif
