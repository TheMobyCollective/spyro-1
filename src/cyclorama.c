#include "common.h"

#include "camera.h"
#include "cyclorama.h"
#include "environment.h"
#include "images.h"
#include "math.h"
#include "memory.h"
#include "sony_image.h"
#include "vector.h"

void func_80050BD0(void) {
  MATRIX viewMatrix;
  MATRIX projMatrix;
  Vector3D delta;
  Vector3D center;

  int portalIndex;
  int color;
  int next;
  int i;
  int thinX;
  int thinY;
  int diff;
  int facing;
  int sumX;
  int sumY;
  int distance;
  int minX;
  int maxX; // Reused for leading bits
  int minY;
  int maxY;
  int visible;
  int edgeCount;
  int fade;
  int *bgColor;
  int group;

  D_80075858 = (D_80075858 + 2) & 0xFFF;
  D_800758FC = (D_800758FC + 2) & 0xFFF;

  if (D_800758FC > 2048) {
    D_800758FC -= 4096;
  }

  if (D_800758FC > 128) {
    D_800758FC = 128;
  }

  Memset(&viewMatrix, 0, sizeof(MATRIX));
  SetTransMatrix(&viewMatrix);
  viewMatrix.m[0][0] = 0x1000;
  viewMatrix.m[1][1] = Cos(g_Camera.m_Rotation.y - D_800758FC);
  viewMatrix.m[2][1] = Sin(g_Camera.m_Rotation.y - D_800758FC);
  viewMatrix.m[1][2] = -Sin(g_Camera.m_Rotation.y - D_800758FC);
  viewMatrix.m[2][2] = Cos(g_Camera.m_Rotation.y - D_800758FC);

  Memset(&projMatrix, 0, sizeof(MATRIX));
  projMatrix.m[0][0] = Cos(g_Camera.m_Rotation.z + D_80075858);
  projMatrix.m[2][0] = -Sin(g_Camera.m_Rotation.z + D_80075858);
  projMatrix.m[1][1] = 0x1000;
  projMatrix.m[0][2] = Sin(g_Camera.m_Rotation.z + D_80075858);
  projMatrix.m[2][2] = Cos(g_Camera.m_Rotation.z + D_80075858);
  MulMatrix(&viewMatrix, &projMatrix);

  Memset(&projMatrix, 0, sizeof(MATRIX));
  projMatrix.m[0][0] = Cos(g_Camera.m_Rotation.x);
  projMatrix.m[1][0] = -Sin(g_Camera.m_Rotation.x);
  projMatrix.m[0][1] = Sin(g_Camera.m_Rotation.x);
  projMatrix.m[1][1] = Cos(g_Camera.m_Rotation.x);
  projMatrix.m[2][2] = 0x1000;
  MulMatrix(&viewMatrix, &projMatrix);

  Memcpy(&projMatrix, &viewMatrix, sizeof(SHORTMATRIX));
  projMatrix.m[1][0] = viewMatrix.m[1][0] * 320 / 512;
  projMatrix.m[1][1] = viewMatrix.m[1][1] * 320 / 512;
  projMatrix.m[1][2] = viewMatrix.m[1][2] * 320 / 512;

  for (portalIndex = 0; portalIndex < g_PortalCount; portalIndex++) {
    // Skip portals in environment sectors that weren't rendered
    if (g_Portals[portalIndex]->m_WorldSector >= 0 &&
        D_800771C8[g_Portals[portalIndex]->m_WorldSector] == 0) {
      continue;
    }

    thinY = 1;
    thinX = 1;

    // Portals in the distance animate a little
    fade = Cos(g_LevelTicks * 16 + portalIndex * 512);
    bgColor = &g_Portals[portalIndex]->m_Skybox->copyBgColor;
    color = ABS(fade) >> 1;
    color = ColorLerp(*bgColor, 0xFFFFFF, ABS(fade) >> 1);

    VecSub(&delta, &g_Portals[portalIndex]->m_Center, &g_Camera.m_Position);
    maxX = func_80016D08(ABS(delta.x) + ABS(delta.y) + ABS(delta.z));

    if (maxX >= 15) {
      maxX >>= 1;
      VecShiftRight(&delta, maxX);
      distance = VecMagnitude(&delta, 1) << maxX;
    } else {
      distance = VecMagnitude(&delta, 1);
    }

    maxX = func_80016D08(distance) - 13;

    if (maxX < 0) {
      maxX = 0;
    }

    // For levels with fog: fade far away portals into the background color
    if (g_SkipLowPolyWorld != 0 && distance > (1024 * 16)) {
      i = (0x8000 - distance) >> 2;

      if (i < 0) {
        i = 0;
      }

      if (i > 0x1000) {
        i = 0x1000;
      }

      color = ColorLerp(*(int *)&g_Cyclorama.m_BackgroundColor, color, i);
    }

    // Project the points on the screen and calculate the center
    VecNull(&center);

    for (i = 0; i < g_Portals[portalIndex]->m_PointCount; i++) {
      func_80017B48(&D_80078DD8[i], &g_Portals[portalIndex]->m_Center + i,
                    maxX);
      VecAdd(&center, &center, &g_Portals[portalIndex]->m_Center + i);
    }

    center.x /= g_Portals[portalIndex]->m_PointCount;
    center.y /= g_Portals[portalIndex]->m_PointCount;
    center.z /= g_Portals[portalIndex]->m_PointCount;

    VecSub(&delta, &g_Camera.m_Position, g_Portals[portalIndex]->m_Points);
    VecShiftRight(&delta, maxX);
    facing = -delta.x * g_Portals[portalIndex]->unk_0x8.x -
             delta.y * g_Portals[portalIndex]->unk_0x8.y -
             delta.z * g_Portals[portalIndex]->unk_0x8.z;

    // SKELETON: Typo lol?
    minX = 5112;
    minY = 240;
    maxX = 0;
    maxY = 0;
    visible = 0;
    edgeCount = 0;
    D_80075934 = 0;
    sumX = 0;
    sumY = 0;
    D_80075798 = &g_SonyImage.u.m_Buf[0x800];

    for (i = 0; i < g_Portals[portalIndex]->m_PointCount; i++) {
      if (facing > 0) {
        next = i + 1;

        if (next == g_Portals[portalIndex]->m_PointCount) {
          next = 0;
        }
      } else {
        next = i - 1;

        if (next < 0) {
          next = g_Portals[portalIndex]->m_PointCount - 1;
        }
      }

      sumX += D_80078DD8[next].x;
      sumY += D_80078DD8[next].y;
      D_80075934 += D_80078DD8[next].z;

      if (D_80078DD8[next].x > 0 && D_80078DD8[next].x < 512 &&
          D_80078DD8[next].y > 0 && D_80078DD8[next].y < 240 &&
          D_80078DD8[next].z > 0) {
        visible = 1;
      }

      if (maxX < D_80078DD8[next].x) {
        maxX = D_80078DD8[next].x;
      }

      if (D_80078DD8[next].x < minX) {
        minX = D_80078DD8[next].x;
      }

      if (maxY < D_80078DD8[next].y) {
        maxY = D_80078DD8[next].y;
      }

      if (D_80078DD8[next].y < minY) {
        minY = D_80078DD8[next].y;
      }

      // Skip edges that are entirely off one side of the screen
      if ((D_80078DD8[i].x < 512 || D_80078DD8[next].x < 512) &&
          (D_80078DD8[i].x > 0 || D_80078DD8[next].x > 0) &&
          (D_80078DD8[i].y < 240 || D_80078DD8[next].y < 240) &&
          (D_80078DD8[i].y > 0 || D_80078DD8[next].y > 0)) {
        diff = D_80078DD8[i].x - D_80078DD8[next].x;

        if (ABS(diff) >= 3) {
          thinX = 0;
        }

        diff = D_80078DD8[i].y - D_80078DD8[next].y;

        if (ABS(diff) >= 3) {
          thinY = 0;
        }

        D_80077EA0[edgeCount].m_Active = 1;
        D_80077EA0[edgeCount].m_Start =
            (D_80078DD8[i].y << 16) | (D_80078DD8[i].x & 0xFFFF);
        D_80077EA0[edgeCount].m_End =
            (D_80078DD8[next].y << 16) | (D_80078DD8[next].x & 0xFFFF);
        D_80077EA0[edgeCount].m_A = D_80078DD8[i].y - D_80078DD8[next].y;
        D_80077EA0[edgeCount].m_B = D_80078DD8[next].x - D_80078DD8[i].x;
        D_80077EA0[edgeCount].m_C =
            -D_80077EA0[edgeCount].m_A * D_80078DD8[i].x -
            D_80077EA0[edgeCount].m_B * D_80078DD8[i].y;
        edgeCount++;
      }
    }

    // Skip if too thin
    if ((thinX || thinY) && edgeCount != 0) {
      continue;
    }

    sumX /= g_Portals[portalIndex]->m_PointCount;
    sumY /= g_Portals[portalIndex]->m_PointCount;
    D_80075934 = (D_80075934 / g_Portals[portalIndex]->m_PointCount) >> 7;

    if (D_80075934 > 255) {
      D_80075934 += 64;
    }

    if (D_80075934 > 2047) {
      D_80075934 = 2047;
    }

    // Visible when it's on screen, or when it covers the whole screen
    if (minX < 512 && minY < 240 && maxX > 0 && maxY > 0 && D_80075934 > 0 &&
        edgeCount != 0) {
      visible |= 2;
    } else if (minX <= 0 && minY <= 0 && maxX >= 512 && maxY >= 240 &&
               D_80075934 > 0) {
      visible |= 2;
    } else {
      visible = 0;
    }

    if (visible == 2 && distance < 4096) {
      Vector3D forward;
      Vector3D toCenter;
      Vector3D8 rotation;
      MATRIX rotMatrix;

      VecSub(&toCenter, &center, &g_Camera.m_Position);
      forward.x = 4096;
      forward.y = 0;
      forward.z = 0;
      rotation.x = g_Camera.m_Rotation.x >> 4;
      rotation.y = g_Camera.m_Rotation.y >> 4;
      rotation.z = g_Camera.m_Rotation.z >> 4;
      RotVec8ToMatrix(&rotation, &rotMatrix, nullptr);
      VecRotateByMatrix(&rotMatrix, &forward, &forward);

      if (forward.x * toCenter.x + forward.y * toCenter.y +
              forward.z * toCenter.z <
          0) {
        visible = 0;
      }
    }

    // Draw the portal's backdrop
    if (visible) {
      if (minX < 0) {
        minX = 0;
      }

      if (minY < 0) {
        minY = 0;
      }

      if (maxX > 512) {
        maxX = 512;
      }

      if (maxY > 240) {
        maxY = 240;
      }

      D_8007AA00[0] = minY << 16;
      D_8007AA00[1] = maxY << 16;
      D_8007AA00[2] = maxX << 16;
      D_8007AA00[3] = minX << 16;
      D_80077EA0[edgeCount].m_Active = 0;

      if (distance < (16 * 1024)) {
        if (distance > (12 * 1024)) {
          bgColor = &g_Portals[portalIndex]->m_Skybox->copyBgColor;
          D_8007575C = distance - (12 * 1024);
          D_800757D4 = ColorLerp(*bgColor, color, D_8007575C);
          func_8004FEA0(&D_800757D4);
        } else {
          func_8004FEA0(&g_Portals[portalIndex]->m_Skybox->copyBgColor);
        }
      } else {
        func_8004FEA0(&color);
      }
    }

    if (distance >= (1024 * 16)) {
      // Too far away to draw the portal's actual contents
      continue;
    }

    minX = 512;
    maxX = 0;
    minY = 240;
    maxY = 0;
    visible = 0;
    edgeCount = 0;
    D_80075798 = &g_SonyImage.u.m_Buf[0x800];

    for (i = 0; i < g_Portals[portalIndex]->m_PointCount; i++) {
      if (D_80078DD8[i].x > sumX) {
        D_80078DD8[i].x += 2;
      } else if (D_80078DD8[i].x < sumX) {
        D_80078DD8[i].x -= 2;
      }

      if (D_80078DD8[i].y > sumY) {
        D_80078DD8[i].y += 2;
      } else if (D_80078DD8[i].y < sumY) {
        D_80078DD8[i].y -= 2;
      }

      if (maxX < D_80078DD8[i].x) {
        maxX = D_80078DD8[i].x;
      }

      if (D_80078DD8[i].x < minX) {
        minX = D_80078DD8[i].x;
      }

      if (maxY < D_80078DD8[i].y) {
        maxY = D_80078DD8[i].y;
      }

      if (D_80078DD8[i].y < minY) {
        minY = D_80078DD8[i].y;
      }
    }

    for (i = 0; i < g_Portals[portalIndex]->m_PointCount; i++) {
      if (facing > 0) {
        next = i + 1;

        if (next == g_Portals[portalIndex]->m_PointCount) {
          next = 0;
        }
      } else {
        next = i - 1;

        if (next < 0) {
          next = g_Portals[portalIndex]->m_PointCount - 1;
        }
      }

      if (D_80078DD8[next].x > 0 && D_80078DD8[next].x < 512 &&
          D_80078DD8[next].y > 0 && D_80078DD8[next].y < 240 &&
          D_80078DD8[next].z > 0) {
        visible = 1;
      }

      if ((D_80078DD8[i].x < 512 || D_80078DD8[next].x < 512) &&
          (D_80078DD8[i].x > 0 || D_80078DD8[next].x > 0) &&
          (D_80078DD8[i].y < 240 || D_80078DD8[next].y < 240) &&
          (D_80078DD8[i].y > 0 || D_80078DD8[next].y > 0)) {
        D_80077EA0[edgeCount].m_Active = 1;
        D_80077EA0[edgeCount].m_Start =
            (D_80078DD8[i].y << 16) | (D_80078DD8[i].x & 0xFFFF);
        D_80077EA0[edgeCount].m_End =
            (D_80078DD8[next].y << 16) | (D_80078DD8[next].x & 0xFFFF);
        D_80077EA0[edgeCount].m_A = D_80078DD8[i].y - D_80078DD8[next].y;
        D_80077EA0[edgeCount].m_B = D_80078DD8[next].x - D_80078DD8[i].x;
        D_80077EA0[edgeCount].m_C =
            -D_80077EA0[edgeCount].m_A * D_80078DD8[i].x -
            D_80077EA0[edgeCount].m_B * D_80078DD8[i].y;
        edgeCount++;
      }
    }

    if (minX < 512 && minY < 240 && maxX > 0 && maxY > 0 && D_80075934 > 0 &&
        edgeCount != 0) {
      visible |= 2;
    } else if (minX <= 0 && minY <= 0 && maxX >= 512 && maxY >= 240 &&
               D_80075934 > 0) {
      visible |= 2;
    } else {
      visible = 0;
    }

    if (visible == 2 && distance < 4096) {
      Vector3D forward;
      Vector3D toCenter;
      Vector3D8 rotation;
      MATRIX rotMatrix;

      VecSub(&toCenter, &center, &g_Camera.m_Position);
      forward.x = 4096;
      forward.y = 0;
      forward.z = 0;
      rotation.x = g_Camera.m_Rotation.x >> 4;
      rotation.y = g_Camera.m_Rotation.y >> 4;
      rotation.z = g_Camera.m_Rotation.z >> 4;
      RotVec8ToMatrix(&rotation, &rotMatrix, nullptr);
      VecRotateByMatrix(&rotMatrix, &forward, &forward);

      if (forward.x * toCenter.x + forward.y * toCenter.y +
              forward.z * toCenter.z <
          0) {
        visible = 0;
      }
    }

    if (!visible) {
      continue;
    }

    if (minX < 0) {
      minX = 0;
    }

    if (minY < 0) {
      minY = 0;
    }

    if (maxX > 512) {
      maxX = 512;
    }

    if (maxY > 240) {
      maxY = 240;
    }

    D_8007AA00[0] = minY << 16;
    D_8007AA00[1] = maxY << 16;
    D_8007AA00[2] = maxX << 16;
    D_8007AA00[3] = minX << 16;
    D_80077EA0[edgeCount].m_Active = 0;

    // Between 12 and 16M, the portal's contents fade away
    if (distance > (12 * 1024)) {
      bgColor = &g_Portals[portalIndex]->m_Skybox->copyBgColor;
      D_8007575C = distance - (12 * 1024);
      D_800757D4 = ColorLerp(*bgColor, color, D_8007575C);
      func_80050240(g_Portals[portalIndex]->m_Skybox, &viewMatrix, &projMatrix);
    } else {
      // If closer than 12M, then just draw the portal contents normally
      func_8004F4BC(g_Portals[portalIndex]->m_Skybox, &viewMatrix, &projMatrix);
    }
  }

  group = g_Camera.m_OcclusionGroup;

  if (group >= g_Environment.m_OcclusionGroupCount) {
    group = -1;
  }

  func_8004EBA8(group, &g_Camera.m_ViewMatrix, &g_Camera.m_ProjectionMatrix);
}
