#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "dungeon_gen.h"

cell grid[MAXGRID][MAXGRID] = {0};
int plyX;
int plyY;

int main() {
    srand(time(NULL));

    int nrooms = 12;
    RoomList* list = newRoomList();

    generateRooms(list,nrooms);

    connectRooms(list);

    spawnPlayer(list);

    spawnTreasure();
    spawnTreasure();
    spawnTreasure();
    spawnTreasure();

    printGrid();
    while(1) {
        if(kbhit()) {
            char c = getch();
            switch (c) {
                case 'w':
                    playerMoveUp();
                    break;
                case 'a':
                    playerMoveLeft();
                    break;
                case 's':
                    playerMoveDown();
                    break;
                case 'd':
                    playerMoveRight();
                    break;

            }
        }
    }
    return 0;
}
