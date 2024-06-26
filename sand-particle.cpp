#include <algorithm>
#include <array>
#include <math.h>
#include <raylib.h>
#include <raymath.h>

enum particle_type { AIR, SAND, WATER, WOOD };
typedef struct {
  particle_type type;
  int vy;
} Particle;

const int screen_size = 800;
const int pixel_size = 1;
const int rows = screen_size / pixel_size;
const int cols = screen_size / pixel_size;
static std::array<std::array<Particle, cols>, rows> world;

void process_sand(int y, int x) {
  Particle current = world[y][x];
  world[y][x] = Particle{AIR, 0};
  int targety = std::min(y + current.vy, rows - 1);
  int targetx = std::clamp(x + GetRandomValue(-1, 1), 0, cols - 1);
  for (int ny = targety; ny > y; ny--) {
    if (world[ny][targetx].type == AIR) {
      targety = ny;
      break;
    }
  }
  if (world[targety][targetx].type != AIR) {
    targety = y;
    targetx = x;
  }
  world[targety][targetx] = Particle{SAND, current.vy + 1};
}

void update_world() {
  auto world_copy = world;
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      switch (world_copy[y][x].type) {
      case SAND:
        process_sand(y, x);
        break;
      case WATER:
        break;
      case WOOD:
        break;
      default:
        break;
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
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      world[y][x] = Particle{AIR, 0};
    }
  }

  while (!WindowShouldClose()) {
    Vector2 mouse_pos =
        Vector2Divide(GetMousePosition(), Vector2{pixel_size, pixel_size});
    if (IsMouseButtonDown(0)) {
      for (int i = 0; i < 20; i++) {
        Vector2 circle_point = GetRandomCirclePoint(40);
        Vector2 draw_point = Vector2Add(mouse_pos, circle_point);
        draw_point = Vector2Clamp(draw_point, Vector2{0, 0},
                                  Vector2{rows - 1, cols - 1});
        world[draw_point.y][draw_point.x] = Particle{SAND, 1};
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);
    for (int y = 0; y < rows; y++) {
      for (int x = 0; x < cols; x++) {
        if (world[y][x].type == SAND)
          DrawRectangle(x * pixel_size, y * pixel_size, pixel_size, pixel_size,
                        YELLOW);
        if (world[y][x].type == WOOD)
          DrawRectangle(x * pixel_size, y * pixel_size, pixel_size, pixel_size,
                        BROWN);
      }
    }
    EndDrawing();
    update_world();
  }

  CloseWindow();
  return 0;
}
