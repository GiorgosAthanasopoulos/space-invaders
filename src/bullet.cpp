#include "bullet.hpp"
#include "config.hpp"
#include "entity_id.hpp"
#include "util.hpp"
#include <cmath>
#include <raylib.h>

Bullet::Bullet(Vector2 pos, float angle, EntityId eid) {
  this->eid = eid;
  this->pos = pos;
  this->angle = angle;
  Resize(GetWindowSize(), GetWindowSize());
}

Bullet::~Bullet() {}

void Bullet::Update() {
  Vector2 vel;
  vel.x = std::sin(DEG2RAD * angle) * speed.x;
  vel.y = std::cos(DEG2RAD * angle) * -speed.y;
  pos += vel * GetFrameTime();
}

void Bullet::Draw(Texture2D tex) {
  // DrawRectangleV(pos, size, BULLET_COLOR);
  DrawTexturePro(tex, {0, 0, (float)tex.width, (float)tex.height}, GetRec(),
                 {0, 0}, 0, WHITE);
  if (DEBUG) {
    DrawRectangleLinesEx(GetRec(), DEBUG_HTBX_THICK, DEBUG_HTBX_COLOR);
  }
}

void Bullet::Resize(Vector2 old, Vector2 neew) {
  speed = CalculateSpeed(BULLET_SPEED_RATIO);
  size = CalculateSize(BULLET_SIZE_RATIO);
  pos = MaintainPosAfterResize(old, neew, pos);
}

Rectangle Bullet::GetRec() { return {pos.x, pos.y, size.x, size.y}; }

EntityId Bullet::GetEid() { return eid; }
