#pragma once

#include "Pieces.h"

// ------ Constants -----
constexpr int BOARD_LINE_WIDTH = 6;     // Width of each of the two lines that delimit the board
constexpr int BLOCK_SIZE = 16;          // Width and Height of each block of a piece
constexpr int BOARD_POSITION = 320;     // Center position of the board from the left of the screen
constexpr int BOARD_WIDTH = 10;         // Board width in blocks
constexpr int BOARD_HEIGHT = 20;        // Board height in blocks
constexpr int MIN_VERTICAL_MARGIN = 20; // Minimum vertical margin for the board limit
constexpr int MIN_HORIZONTAL_MARGIN = 20; // Minimum horizontal margin for the board limit
constexpr int PIECE_BLOCKS = 5; // Number of horizontal and vertical blocks of a matrix piece

class Board
{
public:
    Board(Pieces *pieces, int screenHeight);

    int getXPosInPixels(int pos);
    int getYPosInPixels(int pos);
    bool isFreeBlock(int x, int y);
    bool isPossibleMovement(int x, int y, int piece, int rotation);
    void storePiece(int x, int y, int piece, int rotation);
    void deletePossibleLines();
    bool isGameOver();

private:
    static const int POS_FREE;   // free position of the board
    static const int POS_FILLED; // filled position of the board

    int m_board[BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the pieces
    Pieces *m_pieces;
    int m_screenHeight;

    void InitBoard();
    void DeleteLine(int pY);
};
