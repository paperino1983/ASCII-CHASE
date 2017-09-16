/*****************************************************************************/
/*                                                                           */
/*                                		                                     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 2017      Fabrizio Caruso                                  		     */
/*                					                                         */
/*              				                                             */
/* EMail:        Fabrizio_Caruso@hotmail.com                                 */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/
 
#include "text.h"

#include "display_macros.h"

#include "settings.h"

#include "sleep_macros.h"

#ifdef __ATMOS__
	#include<peekpoke.h>
#endif


extern unsigned char XSize;
extern unsigned char YSize;

extern unsigned char level;
extern unsigned char lives;
extern unsigned char guns;
extern unsigned int points;
extern unsigned char ghostCount;
extern unsigned short ghostLevel;
extern unsigned int highScore;

extern Image PLAYER_IMAGE;
extern Image GHOST_IMAGE;
extern Image GUN_IMAGE;
extern Image INVINCIBLE_GHOST_IMAGE;
extern Image PLAYER_IMAGE;
extern Image MISSILE_IMAGE;

#if defined(FULL_GAME)
	#if defined(__C64__)
		void printKillTheSkull(void)
		{
			printCenteredMessage("kill the skull!");	
		}
	#else
		void printKillTheSkull(void)
		{
			printCenteredMessage("Kill the skull!");
		}	
	#endif	
#endif

// TODO: This is SLOW
void displayStatsTitles(void)
{	
	#if defined(__CBM__) && !defined(__VIC20__) && !defined(__C16__)
		SET_TEXT_COLOR(COLOR_BLUE);		
		//PRINT(2-X_OFFSET,0-Y_OFFSET,"speed:");
		PRINT(2-X_OFFSET,0-Y_OFFSET,"score:");
		PRINT(2-X_OFFSET,1-Y_OFFSET,"level:");
		SET_TEXT_COLOR(TEXT_COLOR);
		
		SET_TEXT_COLOR(COLOR_RED);	
		PRINT(24,0-Y_OFFSET,"-----------");
		PRINT(24,1-Y_OFFSET,"cross chase");
		//PRINT(24,2-Y_OFFSET,"-----------");
		SET_TEXT_COLOR(TEXT_COLOR);
	#elif defined(__ATMOS__)
		//PRINT(2,0-Y_OFFSET,"SPEED:");
		PRINT(2,0-Y_OFFSET,"SCORE:");
		PRINT(2,1-Y_OFFSET,"LEVEL:");
		
		POKE(0xBB80+22+0*40,10);
		POKE(0xBB80+22+1*40,10);	
		
		gotoxy(23,0); 
		cputc('C'+128); 
		cputc('R'+128);
		cputc('O'+128); 
		cputc('S'+128); 
		cputc('S'+128); 
		cputc(' '+128);	
		cputc('C'+128);
		cputc('H'+128);		
		cputc('A'+128);	
		cputc('S'+128);		
		cputc('E'+128); 
		
		gotoxy(23,1); 
		cputc('C'+128); 
		cputc('R'+128);
		cputc('O'+128); 
		cputc('S'+128); 
		cputc('S'+128); 
		cputc(' '+128);	
		cputc('C'+128);	
		cputc('H'+128);
		cputc('A'+128);
		cputc('S'+128);	
		cputc('E'+128); 		
	#elif defined(__ATARI5200__) || ((defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1))
		//SET_TEXT_COLOR(TEXT_COLOR);	
		// PRINT(0,0-Y_OFFSET,"SC:");
		//PRINT(1,1-Y_OFFSET,"LEVEL:");
	#elif defined(__MSX__)
			PRINT(2,-Y_OFFSET+1,"SCORE:");
			PRINT(2,-Y_OFFSET+2,"LEVEL:");	
	#elif defined(__VG5K__)
			PRINT(2,-Y_OFFSET,"SCORE:");
			PRINT(2,-Y_OFFSET+1,"LEVEL:");
			// 2 green
			// 3 cyan
			// 4 red
			SET_TEXT_COLOR(4);	
			PRINT(24,-Y_OFFSET+1,"CROSS CHASE");	
	#elif defined(__CPC__)
			PRINT(0,0-Y_OFFSET,"SCORE:");
			PRINT(0,1-Y_OFFSET,"LEVEL:");
	#elif defined(__AQUARIUS__)		
	#elif defined(__ZX81__)		
	#elif defined(__ZX80__)		
	#elif defined(__ATARI5200__)
	#elif defined(__ENTERPRISE__)
	#elif defined(__SC3000__)		
	#elif defined(__TRS80__)	
	#elif defined(__SVI__)		
	#elif defined(__VZ__)	
	#elif defined(__MTX__)	
	#elif defined(__ACE__)	
			PRINT(2,-Y_OFFSET+1,"SCORE:");
			PRINT(2,-Y_OFFSET+2,"LEVEL:");		
	#else
		SET_TEXT_COLOR(TEXT_COLOR);	
		#if defined(__VIC20__) || defined(__C16__)
			PRINT(0,0-Y_OFFSET,"SCORE:");
			PRINT(0,1-Y_OFFSET,"LEVEL:");		
		#else
			PRINT(2,0-Y_OFFSET,"SCORE:");
			PRINT(2,1-Y_OFFSET,"LEVEL:");
		#endif
		#if !(defined(__SPECTRUM__) && defined(SPECTRUM_32COL)) && !defined(__VIC20__) && (!defined(__ATARI__) && !defined(__ATARIXL__) || !defined(ATARI_MODE1))
			SET_TEXT_COLOR(TEXT_COLOR);	
			PRINT(24,0-Y_OFFSET,"CROSS CHASE");
			SET_TEXT_COLOR(TEXT_COLOR);	
		#endif
	#endif

	
	#if defined (__ATMOS__)
		gotoxy(18+1,0); cputc(GUN_IMAGE._imageData);//cputc(':');
		gotoxy(18-3,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1); cputc(PLAYER_IMAGE._imageData);cputc(':');	
	#elif defined(__ATARI5200__) || ((defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1))
		SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(15+1-5,0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(15-3-2-3,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(15+1-5+4-1,0); cputc(PLAYER_IMAGE._imageData);cputc(':');		
		// gotoxy(15+20,0); cputc(PLAYER_IMAGE._imageData);cputc(':');
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(18+1,0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1); cputc(PLAYER_IMAGE._imageData);cputc(':');
	#elif defined(__CPC__)	 
		// TODO: to implement
		// SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(18+1,0+1); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3,0+1); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1+1); cputc(PLAYER_IMAGE._imageData);cputc(':');	
	#elif defined(__AQUARIUS__)		
	#elif defined(__ZX81__)		
	#elif defined(__ZX80__)	
	#elif defined(__ATARI5200__)
	#elif defined(__ENTERPRISE__)	
	#elif defined(__SC3000__)			
	#elif defined(__MTX__)	
	#elif defined(__TRS80__)	
	#elif defined(__SVI__)	
	#elif defined(__VZ__)	
	#elif defined(__ACE__)	
		gotoxy(18+1,1+0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3,1+0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1+1); cputc(PLAYER_IMAGE._imageData);cputc(':');	
	#elif defined(__MSX__)
		SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(18+1,1+0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3,1+0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1+1); cputc(PLAYER_IMAGE._imageData);cputc(':');	
	#elif defined(__VG5K__)	
		//SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(1+18+1,1+0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(1+18-3,1+0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(1+18,1+1); cputc(PLAYER_IMAGE._imageData);cputc(':');				
	#elif defined(__VIC20__)
		SET_TEXT_COLOR(TEXT_COLOR);		
		gotoxy(18+1-2,0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3-2,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18-2,1); cputc(PLAYER_IMAGE._imageData);cputc(':');
	#else
		SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(18+1,0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1); cputc(PLAYER_IMAGE._imageData);cputc(':');
	#endif

}


void printGunsStats(void)
{
	SET_TEXT_COLOR(TEXT_COLOR);
	
	#if defined (__ATMOS__)
		PRINTF(19-1+1,0-Y_OFFSET,"%hu",guns);
	#elif defined(__ATARI5200__) || ((defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1))
		PRINTF(15+2+1-5-1-X_OFFSET,0-Y_OFFSET,"%hu",guns);
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		PRINTF(18+2+1-X_OFFSET,0-Y_OFFSET,"%hu",guns);
	#elif defined(__SPECTRUM__) 
		PRINTF(18+2+1-X_OFFSET,0-Y_OFFSET,"%d",guns);	
	#elif defined(__CPC__) 	
		PRINTF(18+2+1-X_OFFSET,1+0-Y_OFFSET,"%u",guns);	
	#elif defined(__AQUARIUS__)		
	#elif defined(__ZX81__)	
	#elif defined(__ZX80__)	
	#elif defined(__ATARI5200__)
	#elif defined(__ENTERPRISE__)
	#elif defined(__SC3000__)			
	#elif defined(__MTX__)	
	#elif defined(__TRS80__)	
	#elif defined(__SVI__)	
	#elif defined(__VZ__)	
	#elif defined(__ACE__)
		PRINTF(18+2+1-X_OFFSET,1+0-Y_OFFSET,"%u",guns);		
	#elif defined(__MSX__)	
		PRINTF(18+2+1-X_OFFSET,1+0-Y_OFFSET,"%u",guns);	
	#elif defined(__VG5K__)	
		PRINTF(1+18+2+1-X_OFFSET,0-Y_OFFSET,"%u",guns);			
	#else
		PRINTF(18+2+1-X_OFFSET,0-Y_OFFSET,"%hu",guns);
	#endif			
}

void printLevelStats(void)
{	
	SET_TEXT_COLOR(TEXT_COLOR);
	
	#if defined(__ATMOS__) 
		PRINTF(8,1-Y_OFFSET,"%02hu", level);
	#elif defined(__ATARI5200__) || ((defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1))
		PRINTF(15+2+1-5+4-1+2-X_OFFSET,0-Y_OFFSET,"%02hu",level);	
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || (defined(__CBM__) && !defined(__VIC20__) && !defined(__C16__)) 
		PRINTF(8,1-Y_OFFSET,"%02hu", level);
	#elif defined(__SPECTRUM__) 
		PRINTF(8,1-Y_OFFSET,"%02d", level);	
	#elif defined(__CPC__)
		PRINTF(8,2-Y_OFFSET,"%02u", level);
	#elif defined(__AQUARIUS__)
	#elif defined(__ZX81__)	
	#elif defined(__ZX80__)	
	#elif defined(__ATARI5200__)
	#elif defined(__ENTERPRISE__)
	#elif defined(__SC3000__)			
	#elif defined(__MTX__)	
	#elif defined(__TRS80__)		
	#elif defined(__SVI__)	
	#elif defined(__VZ__)	
	#elif defined(__ACE__)	
		PRINTF(8,1+1-Y_OFFSET,"%02u", level);		
	#elif defined(__MSX__)
		PRINTF(8,1+1-Y_OFFSET,"%02u", level);	
	#elif defined(__VG5K__)
		PRINTF(8,1-Y_OFFSET,"%02u", level);			
	#elif defined(__VIC20__) || defined(__C16__)
		PRINTF(8-2,1-Y_OFFSET,"%02hu", level);	
	#else
		PRINTF(8,1-Y_OFFSET,"%02hu", level);	
	#endif	
}

void printGhostCountStats(void)
{
	SET_TEXT_COLOR(TEXT_COLOR);
	
	#if defined (__ATMOS__)
		PRINTF(19-1-3,0-Y_OFFSET,"%hu",ghostCount);
	#elif defined(__ATARI5200__) || ((defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1))
		PRINTF(15+2-X_OFFSET-3-2-3,0-Y_OFFSET,"%hu",ghostCount);
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		PRINTF(18+2-X_OFFSET-3,0-Y_OFFSET,"%hu",ghostCount);
	#elif defined(__SPECTRUM__)
		PRINTF(18+2-X_OFFSET-3,0-Y_OFFSET,"%d",ghostCount);
	#elif defined(__CPC__)
		PRINTF(18+2-X_OFFSET-3,1+0-Y_OFFSET,"%u",ghostCount);
	#elif defined(__AQUARIUS__)
	#elif defined(__ZX81__)	
	#elif defined(__ZX80__)	
	#elif defined(__ATARI5200__)
	#elif defined(__ENTERPRISE__)	
	#elif defined(__SC3000__)			
	#elif defined(__MTX__)	
	#elif defined(__TRS80__)
	#elif defined(__SVI__)	
	#elif defined(__VZ__)	
	#elif defined(__ACE__)	
		PRINTF(18+2-X_OFFSET-3,1+0-Y_OFFSET,"%u",ghostCount);	
	#elif defined(__MSX__)	
		PRINTF(18+2-X_OFFSET-3,1+0-Y_OFFSET,"%u",ghostCount);
	#elif defined(__VG5K__)	
		PRINTF(1+18+2-X_OFFSET-3,0-Y_OFFSET,"%u",ghostCount);		
	#else
		PRINTF(18+2-X_OFFSET-3,0-Y_OFFSET,"%hu",ghostCount);
	#endif		
}

void printLivesStats(void)
{
	SET_TEXT_COLOR(TEXT_COLOR);
		
	#if defined (__ATMOS__)
		PRINTF(19-1,1-Y_OFFSET,"%02hu",lives);	
	#elif defined(__ATARI5200__) || ((defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1))
		PRINTF(15+2+1-5+4-1-X_OFFSET,0-Y_OFFSET,"%hu",lives);		
		// PRINTF(15+2-X_OFFSET,1-Y_OFFSET,"%02hu",lives);
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		PRINTF(18+2-X_OFFSET,1-Y_OFFSET,"%02hu",lives);
	#elif defined(__SPECTRUM__)
		PRINTF(18+2-X_OFFSET,1-Y_OFFSET,"%02d",lives);
	#elif defined(__CPC__)
		PRINTF(18+2-X_OFFSET,1+1-Y_OFFSET,"%02u",lives);
	#elif defined(__AQUARIUS__)		
	#elif defined(__ZX81__)	
	#elif defined(__ZX80__)	
	#elif defined(__ATARI5200__)
	#elif defined(__ENTERPRISE__)
	#elif defined(__SC3000__)			
	#elif defined(__MTX__)	
	#elif defined(__TRS80__)
	#elif defined(__SVI__)		
	#elif defined(__VZ__)	
	#elif defined(__ACE__)
		PRINTF(18+2-X_OFFSET,1+1-Y_OFFSET,"%02u",lives);	
	#elif defined(__MSX__)	
		PRINTF(18+2-X_OFFSET,1+1-Y_OFFSET,"%02u",lives);	
	#elif defined(__VG5K__)
		PRINTF(1+18+2-X_OFFSET,1-Y_OFFSET,"%02u",lives);		
	#else
		PRINTF(18+2-X_OFFSET,1-Y_OFFSET,"%02hu",lives);
	#endif		
}

void displayStats(void)
{	
	SET_TEXT_COLOR(TEXT_COLOR);
	
	#if defined(__ATMOS__) 
		PRINTF(8,0-Y_OFFSET,"%05u0",points);
	#elif defined(__ATARI5200__) || ((defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1))
		PRINTF(3-3,0-Y_OFFSET,"%05u0",points);
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || (defined(__CBM__) && !defined(__VIC20__) && !defined(__C16__)) 
		PRINTF(8,0-Y_OFFSET,"%05u0",points);
	#elif defined(__SPECTRUM__)
		PRINTF(8,0-Y_OFFSET,"%05u0",points);
	#elif defined(__CPC__)
		PRINTF(8,1-Y_OFFSET,"%05u0",points);
	#elif defined(__AQUARIUS__)		
	#elif defined(__ZX81__)	
	#elif defined(__ZX80__)	
	#elif defined(__ATARI5200__)
	#elif defined(__ENTERPRISE__)
	#elif defined(__SC3000__)			
	#elif defined(__MTX__)	
	#elif defined(__TRS80__)	
	#elif defined(__SVI__)		
	#elif defined(__VZ__)	
	#elif defined(__ACE__)	
		PRINTF(8,1-Y_OFFSET,"%05u0",points);	
	#elif defined(__MSX__)
		PRINTF(8,1-Y_OFFSET,"%05u0",points);	
	#elif defined(__VG5K__)
		PRINTF(8,0-Y_OFFSET,"%05u0",points);			
	#elif defined(__VIC20__) || defined(__C16__)
		PRINTF(8-2,0-Y_OFFSET,"%05u0",points);	
	#else
		PRINTF(8,0-Y_OFFSET,"%05u0",points);
	#endif
}

void setScreenColors(void)
{
	#if !(defined(__CBM__) || defined(__ATARI__) || defined(__ATARIXL__) || defined(__APPLE2__) || defined(__APPLE2ENH__))
	#else
		SET_TEXT_COLOR(TEXT_COLOR);
		
		SET_BORDER_COLOR(BORDER_COLOR);
		
		SET_BACKGROUND_COLOR(BACKGROUND_COLOR);
	#endif
}



void printCenteredMessageOnRow(unsigned char row, char *Text)
{
	PRINTF((XSize - strlen (Text)) / 2, row,"%s", Text);
}

void printCenteredMessage(char *Text)
{
	printCenteredMessageOnRow(YSize / 2, Text);
	
}

#if defined (__C64__)
	void printLevel(void)
	{
		char levelString[22];

		sprintf(levelString, "level %d", level);

		printCenteredMessage(levelString);
	}
#elif defined(__CPC__)
	void printLevel(void) {}
#elif defined(__ZX81__)
	void printLevel(void) {}
#elif defined(__VZ__)
	void printLevel(void) {}
#else
	void printLevel(void)
	{
		char levelString[22];

		sprintf(levelString, "LEVEL %d", level);

		printCenteredMessage(levelString);
	}
#endif

#if defined (__VG5K__)
void _printScore(char * text, unsigned int score)
{
	char levelString[22];

	sprintf(levelString, text, score);

	printCenteredMessage(levelString);	
}
#elif defined(__VZ__)
	void _printScore(char * text, unsigned int score) {}
#else
void _printScore(char * text, unsigned int score)
{
	char levelString[22];

	sprintf(levelString, text, score);

	printCenteredMessage(levelString);
}
#endif

#if defined(__VG5K__)
	void gameCompleted(void)	
	{
		printCenteredMessage("DONE!"); 
	}
#elif defined(__C64__)
	void gameCompleted(void)
	{
		printCenteredMessage("y o u   m a d e   i t !"); 
	}
#elif defined(__VZ__)
	void gameCompleted(void)
	{}
#else
	void gameCompleted(void)
	{
		printCenteredMessage("Y O U  M A D E  I T!"); 
	}
#endif


#if defined(__VG5K__)
		void printPressKeyToStart(void)
		{
			printCenteredMessage("PRESS ANY KEY");
		}

		void deleteCenteredMessage(void)
		{
			printCenteredMessage("                       ");
		}

		void printGameOver(void)
		{
			printCenteredMessage("GAME OVER");
		}

		void printVictoryMessage(void)
		{
			printCenteredMessage("YOU WON!");
		}

		void printDefeatMessage(void)
		{
			printCenteredMessage("YOU LOST!");
		}	
#elif defined(__VZ__)
		void printPressKeyToStart(void)
		{}

		void deleteCenteredMessage(void)
		{
			printCenteredMessage("                       ");
		}

		void printGameOver(void)
		{
			printCenteredMessage("GAME OVER");
		}

		void printVictoryMessage(void)
		{
			printCenteredMessage("YOU WON!");
		}

		void printDefeatMessage(void)
		{
			printCenteredMessage("YOU LOST!");
		}	
#elif defined(__VIC20__) || defined(__ATARI__) || defined(__ATARIXL__)
		void printPressKeyToStart(void)
		{
			printCenteredMessage("PRESS ANY KEY");
		}
		
		void deleteCenteredMessage(void)
		{
			printCenteredMessage("                      ");
		}
		
		void printGameOver(void)
		{
			printCenteredMessage("G A M E  O V E R");
		}

		void printVictoryMessage(void)
		{
			printCenteredMessage("Y O U  W O N !");
		}

		void printDefeatMessage(void)
		{
			printCenteredMessage("Y O U  L O S T !");
		}		
#elif defined(__C16__)
		void printPressKeyToStart(void)
		{
			printCenteredMessage("PRESS ANY KEY TO START");
		}	
		
		void deleteCenteredMessage(void)
		{                                           
			printCenteredMessage("                      ");
		}
		
		void printGameOver(void)
		{
			printCenteredMessage("G A M E  O V E R");
		}

		void printVictoryMessage(void)
		{
			printCenteredMessage("Y O U  W O N !");
		}

		void printDefeatMessage(void)
		{
			printCenteredMessage("Y O U  L O S T !");
		}		
#elif defined(__C64__)
		void printPressKeyToStart(void)
		{
			printCenteredMessage("press any key to start");
		}	
		
		void deleteCenteredMessage(void)
		{
			printCenteredMessage("                      ");
		}	

		void printGameOver(void)
		{
			printCenteredMessage("g a m e   o v e r");
		}

		void printVictoryMessage(void)
		{
			printCenteredMessage("y o u   w o n !");
		}

		void printDefeatMessage(void)
		{
			printCenteredMessage("y o u   l o s t !");
		}
#else
		void printPressKeyToStart(void)
		{
			printCenteredMessage("PRESS ANY KEY TO START");
		}	
		
		void deleteCenteredMessage(void)
		{
			printCenteredMessage("                      ");
		}	

		void printGameOver(void)
		{
			printCenteredMessage("G A M E  O V E R");
		}

		void printVictoryMessage(void)
		{
			printCenteredMessage("Y O U  W O N !");
		}

		void printDefeatMessage(void)
		{
			printCenteredMessage("Y O U  L O S T !");
		}		
#endif



// SPLASH SCREEN

#if defined(__C64__) && defined(REDEFINED_CHARS)
	void c64_splash_title(void)
	{
		SET_TEXT_COLOR(COLOR_RED);
		PRINT((XSize - 22) / 2, 2, "c r o s s   c h a s e");
		SET_TEXT_COLOR(COLOR_BROWN);
		PRINT((XSize - 22) / 2, YSize / 2 - 7,  "by fabrizio caruso");
		SET_TEXT_COLOR(TEXT_COLOR);	
	}
#endif

	
#if defined(__ATMOS__) && defined(FULL_GAME)
	void atmos_splash_title(void)
	{
		POKE(0xBB80+3*40,16);POKE(0xBB80+1+3*40,1); POKE(0xBB80+2+3*40,14);
		POKE(0xBB80+4*40,16);POKE(0xBB80+1+4*40,1); POKE(0xBB80+2+4*40,14);
		POKE(0xBB80+5*40,16);POKE(0xBB80+1+5*40,1); POKE(0xBB80+2+5*40,14);
		
		POKE(0xBB80+6*40,16);POKE(0xBB80+1+6*40,3); POKE(0xBB80+2+6*40,10);
		POKE(0xBB80+7*40,16);POKE(0xBB80+1+7*40,3); POKE(0xBB80+2+7*40,10);
		
		POKE(0xBB80+8*40,16);POKE(0xBB80+1+8*40,1); POKE(0xBB80+2+8*40,10);
		POKE(0xBB80+9*40,16);POKE(0xBB80+1+9*40,1); POKE(0xBB80+2+9*40,10);
		POKE(0xBB80+10*40,16);POKE(0xBB80+1+10*40,3); POKE(0xBB80+2+10*40,10);
		POKE(0xBB80+11*40,16);POKE(0xBB80+1+11*40,3); POKE(0xBB80+2+11*40,10);

		gotoxy(19,6); cputc(PLAYER_IMAGE._imageData);
		gotoxy(19,7); cputc(PLAYER_IMAGE._imageData);
		
		gotoxy(15,10); cputc(GHOST_IMAGE._imageData);
		gotoxy(15,11); cputc(GHOST_IMAGE._imageData);
		
		gotoxy(19,10); cputc(INVINCIBLE_GHOST_IMAGE._imageData);
		gotoxy(19,11); cputc(INVINCIBLE_GHOST_IMAGE._imageData);
		
		gotoxy(23,10); cputc('>');
		gotoxy(23,11); cputc('>');
		
		gotoxy(9, 5); 
		cputc('C'); 
		cputc(' ');
		cputc('R');
		cputc(' ');
		cputc('O');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc(' ');
		cputc(' ');		
		cputc('C');
		cputc(' ');		
		cputc('H');
		cputc(' ');		
		cputc('A');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc('E'); 
		
		gotoxy(9, 4); 
		cputc('C'); 
		cputc(' ');
		cputc('R');
		cputc(' ');
		cputc('O');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc(' ');
		cputc(' ');		
		cputc('C');
		cputc(' ');		
		cputc('H');
		cputc(' ');		
		cputc('A');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc('E'); 		
	}
#endif


#if defined(__C64__)
	void c64_splash_instructions(void)
	{
		PRINT((XSize - 22) / 2, YSize / 2 - 3, "escape the enemies");
		
		PRINT((XSize - 22) / 2, YSize / 2 - 1, "force them into the mines");
		
		PRINT((XSize - 22) / 2, YSize / 2 + 1, "catch the gun for bullets");
	}
#endif


#if defined(__ATMOS__) && defined(FULL_GAME)
	void atmos_splash_instructions(void)
	{
		PRINT(7, YSize / 2 - 1, "Escape from the enemies");
		
		PRINT(7, YSize / 2, "Force them into the mines");
		POKE(0xBB80+(YSize / 2 + 4 + 1)*40,16);POKE(0xBB81+(YSize / 2 + 4 +1)*40,4);
		POKE(0xBB80+(YSize / 2 + 4 + 2)*40,16);POKE(0xBB81+(YSize / 2 + 4 +2)*40,4);
		POKE(0xBB80+(YSize / 2 + 4 + 3)*40,16);POKE(0xBB81+(YSize / 2 + 4 +3)*40,4);	

		POKE(0xBB80+(YSize / 2 + 4 + 4)*40,16);POKE(0xBB81+(YSize / 2 + 4 +4)*40,12);
		POKE(0xBB80+(YSize / 2 + 4 + 5)*40,16);POKE(0xBB81+(YSize / 2 + 4 +5)*40,12);
		POKE(0xBB80+(YSize / 2 + 4 + 6)*40,16);POKE(0xBB81+(YSize / 2 + 4 +6)*40,12);

		gotoxy(19,8); cputc(MISSILE_IMAGE._imageData);
		gotoxy(19,9); cputc(MISSILE_IMAGE._imageData);			
	}
#endif

 
void printStartMessage(void)
{
	#if defined(__C64__) && defined(REDEFINED_CHARS)
		c64_splash_title();
	#elif defined(__ATMOS__) && defined(FULL_GAME) && defined(REDEFINED_CHARS)
		atmos_splash_title();
	#else
		SET_TEXT_COLOR(COLOR_RED);
		printCenteredMessageOnRow(3, "C R O S S  C H A S E");
		SET_TEXT_COLOR(TEXT_COLOR);			
		printCenteredMessageOnRow(5, "by Fabrizio Caruso");
	#endif
	
	#if defined(__PLUS4__) || defined(__C16__)
		SET_TEXT_COLOR(COLOR_CYAN);	
	#else
		SET_TEXT_COLOR(COLOR_BLUE);
	#endif // __PLUS4__

	#if defined(__C64__) 
		c64_splash_instructions();
	#elif defined(__ATMOS__) && defined(FULL_GAME) && defined(REDEFINED_CHARS)
		atmos_splash_instructions();
	#else
		printCenteredMessageOnRow(YSize/2-1, "Lure the enemies");
		printCenteredMessageOnRow(YSize/2+1, "into the mines");
	#endif

	SET_TEXT_COLOR(TEXT_COLOR);		
	
	#if defined(JOYSTICK_CONTROL) || defined(__MSX__)
		printCenteredMessageOnRow(YSize-2, "use the joystick");
	#else
		#if defined(__ATMOS__)
			printCenteredMessageOnRow(YSize-8, "use w a s d space");
		#else
			printCenteredMessageOnRow(YSize-4, "use i j k l space");			
		#endif
	#endif	

}



