#pragma once
#include <stdbool.h>

void InitMovingComponents(void);
void ResetMovingComponents(bool isMultiplayer);
void DrawCourt(bool isSinglePlayer, double deltaTime);
void CheckCollisionSP(double deltaTime);
void CheckCollisionMP(double deltaTime);
