#include <iostream>
#include <cstdlib>
#include <ncurses.h>

#define SIZE 9

using namespace std;

struct Board
{
    int board[SIZE][SIZE] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 1},
        {2, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int xpos = 0;
    int ypos = 0;
};

void ncursesSetup();
void printBoard(Board b);
void detectKeypress(int *xpos, int *ypos);
void wrapCoords(int *xpos, int *ypos);

void ncursesSetup()
{
    initscr();            // setup for ncurses
    cbreak();             // removes buffer
    noecho();             // prevents output from displaying in terminal
    keypad(stdscr, TRUE); // Enable special keys like arrow keys
}

void printBoard(Board b)
{
    system("clear");

    cout << "  ";

    // prints out x axis coord
    for (int i = 0; i < SIZE; i++)
    {
        cout << (char)('A' + i);
    }

    cout << "\r\n  ";

    for (int i = 0; i < SIZE; i++)
    {
        if (i == b.xpos)
        {
            cout << '+';
        }
        else
        {
            cout << ' ';
        }
    }

    cout << "\r\n";

    for (int i = 0; i < SIZE; i++)
    {
        cout << i + 1;

        if (b.ypos == i)
        {
            cout << '+';
        }
        else
        {
            cout << ' ';
        }

        for (int j = 0; j < SIZE; j++)
        {
            cout << b.board[i][j];
        }

        cout << "\r\n";
    }
}

void detectKeypress(int *xpos, int *ypos)
{
    int key = getch();

    switch (key)
    {
    case KEY_UP:
        *ypos -= 1;
        break;
    case KEY_DOWN:
        *ypos += 1;
        break;
    case KEY_LEFT:
        *xpos -= 1;
        break;
    case KEY_RIGHT:
        *xpos += 1;
        break;
    }
}

void wrapCoords(int *xpos, int *ypos)
{
    if (*ypos < 0)
    {
        *ypos = SIZE - 1;
    }
    else if (*ypos > SIZE - 1)
    {
        *ypos = 0;
    }

    if (*xpos < 0)
    {
        *xpos = SIZE - 1;
    }
    else if (*xpos > SIZE - 1)
    {
        *xpos = 0;
    }
}

void gameLoop(Board b)
{
    while (true)
    {
        printBoard(b);
        detectKeypress(&b.xpos, &b.ypos);
        wrapCoords(&b.xpos, &b.ypos);
    }
}

int main()
{
    ncursesSetup();

    Board b;

    gameLoop(b);

    endwin();

    return 0;
}
