#include <raylib.h>

int main() {
  int factor = 80;
  int screenWidth = factor * 16;
  int screenHeight = factor * 9;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Just trying something");
  InitAudioDevice();
  SetTargetFPS(60);
  SetTraceLogLevel(LOG_ALL);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  return 0;
}
