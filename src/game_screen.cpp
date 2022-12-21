#include "game_screen.hpp"

void GameScreen::Init()
{
	_gameManager = GameManager::GetInstance();
	_gameManager->Init();
	framesCounter = 0;
	finishScreen = 0;

}

void GameScreen::Update()
{
	_gameManager->Update();
	// Game end condition
	if (_gameManager->Win())
	{
		_gameManager->Reset();
		finishScreen = 5;
	}
	else if (_gameManager->UpdateLevel() )
		finishScreen = 6;
}

void GameScreen::Draw()
{
	_gameManager->Draw();
}

void GameScreen::Unload()
{
	_gameManager->Unload();
}