#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "common.h"
#include "vector.h"
#include <sys/types.h>

// Misc global variables

extern int D_80075964; // Current absolute level id
extern int D_80075690; // Is flight

extern int g_DragonTotal; // gDragonTotal
extern int g_GemTotal;    // gGemTotal
extern int g_EggTotal;    // gEggTotal

extern int D_8007587C; // Gems we collected before entering the level
extern int D_800756C8; // Gems we've collected in this level since entering

extern int g_LevelDragonCount[TOTAL_LEVEL_COUNT];    // Level dragon counts
extern int g_LevelGemCount[TOTAL_LEVEL_COUNT];       // Level gem counts
extern int g_LevelEggCount[LEVEL_PER_HOMEWORLD * 3]; // Level egg counts

extern short g_TargetGemCounts[TOTAL_LEVEL_COUNT]; // Target gem counts

extern int D_80078618[5];       // Course records
extern u_char D_80078680[5][5]; // Flight collected

extern u_char D_80077908[1200]; // Gem collection mask

extern Vector3D D_80077368;

#endif