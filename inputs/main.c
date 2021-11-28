#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <stdlib.h>
#include <conio.h>
#include <joystick.h> 

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
		tgi_outtextxy(16, 48, "DOWN");
	}
	if (JOY_LEFT(joy)) {
		tgi_outtextxy(16, 64, "LEFT");
	}
	if (JOY_RIGHT(joy)) {
		tgi_outtextxy(16, 80, "RIGHT");
	}
	if (JOY_BTN_1(joy)) {
		tgi_outtextxy(64, 32, "A");
	}
	if (JOY_BTN_2(joy)) {
		tgi_outtextxy(64, 48, "B");
	}

	tgi_updatedisplay();
}

void main(void)
{
	initialize();

	while (1)
	{
		if (kbhit())
		{
			switch (cgetc())
			{
			case 'F':
				tgi_flip();
				break;

			default:
				break;
			}
		}

		if (!tgi_busy())
		{
			show_screen();
		}
	}
	return;
}