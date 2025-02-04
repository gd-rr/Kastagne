### README - Kastagne (StreetFighter 3rd Strike-inspired Fighting Game)

#### Introduction

Welcome to our StreetFighter 3rd Strike-inspired fighting game, Kastagne! 
This game is designed to be played by two players and utilizes the SDL library for display.

#### Folder Organization

- **bin/** : Contains binary files generated during compilation.
- **obj/** : Contains object files generated during compilation.
- **src/** : Contains the game's source code.
  - **core/** : Contains the main classes of the game (camera, fighter, HUD, scenes, etc.).
  - **game/** : Contains the game-specific code (game states, game updates, etc.).
  - **hitbox/** : Contains collision management classes.
  - **sdl/** : Contains SDL wrappers and utilities.
  - **text/** : Contains classes for text-based game display.
  - **utils/** : Contains general utilities.
- **regression/** : Contains regression test files.
- **doc/** : Contains code documentation.

#### Compilation and Execution

- Make sure SDL is installed on your system.
- Clone the Git repository to your machine.
- Navigate to the project's root directory.
- Compile the game using the `make` command.
- Run the game by executing the generated binary file in the `bin/` directory.

Compilation example:

make

SDL version game execution example:

./bin/game

Text version game execution example:

./bin/gameTxt

#### Usage and Purpose of the Application

The purpose of the application is to provide a two-player fighting game experience inspired by StreetFighter 3rd Strike.
Players can choose their fighters and engage in dynamic battles.

#### Controls

- Player 1:
  - Movement: ZQSD.
  - Special Moves: A, E, F, Shift.
  - Attacks: 1, 2, 3.

- Player 2:
  - Movement: Arrow keys.
  - Special Moves: P, I, J, N
  - Attacks: 8, 9, 0.

#### Features

- Game loading screen.
- Navigation menu.
- Character selection.
- Two-player combat.
- Various moves and attacks.
- Camera reacts to movements.
- HUD displays players' vital information.

#### Libraries Used

- SDL2 (game display)
- nlohmann (JSON file handling)
- termios (text version of the game)
- unistd (text version of the game)