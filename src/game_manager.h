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
	bool win;
	bool lost;

	float _levelTimer;
	float _levelTimeout;

public:
	bool UpdateLevel() const { return updateLevel; }
	bool Win() const { return win; }
	bool Lost() const { return lost; }

	static GameManager* GameManager::GetInstance();
	void GameManager::Init();
	void GameManager::Update();
	void GameManager::Draw();
	void GameManager::Unload();
	void GameManager::Reset();
};

#endif // !GAME_MANAGER_H
