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
    .position = {20, 20, 20},
    .target = {0, 0, 0},
    .up = {0, 1, 0},
    .fovy = 90,
    .projection = CAMERA_PERSPECTIVE
  };

  Vector3 cube_position = {0, 0, 0};
  Mesh cube_mesh = GenMeshCube(4.0f, 4.0f, 4.0f);
  Model cube_model = LoadModelFromMesh(cube_mesh);

  while (!WindowShouldClose()) {
    float delta = GetFrameTime();
    BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode3D(camera);
        DrawModel(cube_model, cube_position, 1.0f, RED);
      EndMode3D();
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  return 0;
}
