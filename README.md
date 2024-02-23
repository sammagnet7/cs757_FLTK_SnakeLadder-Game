# FLTK_SnakeLadder_Game
## CS757_DesignOfOOps

## Pre-requisit
### FLTK install command on Linux
```Bash
sudo apt-get install fltk1.3-dev
sudo apt-get install libasound2-dev 
```
### FLTK install command on Mac
```Bash
sudo brew install fltk
```

## Building on Linux
```Bash
g++ -o snake snake.cpp `fltk-config --cxxflags --ldflags --use-images` -lasound
```
## Building on Mac
```Bash
g++ -std=c++17 -o snake snake.cpp `fltk-config --cxxflags --ldflags` -lfltk_images -framework AudioToolbox
```
