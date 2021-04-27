# Dungeon Generator in C

This small program procedurally generates a 32x32 dungeon and lets you play a small game where you run around and collect coins while moving with the W A S D keys!
This was just a small experiment to see how far I could go to create a game from scratch using only C.

The program starts by creating a global 32x32 matrix of an enum "cell". The cell determines what is standing in that spot in the matrix at runtime (a wall,an empty spot, the player etc). I then generate a variable number of random coordinates of x and y and collect them in a linked list. These will be my "rooms" of the dungeon. Then the program creates a 3x3 room in the matrix for every node of the list, with the center being the actual coordinates stored. After all the rooms are generated, they get all connected sequentially by creating a hallway from one room to another. The method I choose to do this is trying to match the row of the second room first, then match the same column (so starting from room A, the program will build a tunnel going up or down until it reaches the same row of room B and then builds left or right until it also matches the same column too).
After the dungeon is complete, I decided to turn the program into a little game by adding the enum PLAYER to the cell and adding some global variables dedicated to his position. I then "spawn" the player by picking a random room in the room list and switching those coordinates in the matrix with the enum PLAYER, meaning that now every time the dungeon is printed, it will change that empty space with a heart, which is the player's symbol. I then created an infinite loop that constantly checks for user input at runtime (see note below) and shift his position in the matrix depending on the button pressed and re-prints the matrix. The coins are also spawned but I used a slower method where the function generates random coordinates until it eventually matches to an available empty space in the matrix and then changes the cell to TREASURE in that spot.

Note: in order to constantly check for user input, I had to use the library <conio.h> which is a non-standard library which might create issues for some users.
