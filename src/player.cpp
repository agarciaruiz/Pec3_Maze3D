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
    map = Map::GetInstance();
    _soundManager = SoundManager::GetInstance();

    _camera.position = Vector3{ 5.0f, 0.5f, 1.0f };  // Camera position
    _camera.target = Vector3{ 0.0f, 1.8f, 0.0f };      // Camera looking at point
    _camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    _camera.fovy = 60.0f;                                // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    SetCameraMode(_camera, CAMERA_FIRST_PERSON);

    _position = Vector2{ _camera.position.x, _camera.position.z };
    _dir = Vector2{ 0, 0 };
    _tile = Vector2{ _position.x - map->Position().x + 0.5f, _position.y - map->Position().z + 0.5f };
    _radius = 0.1f;
    _moveSpeed = 2;
    _isDead = false;
}

void Player::Update()
{
    Vector3 oldCamPos = _camera.position;
    UpdateCamera(&_camera);
    //CheckCollisions(oldCamPos);
    _position = { _camera.position.x, _camera.position.z };
    _tile = Vector2{ _position.x - map->Position().x + 0.5f, _position.y - map->Position().z + 0.5f };

    if ((int)_tile.x < 0) _tile.x = 0;
    else if ((int)_tile.x >= map->MapImg().width) _tile.x = map->MapImg().width - 1;

    if ((int)_tile.y < 0) _tile.y = 0;
    else if ((int)_tile.y >= map->MapImg().height) _tile.y = map->MapImg().height - 1;

    for (int y = 0; y < map->CubicMap().height; y++)
    {
        for (int x = 0; x < map->CubicMap().width; x++)
        {
            if ((map->MapPixels()[y * map->CubicMap().width + x].r == 255) &&       // Collision: white pixel, only check R channel
                (CheckCollisionCircleRec(_position, _radius, Rectangle{ map->Position().x - 0.5f + x, map->Position().z - 0.5f + y, 1.0f, 1.0f })))
            {
                // Collision detected, reset camera position
                _camera.position = oldCamPos;
            }
        }
    }
}

void Player::Draw()
{
    BeginMode3D(_camera);
    map->Draw();
    EndMode3D();
}

void Player::Reset()
{
}