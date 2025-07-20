#include "gamestates/draw.h"
#include "buffers.h"
#include "camera.h"
#include "common.h"
#include "cyclorama.h"
#include "environment.h"
#include "gamepad.h"
#include "graphics.h"
#include "math.h"
#include "moby.h"
#include "moby_lists.h"
#include "overlay_pointers.h"
#include "renderers.h"
#include "sony_image.h"
#include "titlescreen.h"
#include "variables.h"

#include <libgpu.h>

// HAS to be local to this file.
struct {
  int post;
  int pre;
} D_80075950;

extern int D_80075704; // Credits sequence
extern int D_800756F8;

// TODO: Remove once func_8001973C is implemented
extern char D_80010ACC[1]; // "RETURNING HOME..."
extern char D_80010AE0[1];
extern char D_80010AF4[1];
extern char D_80010B04[1];
extern char D_80010B14[1];

/// @brief Create text Mobys, no capitalization
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80017FE4);

Moby *func_800181AC(char *pText, Vector3D *pPosition, Vector3D *pTextSpacing,
                    int pSpaceWidth, int pShadeIndex);

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
// Not u_char, because the input is not AND'd
void func_800190D4(int pMode, int pR, int pG, int pB);
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
void func_8001E6B8() {
  if (g_TitlescreenState.m_0x04 == 2 && g_TitlescreenState.m_0x08 > 139) {
    int a, i;
    Moby *curMoby;

    Vector3D position;
    Vector3D spacing;

    position.y = 120;
    position.z = 5120;

    spacing.x = 14;
    spacing.y = 1;
    spacing.z = 5632;

    curMoby = g_HudMobys;

    if (g_TitlescreenState.m_0x1C == 0) {
      position.x = 92;
      func_800181AC("IN THE WORLD OF DRAGONS...", &position, &spacing, 0x10,
                    0xB);
      a = 184;
    } else if (g_TitlescreenState.m_0x1C == 1) {

      // Have we visited Artisans before?
      if (D_80078E72.m_Levels[0]) {
        position.x = 80;
        func_800181AC("THE ADVENTURE CONTINUES...", &position, &spacing, 0x10,
                      0xB);
        a = 188;
      } else {
        position.x = 100;
        func_800181AC("THE ADVENTURE BEGINS...", &position, &spacing, 0x10,
                      0xB);
        a = 182;
      }

    } else {
      position.x = 104;
      func_800181AC("ENTERING DEMO MODE...", &position, &spacing, 0x10, 0xB);
      a = 178;
    }

    // Hide letters based on the number of ticks ran
    if (a > g_TitlescreenState.m_0x08) {
      g_HudMobys += (a - g_TitlescreenState.m_0x08) >> 1;
    }

    i = 0;
    while ((int)(--curMoby) >= (int)g_HudMobys) {
      int l = g_TitlescreenState.m_0x08 - 140 - i;

      if (l < 56) {
        curMoby->m_Rotation.z = l * 8 + 64;
      } else {
        curMoby->m_Rotation.z =
            COSINE_8(((g_TitlescreenState.m_0x08 * 4) + (i * 12)) & 0xFF) >> 7;
      }

      i++;
    }
  }

  setRGB0(&g_DB[0].m_DrawEnv, 0, 0, 0);
  setRGB0(&g_DB[1].m_DrawEnv, 0, 0, 0);

  g_SonyImage.m_ShadedMobys[0] = (void *)0;
  func_80018880(); // Copies the HUD Mobys to the Shaded Mobys list
  Memset(g_SonyImage.m_Buf, 0, 0x900);
  func_80022A2C(); // Renders the shaded mobys

  if (g_TitlescreenState.m_0x04 == 2) {
    // Draw Spyro
    func_80023AC4();

    // Put the 3D text inside of the world
    ((int *)g_WorldOT)[64] = ((int *)g_HudOT)[0];
    ((int *)g_WorldOT)[65] = ((int *)g_HudOT)[1];
    ((int *)g_HudOT)[0] = 0;
    ((int *)g_HudOT)[1] = 0;
  }

  DrawSync(0);
  VSync(0);
  PutDispEnv(&g_CurDB->m_DispEnv);
  PutDrawEnv(&g_CurDB->m_DrawEnv);
  DrawOTag(func_80016784(0x800));
}

/// @brief Gamestate 14
void func_8001E9C8(void) {

  setRGB0(&g_DB[0].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
          g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);
  setRGB0(&g_DB[1].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
          g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);

  func_800521C0();
  func_8001F158();
  Memset(g_SonyImage.m_Buf, 0, 0x900);
  func_8001F798();
  Memset(g_SonyImage.m_Buf, 0, 0x1C00);

  g_Environment.m_CullingDistance = 0x14000;

  func_800258F0(-1);
  func_8004EBA8(-1, &g_Camera.m_ViewMatrix, &g_Camera.m_ProjectionMatrix);

  if (g_Fade) {
    func_800190D4(2, g_Fade * 16, g_Fade * 16, g_Fade * 16);
  }

  DrawSync(0);

  // No clue why this is here, but it is
  if (D_80075784) {
    VSync(0);
  }

  D_80075950.pre = VSync(-1);

  while (D_80075950.pre - D_80075950.post < 2) {
    VSync(0);
    D_80075950.pre = VSync(-1);
  }

  D_80075950.post = VSync(-1);

  PutDispEnv(&g_CurDB->m_DispEnv);
  PutDrawEnv(&g_CurDB->m_DrawEnv);
  DrawOTag(func_80016784(0x800));
}

/// @brief Gamestate 15
void func_8001EB80(void) {
  Vector3D spacing;
  Vector3D position;
  Moby *curMoby;
  int rotOff;

  spacing.x = 16;
  spacing.y = 1;
  spacing.z = 5120;

  position.x = 118;
  position.y = 110;
  position.z = 4352;

  curMoby = g_HudMobys;

  setRGB0(&g_DB[0].m_DrawEnv, 0, 0, 0);
  setRGB0(&g_DB[1].m_DrawEnv, 0, 0, 0);

  func_800181AC(D_80010ACC, &position, &spacing, 18, 11); // "RETURNING HOME..."

  rotOff = 0;

  // Wtf are these int casts?
  while ((int)(--curMoby) >= (int)g_HudMobys) {
    curMoby->m_Rotation.z = COSINE_8(((D_800756F8 * 2) + rotOff) & 0xFF) >> 7;
    rotOff += 12;
  };

  g_SonyImage.m_ShadedMobys[0] = (void *)0;

  func_80018880(); // Copies the HUD Mobys to the Shaded Mobys list
  Memset(g_SonyImage.m_Buf, 0, 0x900);
  func_80022A2C(); // Renders the shaded mobys
  DrawSync(0);

  D_80075950.pre = VSync(-1);

  while (D_80075950.pre - D_80075950.post < 2) {
    VSync(0);
    D_80075950.pre = VSync(-1);
  }

  D_80075950.post = VSync(-1);

  PutDispEnv(&g_CurDB->m_DispEnv);
  PutDrawEnv(&g_CurDB->m_DrawEnv);
  DrawOTag(func_80016784(0x800));
}

void func_titlescreen_8007CEE4(void); // Overlay functions
void func_credits_8007BFD0(void);     // Overlay functions

/// @brief Gamestate draw function
void GamestateDraw(void) {
  DB *db;

  db = &g_DB[0];

  if (db == g_CurDB) {
    db = &g_DB[1];
  }

  g_CurDB = db;
  D_800758B0 = 0;
  g_WorldOT = db->m_WorldOT;
  g_HudOT = db->m_HudOT;
  D_800757B0 = db->m_PolyBuf;
  D_80075780 = (void *)((char *)D_800757B0 + 0x1C000);
  D_800756FC = (void *)((char *)D_800757B0 + 0x1C000);
  g_HudMobys = (void *)((char *)D_800757B0 + 0x1C000);

  CameraUpdateMatrices();

  if (g_Gamestate != GS_Playing) {
    if (g_Gamestate == GS_LevelTransition) {
      func_8001A050();
    } else if (g_Gamestate == GS_PauseMenu) {
      func_8001A40C();
    } else if (g_Gamestate == GS_InventoryMenu) {
      func_8001A40C();
    } else if (g_Gamestate == GS_Respawn) {
      func_8001CA38();
    } else if (g_Gamestate == GS_GameOver) {
      func_8001CA38();
    } else if (g_Gamestate == GS_OldDragon) {
      func_8001A40C();
    } else if (g_Gamestate == GS_FlightResults) {
      // Calls an overlay function
      D_8007567C();
    } else if (g_Gamestate == GS_Dragon) {
      func_8001CFDC();
    } else if (g_Gamestate == 9) {
      func_8001A050();
    } else if (g_Gamestate == GS_ExitLevel) {
      func_8001C694();
    } else if (g_Gamestate == GS_Fairy) {
      func_8001D718();
    } else if (g_Gamestate == GS_Balloonist) {
      func_8001E24C();
    } else if (g_Gamestate == GS_TitleScreen) {
      if (g_TitlescreenState.m_0x00 == 3) {
        func_8001E6B8();
      } else {
        func_titlescreen_8007CEE4();
      }
    } else if (g_Gamestate == GS_Cutscene) {
      func_8001E9C8();
    } else if (g_Gamestate == GS_Credits) {
      if (D_80075704 < 99) {
        func_credits_8007BFD0(); // Overlay function
      } else {
        func_8001EB80();
      }
    }
  } else {

    // Gamestate 0
    setRGB0(&g_DB[0].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
            g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);
    setRGB0(&g_DB[1].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
            g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);

    func_800521C0(); // Queue render mobys

    if (!D_80075690) {
      func_80019300(); // Draw collectables
    }

    // Is demo mode?
    if (g_DemoMode) {
      func_80018908(); // Draw demo mode text
    }

    func_80019698();
    func_8002B9CC();
    func_80050BD0();
    func_800573C8();

    if (g_Fade) {
      func_800190D4(2, g_Fade * 8, g_Fade * 8, g_Fade * 8);
    }

    if (D_8007570C || D_800756C0) {
      func_80018F30();
    }

    func_800189F0();
    DrawSync(0);

    // If demo mode, we always wait one frame, probably for demo consistency
    if (D_80075784) {
      VSync(0);
    }

    D_80075950.pre = VSync(-1);

    while (D_80075950.pre - D_80075950.post < 2) {
      VSync(0);
      D_80075950.pre = VSync(-1);
    }

    D_80075950.post = VSync(-1);

    PutDispEnv(&g_CurDB->m_DispEnv);
    PutDrawEnv(&g_CurDB->m_DrawEnv);
    DrawOTag(func_80016784(0x800));
  }
}