#ifndef __GAMESTATE_DRAW_H
#define __GAMESTATE_DRAW_H
#include "common.h"
#include "graphics.h"
#include "hud.h"
#include "moby.h"

/// @brief Create text Mobys, no capitalization
Moby *func_80017FE4(char *pText, Vector3D *pPosition, int pSpaceWidth,
                    int pShadeIndex);

/// @brief Create text Mobys
Moby *func_800181AC(char *pText, Vector3D *pPosition, Vector3D *pTextSpacing,
                    int pSpaceWidth, int pShadeIndex);

/// @brief Creates shaded line
void func_8001844C(int pX0, int pY0, int pX1, int pY1);

/// @brief Creates an arrow
void func_80018534(Vector3D *pPosition, int pTimer, int pRotate);

/// @brief Creates a shaded box
void func_8001860C(int pX0, int pX1, int pY0, int pY1);

/// @brief Creates rescued dragon text
void func_80018728(void);

void func_80018878(void);

/// @brief Copies the HUD mobys to the shaded mobys
void func_80018880(void);

/// @brief Creates the demo mode text
void func_80018908(void);

/// @brief Creates tracers, C function, god knows why
void func_800189F0(void);

/// @brief Creates the border
void func_80018F30(void);

/// @brief Creates fade in/out
// Not u_char, because the input is not AND'd
void func_800190D4(int pMode, int pR, int pG, int pB);

/// @brief Creates a 2D sprite
void func_8001919C(RECT *pDest, Tiledef *pUV, ColorInt *pColor);

/// @brief Creates the collectable icons and counters
void func_80019300(void);

/// @brief Creates Mobys, shadows, Spyro, flame and glows and sparkles
void func_80019698(void);

/// @brief Creates the level transition text
void func_8001973C(void);

/// @brief Gamestate 1
void func_8001A050(void);

/// @brief Gamestate 2 & 3
void func_8001A40C(void);

/// @brief Gamestate 10
void func_8001C694(void);

/// @brief Gamestate 4 & 5
void func_8001CA38(void);

/// @brief Gamestate 8
void func_8001CFDC(void);

/// @brief Gamestate 11
void func_8001D718(void);

/// @brief Gamestate 12, balloon transition and balloonist talk
void func_8001E24C(void);

/// @brief Gamestate 13
void func_8001E6B8(void);

/// @brief Gamestate 14
void func_8001E9C8(void);

/// @brief Gamestate 15
void func_8001EB80(void);

/// @brief Gamestate draw function
void GamestateDraw(void);

extern int g_ScreenBorderEnabled; // Is the screen border enabled
extern int D_800756C0;            // Border size

#endif // !__GAMESTATE_DRAW_H
