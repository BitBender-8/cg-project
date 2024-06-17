#pragma once

#include "../includes/snake.h"

Snake::Snake()
{
    setColor(SNAKE_HEAD_COLOR, SNAKE_BODY_COLOR);
}
void Snake::setColor(Color headColor, Color bodyColor)
{
    this->headColor = headColor;
    this->bodyColor = bodyColor;
}

void Snake::setDirection(SnakeDirection direction)
{
    if ((direction == SnakeDirection::UP && this->direction != SnakeDirection::DOWN) ||
        (direction == SnakeDirection::DOWN && this->direction != SnakeDirection::UP) ||
        (direction == SnakeDirection::LEFT && this->direction != SnakeDirection::RIGHT) ||
        (direction == SnakeDirection::RIGHT && this->direction != SnakeDirection::LEFT))
    {
        this->direction = direction;
    }
}

void Snake::drawSnake()
{
    for (size_t i = 0; i < positions.size(); i++)
    {
        if (i == 0)
        {
            glColor3f(headColor.r, headColor.g, headColor.b);
        }
        else
        {
            glColor3f(bodyColor.r, bodyColor.g, bodyColor.b);
        }
        glRectd(this->positions[i].x, this->positions[i].y, this->positions[i].x + 1, this->positions[i].y + 1);
    }
}

void Snake::moveSnake()
{
    // Move each segment from the tail to the head
    for (size_t i = this->positions.size() - 1; i > 0; i--)
    {
        this->positions[i].x = this->positions[i - 1].x;
        this->positions[i].y = this->positions[i - 1].y;
    }

    // Update the head position based on the current direction
    switch (this->direction)
    {
    case SnakeDirection::UP:
        this->positions[0].y++;
        break;
    case SnakeDirection::DOWN:
        this->positions[0].y--;
        break;
    case SnakeDirection::LEFT:
        this->positions[0].x--;
        break;
    case SnakeDirection::RIGHT:
        this->positions[0].x++;
        break;
    default:
        break;
    }
}

const std::vector<Position> &Snake::getPositions()
{
    return this->positions;
}

void Snake::growSnake()
{
    positions.push_back(positions[positions.size() - 1]);
}

size_t Snake::getLength()
{
    return this->positions.size();
}
