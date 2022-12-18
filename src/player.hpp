#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "raylib.h"
#include "global.h"
#include "screen.hpp"
#include "sound_manager.h"
#include "map.h"

class Player {
private:
    static Player* _player;

    Map* map;

    Camera3D _camera;

    Vector2 _position;
    Vector2 _dir;
    Vector2 _tile;
    float _radius;
    float _moveSpeed;
    bool _isDead;

    SoundManager* _soundManager;

    Player::Player();
    void Player::Move();
    void Player::CheckCollisions(Vector3 oldCamPos);
    void Player::CheckCollisionsWithProps();

public:

    static Player* Player::GetInstance();
    void Player::Init();
    void Player::Update();
    void Player::Draw();
    void Player::Reset();
};
#endif