#pragma once
#include "raylib.h"

typedef struct Peddles
{
    Vector2 coordinate;
    int width, height;
    Color color;
    unsigned int movement;
    float movementSpeed;
} Peddles;

Peddles InitPeddles(const Vector2 coordinate, const int w, const int h, const Color c)
{
    Peddles peddles = {coordinate, w, h, c, 450, 0.0};
    return peddles;
}

void MovePeddles(Peddles *peddles, const bool wasdKeys, const bool arrowKeys, const double deltaTime)
{
    peddles->movementSpeed = peddles->movement * deltaTime;
    if (wasdKeys)
    {
        if (IsKeyDown(KEY_W) && peddles->coordinate.y > -1)
        {
            peddles->coordinate.y -= peddles->movementSpeed;
        }
        else if (IsKeyDown(KEY_S) && peddles->coordinate.y <= GetRenderHeight() - 120)
        {
            peddles->coordinate.y += peddles->movementSpeed;
        }
    }
    else if (arrowKeys)
    {
        if (IsKeyDown(KEY_UP) && peddles->coordinate.y > -1)
        {
            peddles->coordinate.y -= peddles->movementSpeed;
        }
        else if (IsKeyDown(KEY_DOWN) && peddles->coordinate.y <= GetRenderHeight() - 120)
        {
            peddles->coordinate.y += peddles->movementSpeed;
        }
    }
}

void MoveAiPeddles(const Ball *ball, Peddles *peddles, const double deltaTime, const bool *collide)
{
	peddles->movementSpeed = peddles->movement * deltaTime;

	if ((ball->coordinates.x > GetRenderWidth() / 2 - ball->radius) && !*collide)
	{
		// Calculate predicted Y position where ball will intersect with a paddle
		const float timeToReach = (peddles->coordinate.x - ball->coordinates.x) / ball->velocity.x;
		const float predictedY = ball->coordinates.y + (ball->velocity.y * timeToReach);

		const float reactionThreshold = 25.0f;

		// Move towards on predicted position
		if (predictedY > peddles->coordinate.y + peddles->height / 2 + reactionThreshold)
		{
			if (peddles->coordinate.y <= GetRenderHeight() - 120)
				peddles->coordinate.y += peddles->movementSpeed;
		}
		else if (predictedY < peddles->coordinate.y + peddles->height / 2 - reactionThreshold)
		{
			if (peddles->coordinate.y > -1)
				peddles->coordinate.y -= peddles->movementSpeed;
		}
	}
}
