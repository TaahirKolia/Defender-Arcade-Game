


# Defender Arcade Game

The **Defender** arcade game is an exciting project that utilizes an object-oriented programming (OOP) approach. It is implemented in C++17 and incorporates the following frameworks:

1. **SFML (Simple and Fast Multimedia Library)**:
   - Version: 2.6.0
   - Purpose: Used for object display, graphics rendering, and handling user input.
   - Website: SFML Official Website

2. **Doctest**:
   - Version: 2.4.11
   - Purpose: Provides an automated unit testing framework for ensuring code correctness.
   - Website: Doctest GitHub Repository

## Features

- Object-oriented design: The game leverages OOP principles to create modular and maintainable code.
- Graphics and animation: SFML allows smooth rendering of game objects, animations, and visual effects.
- Unit testing: Doctest ensures that critical components are thoroughly tested for correctness.

## Getting Started

1. **Prerequisites**:
   - Install a C++ compiler (e.g. GCC).
   - Set up SFML by downloading the appropriate binaries or building from source.
   - Install Doctest. 

2. **Building and Running the Game**:
   - Clone this repository.
     ```
     git@github.com:TaahirKolia/Defender-Arcade-Game.git
     ```
   - Compile the source files using your preferred C++ compiler.
     ```
     g++ -std=c++17 -o defender main.cpp -lsfml-graphics -lsfml-window -lsfml-system
     ```
   - Run the executable to play the game.
     ```
     ./defender
     ```
   - Alternatively, a downloadable game executable can be found in the releases section of this repository.

The aim of the game is to eliminate all the enemy landers. These adversaries appear unpredictably near the player's ship and fire missiles aimed at it. However, the player can dodge the missiles by swiftly moving away from their path or by destroying the landers before they launch a missile. If the player is hit by a lander's missile or collides with a lander, pod, or swarmer, they lose one of their three lives. It's important to fight back by using the ship's lasers and keep an eye on the fuel levels, which deplete as the player maneuvers the ship. Fuel levels can be replenished by collecting fuel canisters. Victory is achieved by destroying all 20 landers. Conversely, the game ends in defeat if the player loses all three lives, runs out of fuel, or if all five humanoids are eliminated or captured.

Comprehensive documentation detailing the game's implementation can be found under the release section. 
