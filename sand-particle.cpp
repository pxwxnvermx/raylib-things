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
        world[y][x] = Particle(AIR, 0);

        if(world[targety][targetx].type != AIR) {
          targety = y;
          targetx = x;
        }
 
        world[targety][targetx] = Particle(SAND, current.vy+1);
      }
    }
  }
}

Vector2 GetRandomCirclePoint(int radius) {
  int high = radius; 
  int low = -radius;
  int ry = GetRandomValue(low, high);
  int rx = GetRandomValue(low, high);
  int theta = GetRandomValue(low, high) * 2 * PI;
  return Vector2(ry * cos(theta), rx * sin(theta));
}

int main() {
  InitWindow(screen_size, screen_size, "Falling Sim");
  SetTargetFPS(165);
  SetTraceLogLevel(LOG_ALL);
  SetRandomSeed(time(0));
  for(int y = 0; y < rows; y++) {
    for(int x = 0; x < cols; x++) {
      world[y][x] = Particle(AIR, 0);
    }
  }

  while (!WindowShouldClose()) {
    int mouse_x = std::clamp(GetMouseX()/pixel_size, 0, rows-1);
    int mouse_y = std::clamp(GetMouseY()/pixel_size, 0, cols-1);
    if(IsMouseButtonDown(0)) {
      for(int i = 0; i < 100; i++) {
        Vector2 circle_point = GetRandomCirclePoint(10);
        int draw_y = mouse_y + circle_point.x;
        int draw_x = mouse_x + circle_point.y;
        world[draw_y][draw_x] = Particle(SAND, 1);
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
