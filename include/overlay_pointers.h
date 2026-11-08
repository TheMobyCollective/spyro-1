#ifndef __OVERLAY_POINTERS_H
#define __OVERLAY_POINTERS_H

#include <sys/types.h>

#include "moby.h"

#define PRIMITIVE_CAT3(a, b, c) a##b##c
#define CAT3(a, b, c) PRIMITIVE_CAT3(a, b, c)

#define NAME_OVERLAY_FUNCTION(func) CAT3(func, _, OVERLAY_NAME)
#define NAME_OVERLAY_FUNCTION_LEVEL(func, level) CAT3(func, _LEVEL_, level)

extern Moby *(*g_SpawnMoby)(int pClass, Moby *pParent);
extern void (*g_UpdateMoby)();

extern void (*g_FlightResultsUpdate)();
extern void (*D_8007567C)(); // g_DrawGameState7

extern void (*g_SpawnParticle)(int pAmount, int pClass, void *spawnParam,
                               int extraParam);
extern void (*g_UpdateParticle)(int);

extern void (*g_BalloonistEnter)(Moby *pBalloonist);
extern void (*g_BalloonistExit)();
extern void (*g_BalloonistUpdate)();
extern void (*g_BalloonistDraw)();

extern void (*D_80075694)(); // g_UnkFunc1Flight (I think update flight stuff?)
extern void (*D_800757A8)(
    int pUnk); // g_UnkFunc2Flight (Related to starting / stopping flight)
extern int (*D_800758C4)(int pTimer, Vector3D *pPos, int pColor); // g_DrawTime

// clang-format off
// For all levels
#define FOR_LEVELS(o) \
    o(10) o(11) o(12) o(13) o(14) o(15) \
    o(20) o(21) o(22) o(23) o(24) o(25) \
    o(30) o(31) o(32) o(33) o(34) o(35) \
    o(40) o(41) o(42) o(43) o(44) o(45) \
    o(50) o(51) o(52) o(53) o(54) o(55) \
    o(60) o(61) o(62) o(63) o(64)

// Flight levels need flight functions
#define FOR_FLIGHTS(f)\
    f(15) \
    f(25) \
    f(35) \
    f(45) \
    f(55)

// Levels with the balloon moby need balloonist functions
#define FOR_BALLOONS(b) \
    b(10) \
    b(11) \
    b(13) \
    b(20) \
    b(21) \
    b(22) \
    b(30) \
    b(40) \
    b(50) \
    b(60)

// Test levels all have the same functions as regular levels
#define FOR_TEST_LEVELS(o) \
    o(0) o(1) o(2) o(3) o(4) \
    o(7) o(9) o(99)

// Test levels that seemingly had balloonist functions
#define FOR_TEST_LEVELS_BALLOON(o) \
    o(0)

#define o(level) \
    void NAME_OVERLAY_FUNCTION_LEVEL(Terminator, level)(void); \
    Moby *NAME_OVERLAY_FUNCTION_LEVEL(SpawnMoby, level)(int pClass, Moby *pParent); \
    void NAME_OVERLAY_FUNCTION_LEVEL(UpdateMoby, level)(void); \
    void NAME_OVERLAY_FUNCTION_LEVEL(SpawnParticle, level)(int pAmount, int pClass, void *spawnParam, int extraParam); \
    void NAME_OVERLAY_FUNCTION_LEVEL(UpdateParticle, level)(int pDelta);

// Flight funcs are generically named for now, here and in overlay_pointers.c
#define f(level) \
    void NAME_OVERLAY_FUNCTION_LEVEL(Flight1, level)(void); \
    void NAME_OVERLAY_FUNCTION_LEVEL(Flight2, level)(int pUnk); \
    void NAME_OVERLAY_FUNCTION_LEVEL(Flight3, level)(void); \
    int NAME_OVERLAY_FUNCTION_LEVEL(Flight4, level)(int pTimer, Vector3D* pPos, int pColor); \
    void NAME_OVERLAY_FUNCTION_LEVEL(Flight5, level)(void);

#define b(level) \
    void NAME_OVERLAY_FUNCTION_LEVEL(BalloonistEnter, level)(Moby* bBalloonist); \
    void NAME_OVERLAY_FUNCTION_LEVEL(BalloonistExit, level)(void); \
    void NAME_OVERLAY_FUNCTION_LEVEL(BalloonistUpdate, level)(void); \
    void NAME_OVERLAY_FUNCTION_LEVEL(BalloonistDraw, level)(void);

// clang-format on

FOR_FLIGHTS(f)
FOR_LEVELS(o)
FOR_BALLOONS(b)

FOR_TEST_LEVELS(o)
FOR_TEST_LEVELS_BALLOON(b)

#undef FOR_LEVELS
#undef FOR_FLIGHTS
#undef FOR_BALLOONS
#undef FOR_TEST_LEVELS
#undef FOR_TEST_LEVELS_BALLOON
#undef o
#undef f
#undef b

#endif
