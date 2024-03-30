#include <raylib.h>
#include <iostream>
#include <algorithm>
#include <array>
#include <math.h>
using std::array;

enum particle_type {AIR, SAND, WATER};
typedef struct{
  particle_type type;
  int vy;
} Particle;

const int screen_size = 800;
const int pixel_size = 1;
const int rows = screen_size / pixel_size;
const int cols = screen_size / pixel_size;

typedef array<array<Particle, cols>, rows> World;

static World world;

void update_world() {
  auto world_copy = world;
  for(int y = 0; y < rows; y++) {
    for(int x = 0; x < cols; x++) {
      Particle current = world_copy[y][x];
      if(current.type == SAND) {
        int targety = std::clamp(y+1, 0, rows-1);
        int targetx = std::clamp(x+GetRandomValue(-1, 1), 0, cols-1);
        world[y][x] = Particle{AIR, 0};

        if(world[targety][targetx].type != AIR) {
          targety = y;
          targetx = x;
        }
 
        world[targety][targetx] = Particle{SAND, current.vy+1};
      }
    }
  }
}

Vector2 GetRandomCirclePoint(int radius) {
  int ry = GetRandomValue(-radius, radius);
  int rx = GetRandomValue(-radius, radius);
  int theta = GetRandomValue(-radius, radius) * 2 * PI;
  return Vector2{ry * cosf(theta), rx * sinf(theta)};
}

int main() {
  InitWindow(screen_size, screen_size, "Falling Sim");
  SetTargetFPS(165);
  SetTraceLogLevel(LOG_ALL);
  SetRandomSeed(time(0));
  for(int y = 0; y < rows; y++) {
    for(int x = 0; x < cols; x++) {
      world[y][x] = Particle{AIR, 0};
    }
  }

  while (!WindowShouldClose()) {
    int mouse_x = GetMouseX() / pixel_size;
    int mouse_y = GetMouseY() / pixel_size;
    if(IsMouseButtonDown(0)) {
      for(int i = 0; i < 100; i++) {
        Vector2 circle_point = GetRandomCirclePoint(10);
        int draw_y = std::clamp(int(mouse_y + circle_point.x), 0, rows-1);
        int draw_x = std::clamp(int(mouse_x + circle_point.y), 0, cols-1);
        world[draw_y][draw_x] = Particle{SAND, 1};
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);
    for(int y = 0; y < rows; y++) {
      for(int x = 0; x < cols; x++) {
        if(world[y][x].type == SAND) DrawRectangle(x*pixel_size, y*pixel_size, pixel_size, pixel_size, YELLOW);
      }
    }
    EndDrawing();
    update_world();
  }

  CloseWindow();
  return 0;
}
