#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

#define cols 25
#define rows 25
#define foods 5

char board[cols * rows];

int isGameOver = 0;

void fill_board()
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

void print_board()
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

#define SNAKE_MAX_LEN 256
struct SnakePart
{
    int x, y;
};
struct Snake
{
    int length;
    struct SnakePart part[SNAKE_MAX_LEN];
};
struct Snake snake;

struct Food
{
    int x, y;
    int consumed;
};
struct Food food[foods];

void draw_snake()
{
    for (int i = snake.length; i > 0; i--)
    {
        board[snake.part[i].y * cols + snake.part[i].x] = '*';
    }
    board[snake.part[0].y * cols + snake.part[0].x] = '@';
}

void move_snake(int deltaX, int deltaY)
{
    for (int i = snake.length; i > 0; i--)
    {
        snake.part[i] = snake.part[i - 1];
    }

    snake.part[0].x += deltaX;
    snake.part[0].y += deltaY;
}

void read_keyboard()
{
    int ch = _getch();
    switch (ch)
    {
    case 'w':
        move_snake(0, -1);
        break;
    case 's':
        move_snake(0, 1);
        break;
    case 'a':
        move_snake(-1, 0);
        break;
    case 'd':
        move_snake(1, 0);
        break;
    }
}

void draw_food()
{
    for (int i = 0; i < foods; i++)
    {
        if (!food[i].consumed)
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
        food[i].consumed = 0;
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
        if (!food[i].consumed)
        {
            if (food[i].x == snake.part[0].x &&
                food[i].y == snake.part[0].y)
            {
                food[i].consumed = 1;
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
        fill_board();
        draw_food();
        draw_snake();
        game_rules();
        system("cls");
        cout << "Snake Game, Score: " << (snake.length) << endl;
        print_board();
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
