#include "hud.h"
#include "42CC4.h"
#include "camera.h"
#include "common.h"
#include "math.h"
#include "memory.h"
#include "overlay_pointers.h"
#include "variables.h"

void HudPrint(int pIdx, int pLen, int pValue, int pArg4) {
  char buf[8];
  char *end = buf;
  int i;

  // break the digits apart backwards ...
  while (pValue != 0) {
    *end = pValue % 10;
    pValue = pValue / 10;
    ++end;
  }
  if (end == buf) {
    buf[0] = 0;
    end = buf + 1;
  }

  // build out the corresponding digit mobys
  for (i = 0; i < pLen; ++i) {
    if (end != buf) {
      --end;
      if (pArg4 == 0) {
        g_Hud.m_Mobys[pIdx + i].m_Substate = *end;
      } else {
        g_Hud.m_Mobys[pIdx + i].m_Class = (*end & 0xFF) + MOBYCLASS_NUMBER_0;
        g_Hud.m_Mobys[pIdx + i].m_RenderRadius = 0xFF;
      }
    } else {
      if (pArg4 != 0) {
        g_Hud.m_Mobys[pIdx + i].m_RenderRadius = 0;
      }
    }
  }
}

void HudMoveMoby(int pIdx, int pLen, int pYOffset) {
  int i;
  for (i = 0; i < pLen; ++i) {
    g_Hud.m_Mobys[pIdx + i].m_Position.y =
        g_HudMobyTargetPos[pIdx + i].y + pYOffset;
  }
}

void HudMoveEgg(int pIdx, int pLen, int pYOffset) {
  int i;
  for (i = 0; i < pLen; ++i) {
    g_Hud.m_SpriteRect[pIdx + i].y = g_HudEggTargetRect[pIdx + i].y + pYOffset;
  }
}

void HudMobyRotate(int pIdx, int pLen, int pZRot) {
  int i;
  for (i = 0; i < pLen; ++i) {
    if (g_Hud.m_Mobys[pIdx + i].m_Rotation.z != 0 ||
        g_Hud.m_Mobys[pIdx + i].m_Substate !=
            g_Hud.m_Mobys[pIdx + i].m_Class - MOBYCLASS_NUMBER_0) {
      g_Hud.m_Mobys[pIdx + i].m_Rotation.z = pZRot;
    }

    if (g_Hud.m_Mobys[pIdx + i].m_Substate != 0xFF && pZRot == 192) {
      g_Hud.m_Mobys[pIdx + i].m_Class =
          (g_Hud.m_Mobys[pIdx + i].m_Substate & 0xFF) + MOBYCLASS_NUMBER_0;
      g_Hud.m_Mobys[pIdx + i].m_RenderRadius = 0xFF;
    }
  }
}

void HudGemUpdate(void) {
  g_Hud.m_GemCount = g_LevelGemCount[D_80075964];
  HudPrint(0, 4, g_Hud.m_GemCount, 1);
  if (g_Hud.m_GemDisplayState == HDS_Opening ||
      g_Hud.m_GemDisplayState == HDS_Open ||
      g_Hud.m_GemDisplayState == HDS_Completed) {
    g_Hud.m_GemDisplayState = HDS_Closing;
    g_Hud.m_GemProgress = 13;
  }
}

void HudReset(int pArg) {
  int i;
  Memset(g_Hud.m_Mobys, 0, sizeof(g_Hud.m_Mobys));
  for (i = 0; i < 12; ++i) {
    func_800529CC(&g_Hud.m_Mobys[i]);
    VecCopy(&g_Hud.m_Mobys[i].m_Position, &g_HudMobyTargetPos[i]);
    g_Hud.m_Mobys[i].m_DepthOffset = 32;
    g_Hud.m_Mobys[i].m_RenderRadius = 0xFF;
    g_Hud.m_Mobys[i].m_Substate = 0xFF;
    g_Hud.m_Mobys[i].m_SpecularMetalType = 11;
  }

  Memset(g_Hud.m_SpriteRect, 0, sizeof(g_Hud.m_SpriteRect));
  for (i = 0; i < 12; ++i) {
    g_Hud.m_SpriteRect[i].x = g_HudEggTargetRect[i].x;
    g_Hud.m_SpriteRect[i].y = g_HudEggTargetRect[i].y;
    g_Hud.m_SpriteRect[i].w = g_HudEggTargetRect[i].w;
    g_Hud.m_SpriteRect[i].h = g_HudEggTargetRect[i].h;
  }

  g_Hud.m_Mobys[4].m_Class = MOBYCLASS_HUD_GEM_CHEST;
  g_Hud.m_Mobys[7].m_Class = MOBYCLASS_HUD_DRAGON;
  g_Hud.m_Mobys[10].m_Class = MOBYCLASS_HUD_SPYRO_HEAD;
  g_Hud.m_Mobys[11].m_Class = MOBYCLASS_HUD_KEY;
  g_Hud.m_Mobys[11].m_Rotation.z = 64;

  g_Hud.m_GemDisplayState = 1;
  g_Hud.m_DragonDisplayState = 1;
  g_Hud.m_LifeDisplayState = 1;
  g_Hud.m_EggDisplayState = 1;
  g_Hud.m_KeyDisplayState = 1;
  g_Hud.m_GemProgress = 0;
  g_Hud.m_DragonProgress = 0;
  g_Hud.m_LifeProgress = 0;
  g_Hud.m_EggProgress = 0;
  g_Hud.m_KeyProgress = 0;
  g_Hud.m_GemSteadyTicks = 0;
  g_Hud.m_DragonSteadyTicks = 0;
  g_Hud.m_LifeSteadyTicks = 0;
  g_Hud.m_EggSteadyTicks = 0;
  g_Hud.m_KeySteadyTicks = 0;

  g_Hud.m_GemCount = g_LevelGemCount[D_80075964];
  g_Hud.m_DragonCount = g_DragonTotal;
  g_Hud.m_LifeCount = D_8007582C;
  g_Hud.m_EggCount = g_EggTotal;
  g_Hud.m_KeyFlag = D_80075830;
  g_Hud.m_LifeOrbCount = D_800758E8;

  HudPrint(0, 4, g_Hud.m_GemCount, 1);
  HudPrint(5, 2, g_Hud.m_DragonCount, 1);
  HudPrint(8, 2, g_Hud.m_LifeCount, 1);
  if (pArg) {
    g_Hud.D_80077FDC = 0;

    for (i = 0; i < D_800758E8; ++i) {
      g_Hud.m_SpriteRect[12 + i].x =
          g_Hud.m_Mobys[10].m_Position.x + g_LifeOrbXYTarget[i].x - 29;
      g_Hud.m_SpriteRect[12 + i].y =
          g_Hud.m_Mobys[10].m_Position.y + g_LifeOrbXYTarget[i].y - 28;
      g_Hud.m_SpriteRect[12 + i].w = 8;
      g_Hud.m_SpriteRect[12 + i].h = 8;
    }
  }
}

inline static uint something_hud(int i) { return (0x6000000 + i * 0x1000000); }

void HudTick(void) {
  int i;
  int j;
  Vector3D vec;

  g_Hud.unk_0x3c = (g_Hud.unk_0x3c - g_DeltaTime) & 0xFF;
  g_Hud.unk_0x40 = (g_Hud.unk_0x40 + 1) % 9;
  g_Hud.m_Mobys[4].m_Rotation.y = COSINE_8(g_Hud.unk_0x3c) >> 9;
  g_Hud.m_Mobys[4].m_Rotation.z = (u_char)g_Hud.unk_0x3c;

  if (g_Hud.m_GemDisplayState == HDS_Hidden) {
    if (g_Hud.m_GemCount != g_LevelGemCount[D_80075964]) {
      g_Hud.m_GemDisplayState = HDS_Opening;
      g_Hud.m_GemProgress = 0;
    }
  } else if (g_Hud.m_GemDisplayState == HDS_Opening) {
    if (g_Hud.m_GemProgress == 13) {
      g_Hud.m_GemDisplayState = HDS_Open;
      g_Hud.m_GemProgress = 0;
      g_Hud.m_GemSteadyTicks = 0;
      if (g_Hud.m_GemCount == g_LevelGemCount[D_80075964]) {
        g_Hud.m_GemSteadyTicks = -40;
      }
    } else {
      HudMoveMoby(0, 5, g_HudOpeningOffsets[g_Hud.m_GemProgress++]);
    }
  } else if (g_Hud.m_GemDisplayState == HDS_Open) {
    if (g_Hud.m_GemCount == g_LevelGemCount[D_80075964] &&
        g_Hud.m_GemProgress == 0) {
      g_Hud.m_GemSteadyTicks++;
      if (g_Hud.m_GemSteadyTicks == 20) {
        g_Hud.m_GemDisplayState = HDS_Closing;
        g_Hud.m_GemProgress = 13;
      }
    } else {
      g_Hud.m_GemSteadyTicks = 0;
      if (g_LevelGemCount[D_80075964] - g_Hud.m_GemCount >= 3 &&
          (g_Hud.m_GemProgress & 0x1F) == 0) {
        g_Hud.m_GemProgress -= 0x20;
      } else {
        g_Hud.m_GemProgress -= 0x10;
      }
      HudPrint(0, 4, g_Hud.m_GemCount + 1, 0);
      HudMobyRotate(0, 4, g_Hud.m_GemProgress);
      if (g_LevelGemCount[D_80075964] - g_Hud.m_GemCount > 200) {
        g_Hud.m_GemCount += 8;
      } else if (g_LevelGemCount[D_80075964] - g_Hud.m_GemCount > 20 ||
                 g_Hud.m_GemProgress == 0xC0) {
        g_Hud.m_GemCount += 1;
      }

      if (g_Hud.m_GemCount == g_TargetGemCounts[D_80075964] &&
          g_Hud.m_GemProgress == 0) {
        g_Hud.m_GemDisplayState = HDS_Completed;
      }
    }
  } else if (g_Hud.m_GemDisplayState == HDS_Closing) {
    if (g_Hud.m_GemCount != g_LevelGemCount[D_80075964]) {
      g_Hud.m_GemDisplayState = HDS_Opening;
    } else if (g_Hud.m_GemProgress == 0) {
      g_Hud.m_GemDisplayState = HDS_Hidden;
    } else {
      HudMoveMoby(0, 5, g_HudClosingOffsets[--g_Hud.m_GemProgress]);
    }
  } else if (g_Hud.m_GemDisplayState == HDS_Completed) {
    g_Hud.m_GemSteadyTicks += g_DeltaTime;
    if (g_Hud.m_GemSteadyTicks >= 240) {
      g_Hud.m_GemDisplayState = HDS_Closing;
      g_Hud.m_GemProgress = 13;
    }
  }

  g_Hud.m_Mobys[7].m_Substate += 8;
  g_Hud.m_Mobys[7].m_Rotation.z =
      COSINE_8(g_Hud.m_Mobys[7].m_Substate & 0xFF) >> 8;
  if (g_Hud.m_DragonDisplayState == HDS_Opening) {
    if (g_Hud.m_DragonProgress == 13) {
      g_Hud.m_DragonDisplayState = HDS_Open;
      g_Hud.m_DragonProgress = 0;
      g_Hud.m_DragonSteadyTicks = -40;
    } else {
      HudMoveMoby(5, 3, g_HudOpeningOffsets[g_Hud.m_DragonProgress++]);
    }
  } else if (g_Hud.m_DragonDisplayState == HDS_Open) {
    g_Hud.m_DragonSteadyTicks++;
    if (g_Hud.m_DragonSteadyTicks == 20) {
      g_Hud.m_DragonDisplayState = HDS_Closing;
      g_Hud.m_DragonProgress = 13;
    }
  } else if (g_Hud.m_DragonDisplayState == HDS_Closing) {
    if (g_Hud.m_DragonProgress == 0) {
      g_Hud.m_DragonDisplayState = HDS_Hidden;
    } else {
      HudMoveMoby(5, 3, g_HudClosingOffsets[--g_Hud.m_DragonProgress]);
    }
  }

  g_Hud.m_Mobys[10].m_Rotation.z = g_Hud.unk_0x3c & 0xFF;
  if (g_Hud.m_LifeDisplayState == HDS_Hidden) {
    if (g_Hud.m_LifeCount != D_8007582C || g_Hud.m_LifeOrbCount != D_800758E8) {
      g_Hud.m_LifeDisplayState = HDS_Opening;
      g_Hud.m_LifeProgress = 0;
    }
  } else if (g_Hud.m_LifeDisplayState == HDS_Opening) {
    if (g_Hud.m_LifeProgress == 13) {
      g_Hud.m_LifeDisplayState = HDS_Open;
      g_Hud.m_LifeProgress = 0;
      g_Hud.m_LifeSteadyTicks = 0;
      if (g_Hud.m_LifeCount == D_8007582C &&
          g_Hud.m_LifeOrbCount == D_800758E8) {
        g_Hud.m_LifeSteadyTicks = -40;
      }
    } else {
      HudMoveMoby(8, 3, g_HudOpeningOffsets[g_Hud.m_LifeProgress++]);
    }
  } else if (g_Hud.m_LifeDisplayState == HDS_Open) {
    if (g_Hud.m_LifeCount == D_8007582C && g_Hud.m_LifeProgress == 0) {
      if (g_Hud.m_LifeOrbCount == D_800758E8) {
        g_Hud.m_LifeSteadyTicks += 1;
        if (g_Hud.m_LifeSteadyTicks == 20) {
          g_Hud.m_LifeDisplayState = HDS_Closing;
          g_Hud.m_LifeProgress = 13;
        }
      } else {
        g_Hud.m_LifeSteadyTicks = 0;
        g_Hud.m_LifeOrbCount = D_800758E8;
      }
    } else {
      g_Hud.m_LifeSteadyTicks = 0;
      g_Hud.m_LifeProgress = g_Hud.m_LifeProgress - 16;
      HudPrint(8, 2, g_Hud.m_LifeCount + 1, 0);
      HudMobyRotate(8, 2, g_Hud.m_LifeProgress);
      if (g_Hud.m_LifeProgress == 0xC0) {
        g_Hud.m_LifeCount += 1;
      }
    }
  } else if (g_Hud.m_LifeDisplayState == HDS_Closing) {
    if (g_Hud.m_LifeCount != D_8007582C || g_Hud.m_LifeOrbCount != D_800758E8) {
      g_Hud.m_LifeDisplayState = HDS_Opening;
      g_Hud.m_LifeOrbCount = D_800758E8;
    } else if (g_Hud.m_LifeProgress == 0) {
      g_Hud.m_LifeDisplayState = HDS_Hidden;
    } else {
      HudMoveMoby(8, 3, g_HudClosingOffsets[--g_Hud.m_LifeProgress]);
    }
  }

  for (i = 0; i < g_Hud.m_LifeOrbCount; ++i) {
    g_Hud.m_SpriteRect[12 + i].x =
        g_Hud.m_Mobys[10].m_Position.x + g_LifeOrbXYTarget[i].x - 29;
    g_Hud.m_SpriteRect[12 + i].y =
        g_Hud.m_Mobys[10].m_Position.y + g_LifeOrbXYTarget[i].y - 28;
    g_Hud.m_SpriteRect[12 + i].w = 8;
    g_Hud.m_SpriteRect[12 + i].h = 8;
  }

  switch (g_Hud.m_EggDisplayState) {
  case HDS_Hidden: {
    if (g_Hud.m_EggCount != g_EggTotal || g_Hud.D_80077FDC != 0) {
      g_Hud.m_EggDisplayState = HDS_Opening;
      g_Hud.m_EggProgress = 0;
    }
    break;
  }
  case HDS_Opening: {
    if (g_Hud.m_EggProgress == 13) {
      g_Hud.m_EggDisplayState = HDS_Open;
      g_Hud.m_EggSteadyTicks = 0;
      if (g_Hud.m_EggCount == g_EggTotal && g_Hud.D_80077FDC == 0) {
        g_Hud.m_EggSteadyTicks = -40;
      }
    } else {
      HudMoveEgg(0, 12, -g_HudOpeningOffsets[g_Hud.m_EggProgress++]);
    }
    break;
  }
  case HDS_Open: {
    if (g_Hud.m_EggCount == g_EggTotal) {
      if (g_Hud.D_80077FDC != 0) {
        g_Hud.m_EggSteadyTicks = 0;
      } else {
        if (g_Hud.m_EggSteadyTicks == 20) {
          g_Hud.m_EggDisplayState = HDS_Closing;
          g_Hud.m_EggProgress = 13;
        }
      }
    } else if (g_Hud.m_EggSteadyTicks == 1) {
      vec.x = g_Hud.m_EggCount * 324 - 2500;
      vec.y = 1008;
      vec.z = 4096;
      (*D_800758E4)(16, 77, &vec, nullptr);
    } else if (g_Hud.m_EggSteadyTicks > 8) {
      g_Hud.m_EggCount += 1;
      g_Hud.m_EggSteadyTicks = 0;
    }
    g_Hud.m_EggSteadyTicks += 1;
    break;
  }
  case HDS_Closing: {
    if (g_Hud.m_EggCount != g_EggTotal || g_Hud.D_80077FDC != 0) {
      g_Hud.m_EggDisplayState = HDS_Opening;
    } else if (g_Hud.m_EggProgress == 0) {
      g_Hud.m_EggDisplayState = HDS_Hidden;
    } else {
      HudMoveEgg(0, 12, -g_HudClosingOffsets[--g_Hud.m_EggProgress]);
    }
    break;
  }
  }

  if (D_80075830 != 1)
    g_Hud.m_KeyFlag = D_80075830;

  switch (g_Hud.m_KeyDisplayState) {
  case HDS_Hidden: {
    if (g_Hud.m_KeyFlag != D_80075830) {
      g_Hud.m_KeyDisplayState = HDS_Opening;
      g_Hud.m_KeyProgress = 0;
    }
    break;
  }
  case HDS_Opening: {
    if (g_Hud.m_KeyProgress == 13) {
      g_Hud.m_KeyDisplayState = HDS_Open;
      g_Hud.m_KeySteadyTicks = 0;
      if (g_Hud.m_KeyFlag == D_80075830) {
        g_Hud.m_KeySteadyTicks = -40;
      }
    } else {
      HudMoveMoby(11, 1, -g_HudOpeningOffsets[g_Hud.m_KeyProgress++]);
    }
    break;
  }
  case HDS_Open: {
    if (g_Hud.m_KeyFlag != D_80075830) {
      if (g_Hud.m_KeySteadyTicks == 0) {
        for (j = 0; j < 6; ++j) {
          (*D_800758E4)(1, 12, &g_Hud.m_Mobys[11].m_Props,
                        (void *)(something_hud(j) + 0x8080));
        }
      } else if (g_Hud.m_KeySteadyTicks > 11) {
        g_Hud.m_Mobys[11].m_Substate = 64;
        g_Hud.m_KeySteadyTicks = 0;
        g_Hud.m_KeyFlag = D_80075830;
      }
    } else if (g_Hud.m_KeySteadyTicks == 20) {
      g_Hud.m_KeyDisplayState = HDS_Closing;
      g_Hud.m_KeyProgress = 13;
    }
    g_Hud.m_KeySteadyTicks += 1;
    break;
  }
  case HDS_Closing: {
    if (g_Hud.m_KeyFlag != D_80075830) {
      g_Hud.m_KeyDisplayState = HDS_Opening;
      g_Hud.m_KeyProgress = 0;
    } else if (g_Hud.m_KeyProgress == 0) {
      g_Hud.m_KeyDisplayState = HDS_Hidden;
    } else {
      HudMoveMoby(11, 1, -g_HudClosingOffsets[--g_Hud.m_KeyProgress]);
    }
    break;
  }
  }

  g_Hud.m_Mobys[11].m_Substate += 4;
  g_Hud.m_Mobys[11].m_Rotation.x = COSINE_8(g_Hud.m_Mobys[11].m_Substate) >> 7;
  g_Hud.m_Mobys[11].m_Rotation.y = SINE_8(g_Hud.m_Mobys[11].m_Substate) >> 7;
  if (D_800758E8 > 19) {
    D_8007582C++;
    if (D_8007582C > 99)
      D_8007582C = 99;
    D_800758E8 -= 20;
  }
}

void GenerateGemCollectMobys(int pGemValue, Moby *pGemPos) {
  int i = 1;
  int moby_x = pGemPos->m_Position.x;
  int moby_y = pGemPos->m_Position.y;
  Vector3D16 vec;

  setXYZ(&vec, Cos(g_Camera.m_Rotation.z - 0x400) >> 8,
         Sin(g_Camera.m_Rotation.z - 0x400) >> 8, 128);

  for (; pGemValue != 0; pGemValue /= 10, i *= 10) {
    MobyNumberProps *props;
    int rem = (pGemValue % 10);
    Moby *pMoby = (*D_800758CC)(rem + MOBYCLASS_NUMBER_0, nullptr);
    setXYZ(&pMoby->m_Position, moby_x, moby_y, pGemPos->m_Position.z);
    setXYZ(&pMoby->m_Rotation, 0, 0, g_Camera.m_Rotation.z >> 4);

    props = pMoby->m_Props;
    setXYZ(&props->unk_0x8, vec.x, vec.y, vec.z);
    props->unk_0x4 = rem * i;

    // this FIXED_MUL may not be exactly what they are getting at, but it
    // matches
    moby_x -= FIXED_MUL(SINE_8(pMoby->m_Rotation.z), 256);
    moby_y += FIXED_MUL(COSINE_8(pMoby->m_Rotation.z), 256);
    vec.z -= 16;
  }
}
