#include "MultiPlayerLevel.h"
#include "Global.h"
#include "Draw.h"
#include "Paddle.h"
#include "Ball.h"
#include <raygui.h>
#include <raylib.h>
#include <Config.h>

void InitMultiPlayerLevel(void)
{
    gState.initMP = false;
    gState.isRunning = true;
    gState.mpNextAction = 0;
    gState.mpGameOver = false;
    gState.mpLastFrameTime = GetTime();

    GuiLoadStyle(STYLE_PATH);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
}

void RenderMultiPlayerLevel(void)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        gState.isRunning = !gState.isRunning;
        gState.showExit = !gState.showExit;
    }

    double now = GetTime();
    double dt = now - gState.mpLastFrameTime;
    gState.mpLastFrameTime = now;

    if (!gState.mpGameOver && gState.isRunning)
    {
        MovePaddle(&gState.leftPaddle, true, false, dt);
        MovePaddle(&gState.rightPaddle, false, true, dt);
    }

    DrawCourt(false, dt);

    if (!gState.mpGameOver && gState.isRunning) MoveBall(&gState.ball, dt);
    CheckCollisionMP(dt);

    if (gState.leftScore >= gState.defaultMP)
    {
        gState.mpNextAction = GuiMessageBox(
            (Rectangle){SCREEN_WIDTH / 2 - 225, SCREEN_HEIGHT / 2 - 100, 450, 200},
            "#191#Congratulations!!!", "Left player won!", "Play again;Exit");
        gState.mpGameOver = true;

        if (gState.mpNextAction == 1)
        {
            ResetMovingComponents(true);
            gState.mpGameOver = false;
        }
        else if (gState.mpNextAction == 2) gState.menu = MAINMENU;
    }
    else if (gState.rightScore >= gState.defaultMP)
    {
        gState.mpNextAction = GuiMessageBox(
            (Rectangle){SCREEN_WIDTH / 2 - 225, SCREEN_HEIGHT / 2 - 100, 450, 200},
            "#191#Congratulations!!!", "Right player won!", "Play again;Exit");
        gState.mpGameOver = true;

        if (gState.mpNextAction == 1)
        {
            ResetMovingComponents(true);
            gState.mpGameOver = false;
        }
        else if (gState.mpNextAction == 2) gState.menu = MAINMENU;
    }

    if (gState.menu == MAINMENU)
    {
        GuiLoadStyleDefault();
        ResetMovingComponents(true);
    }
}
