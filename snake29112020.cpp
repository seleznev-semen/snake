#include <iostream>
#include <ctime>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;

bool gameOver;
const int width = 20, height = 20;
int x, y, meatX, meatY, score, delay;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection edir;

void Setup()
{
    srand(time(0));
    gameOver = false;
    x = width / 2 - 1;
    y = height / 2 - 1;
    meatX = rand() % (width - 2) + 1;
    meatY = rand() % (height - 2) + 1;
    nTail = 0;
    edir = STOP;
    score = 0;
    delay = 100;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i == 0 || i == height - 1) cout << '#';
            else if (j == 0 || j == width - 1) cout << '#';
            else
            {
                if (i == y && j == x) cout << 'O';
                else if (i == meatY && j == meatX) cout << 'X';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; ++k)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            print = true;
                            cout << "o";
                        }
                    }
                    if (!print) cout << ' ';
                }
            }
        }
        cout << endl;
    }
    cout << "\nSCORE: " << score << endl << "SPEED:" << 100 - delay << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            edir = LEFT;
            break;
        case 'd':
            edir = RIGHT;
            break;
        case 'w':
            edir = UP;
            break;
        case 's':
            edir = DOWN;
            break;
        case 'p':
            edir = STOP;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; ++i)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (edir)
    {
    case LEFT:
        --x;
        break;
    case RIGHT:
        ++x;
        break;
    case UP:
        --y;
        break;
    case DOWN:
        ++y;
        break;
    case STOP:
        y = y;
        x = x;
        break;
    }
    if(x == 0 || x > width-2 || y == 0 || y > height-2)  gameOver = true;     //comment this to go though walls
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 2;
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 2;

    for (int i = 0; i < nTail; ++i)
    {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }

    if (x == meatX && y == meatY)
    {
        ++score;
        delay = 1000 / (10 + score * 0.5);
        meatX = rand() % (width - 2) + 1;
        meatY = rand() % (height - 2) + 1;
        ++nTail;
    }
}

void Delay()
{
    this_thread::sleep_for(chrono::milliseconds(delay));
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Delay();
    }
    int b;
    cin >> b;
    return 0;
}