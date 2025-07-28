#pragma once
#include <raygui.h>
#include "Global.h"

void DestructOptions();
static bool saveButton = false, optionWindow = false;

void InitOptions(void)
{
	GuiLoadStyle("./res/style_dark.rgs");
	GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
	initOptions = false;
	optionWindow = true;
}

void RenderOptions(void)
{
	if (optionWindow == true)
	{
		optionWindow = !GuiWindowBox((Rectangle){ 100, 100, 894, 479 }, "Controls");
		if (GuiButton((Rectangle){ 300, 500, 120, 24 }, "Save")) saveButton = true, optionWindow = false;
		if (GuiButton((Rectangle){ 600, 500, 120, 24 }, "Exit")) optionWindow = false;
		GuiSpinner((Rectangle){ 400, 240, 350, 40 }, "Single Player Mode Score", &S_DefaultScore, 1, 30, true);
		GuiSpinner((Rectangle){ 400, 370, 350, 40 }, "Multi Player Mode Score", &M_DefaultScore, 1, 30, true);
	}

	if (IsKeyPressed(KEY_ESCAPE) || optionWindow == false)
	{
		if (saveButton == true)
		{
#ifndef PLATFORM_WEB
			ModifyScoreFile();
#endif
			saveButton = false;
		}
		DestructOptions();
		menu = MAINMENU;
	}
}

void DestructOptions(void)
{
	GuiLoadStyleDefault();
	saveButton = false;
	optionWindow = false;
}
