#include "player.hpp"
#include "bullet.hpp"
#include "config.hpp"
#include "entity_id.hpp"
#include "util.hpp"
#include <optional>
#include <raylib.h>

Player::Player() {
  Reset();
  Resize(GetWindowSize(), GetWindowSize());
}

Player::~Player() {}

std::optional<Bullet *> Player::Update() {
  Vector2 vel = {0, 0};

  if (IsKeyDown(KEY_PLAYER_MOVE_LEFT) && IsKeyDown(KEY_PLAYER_MOVE_RIGHT)) {
    vel.x = 0;
  } else if (IsKeyDown(KEY_PLAYER_MOVE_LEFT)) {
    vel.x = -speed.x;
  } else if (IsKeyDown(KEY_PLAYER_MOVE_RIGHT)) {
    vel.x = speed.x;
  }

  float frameTime = GetFrameTime();
  shootTimer -= frameTime;
  if (IsKeyPressed(KEY_PLAYER_SHOOT) && shootTimer <= 0.0f) {
    shootTimer = SHOOT_INTERVAL;
    return new Bullet({pos.x + size.x / 4, pos.y + size.y / 2}, 0,
                      EntityId::PLAYER);
  }

  pos += vel * frameTime;
  pos = WorldBoundaryCheck(pos, size);

  return {};
}

void Player::Draw(Texture2D tex) {
  // DrawRectangleV(pos, size, PLAYER_COLOR);
  DrawTexturePro(tex, {0, 0, (float)tex.width, (float)tex.height}, GetRec(),
                 {0, 0}, 0, WHITE);
  if (DEBUG) {
    DrawRectangleLinesEx(GetRec(), DEBUG_HTBX_THICK, DEBUG_HTBX_COLOR);
  }
}

void Player::Resize(Vector2 old, Vector2 neew) {
  size = CalculateSize(PLAYER_SIZE_RATIO);
  speed = CalculateSpeed(PLAYER_SPEED_RATIO);
  pos = MaintainPosAfterResize(old, neew, pos);
}

Rectangle Player::GetRec() { return {pos.x, pos.y, size.x, size.y}; }

void Player::Reset() {
  pos = {GetWindowWidth() / 2 - size.x / 2, GetWindowHeight() - 2 * size.y};
  shootTimer = 0;
  health = 3; // MAX_HEALTH
}

void Player::LoseHealth() { health--; }

int Player::GetHealth() { return health; }
