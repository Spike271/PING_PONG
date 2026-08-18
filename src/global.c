#include "Global.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Config.h"

GameState gState;

void SetIcon(void)
{
    const Image img = LoadImage(LOGO_PATH);
    if (img.data != NULL)
    {
        SetWindowIcon(img);
        UnloadImage(img);
    }
}

void LoadScores(void)
{
    gState.defaultSP = DEFAULT_SCORE;
    gState.defaultMP = DEFAULT_SCORE;

    FILE* fp = fopen(SCORE_PATH, "r");
    if (fp != NULL)
    {
        char data[128] = {0}, *endptr;
        while (fgets(data, sizeof(data), fp) != NULL)
        {
            if (strstr(data, "Single Player Score") != NULL)
            {
                const char* eq = strchr(data, '=');
                if (eq != NULL)
                    gState.defaultSP = strtol(eq + 1, &endptr, 10);
            }
            else if (strstr(data, "Multi Player Score") != NULL)
            {
                const char* eq = strchr(data, '=');
                if (eq != NULL)
                    gState.defaultMP = strtol(eq + 1, &endptr, 10);
            }
        }
        fclose(fp);
    }
    else
    {
        fp = fopen(SCORE_PATH, "w");
        if (fp != NULL)
        {
            fprintf(fp, "Single Player Score = %d\n", gState.defaultSP);
            fprintf(fp, "Multi Player Score = %d\n", gState.defaultMP);
            fclose(fp);
        }
    }
}

void SaveScores(void)
{
    FILE* fp = fopen(SCORE_PATH, "w");
    if (fp != NULL)
    {
        fprintf(fp, "Single Player Score = %d\n", gState.defaultSP);
        fprintf(fp, "Multi Player Score = %d\n", gState.defaultMP);
        fclose(fp);
    }
}
