#ifndef MAP_H
#define MAP_H
#include "raylib.h"
#include <stdlib.h>
#include <vector>

class Map {
private:
	// NOTE: We use texture rectangles to define different textures for top-bottom-front-back-right-left (6)
	typedef struct RectangleF {
		float x;
		float y;
		float width;
		float height;
	} RectangleF;

	typedef struct sCube {
		float size = 1.0f;
		float back = -0.5f;
		float front = 0.5f;
		float left = -0.5f;
		float right = 0.5f;
		float down = 0.0f;
		float up = 1.0f;
	} sCube;

	typedef struct sUV {
		RectangleF rightTexUV = { 0.0f, 0.25f, 0.25f, 0.25f };
		RectangleF leftTexUV = { 0.25f, 0.25f, 0.25f, 0.25f };
		RectangleF frontTexUV = { 0.0f, 0.25f, 0.25f, 0.25f };
		RectangleF backTexUV = { 0.25f, 0.25f, 0.25f, 0.25f };
		RectangleF topTexUV = { 0.0f, 0.0f, 0.25f, 0.25f };
		RectangleF bottomTexUV = { 0.25f, 0.0f, 0.25f, 0.25f };
	}sUV;

	Vector3 n1 = { 1.0f, 0.0f, 0.0f };
	Vector3 n2 = { -1.0f, 0.0f, 0.0f };
	Vector3 n3 = { 0.0f, 1.0f, 0.0f };
	Vector3 n4 = { 0.0f, -1.0f, 0.0f };
	Vector3 n5 = { 0.0f, 0.0f, -1.0f };
	Vector3 n6 = { 0.0f, 0.0f, 1.0f };

	static Map* _map;

	Texture2D _texture;
	Texture2D _cubicMap;
	Image _imMap;
	Model _model;
	Color* _mapPixels;

	Vector3 _position;
	std::vector<Vector3> mapVertices;
	std::vector<Vector3> mapNormals;
	std::vector<Vector2> mapTexCoords;
	sCube cube;
	sUV uv;
	enum PropType { NONE, KEY, ROCK, DOOR };

	Map::Map();
	void Map::ReadCubeData(float cubeSize, Image cubicmap);
	void Map::DrawHorizontal(int style, float w, int x, int z);
	void Map::DrawFace(std::vector<Vector3>& vertices, Vector3& normal, RectangleF textureUV, int style);
	void Map::PlaceProp(PropType prop, Vector3 position);
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

