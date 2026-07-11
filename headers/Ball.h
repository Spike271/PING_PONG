#pragma once
#include "Types.h"

Ball InitBall(Vector2 coordinate, float r, Color col, int speed);
void SpeedIncreaseX(Ball *ball, float deltaTime);
void SpeedIncreaseY(Ball *ball, float deltaTime);
void MoveBall(Ball *ball, double deltaTime);
