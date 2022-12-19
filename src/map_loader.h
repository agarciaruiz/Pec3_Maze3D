#ifndef MAP_LOADER_H
#define MAP_LOADER_H
#include "raylib.h"
#include "map.h"

class MapLoader {
private:
	static MapLoader* _mapLoader;

	MapLoader::MapLoader();

	Map* currentMap;
public:
	static MapLoader* MapLoader::GetInstance();
	Map* CurrentMap() const { return currentMap; }

	void MapLoader::LoadMap(const char* mapFile, const char* cubemap);
	void MapLoader::DrawMap();
};
#endif // !MAP_LOADER_H