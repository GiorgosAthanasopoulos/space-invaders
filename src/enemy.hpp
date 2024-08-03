#pragma once

#include "bullet.hpp"
#include <raylib.h>

class Enemy {
public:
  Enemy(Vector2 pos);
  ~Enemy();
  void Update();
  void Draw(Texture2D tex);
  void Resize(Vector2 old, Vector2 neew);
  Rectangle GetRec();
  Bullet *Shoot();
  void MoveX(float x);
  float GetX();

private:
  Vector2 pos, size, speed;
};
