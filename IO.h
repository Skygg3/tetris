#pragma once

enum Color
{
    BLACK,
    RED,
    GREEN,
    BLUE,
    CYAN,
    MAGENTA,
    YELLOW,
    WHITE,
    COLOR_MAX
};

class IO
{
public:
    IO();

    void drawRectangle(int x1, int y1, int x2, int y2, Color c);
    void clearScreen();
    int getScreenHeight();
    int initGraph();
    int pollkey();
    int getkey();
    int isKeyDown(int key);
    void updateScreen();
};
