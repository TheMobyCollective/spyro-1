#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "common.h"
#include "vector.h"
#include <sys/types.h>

// Misc global variables

extern int g_IsFlightLevel;
extern int D_800756A0; // God mode / invincibility cheat flag

extern int g_DragonTotal; // gDragonTotal
extern int g_GemTotal;    // gGemTotal
extern int g_EggTotal;    // gEggTotal

extern int D_8007587C; // Gems we collected before entering the level
extern int
    g_NGemsSinceLevelEntry; // Gems we've collected in this level since entering

extern int g_LevelDragonCount[TOTAL_LEVEL_COUNT];    // Level dragon counts
extern int g_LevelGemCount[TOTAL_LEVEL_COUNT];       // Level gem counts
extern int g_LevelEggCount[LEVEL_PER_HOMEWORLD * 3]; // Level egg counts

extern u_char g_TargetDragonCounts[TOTAL_LEVEL_COUNT]; // Target dragon counts
extern short g_TargetGemCounts[TOTAL_LEVEL_COUNT];     // Target gem counts
extern u_char g_TargetEggCounts[LEVEL_PER_HOMEWORLD * 3]; // Target egg counts

extern int g_FlightCourseRecords[HOMEWORLD_COUNT];   // Course records
extern u_char g_FlightCollected[HOMEWORLD_COUNT][5]; // Flight collected

// extern u_char D_80077908[1200];
extern u_int D_80077908[36][8]; // Gem collection mask

extern u_char g_RecentGemsCollected[32];

extern Vector3D
    g_CollisionPoint; // Collision hit position (set by raycast functions)
extern Vector3D g_CollisionNormal;   // Surface normal at collision point
extern int g_CollisionTriangleIndex; // Index of collision triangle hit

extern int D_80075754; // Sound volume
extern int D_80075748; // Music volume

extern short D_80075788; // Idle animation timer

extern int D_8007568C; // Pause menu no button ticks
extern int D_800758B8; // Pause menu text rotation ticks

#endif
