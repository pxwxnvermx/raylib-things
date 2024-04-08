#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct node {
  Vector2 pos;
  struct node *next;
} SnakeNode;

typedef struct {
  Vector2 dir;
  SnakeNode *head;
  SnakeNode *tail;
  size_t len;
} Snake;

void append_node(Snake *snake, Vector2 pos) {
  SnakeNode *node = (SnakeNode *)malloc(sizeof(SnakeNode));
  node->pos = pos;
  node->next = NULL;

  if (snake->head == NULL)
    snake->head = node;
  else
    snake->tail->next = node;

  snake->tail = node;
  snake->len++;
  return;
}

void draw_snake(Snake *snake, float delta) {
  SnakeNode *cur = snake->head;
  Vector2 vel = Vector2Multiply(snake->dir, (Vector2){32 * delta, 32 * delta});
  while (cur != NULL) {
    DrawRectangle(cur->pos.x, cur->pos.y, 32, 32, GRAY);
    cur->pos = Vector2Add(cur->pos, vel);
    cur = cur->next;
  }
  return;
}

void move_snake(Snake *snake, Vector2 pos) {
  SnakeNode *cur = snake->head;
  while (cur != NULL) {
    cur->pos = Vector2Add(cur->pos, pos);
    cur = cur->next;
  }
  return;
}

int main() {
  int factor = 80;
  int screenWidth = factor * 16;
  int screenHeight = factor * 9;

  InitWindow(screenWidth, screenHeight, "Snake");
  InitAudioDevice();
  SetTargetFPS(60);

  Camera2D camera = {0};
  camera.offset = (Vector2){10, 10};
  camera.target = (Vector2){0, 0};
  camera.zoom = 1;
  camera.rotation = 0;

  Snake snake;
  snake.head = NULL;
  snake.tail = NULL;
  snake.len = 0;
  snake.dir = (Vector2){1, 0};
  append_node(&snake, (Vector2){42, 10});
  append_node(&snake, (Vector2){10, 10});

  while (!WindowShouldClose()) {
    const float delta = GetFrameTime();
    if (IsKeyDown(KEY_W)) {
      snake.dir.x = 0;
      snake.dir.y = -1;
    } else if (IsKeyDown(KEY_A)) {
      snake.dir.x = -1;
      snake.dir.y = 0;
    } else if (IsKeyDown(KEY_S)) {
      snake.dir.x = 0;
      snake.dir.y = 1;
    } else if (IsKeyDown(KEY_D)) {
      snake.dir.x = 1;
      snake.dir.y = 0;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_snake(&snake, delta);

    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  return 0;
}
