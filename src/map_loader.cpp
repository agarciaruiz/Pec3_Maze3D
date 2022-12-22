#include "map_loader.h"

MapLoader* MapLoader::_mapLoader = NULL;

MapLoader* MapLoader::GetInstance()
{
    if (!_mapLoader)
        _mapLoader = new MapLoader();
    return _mapLoader;
}

MapLoader::MapLoader() 
{
    currentMap = new Map();
}

void MapLoader::LoadMap(const char* mapFile, const char* cubemap)
{
    currentMap->Init(mapFile, cubemap);
}