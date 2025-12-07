#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "common.h"
#include "vector.h"
#include <sys/types.h>

// Misc global variables

extern int D_80075690; // Is flight
extern int D_800756A0; // God mode / invincibility cheat flag

extern int g_DragonTotal; // gDragonTotal
extern int g_GemTotal;    // gGemTotal
extern int g_EggTotal;    // gEggTotal

extern int D_8007587C; // Gems we collected before entering the level
extern int D_800756C8; // Gems we've collected in this level since entering

extern int g_LevelDragonCount[TOTAL_LEVEL_COUNT];    // Level dragon counts
extern int g_LevelGemCount[TOTAL_LEVEL_COUNT];       // Level gem counts
extern int g_LevelEggCount[LEVEL_PER_HOMEWORLD * 3]; // Level egg counts

extern short g_TargetGemCounts[TOTAL_LEVEL_COUNT]; // Target gem counts

extern int D_80078618[6];       // Course records
extern u_char D_80078680[6][5]; // Flight collected

extern u_char D_80077908[1200]; // Gem collection mask

extern u_char g_RecentGemsCollected[32];

extern Vector3D
    D_80076B80; // Collision point output (set by collision functions)
extern Vector3D D_80077368; // Collision normal output

extern int D_80075754; // Sound volume
extern int D_80075748; // Music volume

extern short D_80075788; // Idle animation timer

#endif