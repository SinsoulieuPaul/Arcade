# Arcade

Arcade is a second-year C++ project at Epitech. It was to be carried out in groups of three.

We had to recreate the functionality of an emulator by creating two video games (we chose Snake and Pacman) and using three different graphic libraries (NCurses, SDL2, and SFML).

The games had to inherit from IGameModule, and the graphic libraries from IDisplayModule. We had to share these two classes with two other groups so that they could use our games with their graphic libraries, and vice versa.

This was made possible thanks to the fact that the games and libraries were converted into .so files, allowing the addition of plugins, other games, as well as other graphic libraries.

One of the main objectives of this project was to be able to dynamically switch between graphic libraries or games during program execution, without any optimization, crash, or bug issues.

## Requirements

`build`
- C++20 Compiler
- make

`Graphical Libraries`
- NCurses
- SDL
- SDL_image
- SDL_ttf
- SFML

## Usage

```bash
make
./arcade lib/[graphical_library.so]
```

Exemple:

```bash
make
./arcade lib/arcade_Sdl2.so
```

## Collaborators

This project was made with [Louis Anderruthy](https://github.com/LouisA2222) and [Sovn - Loïc](https://github.com/SovnSkyrim)

## License

[MIT](https://choosealicense.com/licenses/mit/)
