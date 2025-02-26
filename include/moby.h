#ifndef __MOBY_H
#define __MOBY_H

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
  /// distnace
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
  char m_Substate;

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
  // 0 = Specular 1/2 = metal (2 being rotated)
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

// Data related
typedef struct {
  u_char m_NodeCount;
  u_char m_CurrentNode;
  char unk_0x2[4]; // No clue, padding? Usually 0
  short unk_0x6;   // Who knows (-1 or 1, might be winding?)
  struct {
    Vector3D m_Position;
    int unk_0xC; // Padding I assume
  } m_Nodes[1];
} PathData;

// Moby models

typedef struct {
  // Vertex offset:    00000000000111111111111111111111
  // Collision model:  00000000111000000000000000000000
  // Frame sound:      11111111000000000000000000000000
  union {

    // Not sure if this will match, but there's only one way to find out
    struct {
      u_int m_VertexOffset : 12;
      u_int m_CollisionModel : 3;
      u_int m_FrameSound : 8;
    } m_Props;
    u_int m_Data;
  } m;

  u_short m_VertexColorOffset;
  u_char m_Shadow;
  u_char m_ShortOffset;
} AnimationFrame;

typedef struct {
  u_char m_NumFrames;
  u_char _Padding1;
  u_short m_NumColors;
  u_char m_Unk1; // Changes something about the model format, but never used
  u_char m_Scale;
  u_char m_ShortEncodeShift;
  u_char m_Radius;
  u_char m_VertCountHigh;
  u_char m_VertCountLow;
  u_char m_Padding2;
  u_char m_MulSomething;
  u_char m_MaxProgress;
  u_char m_Padding3;
  u_short m_Padding4;
  void *m_Unk2; // Used when m_unk1 is set, but that is never used, so it
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

typedef struct {
  int m_NumAnimations; // < 0 == SimpleModel
  void *m_Verts;
  void *m_Colors;
  void *m_Faces;
} SimpleModel;

// static_assert(sizeof(Moby) == 0x58, "Incorrect Moby size");

/// @brief Are any mobys in this pod still alive?
int func_8003B0DC(int pPod);

/// @brief Are all mobys in this pod in this state? (Unused)
int func_8003B160(int pPod, u_int pState);

extern u_short **g_MobyPods; // Pointer to the Moby pods data, the last Moby
                             // in the list has the top bit set.
extern int g_MobyPodCount;   // The number of pods in the current level

extern Moby *D_80075828; // The Mobys in the current level

extern Moby *D_80075890; // Pointer to the first dynamic Moby, used for
                         // delimiting static and dynamic Mobys

extern Moby *D_80075710; // HUD Mobys

#endif // !__MOBY_H