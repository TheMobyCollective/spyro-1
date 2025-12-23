#ifndef __PAD_H
#define __PAD_H

#include <sys/types.h>

#define PAD_L2 (1 << 0)
#define PAD_R2 (1 << 1)
#define PAD_L1 (1 << 2)
#define PAD_R1 (1 << 3)

#define PAD_TRIANGLE (1 << 4)
#define PAD_CIRCLE (1 << 5)
#define PAD_CROSS (1 << 6)
#define PAD_SQUARE (1 << 7)

#define PAD_SELECT (1 << 8)
#define PAD_START (1 << 11)

#define PAD_L3 (1 << 9)
#define PAD_R3 (1 << 10)

#define PAD_UP (1 << 12)
#define PAD_RIGHT (1 << 13)
#define PAD_DOWN (1 << 14)
#define PAD_LEFT (1 << 15)

#define PAD_DPAD (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)
#define PAD_ICONS (PAD_TRIANGLE | PAD_CIRCLE | PAD_CROSS | PAD_SQUARE)
#define PAD_SHOULDERBUTTONS (PAD_L2 | PAD_R2 | PAD_L1 | PAD_R1)
#define PAD_BUTTONS (PAD_DPAD | PAD_ICONS | PAD_SHOULDERBUTTONS)

#define HW_TYPE_NON_DUALSHOCK 0x41
#define HW_TYPE_DUALSHOCK 0x73
#define HW_TYPE_CONTRAPTION 0x53

#define CONTROLLER_TYPE_DISCONNECTED 0
#define CONTROLLER_TYPE_INVALID 1
#define CONTROLLER_TYPE_DPAD 2
#define CONTROLLER_TYPE_STICK 3

#define DEMO_MODE_NONE 0
#define DEMO_MODE_PLAY 1
#define DEMO_MODE_RECORD 2

typedef struct {
  u_char m_RightX;
  u_char m_RightY;
  u_char m_LeftX;
  u_char m_LeftY;
} GamepadSticks;

typedef struct {
  int m_Down;     // Buttons pressed this frame
  int m_Released; // Buttons released this frame
  int m_Held;     // Buttons that are currently held

  int m_Type; // CONTROLLER_TYPE_*

  int m_LeftStickMoved;   // Has the left stick moved?
  GamepadSticks m_Sticks; // Stick data

  int m_NoButtonsDown;           // No buttons are pressed
  int m_NoMovementButtonPressed; // No movement buttons are pressed

  // Stick calibration values (This is all really weird stuff)
  u_char m_CaliStickCenter[4];
  u_char m_CaliStickMin[4];
  u_char m_CaliStickMax[4];
  u_char m_CaliStickUpperMin[4];
  u_char m_CaliStickLowerMin[4];
  u_short m_CaliUpperSensitivity[4];
  u_short m_CaliLowerSensitivity[4];

  struct {
    int m_Type;             // CONTROLLER_TYPE_*
    int m_Held;             // Buttons held during this frame
    int m_Down;             // Buttons pressed during this frame
    int m_Released;         // Buttons released during this frame
    int m_LeftStickMoved;   // Has the left stick moved during this frame?
    GamepadSticks m_Sticks; // Stick data during this frame
  } m_BufferedInputs[4];    // Buffered inputs
} Gamepad;

typedef struct {
  u_char status;        // Current status of the controller, 0 means connected
  u_char size_type;     // HW_TYPE_*
  u_char inputs[2];     // Button states
  GamepadSticks sticks; // Stick data
  u_char padding[24];   // Padding, some controllers provide more data
} PadBuffer;

// static_assert(sizeof(Gamepad) == 0xa4, "Gamepad is the wrong size");

extern Gamepad g_Pad;      // Current gamepad state
extern Gamepad D_800776D8; // Backup gamepad state

extern u_char D_80075944; // Some flag that causes copying
extern u_char g_PadMutex; // Controller update mutex

extern int g_ActEnabled;   // Is vibration enabled in settings
extern int g_ActAvailable; // Is vibration available

extern int D_80075730; // Have to set controller mode to analog

extern int D_800757D0; // Custom (dragon) vibration timer
extern int D_8007584C; // Custom vibration amount

extern int D_80075904; // Normal vibration timer
extern int D_80075764; // Electric shock vibration timer

extern int g_DemoMode;  // Are we in DEMO mode? (0 = no, 1 = play, 2 = record)
extern int D_80075784;  // Extra VSync for DEMO mode
extern int *D_8007585C; // Pointer to the current demo input

extern PadBuffer g_PadBuffer; // Buffer that PSYQ writes out pad state into
extern PadBuffer
    g_PadBufferSecondController; // Backup buffer while inputs are disabled

/// @brief Copies the gamepad over, then resets the input gamepad
void func_80053708(Gamepad *in, Gamepad *out);

/// @brief Play (or record) demos
void PadDemoUpdate(void);

/// @brief VSYNC callback
void PadVSync(void);

/// @brief Resets the gamepad's calibration values
void PadCaliReset(Gamepad *pad);

/// @brief Initializes the gamepad and it's calibration deadzone values
int PadCaliInit(Gamepad *pad);

#endif