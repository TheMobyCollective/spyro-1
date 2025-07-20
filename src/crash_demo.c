#include "common.h"

#include <sys/types.h>

#include <libgte.h>

#include <libapi.h>
#include <libcd.h>
#include <libetc.h>
#include <libgpu.h>
#include <libpad.h>
#include <stdio.h>

// Resets a bunch of PSYQ stuff
static void func_8002BA68(void) {
  SetDispMask(0);
  CdInit();
  CdReadCallback(nullptr);
  VSyncCallback(nullptr);
  PadStopCom();
  ResetGraph(3);
  StopCallback();
}

// Launches the Crash 3 Demo
void CrashDemoLaunch(void) {
  // Shut everything down
  printf("Shutting Down\n");
  func_8002BA68();

  // Reinitializes the ISO filesystem
  _96_remove();
  _96_init();

  // Then launch the demo executable
  printf("Launching Crash Demo\n");
  LoadExec("cdrom:\\S0\\CRASH.EXE;1", // Executable name
           0x801fff00,                // Stack area starting address
           0                          // Number of bytes in stack area
  );
}