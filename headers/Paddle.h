#pragma once
#include "Types.h"

Paddle InitPaddle(Vector2 coordinate, int w, int h, Color c);
void MovePaddle(Paddle *paddle, bool wasdKeys, bool arrowKeys, double deltaTime);
void MoveAiPaddle(const Ball *ball, Paddle *paddle, double deltaTime, const bool *collide);
