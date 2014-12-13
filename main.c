#include <stdlib.h>
#include <SDL/SDL.h>
#include <time.h>

#define MAX 255
#define MIN 1
#define fluct 3
#define ABS(x) (x>0?x:-x)

int pause()
{
    SDL_Event event;
    while(1)
    {
        for(int i = 0; i < 8192; i++);
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                return 0;
            case SDL_KEYDOWN:
                return 1;
        }
        //return 1;
    }
}

int main ( int argc, char** argv )
{
    SDL_Surface *screen = NULL;
    SDL_Rect rect;
    unsigned char mapTable[400][400] = {{0}};
    Uint32 gradient[255];
    int i, j;

    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(400, 400, 32, SDL_HWSURFACE);
    rect.h = 1;
    rect.w = 1;
    /*for(i = 0; i < 8; i++)
        gradient[i] = SDL_MapRGB(screen -> format, 0, 0, 255);
    for(i = 8; i < 24; i++)
        gradient[i] = SDL_MapRGB(screen -> format, 0, 26, 255);
    for(i = 24; i < 32; i++)
        gradient[i] = SDL_MapRGB(screen -> format, 0, 103, 255);
    for(i = 32; i < 64; i++)
        gradient[i] = SDL_MapRGB(screen -> format, 0, 179, 255);
    for(i = 64; i < 120; i++)
        gradient[i] = SDL_MapRGB(screen -> format, 0, 80, 13);
    for(i = 120; i < 180; i++)
        gradient[i] = SDL_MapRGB(screen -> format, 128, 196, 0);
    for(i = 180; i < 210; i++)
        gradient[i] = SDL_MapRGB(screen -> format, 0, 0, 255);
    for(i = 210; i < 255; i++)
        gradient[i] = SDL_MapRGB(screen -> format, 255, 255, 255);*/


    for(i = 0; i < 255; i ++)
        gradient[i] = SDL_MapRGB(screen -> format, i, i, i);
    do
    {
        mapTable[0][0] = 0;//(rand() % (MAX - MIN + 1)) + MIN;
        for(i = 1; i < 400; i++)
        {
            do
            {
                mapTable[0][i] = mapTable[0][i - 1] + rand() % (2 * fluct + 1) - fluct + 2;
            } while(ABS((int)mapTable[0][i] - (int)mapTable[0][i - 1]) > fluct + 2);
            do
            {
                mapTable[i][0] = mapTable[i - 1][0] + rand() % (2 * fluct + 1) - fluct + 2;
            } while(ABS((int)mapTable[i][0] - (int)mapTable[i - 1][0]) > fluct + 2);
        }

        for(i = 1; i < 400; i++)
        {
            for(j = 1; j < 400; j++)
            {
                do{
                    mapTable[i][j] = (mapTable[i - 1][j] + mapTable[i][j - 1] + mapTable[i - 1][j - 1]) / 3 + rand() % (2 * fluct + 1) - fluct + 2;
                } while(ABS((int)mapTable[i][j] - (int)((int)mapTable[i - 1][j] + (int)mapTable[i][j - 1] + (int)mapTable[i - 1][j - 1]) / 3) > fluct + 2);
            }
        }

        for(i = 0; i < 400; i++)
        {
            rect.x = i;
            for(j = 0; j < 400; j++)
            {
                rect.y = j;
                SDL_FillRect(screen, &rect, gradient[mapTable[i][j]]);
                mapTable[i][j] = 0;
            }
        }
        SDL_Flip(screen);
        SDL_SaveBMP(screen, "noise.bmp");
    } while(pause());

    return 0;
}
