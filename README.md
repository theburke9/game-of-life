# Game of life

<p align="center">
  <img src="docs/demo.gif" alt="Game of Life demo" width="480">
</p>

[The Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), also known as Conway's Game of Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.

## Features

- **Toroidal grid**: the edges wrap around, so a pattern leaving one side reappears on the opposite side.
- **Edit the grid**: click a cell to toggle it between alive and dead (only while the simulation is paused).
- **Play/Pause**: press the spacebar to start or stop the simulation.

## Rules

At each step, every cell looks at its 8 neighbors:

- A live cell with fewer than 2 live neighbors dies.
- A live cell with 2 or 3 live neighbors survives.
- A live cell with more than 3 live neighbors dies.
- A dead cell with exactly 3 live neighbors becomes alive.

## Build

Tested on Linux. To run Game of Life, install the SDL dependencies, clone this repository with SDL, and build with CMake.

1. Install the dependencies by following SDL's [Linux build dependencies](https://wiki.libsdl.org/SDL3/README-linux#build-dependencies).

2. Clone the repository and SDL:

```bash
git clone git@github.com:theburke9/game-of-life.git
cd game-of-life
git clone --depth 1 https://github.com/libsdl-org/SDL.git vendored/SDL
```

3. Build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Run

```bash
./build/GameOfLife
```

## TODO

- [x] ~~Restructure the project~~
  - [x] ~~Create the `core` folder and the `game` and `render` modules~~
  - [x] ~~Move `matrix.c`/`matrix.h` and `game.c`/`game.h` with `git mv` (to preserve history)~~
  - [x] ~~Make sure `core` and `game` depend on neither SDL nor a display (only `render` should include it)~~
- [ ] Add unit tests
- [ ] Improve the UI
  - [ ] Background color
  - [ ] Cell color
- [ ] Set the window size via program arguments (`argc`/`argv`)
- [ ] Display a text when the simulation is paused