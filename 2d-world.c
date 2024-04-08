#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdio.h>
#include <stdlib.h>

#define WORLD_SIZE 9
#define CAM_SIZE 3
#define TILE_SIZE 64

int main() {
  int factor = 80;
  int screenWidth = factor * 10;
  int screenHeight = factor * 10;

  InitWindow(screenWidth, screenHeight, "2d World");
  SetTargetFPS(60);

  Rectangle player = {screenWidth * 0.5 - 20, screenHeight * 0.5 - 20, 32, 32};
  Camera2D camera = {
      .offset = {.x = 10, .y = 10},
      .target = {.x = 0, .y = 0},
      .rotation = 0.0f,
      .zoom = 1.0f,
  };
  Vector2 target_pos = {0};
  while (!WindowShouldClose()) {
    float delta = GetFrameTime();

    if (IsKeyDown(KEY_W))
      target_pos.y -= 20;
    if (IsKeyDown(KEY_S))
      target_pos.y += 20;
    if (IsKeyDown(KEY_A))
      target_pos.x -= 20;
    if (IsKeyDown(KEY_D))
      target_pos.x += 20;

    Vector2 vel = Vector2Subtract(target_pos, camera.target);
    vel.x *= 2.0f * delta;
    vel.y *= 2.0f * delta;
    player.x += vel.x;
    player.y += vel.y;
    camera.target = Vector2Add(camera.target, vel);

    char *pos = (char *)malloc((sizeof(char) * 100));
    sprintf(pos, "%.2f %.2f", player.x, player.y);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText(pos, 0, 30, 20, BLACK);
    DrawFPS(0, 0);

    BeginMode2D(camera);
    rlPushMatrix();
    rlTranslatef(0, 25 * 50, 0);
    rlRotatef(90, 1, 0, 0);
    DrawGrid(100, 50);
    rlPopMatrix();
    DrawRectangleRec(player, RED);
    EndMode2D();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
