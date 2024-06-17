#pragma once
#include "utils.h"
#include "globals.h"

#include <GL/freeglut.h>
#include <GL/gl.h>

#include <unordered_set>
#include <random>
#include <vector>

class Level
{
private:
    int levelNo{0};
    std::unordered_set<Position, PositionHasher> obstaclePositions;
    static int maxX, maxY;
    int maxObstacles{0};
    Color obstacleColor{OBSTACLE_COLOR};

public:
    Level(int levelNo, Color obstacleColor);
    void generateObstaclePositions();
    const std::unordered_set<Position, PositionHasher> &getObstaclePositions();
    void drawObstacles();
    int getLevel();
    void setColor(Color color);
};
