#include "common.h"

#include "overlay_pointers.h"

// Later levels keep their raw func_ symbols: the generic overlay spawner
// only names levels 10-15, so point it at this level's spawn function.
#undef NAME_OVERLAY_FUNCTION
#define NAME_OVERLAY_FUNCTION(func) func_level_42_80084718

#define LEVEL 42

#define HAS_MOBY_250
#define HAS_MOBY_194
#define HAS_MOBY_195
#define HAS_MOBY_329
#define HAS_MOBY_421
#define HAS_MOBY_392
#define HAS_MOBY_405
#define HAS_MOBY_400

INCLUDE_ASM("asm/nonmatchings/overlays/level_42", func_level_42_8007AFBC);

#include "overlays/moby_spawn.inc.h"
