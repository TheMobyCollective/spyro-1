#include "common.h"

#include "gamepad.h"
#include "gamestate/draw.h"
#include "gamestate/update.h"
#include "initialization.h"

#include <stdio.h>

// These ARE in this file!
u_char g_PadMutex;
int g_StateSwitch;
int g_DeltaTime;
int g_UnprocessedFrames;

void main(void) {
  Initialize();

  while (1) {
    g_PadMutex = 0;
    GamestateUpdate();
    g_PadMutex = 1;

    g_DeltaTime = g_UnprocessedFrames;

    if (g_DeltaTime < 2)
      g_DeltaTime = 2;

    if (g_DeltaTime > 4)
      g_DeltaTime = 4;

    g_UnprocessedFrames = 0;

    if (!g_StateSwitch) {
      func_8001ED5C();
    }
  }
}
