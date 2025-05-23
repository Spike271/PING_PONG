#pragma once
#include <raylib.h>
#include "Global.h"

static const char* text[] = {
	" - Hey whats is going on guys, my name is Mayank, and welcome in this game.",
	" - The game is just a simple pong game made in C using raylib(amazing library btw).",
	" - Use the WS keys to control the left peddle in single player mode to beat the Ai.",
	" - If you score three(default score) before Ai you won the game.",
	" - You can always change the default scoring thing by going to the 'score.txt'",
	"   file and changing the value.",
	" - In multiplayer mode you can play with your friends(although not online).",
	" - Use WS keys to control the left paddle and up, down arrow keys to control the right paddle.",
	" - Whoever scores the three points(default score) first win's the game.",
	" - You can escape any section of the game by pressing the ESC key."};

void RenderAboutSection(void)
{
	if (IsKeyPressed(KEY_ESCAPE)) menu = MAINMENU;

	ClearBackground(BLUE);
	for (int i = 0; i < 9; i++)
	{
		DrawTextEx(customFont, text[i], (Vector2){10, 50 + i * 60}, 32, 0, WHITE);
	}
}
