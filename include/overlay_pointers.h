#ifndef __OVERLAY_POINTERS_H
#define __OVERLAY_POINTERS_H

#include <sys/types.h>

#include "moby.h"

extern Moby *(*D_800758CC)(int pClass, Moby *pMe); // g_MobySpawn
extern void (*D_80075734)();                       // g_MobyUpdate

extern void (*D_800757C0)(); // g_UpdateGameState7
extern void (*D_8007567C)(); // g_DrawGameState7

extern void (*D_800758E4)(int pAmount, int pClass, void *spawnParam,
                          void *extraParam); // g_ParticleSpawn
extern void (*D_800756BC)();                 // g_ParticleUpdate

extern void (*D_800757A0)(); // g_BalloonistTriggerCode (called inside the
                             // overlay for fuck knows why!)
extern void (*D_800758A8)(); // g_BalloonistCloseDialogue (unused, called
                             // directly instead)
extern void (*D_8007574C)(); // g_BalloonistCameraCode
extern void (*D_800758D8)(); // g_BalloonistTalkCode

extern void (*D_80075694)(); // g_UnkFunc1Flight (I think update flight stuff?)
extern void (
    *D_800757A8)(); // g_UnkFunc2Flight (Related to starting / stopping flight)
extern void (*D_800758C4)(); // g_DrawTime

#endif