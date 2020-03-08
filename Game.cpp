#include "Game.h"

#include <iostream>
#include <random>

Game::Game() :
    m_posX(-1),
    m_posY(-1),
    m_piece(-1),
    m_rotation(-1),
    m_nextPosX(-1),
    m_nextPosY(-1),
    m_nextPiece(-1),
    m_nextRotation(-1),
    m_board(nullptr),
    m_pieces(nullptr),
    m_isRunning(false),
    m_window(nullptr),
    m_renderer(nullptr)
{
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{
    // Initialiase SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }
    std::cout << "Subsystems Initialiased!\n";

    // Create window
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    m_window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (m_window == nullptr)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }
    std::cout << "Window created!\n";

    // Create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == nullptr)
    {
        std::cout << "Failed to create renderer\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }
    std::cout << "Renderer created!\n";

    initGame();

    m_time = SDL_GetTicks();
    m_isRunning = true;
}

void Game::handleEvent()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_KEYDOWN:
        return handleKey(event.key.keysym.sym);
    case SDL_QUIT:
        m_isRunning = false;
    default:
        break;
    }
}

void Game::handleKey(int key)
{
    switch (key)
    {
    case (SDLK_RIGHT):
    {
        if (m_board->isPossibleMovement(m_posX + 1, m_posY, m_piece, m_rotation))
            m_posX++;
        break;
    }

    case (SDLK_LEFT):
    {
        if (m_board->isPossibleMovement(m_posX - 1, m_posY, m_piece, m_rotation))
            m_posX--;
        break;
    }

    case (SDLK_DOWN):
    {
        if (m_board->isPossibleMovement(m_posX, m_posY + 1, m_piece, m_rotation))
            m_posY++;
        break;
    }

    case (SDLK_x):
    {
        // Check collision from up to down
        while (m_board->isPossibleMovement(m_posX, m_posY, m_piece, m_rotation))
        {
            m_posY++;
        }

        m_board->storePiece(m_posX, m_posY - 1, m_piece, m_rotation);
        m_board->deletePossibleLines();

        if (m_board->isGameOver())
        {
            std::cout << "Game Over!\n";
            m_isRunning = false;
        }

        createNewPiece();

        break;
    }

    case (SDLK_z):
    {
        if (m_board->isPossibleMovement(m_posX, m_posY, m_piece, (m_rotation + 1) % 4))
            m_rotation = (m_rotation + 1) % 4;

        break;
    }
    }
}

void Game::drawRectangle(int x1, int y1, int x2, int y2, SDL_Color color)
{
    SDL_Rect rect = {x1, y1, x2 - x1, y2 - y1};
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_renderer, &rect);
}

void Game::update()
{
    auto currentTime = SDL_GetTicks();
    if (currentTime - m_time > WAIT_TIME)
    {
        if (m_board->isPossibleMovement(m_posX, m_posY + 1, m_piece, m_rotation))
        {
            m_posY++;
        }
        else
        {
            m_board->storePiece(m_posX, m_posY, m_piece, m_rotation);

            m_board->deletePossibleLines();

            if (m_board->isGameOver())
            {
                std::cout << "Game Over!\n";
                m_isRunning = false;
            }

            createNewPiece();
        }

        m_time = SDL_GetTicks();
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
    SDL_RenderClear(m_renderer);
    drawScene();
    SDL_RenderPresent(m_renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!\n";
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
    m_pieces = new Pieces();
    m_board = new Board(m_pieces, getWindowHeight());

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
    SDL_Color color; // Color of the block

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
            case 1: // GREEN
                color = {0, 255, 0, 255};
                break; // For each block of the piece except the pivot
            case 2:
                color = {0, 0, 255, 255}; // BLUE
                break;                    // For the pivot
            }

            if (m_pieces->getBlockType(piece, rotation, j, i) != 0)
                drawRectangle(pixelsX + i * BLOCK_SIZE,
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
    int y = getWindowHeight() - (BLOCK_SIZE * BOARD_HEIGHT);

    // Rectangles that delimits the board
    SDL_Color blue = {0, 0, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    drawRectangle(x1 - BOARD_LINE_WIDTH, y, x1, getWindowHeight() - 1, blue);
    drawRectangle(x2, y, x2 + BOARD_LINE_WIDTH, getWindowHeight() - 1, blue);

    // Drawing the blocks that are already stored in the board
    x1 += 1;
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            // Check if the block is filled, if so, draw it
            if (!m_board->isFreeBlock(i, j))
                drawRectangle(x1 + i * BLOCK_SIZE,
                              y + j * BLOCK_SIZE,
                              (x1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                              (y + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
                              red);
        }
    }
}

int Game::getWindowHeight()
{
    int h;
    SDL_GetWindowSize(m_window, nullptr, &h);

    return h;
}
