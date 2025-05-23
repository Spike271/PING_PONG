#pragma once
#include <raylib.h>
#include "Ball.h"
#include "Global.h"
#include "Rectangle.h"

void InitMovingComponents(void)
{
	SetRandomSeed((int)time(NULL));
	leftPeddle = InitPeddles((Vector2){0.0, screenHeight / 2 - 60}, 15, 120, WHITE);
	rightPeddle = InitPeddles((Vector2){screenWidth - 15, screenHeight / 2 - 60}, 15, 120, WHITE);
	ball = InitBall((Vector2){screenWidth / 2, (float)(GetRandomValue(0, screenHeight - 18))}, 18.0, YELLOW, 200);
}

void S_ResetMovingComponents(void)
{
	SetRandomSeed((int)time(NULL));
	leftPeddle = InitPeddles((Vector2){0.0, screenHeight / 2 - 60}, 15, 120, WHITE);
	rightPeddle = InitPeddles((Vector2){screenWidth - 15, screenHeight / 2 - 60}, 15, 120, WHITE);
	ball = InitBall((Vector2){screenWidth / 2, (float)(GetRandomValue(0, screenHeight - 18))}, 18.0, YELLOW, 200);
	humanScore = 0, aiScore = 0;
}

void M_ResetMovingComponents(void)
{
	SetRandomSeed((int)time(NULL));
	leftPeddle = InitPeddles((Vector2){0.0, screenHeight / 2 - 60}, 15, 120, WHITE);
	rightPeddle = InitPeddles((Vector2){screenWidth - 15, screenHeight / 2 - 60}, 15, 120, WHITE);
	ball = InitBall((Vector2){screenWidth / 2, (float)(GetRandomValue(0, screenHeight - 18))}, 18.0, YELLOW, 200);
	leftPlayerScore = 0, rightPlayerScore = 0;
}

void CheckCollisionForMultiPlayer(double deltaTime)
{
	if (CheckCollisionCircleRec(ball.coordinates, ball.radius, (Rectangle){leftPeddle.coordinate.x, leftPeddle.coordinate.y, leftPeddle.width, leftPeddle.height}))
	{
		SpeedIncrease(&ball, 0, deltaTime);
		ball.velocity.x *= -1;
		if (GetRandomValue(0, 1))
		{
			ball.velocity.y *= -1;
		}
	}

	if (ball.coordinates.x <= ball.radius)
	{
		InitMovingComponents();
		rightPlayerScore++;
	}

	if (CheckCollisionCircleRec(ball.coordinates, ball.radius, (Rectangle){rightPeddle.coordinate.x, rightPeddle.coordinate.y, rightPeddle.width, rightPeddle.height}))
	{
		SpeedIncrease(&ball, 1, deltaTime);
		ball.velocity.x *= -1;

		if (GetRandomValue(0, 1))
		{
			ball.velocity.y *= -1;
		}
	}

	if (ball.coordinates.x + ball.radius >= screenWidth)
	{
		InitMovingComponents();
		leftPlayerScore++;
	}
}

void CheckCollisionForSinglePlayer(double deltaTime, bool *collide)
{
	// check collision with left peddle
	if (CheckCollisionCircleRec(ball.coordinates, ball.radius, (Rectangle){leftPeddle.coordinate.x, leftPeddle.coordinate.y, leftPeddle.width, leftPeddle.height}))
    {
		*collide = false;
        SpeedIncrease(&ball, 0, deltaTime);
        ball.velocity.x *= -1;
        if (GetRandomValue(0, 1))
        {
            ball.velocity.y *= -1;
        }
    }

    if (ball.coordinates.x <= ball.radius)
    {
    	*collide = false;
        InitMovingComponents();
        aiScore++;
    }

	// check collision with right peddle
    if (CheckCollisionCircleRec(ball.coordinates, ball.radius, (Rectangle){rightPeddle.coordinate.x, rightPeddle.coordinate.y, rightPeddle.width, rightPeddle.height}))
    {
    	*collide = true;
        SpeedIncrease(&ball, 1, deltaTime);
        ball.velocity.x *= -1;

        if (GetRandomValue(0, 1))
        {
            ball.velocity.y *= -1;
        }
    }

    if (ball.coordinates.x + ball.radius >= screenWidth)
    {
    	*collide = false;
        InitMovingComponents();
        humanScore++;
    }
}
