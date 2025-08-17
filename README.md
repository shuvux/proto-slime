# Slymania

A simple 2D platformer made with **C++** and **raylib**.  
The player controls a slime character that jumps across dynamically generated platforms.

---

## Features
Implemented:
- Platform generation (single + multiple vertical)
- Slime texture loading
- Dynamic jump (hold or press)
- Dynamic speed (player/screen)
- Dynamic platform gap
- Platform textures
- High score and UI
- Dynamic platforms
- Background texture

Planned:
- Obstacles (vines)
- FP system
- Dash mechanic

- ## Requirements
- C++17 or later
- [raylib](https://www.raylib.com/)

- ##**Code for creating the Executable**
- On Windows: g++ -std=c++17 -o Slymania.exe main.cpp Game.cpp Player.cpp PlatformManager.cpp \
    -I. -lraylib -lopengl32 -lgdi32 -lwinmm
