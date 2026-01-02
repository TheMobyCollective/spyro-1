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

/// @brief Control/override flags for Spyro's behavior during scripted sequences
/// Used by m_ControlFlags to modify physics, camera, and surface handling
typedef enum {
  CTRL_CAMERA_0200 = 0x0200,        // Camera behavior modifier (unknown)
  CTRL_CAMERA_0400 = 0x0400,        // Camera behavior modifier (unknown)
  CTRL_SKIP_CAMERA_CENTER = 0x1000, // Skip camera auto-centering on Spyro
  CTRL_SKIP_SURFACE_CHECK = 0x4000, // Skip surface interaction handling
  CTRL_CAMERA_8000 = 0x8000,        // Camera behavior modifier (unknown)
  CTRL_CAMERA_10000 = 0x10000,      // Camera behavior modifier (unknown)
} ControlFlags;

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
  int m_TurnMomentum; // -6 (hard left) to +6 (hard right)
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

  /// @brief Current body animation transition type (0=normal, 1-8=various
  /// blends)
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
  Vector3D m_previousPosition; // 0x8c - Position before movement update
  int m_floorIdleTime;         // 0x98
  int m_airTime;               // 0x9c
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
  /**
   * Tracks proximity state to special surfaces when Spyro is above but not
   * directly on them.
   *
   * - Reset to 0 each frame in UpdateSpyroPhysicsAndSurfaces before surface
   * checks
   * - Set to 1 by ApplySpecialSurfaceEffects when Spyro is above a type-0
   * damage floor (more than 512 units above) but not close enough for direct
   * contact
   * - Checked by physics (func_80043FE4) to modify behavior when hovering
   *   above special surfaces
   */
  int m_SurfaceProximityState;
  int m_damagingFloorIndex;
  int *m_damagingFloorFlags;
  Vector3D unk_0x17c;
  Vector3D m_KnockbackDirection; // Direction vector applied to acceleration on
                                 // knockback
  int unk_0x194;                 // Used to force spyro to flame in cutscenes
  int unk_0x198;
  int unk_0x19c;
  int unk_0x1a0;
  Vector3D
      m_HeadLookTarget; // Target angles for head look-at (set by
                        // SetSpyroHeadLookTarget, consumed by func_80049880)
  int unk_0x1b0;
  int unk_0x1b4;
  int unk_0x1b8;
  int unk_0x1bc;
  int unk_0x1c0;
  int unk_0x1c4;
  MATRIX
  m_headRotationMatrix; // 0x1c8 - Combined body+head rotation for rendering
  int m_seperateTailAnimation; // Whether the tail is animated seperately from
                               // the body, otherwise it copies the body
  int m_flameableFrames; // How many frames have we been able to flame? Not used
                         // for anything, isn't reset either, useless
  int m_noGamepadUpdateFrames; // How many frames the gamepad can't be updated
                               // for
  /**
   * Bitfield of ControlFlags that modify Spyro's behavior during scripted
   * sequences, cutscenes, and special traversal states.
   * Cleared to 0 when exiting cutscene/scripted playback.
   * @see ControlFlags
   */
  int m_ControlFlags;
  Vector3D m_portalEndPos; // Not 100% sure
  Vector3D8 m_portalAngle; // The angle of the portal
  u_char unk_0x207;        // Padding
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
  int m_RotXAccumulator; // Spring-damper accumulator for smooth RotX
                         // transitions
  int m_RotYAccumulator; // Spring-damper accumulator for smooth RotY
                         // transitions
  int unk_0x260;         // No XREFS
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

/** @brief Spyro visibility flag. 0 = visible, 1 = hidden */
extern int g_IsSpyroHidden;

extern int D_8007592C;        // Is spyro in look mode
extern u_char D_8006C588[48]; // Maps Spyro's state to camera states

extern int D_8007580C; // Health before entering flight level

typedef struct {
  int unk_00;
  int unk_04;
  int unk_08;
  int unk_0c;
  int unk_10;
  int unk_14;
  int unk_18;
  int unk_1c;
  int unk_20;
  int unk_24;
  int unk_28;
  int unk_2c;
  int unk_30;
  int unk_34;
  int unk_38;
  int unk_3c;
  int unk_40;
  int unk_44;
  int unk_48;
  int unk_4c;
  int unk_50;
  int unk_54;
  int unk_58;
  int unk_5c;
  int unk_60;
  int unk_64;
  int unk_68;
  int unk_6c;
  int unk_70;
  int unk_74;
  int unk_78;
  int unk_7c;
  int unk_80;
  int unk_84;
  int unk_88;
  int unk_8c;
  int unk_90;
  int unk_94;

  /** @brief Flame breath active flag. 1 = active, 0 = inactive */
  u_char m_IsFlameActive;

  u_char unk_99[3];
  int unk_9c;
  int m_FairyKissTimer;
  int unk_a4;
  int unk_a8;
  int unk_ac;
  int unk_b0;
  int unk_b4;
  int unk_b8;
  int unk_bc;
  int unk_c0;
  int unk_c4;
  int unk_c8;
  int unk_cc;
  int unk_d0;
  int unk_d4;
  int unk_d8;
  int unk_dc;
  int unk_e0;
  int unk_e4;
  int unk_e8;
  int unk_ec;
  int unk_f0;
  int unk_f4;
  int unk_f8;
  int unk_fc;
  int unk_100;
  int unk_104;
  int unk_108;
  int unk_10c;
  int unk_110;
  int unk_114;
  int unk_118;
  int unk_11c;
  int unk_120;
  int unk_124;
  int unk_128;
  int unk_12c;
  int unk_130;
  int unk_134;
} SpyroFlame;

extern SpyroFlame g_SpyroFlame;

/// @brief: Resets Spyro
void func_8004AC24(int pKeepPosition);

/// @brief: Forces state to and resets animation
void func_8003FDC8(int pNewState);

void UpdateSpyroEnterReturnHome(void);

void func_8004A200(void);

void UpdateSpyroReturnHome(void);

/// @brief Handles the state transition for Spyro's body animation
void func_8003CCE4(void);

/// @brief Changes Spyro's state
void func_8003EA68(int pNewState);

#endif // !__SPYRO_H
