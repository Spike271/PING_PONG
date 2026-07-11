#include "Paddle.h"
#include <Config.h>

Paddle InitPaddle(Vector2 coordinate, int w, int h, Color c)
{
    Paddle paddle = {coordinate, w, h, c, PADDLE_SPEED, 0.0f};
    return paddle;
}

void MovePaddle(Paddle *paddle, bool wasdKeys, bool arrowKeys, double deltaTime)
{
    paddle->movementSpeed = paddle->movement * deltaTime;
    if (wasdKeys)
    {
        if (IsKeyDown(KEY_W) && paddle->coordinate.y > -1)
            paddle->coordinate.y -= paddle->movementSpeed;
        else if (IsKeyDown(KEY_S) && paddle->coordinate.y <= GetRenderHeight() - PADDLE_HEIGHT)
            paddle->coordinate.y += paddle->movementSpeed;
    }
    else if (arrowKeys)
    {
        if (IsKeyDown(KEY_UP) && paddle->coordinate.y > -1)
            paddle->coordinate.y -= paddle->movementSpeed;
        else if (IsKeyDown(KEY_DOWN) && paddle->coordinate.y <= GetRenderHeight() - PADDLE_HEIGHT)
            paddle->coordinate.y += paddle->movementSpeed;
    }
}

void MoveAiPaddle(const Ball *ball, Paddle *paddle, double deltaTime, const bool *collide)
{
    paddle->movementSpeed = paddle->movement * deltaTime;

    if ((ball->coordinates.x > GetRenderWidth() / 2 - ball->radius) && !*collide)
    {
        float timeToReach = (paddle->coordinate.x - ball->coordinates.x) / ball->velocity.x;
        float predictedY = ball->coordinates.y + (ball->velocity.y * timeToReach);
        float threshold = 25.0f;

        if (predictedY > paddle->coordinate.y + paddle->height / 2 + threshold)
        {
            if (paddle->coordinate.y <= GetRenderHeight() - PADDLE_HEIGHT)
                paddle->coordinate.y += paddle->movementSpeed;
        }
        else if (predictedY < paddle->coordinate.y + paddle->height / 2 - threshold)
        {
            if (paddle->coordinate.y > -1)
                paddle->coordinate.y -= paddle->movementSpeed;
        }
    }
}
