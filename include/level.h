#ifndef __LEVEL_H
#define __LEVEL_H

/**
 * Levels (including homeworlds) are identified primarily by LevelId.
 * Other representations can be derived from the LevelId.
 *
 * LevelId is a two-digit decimal number
 *   - The first digit is the Homeworld Number
 *   - The second digit is the Level Number
 *
 * Homeworld Number goes from 1 (Artisan's) to 6 (Gnasty's World)
 * Homeworld Index represents the same order but transformed to [0, 5].
 *
 * Level Number is either 0 (Homeworld), 1, 2, 3, 4 (Boss) or 5 (Flight).
 * Any other Level Number is invalid.
 *
 * Level Index is a transformation from LevelId to a continiguous, zero-indexed
 * list of levels from 0 (Artisan's Homeworld) to 34 (Gnasty's Loot).
 *
 * The game code and transformations actually assume 36 levels (6 homeworlds
 * with 5 portals each), but Gnasty's World has one less level (and technically
 * no Flight level as described by Level Number).
 *
 * In practice, the maths doesn't care because Gnasty's World is the final
 * homeworld and the last theoretical LevelId is never used; there is also a
 * runtime check for LevelId 63 being the Boss, rather than the expected 64.
 */
typedef enum {
  // Artisans
  LEVEL_ARTISANS_HOME = 10,
  LEVEL_STONE_HILL = 11,
  LEVEL_DARK_HOLLOW = 12,
  LEVEL_TOWN_SQUARE = 13,
  LEVEL_TOASTY = 14,
  LEVEL_SUNNY_FLIGHT = 15,

  // Peace Keepers
  LEVEL_PEACE_KEEPERS_HOME = 20,
  LEVEL_DRY_CANYON = 21,
  LEVEL_CLIFF_TOWN = 22,
  LEVEL_ICE_CAVERN = 23,
  LEVEL_DOCTOR_SHEMP = 24,
  LEVEL_NIGHT_FLIGHT = 25,

  // Magic Crafters
  LEVEL_MAGIC_CRAFTERS_HOME = 30,
  LEVEL_ALPINE_RIDGE = 31,
  LEVEL_HIGH_CAVES = 32,
  LEVEL_WIZARD_PEAK = 33,
  LEVEL_BLOWHARD = 34,
  LEVEL_CRYSTAL_FLIGHT = 35,

  // Beast Makers
  LEVEL_BEAST_MAKERS_HOME = 40,
  LEVEL_TERRACE_VILLAGE = 41,
  LEVEL_MISTY_BOG = 42,
  LEVEL_TREE_TOPS = 43,
  LEVEL_METALHEAD = 44,
  LEVEL_WILD_FLIGHT = 45,

  // Dream Weavers
  LEVEL_DREAM_WEAVERS_HOME = 50,
  LEVEL_DARK_PASSAGE = 51,
  LEVEL_LOFTY_CASTLE = 52,
  LEVEL_HAUNTED_TOWERS = 53,
  LEVEL_JACQUES = 54,
  LEVEL_ICY_FLIGHT = 55,

  // Gnasty's World
  LEVEL_GNORC_GNEXUS = 60,
  LEVEL_GNORC_COVE = 61,
  LEVEL_TWILIGHT_HARBOR = 62,
  LEVEL_GNASTY_GNORC = 63,
  LEVEL_GNASTYS_LOOT = 64,
  // No Flight level in Gnasty's World

  // Unused
  LEVEL_UNUSED_0 = 0,
  LEVEL_UNUSED_1 = 1,
  LEVEL_UNUSED_2 = 2,
  LEVEL_UNUSED_3 = 3,
  LEVEL_UNUSED_4 = 4,
  LEVEL_UNUSED_7 = 7,
  LEVEL_UNUSED_9 = 9,
  LEVEL_UNUSED_99 = 99
} LevelId;

#define HOMEWORLD_COUNT 6
#define LEVEL_PER_HOMEWORLD 6
#define TOTAL_LEVEL_COUNT (HOMEWORLD_COUNT * LEVEL_PER_HOMEWORLD) /* 36 */

extern int g_LevelId;     // Current level id
extern int g_NextLevelId; // The level you're traveling to
extern int g_Homeworld;   // Homeworld ID, used by Flight levels

extern int g_LevelIndex;         // Current absolute level id
extern int g_PreviousLevelIndex; // Last absolute level ID

extern unsigned char g_VisitedFlags[TOTAL_LEVEL_COUNT];         // Level visited flags
extern unsigned char g_LevelVortexExitFlags[TOTAL_LEVEL_COUNT]; // Level completion flags

// TODO: Value of 2 == HOMEWORLD_UNLOCKED, not sure about other values yet
extern unsigned char D_800758D0[8]; // Unlocked homeworlds

#define LEVEL_ASSOCIATED_HOMEWORLD_LEVELID(levelId) (((levelId) / 10) * 10)
#define LEVEL_ASSOCIATED_HOMEWORLD_NUMBER(levelId) ((levelId) / 10)
#define LEVEL_ASSOCIATED_HOMEWORLD_INDEX(levelId) (((levelId) / 10) - 1)

#define LEVEL_GET_NUMBER(levelId) ((levelId) % 10)
#define LEVEL_GET_INDEX(levelId) ((LEVEL_ASSOCIATED_HOMEWORLD_INDEX(levelId)) * 6 + LEVEL_GET_NUMBER(levelId))

#define LEVEL_IS_HOMEWORLD(levelId) (((levelId) % 10) == 0)
#define LEVEL_IS_BOSS(levelId) (((levelId) % 10) == 4)
#define LEVEL_IS_FLIGHT(levelId) (((levelId) % 10) == 5)

#endif // __LEVEL_H
