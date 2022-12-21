#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <time.h>
#include "raylib.h"
#include "map_loader.h"
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
	MapLoader* _mapLoader;
	Player* _player;
	SoundManager* _soundManager;
	
	// Private methods
	void GameManager::DrawUI();

	int currentLevel;
	bool updateLevel;

public:
	bool UpdateLevel() const { return updateLevel; }

	static GameManager* GameManager::GetInstance();
	void GameManager::Init();
	void GameManager::Update();
	void GameManager::Draw();
	void GameManager::Unload();
};

#endif // !GAME_MANAGER_H
