#ifndef __OVERLAY_POINTERS_H
#define __OVERLAY_POINTERS_H

#include <sys/types.h>

#include "moby.h"

#define PRIMITIVE_CAT3(a, b, c) a##b##c
#define CAT3(a, b, c) PRIMITIVE_CAT3(a, b, c)

#define NAME_OVERLAY_FUNCTION(func) CAT3(func, _level_, LEVEL)
#define NAME_OVERLAY_FUNCTION_LEVEL(func, level) CAT3(func, _level_, level)

extern Moby *(*g_SpawnMoby)(int pClass, Moby *pParent); // g_MobySpawn
extern void (*g_UpdateMoby)();

extern void (*g_FlightResultsUpdate)();
extern void (*D_8007567C)(); // g_DrawGameState7

extern void (*D_800758E4)(int pAmount, int pClass, void *spawnParam,
                          void *extraParam); // g_ParticleSpawn
extern void (*g_UpdateParticle)();

extern void (*D_800757A0)(); // g_BalloonistTriggerCode (called inside the
                             // overlay for fuck knows why!)
extern void (*D_800758A8)(); // g_BalloonistCloseDialogue (unused, called
                             // directly instead)
extern void (*D_8007574C)(); // g_BalloonistCameraCode
extern void (*D_800758D8)(); // g_BalloonistTalkCode

extern void (*D_80075694)(); // g_UnkFunc1Flight (I think update flight stuff?)
extern void (
    *D_800757A8)(int pUnk); // g_UnkFunc2Flight (Related to starting / stopping flight)
extern int (*D_800758C4)(int pTimer, Vector3D* pPos, int pColor); // g_DrawTime

// These don't all exist yet

// clang-format off
#define FOR_LEVELS(o) \
    o(10) \
    o(11) \
    o(12) \
    o(13) \
    o(14) \
    o(15)


#define o(level) \
    Moby *NAME_OVERLAY_FUNCTION_LEVEL(SpawnMoby, level)(int pClass, Moby *pParent);

#define FOR_FLIGHTS(f)\
    f(15) \
    f(25) \
    f(35) \
    f(45) \
    f(55)

// Flight funcs are generically named for now, here and in overlay_pointers.c
#define f(level) \
    void NAME_OVERLAY_FUNCTION_LEVEL(Flight1, level)(void); \
    void NAME_OVERLAY_FUNCTION_LEVEL(Flight2, level)(int pUnk); \
    void NAME_OVERLAY_FUNCTION_LEVEL(Flight3, level)(void); \
    int NAME_OVERLAY_FUNCTION_LEVEL(Flight4, level)(int pTimer, Vector3D* pPos, int pColor); \
    void NAME_OVERLAY_FUNCTION_LEVEL(Flight5, level)(void);

// clang-format on

FOR_FLIGHTS(f)
FOR_LEVELS(o)

#undef o
#undef FOR_LEVELS
#undef f
#undef FOR_FLIGHTS

#endif
