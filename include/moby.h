#ifndef __MOBY_H
#define __MOBY_H

#include "graphics.h"
#include "matrix.h"
#include "vector.h"
#include <sys/types.h>

// Animation state naming comes from PS underground 1:08
typedef struct {
  /// @brief Which animation is currently playing
  u_char m_Animation;

  /// @brief Which animation you're interpolating to
  u_char m_NextAnimation;

  /// @brief The current frame
  u_char m_Frame;

  /// @brief The next frame which you're interpolating to
  u_char m_NextFrame;

  /// @brief The progress of the current frame used for interpolation
  /// 0 - 4096 (0.0 - 1.0)
  u_char m_FrameProgress;

  /// @brief The amount of progress to make per frame
  /// If you want a new frame every in-game frame, this would be 4096 (1.0)
  /// If you want a new frame every 2 in-game frames, this would be 2048 (0.5)
  /// etc..
  u_char m_PerFrameProgress;

  /// @brief Flags that are set by the animation system
  /// Still not entirely sure if it should be part of the animation state
  /// or just in the moby
  /// & 1 == Finished frame (?)
  /// & 2 == Finished animation (used commonly)
  u_char m_AnimationFlags;
} AnimationState;

typedef enum {
  MOBY_DAMAGE_UNK = 0x1,
  MOBY_DAMAGE_FLAME = 0x10000,
  MOBY_DAMAGE_CHARGE = 0x20000,
  MOBY_DAMAGE_FROM_MOBY = 0x40000,
  MOBY_DAMAGE_SUPER = 0x80000,
} MobyDamageFlags;

// Double moby to define struct Moby inside
typedef struct Moby {
  /// @brief Specifies the properties of the moby, which is class specific
  void *m_Props;

  /// @brief The next moby in the collision chain that this Moby is a part of
  struct Moby *m_CollisionChainNext;

  /// @brief This Moby's active collision group (Which is part of it's model)
  void *m_CollisionGroup;

  /// @brief The Moby's position
  Vector3D m_Position;

  /// @brief The damage that has been applied to the Moby
  int m_DamageFlags; // TODO: Enum?

  /// @brief The distance of the shadow from the Moby, equal to the floor
  /// distance
  int m_ShadowDistance;

  /// @brief The Moby's rotation matrix
  SHORTMATRIX m_RotationMatrix;

  /// @brief The collision region that the Moby is in
  short m_CollisionRegion;

  /// @brief The Moby's class, which specifies which kind of Moby it is
  short m_Class;

  /// @brief The distance of the moby to the floor
  short m_FloorDistance;

  /// @brief Flag used to determine if the Moby has already dropped it's drop
  u_char m_DroppedFlag;

  /// @brief The range of the Moby's current collision
  u_char m_CollisionRange;

  /// @brief The Moby's current animation state
  AnimationState m_AnimationState;

  /// @brief The Pod that this Moby is a part of. This is a feature that they
  /// scrapped for S2/3, only to return for R&C It's used to determine which
  /// Moby's are part of the same group and utility functions exist to act on
  /// that group.
  u_char m_Pod;

  /// @brief The Moby's rotation
  Vector3D8 m_Rotation;

  /// @brief Offsets the sorting depth of the entire Moby
  char m_DepthOffset;

  /// @brief The Moby's current state, often used in Moby code
  u_char m_State;

  /// @brief The Moby's substate, less often used in Moby code
  u_char m_Substate;

  /// @brief Sector the Moby is located in, for culling purposes
  u_char m_SectorIndex;

  union {
    struct {
      /// @brief Stores the render distance of the Moby
      u_char m_Distance : 7;

      /// @brief And the renderer to be used
      u_char m_ShinyRenderer : 1;
    } flags;
    u_char raw;
  } m_Renderer;

  // We have to define it like this, we can't use
  // a bitfield because there's no 24 bit integer
  // type and the compiler aligns it to the
  // integer size used

  // Used for the specular color, which is 6 bits per channel (each value is
  // divided by 2)

  // For metal it's straight forward, 8 bits per channel

  u_char m_SpecularMetalColor[3];

  // Stores the type when shinyRenderer is enabled
  // If Shiny renderer: 0 = Specular 1/2 = metal (2 being rotated)
  // If shaded: color index
  u_char m_SpecularMetalType;

  /// @brief Radius of the Moby for clipping purposes (>> 2)
  u_char m_RenderRadius;

  // Stores whether the Moby got drawn last frame
  // If it has, the Moby receives more grace during culling
  // Also often used in Moby code, often enemies will not attack when they
  // are off-screen
  u_char m_WasDrawn;

  /// @brief The distance at which Mobys get updated (/1024)
  // Mobys often initialize this to 0xFF
  u_char m_UpdateDistance;

  /// @brief Moby class dropped by this Moby
  /// They AND this value with 0x7f (not sure why), which limits which Mobys
  /// can be used as a drop moby
  u_char m_DropMoby;

  /// @brief Sound channel the moby is occuping
  u_char m_SoundChannel;

  /// @brief Distance the last sound played was at
  u_char m_SoundDistance;

  // If dynamically allocated, this contains the index of the Moby that spawned
  // us used for keeping track of which index of the gem bitmask needs to be set
  // Ignored if the moby is not dynamically allocated
  u_char m_MobyIndex;

  // Used for resizing the Moby model dynamically, if set to 0 the regular size
  // is used
  u_char m_ScaleOverride;
} Moby;

// Moby models
typedef struct {
  // Vertex offset:    00000000000111111111111111111111
  // Collision model:  00000000111000000000000000000000
  // Frame sound:      11111111000000000000000000000000
  union {

    // Not sure if this will match, but there's only one way to find out
    struct {
      u_int m_VertexOffset : 21;
      u_int m_CollisionModel : 3;
      u_int m_FrameSound : 8;
    } m_Props;
    u_int m_Data;
  } m;

  u_short m_VertexColorOffset;
  u_char m_Shadow;
  u_char m_ShortOffset;
} AnimationFrame;

typedef union {
  struct {
    u_int frameDataOffset : 21;
    u_int nextNotCompressed : 1;
    u_int headNextNotCompressed : 1;
    u_int tailNextNotCompressed : 1;
    u_int soundForFrame : 8;
  } m_Props;
  u_int m_Data;
} SpyroAnimationFrame;

typedef struct {
  short m_NumFrames;
  u_short m_NumColors;

  u_char m_IsSpyroAnimation; // If 1, the other values of the int are unused
  u_char m_Scale;
  u_char m_ShortEncodeShift;
  u_char m_Radius;

  u_char m_VertCountHigh;
  u_char m_VertCountLow;
  u_char m_Padding2;
  u_char m_DepthScale;
  u_char m_ProgressPerTick;
  u_char m_Padding3;
  u_short m_Padding4;

  void *m_AnimationVertices; // Used when m_IsSpyroAnimation is set, otherwise
                             // matches m_faces
  void *m_Faces;
  void *m_Colors;
  void *m_LpFaces;
  void *m_LpColors;
  AnimationFrame m_Frames[1]; // To the size of frameCount
} AnimationHeader;

typedef struct {
  int m_NumAnimations; // >= 0 == Model
  u_char m_Sounds[16];
  void *m_CollisionModels[8];
  void *m_Data; // offset from this to the data, used to offset pointers inside
                // animations
  AnimationHeader *m_Animations[1];
} Model;

#define MODEL_COUNT 512

extern Model *g_Models[MODEL_COUNT];

#define SPYRO_MODEL (g_Models[0])

typedef struct {
  int m_NumAnimations; // < 0 == SimpleModel (always -1 in reality)
  void *m_Verts;
  void *m_Colors;
  void *m_Faces;
} SimpleModel;

extern int g_AnimationFinished;
extern int g_AnimFrameFinished;

// Restart 'anim' from frame 0 at its natural model speed
#define MOBY_ANIM_RESTART(m, anim)                                             \
  (m)->m_AnimationState.m_FrameProgress = 0;                                   \
  (m)->m_AnimationState.m_PerFrameProgress =                                   \
      g_Models[(m)->m_Class]->m_Animations[(anim)]->m_ProgressPerTick;         \
  (m)->m_AnimationState.m_Animation = (anim);                                  \
  (m)->m_AnimationState.m_NextAnimation = (anim);                              \
  (m)->m_AnimationState.m_Frame = 0;                                           \
  (m)->m_AnimationState.m_NextFrame = 1;

// Promote existing next anim to current, then set 'anim' as next anim
#define MOBY_ANIM_ADVANCE(m, anim)                                             \
  (m)->m_AnimationState.m_FrameProgress = 0x10;                                \
  (m)->m_AnimationState.m_PerFrameProgress = 0x10;                             \
  (m)->m_AnimationState.m_Animation = (m)->m_AnimationState.m_NextAnimation;   \
  (m)->m_AnimationState.m_NextAnimation = (anim);                              \
  (m)->m_AnimationState.m_Frame = (m)->m_AnimationState.m_NextFrame;           \
  (m)->m_AnimationState.m_NextFrame = 0;                                       \
  func_80037E98(m);

// Advance to 'anim' if it is not already the next anim
#define MOBY_ANIM_CHANGE(m, anim)                                              \
  if ((m)->m_AnimationState.m_NextAnimation != (anim)) {                       \
    MOBY_ANIM_ADVANCE((m), (anim));                                            \
  }

// Advance to 'anim' if it is not already the next anim and clear
// g_AnimationFinished
#define MOBY_ANIM_CHANGE_CLEAR_FINISHED(m, anim)                               \
  if ((m)->m_AnimationState.m_NextAnimation != (anim)) {                       \
    g_AnimationFinished = 0;                                                   \
    MOBY_ANIM_ADVANCE((m), (anim));                                            \
  }

// Set 'anim' as next without promoting the existing next anim
#define MOBY_ANIM_SET_NEXT(m, anim)                                            \
  if ((m)->m_AnimationState.m_NextAnimation != (anim)) {                       \
    (m)->m_AnimationState.m_FrameProgress = 0x10;                              \
    (m)->m_AnimationState.m_PerFrameProgress = 0x10;                           \
    (m)->m_AnimationState.m_NextAnimation = (anim);                            \
    (m)->m_AnimationState.m_NextFrame = 0;                                     \
    func_80037E98(m);                                                          \
  }

// Data related

typedef enum {
  MOBYCLASS_PORTAL = 1,

  MOBYCLASS_EXIT_VORTEX = 9,

  MOBYCLASS_GEM_SPAWNER = 13,

  MOBYCLASS_LIFE_STATUE = 14,
  MOBYCLASS_LIFE_ORB = 15,
  MOBYCLASS_BUTTERFLY = 16,

  MOBYCLASS_DRAGON_EGG = 34,

  MOBYCLASS_HUD_SPYRO_HEAD = 58,

  MOBYCLASS_EXCLAMATION_MARK = 75,
  MOBYCLASS_LETTER_APOSTROPHE = 76,

  MOBYCLASS_FLIGHT_TRAIN_BARREL = 78,

  MOBYCLASS_GEM_1 = 83,
  MOBYCLASS_GEM_2 = 84,
  MOBYCLASS_GEM_5 = 85,
  MOBYCLASS_GEM_10 = 86,
  MOBYCLASS_GEM_25 = 87,

  MOBYCLASS_SPARX = 120, // Gets spawned in load scene

  MOBYCLASS_KEY = 173, // Both Hud and level key
  MOBYCLASS_LOCKED_CHEST = 174,

  MOBYCLASS_WOODEN_CHEST = 194,
  MOBYCLASS_METAL_CHEST = 195,

  MOBYCLASS_CRYSTAL_DRAGON = 250,
  MOBYCLASS_CRYSTAL_DRAGON_FRAGMENT = 251,

  MOBYCLASS_NUMBER_0 = 260,
  MOBYCLASS_NUMBER_1,
  MOBYCLASS_NUMBER_2,
  MOBYCLASS_NUMBER_3,
  MOBYCLASS_NUMBER_4,
  MOBYCLASS_NUMBER_5,
  MOBYCLASS_NUMBER_6,
  MOBYCLASS_NUMBER_7,
  MOBYCLASS_NUMBER_8,
  MOBYCLASS_NUMBER_9, // 269

  MOBYCLASS_PERCENT = 272,
  MOBYCLASS_SLASH = 277,
  MOBYCLASS_QUESTION_MARK = 278,

  MOBYCLASS_FLIGHT_CHEST = 299,

  MOBYCLASS_FLIGHT_PLANE = 308,

  MOBYCLASS_PLUS = 317,
  MOBYCLASS_CARET = 321,
  MOBYCLASS_PERIOD = 327,

  MOBYCLASS_SPRING_CHEST = 329,

  MOBYCLASS_FLIGHT_GATE = 353,

  MOBYCLASS_FLIGHT_TRAIN_WHEELS = 362,

  MOBYCLASS_ARMORED_CHEST = 401,

  MOBYCLASS_FLIGHT_TRAIN = 407,
  MOBYCLASS_FLIGHT_WAGON = 408,

  MOBYCLASS_LETTER_A = 426,
  MOBYCLASS_LETTER_B,
  MOBYCLASS_LETTER_C,
  MOBYCLASS_LETTER_D,
  MOBYCLASS_LETTER_E,
  MOBYCLASS_LETTER_F,
  MOBYCLASS_LETTER_G,
  MOBYCLASS_LETTER_H,
  MOBYCLASS_LETTER_I,
  MOBYCLASS_LETTER_J,
  MOBYCLASS_LETTER_K,
  MOBYCLASS_LETTER_L,
  MOBYCLASS_LETTER_M,
  MOBYCLASS_LETTER_N,
  MOBYCLASS_LETTER_O,
  MOBYCLASS_LETTER_P,
  MOBYCLASS_LETTER_Q,
  MOBYCLASS_LETTER_R,
  MOBYCLASS_LETTER_S,
  MOBYCLASS_LETTER_T,
  MOBYCLASS_LETTER_U,
  MOBYCLASS_LETTER_V,
  MOBYCLASS_LETTER_W,
  MOBYCLASS_LETTER_X,
  MOBYCLASS_LETTER_Y,
  MOBYCLASS_LETTER_Z, // 451

  MOBYCLASS_HUD_GEM_CHEST = 471,
  MOBYCLASS_HUD_DRAGON = 506,

  // These are the last two classes
  MOBYCLASS_DRAGON_CUTSCENE_DRAGON = 510,
  MOBYCLASS_DRAGON_CUTSCENE_SPYRO = 511,
} MobyClass;

typedef struct {
  u_char m_NodeCount;
  u_char m_CurrentNode;
  char unk_0x2[4];  // No clue, padding? Usually 0
  short m_Reversed; // Path traversal: -1 = normal, 1 = reversed
  struct {
    Vector3D m_Position;
    int unk_0xC; // Padding I assume
  } m_Nodes[1];
} PathData;

#define PATH_NODE(p, i) ((p)->m_Nodes[(i)])
#define PATH_NODE_POS(p, i) (PATH_NODE((p), (i)).m_Position)

#define PATH_CUR_NODE(p) PATH_NODE((p), (p)->m_CurrentNode)
#define PATH_CUR_POS(p) PATH_NODE_POS((p), (p)->m_CurrentNode)

// Present in some fodder classes, as well as the class 214/216 Gnorcs
typedef struct {
  Vector3D m_Origin;
  u_char m_MoveSpeed;
  u_char m_TurnSpeed;
  u_char m_CollisionRadius;
  u_char m_TurnTimerMin;
  u_char m_TurnTimerMax;
  u_char m_RandomTurnMin;
  u_char m_RandomTurnMax;
  u_char m_WanderRadius;
  u_char m_TargetAngleOffsetLimit;
  u_char m_TargetAngleOffsetStep;
  u_char m_0x16;
  u_char m_TurnTimer;
  u_char m_TargetAngle;
  u_char m_TargetAngleOffsetDirection;
  u_char m_FleeRadius;
  u_char m_IsFleeing;
  u_char m_FleeDelay;
  u_char m_IgnoreMobyCollisionTimer;
  short m_TargetAngleOffset;
} MobyWanderState;

// Used by 260-269, 327, 277
typedef struct {
  int m_Lifetime;
  int m_DigitPlaceValue;
  Vector3D m_Velocity;
} MobyNumberProps;

// Used by
// 67, 68, 69, 93, 133, 151, 215, 255
// 256, 257, 309, 310, 311, 359, 360,
// 361, 362, 423, 424, 425, 454, 455,
// 456, 458, 459, 478, 479, 480, 481,
// 482, 483
typedef struct {
  Vector3D16 m_Velocity;
  Vector3D16 m_AngularVelocity;
  int m_Lifetime;
  int m_MinZ;
} MobyFragmentProps;

// Used by 14, 15, 83-87
// TODO: Review names, members might fulfill multiple purposes
typedef struct {
  Vector3D m_InitPos;
  short m_CollisionIndex;
  u_char m_SpawnState;
  u_char m_Ticks;
  u_char m_RotX;
  u_char m_RotY;
  u_char m_RotZ;
  u_char m_RotationTicks;
  u_char m_SparkleHandle;
} MobyCollectableProps;

// Used by 426-451, 76
typedef struct {
  Moby *m_Parent;
  short m_Len;
  short m_Index;
} MobyLetterProps;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
} Moby9Props;

typedef struct {
  Vector3D m_RespawnPosition;
  PathData *m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
} Moby10Props;

typedef struct {
  int m_Timer;
} Moby11Props;

typedef struct {
  int m_0x00;
  Vector3D m_0x04;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
} Moby13Props;

typedef struct {
  int m_0x00;
  Vector3D m_0x04;
  char m_0x10;
  char m_0x11;
  char m_0x12;
  char m_0x13;
  short m_0x14;
  short m_0x16;
} MobyButterflyProps;

typedef struct {
  Vector3D m_0x00;
  int m_0x0c;
} Moby17Props;

typedef struct {
  int m_0x00;
  int m_0x04;
} Moby18Props;

typedef struct {
  Vector3D m_0x00;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24[4];
  int m_0x34;
  PathData *m_0x38;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
} Moby23Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
} Moby28Props;

typedef struct {
  Moby *m_Parent;
} Moby32Props;

typedef struct {
  PathData *m_0x00;
  Moby *m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  int m_0x40;
  Vector3D m_0x44;
  Vector3D m_0x50;
} Moby33Props;

typedef struct {
  Moby *m_0x00;
  Vector3D16 m_0x04;
  Vector3D16 m_0x0a;
  short m_0x10;
  unsigned char m_0x12;
  unsigned char m_0x13;
} Moby34Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  PathData *m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  short m_0x2c;
  short m_0x2e;
  Vector3D m_0x30;
} Moby35Props;

typedef struct {
  // Always equals initial m_Position
  Vector3D m_RespawnPosition;
  PathData *m_Path;
  int m_IsLoopPath;
} Moby36Props;

typedef struct {
  Moby *m_0x00;
  short m_0x04;
  short m_0x06;
  short m_0x08;
  short m_0x0a;
  Moby *m_0x0c;
  u_char m_0x10;
} Moby37Props;

typedef struct {
  int m_0x00;
} Moby38Props;

typedef struct {
  int m_0x00;
  Moby *m_0x04;
  int m_0x08;
} Moby39Props;

// Used by 45 and 46
typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  Vector3D m_0x24;
  int m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
  int m_0x48;
} Moby45Props;

typedef struct {
  u_char m_0x00;
  signed char m_0x01;
  signed char m_0x02;
  u_char m_0x03;
  short m_0x04;
  short m_0x06;
  short m_0x08;
  short m_0x0a;
  Moby *m_0x0c;
} Moby47Props;

typedef struct {
  int m_0x00;
  PathData *m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10[4];
  int m_0x20;
  int m_0x24;
  int m_0x28;
  Vector3D m_0x2c;
  Vector3D m_0x38;
  int m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
} Moby48Props;

typedef struct {
  int m_EnvAnimID;
  int m_AlreadyVisitedCheckDone;
  int m_ArgusStatueMobyIndex;
} Moby49Props;

typedef struct {
  Vector3D m_0x00;
  int m_0x0c;
  Moby **m_0x10;
  int m_0x14;
  Vector3D m_0x18;
  int m_0x24;
} Moby50Props;

typedef struct {
  Vector3D m_0x00;
  int m_0x0c;
  Moby **m_0x10;
  int m_0x14;
  Vector3D m_0x18;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
} Moby51Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
} Moby52Props;

typedef struct {
  int m_0x00[3];
  int m_0x0c;
  int m_0x10;
} Moby53Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby54Props;

typedef struct {
  int m_Lifetime;
} Moby55Props;

typedef struct {
  int m_Lifetime;
} Moby56Props;

typedef struct {
  short m_0x00;
  short m_0x02;
  short m_0x04;
  short m_0x06;
  short m_0x08;
  short m_0x0a;
  u_char m_0x0c;
  u_char m_0x0d;
  u_char m_0x0e;
  u_char m_0x0f;
} Moby57Props;

typedef struct {
  int m_CagedFairyIndex;
  int m_FallSpeed;
} Moby61Props;

typedef struct {
  Vector3D m_0x00;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  PathData *m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
} Moby62Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08[2];
  int *m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  Moby *m_0x24[4];
} Moby65Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
} Moby66Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  short m_0x10;
  short m_0x12;
} Moby70Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
} Moby78Props;

typedef struct {
  Vector3D m_0x00;
  short m_0x0c;
  u_char m_0x0e;
  u_char m_0x0f;
} Moby82Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  Vector3D m_0x0c;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
} Moby88Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  union {
    TracerPoint m_Normal[3][0x91];
    TracerPoint m_Targeted[3][0x82];
  } m_0x28;
} Moby91Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  Vector3D m_0x18;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  PathData *m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
} Moby92Props;

// Used by 100 and 102
typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18[3];
  PathData *m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  Moby *m_0x40;
  int m_0x44;
  int m_0x48;
  Vector3D m_0x4c;
  int m_0x58;
  int m_0x5c[2];
  Vector3D m_0x64;
  int m_0x70[3];
  int m_0x7c;
  int m_0x80;
  int m_0x84;
  int m_0x88;
  int *m_0x8c;
  int m_0x90;
  int m_0x94;
} Moby100Props;

// Used by 101 and 170
typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20[3];
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  PathData *m_0x38;
  Vector3D m_0x3c;
  int m_0x48[3];
  Vector3D m_0x54;
  int m_0x60[3];
  int m_0x6c;
  int m_0x70;
  int m_0x74[2];
  int m_0x7c[2];
  int m_0x84;
  int *m_0x88;
  int m_0x8c;
  int m_0x90;
} Moby101Props;

typedef struct {
  short m_0x00;
  short m_0x02;
  TracerPoint *m_0x04;
  short m_0x08;
  short m_0x0a;
  short m_0x0c;
  short m_0x0e;
  short m_0x10;
  u_char m_0x12;
  u_char m_0x13;
} Moby104Props;

typedef struct {
  int m_0x00;
  PathData *m_0x04;
  PathData *m_0x08;
  PathData *m_0x0c;
  PathData *m_0x10;
  PathData *m_0x14;
  Vector3D m_0x18;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
} Moby109Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  Vector3D m_0x10;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
} Moby110Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby113Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
} Moby114Props;

typedef struct {
  int m_KnockbackAngle;
  int m_KnockbackSpeed;
  int m_LaughCounter;
  int m_LinkedMobyCheckTimer;
  int m_LinkIndex;
} Moby115Props;

typedef struct {
  int m_Timer;
  Vector3D16 m_SpyroOffset;
  Glow *m_Glow;
  Moby *m_Target;
} MobySparxProps;

typedef struct {
  Vector3D m_0x00;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int *m_0x30;
} Moby121Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  Glow *m_0x08;
  Vector3D m_0x0c;
  int m_0x18;
} Moby122Props;

typedef struct {
  Moby *m_0x00;
} Moby124Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  PathData *m_0x08;
  int m_0x0c;
  Vector3D m_0x10;
  Vector3D m_0x1c;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
  int m_0x58;
  int m_0x5c;
  int m_0x60;
  int m_0x64;
} Moby126Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  Vector3D m_0x18;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  PathData *m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
  int m_0x58;
  int m_0x5c;
  int m_0x60;
  int m_0x64;
  u_char m_0x68;
} Moby130Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  Vector3D m_0x10;
  Vector3D m_0x1c;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  PathData *m_0x34;
  int m_0x38;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
} Moby134Props;

typedef struct {
  short m_0x00;
  short m_0x02;
  short m_0x04;
  u_char m_0x06;
  u_char m_0x07;
  short m_0x08;
  short m_0x0a;
  short m_0x0c;
  short m_0x0e;
  u_char m_0x10;
  u_char m_0x11;
  u_char m_0x12;
} Moby135Props;

typedef struct {
  Moby *m_0x00[4];
  int m_0x10;
  int m_0x14;
  int m_0x18;
} Moby136Props;

typedef struct {
  int m_0x00;
  Vector3D m_0x04;
  int m_0x10;
  int m_0x14;
  PathData *m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  int *m_0x40;
  int m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
  int m_0x58;
  int m_0x5c;
} Moby137Props;

// Used by 142, 227, 241
typedef struct {
  Vector3D m_0x00;
  int m_0x0c;
  Vector3D m_0x10;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  PathData *m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
} Moby142Props;

typedef struct {
  int m_0x00;
  int m_0x04;
} Moby143Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  PathData *m_0x1c;
  int m_0x20;
  int m_0x24;
  Vector3D m_0x28[2];
  Vector3D m_0x40[2][2];
  int m_0x70;
  int m_0x74;
} Moby145Props;

typedef struct {
  int m_Timer;
} Moby146Props;

typedef struct {
  int m_0x00;
  PathData *m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  Vector3D m_0x34[2];
  Vector3D m_0x4c[2][2];
  int m_0x7c;
} Moby147Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  Vector3D m_0x10[2];
  PathData *m_0x28;
  PathData *m_0x2c;
  int m_0x30;
  int m_0x34;
  Moby *m_0x38;
  int m_0x3c;
  int m_0x40;
  Vector3D m_0x44[2][2];
  int m_0x74;
} Moby148Props;

typedef struct {
  PathData *m_0x00;
  char m_0x04[8];
  char m_0x0c[8];
  int m_0x14;
  int m_0x18;
  Vector3D m_0x1c;
  Vector3D m_0x28;
  int m_0x34;
  int m_0x38;
  Moby *m_0x3c;
  int m_0x40;
  Moby *m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
} Moby150Props;

typedef struct {
  Vector3D m_Velocity;
  int m_MinZ;
  Vector3D8 m_AngularVelocity;
} Moby152Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  Moby *m_0x08;
  int m_0x0c;
} Moby154Props;

typedef struct {
  int m_0x00;
} Moby155Props;

typedef struct {
  Vector3D m_0x00;
  short m_0x0c;
  short m_0x0e;
} Moby156Props;

typedef struct {
  int m_EnvAnimID;
} Moby157Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  Vector3D m_0x28;
  Vector3D m_0x34;
  int m_0x40[8];
  int m_0x60;
} Moby159Props;

typedef struct {
  MobyWanderState m_Wander;
  char m_0x20[0x18];
  int m_KnockbackAngle;
  int m_KnockbackSpeed;
  char m_0x40[0x10];
} Moby160Props;

typedef struct {
  PathData *m_0x00;
  PathData *m_0x04;
  PathData *m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24[12];
  int m_0x54;
  int m_0x58;
  int m_0x5c;
  int m_0x60;
  int m_0x64;
  int m_0x68;
  int m_0x6c;
  Vector3D m_0x70;
  Vector3D m_0x7c;
  Vector3D m_0x88;
  Vector3D m_0x94;
  Vector3D m_0xa0;
  Vector3D m_0xac;
  int m_0xb8;
  int m_0xbc;
  int m_0xc0;
  int m_0xc4;
  PathData *m_0xc8;
  int m_0xcc;
  u_char m_0xd0[4];
  int m_0xd4;
  int m_0xd8;
  int m_0xdc;
  u_char m_0xe0[3][4200];
} Moby161Props;

typedef struct {
  PathData *m_0x00;
  PathData *m_0x04[4];
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  Vector3D m_0x34;
  int m_0x40;
} Moby162Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
} Moby163Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  short m_0x1c;
  short m_0x1e;
  int m_0x20;
  int m_0x24;
  int m_0x28;
} Moby165Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby166Props;

typedef struct {
  TracerPoint *m_0x00;
  short m_0x04;
  short m_0x06;
  short m_0x08;
  short m_0x0a;
  int m_0x0c;
  int m_0x10;
} Moby169Props;

typedef struct {
  int m_0x00;
  int m_Timer;
} Moby171Props;

typedef struct {
  short m_0x00;
  u_char m_0x02;
  u_char m_0x03;
} Moby173Props;

typedef struct {
  int m_KeyLinkIndex;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
} Moby174Props;

typedef struct {
  int m_0x00;
  short m_0x04;
  short m_0x06;
  short m_0x08;
  short m_0x0a;
  u_char m_0x0c;
  u_char m_0x0d;
  u_char m_0x0e;
  u_char m_0x0f;
} Moby176Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  Vector3D m_0x1c;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  PathData *m_0x34;
  PathData *m_0x38;
  PathData *m_0x3c;
  PathData *m_0x40;
  int m_0x44;
} Moby177Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
} Moby179Props;

typedef struct {
  short m_0x00;
  u_char m_0x02;
  u_char m_0x03;
  int m_0x04;
  Vector3D m_0x08;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
} Moby181Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
} Moby183Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
} Moby184Props;

typedef struct {
  Vector3D m_0x00;
  PathData *m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
} Moby186Props;

// Used by 187-192 in Balloonist1 func
typedef struct {
  int m_BalloonMobyIdx;
} Moby187Props;

typedef struct {
  MobyWanderState m_Wander;
  char m_0x20[0x18];
  int m_KnockbackAngle;
  int m_KnockbackSpeed;
  char m_0x40[0x10];
} Moby193Props;

// m_0x00 has initial values in Cliff Town
typedef struct {
  int m_0x00;
  int m_FollowFloorZ;
} Moby194Props;

typedef struct {
  int m_ShakeTimer;
  int m_BaseRotX;
  int m_BaseRotY;
  int m_BasePosZ;
  int m_FollowFloorZ;
  int m_Heat;
} Moby195Props;

// Dynamic
typedef struct {
  Vector3D m_Velocity;
  short m_Lifetime;
  short m_MobyCollisionDelay;
} Moby197Props;

typedef struct {
  int m_KnockbackAngle;
  int m_KnockbackSpeed;
  int m_LaughCounter;
  int m_0x0c;
  int m_IdleAnimCounter;
} Moby198Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby199Props;

typedef struct {
  int m_0x00;
  Moby *m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
} Moby200Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
} Moby201Props;

typedef struct {
  short m_0x00;
  short m_0x02;
  Moby *m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby202Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  PathData *m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
} Moby203Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04[7];
  int m_0x20[7];
  int m_0x3c;
  Vector3D m_0x40[7][2];
  int m_0xe8[7];
  int m_0x104;
  int m_0x108;
  int m_0x10c;
  Vector3D m_0x110[2];
  int m_0x128;
  int m_0x12c;
  int m_0x130;
  Vector3D m_0x134[2][2];
} Moby204Props;

typedef struct {
  int m_0x00;
} Moby205Props;

typedef struct {
  short m_0x00;
  short m_0x02;
  Moby *m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  short m_0x14;
} Moby207Props;

typedef struct {
  int m_HeadsInitChecked;
} Moby208Props;

// Dynamic
typedef struct {
  Vector3D m_Velocity;
  int m_Lifetime;
} Moby209Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
} Moby210Props;

// Used by 211 and 212
typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
} Moby211Props;

typedef struct {
  Vector3D m_RespawnPosition;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
} Moby213Props;

typedef struct {
  MobyWanderState m_Wander;
  PathData *m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  Vector3D m_0x30;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
  int m_0x58;
  int m_0x5c;
  int m_0x60;
  int m_0x64;
  Vector3D m_0x68;
} Moby214Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  PathData *m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  Vector3D m_0x30;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
  int m_0x58;
  int m_0x5c;
  int m_0x60;
  int m_0x64;
  Vector3D m_0x68;
} Moby216Props;

typedef struct {
  int m_Timer;
} Moby217Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  Moby *m_0x0c;
  int m_0x10;
} Moby218Props;

typedef struct {
  int m_Initialized;
} Moby222Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  u_char m_0x24;
} Moby225Props;

typedef struct {
  PathData *m_0x00;
  PathData *m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
} Moby226Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
} Moby229Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  Vector3D m_0x08;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int *m_0x30;
  int m_0x34;
} Moby230Props;

typedef struct {
  int m_KnockbackAngle;
  int m_FallKnockbackSpeed;
  // This field is used for multiple purposes unfortunately
  int m_Scratch;
  int m_0x0c;
  int m_IdleAnimCounter;
  Vector3D m_DropTarget;
  int m_ChargeCount;
} Moby231Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
} Moby232Props;

typedef struct {
  MobyWanderState m_Wander;
  int m_0x20;
  int m_0x24;
  int *m_0x28;
  int m_0x2c;
} Moby236Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  short m_0x0c;
  short m_0x0e;
  int m_0x10;
  short m_0x14;
} Moby237Props;

typedef struct {
  MobyWanderState m_Wander;
  int m_0x20;
  int m_0x24;
} Moby238Props;

typedef struct {
  Vector3D m_CameraPosition;
  Vector3D m_CameraRotation;
  int m_CutsceneId; // The ID of the cutscene to play when this Moby is
  int m_Rotation;
  int m_DragonPadLink;
  int m_OldDialogueId; // The ID of the *text* dialogue, used in prototypes
  Vector3D m_Angle;
  int m_IsUnskipable;       // Whether the cutscene can't be skipped
  int m_NameIndex;          // The index of the name in the dragon name table
  int m_CutsceneAudioPitch; // The pitch of the cutscene audio (for sample rate)
  int m_CutsceneTicks;      // The number of ticks the cutscene lasts
  int m_ShakeTimer;
  Vector3D m_AngleStorage; // Used in moby code
  // TODO: Not part of any props struct. Prototypes?
  // int m_PosZStorage;       // Used in moby code
} RescuedDragonMobyProps;

typedef struct {
  Vector3D m_Velocity;
  int m_MinZ;
  Vector3D8 m_AngularVelocity;
  u_char m_Lifetime;
} MobyDragonFragmentProps;

typedef struct {
  Vector3D m_0x00;
  PathData *m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
} Moby253Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
} Moby270Props;

typedef struct {
  PathData *m_0x00;
  Vector3D m_0x04;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
  int *m_0x3c;
  int m_0x40;
  int m_0x44;
  int m_0x48;
} Moby271Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
} Moby283Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
} Moby284Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  PathData *m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
} Moby285Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  PathData *m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  Vector3D m_0x18;
  int m_0x24;
} Moby286Props;

// Used by 288, 289
typedef struct {
  short m_0x00;
  short m_0x02;
  short m_0x04;
  short m_0x06;
  short m_0x08;
  short m_0x0a;
  u_char m_0x0c;
  u_char m_0x0d;
  short m_0x0e;
  int m_0x10;
} Moby288Props;

// Used by 293 and 294
typedef struct {
  int m_0x00;
  PathData *m_0x04;
  PathData *m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  Vector3D m_0x34;
  int m_0x40[3];
  Vector3D m_0x4c;
  int m_0x58[3];
  int m_0x64;
} Moby293Props;

typedef struct {
  Moby *m_0x00;
  int m_0x04;
} Moby295Props;

typedef struct {
  int m_0x00;
  u_int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
} Moby296Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
} Moby298Props;

typedef struct {
  int m_0x00;
  int m_0x04;
} Moby299Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby300Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
} Moby301Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  void *m_0x08;
  int m_0x0c;
  int m_0x10;
  Vector3D m_0x14[3];
} Moby302Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby303Props;

typedef struct {
  PathData *m_0x00;
  Moby *m_0x04;
  Vector3D m_0x08;
  short m_0x14;
} Moby304Props;

typedef struct {
  PathData *m_0x00;
  PathData *m_0x04;
  PathData *m_0x08;
  PathData *m_0x0c;
  int m_0x10;
  Vector3D m_0x14;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
} Moby305Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  Vector3D m_0x20;
  int m_0x2c;
  int m_0x30;
} Moby308Props;

typedef struct {
  int m_Timer;
  int m_BaseRotX;
  int m_BaseRotY;
  int m_BasePosZ;
  int m_HitSpyro;
} Moby312Props;

typedef struct {
  PathData *m_0x00;
  PathData *m_0x04;
  int m_0x08[2];
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
} Moby314Props;

// Dynamic
typedef struct {
  Moby *m_Thrower;
  int m_IsThrown;
  int m_ThrowAngle;
  int m_Lifetime;
  int m_ZVelocity;
} Moby315Props;

typedef struct {
  Vector3D m_0x00;
  int m_0x0c;
} Moby318Props;

typedef struct {
  int m_RespawnClass;
  int m_RespawnTimer;
  int m_RespawnInterval;
} Moby323Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  PathData *m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
} Moby326Props;

typedef struct {
  // Initially -1 to serve as init flag
  int m_CollisionTriIndex;
} Moby328Props;

typedef struct {
  Moby *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby329Props;

// Ice Cavern has two instances with
// m_0x00 = 192
typedef struct {
  int m_0x00;
} Moby331Props;

typedef struct {
  PathData *m_0x00;
  int m_0x04;
  Vector3D m_0x08;
  Vector3D m_0x14;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  int *m_0x40;
  int m_0x44;
  int m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
  int m_0x58;
  int m_0x5c;
} Moby335Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  PathData *m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  Vector3D m_0x18[3];
} Moby339Props;

typedef struct {
  Plane m_CollectionPlane;
  Moby *m_TimeRewardMoby;
  int m_TimeRewardMobyIndex;
  int m_RingCollectableIndex;
} Moby340Props;

typedef struct {
  Moby *m_0x00;
  int m_0x04;
  int m_0x08;
} Moby343Props;

typedef struct {
  int m_0x00;
} Moby345Props;

typedef struct {
  int m_0x00;
} Moby346Props;

typedef struct {
  int m_0x00;
} Moby347Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby349Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
} Moby350Props;

// Might be able to use 340's struct instead
typedef struct {
  Plane m_CollectionPlane;
  Moby *m_0x10;
  int m_0x14;
  int m_0x18;
} Moby353Props;

typedef struct {
  int m_0x00;
  Moby *m_0x04[8];
  Moby *m_0x24[8];
  Moby *m_0x44[8];
  union {
    Moby *m_ResultMobys[8];
    struct {
      Moby *m_CategoryMobys[4];
      int m_ObjectiveClasses[4];
    } fields;
  } m_0x64;
  int m_0x84[4];
  int m_0x94;
  int m_0x98;
  int m_0x9c;
} Moby358Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  PathData *m_0x34;
  int m_0x38;
  PathData *m_0x3c;
  Vector3D m_0x40[2][2];
} Moby370Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  PathData *m_0x20;
  PathData *m_0x24;
  int m_0x28[3];
  int m_0x34;
  int m_0x38;
  int m_0x3c;
  int m_0x40;
  int m_0x44;
} Moby371Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
} Moby372Props;

typedef struct {
  Vector3D m_0x00;
  u_char m_0x0c;
  u_char m_0x0d;
  u_char m_0x0e;
  u_char m_0x0f;
  int m_0x10;
} Moby374Props;

// Used by 375-386
typedef struct {
  Vector3D m_Velocity;
  Vector3D8 m_AngularVelocity;
  // TODO: Should this be kept?
  u_char explicit_pad;
  int m_Lifetime;
} Moby375Props;

// Used by 387, 388, 389, 393
//         394, 396, 490, 491
typedef struct {
  Vector3D m_0x00;
  short m_0x0c;
  short m_0x0e;
  short m_0x10;
} Moby387Props;

typedef struct {
  Moby *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby390Props;

typedef struct {
  // Initially -1 to serve as init flag
  int m_CollisionTriIndex;
  Vector3D m_CollisionTriOffset;
} Moby391Props;

typedef struct {
  Vector3D m_0x00;
  int m_0x0c;
} Moby392Props;

typedef struct {
  PathData *m_0x00;
  short m_0x04;
  short m_0x06;
  u_char m_0x08[2];
  u_char m_0x0a;
  u_char m_0x0b;
  int m_0x0c;
  int m_0x10;
  Vector3D m_0x14;
  int m_0x20;
} Moby395Props;

typedef struct {
  int m_LightCollectibleIndex;
  int m_TimeRewardMobyIndex;
  int m_EnvAnimID;
} Moby397Props;

// 398
typedef struct {
  PathData *m_Path;
  Vector3D m_0x04;
  int m_Sidedness;
  int m_0x14;
  int m_0x18; // Some kinda link? not sure
} MobyPortalPathProps;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
} Moby401Props;

typedef struct {
  int m_0x00;
  Vector3D m_0x04;
  int m_0x10;
  PathData *m_0x14;
  int m_0x18;
} Moby402Props;

typedef struct {
  int m_0x00;
  PathData *m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  Moby *m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
  int m_0x30;
  int m_0x34;
  int m_0x38;
} Moby403Props;

// TODO:
typedef struct {
  PathData *m_Path;
  int m_0x04;
  Vector3D m_0x08;
  int m_LifetimeAfterDamage;
} Moby407Props;
// TODO:
typedef struct {
  PathData *m_Path;
  int m_0x04;
  Vector3D m_0x08;
  int m_LifetimeAfterDamage;
} Moby408Props;

typedef struct {
  MobyWanderState m_Wander;
  int m_0x20;
  int m_0x24;
  int m_0x28;
} Moby412Props;

typedef struct {
  MobyWanderState m_Wander;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_0x2c;
} Moby413Props;

// Dynamic
typedef struct {
  Moby *m_Target;
} Moby414Props;

typedef struct {
  int m_BobCenterZ;
} Moby416Props;

typedef struct {
  int m_0x00;
  int m_0x04;
} Moby417Props;

typedef struct {
  Moby *m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
} Moby421Props;

typedef struct {
  Vector3D m_RespawnPosition;
  PathData *m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28[7];
  int m_0x44;
} Moby453Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  u_char m_0x24;
} Moby461Props;

typedef struct {
  Vector3D m_RespawnPosition;
  PathData *m_0x0c;
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  Vector3D m_0x2c;
  int m_0x38[3];
  int m_0x44;
} Moby466Props;

typedef struct {
  int m_0x00;
  PathData *m_0x04;
  int m_0x08;
  int m_0x0c;
  int m_0x10;
  Moby *m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  Moby *m_0x2c[3];
  Moby *m_0x38;
} Moby467Props;

typedef struct {
  int m_0x00;
  int m_0x04;
  Vector3D m_0x08;
  int m_0x14;
  int m_0x18;
  int m_0x1c;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int *m_0x2c;
  int m_0x30;
  int m_0x34;
  u_char m_0x38;
} Moby476Props;

typedef struct {
  Moby *m_0x00;
  Vector3D m_0x04;
  short m_0x10;
  short m_0x12;
} Moby494Props;

typedef struct {
  int m_0x00[4];
  int m_0x10;
  PathData *m_0x14;
  Vector3D m_0x18;
  Vector3D m_0x24;
  PathData *m_0x30;
  PathData *m_0x34;
  PathData *m_0x38;
  PathData *m_0x3c;
  PathData *m_0x40;
  int m_0x44;
  Moby *m_0x48;
  int m_0x4c;
  int m_0x50;
  int m_0x54;
  int m_0x58;
  int m_0x5c;
  int m_0x60;
  int m_0x64;
  int m_0x68;
  int m_0x6c[2];
  Vector3D m_0x74;
} Moby495Props;

typedef struct {
  int m_0x00[4];
  int m_0x10;
  int m_0x14;
  int m_0x18;
  int m_0x1c[5];
  int m_0x30;
} Moby497Props;

typedef struct {
  Vector3D16 m_Velocity;
  Vector3D16 m_AngularVelocity;
  u_char m_Lifetime;
  u_char m_0x0d;
  short m_0x0e;
  int m_0x10;
} Moby502Props;

extern Moby *g_Sparx;

// static_assert(sizeof(Moby) == 0x58, "Incorrect Moby size");

typedef struct {
  Tiledef shadow;
  int *shadow_list; // shadow queue?
} MobyShadow;

extern MobyShadow g_MobyShadows;

/// @brief Are any mobys in this pod still alive?
int func_8003B0DC(int pPod);

/// @brief Are all mobys in this pod in this state? (Unused)
int func_8003B160(int pPod, u_int pState);

extern u_short **g_MobyPods; // Pointer to the Moby pods data, the last Moby
                             // in the list has the top bit set.
extern int g_MobyPodCount;   // The number of pods in the current level

extern Moby *g_KeyMoby; // Pointer to the key Moby for this level

extern Moby *g_LevelMobys; // The Mobys in the current level

/// @brief Pointer to space for the Moby collision chain
extern void *g_MobyCollisionChain;

/// @brief Moby allocation pointer
extern Moby *g_MobyAllocPtr;

/// @brief Props allocation pointer
extern void *g_PropsAllocPtr;

/// @brief Start of the Mobys that are dynamically allocated
extern Moby *g_DynMobys;

/// @brief The current number of dynamically allocated Mobys
extern int g_DynMobyCount;

/// @brief The maximum number of dynamically allocated Mobys
extern int g_DynMobyMax;

/// @brief The end of dynamic Moby space (= start + max * (sizeof(Moby) + 24))
extern void *g_DynMobySpaceEnd;

#define DYN_MOBY_FREE_COUNT (g_DynMobyMax - g_DynMobyCount)

extern Moby *g_HudMobys; // HUD Mobys

extern signed char g_MobyShakeOffsets[32]
                                     [2]; // To shake dragons and various chests

extern u_int D_8006E44C[17]; // Specular shaded color list

#endif // !__MOBY_H
