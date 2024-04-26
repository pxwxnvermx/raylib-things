#include <array>
#include <deque>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

#define FACTOR 80
#define SCREEN_W FACTOR * 16
#define SCREEN_H FACTOR * 9
#define TILE_SIZE 40
#define ROWS 1280 / TILE_SIZE
#define COLS 720 / TILE_SIZE

typedef enum { SNAKE, FOOD, AIR } TileType;

typedef std::deque<Vector2> Snake;

typedef struct {
  Snake snake;
  Vector2 food;
  std::array<std::array<TileType, COLS>, ROWS> board;
  int food_eaten;
  int dir_x;
  int dir_y;
} Game;

Game init_game() {
  Game game = {
      .food = {.x = -1, .y = -1},
  };
  game.snake.push_front({1, 1});
  game.snake.push_front({2, 1});
  game.snake.push_front({3, 1});
  game.snake.push_front({4, 1});
  for (int x = 0; x < ROWS; x++) {
    for (int y = 0; y < COLS; y++) {
      game.board[x][y] = AIR;
    }
  }
  game.board[1][1] = SNAKE;
  game.board[2][1] = SNAKE;
  game.board[3][1] = SNAKE;
  game.board[4][1] = SNAKE;
  return game;
}

void draw_snake(Snake &snake) {
  for (auto cur : snake) {
    DrawRectangle(cur.x * TILE_SIZE, cur.y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                  GRAY);
  }
  return;
}

Vector2 GetRandomCirclePoint(int radius) {
  int ry = GetRandomValue(-radius, radius);
  int rx = GetRandomValue(-radius, radius);
  int theta = GetRandomValue(-radius, radius) * 2 * PI;
  return (Vector2){ry * cosf(theta), rx * sinf(theta)};
}

void update_game(Game *game) {
  while (game->food.x == -1 && GetRandomValue(0, 1) == 0) {
    int x = GetRandomValue(0, ROWS - 1);
    int y = GetRandomValue(0, COLS - 1);
    if (game->board[x][y] == AIR) {
      game->board[x][y] = FOOD;
      game->food.x = x;
      game->food.y = y;
      break;
    }
  }

  Vector2 cur = game->snake.front();
  int x = cur.x + game->dir_x;
  int y = cur.y + game->dir_y;
  if (x < 0)
    x = ROWS - 1;
  if (x > ROWS)
    x = 0;
  if (y < 0)
    y = COLS - 1;
  if (y > COLS)
    y = 0;

  if (game->board[x][y] == SNAKE) {
    *game = init_game();
    return;
  }

  bool check_food =
      game->board[x][y] == FOOD && x == game->food.x && y == game->food.y;

  game->snake.push_front({(float)x, (float)y});
  if (!check_food) {
    game->board[(int)game->snake.end()->x][(int)game->snake.end()->y] = AIR;
    game->snake.pop_back();
  } else {
    game->food_eaten = 1;
  }
  return;
}

int main() {
  Game game = init_game();
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(SCREEN_W, SCREEN_H, "Snake");
  InitAudioDevice();
  int frame_counter = 0;
  float time_step = 0;
  int allow_input = 1;
  Sound sound = LoadSound("./resources/short-bell.ogg");

  char *score = (char *)malloc(25 * sizeof(char));

  while (!WindowShouldClose()) {
    sprintf(score, "Score: %ld", game.snake.size());
    const float delta = GetFrameTime();
    time_step += delta;
    if (IsKeyDown(KEY_W) && game.dir_y != 1 && allow_input != 0) {
      game.dir_x = 0;
      game.dir_y = -1;
      allow_input = 0;
    } else if (IsKeyDown(KEY_A) && game.dir_x != 1 && allow_input != 0) {
      game.dir_x = -1;
      game.dir_y = 0;
      allow_input = 0;
    } else if (IsKeyDown(KEY_S) && game.dir_y != -1 && allow_input != 0) {
      game.dir_x = 0;
      game.dir_y = 1;
      allow_input = 0;
    } else if (IsKeyDown(KEY_D) && game.dir_x != -1 && allow_input != 0) {
      game.dir_x = 1;
      game.dir_y = 0;
      allow_input = 0;
    }

    if (time_step > 0.15f) {
      allow_input = 1;
      time_step = 0;
    }

    update_game(&game);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (auto node : game.snake) {
      float x = node.x + game.dir_x * delta;
      float y = node.y + game.dir_y * delta;
      DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GRAY);
    }
    DrawCircle(game.food.x * TILE_SIZE + (TILE_SIZE / 2),
               game.food.y * TILE_SIZE + (TILE_SIZE / 2), 10, RED);
    if (game.food_eaten) {
      frame_counter++;
      if (frame_counter < 15) {
        DrawCircleLines(game.food.x * TILE_SIZE + (TILE_SIZE / 2),
                        game.food.y * TILE_SIZE + (TILE_SIZE / 2),
                        20 * (15 - frame_counter), BLACK);
      } else {
        frame_counter = 0;
        game.food.x = -1;
        game.food.y = -1;
        game.food_eaten = 0;
        PlaySound(sound);
      }
    }
    DrawText(score, 8, 8, 20, BLACK);
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  return 0;
}
