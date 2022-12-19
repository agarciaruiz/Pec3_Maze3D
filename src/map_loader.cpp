#include "map_loader.h"

MapLoader* MapLoader::_mapLoader = NULL;

MapLoader* MapLoader::GetInstance()
{
    if (!_mapLoader)
        _mapLoader = new MapLoader();
    return _mapLoader;
}

MapLoader::MapLoader() {}

void MapLoader::LoadMap(const char* mapFile, const char* cubemap)
{
    currentMap = new Map();
    currentMap->Init(mapFile, cubemap);
}