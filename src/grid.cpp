#pragma once

#include "../includes/grid.h"

// Static initializations
Color Grid::borderColor{BORDER_COLOR};
Color Grid::meshColor{MESH_COLOR};
std::vector<Position> Grid::boundaries{};

void Grid::drawGrid()
{
    for (int i = 0; i < maxX; i++)
    {
        for (int j = 0; j < maxY; j++)
        {
            if (i == 0 || j == 0 || i == maxX - 1 || j == maxY - 1)
            {
                glColor3f(borderColor.r, borderColor.g, borderColor.b);
                glRectd(i, j, i + 1, j + 1);
            }
            else
            {
                glColor3f(meshColor.r, meshColor.g, meshColor.b);
                glBegin(GL_LINE_LOOP);
                {
                    GLfloat fi = static_cast<GLfloat>(i);
                    GLfloat fj = static_cast<GLfloat>(j);

                    glVertex2f(fi, fj);
                    glVertex2f(fi + 1.0f, fj);
                    glVertex2f(fi + 1.0f, fj + 1.0f);
                    glVertex2f(fi, fj + 1.0f);
                }
                glEnd();
            }
        }
    }
}

std::vector<Position> Grid::getBoundaries()
{
    if (boundaries.empty())
    {
        // Horizontal boundaries
        for (int i = 0; i < maxX; i++)
        {
            boundaries.push_back(Position(i, 0));
            boundaries.push_back(Position(i, Grid::maxY - 1));
        }
        // Vertical boundaries
        for (int i = 0; i < maxY; i++)
        {
            boundaries.push_back(Position(0, i));
            boundaries.push_back(Position(Grid::maxX - 1, i));
        }
    }

    return boundaries;
}
