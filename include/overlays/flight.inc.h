#include "camera.h"
#include "buffers.h"
#include "gamepad.h"
#include "graphics.h"
#include "hud.h"
#include "math.h"
#include "moby_helpers.h"
#include "overlay_pointers.h"
#include "sony_image.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"


extern struct {
  int post;
  int pre;
} D_80075950;

// Used in the pause menu as well
extern int D_80075720; // Selected menu item index
extern int D_80075744; // The index of the current page of the inventory screen
extern int D_800757CC; // Transition progress between inventory pages.


extern int D_8007569C; // Flight Results Screen state 
extern int D_800758F4; // Flight Elapsed Time
extern int D_80075900; // Flight Pause Menu Quit related?
extern int D_80075908; // Flight Remaining Time
extern int D_8006E920[6][5]; // Max Gems Per Flight Collectable
extern u_char D_8006E998[12]; // Post Flight Treasure Chest Gem Classes
extern u_short g_GrayscalePalette[32]; // 32 colors
// look into defining
extern char* D_8006E8C0[6][4];


void NAME_OVERLAY_FUNCTION(Flight1)(void) {
  if (g_Gamestate != GS_FlightResults) {
    g_Gamestate = GS_FlightResults;
    D_80075720 = 0;
    D_8007568C = 0;
    D_800758B8 = 0;
    D_80075744 = 0;
    D_800757CC = 0;
    D_8007569C = 0;
    D_800758F4 *= 10;
    if (!g_FlightCourseRecords[g_Homeworld] &&
      (g_FlightObjectiveCounters[0] +
       g_FlightObjectiveCounters[1] +
       g_FlightObjectiveCounters[2] +
       g_FlightObjectiveCounters[3] == 32)) {
      g_FlightCourseRecords[g_Homeworld] = D_800758F4;
    }
  }
}

void NAME_OVERLAY_FUNCTION(Flight2)(int pUnk) {
  RECT rc;
  int i;

  if (pUnk) {
    setRECT(&rc, 512, 0, 256, 225);
    LoadImage(&rc, g_Buffers.m_HudOTStart - 0x1C200);
    DrawSync(0);
  }
  g_Gamestate = GS_Playing;
  SpecularReset();
  for (i = 0; i < 4; i++) {
    
    if (g_FlightObjectiveCounters[i] == 8 && !g_FlightCollected[g_Homeworld][i]) {
      g_LevelGemCount[g_LevelIndex] += D_8006E920[g_Homeworld][i];
      g_GemTotal += D_8006E920[g_Homeworld][i];
      g_NGemsSinceLevelEntry += 12;
      g_FlightCollected[g_Homeworld][i] = 1;
    }
  }

  if ((g_FlightObjectiveCounters[0] +
     g_FlightObjectiveCounters[1] +
     g_FlightObjectiveCounters[2] +
     g_FlightObjectiveCounters[3]) == 32) {
    if (!g_FlightCollected[g_Homeworld][4]) {
      g_LevelGemCount[g_LevelIndex] += D_8006E920[g_Homeworld][4];
      g_GemTotal += D_8006E920[g_Homeworld][4];
      g_NGemsSinceLevelEntry += 12;
      g_FlightCollected[g_Homeworld][4] = 1;
    }
    // If no record was set, or we beat the record
    if (!g_FlightCourseRecords[g_Homeworld] || D_800758F4 < g_FlightCourseRecords[g_Homeworld]) {
      
        g_FlightCourseRecords[g_Homeworld] = D_800758F4;
    }
  }
  // Set gem types to display during level transition chest anim
  for (i = 0; i < g_NGemsSinceLevelEntry; i++) {
    g_RecentGemsCollected[i & 31] = D_8006E998[i % 12];
  }
  g_Spyro.m_walkingState = 0;
  if (g_Camera.m_State == 0x8000000E) {
    g_Camera.unk_0xC0 = D_8006C588[g_Spyro.m_State];
  }
}

void NAME_OVERLAY_FUNCTION(Flight3)(void) {

  int i;

  if (D_8007568C == 0) {
    func_80056B28(0);
  }
  g_Hud.unk_0x3c -= 4;
  g_Hud.unk_0x3c &= 0xFF;
  
  SpecularUpdate(3);
  D_8007568C++;
  D_800757CC++;
   
  if (D_800757CC >= 5) {
    if (D_80075744 < 9) {
      D_80075744++;
    }
    D_800757CC = 0;
  }
  for (i = 0; i < 4; i++) {
    g_Hud.m_Mobys[i].m_Rotation.z += 8;
  }

  if (D_80075744 >= 9) {
    if (g_Pad.m_Down & (PAD_UP | PAD_DOWN)) {
      D_8007568C = 0;
      D_80075720 = 1 - D_80075720;
      PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
    }
    if (g_Pad.m_Down & (PAD_CROSS | PAD_START)) {
      if ((D_80075744 >= 100) || (
        g_FlightObjectiveCounters[0] +
        g_FlightObjectiveCounters[1] +
        g_FlightObjectiveCounters[2] +
        g_FlightObjectiveCounters[3] < 32 && !g_FlightCourseRecords[g_Homeworld])) {
        switch (D_80075720) {
          case 0:
            (*D_800757A8)(1);
            func_800144C8();
            break;
          case 1:
            (*D_800757A8)(0);
            func_8002C618();
            break;
        }
        PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
      } else {
        D_80075744 = 100;
        PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
      }
    }
  } else if (g_Pad.m_Down & (PAD_CROSS | PAD_START)) {
    D_80075744 = 9;
    D_800757CC = 0;
    PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
  }
}


int NAME_OVERLAY_FUNCTION(Flight4)(int pTimer, Vector3D* pPos, int pColor) {
  int centisecs;
  int mins;
  int secs;
  int len;
  char text[16];

  if (pTimer < 0) {
    pPos->x -= 54;
    pPos->y -= 5;
    func_80017FE4("......", pPos, 18, pColor);
    return 6;
  } else {
    mins = pTimer / 36000;
    secs = (pTimer / 600) % 60;
    centisecs = (pTimer / 6) % 100;
    if (mins != 0) {
      sprintf(text, "%d %02d.%02d", mins, secs, centisecs);
    } else {
      sprintf(text, "%d.%02d", secs, centisecs);
    }
    len = strlen(text);
    pPos->x -= len * 9;
    func_80017FE4(text, pPos, 18, pColor);
    if (mins != 0) {
      pPos->x -= 108;
      pPos->y += 1;
      pPos->z = pPos->z * 3 >> 1;
      func_80017FE4(".", pPos, 18, pColor);
      pPos->x -= 18;
      pPos->y -= 8;
      func_80017FE4(".", pPos, 18, pColor);
      len++;
    }
    return len;
  }
}

void NAME_OVERLAY_FUNCTION(Flight5)(void) {

  
  POLY_FT4* ft4;
  LINE_F2* l2;
  
  int i;
  
  int isCompleted;
  int sfx_idx;
  int earnedGems;
  int mobyCount;
  
  Moby* mobys;
  Moby** mobyBuf;
  
  RECT rcStore;
  char text[32];
  Vector3D vec;
  
  if (D_800758B8 == 0) {
    func_800521C0();
    func_80019698();
    func_800573C8();
    func_80050BD0();
    func_8002B9CC();
    DrawSync(0);
    VSync(0);
    PutDispEnv(&g_CurDB->m_DispEnv);
    PutDrawEnv(&g_CurDB->m_DrawEnv);
    DrawOTag(func_80016784(0x800));
    DrawSync(0);
    VSync(0);
    PutDispEnv(&g_CurDB->m_DispEnv);
    setRECT(&rcStore, 512, 0, 256, 225);
    StoreImage(&rcStore, g_Buffers.m_HudOTStart - 0x1C200);
    for (i = 0; i < 4; i++) {
      setRECT(&rcStore, i * 128, g_CurDB != g_DB ? 248 : 8, 128, 224);
      StoreImage(&rcStore, g_Buffers.m_LowerPolyBuffer);
      DrawSync(0);
      func_80017E98(g_Buffers.m_LowerPolyBuffer, 0x7000);
      setRECT(&rcStore, 512 + i * 64, 0, 64, 224);
      LoadImage(&rcStore, g_Buffers.m_LowerPolyBuffer);
    }
    setRECT(&rcStore, 512, 224, 32, 1);
    LoadImage(&rcStore, (u_long*)g_GrayscalePalette);
    DrawSync(0);
    D_80075950.post = VSync(-1);
  } else {
    isCompleted = 0;
    if (g_CurDB == &g_DB[0]) {
      PutDrawEnv(&g_DB[1].m_DrawEnv);
    } else {
      PutDrawEnv(&g_DB[0].m_DrawEnv);
    }
    
    D_800758B0 = 0;
    D_800757B0 = g_Buffers.m_LowerPolyBuffer;
    D_80075780 = g_Buffers.m_LowerPolyBuffer + 0x1C000;
    g_HudMobys = D_800756FC = g_Buffers.m_HudOTStart - 0x1C200;
    for (i = 0; i < 4; i++) {
      ft4 = D_800757B0;
      ft4->tag = 0x9000000;
      ft4->code = 0x2C;
      setRGB0(ft4, 0x4C, 0x80, 0x40);
      setXY4(ft4, i * 128, 8, ft4->x0 + 128, ft4->y0, ft4->x0,
             ft4->y0 + 224 - 1, ft4->x0 + 128, ft4->y0 + 224 - 1);
      setUV4(ft4, 0, 0, ft4->u0 + 128, ft4->v0, ft4->u0, ft4->v0 + 224 - 1,
             ft4->u0 + 128, ft4->v0 + 224 - 1);
      ft4->clut = getClut(512, 224);
      ft4->tpage = getTPage(1, 0, 512, 0) + i;
      func_800168DC(ft4);
      D_800757B0 = ft4 + 1;
    }
    l2 = D_800757B0;
    l2->tag = 0x3000000;
    l2->code = 0x40;
    setXY2(l2, 0, 231, 512, 231);
    setRGB0(l2, 0, 0, 0);
    func_800168DC(l2);
    D_800757B0 = l2 + 1;
    if (D_80075744 < 100) {
      earnedGems = 0;
      if (g_FlightObjectiveCounters[0] +
        g_FlightObjectiveCounters[1] +
        g_FlightObjectiveCounters[2] +
        g_FlightObjectiveCounters[3] == 32)
      {
        strcpy(text, "COMPLETED");
        isCompleted = 1;
      } else if (D_80075900 != 0) {
        strcpy(text, "QUIT");
      } else if (D_80075908 < 0) {
        strcpy(text, "TIME IS UP");
      } else {
        strcpy(text, "CRASHED");
      }
      setXYZ(&vec, 268 - strlen(text) * 12, 30, 0xC00);
      func_80017FE4(text, &vec, 24, 11);
      Memset(--g_HudMobys, 0, 88);
      g_HudMobys->m_Class = 471;
      g_HudMobys->m_Position.x = 460;
      g_HudMobys->m_Position.y = 40;
      g_HudMobys->m_Position.z = 0xC00;
      g_HudMobys->m_Rotation.y = COSINE_8(g_Hud.unk_0x3c) >> 9;
      g_HudMobys->m_Rotation.z = g_Hud.unk_0x3c;
      g_HudMobys->m_DepthOffset = 127;
      g_HudMobys->m_SpecularMetalType = 11;
      g_HudMobys->m_RenderRadius = 255;
      func_8001844C(60, 46, 452, 46);
      
      setXYZ(&vec, 100, 60, 0x1100);
      func_80017FE4(D_8006E8C0[g_Homeworld][0], &vec, 18, 11);
      if (D_80075744 > 0) {
        sprintf(text, "%d/8", g_FlightObjectiveCounters[0]);
        setXYZ(&vec, 320, 60, 0x1100);
        func_80017FE4(text, &vec, 18, 11);
      }
      if (D_80075744 >= 2) {
        if (g_FlightObjectiveCounters[0] == 8) {
          if (g_FlightCollected[g_Homeworld][0]) {
            sprintf(text, "^");
          } else {
            sprintf(text, "%d", D_8006E920[g_Homeworld][0]);
            earnedGems += D_8006E920[g_Homeworld][0];
          }
          sfx_idx = 0;
        } else {
          sprintf(text, "0");
          sfx_idx = 33;
        }
        setXYZ(&vec, 480 - (strlen(text) * 18), 60, 0x1100);
        func_80017FE4(text, &vec, 18, 11);
        if (D_8007569C < 2) {
          PlaySound(((char*)g_Spu.m_SoundTable)[sfx_idx], (Moby*)&g_Spyro.m_Position, 0x10, 0);
          D_8007569C = 2;
        }
      }

      setXYZ(&vec, 100, 80, 0x1100);
      func_80017FE4(D_8006E8C0[g_Homeworld][1], &vec, 18, 11);
      if (D_80075744 >= 3) {
        sprintf(text, "%d/8", g_FlightObjectiveCounters[1]);
        setXYZ(&vec, 320, 80, 0x1100);
        func_80017FE4(text, &vec, 18, 11);
      }
      if (D_80075744 >= 4) {
        if (g_FlightObjectiveCounters[1] == 8) {
          if (g_FlightCollected[g_Homeworld][1]) {
            sprintf(text, "^");
          } else {
            sprintf(text, "%d", D_8006E920[g_Homeworld][1]);
            earnedGems += D_8006E920[g_Homeworld][1];
          }
          sfx_idx = 0;
        } else {
          sprintf(text, "0");
          sfx_idx = 33;
        }
        setXYZ(&vec, 480 - (strlen(text) * 18), 80, 0x1100);
        func_80017FE4(text, &vec, 18, 11);
        if (D_8007569C < 4) {
          PlaySound(((char*)g_Spu.m_SoundTable)[sfx_idx], (Moby*)&g_Spyro.m_Position, 0x10, 0);
          D_8007569C = 4;
        }
      }

      setXYZ(&vec, 100, 100, 0x1100);
      func_80017FE4(D_8006E8C0[g_Homeworld][2], &vec, 18, 11);
      if (D_80075744 >= 5) {
        sprintf(text, "%d/8", g_FlightObjectiveCounters[2]);
        setXYZ(&vec, 320, 100, 0x1100);
        func_80017FE4(text, &vec, 18, 11);
      }
      if (D_80075744 >= 6) {
        if (g_FlightObjectiveCounters[2] == 8) {
          if (g_FlightCollected[g_Homeworld][2]) {
            sprintf(text, "^");
          } else {
            sprintf(text, "%d", D_8006E920[g_Homeworld][2]);
            earnedGems += D_8006E920[g_Homeworld][2];
          }
          sfx_idx = 0;
        } else {
          sprintf(text, "0");
          sfx_idx = 33;
        }
        setXYZ(&vec, 480 - (strlen(text) * 18), 100, 0x1100);
        func_80017FE4(text, &vec, 18, 11);
        if (D_8007569C < 6) {
          PlaySound(((char*)g_Spu.m_SoundTable)[sfx_idx], (Moby*)&g_Spyro.m_Position, 0x10, 0);
          D_8007569C = 6;
        }
      }

      setXYZ(&vec, 100, 120, 0x1100);
      func_80017FE4(D_8006E8C0[g_Homeworld][3], &vec, 18, 11);
      if (D_80075744 >= 7) {
        sprintf(text, "%d/8", g_FlightObjectiveCounters[3]);
        setXYZ(&vec, 320, 120, 0x1100);
        func_80017FE4(text, &vec, 18, 11);
      }
      if (D_80075744 >= 8) {
        if (g_FlightObjectiveCounters[3] == 8) {
          if (g_FlightCollected[g_Homeworld][3]) {
            sprintf(text, "^");
          } else {
            sprintf(text, "%d", D_8006E920[g_Homeworld][3]);
            earnedGems += D_8006E920[g_Homeworld][3];
          }
          sfx_idx = 0;
        } else {
          sprintf(text, "0");
          sfx_idx = 33;
        }
        setXYZ(&vec, 480 - (strlen(text) * 18), 120, 0x1100);
        func_80017FE4(text, &vec, 18, 11);
        if (D_8007569C < 8) {
          PlaySound(((char*)g_Spu.m_SoundTable)[sfx_idx], (Moby*)&g_Spyro.m_Position, 0x10, 0);
          D_8007569C = 8;
        }
      }

      setXYZ(&vec, 100, 140, 0x1100);
      func_80017FE4("ALL IN ONE", &vec, 18, 11);
      if (D_80075744 >= 9) {
        if (g_FlightObjectiveCounters[0] +
          g_FlightObjectiveCounters[1] +
          g_FlightObjectiveCounters[2] +
          g_FlightObjectiveCounters[3] == 32)
        {
          if (g_FlightCollected[g_Homeworld][4]) {
            sprintf(text, "^");
          } else {
            sprintf(text, "%d", D_8006E920[g_Homeworld][4]);
            earnedGems += D_8006E920[g_Homeworld][4];
          }
          sfx_idx = 0;
        } else {
          sprintf(text, "0");
          sfx_idx = 33;
        }
        setXYZ(&vec, 480 - (strlen(text) * 18), 140, 0x1100);
        func_80017FE4(text, &vec, 18, 11);
        if (D_8007569C < 9) {
          PlaySound(((char*)g_Spu.m_SoundTable)[sfx_idx], (Moby*)&g_Spyro.m_Position, 0x10, 0);
          D_8007569C = 9;
        }
      }
      func_8001844C(416, 150, 470, 150);
      setXYZ(&vec, 100, 160, 0x1100);
      func_80017FE4("TOTAL", &vec, 18, 11);
      sprintf(text, "%d", earnedGems);
      setXYZ(&vec, 480 - (strlen(text) * 18), 160, 0x1100);
      func_80017FE4(text, &vec, 18, 11);
      func_8001844C(60, 176, 452, 176);
      if (D_80075744 >= 9) {
        if ((isCompleted != 0) || (g_FlightCourseRecords[g_Homeworld] != 0)) {
          setXYZ(&vec, 80, 210, 0x1100);
          func_80017FE4("PRESS   TO CONTINUE", &vec, 18, 11);
          vec.x = 188;
          func_80017FE4("X", &vec, 18, 10);
        } else {
          setXYZ(&vec, 140, 190, 0x1100);
          func_80017FE4("TRY AGAIN?", &vec, 18, 11);
          setXYZ(&vec, 348, 190, 0x1100);
          func_80017FE4("YES", &vec, 18,
                  (D_80075720 == 0 &&
                   D_8007568C % 16 < 6)
                  * 2
                  + 10);
          mobys = g_HudMobys;
          mobyCount = 3;
          setXYZ(&vec, 348, 210, 0x1100);
          func_80017FE4("NO", &vec, 18,
                  (D_80075720 == 1 &&
                   D_8007568C % 16 < 6)
                  * 2
                  + 10);
          if (D_80075720 != 0) {
            mobys = g_HudMobys;
            mobyCount = 2;
          }
          for (i = 0; i < mobyCount; i++) {
            mobys->m_Rotation.z = COSINE_8((D_800758B8 * 8 + i * 12) & 0xFF) * 3 >> 9;
            mobys++;
          }
        }
      }
      mobyBuf = g_SonyImage.m_ShadedMobys;
      for (i = 0; i < 4; ++i) {
        *mobyBuf++ = g_Hud.m_Mobys +  i;
      }
      *mobyBuf = nullptr;

    } else {
      setXYZ(&vec, 136, 40, 0xC00);
      func_80017FE4("TIME ATTACK", &vec, 24, 11);
      func_8001844C(60, 61, 452, 61);
      setXYZ(&vec, 320, 80, 0x1100);
      func_80017FE4("BEST TIME", &vec, 18, 11);
      setXYZ(&vec, 401, 100, 0x1100);
      D_800758C4(g_FlightCourseRecords[g_Homeworld], &vec, 11);
      setXYZ(&vec, 56, 80, 0x1100);
      func_80017FE4("YOUR TIME", &vec, 18, 11);
      setXYZ(&vec, 137, 100, 0x1100);
      if (g_FlightCourseRecords[g_Homeworld] >= D_800758F4) {
        // strange var to use, needed for correct register usage
        i = 8;
      } else {
        i = 11;
      } 
      if (g_FlightObjectiveCounters[0] +
        g_FlightObjectiveCounters[1] +
        g_FlightObjectiveCounters[2] +
        g_FlightObjectiveCounters[3] == 32)
      {
        mobyCount = (*D_800758C4)(D_800758F4, &vec, i);
        mobys = g_HudMobys;
        for (i = 0; i < mobyCount; i++) {
          mobys->m_Rotation.z = COSINE_8((D_800758B8 * 8 + i * 12) & 0xFF) * 3 >> 9;
          mobys++;
        }
      } else {
        (*D_800758C4)(-1, &vec, 11);
      }
      if (g_FlightObjectiveCounters[0] +
        g_FlightObjectiveCounters[1] +
        g_FlightObjectiveCounters[2] +
        g_FlightObjectiveCounters[3] < 32)
      {
        if (D_80075900 != 0) {
          strcpy(text, "QUIT");
        } else {
          strcpy(text, "CRASHED");
        }
        mobyCount = strlen(text);
        setXYZ(&vec, 268 - mobyCount * 12, 150, 0xC00);
        func_80017FE4(text, &vec, 24, 11);
        mobys = g_HudMobys;
        for (i = 0; i < mobyCount; i++) {
          mobys->m_Rotation.z = COSINE_8((D_800758B8 * 8 + i * 12) & 0xFF) * 3 >> 9;
          mobys++;
        }

      } else if (g_FlightCourseRecords[g_Homeworld] >= D_800758F4) {
        setXYZ(&vec, 148, 150, 0xC00);
        func_80017FE4("NEW RECORD", &vec, 24, 8);

        mobys = g_HudMobys;
        mobyCount = 10;
        for (i = 0; i < mobyCount; i++) {
          mobys->m_Rotation.z = COSINE_8((D_800758B8 * 8 + i * 12) & 0xFF) * 3 >> 9;
          mobys++;
        }
      }
      func_8001844C(60, 171, 452, 171);
      setXYZ(&vec, 140, 190, 0x1100);

      // account for different padding garbage of last string
      #if LEVEL == 15
        #define GARBAGE_FIX 0x00, 0x00, 0x00
      #elif LEVEL == 25
        #define GARBAGE_FIX 0x00, 0x2A, 0x2A
      #elif LEVEL == 35
        #define GARBAGE_FIX 0x00, 0x0D, 0x0A
      #elif LEVEL == 45
        #define GARBAGE_FIX 0x00, 0x74, 0x20
      #elif LEVEL == 55
        #define GARBAGE_FIX 0x00, 0x00, 0x00
      #endif

      func_80017FE4(
        (char*)(char[])
        {'T','R','Y',' ','A','G','A','I','N', GARBAGE_FIX},
        &vec, 18, 11);

      #undef GARBAGE_FIX

      setXYZ(&vec, 340, 190, 0x1100);
      func_80017FE4("YES", &vec, 18,
                  (D_80075720 == 0 &&
                   D_8007568C % 16 < 6)
                  * 2
                  + 10);
      setXYZ(&vec, 340, 210, 0x1100);
      mobyCount = 3;
      mobys = g_HudMobys;
      func_80017FE4("NO", &vec, 18,
                  (D_80075720 == 1 &&
                   D_8007568C % 16 < 6)
                  * 2
                  + 10);
      if (D_80075720 != 0) {
        mobys = g_HudMobys;
        mobyCount = 2;
      }
      for (i = 0; i < mobyCount; i++) {
        mobys->m_Rotation.z = COSINE_8((D_800758B8 * 8 + i * 12) & 0xFF) * 3 >> 9;
        mobys++;
      }
      g_SonyImage.m_ShadedMobys[0] = 0;
    }
  }

  if (D_800758B8 > 0) {
    func_80018880();
    Memset(g_SonyImage.u.m_Buf, 0, 0x900);
    func_80022A2C();
  }

  DrawOTag(func_80016784(0));
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
  D_800758B8++;
}