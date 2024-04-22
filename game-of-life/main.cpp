#include <raylib.h>
#define FACTOR 100
#define SCREEN_WIDTH 16 * FACTOR
#define SCREEN_HEIGHT 9 * FACTOR
#include "game_of_life.h"

const int sq_size = 10;

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");

  fill_random();
  float frame = 0.0f;
  while (!WindowShouldClose()) {
    float delta = GetFrameTime();
    frame += delta;
    if (frame >= 0.1f) {
      evolve();
      frame = 0.0f;
    }
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (state[i][j] == 1)
          DrawRectangle(i * sq_size, j * sq_size, sq_size, sq_size, WHITE);
      }
    }
    DrawFPS(0, 0);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
