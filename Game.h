#pragma once

#include "Board.h"
#include "IO.h"
#include "Pieces.h"

#include <ctime>

// Number of milliseconds that the piece remains before going 1 block down
constexpr int WAIT_TIME = 700;

class Game
{
public:
    Game(Board *board, Pieces *pieces, IO *io, int screenHeight);

    void drawScene();
    void createNewPiece();

    int m_posX, m_posY;      // Position of the piece that is falling down
    int m_piece, m_rotation; // Kind and rotation the piece that is falling down

private:
    int m_screenHeight;              // Screen height in pixels
    int m_nextPosX, m_nextPosY;      // Position of the next piece
    int m_nextPiece, m_nextRotation; // Kind and rotation of the next piece

    Board *m_board;
    Pieces *m_pieces;
    IO *m_io;

    int getRand(int a, int b);
    void initGame();
    void drawPiece(int x, int y, int piece, int rotation);
    void drawBoard();
};
