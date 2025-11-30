#include "gamestates/draw.h"
#include "balloonist.h"
#include "buffers.h"
#include "camera.h"
#include "common.h"
#include "cyclorama.h"
#include "environment.h"
#include "fairy.h"
#include "gamepad.h"
#include "graphics.h"
#include "math.h"
#include "memory.h"
#include "moby.h"
#include "moby_lists.h"
#include "overlay_pointers.h"
#include "renderers.h"
#include "sony_image.h"
#include "titlescreen.h"
#include "variables.h"

#include <libetc.h>
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
extern char D_80010AE0[1]; // "CONFRONTING %s..."
extern char D_80010AF4[1]; // "ENTERING %s..."
extern char D_80010B04[1]; // "TREASURE FOUND"
extern char D_80010B14[1]; // "TOTAL TREASURE"

extern char D_80010B6C[1]; // "CONTINUE"

// TODO: Remove once the whole file is implemented
extern char D_80075620[1]; // "RETRY"
extern char D_80075628[1]; // "ABORT"
extern char D_80075630[1]; // "SLOT 1"
extern char D_80075638[1]; // "SLOT 2"

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

void func_8001860C(int pX1, int pX2, int pY1, int pY2);
/// @brief Creates a shaded box
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001860C);

/// @brief Creates rescued dragon text
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018728);

// Unused, boy I wonder.. probably the old dragon cutscenes
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018878);

void func_80018880(void);
/// @brief Copies the HUD mobys to the shaded mobys
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018880);

void func_80018908(void);
/// @brief Creates the demo mode text
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018908);

void func_800189F0(void);
/// @brief Creates tracers, C function, god knows why
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_800189F0);

void func_80018F30(void);
/// @brief Creates the border
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80018F30);

/// @brief Creates fade in/out
// Not u_char, because the input is not AND'd
void func_800190D4(int pMode, int pR, int pG, int pB);
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_800190D4);

/// @brief Creates a 2D sprite
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001919C);

void func_80019300(void);
/// @brief Creates the collectable icons and counters
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80019300);

void func_80019698(void);
/// @brief Creates Mobys, shadows, Spyro, flame and glows and sparkles
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_80019698);

void func_8001973C(void);
/// @brief Creates the level transition text
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001973C);

void func_8001A050(void);
/// @brief Gamestate 1
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001A050);

void func_8001A40C(void);
/// @brief Gamestate 2 & 3
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001A40C);

void func_8001C694(void);
/// @brief Gamestate 10
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001C694);

void func_8001CA38(void);
/// @brief Gamestate 4 & 5
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001CA38);

void func_8001CFDC(void);
/// @brief Gamestate 8
INCLUDE_ASM("asm/nonmatchings/gamestates/draw", func_8001CFDC);

typedef struct {
  short x, x2;
  short y, y2;
} FAIRYRECT;

extern FAIRYRECT D_8006F350[8];

/// @brief Gamestate 11
void func_8001D718(void) {
  int i;

  Vector3D position;
  Vector3D spacing;

  Moby *curMoby;
  unsigned char textLen;

  // Dunno what this is about
  if (D_800756FC == D_800785D8.m_HudOTStart) {
    // Reduces the polygon space available from 0x1C000 to 0x1BA00
    D_800756FC = (char *)D_800757B0 + 0x1BA00;

    // Then uses that space to store the list of HUD Mobys
    g_HudMobys = D_800756FC;
  }

  if (D_80078D00.unk_0x00 == 1) {
    func_8001860C(D_80078D00.unk_0x10 + D_8006F350[D_80078D00.unk_0x0c].x,
                  D_80078D00.unk_0x10 + D_8006F350[D_80078D00.unk_0x0c].x2,
                  D_8006F350[D_80078D00.unk_0x0c].y,
                  D_8006F350[D_80078D00.unk_0x0c].y2);

    spacing.x = 16;
    spacing.y = 1; // ... Why?
    spacing.z = 0x1400;

    position.z = 0x1100;

    switch (D_80078D00.unk_0x0c) {
    case 0: // HI SPYRO
      position.x = D_80078D00.unk_0x10 + 64;
      position.y = 50;

      func_800181AC("HI SPYRO,", &position, &spacing, 18, 11);
      position.y += 24;

      position.x = D_80078D00.unk_0x10 + 76;
      func_800181AC("SAVE GAME", &position, &spacing, 18, 11);
      position.y += 19;

      // Selected
      if (D_80078D00.unk_0x08 == 0) {
        curMoby = g_HudMobys;
        textLen = sizeof("SAVEGAME") - 1;
      }

      position.x = D_80078D00.unk_0x10 + 76;
      func_800181AC("REPLAY DRAGON", &position, &spacing, 18, 11);
      position.y += 19;

      if (D_80078D00.unk_0x08 == 1) {
        curMoby = g_HudMobys;
        textLen = sizeof("REPLAYDRAGON") - 1;
      }

      position.x = D_80078D00.unk_0x10 + 76;
      // TODO: func_800181AC("CONTINUE", &position, &spacing, 18, 11);
      func_800181AC(D_80010B6C, &position, &spacing, 18, 11);

      if (D_80078D00.unk_0x08 == 2) {
        curMoby = g_HudMobys;
        textLen = sizeof("CONTINUE") - 1;
      }

      // You're going to be seeing a lot of this
      for (i = 0; i < textLen; i++) {
        (curMoby++)->m_Rotation.z =
            COSINE_8(((D_80078D00.unk_0x04 * 4) + (i * 12)) & 0xFF) * 3 >> 9;
      }
      break;
    case 1: // NO SAVE FILE
      position.y = 50;
      position.x = D_80078D00.unk_0x10 + 82;
      func_800181AC("NO SAVE FILE", &position, &spacing, 18, 11);

      position.y += 26;

      curMoby = g_HudMobys;

      for (i = 0; i < (int)sizeof("NOSAVEFILE") - 1; i++) {
        (curMoby++)->m_Rotation.z =
            COSINE_8(((D_80078D00.unk_0x04 * 4) + (i * 12)) & 0xFF) * 3 >> 9;
      }

      spacing.x = 14;
      spacing.y = 1;
      spacing.z = 0x1600;
      position.z = 0x1400;

      position.x = D_80078D00.unk_0x10 + 45;
      func_800181AC("PLEASE RESTART WITH", &position, &spacing, 16, 11);
      position.y += 17;

      position.x = D_80078D00.unk_0x10 + 67;
      func_800181AC("A MEMORY CARD TO", &position, &spacing, 16, 11);
      position.y += 17;

      position.x = D_80078D00.unk_0x10 + 56;
      func_800181AC("ENABLE GAME SAVES.", &position, &spacing, 16, 11);

      break;
    case 2: // SAVING...
      position.y = 82;
      position.x = D_80078D00.unk_0x10 + 106;
      func_800181AC("SAVING...", &position, &spacing, 18, 11);
      curMoby = g_HudMobys;

      for (i = 0; i < (int)sizeof("SAVING...") - 1; i++) {
        (curMoby++)->m_Rotation.z =
            COSINE_8(((D_80078D00.unk_0x04 * 4) + (i * 12)) & 0xFF) * 3 >> 9;
      }
      break;
    case 3: // NO MEMORY CARD
    case 4: // NO SAVE FILE
      position.y = 50;

      if (D_80078D00.unk_0x0c == 3) {
        position.x = D_80078D00.unk_0x10 + 66;
        func_800181AC("NO MEMORY CARD", &position, &spacing, 18, 11);
        textLen = sizeof("NOMEMORYCARD") - 1;
      } else {
        position.x = D_80078D00.unk_0x10 + 84;
        func_800181AC("NO SAVE FILE", &position, &spacing, 18, 11);
        textLen = sizeof("NOSAVEFILE") - 1;
      }

      curMoby = g_HudMobys;
      position.y += 26;

      for (i = 0; i < textLen; i++) {
        (curMoby++)->m_Rotation.z =
            COSINE_8(((D_80078D00.unk_0x04 * 4) + (i * 12)) & 0xFF) * 3 >> 9;
      }

      spacing.x = 14;
      spacing.y = 1;
      spacing.z = 0x1600;

      position.x = D_80078D00.unk_0x10 + 59;
      position.z = 0x1400;

      func_800181AC("PLEASE INSERT THE", &position, &spacing, 16, 11);
      position.y += 17;

      position.x = D_80078D00.unk_0x10 + 67;
      func_800181AC("MEMORY CARD WITH", &position, &spacing, 16, 11);
      position.y += 17;

      position.x = D_80078D00.unk_0x10 + 45;
      func_800181AC("THIS GAME SAVE FILE", &position, &spacing, 16, 11);

      break;
    case 5: // SAVE ERROR
      position.y = 50;
      position.x = D_80078D00.unk_0x10 + 94;
      func_800181AC("SAVE ERROR", &position, &spacing, 18, 11);
      position.y += 26;

      curMoby = g_HudMobys;

      for (i = 0; i < (int)sizeof("SAVEERROR") - 1; i++) {
        (curMoby++)->m_Rotation.z =
            COSINE_8(((D_80078D00.unk_0x04 * 4) + (i * 12)) & 0xFF) * 3 >> 9;
      }

      spacing.x = 14;
      spacing.y = 1;
      spacing.z = 0x1600;
      position.z = 0x1400;

      position.x = D_80078D00.unk_0x10 + 59;
      func_800181AC("PLEASE CHECK THAT", &position, &spacing, 16, 11);
      position.y += 17;

      position.x = D_80078D00.unk_0x10 + 73;
      func_800181AC("THE MEMORY CARD", &position, &spacing, 16, 11);
      position.y += 17;

      position.x = D_80078D00.unk_0x10 + 54;
      func_800181AC("IS STILL IN PLACE.", &position, &spacing, 16, 11);
      break;
    case 6: // SAVE FAILED
      position.y = 53;
      position.x = D_80078D00.unk_0x10 + 86;
      func_800181AC("SAVE FAILED", &position, &spacing, 18, 11);
      position.y += 40;

      position.x = D_80078D00.unk_0x10 + 135;
      // TODO: func_800181AC("RETRY", &position, &spacing, 18, 11);
      func_800181AC(D_80075620, &position, &spacing, 18, 11);
      position.y += 19;

      // Selected
      if (D_80078D00.unk_0x08 == 0) {
        curMoby = g_HudMobys;
        textLen = sizeof("RETRY") - 1;
      }

      position.x = D_80078D00.unk_0x10 + 135;
      // TODO: func_800181AC("ABORT", &position, &spacing, 18, 11);
      func_800181AC(D_80075628, &position, &spacing, 18, 11);

      // Selected
      if (D_80078D00.unk_0x08 == 1) {
        curMoby = g_HudMobys;
        textLen = sizeof("ABORT") - 1;
      }

      for (i = 0; i < textLen; i++) {
        (curMoby++)->m_Rotation.z =
            COSINE_8(((D_80078D00.unk_0x04 * 4) + (i * 12)) & 0xFF) * 3 >> 9;
      }

      break;
    case 7: // GAME SAVED
      position.y = 82;
      position.x = D_80078D00.unk_0x10 + 94;
      func_800181AC("GAME SAVED", &position, &spacing, 18, 11);

      curMoby = g_HudMobys;

      for (i = 0; i < (int)sizeof("GAMESAVED") - 1; i++) {
        (curMoby++)->m_Rotation.z =
            COSINE_8(((D_80078D00.unk_0x04 * 4) + (i * 12)) & 0xFF) * 3 >> 9;
      }
      break;
    }

    if (D_80078D00.unk_0x0c > 1) {
      // Show the used slot number
      spacing.x = 13;
      spacing.y = 1;
      spacing.z = 0x1a00;

      position.y = 29;
      position.z = 0x1600;

      if (D_80078D00.unk_0x18 == 0) {
        position.x = D_80078D00.unk_0x10 + 48;
        // TODO: func_800181AC("SLOT 1", &position, &spacing, 14, 11);
        func_800181AC(D_80075630, &position, &spacing, 14, 11);
      } else {
        position.x = 230; // SKELETON: Not adding the x offset now?
        // TODO: func_800181AC("SLOT 2", &position, &spacing, 14, 11);
        func_800181AC(D_80075638, &position, &spacing, 14, 11);
      }
    }
  }

  func_800521C0();
  func_80019698();

  if (D_80078D00.unk_0x00 == 1) {
    g_SonyImage.m_ShadedMobys[0] = nullptr;
    func_80018880(); // Copy HUD Mobys to Shaded
    func_80022A2C(); // Draw Shaded Mobys
  }

  func_8002B9CC();
  func_80050BD0();
  func_800573C8();
  func_80018F30();

  DrawSync(0);

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

/// @brief Gamestate 12, balloon transition and balloonist talk
void func_8001E24C(void) {
  Moby *curMoby;
  int rotOff;
  int color;

  Vector3D position;
  Vector3D spacing;
  char buf[64];

  if (D_800777E8.m_State >= 4) {

    if (D_800777E8.m_State < 6) {
      Moby **mobyQueue = (void *)g_SonyImage.m_Buf;

      *(mobyQueue++) = D_800777E8.m_BalloonMoby;
      *(mobyQueue++) = (void *)0;

      if (D_800777E8.m_Homeworld < 5) {
        // Minus one is due to the homeworlds starting at 10
        int homeworld = g_NextLevelId / 10;
        sprintf(buf, "ENTERING %s WORLD", homeworldNameTable[homeworld - 1]);
      } else if (D_800777E8.m_Homeworld == 5) {
        // Exception for Gnasty's World so it doesn't display
        // GNASTY'S WORLD WORLD (like in July)
        int homeworld = g_NextLevelId / 10;
        sprintf(buf, "ENTERING %s", homeworldNameTable[homeworld - 1]);
      } else {
        int homeworld = g_NextLevelId / 10;
        int level = g_NextLevelId % 10;
        sprintf(buf, "ENTERING %s", D_8006F7F0[level + ((homeworld - 1) * 6)]);
      }

      // sprintf(buf, fmt, levelName);
      position.x = 256 - ((strlen(buf) - 1) * 7);
      position.y = 200;
      position.z = 0x1400;

      spacing.x = 14;
      spacing.y = 1;
      spacing.z = 0x1600;

      curMoby = g_HudMobys;

      func_800181AC(buf, &position, &spacing, 16, 2);

      rotOff = 0;
      while ((int)(--curMoby) >= (int)g_HudMobys) {
        curMoby->m_Rotation.z =
            COSINE_8(((D_800777E8.unk_0x04 * 2) + rotOff) & 0xFF) >> 7;
        rotOff += 12;
      }

      func_8001F158(); // Prepare Moby draw
      Memset(g_SonyImage.m_Buf, 0, 0x900);
      func_8001F798(); // Draw Mobys

      g_SonyImage.m_ShadedMobys[0] = nullptr;
      func_80018880(); // Copy HUD Mobys to Shaded
      func_80022A2C(); // Draw Shaded Mobys
      func_80023AC4(); // Draw Spyro

      if (D_800777E8.m_State < 6) {
        D_800757D4 = 0x401010;

        if (D_800777E8.m_State == 4) {
          D_8007575C = D_800777E8.unk_0x04 * 16;
        } else {
          D_8007575C = (0x100 - D_800777E8.unk_0x04) * 16;
        }

        if (D_8007575C < 0)
          D_8007575C = 0;
        if (D_8007575C > 4096)
          D_8007575C = 4096;

        color = ColorLerp(*(int *)&g_Cyclorama.m_BackgroundColor, D_800757D4,
                          D_8007575C);

        setRGB0(&g_DB[0].m_DrawEnv, ((Color *)&color)->r, ((Color *)&color)->g,
                ((Color *)&color)->b);
        setRGB0(&g_DB[1].m_DrawEnv, ((Color *)&color)->r, ((Color *)&color)->g,
                ((Color *)&color)->b);

        if (D_8007575C < 4096) {
          func_8004F000();
        }
      }
    } else {
      D_800758D8();
    }
  } else {
    D_800758D8();
  }

  func_80018F30();

  DrawSync(0);

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
      if (g_VisitedFlags.m_Levels[0]) {
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

  g_SonyImage.m_ShadedMobys[0] = nullptr;
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
    } else if (g_Gamestate == GS_EntranceAnimation) {
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