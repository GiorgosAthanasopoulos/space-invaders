#pragma once

#include <raylib.h>

class AssetManager {
public:
  Texture2D player, enemy, player_bullet, enemy_bullet;
  Texture2D bg, lostTex, wonTex;
  Music bgm;
  Sound shot, receivedDamage, kill, won, lost;

  AssetManager();
  ~AssetManager();
};
