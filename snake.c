#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define FACTOR 80
#define SCREEN_W FACTOR * 16
#define SCREEN_H FACTOR * 9
#define TILE_SIZE 40
#define ROWS 1280 / TILE_SIZE
#define COLS 720 / TILE_SIZE

typedef enum { SNAKE, FOOD, AIR } TileType;

typedef struct node {
  int x;
  int y;
  struct node *prev;
  struct node *next;
} SnakeNode;

typedef struct {
  SnakeNode *head;
  SnakeNode *tail;
  int len;
  int dir_x;
  int dir_y;
} Snake;

typedef struct {
  Snake snake;
  Vector2 food;
  TileType board[ROWS][COLS];
} Game;

SnakeNode *create_node(int x, int y) {
  SnakeNode *node = (SnakeNode *)malloc(sizeof(SnakeNode));
  node->x = x;
  node->y = y;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

void push_front(Snake *snake, SnakeNode *node) {
  SnakeNode *cur = snake->head;
  if (snake->head == NULL)
    snake->tail = node;
  cur->prev = node;
  node->next = cur;
  snake->head = node;
  snake->len++;
  return;
}

void delete_tail(Snake *snake) {
  SnakeNode *prev = snake->tail->prev;
  free(prev->next);
  prev->next = NULL;
  snake->tail = prev;
  snake->len--;
  return;
}

void draw_snake(Snake *snake) {
  SnakeNode *cur = snake->head;
  while (cur != NULL) {
    DrawRectangle(cur->x * TILE_SIZE, cur->y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                  GRAY);
    cur = cur->next;
  }
  return;
}

Snake init_snake() {
  Snake snake;
  snake.head = create_node(1, 1);
  snake.tail = snake.head;
  snake.dir_x = 1;
  snake.dir_y = 0;
  snake.len = 1;
  push_front(&snake, create_node(2, 1));
  push_front(&snake, create_node(3, 1));
  push_front(&snake, create_node(4, 1));
  return snake;
}

void init_board(TileType board[ROWS][COLS]) {
  for (int x = 0; x < ROWS; x++) {
    for (int y = 0; y < COLS; y++) {
      board[x][y] = AIR;
    }
  }
}

void update_snake(Game *game) {
  Snake *snake = &game->snake;
  Vector2 *food = &game->food;
  SnakeNode *cur = snake->head;
  int x = cur->x + snake->dir_x;
  int y = cur->y + snake->dir_y;
  if (x < 0)
    x = ROWS - 1;
  if (x > ROWS)
    x = 0;
  if (y < 0)
    y = COLS - 1;
  if (y > COLS)
    y = 0;
  int check_snake = game->board[x][y] == SNAKE;
  if (check_snake != 0) {
    *snake = init_snake();
    init_board(game->board);
    food->x = -1;
    food->y = -1;
    return;
  }
  int check_food = game->board[x][y] == FOOD && x == food->x && y == food->y;

  SnakeNode *new_head = create_node(x, y);
  game->board[new_head->x][new_head->y] = SNAKE;
  push_front(snake, new_head);
  if (check_food == 0) {
    game->board[snake->tail->x][snake->tail->y] = AIR;
    delete_tail(snake);
  } else {
    food->x = -1;
    food->y = -1;
  }
  return;
}

Game init_game() {
  Game game = {
      .board = {0},
      .food = (Vector2){.x = -1, .y = -1},
      .snake = init_snake(),
  };
  init_board(game.board);
  game.board[1][1] = SNAKE;
  game.board[2][1] = SNAKE;
  game.board[3][1] = SNAKE;
  game.board[4][1] = SNAKE;
  return game;
}

int main() {
  Game game = init_game();
  InitWindow(SCREEN_W, SCREEN_H, "Snake");
  InitAudioDevice();
  SetTargetFPS(60);
  float frame = 0;
  int allow_input = 1;

  char *score = malloc(25 * sizeof(char));

  while (!WindowShouldClose()) {
    sprintf(score, "Score: %d", game.snake.len);
    const float delta = GetFrameTime();
    frame += delta;
    if (IsKeyDown(KEY_W) && game.snake.dir_y != 1 && allow_input != 0) {
      game.snake.dir_x = 0;
      game.snake.dir_y = -1;
      allow_input = 0;
    } else if (IsKeyDown(KEY_A) && game.snake.dir_x != 1 && allow_input != 0) {
      game.snake.dir_x = -1;
      game.snake.dir_y = 0;
      allow_input = 0;
    } else if (IsKeyDown(KEY_S) && game.snake.dir_y != -1 && allow_input != 0) {
      game.snake.dir_x = 0;
      game.snake.dir_y = 1;
      allow_input = 0;
    } else if (IsKeyDown(KEY_D) && game.snake.dir_x != -1 && allow_input != 0) {
      game.snake.dir_x = 1;
      game.snake.dir_y = 0;
      allow_input = 0;
    }

    if (frame > 0.15f) {
      allow_input = 1;
      frame = 0;
      update_snake(&game);
      while (game.food.x == -1 && GetRandomValue(0, 1) == 0) {
        int x = GetRandomValue(0, ROWS - 1);
        int y = GetRandomValue(0, COLS - 1);
        if (game.board[x][y] == AIR) {
          game.board[x][y] = FOOD;
          game.food.x = x;
          game.food.y = y;
          break;
        }
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_snake(&game.snake);
    DrawCircle(game.food.x * TILE_SIZE + (TILE_SIZE / 2),
               game.food.y * TILE_SIZE + (TILE_SIZE / 2), 10, RED);
    DrawText(score, 8, 8, 20, BLACK);
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  return 0;
}

/*
 * TODO: Sound
 * */
