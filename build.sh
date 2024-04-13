#! /usr/bin/bash

set -xe

cc $1 -std=c17 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -pedantic -Wall -Wextra -O2 -o ./bin/$2 
./bin/$2
