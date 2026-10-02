#include "common.h"

#include "overlay_pointers.h"

// Later levels keep their raw func_ symbols: the generic overlay spawner
// only names levels 10-15, so point it at this level's spawn function.
#undef NAME_OVERLAY_FUNCTION
#define NAME_OVERLAY_FUNCTION(func) func_level_60_80083568

#define LEVEL 60

#define HAS_MOBY_250
#define HAS_MOBY_194
#define HAS_MOBY_195
#define HAS_MOBY_398
#define HAS_MOBY_405

INCLUDE_ASM("asm/nonmatchings/overlays/level_60", func_level_60_8007D938);

#include "overlays/moby_spawn.inc.h"
