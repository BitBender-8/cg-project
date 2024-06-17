#pragma once

#include "../includes/level.h"

int Level::maxX = Grid::maxX;
int Level::maxY = Grid::maxY;

Level::Level(int levelNo, Color obstacleColor) : maxObstacles(levelNo * 10), obstacleColor(obstacleColor)
{
    generateObstaclePositions();
}

void Level::generateObstaclePositions()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int xMax = this->maxX - 2;
    int yMax = this->maxY - 2;
    int min = 1;

    std::uniform_int_distribution<> disX(min, xMax);
    std::uniform_int_distribution<> disY(min, yMax);

    for (int i = 0; i < maxObstacles; i++)
    {
        Position position(disX(gen), disY(gen));
        if (obstaclePositions.find(position) == obstaclePositions.end())
        {
            obstaclePositions.insert(std::move(position));
            ++i; // Increment i only when a position is successfully inserted
        }
    }
}

const std::unordered_set<Position, PositionHasher> &Level::getObstaclePositions()
{
    return this->obstaclePositions;
}

void Level::drawObstacles()
{
    glColor3f(this->obstacleColor.r, this->obstacleColor.g, this->obstacleColor.b);
    for (Position position : obstaclePositions)
    {
        glRectd(position.x, position.y, position.x + 1, position.y + 1);
    }
}

int Level::getLevel()
{
    return this->levelNo;
}

void Level::setColor(Color color)
{
    this->obstacleColor = color;
}
