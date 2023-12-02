#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

#define cols 25
#define rows 25
#define foods 10
#define snakeLength 256

char board[cols * rows];
int isGameOver = 0;

struct SnakePart
{
    int x, y;
};

struct Snake
{
    int length;
    struct SnakePart part[snakeLength];
};

struct Snake snake;

struct Food
{
    int x, y;
    int eaten;
};
struct Food food[foods];

void fill()
{
    int x, y;
    int boardSize = cols * rows;
    fill_n(board, boardSize, ' ');

    for (x = 0; x < cols; x++)
    {
        board[x] = '#';
        board[(rows - 1) * cols + x] = '#';
    }

    for (y = 0; y < rows; y++)
    {
        board[y * cols] = '#';
        board[y * cols + cols - 1] = '#';
    }
}

void print()
{
    int x, y;
    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < cols; x++)
        {
            cout << board[y * cols + x];
        }
        cout << endl;
    }
}

void draw_snake()
{
    for (int i = snake.length; i > 0; i--)
    {
        board[snake.part[i].y * cols + snake.part[i].x] = '*';
    }
    board[snake.part[0].y * cols + snake.part[0].x] = '@';
}

void move(int X, int Y)
{
    for (int i = snake.length; i > 0; i--)
    {
        snake.part[i] = snake.part[i - 1];
    }
    snake.part[0].x += X;
    snake.part[0].y += Y;
}

void read_keyboard()
{
    int ch = _getch();
    if (ch == 'w')
    {
        move(0, -1);
    }
    else if (ch == 's')
    {
        move(0, 1);
    }
    else if (ch == 'a')
    {
        move(-1, 0);
    }
    else if (ch == 'd')
    {
        move(1, 0);
    }
}

void draw_food()
{
    for (int i = 0; i < foods; i++)
    {
        if (!food[i].eaten)
        {
            board[food[i].y * cols + food[i].x] = '+';
        }
    }
}

void setup_food()
{
    for (int i = 0; i < foods; i++)
    {
        food[i].x = 1 + rand() % (cols - 2);
        food[i].y = 1 + rand() % (rows - 2);
        food[i].eaten = 0;
    }
}

void setup_snake()
{
    snake.length = 0;
    snake.part[0].x = 1 + rand() % (cols - 2);
    snake.part[0].y = 1 + rand() % (rows - 2);
}

void game_rules()
{
    for (int i = 0; i < foods; i++)
    {
        if (!food[i].eaten)
        {
            if (food[i].x == snake.part[0].x &&
                food[i].y == snake.part[0].y)
            {
                food[i].eaten = 1;
                snake.length++;
            }
        }
    }

    if (snake.part[0].x == 0 || snake.part[0].x == cols - 1 ||
        snake.part[0].y == 0 || snake.part[0].y == rows - 1)
    {
        isGameOver = 1;
    }

    for (int i = 1; i < snake.length; i++)
    {
        if (snake.part[0].x == snake.part[i].x &&
            snake.part[0].y == snake.part[i].y)
        {
            isGameOver = 1;
        }
    }
}

int main()
{
    srand(time(0));

    setup_snake();
    setup_food();

    while (!isGameOver)
    {
        fill();
        draw_food();
        draw_snake();
        game_rules();
        system("cls");
        cout << "Snake Game, Score: " << (snake.length) << endl;
        print();
        if (snake.length == foods)
        {
            cout << "YOU WIN!" << endl;
            cout << "Final score: " << (snake.length) << endl;
            return 0;
        }
        if (!isGameOver)
            read_keyboard();
    }
    cout << "Game Over, Final score: " << (snake.length) << endl;
    while (true)
        _getch();
    return 0;
}
