#include <algorithm>
#include <raylib.h>
#include <iostream>
#include <array>
#define FACTOR 100
#define SCREEN_WIDTH 16*FACTOR
#define SCREEN_HEIGHT 9*FACTOR
#include "game_of_life.h"

const int sq_size = 10;

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");
  SetTargetFPS(120);

  fill_random();

  while (!WindowShouldClose()) {
    evolve();
    BeginDrawing();
    ClearBackground(BLACK);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(state[i][j] == 1) 
				DrawRectangle(i*sq_size, j*sq_size, sq_size, sq_size, WHITE);
		}
	}
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
