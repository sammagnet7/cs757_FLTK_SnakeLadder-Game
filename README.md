# Snake and Ladder Game - CS757 Project Report

## Course Details

* **Course**: CS757 - Advanced Programming Lab
* **Project**: Snake and Ladder Game (with FLTK GUI)
* **Team Members**:

  * Soumik Dutta (23m0826)
  * Sm Arif Ali (23m0822)
* **GitHub Repository**: [cs757\_FLTK\_SnakeLadder-Game](https://github.com/sammagnet7/cs757_FLTK_SnakeLadder-Game)

---

## 1. Introduction

This project implements the classic **Snake and Ladder Game** with a graphical user interface built using the **FLTK (Fast Light Toolkit)** library. The project was developed as part of the CS757 course to demonstrate understanding of object-oriented design, GUI programming, and event-driven development in C++.

The game simulates dice rolling, movement across the board, and the effects of snakes and ladders. It also integrates graphics and sound to enhance the user experience.

---

## 2. Objectives

The primary objectives of this project were:

1. To design and implement a fully functional Snake and Ladder game.
2. To gain hands-on experience with GUI development in C++ using the FLTK library.
3. To apply object-oriented principles for structuring game entities like board, dice, snakes, and ladders.
4. To incorporate multimedia elements such as images and sound.

---

## 3. System Design

### 3.1 Class Design

A UML Class Diagram (`SnakeLadder_ClassDiagram.png`) was prepared to guide the design. The main entities include:

* **Board**: Represents the game board with positions of snakes and ladders.
* **Dice**: Handles random dice rolls (1-6) with visual dice images (`dice_1.png` to `dice_6.png`).
* **Player**: Stores player position and movement logic.
* **Snake/Ladder**: Represent transitions between board positions.

### 3.2 GUI Components

* **FLTK Windows and Widgets**: Used to display the game board (`board.png`) and interactive buttons.
* **Dice Roll Interaction**: Clicking the dice button triggers a dice roll and moves the player.
* **Sound Effects**: `snake.wav` is used for audio feedback during gameplay.

---

## 4. Implementation Details

* **Language**: C++
* **Graphics/UI Library**: FLTK
* **Source Files**: `snake.cpp`
* **Assets**: Images for board and dice, and a sound file.
* **Build System**: `Makefile` provided for compilation.

### Key Features:

1. Two-player gameplay (turn-based).
2. Dice roll simulation with graphical updates.
3. Automatic handling of snake and ladder jumps.
4. Sound effect when encountering a snake.
5. Victory condition detection (reaching final cell).

---

## 5. How to Build and Run

### 5.1 Prerequisites

* C++ compiler (g++)
* FLTK library installed

#### Commands on Linux

```bash
sudo apt-get install fltk1.3-dev
sudo apt-get install libasound2-dev
```

#### Commands on Mac

```bash
brew install fltk
```

### 5.2 Build Instructions

#### Building on Linux

```bash
make linux
```

#### Building on Mac

```bash
make mac
```

### 5.3 Run Instructions

```bash
./snake
```

This launches the game window.

---

## 6. Demonstration

A short demo video is available here: [YouTube Demo](https://youtu.be/Ls99YTCr7vw)
Additionally, `Game_Demo.mp4` has been provided in the repository to demonstrate gameplay and features.

---

## 7. Results and Discussion

The project successfully implements a playable Snake and Ladder game with:

* Functional game logic.
* Graphical representation of board and dice.
* Turn-based two-player system.
* Smooth integration of multimedia (images + sound).

Limitations:

* Currently supports only two players.
* GUI layout is basic and can be further improved for aesthetics.

---

## 8. Conclusion

This project provided hands-on experience in:

* Designing an object-oriented game structure.
* Using FLTK for GUI programming in C++.
* Managing multimedia resources within a game application.

Future improvements could include:

* Extending to support more players.
* Enhancing GUI with animations.
* Adding save/load game functionality.

---

## 9. References

* FLTK Documentation: [https://www.fltk.org/doc-1.3/](https://www.fltk.org/doc-1.3/)
* C++ Standard Library References
* GitHub Repository: [cs757\_FLTK\_SnakeLadder-Game](https://github.com/sammagnet7/cs757_FLTK_SnakeLadder-Game)
* YouTube Demo Video: [https://youtu.be/Ls99YTCr7vw](https://youtu.be/Ls99YTCr7vw)
