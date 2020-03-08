#include "Game.h"

#include <random>

Game::Game(Board *board, Pieces *pieces, IO *io, int screenHeight) :
    m_screenHeight(screenHeight),
    m_board(board),
    m_pieces(pieces),
    m_io(io)
{
    initGame();
}

void Game::drawScene()
{
    drawBoard(); // Draw the delimitation lines and blocks stored in the board
    drawPiece(m_posX, m_posY, m_piece, m_rotation);                 // Draw the playing piece
    drawPiece(m_nextPosX, m_nextPosY, m_nextPiece, m_nextRotation); // Draw the next piece
}

void Game::createNewPiece()
{
    // The new piece
    m_piece = m_nextPiece;
    m_rotation = m_nextRotation;
    m_posX = (BOARD_WIDTH / 2) + m_pieces->getXInitialPosition(m_piece, m_rotation);
    m_posY = m_pieces->getYInitialPosition(m_piece, m_rotation);

    // Random next piece
    m_nextPiece = getRand(0, 6);
    m_nextRotation = getRand(0, 3);
}

int Game::getRand(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

void Game::initGame()
{
    // Init random numbers
    srand(static_cast<unsigned int>(time(nullptr)));

    // First piece
    m_piece = getRand(0, 6);
    m_rotation = getRand(0, 3);
    m_posX = (BOARD_WIDTH / 2) + m_pieces->getXInitialPosition(m_piece, m_rotation);
    m_posY = m_pieces->getYInitialPosition(m_piece, m_rotation);

    //  Next piece
    m_nextPiece = getRand(0, 6);
    m_nextRotation = getRand(0, 3);
    m_nextPosX = BOARD_WIDTH + 5;
    m_nextPosY = 5;
}

void Game::drawPiece(int x, int y, int piece, int rotation)
{
    Color color; // Color of the block

    // Obtain the position in pixel in the screen of the block we want to draw
    int pixelsX = m_board->getXPosInPixels(x);
    int pixelsY = m_board->getYPosInPixels(y);

    // Travel the matrix of blocks of the piece and draw the blocks that are filled
    for (int i = 0; i < PIECE_BLOCKS; ++i)
    {
        for (int j = 0; j < PIECE_BLOCKS; ++j)
        {
            // Get the type of the block and draw it with the correct color
            switch (m_pieces->getBlockType(piece, rotation, j, i))
            {
            case 1:
                color = GREEN;
                break; // For each block of the piece except the pivot
            case 2:
                color = BLUE;
                break; // For the pivot
            }

            if (m_pieces->getBlockType(piece, rotation, j, i) != 0)
                m_io->drawRectangle(pixelsX + i * BLOCK_SIZE,
                                    pixelsY + j * BLOCK_SIZE,
                                    (pixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                                    (pixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
                                    color);
        }
    }
}

void Game::drawBoard()
{
    // Calculate the limits of the board in pixels
    int x1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int x2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int y = m_screenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    // Rectangles that delimits the board
    m_io->drawRectangle(x1 - BOARD_LINE_WIDTH, y, x1, m_screenHeight - 1, BLUE);
    m_io->drawRectangle(x2, y, x2 + BOARD_LINE_WIDTH, m_screenHeight - 1, BLUE);

    // Drawing the blocks that are already stored in the board
    x1 += 1;
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            // Check if the block is filled, if so, draw it
            if (!m_board->isFreeBlock(i, j))
                m_io->drawRectangle(x1 + i * BLOCK_SIZE,
                                    y + j * BLOCK_SIZE,
                                    (x1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                                    (y + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
                                    RED);
        }
    }
}
