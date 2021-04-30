#include <gb/gb.h>
#include <stdio.h>
#include "Assets/map.c"
#include "Assets/tile.c"
#include "Assets/heroTile.c"

void init();
void checkInput();
void updateSwitches();
void moveUp();
void moveDown();
void moveLeft();
void moveRight();
void animate();

UINT8 player[2];
char direction = 'U';

void main()
{
        init();

        // printf("\nhero!");
        // waits until specific key is pressed
        // waitpad(J_START);

        // game runs in a loop
        while(1)
        {
                checkInput();
		updateSwitches();
		wait_vbl_done();
        }
}

void updateSwitches()
{
        HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

void init() 
{
        DISPLAY_ON;
        // by default sprites are 8x8
        SPRITES_8x16;

        // set_bkg_data(0, 18, gameAssets);
        // set_bkg_tiles(0, 0, mapWidth, mapHeight, map);
	player[0] = 80;
	player[1] = 72;
	set_sprite_data(0, 22, HeroTile);
}

void checkInput()
{
        if (joypad() & J_UP) {
                moveUp();
                return;
	}

	if (joypad() & J_DOWN) {
                moveDown();
                return;
	}

	if (joypad() & J_LEFT) {
                moveLeft();
                return;
	}	
	
	if (joypad() & J_RIGHT) {
                moveRight();
                return;
	}

SHOW_SPRITES;
        // animate();
}

void moveDown()
{
        player[1]++;
        direction = 'D';
        
        if (player[1] % 2 == 0) {
                set_sprite_tile(0, 0);
                set_sprite_tile(1, 1);
        } else {
                set_sprite_tile(0, 2);
                set_sprite_tile(1, 3);
        }

        move_sprite(0, player[0], player[1]);
        move_sprite(1, player[0] - 8, player[1]);
}

void moveUp()
{        
        player[1]--;
        direction = 'U';

        if (player[1] % 2 == 0) {
                set_sprite_tile(0, 4);
                set_sprite_tile(1, 5);
        } else {
                set_sprite_tile(0, 6);
                set_sprite_tile(1, 7);
        }

        move_sprite(0, player[0], player[1]);
        move_sprite(1, player[0] - 8, player[1]);
}

void moveLeft()
{
        player[0]--;
        direction = 'L';

        if (player[0] % 2 == 0) {
                set_sprite_tile(0, 8);
                set_sprite_tile(1, 9);
        } else {
                set_sprite_tile(0, 10);
                set_sprite_tile(1, 11);
        }


        // set_sprite_prop(0, S_FLIPX);
        // set_sprite_prop(1, S_FLIPX);
        move_sprite(1, player[0] - 8, player[1]);
        move_sprite(0, player[0], player[1]);
}

void moveRight()
{
        player[0]++;
        direction = 'R';

        if (player[0] % 2 == 0) {
                set_sprite_tile(0, 8);
                set_sprite_tile(1, 9);
        } else {
                set_sprite_tile(0, 10);
                set_sprite_tile(1, 11);
        }

        move_sprite(0, player[0] - 8, player[1]);
        move_sprite(1, player[0], player[1]);
}

void animate()
{
        // switch (direction)
        // {
        // case 'U':
        //         set_sprite_tile(0, 6);
        //         set_sprite_tile(1, 7);
        //         delay(500);
        //         set_sprite_tile(0, 4);
        //         set_sprite_tile(1, 5);
        //         delay(500);
        //         break;
        // case 'D':
        //         set_sprite_tile(0, 2);
        //         set_sprite_tile(1, 3);
        //         delay(500);
        //         set_sprite_tile(0, 0);
        //         set_sprite_tile(1, 1);
        //         delay(500);
        //         break;                
        // case 'L':
        //         set_sprite_tile(1, 9);
        //         set_sprite_prop(1, S_FLIPX);
        //         delay(500);
        //         set_sprite_tile(1, 11);
        //         set_sprite_prop(0, S_FLIPX);
        //         delay(500);
        //         break;
        // case 'R':
        //         set_sprite_tile(0, 10);
        //         set_sprite_tile(1, 11);
        //         delay(500);
        //         set_sprite_tile(1, 9);
        //         set_sprite_tile(0, 8);
        //         delay(500);
        //         break;                
        // default:
        //         break;
        // }
}
