#ifndef __WAD_H_
#define __WAD_H_

extern struct {
  int m_Entry[102][2]; // Using a struct does not match (func_800144C8)
} g_WadHeader;

#define WAD_OFFSET(x) g_WadHeader.m_Entry[x][0]
#define WAD_SIZE(x) g_WadHeader.m_Entry[x][1]

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