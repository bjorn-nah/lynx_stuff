#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <stdlib.h>
#include <conio.h>

extern unsigned char skull[];

/*
SCB_RENONE skullsprite =  {
  BPP_4 | TYPE_NORMAL, 
  REUSEPAL, 0x01,
  0x0000,
  &skull,
  20, 50
};*/

SCB_REHV_PAL  skullsprite =  {
  BPP_4 | TYPE_NORMAL, 
  REHV,
  0x01,
  0x0000,
  skull,
  20, 50,
  0x0100, 0x0100,
  // palette values can be found in .pal file provided by sprpck
  {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF}
  };

int dirrection, grow;

void initialize()
{
	tgi_install(&tgi_static_stddrv);
	tgi_init();

	CLI();

	while (tgi_busy()) ;

	tgi_setpalette(tgi_getdefpalette());
	tgi_setcolor(COLOR_WHITE);
	tgi_setbgcolor(COLOR_BLACK);

	tgi_clear();
	
	dirrection = 1;
	grow = 1;
}

void show_screen()
{
	// Clear current screen
	tgi_clear();
	
	tgi_setcolor(COLOR_WHITE);
	tgi_outtextxy(0, 0, "Sprite basics");
	tgi_sprite(&skullsprite);
	
	if(dirrection){
		skullsprite.hpos++;
	}else{
		skullsprite.hpos--;
	}
	if(skullsprite.hpos==0){
		dirrection=1;
	}
	if(skullsprite.hpos==120){
		dirrection=0;
	}
	if(grow){
		skullsprite.hsize+=0x0010;
		skullsprite.vsize+=0x0010;
	}else{
		skullsprite.hsize-=0x0010;
		skullsprite.vsize-=0x0010;
	}
	if(skullsprite.hsize==0x0010){
		grow=1;
	}
	if(skullsprite.hsize==0x0500){
		grow=0;
	}	
	
	tgi_updatedisplay();
}

void main(void)
{
	initialize();

	while (1)
	{
		
		if (!tgi_busy())
		{
			show_screen();
		}
	}
	return;
}