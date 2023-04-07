#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "graphics/palletes.c"
#include "map.h"
#include "graphics/Letters.h"

void send_joypad(){
    _io_out = joypad();
    send_byte();
}

uint8_t remote_joypad(){
    receive_byte();
    return _io_in;
}

void set_handshake_text(const uchar *text){
    if (text == NULL) {
        return;
    }
    volatile uchar *tilemap = (uchar *)TILEMAP_START;
    static uchar tile;
    
    //todo: character name
    //set name dialogueCharNames[charNameIndex]
    for (uchar i = 0; i < 16; ++i){
        switch(text[i])
        {
            case (' '):
                tile = SPACE_LETTER;
                break;

            case ('.'):
                tile = 66;
                break;

            default:
                tile = letter_table[text[i] - 'A'];
        }
        tilemap[i] = tile;
        tile++;
        tilemap[(i+32)] = tile;
        wait_vbl_done();
    }
}

void multiplayer(){
    game_mode = MODE_MULTIPLAYER;
    set_bkg_palette(0, 1, colors);
    set_bkg_data(0, 46, Letters); //letters. 46 tiles.  23 letters
	move_bkg(0,0);
    wait_vbl_done();
    
    receive_byte(); //check if second console connected first
    uchar playerNum = 0;
    
    if (_io_in == 1){
        playerNum = 2;
        _io_out = 2;
        send_byte();
    }
    else{
        set_handshake_text("PLEASE CONNECT A");
        set_handshake_text("SECOND NINTENDO ");
        set_handshake_text("GAME BOY USING  ");
        set_handshake_text("A LINK CABLE    ");
        
        playerNum = 1;
        //send byte to second console waiting for connect
        do{
            receive_byte();
            _io_out = 1;
            send_byte();
            wait_vbl_done();
        }while(_io_in != 0);
    }

    set_handshake_text("CONNECTED       ");
    //wait 4 secs before start
    for (uchar i = 0; i < 180; ++i){
        wait_vbl_done();
    }

    /*uchar mode = 0;
    while (mode == 0){
        if (joy_impulse & J_A) {
            mode = 1;
            //printf("Player 1 selected\n");
        }
        else if (joy_impulse & J_B) {
            mode = 2;
            //printf("Player 2 selected\n");
        }
        wait_vbl_done();
    }*/

    if (playerNum == 1){ //P1
        enemyMoveMode = enemyMoveLink;
        play_game();
    }
    else if (playerNum == 2){ //P2
        while(1){
            send_joypad();
        }
    }
}
