#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <stdlib.h>
#include <conio.h>
#include <joystick.h> 

#include "game.h"

/*
extern void init_music();
extern void start_music();
*/
extern void std_functions();


extern unsigned int level;

unsigned int playing, holes, pause;
unsigned int x_map, y_map;
unsigned char game_status, gates;
unsigned int randomizator2 = 0;

/*
unsigned char level_map[] = {
	0x00, 0x88, 0x0C, 0x06, 0x00,
	0x00, 0x08, 0x0E, 0x05, 0x00,
	0x00, 0x0A, 0x0F, 0x06, 0x02,
	0x00, 0x01, 0x03, 0x09, 0x07,
	0x00, 0x00, 0x01, 0x00, 0x01
};*/

// extern unsigned char ghost00_spr[];

/*
SCB_REHV_PAL ghost = {
  BPP_4 | TYPE_NORMAL, 
  REHV,
  0x01,
  (char *)&wall_d,
  ghost00_spr,
  20, 20,
  0x0100, 0x0100,
  // 0 and D are inverted to make magenta transluent
  {0xD1,0x23,0x45,0x67,0x89,0xAB,0xC0,0xEF}
};*/



void init_level(){
	//signed int vdiff, hdiff;
	tgi_outtextxy(8, 8, "The GAME");
	tgi_outtextxy(8, 16, "Press A or B");
	tgi_updatedisplay();
	
	pause = 0;
}



void physics(){
	// do physicals stuff here ;)
	
	
}

void game_logic(){
	unsigned char joy;
	
	
	//tgi_sprite(&ghost);
	
	joy = joy_read(JOY_1);
	
	
	if (JOY_BTN_1(joy) || JOY_BTN_2(joy) ) {
		game_status = EXIT;
	}
	else{
		if (game_status == EXIT ) game_status = LEVEL_UP;
	}

}


void game(){
	//char text[20];
	
	playing = 1;
	level = 1;
	
	
	
	game_status = NORMAL;
	tgi_clear();
	init_level();
	
	// chiper init + start
	/*
	init_music();
	start_music();
	*/

	
	while(playing){
		if (!tgi_busy())
		{
			if(game_status == LEVEL_UP){
				level++;
				game_status = NORMAL;
				//init_level();
				//srand(randomizator2);
				{playing = 0;}
			}
			if(!pause){
				game_logic();
				//player_logic();
				physics();
			} else{
				tgi_clear();
				
				tgi_outtextxy(36, 48, "GAME PAUSED");
			}
			/*
			itoa(level, text, 10);
			tgi_outtextxy(8, 2, text);
			*/
			std_functions();
			//tgi_updatedisplay();
			randomizator2++;
		}
	}	
	// chiper stop
	//asm("jsr SndStopAll");

}