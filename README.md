# CPROG Assignment
## Building
### Prerequisites
- The program expects SDL2 along with the extensions: image, mixer and ttf to be installed and available in the include path. 
- The program expects the resources folder to be available two levels above the executable., i.e. from the root of the project the executable should be located at `./build/debug/play` and the resources folder should be located at `./resources/` when running the program from `./build/debug/`.
### Building
```bash	
make
```

## The Game
## About
The game is a spaceinvaders-like game where the player controls a spaceship and shoots down invaders. The game consists of the Spaceship (with 3 HP), Invaders (with 1 HP each) and Blockades (with 10 HP each). The player wins if they manage to shoot down all invaders without losing all their HP.
## Controls
- `A` or `Left` to move left
- `D` or `Right` to move right
- `Space` to shoot