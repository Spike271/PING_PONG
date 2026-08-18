#include "Options.h"
#include "Global.h"
#include <raygui.h>
#include "Config.h"

static bool saveButton = false;
static bool optionWindow = false;

void InitOptions(void)
{
    GuiLoadStyle(STYLE_PATH);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    gState.initOpts = false;
    optionWindow = true;
}

void RenderOptions(void)
{
    if (optionWindow)
    {
        optionWindow = !GuiWindowBox((Rectangle){100, 100, 894, 479}, "Controls");
        if (GuiButton((Rectangle){300, 500, 120, 24}, "Save")) { saveButton = true; optionWindow = false; }
        if (GuiButton((Rectangle){600, 500, 120, 24}, "Exit")) optionWindow = false;
        GuiSpinner((Rectangle){400, 240, 350, 40}, "Single Player Mode Score", &gState.defaultSP, 1, 30, true);
        GuiSpinner((Rectangle){400, 370, 350, 40}, "Multi Player Mode Score", &gState.defaultMP, 1, 30, true);
    }

    if (IsKeyPressed(KEY_ESCAPE) || !optionWindow)
    {
        if (saveButton)
        {
#ifndef PLATFORM_WEB
            SaveScores();
#endif
            saveButton = false;
        }
        GuiLoadStyleDefault();
        saveButton = false;
        optionWindow = false;
        gState.menu = MAINMENU;
    }
}

void DestructOptions(void)
{
    GuiLoadStyleDefault();
    saveButton = false;
    optionWindow = false;
}
