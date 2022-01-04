#define SDL_MAIN_HANDLED
#include <stdio.h>
#include<stdlib.h>
#include"../include/SDL2/SDL.h"
#include"../include/SDL2/SDL_timer.h"
#include "../include/SDL2/SDL_image.h"



int main(void)
{
    FILE *logs = fopen("logs.txt","a");
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        fprintf(logs,"error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Hello, CS50!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       640, 480, 0);
    if (win == NULL)
    {   
        fprintf(logs,"error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (rend == NULL)
    {
      fprintf(logs,"error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
    }

    // load the image into memory using SDL_image library function
    SDL_Surface* surface = IMG_Load("res/r.png");
    if (surface == NULL)
    {
        fprintf(logs,"error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (tex ==  NULL)
    {
        fprintf(logs,"error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // clear the window
    SDL_RenderClear(rend);
    
    // draw the image to the window
    SDL_RenderCopy(rend, tex, NULL, NULL);
    SDL_RenderPresent(rend);

    // wait a few seconds
    SDL_Delay(5000);
    
    // clean up resources before exiting
    fclose(logs);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}