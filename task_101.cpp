#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 750
int wid = SCREEN_WIDTH /2;
int wider = SCREEN_WIDTH/2;
int pink = 150;

bool initializeSDL(SDL_Window** frontend, SDL_Renderer** renderer)
{
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
   {
       printf("ERROR INITIALIZING SDL!");

       return false;
   }

   *frontend = SDL_CreateWindow("Sumu's window ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

   if (*frontend == NULL)
   {
       printf("ERROR INITIALIZING SDL!");

       return false;
   }

   *renderer = SDL_CreateRenderer(*frontend, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

   if (*renderer == NULL)
   {
       printf("ERROR INITIALIZING RENDERER!");

       return false;
   }

   return true;
}

void TheMiddleCircle(SDL_Renderer* renderer, int focusX, int focusY, int r)
{
   for (int x = -r; x <= r; x++)
   {
       for (int y = -r; y <= r; y++)
       {
           if (x*x + y*y <= r*r)
           {
               SDL_RenderDrawPoint(renderer, focusX + x, focusY + y);
           }
       }
   }
}

int main(int argc, char* argv[])
{
   SDL_Window* frontend = NULL;
   SDL_Renderer* renderer = NULL;

   if (!initializeSDL(&frontend, &renderer))
   {
       return 1;
   }

   SDL_Event event;

   bool running = true;

   while (running)
   {
       while (SDL_PollEvent(&event))
       {
           if (event.type == SDL_QUIT)
           {
               running = false;
           }
       }

       SDL_SetRenderDrawColor(renderer, 210, 140, 140, 255);
       SDL_RenderClear(renderer);

           
       SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
       TheMiddleCircle(renderer, wid, wider, pink);

       SDL_RenderPresent(renderer);
   }
  
   return 0;
}



