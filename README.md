# FLTK_SnakeLadder_Game
## CS757_DesignOfOOps

## Building on Linux
```Bash
fltk-config --use-images --compile snake.cpp
```
## Building on Mac
```Bash
g++ -std=c++17 -o snake snake.cpp `fltk-config --cxxflags --ldflags` -lfltk_images
```