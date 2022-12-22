#ifndef MAP_H
#define MAP_H
#define COLOR_EQUAL(col1, col2) ((col1.r == col2.r)&&(col1.g == col2.g)&&(col1.b == col2.b)&&(col1.a == col2.a))

#include "raylib.h"
#include "global.h"
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>

enum class PropType { LAVA, KEY, TURRET, BRIDGE };

typedef struct Prop {
	Model model;
	Texture2D texture;
	Vector3 position;
	float size;
	BoundingBox bb;
	PropType type;
	bool isEmpty;
}Prop;

class Map {
private:
	// NOTE: We use texture rectangles to define different textures for top-bottom-front-back-right-left (6)
	typedef struct RectangleF {
		float x;
		float y;
		float width;
		float height;
	} RectangleF;

	Texture2D _texture;
	Texture2D _cubicMap;
	Image _imMap;
	Model _model;
	Color* _pixels;

	Vector3* mapVertices;
	Vector3* mapNormals;
	Vector2* mapTexcoords;

	std::vector<Vector3> normals;
	std::vector<std::map<std::string, RectangleF>> uvs;

	std::vector<Prop*> props;

	Vector3 _position;
	bool _completed;

	void Map::BuildFullCube(std::vector<Vector3> vertices, std::map<std::string, RectangleF> uvs, int& vCounter, int& nCounter, int& tcCounter, int x, int z);
	void Map::BuildPartialCube(std::vector<Vector3> vertices, std::map<std::string, RectangleF> uvs, int& vCounter, int& nCounter, int& tcCounter);
	void Map::PlaceProp(PropType prop, Vector3 position);
public:
	Map::Map();

	Vector3 Position() const { return _position; }
	Image MapImg() const { return _imMap; }
	Texture2D CubicMap() const { return _cubicMap; }
	Color* MapPixels() const { return _pixels; }
	std::vector<Prop*> Props() const { return props; }
	void Map::Init(const char* mapFile, const char* cubemap);
	void Map::Draw();
	void Map::Reset();

	Mesh Map::GenMeshCubicmapV2(Vector3 cubeSize);
};

#endif // !MAP_H

