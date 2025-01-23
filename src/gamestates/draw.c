#include "buffers.h"
#include "camera.h"
#include "common.h"
#include "graphics.h"
#include "moby.h"
#include "variables.h"

#include <libgpu.h>

/// @brief Create text Mobys, no capitalization
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80017FE4);

/// @brief Create text Mobys
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_800181AC);

/// @brief Creates shaded line
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001844C);

/// @brief Creates an arrow
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018534);

/// @brief Creates a shaded box
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001860C);

/// @brief Creates rescued dragon text
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018728);

// Unused, boy I wonder.. probably the old dragon cutscenes
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018878);

/// @brief Copies the HUD mobys to the shaded mobys
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018880);

/// @brief Creates the demo mode text
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018908);

/// @brief Creates tracers, C function, god knows why
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_800189F0);

/// @brief Creates the border
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018F30);

/// @brief Creates fade in/out
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_800190D4);

/// @brief Creates a 2D sprite
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001919C);

/// @brief Creates the collectable icons and counters
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80019300);

/// @brief Creates Mobys, shadows, Spyro, flame and glows and sparkles
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80019698);

/// @brief Creates the level transition text
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001973C);

/// @brief Gamestate 1
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001A050);

/// @brief Gamestate 2 & 3
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001A40C);

/// @brief Gamestate 10
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001C694);

/// @brief Gamestate 4 & 5
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001CA38);

/// @brief Gamestate 8
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001CFDC);

/// @brief Gamestate 11
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001D718);

/// @brief Gamestate 12
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001E24C);

/// @brief Gamestate 13
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001E6B8);

/// @brief Gamestate 14
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001E9C8);

/// @brief Gamestate 15
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001EB80);

/// @brief Gamestate draw function
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001ED5C);