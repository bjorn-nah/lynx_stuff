#include <lynx.h>
#include <tgi.h>
#include <6502.h> 

void init_music(void)
{
  asm("jsr SndInit");
}

void start_music(void)
{
  asm("jsr SndPauseOn");
  asm("lda musicptr+0");
  asm("ldy musicptr+1");
  asm("ldx #0");
  asm("jsr SndStartSound");
  asm("lda musicptr+2");
  asm("ldy musicptr+3");
  asm("ldx #1");
  asm("jsr SndStartSound");
  asm("lda musicptr+4");
  asm("ldy musicptr+5");
  asm("ldx #2");
  asm("jsr SndStartSound");
  asm("lda musicptr+6");
  asm("ldy musicptr+7");
  asm("ldx #3");
  asm("jsr SndStartSound");
  asm("jsr SndPauseOff");
}


void main(void)
{
  tgi_install(&tgi_static_stddrv);
  tgi_init();
  CLI();
  while (tgi_busy()){};
  tgi_clear();
  tgi_setcolor(COLOR_GREEN);
  tgi_outtextxy(0, 0, "Hello World");
  tgi_updatedisplay();

  init_music();
  start_music();
  /*
  while (1){
    asm("lda $fd22");
    asm("sta $fdb0");
    asm("lda $fd32");
    asm("sta $fda0");
  };
  */
// Stop with
// asm("jsr SndStopSound");
// Pause with with
// asm("jsr SndPauseOn");
// asm("jsr SndPauseOff");
}
