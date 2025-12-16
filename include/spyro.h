#ifndef __SPYRO_H
#define __SPYRO_H

#include <sys/types.h>

#include <libgte.h>
#include <matrix.h>
#include <moby.h>
#include <vector.h>

// This is literally the largest structure in the game
// a massive pain to document and figure out

/// @brief Body animation transition types
/// Used by UpdateBodyAnimationState to control animation blending
typedef enum {
  TRANSITION_NONE = 0,            // Normal playback, no transition
  TRANSITION_SLOW_BLEND = 1,      // Slow blend from frame 0 (+2/tick)
  TRANSITION_SLOW_AT_END = 2,     // Slow blend at animation end
  TRANSITION_SPECIAL = 3,         // Special transition (may play sound)
  TRANSITION_HOLD_END = 4,        // Hold at end frame, manual control
  TRANSITION_FAST_BLEND = 5,      // Fast blend (+4/tick)
  TRANSITION_SLOW_FROM_START = 6, // Slow blend from start frame
  TRANSITION_FAST_FROM_ZERO = 8,  // Fast blend from frame 0 (+2 immediate)
  TRANSITION_SPECIAL_ALT = 10     // Same behavior as TRANSITION_SPECIAL
} BodyTransitionType;

typedef struct {
  int m_Speed;
  int m_RotZ, m_RotY, m_RotX;
} SpyroSpeedAngle;

typedef struct { // Needed to match atleast one place
  SpyroSpeedAngle m_TargetSpeedAngle;
  int m_SlopeGravityZ; // Set by ApplySlopeGravity but never read (unused)
  Vector3D unk_0xdc;
  Vector3D unk_0xe8; // Probably some kind of momentum, not sure
  Vector3D m_Acceleration;
  Vector3D m_Velocity;
  Vector3D m_TrueVelocity; // After collision, how much of the velocity is left
  SpyroSpeedAngle m_SpeedAngle;
  int m_TrueSpeed;              // The size of m_TrueVelocity
  Vector3D m_CollisionMovement; // How much the triangle under spyro moved
  int unk_0x138;
  int unk_0x13c;
  int unk_0x140;
  int unk_0x144;
  int unk_0x148;
  int m_gravity;
} SpyroPhysics;

typedef struct {
  Vector3D m_Position;

  /// @brief The rotation of the body
  Vector3D8 m_bodyRotation;

  /// @brief The rotation of the head
  Vector3D8 m_headRotation;

  /// @brief The rotation of the tail
  Vector3D8 m_tailRotation;

  Vector3D8 unk_0x15; // No idea, no XREFs

  /// @brief The animation the body is playing
  u_char m_bodyAnimation;

  /// @brief The next animation the body will play, used for interpolation
  u_char m_nextBodyAnimation;

  /// @brief The animation the head is playing
  u_char m_headAnimation;

  /// @brief The next animation the head will play, used for interpolation
  u_char m_nextHeadAnimation;

  /// @brief The animation the tail is playing
  u_char m_tailAnimation;

  /// @brief The next animation the tail will play, used for interpolation
  u_char m_nextTailAnimation;

  /// @brief The current frame of the body
  u_char m_bodyAnimationFrame;

  /// @brief The next frame of the body, used for interpolation
  u_char m_nextBodyAnimationFrame;

  /// @brief The current frame of the head
  u_char m_headAnimationFrame;

  /// @brief The next frame of the head, used for interpolation
  u_char m_nextHeadAnimationFrame;

  /// @brief The current frame of the tail
  u_char m_tailAnimationFrame;

  /// @brief The next frame of the tail, used for interpolation
  u_char m_nextTailAnimationFrame;

  // The progress of the current frame used for interpolation,
  // 0 - 4096 (0.0 - 1.0)

  /// @brief The progress of the body frame
  u_char m_bodyFrameProgress;

  /// @brief The progress of the head frame
  u_char m_headFrameProgress;

  /// @brief The progress of the tail frame
  u_char m_tailFrameProgress;

  /// @brief Subtracted from Spyro's Z depth, unsigned though (usually 4)
  u_char m_sortingDepth;

  /// @brief Interpolated with vertex colours, used by Fairy Kiss effect
  struct {
    u_char m_red;
    u_char m_green;
    u_char m_blue;
    u_char m_interpolation; // 0 - 255 (0.0 - 1.0)
  } m_colorFilter;

  /// @brief The damage that's been applied to Spyro, similar to Mobys
  u_int m_DamageFlags; // TODO: enum / defines

  /// @brief The distance to the floor
  int m_FloorDistance;

  /// @brief Spyro's rotation matrix
  MATRIX m_RotationMatrix;

  /// @brief Current body animation transition type (0=normal, 1-8=various blends)
  int m_bodyTransitionType;

  int m_bodyAnimationSpeed;

  /// @brief Previous animation state, used as "from" in transition lookup table
  int m_lastAnimationState;
  int unk_0x60;
  int m_headAnimationSpeed;
  int unk_0x68;
  int unk_0x6C;
  int m_tailAnimationSpeed;
  int unk_0x74;
  int m_State; // TODO: enum / defines
  int m_walkingState;
  int m_idleTimer;
  int unk_0x84;
  int m_touchingMoby;
  Vector3D unk_0x8c;
  int m_floorIdleTime; // 0x98
  int m_airTime;       // 0x9c
  int m_surfaceBelowSpyro;
  Vector3D m_floorPositonOnSlope;
  int m_slopeAngle;
  int m_againstWall;
  Vector3D m_wallAgainstSpyro;
  int m_onEdge;
  SpyroPhysics m_Physics;
  int m_onSlope;
  int m_isGliding;
  int m_highestFlightPoint;
  int unk_0x15c;
  int m_invulverabilityTimer;
  int m_health;
  int m_drowningOffset;
  int m_touchingSurface;
  int unk_0x170;
  int m_damagingFloorIndex;
  int *m_damagingFloorFlags;
  Vector3D unk_0x17c;
  Vector3D m_KnockbackDirection; // Direction vector applied to acceleration on knockback
  int unk_0x194;      // Used to force spyro to flame in cutscenes
  int unk_0x198;
  int unk_0x19c;
  int unk_0x1a0;
  Vector3D m_HeadLookTarget; // Target angles for head look-at (set by SetSpyroHeadLookTarget, consumed by func_80049880)
  int unk_0x1b0;
  int unk_0x1b4;
  int unk_0x1b8;
  int unk_0x1bc;
  int unk_0x1c0;
  int unk_0x1c4;
  MATRIX unk_0x1c8;
  int m_seperateTailAnimation; // Whether the tail is animated seperately from
                               // the body, otherwise it copies the body
  int m_flameableFrames; // How many frames have we been able to flame? Not used
                         // for anything, isn't reset either, useless
  int m_noGamepadUpdateFrames; // How many frames the gamepad can't be updated
                               // for
  int unk_0x1f4;               // Some kind of cutscene flags
  Vector3D m_portalEndPos;     // Not 100% sure
  Vector3D8 m_portalAngle;     // The angle of the portal
  u_char unk_0x207;            // Padding
  Vector3D unk_0x208;
  int unk_0x214;
  int m_fallingState; // Not sure
  Vector3D *unk_0x21c;
  int unk_0x220;

  // Used for the cannon, and whirlwinds, camera related
  Moby *m_mobyInUseBySpyro;
  u_char unk_0x228[24]; // Fuck knows, no XREFs, considering the rest of this
                        // section it's probably moby related though
  PathData *unk_0x240;
  int unk_0x244;       // Path moby related
  int unk_0x248;       // Path moby related
  int m_flyingAbility; // Used in flying levels and gnasty's loot
  int m_doingSupercharge;
  int unk_0x254;
  int unk_0x258;
  int unk_0x25c;
  int unk_0x260; // No XREFS
  int unk_0x264;
  int unk_0x268;
  int unk_0x26c; // No XREFS
  int unk_0x270; // No XREFS
  int m_CollisionTriangleIndex;
  struct {
    Vector3D points[3];
  } m_collisionTriangleUnpacked;
  int *m_floorFlagsPointer;
  u_char m_damageSoundChannel;
  u_char m_chargeSoundChannel;
  short unk_0x2a2; // Probably padding
} Spyro;

// static_assert(sizeof(Spyro) == 0x2a4, "Incorrect Spyro size");

extern Spyro g_Spyro;
extern int D_8007592C;        // Is spyro in look mode
extern u_char D_8006C588[48]; // Maps Spyro's state to camera states

extern int D_8007580C; // Health before entering flight level

/// @brief: Resets Spyro
void func_8004AC24(int pKeepPosition);

/// @brief: Forces state to and resets animation
void func_8003FDC8(int pNewState);

void func_8004A7EC(void);

void func_8004A200(void);

void func_8004AA0C(void);

/// @brief Handles the state transition for Spyro's body animation
void func_8003CCE4(void);

/// @brief Changes Spyro's state
void func_8003EA68(int pNewState);

#endif // !__SPYRO_H