#include "ending_screen.hpp"

void EndingScreen::Init() {
	framesCounter = 0;
	finishScreen = 0;

	SoundManager::GetInstance()->PlayMusic("resources/Audio/Music/GameOverTheme.mp3");
}

void EndingScreen::Update()
{
	framesCounter++;
	SoundManager::GetInstance()->UpdateMusic();

	// Press enter or tap to return to TITLE screen
	if (IsKeyPressed(KEY_ENTER))
		finishScreen = 2;

	if (IsKeyPressed(KEY_O)) {
		SoundManager::GetInstance()->UnloadMusic();
		finishScreen = 3;
	}
}

void EndingScreen::Draw()
{
	GameManager* gameManager = GameManager::GetInstance();

	if(gameManager->Win())
		DrawText("YOU WIN :)", SCR_WIDTH / 2 - MeasureText("YOU WIN :)", 50) / 2, GetScreenHeight() / 2 - 50, 50, YELLOW);
	else
		DrawText("YOU LOOSE :(", SCR_WIDTH / 2 - MeasureText("YOU LOOSE :(", 50) / 2, GetScreenHeight() / 2 - 50, 50, YELLOW);

	if ((framesCounter / 30) % 2 == 0)
	{
		DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);
		DrawText("PRESS [0] for INSTRUCTIONS", GetScreenWidth() / 2 - MeasureText("PRESS [0] for INSTRUCTIONS", 20) / 2, GetScreenHeight() / 2 + 40, 20, DARKGRAY);
	}
}