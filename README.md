# FLTK_SnakeLadder_Game
## CS757_DesignOfOOps

## Building on Linux
```Bash
g++ -o snake snake.cpp SoundFX.cpp `fltk-config --cxxflags --ldflags --use-images` -lopenal -lsndfile -Llib/
```
## Building on Mac
```Bash
g++ -std=c++17 -o snake snake.cpp `fltk-config --cxxflags --ldflags` -lfltk_images
```