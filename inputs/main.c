#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <stdlib.h>
#include <conio.h>
#include <joystick.h> 

char keyboard;
unsigned int tics;

void initialize()
{
	tgi_install(&tgi_static_stddrv);
	joy_install(&joy_static_stddrv);
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
	char text[20];
	unsigned char joy;
	
	// Clear current screen
	tgi_clear();

	tgi_setcolor(COLOR_WHITE);
	tgi_outtextxy(16, 16, "Input tester:");
	
    joy = joy_read(JOY_1);
	if (JOY_UP(joy)) {
		tgi_outtextxy(16, 32, "UP");
	}
	if (JOY_DOWN(joy)) {
		tgi_outtextxy(16, 40, "DOWN");
	}
	if (JOY_LEFT(joy)) {
		tgi_outtextxy(16, 48, "LEFT");
	}
	if (JOY_RIGHT(joy)) {
		tgi_outtextxy(16, 56, "RIGHT");
	}
	if (JOY_BTN_1(joy)) {
		tgi_outtextxy(64, 32, "A");
	}
	if (JOY_BTN_2(joy)) {
		tgi_outtextxy(64, 40, "B");
	}
	
	tgi_outtextxy(16, 72, "buttons");
	itoa(joy, text, 10);
	tgi_outtextxy(16, 80, text);
	tgi_outtextxy(80, 72, "keyboard");
	itoa(keyboard, text, 10);
	tgi_outtextxy(80, 80, text);
	
	//reset keyboard
	if(tics > 0){
		tics--;
	}else{
		keyboard = 0x00;
	}
	
	/*
	switch (cgetc())
			{
			case 'F':
				tgi_flip();
				break;

			default:
				break;
			}
			*/

	tgi_updatedisplay();
}

void main(void)
{

	initialize();

	while (1)
	{
		if (kbhit())
		{
			keyboard = cgetc();
			tics = 60;
		}

		if (!tgi_busy())
		{
			show_screen();
		}
	}
	return;
}