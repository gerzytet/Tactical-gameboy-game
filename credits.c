#include "common.h"
#include "gb/gb.h"
#include "gb/cgb.h"
#include "stdio.h"

void play_credits(){
	game_mode = MODE_CREDITS;
	set_bkg_palette(0, 1, colors);
	move_bkg(0,0);
	
	//DURING FRAME:
    joy_impulse = joy;
    joy = joypad();
    joy_impulse = ~joy_impulse & joy;

	printf("Thank you for playing our game!\nHope you enjoyed it!");

    while(1){
		if (joy_impulse & J_B){
			return;
		}
	}
}