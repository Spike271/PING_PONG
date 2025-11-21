#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ball.h"
#include "Rectangle.h"

const int screenWidth = 1125;
const int screenHeight = 750;

int S_DefaultScore;
int M_DefaultScore;

bool exitButtonPressed = false;
bool initSinglePlayerLevel = false;
bool initMultiPlayerLevel = false;
bool initOptions = false;

unsigned int humanScore = 0;
unsigned int aiScore = 0;

unsigned int leftPlayerScore = 0;
unsigned int rightPlayerScore = 0;

Peddles leftPeddle;
Peddles rightPeddle;
Ball ball;

Font customFont;
Texture2D texture;

typedef enum
{
	MAINMENU = 0,
	SINGLEPLAYERMODE,
	MULTIPLAYERMODE,
	OPTIONS,
	ABOUTSECTION,
	EXIT
} Menu;

Menu menu;

void SetIcon(void)
{
	const Image img = LoadImage("./res/logo.png");
	if (img.data != NULL)
	{
		SetWindowIcon(img);
		UnloadImage(img);
	}
}

void GetScoreFromFile(void)
{
	const char* filename = "./score.txt";

	// Default scores
	S_DefaultScore = 3;
	M_DefaultScore = 3;

	FILE* fp = fopen(filename, "r");

	if (fp != NULL)
	{
		char data[128] = {0}, *endptr;

		while (fgets(data, sizeof(data), fp) != NULL)
		{
			if (strstr(data, "Single Player Score") != NULL)
			{
				const char* eq_pos = strchr(data, '=');

				if (eq_pos != NULL)
					S_DefaultScore = strtol(eq_pos + 1, &endptr, 10);
				else
					fprintf(stderr, "Warning: Skipping malformed line: %s\n", data);
			}
			else if (strstr(data, "Multi Player Score") != NULL)
			{
				const char* eq_pos = strchr(data, '=');

				if (eq_pos != NULL)
					M_DefaultScore = strtol(eq_pos + 1, &endptr, 10);
				else
					fprintf(stderr, "Warning: Skipping malformed line: %s\n", data);
			}
		}
	}
	else
	{
		fp = fopen("./score.txt", "w");

		if (fp != NULL)
		{
			fprintf(fp, "Single Player Score = %d\n", S_DefaultScore);
			fprintf(fp, "Multi Player Score = %d\n", M_DefaultScore);
		}
		else
		{
			fprintf(stderr, "Error: Unable to create '%s'\n", filename);
		}
	}
	if (fp) fclose(fp);
}

void ModifyScoreFile(void)
{
	const char* filename = "./score.txt";
	FILE* fp = fopen(filename, "w");

	if (fp != NULL)
	{
		fprintf(fp, "Single Player Score = %d\n", S_DefaultScore);
		fprintf(fp, "Multi Player Score = %d\n", M_DefaultScore);
	}
}
