#include <gb/gb.h>
#include <gb/cgb.h>
#include "map1.h"
#include "tiles.h"
#include "player.h"
#include "hud_map.h"
#include "hud.h"

unsigned char hud_p[] = 
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

unsigned char map1_p[] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};



INT8 p[2];
INT8 up;
INT8 down;
INT8 left;
INT8 right;


UWORD palette[] = {
	tilesCGBPal0c0, tilesCGBPal0c1, tilesCGBPal0c2, tilesCGBPal0c3,
	//RGB(30, 28, 20), RGB(31, 3, 0), RGB(1, 11, 13), RGB_BLACK
	hudCGBPal0c0,hudCGBPal0c1,hudCGBPal0c2,hudCGBPal0c3,
	tilesCGBPal1c0, tilesCGBPal1c1, tilesCGBPal1c2, tilesCGBPal1c3
};
UWORD p_palette[] = {
	0, RGB(30, 28, 20), RGB(6, 4, 12), RGB_BLACK
};

void performantdelay(UINT8 numloops){
	UINT8 i;
	for(i = 0; i < numloops; i++)
	{
		wait_vbl_done();
	}
	

}

void main(){
	NR52_REG = 0x80;
	NR51_REG = 0x11;
	NR50_REG = 0x77;
					

	p[0] = 75;
	p[1] = 75;

	set_bkg_palette(0, 3, palette);
	

	set_bkg_data(0, 37, tiles);
	VBK_REG = 1;
	set_bkg_tiles(0, 0, 20, 16, map1_p);
	VBK_REG = 0;
	
	set_bkg_tiles(0, 0, 20, 16, map1);
	SPRITES_8x16;
	set_sprite_data(0, 32, player);
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 2);
	set_sprite_palette(0, 3, p_palette);

	move_sprite(0, p[0], p[1]);
	move_sprite(1, p[0] + 8, p[1]);	

	//set_bkg_palette(4, 7, palette);

	set_win_data(37, 59, hud);
	VBK_REG = 1;
	set_win_tiles(0, 0, 20, 18, hud_p);
	VBK_REG = 0;

	set_win_tiles(0, 0, 20, 18, hud_map);
	move_win(8, 128);
	
	SHOW_SPRITES;
	SHOW_BKG;
	SHOW_WIN;
	
	while(1){
		if(joypad() & J_DOWN){
			p[1] += 1;
			if (down <= 8 && down > 4) {
				set_sprite_tile(0, 0);
				set_sprite_tile(1, 2);
			}else if (down <= 4) {
				set_sprite_tile(0, 4);
				set_sprite_tile(1, 6);
			}else {
				down = 0;
			}
			down++;
			up = 0;
			left = 0;
			right = 0;

			move_sprite(0, p[0], p[1]);
			move_sprite(1, p[0] + 8, p[1]);
		}
		if(joypad() & J_UP){
			p[1] -= 1;
			if (up <= 8 && up > 4) {
				set_sprite_tile(0, 24);
				set_sprite_tile(1, 26);
			}else if (up <= 4) {
				set_sprite_tile(0, 28);
				set_sprite_tile(1, 30);
			}else {
				up = 0;
			}
			down = 0;
			up++;
			left = 0;
			right = 0;

			move_sprite(0, p[0], p[1]);
			move_sprite(1, p[0] + 8, p[1]);
		}
		if(joypad() & J_RIGHT){
			p[0] += 1;
			if (right <= 8 && right > 4) {
				set_sprite_tile(0, 8);
				set_sprite_tile(1, 10);
			}else if (right <= 4) {
				set_sprite_tile(0, 12);
				set_sprite_tile(1, 14);
			}else {
				right = 0;
			}
			down = 0;
			up = 0;
			left = 0;
			right++;

			move_sprite(0, p[0], p[1]);
			move_sprite(1, p[0] + 8, p[1]);
		}
		if(joypad() & J_LEFT){
			p[0] -= 1;
			if (left <= 8 && left > 4) {
				set_sprite_tile(0, 20);
				set_sprite_tile(1, 22);
			}else if (left <= 4) {
				set_sprite_tile(0, 16);
				set_sprite_tile(1, 18);
			}else {
				left = 0;
			}

			down = 0;
			up = 0;
			left++;
			right = 0;

			move_sprite(0, p[0], p[1]);
			move_sprite(1, p[0] + 8, p[1]);
		}
		if(joypad() & J_A){
			NR10_REG = 0x16;
			NR11_REG = 0x15;
			NR12_REG = 0x80;
			NR13_REG = 0x00;
			NR14_REG = 0x84;
			
		}

		performantdelay(3);
		
	}


}