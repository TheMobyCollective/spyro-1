#include "common.h"

#include "camera.h"
#include "cutscene.h"
#include "moby.h"

// 10:10:10 format (top 2 bits unused), where every value was divided by 256
#define UNPACK_VECTOR(v, packedPos)                                            \
  v.x = ((packedPos & 0x3FF00000) >> 12);                                      \
  v.y = ((packedPos & 0x000FFC00) >> 2);                                       \
  v.z = ((packedPos & 0x000003FF) << 8);

/// @brief Updates the cutscene for the current tick
void func_8002BFE0(int pTick) {
  int i;

  g_Camera.m_Position.x =
      g_CutsceneLayout->m_CameraData[g_CutsceneLayout->m_CurrentTick >> 1]
          .m_Position.x;
  g_Camera.m_Position.y =
      g_CutsceneLayout->m_CameraData[g_CutsceneLayout->m_CurrentTick >> 1]
          .m_Position.y;
  g_Camera.m_Position.z =
      g_CutsceneLayout->m_CameraData[g_CutsceneLayout->m_CurrentTick >> 1]
          .m_Position.z;
  g_Camera.m_Rotation.x =
      g_CutsceneLayout->m_CameraData[g_CutsceneLayout->m_CurrentTick >> 1]
          .m_Rotation.x;
  g_Camera.m_Rotation.y =
      g_CutsceneLayout->m_CameraData[g_CutsceneLayout->m_CurrentTick >> 1]
          .m_Rotation.y;
  g_Camera.m_Rotation.z =
      g_CutsceneLayout->m_CameraData[g_CutsceneLayout->m_CurrentTick >> 1]
          .m_Rotation.z;

  for (i = 0; i < g_CutsceneLayout->m_MobyCount; i++) {
    Vector3D v, v2;
    int a, b;

    if (g_Models[1 + i]->m_Animations[0]->m_ProgressPerTick == 16) {
      // a = g_CutsceneLayout->m_CurrentTick / 8;
      // b = (g_CutsceneLayout->m_CurrentTick % 8) * 8;
      a = g_CutsceneLayout->m_CurrentTick >> 3;
      b = (g_CutsceneLayout->m_CurrentTick & 7) * 8;
    } else if (g_Models[1 + i]->m_Animations[0]->m_ProgressPerTick == 21) {
      // a = g_CutsceneLayout->m_CurrentTick / 6;
      // b = (g_CutsceneLayout->m_CurrentTick % 6) * 10;
      a = g_CutsceneLayout->m_CurrentTick / 6;
      b = (g_CutsceneLayout->m_CurrentTick % 6) * 10;
    } else if (g_Models[1 + i]->m_Animations[0]->m_ProgressPerTick == 32) {
      // a = g_CutsceneLayout->m_CurrentTick / 4;
      // b = (g_CutsceneLayout->m_CurrentTick % 4) * 16;
      a = g_CutsceneLayout->m_CurrentTick >> 2;
      b = (g_CutsceneLayout->m_CurrentTick & 3) * 16;
    } else {
      // a = g_CutsceneLayout->m_CurrentTick / 2;
      // b = (g_CutsceneLayout->m_CurrentTick % 2) * 32;
      a = g_CutsceneLayout->m_CurrentTick >> 1;
      b = (g_CutsceneLayout->m_CurrentTick & 1) << 5;
    }

    g_LevelMobys[i].m_AnimationState.m_Animation = a / 60;
    g_LevelMobys[i].m_AnimationState.m_Frame = a % 60;
    g_LevelMobys[i].m_AnimationState.m_NextAnimation = (a + 1) / 60;
    g_LevelMobys[i].m_AnimationState.m_NextFrame = (a + 1) % 60;
    g_LevelMobys[i].m_AnimationState.m_FrameProgress = b;

    UNPACK_VECTOR(v, g_CutsceneLayout->m_MobyData[i]->m_PackedPos[a]);
    UNPACK_VECTOR(v2, g_CutsceneLayout->m_MobyData[i]->m_PackedPos[a + 1]);

    g_LevelMobys[i].m_Position.x = ((v.x * (64 - b)) + (v2.x * b)) >> 6; // / 64
    g_LevelMobys[i].m_Position.y = ((v.y * (64 - b)) + (v2.y * b)) >> 6;
    g_LevelMobys[i].m_Position.z = ((v.z * (64 - b)) + (v2.z * b)) >> 6;
  }
}