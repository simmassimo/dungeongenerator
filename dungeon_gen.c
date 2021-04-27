//
// Created by Simon on 24/04/2021.
//

#include "dungeon_gen.h"
#include <stdio.h>
#include <stdlib.h>


Room* newRoom(int x, int y) {
    Room* new = (Room*) malloc(sizeof(Room));
    new->x = x;
    new->y = y;
    new->next = NULL;
    return new;
}

RoomList* newRoomList() {
    RoomList* new = (RoomList*) malloc(sizeof(RoomList));
    new->top = NULL;
    new->bottom = NULL;
    new->cont = 0;
    return new;
}

void generateRooms(RoomList *list, int num) {
    extern cell grid[MAXGRID][MAXGRID];
    int k;
    for(k = 0; k < num; k++) {
        int x = rand() % MAXGRID;
        int y = rand() % MAXGRID;
        if(grid[x][y] != 1) {
            grid[x][y] = 1;
            if(x + 1 < MAXGRID) {
                grid[x + 1][y] = 1;
                if(y + 1 < MAXGRID) {
                    grid[x + 1][y + 1] = 1;
                }
                if(y - 1 >= 0) {
                    grid[x + 1][y - 1] = 1;
                }
            }
            if(x - 1 >= 0) {
                grid[x - 1][y] = 1;
                if(y + 1 < MAXGRID) {
                    grid[x - 1][y + 1] = 1;
                }
                if(y - 1 >= 0) {

                    grid[x - 1][y - 1] = 1;
                }
            }
        }

        if(y + 1 < MAXGRID) grid[x][y + 1] = 1;
        if(y - 1 >= 0) grid[x][y - 1] = 1;
        Room* newroom = newRoom(x,y);
        pushRoom(list,newroom);
    }
}

void pushRoom(RoomList* list, Room* room) {
    if(list->top == NULL && list->bottom == NULL) {
        list->top = room;
        list->bottom = room;
    }
    else {
        list->bottom->next = room;
        list->bottom = room;
    }
    list->cont++;
}

void connectRooms(RoomList* rooms) {
    extern cell grid[MAXGRID][MAXGRID];
    int inc = 0;
    Room* roomA = rooms->top;
    Room* roomB = rooms->top->next;
    while(roomB != NULL) {

        int iy = roomA->y;
        inc = roomA->y < roomB->y ? 1 : -1;
        while(iy != roomB->y) {
            grid[roomA->x][iy] = 1;
            iy += inc;
        }
        grid[roomA->x][iy] = 1;

        int ix = roomA->x;
        inc = roomA->x < roomB->x ? 1 : -1;
        while(ix != roomB->x) {
            grid[ix][iy] = 1;
            ix += inc;
        }
        grid[ix][iy] = 1;

        roomA = roomA->next;
        roomB = roomB->next;
    }
}

void spawnPlayer(RoomList* rooms) {
    extern cell grid[MAXGRID][MAXGRID];
    extern int plyX;
    extern int plyY;
    int n = rand() % rooms->cont;
    int i;
    Room* index = rooms->top;
    for(i = 0; i < n; i++) {
        index = index->next;
        i++;
    }
    plyX = index->x;
    plyY = index->y;
    grid[plyX][plyY] = PLAYER;
}

void spawnTreasure() {
    extern cell grid[MAXGRID][MAXGRID];
    int randx= rand() % MAXGRID;;
    int randy= rand() % MAXGRID;;
    while(grid[randx][randy] != ROOM) {
        randx = rand() % MAXGRID;
        randy = rand() % MAXGRID;
    }
    grid[randx][randy] = TREASURE;
}

void printGrid() {
    extern cell grid[MAXGRID][MAXGRID];
    system("cls");
    int i,j;
    for(i = 0; i < MAXGRID; i++) {
        for(j = 0; j < MAXGRID; j++) {
            switch(grid[i][j]) {
                case EMPTY:
                    printf("%c",178);
                    break;
                case ROOM:
                    printf("%c",176);
                    break;
                case PLAYER:
                    printf("%c",3);
                    break;
                case TREASURE:
                    printf("%c",184);
                    break;
            }
        }
        printf("\n");
    }
}

void playerMoveUp() {
    extern cell grid[MAXGRID][MAXGRID];
    extern int plyX;
    extern int plyY;
    if(grid[plyX - 1][plyY]) {
        grid[plyX][plyY] = ROOM;
        plyX--;
        grid[plyX][plyY] = PLAYER;
        printGrid();
    }
}

void playerMoveLeft() {
    extern cell grid[MAXGRID][MAXGRID];
    extern int plyX;
    extern int plyY;

    if(grid[plyX][plyY - 1]) {
        grid[plyX][plyY] = ROOM;
        plyY--;
        grid[plyX][plyY] = PLAYER;
        printGrid();
    }
}

void playerMoveRight() {
    extern cell grid[MAXGRID][MAXGRID];
    extern int plyX;
    extern int plyY;

    if(grid[plyX][plyY + 1]) {
        grid[plyX][plyY] = ROOM;
        plyY++;
        grid[plyX][plyY] = PLAYER;
        printGrid();
    }
}

void playerMoveDown() {
    extern cell grid[MAXGRID][MAXGRID];
    extern int plyX;
    extern int plyY;

    if(grid[plyX + 1][plyY]) {
        grid[plyX][plyY] = ROOM;
        plyX++;
        grid[plyX][plyY] = PLAYER;
        printGrid();
    }
}