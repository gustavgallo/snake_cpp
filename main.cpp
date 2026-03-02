#include <iostream>
#include <cstdlib>
#include <ctime>
#include "utils/snake.hpp"
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

using namespace std;

const int WIDTH = 35;
const int HEIGHT = 20;
const int UI_HEIGHT = 3;

void sleepMs(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void clearScreen()
{


    cout << "\033[2J\033[1;1H";


}

char getChar()
{
#ifdef _WIN32
    if (_kbhit())
        return _getch();
    return 0;
#else
    char ch = 0;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    read(STDIN_FILENO, &ch, 1);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
#endif
}

void createFood(pos &food)
{

    unsigned int posX = rand() % (WIDTH - 2) + 1;
    unsigned int posY = rand() % (HEIGHT - UI_HEIGHT - 2) + (UI_HEIGHT + 1);

    food.x = posX;
    food.y = posY;
}

void getInput(snake& snake)
{
    char key = getChar();

    switch (key)
    {
        case 'w': snake.changeDirection(UP); break;
        case 's': snake.changeDirection(DOWN); break;
        case 'a': snake.changeDirection(LEFT); break;
        case 'd': snake.changeDirection(RIGHT); break;
        case 'q': exit(0);
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

                int centerY = HEIGHT / 2;
                int centerX = (WIDTH / 2) - 5;

                if (y == centerY && x == centerX)
                {
                    cout << "GAME OVER BRO";
                    x += 8; // pular o resto da palavra
                }
                else if (y == centerY + 2 && x == centerX - 4)
                {
                    cout << "Press ENTER to restart";
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

void drawMenu()
{

    clearScreen();

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {

            if (y == 0 || y == HEIGHT - 1)
            {
                cout << "=";
            }
            else if (x == 0 || x == WIDTH - 1)
            {
                cout << "|";
            }
            else
            {

                int centerY = HEIGHT / 2;
                int centerX = (WIDTH / 2) - 5;

                if (y == centerY - 3 && x == centerX - 7)
                {
                    cout << "WELCOME TO THE SNAKE GAME";
                    x += 24; // tal da gambiarra
                }
                else if (y == centerY - 1 && x == centerX - 5)
                {
                    cout << "Made by F R I E N D S";
                    x += 20;
                }
                else if (y == centerY + 1 && x == centerX - 4)
                {
                    cout << "Press ENTER to start ";
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
    char tmp;
    cin >> tmp;
}

void startGame(snake &snake, pos &apple)
{

    int score = 0;
    while (1)
    {
        getInput(snake);

        snake.move();
        snake.wrap(WIDTH, HEIGHT, UI_HEIGHT);

        pos head = snake.getHead();

        if (head.x == apple.x && head.y == apple.y)
        {
            snake.grow();
            createFood(apple);
            score += 10;
        }

        clearScreen();

        cout << "Use WASD to move | Q to leave\n";
        cout << "SCORE: " << score << endl;

        const auto &body = snake.getBody();
        if (snake.checkSelfCollision())
        {
            return;

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
                    printed = true;
                }

                if (!printed)
                    cout << ' ';
            }
            cout << endl;
        }

        sleepMs(60); 
    }
}

int main()
{
    srand(time(NULL));
    
   

    snake kobra(WIDTH / 2, HEIGHT / 2);
    pos apple;
    createFood(apple);

    while (true)
    {
        drawMenu();
        startGame(kobra,apple);
        drawGameOver();

        
    }
    

    return 0;
}
