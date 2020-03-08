#pragma once

#include "Board.h"
#include "Pieces.h"

#include <SDL.h>

#include <ctime>

// Number of milliseconds that the piece remains before going 1 block down
constexpr int WAIT_TIME = 700;

class Game
{
public:
    Game();

    void init(const char *title, int width, int height, bool fullscreen);
    void handleEvent();
    void update();
    void render();
    bool running() { return m_isRunning; }
    void clean();

    void drawRectangle(int x1, int y1, int x2, int y2, SDL_Color color);
    void drawScene();
    void createNewPiece();

    int m_posX, m_posY;      // Position of the piece that is falling down
    int m_piece, m_rotation; // Kind and rotation the piece that is falling down

private:
    int m_nextPosX, m_nextPosY;      // Position of the next piece
    int m_nextPiece, m_nextRotation; // Kind and rotation of the next piece

    Board *m_board;
    Pieces *m_pieces;

    Uint32 m_time;
    bool m_isRunning;

    int getRand(int a, int b);
    void initGame();
    void drawPiece(int x, int y, int piece, int rotation);
    void drawBoard();
    int getWindowHeight();

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    void handleKey(int key);
};
