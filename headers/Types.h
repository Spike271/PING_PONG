#pragma once
#include "raylib.h"

typedef struct Ball
{
    Vector2 coordinates;
    float radius;
    Color color;
    int initialSpeed;
    Vector2 velocity;
} Ball;

typedef struct Paddle
{
    Vector2 coordinate;
    int width, height;
    Color color;
    unsigned int movement;
    float movementSpeed;
} Paddle;

typedef enum
{
    MAINMENU = 0,
    SINGLEPLAYERMODE,
    MULTIPLAYERMODE,
    OPTIONS,
    ABOUTSECTION,
    EXIT
} Menu;
