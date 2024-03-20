#include <algorithm>
#include <iostream>
#include <array>
#ifndef SCREEN_WIDTH
  #define SCREEN_WIDTH 100
#endif // !SCREEN_WIDTH
#ifndef SCREEN_HEIGHT
  #define SCREEN_HEIGHT 100
#endif // !SCREEN_HEIGHT

using std::array;

static int dirs[8][2] = {{0, 1}, {1, 0}, {1, 1}, {0, -1}, {-1, 0}, {-1, 1}, {1, -1}, {-1, -1}};
const int rows = SCREEN_WIDTH / 2;
const int cols = SCREEN_HEIGHT / 2;
typedef array<array<int, cols>, rows> State;
State state;

int count_nbrs(int i, int j, State &arr) {
	int aliveCount = 0;
	for(int ci = 0; ci < 8; ci++) {
		int x = (i + dirs[ci][0] + rows) % rows;
		int y = (j + dirs[ci][1] + cols) % cols;
		bool alive = arr[x][y] == 1;
		aliveCount += alive ? 1 : 0;
	}
	return aliveCount;
}

void evolve() {
	auto arr_copy = state;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			int &currentCell = state[i][j];
			int aliveCount = count_nbrs(i, j, arr_copy);
			if (currentCell == 1 && (aliveCount < 2 || aliveCount > 3)) currentCell = 0;
			if (aliveCount == 3 && currentCell == 0) currentCell = 1;
		}
	}
}

void fill_random() {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			state[i][j] = rand() % 2;
		}
	}
}
