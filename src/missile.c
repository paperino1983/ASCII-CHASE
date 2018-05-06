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
 
#if !defined(TINY_GAME) 
 
#include "missile.h"
#include "settings.h"
#include "sound_macros.h"
#include "display_macros.h"
#include "level.h"
#include "text.h"
#include "character.h"
#include "item.h"
#include "enemy.h"
#include "strategy.h"

// TODO: DEBUG
#include "sleep_macros.h"

extern unsigned short points;
extern unsigned char ghostCount;
extern Character ghosts[GHOSTS_NUMBER];
extern Image DEAD_GHOST_IMAGE;
extern unsigned char level;

extern Item extraPoints;

extern Character invincibleGhost;
extern unsigned char invincibleGhostHits;
extern unsigned char invincibleGhostAlive;
extern unsigned char playerFire;
extern unsigned char guns;
extern unsigned char playerDirection;
extern unsigned char missileDirection;

extern Character missile;
extern Character player;


	
#if defined(FULL_GAME) 
	extern Item freeze;
	extern Item extraLife;
	extern Item invincibility;
	
	extern Character chasingBullet;
	
	extern Character leftEnemyMissile;
	extern Character rightEnemyMissile;
	extern unsigned char bubbles_x[BUBBLES_NUMBER];
	extern Character bubbles[BUBBLES_NUMBER];
	extern unsigned char dead_bubbles;
	extern unsigned char missileBasesDestroyed;

	extern Character *chasedEnemyPtr;	
#endif

#if defined(FULL_GAME)
	void handle_chasing_bullet(void)
	{
		if(chasingBullet._status)
		{
			deleteMissile(&chasingBullet);
			#if !defined(SIMPLE_STRATEGY)
				moveTowardCharacter(chasedEnemyPtr, &chasingBullet, 4);
			#else
				moveTowardCharacter(chasedEnemyPtr, &chasingBullet);				
			#endif
			displayMissile(&chasingBullet);
			checkMissile(&chasingBullet);
		}	
	}
#endif
	
void handle_missile(void)
{
	// Check if player has fired the gun
	if(playerFire && missile._status==0 && guns>0)
	{
		SHOOT_SOUND();
		--guns;
		printGunsStats();
		missileDirection = playerDirection;
		missile._status = setMissileInitialPosition(&missile, &player, missileDirection);
		playerFire = 0;
		displayMissile(&missile);					
	}
	
	// Move missile if fired
	if(missile._status==1)
	{
		moveMissile(&missile, missileDirection);
		checkMissile(&missile);
	}
}


void checkMissile(Character *missilePtr)
{
	checkMissileVsInvincibleGhost(missilePtr);
	checkMissileVsGhosts(missilePtr);
}

void checkMissileVsGhost(Character * missilePtr,
						 Character * ghostPtr)
{
	if(ghostPtr->_status && 
	   areCharctersAtSamePosition(missilePtr, ghostPtr))
	{
		points+=GHOST_VS_MISSILE;
		ghostPtr->_imagePtr = (Image *)&DEAD_GHOST_IMAGE;
		ghostDies(ghostPtr);
		die(missilePtr);
	}
}
	
void checkMissileVsGhosts(Character * missilePtr)
{
	unsigned char i = 0;
	for(;i<GHOSTS_NUMBER;++i)
	{
		if(ghosts[i]._status)
		{
			checkMissileVsGhost(missilePtr, &ghosts[i]);
		}
	};
}

void checkMissileVsInvincibleGhost(Character *bulletPtr)
{
	if(invincibleGhost._status && 
	   areCharctersAtSamePosition(bulletPtr, &invincibleGhost))
	{
		PING_SOUND();
		die(bulletPtr);
		deleteMissile(bulletPtr);
		bulletPtr->_x = 0; bulletPtr->_y = 0;
		++invincibleGhostHits;
		decreaseGhostLevel();
		reducePowerUpsCoolDowns();
		
		if(invincibleGhostHits>=MIN_INVINCIBLE_GHOST_HITS)
		{
			invincibleGhost._status = 0;
			deleteInvincibleGhost(&invincibleGhost);
			invincibleGhost._x=XSize-2; 
			invincibleGhost._y=YSize-2;
			invincibleGhostAlive = 0;
			EXPLOSION_SOUND();
			points+=INVINCIBLE_GHOST_POINTS;
			displayStats();
		}
		else
		{
			displayInvincibleGhost(&invincibleGhost);
		}
	}	
}


void _moveMissile(Character *missilePtr, unsigned short missileDirection)
{
	deleteMissile(missilePtr);
	switch(missileDirection)
	{
		case RIGHT:
			++missilePtr->_x;
		break;
		case DOWN:
			++missilePtr->_y;
		break;
		case UP:
			--missilePtr->_y;
		break;
		case LEFT:
			--missilePtr->_x;
		break;
	}	
}

unsigned char setMissileInitialPosition(Character *missilePtr, Character *playerPtr,
							  unsigned short missileDirection)
{
	missilePtr->_x = playerPtr->_x; 
	missilePtr->_y = playerPtr->_y;
	_moveMissile(missilePtr, missileDirection);
	if(wallReached(missilePtr))
	{
		die(missilePtr);
		deleteMissile(missilePtr);
		#if defined(FULL_GAME)
			// TODO: Implement this
			DRAW_BROKEN_WALL(missilePtr->_x, missilePtr->_y);
		#endif
		return 0;
	}
	return 1;
}

#if defined(FULL_GAME)
	void destroyEnemyMissile(Character * enemyMissilePtr)
	{
		enemyMissilePtr->_status = 0;
		EXPLOSION_SOUND();
		deleteMissile(enemyMissilePtr);
		points+=HORIZONTAL_MISSILE_BONUS;
		displayStats();				
		++dead_bubbles;
		reducePowerUpsCoolDowns();		
	}
#endif

void moveMissile(Character * missilePtr, unsigned short missileDirection)
{
	_moveMissile(missilePtr, missileDirection);
	if(wallReached(missilePtr) && missilePtr->_status)
	{
		die(missilePtr);
		deleteMissile(missilePtr);
		#if defined(FULL_GAME)
			DRAW_BROKEN_WALL(missilePtr->_x, missilePtr->_y);
			
			if(oneMissileLevel())
			{
				if(missilePtr->_x==XSize-1 && missilePtr->_y==YSize/2 && rightEnemyMissile._status)
				{
					destroyEnemyMissile(&rightEnemyMissile);
				}
			}				
			else if(missileLevel() || bossLevel())
			{
				if(missilePtr->_x==XSize-1 && missilePtr->_y==ENEMY_MISSILE_OFFSET && rightEnemyMissile._status)
				{
					destroyEnemyMissile(&rightEnemyMissile);	
				}
				else if(missilePtr->_x==0 && missilePtr->_y==YSize-1-ENEMY_MISSILE_OFFSET && leftEnemyMissile._status)
				{
					destroyEnemyMissile(&leftEnemyMissile);	
				}
			}
			if((rocketLevel() || bossLevel()) && missilePtr->_y==YSize-1)
			{
				unsigned char i;
				for(i=0;i<BUBBLES_NUMBER;++i)
				{
					if(missilePtr->_x==bubbles_x[i] && bubbles[i]._status)
					{
						bubbles[i]._status = 0;
						++dead_bubbles;
						EXPLOSION_SOUND();
						deleteMissile(&bubbles[i]);
						points+=VERTICAL_MISSILE_BONUS;
						displayStats();		
					}
				}
			}			
		#endif		
	}
	else
	{
		displayMissile(missilePtr);
	}
}

#endif

