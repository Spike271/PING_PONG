#include "Draw.h"
#include "Global.h"
#include "Paddle.h"
#include "Ball.h"
#include <raylib.h>
#include <raygui.h>
#include <time.h>

void InitMovingComponents(void)
{
    SetRandomSeed((int)time(NULL));
    gState.leftPaddle  = InitPaddle((Vector2){0.0f, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2}, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
    gState.rightPaddle = InitPaddle((Vector2){SCREEN_WIDTH - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2}, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
    gState.ball = InitBall((Vector2){SCREEN_WIDTH / 2, (float)GetRandomValue(0, SCREEN_HEIGHT - (int)BALL_RADIUS)}, BALL_RADIUS, YELLOW, BALL_SPEED);
}

void ResetMovingComponents(bool isMultiplayer)
{
    SetRandomSeed((int)time(NULL));
    gState.leftPaddle  = InitPaddle((Vector2){0.0f, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2}, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
    gState.rightPaddle = InitPaddle((Vector2){SCREEN_WIDTH - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2}, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
    gState.ball = InitBall((Vector2){SCREEN_WIDTH / 2, (float)GetRandomValue(0, SCREEN_HEIGHT - (int)BALL_RADIUS)}, BALL_RADIUS, YELLOW, BALL_SPEED);

    if (isMultiplayer)
    {
        gState.leftScore = 0;
        gState.rightScore = 0;
    }
    else
    {
        gState.humanScore = 0;
        gState.aiScore = 0;
    }
}

void DrawCourt(bool isSinglePlayer, double deltaTime)
{
    ClearBackground(BLUE);

    if (gState.isRunning)
    {
        if (GuiLabelButton((Rectangle){15, 20, 10, 10}, "#132#")) gState.isRunning = false;
    }
    else
    {
        if (GuiLabelButton((Rectangle){15, 20, 10, 10}, "#131#")) gState.isRunning = true;
    }

    DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);
    DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, (Color){67, 152, 232, 255});

    if (isSinglePlayer)
    {
        DrawText(TextFormat("%02d", gState.humanScore), SCREEN_WIDTH / 4, 20, 32, WHITE);
        DrawText(TextFormat("%02d", gState.aiScore), SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, 20, 32, WHITE);
    }
    else
    {
        DrawText(TextFormat("%02d", gState.leftScore), SCREEN_WIDTH / 4, 20, 32, WHITE);
        DrawText(TextFormat("%02d", gState.rightScore), SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, 20, 32, WHITE);
    }

#ifndef PLATFORM_WEB
    DrawText(TextFormat("FPS : %d", GetFPS()), 20, 700, 32, GREEN);
#endif

    DrawRectangle(gState.leftPaddle.coordinate.x, gState.leftPaddle.coordinate.y, gState.leftPaddle.width, gState.leftPaddle.height, gState.leftPaddle.color);
    DrawRectangle(gState.rightPaddle.coordinate.x, gState.rightPaddle.coordinate.y, gState.rightPaddle.width, gState.rightPaddle.height, gState.rightPaddle.color);

    DrawCircle(gState.ball.coordinates.x, gState.ball.coordinates.y, gState.ball.radius, gState.ball.color);
}

void CheckCollisionSP(double deltaTime)
{
    if (CheckCollisionCircleRec(gState.ball.coordinates, gState.ball.radius,
        (Rectangle){gState.leftPaddle.coordinate.x, gState.leftPaddle.coordinate.y, gState.leftPaddle.width, gState.leftPaddle.height}))
    {
        gState.spCollide = false;
        SpeedIncreaseY(&gState.ball, deltaTime);
        gState.ball.velocity.x *= -1;
        if (GetRandomValue(0, 1)) gState.ball.velocity.y *= -1;
    }

    if (gState.ball.coordinates.x <= gState.ball.radius)
    {
        gState.spCollide = false;
        ResetMovingComponents(false);
        gState.aiScore++;
    }

    if (CheckCollisionCircleRec(gState.ball.coordinates, gState.ball.radius,
        (Rectangle){gState.rightPaddle.coordinate.x, gState.rightPaddle.coordinate.y, gState.rightPaddle.width, gState.rightPaddle.height}))
    {
        gState.spCollide = true;
        SpeedIncreaseX(&gState.ball, deltaTime);
        gState.ball.velocity.x *= -1;
        if (GetRandomValue(0, 1)) gState.ball.velocity.y *= -1;
    }

    if (gState.ball.coordinates.x + gState.ball.radius >= SCREEN_WIDTH)
    {
        gState.spCollide = false;
        ResetMovingComponents(false);
        gState.humanScore++;
    }
}

void CheckCollisionMP(double deltaTime)
{
    if (CheckCollisionCircleRec(gState.ball.coordinates, gState.ball.radius,
        (Rectangle){gState.leftPaddle.coordinate.x, gState.leftPaddle.coordinate.y, gState.leftPaddle.width, gState.leftPaddle.height}))
    {
        SpeedIncreaseY(&gState.ball, deltaTime);
        gState.ball.velocity.x *= -1;
        if (GetRandomValue(0, 1)) gState.ball.velocity.y *= -1;
    }

    if (gState.ball.coordinates.x <= gState.ball.radius)
    {
        ResetMovingComponents(true);
        gState.rightScore++;
    }

    if (CheckCollisionCircleRec(gState.ball.coordinates, gState.ball.radius,
        (Rectangle){gState.rightPaddle.coordinate.x, gState.rightPaddle.coordinate.y, gState.rightPaddle.width, gState.rightPaddle.height}))
    {
        SpeedIncreaseX(&gState.ball, deltaTime);
        gState.ball.velocity.x *= -1;
        if (GetRandomValue(0, 1)) gState.ball.velocity.y *= -1;
    }

    if (gState.ball.coordinates.x + gState.ball.radius >= SCREEN_WIDTH)
    {
        ResetMovingComponents(true);
        gState.leftScore++;
    }
}
