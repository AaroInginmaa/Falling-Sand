# Falling Sand
A sand simulation made with C and SDL2.

## Compilation
> [!IMPORTANT]  
> SDL 2.0 is required.
> 
Using [GCC](https://gcc.gnu.org/)
```
gcc src/main.c -o ./fallingsand.exe -I./include -L./lib -lSDL2main -lSDL2
```
using [GNU Make](https://www.gnu.org/software/make/)
```
make
```
[example](sand_example.gif)