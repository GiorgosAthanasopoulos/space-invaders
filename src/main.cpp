#include "config.hpp"
#include "raylib.hpp"
#include "space_invaders.hpp"
#include "util.hpp"
#include <raylib.h>

int main() {
  Raylib *r = new Raylib;
  SpaceInvaders *g = new SpaceInvaders;
  Vector2 winSize = GetWindowSize();

  while (!g->ShouldClose()) {
    if (IsWindowResized()) {
      Vector2 neew = GetWindowSize();
      g->Resize(winSize, neew);
      r->Resize(winSize, neew);
      winSize = neew;
    }

    g->Update();
    r->Update();

    BeginDrawing();
    ClearBackground(WIN_BG);
    g->Draw();
    r->Draw();
    EndDrawing();
  }

  delete g;
  delete r;
  return 0;
}
