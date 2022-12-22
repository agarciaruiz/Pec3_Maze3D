#include "player.hpp"

Player* Player::_player = NULL;

Player::Player(){}

// PRIVATE METHODS
void Player::Move() 
{
    _position.x += _dir.x * _moveSpeed;
    _position.y += _dir.y * _moveSpeed;
}

void Player::CheckCollisions(Vector3 oldCamPos) 
{
    _position = { _camera.position.x, _camera.position.z };
    _tile = Vector2{ _position.x - mapLoader->CurrentMap()->Position().x + 0.5f, _position.y - mapLoader->CurrentMap()->Position().z + 0.5f };

    if ((int)_tile.x < 0) _tile.x = 0;
    else if ((int)_tile.x >= mapLoader->CurrentMap()->MapImg().width) _tile.x = mapLoader->CurrentMap()->MapImg().width - 1;

    if ((int)_tile.y < 0) _tile.y = 0;
    else if ((int)_tile.y >= mapLoader->CurrentMap()->MapImg().height) _tile.y = mapLoader->CurrentMap()->MapImg().height - 1;

    for (int y = 0; y < mapLoader->CurrentMap()->CubicMap().height; y++)
    {
        for (int x = 0; x < mapLoader->CurrentMap()->CubicMap().width; x++)
        {
            if ((mapLoader->CurrentMap()->MapPixels()[y * mapLoader->CurrentMap()->CubicMap().width + x].r == 255) &&       // Collision: white pixel, only check R channel
                (CheckCollisionCircleRec(_position, _radius, Rectangle{ mapLoader->CurrentMap()->Position().x - 0.5f + x, mapLoader->CurrentMap()->Position().z - 0.5f + y, 1.0f, 1.0f })))
            {
                // Collision detected, reset camera position
                _camera.position = oldCamPos;
            }
        }
    }
}

void Player::CheckCollisionsWithProps(Vector3 oldCamPos) 
{
    for(Prop* p : mapLoader->CurrentMap()->Props())
    {
        if(!p->isEmpty && CheckCollisionCircleRec(_position, _radius, Rectangle{ p->position.x, p->position.z, 1.0f, 1.0f }))
        {
            if (p->type == PropType::KEY) 
            {
                printf("Key collected!");
                p->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color.a = 0;
                p->isEmpty = true;
                _hasKey = true;
            }
            else if (p->type == PropType::BRIDGE) 
            {
                if (!_hasKey)
                {
                    printf("Need a key to pass.");
                    _camera.position = oldCamPos;
                }
                else
                {
                    printf("Level completed!");
                    _levelCompleted = true;
                }
            }
            else if (p->type == PropType::LAVA) 
            {
                _isDead = true;
            }
        }
    }
}

// PUBLIC METHODS
Player* Player::GetInstance() 
{
    if (!_player)
        _player = new Player();
    return _player;
}

void Player::Init() 
{
    mapLoader = MapLoader::GetInstance();
    _soundManager = SoundManager::GetInstance();

    _camera.position = Vector3{ 5.0f, 0.5f, 1.0f };  // Camera position
    _camera.target = Vector3{ 0.0f, 1.8f, 0.0f };      // Camera looking at point
    _camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    _camera.fovy = 60.0f;                                // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    SetCameraMode(_camera, CAMERA_FIRST_PERSON);

    _position = Vector2{ _camera.position.x, _camera.position.z };
    _dir = Vector2{ 0, 0 };
    _tile = Vector2{ _position.x - mapLoader->CurrentMap()->Position().x + 0.5f, _position.y - mapLoader->CurrentMap()->Position().z + 0.5f};
    _radius = 0.1f;
    _moveSpeed = 2;
    _isDead = false;
    _hasKey = false;
    _levelCompleted = false;
}

void Player::Update()
{
    Vector3 oldCamPos = _camera.position;
    UpdateCamera(&_camera);
    CheckCollisions(oldCamPos);
    CheckCollisionsWithProps(oldCamPos);
}

void Player::Draw(){}

void Player::Reset()
{
    _isDead = false;
}