#pragma once

#include "../includes/game.h"

Color Game::backgroundColor{BACKGROUND_COLOR};
int Game::score{0};
int Game::levelNo{0};
GameState Game::gameState{GameState::WAITING};

Snake Game::snake{};
Food Game::food(Grid::maxX, Grid::maxY);
size_t Game::maxSnakeLength{10};
Level Game::level(0, OBSTACLE_COLOR);

const unsigned char Game::waitingText[] = R"(
        Try not to eat yourself    
     and watch where you are going. 
    Good luck! Press space to start...
)";
const unsigned char Game::pauseText[] = R"(
    Game paused. Options:
        1. 'ESC' to resume
        2. 'L' to save your score and level
        3. 'TAB' to close the game
)";
const unsigned char Game::gameOverText[] =
    R"(Game over. Options:
        1. 'N' to start a new game
        2. 'L' to save your score and level
        3. 'TAB' to close the game
)";

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    switch (gameState)
    {
    case GameState::WAITING:
        glColor3f(WHITE.r, WHITE.g, WHITE.b);
        glRasterPos2f(Grid::maxX / 2 - 6, Grid::maxY / 2);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, waitingText);
        break;
    case GameState::RUNNING:
        if (snake.getLength() <= maxSnakeLength)
        {
            Grid::drawGrid();
            level.drawObstacles();
            food.drawFood();
            snake.moveSnake();

            std::vector<Position> snakePositions = snake.getPositions();
            std::vector<Position> snakeHead(
                snakePositions.begin(),
                snakePositions.begin() + 1);
            std::vector<Position> snakeBody(
                snakePositions.begin() + 1,
                snakePositions.end());
            std::vector<Position> obstaclePositions(
                level.getObstaclePositions().begin(),
                level.getObstaclePositions().end());

            if (checkCollision(snakeHead, Grid::getBoundaries()) ||
                checkCollision(snakeHead, obstaclePositions) ||
                checkCollision(snakeHead, snakeBody))
            {
                std::cout << "Level: " << levelNo << ", Score: " << score << std::endl;
                saveScore();
                gameState = GameState::GAMEOVER;
            }
            else if (checkCollision(std::vector<Position>{food.getPosition()}, snakeHead))
            {
                snake.growSnake();
                food.generateNewPosition();
                score++;
            }
            snake.drawSnake();
        }
        else
        {
            levelNo++;
            level = Level(levelNo, OBSTACLE_COLOR);
            std::cout << "Good job! Moving on to level " << levelNo + 1 << std::endl;
            snake = Snake();
            gameState = GameState::RUNNING;
        }
        break;
    case GameState::GAMEOVER:
        glColor3f(WHITE.r, WHITE.g, WHITE.b);
        glRasterPos2f(Grid::maxX / 2 - 5, Grid::maxY / 2 + 1);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, gameOverText);
        break;
    case GameState::PAUSED:
        glColor3f(WHITE.r, WHITE.g, WHITE.b);
        glRasterPos2f(Grid::maxX / 2 - 5, Grid::maxY / 2 + 1);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, pauseText);
        break;
    default:
        break;
    }
    glutSwapBuffers();
}

bool Game::checkCollision(const std::vector<Position> &object1, const std::vector<Position> &object2)
{
    std::unordered_set<Position, PositionHasher> object1Set;

    // Insert all positions from object1 into the unordered_set
    for (const auto &pos : object1)
    {
        object1Set.insert(pos);
    }

    // Check each position in object2 against the positions in object1Set
    for (const auto &pos : object2)
    {
        if (object1Set.find(pos) != object1Set.end())
            return true; // Collision detected
    }

    return false; // No collision detected
}

void Game::saveScore()
{
    std::ofstream file("../game-scores/scores.txt", std::ios::app);

    if (file.is_open())
    {
        file << "Level: " << levelNo << ", Score: " << score << std::endl;
        file.close();
        std::cout << "Score saved.\n";
    }
    else
    {
        std::cout << "Failed to open the file." << std::endl;
    }
}

void Game::keyboardInput(GLubyte key, int, int)
{
    // Handle keyboard input based on game state

    switch (gameState)
    {
    case GameState::WAITING:
        switch (key)
        {
        case ' ':
            gameState = GameState::RUNNING;
            break;
        default:
            break;
        }
        break;
    case GameState::RUNNING:
        // Handle directional keys for snake movement
        switch (key)
        {
        case 'W':
        case 'w':
            snake.setDirection(SnakeDirection::UP);
            break;
        case 'A':
        case 'a':
            snake.setDirection(SnakeDirection::LEFT);
            break;
        case 'S':
        case 's':
            snake.setDirection(SnakeDirection::DOWN);
            break;
        case 'D':
        case 'd':
            snake.setDirection(SnakeDirection::RIGHT);
            break;
        case ESC_KEY:
            togglePause();
            break;
        default:
            break;
        }
        break;
    case GameState::PAUSED:
        switch (key)
        {
        case 'l':
        case 'L':
            saveScore();
            break;
        case '\t':
            killGame();
            break;
        case ESC_KEY:
            togglePause();
            break;
        default:
            break;
        }
        break;
    case GameState::GAMEOVER:
        switch (key)
        {
        case 'l':
        case 'L':
            saveScore();
            break;
        case '\t':
            killGame();
            break;
        case 'n':
        case 'N':
            newGame();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void Game::initGlut(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glClearColor(backgroundColor.r, backgroundColor.g,
                 backgroundColor.b, backgroundColor.a);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPosX, windowPosY);
    glutCreateWindow(windowTitle);

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboardInput);
}

void Game::reshape(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1; // To prevent division by 0
    GLfloat aspect = static_cast<GLfloat>(w) / static_cast<GLfloat>(h);

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w >= h)
    {
        gluOrtho2D(0, Grid::maxX * aspect, 0, Grid::maxY);
    }
    else
    {
        gluOrtho2D(0, Grid::maxX, 0, Grid::maxY / aspect);
    }
}

void Game::timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(static_cast<unsigned int>(1000) / FPS, timer, 0);
}

void Game::prepareGame()
{
    initGlut(0, nullptr);
    std::cout << "Game waiting\n";
    glutMainLoop();
}

void Game::newGame() 
{
    score = 0;
    levelNo = 0;
    level = Level(levelNo, OBSTACLE_COLOR);
    snake = Snake();
    gameState = GameState::RUNNING;
}

void Game::togglePause()
{
    if (gameState == GameState::PAUSED)
    {
        gameState = GameState::RUNNING;
        std::cout << "Game resumed\n";
    }
    else if (gameState == GameState::RUNNING)
    {
        gameState = GameState::PAUSED;
        std::cout << "Game paused\n";
    }
}

void Game::killGame()
{
    std::cout << "Game terminated\n";
    glutLeaveMainLoop();
}
