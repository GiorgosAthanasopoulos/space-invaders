#pragma once

#include "asset_manager.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include <raylib.h>
#include <vector>

class SpaceInvaders {
public:
  SpaceInvaders();
  ~SpaceInvaders();
  bool ShouldClose();
  void Update();
  void Draw();
  void Resize(Vector2 old, Vector2 neew);
  void Restart();

private:
  Vector2 winSize;
  Player player;
  std::vector<Bullet *> bullets;
  std::vector<Enemy> enemies;
  int score;
  bool ltr, lost, paused, won, frozen;
  AssetManager am;
  float enemiesShootTimer;

  void HandlePlayer();
  void HandleBullets();
  void HandleEnemies();
  void HandlePaused();
  void HandleLoss();
  void HandleWon();
  void HandleMusic();
  void MoveEnemies();
  void GenerateEnemies();
  void HandleEnemiesShooting();
  std::vector<Enemy> GetEnemiesWithLOSToPlayer();
  void HandleFrozen();

  void DrawEntities();
  void DrawUI();
  void DrawPaused();
  void DrawLost();
  void DrawWon();
};
