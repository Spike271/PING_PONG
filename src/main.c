#include <raylib.h>

#include "lock.h"
#include "Global.h"
#include "Draw.h"
#include "AboutSection.h"
#include "Options.h"
#include "ExitMenu.h"
#include "SinglePlayerLevel.h"
#include "MultiPlayerLevel.h"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

#ifdef _MSC_VER
	#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

static void UpdateDrawFrame(void);
static void RenderMainMenu(void);

int main(void)
{
    if (AcquireLock() == -1)
    {
        fprintf(stderr, "Another instance is already running.");
        return 1;
    }

    InitMovingComponents();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong game");
    SetExitKey(0);
    gState.menu = MAINMENU;

    gState.font = LoadFontEx(FONT_PATH, 64, 0, 0);
    SetTextureFilter(gState.font.texture, TEXTURE_FILTER_BILINEAR);
    gState.bg = LoadTexture(BG_PATH);

#if defined(PLATFORM_WEB)
    gState.defaultSP = DEFAULT_SCORE;
    gState.defaultMP = DEFAULT_SCORE;
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    LoadScores();
    SetTargetFPS(GetMonitorRefreshRate(0));
    SetIcon();

    while (!WindowShouldClose() && !gState.exitPressed)
    {
        UpdateDrawFrame();
    }
#endif

    UnloadTexture(gState.bg);
    UnloadFont(gState.font);
    CloseWindow();
    ReleaseLock();
}

static void UpdateDrawFrame(void)
{
    BeginDrawing();

    switch (gState.menu)
    {
        case MAINMENU:
            RenderMainMenu();
            break;

        case SINGLEPLAYERMODE:
            if (gState.initSP) InitSinglePlayerLevel();
            RenderSinglePlayerLevel();
            if (gState.showExit)
            {
                if (DrawExitMenu()) RenderSinglePlayerLevel();
            }
            break;

        case MULTIPLAYERMODE:
            if (gState.initMP) InitMultiPlayerLevel();
            RenderMultiPlayerLevel();
            if (gState.showExit)
            {
                if (DrawExitMenu()) RenderMultiPlayerLevel();
            }
            break;

        case OPTIONS:
            if (gState.initOpts) InitOptions();
            RenderOptions();
            break;

        case ABOUTSECTION:
            RenderAboutSection();
            break;

        case EXIT:
            gState.exitPressed = true;
            break;
    }

    EndDrawing();
}

static void RenderMainMenu(void)
{
    ClearBackground(BLUE);
    DrawTexture(gState.bg, 0, 0, WHITE);

    GuiSetFont(gState.font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, (int)0xff0000ff);
    GuiLabel((Rectangle){20, 20, 550, 100}, "PONG GAME");

    GuiSetFont(GetFontDefault());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xFF);

    if (GuiLabelButton((Rectangle){20, 120, 100, 100}, "Single Player")) { gState.menu = SINGLEPLAYERMODE; gState.initSP = true; }
    if (GuiLabelButton((Rectangle){20, 220, 100, 100}, "Multi Player")) { gState.menu = MULTIPLAYERMODE; gState.initMP = true; }
    if (GuiLabelButton((Rectangle){20, 320, 100, 100}, "Options")) { gState.menu = OPTIONS; gState.initOpts = true; }
    if (GuiLabelButton((Rectangle){20, 420, 100, 100}, "About")) gState.menu = ABOUTSECTION;

#ifndef PLATFORM_WEB
    if (GuiLabelButton((Rectangle){20, 520, 100, 100}, "Exit")) gState.menu = EXIT;
#endif
}
