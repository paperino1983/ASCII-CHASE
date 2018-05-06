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

#ifndef _WINCMOC_SOUNDS
#define _WINCMOC_SOUNDS
	#include <basic.h>
	
	#define EXPLOSION_SOUND() do {beep(100,3);} while(0);

	#define SHOOT_SOUND() do {beep(100,2);} while(0);
	
	#define PING_SOUND() do {beep(200,0);} while(0);
	#define TICK_SOUND() do {beep(220,0);} while(0);
	#define TOCK_SOUND() do {beep(140,0);} while(0);
	#define ZAP_SOUND() \
		do \
			{ \
				unsigned char i; \
				\
				for(i=0;i<70;++i) \
					beep(80+i,0); \
			} \
		while(0);
	
	// TODO: Save more memory to implement it
	#define TICK_SOUND()	
	
#endif // _WINCMOC_SOUNDS
