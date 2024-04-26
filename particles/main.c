#include "particles.h"
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

  ParticleState particle_state = {0};
  particle_state.pool_index = NUM_PARTICLES - 1;

  while (!WindowShouldClose()) {
    float delta = GetFrameTime();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 mpos = GetMousePosition();
      emit_particle(&particle_state, mpos);
    }
    update_particles(&particle_state, delta);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_particles(&particle_state);
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  return 0;
}
