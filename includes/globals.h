#pragma once

#include "./utils.h"

// Some predefined colors
const Color BLACK(0x000000FF);
const Color WHITE(0xFFFFFFFF);
const Color RED(0xFF0000FF);
const Color GREEN(0x00FF00FF);
const Color BLUE(0x0000FFFF);

const Color BORDER_COLOR(0xD23030FF);
const Color SNAKE_BODY_COLOR(0xFFA000FF);
const Color SNAKE_HEAD_COLOR(0xFF6F00FF);
const Color OBSTACLE_COLOR(0xE65100FF);
const Color FOOD_COLOR(0x4CAF50FF);
const Color BACKGROUND_COLOR(BLACK);
const Color MESH_COLOR(0x908E8EFF);

// Window parameters
const int windowWidth = 800;
const int windowHeight = 800;
const int windowPosX = 50;
const int windowPosY = 50;
const char windowTitle[] = "Snake";

// Keyboard key
const char ESC_KEY = 27;
