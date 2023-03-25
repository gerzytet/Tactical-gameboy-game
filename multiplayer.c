#include "common.h"
#include "graphics/palletes.c"

void multiplayer(){
    game_mode = MODE_MULTIPLAYER;
    set_bkg_palette(0, 1, colors);
	move_bkg(0,0);

    printf("loading");
    wait_vbl_done();
    //joypad_init(2, /*pointer to some struct*/);
    //connected

    printf("Connect a second console before you continue!\nPress A for SEND MODE, press B for RECEIVE MODE\n");
    uchar mode = 0;
    while (mode == 0){
        //DURING FRAME:
		joy_impulse = joy;
		joy = joypad();
		joy_impulse = ~joy_impulse & joy;

        if (joy_impulse & J_A) {
            mode = 1;
            printf("Player 1 selected\n");
        }
        else if (joy_impulse & J_B) {
            mode = 2;
            printf("Player 2 selected\n");
        }
        wait_vbl_done();
    }

    printf("Searching for second console\n");

    while(mode == 1){
		//DURING FRAME:
		joy_impulse = joy;
		joy = joypad();
		joy_impulse = ~joy_impulse & joy;
		
        // Check which button was pressed
        if (joy_impulse & J_A) {
            printf("A\n");
            _io_out = 0;
            send_byte();
            /* Wait for IO completion... */
            while((_io_status == IO_SENDING) && (joypad() == 0));
        } else if (joy_impulse & J_B) {
            printf("B\n");
            _io_out = 1;
            send_byte();
            /* Wait for IO completion... */
            while((_io_status == IO_SENDING) && (joypad() == 0));
        } else if (joy_impulse & J_START) {
            printf("START\n");
            _io_out = 2;
            send_byte();
            /* Wait for IO completion... */
            while((_io_status == IO_SENDING) && (joypad() == 0));
        } else if (joy_impulse & J_SELECT) {
            printf("SELECT\n");
            _io_out = 3;
            send_byte();
            /* Wait for IO completion... */
            while((_io_status == IO_SENDING) && (joypad() == 0));
        } else if (joy_impulse & J_UP) {
            printf("UP\n");
            _io_out = 4;
            send_byte();
            /* Wait for IO completion... */
            while((_io_status == IO_SENDING) && (joypad() == 0));
        } else if (joy_impulse & J_DOWN) {
            printf("DOWN\n");
            _io_out = 5;
            send_byte();
            /* Wait for IO completion... */
            while((_io_status == IO_SENDING) && (joypad() == 0));
        } else if (joypad() & J_LEFT) {
            printf("LEFT\n");
            _io_out = 6;
            send_byte();
            /* Wait for IO completion... */
            while((_io_status == IO_SENDING) && (joypad() == 0));
        } else if (joy_impulse   & J_RIGHT) {
            printf("RIGHT\n");
            _io_out = 7;
            send_byte();
            /* Wait for IO completion... */
            while((_io_status == IO_SENDING) && (joypad() == 0));
        }
        wait_vbl_done();
	}

    while (mode == 2){
        /* Receive 1 byte */
        receive_byte();
        /* Wait for IO completion... */
        while((_io_status == IO_RECEIVING) && (joypad() == 0));
        
        switch(_io_in){
            case (0):
                printf("A Button received\n");
                break;
            case (1):
                printf("B Button received\n");
                break;
            case (2):
                printf("START Button received\n");
                break;
            case (3):
                printf("SELECT Button received\n");
                break;
            case (4):
                printf("DPAD Up received\n");
                break;
            case (5):
                printf("DPAD Down received\n");
                break;
            case (6):
                printf("DPAD Left received\n");
                break;
            case (7):
                printf("DPAD Right received\n");
                break;
        }  
        wait_vbl_done();
    }
}
