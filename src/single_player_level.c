#include "SinglePlayerLevel.h"
#include "Global.h"
#include "Draw.h"
#include "Paddle.h"
#include "Ball.h"
#include <raygui.h>
#include <raylib.h>

void InitSinglePlayerLevel(void)
{
    gState.spGameOver = false;
    gState.spCollide = false;
    gState.isRunning = true;
    gState.spNextAction = 0;
    gState.initSP = false;
    gState.spLastFrameTime = GetTime();

    GuiLoadStyle(STYLE_PATH);
    GuiSetStyle(BUTTON, TEXT_SIZE, 16);
}

void RenderSinglePlayerLevel(void)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        gState.isRunning = !gState.isRunning;
        gState.showExit = !gState.showExit;
    }

    double now = GetTime();
    double dt = now - gState.spLastFrameTime;
    gState.spLastFrameTime = now;

    if (!gState.spGameOver && gState.isRunning)
    {
        MovePaddle(&gState.leftPaddle, true, false, dt);
        MoveAiPaddle(&gState.ball, &gState.rightPaddle, dt, &gState.spCollide);
    }

    DrawCourt(true, dt);

    if (!gState.spGameOver && gState.isRunning) MoveBall(&gState.ball, dt);
    CheckCollisionSP(dt);

    if (gState.humanScore >= gState.defaultSP)
    {
        gState.spNextAction = GuiMessageBox(
            (Rectangle){SCREEN_WIDTH / 2 - 225, SCREEN_HEIGHT / 2 - 100, 450, 200},
            "#191#Congratulations!!!", "You won!", "Play again;Exit");
        gState.spGameOver = true;

        if (gState.spNextAction == 1)
        {
            ResetMovingComponents(false);
            gState.spGameOver = false;
            gState.spCollide = false;
        }
        else if (gState.spNextAction == 2) gState.menu = MAINMENU;
    }
    else if (gState.aiScore >= gState.defaultSP)
    {
        gState.spNextAction = GuiMessageBox(
            (Rectangle){SCREEN_WIDTH / 2 - 225, SCREEN_HEIGHT / 2 - 100, 450, 200},
            "#152#", "You lost!", "Play again;Exit");
        gState.spGameOver = true;

        if (gState.spNextAction == 1)
        {
            ResetMovingComponents(false);
            gState.spGameOver = false;
            gState.spCollide = false;
        }
        else if (gState.spNextAction == 2) gState.menu = MAINMENU;
    }

    if (gState.menu == MAINMENU)
    {
        GuiLoadStyleDefault();
        ResetMovingComponents(false);
    }
}
