#include "loading_screen.h"

void LoadingScreen::Init()
{
	finishScreen = 0;
	framesCounter = 0;

	textPos.x = GetScreenWidth() / 2;
	textPos.y = GetScreenHeight() / 2;
}

void LoadingScreen::Update() 
{
	framesCounter++;

	if (framesCounter > 180)
	{
		finishScreen = 4;
		framesCounter = 0;
	}
}

void LoadingScreen::Draw()
{
	if ((framesCounter / 30) % 2 == 0)
	{
		DrawText("LOADING...", SCR_WIDTH / 2 - MeasureText("LOADING...", 50) / 2, GetScreenHeight() / 2 - 50, 50, GRAY);
	}
}

void LoadingScreen::Unload() {}