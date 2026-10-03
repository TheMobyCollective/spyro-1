#include "environment.h"
#include "camera.h"
#include "common.h"
#include "memory.h"
#include "renderers.h"
#include "sony_image.h"

/// @brief: Create the environment
void func_8002B9CC() {
  int occlusionGroup;

  Memset16(
      g_SonyImage.u.m_Buf, 0,
      sizeof(g_SonyImage.u.m_Buf)); // Reset the buffer used for edge filling

  if (g_Camera.m_OcclusionGroup < g_Environment.m_OcclusionGroupCount) {
    g_Environment.m_CullingDistance = 0x28000;
    occlusionGroup = g_Camera.m_OcclusionGroup;
  } else {
    if (g_Gamestate >= GS_TitleScreen && g_Gamestate < GS_Credits) {
      g_Environment.m_CullingDistance = 0x1c000;
    } else {
      g_Environment.m_CullingDistance = 0x14000;
    }

    occlusionGroup = -1;
  }

  func_800258F0(occlusionGroup);
}
