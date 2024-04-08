#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct node {
  Vector2 pos;
  struct node *prev;
  struct node *next;
} SnakeNode;

typedef struct {
  SnakeNode *head;
  SnakeNode *tail;
  size_t len;
  Vector2 dir;
} Snake;

SnakeNode *create_node(Vector2 pos) {
  SnakeNode *node = (SnakeNode *)malloc(sizeof(SnakeNode));
  node->pos = pos;
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

void update_snake(Snake *snake) {
  SnakeNode *cur = snake->head;
  Vector2 vel = Vector2Multiply(snake->dir, (Vector2){1, 1});
  Vector2 pos = Vector2Add(cur->pos, vel);
  SnakeNode *new_head = create_node(pos);

  push_front(snake, new_head);

  delete_tail(snake);
  return;
}

void draw_snake(Snake *snake) {
  SnakeNode *cur = snake->head;
  while (cur != NULL) {
    DrawRectangle((int)cur->pos.x * 32 % GetScreenWidth(),
                  (int)cur->pos.y * 32 % GetScreenHeight(), 32, 32, GRAY);
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

  Snake snake;
  snake.head = create_node((Vector2){1, 1});
  snake.tail = snake.head;
  snake.dir = (Vector2){1, 0};
  snake.len = 0;
  push_front(&snake, create_node((Vector2){2, 1}));
  push_front(&snake, create_node((Vector2){3, 1}));
  push_front(&snake, create_node((Vector2){4, 1}));

  float frame = 0;
  Vector2 food = {0};

  while (!WindowShouldClose()) {
    const float delta = GetFrameTime();
    frame += delta;

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
    } else if (IsKeyPressed(KEY_T)) {
      delete_tail(&snake);
    }

    if (frame > 0.15f) {
      update_snake(&snake);
      frame = 0;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_snake(&snake);

    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  return 0;
}

/*
 * TODO: Create a game board
 * TODO: Spawn Food
 * TODO: Collision
 * TODO: Sound
 * */
