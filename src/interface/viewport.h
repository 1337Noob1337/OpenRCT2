/*****************************************************************************
 * Copyright (c) 2014 Ted John
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * This file is part of OpenRCT2.
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "../world/map.h"
#include "../world/sprite.h"
#include "window.h"

enum {
	VIEWPORT_FLAG_UNDERGROUND_INSIDE = (1 << 0),
	VIEWPORT_FLAG_SEETHROUGH_RIDES = (1 << 1),
	VIEWPORT_FLAG_SEETHROUGH_SCENERY = (1 << 2),
	VIEWPORT_FLAG_INVISIBLE_SUPPORTS = (1 << 3),
	VIEWPORT_FLAG_LAND_HEIGHTS = (1 << 4),
	VIEWPORT_FLAG_TRACK_HEIGHTS = (1 << 5),
	VIEWPORT_FLAG_PATH_HEIGHTS = (1 << 6),
	VIEWPORT_FLAG_GRIDLINES = (1 << 7),
	VIEWPORT_FLAG_LAND_OWNERSHIP = (1 << 8),
	VIEWPORT_FLAG_CONSTRUCTION_RIGHTS = (1 << 9),
	VIEWPORT_FLAG_SOUND_ON = (1 << 10),
	VIEWPORT_FLAG_INVISIBLE_PEEPS = (1 << 11),
	VIEWPORT_FLAG_HIDE_BASE = (1 << 12),
	VIEWPORT_FLAG_HIDE_VERTICAL = (1 << 13),
	VIEWPORT_FLAG_INVISIBLE_SPRITES = (1 << 14),
	VIEWPORT_FLAG_15 = (1 << 15)
};

enum {
	VIEWPORT_INTERACTION_ITEM_NONE,
	VIEWPORT_INTERACTION_ITEM_TERRAIN,
	VIEWPORT_INTERACTION_ITEM_SPRITE,
	VIEWPORT_INTERACTION_ITEM_RIDE,
	VIEWPORT_INTERACTION_ITEM_WATER,
	VIEWPORT_INTERACTION_ITEM_SCENERY,
	VIEWPORT_INTERACTION_ITEM_FOOTPATH,
	VIEWPORT_INTERACTION_ITEM_FOOTPATH_ITEM,
	VIEWPORT_INTERACTION_ITEM_PARK,
	VIEWPORT_INTERACTION_ITEM_WALL,
	VIEWPORT_INTERACTION_ITEM_LARGE_SCENERY,
	VIEWPORT_INTERACTION_ITEM_LABEL,
	VIEWPORT_INTERACTION_ITEM_BANNER,

};

enum {
	VIEWPORT_INTERACTION_MASK_NONE = 0,
	VIEWPORT_INTERACTION_MASK_TERRAIN = ~(1 << (VIEWPORT_INTERACTION_ITEM_TERRAIN - 1)),
	VIEWPORT_INTERACTION_MASK_SPRITE = ~(1 << (VIEWPORT_INTERACTION_ITEM_SPRITE - 1)),
	VIEWPORT_INTERACTION_MASK_RIDE = ~(1 << (VIEWPORT_INTERACTION_ITEM_RIDE - 1)),
	VIEWPORT_INTERACTION_MASK_WATER = ~(1 << (VIEWPORT_INTERACTION_ITEM_WATER - 1)),
	VIEWPORT_INTERACTION_MASK_SCENERY = ~(1 << (VIEWPORT_INTERACTION_ITEM_SCENERY - 1)),
	VIEWPORT_INTERACTION_MASK_FOOTPATH = ~(1 << (VIEWPORT_INTERACTION_ITEM_FOOTPATH - 1)),
	VIEWPORT_INTERACTION_MASK_FOOTPATH_ITEM = ~(1 << (VIEWPORT_INTERACTION_ITEM_FOOTPATH_ITEM - 1)),
	VIEWPORT_INTERACTION_MASK_PARK = ~(1 << (VIEWPORT_INTERACTION_ITEM_PARK - 1)),
	VIEWPORT_INTERACTION_MASK_WALL = ~(1 << (VIEWPORT_INTERACTION_ITEM_WALL - 1)),
	VIEWPORT_INTERACTION_MASK_LARGE_SCENERY = ~(1 << (VIEWPORT_INTERACTION_ITEM_LARGE_SCENERY - 1)),
	VIEWPORT_INTERACTION_MASK_BANNER = ~(1 << (VIEWPORT_INTERACTION_ITEM_BANNER - 2)), // Note the -2 for BANNER
};

typedef struct paint_struct paint_struct;

struct paint_struct{
	uint32 image_id;		// 0x00
	uint32 var_04;
	uint16 attached_x;		// 0x08
	uint16 attached_y;		// 0x0A
	union {
		struct {
			uint8 var_0C;
			uint8 pad_0D;
			paint_struct* next_attached_ps;	//0x0E
			uint16 pad_12;
		};
		struct {
			uint16 attached_z; // 0x0C
			uint16 attached_z_end; // 0x0E
			uint16 attached_x_end; // 0x10
			uint16 attached_y_end; // 0x12
		};
	};
	uint16 x;				// 0x14
	uint16 y;				// 0x16
	uint16 var_18;
	uint8 var_1A;
	uint8 var_1B;
	paint_struct* attached_ps;	//0x1C
	paint_struct* var_20;
	paint_struct* next_quadrant_ps; // 0x24
	uint8 sprite_type;		//0x28
	uint8 var_29;
	uint16 pad_2A;
	uint16 map_x;			// 0x2C
	uint16 map_y;			// 0x2E
	rct_map_element *mapElement; // 0x30 (or sprite pointer)
};

typedef struct {
	int type;
	int x;
	int y;
	union {
		rct_map_element *mapElement;
		rct_sprite *sprite;
		rct_peep *peep;
		rct_vehicle *vehicle;
	};
} viewport_interaction_info;

#define MAX_VIEWPORT_COUNT MAX_WINDOW_COUNT

#define gSavedViewX				RCT2_GLOBAL(RCT2_ADDRESS_SAVED_VIEW_X, sint16)
#define gSavedViewY				RCT2_GLOBAL(RCT2_ADDRESS_SAVED_VIEW_Y, sint16)
#define gSavedViewZoom			RCT2_GLOBAL(RCT2_ADDRESS_SAVED_VIEW_ZOOM_AND_ROTATION, uint8)
#define gSavedViewRotation		RCT2_GLOBAL(RCT2_ADDRESS_SAVED_VIEW_ZOOM_AND_ROTATION + 1, uint8)
#define gCurrentRotation		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_ROTATION, uint8)
#define gCurrentViewportFlags	RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_VIEWPORT_FLAGS, uint16)

// rct2: 0x014234BC
extern rct_viewport g_viewport_list[MAX_VIEWPORT_COUNT];

void viewport_init_all();
void center_2d_coordinates(int x, int y, int z, int* out_x, int* out_y, rct_viewport* viewport);
void viewport_create(rct_window *w, int x, int y, int width, int height, int zoom, int center_x, int center_y, int center_z, char flags, sint16 sprite);
void viewport_update_pointers();
void viewport_update_position(rct_window *window);
void viewport_update_sprite_follow(rct_window *window);
void viewport_render(rct_drawpixelinfo *dpi, rct_viewport *viewport, int left, int top, int right, int bottom);
void viewport_paint(rct_viewport* viewport, rct_drawpixelinfo* dpi, int left, int top, int right, int bottom);

void sub_689174(sint16* x, sint16* y, sint16 *z);

rct_xy16 screen_coord_to_viewport_coord(rct_viewport *viewport, uint16 x, uint16 y);
rct_xy16 viewport_coord_to_map_coord(int x, int y, int z);
void screen_pos_to_map_pos(sint16 *x, sint16 *y, int *direction);

void show_gridlines();
void hide_gridlines();
void show_land_rights();
void hide_land_rights();
void show_construction_rights();
void hide_construction_rights();
void viewport_set_visibility(uint8 mode);

void get_map_coordinates_from_pos(int screenX, int screenY, int flags, sint16 *x, sint16 *y, int *interactionType, rct_map_element **mapElement, rct_viewport **viewport);

int viewport_interaction_get_item_left(int x, int y, viewport_interaction_info *info);
int viewport_interaction_left_over(int x, int y);
int viewport_interaction_left_click(int x, int y);
int viewport_interaction_get_item_right(int x, int y, viewport_interaction_info *info);
int viewport_interaction_right_over(int x, int y);
int viewport_interaction_right_click(int x, int y);
void sub_68A15E(int screenX, int screenY, short *x, short *y, int *direction, rct_map_element **mapElement);

void viewport_interaction_remove_park_entrance(rct_map_element *mapElement, int x, int y);

void sub_68B2B7(int x, int y);
void painter_setup();
void sub_688485();
void sub_688217();

bool sub_98196C(uint32 image_id, sint8 x_offset, sint8 y_offset, sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z, uint16 z_offset, uint32 rotation);
bool sub_98197C(uint32 image_id, sint8 x_offset, sint8 y_offset, sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z, uint16 z_offset, sint16 bound_box_offset_x, sint16 bound_box_offset_y, sint16 bound_box_offset_z, uint32 rotation);
bool sub_98198C(uint32 image_id, sint8 x_offset, sint8 y_offset, sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z, uint16 z_offset, sint16 bound_box_offset_x, uint16 bound_box_offset_y, sint16 bound_box_offset_z, uint32 rotation);
bool sub_98199C(uint32 image_id, sint8 x_offset, sint8 y_offset, sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z, uint16 z_offset, sint16 bound_box_offset_x, uint16 bound_box_offset_y, sint16 bound_box_offset_z, uint32 rotation);
bool sub_68818E(uint32 image_id, uint16 x_offset, uint16 y_offset, paint_struct ** paint);

void viewport_invalidate(rct_viewport *viewport, int left, int top, int right, int bottom);

void screen_get_map_xy(int screenX, int screenY, sint16 *x, sint16 *y, rct_viewport **viewport);
void screen_get_map_xy_with_z(sint16 screenX, sint16 screenY, sint16 z, sint16 *mapX, sint16 *mapY);
void screen_get_map_xy_quadrant(sint16 screenX, sint16 screenY, sint16 *mapX, sint16 *mapY, uint8 *quadrant);
void screen_get_map_xy_quadrant_with_z(sint16 screenX, sint16 screenY, sint16 z, sint16 *mapX, sint16 *mapY, uint8 *quadrant);
void screen_get_map_xy_side(sint16 screenX, sint16 screenY, sint16 *mapX, sint16 *mapY, uint8 *side);
void screen_get_map_xy_side_with_z(sint16 screenX, sint16 screenY, sint16 z, sint16 *mapX, sint16 *mapY, uint8 *side);

uint8 get_current_rotation();

#endif
