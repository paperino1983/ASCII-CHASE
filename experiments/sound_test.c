#include <psg.h>
#include <conio.h>

#define A_PERIOD_LOW 0
#define A_PERIOD_HI 1

#define B_PERIOD_LOW 2
#define B_PERIOD_HI 3

#define C_PERIOD_LOW 4
#define C_PERIOD_HI 5
	
#define NOISE 6
#define CONTROL 7

#define A_VOLUME 8
#define B_VOLUME 9
#define C_VOLUME 10
	
#define ENV_PERIOD_LOW 11
#define ENV_PERIOD_HI 12

#define ENV_WAVE 13
	
void ZAP_SOUND(void) 
{
	unsigned char control;
	unsigned char i;
	unsigned char j;
	
	set_psg(A_VOLUME,15);
	
	set_psg(A_PERIOD_LOW,255);
	set_psg(A_PERIOD_HI, 15);
	
	control = get_psg(CONTROL);
	set_psg(CONTROL, get_psg(CONTROL) & (0xFF  - 0x01));
	
	for(i=0;i<16;i++)
	{
		set_psg(A_PERIOD_HI,15-i);		
		for(j=0;j<150;++j)
		{
		}
	}
	
	set_psg(CONTROL, control);

	set_psg(A_VOLUME,0);		
}


void _ping_sound(unsigned char freq)
{ 
	unsigned char control;
	unsigned char i;
	
	set_psg(A_VOLUME,15);
	set_psg(A_PERIOD_LOW,255);
	set_psg(A_PERIOD_HI, 15 - (freq>>4));		

	control = get_psg(CONTROL);		
	set_psg(CONTROL, control & (0xFF - 0x01));
	
	for(i=0;i<220;++i)
	{
	}
	
	set_psg(CONTROL, control);		
	set_psg(A_VOLUME,0);		
}			


void _explosion_sound(unsigned char freq)
{ 
	unsigned char control;
	unsigned char i;
	unsigned char j;
	
	set_psg(NOISE,15);
	set_psg(A_VOLUME,15);
	
	set_psg(A_PERIOD_LOW,0);
	set_psg(A_PERIOD_HI, 15 - (freq>>4));
	
	control = get_psg(CONTROL);
	set_psg(CONTROL, get_psg(CONTROL) & (0xFF - 0x08));
	
	for(i=0;i<13;i++)
	{
		set_psg(A_VOLUME,15-i);		
		for(j=0;j<253;++j)
		{
		}		
	}

	set_psg(CONTROL, control);
	set_psg(A_VOLUME,0);		
}



int main()
{
	
	clrscr();
	
	do
	{
		ZAP_SOUND();
		gotoxy(2,2); cprintf("zap");

		_ping_sound(100);
		gotoxy(2,5); cprintf("ping");
		
		_explosion_sound(100);
		gotoxy(2,8); cprintf("explosion");
	}
	while(!kbhit());
	
	return 0;
}
