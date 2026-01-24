#ifndef __LOADERS_H
#define __LOADERS_H

#include <sys/types.h>

#include "moby.h"

extern int g_PortalLevelId; // Portal level id
extern int g_LoadStage;     // Load stage
extern int g_CutsceneIdx;   // Cutscene type

/// @brief Flag indicating active level transition (1 = transitioning, 0 = not)
extern int g_HasLevelTransition;

typedef struct {
    short xOffset;
    short yOffset;
    short targetX;
    short targetY;
    u_char _08;
    u_char age;
    Vector3D8 rot;
    u_char _0D;
    u_char _0E;
    u_char _0F;
} TransGem;

extern int g_LevelTransHudActive;     // Show transition text D_800756B0
extern int g_LevelTransTicks;         // Ticks in level transition D_800756AC
extern TransGem* g_LevelTransGems;    // Up to 64 gems D_8007571C
extern int g_LevelTransChestDuration; // Duration for initial chest popup depending on collected gems D_80075740
extern int g_NGemsSinceLevelEntry;    // Number of gems collected since level entry D_800756C8







Model *PatchMobyModelPointers(Model *pModel);

void LoadCutscene(void); // Load titlescreen

/// @brief Load dragon cutscene
void LoadDragonCutscene(void);

void LoadLevel(int); // Load level

#endif
