#include "raylib.h"

#define GRAVITY 100

typedef struct {
  Vector2 pos;
  Vector2 vel;
} block_t;

int main() {
  int factor = 80;
  int screenWidth = factor * 16;
  int screenHeight = factor * 9;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight, "Mass and Gravity");
  SetTraceLogLevel(LOG_ALL);

  block_t sand = {{20, 0}, {0, 0}};
  block_t iron = {{50, 0}, {0, 0}};

  while (!WindowShouldClose()) {
    float delta = GetFrameTime();
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    sand.vel.y += GRAVITY * delta;
    sand.pos.y += sand.vel.y * delta;
    if (sand.pos.y > screenHeight - 20) {
      sand.vel.y = -sand.vel.y / 2;
      sand.pos.y = screenHeight - 20;
    }
    iron.vel.y += GRAVITY * delta;
    iron.pos.y += iron.vel.y * delta;
    if (iron.pos.y > screenHeight - 20) {
      iron.vel.y = -iron.vel.y / 2;
      iron.pos.y = screenHeight - 20;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle((int)sand.pos.x, (int)sand.pos.y, 20, 20, YELLOW);
    DrawRectangle((int)iron.pos.x, (int)iron.pos.y, 20, 20, GRAY);
    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
