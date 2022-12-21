#include "map.h"

Map::Map(){}


void Map::BuildFullCube(std::vector<Vector3> vertices, std::map<std::string, RectangleF> uvs, int& vCounter, int& nCounter, int& tcCounter, int x, int z)
{
    // Define triangles and checking collateral cubes
    //------------------------------------------------

    // Define top triangles (2 tris, 6 vertex --> vertices[0]-vertices[1]-vertices[2], vertices[0]-vertices[2]-vertices[3])
    // WARNING: Not required for a WHITE cubes, created to allow seeing the map from outside
    mapVertices[vCounter] = vertices[0];
    mapVertices[vCounter + 1] = vertices[1];
    mapVertices[vCounter + 2] = vertices[2];
    mapVertices[vCounter + 3] = vertices[0];
    mapVertices[vCounter + 4] = vertices[2];
    mapVertices[vCounter + 5] = vertices[3];
    vCounter += 6;

    mapNormals[nCounter] = normals[2];
    mapNormals[nCounter + 1] = normals[2];
    mapNormals[nCounter + 2] = normals[2];
    mapNormals[nCounter + 3] = normals[2];
    mapNormals[nCounter + 4] = normals[2];
    mapNormals[nCounter + 5] = normals[2];
    nCounter += 6;

    mapTexcoords[tcCounter] = Vector2{ uvs["top"].x, uvs["top"].y };
    mapTexcoords[tcCounter + 1] = Vector2{ uvs["top"].x, uvs["top"].y + uvs["top"].height };
    mapTexcoords[tcCounter + 2] = Vector2{ uvs["top"].x + uvs["top"].width, uvs["top"].y + uvs["top"].height };
    mapTexcoords[tcCounter + 3] = Vector2{ uvs["top"].x, uvs["top"].y };
    mapTexcoords[tcCounter + 4] = Vector2{ uvs["top"].x + uvs["top"].width, uvs["top"].y + uvs["top"].height };
    mapTexcoords[tcCounter + 5] = Vector2{ uvs["top"].x + uvs["top"].width, uvs["top"].y };
    tcCounter += 6;

    // Define bottom triangles (2 tris, 6 vertex --> vertices[5]-vertices[7]-vertices[6], vertices[5]-vertices[4]-vertices[7])
    mapVertices[vCounter] = vertices[5];
    mapVertices[vCounter + 1] = vertices[7];
    mapVertices[vCounter + 2] = vertices[6];
    mapVertices[vCounter + 3] = vertices[5];
    mapVertices[vCounter + 4] = vertices[4];
    mapVertices[vCounter + 5] = vertices[7];
    vCounter += 6;

    mapNormals[nCounter] = normals[3];
    mapNormals[nCounter + 1] = normals[3];
    mapNormals[nCounter + 2] = normals[3];
    mapNormals[nCounter + 3] = normals[3];
    mapNormals[nCounter + 4] = normals[3];
    mapNormals[nCounter + 5] = normals[3];
    nCounter += 6;

    mapTexcoords[tcCounter] = Vector2{ uvs["bottom"].x + uvs["bottom"].width, uvs["bottom"].y };
    mapTexcoords[tcCounter + 1] = Vector2{ uvs["bottom"].x, uvs["bottom"].y + uvs["bottom"].height };
    mapTexcoords[tcCounter + 2] = Vector2{ uvs["bottom"].x + uvs["bottom"].width, uvs["bottom"].y + uvs["bottom"].height };
    mapTexcoords[tcCounter + 3] = Vector2{ uvs["bottom"].x + uvs["bottom"].width, uvs["bottom"].y };
    mapTexcoords[tcCounter + 4] = Vector2{ uvs["bottom"].x, uvs["bottom"].y };
    mapTexcoords[tcCounter + 5] = Vector2{ uvs["bottom"].x, uvs["bottom"].y + uvs["bottom"].height };
    tcCounter += 6;

    // Define front triangles (2 tris, 6 vertex) --> vertices[1] vertices[6] vertices[2], vertices[2] vertices[6] vertices[7]
    // NOTE: Collateral occluded faces are not generated
    mapVertices[vCounter] = vertices[1];
    mapVertices[vCounter + 1] = vertices[6];
    mapVertices[vCounter + 2] = vertices[2];
    mapVertices[vCounter + 3] = vertices[2];
    mapVertices[vCounter + 4] = vertices[6];
    mapVertices[vCounter + 5] = vertices[7];
    vCounter += 6;

    mapNormals[nCounter] = normals[5];
    mapNormals[nCounter + 1] = normals[5];
    mapNormals[nCounter + 2] = normals[5];
    mapNormals[nCounter + 3] = normals[5];
    mapNormals[nCounter + 4] = normals[5];
    mapNormals[nCounter + 5] = normals[5];
    nCounter += 6;

    mapTexcoords[tcCounter] = Vector2{ uvs["front"].x, uvs["front"].y };
    mapTexcoords[tcCounter + 1] = Vector2{ uvs["front"].x, uvs["front"].y + uvs["front"].height };
    mapTexcoords[tcCounter + 2] = Vector2{ uvs["front"].x + uvs["front"].width, uvs["front"].y };
    mapTexcoords[tcCounter + 3] = Vector2{ uvs["front"].x + uvs["front"].width, uvs["front"].y };
    mapTexcoords[tcCounter + 4] = Vector2{ uvs["front"].x, uvs["front"].y + uvs["front"].height };
    mapTexcoords[tcCounter + 5] = Vector2{ uvs["front"].x + uvs["front"].width, uvs["front"].y + uvs["front"].height };
    tcCounter += 6;

        // Define back triangles (2 tris, 6 vertex) --> vertices[0] vertices[4] vertices[5], vertices[0] vertices[3] vertices[4]
        // NOTE: Collateral occluded faces are not generated
        mapVertices[vCounter] = vertices[0];
        mapVertices[vCounter + 1] = vertices[4];
        mapVertices[vCounter + 2] = vertices[5];
        mapVertices[vCounter + 3] = vertices[0];
        mapVertices[vCounter + 4] = vertices[3];
        mapVertices[vCounter + 5] = vertices[4];
        vCounter += 6;

        mapNormals[nCounter] = normals[4];
        mapNormals[nCounter + 1] = normals[4];
        mapNormals[nCounter + 2] = normals[4];
        mapNormals[nCounter + 3] = normals[4];
        mapNormals[nCounter + 4] = normals[4];
        mapNormals[nCounter + 5] = normals[4];
        nCounter += 6;

        mapTexcoords[tcCounter] = Vector2{ uvs["back"].x + uvs["back"].width, uvs["back"].y };
        mapTexcoords[tcCounter + 1] = Vector2{ uvs["back"].x, uvs["back"].y + uvs["back"].height };
        mapTexcoords[tcCounter + 2] = Vector2{ uvs["back"].x + uvs["back"].width, uvs["back"].y + uvs["back"].height };
        mapTexcoords[tcCounter + 3] = Vector2{ uvs["back"].x + uvs["back"].width, uvs["back"].y };
        mapTexcoords[tcCounter + 4] = Vector2{ uvs["back"].x, uvs["back"].y };
        mapTexcoords[tcCounter + 5] = Vector2{ uvs["back"].x, uvs["back"].y + uvs["back"].height };
        tcCounter += 6;
    

        // Define right triangles (2 tris, 6 vertex) --> vertices[2] vertices[7] vertices[3], vertices[3] vertices[7] vertices[4]
        // NOTE: Collateral occluded faces are not generated
        mapVertices[vCounter] = vertices[2];
        mapVertices[vCounter + 1] = vertices[7];
        mapVertices[vCounter + 2] = vertices[3];
        mapVertices[vCounter + 3] = vertices[3];
        mapVertices[vCounter + 4] = vertices[7];
        mapVertices[vCounter + 5] = vertices[4];
        vCounter += 6;

        mapNormals[nCounter] = normals[0];
        mapNormals[nCounter + 1] = normals[0];
        mapNormals[nCounter + 2] = normals[0];
        mapNormals[nCounter + 3] = normals[0];
        mapNormals[nCounter + 4] = normals[0];
        mapNormals[nCounter + 5] = normals[0];
        nCounter += 6;

        mapTexcoords[tcCounter] = Vector2{ uvs["right"].x, uvs["right"].y };
        mapTexcoords[tcCounter + 1] = Vector2{ uvs["right"].x, uvs["right"].y + uvs["right"].height };
        mapTexcoords[tcCounter + 2] = Vector2{ uvs["right"].x + uvs["right"].width, uvs["right"].y };
        mapTexcoords[tcCounter + 3] = Vector2{ uvs["right"].x + uvs["right"].width, uvs["right"].y };
        mapTexcoords[tcCounter + 4] = Vector2{ uvs["right"].x, uvs["right"].y + uvs["right"].height };
        mapTexcoords[tcCounter + 5] = Vector2{ uvs["right"].x + uvs["right"].width, uvs["right"].y + uvs["right"].height };
        tcCounter += 6;
    
        // Define left triangles (2 tris, 6 vertex) --> vertices[0] vertices[6] vertices[1], vertices[0] vertices[5] vertices[6]
        // NOTE: Collateral occluded faces are not generated
        mapVertices[vCounter] = vertices[0];
        mapVertices[vCounter + 1] = vertices[6];
        mapVertices[vCounter + 2] = vertices[1];
        mapVertices[vCounter + 3] = vertices[0];
        mapVertices[vCounter + 4] = vertices[5];
        mapVertices[vCounter + 5] = vertices[6];
        vCounter += 6;

        mapNormals[nCounter] = normals[1];
        mapNormals[nCounter + 1] = normals[1];
        mapNormals[nCounter + 2] = normals[1];
        mapNormals[nCounter + 3] = normals[1];
        mapNormals[nCounter + 4] = normals[1];
        mapNormals[nCounter + 5] = normals[1];
        nCounter += 6;

        mapTexcoords[tcCounter] = Vector2{ uvs["left"].x, uvs["left"].y };
        mapTexcoords[tcCounter + 1] = Vector2{ uvs["left"].x + uvs["left"].width, uvs["left"].y + uvs["left"].height };
        mapTexcoords[tcCounter + 2] = Vector2{ uvs["left"].x + uvs["left"].width, uvs["left"].y };
        mapTexcoords[tcCounter + 3] = Vector2{ uvs["left"].x, uvs["left"].y };
        mapTexcoords[tcCounter + 4] = Vector2{ uvs["left"].x, uvs["left"].y + uvs["left"].height };
        mapTexcoords[tcCounter + 5] = Vector2{ uvs["left"].x + uvs["left"].width, uvs["left"].y + uvs["left"].height };
        tcCounter += 6;
    
}

void Map::BuildPartialCube(std::vector<Vector3> vertices, std::map<std::string, RectangleF> uvs, int& vCounter, int& nCounter, int& tcCounter)
{
    // Define top triangles (2 tris, 6 vertex --> vertices[0]-vertices[1]-vertices[2], vertices[0]-vertices[2]-vertices[3])
    mapVertices[vCounter] = vertices[0];
    mapVertices[vCounter + 1] = vertices[2];
    mapVertices[vCounter + 2] = vertices[1];
    mapVertices[vCounter + 3] = vertices[0];
    mapVertices[vCounter + 4] = vertices[3];
    mapVertices[vCounter + 5] = vertices[2];
    vCounter += 6;

    mapNormals[nCounter] = normals[3];
    mapNormals[nCounter + 1] = normals[3];
    mapNormals[nCounter + 2] = normals[3];
    mapNormals[nCounter + 3] = normals[3];
    mapNormals[nCounter + 4] = normals[3];
    mapNormals[nCounter + 5] = normals[3];
    nCounter += 6;

    mapTexcoords[tcCounter] = Vector2{ uvs["top"].x, uvs["top"].y };
    mapTexcoords[tcCounter + 1] = Vector2{ uvs["top"].x + uvs["top"].width, uvs["top"].y + uvs["top"].height };
    mapTexcoords[tcCounter + 2] = Vector2{ uvs["top"].x, uvs["top"].y + uvs["top"].height };
    mapTexcoords[tcCounter + 3] = Vector2{ uvs["top"].x, uvs["top"].y };
    mapTexcoords[tcCounter + 4] = Vector2{ uvs["top"].x + uvs["top"].width, uvs["top"].y };
    mapTexcoords[tcCounter + 5] = Vector2{ uvs["top"].x + uvs["top"].width, uvs["top"].y + uvs["top"].height };
    tcCounter += 6;

    // Define bottom triangles (2 tris, 6 vertex --> vertices[5]-vertices[7]-vertices[6], vertices[5]-vertices[4]-vertices[7])
    mapVertices[vCounter] = vertices[5];
    mapVertices[vCounter + 1] = vertices[6];
    mapVertices[vCounter + 2] = vertices[7];
    mapVertices[vCounter + 3] = vertices[5];
    mapVertices[vCounter + 4] = vertices[7];
    mapVertices[vCounter + 5] = vertices[4];
    vCounter += 6;

    mapNormals[nCounter] = normals[2];
    mapNormals[nCounter + 1] = normals[2];
    mapNormals[nCounter + 2] = normals[2];
    mapNormals[nCounter + 3] = normals[2];
    mapNormals[nCounter + 4] = normals[2];
    mapNormals[nCounter + 5] = normals[2];
    nCounter += 6;

    mapTexcoords[tcCounter] = Vector2{ uvs["bottom"].x + uvs["bottom"].width, uvs["bottom"].y };
    mapTexcoords[tcCounter + 1] = Vector2{ uvs["bottom"].x + uvs["bottom"].width, uvs["bottom"].y + uvs["bottom"].height };
    mapTexcoords[tcCounter + 2] = Vector2{ uvs["bottom"].x, uvs["bottom"].y + uvs["bottom"].height };
    mapTexcoords[tcCounter + 3] = Vector2{ uvs["bottom"].x + uvs["bottom"].width, uvs["bottom"].y };
    mapTexcoords[tcCounter + 4] = Vector2{ uvs["bottom"].x, uvs["bottom"].y + uvs["bottom"].height };
    mapTexcoords[tcCounter + 5] = Vector2{ uvs["bottom"].x, uvs["bottom"].y };
    tcCounter += 6;
}


void Map::PlaceProp(PropType prop, Vector3 position)
{
    Prop* p = new Prop();
    Texture2D texture;
    switch (prop) 
    {
        case LAVA:
            p->size = 0.05f;
            p->type = LAVA;
            break;
        case KEY:
            p->model = LoadModel("resources/models/obj/cube.obj");                 // Load model
            texture = LoadTexture("resources/models/obj/cube_diffuse.png"); // Load model texture
            p->size = 0.02f;
            p->type = KEY;
            break;
        case TURRET:
            p->model = LoadModel("resources/models/obj/turret.obj");                 // Load model
            texture = LoadTexture("resources/models/obj/turret_diffuse.png"); // Load model texture
            p->size = 0.02f;
            p->type = TURRET;
            break;
        case BRIDGE:
            p->model = LoadModel("resources/models/obj/bridge.obj");                 // Load model
            texture = LoadTexture("resources/models/obj/bridge_diffuse.png"); // Load model texture            
            p->size = 0.1;
            p->type = BRIDGE;
            break;
    }

    if(p->type != LAVA)
    {
        p->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;            // Set map diffuse texture
        p->bb = GetMeshBoundingBox(p->model.meshes[0]);   // Set model bounds
    }
    p->position = position;
    p->isEmpty = false;
    props.push_back(p);
}

void Map::Init(const char* mapFile, const char* cubemap)
{
    _imMap = LoadImage(mapFile);      // Load cubicmap image (RAM)
    _cubicMap = LoadTextureFromImage(_imMap);       // Convert image to texture to display (VRAM)

    Mesh mesh = GenMeshCubicmapV2(Vector3{ 1.0f, 1.0f, 1.0f });
    _model = LoadModelFromMesh(mesh);

    _texture = LoadTexture(cubemap);    // Load map texture
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;             // Set map diffuse texture

    _position = { 0.0f, 0.0f, 0.0f };  // Set model position
    _completed = false;
}

void Map::Draw() 
{
    DrawModel(_model, _position, 1.0f, WHITE);

    for (Prop* p : props) 
    {
        if(!p->isEmpty)
            DrawModel(p->model, p->position, p->size, WHITE);
    }
}

void Map::Reset() 
{
    UnloadImageColors(_pixels);
    UnloadImage(_imMap);
    UnloadTexture(_cubicMap);        // Unload cubicmap texture
    UnloadTexture(_texture);         // Unload map texture
    UnloadModel(_model);

    props.clear();
    normals.clear();
    uvs.clear();
}

// Generate a cubes mesh from pixel data
// NOTE: Vertex data is uploaded to GPU
Mesh Map::GenMeshCubicmapV2(Vector3 cubeSize)
{
    Mesh mesh = { 0 };

    _pixels = LoadImageColors(_imMap);

    int mapWidth = _imMap.width;
    int mapHeight = _imMap.height;

    // NOTE: Max possible number of triangles numCubes*(12 triangles by cube)
    int maxTriangles = _imMap.width * _imMap.height * 12;

    int vCounter = 0;       // Used to count vertices
    int tcCounter = 0;      // Used to count texcoords
    int nCounter = 0;       // Used to count normals

    float w = cubeSize.x;
    float h = cubeSize.z;
    float h2 = cubeSize.y;

    mapVertices = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));
    mapTexcoords = (Vector2*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector2));
    mapNormals = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));

    // Define the 6 normals of the cube, we will combine them accordingly later...
    normals.push_back({1.0f, 0.0f, 0.0f});
    normals.push_back({ -1.0f, 0.0f, 0.0f });
    normals.push_back({ 0.0f, 1.0f, 0.0f });
    normals.push_back({ 0.0f, -1.0f, 0.0f });
    normals.push_back({ 0.0f, 0.0f, -1.0f });
    normals.push_back({ 0.0f, 0.0f, 1.0f });

    for (int i = 0; i < 2; i++) 
    {
        for (int j = 0; j < 2; j++) 
        {
            std::map<std::string, RectangleF> uv;
            uv.insert({ "right", {j * 0.5f, i * 0.5f, 0.25f, 0.25f} });
            uv.insert({ "left", {0.25f + j * 0.5f, i * 0.5f, 0.25f, 0.25f} });
            uv.insert({ "front", {j * 0.5f, i * 0.5f, 0.25f, 0.25f} });
            uv.insert({ "back", {0.25f + j * 0.5f, i * 0.5f, 0.25f, 0.25f} });
            uv.insert({ "top", {j * 0.5f, 0.25f + i * 0.5f, 0.25f, 0.25f} });
            uv.insert({ "bottom", {0.25f + j * 0.5f, 0.25f + i * 0.5f, 0.25f, 0.25f} });
            uvs.push_back(uv);
        }
    }

    for (int z = 0; z < mapHeight; ++z)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            std::vector<Vector3> vertices;
            // Define the 8 vertex of the cube, we will combine them accordingly later...
            vertices.push_back({ w * (x - 0.5f), h2, h * (z - 0.5f) });     // vertices[0]
            vertices.push_back({ w * (x - 0.5f), h2, h * (z + 0.5f) });     // vertices[1]
            vertices.push_back({ w * (x + 0.5f), h2, h * (z + 0.5f) });     // vertices[2]
            vertices.push_back({ w * (x + 0.5f), h2, h * (z - 0.5f) });     // vertices[3]
            vertices.push_back({ w * (x + 0.5f), 0, h * (z - 0.5f) });      // vertices[4]
            vertices.push_back({ w * (x - 0.5f), 0, h * (z - 0.5f) });      // vertices[5]
            vertices.push_back({ w * (x - 0.5f), 0, h * (z + 0.5f) });      // vertices[6]
            vertices.push_back({ w * (x + 0.5f), 0, h * (z + 0.5f) });      // vertices[7]

            std::map<std::string, RectangleF> uv;
            switch (_pixels[z * _imMap.width + x].b)
            {
                case 0:
                    uv = uvs[0];
                    break;
                case 1:
                    uv = uvs[1];
                    break;
                case 2:
                    uv = uvs[2];
                    break;
                case 3:
                    uv = uvs[3];
                    break;
            }

            // We check pixel color to be WHITE -> draw full cube
            if (_pixels[z * _imMap.width + x].r == 255)
            {
                BuildFullCube(vertices, uv, vCounter, nCounter, tcCounter, x, z);
            }
            // We check pixel color to be BLACK, we will only draw floor and roof
            else if (_pixels[z * _imMap.width + x].r == 0)
            {
                BuildPartialCube(vertices, uv, vCounter, nCounter, tcCounter);
            }
            else if(_pixels[z * _imMap.width + x].r == 128)
            {
                BuildPartialCube(vertices, uv, vCounter, nCounter, tcCounter);
                switch(_pixels[z * _imMap.width + x].g)
                {
                    case 0:
                        PlaceProp(LAVA, { (float)x, 0, (float)z });
                        break;
                    case 1: // TURRET
                        PlaceProp(TURRET, { (float)x, 0, (float)z });
                        break;
                    case 2: // KEY
                        PlaceProp(KEY, { (float)x, 0, (float)z });
                        break;
                    case 3: // BRIDGE
                        PlaceProp(BRIDGE, { (float)x, 0, (float)z });
                        break;
                }
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

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}