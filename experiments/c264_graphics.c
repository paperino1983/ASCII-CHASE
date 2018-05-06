/* --------------------------------------------------------------------------------------- */ 
// 
// CROSS CHASE by Fabrizio Caruso
//
// Fabrizio_Caruso@hotmail.com
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from
// the use of this software.

// Permission is granted to anyone to use this software for non-commercial applications, 
// subject to the following restrictions:

// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software in
// a product, an acknowledgment in the product documentation would be
// appreciated but is not required.

// 2. Altered source versions must be plainly marked as such, and must not
// be misrepresented as being the original software.

// 3. This notice may not be removed or altered from any source distribution.
/* --------------------------------------------------------------------------------------- */ 


#include <conio.h>
#include <peekpoke.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../display_macros.h"

#if defined(FULL_GAME)
	#define UDG_BASE_FACTOR 29
#else
	#define UDG_BASE_FACTOR 15
#endif

// BLUE
#define _PLAYER 0x3B
#define _PLAYER_DOWN 0x3B
#define _PLAYER_UP 0x3C
#define _PLAYER_RIGHT 0x3D 
#define _PLAYER_LEFT 0x3E

#define _GUN 0x3F

// YELLOW
#define _INVINCIBLE_GHOST 0x27
#define _VERTICAL_BRICK 0x26
#define _HORIZONTAL_BRICK 0x2B
#define _EXTRA_LIFE 0x25
#define _EXTRA_POINTS 0x24

// GREEN
#define _POWERUP  0x2C

// RED
#define _BOMB 0x5E
#define _DEAD_GHOST 0x5B
// #define _MISSILE 0x5F

// CYAN
#define _INVINCIBILITY 0x21
#define _MISSILE 0x23

// WHITE
#define _GHOST 0x7E

#define _LEFT_ENEMY_MISSILE ((unsigned char)0x7B)
#define _RIGHT_ENEMY_MISSILE ((unsigned char)0x7D)
#define _BUBBLE ((unsigned char)0x60)

#define VERTICAL_BRICK '='
#define HORIZONTAL_BRICK 62

extern Image PLAYER_IMAGE;
extern Image GHOST_IMAGE;
extern Image DEAD_GHOST_IMAGE;
extern Image INVINCIBLE_GHOST_IMAGE;
extern Image BOMB_IMAGE;
extern Image POWERUP_IMAGE;
extern Image MISSILE_IMAGE;
extern Image GUN_IMAGE;

#if defined(FULL_GAME)
	extern Image LEFT_ENEMY_MISSILE_IMAGE;
	extern Image RIGHT_ENEMY_MISSILE_IMAGE;

	extern Image BUBBLE_IMAGE;

	extern Image EXTRA_POINTS_IMAGE;
	extern Image EXTRA_LIFE_IMAGE;
	extern Image INVINCIBILITY_IMAGE;	
	
	extern Image BROKEN_WALL_IMAGE;
#endif

Image PLAYER_DOWN;
Image PLAYER_UP;
Image PLAYER_RIGHT;
Image PLAYER_LEFT;

#if defined(REDEFINED_CHARS)
struct redefine_struct
{
   unsigned char ascii;
   unsigned char bitmap[8];
} ;
#endif

#if defined(REDEFINED_CHARS)
struct redefine_struct redefine_map[] =
{
	{_PLAYER_DOWN, { 24, 36, 24,102,153, 24, 36,102}},
	{_PLAYER_UP, { 24, 60, 24,102,153, 24, 36,102}},
	{_PLAYER_RIGHT, { 24, 52, 25,118,152, 24, 20, 20}},	
	{_PLAYER_LEFT, { 24, 44,152,110, 25, 24, 40, 40}},
	{_GHOST, {129,126,165,129,129,189,129,126}},
	{_RIGHT_ENEMY_MISSILE, {  0,  0, 15,252,252, 15,  0,  0}},
	{_LEFT_ENEMY_MISSILE, {  0,  0,240, 63, 63,240,  0,  0}},
	{_INVINCIBLE_GHOST, { 60, 66,165,129, 90, 36, 36, 60}},
	{_GUN, {  0,128,126,200,248,192,128,  0}},
	{_POWERUP, {  0, 60, 54,223,231,122, 36, 24}},
	{_MISSILE, {  0,  0,  8, 56, 28, 16,  0,  0}},
	{_BOMB, { 60, 66,165,153,153,165, 66, 60}},
	{_BUBBLE, { 24, 60, 60, 60,126, 90, 66, 66}},
	{_INVINCIBILITY, { 24, 36, 24,  0,153,  0, 36,102}},
	{_VERTICAL_BRICK, { 24, 24, 24, 48, 24, 12, 24, 24}},
	{_HORIZONTAL_BRICK, {  0,  0,  0,255,  0,  0,  0,  0}}			
};
#endif

// void redefine(unsigned long loc, const unsigned char * data)
// {
	// unsigned short i;
	// for(i=0;i<8;++i)
	// {
		// POKE(loc+i,data[i]);
	// }
// }

void INIT_GRAPHICS(void)
{
	unsigned short i;
	// static const char player_down[8] =      { 24, 36, 24,102,153, 24, 36,102};
	// static const char player_up[8] =        { 24, 60, 24,102,153, 24, 36,102};
	// static const char player_right[8] =     { 24, 52, 25,118,152, 24, 20, 20};	
	// static const char player_left[8] =      { 24, 44,152,110, 25, 24, 40, 40};
	// static const char ghost[8] =            {129,126,165,129,129,189,129,126};
	// static const char missile_right[8] =    {  0,  0, 15,252,252, 15,  0,  0};
	// static const char missile_left[8] =     {  0,  0,240, 63, 63,240,  0,  0};
	// static const char invincible_ghost[8] = { 60, 66,165,129, 90, 36, 36, 60};
	// static const char gun[8] =              {  0,128,126,200,248,192,128,  0};
	// static const char powerUp[8] =          {  0, 60, 54,223,231,122, 36, 24};
	// static const char missile[8] =          {  0,  0,  8, 56, 28, 16,  0,  0};
	// static const char bomb[8] =             { 60, 66,165,153,153,165, 66, 60};
	// static const char bubble[8] =           { 24, 60, 60, 60,126, 90, 66, 66};
	// static const char invincibility[8] =    { 24, 36, 24,  0,153,  0, 36,102};	
	// static const char vertical_brick[8] =   { 24, 24, 24, 48, 24, 12, 24, 24};
	// static const char horizontal_brick[8] = {  0,  0,  0,255,  0,  0,  0,  0};	
	
	POKE(1177,62); // disable switch to RAM in PEEK
	for(i=0;i<1023;++i)
	{
		POKE(UDG_BASE_FACTOR*1024+i,PEEK((unsigned long) (54272ul+(unsigned long) i)));
	}
	POKE(1177,63); // re-enable switch to RAM in PEEK
	POKE(65299ul,(PEEK(65299ul)&3)|((UDG_BASE_FACTOR)*4)); // change character base address to 28th Kbyte
	POKE(65298ul,PEEK(65298ul)&251); // make graphics chip get characters from RAM
	
	
	for(i=0;i<sizeof(redefine_map)/sizeof(*redefine_map);++i)
	{
		memcpy(UDG_BASE_FACTOR*1024 + (redefine_map[i].ascii)*8, redefine_map[i].bitmap, 8);		
	}
	
	// redefine(UDG_BASE_FACTOR*1024+296,player_down);
	// redefine(UDG_BASE_FACTOR*1024+296+8,player_up);		
	// redefine(UDG_BASE_FACTOR*1024+296+8*2,player_right);
	// redefine(UDG_BASE_FACTOR*1024+296+8*3,player_left);
	
	// redefine(UDG_BASE_FACTOR*1024+296+8*4,missile_right);
	// redefine(UDG_BASE_FACTOR*1024+296+8*5,missile_left);	
	
	// redefine(UDG_BASE_FACTOR*1024+296+8*6,invincible_ghost);
	// redefine(UDG_BASE_FACTOR*1024+296+8*7,gun);

	// redefine(UDG_BASE_FACTOR*1024+296-8*2,powerUp);
	// redefine(UDG_BASE_FACTOR*1024+296+8*9,missile);

	// redefine(UDG_BASE_FACTOR*1024+296+8*10,bomb); //47
	// redefine(UDG_BASE_FACTOR*1024+296-8*3,ghost);
	// redefine(UDG_BASE_FACTOR*1024+296+8*22,bubble);
	// redefine(UDG_BASE_FACTOR*1024+296+8*23,invincibility);
	// redefine(UDG_BASE_FACTOR*1024+296+8*24,vertical_brick); 
	// redefine(UDG_BASE_FACTOR*1024+296+8*25,horizontal_brick);	
}
 
 
// TODO: Sprite initialization (to be performed only once) should be separated from level generation
void INIT_IMAGES(void)
{		
	PLAYER_IMAGE._color = COLOR_CYAN;
	INVINCIBLE_GHOST_IMAGE._color = COLOR_YELLOW;
	POWERUP_IMAGE._color = COLOR_BLUE;
	GUN_IMAGE._color = COLOR_BLUE;
	BOMB_IMAGE._color = COLOR_RED;
	DEAD_GHOST_IMAGE._color = COLOR_RED;


	GHOST_IMAGE._color = COLOR_WHITE;
	MISSILE_IMAGE._color = COLOR_WHITE;

	PLAYER_DOWN._color = COLOR_CYAN;
	PLAYER_UP._color = COLOR_CYAN;
	PLAYER_RIGHT._color = COLOR_CYAN;
	PLAYER_LEFT._color = COLOR_CYAN;
		

	
	#if defined(FULL_GAME)
		RIGHT_ENEMY_MISSILE_IMAGE._color = COLOR_WHITE;		
		LEFT_ENEMY_MISSILE_IMAGE._color = COLOR_WHITE;
		
		BUBBLE_IMAGE._color = COLOR_WHITE;
		
		EXTRA_POINTS_IMAGE._imageData = '$';
		EXTRA_POINTS_IMAGE._color = COLOR_YELLOW;
		
		EXTRA_LIFE_IMAGE._color = COLOR_YELLOW;
		
		INVINCIBILITY_IMAGE._color = COLOR_YELLOW;
	#endif
	
		DEAD_GHOST_IMAGE._imageData = GHOST_IMAGE._imageData;
	
		PLAYER_IMAGE._imageData = _PLAYER_DOWN;
		PLAYER_DOWN._imageData = _PLAYER_DOWN;
		PLAYER_UP._imageData = _PLAYER_UP;		
		PLAYER_RIGHT._imageData = _PLAYER_RIGHT;
		PLAYER_LEFT._imageData = _PLAYER_LEFT;	
		
		GHOST_IMAGE._imageData = _GHOST;
		INVINCIBLE_GHOST_IMAGE._imageData = _INVINCIBLE_GHOST;
		BOMB_IMAGE._imageData = _BOMB;		
		POWERUP_IMAGE._imageData = _POWERUP;
		GUN_IMAGE._imageData = _GUN;
		MISSILE_IMAGE._imageData = _MISSILE;

		#if defined(FULL_GAME)
			LEFT_ENEMY_MISSILE_IMAGE._imageData = _LEFT_ENEMY_MISSILE;
			RIGHT_ENEMY_MISSILE_IMAGE._imageData = _RIGHT_ENEMY_MISSILE;		
			BUBBLE_IMAGE._imageData = _BUBBLE;
			INVINCIBILITY_IMAGE._imageData = _INVINCIBILITY;
			EXTRA_LIFE_IMAGE._imageData = PLAYER_DOWN._imageData;			
		#endif	
}

#if defined(FULL_GAME)
	void DRAW_BROKEN_WALL(char x, char y)
	{
		gotoxy((x+X_OFFSET),(y+Y_OFFSET)); 
		(void) textcolor (COLOR_RED);
		cputc(BOMB_IMAGE._imageData);
	}
#endif

void _draw(char x, char y, Image * image) 
{
	gotoxy((x+X_OFFSET),(y+Y_OFFSET)); 
	(void) textcolor (image->_color);
	cputc(image->_imageData); 
};

void _blink_draw(unsigned char x, unsigned char y, Image * image, unsigned char * blinkCounter)
{
	gotoxy((x+X_OFFSET),(y+Y_OFFSET)); 
	SET_TEXT_COLOR(image->_color);
	if(*blinkCounter) 
	{
		cputc(image->_imageData); 
		*blinkCounter=0;
	} 
	else 
	{
		cputc(' '); 
		*blinkCounter=1;
	}	
}	


void _delete(char x, char y)
{
	gotoxy(x+X_OFFSET,y+Y_OFFSET); cputc(' ');
};

void DRAW_HORIZONTAL_LINE(unsigned char x,unsigned char y, unsigned char length) 
{
	unsigned char i;
	SET_TEXT_COLOR(COLOR_YELLOW);

	for(i=0;i<length;++i) 
	{ 
		gotoxy(x+i+X_OFFSET,y+Y_OFFSET);  cputc(HORIZONTAL_BRICK);
	} 	
}


void DRAW_VERTICAL_LINE(unsigned char x,unsigned char y, unsigned char length) 
{
	unsigned char i;
	SET_TEXT_COLOR(COLOR_YELLOW);

	for(i=0;i<length;++i) 
	{ 
		gotoxy(x+X_OFFSET,y+Y_OFFSET+i);  cputc(VERTICAL_BRICK);
	} 	
}

