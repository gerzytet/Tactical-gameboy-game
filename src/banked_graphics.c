#include <gb/gb.h>
#include <gb/cgb.h>
#include <ctype.h>

void set_banked_bkg_data(uint8_t first_tile, uint8_t nb_tiles, const uint8_t *data, uint8_t bank) NONBANKED 
{
    uint8_t save = _current_bank;
    SWITCH_ROM(bank);
    set_bkg_data(first_tile, nb_tiles, data);
    SWITCH_ROM(save);
}

#define set_banked_win_data set_banked_bkg_data

void set_banked_sprite_data(uint8_t first_tile, uint8_t nb_tiles, const uint8_t *data, uint8_t bank) NONBANKED 
{
    uint8_t save = _current_bank;
    SWITCH_ROM(bank);
    set_sprite_data(first_tile, nb_tiles, data);
    SWITCH_ROM(save);
}

void set_banked_bkg_tiles(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *map, uint8_t bank) NONBANKED{
    uint8_t save = _current_bank;
    SWITCH_ROM(bank);
    set_bkg_tiles(x, y, w, h, map);
    SWITCH_ROM(save);
}

void set_banked_win_tiles(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *map, uint8_t bank) NONBANKED{
    uint8_t save = _current_bank;
    SWITCH_ROM(bank);
    set_win_tiles(x, y, w, h, map);
    SWITCH_ROM(save);
}

/*void hUGE_init_banked(const hUGESong_t * song, uint8_t bank) NONBANKED{
    uint8_t save = _current_bank;
    SWITCH_ROM(bank);
    hUGE_init(song);
    SWITCH_ROM(save);
}*/

/*void hUGE_dosound_banked() NONBANKED{
    uint8_t save = _current_bank;
    SWITCH_ROM(2);
    hUGE_dosound();
    SWITCH_ROM(save);
}*/
