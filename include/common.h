#ifndef __COMMON_H
#define __COMMON_H

#include "include_asm.h"

// x0: Homeworld
// x1: Level B
// x2: Level C
// x3: Level D
// x4: Boss
// x5: Flying

#define HOMEWORLD_COUNT 6
#define LEVEL_PER_HOMEWORLD 6
#define TOTAL_LEVEL_COUNT (HOMEWORLD_COUNT * LEVEL_PER_HOMEWORLD) /* 36 */

/* clang-format off */ 

#define nullptr ((void *)0)

/* clang-format on */

#define PATCH_POINTER(dest, base) dest = (void *)((u_int)(base) + (u_int)(dest));
#define PATCH_POINTER2(dest, base) dest = (void *)((u_int)(dest) + (u_int)(base));

// This ABS macro makes GCC really shit the bed when it comes to optimizations!
// Holy fuck!
#define ABS(x) ((x) >= 0 ? (x) : -(x))

//because why not have this one too!
#define ABS2(x) ((x) > 0 ? (x) : -(x))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

typedef enum {
  GS_Playing = 0,
  GS_Loading = 1,
  GS_PauseMenu = 2,
  GS_InvetoryMenu = 3,
  GS_Respawn = 4,
  GS_GameOver = 5,

  GS_Dragon = 8,

  GS_ExitLevel = 10,
  GS_Fairy = 11,
  GS_Baloonist = 12,
  GS_TitleScreen = 13,

  GS_Credits = 15
} Gamestate;

extern int g_Gamestate;   // Gamestate
extern int g_StateSwitch; // Whether to skip the draw routine because of a
                          // gamestate switch

// Number of unprocessed frames
extern int g_UnprocessedFrames;

extern int g_DeltaTime; // global delta time
extern int D_800756C4;  // Deltatime inside overlays

extern int D_800758C8; // Number of ticks since in the level

extern int D_8007572C; // Number of ticks (also since in the level)

extern int D_8007576C; // For loading, the VRAM part we're loading

extern int D_80075918; // Fade

extern int g_LevelId;  // Current level id
extern int D_800758B4; // The level you're traveling to

// Used to save which level you started the credits cheat on
extern int D_80075818;

extern unsigned char D_800758D0[8]; // Unlocked homeworlds

extern int D_80075830; // Key flag

extern int D_8007582C; // Spyro's extra life count
extern int D_800758E8; // Life orb count

extern struct {
  unsigned char m_Homeworlds[HOMEWORLD_COUNT];
  unsigned char m_Levels[TOTAL_LEVEL_COUNT];
} D_80078E72;

extern unsigned char D_8007A6A8[TOTAL_LEVEL_COUNT]; // Level completion flags

extern const char* D_8006F7F0[]; // Level name table

#endif