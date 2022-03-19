#include "snakeGame.h"

Position::Position() = default;
Position::Position(int _x, int _y) : x(_x), y(_y){};
Position::Position(Position &that) : x(that.x), y(that.y){};

Position Position::operator=(const Position &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

bool Position::operator==(const Position &that) const
{
    if(x == that.x && y == that.y) return 1;
    return 0;
}

Food::Food()
{
    srand(time(NULL));
    position = Position(rand() % WIDTH, rand() % HEIGHT);
}

void Food::reswpan()
{
    position = Position(rand() % WIDTH, rand() % HEIGHT);
}

Snake::Snake() : direction(0), length(1)
{
    body[0] = new Position(WIDTH/2, HEIGHT/2);
    for(int i = 1; i < MAX_LENGTH; ++i)
        body[i] = new Position(-1, -1);
}

void Snake::moving()
{
    Position prev, prev2(*body[0]);
    for(int i = 1; i < length ; ++i)
    {
        prev = *(body[i]);
        *(body[i]) = prev2;
        prev2 = prev;
    }
    switch(dir)
    {
        case UP:
            --body[0]->y;
            break;
        case DOWN:
            ++body[0]->y;
            break;
        case RIGHT:
            ++body[0]->x;
            break;
        case LEFT:
            --body[0]->x;
            break;
        default:
            break;
    }
}

void Snake::action()
{
    if(kbhit()) direction = getch();
    switch(direction)
    {
        case 0x4B: // UP
            if(dir != DOWN) dir = UP;
            break;
        case 0x4D: // DOWN
            if(dir != UP) dir = DOWN;
            break;
        case 0x50: // RIGHT
            if(dir != LEFT) dir = RIGHT;
            break;
        case 0x48: // LEFT
            if(dir != RIGHT) dir = LEFT;
            break;
    }
}

GameMap::GameMap() : score(0), win(0), lose(0) {}

void GameMap::snakeCrossWall()
{
    if(snake.body[0]->x == -1) snake.body[0]->x = WIDTH-1;
    if(snake.body[0]->x == WIDTH) snake.body[0]->x = 0;
    if(snake.body[0]->y == -1) snake.body[0]->y = HEIGHT-1;
    if(snake.body[0]->y == HEIGHT) snake.body[0]->y = 0;
}

void GameMap::snakeEatFood()
{
    if(*(snake.body[0]) == food.position)
    {
        food.reswpan();
        ++score;
        ++snake.length;
    }
}

void GameMap::checkSnakelength()
{
    if(snake.length == MAX_LENGTH) win = 1;
}

void GameMap::checkSnakeEatSelf()
{
    for(int i = 1; i < snake.length; ++i)
        if(*(snake.body[0]) == *(snake.body[i])) lose = 1;
}

void GameMap::checkSnakeCollideFood()
{
    for(int i = 1; i < snake.length; ++i)
    {
        while(*(snake.body[i]) == food.position)
        {
            food.reswpan();
            break;
        }
    }
}

void GameMap::draw() const
{
    system("cls");
    if(!win && !lose)
    {
        cout << "Score:" << score << endl <<" ╔════════════════════════════════════════════╗ " << endl;
        for(int i = 0; i < HEIGHT; ++i)
        {
            cout << " ║ ";
            for(int j = 0; j < WIDTH; ++j)
            {
                bool isSnakeBody = 0;
                for(int k = 0; k < snake.length; ++k)
                {
                    if(*(snake.body[k]) == Position(i, j))
                    {
                        isSnakeBody = 1;
                        break;
                    }
                }
                if(isSnakeBody) cout << "▉";
                else if(food.position == Position(i, j)) cout << "▓▓";
                else cout << "  ";
            }
            cout << " ║ " << endl;
        }
        cout << " ╚════════════════════════════════════════════╝ " << endl;
        Sleep(50);
    }
    else if(win) cout << "YOU WIN!" << endl;
    else cout << "YOU LOSE! " << endl << "Your score:" << score << endl;
}

void GameMap::excute()
{
    ios_base::sync_with_stdio(0);
    while(!win && !lose)
    {
        checkSnakeCollideFood();
        snake.action();
        snake.moving();
        checkSnakeEatSelf();
        checkSnakelength();
        snakeCrossWall();
        snakeEatFood();
        draw();
    }
}
