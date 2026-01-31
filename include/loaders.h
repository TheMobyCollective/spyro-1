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



/// @brief Loads in a new sound table
/// @param pData The data to load
/// @param pPatchAddressesInTable Whether to patch the addresses in the table
void SetNewSoundTable(char *pData, int pPatchAddressesInTable);

/// @brief Loads the level scene, as we used to call it
/// @param pData The data to load
/// @param pCutscene Whether it's scene data for a cutscene, which is missing
/// collision and occlusion data
/// @return The end of the scene data
void *func_80012D58(void *pData, int pCutscene);

/// @brief Patches the pointers inside of Spyro's model
// Has some cool code added after July
void PatchInSpyroAnimations(void *data);

/// @brief Patches the pointers inside of a Moby's model
Model *PatchMobyModelPointers(Model *pModel);

/// @brief Loads the level's layout
void func_8001364C(int pAnimationsAndSparx);

/// @brief Reload the current level's layout
void func_800144C8(void);

/// @brief Load a cutscene (titlescreen, intro, outro)
void LoadCutscene(void);

/// @brief Load dragon cutscene
void LoadDragonCutscene(void);

/// @brief Runs through load stages to load a level
void LoadLevel(int pArg);

#endif
