#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const int factor = 80;
const int screenWidth = factor * 16;
const int screenHeight = factor * 9;
const int tile_size = 32;
const int rows = screenWidth / tile_size;
const int cols = screenHeight / tile_size;

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
    DrawRectangle(cur->x * tile_size, cur->y * tile_size, tile_size - 2,
                  tile_size - 2, GRAY);
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
  snake.len = 0;
  push_front(&snake, create_node(2, 1));
  push_front(&snake, create_node(3, 1));
  push_front(&snake, create_node(4, 1));
  return snake;
}

void init_board(TileType board[rows][cols]) {
  for (int x = 0; x < rows; x++) {
    for (int y = 0; y < cols; y++) {
      board[x][y] = AIR;
    }
  }
}

void update_snake(Snake *snake, TileType board[rows][cols], Vector2 *food) {
  SnakeNode *cur = snake->head;
  int x = cur->x + snake->dir_x;
  int y = cur->y + snake->dir_y;
  if (x < 0)
    x = rows - 1;
  if (x > rows)
    x = 0;
  if (y < 0)
    y = cols - 1;
  if (y > cols)
    y = 0;
  int check_snake = board[x][y] == SNAKE;
  if (check_snake != 0) {
    *snake = init_snake();
    init_board(board);
    food->x = -1;
    food->y = -1;
    return;
  }
  int check_food = board[x][y] == FOOD && x == food->x && y == food->y;

  SnakeNode *new_head = create_node(x, y);
  board[new_head->x][new_head->y] = SNAKE;
  push_front(snake, new_head);
  if (check_food == 0) {
    board[snake->tail->x][snake->tail->y] = AIR;
    delete_tail(snake);
  } else {
    food->x = -1;
    food->y = -1;
  }
  return;
}

int main() {
  TileType board[rows][cols];
  init_board(board);
  InitWindow(screenWidth, screenHeight, "Snake");
  InitAudioDevice();
  SetTargetFPS(60);
  float frame = 0;
  int allow_input = 1;

  Snake snake = init_snake();
  board[1][1] = SNAKE;
  board[2][1] = SNAKE;
  board[3][1] = SNAKE;
  board[4][1] = SNAKE;
  Vector2 food = (Vector2){-1, -1};
  char *score = malloc(25 * sizeof(char));

  while (!WindowShouldClose()) {
    sprintf(score, "Score: %d", snake.len);
    const float delta = GetFrameTime();
    frame += delta;
    if (IsKeyDown(KEY_W) && snake.dir_y != 1 && allow_input != 0) {
      snake.dir_x = 0;
      snake.dir_y = -1;
      allow_input = 0;
    } else if (IsKeyDown(KEY_A) && snake.dir_x != 1 && allow_input != 0) {
      snake.dir_x = -1;
      snake.dir_y = 0;
      allow_input = 0;
    } else if (IsKeyDown(KEY_S) && snake.dir_y != -1 && allow_input != 0) {
      snake.dir_x = 0;
      snake.dir_y = 1;
      allow_input = 0;
    } else if (IsKeyDown(KEY_D) && snake.dir_x != -1 && allow_input != 0) {
      snake.dir_x = 1;
      snake.dir_y = 0;
      allow_input = 0;
    }

    if (frame > 0.15f) {
      allow_input = 1;
      frame = 0;
      update_snake(&snake, board, &food);
      while (food.x == -1 && GetRandomValue(0, 1) == 0) {
        int x = GetRandomValue(0, rows - 1);
        int y = GetRandomValue(0, cols - 1);
        if (board[x][y] == AIR) {
          board[x][y] = FOOD;
          food.x = x;
          food.y = y;
          break;
        }
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_snake(&snake);
    DrawCircle(food.x * tile_size + 16, food.y * tile_size + 16, 10, RED);
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
