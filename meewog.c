#include <gb/gb.h>
#include <stdio.h>
#include "Assets/heroTile.c"

void init();
void run();
void registerInput();
void updateSprites(UINT8 *sprites, BOOLEAN flip);
void flipSprite(INT8 spriteId);
void unFlipSprite(INT8 spriteId);

/**
 * to hold x and y cooridnates respectively
 * we center the player
 * */
UINT8 hero[2] = {80, 72};
// pressed key
UINT8 key = 0;
// specifies if hero is walking or has stopped
BOOLEAN isMoving = 0;

UINT8 DIRECTION_UP = 0;
UINT8 DIRECTION_DOWN = 1;
UINT8 DIRECTION_LEFT = 2;
UINT8 DIRECTION_RIGHT = 3;
UINT8 CURRENT_DIRECTION;
UINT8 animationFrame;

UINT8 UP_SPRITES[] = {
    8, 10,
    9, 11,
    12, 14,
    13, 15,
};

UINT8 DOWN_SPRITES[] = {
    0, 2,
    1, 3,
    4, 6,
    5, 7,
};

UINT8 RIGHT_SPRITES[] = {
    16, 18,
    17, 19,
    20, 22,
    21, 23,
};

void main()
{
    init();
    run();
}

void init()
{
    // default sprite size is 8x8
    SPRITES_8x16;
    // show the sprite layer
    SHOW_SPRITES;
    // easiest way is to count the lines in the asset.h file
    set_sprite_data(0, 48, HeroTile);
    animationFrame = 0;

    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);
}

void run()
{
    // game loops here
    while(1)
    {
        // Wait for v-blank (screen refresh)
        wait_vbl_done();
        registerInput();
    }
}

void registerInput()
{
    key = joypad();

    if (!key) {
        isMoving = 0;
        animationFrame = 0;
        return;
    }

    isMoving = 1;

    switch (key)
    {
    case J_UP:
        CURRENT_DIRECTION = DIRECTION_UP;
        updateSprites(UP_SPRITES, 0);
        hero[1] -= 1; 
        break;
    case J_DOWN:
        CURRENT_DIRECTION = DIRECTION_DOWN;
        updateSprites(DOWN_SPRITES, 0);
        hero[1] += 1;
        break;
    case J_LEFT:
        CURRENT_DIRECTION = DIRECTION_LEFT;
        updateSprites(RIGHT_SPRITES, 1);
        hero[0] -= 1;
        break;
    case J_RIGHT:
        CURRENT_DIRECTION = DIRECTION_RIGHT;
        updateSprites(RIGHT_SPRITES, 0);
        hero[0] += 1;
        break;
    default:
    // no key pressed
        break;
    }
}

void updateSprites(UINT8 *sprites, BOOLEAN flip)
{
    UINT8 baseValue = (animationFrame * 1) + animationFrame;
    UINT8 spriteX = baseValue;
    UINT8 spriteY = baseValue + 1;

    move_sprite(0, hero[0], hero[1]);
    move_sprite(1, hero[0] + 8, hero[1]);
    

    if (flip) {
        set_sprite_tile(0, sprites[spriteY]);
        set_sprite_tile(1, sprites[spriteX]);

        flipSprite(0);
        flipSprite(1);
        // move_sprite(1, hero[0] - 8, hero[1]);
    } else {
        set_sprite_tile(0, sprites[spriteX]);
        set_sprite_tile(1, sprites[spriteY]);

        unFlipSprite(0);
        unFlipSprite(1);
    }

    if (animationFrame == 3) {
        animationFrame = 0;

        return;
    }

    animationFrame += 1;
}

void flipSprite(INT8 spriteId)
{
    set_sprite_prop(spriteId, get_sprite_prop(spriteId) | S_FLIPX);
}

void unFlipSprite(INT8 spriteId)
{
    set_sprite_prop(spriteId, get_sprite_prop(spriteId) & ~S_FLIPX);
}
