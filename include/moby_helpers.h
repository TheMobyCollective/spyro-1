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
int func_80038074(int p1, int p2);

/// @brief Normalizes the difference between two angles to -128 to 128
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @return The normalized difference
int func_800381BC(int p1, int p2);

int func_80038098(int p1, int p2, int p3);

int func_80038120(int p1, int p2, u_char p3);

int func_80038178(int p1, int p2, int p3, u_char p4);

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
void func_8003851C(Moby *pMoby, int pSoundIndex, u_char *pChannel);

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
void UpdateMobyDragonFragment(Moby *pMoby);

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
/// @param pBounds Collision bounds (passed to MoveMobyTowardTarget)
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
int MoveMobyTowardTarget(Moby *pMoby, Vector3D *pTarget, int pSpeed,
                         int turnRateH, int turnRateV, int pBounds);

/**
 * @brief Updates moby movement with horizontal motion, deceleration and
 * gravity.
 *
 * Handles two types of movement:
 * 1. Horizontal movement via speed - calls func_80039688 while speed > 0
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
int MoveMobyWithGravity(Moby *pMoby, int *pHorizontalSpeed, int pAngle,
                        int *pZVelocity, int pDeceleration, int pGravity);

/// @brief Moves a moby horizontally by (distance) along (angle), then resolves
/// floor/wall collision and snaps height, gated by flag bits. Returns 0
/// normally, 1 on a blocking hit, 2 when the floor is out of reach.
int func_80039688(Moby *pMoby, int angle, int distance, int mobyCollisionRadius,
                  int collisionRadius, int flags);

int func_8003BCCC(Moby *pMoby, int pForwardDist, int pMobyRadius,
                  int pGroundRadius, int flags);

int func_80039228(Moby *pMoby, Vector3D vec1, int arg4, int arg5, int arg6);

/// @brief Rotate moby to face an angle
/// @param pMoby The moby to rotate
/// @param targetAngle The target angle to face
/// @param rotSpeed The rotation speed
/// @param withinAngle The threshold angle for "close enough"
/// @param continueRotation Whether to continue rotating when close
/// @return 1 if close to target angle, 0 otherwise
int RotateMobyToAngle(Moby *pMoby, int targetAngle, int rotSpeed,
                      int withinAngle, int continueRotation);

/// @brief Rotate moby to face Spyro
/// @param pMoby The moby to rotate
/// @param rotSpeed The rotation speed
/// @param withinAngle The threshold angle for "close enough"
/// @param continueRotation Whether to continue rotating when close
/// @return 1 if close to target angle, 0 otherwise
int RotateMobyToSpyro(Moby *pMoby, int rotSpeed, int withinAngle,
                      int continueRotation);

int func_80038250(Vector3D *pPoint);

/// @brief Looks for the floor below the Moby
int func_80038340(Moby *pMoby);

int func_8003838C(Moby *pMoby);

int func_80038400(Moby *pMoby, int pDistFromFloor);

void func_80038458(Moby *pMoby);

void func_800385BC(Moby *pMoby, int pUnknown);

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
int func_80038AFC(PathData *pPathData, int *pNodeIndexOut);

/// @brief Find the path node furthest away from Spyro
int func_80038BB0(PathData *pPathData);

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

/// @brief Spawns a Moby drop and initializes its position and movement
Moby *func_8003ABC0(Moby *pMoby, int pSpawnMode, Vector3D *pStartPosition,
                    Vector3D *pTargetPosition);

/// @brief Returns if a Moby has been killed
int func_80038494(Moby *pMoby);

/// @brief Marks a moby as killed
void func_8003B7C0(Moby *pMoby);

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
void func_8003B47C(Moby *pMoby, u_int pState, u_int pRequiredNotState);

/// @brief Sets the state of all mobys in this pod, if they have a certain state
void func_8003B538(Moby *pMoby, u_int pState, u_int pRequiredState);

/// @brief Sets the damage flags of all mobys in this pod (metalhead)
void func_8003B5F4(int pPodId, int pDamageFlags);

/// @brief Deallocates all mobys inside this pod (metalhead)
void func_8003B688(int pPodId);

/// @brief Sets the substate of all mobys in this pod
void func_8003B728(Moby *pMoby, u_int pSubstate);

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
void func_8003B854(int pGemValue, Moby *pMoby);

/// @brief Collect an item (gem, key, ...)
void CollectItem(Moby *pMoby);

/// @brief Create portal text
void func_8003C358(Moby *pMoby, int pIsLevelName);

/// @brief Flight level active object slots (4 slots, negative = empty)
extern int g_FlightObjectiveActiveSlots[4];

/// @brief Flight level objective counters
extern int g_FlightObjectiveCounters[4];

#endif
