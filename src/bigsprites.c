#include "common.h"
#include <gb/gb.h>

void set_bigsprite_color(uchar bigsprite, uchar color) {
    uchar sprite = bigsprite * 2;
    uchar bytenum = sprite * 4;

    volatile unsigned char* oam_data = &((unsigned char*)&shadow_OAM)[bytenum];
    oam_data[3] &= 0b11111000;
    oam_data[3] |= color;
    oam_data = &((unsigned char*)&shadow_OAM)[(sprite + 1)*4];
    oam_data[3] &= 0b11111000;
    oam_data[3] |= color;
}

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