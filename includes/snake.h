#pragma once

#include "utils.h"
#include "globals.h"

#include <GL/freeglut.h>
#include <GL/gl.h>

#include <vector>

class Snake
{
private:
    // The length of this array is the same as the snake's length
    std::vector<Position> positions{{20, 20}, {20, 19}, {20, 18}, {20, 17}, {20, 16}};
    Color headColor{SNAKE_HEAD_COLOR};
    Color bodyColor{SNAKE_BODY_COLOR};
    SnakeDirection direction{SnakeDirection::RIGHT};

public:
    Snake();
    void setColor(Color headColor, Color bodyColor);
    void setDirection(SnakeDirection direction);
    void drawSnake();
    void moveSnake();
    const std::vector<Position> &getPositions();
    void growSnake();
    size_t getLength();
};
