#include <stdlib.h>

#include "common.h"
#include "camera.h"
#include "cyclorama.h"
#include "environment.h"
#include "images.h"
#include "math.h"
#include "matrix.h"
#include "memory.h"
#include "renderers.h"
#include "vector.h"

/* --- Globals touched by func_80050BD0 that lack a public declaration --- */

/* Per-portal "blocked" table, indexed by the portal's world-sector id.
 * If non-zero the portal/sky is currently occluded and is skipped. */
extern u_char D_800771C8[];

/* Source matrix/rotation table fed into the lower-level sky renderers. */
extern u_char D_8006FCF4[];

/* Pointer used by the lower-level sky renderers (set to a slot in the
 * rotation table above). */
extern void *D_80075798;

/* Accumulated/clamped screen Z used to decide whether a face is visible. */
extern int D_80075934;

/* Color targets / lerp scratch consumed by the sky renderers. */
/* D_8007575C (skybox color lerp value) is declared in common.h.   */
/* D_800757D4 (lerp color target)       is declared in cyclorama.h. */

/* Screen-projected vertices of the current portal's points.
 * Layout: D_80078DD8[i] = { int x, int y, int z } (12-byte stride). */
typedef struct {
  int x;
  int y;
  int z;
} ProjPoint;
extern ProjPoint D_80078DD8[]; /* one entry per portal point */

/* Column views of the projected-point array above: the y and z members
 * live at their own symbols (12-byte stride). */
typedef struct {
  int v;
  int pad[2];
} PtCol;
extern PtCol D_80078DDC[]; /* y column */
extern PtCol D_80078DE0[]; /* z column */

/* Output edge list, 0x18-byte stride.
 *   +0x00 reserved/flag, +0x04 packed v0 (y<<16|x), +0x08 packed v1,
 *   +0x0C edge dy, +0x10 edge dx, +0x14 cross term. */
typedef struct {
  int reserved; /* +0x00 */
  int v0;       /* +0x04 packed (y<<16 | x) of "next" vertex */
  int v1;       /* +0x08 packed (y<<16 | x) of "this" vertex */
  int dy;       /* +0x0C */
  int dx;       /* +0x10 */
  int cross;    /* +0x14 */
} Edge;
extern Edge D_80077EA0[]; /* D_80077EA0/EA4/EA8/EAC/EB0/EB4 */

/* Column views of the edge list above (0x18-byte stride). */
typedef struct {
  int v;
  int pad[5];
} EdgeCol;
extern EdgeCol D_80077EA4[]; /* v0 column */
extern EdgeCol D_80077EA8[]; /* v1 column */
extern EdgeCol D_80077EAC[]; /* dy column */
extern EdgeCol D_80077EB0[]; /* dx column */
extern EdgeCol D_80077EB4[]; /* cross column */

/* Screen-space bounding box of the current portal: stored as four words,
 * each value placed in the high 16 bits. */
extern int D_8007AA00[4];

/* Lower-level sky / portal renderers. */
extern void func_8004FEA0(void *pColorOrMatrix);
extern void func_80050240(int pTexture, SHORTMATRIX *pViewMatrix,
                          SHORTMATRIX *pProjMatrix);
extern void func_8004F4BC(int pTexture, SHORTMATRIX *pViewMatrix,
                          SHORTMATRIX *pProjMatrix);

/* Returns the number of significant bits of an integer (log2-ish);
 * used to choose right-shift amounts for distance scaling. */
extern int func_80016D08(int pValue);


/* Compute the screen bounding box pass that walks a portal's edges and
 * emits visible ones into the global edge list.  Returns the visibility
 * flag (0, or 2 == fully visible) and fills the bounding box via pointers. */
typedef struct {
  int minX, maxX; /* s4 / fp */
  int minY, maxY; /* s7 / s6 */
  int triCount;   /* s3 */
} EdgePass;

/**
 * Renders the main cyclorama (sky) and every active portal.
 *
 * Each frame the sky's pitch/yaw scroll slowly, two rotation matrices are
 * built from the camera orientation (one for the sky dome, one for the
 * portal billboards), then every portal is processed:
 *   - reject it if its sector is occluded,
 *   - compute its distance and a fade color,
 *   - project its points to screen space and build the screen bounding box,
 *   - tessellate visible edges into the global edge list, and finally
 *   - hand the portal off to the appropriate sky/portal renderer depending
 *     on how far away it is.
 * Afterwards the cyclorama itself is drawn using the camera matrices.
 */
void func_80050BD0(void) {
  MATRIX skyMatrix;      /* sp+0x10 : sky-dome rotation matrix          */
  MATRIX portalMatrix;   /* sp+0x30 : portal billboard matrix           */
  Vector3D toCamera;          /* sp+0x50 : portal->camera vector             */
  Vector3D portalCenter;      /* sp+0x60 : averaged portal point centre      */
  Vector3D rotatedNormal;     /* sp+0x70 : portal normal rotated to view     */
  Vector3D camRel;            /* sp+0x80 : portal centre relative to camera   */
  Vector3D8 packedRot;        /* sp+0x90 : packed camera rotation            */
  MATRIX faceMatrix;     /* sp+0x98 : matrix from RotVec8ToMatrix        */
  Color fadeColor;            /* sp+0xB8 : per-portal fade colour             */
  Vector3D rotatedNormal2;    /* sp+0xC0                                     */
  Vector3D camRel2;           /* sp+0xD0 : portal centre relative to camera   */
  Vector3D8 packedRot2;       /* sp+0xE0                                     */
  MATRIX faceMatrix2;    /* sp+0xE8                                     */

  short *m;                   /* short view of a matrix */
  int faceVisible;            /* s1 */
  int minX, maxX, minY, maxY; /* s4 / fp / s7 / s6 ; minX also holds the
                               * per-portal distance shift before the
                               * box is reset (one variable in retail) */
  int triCount;               /* s3 */
  int portalIndex;            /* sp+0x108 */
  int flagDx, flagDy;         /* sp+0x110 / sp+0x118 : all-edges-short flags */
  int facingSign;             /* sp+0x120 */
  int sumX, sumY;             /* sp+0x128 / sp+0x130 */
  int distance;               /* sp+0x138 */
  int i;
  int next;

  /* --- Slowly scroll the sky's yaw and pitch every frame --- */
  D_80075858 = (D_80075858 + 2) & 0xFFF;
  D_800758FC = (D_800758FC + 2) & 0xFFF;
  if (D_800758FC > 0x800) {
    D_800758FC -= 0x1000;
  }
  if (D_800758FC >= 0x81) {
    D_800758FC = 0x80;
  }

  /* --- Build the sky-dome rotation matrix (skyMatrix) --- */
  Memset(&skyMatrix, 0, sizeof(skyMatrix));
  SetTransMatrix(&skyMatrix);
  m = &skyMatrix.m[0][0];
  m[0] = 0x1000;                                     /* +0x00 */
  m[4] = Cos(g_Camera.m_Rotation.y - D_800758FC);    /* +0x08 */
  m[7] = Sin(g_Camera.m_Rotation.y - D_800758FC);    /* +0x0E */
  m[5] = -Sin(g_Camera.m_Rotation.y - D_800758FC);   /* +0x0A */
  m[8] = Cos(g_Camera.m_Rotation.y - D_800758FC);    /* +0x10 */

  /* --- Build a billboard matrix from the sky-scroll yaw and combine --- */
  Memset(&portalMatrix, 0, sizeof(portalMatrix));
  m = &portalMatrix.m[0][0];
  m[0] = Cos(g_Camera.m_Rotation.z + D_80075858);  /* +0x30 */
  m[6] = -Sin(g_Camera.m_Rotation.z + D_80075858); /* +0x3C */
  m[4] = 0x1000;                                   /* +0x38 */
  m[2] = Sin(g_Camera.m_Rotation.z + D_80075858);  /* +0x34 */
  m[8] = Cos(g_Camera.m_Rotation.z + D_80075858);  /* +0x40 */
  MulMatrix(&skyMatrix, &portalMatrix);

  /* --- And again from the camera's pitch --- */
  Memset(&portalMatrix, 0, sizeof(portalMatrix));
  m = &portalMatrix.m[0][0];
  m[0] = Cos(g_Camera.m_Rotation.x);  /* +0x30 */
  m[3] = -Sin(g_Camera.m_Rotation.x); /* +0x36 */
  m[1] = Sin(g_Camera.m_Rotation.x);  /* +0x32 */
  m[4] = Cos(g_Camera.m_Rotation.x);  /* +0x38 */
  m[8] = 0x1000;                      /* +0x40 */
  MulMatrix(&skyMatrix, &portalMatrix);

  /* Copy the top of the sky matrix into the portal matrix and round-scale
   * three of its entries (the sky-dome basis vectors). */
  Memcpy(&portalMatrix, &skyMatrix, 0x14);
  m = &portalMatrix.m[0][0];
  {
    int t;
    t = skyMatrix.m[1][0] * 0x140;
    if (t < 0) t += 0x1FF;
    m[3] = t >> 9; /* +0x36 from skyMatrix +0x16 */
    t = skyMatrix.m[1][1] * 0x140;
    if (t < 0) t += 0x1FF;
    m[4] = t >> 9; /* +0x38 from skyMatrix +0x18 */
    t = skyMatrix.m[1][2] * 0x140;
    if (t < 0) t += 0x1FF;
    m[5] = t >> 9; /* +0x3A from skyMatrix +0x1A */
  }

  /* --- Iterate over every active portal --- */
  for (portalIndex = 0; portalIndex < g_PortalCount; portalIndex++) {

    /* Skip portals whose world sector is currently occluded. */
    if (g_Portals[portalIndex]->m_WorldSector >= 0 &&
        D_800771C8[g_Portals[portalIndex]->m_WorldSector] == 0) {
      continue;
    }

    /* Per-portal "all edges short" flags (cleared when any edge spans >= 3
     * pixels in x or y); used to skip near-degenerate portals below. */
    flagDy = 1;
    flagDx = 1;

    /* Animated shimmer used as the fade lerp amount. */
    {
      int shimmer = abs(Cos((g_LevelTicks << 4) + (portalIndex << 9))) >> 1;
      Portal *p = g_Portals[portalIndex];
      *(int *)&fadeColor = shimmer;
      *(int *)&fadeColor = ColorLerp(*(int *)((char *)p->m_Skybox + 0x10),
                                     0xFFFFFF, shimmer);
    }

    /* Vector from the portal centre to the camera; octagonal distance. */
    VecSub(&toCamera, (Vector3D *)((char *)g_Portals[portalIndex] + 0x20),
           &g_Camera.m_Position);
    {
      int ax = toCamera.x, ay = toCamera.y, az = toCamera.z;
      minX = func_80016D08(ABS(ax) + ABS(ay) + ABS(az));
    }
    if (minX >= 0xF) {
      minX >>= 1;
      VecShiftRight(&toCamera, minX);
      distance = VecMagnitude(&toCamera, 1) << minX;
    } else {
      minX >>= 1;
      distance = VecMagnitude(&toCamera, 1);
    }

    /* Distance-driven scaling shift, clamped to >= 0. */
    minX = func_80016D08(distance) - 0xD;
    if (minX < 0) {
      minX = 0;
    }

    /* When the low-poly world is skipped, blend the cyclorama colour in
     * based on how far the portal is (a coarse LOD fade). */
    if (g_SkipLowPolyWorld && distance >= 0x4001) {
      i = (0x8000 - distance) >> 2;
      if (i < 0) i = 0;
      if (i >= 0x1001) i = 0x1000;
      *(int *)&fadeColor = ColorLerp(*(int *)&g_Cyclorama.m_BackgroundColor,
                                     *(int *)&fadeColor, i);
    }

    /* --- Average the portal's points to get a centre, projecting each one
     *     to screen space (D_80078DD8...) along the way. --- */
    VecNull(&portalCenter);
    for (i = 0; i < g_Portals[portalIndex]->m_PointCount; i++) {
      func_80017B48((Vector3D *)&D_80078DD8[i],
                    (Vector3D *)((char *)g_Portals[portalIndex] + 0x20 + i * 12),
                    minX);
      VecAdd(&portalCenter, &portalCenter,
             (Vector3D *)((char *)g_Portals[portalIndex] + 0x20 + i * 12));
    }
    portalCenter.x /= g_Portals[portalIndex]->m_PointCount;
    portalCenter.y /= g_Portals[portalIndex]->m_PointCount;
    portalCenter.z /= g_Portals[portalIndex]->m_PointCount;

    /* Back-face sign: dot of the camera-relative vector (taken at the
     * portal's normal field, +0x2C) with the portal's first three words. */
    VecSub(&toCamera, &g_Camera.m_Position,
           (Vector3D *)((char *)g_Portals[portalIndex] + 0x2C));
    VecShiftRight(&toCamera, minX);
    {
      Portal *p = g_Portals[portalIndex];
      facingSign = -toCamera.x * ((int *)p)[2] - toCamera.y * ((int *)p)[3] -
                   toCamera.z * ((int *)p)[4];
    }

    /* --- Reset per-portal accumulators. --- */
    maxX = 0x13F8;
    maxY = 0xF0;
    minY = 0;
    faceVisible = 0;
    triCount = 0;
    sumX = 0;
    sumY = 0;
    D_80075934 = 0;
    minX = 0;
    D_80075798 = &D_8006FCF4[0x800];

    /* --- First pass: project edges into the global edge list. --- */
    {
      for (i = 0; i < g_Portals[portalIndex]->m_PointCount; i++) {
        if (facingSign > 0) {
          next = i + 1;
          if (next == g_Portals[portalIndex]->m_PointCount) next = 0;
        } else {
          next = i - 1;
          if (next < 0) next = g_Portals[portalIndex]->m_PointCount - 1;
        }

        sumX += D_80078DD8[next].x;
        sumY += D_80078DDC[next].v;
        D_80075934 += D_80078DE0[next].v;

        /* On-screen visibility of the "next" projected vertex. */
        if ((u_int)(D_80078DD8[next].x - 1) < 0x1FF &&
            (u_int)(D_80078DDC[next].v - 1) < 0xEF && D_80078DE0[next].v > 0) {
          faceVisible = 1;
        }

        /* Extend the screen bounding box. */
        if (minX < D_80078DD8[next].x) minX = D_80078DD8[next].x;
        if (D_80078DD8[next].x < maxX) maxX = D_80078DD8[next].x;
        if (minY < D_80078DDC[next].v) minY = D_80078DDC[next].v;
        if (D_80078DDC[next].v < maxY) maxY = D_80078DDC[next].v;

        /* Emit the edge unless both endpoints are off the same screen side. */
        if ((D_80078DD8[i].x < 0x200 || D_80078DD8[next].x < 0x200) &&
            (D_80078DD8[i].x > 0 || D_80078DD8[next].x > 0) &&
            (D_80078DDC[i].v < 0xF0 || D_80078DDC[next].v < 0xF0) &&
            (D_80078DDC[i].v > 0 || D_80078DDC[next].v > 0)) {
          int d = D_80078DD8[i].x - D_80078DD8[next].x;
          if (d < 0) d = -d;
          if (d >= 3) flagDx = 0;
          d = D_80078DDC[i].v - D_80078DDC[next].v;
          if (d < 0) d = -d;
          if (d >= 3) flagDy = 0;

          D_80077EA0[triCount].reserved = 1;
          D_80077EA4[triCount].v =
              (D_80078DDC[i].v << 16) | (u_short)D_80078DD8[i].x;
          D_80077EA8[triCount].v =
              (D_80078DDC[next].v << 16) | (u_short)D_80078DD8[next].x;
          D_80077EAC[triCount].v = D_80078DDC[i].v - D_80078DD8[next].y;
          D_80077EB0[triCount].v = D_80078DD8[next].x - D_80078DD8[i].x;
          D_80077EB4[triCount].v =
              (-D_80077EAC[triCount].v * D_80078DD8[i].x) -
              (D_80077EB0[triCount].v * D_80078DDC[i].v);
          triCount++;
        }
      }
    }

    /* Skip portals whose every emitted edge was near-degenerate. */
    if ((flagDx || flagDy) && triCount) {
      continue;
    }

    /* Average the accumulated screen position and depth. */
    sumX /= g_Portals[portalIndex]->m_PointCount;
    sumY /= g_Portals[portalIndex]->m_PointCount;
    D_80075934 = (D_80075934 / g_Portals[portalIndex]->m_PointCount) >> 7;
    if (D_80075934 >= 0x100) {
      D_80075934 += 0x40;
    }
    if (D_80075934 >= 0x800) {
      D_80075934 = 0x7FF;
    }

    /* Visible when the whole box is on-screen and depth is positive, or
     * when the box spans the entire screen (a portal filling the view). */
    if (maxX < 0x200 && maxY < 0xF0 && minX > 0 && minY > 0 &&
        D_80075934 > 0 && triCount) {
      faceVisible |= 2;
    } else if (maxX <= 0 && maxY <= 0 && minX >= 0x200 && minY >= 0xF0 &&
               D_80075934 > 0) {
      faceVisible |= 2;
    } else {
      faceVisible = 0;
    }

    /* Refine visibility for nearby portals using the rotated normal. */
    if (faceVisible == 2 && distance < 0x1000) {
      VecSub(&camRel, &portalCenter, &g_Camera.m_Position);
      rotatedNormal.x = 0x1000;
      rotatedNormal.y = 0;
      rotatedNormal.z = 0;
      packedRot.x = (u_char)((u_short)g_Camera.m_Rotation.x >> 4);
      packedRot.y = (u_char)((u_short)g_Camera.m_Rotation.y >> 4);
      packedRot.z = (u_char)((u_short)g_Camera.m_Rotation.z >> 4);
      RotVec8ToMatrix(&packedRot, &faceMatrix, 0);
      VecRotateByMatrix(&faceMatrix, &rotatedNormal, &rotatedNormal);
      if (rotatedNormal.x * camRel.x +
              rotatedNormal.y * camRel.y +
              rotatedNormal.z * camRel.z <
          0) {
        faceVisible = 0;
      }
    }

    if (faceVisible) {
      if (maxX < 0) maxX = 0;
      if (maxY < 0) maxY = 0;
      if (minX > 0x200) minX = 0x200;
      if (minY > 0xF0) minY = 0xF0;
      D_8007AA00[0] = maxY << 16;
      D_8007AA00[1] = minY << 16;
      D_8007AA00[2] = minX << 16;
      D_8007AA00[3] = maxX << 16;
      D_80077EA0[triCount].reserved = 0;

      if (distance < 0x4000) {
        if (distance >= 0x3001) {
          D_8007575C = distance - 0x3000;
          D_800757D4 = ColorLerp(*(int *)((char *)g_Portals[portalIndex]->m_Skybox + 0x10),
                                 *(int *)&fadeColor, distance - 0x3000);
          func_8004FEA0(&D_800757D4);
        } else {
          func_8004FEA0((void *)((char *)g_Portals[portalIndex]->m_Skybox + 0x10));
        }
      } else {
        func_8004FEA0(&fadeColor);
      }
    }

    /* Far portals are done after the renderer call above. */
    if (distance >= 0x4000) {
      continue;
    }

    /* --- Second pass: smooth the projected vertices toward the average,
     *     re-build the box and emit again, then call the LOD renderer. --- */
    maxX = 0x200;
    minX = 0;
    maxY = 0xF0;
    minY = 0;
    faceVisible = 0;
    triCount = 0;
    D_80075798 = &D_8006FCF4[0x800];

    /* First sub-pass: push every projected point away from the average
     * (fattens the silhouette by a pixel each side) and rebuild the box. */
    for (i = 0; i < g_Portals[portalIndex]->m_PointCount; i++) {
        if (D_80078DD8[i].x > sumX) {
          D_80078DD8[i].x += 2;
        } else if (D_80078DD8[i].x < sumX) {
          D_80078DD8[i].x -= 2;
        }
        if (D_80078DDC[i].v > sumY) {
          D_80078DDC[i].v += 2;
        } else if (D_80078DDC[i].v < sumY) {
          D_80078DDC[i].v -= 2;
        }

        if (minX < D_80078DD8[i].x) minX = D_80078DD8[i].x;
        if (D_80078DD8[i].x < maxX) maxX = D_80078DD8[i].x;
        if (minY < D_80078DDC[i].v) minY = D_80078DDC[i].v;
        if (D_80078DDC[i].v < maxY) maxY = D_80078DDC[i].v;
      }

    /* Second sub-pass: emit the smoothed edges. */
    {
      for (i = 0; i < g_Portals[portalIndex]->m_PointCount; i++) {
        if (facingSign > 0) {
          next = i + 1;
          if (next == g_Portals[portalIndex]->m_PointCount) next = 0;
        } else {
          next = i - 1;
          if (next < 0) next = g_Portals[portalIndex]->m_PointCount - 1;
        }

        if ((u_int)(D_80078DD8[next].x - 1) < 0x1FF &&
            (u_int)(D_80078DDC[next].v - 1) < 0xEF && D_80078DE0[next].v > 0) {
          faceVisible = 1;
        }

        if ((D_80078DD8[i].x < 0x200 || D_80078DD8[next].x < 0x200) &&
            (D_80078DD8[i].x > 0 || D_80078DD8[next].x > 0) &&
            (D_80078DDC[i].v < 0xF0 || D_80078DDC[next].v < 0xF0) &&
            (D_80078DDC[i].v > 0 || D_80078DDC[next].v > 0)) {
          D_80077EA0[triCount].reserved = 1;
          D_80077EA4[triCount].v =
              (D_80078DDC[i].v << 16) | (u_short)D_80078DD8[i].x;
          D_80077EA8[triCount].v =
              (D_80078DDC[next].v << 16) | (u_short)D_80078DD8[next].x;
          D_80077EAC[triCount].v = D_80078DDC[i].v - D_80078DD8[next].y;
          D_80077EB0[triCount].v = D_80078DD8[next].x - D_80078DD8[i].x;
          D_80077EB4[triCount].v =
              (-D_80077EAC[triCount].v * D_80078DD8[i].x) -
              (D_80077EB0[triCount].v * D_80078DDC[i].v);
          triCount++;
        }
      }
    }

    if (maxX < 0x200 && maxY < 0xF0 && minX > 0 && minY > 0 &&
        D_80075934 > 0 && triCount) {
      faceVisible |= 2;
    } else if (maxX <= 0 && maxY <= 0 && minX >= 0x200 && minY >= 0xF0 &&
               D_80075934 > 0) {
      faceVisible |= 2;
    } else {
      faceVisible = 0;
    }

    if (faceVisible == 2 && distance < 0x1000) {
      VecSub(&camRel2, &portalCenter, &g_Camera.m_Position);
      rotatedNormal2.x = 0x1000;
      rotatedNormal2.y = 0;
      rotatedNormal2.z = 0;
      packedRot2.x = (u_char)((u_short)g_Camera.m_Rotation.x >> 4);
      packedRot2.y = (u_char)((u_short)g_Camera.m_Rotation.y >> 4);
      packedRot2.z = (u_char)((u_short)g_Camera.m_Rotation.z >> 4);
      RotVec8ToMatrix(&packedRot2, &faceMatrix2, 0);
      VecRotateByMatrix(&faceMatrix2, &rotatedNormal2, &rotatedNormal2);
      if (rotatedNormal2.x * camRel2.x +
              rotatedNormal2.y * camRel2.y +
              rotatedNormal2.z * camRel2.z <
          0) {
        faceVisible = 0;
      }
    }

    if (faceVisible == 0) {
      continue;
    }

    if (maxX < 0) maxX = 0;
    if (maxY < 0) maxY = 0;
    if (minX > 0x200) minX = 0x200;
    if (minY > 0xF0) minY = 0xF0;
    D_8007AA00[0] = maxY << 16;
    D_8007AA00[1] = minY << 16;
    D_8007AA00[2] = minX << 16;
    D_8007AA00[3] = maxX << 16;
    D_80077EA0[triCount].reserved = 0;

    if (distance >= 0x3001) {
      D_8007575C = distance - 0x3000;
      D_800757D4 = ColorLerp(*(int *)((char *)g_Portals[portalIndex]->m_Skybox + 0x10),
                             *(int *)&fadeColor, distance - 0x3000);
      func_80050240((int)g_Portals[portalIndex]->m_Skybox, &skyMatrix, &portalMatrix);
    } else {
      func_8004F4BC((int)g_Portals[portalIndex]->m_Skybox, &skyMatrix, &portalMatrix);
    }
  }

  /* Finally draw the cyclorama itself with the camera's matrices.  Use the
   * camera's occlusion group when it is in range, otherwise -1. */
  {
    int occlusionGroup = g_Camera.m_OcclusionGroup;
    if (occlusionGroup >= g_Environment.m_OcclusionGroupCount) {
      occlusionGroup = -1;
    }
    func_8004EBA8(occlusionGroup, &g_Camera.m_ViewMatrix,
                  &g_Camera.m_ProjectionMatrix);
  }
}
