#ifndef BIGSPRITES_H
#define BIGSPRITES_H

#include "common.h"
#include <gb/gb.h>

#define internal_display_bigsprite(slot, tile)\
    set_sprite_tile((slot)*2, (tile)*4);\
    set_sprite_tile((slot)*2+1, (tile)*4+2);\

#define internal_move_bigsprite(slot, x, y)\
    move_sprite((slot)*2, (x), (y));\
    move_sprite((slot)*2+1, (x)+8, (y));

#define move_bigsprite(slot, x_, y_)\
    bigsprites[slot].x = (x_);\
    bigsprites[slot].y = (y_);

#define display_bigsprite(slot, tile)\
    bigsprites[slot].sprite = (tile);

uchar bigspriteCounts[10];

struct Bigsprite {
    uchar y;
    uchar x;
    uchar sprite;
    //uchar color; or something
};

struct Bigsprite bigsprites[20];

extern void display_bigsprites();

void process_bigsprites() {
    static uchar count = 0;
    count++;
    //for (uchar i = 0; i < 20; i++) {
    //    internal_display_bigsprite(i, bigsprites[i].sprite);
    //    internal_move_bigsprite(i, bigsprites[i].x, bigsprites[i].y);
    //}
    display_bigsprites();
    for (uchar i = 0; i < 10; i++) {
        bigspriteCounts[i] = 0;
    }
    for (uchar i = 0; i < 20; i++) {
        bigspriteCounts[bigsprites[i].y / 16]++;
        if (bigsprites[i].y & 15) {
            bigspriteCounts[bigsprites[i].y / 16 + 1]++;
        }
    }

    for (uchar i = 1; i < 10; i++) {
        if (bigspriteCounts[i] > 5) {
            uchar excluded = bigspriteCounts[i] - 5;
            uchar start = count % bigspriteCounts[i];
            uchar end = start + excluded;
            if (end > bigspriteCounts[i]) {
                end -= bigspriteCounts[i];
            }
            for (uchar j = start; j != end; j++) {
                if (j >= bigspriteCounts[i]) {
                    j -= bigspriteCounts[i];
                    if (j == end) {
                        break;
                    }
                }
                internal_move_bigsprite(j, 0, 0);
            }
        }
    }
}

void init_bigsprites() {
    for (uchar i = 0; i < 20; i++) {
        bigsprites[i].x = 0;
        bigsprites[i].y = 0;
        bigsprites[i].sprite = 0;
    }
}

#endif