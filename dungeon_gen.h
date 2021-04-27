//
// Created by Simon on 24/04/2021.
//

#ifndef DUNGEONGENERATOR_DUNGEON_GEN_H
#define DUNGEONGENERATOR_DUNGEON_GEN_H

#define MAXGRID 16

typedef enum {EMPTY, ROOM, PLAYER, TREASURE, ENEMY} cell;

struct node {
    int x;
    int y;
    struct node *next;
};
typedef struct node Room;

typedef struct {
    Room* top;
    Room* bottom;
    int cont;
} RoomList;

Room* newRoom(int x, int y);

RoomList* newRoomList();

void generateRooms(RoomList *list, int num);

void pushRoom(RoomList* list, Room* room);

void connectRooms(RoomList* rooms);

void spawnPlayer(RoomList* rooms);

void spawnTreasure();

void playerMoveLeft();

void playerMoveRight();

void playerMoveUp();

void playerMoveDown();

void printGrid();

#endif //DUNGEONGENERATOR_DUNGEON_GEN_H
