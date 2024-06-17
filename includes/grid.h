#pragma once

#include "utils.h"
#include "globals.h"

#include <GL/freeglut.h>
#include <GL/gl.h>

#include <vector>

class Grid
{
public:
    static const int maxX = 40, maxY = 40;
    static Color meshColor;
    static Color borderColor;
    static std::vector<Position> boundaries;

public:
    void static drawGrid();
    static std::vector<Position> getBoundaries();
};
