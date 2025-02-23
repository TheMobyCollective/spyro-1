#ifndef __WAD_H_
#define __WAD_H_

typedef struct {
  int m_Offset;
  int m_Length;
} OffsetLength;

extern struct {
  OffsetLength m_UniversalLogo;
  OffsetLength m_wad1;
  OffsetLength m_TitleScreenOverlay;
  OffsetLength m_TitleScreen[4];
  OffsetLength m_wad7;
  OffsetLength m_wad8;
  OffsetLength m_wad9;
  OffsetLength m_LevelEntry[92];
} g_WadHeader;

#define WAD_OFFSET(x) g_WadHeader.x.m_Offset
#define WAD_SIZE(x) g_WadHeader.x.m_Length

typedef struct {
  int m_VramSramOffset;
  int m_VramSramSize;
  int m_SceneOffset;
  int m_SceneSize;
  int m_ModelDataOffset;
  int m_ModelDataSize;
  int m_LayoutOffset;
  int m_LayoutSize;
  struct {
    int offset, size;
  } m_Dragons[6];
  int m_ModelOffsets[64];
  short m_ModelIndices[64];
} LevelHeader;

LevelHeader g_LevelHeader;

#endif