#include "game_manager.h"

GameManager* GameManager::_gameManager = NULL;


GameManager::GameManager() : currentLevel{1}
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

	win = false;
	lost = false;
	updateLevel = false;

	_levelTimer = 0;
	_levelTimeout = 60;

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

		_levelTimer += GetFrameTime();
		if(_levelTimer >= _levelTimeout || _player->IsDead())
		{
			lost = true;
		}

		if (_player->LevelCompleted())
		{
			updateLevel = true;
			currentLevel++;
			if (currentLevel > 3)
				win = true;
		}
	}
}

void GameManager::Draw()
{
	BeginMode3D(_player->Camera());
	_mapLoader->CurrentMap()->Draw();
	EndMode3D();

	DrawUI();
}

void GameManager::DrawUI()
{
	// PAUSED GAME
	if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);

	char* time = (char*)TextFormat("TIME: %is", ((int)_levelTimeout - (int)_levelTimer));
	DrawText(time, 20, 20, 40, WHITE);
}

void GameManager::Unload() 
{
	_player->Reset();
	_mapLoader->CurrentMap()->Reset();
}

void GameManager::Reset()
{
	currentLevel = 1;
}