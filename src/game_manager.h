#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <time.h>
#include "raylib.h"
#include "player.hpp"
#include "sound_manager.h"

class GameManager {
private:

	// Singleton
	GameManager::GameManager();
	static GameManager* _gameManager;

	// Game settings
	bool gamePaused;
	Music _music;

	// Player settings
	Map* _map;
	Player* _player;
	SoundManager* _soundManager;
	
	// Private methods
	void GameManager::DrawUI();

public:

	static GameManager* GameManager::GetInstance();
	void GameManager::Init();
	void GameManager::Update();
	void GameManager::Draw();
	void GameManager::Unload();
};

#endif // !GAME_MANAGER_H
