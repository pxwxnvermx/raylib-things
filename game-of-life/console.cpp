#include <iostream>
#include <unistd.h>
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 200
#include "./game_of_life.h"

int main() {
  // glider
  state[5][1] = 1;
  state[5][3] = 1;
  state[6][2] = 1;
  state[6][3] = 1;
  state[7][2] = 1;

  // state[rows-4][7] = 1;
  // state[rows-4][8] = 1;
  // state[rows-4][9] = 1;
  fill_random();
  while (true) {
    evolve();
    std::cout << "\033[2J\033[1;1H";
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (state[i][j] == 1)
          std::cout << "O";
        else
          std::cout << "-";
      }
      std::cout << "\n";
    }
    sleep(1);
  }
  return 0;
}
