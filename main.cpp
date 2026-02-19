#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "utils/snake.hpp"

using namespace std;

const int WIDTH = 35;
const int HEIGHT = 20;
const int UI_HEIGHT = 3;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void createFood(pos &food)
{

    unsigned int posX = rand() % (WIDTH - 2) + 1;
    unsigned int posY = rand() % (HEIGHT - UI_HEIGHT - 2) + (UI_HEIGHT + 1);

    food.x = posX;
    food.y = posY;
}

void getInput(snake &snake)
{
    if (_kbhit())
    {
        char c = _getch();
        switch (c)
        {
        case 'w':
            snake.changeDirection(UP);
            break;
        case 's':
            snake.changeDirection(DOWN);
            break;
        case 'a':
            snake.changeDirection(LEFT);
            break;
        case 'd':
            snake.changeDirection(RIGHT);
            break;
        case 'q':
            exit(0);
        }
    }
}

bool drawBorders(int x, int y)
{

    if ((x == 0 || x == WIDTH - 1) && y > UI_HEIGHT)
    {
        cout << "|";
        return true;
    }

    if (y == UI_HEIGHT)
    {
        cout << "_";
        return true;
    }

    if (y == HEIGHT - 1)
    {
        cout << "_";
        return true;
    }
    return false;
}

void drawGameOver()
{
    clearScreen();

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // Bordas
            if (y == 0 || y == HEIGHT - 1)
            {
                cout << "_";
            }
            else if (x == 0 || x == WIDTH - 1)
            {
                cout << "|";
            }
            else
            {
                // Centralizar texto
                int centerY = HEIGHT / 2;
                int centerX = (WIDTH / 2) - 5;

                if (y == centerY && x == centerX)
                {
                    cout << "GAME OVER";
                    x += 8; // pular o resto da palavra
                }
                else if (y == centerY + 2 && x == centerX - 4)
                {
                    cout << "Press any key to exit";
                    x += 20;
                }
                else
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

int main()
{
    srand(time(NULL));

    snake snake(WIDTH / 2, HEIGHT / 2);
    pos apple;
    createFood(apple);

    while (true)
    {

        getInput(snake);

        snake.move();
        snake.wrap(WIDTH, HEIGHT, UI_HEIGHT);

        pos head = snake.getHead();

        if (head.x == apple.x && head.y == apple.y)
        {
            snake.grow();
            createFood(apple);
        }

        clearScreen();

        cout << "SNAKE TEST\n";
        // cout << "Use WASD to move | Q to leave\n";
        cout << "Apple: " << apple.x << " " << apple.y << endl;

        const auto &body = snake.getBody();
        if (snake.checkSelfCollision())
        {
            drawGameOver();
            cin.get();
            break;
        }

        // PRINTING STARTS DOWN FROM HERE
        /////////////////////////////////
        for (int y = UI_HEIGHT; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {

                if (drawBorders(x, y))
                    continue;

                bool printed = false;

                for (int i = 0; i < body.size(); i++)
                {
                    if (body[i].x == x && body[i].y == y)
                    {
                        cout << (i == 0 ? 'O' : 'o');
                        printed = true;
                        break;
                    }
                }

                if ((apple.x == x) && (apple.y == y))
                {
                    cout << '*';
                }

                if (!printed)
                    cout << ' ';
            }
            cout << endl;
        }

        Sleep(60);
    }

    return 0;
}
