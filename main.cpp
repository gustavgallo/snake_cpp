#include <iostream>
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

int main()
{

    snake snake(WIDTH / 2, HEIGHT / 2);

    while (true)
    {

        getInput(snake);

        snake.move();
        snake.wrap(WIDTH, HEIGHT, UI_HEIGHT);

        clearScreen();

        cout << "SNAKE TESTE\n";
        cout << "Use WASD para mover | Q para sair\n";

        const auto &body = snake.getBody();

        for (int y = UI_HEIGHT; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {

                bool printed = false;

                if ((x == 0 || x == WIDTH - 1) && y > UI_HEIGHT)
                {
                    cout << "|";
                    continue;
                }

                if (y == UI_HEIGHT)
                {
                    cout << "_";
                    continue;
                }

                if (y == HEIGHT - 1)
                {
                    cout << "_";
                    continue;
                }


                for (size_t i = 0; i < body.size(); i++)
                {
                    if (body[i].x == x && body[i].y == y)
                    {
                        cout << (i == 0 ? '@' : '*');
                        printed = true;
                        break;
                    }
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
