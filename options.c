#include "common.h"
#include "gb/gb.h"
#include "gb/cgb.h"
#include "stdio.h"

//todo

void options_menu(){
	game_mode = MODE_OPTIONS;
	set_bkg_palette(0, 1, colors);
	move_bkg(0,0);

	printf("Options\nThere are no current Options\nPress B to Return");

	while(1){
		//DURING FRAME:
		joy_impulse = joy;
		joy = joypad();
		joy_impulse = ~joy_impulse & joy;
		
		if (joy_impulse & J_B){
			menu_option = 255;
			return;
		}
		wait_vbl_done();
	}
}
