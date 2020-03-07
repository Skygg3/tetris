#pragma once

class Pieces
{
public:
    int getBlockType(int piece, int rotation, int x, int y);
    int getXInitialPosition(int piece, int rotation);
    int getYInitialPosition(int piece, int rotation);
};
