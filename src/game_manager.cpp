#include "game_manager.h"

GameManager* GameManager::_gameManager = NULL;


GameManager::GameManager() : currentLevel{0}
{}

GameManager* GameManager::GetInstance()
{
	if (!_gameManager)
		_gameManager = new GameManager();
	return _gameManager;
}

void GameManager::Init()
{
	gamePaused = false;

	_mapLoader = MapLoader::GetInstance();

	updateLevel = false;
	currentLevel++;
	switch (currentLevel) 
	{
	case 1:
		_mapLoader->LoadMap("resources/map1.png", "resources/cubemap_atlas_full.png");
		break;
	case 2:
		_mapLoader->LoadMap("resources/map2.png", "resources/cubemap_atlas_full.png");
		break;
	case 3: 
		_mapLoader->LoadMap("resources/map3.png", "resources/cubemap_atlas_full.png");
		break;
	}

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

		if (_player->LevelCompleted())
			updateLevel = true;
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
	_mapLoader->CurrentMap()->Reset();
}