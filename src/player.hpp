#pragma once

#include "bullet.hpp"
#include <optional>
#include <raylib.h>

class Player {
public:
  Player();
  ~Player();
  std::optional<Bullet *> Update();
  void Draw(Texture2D tex);
  void Resize(Vector2 old, Vector2 neew);
  Rectangle GetRec();
  void Reset();

  void LoseHealth();
  int GetHealth();

private:
  Vector2 pos, size, speed;
  float shootTimer;
  int health;
};
