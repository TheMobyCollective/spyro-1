#ifndef __GAMESTATE_DRAW_H
#define __GAMESTATE_DRAW_H
#include "common.h"
#include "moby.h"
#include "graphics.h"
#include "hud.h"

Moby *func_80017FE4(char *pText, Vector3D *pPosition, int pSpaceWidth,
                    int pShadeIndex);


Moby *func_800181AC(char *pText, Vector3D *pPosition, Vector3D *pTextSpacing,
                    int pSpaceWidth, int pShadeIndex);


void func_8001844C(int pX0, int pY0, int pX1, int pY1);

void func_80018534(Vector3D* pPosition, int pTimer, int pRotate);

void func_8001860C(int pX0, int pX1, int pY0, int pY1);

void func_80018728(void);

void func_80018878(void);

void func_80018880(void);

void func_80018908(void);

void func_800189F0(void);

void func_80018F30(void);

void func_800190D4(int pMode, int pR, int pG, int pB);

void func_8001919C(RECT* pDest, Tiledef* pUV, ColorInt* pColor);

void func_80019300(void);

void func_80019698(void);

void func_8001973C(void);

void func_8001A050(void);

void func_8001A40C(void);

void func_8001C694(void);

void func_8001CA38(void);

void func_8001CFDC(void);

void func_8001D718(void);

void func_8001E24C(void);

void func_8001E6B8(void);

void func_8001E9C8(void);

void func_8001EB80(void);



/// @brief Gamestate draw function
void GamestateDraw(void);

extern int g_ScreenBorderEnabled; // Is the screen border enabled
extern int D_800756C0;            // Border size

#endif // !__GAMESTATE_DRAW_H

