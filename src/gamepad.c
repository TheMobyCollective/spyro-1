#include "gamepad.h"
#include "common.h"
#include <libpad.h>

#include "cd.h"
#include "memory.h"
#include "music.h"

extern int D_800758E0; // Is pad intialized

extern u_char D_8006FCCC[6]; // Act alignment
extern u_char D_80075800[2]; // Buffer that PSYQ reads our actuator state from

// Resets a gamepad
void PadReset(Gamepad *pad) {
  int i;

  pad->m_Held = 0;
  pad->m_Down = 0;
  pad->m_Released = 0;

  *((int *)&pad->m_Sticks) = 0x7F7F7F7F;

  pad->m_NoButtonsDown = 1;
  pad->m_NoMovementButtonPressed = 1;

  for (i = 0; i < 4; i++) {
    pad->m_BufferedInputs[i].m_Type = pad->m_Type;
    pad->m_BufferedInputs[i].m_Held = 0;
    pad->m_BufferedInputs[i].m_Down = 0;
    pad->m_BufferedInputs[i].m_Released = 0;
    *((u_int *)&pad->m_BufferedInputs[i].m_Sticks) = 0x7F7F7F7F;
  }
}

// Temporarily copies the gamepad, then resets the input gamepad
// Used to disable player input, for example (horrible)
void func_80053708(Gamepad *oldPad, Gamepad *newPad) {
  D_80075944 = 1 - D_80075944; // Flag for if we've copied the gamepad

  Memcpy(newPad, oldPad, sizeof(Gamepad)); // Copy the gamepad

  PadReset(oldPad); // Reset the old gamepad
}

// Resets the gamepad's calibration values
void PadCaliReset(Gamepad *pad) {
  int i;

  for (i = 0; i < 4; i++) {
    pad->m_CaliStickMin[i] = 0;
    pad->m_CaliStickCenter[i] = 127;
    pad->m_CaliStickMax[i] = 255;
  }
}

// Initializes the gamepad and it's calibration deadzone values
int PadCaliInit(Gamepad *pad) {
  int i, t;
  int res = 1;

  // WTF? This code is HORRIBLE!
  // The if statement causes PadCaliReset to always be executed, because those
  // constants will never match those values And everytime this function is
  // executed, PadCaliReset is always executed right before!
  for (i = 0; i < 4; i++) {
    if (!(pad->m_CaliStickCenter[i] + 48 < pad->m_CaliStickMax[i] &&
          pad->m_CaliStickMin[i] < pad->m_CaliStickCenter[i] - 48)) {
      PadCaliReset(pad); // Reinitializes the pad calibrations
      res = 0;
      break;
    }
  }

  for (i = 0; i < 4; i++) {
    pad->m_CaliStickUpperMin[i] = pad->m_CaliStickCenter[i] + 48;
    pad->m_CaliStickLowerMin[i] = pad->m_CaliStickCenter[i] - 48;
    pad->m_CaliUpperSensitivity[i] =
        0x4000 / (pad->m_CaliStickMax[i] - pad->m_CaliStickUpperMin[i]);
    pad->m_CaliLowerSensitivity[i] =
        0x3f80 / (pad->m_CaliStickLowerMin[i] - pad->m_CaliStickMin[i]);
  }

  pad->m_Down = 0;
  pad->m_Released = 0;
  pad->m_Held = 0;
  pad->m_NoButtonsDown = 1;
  pad->m_NoMovementButtonPressed = 1;

  for (i = 0; i < 4; i++) {
    ((u_char *)&pad->m_Sticks)[i] = 127;
  }

  for (t = 0; t < 4; t++) {
    pad->m_BufferedInputs[t].m_Down = 0;
    pad->m_BufferedInputs[t].m_Released = 0;
    pad->m_BufferedInputs[t].m_Held = 0;
    for (i = 0; i < 4; i++) {
      ((u_char *)&pad->m_BufferedInputs[t].m_Sticks)[i] = 127;
    }
  }

  return res;
}

// Modify the stick values based on the calibration values
void PadApplyCali(GamepadSticks *sticks, Gamepad *pad) {
  u_char *stickValues;
  int calibratedValue;
  int i;

  stickValues = (u_char *)sticks; // Treat sticks as an array of 4 values

  for (i = 0; i < 4; i++) {
    if (stickValues[i] >
        pad->m_CaliStickUpperMin[i]) { // Over the high deadzone
      calibratedValue = (((stickValues[i] - pad->m_CaliStickUpperMin[i]) *
                          pad->m_CaliUpperSensitivity[i]) >>
                         7) +
                        127;
      if (calibratedValue > 255) {
        stickValues[i] = 255;
      } else {
        stickValues[i] = calibratedValue;
      }
    } else if (stickValues[i] <
               pad->m_CaliStickLowerMin[i]) { // Over the low deadzone
      calibratedValue = 127 - (((pad->m_CaliStickLowerMin[i] - stickValues[i]) *
                                pad->m_CaliLowerSensitivity[i]) >>
                               7);
      if (calibratedValue < 0) {
        stickValues[i] = 0;
      } else {
        stickValues[i] = calibratedValue;
      }
    } else {
      stickValues[i] = 127;
    }
  }
}

// Play (or record) demos
void PadDemoUpdate(void) {
  int demoInput;
  int i;

  // Are we in recording mode?
  if (g_DemoMode == DEMO_MODE_RECORD) {
    // Writes the demo recording data

    // Get the inputs
    demoInput = ~(g_PadBuffer.inputs[0] << 8 | g_PadBuffer.inputs[1]);

    // Update the sticks
    *(int *)&g_Pad.m_Sticks = *(int *)&g_PadBuffer.sticks;
    PadApplyCali(&g_Pad.m_Sticks, &g_Pad);

    // Combine into the demo data
    demoInput &= 0xFFFF;
    demoInput |= (g_Pad.m_Sticks.m_LeftX << 0x10);
    demoInput |= (g_Pad.m_Sticks.m_LeftY << 0x18);

    // Write the data and increment the pointer
    *(D_8007585C++) = demoInput;
  } else { // Always DEMO_MODE_PLAY since this function is only called during
           // demos

    // Reads the current demo recording data, increments the pointer
    demoInput = *(D_8007585C++);
    g_Pad.m_Sticks.m_RightX = 127;
    g_Pad.m_Sticks.m_RightY = 127;
    g_Pad.m_Sticks.m_LeftX = (u_char)(demoInput >> 0x10);
    g_Pad.m_Sticks.m_LeftY = (u_char)(demoInput >> 0x18);
  }

  demoInput &= 0xFFFF;

  g_Pad.m_Down = ~g_Pad.m_Held & demoInput;
  g_Pad.m_Released = g_Pad.m_Held & ~demoInput;
  g_Pad.m_Held = demoInput;

  g_Pad.m_Type = CONTROLLER_TYPE_STICK; // Type is always type stick

  // Has the stick moved this frame?
  if ((*(int *)&g_Pad.m_Sticks & 0xFFFF0000) != 0x7F7F0000) {
    g_Pad.m_LeftStickMoved = 1;
  } else {
    g_Pad.m_LeftStickMoved = 0;
  }

  // We don't use the buffered input system for demos
  for (i = 0; i < 4; i++) {
    g_Pad.m_BufferedInputs[i].m_Held = g_Pad.m_Held;
    g_Pad.m_BufferedInputs[i].m_Down = g_Pad.m_Down;
    g_Pad.m_BufferedInputs[i].m_Released = g_Pad.m_Released;
    g_Pad.m_BufferedInputs[i].m_Type = g_Pad.m_Type;
    *(int *)&g_Pad.m_BufferedInputs[i].m_Sticks = *(int *)&g_Pad.m_Sticks;
    g_Pad.m_BufferedInputs[i].m_LeftStickMoved = g_Pad.m_LeftStickMoved;
  }

  g_Pad.m_NoButtonsDown = 1;
  g_Pad.m_NoMovementButtonPressed = 1;

  if (g_Pad.m_Held & PAD_DPAD ||
      (*(int *)&g_Pad.m_Sticks & 0xFFFF0000) != 0x7F7F0000) {
    g_Pad.m_NoMovementButtonPressed = 0;
  }

  if (g_Pad.m_NoMovementButtonPressed == 0 || g_Pad.m_Held & PAD_BUTTONS) {
    g_Pad.m_NoButtonsDown = 0;
  }

  // No lag frames in demo recordings
  g_UnprocessedFrames = 2;
}

// VSYNC callback, updates some CD and music stuff
// But mainly for updating the gamepad with the current pad state
// also contains logic for initializing and updating dualshock controllers
void PadVSync(void) {
  GamepadSticks gamepadSticks;
  int padState;
  int controllerType;
  int releasedButtons;
  int updatedInputs;
  int inputState;

  D_800758C8 += 1; // Increment the level ticks

  // Is there a CD max time set?
  if (g_CDMaxReadTime) {
    // Increment the read time
    g_CDReadTime += 1;
  }

  // Check if we're in DEMO mode, if we are, just return
  if (g_DemoMode)
    return;

  padState = PadGetState(0);

  if (padState == PadStateFindPad) {
    D_800758E0 = 0; // Set pad uninitialized
  }

  // Check if we've initialized the gamepad yet
  if (!D_800758E0) {
    // We're going to initialize the actuator buffer
    PadSetAct(0, D_80075800, 2);

    // PadStateFindCTP1 Means the controller doesn't support actuators, if we're
    // in PadStateStable however, we want to set the alignment buffer which
    // specifies how the actuator buffer is laid out
    if (padState == PadStateFindCTP1 ||
        (padState == PadStateStable && PadSetActAlign(0, D_8006FCCC))) {
      D_800758E0 = 1;
    }
  }

  // For sticks
  if (PadInfoMode(0, InfoModeCurExID, 0) != 0) {

    // Do we have to set the mode?
    if (D_80075730) {

      // Set the mode (turns on the LED and enables analog controls)
      if (PadSetMainMode(0, 1, 0) != 0) {
        D_80075730 = 0; // Unset the flag
      }
    }

    // The controller has actuators, so enable the feature
    g_ActAvailable = 1;

  } else {

    // The controller doesn't have actuators
    g_ActAvailable = 0;
  }

  // If vibration is disabled in the options menu or not available at all
  if (!g_ActEnabled || !g_ActAvailable) {
    // Reset all the vibration timers
    D_80075904 = 0;
    D_80075764 = 0;
    D_800757D0 = 0;
    D_8007584C = 0;
  }

  if (D_80075904) { // Normal
    D_80075800[0] = 1;
    D_80075800[1] = 120;
  } else if (D_80075764) { // Electric shock vibration
    D_80075800[0] = 1;
    D_80075800[1] = 0;
  } else if (D_800757D0) { // Custom vibration amount (i.e. dragon)
    D_80075800[0] = 0;
    D_80075800[1] = (char)D_8007584C;
  } else { // No vibration
    D_80075800[0] = 0;
    D_80075800[1] = 0;
  }

  // Decrement the timers
  if (--D_80075904 < 0) { // Normal vibration
    D_80075904 = 0;
  }

  if (--D_80075764 < 0) { // Electric shock vibration
    D_80075764 = 0;
  }

  if (--D_800757D0 < 0) { // Custom vibration
    D_800757D0 = 0;
  }

  // Check if the controller is connected
  if (g_PadBuffer.status != 0) {
    D_80075730 = 1; // Has been disconnected, we have to set the mode of the
                    // controller again
    controllerType = CONTROLLER_TYPE_DISCONNECTED; // Disconnected
  } else {

    // Set the controller type
    switch (g_PadBuffer.size_type) {
    case HW_TYPE_NON_DUALSHOCK:
      controllerType = CONTROLLER_TYPE_DPAD; // Non-dualshock controller
      break;

    case HW_TYPE_DUALSHOCK:
    case HW_TYPE_CONTRAPTION: // SCPH-1100
      if (g_Pad.m_Type !=
          CONTROLLER_TYPE_STICK) { // If it wasn't stick before, we have to
                                   // initialize some things
        PadCaliReset(&g_Pad);
        *(int *)&g_Pad.m_CaliStickCenter = *(int *)&g_PadBuffer.sticks;
        PadCaliInit(&g_Pad);
      }

      controllerType = CONTROLLER_TYPE_STICK;
      break;

    default:
      controllerType = CONTROLLER_TYPE_INVALID; // Unsupported
      break;
    }
  }

  g_Pad.m_LeftStickMoved = 0;

  if (controllerType >
      CONTROLLER_TYPE_INVALID) { // Check if the controller isn't disconnected
                                 // or unsupported

    inputState = ~(g_PadBuffer.inputs[0] << 8 | g_PadBuffer.inputs[1]); // Lol

    // Is this a controller with sticks?
    if (controllerType == CONTROLLER_TYPE_STICK) {
#ifndef MODERN_COMPILER
      // Update the stick data
      *(int *)&gamepadSticks = *(int *)&g_PadBuffer.sticks;
#else
      gamepadSticks.m_LeftX = g_PadBuffer.sticks.m_LeftX;
      gamepadSticks.m_LeftY = g_PadBuffer.sticks.m_LeftY;
      gamepadSticks.m_RightX = g_PadBuffer.sticks.m_RightX;
      gamepadSticks.m_RightY = g_PadBuffer.sticks.m_RightY;
#endif

      PadApplyCali(&gamepadSticks, &g_Pad);

      if (g_PadBuffer.size_type ==
          HW_TYPE_CONTRAPTION) { // The contraption (SCPH-1110)
        updatedInputs = inputState &
                        ~(PAD_R2 | PAD_L1 | PAD_R1 | PAD_TRIANGLE | PAD_SQUARE);

        // This literally remaps the L1 and R1 buttons to Square and triangle,
        // and vice versa
        if (inputState & PAD_SQUARE) {
          updatedInputs |= PAD_R2;
        }

        if (inputState & PAD_TRIANGLE) {
          updatedInputs |= PAD_R1;
        }

        if (inputState & PAD_R1) {
          updatedInputs |= PAD_TRIANGLE;
        }

        // This one doesn't make much sense
        if (inputState & PAD_R2) {
          updatedInputs |= PAD_L1;
        }

        if (inputState & PAD_L1) {
          updatedInputs |= PAD_SQUARE;
        }

        inputState = updatedInputs;
      }

      // This sets the left/right/up/down based on the stick if the DPAD hasn't
      // been used
      if (!(inputState & PAD_DPAD)) {
        if (gamepadSticks.m_LeftX >= 193) {
          inputState |= PAD_RIGHT;
        } else if (gamepadSticks.m_LeftX < 64) {
          inputState |= PAD_LEFT;
        }
        if (gamepadSticks.m_LeftY >= 193) {
          inputState |= PAD_DOWN;
        } else if (gamepadSticks.m_LeftY < 64) {
          inputState |= PAD_UP;
        }

        if ((gamepadSticks.m_LeftX != 127) || (gamepadSticks.m_LeftY != 127)) {
          g_Pad.m_LeftStickMoved = 1;
        }
      }
    } else {
      // No sticks, center it
      *(int *)&gamepadSticks = 0x7F7F7F7F;
    }

    updatedInputs = ~g_Pad.m_Held & inputState;
    releasedButtons = g_Pad.m_Held & ~inputState;

    // Can we update the controller?
    if (g_PadMutex) { // Sorta like a mutex so that the controller isn't updated
                      // during the update logic

      g_Pad.m_Type = controllerType;
      g_Pad.m_Held = inputState;

      // If we've missed a frame already
      if (g_UnprocessedFrames != 0) {
        // We OR it instead
        g_Pad.m_Down |= updatedInputs;
        g_Pad.m_Released |= releasedButtons;
      } else {
        // We haven't missed a frame yet, overwrite it entirely
        g_Pad.m_Down = updatedInputs;
        g_Pad.m_Released = releasedButtons;
        g_Pad.m_NoButtonsDown = 1;
        g_Pad.m_NoMovementButtonPressed = 1;
      }

#ifndef MODERN_COMPILER
      // Update the stick data
      *(int *)&g_Pad.m_Sticks = *(int *)&gamepadSticks;
#else
      g_Pad.m_Sticks.m_LeftX = gamepadSticks.m_LeftX;
      g_Pad.m_Sticks.m_LeftY = gamepadSticks.m_LeftY;
      g_Pad.m_Sticks.m_RightX = gamepadSticks.m_RightX;
      g_Pad.m_Sticks.m_RightY = gamepadSticks.m_RightY;
#endif

      if (g_Pad.m_NoButtonsDown != 0) {

        // Check if we used any movement buttons
        if (g_Pad.m_Held & PAD_DPAD ||
            controllerType == CONTROLLER_TYPE_STICK &&
                (gamepadSticks.m_LeftX != 127 ||
                 gamepadSticks.m_LeftY != 127)) {
          g_Pad.m_NoMovementButtonPressed = 0;
        }

        // This just checks if we've used any buttons at all
        if (!g_Pad.m_NoMovementButtonPressed || g_Pad.m_Held & PAD_BUTTONS) {
          g_Pad.m_NoButtonsDown = 0;
        }
      }

    } else if (g_Pad.m_Type <=
               CONTROLLER_TYPE_INVALID) { // If we were disconnected or invalid
                                          // before
      // Update it, even if we're currently waiting
      g_Pad.m_Type = controllerType;
    }

    // If we're less than 4 frames late, buffer the inputs
    if (g_UnprocessedFrames < 4) {
      // Buffered inputs are only used Spyro, so that your inputs
      // can't be dropped even if the game is running at a low framerate
      g_Pad.m_BufferedInputs[g_UnprocessedFrames].m_Type = controllerType;
      g_Pad.m_BufferedInputs[g_UnprocessedFrames].m_Held = inputState;
      g_Pad.m_BufferedInputs[g_UnprocessedFrames].m_Down = updatedInputs;
      g_Pad.m_BufferedInputs[g_UnprocessedFrames].m_Released = releasedButtons;
      g_Pad.m_BufferedInputs[g_UnprocessedFrames].m_LeftStickMoved =
          g_Pad.m_LeftStickMoved;
      *(int *)&g_Pad.m_BufferedInputs[g_UnprocessedFrames].m_Sticks =
          *(int *)&g_Pad.m_Sticks;
    }
  } else if (g_PadMutex) { // Controller mutex
    // Disconnected or invalid
    g_Pad.m_Type = controllerType;
  }

  // Increment the missed frame counter
  g_UnprocessedFrames += 1;
}
