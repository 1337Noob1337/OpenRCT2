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

#ifndef _SCENARIO_H_
#define _SCENARIO_H_

#include "common.h"
#include "management/award.h"
#include "management/news_item.h"
#include "management/research.h"
#include "ride/ride.h"
#include "object.h"
#include "platform/platform.h"
#include "world/banner.h"
#include "world/map.h"
#include "world/sprite.h"

/**
 * SV6/SC6 header chunk
 * size: 0x20
 */
typedef struct {
	uint16 type;				// 0x00
	uint16 num_packed_objects;	// 0x02
	uint32 version;				// 0x04
	uint32 magic_number;		// 0x08
	uint8 pad_0C[0x14];
} rct_s6_header;

/**
 * SC6 information chunk
 * size: 0x198
 */
typedef struct {
	uint8 editor_step;
	uint8 category;				// 0x01
	uint8 objective_type;		// 0x02
	uint8 objective_arg_1;		// 0x03
	sint32 objective_arg_2;		// 0x04
	sint16 objective_arg_3;		// 0x08
	uint8 pad_00A[0x3E];
	char name[64];				// 0x48
	char details[256];			// 0x88
	rct_object_entry entry;		// 0x188
} rct_s6_info;

/**
 * Scenario scores file header.
 * size: 0x10
 */
typedef struct {
	uint32 var_0;
	uint32 var_4;
	uint32 var_8;
	uint32 scenario_count;		// 0x0C
} rct_scenario_scores_header;

typedef enum {
	SCENARIO_SOURCE_RCT1,
	SCENARIO_SOURCE_RCT1_AA,
	SCENARIO_SOURCE_RCT1_LL,
	SCENARIO_SOURCE_RCT2,
	SCENARIO_SOURCE_RCT2_WW,
	SCENARIO_SOURCE_RCT2_TT,
	SCENARIO_SOURCE_REAL,
	SCENARIO_SOURCE_OTHER
} scenario_source;

/**
 * Scenario basic structure, mainly for scenario select
 * size: 0x02B0
 */
typedef struct {
	char path[256];				// 0x0000
	uint8 category;				// 0x0100
	uint8 pad_0101[0x1F];
	sint8 objective_type;		// 0x0120
	sint8 objective_arg_1;		// 0x0121
	sint32 objective_arg_2;		// 0x0122
	sint16 objective_arg_3;		// 0x0126
	char name[64];				// 0x0128
	char details[256];			// 0x0168
	sint32 flags;				// 0x0268
	uint32 company_value;		// 0x026C
	char completed_by[64];		// 0x0270
	// uint8 source_game;			// new in OpenRCT2
	// sint16 source_index;		// new in OpenRCT2
} rct_scenario_basic;

typedef struct {
	rct_string_id scenario_name;	// 0x00
	rct_string_id park_name;		// 0x02
	rct_string_id details;			// 0x04
	uint8 var_06;
} rct_stex_entry;

#define g_stexEntries ((rct_stex_entry**)object_entry_groups[OBJECT_TYPE_SCENARIO_TEXT].chunks)

// This will be useful for backwards compatibility
typedef struct {
	// SC6[0]
	rct_s6_header header;

	// SC6[1]
	rct_s6_info info;

	// SC6[2]
	// packed objects

	// SC6[3]
	rct_object_entry objects[721];

	// SC6[4]
	uint16 elapsed_months;
	uint16 current_day;
	uint32 dword_F663AC;
	uint32 scenario_srand_0;
	uint32 scenario_srand_1;

	// SC6[5]
	rct_map_element map_elements[0x30000];

	// SC6[6]
	uint32 dword_010E63B8;
	rct_sprite sprites[10000];
	uint16 sprites_next_index;
	uint16 sprites_start_vehicle;
	uint16 sprites_start_peep;
	uint16 sprites_start_textfx;
	uint16 sprites_start_litter;
	uint8 pad_013573C6[2];
	uint16 word_013573C8;
	uint16 sprites_count_vehicle;
	uint16 sprites_count_peep;
	uint16 sprites_count_misc;
	uint16 sprites_count_litter;
	uint8 pad_013573D2[2];
	rct_string_id park_name;
	uint8 pad_013573D6[2];
	uint32 park_name_args;
	money32 initial_cash;
	money32 current_loan;
	uint32 park_flags;
	money16 park_entrance_fee;
	uint16 word_013573EA;
	uint16 word_013573EC;
	uint8 pad_013573EE[2];
	uint8 byte_013573F0;
	uint8 pad_013573F1;
	rct2_peep_spawn peep_spawns[2];
	uint8 guest_count_change_modifier;
	uint8 current_research_level;
	uint8 pad_01357400[4];
	uint32 ride_types_researched[8];
	uint32 ride_entries_researched[8];
	uint32 dword_01357444[128];
	uint32 dword_01357644[128];

	// SC6[7]
	uint16 guests_in_park;
	uint16 guests_heading_for_park;

	// Ignored in scenario
	money32 expenditure_table[14];
	uint32 dword_01357880[5];
	uint32 dword_01357894;
	uint32 dword_01357898;
	uint32 dword_0135789C;
	uint32 dword_013578A0;
	uint32 dword_013578A4[201];

	// SC6[8]
	uint16 last_guests_in_park;
	uint8 pad_01357BCA[3];
	uint8 handyman_colour;
	uint8 mechanic_colour;
	uint8 security_colour;

	// Ignored in scenario
	uint32 dword_01357BD0[56];

	// SC6[9]
	uint16 park_rating;

	// Ignored in scenario
	uint8 park_rating_history[32];
	uint8 guests_in_park_history[32];

	// SC6[10]
	uint8 active_research_types;
	uint8 research_progress_stage;
	uint32 dword_01357CF4;
	uint8 byte_01357CF8[1000];
	uint32 next_research_item;
	uint16 research_progress;
	uint8 next_research_category;
	uint8 next_research_expected_day;
	uint8 next_research_expected_month;
	uint8 guest_initial_happiness;
	uint16 park_size;
	uint16 guest_generation_probability;
	uint16 total_ride_value;
	money32 maximum_loan;
	money16 guest_initial_cash;
	uint8 guest_initial_hunger;
	uint8 guest_initial_thirst;
	uint8 objective_type;
	uint8 objective_year;
	uint8 pad_013580FA[2];
	money32 objective_currency;
	uint16 objective_guests;
	uint8 campaign_weeks_left[20];
	uint8 campaign_ride_index[22];

	// Ignored in scenario
	money32 balance_history[128];

	// SC6[11]
	money32 current_expenditure;
	money32 current_profit;
	uint32 dword_01358334;
	uint16 word_01358338;
	uint8 pad_0135833A[2];

	// Ignored in scenario
	money32 weekly_profit_history[128];

	// SC6[12]
	money32 park_value;

	// Ignored in scenario
	money32 park_value_history[128];

	// SC6[13]
	money32 completed_company_value;
	uint32 total_admissions;
	money32 income_from_admissions;
	money32 company_value;
	uint8 byte_01358750[16];
	rct_award awards[4];
	money16 land_price;
	money16 construction_rights_price;
	uint16 word_01358774;
	uint8 pad_01358776[2];
	uint32 dword_01358778[17];
	uint32 game_version_number;
	uint32 dword_013587C0;
	uint32 loan_hash;
	uint16 ride_count;
	uint8 pad_013587CA[6];
	uint32 dword_013587D0;
	uint8 pad_013587D4[4];
	char scenario_completed_name[32];
	money32 cash;
	uint8 pad_013587FC[50];
	uint16 word_0135882E;
	uint16 map_size_units;
	uint16 map_size_minus_2;
	uint16 map_size;
	uint16 map_max_xy;
	uint32 same_price_throughout;
	uint16 suggested_max_guests;
	uint16 park_rating_warning_days;
	uint8 word_01358840;
	uint8 rct1_water_colour;
	uint8 pad_01358842[2];
	rct_research_item research_items[500];
	uint16 word_01359208;
	char scenario_name[64];
	char scenario_description[256];
	uint8 current_interest_rate;
	uint8 pad_0135934B;
	uint32 same_price_throughout_extended;
	uint16 park_entrance_x[4];
	uint16 park_entrance_y[4];
	uint16 park_entrance_z[4];
	uint8 park_entrance_direction[4];
	char scenario_filename[256];
	uint8 saved_expansion_pack_names[3256];
	rct_banner banners[250];
	char custom_strings[0x8000];
	uint32 game_ticks_1;
	rct_ride rides[255];
	uint16 word_01388698;
	uint16 saved_view_x;
	uint16 saved_view_y;
	uint16 saved_view_zoom_and_rotation;
	uint8 map_animations[6000];
	uint8 byte_01389E10[6000];
	uint16 num_map_animations;
	uint8 pad_0138B582[2];
	uint16 ride_ratings_proximity_x;
	uint16 ride_ratings_proximity_y;
	uint16 ride_ratings_proximity_z;
	uint16 ride_ratings_proximity_start_x;
	uint16 ride_ratings_proximity_start_y;
	uint16 ride_ratings_proximity_start_z;
	uint8 ride_ratings_current_ride;
	uint8 ride_ratings_state;
	uint8 ride_ratings_proximity_track_type;
	uint8 ride_ratings_proximity_base_height;
	uint16 ride_ratings_proximity_total;
	uint16 word_0138B596;
	uint16 word_0138B598;
	uint16 word_0138B59A;
	uint16 word_0138B59C;
	uint16 word_0138B59E;
	uint16 word_0138B5A0;
	uint16 word_0138B5A2;
	uint16 word_0138B5A4;
	uint16 word_0138B5A6;
	uint16 word_0138B5A8;
	uint16 word_0138B5AA;
	uint16 word_0138B5AC;
	uint16 word_0138B5AE;
	uint16 word_0138B5B0;
	uint16 word_0138B5B2;
	uint16 word_0138B5B4;
	uint16 word_0138B5B6;
	uint16 word_0138B5B8;
	uint16 word_0138B5BA;
	uint16 word_0138B5BC;
	uint16 word_0138B5BE;
	uint16 word_0138B5C0;
	uint16 word_0138B5C2;
	uint16 word_0138B5C4;
	uint16 word_0138B5C6;
	uint16 word_0138B5C8;
	uint16 word_0138B5CA;
	uint16 word_0138B5CC;
	uint16 word_0138B5CE[31];
	uint8 ride_measurements[0x25860];
	uint32 next_guest_index;
	uint16 grass_and_scenery_tilepos;
	uint32 patrol_areas[0x6600]; // 512 bytes per staff peep
	uint8 byte_13CA672[116];
	uint8 byte_13CA6E6[84];
	uint8 byte_13CA73A[4];
	uint8 unk_13CA73E;
	uint8 pad_13CA73F;
	uint8 byte_13CA740;
	uint8 byte_13CA741;
	uint8 byte_13CA742[4];
	uint8 climate;
	uint8 pad_013CA747;
	uint16 climate_update_timer;
	uint8 current_weather;
	uint8 next_weather;
	uint8 temperature;
	uint8 next_temperature;
	uint8 current_weather_effect;
	uint8 next_weather_effect;
	uint8 current_weather_gloom;
	uint8 next_weather_gloom;
	uint8 current_rain_level;
	uint8 next_rain_level;
	rct_news_item news_items[61];
	uint8 byte_13CE730[64];
	uint32 dword_13CE770;
	uint16 wide_path_tile_loop_x;
	uint16 wide_path_tile_loop_y;
	uint8 pad_13CE778[434];
} rct_s6_data;

enum {
	SCENARIO_FLAGS_VISIBLE = (1 << 0),
	SCENARIO_FLAGS_COMPLETED = (1 << 1),
	SCENARIO_FLAGS_SIXFLAGS = (1 << 2)
};

enum {
	S6_TYPE_SAVEDGAME,
	S6_TYPE_SCENARIO
};

#define S6_RCT2_VERSION 120001
#define S6_MAGIC_NUMBER 0x00031144

enum {
	// RCT2 categories (keep order)
	SCENARIO_CATEGORY_BEGINNER,
	SCENARIO_CATEGORY_CHALLENGING,
	SCENARIO_CATEGORY_EXPERT,
	SCENARIO_CATEGORY_REAL,
	SCENARIO_CATEGORY_OTHER,

	// OpenRCT2 categories
	SCENARIO_CATEGORY_DLC,
	SCENARIO_CATEGORY_BUILD_YOUR_OWN,

	SCENARIO_CATEGORY_COUNT
};

enum {
	OBJECTIVE_NONE,
	OBJECTIVE_GUESTS_BY,
	OBJECTIVE_PARK_VALUE_BY,
	OBJECTIVE_HAVE_FUN,
	OBJECTIVE_BUILD_THE_BEST,
	OBJECTIVE_10_ROLLERCOASTERS,
	OBJECTIVE_GUESTS_AND_RATING,
	OBJECTIVE_MONTHLY_RIDE_INCOME,
	OBJECTIVE_10_ROLLERCOASTERS_LENGTH,
	OBJECTIVE_FINISH_5_ROLLERCOASTERS,
	OBJECTIVE_REPLAY_LOAN_AND_PARK_VALUE,
	OBJECTIVE_MONTHLY_FOOD_INCOME
};

typedef struct {
	utf8 *fileName;
	utf8 *name;
	money32 company_value;
	datetime64 timestamp;
} scenario_highscore_entry;

typedef struct {
	utf8 path[MAX_PATH];
	uint64 timestamp;

	// Category / sequence
	uint8 category;
	uint8 source_game;
	sint16 source_index;
	uint16 sc_id;

	// Objective
	uint8 objective_type;
	uint8 objective_arg_1;
	sint32 objective_arg_2;
	sint16 objective_arg_3;
	scenario_highscore_entry *highscore;

	utf8 name[64];
	utf8 details[256];
} scenario_index_entry;

typedef struct {
	const utf8 *title;
	uint8 id;
	uint8 source;
	sint32 index;
	uint8 category;
} source_desc;

extern const rct_string_id ScenarioCategoryStringIds[SCENARIO_CATEGORY_COUNT];

#define gScenarioSrand0						RCT2_GLOBAL(RCT2_ADDRESS_SCENARIO_SRAND_0, uint32)
#define gScenarioSrand1						RCT2_GLOBAL(RCT2_ADDRESS_SCENARIO_SRAND_1, uint32)

#define gScenarioObjectiveType				RCT2_GLOBAL(RCT2_ADDRESS_OBJECTIVE_TYPE, uint8)
#define gScenarioObjectiveYear				RCT2_GLOBAL(RCT2_ADDRESS_OBJECTIVE_YEAR, uint8)
#define gScenarioObjectiveNumGuests			RCT2_GLOBAL(RCT2_ADDRESS_OBJECTIVE_NUM_GUESTS, uint16)
#define gScenarioObjectiveCurrency			RCT2_GLOBAL(RCT2_ADDRESS_OBJECTIVE_CURRENCY, money32)

#define gScenarioParkRatingWarningDays		RCT2_GLOBAL(RCT2_ADDRESS_PARK_RATING_WARNING_DAYS, uint16)
#define gScenarioCompletedCompanyValue		RCT2_GLOBAL(RCT2_ADDRESS_COMPLETED_COMPANY_VALUE, money32)

// Scenario list
extern int gScenarioListCount;
extern int gScenarioListCapacity;
extern scenario_index_entry *gScenarioList;

extern char *gScenarioName;
extern char *gScenarioDetails;
extern char *gScenarioCompletedBy;
extern char gScenarioSavePath[MAX_PATH];
extern int gFirstTimeSave;
extern uint32 gLastAutoSaveTick;

bool scenario_scores_save();
void scenario_load_list();
void scenario_list_dispose();
scenario_index_entry *scenario_list_find_by_filename(const utf8 *filename);
scenario_index_entry *scenario_list_find_by_path(const utf8 *path);
scenario_highscore_entry *scenario_highscore_insert();
void scenario_highscore_free(scenario_highscore_entry *highscore);
bool scenario_load_basic(const char *path, rct_s6_header *header, rct_s6_info *info);
int scenario_load(const char *path);
int scenario_load_and_play_from_path(const char *path);
void scenario_begin();
void scenario_update();
unsigned int scenario_rand();
unsigned int scenario_rand_max(unsigned int max);
int scenario_prepare_for_save();
int scenario_save(SDL_RWops* rw, int flags);
int scenario_save_network(SDL_RWops* rw);
bool scenario_save_s6(SDL_RWops* rw, rct_s6_data *s6);
void scenario_set_filename(const char *value);
void scenario_failure();
void scenario_success();
void scenario_success_submit_name(const char *name);
void scenario_autosave_check();

bool scenario_get_source_desc(const utf8 *name, source_desc *outDesc);
bool scenario_get_source_desc_by_id(uint8 id, source_desc *outDesc);
void scenario_normalise_name(utf8 *name);

// RCT1 scenario index map
enum {
	SC_UNIDENTIFIED = 255,

	// RCT
	SC_FOREST_FRONTIERS = 0,
	SC_DYNAMITE_DUNES,
	SC_LEAFY_LAKES,
	SC_DIAMOND_HEIGHTS,
	SC_EVERGREEN_GARDENS,
	SC_BUMBLY_BEACH,
	SC_TRINITY_ISLANDS,
	SC_KATIES_DREAMLAND,
	SC_POKEY_PARK,
	SC_WHITE_WATER_PARK,
	SC_MILLENNIUM_MINES,
	SC_KARTS_COASTERS,
	SC_MELS_WORLD,
	SC_MYSTIC_MOUNTAIN,
	SC_PACIFIC_PYRAMIDS,
	SC_CRUMBLY_WOODS,
	SC_PARADISE_PIER,
	SC_LIGHTNING_PEAKS,
	SC_IVORY_TOWERS,
	SC_RAINBOW_VALLEY,
	SC_THUNDER_ROCK,
	SC_MEGA_PARK,

	// Loopy Landscapes
	SC_ICEBERG_ISLANDS,
	SC_VOLCANIA,
	SC_ARID_HEIGHTS,
	SC_RAZOR_ROCKS,
	SC_CRATER_LAKE,
	SC_VERTIGO_VIEWS,
	SC_PARADISE_PIER_2,
	SC_DRAGONS_COVE,
	SC_GOOD_KNIGHT_PARK,
	SC_WACKY_WARREN,

	// Special
	ALTON_TOWERS,
	FORT_ANACHRONISM,

	// Added Attractions
	SC_WHISPERING_CLIFFS = 40,
	SC_THREE_MONKEYS_PARK,
	SC_CANARY_MINES,
	SC_BARONY_BRIDGE,
	SC_FUNTOPIA,
	SC_HAUNTED_HARBOUR,
	SC_FUN_FORTRESS,
	SC_FUTURE_WORLD,
	SC_GENTLE_GLEN,
	SC_JOLLY_JUNGLE,
	SC_HYDRO_HILLS,
	SC_SPRIGHTLY_PARK,
	SC_MAGIC_QUARTERS,
	SC_FRUIT_FARM,
	SC_BUTTERFLY_DAM,
	SC_COASTER_CANYON,
	SC_THUNDERSTORM_PARK,
	SC_HARMONIC_HILLS,
	SC_ROMAN_VILLAGE,
	SC_SWAMP_COVE,
	SC_ADRENALINE_HEIGHTS,
	SC_UTOPIA,
	SC_ROTTING_HEIGHTS,
	SC_FIASCO_FOREST,
	SC_PICKLE_PARK,
	SC_GIGGLE_DOWNS,
	SC_MINERAL_PARK,
	SC_COASTER_CRAZY,
	SC_URBAN_PARK,
	SC_GEOFFREY_GARDENS,

	// Special
	SC_HEIDE_PARK,
	SC_PCPLAYER,
	SC_PCGW,
	SC_GAMEPLAY,
	SC_BLACKPOOL_PLEASURE_BEACH,

	// Loopy Landscapes
	SC_GRAND_GLACIER = 80,
	SC_CRAZY_CRATERS,
	SC_DUSTY_DESERT,
	SC_WOODWORM_PARK,
	SC_ICARUS_PARK,
	SC_SUNNY_SWAMPS,
	SC_FRIGHTMARE_HILLS,
	SC_THUNDER_ROCKS,
	SC_OCTAGON_PARK,
	SC_PLEASURE_ISLAND,
	SC_ICICLE_WORLDS,
	SC_SOUTHERN_SANDS,
	SC_TINY_TOWERS,
	SC_NEVERMORE_PARK,
	SC_PACIFICA,
	SC_URBAN_JUNGLE,
	SC_TERROR_TOWN,
	SC_MEGAWORLD_PARK,
	SC_VENUS_PONDS,
	SC_MICRO_PARK,
};

#endif
