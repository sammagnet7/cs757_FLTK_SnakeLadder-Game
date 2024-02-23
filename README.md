# FLTK_SnakeLadder_Game
## CS757_DesignOfOOps

## Building on Linux
```Bash
g++ -o snake snake.cpp `fltk-config --cxxflags --ldflags --use-images` -lasound
```
## Building on Mac
```Bash
g++ -std=c++17 -o snake snake.cpp `fltk-config --cxxflags --ldflags` -lfltk_images -framework AudioToolbox
```

### FLTK install command on Linux
```Bash
sudo apt-get install linfltk1.3-dev
```
### FLTK install command on Mac
```Bash
sudo brew install fltk
```