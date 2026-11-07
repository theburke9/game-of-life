# Game of life

# Configuration and build

Install SDL3 dependencies from [here](https://wiki.libsdl.org/SDL3/README-linux#build-dependencies)

Clone SDL3: 
```{shell}
git clone https://github.com/libsdl-org/SDL.git vendored/SDL
```

Configure and build:
```{shell}
cmake -S . -B build
cmake --build build
```

Run:
```{shell}
./build/GameOfLife
```
