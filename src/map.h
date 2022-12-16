#ifndef MAP_H
#define MAP_H
#include "raylib.h"
#include <stdlib.h>

class Map {
private:
	static Map* _map;

	Texture2D _texture;
	Texture2D _cubicMap;
	Image _imMap;
	Model _model;
	Color* _mapPixels;

	Vector3 _position;

	Map::Map();
public:
	static Map* Map::GetInstance();

	Vector3 Position() const { return _position; }
	Image MapImg() const { return _imMap; }
	Texture2D CubicMap() const { return _cubicMap; }
	Color* MapPixels() const { return _mapPixels; }
	void Map::Init();
	void Map::Draw();
	void Map::Reset();

	Mesh Map::GenMeshCubicmapV2(Image cubicmap, Vector3 cubeSize);
};

#endif // !MAP_H

