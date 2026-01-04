#ifndef __SONY_IMAGE_H
#define __SONY_IMAGE_H

#include <sys/types.h>

#include "moby.h"

// The Sony Computer Entertainment Presents.. Screen
// is also used as memory for some stuff.
// That stuff expects it to be a struct.

extern char D_8006FCF4[1]; // Sony image

extern struct {
  u_char m_Buf[0x1c00]; // Used for some stuff
  u_int m_WorldNearQueued[256];
  u_int m_WorldFarQueued[256];
  Moby *m_ShadedMobys[256];
  char unk_0x2800[2464];
} g_SonyImage;

#endif
