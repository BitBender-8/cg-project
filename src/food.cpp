#include "../includes/food.h"

Food::Food(int maxX, int maxY, Color color) : maxX{maxX}, maxY(maxY), color{color}
{
    generateNewPosition();
}

void Food::generateNewPosition()
{
    int xMax = this->maxX - 2;
    int yMax = this->maxY - 2;
    int min = 1;

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(min, xMax);
    std::uniform_int_distribution<> disY(min, yMax);
    position.x = disX(gen);
    position.y = disY(gen);
}

Position Food::getPosition()
{
    return position;
}

void Food::drawFood()
{
    glColor3f(color.r, color.g, color.b);
    glRectd(position.x, position.y, position.x + 1, position.y + 1);
}
