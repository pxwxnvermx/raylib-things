#! /usr/bin/bash

set -xe

cc $1 -std=c++20 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -pedantic -Wall -Wextra -o ./bin/$2 
./bin/$2
