#include "game_manager.h"

GameManager* GameManager::_gameManager = NULL;


GameManager::GameManager() {}

GameManager* GameManager::GetInstance()
{
	if (!_gameManager)
		_gameManager = new GameManager();
	return _gameManager;
}

void GameManager::Init()
{
	gamePaused = false;

	_map = Map::GetInstance();
	_map->Init();

	_player = Player::GetInstance();
	_player->Init();

	_soundManager = SoundManager::GetInstance();
	_soundManager->PlaySoundStream("resources/Audio/Sounds/GameStart.mp3");
}

void GameManager::Update()
{
	if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

	// Press enter or tap to change to ENDING screen
	if (!gamePaused)
	{
		// PLAYER UPDATE
		_player->Update();
	}
}

void GameManager::Draw()
{
	// UI DRAW
	DrawUI();
	
	// PLAYER DRAW
	_player->Draw();
}

void GameManager::DrawUI()
{
	// PAUSED GAME
	if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);

}

void GameManager::Unload() 
{
	_player->Reset();
	_map->Reset();
}