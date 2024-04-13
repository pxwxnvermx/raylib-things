#! /usr/bin/bash

set -xe

RAYLIB_PATH=$HOME/Repos/software/raylib/src

emcc -o ./bin/$2.html $1 -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. -I $RAYLIB_PATH -I $RAYLIB_PATH/external -L. -L $RAYLIB_PATH -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 $RAYLIB_PATH/web/libraylib.a -DPLATFORM_WEB -s 'EXPORTED_FUNCTIONS=["_free","_malloc","_main"]' -s EXPORTED_RUNTIME_METHODS=ccall
