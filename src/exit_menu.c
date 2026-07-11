#include "ExitMenu.h"
#include "Global.h"
#include <raylib.h>

static Rectangle yesBtn = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 120, 50 };
static Rectangle noBtn  = { SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2, 120, 50 };

bool DrawExitMenu(void)
{
    Vector2 mouse = GetMousePosition();
    bool pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool hoverYes = CheckCollisionPointRec(mouse, yesBtn);
    bool hoverNo  = CheckCollisionPointRec(mouse, noBtn);

    if (pressed)
    {
        if (hoverYes) { gState.showExit = false; gState.menu = MAINMENU; }
        if (hoverNo)  { gState.isRunning = true; gState.showExit = false; }
    }

    DrawRectangleRounded((Rectangle){SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100, 400, 200}, 0.15f, 8, (Color){30, 30, 30, 255});
    DrawRectangleRoundedLines((Rectangle){SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100, 400, 200}, 0.15f, 8, (Color){200, 200, 200, 200});

    const char *title = "Do you want to exit?";
    int tw = MeasureText(title, 24);
    DrawText(title, SCREEN_WIDTH / 2 - tw / 2, SCREEN_HEIGHT / 2 - tw / 4, 24, WHITE);

    DrawRectangleRounded(yesBtn, 0.3f, 8, hoverYes ? RED : (Color){180, 30, 30, 255});
    int yw = MeasureText("YES", 22);
    DrawText("YES", (int)(yesBtn.x + yesBtn.width / 2) - yw / 2, (int)(yesBtn.y + 14), 22, WHITE);

    DrawRectangleRounded(noBtn, 0.3f, 8, hoverNo ? (Color){80, 200, 80, 255} : (Color){30, 140, 30, 255});
    int nw = MeasureText("NO", 22);
    DrawText("NO", (int)(noBtn.x + noBtn.width / 2) - nw / 2, (int)(noBtn.y + 14), 22, WHITE);

    return !gState.showExit;
}
