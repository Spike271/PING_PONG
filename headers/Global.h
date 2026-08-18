#pragma once
#include <stdbool.h>
#include "Types.h"

typedef struct
{
    int defaultSP;
    int defaultMP;
    unsigned int humanScore;
    unsigned int aiScore;
    unsigned int leftScore;
    unsigned int rightScore;
    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;
    Font font;
    Texture2D bg;
    bool exitPressed;
    bool initSP;
    bool initMP;
    bool initOpts;
    bool showExit;
    bool isRunning;
    double spLastFrameTime;
    bool spGameOver;
    bool spCollide;
    int spNextAction;
    double mpLastFrameTime;
    bool mpGameOver;
    int mpNextAction;
    Menu menu;
} GameState;

extern GameState gState;

void SetIcon(void);
void LoadScores(void);
void SaveScores(void);
