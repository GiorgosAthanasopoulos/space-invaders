#include "space_invaders.hpp"
#include "config.hpp"
#include "entity_id.hpp"
#include "util.hpp"
#include <raylib.h>
#include <sstream>

SpaceInvaders::SpaceInvaders() {
  winSize = GetWindowSize();
  Restart();
  PlayMusicStream(am.bgm);
}

SpaceInvaders::~SpaceInvaders() {
  for (size_t i = 0; i < bullets.size(); ++i) {
    delete bullets[i];
  }
}

bool SpaceInvaders::ShouldClose() { return WindowShouldClose(); }

void SpaceInvaders::Update() {
  HandleMusic();
  HandlePaused();
  HandleFrozen();
  if (paused) {
    return;
  }
  if (frozen) {
    return;
  }
  if (lost) {
    HandleLoss();
    return;
  }
  if (won) {
    HandleWon();
    return;
  }
  HandlePlayer();
  HandleBullets();
  HandleEnemies();
}

void SpaceInvaders::Draw() {
  if (paused) {
    DrawPaused();
    return;
  }
  if (lost) {
    DrawLost();
    return;
  }
  if (won) {
    DrawWon();
    return;
  }
  DrawEntities();
  DrawUI();
}

void SpaceInvaders::Resize(Vector2 old, Vector2 neew) {
  player.Resize(old, neew);
  for (size_t i = 0; i < bullets.size(); ++i) {
    bullets[i]->Resize(old, neew);
  }
  for (size_t i = 0; i < enemies.size(); ++i) {
    enemies[i].Resize(old, neew);
  }
  winSize = neew;
}

void SpaceInvaders::Restart() {
  player.Reset();
  for (size_t i = 0; i < bullets.size(); ++i) {
    delete bullets[i];
  }
  bullets.clear();
  enemies.clear();
  score = 0;
  ltr = true;
  lost = false;
  won = false;
  paused = false;
  enemiesShootTimer = ENEMIES_SHOOT_TIMER;
  GenerateEnemies();
  frozen = false;
}

void SpaceInvaders::HandlePlayer() {
  if (auto b = player.Update()) {
    PlaySound(am.shot);
    bullets.push_back(*b);
  }
}

void SpaceInvaders::HandleBullets() {
  for (size_t i = 0; i < bullets.size(); ++i) {
    bullets[i]->Update();

    Rectangle bulletRec = bullets[i]->GetRec();
    if (bulletRec.y < 0 || bulletRec.y > winSize.y) {
      delete bullets[i];
      bullets.erase(bullets.begin() + i);
      continue;
    }

    for (size_t j = 0; j < enemies.size(); ++j) {
      if (CheckCollisionRecs(enemies[j].GetRec(), bulletRec) &&
          bullets[i]->GetEid() != EntityId::ENEMY) {
        enemies.erase(enemies.begin() + j);
        score += SCORE_INTERVAL;

        if (enemies.size() == 0) {
          won = true;
          StopMusicStream(am.bgm);
          PlaySound(am.won);
        } else {
          PlaySound(am.kill);
        }

        delete bullets[i];
        bullets.erase(bullets.begin() + i);
        break;
      }
    }

    if (CheckCollisionRecs(bulletRec, player.GetRec()) &&
        bullets[i]->GetEid() != EntityId::PLAYER) {
      player.LoseHealth();

      if (player.GetHealth() == 0) {
        StopMusicStream(am.bgm);
        PlaySound(am.lost);
        lost = true;
      } else {
        PlaySound(am.receivedDamage);
      }

      delete bullets[i];
      bullets.erase(bullets.begin() + i);
      continue;
    }
  }
}

void SpaceInvaders::HandleEnemies() {
  for (size_t i = 0; i < enemies.size(); ++i) {
    enemies[i].Update();
  }

  MoveEnemies();
  HandleEnemiesShooting();
}

void SpaceInvaders::DrawEntities() {
  DrawTexturePro(am.bg, {0, 0, (float)am.bg.width, (float)am.bg.height},
                 {0, 0, winSize.x, winSize.y}, {0, 0}, 0, WHITE);
  player.Draw(am.player);
  for (size_t i = 0; i < bullets.size(); ++i) {
    bullets[i]->Draw(bullets[i]->GetEid() == EntityId::PLAYER
                         ? am.player_bullet
                         : am.enemy_bullet);
  }
  for (size_t i = 0; i < enemies.size(); ++i) {
    enemies[i].Draw(am.enemy);
  }
}

void SpaceInvaders::DrawUI() {
  std::ostringstream ss;
  ss << "Score: " << score;
  std::string s = ss.str();
  const char *t = s.data();
  Vector2 maxSize = GetWindowSize() / 6;
  Vector2 tSize = AssertTextFitsInViewport(t, FONT_SIZE, maxSize);
  DrawText(t, SCORE_TEXT_PADDING_X, SCORE_TEXT_PADDING_Y, tSize.y,
           SCORE_TEXT_COLOR);

  const char *lives[] = {"Lives: ", "|", player.GetHealth() >= 2 ? "|" : "",
                         player.GetHealth() >= 3 ? "|" : ""};
  const char *t2 = TextJoin(lives, 4, " ");
  Vector2 t2Size = AssertTextFitsInViewport(t2, FONT_SIZE, maxSize);
  DrawText(t2, winSize.x - t2Size.x - SCORE_TEXT_PADDING_X,
           SCORE_TEXT_PADDING_Y, t2Size.y, SCORE_TEXT_COLOR);
}

void SpaceInvaders::HandlePaused() {
  if (IsKeyPressed(KEY_PAUSE_GAME)) {
    paused = !paused;
  }
}

void SpaceInvaders::HandleLoss() {
  if (IsKeyPressed(KEY_RESTART)) {
    Restart();
  }
}

void SpaceInvaders::HandleWon() {
  if (IsKeyPressed(KEY_RESTART)) {
    Restart();
  }
}

void SpaceInvaders::HandleMusic() {
  if (IsKeyPressed(KEY_MUTE)) {
    if (IsMusicStreamPlaying(am.bgm)) {
      PauseMusicStream(am.bgm);
    } else {
      ResumeMusicStream(am.bgm);
    }
  }
  UpdateMusicStream(am.bgm);
}

void SpaceInvaders::DrawPaused() {
  const char *text = "Paused";
  Vector2 textSize =
      AssertTextFitsInViewport(text, LARGE_FONT_SIZE, GetWindowSize() / 2);
  DrawText(text, winSize.x / 2 - textSize.x / 2, winSize.y / 2 - textSize.y / 2,
           textSize.y, WON_TEXT_COLOR);
}

void SpaceInvaders::DrawLost() {
  DrawTexturePro(am.lostTex,
                 {0, 0, (float)am.lostTex.width, (float)am.lostTex.height},
                 {0, 0, winSize.x, winSize.y}, {0, 0}, 0, WHITE);
}

void SpaceInvaders::DrawWon() {
  DrawTexturePro(am.wonTex,
                 {0, 0, (float)am.wonTex.width, (float)am.wonTex.height},
                 {0, 0, winSize.x, winSize.y}, {0, 0}, 0, WHITE);
}

void SpaceInvaders::MoveEnemies() {
  Vector2 speed = CalculateSpeed(ENEMY_SPEED_RATIO) * GetFrameTime();
  Vector2 size = CalculateSize(ENEMY_SIZE_RATIO);
  if (ltr) {
    int maxX = 0;
    for (size_t i = 0; i < enemies.size(); ++i) {
      if (enemies[i].GetX() > maxX) {
        maxX = enemies[i].GetX();
      }
    }
    if (maxX + speed.x <= winSize.x - size.x) {
      for (size_t i = 0; i < enemies.size(); ++i) {
        enemies[i].MoveX(speed.x);
      }
    } else {
      ltr = false;
    }
  } else {
    int minX = winSize.x;
    for (size_t i = 0; i < enemies.size(); ++i) {
      if (enemies[i].GetX() < minX) {
        minX = enemies[i].GetX();
      }
    }
    if (minX - speed.x >= 0) {
      for (size_t i = 0; i < enemies.size(); ++i) {
        enemies[i].MoveX(-speed.x);
      }
    } else {
      ltr = true;
    }
  }
}

void SpaceInvaders::GenerateEnemies() {
  Vector2 enemySize = CalculateSize(ENEMY_SIZE_RATIO);
  Vector2 padding = {(GetWindowWidth() - ENEMIES_COUNT_ROW * enemySize.x) / 2,
                     (GetWindowHeight() / 2 - ENEMIES_COUNT_COL * enemySize.y) /
                         2};
  for (int i = 0; i < ENEMIES_COUNT_COL; ++i) {
    for (int j = 0; j < ENEMIES_COUNT_ROW; ++j) {
      enemies.push_back(
          Enemy({padding.x + j * enemySize.x, padding.y + i * enemySize.y}));
    }
  }
}

void SpaceInvaders::HandleEnemiesShooting() {
  enemiesShootTimer -= GetFrameTime();
  if (enemiesShootTimer <= 0.0f) {
    enemiesShootTimer = ENEMIES_SHOOT_TIMER;

    for (Enemy enemy : GetEnemiesWithLOSToPlayer()) {
      if (GetRandomValue(0, 100) <= ENEMY_SHOOT_CHANCE_PERCENTAGE) {
        bullets.push_back(enemy.Shoot());
      }
    }
  }
}

std::vector<Enemy> SpaceInvaders::GetEnemiesWithLOSToPlayer() {
  std::vector<Enemy> res;

  for (size_t i = 0; i < enemies.size(); ++i) {
    Rectangle possibleShooterRec = enemies[i].GetRec();
    bool hasEnemyBelow = false;

    for (size_t j = 0; j < enemies.size(); ++j) {
      if (i == j)
        continue; // Skip comparing the enemy with itself

      Rectangle otherRec = enemies[j].GetRec();

      bool sameCol = possibleShooterRec.x == otherRec.x;
      bool otherBelowPossibleShooter = possibleShooterRec.y < otherRec.y;

      if (sameCol && otherBelowPossibleShooter) {
        hasEnemyBelow = true;
        break;
      }
    }

    if (!hasEnemyBelow) {
      res.push_back(enemies[i]);
    }
  }

  return res;
}

void SpaceInvaders::HandleFrozen() {
  if (IsKeyPressed(KEY_FREEZE)) {
    frozen = !frozen;
  }
}
