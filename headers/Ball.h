#pragma once
#include "raylib.h"
#include "time.h"
#include "math.h"

typedef struct Ball
{
    Vector2 coordinates;
    float radius;
    Color color;
    int initialSpeed;
    Vector2 velocity;
} Ball;

int GetRandomDirection(void)
{
    SetRandomSeed((int)time(NULL));
    return GetRandomValue(0, 1);
}

Ball InitBall(Vector2 coordinate, float r, Color col, int speed)
{
    Ball ball = {{coordinate.x, coordinate.y}, r, col, speed};

    int randomXDirection = GetRandomDirection();
    ball.velocity.x = (randomXDirection == 0 ? -1 : 1) * ball.initialSpeed;

    int randomYDirection = GetRandomDirection();
    ball.velocity.y = (randomYDirection == 0 ? -1 : 1) * ball.initialSpeed;

    return ball;
}

void SpeedIncrease(Ball *ball, bool xy, float deltaTime)
{
    if (xy)
    {
        ball->velocity.x = fabsf(ball->velocity.x);

        if (ball->velocity.x < 600)
            ball->velocity.x += 5000.0 * deltaTime;
    }
    else
    {
        ball->velocity.y = fabsf(ball->velocity.y);

        if (ball->velocity.y < 600)
            ball->velocity.y += 5000.0 * deltaTime;
    }
}

void MoveBall(Ball *ball, double deltaTime)
{
    ball->coordinates.x += ball->velocity.x * deltaTime;
    ball->coordinates.y += ball->velocity.y * deltaTime;

    if (ball->coordinates.y < ball->radius)
    {
        ball->coordinates.y = ball->radius;
        ball->velocity.y *= -1;
    }
    else if (ball->coordinates.y > GetRenderHeight() - ball->radius)
    {
        ball->coordinates.y = GetRenderHeight() - ball->radius;
        ball->velocity.y *= -1;
    }
}
