#ifndef SNAKEGAME_H_INCLUDED
#define SNAKEGAME_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

const int WIDTH = 21, HEIGHT = 21, MAX_LENGTH = 16;

class Position
{
    private:
        int x, y;
        Position();
        Position(int _x, int _y);
        Position(Position &that);
        Position operator=(const Position &that);
        bool operator==(const Position &that) const;
    public:
        friend class Food;
        friend class Snake;
        friend class GameMap;
};

class Food
{
    private:
        Position position;
        Food();
        void reswpan();
    public:
        friend class Snake;
        friend class GameMap;
};

class Snake
{
    private:
        enum {STOP, UP, DOWN, LEFT, RIGHT} dir = STOP;
        Position *body[MAX_LENGTH];
        int direction, length;
        Snake();
        void moving();
        void action();
    public:
        friend class GameMap;
};

class GameMap
{
    private:
        Snake snake;
        Food food;
        int score;
        bool win, lose;
    public:
        GameMap();
        void snakeCrossWall();
        void snakeEatFood();
        void checkSnakelength();
        void checkSnakeEatSelf();
        void checkSnakeCollideFood();
        void draw() const;
        void excute();
};
#endif // SNAKEGAME_H_INCLUDED
