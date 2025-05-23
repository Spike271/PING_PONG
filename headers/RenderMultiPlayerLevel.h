#pragma once
#include <raygui.h>
#include <raylib.h>

#include "Draw.h"
#include "Global.h"

int M_nextAction;
bool M_gameOver;
double M_lastFrameTime;

void DestructMultiPlayerLevel(void);

void InitMultiPlayerLevel(void)
{
#ifndef PLATFORM_WEB
	SetTargetFPS(GetMonitorRefreshRate(0));
#endif

	initMultiPlayerLevel = false;
	M_nextAction = 0;
	M_gameOver = false;

	GuiLoadStyle("./../res/style_dark.rgs");
	GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

	M_lastFrameTime = GetTime();
}

void RenderMultiPlayerLevel(void)
{
	if (IsKeyPressed(KEY_ESCAPE)) menu = MAINMENU;

	double currentFrameTime = GetTime();
	double deltaTime = currentFrameTime - M_lastFrameTime;
	M_lastFrameTime = currentFrameTime;

	if (!M_gameOver) MovePeddles(&leftPeddle, true, false, deltaTime);
	if (!M_gameOver) MovePeddles(&rightPeddle, false, true, deltaTime);

	ClearBackground(BLUE);

	DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
	DrawCircle(screenWidth / 2, screenHeight / 2, 100, (Color){67, 152, 232, 255});

	DrawText(TextFormat("%02d", leftPlayerScore), screenWidth / 4, 20, 32, WHITE);
	DrawText(TextFormat("%02d", rightPlayerScore), screenWidth / 2 + screenWidth / 4, 20, 32, WHITE);

#ifndef PLATFORM_WEB
	DrawText(TextFormat("FPS : %d", GetFPS()), 20, 700, 32, GREEN);
#endif

	DrawRectangle(leftPeddle.coordinate.x, leftPeddle.coordinate.y, leftPeddle.width, leftPeddle.height, leftPeddle.color);
	DrawRectangle(rightPeddle.coordinate.x, rightPeddle.coordinate.y, rightPeddle.width, rightPeddle.height, rightPeddle.color);

	DrawCircle(ball.coordinates.x, ball.coordinates.y, ball.radius, ball.color);
	if (!M_gameOver) MoveBall(&ball, deltaTime);
	CheckCollisionForMultiPlayer(deltaTime);

	if (leftPlayerScore >= M_DefaultScore)
	{
		M_nextAction = GuiMessageBox((Rectangle){screenWidth / 2 - 225, screenHeight / 2 - 100, 450, 200},
								   "#191#Congratulations!!!", "Left player won!", "Play again;Exit");
		M_gameOver = true;

		if (M_nextAction == 1)
		{
			M_ResetMovingComponents();
			M_gameOver = false;
		}
		else if (M_nextAction == 2) menu = MAINMENU;
	}
	else if (rightPlayerScore >= M_DefaultScore)
	{
		M_nextAction = GuiMessageBox((Rectangle){screenWidth / 2 - 225, screenHeight / 2 - 100, 450, 200},
								   "#191#Congratulations!!!", "Right player won!", "Play again;Exit");
		M_gameOver = true;

		if (M_nextAction == 1)
		{
			M_ResetMovingComponents();
			M_gameOver = false;
		}
		else if (M_nextAction == 2) menu = MAINMENU;
	}

	if (menu == MAINMENU) DestructMultiPlayerLevel();
}

void DestructMultiPlayerLevel(void)
{
	GuiLoadStyleDefault();
	M_ResetMovingComponents();

#ifndef PLATFORM_WEB
	SetTargetFPS(60);
#endif
}
