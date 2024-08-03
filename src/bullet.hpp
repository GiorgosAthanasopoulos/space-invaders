#pragma once

#include "entity_id.hpp"
#include <raylib.h>

class Bullet {
public:
  Bullet(Vector2 pos, float angle, EntityId eid);
  ~Bullet();
  void Update();
  void Draw(Texture2D tex);
  void Resize(Vector2 old, Vector2 neew);
  Rectangle GetRec();
  EntityId GetEid();

private:
  Vector2 pos, speed, size;
  float angle;
  EntityId eid;
};
