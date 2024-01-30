# Simulation of a 4-Player Game with Graph Algorithms

## Introduction:

This project simulates a complex 4-player game set on the planet Crematoria, incorporating graph algorithms to manage interactions among various units.

## How to Run:

### Compilation:

To compile the game, run the following command in the terminal:

```bash
make all
```
Execution:

Execute the game with the following command:

bash
Copy code
./Game SterrySX Demo Demo Demo -s 30 -i default.cnf -o default.res
Viewing the Match:
After compilation and execution, follow these steps to witness the match:

Go to the Game folder (unzip it).
Navigate to the viewer folder.
Open the "viewer.html" file.
Select the "default.res" file in the Game folder.
Additional Information:
For those interested in delving deeper into the project, I extend an open invitation to schedule a meeting at your convenience. During this meeting, I will provide an in-depth explanation, address any inquiries, and further explore the intricate details of this project.

Project Background:
Crematoria:
The game is based on the planet Crematoria, a once uninhabitable place turned into a battleground for four rival groups of pioneers. The surface, once a maximum-security prison, is now sought after for its valuable gems.

Game Rules:
The game involves 4 players, each controlling a group of pioneers and Furyans.
Goals include conquering cave cells and collecting gems.
Units include Pioneers, Furyans, Hellhounds, and Necromongers, each with unique abilities.
The game lasts for 120 rounds, and the winner is the group with the most points.
Game Mechanics:
Movement is allowed on a board with two levels (underground and outside).
Gems generate under sunlight, and the sun's movement affects gameplay.
Units can attack, conquer cells, and collect gems.
Programming the Game:
Running Your First Game:
Open a console and navigate to the source code directory.
If using Linux, run:
bash
Copy code
cp AIDummy.o.Linux AIDummy.o
cp Board.o.Linux Board.o
Run make all to build the game and players.
Execute a game with:
bash
Copy code
./Game Demo Demo Demo Demo -s 30 -i default.cnf -o default.res
Watch the game using the viewer.
Adding Your Player:
Copy AINull.cc to a new file, e.g., AIRiddick.cc.
Edit the new file, changing the #define PLAYER NAME Null line to #define PLAYER NAME Riddick.
Implement the play() method in your new player class.
Restrictions:
All code must be in a single file.
Avoid global variables; use attributes in your class.
Use only standard libraries.
No file operations or system calls.
Limit CPU time and memory usage.
