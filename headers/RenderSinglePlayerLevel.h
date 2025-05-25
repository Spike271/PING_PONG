#pragma once
#include <raygui.h>
#include <raylib.h>

#include "Draw.h"
#include "Global.h"

double S_lastFrameTime;
bool S_gameOver, S_collide;
int S_nextAction;

void DestructSinglePlayerLevel(void);

void InitSinglePlayerLevel(void)
{
#ifndef PLATFORM_WEB
	SetTargetFPS(GetMonitorRefreshRate(0));
#endif

	S_gameOver = false;
	S_collide = false;
	S_nextAction = 0;

	GuiLoadStyle("./res/style_dark.rgs");
	GuiSetStyle(BUTTON, TEXT_SIZE, 16);

	initSinglePlayerLevel = false;
	S_lastFrameTime = GetTime();
}

void RenderSinglePlayerLevel(void)
{
	if (IsKeyPressed(KEY_ESCAPE)) menu = MAINMENU;

	double currentFrameTime = GetTime();
	double deltaTime = currentFrameTime - S_lastFrameTime;
	S_lastFrameTime = currentFrameTime;

	if (!S_gameOver) MovePeddles(&leftPeddle, true, false, deltaTime);
	if (!S_gameOver) MoveAiPeddles(&ball, &rightPeddle, deltaTime, &S_collide);

	ClearBackground(BLUE);

	DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
	DrawCircle(screenWidth / 2, screenHeight / 2, 100, (Color){67, 152, 232, 255});

	DrawText(TextFormat("%02d", humanScore), screenWidth / 4, 20, 32, WHITE);
	DrawText(TextFormat("%02d", aiScore), screenWidth / 2 + screenWidth / 4, 20, 32, WHITE);

#ifndef PLATFORM_WEB
	DrawText(TextFormat("FPS : %d", GetFPS()), 20, 700, 32, GREEN);
#endif

	DrawRectangle(leftPeddle.coordinate.x, leftPeddle.coordinate.y, leftPeddle.width, leftPeddle.height, leftPeddle.color);
	DrawRectangle(rightPeddle.coordinate.x, rightPeddle.coordinate.y, rightPeddle.width, rightPeddle.height, rightPeddle.color);

	DrawCircle(ball.coordinates.x, ball.coordinates.y, ball.radius, ball.color);
	if (!S_gameOver) MoveBall(&ball, deltaTime);
	CheckCollisionForSinglePlayer(deltaTime, &S_collide);

	if (humanScore >= S_DefaultScore)
	{
		S_nextAction = GuiMessageBox((Rectangle){screenWidth / 2 - 225, screenHeight / 2 - 100, 450, 200},
								   "#191#Congratulations!!!", "You won!", "Play again;Exit");
		S_gameOver = true;

		if (S_nextAction == 1)
		{
			S_ResetMovingComponents();
			S_gameOver = false, S_collide = false;
		}
		else if (S_nextAction == 2) menu = MAINMENU;
	}
	else if (aiScore >= S_DefaultScore)
	{
		S_nextAction = GuiMessageBox((Rectangle){screenWidth / 2 - 225, screenHeight / 2 - 100, 450, 200}, "#152#",
								   "You lost!", "Play again;Exit");
		S_gameOver = true;

		if (S_nextAction == 1)
		{
			S_ResetMovingComponents();
			S_gameOver = false, S_collide = false;
		}
		else if (S_nextAction == 2) menu = MAINMENU;
	}

	if (menu == MAINMENU) DestructSinglePlayerLevel();
}

void DestructSinglePlayerLevel(void)
{
	GuiLoadStyleDefault();
	S_ResetMovingComponents();

#ifndef PLATFORM_WEB
	SetTargetFPS(60);
#endif
}
