# Project description
Project utilizes SFML library to present John Conway's cellular automaton called `Game of life`. User can select which cells should be activated with mouse. Automaton is started by pressing the `space` key. During the operation program can be stopped by `space` key and cells can be activated/deactivated manually.

# Build and run
To run the project use commands:
```
mkdir build
cmake -B build .
cd build
make
./game_of_life
```