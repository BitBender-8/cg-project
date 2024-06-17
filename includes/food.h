#pragma once
#include "utils.h"
#include "globals.h"

#include <GL/freeglut.h>
#include <GL/gl.h>

#include <random>

class Food
{
private:
    Position position;
    int maxX, maxY;
    Color color;

public:
    Food(int maxX, int maxY, Color color = FOOD_COLOR);
    void generateNewPosition();
    Position getPosition();
    void drawFood();
};
