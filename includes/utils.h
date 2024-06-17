#pragma once

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <functional>

typedef unsigned int ColorHex;

// Color class to store rgb values of colors. Has a constructor
// which supports hex color values.
class Color
{
public:
    GLclampf r;
    GLclampf g;
    GLclampf b;
    GLclampf a; // Default alpha to fully opaque

public:
    Color(ColorHex hex);
    Color() : r{0.0f}, g{0.0f}, b{0.0f}, a{1.0f} {}
    Color(GLclampf r, GLclampf g, GLclampf b, GLclampf a) : r{r}, g{g}, b{b}, a{a} {}
};

enum class SnakeDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Position
{
public:
    int x;
    int y;
    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}
    // Define equality operator for Position
    bool operator==(const Position &other) const;
};

class PositionHasher
{
public:
    std::size_t operator()(const Position &pos) const;
};
