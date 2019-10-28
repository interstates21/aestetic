#ifndef DEFINES_H
# define DEFINES_H

#define COLLISION_DIST 0.3
#define MINIMUM_HEIGHT_TO_WALK 0.32
#define MINIMUM_CEIL_DIST 0.1

#define MIN_HEIGHT_MONSTER_TO_WALK 1
#define SMALLEST_HEIGHT_FOR_MONSTERS 1.4

#define ANIMATION_TIME (SDL_GetTicks() / 1000.0)
#define CLAMP(x, a, b) (((x) > (b)) ? (b) : (((x) < (a)) ? (a) : (x)))
#define NORMALIZE(val, min, max) ((((double)val) - ((double)min)) / (((double)max) - ((double)min)))
#define MOD(i, n) (((i) % (n) + (n)) % (n))
#define LERP(n, min, max) (((double)min) * (1 - ((double)n)) + ((double)max) * ((double)n))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) > (b)) ? (b) : (a))

#define INCREMENT true
#define SET false

#define COLLISION_R 0.8

#define MAX_FUEL 500
#define MAX_BULLETS  30
#define FUEL 300

#define BLASTER_HITBOX 0.4
#define LEFT_MOUSE_BLASTER_DAMAGE 35
#define RIGHT_MOUSE_BLASTER_DAMAGE 35

#define MAX_THREADS 8

#define NB_TEX (int[3]){13, 15, 3}
#define NB_PROJECTILE (int[3]){20, 0, 5}
#define DIST_COLL_PROJ_CEIL_FLOOR 0.1
#define TRANSLATE_WEAP_TIME 30
#define MONSTER_MIN_DIST_HITBOX 0.15
#define MINIMUM_SIZE_AROUND_MONSTERS 0.8
#define FLYING_SPEED 0.01
#define NB_MENU_ITEMS 3
#define M "  I'M TOO YOUNG TO DIE.\n  HEY, NOT TOO ROUGH.\n  HURT ME PLENTY."
#define CROUCH_SPEED 0.01
#define COLLISION_RANGE_CHARGINGDEMON 0.2
#define TURN_SPEED 0.02

#define DEPTH_TO_SCAN 10

#define MINIMUM_HEIGHT_TO_WALK 0.32
#define MOVE_SPEED 0.02
#define MINIMUM_HEIGHT_OF_WALKABLE_SECTOR 0.6

#define Y_OFFSET_TO_ROT -0.00125

#define ACTIVATION_RADIUS 6
#define LONG_RANGE 7
#define COLLISION_DIST_MOTHERDEMON 1.0

#define SIZE_OF_WEAP 1.5;
#define MAX_INERTIA 0.19

#define ACTIVATION_DIST 3.0

#define M16_DAMAGE 4
#define Y_OFFSET_TO_ROT -0.00125

#define NB_OF_SECTOR_DEPTH 2

#define C0 {0x00,0x00,0x00,0x00,0x00},{0x00,0x00,0xbe,0x00,0x00}
#define C1 {0x00,0x07,0x00,0x07,0x00},{0x48,0xfc,0x48,0xfc,0x48}
#define C2 {0x48,0x54,0xfe,0x54,0x24},{0x88,0x54,0x28,0x50,0xa8}
#define C3 {0x6c,0x92,0x92,0xac,0x40},{0x00,0x00,0x07,0x00,0x00}
#define C4 {0x00,0x7c,0x82,0x01,0x00},{0x00,0x01,0x82,0x7c,0x00}
#define C5 {0x28,0x10,0x7c,0x10,0x28},{0x10,0x10,0x7c,0x10,0x10}
#define C6 {0x00,0x40,0x20,0x00,0x00},{0x10,0x10,0x10,0x10,0x10}
#define C7 {0x00,0x00,0x80,0x00,0x00},{0x00,0xc0,0x30,0x0c,0x03}
#define C8 {0x7c,0x82,0x92,0x82,0x7c},{0x00,0x84,0xfe,0x80,0x00}
#define C9 {0xc4,0xa2,0x92,0x92,0x8c},{0x44,0x82,0x92,0x92,0x6c}
#define C10 {0x30,0x28,0x24,0xfe,0x20},{0x5e,0x92,0x92,0x92,0x62}
#define C11 {0x78,0x94,0x92,0x92,0x60},{0x02,0x82,0x62,0x1a,0x06}
#define C12 {0x6c,0x92,0x92,0x92,0x6c},{0x0c,0x92,0x92,0x52,0x3c}
#define C13 {0x00,0x00,0x48,0x00,0x00},{0x00,0x80,0x48,0x00,0x00}
#define C14 {0x10,0x10,0x28,0x28,0x44},{0x28,0x28,0x28,0x28,0x28}
#define C15 {0x44,0x28,0x28,0x10,0x10},{0x04,0x02,0xa2,0x12,0x0c}
#define C16 {0x7c,0x82,0xba,0xba,0xa2},{0xe0,0x38,0x26,0x38,0xe0}
#define C17 {0xfe,0x92,0x92,0x92,0x6c},{0x7c,0x82,0x82,0x82,0x44}
#define C18 {0xfe,0x82,0x82,0x44,0x38},{0xfe,0x92,0x92,0x92,0x82}
#define C19 {0xfe,0x12,0x12,0x12,0x02},{0x7c,0x82,0x82,0x92,0xf4}
#define C20 {0xfe,0x10,0x10,0x10,0xfe},{0x00,0x82,0xfe,0x82,0x00}
#define C21 {0x80,0x80,0x82,0x82,0x7e},{0xfe,0x10,0x28,0x44,0x82}
#define C22 {0xfe,0x80,0x80,0x80,0x80},{0xfe,0x18,0x60,0x18,0xfe}
#define C23 {0xfe,0x06,0x38,0xc0,0xfe},{0x7c,0x82,0x82,0x82,0x7c}
#define C24 {0xfe,0x12,0x12,0x12,0x0c},{0x7c,0x82,0x82,0xc2,0xfc}
#define C25 {0xfe,0x12,0x12,0x12,0xec},{0x4c,0x92,0x92,0x92,0x64}
#define C26 {0x02,0x02,0xfe,0x02,0x02},{0x7e,0x80,0x80,0x80,0x7e}
#define C27 {0x0e,0x30,0xc0,0x30,0x0e},{0x1e,0xe0,0x1c,0xe0,0x1e}
#define C28 {0xc6,0x28,0x10,0x28,0xc6},{0x0e,0x10,0xf0,0x10,0x0e}
#define C29 {0xc2,0xa2,0x92,0x8a,0x86},{0x00,0xff,0x01,0x01,0x00}
#define C30 {0x03,0x0c,0x30,0xc0,0x00},{0x00,0x01,0x01,0xff,0x00}
#define C31 {0x08,0x04,0x02,0x04,0x08},{0x00,0x00,0x00,0x00,0x00}
#define C32 {0x00,0x00,0x02,0x04,0x00},{0x40,0xa8,0xa8,0xa8,0xf0}
#define C33 {0xff,0x88,0x88,0x88,0x70},{0x70,0x88,0x88,0x88,0x88}
#define C34 {0x70,0x88,0x88,0x88,0xff},{0x70,0xa8,0xa8,0xa8,0xb0}
#define C35 {0x08,0xfe,0x09,0x09,0x01},{0x70,0x88,0x88,0x88,0xf0}
#define C36 {0xff,0x08,0x08,0x08,0xf0},{0x00,0x08,0xfa,0x00,0x00}
#define C37 {0x00,0x00,0x08,0xfa,0x00},{0x00,0xff,0x20,0x50,0x88}
#define C38 {0x00,0x01,0xff,0x00,0x00},{0xf8,0x08,0xf0,0x08,0xf0}
#define C39 {0xf8,0x08,0x08,0x08,0xf0},{0x70,0x88,0x88,0x88,0x70}
#define C40 {0xfe,0x22,0x22,0x22,0x1c},{0x1c,0x22,0x22,0x22,0xfe}
#define C41 {0xf8,0x10,0x08,0x08,0x10},{0x90,0xa8,0xa8,0xa8,0x48}
#define C42 {0x00,0x7e,0x88,0x88,0x80},{0x78,0x80,0x80,0x80,0xf8}
#define C43 {0x18,0x60,0x80,0x60,0x18},{0x38,0xc0,0x30,0xc0,0x38}
#define C44 {0x88,0x50,0x20,0x50,0x88},{0x1e,0xa0,0xa0,0xa0,0x7e}
#define C45 {0x88,0xc8,0xa8,0x98,0x88},{0x00,0x10,0xee,0x01,0x00}
#define C46 {0x00,0x00,0xff,0x00,0x00},{0x00,0x01,0xee,0x10,0x00}
#define C47 {0x20,0x10,0x10,0x20,0x20},{0x00,0x00,0x00,0x00,0x00}

#define MOUSE_SENSITIVTY 1
#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8

#define MINIMUM_HEIGHT 0.5

#define MAX_INERTIA 0.19

#define SPEED_ANIM 10
#define SPEED_ANIM_CHARG 7
#define SPEED_ANIM_CHOW 17
#define MOTHER_DEMON_ATTACK 6

#define BOUNCING_DIST_PROJ 0.12
#define BOUNCING_DIST_MOTHERDEMON 0.1
#define BOUCING_DIST_CHARGINGDEMON 0.18

#define MIN_DIST_TO_PLAYER 0.15

#define NB_OF_SECTOR_DEPTH 2

#define SLOT_W 64

#define WEAP_NAME (char*[]){"cryo_ballista/", "blaster/", "m16/"}
#define NB_TEX (int[3]){13, 15, 3}
#define NB_PROJECTILE (int[3]){20, 0, 5}

#define MAX_SIZE_FOR_SOUND 5000000

#define COLOR_SELECT 0x009900

# endif
