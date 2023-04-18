/*
@file banked_graphics.h
@author entire team
@date 4/17/2023
@brief 
*/

#ifndef BANKED_GRAPHICS_H
#define BANKED_GRAPHICS_H

void set_banked_bkg_data(uint8_t first_tile, uint8_t nb_tiles, const uint8_t *data, uint8_t bank) NONBANKED;
void set_banked_sprite_data(uint8_t first_tile, uint8_t nb_tiles, const uint8_t *data, uint8_t bank) NONBANKED;
void set_banked_bkg_tiles(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *map, uint8_t bank) NONBANKED;
void set_banked_win_tiles(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *map, uint8_t bank) NONBANKED;


#endif