#include <iostream>
#include <cstdlib>
#include <ncurses.h>

#define SIZE 9

using namespace std;

struct WinCon
{
    bool win = false;
    int lives = 3;
};

struct Board
{
    int board[SIZE][SIZE] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    bool playableBoard[SIZE][SIZE];

    int xpos = 0;
    int ypos = 0;
};

void ncursesSetup();
void printBoard(Board *b, WinCon *wc);
void detectKeypress(Board *b);
void wrapCoords(Board *b);
void createPlayableBoard(Board *b);
void checkWin(Board *b, WinCon *wc);

void ncursesSetup()
{
    initscr();            // setup for ncurses
    cbreak();             // removes buffer
    noecho();             // prevents output from displaying in terminal
    keypad(stdscr, TRUE); // Enable special keys like arrow keys
}

void printBoard(Board *b, WinCon *wc)
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
        if (i == b->xpos)
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

        if (b->ypos == i)
        {
            cout << '+';
        }
        else
        {
            cout << ' ';
        }

        for (int j = 0; j < SIZE; j++)
        {
            cout << b->board[i][j];
        }

        cout << "\r\n";
    }

    cout << "\r\n";
    cout << "[LIVES] " << wc->lives << endl;

    if (wc->lives == 0)
    {
        system("clear");
        cout << "[PRESS ANY KEY TO EXIT]" << endl;
    }
    else if (wc->win == true)
    {
        system("clear");
        cout << "YOU WIN\r\n";
        cout << "[PRESS ANY KEY TO EXIT]" << endl;
    }
}

void detectKeypress(Board *b)
{
    int key = getch();

    if (!isdigit(key))
    {
        switch (key)
        {
        case KEY_UP:
            b->ypos -= 1;
            break;
        case KEY_DOWN:
            b->ypos += 1;
            break;
        case KEY_LEFT:
            b->xpos -= 1;
            break;
        case KEY_RIGHT:
            b->xpos += 1;
            break;
        }
    }
    else if (isdigit(key))
    {
        if (b->playableBoard[b->ypos][b->xpos])
        {
            b->board[b->ypos][b->xpos] = key - '0';
        }
    }
}

void wrapCoords(Board *b)
{
    if (b->ypos < 0)
    {
        b->ypos = SIZE - 1;
    }
    else if (b->ypos > SIZE - 1)
    {
        b->ypos = 0;
    }

    if (b->xpos < 0)
    {
        b->xpos = SIZE - 1;
    }
    else if (b->xpos > SIZE - 1)
    {
        b->xpos = 0;
    }
}

void gameLoop(Board *b, WinCon *wc)
{
    printBoard(b, wc);

    while (!wc->win && wc->lives != 0)
    {
        wrapCoords(b);
        checkWin(b, wc);
        printBoard(b, wc);
        detectKeypress(b);
    }
}

void checkWin(Board *b, WinCon *wc)
{
    for (int i = 0; i < SIZE; i++)
    {
        int check[SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

        for (int j = 0; j < SIZE; j++)
        {
            if (b->board[i][j] != 0)
            {
                check[b->board[i][j] - 1]++;

                if (check[b->board[i][j] - 1] > 1)
                {
                    wc->lives--;
                    b->board[b->ypos][b->xpos] = 0;
                    return;
                }
            }
        }
    }

    for (int j = 0; j < SIZE; j++)
    {
        int check[SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

        for (int i = 0; i < SIZE; i++)
        {
            if (b->board[i][j] != 0)
            {
                check[b->board[i][j] - 1]++;

                if (check[b->board[i][j] - 1] > 1)
                {
                    wc->lives--;
                    b->board[b->ypos][b->xpos] = 0;
                    return;
                }
            }
        }
    }

    for (int k = 0; k < 3; k++)
    {
        for (int l = 0; l < 3; l++)
        {
            int check[SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int xsect = l * 3;
                    int ysect = k * 3;

                    if (b->board[ysect + i][xsect + j] != 0)
                    {
                        check[b->board[ysect + i][xsect + j] - 1]++;

                        if (check[b->board[ysect + i][xsect + j] - 1] > 1)
                        {
                            wc->lives--;
                            b->board[b->ypos][b->xpos] = 0;
                            return;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (b->board[i][j] == 0)
            {
                return;
            }
        }
    }

    wc->win = true;
    return;
}

void createPlayableBoard(Board *b)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (b->board[i][j] != 0)
            {
                b->playableBoard[i][j] = false;
            }
            else
            {
                b->playableBoard[i][j] = true;
            }
        }
    }
}

int main()
{
    ncursesSetup();

    Board b;
    WinCon wc;

    createPlayableBoard(&b);

    gameLoop(&b, &wc);

    endwin();

    return 0;
}
