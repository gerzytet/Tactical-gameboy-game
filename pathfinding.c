#include "common.h"
#include "leveldata.h"
#include "tile_definitions.h"

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

//1 bit for each tile
uchar visited[16][2];

//255 = no traceback
uchar traceback[16][16];

uchar xQueue[256];
uchar yQueue[256];
uchar queueStart, queueEnd;

uchar passable_matrix[WIDTH][HEIGHT];

const uchar shiftTable[16] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

uchar diff = 0;
uchar pathEndX;
uchar pathEndY;

//1 if a path was found, otherwise 0
uchar pathfind(uchar startX, uchar startY, uchar endX, uchar endY, uchar dist) {
    for (uchar i = 0; i < 16; i++) {
        visited[i][0] = 0;
        visited[i][1] = 0;
    }
    pathEndX = endX;
    pathEndY = endY;
    static uchar myDist;
    myDist = dist;
    queueStart = 0;
    queueEnd = 2;
    xQueue[0] = startX;
    yQueue[0] = startY;
    xQueue[1] = 255;
    yQueue[1] = 255;
    traceback[startY][startX] = 255;
    traceback[endY][endX] = 255;
    //255 in the queue means we are done with this level of the queue, so decrement the dist
    while (1) {
        static uchar x;
        x = xQueue[queueStart];
        queueStart++;
        if (x == 255) {
            myDist--;
            if (myDist == 255) {
                return 0;
            }
            xQueue[queueEnd] = 255;
            yQueue[queueEnd] = 255;
            queueEnd++;
            continue;
        }

        if (queueEnd == queueStart) {
            return 0;
        }

        static uchar y;
        y = yQueue[queueStart - 1];

        if (visited[y][x/8] & shiftTable[x]) {
            continue;
        }

        visited[y][x/8] |= shiftTable[x];
       
        diff = 0;
        if (x > endX) {
            diff = x - endX;
        } else {
            diff = endX - x;
        }

        if (y > endY) {
            diff += y - endY;
        } else {
            diff += endY - y;
        }

        if (diff > myDist) {
            continue;
        }

        if (diff == 0) {
            return 1;
        }

        #define EXPLORE_HORIZ(DIR) if (~x & 16 && ~visited[y][x/8] & shiftTable[x] && passable_matrix[y][x] != 0) {\
            traceback[y][x] = DIR;\
            xQueue[queueEnd] = x;\
            yQueue[queueEnd] = y;\
            queueEnd++;\
        }

        x++;
        EXPLORE_HORIZ(WEST);

        x -= 2;
        EXPLORE_HORIZ(EAST);

        x++;

#define EXPLORE_VERT(DIR) if (~y & 16 && ~visited[y][x/8] & shiftTable[x] && passable_matrix[y][x] != 0) {\
    traceback[y][x] = DIR;\
    xQueue[queueEnd] = x;\
    yQueue[queueEnd] = y;\
    queueEnd++;\
}

        y++;
        EXPLORE_VERT(NORTH);

        y -= 2;
        EXPLORE_VERT(SOUTH);
    }
}

uchar movement_started = 0;
//returns 1 if the entity is done moving
uchar move_entity_after_pathfinding(uchar index) {
    if (!movement_started) {
        uchar x = pathEndX;
        uchar y = pathEndY;
        movement_started = 1;
        queueStart = 1;
        queueEnd = 1;
        uchar startX = entities[index].x / 16;
        uchar startY = entities[index].y / 16;
        passable_matrix[startY][startX] = passable_table[MAPS[mapIndex][startY][startX]];
        do {
            xQueue[queueEnd] = x;
            yQueue[queueEnd] = y;
            queueEnd++;
            if (traceback[y][x] == NORTH) {
                y--;
            } else if (traceback[y][x] == SOUTH) {
                y++;
            } else if (traceback[y][x] == EAST) {
                x++;
            } else if (traceback[y][x] == WEST) {
                x--;
            } 
        } while (x != startX || y != startY);
        queueEnd--;
        queueStart--;
    } else {
        for (uchar i = 0; i < 3; i++) {
            if (queueStart == queueEnd) {
                entities[index].moved = 1;
                {
                    uchar endX = entities[index].x / 16;
                    uchar endY = entities[index].y / 16;
                    passable_matrix[endY][endX] = 0;
                }
                movement_started = 0;
                return 1;
            }
            uchar x = xQueue[queueEnd] * 16;
            uchar y = yQueue[queueEnd] * 16;
            uchar currX = entities[index].x;
            uchar currY = entities[index].y;
            if (currX != x) {
                if (currX < x) {
                    entities[index].x++;
                } else {
                    entities[index].x--;
                }
            } else if (currY != y) {
                if (currY < y) {
                    entities[index].y++;
                } else {
                    entities[index].y--;
                }
            } else {
                queueEnd--;
            }
        }
    }
    return 0;
}

void setup_passable_matrix() {
    for (uchar r = 0; r < HEIGHT; r++) {
        for (uchar c = 0; c < WIDTH; c++) {
            passable_matrix[r][c] = passable_table[MAPS[mapIndex][r][c]];
        }
    }

    for (uchar i = 0; i < numCharacters; i++) {
        passable_matrix[entities[i].y / 16][entities[i].x / 16] = 0;
    }
}
