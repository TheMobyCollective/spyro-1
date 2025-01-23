#ifndef __CD_H
#define __CD_H

#include <sys/types.h>

#include <libcd.h>

/// @brief Maximum read time for the current disc read
extern int D_800756E0;

/// @brief Disc read timer
extern int D_8007588C;

typedef struct {
  int m_WadSector;
  int m_Size;
  CdlLOC m_ReadLoc;
  void *m_OutBuf;
  int m_0x10; // Unused space
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  volatile int m_IsReading;
} CdState;

extern CdState g_CdState;

// CDReadDone name from S3 printf

// Function that checks if the read time is not exceeded, reinitiates if it is
void CDLoadTime(void);

// (Official name, from S3 printf)
// CD Read callback, used for unsetting the reading state and retrying on error
void CDReadDone(u_char intr, u_char *result);

// Function for reading data from disc synchronously
void CDLoadSync(int sector, void *buf, int size, int offset, int maxTime);

// Function for reading data from disc asynchronously
void CDLoadAsync(int sector, void *buf, int size, int offset, int maxTime);

#endif // !__CD_H