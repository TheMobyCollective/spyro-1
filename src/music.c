#include "music.h"
#include "common.h"
#include "spu.h"

// Music update
INCLUDE_ASM("asm/nonmatchings/music", func_8002BBE0);

// TODO: Oops have to relocate, this is the cutscene update function
INCLUDE_ASM("asm/nonmatchings/music", func_8002BFE0);
