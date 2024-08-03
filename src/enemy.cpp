#include "enemy.hpp"
#include "bullet.hpp"
#include "config.hpp"
#include "entity_id.hpp"
#include "util.hpp"
#include <raylib.h>

Enemy::Enemy(Vector2 pos) {
  this->pos = pos;
  Resize(GetWindowSize(), GetWindowSize());
}

Enemy::~Enemy() {}

void Enemy::Update() {}

void Enemy::Draw(Texture2D tex) {
  // DrawRectangleV(pos, size, ENEMY_COLOR);
  DrawTexturePro(tex, {0, 0, (float)tex.width / 2, (float)tex.height},
                 {pos.x + (float)tex.width / 3, pos.y, size.x, size.y}, {0, 0},
                 0, WHITE);
  if (DEBUG) {
    DrawRectangleLinesEx(GetRec(), DEBUG_HTBX_THICK, DEBUG_HTBX_COLOR);
  }
}

void Enemy::Resize(Vector2 old, Vector2 neew) {
  speed = CalculateSpeed(ENEMY_SPEED_RATIO);
  size = CalculateSize(ENEMY_SIZE_RATIO);
  pos = MaintainPosAfterResize(old, neew, pos);
}

Rectangle Enemy::GetRec() { return {pos.x, pos.y, size.x, size.y}; }

Bullet *Enemy::Shoot() { return new Bullet(pos, 180, EntityId::ENEMY); }

void Enemy::MoveX(float x) { pos.x += x; }

float Enemy::GetX() { return pos.x; }
