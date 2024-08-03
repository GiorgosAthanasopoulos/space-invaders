#include "asset_manager.hpp"
#include "config.hpp"
#include <raylib.h>

AssetManager::AssetManager() {
  player = LoadTexture("assets/player.png");
  enemy = LoadTexture("assets/enemies.png");
  player_bullet = LoadTexture("assets/player_bullet.png");
  enemy_bullet = LoadTexture("assets/enemy_bullet.png");
  bg = LoadTexture("assets/backdrop.png");
  lostTex = LoadTexture("assets/dead_screen.png");
  wonTex = LoadTexture("assets/win_screen.png");

  bgm = LoadMusicStream("assets/bgm.mp3");
  SetMusicVolume(bgm, MUSIC_VOLUME);

  shot = LoadSound("assets/shot.mp3");
  receivedDamage = LoadSound("assets/receivedDamage.mp3");
  kill = LoadSound("assets/kill.mp3");
  won = LoadSound("assets/won.mp3");
  lost = LoadSound("assets/lost.mp3");
  SetSoundVolume(shot, SOUND_VOLUME);
  SetSoundVolume(receivedDamage, SOUND_VOLUME);
  SetSoundVolume(kill, SOUND_VOLUME);
  SetSoundVolume(won, SOUND_VOLUME);
  SetSoundVolume(lost, SOUND_VOLUME);
}

AssetManager::~AssetManager() {
  UnloadTexture(player);
  UnloadTexture(enemy);
  UnloadTexture(player_bullet);
  UnloadTexture(enemy_bullet);
  UnloadTexture(bg);
  UnloadTexture(lostTex);
  UnloadTexture(wonTex);

  UnloadMusicStream(bgm);

  UnloadSound(shot);
  UnloadSound(receivedDamage);
  UnloadSound(kill);
  UnloadSound(won);
  UnloadSound(lost);
}
