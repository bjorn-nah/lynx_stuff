#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <stdlib.h>
#include <conio.h>

extern unsigned char skull[];
SCB_RENONE skullsprite =  {
  BPP_4 | TYPE_NORMAL, 
  REUSEPAL, 0x01,
  0x0000,
  &skull,
  20, 50
};

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
}

void show_screen()
{
	// Clear current screen
	tgi_clear();
	
	tgi_setcolor(COLOR_WHITE);
	tgi_outtextxy(0, 0, "Sprite basics");
	tgi_sprite(&skullsprite);
	
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