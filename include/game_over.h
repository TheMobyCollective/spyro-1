#ifndef __GAMEOVER_H
#define __GAMEOVER_H

extern int g_GameOverTicks; // Game over ticks
extern int D_80075940;

//Placement and rotation of the GAME OVER text
extern struct {
  short x, y;
} g_GameOverTextXY[8];
extern short g_GameOverTextZ[24];
extern char g_GameOverTextRot[8];

//Tick offsets for when each letter shows up
extern u_char g_GameOverLetterDisplayTicks[8];

extern short g_GameOverSkyboxRotY;
extern short g_GameOverSkyboxRotZ;
extern short g_GameOverRotY;
extern short g_GameOverRotZ;

#endif // __GAMEOVER_H
