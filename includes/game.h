#pragma once

#include "globals.h"
#include "utils.h"
#include "grid.h"
#include "level.h"
#include "food.h"
#include "snake.h"

#include <iostream>
#include <cstring>
#include <fstream>

enum class GameState
{
    GAMEOVER,
    RUNNING,
    PAUSED,
    WAITING,
};

class Game
{
private:
    static Color backgroundColor;
    static const int FPS{10};
    static int score;
    static int levelNo;
    static GameState gameState;

    static const unsigned char pauseText[];
    static const unsigned char gameOverText[];
    static const unsigned char waitingText[];

    static Snake snake;
    static Food food;
    static size_t maxSnakeLength;
    static Level level;

private:
    Game() = delete;
    static void render();
    static void keyboardInput(GLubyte key, int, int);
    static void initGlut(int argc, char *argv[]);
    static void reshape(int w, int h);
    static void timer(int);
    static bool checkCollision(const std::vector<Position> &object1, const std::vector<Position> &object2);

public:
    static void prepareGame();
    static void newGame();
    static void togglePause();
    static void saveScore();
    static void killGame();
};
