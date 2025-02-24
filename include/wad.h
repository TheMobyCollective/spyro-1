#ifndef __WAD_H_
#define __WAD_H_

typedef struct {
  int m_Offset;
  int m_Length;
} OffsetLength;

// TODO: PETE.WAD
extern struct {
  OffsetLength m_UniversalLogo;
  OffsetLength m_wad1;

  OffsetLength m_TitleScreenOverlay;
  OffsetLength m_TitleScreenData;

  OffsetLength m_IntroData;
  OffsetLength m_OutroData;
  OffsetLength m_Outro2Data;

  OffsetLength m_wad8;
  OffsetLength m_wad9;

  struct {
    OffsetLength m_Overlay;
    OffsetLength m_Data;
  } m_LevelEntry[36]; // Last entry is empty

  OffsetLength m_CreditsOverlay;

  OffsetLength m_Credits1Data[10];
  OffsetLength m_Credits2Data[10];

} g_WadHeader;

typedef struct {
  int m_VramSramOffset;
  int m_VramSramSize;
  int m_SceneOffset;
  int m_SceneSize;
  int m_ModelDataOffset;
  int m_ModelDataSize;
  int m_LayoutOffset;
  int m_LayoutSize;
  OffsetLength m_Dragons[6];
  int m_ModelOffsets[64];
  short m_ModelIndices[64];
} LevelHeader;

LevelHeader g_LevelHeader;

#endif