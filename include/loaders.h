#ifndef __LOADERS_H
#define __LOADERS_H

#include <sys/types.h>

#include "moby.h"

extern int g_PortalLevelId; // Portal level id
extern int g_LoadStage;     // Load stage
extern int g_CutsceneIdx;   // Cutscene type

extern int D_800756D0; // Has level transition
extern int D_800756B0; // Show transition text
extern int D_800756AC; // Ticks in level transition

Model *PatchMobyModelPointers(Model *pModel);

void LoadCutscene(void); // Load titlescreen

/// @brief Load dragon cutscene
void LoadDragonCutscene(void);

void LoadLevel(int); // Load level

#endif