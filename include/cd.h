#ifndef __CD_H
#define __CD_H

#include <sys/types.h>

#include <libcd.h>

/// @brief Maximum read time for the current disc read
extern int g_CDMaxReadTime;

/// @brief Disc read timer
extern int g_CDReadTime;

typedef struct {
  int m_WadSector;
  int m_Size;
  CdlLOC m_ReadLoc;
  void *m_OutBuf;

  // Unused in Final, used in Prototypes and Demos (see CDGetFileSector)
  CdlFILE m_FileInfo;

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
