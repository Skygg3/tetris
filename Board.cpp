#include "Board.h"

const int Board::POS_FREE = 0;
const int Board::POS_FILLED = 1;

Board::Board(Pieces *pieces, int screenHeight) :
    m_board(),
    m_pieces(pieces),
    m_screenHeight(screenHeight)
{
}

int Board::getXPosInPixels(int pos)
{
    // TODO
    return 0;
}

int Board::getYPosInPixels(int pos)
{
    // TODO
    return 0;
}

bool Board::isFreeBlock(int x, int y)
{
    // TODO
    return true;
}

bool Board::isPossibleMovement(int x, int y, int piece, int rotation)
{
    // TODO
    return true;
}

void Board::storePiece(int x, int y, int piece, int rotation)
{
}

void Board::deletePossibleLines()
{
}

bool Board::isGameOver()
{
    // TODO
    return true;
}
