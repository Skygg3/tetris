#include "Board.h"

#include <algorithm>

const int Board::POS_FREE = 0;
const int Board::POS_FILLED = 1;

Board::Board(Pieces *pieces, int screenHeight) : m_pieces(pieces), m_screenHeight(screenHeight)
{
    initBoard();
}

int Board::getXPosInPixels(int pos)
{
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pos * BLOCK_SIZE));
}

int Board::getYPosInPixels(int pos)
{
    return ((m_screenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pos * BLOCK_SIZE));
}

bool Board::isFreeBlock(int x, int y)
{
    return m_board[x][y] == POS_FREE;
}

bool Board::isPossibleMovement(int x, int y, int piece, int rotation)
{
    // Checks collision with pieces already stored in the board or the board limits
    // This is just to check the 5x5 blocks of a piece with the appropriate area in the board
    for (int i1 = x, i2 = 0; i1 < x + PIECE_BLOCKS; i1++, i2++)
    {
        for (int j1 = y, j2 = 0; j1 < y + PIECE_BLOCKS; j1++, j2++)
        {
            // Check if the piece is outside the limits of the board
            if (i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1)
            {
                if (m_pieces->getBlockType(piece, rotation, j2, i2) != 0)
                    return false;
            }

            // Check if the piece have collisioned with a block already stored in the map
            if (j1 >= 0)
            {
                if ((m_pieces->getBlockType(piece, rotation, j2, i2) != 0) &&
                    (!isFreeBlock(i1, j1)))
                    return false;
            }
        }
    }

    // No collision
    return true;
}

void Board::storePiece(int x, int y, int piece, int rotation)
{
    // Store each block of the piece into the board
    for (int i1 = x, i2 = 0; i1 < x + PIECE_BLOCKS; ++i1, ++i2)
    {
        for (int j1 = y, j2 = 0; j1 < y + PIECE_BLOCKS; ++j1, ++j2)
        {
            // Store only the blocks of the piece that are not holes
            if (m_pieces->getBlockType(piece, rotation, j2, i2) != 0)
                m_board[i1][j1] = POS_FILLED;
        }
    }
}

void Board::deletePossibleLines()
{
    for (int j = 0; j < BOARD_HEIGHT; ++j)
    {
        // Check if the line is completely filled with blocks
        bool lineIsFilled = true;
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            if (m_board[i][j] == POS_FREE)
            {
                lineIsFilled = false;
                break;
            }
        }

        if (lineIsFilled)
            deleteLine(j);
    }
}

bool Board::isGameOver()
{
    // If the first line has blocks, then, game over
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        if (m_board[i][0] == POS_FILLED)
            return true;
    }

    return false;
}

void Board::initBoard()
{
    std::fill_n(&m_board[0][0], BOARD_WIDTH * BOARD_HEIGHT, POS_FREE);
}

void Board::deleteLine(int y)
{
    // Moves all the upper lines one row down
    for (int j = y; j > 0; --j)
    {
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            m_board[i][j] = m_board[i][j - 1];
        }
    }
}
