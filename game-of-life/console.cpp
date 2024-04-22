#include <cstdio>
#include <unistd.h>

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 200
#include "./game_of_life.h"

int main() {
  fill_random();
  while (true) {
    evolve();
    printf("\033[2J\033[1;1H");
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (state[i][j] == 1)
          printf("O");
        else
          printf(" ");
      }
      printf("\n");
    }
    sleep(1);
  }
  return 0;
}
