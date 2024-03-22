#! /usr/bin/bash

set -xe

g++ $1 -std=c++20 `pkg-config --libs --cflags raylib` -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL /opt/homebrew/Cellar/raylib/5.0/lib/libraylib.a -o ./bin/$2 
./bin/$2
