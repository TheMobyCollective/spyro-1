#ifndef __MOBY_HELPERS_H__
#define __MOBY_HELPERS_H__

#include "moby.h"

/// @brief Function that ticks a timer
/// @param pTimer The timer to update
/// @param pTimerType The type of timer, equal to the size of the type
/// @return non-0 if the timer has elapsed
int func_80037F90(void *pTimer, int pTimerType);

#define TICK_TIMER(t) func_80037F90(&(t), sizeof((t)))

/// @brief Adds two angles together
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @return The sum of the two angles
int AngleAdd(int p1, int p2);

/// @brief Gives the shorted signed distance from angle p1 to angle p2
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @return Distance normalised to -128 to 128
int AngleSignedDistance(int p1, int p2);

/// @brief Clamps the distance between two angles to a maximum
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @param p3 Maximum step
/// @return The new angle after clamping
int AngleClampDistance(int p1, int p2, int p3);

/// @brief Linearly interpolates between two angles
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @param interp Interpolation factor (0-255)
/// @return The interpolated angle
int AngleLerp(int p1, int p2, u_char interp);

/// @brief Interpolates between two angles, clamping the maximum distance
/// between calls
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @param maxDistance Maximum distance per call
/// @param interp Interpolation factor (0-255)
/// @return The resulting angle after clamping and interpolation
int AngleLerpClamped(int p1, int p2, int maxDistance, u_char interp);

// Distance and delta helpers
#define DISTANCE_TO_SPYRO(m) OctDistance(&(m)->m_Position, &g_Spyro.m_Position)
#define MOBY_BASE_Z(m) ((m)->m_Position.z - (m)->m_FloorDistance)
#define MOBY_BASE_Z_DELTA(m, z) (MOBY_BASE_Z(m) - (z))
#define MOBY_BASE_Z_DISTANCE(m, z) ABS2(MOBY_BASE_Z_DELTA(m, z))
#define SPYRO_BASE_Z_DELTA(m) MOBY_BASE_Z_DELTA(m, g_Spyro.m_Position.z)
#define SPYRO_BASE_Z_DISTANCE(m) ABS2(SPYRO_BASE_Z_DELTA(m))
// This version does not use m_FloorDistance
#define SPYRO_ORIGIN_Z_DELTA(m) ((m)->m_Position.z - g_Spyro.m_Position.z)
#define SPYRO_ORIGIN_Z_DISTANCE(m) ABS2(SPYRO_ORIGIN_Z_DELTA(m))
// Angle helpers
#define ANGLE_FROM(from, to) Atan2((to).x - (from).x, (to).y - (from).y, 0)
#define ANGLE_TO_SPYRO(from) ANGLE_FROM((from), g_Spyro.m_Position)
#define ANGLE_FROM_SPYRO(to) ANGLE_FROM(g_Spyro.m_Position, (to))

/// @brief Plays a sound from a Moby
void MobyPlaySound(Moby *pMoby, int pSoundIndex, u_char *pChannel);

/// @brief Returns the dot product of a vector and a plane's normal vector
/// (doesn't use the GTE)
int func_80038D54(Vector3D *param_1, Plane *param_2);

int func_80038FC8(Moby *pMoby, int *pTurnDirection, int *pFacingAngle,
                  int pTurnSpeed, int pTurnSwitchThreshold,
                  int pBaseTurnAnimation);

/// @brief Moby walking movement, used by most fodder and classes 214/216
void func_80039AA8(Moby *pMoby, MobyWanderState *pWander);

/// @brief Updates a dragon fragment's animation each frame
/// @param pMoby The fragment moby to update
/// Applies velocity to position, gravity to z velocity (clamped to -128),
/// rotation deltas, and spawns particles every other frame. When lifetime
/// expires or fragment falls below initZ, spawns end particles and deactivates
/// the moby.
void MobyUpdateDragonFragment(Moby *pMoby);

/**
 * @brief Moves a moby along a 3D path with rotation toward waypoints
 * @param pMoby The moby to move along the path
 * @param pPath Path data containing waypoint nodes
 * @param threshold Distance to consider a waypoint reached
 * @param maxSpeed Maximum movement speed per frame
 * @param bounds Collision bounds radius (0 to skip collision checks)
 * @param turnRate Maximum angle change per frame (8-bit angle units)
 * @param angleLimit If angle to waypoint exceeds this, movement stops
 * @param pVelocity Optional velocity accumulator for smoothing (NULL to skip)
 * @return 0 if still following path, (newNodeIndex + 0x100) when waypoint
 * reached
 */
int MoveMobyAlongPath(Moby *pMoby, PathData *pPath, int threshold, int maxSpeed,
                      int bounds, int turnRate, int angleLimit,
                      Vector3D *pVelocity);

/// @brief Updates a moby to follow a path, advancing waypoints when close
/// @param pMoby The moby to move along the path
/// @param pPath The path data containing waypoints
/// @param threshold Distance threshold to advance to the next waypoint
/// @param maxSpeed Maximum movement speed (clamped)
/// @param pBounds Collision bounds (passed to MobyMoveTowardTarget)
/// @param turnRateH Horizontal/yaw turn rate
/// @param turnRateV Vertical/pitch turn rate
/// @note Only used for Puffer Bird in Lofty Castle
void UpdatePufferBirdMobyPathNode(Moby *pMoby, PathData *pPath, int threshold,
                                  int maxSpeed, int pBounds, int turnRateH,
                                  int turnRateV);

/// @brief Moves a moby toward a target position, rotating to face it
/// @param pMoby The moby to move
/// @param pTarget Target position to move toward
/// @param pSpeed Movement speed
/// @param turnRateH Horizontal (yaw) turn rate limit
/// @param turnRateV Vertical (pitch) turn rate limit
/// @param pBounds Collision bounds radius (0 to skip collision checks)
/// @return 1 if collision occurred, 0 otherwise
int MobyMoveTowardTarget(Moby *pMoby, Vector3D *pTarget, int pSpeed,
                         int turnRateH, int turnRateV, int pBounds);

/**
 * @brief Updates moby movement with horizontal motion, deceleration and
 * gravity.
 *
 * Handles two types of movement:
 * 1. Horizontal movement via speed - calls MobyMove while speed > 0
 * 2. Vertical movement with gravity - applies velocity and detects landing
 *
 * @param pMoby The moby to move
 * @param pHorizontalSpeed Pointer to horizontal speed (decremented each frame
 * until 0)
 * @param pAngle Angle parameter passed to horizontal movement
 * @param pZVelocity Pointer to vertical velocity (NULL or 0xFFFF to disable)
 * @param pDeceleration Amount to subtract from horizontal speed each frame
 * @param pGravity Gravity to subtract from z velocity each frame
 * @return 0 = normal, 2 = horizontal collision, 3 = landed on ground
 */
int MobyMoveWithGravity(Moby *pMoby, int *pHorizontalSpeed, int pAngle,
                        int *pZVelocity, int pDeceleration, int pGravity);

/// @brief Moves a moby horizontally by (distance) along (angle), then resolves
/// floor/wall collision and snaps height, gated by flag bits. Returns 0
/// normally, 1 on a blocking hit, 2 when the floor is out of reach.
int MobyMove(Moby *pMoby, int angle, int distance, int mobyCollisionRadius,
             int collisionRadius, int flags);

int MobyMoveForward(Moby *pMoby, int pForwardDist, int pMobyRadius,
                    int pGroundRadius, int flags);

int func_80039228(Moby *pMoby, Vector3D vec1, int arg4, int arg5, int arg6);

/// @brief Rotate moby to face an angle
/// @param pMoby The moby to rotate
/// @param targetAngle The target angle to face
/// @param rotSpeed The rotation speed
/// @param withinAngle The threshold angle for "close enough"
/// @param continueRotation Whether to continue rotating when close
/// @return 1 if close to target angle, 0 otherwise
int MobyRotateToAngle(Moby *pMoby, int targetAngle, int rotSpeed,
                      int withinAngle, int continueRotation);

/// @brief Rotate moby to face Spyro
/// @param pMoby The moby to rotate
/// @param rotSpeed The rotation speed
/// @param withinAngle The threshold angle for "close enough"
/// @param continueRotation Whether to continue rotating when close
/// @return 1 if close to target angle, 0 otherwise
int MobyRotateToSpyro(Moby *pMoby, int rotSpeed, int withinAngle,
                      int continueRotation);

int MobyCanSeeSpyro(Vector3D *pPoint);

/// @brief Looks for the floor below the Moby
int MobyFloorHeight(Moby *pMoby);

int MobyFloorStandable(Moby *pMoby);

int func_80038400(Moby *pMoby, int pDistFromFloor);

void func_80038458(Moby *pMoby);

void MobyCreatePoof(Moby *pMoby, int pSmokeSize);

/// @brief Moves a Moby around a point toward a target angle, with angle limits
/// and collision checks
int func_80038638(Moby *pMoby, Vector3D *pCenter, int radius, int targetAngle,
                  int angleThreshold, int moveSpeed, int turnSpeed,
                  int turnThreshold, int limitAngle1, int limitAngle2,
                  int mobyCollisionRadius, int collisionRadius, int flags);

int func_8003891C(Vector3D *pVec1, Vector3D *pVec2, int p3, int p4, int *pOut);

/// @brief Finds the path node closest to the moby
int func_80038A40(Moby *pMoby, PathData *pPathData, int *pNodeIndexOut);

/// @brief Finds the path node closest to Spyro
int PathNodeClosestToSpyro(PathData *pPathData, int *pNodeIndexOut);

/// @brief Find the path node furthest away from Spyro
int PathNodeFurthestFromSpyro(PathData *pPathData);

/// @brief Checks if a point is within a rectangle
int func_80038C4C(Vector3D *point, Vector3D *rect);

int func_80039398(Moby *pMoby, int distance, int mobyCollisionRadius,
                  int collisionRadius, int flags);

int func_80039E94(Moby *pMoby, PathData *pPath, int arrivalRadius, int speed,
                  int mobyCollisionRadius, int turnSpeed, int withinAngle,
                  int waitForFlags, int moveFlags);

int func_8003A16C(Moby *pMoby, PathData *pPath, int threshold, int maxMag,
                  int mobyCollisionRadius, int clampRange, int arc,
                  int *pHeading);

typedef enum {
  DROP_MODE_LAUNCH_NO_SCATTER = 0, // Launches without scatter (unused and bad)
  DROP_MODE_SCATTER = 1,           // Launches and always scatters
  DROP_MODE_AT_TARGET = 2,         // Arches aimed at a specific target

  // Launches with scatter but can conditionally home in
  // Based on the distance to Spyro, and if Spyro is in a state
  // considered charging (charge)
  DROP_MODE_SCATTER_OR_HOMING = 3,
  DROP_MODE_HOMING = 4,      // Always homes in
  DROP_MODE_NO_MOVEMENT = 5, // Used by spring and life chest
  DROP_MODE_FIREWORKS = 6,   // High launch tight scatter
} DropSpawnMode;

/// @brief Spawns a Moby drop and initializes its position and movement
Moby *MobySpawnDrop(Moby *pMoby, int pSpawnMode, Vector3D *pStartPosition,
                    Vector3D *pTargetPosition);

/// @brief Returns if a Moby has been killed
int MobyIsMarkedKilled(Moby *pMoby);

/// @brief Marks a moby as killed
void MobyMarkKilled(Moby *pMoby);

int func_8003BFC0(Moby *pMoby, PathData *pPath, Vector3D *pPreviousMovement,
                  int *pSegmentFrame, int pSegmentDuration, int pFlags);

/// @brief Initialize a Moby
void func_8003A720(Moby *pMoby);

/// @brief Calculates viewing angles from Spyro to a target position
/// @param pTarget The target position to look at
/// Stores clamped elevation angle in g_Spyro.m_HeadLookTarget.y
/// Stores clamped azimuth angle in g_Spyro.m_HeadLookTarget.z
void SetSpyroHeadLookTarget(Vector3D *pTarget);

/// @brief Registers a flight level collectible moby type in one of 4 slots
/// @param index The moby type index to register
void RegisterFlightMobyCollectibleType(int index);

///// @brief Advanced flame heat effect with external heat tracking and RGB
/// specular color output
/// @param pMoby The moby to apply the flame heat effect to
/// @param heat Current heat value (caller-managed, typically 0-80+)
/// @return Updated heat value (caller should store and pass back on subsequent
/// frames)
int ApplyFlameHeatExternal(Moby *pMoby, int heat);

/// @brief Apply flame heat
void ApplyFlameHeat(Moby *pMoby);

/// @brief Are any mobys in this pod still alive?
int func_8003B0DC(int pPod);

/// @brief Are all mobys in this pod in this state? (Unused)
int func_8003B160(int pPod, u_int pState);

/// @brief Set the state of all mobys in the moby's pod
void func_8003B1E8(Moby *pMoby, u_int pState);

// Something related to damaging other mobys inside a pod (metalhead)
void func_8003B294(Moby *pMoby, int pPodIdx, uint pFlag, int pWithinOctDist,
                   int pWithinZDist, int pWithinXYDist, int pWithinAngle);

/// @brief Sets the state of all mobys in this pod, if they do not have a
/// certain state
void MobyPodSetStateIfNot(Moby *pMoby, u_int pState, u_int pRequiredNotState);

/// @brief Sets the state of all mobys in this pod, if they have a certain state
void MobyPodSetStateIf(Moby *pMoby, u_int pState, u_int pRequiredState);

/// @brief Sets the damage flags of all mobys in this pod (metalhead)
void PodDamage(int pPodId, int pDamageFlags);

/// @brief Deallocates all mobys inside this pod (metalhead)
void PodDeallocate(int pPodId);

/// @brief Sets the substate of all mobys in this pod
void MobyPodSetSubstate(Moby *pMoby, u_int pSubstate);

// Vector interpolation curve lookup tables
// Each table contains pairs of weights (w1, w2) where w1 + w2 = 1024
// Used for smooth interpolation between two vectors along a curve

/// @brief Linear interpolation weights (1 pair for 2 steps)
extern short D_80075280[];
/// @brief Interpolation curve weights (4 pairs for 5 steps)
extern short D_8006CBA4[];
/// @brief Interpolation curve weights (6 pairs for 7 steps)
extern short D_8006CBB4[];
/// @brief Interpolation curve weights (8 pairs for 9 steps)
extern short D_8006CBCC[];

/// @brief Spawns a sparkle particle attached to a moby
/// @param pMoby The moby to attach the sparkle to
/// @param pOffset The offset vector to rotate by the moby's rotation matrix
/// @return The slot index, or -1 if no slot available
int SpawnMobySparkle(Moby *pMoby, Vector3D *pOffset);

/// @brief Persist a collected gem to checkpoint / global collected mask
void MobyMarkCollected(int pGemValue, Moby *pMoby);

/// @brief Collect an item (gem, key, ...)
void MobyCollectItem(Moby *pMoby);

/// @brief Create portal text
void func_8003C358(Moby *pMoby, int pIsLevelName);

/// @brief Flight level active object slots (4 slots, negative = empty)
extern int g_FlightObjectiveActiveSlots[4];

/// @brief Flight level objective counters
extern int g_FlightObjectiveCounters[4];

#endif
