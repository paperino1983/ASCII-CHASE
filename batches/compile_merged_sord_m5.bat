@REM set cc65path="C:\Retro\DEV\cc65-snapshot-win32"
@REM set mypath="C:\Users\Brizio\Documents\GitHub\PortableChase\merged"
@REM set configpath="C:\Users\Brizio\Documents\GitHub\PortableChase\merged\experiments"

@REM 
set cc65path="D:\personal\cc65-snapshot-win32"
@REM 
set configpath="D:\Userfiles\fcaruso\Documents\GitHub\ASCII-CHASE\merged\cfg"
@REM 
set mypath="d:\Userfiles\fcaruso\Documents\GitHub\ASCII-CHASE\merged"

@REM set cc65path="C:\cc65-snapshot-win32"
@REM set configpath="C:\Users\Brizio\Retro\ASCII-CHASE\merged\cfg"
@REM set mypath="C:\Users\Brizio\Retro\ASCII-CHASE\merged"



set Deliverables=%mypath%\deliverables

mkdir %deliverables% 2> NUL

@REM del %deliverables%\*.prg
@REM del %deliverables%\*.bin
@REM del %deliverables%\*.xex
@REM del %deliverables%\*.tap
del %mypath%\*.o
del %mypath%\atmos\*.o
del %mypath%\c64\*.o
del %mypath%\patch\*.o

cd %cc65path%\bin\

@REM 
cd %mypath%\


@REM CPC HALF-WORKINg
@REM -DDEBUG_CHARACTERS
@REM 

@REM zcc +zx81 -O3 -vn -D__ZX81__ -lndos -create-app -o %deliverables%\MINIMAL_zx81_experimental.prg %mypath%\display_macros.c %mypath%\enemy.c %mypath%\invincible_enemy.c %mypath%\level.c %mypath%\character.c %mypath%\text.c %mypath%\missile.c %mypath%\strategy.c %mypath%\input_macros.c %mypath%\main.c
@REM 
@REM zcc +zx81 -O3 -vn -clib=ansi -D__ZX81__ -lndos -create-app -o %deliverables%\MINIMAL_zx81_experimental.prg %mypath%\display_macros.c %mypath%\enemy.c %mypath%\invincible_enemy.c %mypath%\level.c %mypath%\character.c %mypath%\text.c %mypath%\missile.c %mypath%\strategy.c %mypath%\input_macros.c %mypath%\main.c

@REM -O3

@REM 
zcc  +m5 -D__M5__ -lndos -lm -create-app -Cz--audio -o %deliverables%\MINIMAL_m5 %mypath%\display_macros.c %mypath%\enemy.c %mypath%\invincible_enemy.c %mypath%\level.c %mypath%\character.c %mypath%\text.c %mypath%\missile.c %mypath%\strategy.c %mypath%\input_macros.c %mypath%\main.c

@REM zcc  +m5 -D__M5__ -lndos -lm -create-app -Cz--audio -o %deliverables%\test_m5 %mypath%\test_a5200.c

@REM zcc +ace -vn -D__ACE__ -lndos -create-app -o  %deliverables%\MINIMAL_ace_experimental.prg %mypath%\display_macros.c %mypath%\enemy.c %mypath%\invincible_enemy.c %mypath%\level.c %mypath%\character.c %mypath%\text.c %mypath%\missile.c %mypath%\strategy.c %mypath%\input_macros.c %mypath%\main.c

@REM zcc +aquarius -vn -create-app -o %deliverables%\MINIMAL_aquarius_experimental.prg %mypath%\..\experiments\my_hello.c

@REM del %deliverables%\MINIMAL_aquarius_experimental.prg
@REM del %deliverables%\cpc.cpc


del %mypath%\*.o
del %mypath%\atmos\*.o
del %mypath%\c64\*.o
del %mypath%\patch\*.o
