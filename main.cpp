#include "Game.h"

int main(int argc, char *argv[])
{
    auto game = new Game();
    game->init("Tetris", 800, 600, false);

    while (game->running())
    {
        game->handleEvent();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}
