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
  Camera3D camera = {
      .position = {100, -100, -100},
      .target = {0, 0, 0},
      .fovy = 90,
  };

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      BeginMode3D(camera);
      ClearBackground(RAYWHITE);
      { DrawCube(Vector3(), 20, 20, 20, RED); }
      EndMode3D();
    }
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  return 0;
}
