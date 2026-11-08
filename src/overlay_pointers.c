#include "overlay_pointers.h"
#include "buffers.h"
#include "common.h"

#include <stdlib.h>

#define LEVEL_CASE(pLevel)                                                     \
  case pLevel:                                                                 \
    g_Buffers.m_CopyBuf = Terminator_LEVEL_##pLevel;                           \
    g_SpawnMoby = SpawnMoby_LEVEL_##pLevel;                                    \
    g_UpdateMoby = UpdateMoby_LEVEL_##pLevel;                                  \
    g_SpawnParticle = SpawnParticle_LEVEL_##pLevel;                            \
    g_UpdateParticle = UpdateParticle_LEVEL_##pLevel;                          \
    break;

#define LEVEL_CASE_BALLOON(pLevel)                                             \
  case pLevel:                                                                 \
    g_Buffers.m_CopyBuf = Terminator_LEVEL_##pLevel;                           \
    g_SpawnMoby = SpawnMoby_LEVEL_##pLevel;                                    \
    g_UpdateMoby = UpdateMoby_LEVEL_##pLevel;                                  \
    g_SpawnParticle = SpawnParticle_LEVEL_##pLevel;                            \
    g_UpdateParticle = UpdateParticle_LEVEL_##pLevel;                          \
    g_BalloonistEnter = BalloonistEnter_LEVEL_##pLevel;                        \
    g_BalloonistExit = BalloonistExit_LEVEL_##pLevel;                          \
    g_BalloonistUpdate = BalloonistUpdate_LEVEL_##pLevel;                      \
    g_BalloonistDraw = BalloonistDraw_LEVEL_##pLevel;                          \
    break;

#define LEVEL_CASE_FLIGHT(pLevel)                                              \
  case pLevel:                                                                 \
    g_Buffers.m_CopyBuf = Terminator_LEVEL_##pLevel;                           \
    g_SpawnMoby = SpawnMoby_LEVEL_##pLevel;                                    \
    g_UpdateMoby = UpdateMoby_LEVEL_##pLevel;                                  \
    g_SpawnParticle = SpawnParticle_LEVEL_##pLevel;                            \
    g_UpdateParticle = UpdateParticle_LEVEL_##pLevel;                          \
    D_80075694 = Flight1_LEVEL_##pLevel;                                       \
    D_800757A8 = Flight2_LEVEL_##pLevel;                                       \
    g_FlightResultsUpdate = Flight3_LEVEL_##pLevel;                            \
    D_8007567C = Flight5_LEVEL_##pLevel;                                       \
    D_800758C4 = Flight4_LEVEL_##pLevel;                                       \
    break;

void SetOverlayPointers(void) {
  switch (g_LevelId) {
    // Test levels
    LEVEL_CASE_BALLOON(0);
    LEVEL_CASE(1);
    LEVEL_CASE(2);
    LEVEL_CASE(3);
    LEVEL_CASE(4);
    LEVEL_CASE(7);
    LEVEL_CASE(9);

    // Actual level cases

    // Artisans
    LEVEL_CASE_BALLOON(10);
    LEVEL_CASE_BALLOON(11);
    LEVEL_CASE(12);
    LEVEL_CASE_BALLOON(13);
    LEVEL_CASE(14);
    LEVEL_CASE_FLIGHT(15);

    // Peace Keepers
    LEVEL_CASE_BALLOON(20);
    LEVEL_CASE_BALLOON(21);
    LEVEL_CASE_BALLOON(22);
    LEVEL_CASE(23);
    LEVEL_CASE(24);
    LEVEL_CASE_FLIGHT(25);

    // Magic Crafters
    LEVEL_CASE_BALLOON(30);
    LEVEL_CASE(31);
    LEVEL_CASE(32);
    LEVEL_CASE(33);
    LEVEL_CASE(34);
    LEVEL_CASE_FLIGHT(35);

    // Beast Makers
    LEVEL_CASE_BALLOON(40);
    LEVEL_CASE(41);
    LEVEL_CASE(42);
    LEVEL_CASE(43);
    LEVEL_CASE(44);
    LEVEL_CASE_FLIGHT(45);

    // Dream Weavers
    LEVEL_CASE_BALLOON(50);
    LEVEL_CASE(51);
    LEVEL_CASE(52);
    LEVEL_CASE(53);
    LEVEL_CASE(54);
    LEVEL_CASE_FLIGHT(55);

    // Gnasty's World
    LEVEL_CASE_BALLOON(60);
    LEVEL_CASE(61);
    LEVEL_CASE(62);
    LEVEL_CASE(63);
    LEVEL_CASE(64);

    // Another test level
    LEVEL_CASE(99);

#if 0
  default:
    // There used to be a printf here that said:
    printf("Invalid Level %d, file LOADERS.C\n", g_LevelId);
    exit();
    break;
#endif
  }

  g_Buffers.m_DiscCopyBuf = g_Buffers.m_CopyBuf;
}
