#ifndef __SONY_IMAGE_H
#define __SONY_IMAGE_H

#include <sys/types.h>

#include "moby.h"

// The Sony Computer Entertainment Presents.. Screen
// is also used as memory for some stuff.
// That stuff expects it to be a struct.

typedef struct {
  Moby* m_Moby[0x240]; //0x900
  u_char unk_0x900[0xD00]; //??
  int unk_0x1600;
  u_char unk_0x1604[24];
  Vector3D16 unk_0x161C;
  Vector3D16 unk_0x1622;
  u_char unk_0x1628[0x5D8];
} DrawStateSonyBuf;

extern struct {
  union {
    u_char m_Buf[0x1c00];
    DrawStateSonyBuf m_Draw;
  }  u; // Used for some stuff
  u_int m_WorldNearQueued[256];
  u_int m_WorldFarQueued[256];
  Moby *m_ShadedMobys[256];
  char unk_0x2800[2464];
} g_SonyImage;

#endif
