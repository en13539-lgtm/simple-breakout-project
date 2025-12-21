# Simple Breakout

![Breakout](https://i.postimg.cc/FzBNx6FK/Screenshot-20251103-175907.png)

---

The primary goal of this project is to build a simple [Breakout](https://en.wikipedia.org/wiki/Breakout_(video_game)) game written in C++ using the [raylib](https://www.raylib.com) graphics library. In this game, the player controls a paddle that keeps the ball within the level, which destroys blocks upon contact. The objective of the game is to navigate through a series of levels, cleaning all levels of blocks.

The game should adhere to the best structured and procedural programming principles. You should strive to effectively utilize structured programming constructs such as selection constructs and loops. Additionally, endeavor to achieve procedural decomposition of your code into functions. Ensure consistent formatting in your code, adhering to coding style best practices, including proper naming, indentation, use of white spaces, blank lines, and comments.

Be creative, and ensure to implement all the requirements outlined below in your project.

---

## Core Requirements

* **Title or Menu Screen**: The game should start with a title screen featuring a game logo and a message to start the game. Alternatively, it could be a menu screen with options to start the game, view the instructions, or quit the game.

![Title Screen](https://i.postimg.cc/ZRXBRS8N/Screenshot-20251029-161437.png)

* **Game Screen**: From the title or menu screen, the player should be able to start the game. The game screen displays the paddle, the ball, and the level. The player moves the paddle using the keyboard. The goal is to move from one level to the next by destroying all the blocks in every level. In our game, the objective of the player is to reach the end by passing through all the levels.

![Game Screen, Level 2](https://i.postimg.cc/FzBNx6FK/Screenshot-20251103-175907.png)

* **Pause Screen**: The player should be able to pause the game by pressing the Escape key. A 'Pause' screen appears with an option to resume the game. Pressing the Escape key resumes the game.

![Pause Screen](https://i.postimg.cc/Gt5djf3h/Screenshot-20251103-175849.png)

* **Victory Screen**: Upon passing through all the levels, a victory screen displays a congratulatory message, allowing the player to return to the title screen. Some animation, possibly from lab class exercises, should play in the background to indicate the game's completion. You are at liberty to come up with the animation.

![Victory Screen](https://i.postimg.cc/CL5KfGhW/Screenshot-20251103-175933.png)

## Additional Requirements

* **Additional Levels**: Add at least *three extra levels* to the game. These levels should be more challenging than the ones given. You may add more levels if you want.

* **Additional Game Elements**: Introduce at least *three new elements* to the game. These could include collectibles, moving obstacles, additional balls, turning the game 3-D, special time events, portals, more advanced bounce-off physics, improved collision detecion, or other modifications to the gameplay. Let your creativity guide you.

* **Game Over Screen**: Implement *a 'Game Over' screen* that displays a message when the player loses the game, such as when the player runs out of lives or the ball leaves the level. This screen should allow the player to return to the title screen or try again.

* **Additional Sounds**: Add at least *three new sounds* to the game. These sounds could accompany actions like bouncing off obstacles, picking up collectibles, or exiting the final level.

* **Background Music**: Incorporate at least *one music track* into the game. This track should play on at least one of the screens. Ensure the track is royalty-free or that you have usage rights. Store the music files in the `data/music/` directory and keep them reasonably sized.

## Practical Requirements

* Develop the code **independently of your peers** and maintain a **detailed project commit history**. Be aware that points will be withheld for any suspicion of code plagiarism, even if it's unfounded. Additionally, consistent progress must be evident in your project commit history to receive any points at all.

* Rewrite the `Readme.md` file with a description of your game and a list of the features that you have implemented. **Note that partially implementing some features is preferable to not implementing any.**

* Ensure that the game is playable and contains all necessary files. **It should be straightforward for the instructor to set up and start the game with minimal effort.**

## Deliverables

* Develop the game within the `<repository>` directory. This directory should include a `data/` subdirectory containing all game assets (images, sprites, fonts, sounds, etc.).

* Organize your code into `.h` and `.cpp` files. Each file should contain related constants, variables, and functions.

* Place your main game loop into the `breakout.cpp` file.

Upon completion, your Project directory should have an organized structure similar to the following example:

```
.
└── <repository>
    ├── data
    │   ├── fonts
    │   │   └── ...
    │   ├── images
    │   │   └── ...
    │   ├── music
    │   │   └── ...
    │   └── sounds
    │       └── ...
    ├── breakout.cpp
    ├── game.h
    ├── <various header and C++ files>.h/cpp
    ├── ... (.idea, .gitignore, .clang-format, CMakeLists.txt, other files)
    └── Readme.md
```

[Fork](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/fork-a-repo) our repository first, then clone it. If you skip this step, you will not be able to push your changes. Commit regularly, such as after implementing a feature (ensure the program is in a compilable state).

---

## Project Setup Notes

Set up the raylib project as you have done in previous labs for graphical assignments.

Before attempting to run the code for the `breakout` target, please ensure that you set the `Working directory` correctly in your CLion IDE.

The current working directory must point to the directory containing the necessary resource files (e.g., `data/images/`, `data/fonts/`, and `data/sound|music/`). Failure to do so will result in these resources not being loaded properly, and you will not see or hear the intended visuals or sounds in the game.

To set the working directory:

1. Open the `Run` menu and find the `Edit configurations` button there in CLion.
2. Select the `breakout` target.
3. Locate the `Working directory` field.
4. Set it to the `$ProjectFileDir$` value (this ensures it points to the root project directory with the `data` folder).
5. Save your configuration and run the target again.

If you encounter any issues, double-check that the paths to the resource files are correct relative to the working directory.

## Implementation Tips

- Read the raylib [cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html) to discover what is possible.
- Explore the raylib [examples](https://www.raylib.com/examples.html) for inspiration.
- Spend time searching for ways to break your program: that will help you eliminate edge cases and bugs.
- Log values and verify their correctness if stumbling across a bug.
- Use compilation and linking errors to your advantage: _read_ them.
- Use the debug tool to resolve crashes.

## Deadline

Refer to the specific course or assignment page on Moodle for detailed information about deadlines and the grading rubric.

## Links

### raylib

* [Wiki](https://github.com/raysan5/raylib/wiki)
* [Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)
* [Examples](https://www.raylib.com/examples.html)

### Tools

* [libresprite](https://libresprite.github.io/#!/)
* [jsfxr](https://sfxr.me/)

## Books

* Introduction to Programming with C++, 3rd Edition by Daniel Liang

## Credits

* [Luna Maltseva](https://github.com/lunamaltseva)

## About the Project

### Game Description

* This is a game where you need to hit the ball and destroy all the blocks on the level.
* Controls: </> movement, ESC - pause/unpause, ENTER - confirmation (menu/shop/new game).

### Game Screens

* Menu screen: Press ENTER to start the game.
* Game screen: Main gameplay.
* Pause screen: ESC pauses the game, ESC resumes.
* Shop screen: Appears after each level pass.
* Game Over screen: Displayed when you lose all your lives; ENTER restarts the game from the first level.
* Victory screen: Displayed after completing the final level.

### Lives
At the beginning of the game, the player is given three lives. Each time they fail to intercept 
the ball with the board and it touches the floor, they lose a life. 
After losing all lives, the game state transitions to game_over state.
The player can see how many lives(hearts) he has left in the lower left part of the screen.

### Coins or Dollars
By completing levels, the player can earn coins ($). The collected coins are added up and displayed in the upper left corner.
Each coin is 10 Dollars in a local valute.

### Shop
The shop appears between levels after the current level is won.
The store offers three items for purchase:
1) Add one life (50 coins) if the player loses any during the game
2) Expand the board to help with progression (30)
3) Slow down the ball (40 dollars)

### Levels
There are 5 levels with different difficulty.
Win a level > Shop > Next level
After the last level > Victory

### Sounds
There are five sounds
1. bonus.mp3 - when a ball breaks blocks
2. cache.mp3 - coin collection
3. choice.mp3 - when an item from shop was purchased
4. lose.wav - when a ball hits a bottom of the screen
5. win.wav - when all the blocks for the current level were destroyed.

### Background music
1. shopping.mp3 - plays when game_state is in shop_state



