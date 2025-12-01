#include <raylib.h>

#include "./../headers/lock.h"
#include "./../headers/Options.h"
#include "./../headers/Draw.h"
#include "./../headers/Global.h"
#include "./../headers/AboutSection.h"
#include "./../headers/SinglePlayerLevel.h"
#include "./../headers/MultiPlayerLevel.h"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

#ifdef _MSC_VER
    #pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

void UpdateDrawFrame(void);
void RenderMainMenu(void);

int main(void)
{
	if (acquire_lock() == -1)
	{
		fprintf(stderr, "Another instance is already running.");
		return 1;
	}
	InitMovingComponents();
	InitWindow(screenWidth, screenHeight, "Pong game");
	SetExitKey(0);
	menu = MAINMENU;

	customFont = LoadFontEx("./res/Roboto-Medium.ttf", 64, 0, 0);
	SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);
	texture = LoadTexture("./res/bg.jpg");

#if defined(PLATFORM_WEB)
	S_DefaultScore = 3;
	M_DefaultScore = 3;
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	GetScoreFromFile();
	SetTargetFPS(GetMonitorRefreshRate(0));
	SetIcon();

	while (!WindowShouldClose() && !exitButtonPressed)
	{
		UpdateDrawFrame();
	}
#endif

	UnloadTexture(texture);
	UnloadFont(customFont);

	CloseWindow();
	release_lock();
}

void UpdateDrawFrame(void)
{
	BeginDrawing();

	switch (menu)
	{
		case MAINMENU:
			RenderMainMenu();
			break;

		case SINGLEPLAYERMODE:
			if (initSinglePlayerLevel) InitSinglePlayerLevel();
			RenderSinglePlayerLevel();
			break;

		case MULTIPLAYERMODE:
			if (initMultiPlayerLevel) InitMultiPlayerLevel();
			RenderMultiPlayerLevel();
			break;

		case OPTIONS:
			if (initOptions) InitOptions();
			RenderOptions();
			break;

		case ABOUTSECTION:
			RenderAboutSection();
			break;

		case EXIT:
			exitButtonPressed = true;
			break;

		default: break;
	}

	EndDrawing();
}

void RenderMainMenu()
{
	ClearBackground(BLUE);
	DrawTexture(texture, 0, 0, WHITE);

	GuiSetFont(customFont);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
	GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, (int)0xff0000ff);
	GuiLabel((Rectangle){20, 20, 550, 100}, "PONG GAME");

	GuiSetFont(GetFontDefault());
	GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
	GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xFF);

	if (GuiLabelButton((Rectangle){20, 120, 100, 100}, "Single Player")) menu = SINGLEPLAYERMODE, initSinglePlayerLevel = true;
	if (GuiLabelButton((Rectangle){20, 220, 100, 100}, "Multi Player")) menu = MULTIPLAYERMODE, initMultiPlayerLevel = true;
	if (GuiLabelButton((Rectangle){20, 320, 100, 100}, "Options")) menu = OPTIONS, initOptions = true;
	if (GuiLabelButton((Rectangle){20, 420, 100, 100}, "About")) menu = ABOUTSECTION;

#ifndef PLATFORM_WEB
	if (GuiLabelButton((Rectangle){20, 520, 100, 100}, "Exit")) menu = EXIT;
#endif
}
