#include "Draw.h"
#include "Surface.h"
#include "Board.h"
#include <unistd.h>

Draw::Draw()
{
    Surf_Display =  NULL;
    Surf_Puzzle = NULL;
    Running = true;
}

bool Draw::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    if ((Surf_Display = SDL_SetVideoMode(400, 400, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
        return false;

    if ((Surf_Puzzle = Surface::OnLoad("./8puzzle.jpg")) == NULL)
        return false;

    return true;
}

void Draw::OnLoop(Board* b)
{
    Surface::OnDraw(Surf_Display, Surf_Puzzle, 0, 0);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int N = b->getBlocks()[i][j];
            if (N != 0)
                Surface::OnDraw(Surf_Display, Surf_Puzzle, START_X + j * TILE , START_Y + i * TILE,
                                START_X + TILE * ((N - 1) % 4),
                                START_Y + TILE * ((N - 1) / 4),
                                TILE, TILE);
            else
                Surface::OnDraw(Surf_Display, Surf_Puzzle, START_X + j * TILE, START_Y + i * TILE,
                                START_X + 3 * TILE, START_Y + 3 * TILE, TILE, TILE);
        }
    }
    SDL_Flip(Surf_Display);
}

void Draw::OnCleanup()
{
    SDL_FreeSurface(Surf_Puzzle);
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}

int Draw::OnExecute(std::forward_list<Board*> list)
{
    if(OnInit() == false)
        return -1;

    SDL_Event Event;
    Board initial = list.front();
    OnLoop(&initial);
    while (Running)
    {
        sleep(2);
        OnLoop(&initial);
        sleep(2);
        for (Board* b : list)
        {
            while(SDL_PollEvent(&Event))
                OnExit(&Event);
            if (!Running) break;
            OnLoop(b);
            sleep(1);
        }
    }
    OnCleanup();

    return 0;
}

void Draw::OnExit(SDL_Event* Event)
{
    if(Event->type == SDL_QUIT)
        Running = false;
}
