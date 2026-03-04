#ifndef __COMMON_H
#define __COMMON_H

#include "include_asm.h"
#include "level.h"

#include <sys/types.h>

/* clang-format off */ 

#define nullptr ((void *)0)

/* clang-format on */

#define OFFSET(type, field) ((u_int) & (((type *)0)->field))

// Different from setUVWH, that one calculates the UVs based on the input
// this one reuses them (i.e. u3=u1, v3=v2)
#define setUVWH2(p, _u0, _v0, _w, _h)                                          \
  (p)->u0 = (_u0), (p)->v0 = (_v0), (p)->u1 = (p)->u0 + (_w),                  \
  (p)->v1 = (p)->v0, (p)->u2 = (p)->u0, (p)->v2 = (p)->v0 + (_h),              \
  (p)->u3 = (p)->u1, (p)->v3 = (p)->v2

#define PATCH_POINTER(dest, base)                                              \
  dest = (void *)((u_int)(base) + (u_int)(dest));
#define PATCH_POINTER2(dest, base)                                             \
  dest = (void *)((u_int)(dest) + (u_int)(base));

// This ABS macro makes GCC really shit the bed when it comes to optimizations!
// Holy fuck!
#define ABS(x) ((x) >= 0 ? (x) : -(x))

// because why not have this one too!
#define ABS2(x) ((x) > 0 ? (x) : -(x))

#define MIN(a, b) ((b) < (a) ? (b) : (a))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

typedef enum {
  GS_Playing = 0,
  GS_LevelTransition = 1,

  GS_PauseMenu = 2,
  GS_InventoryMenu = 3,

  GS_Respawn = 4,
  GS_GameOver = 5,

  GS_OldDragon = 6, // From prototypes

  GS_FlightResults = 7, // From prototypes

  GS_Dragon = 8,

  GS_EntranceAnimation = 9,

  GS_ExitLevel = 10,
  GS_Fairy = 11,
  GS_Balloonist = 12,

  // Special
  GS_TitleScreen = 13,
  GS_Cutscene = 14,
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

extern int g_GameTick; // Game frame counter (reset on level load)

extern int D_8007576C; // For loading, the VRAM part we're loading

extern int g_Fade; // Fade

// Used to save which level you started the credits cheat on
extern int D_80075818;

extern int D_80075830; // Key flag

extern int g_SkipLowPolyWorld; // Skip low-poly model in world

extern int g_SpyroLifeCount; // Spyro's extra life count
extern int g_LifeOrbCount;   // Life orb count

extern int D_8007575C; // Skybox color lerp value

typedef struct {
  u_char r, g, b, s;
} Color;

typedef struct {
  int r, g, b;
} ColorInt;

typedef struct {
  union {
    struct {
      u_char u0, v0;
      u_short clut;
    } s;
    int all;
  } uv0;
  union {
    struct {
      u_char u1, v1;
      u_short tpage;
    } s;
    int all;
  } uv1;
} Tiledef;

#endif
