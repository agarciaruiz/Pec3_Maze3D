#include "map.h"

Map* Map::_map = NULL;

Map* Map::GetInstance()
{
    if (!_map)
        _map = new Map();
    return _map;
}

Map::Map(){}

void Map::ReadCubeData(float cubeSize, Image cubicmap)
{
    Color* cubicmapPixels = LoadImageColors(cubicmap);

    int mapWidth = cubicmap.width;
    int mapHeight = cubicmap.height;
    int maxTriangles = cubicmap.width * cubicmap.height * 12;
    // Iterating through every cube in the map
    for (int z = 0; z < mapHeight; z++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            // Texture style
            int texStyle = (int)cubicmapPixels[z * cubicmap.width + x].b;// 4 styles, TODO avoid hardcoding by managing atlas in class

            // Shape switches (props are nested in their relevant case)
            switch ((int)cubicmapPixels[z * cubicmap.width + x].r) 
            {
                case 0:
                {
                    //transitable
                    DrawHorizontal(texStyle, cube.size, x, z);
                    break;
                }
                case 128:
                {
                    //transitable-blocked. Prop may be applied (nested switch)
                    switch (cubicmapPixels[z * cubicmap.width + x].g) 
                    {
                        // Special cases, breaks or gotos
                        case 0:	//none
                            break;
                        case 1: // key
                            Map::PlaceProp(KEY, Vector3{ (float)x, 0, (float)z });
                            break;
                        case 2: // rock
                            Map::PlaceProp(ROCK, Vector3{ (float)x, 0, (float)z });
                            break;
                        case 3: // door
                            Map::PlaceProp(DOOR, Vector3{ (float)x, 0, (float)z });
                            break;
                    }
                }
                case 255:
                {
                    // Wall. Drawing only relevant faces.
                    //drawVerticalFaces(mapVertices, mapNormals, mapTexcoords, style, cube.size, x, z, cubicmap, cubicmapPixels);
                    break;
                }
            }
        }
    }
}

void Map::DrawHorizontal(int style, float w, int x, int z)
{
    // Draw bottom face
    std::vector<Vector3> bottomVertices;
    bottomVertices.push_back({ cube.size * (x + cube.left), cube.size * cube.down, cube.size * (z + cube.front) });
    bottomVertices.push_back({ cube.size * (x + cube.right), cube.size * cube.down, cube.size * (z + cube.front) });
    bottomVertices.push_back({ cube.size * (x + cube.left), cube.size * cube.down, cube.size * (z + cube.back) });
    bottomVertices.push_back({ cube.size * (x + cube.left), cube.size * cube.down, cube.size * (z + cube.back) });
    bottomVertices.push_back({ cube.size * (x + cube.right), cube.size * cube.down, cube.size * (z + cube.front) });
    bottomVertices.push_back({ cube.size * (x + cube.right), cube.size * cube.down, cube.size * (z + cube.back) });

    // normal 4, bottomTexUV
    DrawFace(bottomVertices, n4, uv.bottomTexUV, style);

    // Draw top face
    std::vector<Vector3> topVertices;
    topVertices.push_back({ cube.size * (x + cube.left), cube.size * cube.up, cube.size * (z + cube.front) });
    topVertices.push_back({ cube.size * (x + cube.left), cube.size * cube.up, cube.size * (z + cube.back) });
    topVertices.push_back({ cube.size * (x + cube.right), cube.size * cube.up, cube.size * (z + cube.front) });
    topVertices.push_back({ cube.size * (x + cube.right), cube.size * cube.up, cube.size * (z + cube.front) });
    topVertices.push_back({ cube.size * (x + cube.left), cube.size * cube.up, cube.size * (z + cube.front) });
    topVertices.push_back({ cube.size * (x + cube.right), cube.size * cube.up, cube.size * (z + cube.back) });
    // normal 3, topTexUV
    DrawFace(topVertices, n3, uv.topTexUV, style);
}

void Map::DrawFace(std::vector<Vector3>& vertices, Vector3& normal, RectangleF textureUV, int style)
{
    for (Vector3 vertex : vertices) {
        mapVertices.push_back(vertex);
    }

    for (int i = 0; i < 6; i++) {
        mapNormals.push_back(normal);
    }

    float vertical = textureUV.y + (float)(style % 2) / 2.0f;
    float horizontal = textureUV.x + (float)(style / 2) / 2.0f;

    mapTexCoords.push_back(Vector2{ horizontal, vertical });
    mapTexCoords.push_back(Vector2{ horizontal,	vertical + textureUV.height });
    mapTexCoords.push_back(Vector2{ horizontal + textureUV.width, vertical });
    mapTexCoords.push_back(Vector2{ horizontal + textureUV.width, vertical });
    mapTexCoords.push_back(Vector2{ horizontal,	vertical + textureUV.height });
    mapTexCoords.push_back(Vector2{ horizontal + textureUV.width, vertical + textureUV.height });
}

void Map::PlaceProp(PropType prop, Vector3 position)
{

}

void Map::Init()
{
    _imMap = LoadImage("resources/cubicmap.png");      // Load cubicmap image (RAM)
    _cubicMap = LoadTextureFromImage(_imMap);       // Convert image to texture to display (VRAM)

    Mesh mesh = GenMeshCubicmapV2(_imMap, Vector3{ 1.0f, 1.0f, 1.0f });
    _model = LoadModelFromMesh(mesh);

    _texture = LoadTexture("resources/cubemap_atlas.png");    // Load map texture
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;             // Set map diffuse texture

    _mapPixels = LoadImageColors(_imMap);

    _position = { 0.0f, 0.0f, 0.0f };  // Set model position
}

void Map::Draw() 
{
    DrawModel(_model, _position, 1.0f, WHITE);
}

void Map::Reset() 
{
    UnloadImage(_imMap);
    UnloadTexture(_cubicMap);        // Unload cubicmap texture
    UnloadTexture(_texture);         // Unload map texture
}

// Generate a cubes mesh from pixel data
// NOTE: Vertex data is uploaded to GPU
Mesh Map::GenMeshCubicmapV2(Image cubicmap, Vector3 cubeSize)
{
#define COLOR_EQUAL(col1, col2) ((col1.r == col2.r)&&(col1.g == col2.g)&&(col1.b == col2.b)&&(col1.a == col2.a))

    Mesh mesh = { 0 };

    Color* pixels = LoadImageColors(cubicmap);

    int mapWidth = cubicmap.width;
    int mapHeight = cubicmap.height;

    // NOTE: Max possible number of triangles numCubes*(12 triangles by cube)
    int maxTriangles = cubicmap.width * cubicmap.height * 12;

    int vCounter = 0;       // Used to count vertices
    int tcCounter = 0;      // Used to count texcoords
    int nCounter = 0;       // Used to count normals

    float w = cubeSize.x;
    float h = cubeSize.z;
    float h2 = cubeSize.y;

    Vector3* mapVertices = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));
    Vector2* mapTexcoords = (Vector2*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector2));
    Vector3* mapNormals = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));

    // Define the 6 normals of the cube, we will combine them accordingly later...

    RectangleF rightTexUV = { 0.0f, 0.0f, 0.5f, 0.5f };
    RectangleF leftTexUV = { 0.5f, 0.0f, 0.5f, 0.5f };
    RectangleF frontTexUV = { 0.0f, 0.0f, 0.5f, 0.5f };
    RectangleF backTexUV = { 0.5f, 0.0f, 0.5f, 0.5f };
    RectangleF topTexUV = { 0.0f, 0.5f, 0.5f, 0.5f };
    RectangleF bottomTexUV = { 0.5f, 0.5f, 0.5f, 0.5f };

    for (int z = 0; z < mapHeight; ++z)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            // Define the 8 vertex of the cube, we will combine them accordingly later...
            Vector3 v1 = { w * (x - 0.5f), h2, h * (z - 0.5f) };
            Vector3 v2 = { w * (x - 0.5f), h2, h * (z + 0.5f) };
            Vector3 v3 = { w * (x + 0.5f), h2, h * (z + 0.5f) };
            Vector3 v4 = { w * (x + 0.5f), h2, h * (z - 0.5f) };
            Vector3 v5 = { w * (x + 0.5f), 0, h * (z - 0.5f) };
            Vector3 v6 = { w * (x - 0.5f), 0, h * (z - 0.5f) };
            Vector3 v7 = { w * (x - 0.5f), 0, h * (z + 0.5f) };
            Vector3 v8 = { w * (x + 0.5f), 0, h * (z + 0.5f) };

            // We check pixel color to be WHITE -> draw full cube
            if (COLOR_EQUAL(pixels[z * cubicmap.width + x], WHITE))
            {
                // Define triangles and checking collateral cubes
                //------------------------------------------------

                // Define top triangles (2 tris, 6 vertex --> v1-v2-v3, v1-v3-v4)
                // WARNING: Not required for a WHITE cubes, created to allow seeing the map from outside
                mapVertices[vCounter] = v1;
                mapVertices[vCounter + 1] = v2;
                mapVertices[vCounter + 2] = v3;
                mapVertices[vCounter + 3] = v1;
                mapVertices[vCounter + 4] = v3;
                mapVertices[vCounter + 5] = v4;
                vCounter += 6;

                mapNormals[nCounter] = n3;
                mapNormals[nCounter + 1] = n3;
                mapNormals[nCounter + 2] = n3;
                mapNormals[nCounter + 3] = n3;
                mapNormals[nCounter + 4] = n3;
                mapNormals[nCounter + 5] = n3;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ topTexUV.x, topTexUV.y };
                mapTexcoords[tcCounter + 1] = Vector2{ topTexUV.x, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 2] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 3] = Vector2{ topTexUV.x, topTexUV.y };
                mapTexcoords[tcCounter + 4] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 5] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y };
                tcCounter += 6;

                // Define bottom triangles (2 tris, 6 vertex --> v6-v8-v7, v6-v5-v8)
                mapVertices[vCounter] = v6;
                mapVertices[vCounter + 1] = v8;
                mapVertices[vCounter + 2] = v7;
                mapVertices[vCounter + 3] = v6;
                mapVertices[vCounter + 4] = v5;
                mapVertices[vCounter + 5] = v8;
                vCounter += 6;

                mapNormals[nCounter] = n4;
                mapNormals[nCounter + 1] = n4;
                mapNormals[nCounter + 2] = n4;
                mapNormals[nCounter + 3] = n4;
                mapNormals[nCounter + 4] = n4;
                mapNormals[nCounter + 5] = n4;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
                mapTexcoords[tcCounter + 1] = Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 2] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 3] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
                mapTexcoords[tcCounter + 4] = Vector2{ bottomTexUV.x, bottomTexUV.y };
                mapTexcoords[tcCounter + 5] = Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
                tcCounter += 6;

                // Checking cube on bottom of current cube
                if (((z < cubicmap.height - 1) && COLOR_EQUAL(pixels[(z + 1) * cubicmap.width + x], BLACK)) || (z == cubicmap.height - 1))
                {
                    // Define front triangles (2 tris, 6 vertex) --> v2 v7 v3, v3 v7 v8
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v2;
                    mapVertices[vCounter + 1] = v7;
                    mapVertices[vCounter + 2] = v3;
                    mapVertices[vCounter + 3] = v3;
                    mapVertices[vCounter + 4] = v7;
                    mapVertices[vCounter + 5] = v8;
                    vCounter += 6;

                    mapNormals[nCounter] = n6;
                    mapNormals[nCounter + 1] = n6;
                    mapNormals[nCounter + 2] = n6;
                    mapNormals[nCounter + 3] = n6;
                    mapNormals[nCounter + 4] = n6;
                    mapNormals[nCounter + 5] = n6;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ frontTexUV.x, frontTexUV.y };
                    mapTexcoords[tcCounter + 1] = Vector2{ frontTexUV.x, frontTexUV.y + frontTexUV.height };
                    mapTexcoords[tcCounter + 2] = Vector2{ frontTexUV.x + frontTexUV.width, frontTexUV.y };
                    mapTexcoords[tcCounter + 3] = Vector2{ frontTexUV.x + frontTexUV.width, frontTexUV.y };
                    mapTexcoords[tcCounter + 4] = Vector2{ frontTexUV.x, frontTexUV.y + frontTexUV.height };
                    mapTexcoords[tcCounter + 5] = Vector2{ frontTexUV.x + frontTexUV.width, frontTexUV.y + frontTexUV.height };
                    tcCounter += 6;
                }

                // Checking cube on top of current cube
                if (((z > 0) && COLOR_EQUAL(pixels[(z - 1) * cubicmap.width + x], BLACK)) || (z == 0))
                {
                    // Define back triangles (2 tris, 6 vertex) --> v1 v5 v6, v1 v4 v5
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v1;
                    mapVertices[vCounter + 1] = v5;
                    mapVertices[vCounter + 2] = v6;
                    mapVertices[vCounter + 3] = v1;
                    mapVertices[vCounter + 4] = v4;
                    mapVertices[vCounter + 5] = v5;
                    vCounter += 6;

                    mapNormals[nCounter] = n5;
                    mapNormals[nCounter + 1] = n5;
                    mapNormals[nCounter + 2] = n5;
                    mapNormals[nCounter + 3] = n5;
                    mapNormals[nCounter + 4] = n5;
                    mapNormals[nCounter + 5] = n5;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ backTexUV.x + backTexUV.width, backTexUV.y };
                    mapTexcoords[tcCounter + 1] = Vector2{ backTexUV.x, backTexUV.y + backTexUV.height };
                    mapTexcoords[tcCounter + 2] = Vector2{ backTexUV.x + backTexUV.width, backTexUV.y + backTexUV.height };
                    mapTexcoords[tcCounter + 3] = Vector2{ backTexUV.x + backTexUV.width, backTexUV.y };
                    mapTexcoords[tcCounter + 4] = Vector2{ backTexUV.x, backTexUV.y };
                    mapTexcoords[tcCounter + 5] = Vector2{ backTexUV.x, backTexUV.y + backTexUV.height };
                    tcCounter += 6;
                }

                // Checking cube on right of current cube
                if (((x < cubicmap.width - 1) && COLOR_EQUAL(pixels[z * cubicmap.width + (x + 1)], BLACK)) || (x == cubicmap.width - 1))
                {
                    // Define right triangles (2 tris, 6 vertex) --> v3 v8 v4, v4 v8 v5
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v3;
                    mapVertices[vCounter + 1] = v8;
                    mapVertices[vCounter + 2] = v4;
                    mapVertices[vCounter + 3] = v4;
                    mapVertices[vCounter + 4] = v8;
                    mapVertices[vCounter + 5] = v5;
                    vCounter += 6;

                    mapNormals[nCounter] = n1;
                    mapNormals[nCounter + 1] = n1;
                    mapNormals[nCounter + 2] = n1;
                    mapNormals[nCounter + 3] = n1;
                    mapNormals[nCounter + 4] = n1;
                    mapNormals[nCounter + 5] = n1;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ rightTexUV.x, rightTexUV.y };
                    mapTexcoords[tcCounter + 1] = Vector2{ rightTexUV.x, rightTexUV.y + rightTexUV.height };
                    mapTexcoords[tcCounter + 2] = Vector2{ rightTexUV.x + rightTexUV.width, rightTexUV.y };
                    mapTexcoords[tcCounter + 3] = Vector2{ rightTexUV.x + rightTexUV.width, rightTexUV.y };
                    mapTexcoords[tcCounter + 4] = Vector2{ rightTexUV.x, rightTexUV.y + rightTexUV.height };
                    mapTexcoords[tcCounter + 5] = Vector2{ rightTexUV.x + rightTexUV.width, rightTexUV.y + rightTexUV.height };
                    tcCounter += 6;
                }

                // Checking cube on left of current cube
                if (((x > 0) && COLOR_EQUAL(pixels[z * cubicmap.width + (x - 1)], BLACK)) || (x == 0))
                {
                    // Define left triangles (2 tris, 6 vertex) --> v1 v7 v2, v1 v6 v7
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v1;
                    mapVertices[vCounter + 1] = v7;
                    mapVertices[vCounter + 2] = v2;
                    mapVertices[vCounter + 3] = v1;
                    mapVertices[vCounter + 4] = v6;
                    mapVertices[vCounter + 5] = v7;
                    vCounter += 6;

                    mapNormals[nCounter] = n2;
                    mapNormals[nCounter + 1] = n2;
                    mapNormals[nCounter + 2] = n2;
                    mapNormals[nCounter + 3] = n2;
                    mapNormals[nCounter + 4] = n2;
                    mapNormals[nCounter + 5] = n2;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ leftTexUV.x, leftTexUV.y };
                    mapTexcoords[tcCounter + 1] = Vector2{ leftTexUV.x + leftTexUV.width, leftTexUV.y + leftTexUV.height };
                    mapTexcoords[tcCounter + 2] = Vector2{ leftTexUV.x + leftTexUV.width, leftTexUV.y };
                    mapTexcoords[tcCounter + 3] = Vector2{ leftTexUV.x, leftTexUV.y };
                    mapTexcoords[tcCounter + 4] = Vector2{ leftTexUV.x, leftTexUV.y + leftTexUV.height };
                    mapTexcoords[tcCounter + 5] = Vector2{ leftTexUV.x + leftTexUV.width, leftTexUV.y + leftTexUV.height };
                    tcCounter += 6;
                }
            }
            // We check pixel color to be BLACK, we will only draw floor and roof
            else if (COLOR_EQUAL(pixels[z * cubicmap.width + x], BLACK))
            {
                // Define top triangles (2 tris, 6 vertex --> v1-v2-v3, v1-v3-v4)
                mapVertices[vCounter] = v1;
                mapVertices[vCounter + 1] = v3;
                mapVertices[vCounter + 2] = v2;
                mapVertices[vCounter + 3] = v1;
                mapVertices[vCounter + 4] = v4;
                mapVertices[vCounter + 5] = v3;
                vCounter += 6;

                mapNormals[nCounter] = n4;
                mapNormals[nCounter + 1] = n4;
                mapNormals[nCounter + 2] = n4;
                mapNormals[nCounter + 3] = n4;
                mapNormals[nCounter + 4] = n4;
                mapNormals[nCounter + 5] = n4;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ topTexUV.x, topTexUV.y };
                mapTexcoords[tcCounter + 1] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 2] = Vector2{ topTexUV.x, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 3] = Vector2{ topTexUV.x, topTexUV.y };
                mapTexcoords[tcCounter + 4] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y };
                mapTexcoords[tcCounter + 5] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
                tcCounter += 6;

                // Define bottom triangles (2 tris, 6 vertex --> v6-v8-v7, v6-v5-v8)
                mapVertices[vCounter] = v6;
                mapVertices[vCounter + 1] = v7;
                mapVertices[vCounter + 2] = v8;
                mapVertices[vCounter + 3] = v6;
                mapVertices[vCounter + 4] = v8;
                mapVertices[vCounter + 5] = v5;
                vCounter += 6;

                mapNormals[nCounter] = n3;
                mapNormals[nCounter + 1] = n3;
                mapNormals[nCounter + 2] = n3;
                mapNormals[nCounter + 3] = n3;
                mapNormals[nCounter + 4] = n3;
                mapNormals[nCounter + 5] = n3;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
                mapTexcoords[tcCounter + 1] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 2] = Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 3] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
                mapTexcoords[tcCounter + 4] = Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 5] = Vector2{ bottomTexUV.x, bottomTexUV.y };
                tcCounter += 6;
            }
        }
    }

    // Move data from mapVertices temp arays to vertices float array
    mesh.vertexCount = vCounter;
    mesh.triangleCount = vCounter / 3;

    mesh.vertices = (float*)RL_MALLOC(mesh.vertexCount * 3 * sizeof(float));
    mesh.normals = (float*)RL_MALLOC(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float*)RL_MALLOC(mesh.vertexCount * 2 * sizeof(float));
    mesh.colors = NULL;

    int fCounter = 0;

    // Move vertices data
    for (int i = 0; i < vCounter; i++)
    {
        mesh.vertices[fCounter] = mapVertices[i].x;
        mesh.vertices[fCounter + 1] = mapVertices[i].y;
        mesh.vertices[fCounter + 2] = mapVertices[i].z;
        fCounter += 3;
    }

    fCounter = 0;

    // Move normals data
    for (int i = 0; i < nCounter; i++)
    {
        mesh.normals[fCounter] = mapNormals[i].x;
        mesh.normals[fCounter + 1] = mapNormals[i].y;
        mesh.normals[fCounter + 2] = mapNormals[i].z;
        fCounter += 3;
    }

    fCounter = 0;

    // Move texcoords data
    for (int i = 0; i < tcCounter; i++)
    {
        mesh.texcoords[fCounter] = mapTexcoords[i].x;
        mesh.texcoords[fCounter + 1] = mapTexcoords[i].y;
        fCounter += 2;
    }
    
    RL_FREE(mapVertices);
    RL_FREE(mapNormals);
    RL_FREE(mapTexcoords);

    UnloadImageColors(pixels);   // Unload pixels color data

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}