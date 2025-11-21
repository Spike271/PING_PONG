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

static int GetRandomDirection(void)
{
    SetRandomSeed((int)time(NULL));
    return GetRandomValue(0, 1);
}

Ball InitBall(const Vector2 coordinate, const float r, const Color col, const int speed)
{
    Ball ball = {{coordinate.x, coordinate.y}, r, col, speed};

    const int randomXDirection = GetRandomDirection();
    ball.velocity.x = (randomXDirection == 0 ? -1 : 1) * ball.initialSpeed;

    const int randomYDirection = GetRandomDirection();
    ball.velocity.y = (randomYDirection == 0 ? -1 : 1) * ball.initialSpeed;

    return ball;
}

void SpeedIncrease(Ball *ball, const bool xy, const float deltaTime)
{
    if (xy == true)
    {
        ball->velocity.x = fabsf(ball->velocity.x);
        if (ball->velocity.x < 600) ball->velocity.x += 5000.0f * deltaTime;
    }
    else
    {
        ball->velocity.y = fabsf(ball->velocity.y);
        if (ball->velocity.y < 600) ball->velocity.y += 5000.0f * deltaTime;
    }
}

void MoveBall(Ball *ball, const double deltaTime)
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
