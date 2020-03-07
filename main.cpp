#include <iostream>

#include <SDL.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *fenetre = SDL_CreateWindow(
      "Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Delay(3000);

    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}
