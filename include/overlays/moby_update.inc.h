#include "42CC4.h"
#include "balloonist.h"
#include "camera.h"
#include "checkpoint.h"
#include "collision.h"
#include "common.h"
#include "cutscene.h"
#include "cyclorama.h"
#include "dragon.h"
#include "environment.h"
#include "gamepad.h"
#include "gamestates/draw.h"
#include "gamestates/init.h"
#include "graphics.h"
#include "hud.h"
#include "loaders.h"
#include "math.h"
#include "moby.h"
#include "moby_helpers.h"
#include "moby_lists.h"
#include "overlay_pointers.h"
#include "rand.h"
#include "renderers.h"
#include "sony_image.h"
#include "special_surfaces.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"
#include "vector.h"

extern struct {
  Vector3D16 m_LocalOffset;
  Vector3D16 m_Velocity;
} D_8006E614[3];

extern int D_800757C4;

// Find out exact size
// props->m_0x18 of Class 398 ranges from -1 to 5
extern SphericalCoordsOffset D_8006CA24[];

// Gem pickup particle color lookup?
extern int D_8006E47C[];

extern int D_8006E3E4[];

// Fix type
extern int D_8006E490;
extern int D_8006E494;

extern Vector3D D_8006E57C[3];
extern Vector3D D_8006E5A0;
extern Vector3D D_8006E5AC;
extern Vector3D D_8006E5B8;
extern Vector3D D_8006E5C4[];

// Spring chest and fireworks chest color lookup
extern int D_8006E678[];

extern Vector3D D_8006E824[];

extern u_short D_80073094[];

// Symbolize these properly
extern int D_8007577C;
extern int D_80075838[2];
extern int D_80075840;
extern int D_80075850;
extern int D_80075854;
extern int D_80075870[2];
extern int D_800758F4;
extern int D_800758F8;
extern int D_80075900;
extern int D_80075908;
extern int D_800770F8[4];
extern Vector3D D_80077858;

void NAME_OVERLAY_FUNCTION(UpdateMoby)(void) {

  Moby **mobyList;
  Moby *moby;
  // Generate the moby update list (which looks at things such as the state and
  // distance)
  func_80051FEC();

  func_800522C0((Moby **)(g_SonyImage.u.m_Buf + 0x400), 0);

  if (g_DeltaTime > 2) {
    func_800522C0((Moby **)(g_SonyImage.u.m_Buf + 0x400),
                  g_DeltaTime == 3 ? 0x80000001 : 0x80000000);
  }

  mobyList = (Moby **)(g_SonyImage.u.m_Buf + 0x400);

  while (moby = *mobyList++) {
    if (!(moby->m_State < 0x80))
      continue;

    g_AnimationFinished = moby->m_AnimationState.m_AnimationFlags & 2;
    g_AnimFrameFinished = moby->m_AnimationState.m_AnimationFlags & 1;
    D_800756C4 = g_DeltaTime; // Deltatime used in overlays, dunno why

    switch (moby->m_Class) {
#ifdef HAS_MOBY_1
    case 1: { // Portal text
      int shouldSpawnText, cameraPortalAngleDiff;
      int distance = OctDistance(&moby->m_Position, &g_Camera.m_Position);

      if (distance < (moby->m_State ? 12 : 11) * 1024) {
        shouldSpawnText = moby->m_State == 0;

        moby->m_State = 1;

        // Subtract the angle between us and the camera from the portal
        // rotation
        cameraPortalAngleDiff =
            func_80017908(moby->m_Rotation.z,
                          ANGLE_FROM(moby->m_Position, g_Camera.m_Position));

        // You're facing the rotation of the portal
        if (cameraPortalAngleDiff <= ROTDEG8(80)) {
          if (moby->m_Substate == 1) {
            // Retrigger
            shouldSpawnText = 1;
          }

          // Rotate the text by 180 degrees
          moby->m_Substate = 0;
        } else if (cameraPortalAngleDiff >
                   ROTDEG8(100)) { // You're facing against the rotation of
                                   // the portal
          if (moby->m_Substate == 0) {
            // Retrigger
            shouldSpawnText = 1;
          }

          // Keep the portal rotation
          moby->m_Substate = 1;
        } else {
          // You're facing the portal in the 20 degree deadzone
          // Disable the text
          moby->m_State = 0;
        }

        if (moby->m_State && shouldSpawnText) {
          // Create the portal text
          func_8003C358(moby, 1);
        }
      } else {
        moby->m_State = 0;
      }

      break;
    }
#endif
#ifdef HAS_MOBY_9
    case MOBYCLASS_EXIT_VORTEX: {
      Moby9Props *vortexProps;
      int distance;
      int i;

      vortexProps = moby->m_Props;

      distance = OctDistance(&moby->m_Position, &g_Camera.m_Position);

      if ((moby->m_State != 0 && distance < 0x2800) ||
          (moby->m_State == 0 && distance < 0x2400)) {
        if (moby->m_State == 0) {
          moby->m_Position.z += 0x600;
          func_8003C358(moby, 0);
          moby->m_Position.z -= 0x600;
        }
        moby->m_State = 1;
      } else {
        moby->m_State = 0;
      }

      distance = DISTANCE_TO_SPYRO(moby);

      for (i = 0; i < g_DeltaTime; i++) {
        vortexProps->m_0x04++;
        if (distance < 0x4000) {
          if (!(vortexProps->m_0x04 % 4)) {
            g_SpawnParticle(1, 21, &moby->m_Position, vortexProps->m_0x04);
          }
        } else if ((vortexProps->m_0x04 & 15) < 8) {
          if (!(vortexProps->m_0x04 % 4)) {
            g_SpawnParticle(1, 76, &moby->m_Position, vortexProps->m_0x04);
          }
        }
      }

      if (distance < 0x400) {
        int zDelta;
        zDelta = g_Spyro.m_Position.z - moby->m_Position.z;
        if (0x200 < zDelta && zDelta < 0x4000) {
          // heighLimit is m_0x0c if m_0x0c is non-zero, 0x2000
          // otherwise
          int heightLimit = vortexProps->m_0x0c ?: 0x2000;

          if (g_Spyro.m_State == 0x11 ||
              g_Spyro.m_Position.z + 0xc00 < moby->m_Position.z + heightLimit) {
            if (g_Hud.m_GemDisplayState == HDS_Open) {
              HudGemUpdate();
            }
            g_Spyro.m_ControlFlags = 0x80008000;
            g_Spyro.m_mobyInUseBySpyro = moby;
            g_Spyro.m_DamageFlags |= 0x800;
            g_Spyro.m_portalEndPos.z = moby->m_Position.z + 0x4000;
            VecCopy(&g_Spyro.unk_0x17c, &moby->m_Position);
            if (heightLimit < zDelta) {
              int camPitch;
              camPitch = g_Camera.m_Rotation.y & 0xfff;
              if (camPitch > 0x800) {
                camPitch -= 0x1000;
              }
              if (camPitch < -0x200) {
                g_LevelVortexExitFlags[g_LevelIndex] = 1;
                g_LoadStage = 0;
                D_8007576C = -1;
                g_HasLevelTransition = 1;
                g_LevelTransHudActive = 1;
                g_LevelTransTicks = 0;
                g_Gamestate = GS_LevelTransition;
                g_StateSwitch = 1;
                g_PortalLevelId = g_LevelId;
                g_NextLevelId = (g_LevelId / 10) * 10;
                g_Camera.unk_0xC0 = 0x80000012;
                g_Spyro.m_ControlFlags = 0;
                func_8004AC24(0);
                g_Spyro.m_flyingAbility = 0;
                g_SpyroFlame.m_FairyKissTimer = 0;
              }
            }
          }
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_10
    case 10: {

      Moby10Props *props = (Moby10Props *)moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 3) {
        moby->m_DamageFlags = 0;
        props->m_0x1c = ANGLE_FROM_SPYRO(moby->m_Position);

        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          props->m_0x20 = 200;
        } else {
          props->m_0x20 = 400;
        }

        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_RESTART(moby, 3);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        func_80038458(moby);

        if (DISTANCE_TO_SPYRO(moby) < 0x1400 &&
            SPYRO_ORIGIN_Z_DISTANCE(moby) < 0x400) {
          if (moby->m_Pod != 0xFF) {
            Moby **scan = (Moby **)(g_SonyImage.u.m_Buf + 0x400);
            Moby *other;

            while ((other = *scan++) != nullptr) {
              Moby10Props *otherProps = (Moby10Props *)other->m_Props;

              if (other->m_Pod == moby->m_Pod && other->m_State == 0) {
                if (otherProps->m_0x0c->m_CurrentNode ==
                    props->m_0x0c->m_CurrentNode) {
                  other->m_State = 1;
                  otherProps->m_0x30 = RandRange(6, 0x28);
                }
              }
            }
          }

          moby->m_State = 1;
          continue;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);

        break;
      }
      case 1: {
        int spyroAngle;
        int angle;
        int angle2;
        int previousAngle;
        int nextNode;
        int previousNode;
        int distance;
        int angleScale;
        int nextAngle;

        spyroAngle = ANGLE_TO_SPYRO(moby->m_Position);
        nextNode =
            (props->m_0x0c->m_CurrentNode + 1) % props->m_0x0c->m_NodeCount;
        previousNode =
            (props->m_0x0c->m_CurrentNode - 1 + props->m_0x0c->m_NodeCount) %
            props->m_0x0c->m_NodeCount;

        nextAngle = ANGLE_FROM(moby->m_Position,
                               PATH_NODE_POS(props->m_0x0c, nextNode));
        previousAngle = ANGLE_FROM(moby->m_Position,
                                   PATH_NODE_POS(props->m_0x0c, previousNode));

        if (func_80017908(spyroAngle, nextAngle) >
            func_80017908(spyroAngle, previousAngle)) {
          props->m_0x0c->m_CurrentNode = nextNode;
        } else {
          props->m_0x0c->m_CurrentNode = previousNode;
        }

        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x0c));
        angle = (angle + RandRange(-0x20, 0x20)) & 0xFF;
        angle2 = ANGLE_FROM_SPYRO(moby->m_Position);
        angleScale = 108;
        angle2 += (func_800381BC(angle2, angle) * angleScale) >> 7;
        angle2 &= 0xFF;
        props->m_0x1c = angle2;
        props->m_0x24 = RandRange(110, 0xA0);
        props->m_0x20 = 0;
        distance = OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x0c));
        props->m_0x28 = (distance / props->m_0x24) >> 1;

        if (props->m_0x28 >= 0x5B) {
          props->m_0x28 = 0x5A;
        }

        moby->m_State = 2;
        continue;
      }
      case 2: {
        int distance =
            OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x0c));

        if (TICK_TIMER(props->m_0x30)) {

          if (props->m_0x20 < props->m_0x24) {
            props->m_0x20 += 0xA;
          }

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

          if (TICK_TIMER(props->m_0x28)) {
            int angleDelta;
            int turn;

            angleDelta = func_800381BC(
                ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x0c)),
                props->m_0x1c);
            turn = 1;

            if (ABS2(angleDelta) >= 0x1F) {
              turn = 2;
            }

            if (angleDelta > 0) {
              props->m_0x1c -= turn;
              props->m_0x1c &= 0xFF;
            } else if (angleDelta < 0) {
              props->m_0x1c += turn;
              props->m_0x1c &= 0xFF;
            }
          }

          if (RotateMobyToAngle(moby, props->m_0x1c, 6, 0x14, 1) != 0) {
            if (func_80039398(moby, props->m_0x20, 300, 300, 0x15) != 0) {
              props->m_0x2c++;
            } else {
              props->m_0x2c = 0;
            }
            if (props->m_0x2c >= 4 && g_AnimationFinished) {
              if (distance < 0x1400) {
                moby->m_State = 0;
                continue;
              }
              props->m_0x1c =
                  func_80038074(props->m_0x1c, RandRangeSigned(60, 100));
            }
          }
          if (distance < 0xC00 && g_AnimationFinished) {
            moby->m_State = 0;
            continue;
          }
        }

        break;
      }

      case 3: {
        if (props->m_0x20 >= 0x10) {
          props->m_0x20 -= 0xF;
          func_80039688(moby, props->m_0x1c, props->m_0x20, 0, 700, 5);
        }

        if (g_AnimationFinished) {
          func_80052568(moby);
          continue;
        }

        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_11 // Waterfall Particle Spawner
    case 11: {
      Moby11Props *props = moby->m_Props;

      if (TICK_TIMER(props->m_Timer)) {
        g_SpawnParticle(1, 22, &moby->m_Position, 0);
        props->m_Timer = rand() & 0xE;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_13
    case MOBYCLASS_GEM_SPAWNER: {
      Moby *parent;
      Moby13Props *spawnerProps;
      spawnerProps = (Moby13Props *)moby->m_Props;
      parent = &g_LevelMobys[spawnerProps->m_0x00];

      if (spawnerProps->m_0x10 == 0) {
        if (spawnerProps->m_0x18 != 0) {
          VecSub(&spawnerProps->m_0x04, &spawnerProps->m_0x04,
                 &parent->m_Position);
          moby->m_UpdateDistance = 255;
        } else {
          moby->m_UpdateDistance = 32;
        }

        if (spawnerProps->m_0x14 != 0 &&
            (parent->m_State >= 0x80 || (parent->m_DropMoby & 0x80))) {
          Moby *dst;
          Moby *src;
          int newIndex;

          parent->m_DropMoby = moby->m_DropMoby;
          func_80052568(moby);
          if (parent->m_State < 0x80) {
            func_80052568(parent);
          }

          dst = moby;
          src = parent;
          *dst = *src;
          func_800526A8(moby);
          moby->m_WasDrawn = 1;

          newIndex = moby - g_LevelMobys;

          for (parent = g_LevelMobys; parent < (Moby *)g_DynMobys; parent++) {
            Moby13Props *mp;
            if (parent == moby)
              continue;
            if (parent->m_State >= 0x80)
              continue;
            if (parent->m_Class != MOBYCLASS_GEM_SPAWNER)
              continue;
            mp = (Moby13Props *)parent->m_Props;
            if (mp->m_0x00 == spawnerProps->m_0x00) {
              mp->m_0x00 = newIndex;
            }
          }

          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          break;
        } else {
          spawnerProps->m_0x10 = 1;
        }
      }

      if (spawnerProps->m_0x18 != 0) {
        VecCopy(&moby->m_Position, &parent->m_Position);
      }

      if (spawnerProps->m_0x1c != 0) {
        if (TICK_TIMER(spawnerProps->m_0x1c)) {
          if (spawnerProps->m_0x18 != 0) {
            VecAdd(&spawnerProps->m_0x04, &spawnerProps->m_0x04,
                   &moby->m_Position);
          } else {
            VecCopy(&moby->m_Position, &parent->m_Position);
          }

          spawnerProps->m_0x04.z += 1024;

          if (spawnerProps->m_0x24 != 0) {
            func_8003ABC0(moby, 4, 0, nullptr);
          } else if (func_8004D5EC(&spawnerProps->m_0x04, 0x1400) != 0) {
            spawnerProps->m_0x04.z -= 1024;
            func_8003ABC0(moby, 2, 0, &spawnerProps->m_0x04);
          } else {
            func_8003ABC0(moby, 1, 0, nullptr);
          }

          func_8003B7C0(moby);

          spawnerProps->m_0x20 <<= 7;
          g_Spu.m_NextSoundOverrideFlags = 2;
          g_Spu.m_PitchOverride =
              g_Spu.m_SoundDefinitions[g_Spu.m_SoundTable->titlescreenMove]
                  .m_Pitch +
              spawnerProps->m_0x20;
          PlaySound(g_Spu.m_SoundTable->titlescreenMove, moby, 8,
                    &moby->m_SoundChannel);
          func_80052568(moby);
        }
      } else if (moby->m_Substate != 0 || parent->m_State >= 0x80) {
        spawnerProps->m_0x1c = 9;
        spawnerProps->m_0x20 = 1;

        for (parent = g_LevelMobys; parent < moby; parent++) {
          Moby13Props *mp;
          if (parent->m_State >= 0x80)
            continue;
          if (parent->m_Class != MOBYCLASS_GEM_SPAWNER)
            continue;
          mp = (Moby13Props *)parent->m_Props;
          if (mp->m_0x00 == spawnerProps->m_0x00) {
            spawnerProps->m_0x1c += 9;
            spawnerProps->m_0x20 += 1;
          }
        }

        if (spawnerProps->m_0x20 == 1) {
          g_Spu.m_NextSoundOverrideFlags = 2;
          g_Spu.m_PitchOverride =
              g_Spu.m_SoundDefinitions[g_Spu.m_SoundTable->titlescreenMove]
                  .m_Pitch;
          PlaySound(g_Spu.m_SoundTable->titlescreenMove, moby, 8,
                    &moby->m_SoundChannel);
        }
      }
      break;
    }
#endif
    case MOBYCLASS_BUTTERFLY: { // Butterfly
      MobyButterflyProps *butterflyProps = moby->m_Props;

      if (g_Spyro.m_health < 3 && DISTANCE_TO_SPYRO(moby) < 2400) {
        // We're in range and Spyro's health isn't full
        if (SPYRO_BASE_Z_DISTANCE(moby) < 1800) {

          if (g_Sparx == nullptr) {             // If Sparx is not alive
            if (g_Spyro.m_health >= 0) {        // And Spyro isn't dead
              g_Sparx = g_SpawnMoby(120, moby); // Spawn Sparx

              // Play the sound
              func_8003851C(g_Sparx, 0, nullptr);

              g_Spyro.m_health = 1;

              func_80052568(moby); // Kill the Butterfly
              break;
            }
          } else if (g_Sparx->m_Substate != 99) {
            MobySparxProps *sparxProps = g_Sparx->m_Props;

            // Sparx is alive, and not chasing something already
            if (sparxProps->m_Target == nullptr) {
              // Set him to chase us
              if (func_800381BC(g_Spyro.m_bodyRotation.z,
                                ANGLE_FROM_SPYRO(moby->m_Position)) < 0) {
                butterflyProps->m_0x00 = 1;
              } else {
                butterflyProps->m_0x00 = -1;
              }

              g_Sparx->m_Substate = 0;
              sparxProps->m_Target = moby;
              sparxProps->m_Timer = RandRange(150, 210);

              moby->m_State = 1;
            }
          }
        }
      }

      if (moby->m_RenderRadius & 0x80)
        break;

      switch (moby->m_State) {
      case 0: {
        // Timer running, exit
        // Wasn't drawn last frame, exit
        if (!TICK_TIMER(butterflyProps->m_0x14) || moby->m_WasDrawn) {
          int refHeight, rotated, moved;

          if (TICK_TIMER(butterflyProps->m_0x12)) {
            int r = RandRangeSigned(30, 90);
            if (rand() & 1) {
              r = -r;
            }

            butterflyProps->m_0x11 = func_80038074(butterflyProps->m_0x11, r);
            butterflyProps->m_0x12 = RandRange(60, 140);
          }

          if (TICK_TIMER(butterflyProps->m_0x13)) {
            butterflyProps->m_0x10 = RandRangeSigned(10, 25);
            butterflyProps->m_0x13 = RandRange(80, 140);
          }

          if (butterflyProps->m_0x10 >= 128) {
            moby->m_Position.z =
                moby->m_Position.z + (butterflyProps->m_0x10 - 256);
          } else {
            moby->m_Position.z = moby->m_Position.z + butterflyProps->m_0x10;
          }

          refHeight = moby->m_Position.z - func_80038340(moby);

          if (refHeight < 300) {
            butterflyProps->m_0x10 = RandRange(10, 25);
            butterflyProps->m_0x13 = RandRange(80, 140);
          }

          if (1024 < refHeight && refHeight < 2048) {
            butterflyProps->m_0x10 = -RandRange(10, 25);
            butterflyProps->m_0x13 = RandRange(80, 140);
          }

          rotated = RotateMobyToAngle(moby, butterflyProps->m_0x11, 4, 0xA, 1);
          moved = func_80039398(moby, 30, 0, 50, 1);

          if (rotated && moved) {
            butterflyProps->m_0x11 =
                func_80038074(butterflyProps->m_0x11, RandRange(98, 158));
            butterflyProps->m_0x12 = RandRange(30, 80);
          }

          // Check distance to target position
          if (OctDistance(&moby->m_Position, &butterflyProps->m_0x04) > 2000) {
            // Too far from target, turn directly towards it
            int angle = ANGLE_FROM(moby->m_Position, butterflyProps->m_0x04);

            butterflyProps->m_0x11 = angle;
            butterflyProps->m_0x12 = 40;
          }
        } else {
          func_80052568(moby);
        }
        break;
      }
      case 1: {
        func_80038638(moby, &g_Spyro.m_Position, 800,
                      func_80038074(ANGLE_FROM_SPYRO(moby->m_Position),
                                    butterflyProps->m_0x00 * 8),
                      8, 0x82, 0xE, 0x80, 0xFF, 0xFF, 0, 0, 0);

        // If Sparx is not alive, or is chasing something
        if (g_Sparx == nullptr || g_Sparx->m_Substate == 99) {
          moby->m_State = 0;
        } else {
          int refHeight;

          // Timer
          if (TICK_TIMER(butterflyProps->m_0x13)) {
            butterflyProps->m_0x10 = RandRangeSigned(5, 20);
            butterflyProps->m_0x13 = RandRange(40, 80);
          }

          if (butterflyProps->m_0x10 >= 128) {
            moby->m_Position.z =
                (moby->m_Position.z) + (butterflyProps->m_0x10 - 256);
          } else {
            moby->m_Position.z = moby->m_Position.z + butterflyProps->m_0x10;
          }

          refHeight = moby->m_Position.z - func_80038340(moby);

          if (refHeight < 200) {
            butterflyProps->m_0x10 = RandRange(5, 20);
            butterflyProps->m_0x13 = RandRange(40, 80);
          }

          if (1000 < refHeight && refHeight < 2048) {
            butterflyProps->m_0x10 = -RandRange(5, 20);
            butterflyProps->m_0x13 = RandRange(40, 80);
          }
        }
        break;
      }
      }

      break;
    }
#ifdef HAS_MOBY_17
    case 17: {
      Moby17Props *props = moby->m_Props;
      Vector3D position;

      if (!TICK_TIMER(props->m_0x0c)) {
        VecAdd(&position, &moby->m_Position, &props->m_0x00);

        if (!func_8004AE38(&moby->m_Position, &position) &&
            !func_8004E2E8(&moby->m_Position, 0, 1)) {
          VecCopy(&moby->m_Position, &position);
          break;
        }
      }
      func_80052568(moby);
      break;
    }
#endif
#ifdef HAS_MOBY_18
    case 18: {
      Moby18Props *props = moby->m_Props;
      int active = ((u_int *)D_80077908)[30 * 4] & 1;

      switch (moby->m_Substate) {
      case 0: {
        if (DISTANCE_TO_SPYRO(moby) < 0x500 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x280) {
          if ((g_LevelMobys[props->m_0x04].m_Substate >> props->m_0x00) & 1) {
            g_LevelMobys[props->m_0x04].m_Substate = 0;
          } else {
            g_LevelMobys[props->m_0x04].m_Substate |= 1 << props->m_0x00;
          }
          moby->m_Substate = 1;
        }
        break;
      }

      case 1: {
        if (DISTANCE_TO_SPYRO(moby) > 0x600 ||
            SPYRO_BASE_Z_DISTANCE(moby) > 0x2C0) {
          moby->m_Substate = 0;
        }
        break;
      }
      }

      if (g_LevelMobys[props->m_0x04].m_State == 10) {
        if ((moby->m_State & 1) == 0) {
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
        }
        break;
      }

      if (g_LevelMobys[props->m_0x04].m_State == 11) {
        if ((moby->m_State & 1) != 0) {
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
        }
        break;
      }

      if (((g_LevelMobys[props->m_0x04].m_Substate >> props->m_0x00) & 1) !=
              0 &&
          active != 0 && g_LevelMobys[props->m_0x04].m_State < 99) {
        if ((moby->m_State & 1) == 0) {
          g_Spu.m_NextSoundOverrideFlags = 2;
          g_Spu.m_PitchOverride =
              g_Spu.m_SoundDefinitions[g_Spu.m_SoundTable->titlescreenMove]
                  .m_Pitch +
              D_80073094[props->m_0x00];
          PlaySound(g_Models[moby->m_Class]->m_Sounds[0], moby, 8,
                    &moby->m_SoundChannel);
        }
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
      } else if ((moby->m_State & 1) != 0) {
        moby->m_State = 0;
        MOBY_ANIM_RESTART(moby, 0);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_23
    case 23: {
      Moby23Props *props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 4 && moby->m_State != 5 && moby->m_State != 9) {
        props->m_0x10 = func_80038098(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        props->m_0x18 = 2;
        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
          props->m_0x14 = 250;
        }
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          moby->m_State = 9;
          MOBY_ANIM_RESTART(moby, 9);
          break;
        }
        moby->m_State = 4;
        MOBY_ANIM_CHANGE(moby, 4);
        break;
      }

      TICK_TIMER(props->m_0x20);
      if (DISTANCE_TO_SPYRO(moby) > 0xC00) {
        props->m_0x20 = 0;
      }

      if (moby->m_AnimationState.m_Animation == 8 && props->m_0x44 == 0 &&
          DISTANCE_TO_SPYRO(moby) < 0x600 &&
          func_80017908(moby->m_Rotation.z, ANGLE_TO_SPYRO(moby->m_Position)) <
              0x20) {
        int angle = (moby->m_Rotation.z + ROTDEG8(45)) & 0xFF;
        g_Spyro.m_DamageFlags |= 0x80;
        g_Spyro.unk_0x208.x = FIXED_MUL(COSINE_8(angle), 80);
        g_Spyro.unk_0x208.y = FIXED_MUL(SINE_8(angle), 80);
        g_Spyro.unk_0x208.z = 120;
        props->m_0x44 = 1;
      }

      switch (moby->m_State) {
      case 0: {
        switch (props->m_0x34) {
        case 0: {
          RotateMobyToSpyro(moby, 0xA, 0, 0);
          if (SPYRO_BASE_Z_DISTANCE(moby) < 800 &&
              DISTANCE_TO_SPYRO(moby) < 0x2000) {
            props->m_0x1c = 0;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
          break;
        }
        case 1: {
          props->m_0x14 = 100;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          moby->m_State = 98;
          continue;
        }
        case 2: {
          props->m_0x14 = 100;
          props->m_0x38->m_CurrentNode = 0;
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        }
        break;
      }
      case 1: {
        switch (props->m_0x34) {
        case 0: {
          int angle;
          if (TICK_TIMER(props->m_0x0c)) {
            props->m_0x10 = g_Spyro.m_bodyRotation.z;
            props->m_0x0c = 0x1E;
          }
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          RotateMobyToAngle(moby, angle, 4, 0x1E, 1);
          if (func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) >= 0x31) {
            if (props->m_0x1c != 0) {
              if (TICK_TIMER(props->m_0x1c)) {
                props->m_0x1c = 0;
                moby->m_State = 100;
                continue;
              }
            } else {
              props->m_0x1c = 0x28;
            }
          } else {
            props->m_0x1c = 0;
          }
          if (func_80039398(moby, 100, 0x300, 0x200, 0x25) != 0 ||
              OctDistance(&moby->m_Position, &props->m_0x00) > 0x2800) {
            moby->m_State = 100;
            continue;
          }
          if (props->m_0x20 == 0 && DISTANCE_TO_SPYRO(moby) < 0x800 &&
              func_80017908(moby->m_Rotation.z,
                            ANGLE_TO_SPYRO(moby->m_Position)) < ROTDEG8(90)) {
            props->m_0x20 = 0x78;
            props->m_0x44 = 0;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
          }
          if (moby->m_AnimationState.m_Animation == 8 && g_AnimationFinished) {
            moby->m_State = 100;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            continue;
          }
          break;
        }
        case 2: {
          if ((g_LevelMobys[props->m_0x40].m_State & 128) == 0 ||
              OctDistance(&moby->m_Position, &props->m_0x00) > 0x400) {
            int angle =
                ANGLE_FROM(PATH_CUR_POS(props->m_0x38), moby->m_Position);
            func_80038638(moby, &PATH_NODE_POS(props->m_0x38, 0), props->m_0x3c,
                          (angle - 3) & 0xFF, 0, props->m_0x14, 0x1E, 0x80,
                          0xFF, 0xFF, 0, 0, 4);
            if (props->m_0x20 == 0 && DISTANCE_TO_SPYRO(moby) < 0x800 &&
                func_80017908(moby->m_Rotation.z,
                              ANGLE_TO_SPYRO(moby->m_Position)) < 0x40) {
              props->m_0x20 = 0x78;
              props->m_0x44 = 0;
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
            }
            if (moby->m_AnimationState.m_Animation == 8 &&
                g_AnimationFinished) {
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
              continue;
            }
            break;
          }
          props->m_0x34 = 1;
          props->m_0x38->m_CurrentNode = 1;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        }

        break;
      }
      case 2: {
        if (props->m_0x14 > 0) {
          func_80039398(moby, props->m_0x14, 0x300, 0x200, 0x27);
          props->m_0x14 -= 8;
        }
        if (g_AnimationFinished) {
          moby->m_Rotation.z += 0x80;
          props->m_0x38->m_CurrentNode =
              (props->m_0x38->m_CurrentNode + 1) % props->m_0x38->m_NodeCount;
          if (props->m_0x38->m_CurrentNode == 0 &&
              props->m_0x38->m_NodeCount >= 3) {
            props->m_0x38->m_CurrentNode++;
          }
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      case 4: {
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          moby->m_State = 9;
          MOBY_ANIM_SET_NEXT(moby, 9);
          continue;
        }
        if (g_AnimationFinished) {
          props->m_0x1c = (rand() & 0x3F) + 0x40;
          moby->m_State = 5;
          MOBY_ANIM_RESTART(moby, 5);
          continue;
        }
        if (moby->m_AnimationState.m_Frame < 5) {
          moby->m_Rotation.z += props->m_0x18;
        }
        if (props->m_0x14 >= 0x10) {
          props->m_0x14 -= 0xF;
          func_80039688(moby, props->m_0x10, props->m_0x14, 0, 300, 5);
        }
        break;
      }
      case 5: {
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          moby->m_State = 9;
          MOBY_ANIM_SET_NEXT(moby, 9);
          continue;
        }
        switch (moby->m_AnimationState.m_Animation) {
        case 4: {
          if (g_AnimationFinished) {
            moby->m_State = 5;
            MOBY_ANIM_RESTART(moby, 5);
          }
          continue;
        }
        case 5: {
          if (TICK_TIMER(props->m_0x1c)) {
            if (DISTANCE_TO_SPYRO(moby) > 0x2800) {
              func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
              func_800385BC(moby, 0x20);
              func_80052568(moby);
              continue;
            }
            if (moby->m_AnimationState.m_Animation != 6) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 6);
            }
            moby->m_AnimationState.m_Frame = 0x31;
            moby->m_AnimationState.m_NextFrame = 0x32;
            moby->m_AnimationState.m_FrameProgress = 0;
          }
          continue;
        }
        case 6: {
          if (moby->m_AnimationState.m_Frame >= 44 &&
              moby->m_AnimationState.m_Frame < 50) {
            moby->m_DamageFlags = 0;
            props->m_0x1c = (rand() & 0x3F) + 0x40;
            if (moby->m_AnimationState.m_Animation != 5) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 5);
            }
          }
          continue;
        }
        default: {
          continue;
        }
        }
      }
      case 9: {
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x20);
          func_80052568(moby);
        }
        break;
      }
      case 98: {
        int angle;
        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x38)) <
            0x80) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x38));
        RotateMobyToAngle(moby, angle, 4, 0x14, 1);
        func_80039398(moby, props->m_0x14, 0x300, 0x200, 0x27);
        if (props->m_0x20 == 0 && DISTANCE_TO_SPYRO(moby) < 0x800 &&
            func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) < 0x40) {
          props->m_0x20 = 0x78;
          props->m_0x44 = 0;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
        }
        if (moby->m_AnimationState.m_Animation == 8 && g_AnimationFinished) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          continue;
        }
        break;
      }
      case 100: {
        int angle = Atan2Fast(props->m_0x00.x - moby->m_Position.x,
                              props->m_0x00.y - moby->m_Position.y);
        if (RotateMobyToAngle(moby, angle, 4, 0x14, 1) != 0) {
          func_80039398(moby, 0x5A, 0x300, 0x200, 0x27);
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (OctDistance(&moby->m_Position, &props->m_0x00) < 0x80) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_28
    case 28: {
      Moby28Props *props;
      int distance;
      int result;
      int range;

      props = moby->m_Props;

      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 5) {
        if ((moby->m_DamageFlags & MOBY_DAMAGE_SUPER) != 0) {
          props->m_0x08 = 0;
          props->m_0x0c = 260;
        } else {
          props->m_0x08 = 0x190;
          props->m_0x0c = 170;
          props->m_0x10 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        }

        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 5;

        MOBY_ANIM_CHANGE(moby, 5);

        continue;
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0: {
        Moby *linkedMoby;

        if (props->m_0x18 == 0) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        if (props->m_0x18 == 1) {
          linkedMoby = &g_LevelMobys[props->m_0x04];
          if (linkedMoby->m_State != 0) {
            props->m_0x18 = 0;
            moby->m_State = 4;
            MOBY_ANIM_CHANGE(moby, 4);
            continue;
          }

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);

          func_80039E94(moby, props->m_0x00, 0x100, 0xA0, 0, 8, 0x28, 0xFF, 5);
          break;
        }

        if (props->m_0x18 == 2) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);

          if (DISTANCE_TO_SPYRO(moby) < 1600 &&
              g_LevelMobys[props->m_0x04].m_State == 0) {
            moby->m_State = 9;
            MOBY_ANIM_CHANGE(moby, 9);
            continue;
          }

          if (moby->m_Substate != 0) {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        }

        break;
      }

      case 1: {
        if (moby->m_AnimationState.m_NextFrame >= 4 &&
            g_LevelMobys[props->m_0x04].m_State == 0) {
          g_LevelMobys[props->m_0x04].m_State = 1;
        }

        if (g_AnimationFinished) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        break;
      }

      case 2: {
        RotateMobyToAngle(moby,
                          ANGLE_FROM(moby->m_Position,
                                     g_LevelMobys[props->m_0x04].m_Position),
                          4, 0, 0);

        if (g_AnimationFinished) {
          props->m_0x14 = 0x78;
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }

        break;
      }

      case 3: {
        RotateMobyToAngle(moby,
                          ANGLE_FROM(moby->m_Position,
                                     g_LevelMobys[props->m_0x04].m_Position),
                          6, 0, 0);

        if (TICK_TIMER(props->m_0x14) || DISTANCE_TO_SPYRO(moby) < 1300) {
          if (g_AnimationFinished) {
            if (moby->m_AnimationState.m_Animation != 4) {
              moby->m_AnimationState.m_FrameProgress = 8;
              moby->m_AnimationState.m_PerFrameProgress = 8;
              moby->m_AnimationState.m_Animation =
                  moby->m_AnimationState.m_NextAnimation;
              moby->m_AnimationState.m_NextAnimation = 4;
              moby->m_AnimationState.m_Frame =
                  moby->m_AnimationState.m_NextFrame;
              moby->m_AnimationState.m_NextFrame = 0;
              func_80037E98(moby);
            }

            moby->m_State = 4;
            continue;
          }
        }

        break;
      }

      case 4: {
        distance = DISTANCE_TO_SPYRO(moby);
        range = props->m_0x20;

        if (range < 0x20) {
          range <<= 10;
        }

        if (distance < range && g_Spyro.m_State != 11 &&
            g_Spyro.m_State != 20) {
          props->m_0x14 = 0x78;
          moby->m_State = 7;
          MOBY_ANIM_CHANGE(moby, 7);
          continue;
        }

        RotateMobyToSpyro(moby, 4, 0, 0);

        if (TICK_TIMER(props->m_0x14) && distance < 1300) {
          props->m_0x14 = 0x78;
          moby->m_State = 8;
          MOBY_ANIM_CHANGE(moby, 8);
          continue;
        }

        break;
      }

      case 5: {
        int floorHeight;

        result = MoveMobyWithGravity(moby, &props->m_0x08, props->m_0x10,
                                     &props->m_0x0c, 0xC, 0x10);

        if ((g_SurfaceBelowFlags & 0x3F) == 0) {
          floorHeight = func_80038340(moby);
          if (MOBY_BASE_Z_DISTANCE(moby, floorHeight) < 100) {
            PlaySound(g_Spu.m_SoundTable->waterSplash, moby, 8,
                      &moby->m_SoundChannel);
            g_SpawnMoby(400, moby);
            props->m_0x14 = 0xA;
            moby->m_State = 10;
            continue;
          }
        }

        if (result == 3 && props->m_0x1c == 0) {
          props->m_0x1c = 1;
          func_8003851C(moby, 0, 0);
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x20);
          func_80052568(moby);
          continue;
        }

        break;
      }

      case 7: {
        if (TICK_TIMER(props->m_0x14) || DISTANCE_TO_SPYRO(moby) < 1000) {
          props->m_0x20 = 0;
          props->m_0x14 = 0;
          moby->m_State = 8;
          MOBY_ANIM_CHANGE(moby, 8);
          continue;
        }

        if (RotateMobyToSpyro(moby, 6, 0x14, 1) != 0 &&
            func_80039398(moby, 0xA0, 300, 300, 0x15) != 0) {
          props->m_0x14 = 0;
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        break;
      }

      case 8: {
        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        break;
      }

      case 9: {
        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        break;
      }

      case 10: {
        if (TICK_TIMER(props->m_0x14)) {
          func_80052568(moby);
          continue;
        }

        moby->m_Position.z -= 100;
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_32
    case 32: {
      Moby32Props *props = moby->m_Props;

      if (moby->m_Substate != 0 || props->m_Parent->m_State != 4) {
        func_80052568(moby);
        continue;
      }

      func_80052D64(props->m_Parent, 0, &moby->m_Position);
    }
#endif
#ifdef HAS_MOBY_33
    case 33: {
      Moby33Props *props = moby->m_Props;
      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 10) {
        props->m_0x20 = 150;
        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
          props->m_0x20 = 0xE1;
        }
        props->m_0x1c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        if (moby->m_DropMoby == 0xFF) {
          moby->m_DropMoby = 0xF;
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
        }
        moby->m_State = 10;
        continue;
      }

      if (moby->m_DropMoby != 0xFF && props->m_0x04 == 0 &&
          moby->m_State != 10) {
        props->m_0x04 = g_SpawnMoby(34, moby);
        props->m_0x04->m_DepthOffset = 0;
        *(Moby **)props->m_0x04->m_Props = moby;
      }

      if (TICK_TIMER(props->m_0x3c) &&
          (moby->m_State == 1 || moby->m_State == 40)) {
        int i;
        props->m_0x3c = rand() % 3 + 4;
        i = rand() % 5;
        while (i == props->m_0x40) {
          i = rand() % 5;
        }
        func_8003851C(moby, i, 0);
        props->m_0x40 = i;
      }

      if (moby->m_AnimationState.m_NextAnimation == 4) {
        if (moby->m_AnimationState.m_NextFrame == 2 && (rand() & 3) == 0 &&
            IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[6]) ==
                0) {
          func_8003851C(moby, 6, 0);
        }
        if (moby->m_AnimationState.m_NextFrame == 0xC && (rand() & 3) == 0 &&
            IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[5]) ==
                0) {
          func_8003851C(moby, 5, 0);
        }
      }

      switch (moby->m_State) {
      case 0: {
        moby->m_DepthOffset = 2;
        if (props->m_0x08 == 0) {
          RotateMobyToSpyro(moby, 6, 0, 0);
          if (DISTANCE_TO_SPYRO(moby) < 0x1C00) {
            props->m_0x10 = 0;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            moby->m_State = 1;
            continue;
          }
          break;
        } else if (props->m_0x08 == 1) {
          int speed;
          speed = 0x154;
          speed -= DISTANCE_TO_SPYRO(moby) >> 5;
          if (speed < 0x8C) {
            speed = 0x8C;
          }
          if (speed > 0xF0) {
            speed = 0xF0;
          }
          if (moby->m_Substate == 0) {
            int angle;
            int angle2;
            int distance;
            // Can be read uninitialized in condition below
            int result;
            int i;
            angle2 =
                ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x00, 0));
            if (OctDistance(&moby->m_Position,
                            &PATH_NODE_POS(props->m_0x00, 0)) < 0x1000) {
              angle = ANGLE_FROM_SPYRO(moby->m_Position);
              RotateMobyToAngle(moby, angle, 8, 0, 0);
              func_80039398(moby, speed, 0, 0, 5);
              break;
            }
            angle = ANGLE_FROM_SPYRO(PATH_CUR_POS(props->m_0x00));
            distance =
                ANGLE_FROM(PATH_NODE_POS(props->m_0x00, 0), moby->m_Position);
            i = 0xA;
            if (moby->m_AnimationState.m_NextAnimation == 4) {
              i = 0x28;
            }
            if (func_80017908(angle, distance) > i &&
                DISTANCE_TO_SPYRO(moby) < 0x3000) {
              result = func_80038638(moby, &PATH_NODE_POS(props->m_0x00, 0),
                                     0x1800, angle, 5, speed, 0xE, 0x14, 0xFF,
                                     0xFF, 0, 0, 4);
            }
            if (result >= 0x5B) {
              props->m_0x18++;
            } else {
              props->m_0x18 = 0;
            }
            if (result < 0x1E) {
              RotateMobyToSpyro(moby, 6, 0, 0);
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
            } else {
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            }
            if (props->m_0x18 >= 0x1E &&
                func_80017908(angle2, ANGLE_TO_SPYRO(moby->m_Position)) >=
                    0x21) {
              moby->m_Substate = 1;
            }
          } else {
            int angle;
            int angle2;
            angle =
                ANGLE_FROM(g_Spyro.m_Position, PATH_NODE_POS(props->m_0x00, 0));
            angle2 =
                ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x00, 0));
            RotateMobyToAngle(moby, angle, 8, 0, 0);
            func_80039398(moby, speed, 0, 0, 5);
            if (func_80017908(angle, angle2) > 0x50) {
              moby->m_Substate = 0;
            }
            if (OctDistance(&moby->m_Position,
                            &PATH_NODE_POS(props->m_0x00, 0)) > 0x1800) {
              moby->m_Substate = 0;
            }
          }
          break;
        } else if (props->m_0x08 == 2) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x00, 6)) < 0x1800) {
            moby->m_State = 25;
            continue;
          }
          if (DISTANCE_TO_SPYRO(moby) < 0x1C00) {
            moby->m_State = 20;
            continue;
          }
          break;
        } else if (props->m_0x08 == 3) {
          if (DISTANCE_TO_SPYRO(moby) < (props->m_0x2c << 10) &&
              SPYRO_BASE_Z_DISTANCE(moby) < 0x708 &&
              (props->m_0x34 == 0 || func_80038250(&moby->m_Position) != 0)) {
            props->m_0x28 = func_80038BB0(props->m_0x00);
            props->m_0x14 = 0;
            if (props->m_0x28 - props->m_0x00->m_Reversed !=
                props->m_0x00->m_CurrentNode) {
              props->m_0x30 = 0;
              if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <
                  0x100) {
                props->m_0x00->m_CurrentNode =
                    (props->m_0x00->m_CurrentNode + props->m_0x00->m_Reversed +
                     props->m_0x00->m_NodeCount) %
                    props->m_0x00->m_NodeCount;
              }
              moby->m_State = 30;
              continue;
            }
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
            RotateMobyToSpyro(moby, 6, 0, 0);
          } else {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
            RotateMobyToSpyro(moby, 6, 0, 0);
          }
        } else if (props->m_0x08 == 4) {
          if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x44) != 0) {
            moby->m_State = 40;
            continue;
          }
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
          RotateMobyToSpyro(moby, 6, 0, 0);
          break;
        } else if (props->m_0x08 == 5) {
          int angle;
          int angle2;
          if (props->m_0x38 == 0) {
            props->m_0x38 =
                OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
          }
          if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
            angle = ANGLE_TO_SPYRO(PATH_CUR_POS(props->m_0x00));
            angle2 = ANGLE_FROM(PATH_CUR_POS(props->m_0x00), moby->m_Position);
            angle2 -= 0x80;
            angle = (angle - angle2) & 0xFF;
            if (angle > 0x80) {
              angle -= 0x100;
            }
            if (ABS2(angle) >= 0x31) {
              moby->m_State = 50;
              continue;
            }
          }
          break;
        } else if (props->m_0x08 == 6) {
          moby->m_State = 60;
          continue;
        }
        break;
      }
      case 1: {
        int speed;
        speed = 0x154;
        speed -= DISTANCE_TO_SPYRO(moby) >> 5;
        if (speed < 0x46) {
          speed = 0x46;
        }
        if (speed > 0xDC) {
          speed = 0xDC;
        }
        if (func_80039E94(moby, props->m_0x00, 0x73A, speed, 200, 0xA, 0x80,
                          moby->m_Pod, 0) == 260) {
          props->m_0x0c = 300;
          moby->m_State = 2;
          continue;
        }
        break;
      }
      case 2: {
        int angle;
        moby->m_DepthOffset = 0;
        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));
        RotateMobyToAngle(moby, angle, 6, 0, 0);
        func_80039398(moby, 150, 0, 0, 1);
        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <
            0x100) {
          moby->m_State = 3;
          continue;
        }
        moby->m_Position.z += props->m_0x0c;
        props->m_0x0c -= 0x14;
        break;
      }
      case 3: {
        int angle;
        int distance;
        int floorHeight;
        int i;
        floorHeight = func_80038340(moby);
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        if (props->m_0x10 == 0) {
          if (moby->m_Position.z + props->m_0x0c <= floorHeight) {
            moby->m_Position.z = floorHeight;
            props->m_0x10 = 1;
          } else {
            moby->m_Position.z += props->m_0x0c;
            props->m_0x0c -= 0x14;
            if (props->m_0x0c < -200) {
              props->m_0x0c = -200;
            }
          }
        } else {
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x00, 4)) <
              OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x00, 5))) {
            i = 4;
          } else {
            i = 5;
          }
          angle = ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x00, i));
          distance =
              OctDistance(&moby->m_Position, &PATH_NODE_POS(props->m_0x00, i));
          if (distance >= 0x101) {
            if (RotateMobyToAngle(moby, angle, 8, 0x14, 1) != 0) {
              func_80039398(moby, 150, 0, 0, 5);
            }
          } else if (OctDistance(&g_Spyro.m_Position,
                                 &PATH_NODE_POS(props->m_0x00, 6)) < 0x800 ||
                     OctDistance(&g_Spyro.m_Position,
                                 &PATH_NODE_POS(props->m_0x00, 7)) < 0x800) {
            props->m_0x0c = 150;
            moby->m_State = 4;
            continue;
          }
        }
        break;
      }
      case 4: {
        int angle;
        int floorHeight;
        angle = ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x00, 0));
        RotateMobyToAngle(moby, angle, 6, 0, 0);
        if (OctDistance(&moby->m_Position, &PATH_NODE_POS(props->m_0x00, 0)) >
            0x100) {
          func_80039398(moby, 0x82, 0, 0, 1);
        }
        moby->m_Position.z += props->m_0x0c;
        props->m_0x0c -= 0x14;
        floorHeight = func_80038340(moby);
        if (props->m_0x0c < 0) {
          if (moby->m_Position.z + props->m_0x0c <= floorHeight) {
            moby->m_Position.z = floorHeight;
            props->m_0x00->m_CurrentNode = 0;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
            moby->m_State = 0;
            continue;
          }
          moby->m_Position.z += props->m_0x0c;
          props->m_0x0c -= 0x14;
          if (props->m_0x0c < -200) {
            props->m_0x0c = -200;
          }
        }
        break;
      }
      case 10: {
        if (props->m_0x04 != 0) {
          g_Spyro.m_ControlFlags = 0x80002000;
          if (moby->m_AnimationState.m_NextAnimation == 3 &&
              moby->m_AnimationState.m_NextFrame >= 5) {
            props->m_0x04->m_State = 1;
            props->m_0x04->m_DepthOffset = 4;
            props->m_0x04 = 0;
          }
        }
        if (props->m_0x20 != 0) {
          func_80039688(moby, props->m_0x1c, props->m_0x20, 0, 300, 5);
          props->m_0x20 -= 0x10;
          if (props->m_0x20 < 0) {
            props->m_0x20 = 0;
          }
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }
      case 20: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (func_80039E94(moby, props->m_0x00, 0x100, 0xF0, 0, 8, 0x10, 0xFF,
                          5) == 0x103) {
          moby->m_State = 21;
          continue;
        }
        break;
      }
      case 21: {
        if (OctDistance(&g_Spyro.m_Position, &PATH_NODE_POS(props->m_0x00, 6)) <
            0x1800) {
          moby->m_State = 25;
          continue;
        }
        if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
          moby->m_State = 22;
          continue;
        }
        RotateMobyToSpyro(moby, 4, 0, 0);
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        break;
      }
      case 22: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (func_80039E94(moby, props->m_0x00, 0x100, 0xDA, 0, 0xA, 0x30, 0xFF,
                          5) == 0x101) {
          moby->m_State = 23;
          continue;
        }
        break;
      }
      case 23: {
        int distance;
        distance = DISTANCE_TO_SPYRO(moby);
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (distance < 0x2000 &&
            g_Spyro.m_Position.z - moby->m_Position.z >= -0xC7) {
          props->m_0x0c = 150;
          props->m_0x10 = 0;
          moby->m_State = 24;
          continue;
        }
        break;
      }
      case 24: {
        int angle;
        int floorHeight;
        int moveFlag;
        moveFlag = 1;
        if (props->m_0x10 != 0) {
          moveFlag = 5;
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        angle = ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x00, 2));
        if (RotateMobyToAngle(moby, angle, 8, 0x1E, 1) == 0) {
          break;
        }
        func_80039398(moby, 0xFA, 0, 0, moveFlag);
        if (OctDistance(&moby->m_Position, &PATH_NODE_POS(props->m_0x00, 2)) <
            0x100) {
          props->m_0x00->m_CurrentNode = 3;
          moby->m_State = 21;
          continue;
        }
        if (props->m_0x10 == 0) {
          floorHeight = func_80038400(moby, 0x1800);
          moby->m_Position.z += props->m_0x0c;
          props->m_0x0c -= 0x14;
          if (props->m_0x0c < 0 &&
              moby->m_Position.z - floorHeight < ABS2(props->m_0x0c)) {
            props->m_0x10 = 1;
          }
        }
        break;
      }
      case 25: {
        VecCopy(&moby->m_Position, &PATH_NODE_POS(props->m_0x00, 0));
        props->m_0x00->m_CurrentNode = 1;
        func_80038458(moby);
        moby->m_State = 23;
        continue;
      }
      case 30: {
        int angle;
        int angle2;
        int distance;
        int nextDistance;
        int result;
        int speed;
        int nextNode;
        int currentDiff;
        int nextDiff;
        int spyroAngle;
        int i;
        speed = 0xCD;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (PATH_CUR_NODE(props->m_0x00).unk_0xC > 0) {
          speed = PATH_CUR_NODE(props->m_0x00).unk_0xC;
        }
        if (props->m_0x14 < speed) {
          props->m_0x14 += 0x1E;
          if (props->m_0x14 > speed) {
            props->m_0x14 = speed;
          }
        } else if (props->m_0x14 > speed) {
          props->m_0x14 -= 0x1E;
          if (props->m_0x14 < speed) {
            props->m_0x14 = speed;
          }
        }
        nextNode = (props->m_0x00->m_CurrentNode + props->m_0x00->m_Reversed +
                    props->m_0x00->m_NodeCount) %
                   props->m_0x00->m_NodeCount;
        distance = OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
        nextDistance = OctDistance(&moby->m_Position,
                                   &PATH_NODE_POS(props->m_0x00, nextNode));
        if (distance >= 0x191 && nextDistance >= 0x191) {
          angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));
          angle2 = ANGLE_FROM(moby->m_Position,
                              PATH_NODE_POS(props->m_0x00, nextNode));
          spyroAngle = ANGLE_TO_SPYRO(moby->m_Position);
          currentDiff = func_80017908(angle, spyroAngle);
          nextDiff = func_80017908(angle2, spyroAngle);
          if (props->m_0x30 == 0 && ABS2(currentDiff - nextDiff) < 0x28) {
            props->m_0x30 = 1;
            props->m_0x00->m_Reversed = -props->m_0x00->m_Reversed;
          } else if (currentDiff < nextDiff &&
                     ABS2(currentDiff - nextDiff) >= 0x1D && nextDiff >= 0x3D &&
                     func_80017908(moby->m_Rotation.z,
                                   ANGLE_TO_SPYRO(moby->m_Position)) < 0x3C) {
            props->m_0x00->m_Reversed = -props->m_0x00->m_Reversed;
            props->m_0x00->m_CurrentNode = nextNode;
          }
        }
        result = func_80039E94(moby, props->m_0x00, 0x100, props->m_0x14, 0, 8,
                               0x1E, 0xFF, 5);
        if ((result & 0x100) != 0) {
          i = (props->m_0x28 - props->m_0x00->m_Reversed) %
              props->m_0x00->m_NodeCount;
          if ((result & ~0x100) == i) {
            moby->m_State = 0;
            continue;
          }
          props->m_0x28 = func_80038BB0(props->m_0x00);
        }
        break;
      }
      case 40: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (moby->m_Position.z < 0x800) {
          VecCopy(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
          func_80038458(moby);
        }
        props->m_0x14 = 0xB4;
        if (PATH_CUR_NODE(props->m_0x00).unk_0xC > 0) {
          props->m_0x14 = PATH_CUR_NODE(props->m_0x00).unk_0xC;
        }
        if (func_80039E94(moby, props->m_0x00, 0x100, props->m_0x14, 0, 8, 0x20,
                          0xFF, 5) == 0x10B) {
          props->m_0x0c = 150;
          moby->m_State = 41;
          continue;
        }
        break;
      }
      case 41: {
        int angle;
        int distance;
        int floorHeight;
        floorHeight = func_80038340(moby);
        distance = OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
        if (moby->m_Position.z < 0x800) {
          VecCopy(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
          func_80038458(moby);
        }
        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));
        RotateMobyToAngle(moby, angle, 6, 0, 0);
        if (distance >= 0x101) {
          func_80039398(moby, 150, 0, 0, 1);
        }
        if (distance < 0x100 && moby->m_Position.z == floorHeight) {
          if (++props->m_0x00->m_CurrentNode == 0xD) {
            moby->m_State = 42;
            continue;
          }
          props->m_0x0c = 150;
          break;
        }
        moby->m_Position.z += props->m_0x0c;
        props->m_0x0c -= 0x14;
        if (props->m_0x0c < -200) {
          props->m_0x0c = -200;
        }
        if (moby->m_Position.z + props->m_0x0c <= floorHeight) {
          moby->m_Position.z = floorHeight;
        }
        break;
      }
      case 42: {
        PathData *path;
        int heightDelta;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (moby->m_Position.z < 0x800) {
          VecCopy(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
          func_80038458(moby);
        }
        path = props->m_0x00;
        heightDelta = g_Spyro.m_Position.z - PATH_NODE_POS(path, 10).z;
        if (heightDelta < -1500 && DISTANCE_TO_SPYRO(moby) < 0x1800) {
          props->m_0x0c = 0x1A4;
          props->m_0x00->m_CurrentNode = 9;
          moby->m_State = 43;
          continue;
        }
        break;
      }
      case 43: {
        int angle;
        int distance;
        int floorHeight;
        floorHeight = func_80038340(moby);
        distance = OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));
        RotateMobyToAngle(moby, angle, 6, 0, 0);
        if (distance >= 0x101) {
          func_80039398(moby, 150, 0, 0, 1);
        }
        if (distance < 0x100 && moby->m_Position.z == floorHeight) {
          props->m_0x00->m_Reversed = -props->m_0x00->m_Reversed;
          props->m_0x00->m_CurrentNode = 8;
          moby->m_State = 44;
          continue;
        }
        moby->m_Position.z += props->m_0x0c;
        props->m_0x0c -= 0x14;
        if (props->m_0x0c < -200) {
          props->m_0x0c = -200;
        }
        if (moby->m_Position.z + props->m_0x0c <= floorHeight) {
          moby->m_Position.z = floorHeight;
        }
        break;
      }
      case 44: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        props->m_0x14 = 200;
        if (moby->m_Position.z < 0x800) {
          VecCopy(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
          func_80038458(moby);
        }
        if (func_80039E94(moby, props->m_0x00, 0x100, props->m_0x14, 0, 8, 0x20,
                          0xFF, 5) == props->m_0x00->m_NodeCount + 0xFF) {
          props->m_0x00->m_Reversed = -props->m_0x00->m_Reversed;
          props->m_0x00->m_CurrentNode = 1;
          moby->m_State = 0;
          continue;
        }
        break;
      }
      case 50: {
        int angle;
        int angle2;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
          angle = (ANGLE_TO_SPYRO(PATH_CUR_POS(props->m_0x00)) + 0x80) & 0xFF;
          func_80038638(moby, &PATH_NODE_POS(props->m_0x00, 0), props->m_0x38,
                        angle, 8, props->m_0x14, 0xF, 0x40, 0xFF, 0xFF, 0, 0,
                        0);
          angle2 = ANGLE_FROM(PATH_CUR_POS(props->m_0x00), moby->m_Position);
          angle = (angle - angle2) & 0xFF;
          if (angle > 0x80) {
            angle -= 0x100;
          }
          if (ABS2(angle) < 0x20) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
          break;
        }
        moby->m_State = 0;
        MOBY_ANIM_CHANGE(moby, 0);
        continue;
      }
      case 60: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        RotateMobyToSpyro(moby, 4, 0, 0);
        break;
      }
      }

      if (props->m_0x04 != 0) {
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        func_80052D64(moby, 0, &props->m_0x04->m_Position);
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
    case MOBYCLASS_DRAGON_EGG: { // Dragon Egg
      Moby34Props *eggProps = moby->m_Props;

      // If egg is in active collection states (1-4), prevent Spyro from
      // certain actions
      if (moby->m_State != 0 && moby->m_State < 5) {
        g_Spyro.m_ControlFlags = (0x80000000 | 0x00002000); // Set some flag

        // Skip if spyro isn't in a valid state
        if (g_Spyro.m_State != 0 && g_Spyro.m_State != 0xC) {
          moby->m_State = 5;
        }
      }

      // During spinning states (2-4), make spyro look at the Moby, and spawn
      // particle
      if (moby->m_State >= 2 && moby->m_State <= 4) {
        SetSpyroHeadLookTarget(&moby->m_Position);
        g_SpawnParticle(1, 12, moby, 0x602080); // Spawn particle
      }

      switch (moby->m_State) {
      case 1: { // Initialize collection
        g_ScreenBorderEnabled = 1;

        // Store starting position
        func_80017BFC(&eggProps->m_0x04, &moby->m_Position);

        // Calculate initial angle from egg to Spyro
        eggProps->m_0x13 =
            (Atan2Fast(moby->m_Position.x - g_Spyro.m_Position.x,
                       moby->m_Position.y - g_Spyro.m_Position.y) +
             64);

        eggProps->m_0x10 = 0;
        eggProps->m_0x12 = 0;
        g_Hud.D_80077FDC = 1; // Show collection UI?

        moby->m_Rotation.x = 0;
        moby->m_Rotation.y = 8;
        moby->m_State++;
        break;
      }

      case 2: {
        eggProps->m_0x12 += g_DeltaTime;
        if (eggProps->m_0x12 < 128) {

          eggProps->m_0x10 += g_DeltaTime * 4;
          eggProps->m_0x13 += g_DeltaTime * 4;

          func_80017C24(&moby->m_Position, &eggProps->m_0x04);

          // Apply circular motion
          moby->m_Position.x +=
              FIXED_MUL(Cos(eggProps->m_0x13 * 16), eggProps->m_0x10);
          moby->m_Position.y +=
              FIXED_MUL(Sin(eggProps->m_0x13 * 16), eggProps->m_0x10);

          // Spin and rise
          moby->m_Position.z -= eggProps->m_0x12 * 8;
          moby->m_Rotation.z += g_DeltaTime * 4;
        } else {
          Vector3D vec_38;
          int xCos;
          int xSin;
          int ySin;
          int yCos;

          VecCopy(&vec_38, &g_Spyro.m_Position);

          xCos = Cos(g_Spyro.m_bodyRotation.z * 16);
          xSin = Sin(g_Spyro.m_bodyRotation.z * 16);
          // Should this just be xCos * 724?
          xCos = (xCos * 181) * 4;
          xSin = (xSin * 181) * 4;
          vec_38.x += (xCos + xSin) >> 12;

          ySin = Sin(g_Spyro.m_bodyRotation.z * 16);
          yCos = Cos(g_Spyro.m_bodyRotation.z * 16);
          ySin = (ySin * 181) * 4;
          yCos = (yCos * 181) * 4;
          vec_38.y += (ySin - yCos) >> 12;

          vec_38.z += 768;

          func_80017BFC(&eggProps->m_0x0a, &vec_38);
          func_80017BFC(&eggProps->m_0x04, &moby->m_Position);

          eggProps->m_0x12 = 0;
          moby->m_State++;
        }

        if (g_Pad.m_Down & PAD_CROSS) { // Skip button
          moby->m_State = 5;
        }
        break;
      }

      case 3: {
        Vector3D eggInterpStartPos;
        Vector3D eggInterpDelta;
        eggProps->m_0x12 += g_DeltaTime;
        if (eggProps->m_0x12 < 64) {

          func_80017C24(&eggInterpStartPos, &eggProps->m_0x04);
          func_80017C24(&eggInterpDelta, &eggProps->m_0x0a);

          // Interpolate between start and target
          VecSub(&eggInterpDelta, &eggInterpDelta, &eggInterpStartPos);
          VecMult(&eggInterpDelta, &eggInterpDelta, eggProps->m_0x12);
          VecShiftRight(&eggInterpDelta,
                        6); // Divide by 64 for smooth interpolation
          VecAdd(&moby->m_Position, &eggInterpStartPos, &eggInterpDelta);

          moby->m_Rotation.z += g_DeltaTime * 4;
        } else {
          Vector3D vec_68;

          VecCopy(&vec_68, &g_Spyro.m_Position);

          vec_68.x += Cos(g_Spyro.m_bodyRotation.z * 0x10) >> 3;
          vec_68.y += Sin(g_Spyro.m_bodyRotation.z * 0x10) >> 3;
          vec_68.z += 0x300;

          func_80017BFC(&eggProps->m_0x04, &vec_68);

          eggProps->m_0x13 = (g_Spyro.m_bodyRotation.z - 64);
          eggProps->m_0x10 = 0x200;
          eggProps->m_0x12 = 0;
          moby->m_State++;
        }

        if (g_Pad.m_Down & PAD_CROSS) { // Skip
          moby->m_State = 5;
        }
        break;
      }

      case 4: {
        eggProps->m_0x12 += g_DeltaTime;
        if (eggProps->m_0x12 < 128) {
          int deltaAngle = g_DeltaTime * 4;

          // Contract spiral
          eggProps->m_0x10 -= deltaAngle;
          eggProps->m_0x13 -= deltaAngle;

          func_80017C24(&moby->m_Position, &eggProps->m_0x04);

          // Apply circular motion
          moby->m_Position.x +=
              FIXED_MUL(Cos(eggProps->m_0x13 * 16), eggProps->m_0x10);
          moby->m_Position.y +=
              FIXED_MUL(Sin(eggProps->m_0x13 * 16), eggProps->m_0x10);

          moby->m_Position.z -= eggProps->m_0x12 * 4;
          moby->m_Rotation.z += g_DeltaTime * 4;
        } else {
          moby->m_State++;
        }

        if (g_Pad.m_Down & PAD_CROSS) { // Skip button
          moby->m_State = 5;
        }
        break;
      }

      case 5: {
        Vector3D eggCameraEffectPos;

        // Get position relative to camera for particle effect
        VecSub(&eggCameraEffectPos, &moby->m_Position, &g_Camera.m_Position);
        VecRotateByCam(&eggCameraEffectPos, &eggCameraEffectPos);
        g_SpawnParticle(16, 77, &eggCameraEffectPos, 0);

        g_ScreenBorderEnabled = 0;
        VecNull(&g_Spyro.m_HeadLookTarget);

        func_8003B854(0, eggProps->m_0x00);

        // Update egg counters
        g_EggTotal++;
        g_LevelEggCount[g_LevelIndex]++;

        g_Hud.D_80077FDC = 0; // Hide collection UI?

        func_80052568(moby); // Delete egg moby

        break;
      }
      }

      break;
    }
#ifdef HAS_MOBY_35
    case 35: {
      Moby35Props *props = moby->m_Props;
      Vector3D delta;
      int distance;

      VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);
      if (distance < 13000) {
        distance = VecMagnitude(&delta, 0);
      }

      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 3) {
        int i;

        props->m_0x14 = 0xE6;
        props->m_0x10 = 300;
        props->m_0x0c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        moby->m_DamageFlags = 0;
        props->m_0x2c = RandRangeSigned(6, 0xA);
        props->m_0x2e = RandRangeSigned(6, 0xA);

        for (i = 0; i < 10 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(93, moby);
        }

        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        if (moby->m_AnimationState.m_Animation != 6) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 6);
        }
        func_8003851C(moby, 0, 0);
        moby->m_State = 3;
        continue;
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);

        if (props->m_0x00 == 1) {
          if ((func_80038C4C(&g_Spyro.m_Position, &props->m_0x30) != 0 ||
               distance < (props->m_0x20 << 10)) &&
              SPYRO_BASE_Z_DISTANCE(moby) < 3000) {
            if (moby->m_Pod != 0xFF) {
              func_8003B47C(moby, 0xA, 3);
            }
            moby->m_State = 10;
            continue;
          }
        }

        if (props->m_0x00 == 2) {
          if (props->m_0x28 != -1 && distance < (props->m_0x20 << 10) &&
              SPYRO_BASE_Z_DISTANCE(moby) < 3000) {
            props->m_0x08 = 0x3C;
            moby->m_State = 20;
            continue;
          }
        }

        RotateMobyToSpyro(moby, 6, 0, 0);
        if (TICK_TIMER(props->m_0x04) && distance < 4000 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 800 && TICK_TIMER(props->m_0x24)) {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }
        break;

      case 1:
        if (g_AnimationFinished) {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }
        break;

      case 2: {
        int i;

        RotateMobyToSpyro(moby, 0xE, 0, 1);
        if (TICK_TIMER(props->m_0x04)) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          for (i = 0; i < 2; i++) {
            Moby *spawned = g_SpawnMoby(494, moby);
            Moby494Props *spawnedProps;

            spawned->m_ScaleOverride = 0x48;
            spawned->m_Rotation.z = moby->m_Rotation.z;
            spawnedProps = spawned->m_Props;
            spawnedProps->m_0x12 = 1;
            spawnedProps->m_0x10 = 0x1E;
            func_80052D64(moby, i, &spawned->m_Position);
          }
          props->m_0x04 = 8;
        }

        if (TICK_TIMER(props->m_0x08) && g_AnimationFinished) {
          props->m_0x04 = 0xB4;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 3:
        moby->m_Rotation.x += (u_char)props->m_0x2c;
        moby->m_Rotation.y += (u_char)props->m_0x2e;
        if (MoveMobyWithGravity(moby, &props->m_0x10, props->m_0x0c,
                                &props->m_0x14, 0xC, 0x10) == 3) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 5:
        if (g_AnimationFinished) {
          props->m_0x08 = 0x28;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;

      case 10:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);

        if (func_80039E94(moby, props->m_0x1c, 0x100, 0x5A, 0, 8, 0x10, 0xFF,
                          5) == 0x100) {
          props->m_0x00 = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        if (DISTANCE_TO_SPYRO(moby) < 0xC00) {
          props->m_0x00 = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 20: {
        int angle;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);

        if (g_LevelMobys[props->m_0x28].m_State >= 0x80 ||
            DISTANCE_TO_SPYRO(moby) < 0x1400 || props->m_0x28 == -1) {
          props->m_0x00 = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        angle = ANGLE_FROM(moby->m_Position,
                           g_LevelMobys[props->m_0x28].m_Position);
        RotateMobyToAngle(moby, angle, 6, 0, 0);
        if (TICK_TIMER(props->m_0x08)) {
          props->m_0x08 = 0x19;
          moby->m_State = 21;
          continue;
        }
        break;
      }

      case 21: {
        int i;
        int angle;
        int *linkedProps;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);

        angle = ANGLE_FROM(moby->m_Position,
                           g_LevelMobys[props->m_0x28].m_Position);
        RotateMobyToAngle(moby, angle, 6, 0, 0);

        if (TICK_TIMER(props->m_0x04)) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          for (i = 0; i < 2; i++) {
            Moby *spawned = g_SpawnMoby(494, moby);
            Moby494Props *spawnedProps;

            spawned->m_ScaleOverride = 0x48;
            spawned->m_Rotation.z = moby->m_Rotation.z;
            spawnedProps = spawned->m_Props;
            spawnedProps->m_0x12 = 2;
            spawnedProps->m_0x10 = 0x2D;
            VecCopy(&spawnedProps->m_0x04,
                    &g_LevelMobys[props->m_0x28].m_Position);
            spawnedProps->m_0x04.z += 0xFA;
            func_80052D64(moby, i, &spawned->m_Position);
          }
          props->m_0x04 = 8;
        }

        if (TICK_TIMER(props->m_0x08) && g_AnimationFinished) {
          linkedProps = g_LevelMobys[props->m_0x28].m_Props;
          if (g_LevelMobys[props->m_0x28].m_State >= 0x80 ||
              props->m_0x28 == -1) {
            props->m_0x00 = 0;
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }

          props->m_0x28 = linkedProps[8];
          props->m_0x08 = 0x3C;
          moby->m_State = 20;
          continue;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_36
    case 36: { // Magic Crafters Mountain Goat Fodder
      Moby36Props *props = moby->m_Props;

      // Kill when flamed or charged
      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 2) {
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        // Enter dying state
        moby->m_State = 2;
        MOBY_ANIM_RESTART(moby, 2);
        continue;
      }

      switch (moby->m_State) {
      case 0: // Idle
        // Enter fleeing state if Spyro is close enough
        if (DISTANCE_TO_SPYRO(moby) < 0x1800 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;

      case 1: { // Fleeing
        // Only consider changing course if the Moby is close enough to the
        // current node
        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_Path)) <
            0x400) {
          // Return to idle if Spyro is far enough again
          if (DISTANCE_TO_SPYRO(moby) > 0x1800 ||
              SPYRO_BASE_Z_DISTANCE(moby) > 0x800) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }

          // Consider the path's end points if the path is not a loop:
          // Node indices -1 or m_NodeCount do not exist
          if (props->m_Path->m_CurrentNode == 0 && !props->m_IsLoopPath) {
            props->m_Path->m_CurrentNode = 1;
          } else if (props->m_Path->m_CurrentNode ==
                         props->m_Path->m_NodeCount - 1 &&
                     !props->m_IsLoopPath) {
            props->m_Path->m_CurrentNode--;
          } else {
            int spyroAngle;
            int nextNode;
            int previousNode;
            int nextAngle;
            int previousAngle;

            spyroAngle = ANGLE_TO_SPYRO(moby->m_Position);
            nextNode =
                (props->m_Path->m_CurrentNode + 1) % props->m_Path->m_NodeCount;
            previousNode = (props->m_Path->m_CurrentNode - 1 +
                            props->m_Path->m_NodeCount) %
                           props->m_Path->m_NodeCount;
            nextAngle = ANGLE_FROM(moby->m_Position,
                                   PATH_NODE_POS(props->m_Path, nextNode)),
            previousAngle = ANGLE_FROM(
                moby->m_Position, PATH_NODE_POS(props->m_Path, previousNode));

            if (func_80017908(spyroAngle, nextAngle) >
                func_80017908(spyroAngle, previousAngle)) {
              props->m_Path->m_CurrentNode = nextNode;
            } else {
              props->m_Path->m_CurrentNode = previousNode;
            }
          }
        }

        if (RotateMobyToAngle(
                moby, ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_Path)),
                8, 0x20, 1) != 0) {
          func_80039398(moby, 0x60, 0x200, 0x200, 0x27);
        }
        break;
      }

      case 2: // Dying
        if (g_AnimationFinished) {
          func_80052568(moby);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_37 // Blowhard Storm Cloud
    case 37: {
      Moby37Props *props;
      Vector3D vec;

      props = moby->m_Props;
      VecCopy(&vec, &moby->m_Position);
      vec.z += 0x400;
      func_8004D5EC(&vec, 0x10000);
      func_800533D0(moby);

      switch (moby->m_State) {
      case 0: {
        if (DISTANCE_TO_SPYRO(moby) < 0x200 &&
            moby->m_AnimationState.m_Frame >= 0x0F) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        moby->m_Position.x =
            props->m_0x00->m_Position.x +
            FIXED_MUL(COSINE_8(props->m_0x00->m_Rotation.z), 0x200);
        moby->m_Position.y =
            props->m_0x00->m_Position.y +
            FIXED_MUL(SINE_8(props->m_0x00->m_Rotation.z), 0x200);
        RotateMobyToSpyro(moby, 8, 0, 0);

        if (g_AnimationFinished) {
          props->m_0x08 = g_Spyro.m_Position.x >> 4;
          props->m_0x0a = g_Spyro.m_Position.y >> 4;
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
        }
        break;
      }

      case 1: {
        switch (props->m_0x10) {
        case 1: {
          int distance =
              OctDistance(&moby->m_Position, &props->m_0x00->m_Position);
          if (props->m_0x06 < distance) {
            distance = props->m_0x06;
          }
          if (distance >= props->m_0x06) {
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
            continue;
          }

          distance += props->m_0x04;
          moby->m_Position.x =
              props->m_0x00->m_Position.x +
              FIXED_MUL(distance, COSINE_8(props->m_0x00->m_Rotation.z));
          moby->m_Position.y =
              props->m_0x00->m_Position.y +
              FIXED_MUL(distance, SINE_8(props->m_0x00->m_Rotation.z));
          break;
        }

        case 3: {
          if (props->m_0x0c == 0) {
            props->m_0x0c = g_SpawnMoby(39, moby);
            func_8003851C(moby, 1, 0);
          }
        }
        case 2: {
          int distance =
              OctDistance(&moby->m_Position, &props->m_0x00->m_Position);

          if (props->m_0x06 < distance) {
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
            continue;
          } else {
            vec.x = props->m_0x08 << 4;
            vec.y = props->m_0x0a << 4;
            distance = OctDistance(&moby->m_Position, &vec);
            if (distance > 0x3000) {
              distance = 0x3000;
            }

            if ((props->m_0x04 >> 1) >= distance) {
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
              continue;
            } else {
              moby->m_Position.x +=
                  FIXED_MUL(props->m_0x04, COSINE_8(moby->m_Rotation.z));
              moby->m_Position.y +=
                  FIXED_MUL(props->m_0x04, SINE_8(moby->m_Rotation.z));
            }
          }
          break;
        }
        }

        if (DISTANCE_TO_SPYRO(moby) < 0x200) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
        }
        break;
      }

      case 2: {
        props->m_0x0c = 0;
        if (g_AnimationFinished) {
          Moby495Props *parentProps = props->m_0x00->m_Props;
          parentProps->m_0x48 = nullptr;
          func_80052568(moby);
        }
        break;
      }

      case 3: {
        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
        }
        break;
      }

      case 4: {
        props->m_0x0c = g_SpawnMoby(39, moby);
        func_8003851C(moby, 1, 0);
        moby->m_State = 5;
        MOBY_ANIM_CHANGE(moby, 5);
        break;
      }

      case 5: {
        if (g_AnimationFinished) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
        }
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_38
    case 38: {
      Moby38Props *props = moby->m_Props;

      switch (moby->m_State) {
      case 0:
      case 1:
      case 3:
        if (g_AnimationFinished && TICK_TIMER(props->m_0x00)) {
          func_80052568(moby);
        }
        break;

      case 2: {
        Vector3D oldPosition;
        int i;

        VecCopy(&oldPosition, &moby->m_Position);
        if (moby->m_Position.x < 0x400 || moby->m_Position.y < 0x400 ||
            moby->m_Position.z < 0x400) {
          func_80052568(moby);
          break;
        }

        if (func_8004E2E8(&moby->m_Position, 0x80, 0x20020)) {
          int angle = rand() & 0x3F;
          for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
            Moby *m = g_SpawnMoby(38, moby);
            m->m_Rotation.x = angle + i * 0x40;
          }
          func_80052568(moby);
          break;
        }

        if (TICK_TIMER(props->m_0x00) ||
            func_8003BCCC(moby, 0x80, 0, 0x100, 0) ||
            func_8004AE38(&oldPosition, &moby->m_Position)) {
          func_80052568(moby);
          break;
        }

        if (!(props->m_0x00 & 7)) {
          g_SpawnParticle(1, 7, &moby->m_Position, 0x10);
        }
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_39
    case 39: {
      Moby39Props *props;
      Vector3D oldPosition;
      props = moby->m_Props;

      if (((int *)props->m_0x04->m_Props)[3] == 0) {
        func_80052568(moby);
        break;
      }

      moby->m_Position.x = props->m_0x04->m_Position.x;
      moby->m_Position.y = props->m_0x04->m_Position.y;

      if (TICK_TIMER(props->m_0x08)) {
        func_8003851C(moby, 0, 0);
        props->m_0x08 = 99999;
      }

      if (moby->m_State == 0) {
        moby->m_Rotation.z = ANGLE_FROM(moby->m_Position, g_Camera.m_Position);
        VecCopy(&oldPosition, &props->m_0x04->m_Position);

        if (TICK_TIMER(props->m_0x00) ||
            func_8004E2E8(&oldPosition, 0x140, 0x26) != 0) {
          ((int *)props->m_0x04->m_Props)[3] = 0;
          func_80052568(moby);
        }
      }
      break;
    }
#endif
#if defined(HAS_MOBY_45) || defined(HAS_MOBY_46)
#ifdef HAS_MOBY_45
    case 45:
#endif
#ifdef HAS_MOBY_46
    case 46:
#endif
    {
      Moby45Props *props;
      int distance;
      int movement;
      int attackAngle;
      int homeAngle;
      Vector3D vec_68;

      props = moby->m_Props;
      movement = 0x708;
      VecSub(&vec_68, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);
      if (distance < 13000) {
        distance = VecMagnitude(&vec_68, 0);
      }
      if (moby->m_Class == 45) {
        movement = 1500;
      }

      if (props->m_0x00 == 0) {
        props->m_0x00 = 1;
        moby->m_AnimationState.m_NextFrame = rand() % 10;
        moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
        if (props->m_0x04 != 0) {
          moby->m_State = 2;
          moby->m_AnimationState.m_NextAnimation = 2;
          moby->m_AnimationState.m_Animation = 2;
        }
      }

      if (moby->m_Class == 45) {
        ApplyFlameHeat(moby);
      }

      if (moby->m_State != 4 &&
          ((moby->m_Class == 45 &&
            (moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER))) ||
           (moby->m_Class == 46 &&
            (moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER))))) {
        props->m_0x08 = 0x190;
        props->m_0x0c = 170;
        props->m_0x14 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        moby->m_DamageFlags = 0;
        if (props->m_0x44 != 0) {
          func_8003ABC0(moby, 4, 0, 0);
        } else {
          func_8003ABC0(moby, 3, 0, 0);
        }
        func_8003B7C0(moby);
        moby->m_State = 4;
        MOBY_ANIM_RESTART(moby, 4);
        break;
      }

      moby->m_DamageFlags = 0;
      func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
      if (distance > 0xC00) {
        props->m_0x38 = 0;
      }

      switch (moby->m_State) {
      case 0:
      case 2:
        TICK_TIMER(props->m_0x48);
        if (props->m_0x48 == 0 && distance < 0x2000 && moby->m_Class == 46 &&
            props->m_0x04 != 0 &&
            func_80017908(g_Spyro.m_bodyRotation.z,
                          ANGLE_FROM_SPYRO(moby->m_Position)) < 0x26 &&
            func_80017908(g_Camera.m_Rotation.z >> 4,
                          ANGLE_FROM(g_Camera.m_Position, moby->m_Position)) <
                0x23) {
          if (moby->m_AnimationState.m_NextAnimation < 2) {
            moby->m_State = 6;
            MOBY_ANIM_RESTART(moby, 6);
          } else {
            moby->m_State = 6;
            MOBY_ANIM_CHANGE(moby, 6);
          }
        } else {
          RotateMobyToSpyro(moby, 7, 5, 0);
          if (props->m_0x48 == 0 && distance < movement) {
            props->m_0x48 = 0xA0;
            props->m_0x40 = moby->m_State;
            if (props->m_0x04 == 0) {
              moby->m_State = 1;
              MOBY_ANIM_CHANGE(moby, 1);
            } else {
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
            }
          }
        }
        break;
      case 1:
      case 3:
        if (moby->m_AnimationState.m_NextFrame < 10) {
          attackAngle = moby->m_Rotation.z;
          if (moby->m_Class == 45) {
            attackAngle = (attackAngle + 30) & 0xFF;
          }
          g_Spyro.unk_0x208.x = FIXED_MUL(COSINE_8(attackAngle), 80);
          g_Spyro.unk_0x208.y = FIXED_MUL(SINE_8(attackAngle), 80);
          g_Spyro.unk_0x208.z = 30;
        }
        RotateMobyToSpyro(moby, 7, 5, 0);
        if (g_AnimationFinished) {
          moby->m_State = props->m_0x40;
          MOBY_ANIM_CHANGE(moby, props->m_0x40);
        }
        break;
      case 4:
        MoveMobyWithGravity(moby, &props->m_0x08, props->m_0x14, &props->m_0x0c,
                            0xC, 0x10);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
          func_800385BC(moby, 0x20);
          func_80052568(moby);
        }
        break;
      case 5:
        if (props->m_0x38 != 0) {
          moby->m_State = 100;
          break;
        }
        if (TICK_TIMER(props->m_0x34)) {
          props->m_0x14 = g_Spyro.m_bodyRotation.z;
          props->m_0x34 = 0x1E;
        }
        if (RotateMobyToAngle(moby, ANGLE_TO_SPYRO(moby->m_Position), 4, 0x1E,
                              1) != 0) {
          if (func_80039398(moby, 100, 0x300, 0x200, 0x25) != 0 ||
              OctDistance(&moby->m_Position, &props->m_0x24) > 0x2800) {
            moby->m_State = 100;
            break;
          }
        }
        if (func_80017908(g_Spyro.m_bodyRotation.z,
                          ANGLE_FROM_SPYRO(moby->m_Position)) >= 0x31) {
          if (props->m_0x30 != 0) {
            if (TICK_TIMER(props->m_0x30)) {
              props->m_0x30 = 0;
              moby->m_State = 100;
              break;
            }
          } else {
            props->m_0x30 = 0x28;
          }
        } else {
          props->m_0x30 = 0;
        }
        if (props->m_0x38 == 0 && distance < movement - 600 &&
            func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) < 0x40) {
          props->m_0x48 = 0xA0;
          props->m_0x38 = 1;
          props->m_0x40 = 6;
          func_800529E4(moby, UPDATE_PROP_COLLISION);
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
        }
        break;
      case 6:
        if (moby->m_AnimationState.m_Frame >= 3) {
          moby->m_State = 5;
          MOBY_ANIM_SET_NEXT(moby, 5);
        }
        break;
      case 100:
        homeAngle = Atan2Fast(props->m_0x24.x - moby->m_Position.x,
                              props->m_0x24.y - moby->m_Position.y);
        func_800529E4(moby, UPDATE_PROP_COLLISION);
        if (RotateMobyToAngle(moby, homeAngle, 4, 0x14, 1) != 0) {
          func_80039398(moby, 0x5A, 0x300, 0x200, 0x27);
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
        if (OctDistance(&moby->m_Position, &props->m_0x24) < 0x80) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_47 // Jacques Gift Projectile
    case 47: {
      Moby47Props *props;
      int distance;
      int heightDifference;
      Vector3D vec_38;
      Vector3D vec1;
      Vector3D vec2;

      props = moby->m_Props;
      if (props->m_0x03 != 0x63) {
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
        func_8004D5EC(&moby->m_Position, 0x10000);
        func_800533D0(moby);
        VecCopy(&vec_38, &moby->m_Position);
        vec_38.z += 200;
        if (moby->m_State == 0 || moby->m_State == 9) {
          if (func_8004E2E8(&vec_38, 0xDC, 1) != 0) {
            func_8003851C(moby, 0, 0);
            moby->m_State = 1;
            MOBY_ANIM_RESTART(moby, 1);
            break;
          }
        }
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x0c->m_State == 10) {
          ((Moby150Props *)props->m_0x0c->m_Props)->m_0x34 = 0;
          ((Moby150Props *)props->m_0x0c->m_Props)->m_0x54 = 0;
          ((Moby150Props *)props->m_0x0c->m_Props)->m_0x44 = nullptr;
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          break;
        }
        if (props->m_0x0c->m_AnimationState.m_NextFrame == 4) {
          props->m_0x03 = 0;
        }
        if (props->m_0x03 == 1) {
          func_80052D64(props->m_0x0c, 1, &vec1);
          func_80052D64(props->m_0x0c, 2, &vec2);
          moby->m_Position.x = vec1.x + ((vec2.x - vec1.x) >> 1);
          moby->m_Position.y = vec1.y + ((vec2.y - vec1.y) >> 1);
          moby->m_Position.z = vec1.z + ((vec2.z - vec1.z) >> 1);
        } else if (props->m_0x03 != 0x63) {
          Vector3D vec3;
          VecCopy(&vec3, &g_Spyro.m_Position);
          if (moby->m_Position.x < 0x400 || moby->m_Position.y < 0x400 ||
              moby->m_Position.z < 0x400) {
            moby->m_State = 1;
            MOBY_ANIM_RESTART(moby, 1);
            break;
          }
          vec3.z = func_8004D5EC(&g_Spyro.m_Position, 0x2800) + 300;
          heightDifference = vec3.z - props->m_0x0c->m_Position.z;
          if (heightDifference < 0) {
            heightDifference = -heightDifference;
          }
          if (heightDifference >= 0x1001) {
            vec3.z = moby->m_Position.z - 300;
          }
          moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);
          props->m_0x00 = 8;
          props->m_0x0a = 0x78;
          ((Moby150Props *)props->m_0x0c->m_Props)->m_0x44 = nullptr;
          props->m_0x04 = 300;
          distance = OctDistance(&moby->m_Position, &vec3);
          if (distance < props->m_0x04) {
            props->m_0x08 = -distance;
          } else {
            props->m_0x08 =
                (vec3.z - moby->m_Position.z) / (distance / props->m_0x04);
            props->m_0x02 = 2;
            props->m_0x06 = 0;
            props->m_0x01 = 1;
          }
          moby->m_State = 9;
        }
        break;
      case 1:
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
        if (g_AnimationFinished) {
          func_80052568(moby);
        }
        break;
      case 2:
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
        if (g_AnimationFinished) {
          func_80052568(moby);
        }
        break;
      case 9:
        moby->m_Position.x +=
            FIXED_MUL(props->m_0x04, COSINE_8(moby->m_Rotation.z));
        moby->m_Position.y +=
            FIXED_MUL(props->m_0x04, SINE_8(moby->m_Rotation.z));
        moby->m_Position.z += props->m_0x08;
        moby->m_Rotation.x += props->m_0x01;
        moby->m_Rotation.y += props->m_0x02;
        if (TICK_TIMER(props->m_0x00)) {
          VecCopy(&vec_38, &moby->m_Position);
          vec_38.z += 200;
          if (func_8004BE4C(&vec_38, 220, 220) != 0) {
            props->m_0x06 = 0;
            props->m_0x04 = 0;
            props->m_0x01 = 0;
            props->m_0x02 = 0;
            func_8003851C(moby, 0, 0);
            moby->m_State = 2;
            MOBY_ANIM_RESTART(moby, 2);
            break;
          }
        }
        if (TICK_TIMER(props->m_0x0a)) {
          props->m_0x06 = 0;
          props->m_0x04 = 0;
          props->m_0x01 = 0;
          props->m_0x02 = 0;
          func_8003851C(moby, 0, 0);
          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
        }
        break;
      }
      break;
    }

#endif
#ifdef HAS_MOBY_48
    case 48: {

      Moby48Props *props = moby->m_Props;
      Vector3D delta;
      int distance;

      VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);
      if (distance < 13000) {
        distance = VecMagnitude(&delta, 0);
      }

      if (props->m_0x48 == 0) {
        props->m_0x48 = 1;
        func_8002B390(3, 0xFC, 0);
        if (func_80038494(moby) != 0) {
          func_8002B390(4, 0xFC, 0);
          func_8002B390(5, 0xFC, 0);
          func_8003B5F4(0, 0x40000);
          func_8003B5F4(1, 0x40000);
          func_8003B688(2);
          func_8003B688(3);
          VecCopy(
              &moby->m_Position,
              &PATH_NODE_POS(props->m_0x04, props->m_0x04->m_NodeCount - 1));
          if (moby->m_DropMoby == 0xFF) {
            func_80052568(moby);
            continue;
          }
          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);
          func_80052568(moby);
          continue;
        }
      }

      props->m_0x50 = ApplyFlameHeatExternal(moby, props->m_0x50);
      moby->m_DamageFlags = 0;

      if (moby->m_State < 10) {
        if (props->m_0x00 == 0) {
          if (TICK_TIMER(props->m_0x4c) && SPYRO_BASE_Z_DISTANCE(moby) < 1400 &&
              distance < 0x6400) {
            if (g_Spyro.m_State != 0xB && g_Spyro.m_State != 0x14) {
              g_Spyro.m_ControlFlags = 0x80010000;
              g_Spyro.m_mobyInUseBySpyro = moby;
            }
          }
        } else {
          if (TICK_TIMER(props->m_0x4c) && SPYRO_BASE_Z_DISTANCE(moby) < 1400 &&
              distance < 0x6000) {
            if (g_Spyro.m_State != 0xB && g_Spyro.m_State != 0x14) {
              g_Spyro.m_ControlFlags = 0x80010000;
              g_Spyro.m_mobyInUseBySpyro = moby;
            }
          }
        }
      }

      if (g_Spyro.m_State == 0xB || g_Spyro.m_State == 0x14) {
        props->m_0x4c = 0x3C;
      }

      if (func_8003B0DC(props->m_0x00 + 2) == 0 && moby->m_State < 4) {
        func_8002B390(props->m_0x00 + 4, 0xFC, 0);
        moby->m_State = 10;
        continue;
      }

      if (props->m_0x44 == 0 && distance < 0x6800) {
        props->m_0x44 = 1;
        func_8002B390(3, 0xFC, 0);
      }

      switch (moby->m_State) {
      case 0: {
        int actionMode;
        int value;
        int stateDistance;

        stateDistance = DISTANCE_TO_SPYRO(moby);
        actionMode = 1;
        if (func_8003B0DC(props->m_0x00) == 0 || stateDistance < 0x2000 ||
            SPYRO_BASE_Z_DISTANCE(moby) > 900) {
          actionMode = 2;
          if (props->m_0x20 == 1) {
            props->m_0x20 = 0;
          }
        }

        RotateMobyToSpyro(moby, 4, 0, 0);

        if (props->m_0x20 == 0) {
          value = RandRange(0, 100);
          if (actionMode >= 2) {
            value = RandRange(0x3C, 100);
          }
          if (value < 0x3C) {
            props->m_0x20 = 1;
          } else if (value < 0x55) {
            props->m_0x20 = 2;
          } else {
            props->m_0x20 = 3;
          }
        }

        if (!TICK_TIMER(props->m_0x08)) {
          break;
        }

        switch (props->m_0x20) {
        case 1: {
          if (stateDistance < (*((props->m_0x00 + 2) + props->m_0x10) << 10) &&
              stateDistance > 0x2000 && SPYRO_BASE_Z_DISTANCE(moby) < 800) {
            if (moby->m_Substate == 0) {
              moby->m_Substate = 1;
            }
          } else if (moby->m_Substate == 1) {
            moby->m_Substate = 0;
          }

          if (moby->m_Substate == 2) {
            moby->m_Substate = 0;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
          break;
        }

        case 2: {
          if (stateDistance > 0x800 && stateDistance < 0x7000 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 1000) {
            props->m_0x24 = 0;
            moby->m_State = 2;
            continue;
          }
          props->m_0x20 = 0;
          break;
        }

        case 3: {
          if (stateDistance > 0x2800 && stateDistance < 0x7000 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 1000) {
            props->m_0x28 = 0;
            VecCopy(&props->m_0x2c, &g_Spyro.m_Position);
            moby->m_State = 3;
            continue;
          }
          props->m_0x20 = 0;
          break;
        }
        }
        break;
      }

      case 1: {
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_AnimationFinished) {
          props->m_0x08 = 0x50;
          props->m_0x20 = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 2: {
        Moby *projectile;
        Moby82Props *projectileProps;
        Vector3D targetPosition;
        int travelTime;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 12);

        if (moby->m_AnimationState.m_NextFrame > 4 &&
            moby->m_AnimationState.m_NextFrame < 21) {
          projectile = g_SpawnMoby(82, moby);
          projectileProps = projectile->m_Props;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 3, &projectile->m_Position);
          VecCopy(&targetPosition, &moby->m_Position);
          targetPosition.x += FIXED_MUL(props->m_0x24 * 150 + 3000,
                                        COSINE_8(moby->m_Rotation.z));
          targetPosition.y +=
              FIXED_MUL(props->m_0x24 * 150 + 3000, SINE_8(moby->m_Rotation.z));
          targetPosition.x += RandRange(-800, 800);
          targetPosition.y += RandRange(-800, 800);
          targetPosition.z += 300;
          VecSub(&projectileProps->m_0x00, &targetPosition,
                 &projectile->m_Position);
          travelTime = OctDistance(&moby->m_Position, &targetPosition) / 500;
          projectileProps->m_0x00.x /= travelTime;
          projectileProps->m_0x00.y /= travelTime;
          projectileProps->m_0x00.z /= travelTime;
          projectile->m_RenderRadius = 0x28;
          projectile->m_Rotation.z =
              ANGLE_FROM(projectile->m_Position, targetPosition);
          projectile->m_Rotation.y =
              Atan2(OctDistance(&projectile->m_Position, &targetPosition),
                    targetPosition.z - projectile->m_Position.z, 0);
          projectileProps->m_0x0c = 0xB4;
          projectileProps->m_0x0e = props->m_0x00 + 2;
          projectileProps->m_0x0f = 0;
          props->m_0x24 += g_DeltaTime;
        }

        if (g_AnimationFinished) {
          props->m_0x08 = 0x50;
          props->m_0x20 = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 3: {
        Moby *projectile;
        Moby70Props *projectileProps;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 13);

        if (moby->m_AnimationState.m_NextFrame > 3 &&
            moby->m_AnimationState.m_NextFrame < 9 && props->m_0x28 >= 7) {
          projectile = g_SpawnMoby(70, moby);
          VecCopy(&projectile->m_Position, &props->m_0x38);
          projectileProps = projectile->m_Props;
          projectileProps->m_0x10 = 0xF0;
          projectile->m_Rotation.z =
              ANGLE_FROM(projectile->m_Position, props->m_0x2c);
          projectile->m_RenderRadius = 0x28;
          props->m_0x28 = 0;
          projectileProps->m_0x12 = props->m_0x00 + 2;
          projectileProps->m_0x08 = -7;
          projectileProps->m_0x00 = (DISTANCE_TO_SPYRO(moby) >> 8) + 0x190;
          projectileProps->m_0x04 = func_8003891C(
              &projectile->m_Position, &props->m_0x2c, projectileProps->m_0x00,
              projectileProps->m_0x08, &projectileProps->m_0x0c);
        }

        if (moby->m_AnimationState.m_NextFrame < 3) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 5, &props->m_0x38);
        }

        props->m_0x28 += g_DeltaTime;
        if (g_AnimationFinished) {
          props->m_0x08 = 0x50;
          props->m_0x20 = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 10: {
        int angle;

        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x04));
        func_8003B5F4(props->m_0x00, 0x40000);
        if (props->m_0x00 == 1) {
          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 20;
          continue;
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        if (RotateMobyToAngle(moby, angle, 6, 8, 1) != 0) {
          moby->m_Substate = 0;
          moby->m_State++;
          continue;
        }
        break;
      }

      case 11: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
        if (g_AnimationFinished) {
          if (moby->m_AnimationState.m_NextAnimation != 9) {
            g_AnimationFinished = 0;
            moby->m_AnimationState.m_FrameProgress = 0x10;
            moby->m_AnimationState.m_PerFrameProgress = 0x10;
            moby->m_AnimationState.m_NextAnimation = 9;
            moby->m_AnimationState.m_NextFrame = 0;
            func_80037E98(moby);
          }
          props->m_0x0c = 0x46;
          moby->m_State++;
          continue;
        }
        break;
      }

      case 12: {
        func_80039E94(moby, props->m_0x04, 0x100, 0x78, 0, 3, 5, 0xFF, 5);
        if (TICK_TIMER(props->m_0x0c)) {
          moby->m_State++;
          continue;
        }
        break;
      }

      case 13: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 10);
        if (g_AnimationFinished) {
          if (moby->m_AnimationState.m_NextAnimation != 5) {
            g_AnimationFinished = 0;
            moby->m_AnimationState.m_FrameProgress = 0x10;
            moby->m_AnimationState.m_PerFrameProgress = 0x10;
            moby->m_AnimationState.m_NextAnimation = 5;
            moby->m_AnimationState.m_NextFrame = 0;
            func_80037E98(moby);
          }
          moby->m_State++;
          continue;
        }
        break;
      }

      case 14: {
        int result;

        result =
            func_80039E94(moby, props->m_0x04, 350, 0x118, 0, 8, 0x80, 0xFF, 5);
        if (result == props->m_0x10[props->m_0x00] + 0x100) {
          moby->m_State++;
          continue;
        }
        break;
      }

      case 15: {
        if (RotateMobyToSpyro(moby, 6, 4, 1) != 0) {
          props->m_0x00++;
          moby->m_Pod = props->m_0x00;
          func_8003B728(moby, 1);
          moby->m_Pod = 0xFF;
          moby->m_Substate = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 20: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 11);
        if (g_AnimationFinished) {
          func_8002B390(3, 0xFC, 0);
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x40);
          D_80075854 = 1;
          func_80052568(moby);
          continue;
        }
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_49 // Dragon Head Opener in Artisans
    case 49: {
      Moby49Props *props = moby->m_Props;
      int state;

      if (props->m_AlreadyVisitedCheckDone == 0) {
        // Open the head immediately if Toasty has been visited before
        if (g_VisitedFlags[4] != 0) {
          func_8002B390(props->m_EnvAnimID, 0xFC, 0);
          func_8002B444(props->m_EnvAnimID, 59, 0);
        }
        props->m_AlreadyVisitedCheckDone = 1;
      }

      state = (func_8002B3F4(props->m_EnvAnimID) >> 8) & 0xFF;

      switch (state) {
      case 0: {
        // If any of the other Artisans levels were exited through the Vortex,
        // the dragon in front of the dragon head, Argus, has been collected
        // and Spyro is close enough, open the dragon head
        if ((g_LevelVortexExitFlags[1] || g_LevelVortexExitFlags[2] ||
             g_LevelVortexExitFlags[3] || g_LevelVortexExitFlags[4]) &&
            g_LevelMobys[props->m_ArgusStatueMobyIndex].m_State >= 0x80 &&
            DISTANCE_TO_SPYRO(moby) < 0x4000) {
          func_8002B390(props->m_EnvAnimID, 0xFC, 0);
          moby->m_SoundDistance = 0x30;
          PlaySound(g_Spu.m_SoundTable->sound_0x41, moby, 8,
                    &moby->m_SoundChannel);
        }
        break;
      }
      case 60: {
        func_800562A4(moby, 1);
        if (DISTANCE_TO_SPYRO(moby) > 0x4800) {
          func_8002B390(props->m_EnvAnimID, 0xFC, 0);
        }
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_50
    case 50: {
      Moby50Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 5 && moby->m_State != 1) {
        if (*props->m_0x10 == moby) {
          *props->m_0x10 = 0;
          if (props->m_0x24 >= 0) {
            g_LevelMobys[props->m_0x24].m_Substate &= ~4;
          }
        }
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 5;
        MOBY_ANIM_CHANGE(moby, 5);
        continue;
      }

      moby->m_DamageFlags = 0;

      if (props->m_0x24 >= 0) {
        if (moby->m_State != 3 && moby->m_State != 5 &&
            g_LevelMobys[props->m_0x24].m_Substate == 3) {
          if (*props->m_0x10 == moby) {
            *props->m_0x10 = 0;
            if (props->m_0x24 >= 0) {
              g_LevelMobys[props->m_0x24].m_Substate &= ~4;
            }
          }
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
      } else {
        moby->m_Class = 51;
        moby->m_State = 0;
        MOBY_ANIM_RESTART(moby, 0);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        int angle;

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (*props->m_0x10 == moby && TICK_TIMER(props->m_0x14)) {
          *props->m_0x10 = 0;
          if (props->m_0x24 >= 0) {
            g_LevelMobys[props->m_0x24].m_Substate &= ~4;
          }
        }

        if (TICK_TIMER(props->m_0x0c) && DISTANCE_TO_SPYRO(moby) < 0x1800 &&
            ABS2(SPYRO_BASE_Z_DELTA(moby) + 0x164) < 0x200 &&
            g_Spyro.m_airTime == 0 && g_Spyro.m_State != 0xB &&
            g_Spyro.m_State != 0x14 && *props->m_0x10 == 0) {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          if (func_80017908(moby->m_Rotation.z, angle) < 0x20) {
            moby->m_Substate = 0;
            *props->m_0x10 = moby;
            props->m_0x14 = 0x3C;
            props->m_0x0c = 0x3C;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
        break;
      }

      case 1: {
        Vector3D delta;
        int progress;

        if (g_AnimationFinished) {
          moby->m_Substate = 1;
          if (props->m_0x24 >= 0) {
            g_LevelMobys[props->m_0x24].m_Substate &= ~4;
          }
          props->m_0x0c = 0xF0;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        if (g_IsSpyroHidden && moby->m_AnimationState.m_NextFrame >= 0x20) {
          VecSub(&g_Spyro.unk_0x208, &props->m_0x18, &moby->m_Position);
          VecShiftRight(&g_Spyro.unk_0x208, 4);
          g_Spyro.m_DamageFlags = 0x80;
          g_IsSpyroHidden = 0;
          moby->m_Substate = 1;
          break;
        }

        if (moby->m_Substate == 0) {
          if (moby->m_AnimationState.m_NextFrame >= 7) {
            if (!g_IsSpyroHidden) {
              props->m_0x18.x = 0x25F;
              props->m_0x18.y = 0;
              props->m_0x18.z = 0x367;
              func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
              VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix,
                                &props->m_0x18, &props->m_0x18);
              VecAdd(&props->m_0x18, &moby->m_Position, &props->m_0x18);
            }

            VecSub(&delta, &props->m_0x18, &g_Spyro.m_Position);
            progress = ((moby->m_AnimationState.m_NextFrame - 7) << 12) / 25;
            VecMult(&delta, &delta, progress);
            VecShiftRight(&delta, 12);
            VecAdd(&g_Spyro.m_portalEndPos, &g_Spyro.m_Position, &delta);
            g_Spyro.m_fallingState = 0;
            g_IsSpyroHidden = 1;
            g_Spyro.m_ControlFlags = 0x80006107;
          } else {
            g_Spyro.m_ControlFlags = 0x80002100;
            g_Spyro.m_fallingState = 0x23;
          }
        }
        break;
      }

      case 2: {

        if (moby->m_Substate != 0) {
          int angle;
          int distance;
          if (*props->m_0x10 == moby && TICK_TIMER(props->m_0x14)) {
            *props->m_0x10 = 0;
            if (props->m_0x24 >= 0) {
              g_LevelMobys[props->m_0x24].m_Substate &= ~4;
            }
          }

          angle = ANGLE_FROM(moby->m_Position, props->m_0x00);
          distance = OctDistance(&moby->m_Position, &props->m_0x00);

          if (TICK_TIMER(props->m_0x0c) || distance < 0x20) {
            props->m_0x0c = 0x3C;
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }

          if (distance > 0x80) {
            distance = 0x80;
          }

          if (RotateMobyToAngle(moby, angle, 4, 0x18, 1) != 0) {
            func_80039398(moby, distance, 0x500, 0x500, 0x37);
          }
        } else {
          int angle;
          RotateMobyToSpyro(moby, 6, 0, 0);
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          func_80039688(moby, angle, 0x200, 0x500, 0x500, 0x37);

          if (TICK_TIMER(props->m_0x0c)) {
            *props->m_0x10 = 0;
            if (props->m_0x24 >= 0) {
              g_LevelMobys[props->m_0x24].m_Substate &= ~4;
            }
            moby->m_Substate = 1;
            props->m_0x0c = 0xF0;
            break;
          }

          if (!(DISTANCE_TO_SPYRO(moby) >= 1500 ||
                ABS2(SPYRO_BASE_Z_DELTA(moby) + 0x164) >= 0x200)) {
            moby->m_Substate = 0;

            if (props->m_0x24 >= 0) {
              if (!(g_LevelMobys[props->m_0x24].m_Substate & 2)) {
                *props->m_0x10 = 0;
                if (props->m_0x24 >= 0) {
                  g_LevelMobys[props->m_0x24].m_Substate &= ~4;
                }
                moby->m_Substate = 1;
                props->m_0x0c = 0xF0;
                break;
              }

              g_LevelMobys[props->m_0x24].m_Substate |= 4;
              moby->m_State = 1;
              MOBY_ANIM_CHANGE(moby, 1);
              continue;
            }

            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        }

        break;
      }

      case 3:
        if (g_AnimationFinished) {
          moby->m_Class = 51;
          moby->m_Substate = 1;
          props->m_0x0c = 0xF0;
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          continue;
        }
        break;

      case 4: {
        int radius = (moby->m_AnimationState.m_NextFrame << 7) + 0x200;

        if (radius > 0x500) {
          radius = 0x500;
        }

        func_8004E3C8(&moby->m_Position, radius, 0, 0, moby, 1);

        if (g_AnimationFinished) {
          props->m_0x0c = 0;
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
          continue;
        }
        break;
      }

      case 5:
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x34);
          func_80052568(moby);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_51
    case 51: {
      Moby51Props *props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 3) {
        if (*props->m_0x10 == moby) {
          *props->m_0x10 = 0;
        }

        if (moby->m_DamageFlags & MOBY_DAMAGE_FLAME) {
          props->m_0x2c = 200;
        } else {
          props->m_0x2c = 0x190;
        }

        props->m_0x30 = 0;
        props->m_0x28 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        moby->m_DamageFlags = 0;

        MOBY_ANIM_CHANGE(moby, 3);
        continue;
      }

      if (moby->m_State != 3 && props->m_0x24 >= 0 &&
          g_LevelMobys[props->m_0x24].m_Substate == 2) {
        if (*props->m_0x10 == moby) {
          *props->m_0x10 = 0;
        }
        moby->m_Class = 50;
        moby->m_State = 4;
        MOBY_ANIM_RESTART(moby, 4);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        int angle;

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (TICK_TIMER(props->m_0x0c) && DISTANCE_TO_SPYRO(moby) < 0xC00 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x400 && g_Spyro.m_State != 0xB &&
            g_Spyro.m_State != 0x14 && *props->m_0x10 == 0) {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          if (func_80017908(moby->m_Rotation.z, angle) < 0x20) {
            moby->m_Substate = 0;
            *props->m_0x10 = moby;
            props->m_0x0c = 0x3C;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        }
        break;
      }

      case 1: {
        if (moby->m_Substate != 0) {
          int angle;
          int distance;
          angle = ANGLE_FROM(moby->m_Position, props->m_0x00);
          distance = OctDistance(&moby->m_Position, &props->m_0x00);

          if (TICK_TIMER(props->m_0x0c) || distance < 0x20) {
            props->m_0x0c = 0x3C;
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }

          if (distance > 0x80) {
            distance = 0x80;
          }

          if (RotateMobyToAngle(moby, angle, 4, 0x18, 1) != 0) {
            func_80039398(moby, distance, 0x200, 0x200, 0x37);
          }
        } else {
          int angle;
          RotateMobyToSpyro(moby, 6, 0, 0);
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          func_80039688(moby, angle, 0xF0, 0x200, 0x200, 0x37);

          if (TICK_TIMER(props->m_0x0c)) {
            *props->m_0x10 = 0;
            moby->m_Substate = 1;
            props->m_0x0c = 0xF0;
          } else if (DISTANCE_TO_SPYRO(moby) < 0x300 &&
                     SPYRO_BASE_Z_DISTANCE(moby) < 800) {
            moby->m_State = 2;
            moby->m_Substate = 0;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
        break;
      }

      case 2:
        if (g_AnimationFinished) {
          moby->m_Substate = 1;
          *props->m_0x10 = 0;
          props->m_0x0c = 0xF0;
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;

      case 3:
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        MoveMobyWithGravity(moby, &props->m_0x2c, props->m_0x28, &props->m_0x30,
                            0xC, 0x10);
        break;
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_52
    case 52: {
      Moby52Props *props = moby->m_Props;
      Moby *spawn;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 2) {
        props->m_0x08 = 0xF0;
        props->m_0x04 = g_Spyro.m_bodyRotation.z;
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
      } else {
        switch (moby->m_State) {
        case 0:
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (TICK_TIMER(props->m_0x00) && moby->m_WasDrawn &&
              DISTANCE_TO_SPYRO(moby) < 0x2800 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 0xA00) {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
          }
          break;

        case 1:
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (g_AnimationFinished) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
          } else if (moby->m_AnimationState.m_NextFrame >= 6 &&
                     !props->m_0x00) {
            func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
            spawn = g_SpawnMoby(55, moby);
            g_SpawnParticle(16, 28, spawn, 0x10);
            props->m_0x00 = props->m_0x0c;
          }
          break;
        case 2:
          if (g_AnimationFinished) {
            func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
            func_800385BC(moby, 0x28);
            func_80052568(moby);
          } else if (props->m_0x08 > 0) {
            func_80039688(moby, props->m_0x04, props->m_0x08, 500, 700, 1);
            props->m_0x08 -= 0x10;
          }
          break;
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_53
    case 53: {
      Moby53Props *props = moby->m_Props;

      ApplyFlameHeat(moby);
      moby->m_DamageFlags = 0;

      if (props->m_0x0c >= 0) {
        if (moby->m_State != 2 && g_LevelMobys[props->m_0x0c].m_Substate == 3) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
      } else {
        moby->m_Class = 54;
        moby->m_State = 0;
        MOBY_ANIM_RESTART(moby, 0);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        int angle;

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (props->m_0x10 != 0) {
          if (moby->m_Substate < 2 && g_Spyro.m_State == 0xE) {
            props->m_0x10 += 0x3C;
            moby->m_Substate = 2;
          }

          if (TICK_TIMER(props->m_0x10) && moby->m_WasDrawn) {
            props->m_0x10 = 1;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        } else if (DISTANCE_TO_SPYRO(moby) < 0x1400 &&
                   SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          if (func_80017908(moby->m_Rotation.z, angle) < 0x18) {
            if (moby->m_Substate != 0) {
              props->m_0x10 = 0x2C;
            } else {
              props->m_0x10 = 0x1A;
            }
            moby->m_Substate = 1;
          } else {
            moby->m_Substate = 0;
          }
        } else {
          moby->m_Substate = 0;
        }
        break;
      }

      case 1: {
        Moby *spawn;

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        if (moby->m_AnimationState.m_NextFrame >= 5 && props->m_0x10 != 0) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          spawn = g_SpawnMoby(155, moby);
          if (DISTANCE_TO_SPYRO(moby) < 0xC00) {
            VecCopy(&spawn->m_Position, &g_Spyro.m_Position);
          }
          props->m_0x10 = 0;
        }
        break;
      }

      case 2:
        if (g_AnimationFinished) {
          moby->m_Class = 54;
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;

      case 3:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }

#endif
#ifdef HAS_MOBY_54
    case 54: {
      Moby54Props *props = moby->m_Props;

      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State < 2) {
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        props->m_0x00 = 0x190;
        props->m_0x04 = 0x8C;
        props->m_0x08 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x28, 0x80);
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        continue;
      }

      moby->m_DamageFlags = 0;

      if (moby->m_State < 2 && props->m_0x0c >= 0 &&
          g_LevelMobys[props->m_0x0c].m_Substate == 2) {
        moby->m_Class = 53;
        moby->m_State = 3;
        MOBY_ANIM_RESTART(moby, 3);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        int angle;

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (props->m_0x10 != 0) {
          if (moby->m_Substate < 2 && g_Spyro.m_State == 0xE) {
            props->m_0x10 += 0x3C;
            moby->m_Substate = 2;
          }

          if (TICK_TIMER(props->m_0x10) && moby->m_WasDrawn) {
            props->m_0x10 = 1;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        } else if (DISTANCE_TO_SPYRO(moby) < 0x1400 &&
                   SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          if (func_80017908(moby->m_Rotation.z, angle) < 0x18) {
            if (moby->m_Substate != 0) {
              props->m_0x10 = 0x2C;
            } else {
              props->m_0x10 = 0x1A;
            }
            moby->m_Substate = 1;
          } else {
            moby->m_Substate = 0;
          }
        } else {
          moby->m_Substate = 0;
        }
        break;
      }

      case 1:
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        if (moby->m_AnimationState.m_NextFrame >= 2 && props->m_0x10 != 0) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          g_SpawnMoby(155, moby);
          props->m_0x10 = 0;
        }
        break;

      case 2:
        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_SET_NEXT(moby, 3);
          continue;
        }

        moby->m_Rotation.y += 4;
        RotateMobyToAngle(moby, (props->m_0x08 + 0x80) & 0xFF, 0x10, 0x20, 1);
        MoveMobyWithGravity(moby, &props->m_0x00, props->m_0x08, &props->m_0x04,
                            0xC, 0xC);
        break;

      case 3:
        if (MoveMobyWithGravity(moby, &props->m_0x00, props->m_0x08,
                                &props->m_0x04, 0xC, 0x10) == 3) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        RotateMobyToAngle(moby, (props->m_0x08 + 0x80) & 0xFF, 0x10, 0x20, 1);
        break;

      case 4:
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_55
    case 55: { // Cupid Arrow
      Moby55Props *props = moby->m_Props;
      Vector3D oldPosition;

      switch (moby->m_State) {
      case 0:
        if (moby->m_Position.x >= 0x400 && moby->m_Position.y >= 0x400 &&
            moby->m_Position.z >= 0x400) {
          VecCopy(&oldPosition, &moby->m_Position);
          if (props->m_Lifetime < 100) {
            func_8004E3C8(&moby->m_Position, 100, 0, 0x20000, moby, 0);
          }
          if (func_8004E2E8(&moby->m_Position, 100, 7) ||
              TICK_TIMER(props->m_Lifetime) ||
              func_8003BCCC(moby, 0xE0, 0, 0x100, 0) ||
              func_8004AE38(&oldPosition, &moby->m_Position)) {
            moby->m_State = 1;
          }
          g_SpawnParticle(1, 28, moby, 8);
        } else {
          moby->m_State = 1;
        }

        break;

      case 1:
        g_SpawnParticle(16, 28, moby, 0x10);
        func_80052568(moby);
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_56
    case 56: { // Nothing seems to spawn this
      Moby56Props *props = moby->m_Props;
      Vector3D oldPosition;

      switch (moby->m_State) {
      case 0:
        VecCopy(&oldPosition, &moby->m_Position);

        if (props->m_Lifetime < 200) {
          func_8004E3C8(&moby->m_Position, 100, 0, 0x20000, moby, 0);
        }

        if (func_8004E2E8(&moby->m_Position, 100, 7) ||
            TICK_TIMER(props->m_Lifetime) ||
            func_8003BCCC(moby, 0x80, 0, 0x100, 0) ||
            func_8004AE38(&oldPosition, &moby->m_Position)) {
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          continue;
        }
        break;

      case 1:
        if (g_AnimationFinished) {
          func_80052568(moby);
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_57
    case 57: {

      Moby57Props *props = moby->m_Props;
      Vector3D oldPosition;

      switch (moby->m_State) {
      case 0: {
        int i;
        int floorZ;
        int height;

        if (moby->m_Substate == 0) {
          break;
        }

        floorZ = func_80038340(moby);
        height = moby->m_Position.z - 0x50;
        props->m_0x04 = floorZ - height;
        if (props->m_0x04 > 0x50) {
          props->m_0x04 = 0x50;
        }
        if (props->m_0x04 < -0x50) {
          props->m_0x04 = -0x50;
        }
        if (ABS2(props->m_0x04) < 0x32) {
          props->m_0x04 = 0;
        }
        if (props->m_0x0a >= 0xB) {
          props->m_0x04 = 0;
        }

        VecCopy(&oldPosition, &moby->m_Position);
        moby->m_Position.x += props->m_0x00;
        moby->m_Position.y += props->m_0x02;
        moby->m_Position.z += props->m_0x04;
        moby->m_Rotation.x += props->m_0x0c;
        moby->m_Rotation.y += props->m_0x0d;
        moby->m_Rotation.z += props->m_0x0e;
        props->m_0x0a += g_DeltaTime;

        if (moby->m_Substate != 2 && props->m_0x0a < 0x79) {
          if (func_8004E2E8(&moby->m_Position, 220, 0x86) == 0) {
            if (func_8004AE38(&oldPosition, &moby->m_Position) == 0) {
              break;
            }
          }
        }

        for (i = 0; i < 8 && DYN_MOBY_FREE_COUNT > 20; i++) {
          Moby *fragment;
          Moby57Props *fragmentProps;

          fragment = g_SpawnMoby(57, moby);
          fragment->m_State = 1;
          if (fragment->m_AnimationState.m_Animation != 1) {
            MOBY_ANIM_RESTART(fragment, 1);
          }

          fragmentProps = fragment->m_Props;
          if (moby->m_Substate == 2) {
            int angle = (props->m_0x0f + RandRange(-40, 40)) & 0xFF;
            int speed = RandRange(150, 250);
            fragmentProps->m_0x00 = FIXED_MUL(speed, COSINE_8(angle));
            fragmentProps->m_0x02 = FIXED_MUL(speed, SINE_8(angle));
          } else {
            fragmentProps->m_0x00 = RandRange(-150, 150);
            fragmentProps->m_0x02 = RandRange(-150, 150);
          }
          fragmentProps->m_0x04 = RandRange(-120, 250);
          fragmentProps->m_0x0a = RandRange(80, 120);
          fragment->m_Rotation.x = rand();
          fragment->m_Rotation.y = rand();
          fragment->m_Rotation.z = rand();
          fragmentProps->m_0x0c = RandRangeSigned(7, 15);
          fragmentProps->m_0x0d = RandRangeSigned(7, 15);
          fragmentProps->m_0x0e = RandRangeSigned(7, 15);
        }

        g_Spyro.unk_0x208.x = FIXED_MUL(props->m_0x00, 0x600);
        g_Spyro.unk_0x208.y = FIXED_MUL(props->m_0x02, 0x600);
        g_Spyro.unk_0x208.z = 30;
        func_80052568(moby);
        continue;
      }

      case 1: {
        Vector3D velocity;
        Vector3D normal;

        if (moby->m_WasDrawn == 0) {
          func_80052568(moby);
          continue;
        }

        moby->m_Rotation.x += props->m_0x0c;
        moby->m_Rotation.y += props->m_0x0d;
        moby->m_Rotation.z += props->m_0x0e;
        props->m_0x04 -= 0x14;
        if (props->m_0x04 < -0xA0) {
          props->m_0x04 = -0xA0;
        }

        velocity.x = props->m_0x00;
        velocity.y = props->m_0x02;
        velocity.z = props->m_0x04;
        VecCopy(&oldPosition, &moby->m_Position);
        VecAdd(&moby->m_Position, &moby->m_Position, &velocity);

        if (TICK_TIMER(props->m_0x0a)) {
          func_80052568(moby);
          continue;
        }

        if (func_8004BE4C(&moby->m_Position, 0x100, 0x100) == 0) {
          break;
        }

        VecCopy(&normal, &g_CollisionNormal);
        if (func_80017428(&velocity, &normal, &velocity) == 0) {
          break;
        }

        // FIXED_MUL with 0xE00 compiles as srl instead of sra
        props->m_0x00 = velocity.x * 7 >> 3;
        props->m_0x02 = velocity.y * 7 >> 3;
        props->m_0x04 = velocity.z * 7 >> 3;
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_61
    case 61: { // Lofty Castle Fairy Cage
      Moby61Props *props = moby->m_Props;
      int floorZ;

      // Intact Cage breaking
      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State == 0) {
        props->m_FallSpeed = 0;
        g_LevelMobys[props->m_CagedFairyIndex].m_State = 1;
        func_8003851C(&g_LevelMobys[props->m_CagedFairyIndex], 0, 0);
        func_8003B7C0(&g_LevelMobys[props->m_CagedFairyIndex]);
        func_8003B854(0, &g_LevelMobys[props->m_CagedFairyIndex]);
        func_8003B7C0(moby);
        func_8003B854(0, moby);
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
        break;
      } else if (moby->m_State == 1) {
        // Move cage towards the floor at increasing speed
        props->m_FallSpeed += 12;
        if (props->m_FallSpeed > 120) {
          props->m_FallSpeed = 120;
        }
        moby->m_Position.z += 512;
        floorZ = func_8004D5EC(&moby->m_Position, props->m_FallSpeed + 512);
        if (floorZ != 0) {
          moby->m_Position.z = floorZ;
        } else {
          moby->m_Position.z -= props->m_FallSpeed + 512;
        }
        if (g_AnimationFinished) {
          func_80052568(moby);
          break;
        }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_62
    case 62: {
      Moby62Props *props = moby->m_Props;
      int distance;
      int angle;
      int angleDelta;
      int pathNode;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 4) {
        props->m_0x10 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        if (moby->m_DamageFlags & MOBY_DAMAGE_SUPER) {
          props->m_0x14 = (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >> 6) + 450;
          props->m_0x18 = 0x50;
        } else if (moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) {
          props->m_0x14 = 500;
          props->m_0x18 = 0x20;
        } else {
          props->m_0x14 = 300;
          props->m_0x18 = 0x10;
        }
        func_8003ABC0(moby, 4, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 4;
        MOBY_ANIM_CHANGE(moby, 4);
        break;
      }

      if (props->m_0x20 < 0) {
        if (props->m_0x24) {
          props->m_0x20 = props->m_0x1c->m_CurrentNode;
          props->m_0x1c->m_Reversed = -1;
        } else {
          props->m_0x20 = 0;
        }
      }

      if (TICK_TIMER(props->m_0x2c) && moby->m_State < 3) {
        int randNum;
        randNum = rand() % 3;
        while (randNum == props->m_0x28) {
          randNum = rand() % 3;
        }
        func_8003851C(moby, randNum, 0);
        props->m_0x28 = randNum;
        props->m_0x2c = rand() % 45 + 90;
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x24) {
          UpdatePufferBirdMobyPathNode(moby, props->m_0x1c, 0x400, 0x5C, 0x180,
                                       4, 2);
        } else {
          RotateMobyToSpyro(moby, 3, 0, 0);
          angleDelta = (-moby->m_Rotation.y) & 0xFF;
          if (angleDelta > 0x80) {
            angleDelta -= 0x100;
          }
          if (angleDelta >= 3) {
            angleDelta = 2;
          }
          if (angleDelta < -2) {
            angleDelta = -2;
          }
          moby->m_Rotation.y += angleDelta;
        }
        if (moby->m_WasDrawn && DISTANCE_TO_SPYRO(moby) < 0x800 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          if (func_80017908(moby->m_Rotation.z, angle) < 0x20 &&
              func_80038250(&moby->m_Position)) {
            props->m_0x0c = 0x78;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
        (moby, 5);
        break;

      case 1: {
        Vector3D delta;

        if (props->m_0x24) {
          distance = func_80038A40(moby, props->m_0x1c, &pathNode);
          props->m_0x1c->m_CurrentNode = pathNode;
          if (distance < 0x200) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
          angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x1c));
          angleDelta = (angle - moby->m_Rotation.z) & 0xFF;
          if (angleDelta > 0x80) {
            angleDelta -= 0x100;
          }
          if (ABS2(angleDelta) < 0x18) {
            distance >>= 4;
            if (distance > 0x5C) {
              distance = 0x5C;
            }
            if (props->m_0x0c) {
              if (MoveMobyTowardTarget(moby, &PATH_CUR_POS(props->m_0x1c),
                                       distance, 4, 2, 0x180)) {
                TICK_TIMER(props->m_0x0c);
              } else {
                props->m_0x0c = 0x3C;
              }
            } else {
              MoveMobyTowardTarget(moby, &PATH_CUR_POS(props->m_0x1c), distance,
                                   4, 2, 0);
            }
          } else {
            RotateMobyToAngle(moby, angle, 4, 0, 0);
          }
          break;
        }

        VecSub(&delta, &moby->m_Position, &props->m_0x00);
        distance = VecMagnitude(&delta, 1);
        if (distance < 0x200) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        angle = ANGLE_FROM(moby->m_Position, props->m_0x00);
        angleDelta = (angle - moby->m_Rotation.z) & 0xFF;
        if (angleDelta > 0x80) {
          angleDelta -= 0x100;
        }
        if (ABS2(angleDelta) < 0x18) {
          distance >>= 4;
          if (distance > 0x5C) {
            distance = 0x5C;
          }
          if (props->m_0x0c) {
            if (MoveMobyTowardTarget(moby, &props->m_0x00, distance, 4, 2,
                                     0x180)) {
              TICK_TIMER(props->m_0x0c);
            } else {
              props->m_0x0c = 0x3C;
            }
          } else {
            MoveMobyTowardTarget(moby, &props->m_0x00, distance, 4, 2, 0);
          }
        } else {
          RotateMobyToAngle(moby, angle, 4, 0, 0);
        }
        break;
      }

      case 2:
        MoveMobyTowardTarget(moby, &g_Spyro.m_Position, 0x80, 4, 2, 0x180);
        if (moby->m_WasDrawn && func_80038250(&moby->m_Position)) {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          if (func_80017908(moby->m_Rotation.z, angle) < 0x18) {
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
            continue;
          }
          if (TICK_TIMER(props->m_0x0c)) {
            props->m_0x0c = 0x3C;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
          break;
        }
        moby->m_State = 1;
        MOBY_ANIM_CHANGE(moby, 1);
        continue;

      case 3:
        MoveMobyTowardTarget(moby, &g_Spyro.m_Position, 0x40, 4, 2, 0x180);
        if (g_AnimationFinished) {
          props->m_0x0c = 0x3C;
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;

      case 4:
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        if (MoveMobyWithGravity(moby, &props->m_0x14, props->m_0x10,
                                &props->m_0x18, 0xC, 0x10)) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }
      func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_66
    case 66: {
      Moby66Props *props = moby->m_Props;

      if (props->m_0x14 == 1) {
        if (moby->m_State != 7) {
          moby->m_State = 7;
          moby->m_AnimationState.m_Animation = 7;
          moby->m_AnimationState.m_NextAnimation = 7;
          moby->m_AnimationState.m_FrameProgress = 0;
          moby->m_AnimationState.m_PerFrameProgress = 0;
          moby->m_AnimationState.m_Frame = 0;
          moby->m_AnimationState.m_NextFrame = 1;
        }
        func_800529E4(moby, UPDATE_PROP_COLLISION);
        if (g_LevelMobys[props->m_0x10].m_State >= 0x80) {
          props->m_0x14 = 2;
        }
        break;
      }

      if (props->m_0x14 == 2) {
        if (TICK_TIMER(props->m_0x00)) {
          moby->m_RenderRadius = 0x20;
          moby->m_AnimationState.m_PerFrameProgress = 0x10;
        } else {
          moby->m_AnimationState.m_PerFrameProgress = 0;
          moby->m_DamageFlags = 0;
        }

        if (moby->m_State != 7 && moby->m_State != 5) {
          moby->m_State = 7;
          MOBY_ANIM_SET_NEXT(moby, 7);
          continue;
        }
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 5) {
        props->m_0x04 = 200;
        props->m_0x08 = g_Spyro.m_bodyRotation.z;
        props->m_0x14 = 0;
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 5;
        MOBY_ANIM_CHANGE(moby, 5);
        continue;
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x14 == 4) {
          moby->m_State = 9;
          MOBY_ANIM_CHANGE(moby, 9);
          continue;
        }

        if (props->m_0x14 == 5) {
          moby->m_State = 8;
          MOBY_ANIM_CHANGE(moby, 8);
          continue;
        }

        if (props->m_0x14 == 6) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }

        RotateMobyToSpyro(moby, 3, 0x10, 0);
        if (DISTANCE_TO_SPYRO(moby) < 6000 &&
            SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }

        if (props->m_0x0c >= 0) {
          if (g_LevelMobys[props->m_0x0c].m_State < 0x80) {
            int *linkedProps = g_LevelMobys[props->m_0x0c].m_Props;

            if (linkedProps[1] == 1) {
              PathData *path = (PathData *)linkedProps[0];
              int angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(path));
              RotateMobyToAngle(moby, angle, 4, 8, 1);
            }
          } else {
            props->m_0x0c = -1;
          }
        }
        break;

      case 1:
        if (g_AnimationFinished) {
          props->m_0x00 = 0x40;
          moby->m_State = 2;
          MOBY_ANIM_SET_NEXT(moby, 2);
          continue;
        }

        if (DISTANCE_TO_SPYRO(moby) < 6000 &&
            SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
          RotateMobyToSpyro(moby, 3, 0, 0);
        }
        break;

      case 2: {
        int distance = DISTANCE_TO_SPYRO(moby);

        if (distance < 4000 && SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
          props->m_0x00 = 0;
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }

        if (props->m_0x14 >= 5) {
          int angle;

          if (g_LevelMobys[props->m_0x0c].m_State >= 0x80) {
            props->m_0x14 = 0;
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }

          if (distance < 6000 && SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
            RotateMobyToSpyro(moby, 3, 0, 0);
            break;
          }

          angle = ANGLE_FROM(moby->m_Position,
                             g_LevelMobys[props->m_0x0c].m_Position);
          RotateMobyToAngle(moby, angle, 8, 0, 0);
          if (TICK_TIMER(props->m_0x00)) {
            moby->m_State = 9;
            MOBY_ANIM_CHANGE(moby, 9);
            continue;
          }
        } else {
          RotateMobyToSpyro(moby, 3, 0, 0);
          if (distance >= 0x1B59) {
            moby->m_State = 4;
            MOBY_ANIM_CHANGE(moby, 4);
            continue;
          }

          if (TICK_TIMER(props->m_0x00)) {
            moby->m_State = 8;
            MOBY_ANIM_CHANGE(moby, 8);
            continue;
          }
        }
        break;
      }

      case 3:
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_Spyro.m_State == 0x19) {
          props->m_0x00 = 3;
        }
        if (g_AnimationFinished) {
          if (props->m_0x00 != 0) {
            moby->m_State = 6;
            MOBY_ANIM_SET_NEXT(moby, 6);
            continue;
          }
          if (DISTANCE_TO_SPYRO(moby) < 6000 &&
              SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
            moby->m_State = 1;
            MOBY_ANIM_SET_NEXT(moby, 1);
            continue;
          }
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
          continue;
        }
        break;

      case 4:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
          continue;
        }
        break;

      case 5:
        if (props->m_0x04 > 0) {
          func_80039688(moby, props->m_0x08, props->m_0x04, 500, 700, 0);
          props->m_0x04 -= 0x10;
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x32);
          func_80052568(moby);
          continue;
        }
        break;

      case 6:
        if (g_AnimationFinished && TICK_TIMER(props->m_0x00)) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 7:
        if (g_AnimationFinished) {
          props->m_0x14 = 3;
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
          continue;
        }
        break;

      case 8:
        if (props->m_0x14 >= 5 && props->m_0x0c >= 0) {
          int angle;

          if (g_LevelMobys[props->m_0x0c].m_State >= 0x80) {
            props->m_0x14 = 0;
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }

          if (DISTANCE_TO_SPYRO(moby) < 6000 &&
              SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
            RotateMobyToSpyro(moby, 3, 0, 0);
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }

          angle = ANGLE_FROM(moby->m_Position,
                             g_LevelMobys[props->m_0x0c].m_Position);
          RotateMobyToAngle(moby, angle, 8, 0, 0);
          break;
        }

        RotateMobyToSpyro(moby, 3, 0, 0);

        if (g_AnimationFinished) {
          props->m_0x00 = 0x5A;
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;

      case 9:
        if (props->m_0x14 == 4) {
          if (g_AnimationFinished) {
            props->m_0x00 = 3;
            props->m_0x14 = 0;
            moby->m_State = 0;
            MOBY_ANIM_SET_NEXT(moby, 0);
            continue;
          }
        } else if (props->m_0x14 >= 5) {
          int angle = ANGLE_FROM(moby->m_Position,
                                 g_LevelMobys[props->m_0x0c].m_Position);
          RotateMobyToAngle(moby, angle, 8, 0, 0);
          if (g_AnimationFinished) {
            moby->m_State = 1;
            MOBY_ANIM_SET_NEXT(moby, 1);
            continue;
          }
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_70
    case 70: {

      Moby70Props *props = moby->m_Props;

      switch (moby->m_State) {
      case 0: {
        moby->m_Position.x +=
            FIXED_MUL(props->m_0x00, COSINE_8(moby->m_Rotation.z));
        moby->m_Position.y +=
            FIXED_MUL(props->m_0x00, SINE_8(moby->m_Rotation.z));
        if (TICK_TIMER(props->m_0x10)) {
          func_80052568(moby);
          continue;
        }
        if (func_8004E2E8(&moby->m_Position, 200, 0x26) != 0) {
          func_80052568(moby);
          continue;
        }
        func_8003B294(moby, props->m_0x12, 0xC0000, 600, 1200, 1200, 0x28);
        if (func_8004BE4C(&moby->m_Position, 0x168, 0x168) != 0) {
          func_80052568(moby);
          continue;
        }
        moby->m_Position.z += props->m_0x04;
        props->m_0x04 += props->m_0x08;
        moby->m_Rotation.y = Atan2(props->m_0x00, props->m_0x04, 0);
        break;
      }

      case 1: {
        Vector3D particleVelocity;
        Vector3D particlePosition;
        int i;

        for (i = 0; i < 8; i++) {
          particleVelocity.x = (rand() & 0x3E) - 0x1F;
          particleVelocity.y = (rand() & 0x3E) - 0x1F;
          particleVelocity.z = rand() & 0xF;
          VecCopy(&particlePosition, &particleVelocity);
          VecShiftLeft(&particlePosition, 2);
          VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
          g_SpawnParticle(1, 13, &particlePosition, (int)&particleVelocity);
        }
        func_80052568(moby);
        continue;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#if defined(HAS_MOBY_77) || defined(HAS_MOBY_168)
#ifdef HAS_MOBY_77
    case 77:
#endif
#ifdef HAS_MOBY_168
    case 168:
#endif
    {
      if (moby->m_Substate != 0) {
        moby->m_Substate--;
        moby->m_AnimationState.m_Frame = 0;
        moby->m_AnimationState.m_NextFrame = 1;
        moby->m_AnimationState.m_FrameProgress = 0;
      }
      if (g_AnimationFinished) {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_82
    case 82: {

      Moby82Props *props = moby->m_Props;
      Vector3D oldPosition;

      VecCopy(&oldPosition, &moby->m_Position);
      VecAdd(&moby->m_Position, &moby->m_Position, &props->m_0x00);

      if (props->m_0x0f == 1) {
        if (TICK_TIMER(props->m_0x0c)) {
          func_80052568(moby);
          continue;
        }
        break;
      }

      if (func_8004E2E8(&moby->m_Position, 100, 0x26) != 0) {
        g_Spyro.unk_0x208.z = 0;
        func_80052568(moby);
        continue;
      }
      if (TICK_TIMER(props->m_0x0c)) {
        func_80052568(moby);
        continue;
      }
      if (func_8004AE38(&oldPosition, &moby->m_Position) != 0) {
        func_80052568(moby);
        continue;
      }
      func_8003B294(moby, props->m_0x0e, 0xC0000, 300, 1200, 600, 0x32);
      break;
    }
#endif
#ifdef HAS_MOBY_91 // Dream Weavers Cannon
    case 91: {
      Moby91Props *props;
      Moby *linkedMoby;

      props = moby->m_Props;
      linkedMoby = &g_LevelMobys[props->m_0x04];
      func_800529E4(moby, UPDATE_PROP_ROTMATRIX);

      if (moby->m_AnimationState.m_NextAnimation >= 3 &&
          moby->m_AnimationState.m_NextFrame >= 0xE &&
          moby->m_AnimationState.m_NextAnimation != 0) {
        g_AnimationFinished = 0;
        MOBY_ANIM_ADVANCE(moby, 0);
      }

      if (props->m_0x24 == 0) {
        props->m_0x24 = 1;
        props->m_0x14 = moby->m_Rotation.z << 4;
      }

      if (props->m_0x18 != 0) {
        g_Spyro.m_ControlFlags = 0x80001000;
        g_Spyro.m_mobyInUseBySpyro = moby;
      }

      switch (moby->m_State) {
      case 0: {
        int range;
        int angleWindow;
        int angleThreshold;
        int angleA;
        int angleAbs;
        int angleB;
        int attackAngle;

        if (moby->m_Substate != 0 && linkedMoby->m_State < 127) {
          props->m_0x08 = moby->m_Substate;
          moby->m_Substate = 0;
          props->m_0x20 = (props->m_0x20 + 1) % 3;
          moby->m_State = 10;
          continue;
        }

        if (linkedMoby->m_State >= 0x80) {
          range = 0x4E2;
          angleWindow = 0x20;
          angleThreshold = 0x50;
          if (props->m_0x18 != 0) {
            range = 1400;
            angleWindow = 0x2C;
            angleThreshold = 0x41;
          }

          TICK_TIMER(props->m_0x10);

          if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
            Vector3D vector;
            moby->m_DamageFlags = 0;
            vector.x = -1000;
            vector.y = 0;
            vector.z = 0x172;
            func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
            VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vector,
                              &vector);
            VecAdd(&vector, &vector, &moby->m_Position);
            attackAngle = ANGLE_FROM_SPYRO(vector);
            if (props->m_0x10 == 0 &&
                func_80017908(attackAngle, g_Spyro.m_bodyRotation.z) < 0x30) {
              moby->m_State = 1;
              continue;
            }
          }

          props->m_0x18 = 0;
          if (DISTANCE_TO_SPYRO(moby) < range) {
            angleA =
                func_800381BC(moby->m_Rotation.z, g_Spyro.m_bodyRotation.z);
            angleAbs = ABS2(angleA);
            if (angleAbs > 0x40 - angleWindow &&
                angleAbs < angleWindow + 0x40) {
              angleB = func_800381BC(ANGLE_TO_SPYRO(moby->m_Position),
                                     moby->m_Rotation.z);
              if (ABS2(angleB) > angleThreshold) {
                if ((angleA < 0 && angleB < 0) || (angleA > 0 && angleB > 0)) {
                  props->m_0x18 = 1;
                }
              }
            }
          }
        } else {
          props->m_0x14 = moby->m_Rotation.z << 4;
        }

        moby->m_DamageFlags = 0;
        break;
      }

      case 1: {
        props->m_0x10 = 0x4B;
        moby->m_State = 3;
        continue;
      }

      case 2: {
        int i;

        if (props->m_0x10 >= 0xB) {
          Vector3D particlePosition;
          Vector3D particleVelocity;
          moby->m_DamageFlags = 0;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 3, &particlePosition);
          particleVelocity.x = -0x10;
          particleVelocity.y = 0;
          particleVelocity.z = -0xE;
          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix,
                            &particleVelocity, &particleVelocity);
          for (i = 0; i < 5; i++) {
            particleVelocity.x += (rand() & 0xF) - 8;
            particleVelocity.y += (rand() & 0xF) - 8;
            g_SpawnParticle(1, 74, &particlePosition, (int)&particleVelocity);
          }
        }

        if (TICK_TIMER(props->m_0x10)) {
          func_800562A4(moby, 2);
          moby->m_State = 3;
          continue;
        }
        break;
      }

      case 3: {
        Moby104Props *projectileProps;
        Moby *projectile;
        Moby *candidate;
        Moby *bestMoby;
        Vector3D delta;
        Vector3D targetPosition;
        int angle;
        int distance;
        int bestScore;
        int flightTime;

        func_8003851C(moby, 1, 0);
        props->m_0x20 = (props->m_0x20 + 1) % 3;
        projectile = g_SpawnMoby(104, moby);
        projectileProps = projectile->m_Props;
        VecCopy(&projectile->m_Position, &moby->m_Position);
        projectile->m_Rotation.z = moby->m_Rotation.z;
        func_80039398(projectile, 600, 0, 0, 0);
        projectile->m_Position.z += 0x352;
        projectileProps->m_0x08 = 800;
        projectileProps->m_0x0e = -6;
        projectileProps->m_0x0a = 150;
        projectileProps->m_0x10 = 0x8C;
        projectileProps->m_0x12 = 0;
        projectileProps->m_0x13 = 0;
        projectileProps->m_0x0c = 0;
        projectileProps->m_0x00 = 0;
        projectileProps->m_0x02 = 0;
        projectileProps->m_0x04 = props->m_0x28.m_Normal[props->m_0x20];
        projectile->m_RenderRadius = 0;
        projectile->m_UpdateDistance = 0xFF;
        bestMoby = 0;
        bestScore = 42000;
        moby->m_DamageFlags = 0;

        for (candidate = g_LevelMobys; candidate < g_DynMobys; candidate++) {
          if (candidate == moby) {
            continue;
          }
          if (candidate->m_State >= 0x80) {
            continue;
          }
          if (candidate->m_Class == 250 || candidate->m_Class == 110) {
            continue;
          }
          if (candidate->m_CollisionGroup == 0) {
            continue;
          }
          if ((int)candidate->m_CollisionGroup >= 0) {
            continue;
          }

          VecSub(&delta, &candidate->m_Position, &moby->m_Position);
          distance = ABS2(delta.x) + ABS2(delta.y);
          if (distance >= 0x11000) {
            continue;
          }

          angle = (ANGLE_FROM(moby->m_Position, candidate->m_Position) -
                   moby->m_Rotation.z) &
                  0xFF;
          if (angle > 0x80) {
            angle -= 0x100;
          }
          angle = ABS2(angle);
          if (angle >= 7) {
            continue;
          }

          if (distance < 0xC000) {
            distance = VecMagnitude(&delta, 0);
          } else {
            distance = OctDistance(&candidate->m_Position, &moby->m_Position);
          }
          if (distance >= 0xB000) {
            continue;
          }

          if (distance > 0x5800) {
            distance -= 0x5800;
          } else if (distance < 0x4000) {
            distance = 0x4000 - distance;
          } else {
            distance = 0;
          }
          distance += angle << 12;
          if (distance < bestScore) {
            bestMoby = candidate;
            bestScore = distance;
          }
        }

        if (bestMoby != 0) {
          VecCopy(&targetPosition, &bestMoby->m_Position);
          if (bestMoby->m_Class == 92 || bestMoby->m_Class == 130) {
            targetPosition.z += 800;
          }
          projectile->m_Rotation.z =
              ANGLE_FROM(moby->m_Position, bestMoby->m_Position);
          projectileProps->m_0x0e = -8;
          projectileProps->m_0x08 = 600;
          projectileProps->m_0x0a =
              func_8003891C(&projectile->m_Position, &targetPosition, 600,
                            projectileProps->m_0x0e, &flightTime);
          projectileProps->m_0x00 = flightTime;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
        moby->m_State = 0;
        continue;
      }

      case 10: {
        Moby104Props *projectileProps;
        Moby *projectile;
        int flightTime;
        Vector3D targetPosition;
        int velocityZ;
        int i;
        int angle;

        if (moby->m_AnimationState.m_NextAnimation == 3) {
          g_AnimationFinished = 0;
          moby->m_AnimationState.m_Animation = 3;
          moby->m_AnimationState.m_FrameProgress = 0;
          moby->m_AnimationState.m_Frame = 0;
          moby->m_AnimationState.m_NextFrame = 1;
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);

        if (moby->m_WasDrawn) {
          angle = ANGLE_FROM(moby->m_Position,
                             g_LevelMobys[props->m_0x08].m_Position);
          if (RotateMobyToAngle(moby, angle, 6, 0x14, 1) == 0) {
            continue;
          }
        }

        VecCopy(&targetPosition, &g_LevelMobys[props->m_0x08].m_Position);
        projectile = g_SpawnMoby(104, moby);
        projectile->m_Rotation.z =
            ANGLE_FROM(projectile->m_Position, targetPosition);
        VecCopy(&projectile->m_Position, &moby->m_Position);
        targetPosition.z += 800;
        projectile->m_Position.x +=
            FIXED_MUL(COSINE_8(projectile->m_Rotation.z), 2000);
        projectile->m_Position.y +=
            FIXED_MUL(SINE_8(projectile->m_Rotation.z), 2000);
        projectile->m_Position.z += 1400;
        projectile->m_RenderRadius = 0;
        projectile->m_UpdateDistance = 0xFF;
        projectileProps = projectile->m_Props;
        projectileProps->m_0x10 = 0x78;
        projectileProps->m_0x12 = props->m_0x00;
        projectileProps->m_0x13 = 0;
        projectileProps->m_0x0e = -7;
        projectileProps->m_0x08 = 800;
        projectileProps->m_0x0c = 0;
        projectileProps->m_0x0a =
            func_8003891C(&projectile->m_Position, &targetPosition, 800,
                          projectileProps->m_0x0e, &flightTime);
        projectileProps->m_0x04 = props->m_0x28.m_Targeted[props->m_0x20];
        velocityZ = projectileProps->m_0x0a;
        projectileProps->m_0x02 = 1;
        projectileProps->m_0x00 = flightTime;
        // TODO: Remove artificial scope
        {
          Vector3D simulatedPosition;
          VecCopy(&simulatedPosition, &projectile->m_Position);

          for (i = 0; i < flightTime; i++) {
            simulatedPosition.x += FIXED_MUL(
                projectileProps->m_0x08, COSINE_8(projectile->m_Rotation.z));
            simulatedPosition.y += FIXED_MUL(projectileProps->m_0x08,
                                             SINE_8(projectile->m_Rotation.z));
            simulatedPosition.z += velocityZ;
            velocityZ += projectileProps->m_0x0e;
          }

          VecSub(&simulatedPosition, &targetPosition, &simulatedPosition);
          VecAdd(&projectile->m_Position, &projectile->m_Position,
                 &simulatedPosition);
        }
        moby->m_State = 0;
        continue;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_92 // Carrot-Topped Monk
    case 92: {
      Moby92Props *props;
      Vector3D delta;
      int distance;
      int result;
      int angle;

      props = moby->m_Props;
      VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);
      if (distance < 13000) {
        distance = VecMagnitude(&delta, 0);
      }

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 3) {
        if (!(props->m_0x10 == 1 &&
              (moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0)) {
          props->m_0x08 = 0;
          props->m_0x00 = 200;
          if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
            props->m_0x00 = 350;
          }
          props->m_0x04 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
          moby->m_DamageFlags = 0;
          props->m_0x54 = RandRangeSigned(8, 0xE);
          moby->m_Substate = 0;
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c + 3);
          moby->m_State = 3;
          continue;
        }
      }

      if (props->m_0x38 == 0) {
        props->m_0x38 = 1;
        if (props->m_0x10 == 0) {
          props->m_0x0c = 4;
          if (moby->m_AnimationState.m_Animation != props->m_0x0c) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, props->m_0x0c);
          }
        }
      }

      if (moby->m_State < 3 &&
          (props->m_0x3c != 0 ||
           (moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) != 0)) {
        if (props->m_0x3c > 0 && moby->m_State == 0 &&
            (DISTANCE_TO_SPYRO(moby) < props->m_0x3c ||
             func_80038C4C(&g_Spyro.m_Position, &props->m_0x18) != 0) &&
            TICK_TIMER(props->m_0x4c)) {
          props->m_0x3c = -props->m_0x3c;
          if (props->m_0x3c == 0) {
            props->m_0x3c = -1;
          }
          g_LevelMobys[props->m_0x40].m_Substate = moby - g_LevelMobys;
          *(int *)g_LevelMobys[props->m_0x40].m_Props = props->m_0x44;
          props->m_0x4c = props->m_0x50;
        } else if ((moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) != 0) {
          moby->m_DamageFlags = 0;
          if ((props->m_0x34 & 4) != 0) {
            props->m_0x3c = -props->m_0x3c;
          } else {
            props->m_0x3c = 0;
          }
          if (props->m_0x10 == 0) {
            func_800385BC(moby, 0x28);
            moby->m_ScaleOverride = 0x40;
            props->m_0x0c = 0;
            if (moby->m_AnimationState.m_Animation != props->m_0x0c) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, props->m_0x0c);
            }
            moby->m_State = 10;
            continue;
          } else {
            moby->m_ScaleOverride = 0x20;
            moby->m_State = 20;
            continue;
          }
        } else if (props->m_0x3c < 0) {
          TICK_TIMER(props->m_0x4c);
        }
      }

      moby->m_DamageFlags = 0;
      if (props->m_0x34 == 1) {
        props->m_0x34 = 0;
        moby->m_State = 30;
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        if ((props->m_0x34 & 2) != 0 &&
            DISTANCE_TO_SPYRO(moby) < props->m_0x48) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c + 1);
          moby->m_State = 1;
          continue;
        }

        RotateMobyToSpyro(moby, 4, 0, 0);
        if (!TICK_TIMER(props->m_0x14)) {
          break;
        }
        if (SPYRO_BASE_Z_DISTANCE(moby) < 0x190) {
          if (props->m_0x10 == 0) {
            if (DISTANCE_TO_SPYRO(moby) < 1500) {
              moby->m_State = 2;
              continue;
            }
          } else if (props->m_0x10 == 1) {
            if (DISTANCE_TO_SPYRO(moby) < 8000) {
              moby->m_State = 2;
              continue;
            }
          }
        }
        break;
      }

      case 1: {
        props->m_0x34 &= ~2;
        if (DISTANCE_TO_SPYRO(moby) >= 0xC00) {
          if (func_80039E94(moby, props->m_0x30, 0x100, 0x8C, 0, 8, 0x28, 0xFF,
                            1) != 0x100) {
            break;
          }
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c);
        moby->m_State = 0;
        continue;
      }

      case 2: {
        if (props->m_0x10 == 0) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c + 2);
          RotateMobyToSpyro(moby, 6, 0, 0);
          g_Spyro.unk_0x208.x = FIXED_MUL(COSINE_8(moby->m_Rotation.z), 140);
          g_Spyro.unk_0x208.y = FIXED_MUL(SINE_8(moby->m_Rotation.z), 140);
          g_Spyro.unk_0x208.z = 0x46;
          if (g_AnimationFinished) {
            props->m_0x14 = 0x78;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c);
            moby->m_State = 0;
            continue;
          }
          break;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c + 2);
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_AnimationFinished || distance > 9000) {
          props->m_0x14 = 150;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c);
          moby->m_State = 0;
          continue;
        }
        if (distance < 2500 &&
            moby->m_AnimationState.m_Animation ==
                moby->m_AnimationState.m_NextAnimation &&
            moby->m_AnimationState.m_NextFrame < 0x12) {
          moby->m_AnimationState.m_Frame = 0x15;
          moby->m_AnimationState.m_NextFrame = 0x16;
          moby->m_AnimationState.m_FrameProgress = 0;
        }
        if (moby->m_AnimationState.m_NextFrame == 0x15) {
          moby->m_AnimationState.m_Frame = 7;
          moby->m_AnimationState.m_NextFrame = 8;
          moby->m_AnimationState.m_FrameProgress = 0;
        }
        break;
      }

      case 3: {
        moby->m_Rotation.z += props->m_0x54;
        moby->m_Substate++;
        if (moby->m_Substate >= 3) {
          if (props->m_0x54 > 0) {
            props->m_0x54--;
            if (props->m_0x54 < 0) {
              props->m_0x54 = 0;
            }
          } else if (props->m_0x54 < 0) {
            props->m_0x54++;
            if (props->m_0x54 > 0) {
              props->m_0x54 = 0;
            }
          }
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }

        result = MoveMobyWithGravity(moby, &props->m_0x00, props->m_0x04,
                                     &props->m_0x08, 0xC, 0x10);
        if (props->m_0x10 == 0) {
          if (result == 3 && moby->m_AnimationState.m_NextFrame >= 11 &&
              moby->m_AnimationState.m_NextFrame <= 19) {
            g_AnimationFinished = 0;
            moby->m_AnimationState.m_FrameProgress = 0x20;
            moby->m_AnimationState.m_PerFrameProgress = 0x20;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 0x14;
            func_80037E98(moby);
          }
        } else {
          if (result == 3 && moby->m_AnimationState.m_NextFrame >= 11 &&
              moby->m_AnimationState.m_NextFrame <= 19) {
            g_AnimationFinished = 0;
            moby->m_AnimationState.m_FrameProgress = 0x20;
            moby->m_AnimationState.m_PerFrameProgress = 0x20;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 0x16;
            func_80037E98(moby);
          }
        }

        if (ABS2(moby->m_AnimationState.m_NextFrame -
                 moby->m_AnimationState.m_Frame) < 3) {
          moby->m_AnimationState.m_PerFrameProgress =
              g_Models[moby->m_Class]
                  ->m_Animations[moby->m_AnimationState.m_Animation]
                  ->m_ProgressPerTick;
        }
        break;
      }

      case 10: {
        TICK_TIMER(props->m_0x4c);
        moby->m_ScaleOverride -= g_DeltaTime * 2;
        if (moby->m_ScaleOverride < 0x21) {
          moby->m_ScaleOverride = 0x20;
          props->m_0x10 = !props->m_0x10;
          moby->m_State = 0;
          continue;
        }
        break;
      }

      case 20: {
        TICK_TIMER(props->m_0x4c);
        moby->m_ScaleOverride += g_DeltaTime * 2;
        if (moby->m_ScaleOverride >= 0x38) {
          moby->m_ScaleOverride = 0x20;
          func_800385BC(moby, 0x20);
          props->m_0x0c = 4;
          if (moby->m_AnimationState.m_Animation != props->m_0x0c) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, props->m_0x0c);
          }
          props->m_0x10 = !props->m_0x10;
          moby->m_State = 0;
          continue;
        }
        break;
      }

      case 30: {
        Moby *linkedMoby;

        linkedMoby = &g_LevelMobys[props->m_0x40];
        angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
        result = func_80038074(ANGLE_TO_SPYRO(linkedMoby->m_Position), 0x80);
        func_80038638(moby, &linkedMoby->m_Position, 1500, result, 4, 0x32, 0xE,
                      0x80, 0xFF, 0xFF, 0, 0, 0xD);
        if (linkedMoby->m_State != 10) {
          if (TICK_TIMER(props->m_0x14)) {
            RotateMobyToAngle(linkedMoby, angle, 4, 0, 0);
          }
        } else {
          props->m_0x14 = 0x3C;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#if defined(HAS_MOBY_100) || defined(HAS_MOBY_102)
#ifdef HAS_MOBY_100
    case 100:
#endif
#ifdef HAS_MOBY_102
    case 102:
#endif
    {
      Moby100Props *props = moby->m_Props;

      if (moby->m_Class == 102) {
        ApplyFlameHeat(moby);
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE |
                                  MOBY_DAMAGE_FROM_MOBY | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 3) {
        if (moby->m_Class != 102 || moby->m_DamageFlags != MOBY_DAMAGE_FLAME) {
          Moby *child;

          if ((moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) != 0) {
            props->m_0x34 = 0;
            props->m_0x3c = 0x28;
          } else {
            if (moby->m_DamageFlags == MOBY_DAMAGE_CHARGE) {
              props->m_0x34 = 350;
            } else {
              props->m_0x34 = 0x118;
            }
            props->m_0x30 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                          g_Spyro.m_bodyRotation.z, 0x20, 0x40);
            if (moby->m_State != 43) {
              props->m_0x3c = 0x1E;
            }
          }

          moby->m_DamageFlags = 0;

          child = props->m_0x40;
          if (child != nullptr) {
            Moby57Props *projectileProps;

            if (child->m_Substate == 0) {
              child->m_Substate = 2;
              projectileProps = (Moby57Props *)child->m_Props;
              props->m_0x40 = nullptr;
              projectileProps->m_0x0f = props->m_0x30;
            }
          }

          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
      }

      moby->m_DamageFlags = 0;

      if (props->m_0x7c != 0) {
        if (props->m_0x7c == 1) {
          props->m_0x7c = 0;
          moby->m_State = 40;
          continue;
        }

        if (moby->m_Pod != 0 && moby->m_Substate == 0) {
          continue;
        }

        moby->m_Substate++;
        props->m_0x24->m_Reversed = -1;

        while (func_80017908(
                   moby->m_Rotation.z,
                   ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x24))) >=
               ROTDEG8(90)) {
          props->m_0x24->m_CurrentNode++;
        }

        props->m_0x7c = 0;
        moby->m_State = 50;
        continue;
      }

      if (props->m_0x28 == 2) {
        if (props->m_0x24->m_CurrentNode != 0 &&
            func_80038C4C(&g_Spyro.m_Position, &props->m_0x4c) != 0) {
          props->m_0x24->m_CurrentNode = 0;
          VecCopy(&moby->m_Position, &PATH_NODE_POS(props->m_0x24, 0));
          func_80038458(moby);
        } else if (props->m_0x24->m_CurrentNode != 1 &&
                   func_80038C4C(&g_Spyro.m_Position, &props->m_0x64) != 0) {
          props->m_0x24->m_CurrentNode = 1;
          VecCopy(&moby->m_Position, &PATH_NODE_POS(props->m_0x24, 1));
          func_80038458(moby);
        }
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0: {
        if (moby->m_Substate != 0) {
          moby->m_State = moby->m_Substate;
          MOBY_ANIM_CHANGE(moby, moby->m_Substate);
          continue;
        }

        if (props->m_0x10 != 0) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      }

      case 1: {
        if (g_AnimationFinished) {
          if (props->m_0x08 != 0) {
            func_8003B728(moby, 1);
            func_8002B390(props->m_0x0c, 0xFC, 0);
          }

          if ((props->m_0x28 & 1) != 0) {
            moby->m_State = 5;
            MOBY_ANIM_CHANGE(moby, 5);
            continue;
          }

          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
          continue;
        }
        break;
      }

      case 2: {
        RotateMobyToSpyro(moby, 4, 0, 0);

        if (((props->m_0x28 & 1) != 0 && SPYRO_BASE_Z_DISTANCE(moby) < 500 &&
             DISTANCE_TO_SPYRO(moby) < props->m_0x48) ||
            (props->m_0x58 != 0 &&
             func_80038C4C(&g_Spyro.m_Position, &props->m_0x4c) != 0)) {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }

        if (!TICK_TIMER(props->m_0x2c)) {
          break;
        }

        if (DISTANCE_TO_SPYRO(moby) >= props->m_0x44) {
          break;
        }

        if (SPYRO_BASE_Z_DISTANCE(moby) < 500) {
          if (func_80038250(&moby->m_Position) != 0) {
            moby->m_State = 4;
            MOBY_ANIM_CHANGE(moby, 4);
            continue;
          }
        }
        break;
      }

      case 3: {
        int result;

        result = MoveMobyWithGravity(moby, &props->m_0x34, props->m_0x30,
                                     &props->m_0x3c, 0xC, 0xA);

        if (result == 3 && props->m_0x34 == 0 && props->m_0x94 == 0) {
          func_8003851C(moby, 0, 0);
          props->m_0x94 = 1;
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }

      case 4: {
        Moby57Props *projectileProps;
        int angle;

        RotateMobyToSpyro(moby, 8, 0, 0);

        if (moby->m_AnimationState.m_NextFrame > 2 &&
            moby->m_AnimationState.m_NextFrame < 8) {
          if (props->m_0x40 == nullptr) {
            props->m_0x40 = g_SpawnMoby(57, moby);
            props->m_0x40->m_Substate = 0;
          }
        }

        if (props->m_0x40 != nullptr && props->m_0x40->m_Substate == 0) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 0, &props->m_0x40->m_Position);
          angle = ANGLE_TO_SPYRO(props->m_0x40->m_Position);
          props->m_0x40->m_Rotation.z = angle;

          if (moby->m_AnimationState.m_NextFrame >= 0x10) {
            projectileProps = (Moby57Props *)props->m_0x40->m_Props;
            projectileProps->m_0x0a = 0;
            projectileProps->m_0x00 =
                FIXED_MUL(COSINE_8(props->m_0x40->m_Rotation.z), 300);
            projectileProps->m_0x02 =
                FIXED_MUL(SINE_8(props->m_0x40->m_Rotation.z), 300);
            projectileProps->m_0x04 = 0;
            props->m_0x40->m_Substate = 1;
            props->m_0x40 = nullptr;
            projectileProps->m_0x0c = RandRangeSigned(7, 0xF);
            projectileProps->m_0x0d = RandRangeSigned(7, 0xF);
            projectileProps->m_0x0e = RandRangeSigned(7, 0xF);
          }
        }

        if (g_AnimationFinished) {
          props->m_0x2c = 0x78;
          if (moby->m_Class == 102) {
            props->m_0x2c = 0x50;
          }

          props->m_0x40 = nullptr;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      }

      case 5: {
        int result;

        props->m_0x28 &= ~1;

        if (DISTANCE_TO_SPYRO(moby) < 0x1400) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        result = func_80039E94(moby, props->m_0x24, 0x100, 0x8C, 0, 8, 0x28,
                               0xFF, 5);
        if (result == 0x100) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      }

      case 40: {
        Moby *linkedMoby;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);

        if (moby->m_Substate == 0) {
          break;
        }

        linkedMoby = &g_LevelMobys[props->m_0x00];
        props->m_0x80 = OctDistance(&moby->m_Position, &linkedMoby->m_Position);
        moby->m_State = 41;
        continue;
      }

      case 41: {
        int result;
        int rotation;

        rotation = g_LevelMobys[props->m_0x00].m_Rotation.z;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);

        result = func_80038638(moby, &g_LevelMobys[props->m_0x00].m_Position,
                               props->m_0x80, rotation, 4, 100, 0xE, 0x80, 0xFF,
                               0xFF, 0, 0, 0);
        if (result < 6) {
          g_LevelMobys[props->m_0x00].m_Substate = 1;
          moby->m_Substate = 0;
          moby->m_State = 42;
          continue;
        }
        break;
      }

      case 42: {
        int distance;
        int angle;
        int rotation;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (moby->m_Substate != 0) {
          distance = DISTANCE_TO_SPYRO(moby);

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);

          props->m_0x30 = ANGLE_TO_SPYRO(moby->m_Position);
          props->m_0x34 = 350;
          props->m_0x3c = distance >> 7;

          if (distance < 0x1800) {
            props->m_0x3c = 0;
          } else if (distance < 0x2800 && SPYRO_BASE_Z_DISTANCE(moby) > 1000) {
            props->m_0x3c = 0;
          }

          if (props->m_0x3c > 110) {
            props->m_0x3c = 110;
          }

          props->m_0x84 = RandRangeSigned(8, 0xF);
          props->m_0x88 = RandRangeSigned(8, 0xF);
          props->m_0x2c = 0xF0;
          moby->m_State = 43;
          continue;
        }

        if (g_LevelMobys[props->m_0x00].m_Substate == 0) {
          break;
        }

        rotation = g_LevelMobys[props->m_0x00].m_Rotation.z;
        angle = ANGLE_FROM(g_LevelMobys[props->m_0x00].m_Position,
                           moby->m_Position);
        if (func_80017908(rotation, angle) < 0xD) {
          break;
        }

        g_LevelMobys[props->m_0x00].m_Substate = 0;
        moby->m_State = 41;
        continue;
      }

      case 43: {
        Vector3D oldPosition;
        Moby **scan;
        Moby *other;
        int result;
        int distance;
        int angle;

        VecCopy(&oldPosition, &moby->m_Position);
        result = MoveMobyWithGravity(moby, &props->m_0x34, props->m_0x30,
                                     &props->m_0x3c, 0, 0x12);

        if (result == 3) {
          props->m_0x3c = 0x50;
        }

        moby->m_UpdateDistance = 0xFF;
        moby->m_CollisionRange = 0xFF;

        RotateMobyToAngle(moby, props->m_0x30, 6, 0, 0);

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);

        distance = DISTANCE_TO_SPYRO(moby);
        if (distance < 700 && SPYRO_BASE_Z_DISTANCE(moby) < 700) {
          if (g_Spyro.m_State != 0xB && g_Spyro.m_State != 0x14) {
            angle = func_80038098(ANGLE_TO_SPYRO(moby->m_Position),
                                  props->m_0x30, 0x20);
            g_Spyro.m_DamageFlags |= 0x86;
            g_Spyro.unk_0x208.x = FIXED_MUL(Cos(angle << 4), 110);
            g_Spyro.unk_0x208.y = FIXED_MUL(Sin(angle << 4), 110);
            g_Spyro.unk_0x208.z = 40;
            props->m_0x30 = ANGLE_FROM_SPYRO(moby->m_Position);
            props->m_0x34 = 0xDC;
            props->m_0x3c = 0x3C;
            func_8003ABC0(moby, 4, 0, 0);
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
            continue;
          }
        }

        if (TICK_TIMER(props->m_0x2c) || result == 2 ||
            DISTANCE_TO_SPYRO(moby) > 38000) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_8003ABC0(moby, 4, 0, 0);
          func_8003B7C0(moby);
          func_80052568(moby);
          continue;
        }

        scan = (Moby **)(g_SonyImage.u.m_Buf + 0x400);
        while ((other = *scan++) != nullptr) {
          if (other->m_Class == 65 &&
              ABS2(moby->m_Position.x - other->m_Position.x) < 3000 &&
              ABS2(moby->m_Position.y - other->m_Position.y) < 3000 &&
              OctDistance(&moby->m_Position, &other->m_Position) < 900 &&
              func_80017908(props->m_0x30,
                            ANGLE_FROM(moby->m_Position, other->m_Position)) <
                  0x28) {
            other->m_DamageFlags |= (MOBY_DAMAGE_FROM_MOBY | MOBY_DAMAGE_SUPER);
          }
        }
        break;
      }
      case 50: {
        if (props->m_0x14 != 0) {
          moby->m_RenderRadius = 0x28;
          moby->m_State++;
        }
        break;
      }
      case 51: {
        int result;

        result = func_80039E94(moby, props->m_0x24, 0x100, 0x78, 0, 8, 0x80,
                               0xFF, 5);

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);

        if (result == 0x100) {
          moby->m_State++;
        }
        break;
      }
      case 52: {
        Moby *linkedMoby;
        int angle;

        linkedMoby = &g_LevelMobys[props->m_0x04];

        if (linkedMoby->m_Substate != 0) {
          props->m_0x30 = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
          props->m_0x34 = 0x5A;
          props->m_0x3c = 0x78;
          linkedMoby->m_Substate = 2;
          moby->m_State++;
          break;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);

        angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
        RotateMobyToAngle(moby, angle, 6, 0, 0);
        break;
      }
      case 53: {
        Moby *linkedMoby;
        Vector3D midpoint;
        Vector3D pointA;
        Vector3D pointB;

        linkedMoby = &g_LevelMobys[props->m_0x04];
        RotateMobyToAngle(moby, props->m_0x30, 6, 0, 0);

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 6);

        func_800529E4(linkedMoby, 4);
        func_80052D64(linkedMoby, 0, &pointA);
        func_80052D64(linkedMoby, 1, &pointB);
        VecAdd(&midpoint, &pointA, &pointB);
        VecShiftRight(&midpoint, 1);
        MoveMobyWithGravity(moby, &props->m_0x34, props->m_0x30, &props->m_0x3c,
                            0, 0x10);

        if (moby->m_Position.z < midpoint.z) {
          VecCopy(&moby->m_Position, &midpoint);
          moby->m_State++;
        }
        break;
      }
      case 54: {
        Moby *linkedMoby;
        Vector3D midpoint;
        Vector3D pointA;
        Vector3D pointB;

        linkedMoby = &g_LevelMobys[props->m_0x04];
        RotateMobyToAngle(moby, props->m_0x30, 6, 0, 0);
        func_800529E4(linkedMoby, 4);
        func_80052D64(linkedMoby, 0, &pointA);
        func_80052D64(linkedMoby, 1, &pointB);
        VecAdd(&midpoint, &pointA, &pointB);
        VecShiftRight(&midpoint, 1);
        VecCopy(&moby->m_Position, &midpoint);

        if (linkedMoby->m_AnimationState.m_NextFrame >= 0xE) {
          if (props->m_0x00 != -1) {
            // This addresses classes 101, 102, 170
            // Determine common struct
            ((int *)g_LevelMobys[props->m_0x00].m_Props)[5] = 1;
          }

          *props->m_0x8c = 0;
          props->m_0x30 = ANGLE_TO_SPYRO(moby->m_Position);
          props->m_0x34 = 450;
          props->m_0x2c = 0xB4;
          props->m_0x3c = 0;
          moby->m_State = 43;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#if defined(HAS_MOBY_101) || defined(HAS_MOBY_170)
#ifdef HAS_MOBY_101
    case 101:
#endif
#ifdef HAS_MOBY_170
    case 170:
#endif
    {
      Moby101Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_FROM_MOBY |
                                  MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 5) {
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) != 0) {
          props->m_0x30 = 0;
          props->m_0x34 = 0x28;
        } else {
          props->m_0x30 = 0xF0;
          props->m_0x2c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        }
        if (moby->m_State != 43) {
          props->m_0x34 = 0x1E;
        }
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 5;
        MOBY_ANIM_CHANGE(moby, 5);
        continue;
      }

      if (props->m_0x6c != 0) {
        if (props->m_0x6c == 1) {
          props->m_0x6c = 0;
          moby->m_State = 40;
          continue;
        }

        if (moby->m_Pod != 0 && moby->m_Substate == 0) {
          continue;
        }

        moby->m_Substate++;
        props->m_0x38->m_Reversed = -1;

        while (func_80017908(moby->m_Rotation.z,
                             ANGLE_FROM(moby->m_Position,
                                        PATH_CUR_POS(props->m_0x38))) >= 0x40) {
          props->m_0x38->m_CurrentNode++;
        }

        props->m_0x6c = 0;
        moby->m_State = 50;
        continue;
      }

      if (props->m_0x18 == 2) {
        if (props->m_0x38->m_CurrentNode != 0 &&
            func_80038C4C(&g_Spyro.m_Position, &props->m_0x3c) != 0) {
          props->m_0x38->m_CurrentNode = 0;
          VecCopy(&moby->m_Position, &PATH_NODE_POS(props->m_0x38, 0));
          func_80038458(moby);
        } else if (props->m_0x38->m_CurrentNode != 1 &&
                   func_80038C4C(&g_Spyro.m_Position, &props->m_0x54) != 0) {
          props->m_0x38->m_CurrentNode = 1;
          VecCopy(&moby->m_Position, &PATH_NODE_POS(props->m_0x38, 1));
          func_80038458(moby);
        }
      }

      switch (moby->m_State) {
      case 0: {
        if (moby->m_Substate != 0 || props->m_0x10 != 0) {
          if (moby->m_Class == 170) {
            moby->m_State = 2;
            MOBY_ANIM_RESTART(moby, 2);
          } else {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
          }
          continue;
        }
        break;
      }

      case 1: {
        if (g_AnimationFinished) {
          if (props->m_0x08 != 0) {
            func_8003B728(moby, 2);
            func_8002B390(props->m_0x0c, 0xFC, 0);
          }
          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
          continue;
        }
        break;
      }

      case 2: {
        RotateMobyToSpyro(moby, 4, 0, 0);

        if (DISTANCE_TO_SPYRO(moby) < 0x1C00) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;
      }

      case 3: {
        int distance;
        int height;

        distance = DISTANCE_TO_SPYRO(moby);
        height = SPYRO_BASE_Z_DELTA(moby);
        RotateMobyToSpyro(moby, 4, 0, 0);

        if (distance > 0x2400) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        if (TICK_TIMER(props->m_0x1c) && distance < 3400 && height > -1400 &&
            height < -200) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;
      }

      case 4: {
        int distance;
        int maxDistance;

        distance = DISTANCE_TO_SPYRO(moby);
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (moby->m_AnimationState.m_NextFrame > 5 &&
            moby->m_AnimationState.m_NextFrame < 10) {
          maxDistance = (moby->m_AnimationState.m_NextFrame - 5) * 1000;
          if (maxDistance < 1000) {
            maxDistance = 1000;
          }
          if (maxDistance > 3500) {
            maxDistance = 3500;
          }
          if (distance < maxDistance) {
            if (SPYRO_BASE_Z_DELTA(moby) < -200) {
              g_Spyro.m_DamageFlags |= 0x86;
              g_Spyro.unk_0x208.x =
                  FIXED_MUL(Cos(moby->m_Rotation.z << 4), 140);
              g_Spyro.unk_0x208.y =
                  FIXED_MUL(Sin(moby->m_Rotation.z << 4), 140);
              g_Spyro.unk_0x208.z = 70;
            }
          }
        }

        if (g_AnimationFinished) {
          props->m_0x1c = 0x78;
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;
      }

      case 5: {
        MoveMobyWithGravity(moby, &props->m_0x30, props->m_0x2c, &props->m_0x34,
                            0xE, 0xA);

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x34);
          func_80052568(moby);
          continue;
        }
        break;
      }

      case 40: {
        int distance;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);

        RotateMobyToSpyro(moby, 4, 0, 0);

        if (props->m_0x70 < props->m_0x84) {
          distance = DISTANCE_TO_SPYRO(moby);

          if (distance < ((props->m_0x74[0] + 6) << 10) && moby->m_WasDrawn) {
            if (props->m_0x90 == -1 ||
                func_80017908(props->m_0x90, ANGLE_TO_SPYRO(moby->m_Position)) <
                    0x1C) {
              g_LevelMobys[props->m_0x7c[props->m_0x70]].m_Substate = 1;
              moby->m_State++;
              break;
            }
          }
        }

        if (props->m_0x70 >= props->m_0x84) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        break;
      }

      case 41: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);

        RotateMobyToSpyro(moby, 4, 0, 0);

        if (moby->m_Substate) {
          if (DISTANCE_TO_SPYRO(moby) < (props->m_0x74[props->m_0x70] << 10) &&
              func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) < 0x30 &&
              moby->m_WasDrawn && func_80038250(&moby->m_Position)) {

            moby->m_Substate = 0;
            moby->m_State++;
          }
        }

        break;
      }

      case 42: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (moby->m_AnimationState.m_NextFrame >= 6 &&
            (props->m_0x7c[props->m_0x70] != -1)) {
          g_LevelMobys[props->m_0x7c[props->m_0x70]].m_Substate = 1;
          props->m_0x7c[props->m_0x70] = -1;
          props->m_0x70++;

          if (props->m_0x70 < props->m_0x84) {
            g_LevelMobys[props->m_0x7c[props->m_0x70]].m_Substate = 1;
          }

          moby->m_State = 44;
          continue;
        }
        break;
      }

      case 43: {
        Vector3D oldPosition;
        Moby **scan;
        Moby *other;
        int result;
        int distance;
        int angle;

        VecCopy(&oldPosition, &moby->m_Position);
        result = MoveMobyWithGravity(moby, &props->m_0x30, props->m_0x2c,
                                     &props->m_0x34, 0, 0x12);

        moby->m_UpdateDistance = 0xFF;

        if (result == 3) {
          props->m_0x34 = 0x5A;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);

        moby->m_CollisionRange = 0xFF;
        RotateMobyToAngle(moby, props->m_0x2c, 6, 0, 0);

        distance = DISTANCE_TO_SPYRO(moby);
        if (distance < 1000 && SPYRO_BASE_Z_DISTANCE(moby) < 800) {
          angle = func_80038098(ANGLE_TO_SPYRO(moby->m_Position), props->m_0x2c,
                                0x20);
          g_Spyro.m_DamageFlags |= 0x86;
          g_Spyro.unk_0x208.x = FIXED_MUL(Cos(angle << 4), 110);
          g_Spyro.unk_0x208.y = FIXED_MUL(Sin(angle << 4), 110);
          g_Spyro.unk_0x208.z = 40;
          props->m_0x2c = ANGLE_FROM_SPYRO(moby->m_Position);
          props->m_0x30 = 0xF0;
          props->m_0x34 = 0x3C;
          func_8003ABC0(moby, 4, 0, 0);
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }

        if (TICK_TIMER(props->m_0x1c) || result == 2 ||
            DISTANCE_TO_SPYRO(moby) > 38000) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x34);
          func_8003ABC0(moby, 4, 0, 0);
          func_8003B7C0(moby);
          func_80052568(moby);
          continue;
        }

        scan = (Moby **)(g_SonyImage.u.m_Buf + 0x400);
        while ((other = *scan++) != nullptr) {
          if (other->m_Class == 65 &&
              ABS2(moby->m_Position.x - other->m_Position.x) < 3000 &&
              ABS2(moby->m_Position.y - other->m_Position.y) < 3000 &&
              OctDistance(&moby->m_Position, &other->m_Position) < 1200 &&
              func_80017908(props->m_0x2c,
                            ANGLE_FROM(moby->m_Position, other->m_Position)) <
                  0x28) {
            other->m_DamageFlags |= (MOBY_DAMAGE_FROM_MOBY | MOBY_DAMAGE_SUPER);
          }
        }
        break;
      }

      case 44: {
        if (g_AnimationFinished) {
          if (props->m_0x70 < props->m_0x84) {
            moby->m_State = 41;
            continue;
          }

          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      }

      case 50: {
        if (props->m_0x14 != 0) {
          moby->m_RenderRadius = 0x28;
          moby->m_State++;
        }
        break;
      }

      case 51: {
        int result;

        result = func_80039E94(moby, props->m_0x38, 0x100, 0x78, 0, 8, 0x80,
                               0xFF, 5);

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 6);

        if (result == 0x100) {
          moby->m_State++;
        }
        break;
      }

      case 52: {
        Moby *linkedMoby;
        int angle;

        linkedMoby = &g_LevelMobys[props->m_0x04];

        if (linkedMoby->m_Substate != 0) {
          props->m_0x2c = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
          props->m_0x30 = 0x5A;
          props->m_0x34 = 0x78;
          linkedMoby->m_Substate = 2;
          moby->m_State++;
          break;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);

        angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
        RotateMobyToAngle(moby, angle, 6, 0, 0);
        break;
      }

      case 53: {
        Moby *linkedMoby;
        Vector3D midpoint;
        Vector3D pointA;
        Vector3D pointB;

        linkedMoby = &g_LevelMobys[props->m_0x04];
        RotateMobyToAngle(moby, props->m_0x2c, 6, 0, 0);

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);

        func_800529E4(linkedMoby, 4);
        func_80052D64(linkedMoby, 0, &pointA);
        func_80052D64(linkedMoby, 1, &pointB);
        VecAdd(&midpoint, &pointA, &pointB);
        VecShiftRight(&midpoint, 1);
        MoveMobyWithGravity(moby, &props->m_0x30, props->m_0x2c, &props->m_0x34,
                            0, 0x10);

        if (moby->m_Position.z < midpoint.z) {
          VecCopy(&moby->m_Position, &midpoint);
          moby->m_State++;
        }
        break;
      }

      case 54: {
        Moby *linkedMoby;
        Vector3D midpoint;
        Vector3D pointA;
        Vector3D pointB;

        linkedMoby = &g_LevelMobys[props->m_0x04];
        RotateMobyToAngle(moby, props->m_0x2c, 6, 0, 0);
        func_800529E4(linkedMoby, 4);
        func_80052D64(linkedMoby, 0, &pointA);
        func_80052D64(linkedMoby, 1, &pointB);
        VecAdd(&midpoint, &pointA, &pointB);
        VecShiftRight(&midpoint, 1);
        VecCopy(&moby->m_Position, &midpoint);

        if (linkedMoby->m_AnimationState.m_NextFrame >= 0xE) {
          if (props->m_0x00 != -1) {
            // This addresses classes 100, 101, 102, 170
            // Determine common struct
            ((int *)g_LevelMobys[props->m_0x00].m_Props)[5] = 1;
          }

          *props->m_0x88 = 0;
          props->m_0x2c = ANGLE_TO_SPYRO(moby->m_Position);
          props->m_0x30 = 500;
          props->m_0x1c = 0xB4;
          props->m_0x34 = 0;
          moby->m_State = 43;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_65
    case 65: {
      Moby65Props *props = moby->m_Props;
      int childCount = 4;
      int i;

      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0 &&
          moby->m_State < 2) {
        func_8003851C(moby, 0, 0);
        moby->m_Position.z -= 0x190;
        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(93, moby);
        }
        (*props->m_0x10)--;
        for (i = 0; i < childCount; i++) {
          if (props->m_0x24[i] != 0) {
            func_80052568(props->m_0x24[i]);
          }
        }
        func_80052568(moby);
        continue;
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FROM_MOBY | MOBY_DAMAGE_SUPER)) ==
          (MOBY_DAMAGE_FROM_MOBY | MOBY_DAMAGE_SUPER)) {
        func_8003851C(moby, 0, 0);
        moby->m_Position.z -= 0x190;
        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(93, moby);
        }
        (*props->m_0x10)--;
        for (i = 0; i < childCount; i++) {
          if (props->m_0x24[i] != 0) {
            func_80052568(props->m_0x24[i]);
          }
        }
        func_80052568(moby);
        continue;
      }

      moby->m_DamageFlags = 0;

      if (props->m_0x18 == 0) {
        props->m_0x18 = 1;
        *props->m_0x10 = props->m_0x14;
        props->m_0x00 *= 60;
      }

      switch (moby->m_State) {
      case 0: {
        if (TICK_TIMER(props->m_0x00)) {
          props->m_0x00 = 0x46;
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          continue;
        }
        break;
      }

      case 1: {
        if (TICK_TIMER(props->m_0x00) && g_AnimationFinished) {
          props->m_0x00 = props->m_0x04;
          for (i = 0; i < childCount; i++) {
            Moby210Props *childProps;
            props->m_0x24[i] = g_SpawnMoby(210, moby);
            props->m_0x24[i]->m_RenderRadius = 0;
            childProps = props->m_0x24[i]->m_Props;
            VecCopy(&props->m_0x24[i]->m_Position, &moby->m_Position);
            childProps->m_0x08 = 0x3B6;
            childProps->m_0x04 = 1;
            childProps->m_0x00 = i * (0x3B6 / childCount);
            childProps->m_0x0c = props->m_0x24[i]->m_Position.z - 0x2EE;
            props->m_0x24[i]->m_Position.z += childProps->m_0x00;
            props->m_0x24[i]->m_Rotation.z = i * 0x3C;
            props->m_0x24[i]->m_DepthOffset = 6;
            props->m_0x24[i]->m_Substate = RandRangeSigned(0xA, 0x12);
          }
          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
          continue;
        }
        break;
      }

      case 2: {
        if (*(int *)g_LevelMobys[props->m_0x1c].m_Props == moby->m_Pod - 2) {
          if (TICK_TIMER(props->m_0x20)) {
            Moby *projectile;
            Moby82Props *projectileProps;
            Vector3D targetPosition;
            int travelTime;

            projectile = g_SpawnMoby(82, moby);
            projectileProps = projectile->m_Props;
            props->m_0x20 = RandRange(0xC, 0x28);
            if (projectile->m_AnimationState.m_Animation != 1) {
              MOBY_ANIM_RESTART(projectile, 1);
            }
            projectile->m_ScaleOverride = 0x36;
            projectile->m_Position.z += 500;
            VecCopy(&targetPosition, &g_LevelMobys[props->m_0x1c].m_Position);
            targetPosition.z += 2200;
            VecSub(&projectileProps->m_0x00, &targetPosition,
                   &projectile->m_Position);
            travelTime = OctDistance(&moby->m_Position, &targetPosition) / 300;
            projectileProps->m_0x00.x /= travelTime;
            projectileProps->m_0x00.y /= travelTime;
            projectileProps->m_0x00.z /= travelTime;
            projectile->m_RenderRadius = 0x28;
            projectile->m_Rotation.z =
                ANGLE_FROM(projectile->m_Position, targetPosition);
            projectile->m_Rotation.y =
                Atan2(OctDistance(&projectile->m_Position, &targetPosition),
                      targetPosition.z - projectile->m_Position.z, 0);
            projectileProps->m_0x0c = travelTime * 2;
            projectileProps->m_0x0e = 0xFF;
            projectileProps->m_0x0f = 1;
            VecAdd(&projectile->m_Position, &projectile->m_Position,
                   &projectileProps->m_0x00);
            VecAdd(&projectile->m_Position, &projectile->m_Position,
                   &projectileProps->m_0x00);
          }
        }

        if (TICK_TIMER(props->m_0x00)) {
          props->m_0x00 = *props->m_0x10 * 60;
          for (i = 0; i < childCount; i++) {
            func_80052568(props->m_0x24[i]);
            props->m_0x24[i] = 0;
          }
          func_800562A4(moby, 1);
          func_8003851C(moby, 1, 0);
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_104 // Dream Weavers Cannon Invisible Projectile?
    case 104: {
      Moby104Props *props;
      Moby *spawned;
      int activePoints;
      int tracerPointIndex;
      int state;
      int i;

      props = moby->m_Props;
      state = moby->m_State;

      // TODO: if conditions seem unnatural, investigate switch
      if (state < 3) {
        if (state >= 0) {
          if (state == 0) {
            props->m_0x0c += g_DeltaTime;
            if (props->m_0x0c >= 0xC) {
              spawned = g_SpawnMoby(77, moby);
              VecCopy(&spawned->m_Position, &moby->m_Position);
              spawned->m_Substate = 7;
              spawned->m_Rotation.y = Atan2(props->m_0x08, props->m_0x0a, 0);
              spawned->m_Rotation.z = moby->m_Rotation.z;
              spawned->m_RenderRadius = 0x50;
              props->m_0x0c = 0;
            }

            do {
              moby->m_Position.x +=
                  FIXED_MUL(props->m_0x08, COSINE_8(moby->m_Rotation.z));
              moby->m_Position.y +=
                  FIXED_MUL(props->m_0x08, SINE_8(moby->m_Rotation.z));
              moby->m_Position.z += props->m_0x0a;
              props->m_0x0a += props->m_0x0e;
              if (props->m_0x12 != 0) {
                props->m_0x12--;
              }
              if (props->m_0x02 != 0) {
                if (props->m_0x00 == 0) {
                  moby->m_State = 1;
                }
                props->m_0x00--;
              }
            } while (props->m_0x12 != 0);

            if (TICK_TIMER(props->m_0x10)) {
              moby->m_State = 1;
            }
            if (moby->m_Position.x < 0 || moby->m_Position.y < 0 ||
                moby->m_Position.z < 0) {
              moby->m_RenderRadius = 0;
              moby->m_WasDrawn = 0;
              moby->m_State = 1;
              continue;
            }
            func_8004E3C8(&moby->m_Position, 600, 0, 0x40000, moby, 2);
            if (func_8004BE4C(&moby->m_Position, 0x168, 0x168) != 0) {
              moby->m_State = 1;
            }
            if (moby->m_State == 1) {
              moby->m_RenderRadius = 0;
              moby->m_WasDrawn = 0;
            }
          }

          activePoints = 0;
          if (moby->m_State < 2 && g_TracerCount < 3 && props->m_0x13 < 0x78) {
            tracerPointIndex = props->m_0x13;
            VecCopy(&props->m_0x04[tracerPointIndex].WorldPos,
                    &moby->m_Position);
            props->m_0x04[tracerPointIndex].Age = 0;
            props->m_0x13++;
          }

          for (i = 0; i < props->m_0x13; i++) {
            props->m_0x04[i].Age += g_DeltaTime;
            if (props->m_0x04[i].Age < 0x51) {
              activePoints++;
            }
          }

          if (activePoints == 0 && moby->m_State != 0) {
            func_80052568(moby);
            continue;
          }

          if (g_TracerCount < 3) {
            g_TracerPointCount[g_TracerCount] = props->m_0x13;
            g_TracerLists[g_TracerCount] = props->m_0x04;
            g_TracerCount++;
          }

          if (moby->m_State == 1) {
            moby->m_State = 2;
          }
        }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_121
    case 121: {

      Moby121Props *props = (Moby121Props *)moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 2) {
        props->m_0x10 = func_80038098(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20);

        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          props->m_0x14 = 0xFA;
        } else {
          props->m_0x14 = 450;
        }

        props->m_0x18 = 0;

        if (moby->m_State != 0) {
          *props->m_0x30 = 0;
        }

        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 2;

        MOBY_ANIM_CHANGE(moby, 2);

        continue;
      }

      if (!TICK_TIMER(props->m_0x2c)) {
        int cameraDistance = DISTANCE_TO_SPYRO(moby) + 0x1000;

        if (props->m_0x24 < cameraDistance) {
          props->m_0x24 = cameraDistance;
        }

        g_Spyro.m_ControlFlags = 0x80000200;
        D_80078668.m_Coords.azimuth = -ANGLE_TO_SPYRO(moby->m_Position) << 4;
        D_80078668.m_Coords.radius = props->m_0x24;
      }

      switch (moby->m_State) {
      case 0: {
        RotateMobyToSpyro(moby, 0xA, 0, 0);

        if (*props->m_0x30 == 0 && SPYRO_BASE_Z_DISTANCE(moby) < 1500 &&
            DISTANCE_TO_SPYRO(moby) < 0x2800) {
          *props->m_0x30 = 1;
          props->m_0x0c = 0;
          moby->m_State = 1;
          continue;
        }

        break;
      }

      case 1: {
        int angle;
        int targetAngle;

        if (!TICK_TIMER(props->m_0x0c)) {
          break;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

        if (TICK_TIMER(props->m_0x1c)) {
          props->m_0x10 = g_Spyro.m_bodyRotation.z;
          props->m_0x1c = 0x1E;
        }

        angle = ANGLE_FROM_SPYRO(moby->m_Position);
        props->m_0x18 = (angle - props->m_0x10 + 0x100) % 0x100;
        targetAngle =
            func_80038074(ANGLE_TO_SPYRO(moby->m_Position), props->m_0x18);

        if (RotateMobyToAngle(moby, targetAngle, 4, 0x1E, 1) != 0) {
          if (func_80039398(moby, 100, 0, 300, 5) != 0) {
            *props->m_0x30 = 0;
            moby->m_State = 100;
            continue;
          }

          if (func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) >= 0x31 ||
              OctDistance(&moby->m_Position, &props->m_0x00) > 0x2800) {
            *props->m_0x30 = 0;
            moby->m_State = 100;
            continue;
          }

          if (DISTANCE_TO_SPYRO(moby) < 3800 &&
              func_80017908(moby->m_Rotation.z,
                            ANGLE_TO_SPYRO(moby->m_Position)) < 0x14) {
            props->m_0x14 = 100;
            props->m_0x20 = 0;
            moby->m_State = 3;

            MOBY_ANIM_CHANGE(moby, 3);

            continue;
          }
        }

        break;
      }

      case 2: {
        if (moby->m_AnimationState.m_Frame < 5) {
          moby->m_Rotation.z += props->m_0x18;
        }

        if (props->m_0x14 >= 0x10) {
          props->m_0x14 -= 0xF;
          func_80039688(moby, props->m_0x10, props->m_0x14, 0, 300, 5);
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }

        break;
      }

      case 3: {
        RotateMobyToSpyro(moby, 4, 0, 0);
        func_80039398(moby, props->m_0x14, 0, 300, 5);

        if (moby->m_AnimationState.m_Frame >= 5 && props->m_0x14 > 0x50) {
          props->m_0x14 -= 5;
        }

        if (DISTANCE_TO_SPYRO(moby) < 1500 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 900) {
          if (props->m_0x20 == 0 && g_Spyro.m_State != 0xB &&
              g_Spyro.m_State != 0x14) {
            props->m_0x20 = 1;
            g_Spyro.m_DamageFlags |= 0x80;
            g_Spyro.unk_0x208.x = FIXED_MUL(Cos(moby->m_Rotation.z << 4), 150);
            g_Spyro.unk_0x208.y = FIXED_MUL(Sin(moby->m_Rotation.z << 4), 150);
            g_Spyro.unk_0x208.z = 50;
          } else if (props->m_0x20 == 1) {
            props->m_0x20 = 2;
            props->m_0x2c = 0x32;
            g_Spyro.m_ControlFlags |= 0x80000200;
            g_Spyro.unk_0x21c = &moby->m_Position;
            g_Spyro.unk_0x220 = &D_80078668;
            D_80078668.m_Coords.azimuth = -ANGLE_TO_SPYRO(moby->m_Position)
                                          << 4;
            D_80078668.m_Coords.radius = DISTANCE_TO_SPYRO(moby) + 0xC00;
            D_80078668.m_Coords.elevation = 100;
            D_80078668.m_Offset.azimuth = 0;
            D_80078668.m_Offset.elevation = -200;
            D_80078668.m_Offset.radius = 0;
          }
        }

        if (g_AnimationFinished) {
          moby->m_State = 4;

          MOBY_ANIM_CHANGE(moby, 4);

          continue;
        }
      }

      case 4: {
        if (g_AnimFrameFinished != 0 && moby->m_AnimationState.m_Frame >= 6) {
          if (props->m_0x14 >= 0xD) {
            props->m_0x14 -= 0xC;
          } else {
            props->m_0x14 = 0;
          }
        }

        func_80039398(moby, props->m_0x14, 0, 300, 5);

        if (g_AnimationFinished) {
          moby->m_Rotation.z = func_80038074(moby->m_Rotation.z, 0x80);

          if (props->m_0x20 == 0) {
            moby->m_State = 1;

            MOBY_ANIM_CHANGE(moby, 1);
          } else {
            *props->m_0x30 = 0;

            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

            moby->m_State = 100;
          }

          continue;
        }

        break;
      }

      case 100: {
        int targetAngle = Atan2Fast(props->m_0x00.x - moby->m_Position.x,
                                    props->m_0x00.y - moby->m_Position.y);

        if (RotateMobyToAngle(moby, targetAngle, 4, 0x14, 1) != 0) {
          func_80039398(moby, 0x5A, 0, 0, 5);
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

        if (OctDistance(&moby->m_Position, &props->m_0x00) < 0x80) {
          moby->m_State = 0;

          MOBY_ANIM_CHANGE(moby, 0);

          continue;
        }

        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#if defined(HAS_MOBY_67) || defined(HAS_MOBY_68) || defined(HAS_MOBY_93) ||    \
    defined(HAS_MOBY_133) || defined(HAS_MOBY_215) || defined(HAS_MOBY_255) || \
    defined(HAS_MOBY_256) || defined(HAS_MOBY_423) || defined(HAS_MOBY_424) || \
    defined(HAS_MOBY_478) || defined(HAS_MOBY_479)
#ifdef HAS_MOBY_67
    case 67:
#endif
#ifdef HAS_MOBY_68
    case 68:
#endif
#ifdef HAS_MOBY_93
    case 93:
#endif
#ifdef HAS_MOBY_133
    case 133:
#endif
#ifdef HAS_MOBY_215
    case 215:
#endif
#ifdef HAS_MOBY_255
    case 255:
#endif
#ifdef HAS_MOBY_256
    case 256:
#endif
#ifdef HAS_MOBY_423
    case 423:
#endif
#ifdef HAS_MOBY_424
    case 424:
#endif
#ifdef HAS_MOBY_478
    case 478:
#endif
#ifdef HAS_MOBY_479
    case 479:
#endif
    {
      MobyFragmentProps *props = moby->m_Props;
      Vector3D particleVelocity;

      if (props->m_Lifetime > 0 && moby->m_WasDrawn) {
        if (func_8004BE4C(&moby->m_Position, 0x100, 0x100)) {
          int dot;
          func_80017330(&g_CollisionNormal, 0x1000);
          dot = (props->m_Velocity.x * g_CollisionNormal.x +
                 props->m_Velocity.y * g_CollisionNormal.y +
                 props->m_Velocity.z * g_CollisionNormal.z) >>
                11;
          if (dot < 0) {
            VecScaleToLength(&g_CollisionNormal, 0x1000, (dot >> 2) - (dot));
            props->m_Velocity.x += g_CollisionNormal.x;
            props->m_Velocity.y += g_CollisionNormal.y;
            props->m_Velocity.z += g_CollisionNormal.z;
          }
        }

        moby->m_Position.x += props->m_Velocity.x;
        moby->m_Position.y += props->m_Velocity.y;
        props->m_Velocity.z -= 6;
        if (props->m_Velocity.z < -128)
          props->m_Velocity.z = -128;
        moby->m_Position.z += props->m_Velocity.z;

        moby->m_Rotation.x += props->m_AngularVelocity.x;
        moby->m_Rotation.y += props->m_AngularVelocity.y;
        moby->m_Rotation.z += props->m_AngularVelocity.z;
        if (!(props->m_Lifetime & 3)) {

          particleVelocity.x = rand() & 3;
          particleVelocity.y = rand() & 3;
          particleVelocity.z = 20;
          g_SpawnParticle(1, 1, &moby->m_Position, (int)&particleVelocity);
        }
        props->m_Lifetime--;
      } else {
        g_SpawnParticle(8, 70, &moby->m_Position, 0x10);
        func_80052568(moby);
      }
      break;
    }
#endif
#if defined(HAS_MOBY_69) || defined(HAS_MOBY_151) || defined(HAS_MOBY_257) ||  \
    defined(HAS_MOBY_425) || defined(HAS_MOBY_480)
#ifdef HAS_MOBY_69
    case 69:
#endif
#ifdef HAS_MOBY_151
    case 151:
#endif
#ifdef HAS_MOBY_257
    case 257:
#endif
#ifdef HAS_MOBY_425
    case 425:
#endif
#ifdef HAS_MOBY_480
    case 480:
#endif
    {
      MobyFragmentProps *physicsProps = moby->m_Props;

      if (physicsProps->m_Lifetime != 0 && moby->m_WasDrawn &&
          moby->m_Position.z > physicsProps->m_MinZ) {
        // Apply velocity to position
        moby->m_Position.x += physicsProps->m_Velocity.x;
        moby->m_Position.y += physicsProps->m_Velocity.y;

        // Apply gravity to Z velocity
        physicsProps->m_Velocity.z -= 6;

        if (physicsProps->m_Velocity.z < -0x80) {
          physicsProps->m_Velocity.z = -0x80;
        }

        moby->m_Position.z += physicsProps->m_Velocity.z;

        // Apply angular velocity to rotation
        moby->m_Rotation.x += physicsProps->m_AngularVelocity.x;
        moby->m_Rotation.y += physicsProps->m_AngularVelocity.y;
        moby->m_Rotation.z += physicsProps->m_AngularVelocity.z;

        physicsProps->m_Lifetime--;
      } else {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_78
    case 78: {
      Moby78Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 1) {
        if (moby->m_DamageFlags & MOBY_DAMAGE_SUPER) {
          props->m_0x0c = 10;
        } else {
          props->m_0x0c = 0;
        }
        moby->m_State = 1;
      }

      func_80052D64(&g_LevelMobys[props->m_0x08], 0, &moby->m_Position);
      moby->m_Rotation = g_LevelMobys[props->m_0x08].m_Rotation;
      func_800529E4(moby, UPDATE_PROP_CHAIN);

      switch (moby->m_State) {
      case 0:
        break;
      case 1: {
        int i;
        Vector3D particleVelocity;
        Vector3D particlePosition;

        if (TICK_TIMER(props->m_0x0c)) {
          Moby *spawned;

          spawned = g_SpawnMoby(props->m_0x00 + 344, moby);
          if (spawned != 0) {
            spawned->m_State = 1;
          }

          RegisterFlightMobyCollectibleType(props->m_0x04);
          func_8004E3C8(&moby->m_Position, 0x1000, 0, 0x80000, moby, 2);

          for (i = 0; i < 3 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(359, moby);
            g_SpawnMoby(360, moby);
            g_SpawnMoby(361, moby);
          }

          for (i = 0; i < 8; i++) {
            particleVelocity.x = (rand() & 0x7E) - 0x3F;
            particleVelocity.y = (rand() & 0x7E) - 0x3F;
            particleVelocity.z = rand() & 0x1F;
            VecCopy(&particlePosition, &particleVelocity);
            VecShiftLeft(&particlePosition, 2);
            VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
            g_SpawnParticle(1, 13, &particlePosition, (int)&particleVelocity);
          }

          func_8003851C(moby, 0, 0);
          func_80052568(moby);
        }
        break;
      }
      }
      break;
    }
#endif
    case MOBYCLASS_LIFE_STATUE:
    case MOBYCLASS_LIFE_ORB:
    case MOBYCLASS_GEM_1:
    case MOBYCLASS_GEM_2:
    case MOBYCLASS_GEM_5:
    case MOBYCLASS_GEM_10:
    case MOBYCLASS_GEM_25: {
      MobyCollectableProps *collectableProps = moby->m_Props;

      int distanceToSpyro = DISTANCE_TO_SPYRO(moby);

      // Sparkle stuff
      if (collectableProps->m_Ticks < 250) {
        collectableProps->m_Ticks += g_DeltaTime;
      }

      if (moby->m_Class != 15) {

        if (collectableProps->m_SparkleHandle != 255) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);

          if (moby->m_Class == 14) {
            VecRotateByMatrix(
                (MATRIX *)&moby->m_RotationMatrix, &D_8006E5B8,
                &g_Sparkles[collectableProps->m_SparkleHandle].m_Position);
          } else {
            VecRotateByMatrix(
                (MATRIX *)&moby->m_RotationMatrix, &D_8006E5A0,
                &g_Sparkles[collectableProps->m_SparkleHandle].m_Position);
          }

          VecAdd(&g_Sparkles[collectableProps->m_SparkleHandle].m_Position,
                 &g_Sparkles[collectableProps->m_SparkleHandle].m_Position,
                 &moby->m_Position);

          if (g_Sparkles[collectableProps->m_SparkleHandle].m_Life < 5) {
            collectableProps->m_SparkleHandle = 255;
          }
        } else {
          if (collectableProps->m_Ticks > 0xf7) {
            int handle = SpawnMobySparkle(moby, &D_8006E5A0);
            if (handle >= 0 && distanceToSpyro < 0x4000) {
              collectableProps->m_SparkleHandle = handle;
            }

            collectableProps->m_Ticks = (rand() & 0x1F) + 33;
          }
        }
      }

      if (!moby->m_WasDrawn && distanceToSpyro > 0x2000 &&
          moby->m_Substate == 1 && collectableProps->m_SpawnState == 0) {
        break;
      }

      switch (moby->m_Substate) {
      case 0: {
        Vector3D vec;

        // Initialize
        VecCopy(&vec, &moby->m_Position);
        vec.z += 0x400;
        func_8004D5EC(&vec, 0x10000);
        collectableProps->m_RotY = -Atan2Fast(
            func_80017A38((g_CollisionNormal.x * g_CollisionNormal.x) +
                          (g_CollisionNormal.z * g_CollisionNormal.z)),
            g_CollisionNormal.y);
        collectableProps->m_RotZ =
            -Atan2Fast(g_CollisionNormal.z, g_CollisionNormal.x);

        // Smart compiler c:
        if (collectableProps->m_RotY != 0 || collectableProps->m_RotZ != 0) {
          moby->m_Rotation.z = 0;
        }

        moby->m_Substate = 1;
        break;
      }
      case 1: {
        Vector3D vec;
        Vector3D collectableCollVerts[3];

        if (collectableProps->m_SpawnState != 0) {

          if (collectableProps->m_SpawnState == 1) {
            func_80038458(moby); // Place on floor
            func_800533D0(moby); // Set shadow
            if (moby->m_Class >= 83) {
              collectableProps->m_RotY = -Atan2Fast(
                  func_80017A38((g_CollisionNormal.x * g_CollisionNormal.x) +
                                (g_CollisionNormal.z * g_CollisionNormal.z)),
                  g_CollisionNormal.y);
              collectableProps->m_RotZ =
                  -Atan2Fast(g_CollisionNormal.z, g_CollisionNormal.x);
            }
          } else if (collectableProps->m_SpawnState == 2) {

            // Get a collision polygon, unpack it
            ColTriUnpack(collectableProps->m_CollisionIndex,
                         collectableCollVerts);

            // Sum the entire thing together
            VecAdd(&collectableCollVerts[0], &collectableCollVerts[0],
                   &collectableCollVerts[1]);
            VecAdd(&collectableCollVerts[0], &collectableCollVerts[0],
                   &collectableCollVerts[2]);

            // Set the moby's position to the average of that collision
            // polygon
            moby->m_Position.x = collectableCollVerts[0].x / 3;
            moby->m_Position.y = collectableCollVerts[0].y / 3;
            moby->m_Position.z = collectableCollVerts[0].z / 3;

            func_800529E4(moby, UPDATE_PROP_CHAIN);
            func_80038458(moby); // Place on floor
            func_800533D0(moby); // Set shadow
          } else if (collectableProps->m_SpawnState == 3) {
            int colIndex;

            VecCopy(&vec, &moby->m_Position);
            vec.z += 0x400;

            func_800529E4(moby, UPDATE_PROP_CHAIN);

            // I think this should be >= 0, not > 0?
            if (func_8004D5EC(&vec, 0x1000) > 0) {
              colIndex = g_CollisionTriangleIndex;
              collectableProps->m_SpawnState = 2;
              collectableProps->m_CollisionIndex = colIndex;
            }
          }
        }

        if (distanceToSpyro < 1434) {
          int pickupHeight = moby->m_Position.z + 356;
          int zDist = g_Spyro.m_Position.z - pickupHeight;

          if (ABS2(zDist) < 512 && g_Sparx != nullptr &&
              g_Spyro.m_airTime == 0 &&
              // Check added after Tabloid/E3
              func_80033E40(&g_Sparx->m_Position, &moby->m_Position)) {
            MobySparxProps *sparxProps = g_Sparx->m_Props;

            if (sparxProps->m_Target == nullptr) {
              if (!IsMobyPlayingSound(
                      g_Sparx, g_Models[g_Sparx->m_Class]->m_Sounds[0])) {
                g_Spu.m_NextSoundOverrideFlags = 1;
                g_Spu.m_VolumeOverride.right = 0x2000;
                g_Spu.m_VolumeOverride.left = 0x2000;
                func_8003851C(g_Sparx, 0, 0);
              }

              g_Sparx->m_Substate = 4;
              sparxProps->m_Target = moby;
            }
          }
        }
        break;
      }
      case 2: {
        Vector3D collectableMovePos;
        Vector3D collectableSurfaceNormal;
        int speed;

        VecMult(&collectableMovePos, &collectableProps->m_InitPos, g_DeltaTime);
        VecShiftRight(&collectableMovePos, 1);

        speed = VecMagnitude(&collectableMovePos, 1);

        if (220 < speed) {
          VecScaleToLength(&collectableMovePos, speed, 220);
        }

        VecAdd(&collectableMovePos, &moby->m_Position, &collectableMovePos);

        // Apply gravity
        if (-220 < collectableProps->m_InitPos.z) {
          collectableProps->m_InitPos.z -= g_DeltaTime * 5;
        }

        if (collectableMovePos.z < 0) {
          // Fell off the world
          // If it's not a life statue or orb, collect it
          if (moby->m_Class != 14 && moby->m_Class != 15) {
            CollectItem(moby);
          }
          func_80052568(moby);
          // Easiest way to exit out
          continue;
        } else {
          collectableMovePos.z += 240;

          if (func_8004BE4C(&collectableMovePos, 240, 240)) {
            // Checks if the last collision was water
            if (func_80057380() == 0) {
              // If it's not a life statue or orb, collect it
              if (moby->m_Class != 14 && moby->m_Class != 15) {
                CollectItem(moby);
              }
              func_80052568(moby);
              // Easiest way to exit out
              continue;
            }

            VecCopy(&collectableSurfaceNormal, &g_CollisionNormal);
            VecCopy(&moby->m_Position, &g_CollisionPoint);
            moby->m_Position.z -= 0xF0;

            if (collectableProps->m_RotX == 0) {
              int groundHeight = func_8004D5EC(&collectableMovePos, 0x400);
              int groundAngle = (signed char)Atan2Fast(
                  collectableSurfaceNormal.z,
                  VecMagnitude(&collectableSurfaceNormal, 0));
              // Settle on ground if close and flat enough
              if ((collectableMovePos.z - 400) < groundHeight &&
                  groundAngle < 24) {
                moby->m_Substate = 1;
                VecCopy(&moby->m_Position, &collectableMovePos);
                moby->m_Position.z = groundHeight;

                if (moby->m_Class != 15) {

                  collectableProps->m_RotY =
                      -Atan2Fast(func_80017A38((collectableSurfaceNormal.x *
                                                collectableSurfaceNormal.x) +
                                               (collectableSurfaceNormal.z *
                                                collectableSurfaceNormal.z)),
                                 collectableSurfaceNormal.y);
                  collectableProps->m_RotZ = -Atan2Fast(
                      collectableSurfaceNormal.z, collectableSurfaceNormal.x);

                  if (collectableProps->m_RotY != 0 ||
                      collectableProps->m_RotZ != 0) {
                    moby->m_Rotation.z = 0;
                  }
                }

                func_800533D0(moby);
              } else {
                collectableProps->m_RotX++;
              }
            }

            if (collectableProps->m_RotX != 0) {
              g_Spu.m_NextSoundOverrideFlags = 1;
              g_Spu.m_VolumeOverride.left =
                  0x3CCC >> (3 - collectableProps->m_RotX);
              g_Spu.m_VolumeOverride.right =
                  0x3CCC >> (3 - collectableProps->m_RotX);

              // Bounce sound? I think
              PlaySound(g_Spu.m_SoundTable->pickupDing, moby, 8,
                        &moby->m_SoundChannel);

              if (func_80017428(&collectableProps->m_InitPos,
                                &collectableSurfaceNormal,
                                &collectableProps->m_InitPos)) {
                collectableProps->m_RotX--;

                // Reduce velocity each bounce with randomness
                collectableProps->m_InitPos.x =
                    (collectableProps->m_InitPos.x >> 3) + (rand() & 0x3F) - 32;
                collectableProps->m_InitPos.y =
                    (collectableProps->m_InitPos.y >> 3) + (rand() & 0x3F) - 32;
                collectableProps->m_InitPos.z =
                    (collectableProps->m_InitPos.z >> 2) + (rand() & 0xF);
              }
            }

          } else {
            // In air
            collectableMovePos.z -= 240;
            VecCopy(&moby->m_Position, &collectableMovePos);
            func_8004D5EC(&collectableMovePos, 0x10000);
            func_800533D0(moby);
          }
        }

        if (distanceToSpyro < 1434) {
          int pickupHeight = moby->m_Position.z + 356;
          int zDist = g_Spyro.m_Position.z - pickupHeight;

          if (ABS2(zDist) < 512) {
            if (g_Sparx != nullptr && g_Spyro.m_airTime == 0 &&
                collectableProps->m_RotX < 3) {

              MobySparxProps *sparxProps = g_Sparx->m_Props;

              if (sparxProps->m_Target == nullptr) {
                if (!IsMobyPlayingSound(
                        g_Sparx, g_Models[g_Sparx->m_Class]->m_Sounds[0])) {
                  g_Spu.m_NextSoundOverrideFlags = 1;
                  g_Spu.m_VolumeOverride.right = 0x2000;
                  g_Spu.m_VolumeOverride.left = 0x2000;
                  func_8003851C(g_Sparx, 0, 0);
                }

                g_Sparx->m_Substate = 4;
                sparxProps->m_Target = moby;
              }
            }
          }
        }

        break;
      }
      case 3: { // After being picked up, move towards spyro
        Vector3D collectablePickupDelta;
        if (collectableProps->m_Ticks >= 32) {
          // Snap to Spyro
          VecCopy(&moby->m_Position, &g_Spyro.m_Position);
        } else {

          // Interpolate toward Spyro
          VecSub(&collectablePickupDelta, &g_Spyro.m_Position,
                 &collectableProps->m_InitPos);
          VecShiftRight(&collectablePickupDelta, 5);

          if (VecMagnitude(&collectablePickupDelta, 1) > 480) {
            // Too far, snap
            VecCopy(&moby->m_Position, &g_Spyro.m_Position);
            collectableProps->m_Ticks = 32;
          } else {
            // Move toward Spyro
            VecMult(&collectablePickupDelta, &collectablePickupDelta,
                    collectableProps->m_Ticks);
            VecAdd(&moby->m_Position, &collectableProps->m_InitPos,
                   &collectablePickupDelta);
            moby->m_Position.z += SINE_8(collectableProps->m_Ticks * 4) / 12;
          }
        }

        // Spin rapidly while being sucked in
        moby->m_Rotation.x = moby->m_Rotation.x - 7 + collectableProps->m_RotY;
        moby->m_Rotation.y = moby->m_Rotation.y - 7 + collectableProps->m_RotZ;
        moby->m_Rotation.z =
            moby->m_Rotation.z - 7 + collectableProps->m_RotationTicks;
        break;
      }

      case 4: {
        continue;
      }
      }
      if (moby->m_Substate < 3) {
        if (moby->m_Class == 14) {
          moby->m_Rotation.x =
              (COSINE_8(collectableProps->m_RotationTicks) >> 9) +
              collectableProps->m_RotY;
          moby->m_Rotation.y =
              (SINE_8(collectableProps->m_RotationTicks) >> 9) +
              collectableProps->m_RotZ;
          collectableProps->m_RotationTicks += g_DeltaTime << 1;
        } else if (moby->m_Class == 15) {
          moby->m_Rotation.z += 8;
          moby->m_Rotation.y -= 6;
        } else {
          moby->m_Rotation.x =
              (COSINE_8(collectableProps->m_RotationTicks) >> 7) +
              collectableProps->m_RotY;
          moby->m_Rotation.y =
              (SINE_8(collectableProps->m_RotationTicks) >> 7) +
              collectableProps->m_RotZ;
          collectableProps->m_RotationTicks += g_DeltaTime << 1;
        }
      }
      if ((collectableProps->m_Ticks > 32 && distanceToSpyro < 512 &&
           (-384 < (g_Spyro.m_Position.z - moby->m_Position.z)) &&
           ((g_Spyro.m_Position.z - moby->m_Position.z) < 512)) ||
          (moby->m_Substate == 3 && collectableProps->m_Ticks > 64)) {

        if (g_Sparx != nullptr) {
          MobySparxProps *sparxProps = g_Sparx->m_Props;

          if (sparxProps->m_Target == moby) {
            sparxProps->m_Target = nullptr;
          }
        }

        // Extra life
        if (moby->m_Class == 14) {
          PlaySound(g_Spu.m_SoundTable->gemPickup, moby, 16, nullptr);
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          g_SpawnParticle(16, 70, &moby->m_Position, 8);
          g_SpawnParticle(16, 70, &moby->m_Position, 0x10);

          // If life count is less than 99, increment it
          if (g_SpyroLifeCount < 99) {
            g_SpyroLifeCount++;
          }

          // Mark as collected and destroy
          func_8003B854(0, moby);
          func_80052568(moby);
        } else if (moby->m_Class == 15) { // Life orb
          PlaySound(g_Spu.m_SoundTable->gemPickup, moby, 16, nullptr);
          g_LifeOrbCount++;

          func_80052568(moby);
        } else {
          CollectItem(moby);
          func_80052568(moby);
        }
      }

      break;
    }
#ifdef HAS_MOBY_88
    case 88: {
      Moby88Props *props = moby->m_Props;
      int angle;
      int zDelta;
      Vector3D particlePosition;

      switch (moby->m_State) {
      case 0:
        if (moby->m_DropMoby) {
          VecCopy(&moby->m_Position, &g_LevelMobys[props->m_0x00].m_Position);
          moby->m_State = 2;
        }
        break;

      case 1:
        if (func_8003BFC0(moby, props->m_0x08, &props->m_0x0c, &props->m_0x18,
                          0x20, 4) == 2) {
          moby->m_State = 2;
        }
        break;

      case 2: {
        int index = props->m_0x1c;

        if (func_80038638(moby, &g_LevelMobys[props->m_0x00].m_Position, 0x600,
                          index * 0x55, 0, 0x80, 3, 0, 0xFF, 0xFF, 0, 0,
                          8) < 0x10) {
          moby->m_State = 3;
        }
        zDelta = g_LevelMobys[props->m_0x00].m_Position.z;
        angle = moby->m_Position.z - 0x200;
        zDelta -= angle;
        if (zDelta < -0x40) {
          zDelta = -0x40;
        }
        if (zDelta > 0x40) {
          zDelta = 0x40;
        }
        moby->m_Position.z += zDelta;
        break;
      }

      case 3: {
        int *linkedProps;

        if (props->m_0x04 >= 0) {
          g_LevelMobys[props->m_0x04].m_Substate |= 1 << props->m_0x1c;
          if (g_LevelMobys[props->m_0x04].m_State == 4) {
            moby->m_State = 4;
            props->m_0x20 = 0x20;
            props->m_0x18 = 0x78;
          }
        } else if (moby->m_Substate == 6 &&
                   DISTANCE_TO_SPYRO(&g_LevelMobys[props->m_0x00]) < 0x1800) {
          linkedProps = g_LevelMobys[props->m_0x00].m_Props;
          moby->m_State = 4;
          linkedProps[2] = 0x10;
          props->m_0x20 = 0x20;
          props->m_0x18 = 0x78;
        }

        angle = ANGLE_FROM(moby->m_Position,
                           g_LevelMobys[props->m_0x00].m_Position);
        RotateMobyToAngle(moby, angle, 2, 0, 0);

        zDelta = g_LevelMobys[props->m_0x00].m_Position.z;
        angle = moby->m_Position.z - 0x200;
        zDelta -= angle;
        if (zDelta < -0x40) {
          zDelta = -0x40;
        }
        if (zDelta > 0x40) {
          zDelta = 0x40;
        }
        moby->m_Position.z += zDelta;
        break;
      }

      case 4:
        angle = (ANGLE_FROM(g_LevelMobys[props->m_0x00].m_Position,
                            moby->m_Position) +
                 0x78) &
                0xFF;
        func_80038638(moby, &g_LevelMobys[props->m_0x00].m_Position, 0x600,
                      angle, 0, props->m_0x20, 0x10, 0, 0xFF, 0xFF, 0, 0, 8);
        moby->m_Position.z += (props->m_0x20 - 0x20) >> 3;
        props->m_0x20 += g_DeltaTime * 2;
        if (props->m_0x20 > 0x100) {
          props->m_0x20 = 0x100;
        }
        if (TICK_TIMER(props->m_0x18)) {
          g_SpawnParticle(16, 80, &moby->m_Position, 0xC);
          func_80052568(moby);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
      func_80052D64(moby, 0, &particlePosition);
      g_SpawnParticle(2, 66, &particlePosition, 2);
      break;
    }
#endif
#ifdef HAS_MOBY_109
    case 109: {
      int pathChoice = 0;
      Moby109Props *props = moby->m_Props;

      Vector3D targetPosition;
      int distance;
      int angle;
      int reachedTarget;
      int closestDistance;
      int pathIndex;
      int i;
      int angleOffset;

      switch (props->m_0x00 & 3) {
      case 0:
        if ((props->m_0x00 & 0x80) != 0) {
          if (g_Spyro.m_airTime != 0) {
            g_Spyro.m_ControlFlags = 0x80000200;
            if (g_Spyro.m_State == 8) {
              D_80078668.m_Coords.azimuth =
                  (D_8006C934.m_Coords.azimuth -
                   g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ) &
                  0xFFF;
            } else {
              D_80078668.m_Coords.azimuth =
                  (D_8006C934.m_Coords.azimuth -
                   g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
                  0xFFF;
            }
            D_80078668.m_Coords.elevation = D_8006C934.m_Coords.elevation;
            D_80078668.m_Coords.radius = D_8006C934.m_Coords.radius;
            D_80078668.m_Offset.azimuth = D_8006C934.m_Offset.azimuth;
            D_80078668.m_Offset.elevation = D_8006C934.m_Offset.elevation;
            D_80078668.m_Offset.radius = D_8006C934.m_Offset.radius;
            g_Spyro.unk_0x220 = &D_80078668;
          } else {
            props->m_0x00 &= ~0x80;
          }
        }

        if ((props->m_0x00 & 0x2C) != 0) {
          g_Spyro.m_ControlFlags = 0x80000327;
          VecSub(&targetPosition, &moby->m_Position, &g_Spyro.m_Position);
          targetPosition.z -= 0x80;
          VecShiftRight(&targetPosition, 2);
          distance = VecMagnitude(&targetPosition, 1);
          if (distance >= 0x201) {
            VecScaleToLength(&targetPosition, distance, 0x200);
          }
          VecAdd(&g_Spyro.m_portalEndPos, &targetPosition, &g_Spyro.m_Position);

          angle = (moby->m_Rotation.z - g_Spyro.m_bodyRotation.z) & 0xFF;
          if (angle > 0x80) {
            angle -= 0x100;
          }
          if (angle < -4) {
            angle = -4;
          }
          if (angle > 4) {
            angle = 4;
          }
          g_Spyro.m_portalAngle.z = g_Spyro.m_bodyRotation.z + angle;
          g_Spyro.m_fallingState = 0x11;
          g_Spyro.unk_0x21c = &g_Spyro.m_Position;
          g_Spyro.m_mobyInUseBySpyro = 0;
          g_Spyro.unk_0x220 = &D_80078668;
          D_80078668.m_Coords.azimuth =
              (D_8006C934.m_Coords.azimuth -
               g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
              0xFFF;
          D_80078668.m_Coords.elevation = D_8006C934.m_Coords.elevation;
          D_80078668.m_Coords.radius = D_8006C934.m_Coords.radius;
          D_80078668.m_Offset.azimuth = D_8006C934.m_Offset.azimuth;
          D_80078668.m_Offset.elevation = D_8006C934.m_Offset.elevation;
          D_80078668.m_Offset.radius = D_8006C934.m_Offset.radius;
        } else if ((props->m_0x00 & 0x10) != 0) {
          g_Spyro.m_ControlFlags = 0x80000327;
          VecCopy(&g_Spyro.m_portalEndPos, &g_Spyro.m_Position);

          angle = (moby->m_Rotation.z - g_Spyro.m_bodyRotation.z) & 0xFF;
          if (angle > 0x80) {
            angle -= 0x100;
          }
          if (angle < -3) {
            angle = -3;
          }
          if (angle > 3) {
            angle = 3;
          }
          g_Spyro.m_portalAngle.z = g_Spyro.m_bodyRotation.z + angle;
          g_Spyro.m_fallingState = 0x11;
          g_Spyro.unk_0x21c = &g_Spyro.m_Position;
          g_Spyro.m_mobyInUseBySpyro = 0;
          g_Spyro.unk_0x220 = &D_80078668;
          D_80078668.m_Coords.azimuth =
              (D_8006C934.m_Coords.azimuth -
               g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
              0xFFF;
          D_80078668.m_Coords.elevation = D_8006C934.m_Coords.elevation;
          D_80078668.m_Coords.radius = D_8006C934.m_Coords.radius;
          D_80078668.m_Offset.azimuth = D_8006C934.m_Offset.azimuth;
          D_80078668.m_Offset.elevation = D_8006C934.m_Offset.elevation;
          D_80078668.m_Offset.radius = D_8006C934.m_Offset.radius;
        }

        if ((props->m_0x00 & 4) != 0) {
          distance = OctDistance(&moby->m_Position, &props->m_0x18);
          if (distance < 0x200) {
            props->m_0x00 = (props->m_0x00 & ~4) | 8;
            props->m_0x14 = props->m_0x10;
            props->m_0x14->m_CurrentNode = 0;
            props->m_0x2c = 0;
            break;
          }

          angle = ANGLE_FROM(moby->m_Position, props->m_0x18);
          distance >>= 1;
          if (distance > 0x140) {
            distance = 0x140;
          }
          if (RotateMobyToAngle(moby, angle, 4, 0x20, 1) != 0) {
            func_80039398(moby, distance, 0, 0x200, 0x20);
          } else {
            angle = (angle - moby->m_Rotation.z) & 0xFF;
            if (angle > 0x80) {
              angle -= 0x100;
            }
            distance -= ABS2(angle) << 4;
            if (distance > 0) {
              func_80039398(moby, distance, 0, 0x200, 0x20);
            }
          }

          distance = props->m_0x18.z - moby->m_Position.z;
          if (distance != 0) {
            distance >>= 1;
            if (distance < -0x40) {
              distance = -0x40;
            }
            if (distance > 0x40) {
              distance = 0x40;
            }
            moby->m_Position.z += distance;
          }
          break;
        } else if ((props->m_0x00 & 8) != 0) {
          distance = 0x140;
          angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x14));
          if (RotateMobyToAngle(moby, angle, 8, 0x30, 1) != 0) {
            func_80039398(moby, 0x140, 0, 0x200, 0x20);
          } else {
            angle = (angle - moby->m_Rotation.z) & 0xFF;
            if (angle > 0x80) {
              angle -= 0x100;
            }
            distance -= ABS2(angle) << 4;
            if (distance > 0) {
              func_80039398(moby, distance, 0, 0x200, 0x20);
            }
          }

          distance = (PATH_CUR_POS(props->m_0x14).z - moby->m_Position.z) >> 2;
          if (distance > 0x60) {
            distance = 0x60;
          }
          if (distance < -0x60) {
            distance = -0x60;
          }

          distance = (distance - props->m_0x2c) >> 1;
          if (distance < -0x10) {
            distance = -0x10;
          }
          if (distance > 0x10) {
            distance = 0x10;
          }
          props->m_0x2c += distance;
          moby->m_Position.z += props->m_0x2c;

          if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x14)) <
              0x200) {
            if (++props->m_0x14->m_CurrentNode >= props->m_0x14->m_NodeCount) {
              props->m_0x14->m_CurrentNode = props->m_0x14->m_NodeCount - 2;
              props->m_0x00 = (props->m_0x00 & ~8) | 0xC0;
              g_Spyro.m_fallingState = 8;
              g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ = 0x290;
            }
          }
          break;
        } else if ((props->m_0x00 & 0x10) != 0) {
          reachedTarget = 1;

          PlaySound(g_Spu.m_SoundTable->whirlwind, moby, 8,
                    &moby->m_SoundChannel);

          if (!moby->m_WasDrawn) {
            VecCopy(&moby->m_Position, &g_Spyro.m_Position);
            moby->m_Position.z += 0x400;
          } else {
            distance = DISTANCE_TO_SPYRO(moby);
            if (distance >= 0x81) {
              distance = distance >> 1;
              if (distance > 0x140) {
                distance = 0x140;
              }
              angle = ANGLE_TO_SPYRO(moby->m_Position);
              if (RotateMobyToAngle(moby, angle, 0x10, 0x30, 1) != 0) {
                func_80039398(moby, distance, 0, 0, 0);
              } else {
                angle = (angle - moby->m_Rotation.z) & 0xFF;
                if (angle > 0x80) {
                  angle -= 0x100;
                }
                distance -= ABS2(angle) << 4;
                if (distance > 0) {
                  func_80039398(moby, distance, 0, 0, 0);
                }
              }
              reachedTarget = 0;
            } else {
              distance = g_Spyro.m_Position.z - moby->m_Position.z + 0x100;
              if (ABS2(distance) >= 0x81) {
                if (distance < -0x80) {
                  distance = -0x80;
                }
                if (distance > 0x80) {
                  distance = 0x80;
                }
                moby->m_Position.z += distance;
                reachedTarget = 0;
              }
            }
          }

          if (reachedTarget == 0) {
            break;
          }

          props->m_0x00 &= ~0x10;
          distance = OctDistance(&moby->m_Position, &props->m_0x18);
          pathChoice = 0;

          for (pathIndex = 0; pathIndex < props->m_0x04->m_NodeCount;
               pathIndex++) {
            closestDistance = OctDistance(
                &moby->m_Position, &PATH_NODE_POS(props->m_0x04, pathIndex));
            if (closestDistance < distance) {
              distance = closestDistance;
              pathChoice = 1;
              props->m_0x04->m_CurrentNode = pathIndex;
            }
          }

          for (pathIndex = 0; pathIndex < props->m_0x08->m_NodeCount;
               pathIndex++) {
            closestDistance = OctDistance(
                &moby->m_Position, &PATH_NODE_POS(props->m_0x08, pathIndex));
            if (closestDistance < distance) {
              distance = closestDistance;
              pathChoice = 2;
              props->m_0x08->m_CurrentNode = pathIndex;
            }
          }

          for (pathIndex = 0; pathIndex < props->m_0x0c->m_NodeCount;
               pathIndex++) {
            closestDistance = OctDistance(
                &moby->m_Position, &PATH_NODE_POS(props->m_0x0c, pathIndex));
            if (closestDistance < distance) {
              distance = closestDistance;
              pathChoice = 3;
              props->m_0x0c->m_CurrentNode = pathIndex;
            }
          }

          switch (pathChoice) {
          case 0:
            props->m_0x00 |= 4;
            break;
          case 1:
            props->m_0x00 |= 0x20;
            props->m_0x14 = props->m_0x04;
            break;
          case 2:
            props->m_0x00 |= 0x20;
            props->m_0x14 = props->m_0x08;
            break;
          case 3:
            props->m_0x00 |= 0x20;
            props->m_0x14 = props->m_0x0c;
            break;
          }
          break;
        } else if ((props->m_0x00 & 0x20) != 0) {
          distance = 0x140;
          angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x14));
          if (RotateMobyToAngle(moby, angle, 8, 0x30, 1) != 0) {
            func_80039398(moby, 0x140, 0, 0x200, 0x20);
          } else {
            angle = (angle - moby->m_Rotation.z) & 0xFF;
            if (angle > 0x80) {
              angle -= 0x100;
            }
            distance -= ABS2(angle) << 4;
            if (distance > 0) {
              func_80039398(moby, distance, 0, 0x200, 0x20);
            }
          }

          distance = (PATH_CUR_POS(props->m_0x14).z - moby->m_Position.z) >> 1;
          if (distance > 0x40) {
            distance = 0x40;
          }
          if (distance < -0x40) {
            distance = -0x40;
          }
          moby->m_Position.z += distance;

          if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x14)) <
              0x200) {
            if (++props->m_0x14->m_CurrentNode >= props->m_0x14->m_NodeCount) {
              props->m_0x14->m_CurrentNode = 0;
              props->m_0x00 = (props->m_0x00 & ~0x20) | 4;
            }
          }
          break;
        } else if ((props->m_0x00 & 0x40) != 0) {
          if (props->m_0x14->m_CurrentNode > props->m_0x14->m_NodeCount) {
            distance = OctDistance(&moby->m_Position, &props->m_0x18);
            if (distance > 0x140) {
              distance = 0x140;
            }
            angle = ANGLE_FROM(moby->m_Position, props->m_0x18);
            if (RotateMobyToAngle(moby, angle, 8, 0x30, 1) != 0) {
              func_80039398(moby, distance, 0, 0x200, 0x20);
            } else {
              angle = (angle - moby->m_Rotation.z) & 0xFF;
              if (angle > 0x80) {
                angle -= 0x100;
              }
              distance -= ABS2(angle) << 4;
              if (distance > 0) {
                func_80039398(moby, distance, 0, 0x200, 0x20);
              }
            }

            distance = (props->m_0x18.z - moby->m_Position.z) >> 1;
            if (ABS2(distance) < 0x80) {
              props->m_0x14->m_CurrentNode = 0;
              props->m_0x00 &= ~0x40;
            }
            if (distance > 0x80) {
              distance = 0x80;
            }
            if (distance < -0x80) {
              distance = -0x80;
            }
            moby->m_Position.z += distance;
          } else {
            distance = 0x140;
            angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x14));
            if (RotateMobyToAngle(moby, angle, 8, 0x30, 1) != 0) {
              func_80039398(moby, 0x140, 0, 0x200, 0x20);
            } else {
              angle = (angle - moby->m_Rotation.z) & 0xFF;
              if (angle > 0x80) {
                angle -= 0x100;
              }
              distance -= ABS2(angle) << 4;
              if (distance > 0) {
                func_80039398(moby, distance, 0, 0x200, 0x20);
              }
            }

            distance =
                (PATH_CUR_POS(props->m_0x14).z - moby->m_Position.z) >> 1;
            if (distance > 0x40) {
              distance = 0x40;
            }
            if (distance < -0x40) {
              distance = -0x40;
            }
            moby->m_Position.z += distance;

            if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x14)) <
                0x200) {
              props->m_0x14->m_CurrentNode--;
            }
          }
          break;
        } else {
          distance = OctDistance(&g_Spyro.m_Position, &props->m_0x18);
          props->m_0x14 = 0;

          for (i = 0; i < props->m_0x04->m_NodeCount; i++) {
            closestDistance = OctDistance(&g_Spyro.m_Position,
                                          &PATH_NODE_POS(props->m_0x04, i));
            if (closestDistance < distance) {
              distance = closestDistance;
              props->m_0x14 = props->m_0x04;
              props->m_0x14->m_CurrentNode = i;
            }
          }

          for (i = 0; i < props->m_0x08->m_NodeCount; i++) {
            closestDistance = OctDistance(&g_Spyro.m_Position,
                                          &PATH_NODE_POS(props->m_0x08, i));
            if (closestDistance < distance) {
              distance = closestDistance;
              props->m_0x14 = props->m_0x08;
              props->m_0x14->m_CurrentNode = i;
            }
          }

          for (i = 0; i < props->m_0x0c->m_NodeCount; i++) {
            closestDistance = OctDistance(&g_Spyro.m_Position,
                                          &PATH_NODE_POS(props->m_0x0c, i));
            if (closestDistance < distance) {
              distance = closestDistance;
              props->m_0x14 = props->m_0x0c;
              props->m_0x14->m_CurrentNode = i;
            }
          }

          if (distance >= 0x3000) {
            break;
          }

          if (props->m_0x14 != 0) {
            VecCopy(&targetPosition, &PATH_CUR_POS(props->m_0x14));
          } else {
            VecCopy(&targetPosition, &props->m_0x18);
          }

          distance = OctDistance(&moby->m_Position, &targetPosition);
          if (distance >= 0x101) {
            distance = distance >> 1;
            if (distance > 0x140) {
              distance = 0x140;
            }
            angle = ANGLE_FROM(moby->m_Position, targetPosition);
            if (RotateMobyToAngle(moby, angle, 0x20, 0x30, 1) != 0) {
              func_80039398(moby, distance, 0, 0x200, 0x20);
            } else {
              angle = (angle - moby->m_Rotation.z) & 0xFF;
              if (angle > 0x80) {
                angle -= 0x100;
              }
              distance -= ABS2(angle) << 4;
              if (distance > 0) {
                func_80039398(moby, distance, 0, 0x200, 0x20);
              }
            }
          } else {
            func_800562A4(moby, 1);
            RotateMobyToSpyro(moby, 0x10, 0x18, 1);
          }

          distance = (g_Spyro.m_Position.z - moby->m_Position.z - 0x400) >> 1;
          if (distance < 0) {
            if (distance < -0x80) {
              distance = -0x80;
            }
            moby->m_Position.z += distance;
          } else {
            distance = props->m_0x18.z - moby->m_Position.z;
            if (distance > 0x40) {
              distance = 0x40;
            }
            moby->m_Position.z += distance;
          }

          if (g_Spyro.m_Position.z <= 0x9357) {
            props->m_0x00 |= 0x10;
          }
          break;
        }

      case 1:
      case 2:
        if ((*(int *)g_LevelMobys[props->m_0x24].m_Props & 0x2C) != 0) {
          if ((props->m_0x00 & 3) == 1) {
            angleOffset = 0x40;
          } else {
            angleOffset = -0x40;
          }

          VecCopy(&targetPosition, &g_Spyro.m_Position);

          if (moby->m_State != props->m_0x00) {
            moby->m_State = props->m_0x00 & 3;
            if (moby->m_AnimationState.m_NextAnimation != props->m_0x00) {
              MOBY_ANIM_ADVANCE(moby, props->m_0x00 & 3);
            }
            break;
          }

          angle = (angleOffset << 4) + g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
          targetPosition.x += Cos(angle) >> 4;
          targetPosition.y += Sin(angle) >> 4;
          VecCopy(&moby->m_Position, &targetPosition);
          RotateMobyToAngle(moby, g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4, 8,
                            0x20, 1);
          props->m_0x28 = (props->m_0x28 + (g_DeltaTime << 1)) & 0xFF;
          func_800533D0(moby);
          func_800529E4(moby, UPDATE_PROP_CHAIN);
          break;
        } else {
          if ((props->m_0x00 & 3) == 1) {
            angleOffset = 0x50;
          } else {
            angleOffset = -0x50;
          }

          VecCopy(&targetPosition, &g_LevelMobys[props->m_0x24].m_Position);

          if (moby->m_State != 0) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            break;
          }

          angle =
              ((angleOffset + g_LevelMobys[props->m_0x24].m_Rotation.z) & 0xFF)
              << 4;
          targetPosition.z -= 0x180;
          targetPosition.x += Cos(angle) >> 2;
          targetPosition.y += Sin(angle) >> 2;

          distance = OctDistance(&targetPosition, &moby->m_Position);
          VecSub(&targetPosition, &targetPosition, &moby->m_Position);

          if (distance >= 0x21) {
            angle = Atan2(targetPosition.x, targetPosition.y, 0);
            distance = distance >> 1;
            if (distance > 0x190) {
              distance = 0x190;
            }
            if (RotateMobyToAngle(moby, angle, 8, 0x20, 1) != 0) {
              func_80039398(moby, distance, 0, 0x200, 0x20);
            } else {
              angle = (angle - moby->m_Rotation.z) & 0xFF;
              if (angle > 0x80) {
                angle -= 0x100;
              }
              distance -= ABS2(angle) << 5;
              if (distance > 0) {
                func_80039398(moby, distance, 0, 0x200, 0x20);
              }
            }
            props->m_0x28 = g_LevelMobys[props->m_0x24].m_Rotation.z;
          } else {
            RotateMobyToAngle(moby, g_LevelMobys[props->m_0x24].m_Rotation.z, 8,
                              0x20, 1);
          }

          if (targetPosition.z < -0x80) {
            targetPosition.z = -0x80;
          }
          if (targetPosition.z > 0x80) {
            targetPosition.z = 0x80;
          }
          moby->m_Position.z += targetPosition.z;
          break;
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_110
    case 110: { // Dragon Pad Fairy
      Moby110Props *fairyProps = moby->m_Props;

      Moby *dragonMoby = &g_LevelMobys[fairyProps->m_0x00];
      Moby *padMoby = &g_LevelMobys[fairyProps->m_0x04];

      switch (moby->m_State) {
      case 0: {
        moby->m_CollisionGroup = nullptr;
        if (DISTANCE_TO_SPYRO(padMoby) > 2560) {
          moby->m_State = 1;
        }
        break;
      }

      case 1: {
        if (dragonMoby->m_State >= 0x80) {
          // If dragon is dead
          moby->m_State = 2;
          fairyProps->m_0x08 = 16;
          fairyProps->m_0x0c = moby->m_Position.z;
        }
        break;
      }

      case 2: {
        if (fairyProps->m_0x08 != 0) {
          fairyProps->m_0x08--;
        } else {
          moby->m_CollisionGroup = nullptr;

          if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
            if (SPYRO_BASE_Z_DISTANCE(moby) < 2048) {
              if (fairyProps->m_0x24 == 0 || padMoby->m_State == 1) {
                // Spawn the fairy
                fairyProps->m_0x24 = 0;
                moby->m_Position.z = fairyProps->m_0x0c + 0x80;
                moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position) - 128;
                moby->m_RenderRadius = 0x20;
                moby->m_State = 3;
                moby->m_ScaleOverride = 0x60;

                // Spawn particle effect
                g_SpawnParticle(24, 80, &moby->m_Position, 12);

                func_800529E4(moby, UPDATE_PROP_COLLISION);
                func_8004D5EC(&moby->m_Position, 0x1000);
                func_800533D0(moby);
                moby->m_ShadowDistance |= 0x80000000;
              }
            }
          }
        }
        break;
      }

      case 3: {
        if (moby->m_ScaleOverride >= 0x21) {
          moby->m_ScaleOverride -= 4;                  // Shrink
          moby->m_Rotation.z = moby->m_Rotation.z + 8; // Spin
        } else {
          moby->m_State = 4;
          fairyProps->m_0x08 = 0;
          fairyProps->m_0x20 = 30;
        }
        break;
      }

      case 4: { // Idle hovering
        fairyProps->m_0x08++;
        moby->m_Position.z =
            fairyProps->m_0x0c + (Cos(fairyProps->m_0x08 << 7) >> 6);

        // Check if pad is near Spyro and Spyro is idle
        if ((padMoby->m_State == 0 ||
             (padMoby->m_State == 2 && padMoby->m_Substate >= 0x10)) &&
            DISTANCE_TO_SPYRO(padMoby) < 1024 &&
            SPYRO_BASE_Z_DISTANCE(padMoby) < 512) {

          // Spyro must be idle or standing still
          if ((g_Spyro.m_State == 0 || g_Spyro.m_State == 0xD) &&
              g_Spyro.m_idleTimer > 0) {
            moby->m_State = 6;
            fairyProps->m_0x24 = 1;
            InitFairyCutscene(moby);
            break;
          }
        }

        // Check if should retarget or move away
        if (DISTANCE_TO_SPYRO(moby) > 0x2400 ||
            (SPYRO_BASE_Z_DISTANCE(moby) > 0xC00)) {
          // Too far from Spyro, despawn
          moby->m_State = 6;
        } else {
          fairyProps->m_0x20--;
          if (fairyProps->m_0x20 == 0) {
            // Calculate new target position away from Spyro
            int baseDistance = (rand() & 0x3F) + 0x140; // 320-383
            char finalAngle =
                (ANGLE_TO_SPYRO(padMoby->m_Position) + (rand() & 0xF) - 8);

            VecCopy(&fairyProps->m_0x10, &padMoby->m_Position);

            moby->m_State = 5;

            // Calculate offset from parent
            fairyProps->m_0x10.x -=
                FIXED_MUL(Cos(finalAngle * 0x10), baseDistance);
            fairyProps->m_0x10.y -=
                FIXED_MUL(Sin(finalAngle * 0x10), baseDistance);

            fairyProps->m_0x1c = ANGLE_TO_SPYRO(fairyProps->m_0x10);
            fairyProps->m_0x20 = 0;
          }
        }
        break;
      }
      case 5: {
        fairyProps->m_0x08++;
        moby->m_Position.z =
            fairyProps->m_0x0c + (Cos(fairyProps->m_0x08 << 7) >> 6);

        if ((padMoby->m_State == 0 ||
             (padMoby->m_State == 2 && padMoby->m_Substate >= 0x10)) &&
            DISTANCE_TO_SPYRO(padMoby) < 0x400 &&
            SPYRO_BASE_Z_DISTANCE(padMoby) < 512) {

          if ((g_Spyro.m_State == 0 || g_Spyro.m_State == 0xD) &&
              g_Spyro.m_idleTimer > 0) {
            moby->m_State = 6;
            fairyProps->m_0x24 = 1;
            InitFairyCutscene(moby);
            break;
          }
        }

        // Continue moving toward target
        if (DISTANCE_TO_SPYRO(moby) > 0x2800 ||
            SPYRO_BASE_Z_DISTANCE(moby) > 0xC00) {
          moby->m_State = 6;
        } else {
          Vector3D fairyMovementDelta;
          int angleDiff;
          int cosWeight1;
          int cosDelta;
          int totalWeight;

          fairyProps->m_0x20++;

          VecSub(&fairyMovementDelta, &fairyProps->m_0x10, &moby->m_Position);

          angleDiff = func_80017948(fairyProps->m_0x1c, moby->m_Rotation.z);

          // Smooth interpolation using cosine
          cosWeight1 = Cos((fairyProps->m_0x20 - 1) << 7);
          cosDelta = cosWeight1 - Cos(fairyProps->m_0x20 << 7);
          totalWeight = Cos((fairyProps->m_0x20 - 1) << 7) + 0x1000;

          // Move toward target with smooth acceleration
          moby->m_Position.x += (fairyMovementDelta.x * cosDelta) / totalWeight;
          moby->m_Position.y +=
              ((fairyMovementDelta.y * cosDelta) / totalWeight);
          moby->m_Rotation.z += (angleDiff * cosDelta) / totalWeight;

          func_8004D5EC(&moby->m_Position, 0x1000);
          func_800533D0(moby);

          // Reached target
          if (fairyProps->m_0x20 == 0x10) {
            moby->m_State = 4;
            fairyProps->m_0x20 = (rand() & 0x1F) + 0x1E; // 30-61
          }
        }

        break;
      }

      case 6: {
        if (moby->m_ScaleOverride < 96) {
          moby->m_ScaleOverride += 4;
          moby->m_Rotation.z = moby->m_Rotation.z + 8;
        } else {
          // Fully shrunk
          moby->m_RenderRadius = 0;
          moby->m_WasDrawn = 0;
          moby->m_State = 2;
          fairyProps->m_0x08 = 16;

          // Spawn particle effect
          g_SpawnParticle(24, 80, &moby->m_Position, 12);

          moby->m_ShadowDistance &= 0x7FFFFFFF;
        }
        break;
      }
      }

      break;
    }
#endif
#ifdef HAS_MOBY_113
    case 113: {
      Moby113Props *props;
      int dist;

      props = (Moby113Props *)moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 7) {
        props->m_0x08 = func_80038098(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20);
        props->m_0x0c = 0x190;

        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
          props->m_0x0c = 500;
        }

        props->m_0x10 = RandRange(2, 5);

        if (rand() & 1) {
          props->m_0x10 = -props->m_0x10;
        }

        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 7;
        MOBY_ANIM_CHANGE(moby, 7);
        continue;
      }

      switch (moby->m_State) {
      case 0:
        if (g_AnimationFinished) {
          if (props->m_0x00 == 0) {
            props->m_0x00 = RandRange(3, 6);

            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          } else {
            props->m_0x00--;

            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          }
        }

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (TICK_TIMER(props->m_0x04)) {
          if (DISTANCE_TO_SPYRO(moby) < 0x2000 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 1500) {
            if (moby->m_AnimationState.m_Animation == 0) {
              moby->m_State = 2;
              MOBY_ANIM_CHANGE(moby, 2);
            } else {
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
            }

            continue;
          }
        }

        break;

      case 2:
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }

        break;

      case 3:
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        break;

      case 4:
        dist = DISTANCE_TO_SPYRO(moby);

        if (g_AnimationFinished) {
          if (dist > 0xC00) {
            if (props->m_0x00 == 0) {
              props->m_0x00 = RandRange(3, 6);

              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 10);
            } else {
              props->m_0x00--;

              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
            }
          } else if (moby->m_AnimationState.m_NextAnimation != 4) {
            g_AnimationFinished = 0;
            MOBY_ANIM_ADVANCE(moby, 4);
          }
        }

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (dist < 3000 && SPYRO_BASE_Z_DISTANCE(moby) < 1200) {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }

        if (dist > 0x2400 || SPYRO_BASE_Z_DISTANCE(moby) > 1700) {
          moby->m_State = 6;
          MOBY_ANIM_CHANGE(moby, 6);
          continue;
        }

        break;

      case 5:
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (g_Spyro.m_State == 0x16) {
          props->m_0x04 = 0x8C;
        }

        if (g_AnimationFinished) {
          if (props->m_0x04 == 0) {
            moby->m_State = 4;
            MOBY_ANIM_CHANGE(moby, 4);
          } else {
            moby->m_State = 8;
            MOBY_ANIM_CHANGE(moby, 8);
          }

          continue;
        }

        g_Spyro.unk_0x208.x = FIXED_MUL(SINE_8(moby->m_Rotation.z), 0x80);
        g_Spyro.unk_0x208.y = FIXED_MUL(COSINE_8(moby->m_Rotation.z), -0x80);
        g_Spyro.unk_0x208.z = 0;
        break;

      case 6:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        break;

      case 7:
        if (moby->m_AnimationState.m_Frame < 10) {
          moby->m_Rotation.z += props->m_0x10;
        }

        if (props->m_0x0c >= 0x1F) {
          props->m_0x0c -= 0x1E;
          func_80039688(moby, props->m_0x08, props->m_0x0c, 0, 300, 1);
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x20);
          func_80052568(moby);
          continue;
        }

        break;

      case 8:
        if (moby->m_AnimationState.m_Frame >= 0x1C) {
          if (TICK_TIMER(props->m_0x04)) {
            moby->m_AnimationState.m_Frame = 0x0F;
          }
        }

        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        break;
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_114
    case 114: {
      Moby114Props *props = moby->m_Props;
      int distance;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          !(moby->m_State > 6 && moby->m_State < 10)) {
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);

        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
          props->m_0x10 = 0x190;
          props->m_0x14 = 0x46;
          props->m_0x0c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x28, 0x80);
          moby->m_State = 8;
          MOBY_ANIM_CHANGE(moby, 8);
          continue;
        }

        PlaySound(g_Spu.m_SoundTable->sound_0x27, moby, 8,
                  &moby->m_SoundChannel);
        props->m_0x14 = 0xB4;
        props->m_0x10 = 0x118;
        props->m_0x0c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        moby->m_State = 7;
        MOBY_ANIM_CHANGE(moby, 7);
        continue;
      }

      if (props->m_0x08 >= 0 && g_LevelMobys[props->m_0x08].m_State >= 0x80) {
        props->m_0x08 = -1;
      }

      switch (moby->m_State) {
      case 0: {
        int xyDistance;
        int deltaY;
        int deltaZ;

        xyDistance = g_Spyro.m_Position.x - moby->m_Position.x;
        deltaY = g_Spyro.m_Position.y - moby->m_Position.y;

        xyDistance = ABS2(xyDistance);
        xyDistance += ABS2(deltaY);
        deltaZ = g_Spyro.m_Position.z - moby->m_Position.z;
        deltaZ = ABS2(deltaZ);
        distance = xyDistance + deltaZ;

        if (distance < 0x4000 && DISTANCE_TO_SPYRO(moby) < 0x2800 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        if (props->m_0x08 >= 0 && TICK_TIMER(props->m_0x04)) {
          if (OctDistance(&moby->m_Position,
                          &g_LevelMobys[props->m_0x08].m_Position) < 0x1000) {
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }

          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }

        func_80038458(moby);
        break;
      }
      case 1: {
        int xyDistance;
        int deltaY;
        int deltaZ;

        xyDistance =
            g_LevelMobys[props->m_0x08].m_Position.x - moby->m_Position.x;
        deltaY = g_LevelMobys[props->m_0x08].m_Position.y - moby->m_Position.y;

        xyDistance = ABS2(xyDistance);
        xyDistance += ABS2(deltaY);
        deltaZ = g_LevelMobys[props->m_0x08].m_Position.z - moby->m_Position.z;
        deltaZ = ABS2(deltaZ);
        distance = xyDistance + deltaZ;

        if (distance < 0x1800 &&
            OctDistance(&moby->m_Position,
                        &g_LevelMobys[props->m_0x08].m_Position) < 0x1000) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        if (g_AnimationFinished) {
          props->m_0x04 = (rand() & 0x3F) + 0x20;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        func_80038458(moby);
        break;
      }

      case 2: {
        int xyDistance;
        int deltaY;
        int deltaZ;

        xyDistance = g_Spyro.m_Position.x - moby->m_Position.x;
        deltaY = g_Spyro.m_Position.y - moby->m_Position.y;

        xyDistance = ABS2(xyDistance);
        xyDistance += ABS2(deltaY);
        deltaZ = g_Spyro.m_Position.z - moby->m_Position.z;
        deltaZ = ABS2(deltaZ);
        distance = xyDistance + deltaZ;

        if (distance < 0x4000 && DISTANCE_TO_SPYRO(moby) < 0x2800 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        RotateMobyToAngle(moby,
                          ANGLE_FROM(moby->m_Position,
                                     g_LevelMobys[props->m_0x08].m_Position),
                          8, 0x10, 1);

        if (g_AnimationFinished) {
          props->m_0x04 = (rand() & 0x3F) + 0x20;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        func_80038458(moby);
        break;
      }

      case 3: {
        int angle;
        int angleDelta;
        int xyDistance;
        int deltaY;
        int deltaZ;

        xyDistance = g_Spyro.m_Position.x - moby->m_Position.x;
        deltaY = g_Spyro.m_Position.y - moby->m_Position.y;

        xyDistance = ABS2(xyDistance);
        xyDistance += ABS2(deltaY);
        deltaZ = g_Spyro.m_Position.z - moby->m_Position.z;
        deltaZ = ABS2(deltaZ);
        distance = xyDistance + deltaZ;

        if (distance < 0x4000 && DISTANCE_TO_SPYRO(moby) < 0x2800 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          if (props->m_0x00->m_CurrentNode < props->m_0x00->m_NodeCount - 1) {
            props->m_0x00->m_CurrentNode++;
          }
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <
            0x200) {
          if (props->m_0x00->m_CurrentNode == 0) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
          props->m_0x00->m_CurrentNode--;
        }

        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));
        angleDelta = (angle - moby->m_Rotation.z) & 0xFF;
        if (angleDelta > 0x80) {
          angleDelta -= 0x100;
        }

        if (ABS2(angleDelta) < 0x20) {
          func_80039398(moby, 0x40, 0x200, 0x200, 0x27);
        }

        if (angleDelta < -8) {
          angleDelta = -8;
        }
        if (angleDelta > 8) {
          angleDelta = 8;
        }

        moby->m_Rotation.z += angleDelta;
        break;
      }

      case 4: {
        if (g_AnimationFinished) {
          if (g_Spyro.m_State == 11 || g_Spyro.m_State == 20) {
            if (moby->m_AnimationState.m_Animation != 6) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 6);
            }
            moby->m_State = 20;
            continue;
          }

          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }

        RotateMobyToSpyro(moby, 8, 0x10, 1);
        break;
      }

      case 5: {
        int angle;
        int angleDelta;

        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <
            0x200) {
          if (props->m_0x00->m_CurrentNode < props->m_0x00->m_NodeCount - 1) {
            props->m_0x00->m_CurrentNode++;
          } else {
            props->m_0x04 = 0x78;
            moby->m_State = 6;
            MOBY_ANIM_CHANGE(moby, 6);
            continue;
          }
        }

        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));
        angleDelta = (angle - moby->m_Rotation.z) & 0xFF;
        if (angleDelta > 0x80) {
          angleDelta -= 0x100;
        }

        if (ABS2(angleDelta) < 0x20) {
          func_80039398(moby, 0x82, 0x200, 0x200, 0x27);
        }

        if (angleDelta < -8) {
          angleDelta = -8;
        }
        if (angleDelta > 8) {
          angleDelta = 8;
        }

        moby->m_Rotation.z += angleDelta;
        break;
      }

      case 6: {
        int xyDistance;
        int deltaY;
        int deltaZ;

        xyDistance = g_Spyro.m_Position.x - moby->m_Position.x;
        deltaY = g_Spyro.m_Position.y - moby->m_Position.y;

        xyDistance = ABS2(xyDistance);
        xyDistance += ABS2(deltaY);
        deltaZ = g_Spyro.m_Position.z - moby->m_Position.z;
        deltaZ = ABS2(deltaZ);
        distance = xyDistance + deltaZ;

        if (distance < 0x4000 && DISTANCE_TO_SPYRO(moby) < 0x2800 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          RotateMobyToSpyro(moby, 8, 0x10, 1);
          props->m_0x04 = 0x78;
          break;
        }

        if (TICK_TIMER(props->m_0x04)) {
          props->m_0x00->m_CurrentNode = props->m_0x00->m_NodeCount - 1;
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }

        break;
      }
      case 7: {
        if (g_AnimationFinished) {
          moby->m_State = 9;
          MOBY_ANIM_CHANGE(moby, 9);
          continue;
        }

        moby->m_Rotation.y += 4;
        RotateMobyToAngle(moby, (props->m_0x0c + 0x80) & 0xFF, 0x10, 0x20, 1);
        MoveMobyWithGravity(moby, &props->m_0x10, props->m_0x0c, &props->m_0x14,
                            0xC, 0xC);
        break;
      }

      case 8: {
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x1C);
          func_80052568(moby);
          continue;
        }

        MoveMobyWithGravity(moby, &props->m_0x10, props->m_0x0c, &props->m_0x14,
                            0xC, 0xC);
        RotateMobyToAngle(moby, (props->m_0x0c + 0x80) & 0xFF, 0x10, 0x20, 1);
        break;
      }

      case 9: {
        if (MoveMobyWithGravity(moby, &props->m_0x10, props->m_0x0c,
                                &props->m_0x14, 0xC, 0x10) == 3) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x10);
          func_80052568(moby);
          continue;
        }

        RotateMobyToAngle(moby, (props->m_0x0c + 0x80) & 0xFF, 0x10, 0x20, 1);
        break;
      }

      case 20: {
        RotateMobyToSpyro(moby, 4, 0, 0);

        if (g_Spyro.m_State != 0xB && g_Spyro.m_State != 0x14) {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_115
    case 115: {
      Moby115Props *props = moby->m_Props;

      // If the Gnorc has been flamed while not in its dying state
      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 6) {
        // Prepare knockback values
        props->m_KnockbackSpeed = 0xF0;
        props->m_KnockbackAngle = g_Spyro.m_bodyRotation.z;
        moby->m_DamageFlags = 0;

        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        // Enter dying state
        moby->m_State = 6;
        MOBY_ANIM_CHANGE(moby, 6);
        break;
      }

      switch (moby->m_State) {
      case 0: // Idle
        RotateMobyToSpyro(moby, 3, 0x10, 0);

        // Take note of Spyro: enter attack stance state
        if (DISTANCE_TO_SPYRO(moby) < 0x2000 &&
            SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
          // Value is overwritten before entering dying state and never used
          props->m_KnockbackSpeed = 0x48;

          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        // Index is -1 in all placements: unused
        if (props->m_LinkIndex != -1) {
          if (TICK_TIMER(props->m_LinkedMobyCheckTimer)) {
            Moby *targetMoby = &g_LevelMobys[props->m_LinkIndex];
            int angle = func_800381BC(
                ANGLE_FROM(moby->m_Position, targetMoby->m_Position),
                moby->m_Rotation.z);
            if (-ROTDEG8(45) <= angle && angle <= -ROTDEG8(37)) {
              moby->m_Substate = 0;
              moby->m_State = 10;
              continue;
            }
          }
        }
        break;
      case 2: // Entering attack stance
        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;
      case 3: { // Attack stance
        int distance = DISTANCE_TO_SPYRO(moby);
        RotateMobyToSpyro(moby, 3, 0, 0);

        // Spyro is close enough to hit
        if (distance < 3000 && SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
          // Value is overwritten before entering dying state and never used
          props->m_KnockbackSpeed = 0x48;

          props->m_LaughCounter = 0;

          // Enter attacking state
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        // Spyro is out of range again
        if (distance > 0x2400) {
          // Enter attack stance exit state
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }
      }

      break;
      case 4: // Attacking
        RotateMobyToSpyro(moby, 6, 0, 0);

        // If Spyro has been flattened
        if (g_Spyro.m_State == 25) {
          // Will cause 1 laughing anim
          props->m_LaughCounter = 2;
        }

        if (g_AnimationFinished) {
          // If the hit landed, proceed to laughing state
          // Otherwise, ready hit again
          if (props->m_LaughCounter) {
            moby->m_State = 7;
            MOBY_ANIM_CHANGE(moby, 7);
          } else {
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
          }
          continue;
        }
        break;
      case 5: // Leaving attack stance
        if (g_AnimationFinished) {
          // Return to idle state
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      case 6: // Dying
        if (props->m_KnockbackSpeed > 0) {
          func_80039688(moby, props->m_KnockbackAngle, props->m_KnockbackSpeed,
                        500, 700, 0);
          // Incrementally reduce knockback speed
          props->m_KnockbackSpeed -= 0x10;
        }

        // Wrap up Moby's death
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x48);
          func_80052568(moby);
          continue;
        }
        break;
      case 7: // Laughing
        // Play laughing anim
        if (g_AnimationFinished) {
          if (TICK_TIMER(props->m_LaughCounter)) {
            // Return to idle
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        }
        break;
      case 10: // Unused linked Moby state
        switch (moby->m_Substate) {
        case 0:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);
          if (g_AnimationFinished) {
            moby->m_Substate++;
          }
          break;
        case 1:
          // This animation did not ship
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);

          // No Dark Hollow Moby has Animation 13
          if (g_AnimFrameFinished && moby->m_AnimationState.m_Frame == 8) {
            g_LevelMobys[props->m_LinkIndex].m_State = 13;
            g_LevelMobys[props->m_LinkIndex].m_AnimationState.m_Animation = 13;
            g_LevelMobys[props->m_LinkIndex].m_AnimationState.m_NextAnimation =
                13;
            g_LevelMobys[props->m_LinkIndex].m_AnimationState.m_Frame = 0;
            g_LevelMobys[props->m_LinkIndex].m_AnimationState.m_NextFrame = 0;
            g_LevelMobys[props->m_LinkIndex].m_AnimationState.m_FrameProgress =
                0;
          }
          if (g_AnimationFinished) {
            moby->m_Substate++;
          }
          break;
        case 2:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
          if (g_AnimationFinished) {
            // 10s timer for the linked moby code
            props->m_LinkedMobyCheckTimer = 600;
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
          break;
        }
        break;
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
    case MOBYCLASS_SPARX: {
      MobySparxProps *sparxProps = moby->m_Props;
      char pitchAngle;
      Vector3D sparxPosition;

      if (g_Spyro.m_health >= 2) {

        sparxPosition.x = 0;
        sparxPosition.y = 100;
        sparxPosition.z = 0;
        VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &sparxPosition,
                          &sparxPosition);
        VecAdd(&sparxPosition, &sparxPosition, &moby->m_Position);
        g_SpawnParticle(2, 66, &sparxPosition, 0);

        sparxPosition.x = 0;
        sparxPosition.y = -100;
        sparxPosition.z = 0;
        VecRotateByLastMatrix(&sparxPosition, &sparxPosition);
        VecAdd(&sparxPosition, &sparxPosition, &moby->m_Position);
        g_SpawnParticle(2, 66, &sparxPosition, 0);
      }

      if (g_Spyro.m_health >= 3) {
        if (sparxProps->m_Glow == nullptr) {
          if ((sparxProps->m_Glow = func_80058AE8()) != nullptr) {
            sparxProps->m_Glow->m_MobyPos = &moby->m_Position;
            sparxProps->m_Glow->m_Radius = 0x40;
            sparxProps->m_Glow->m_PosOffset.x = 0;
            sparxProps->m_Glow->m_PosOffset.y = 0;
            sparxProps->m_Glow->m_PosOffset.z = 0;
            sparxProps->m_Glow->m_GlowColor.r = 192;
            sparxProps->m_Glow->m_GlowColor.g = 192;
            sparxProps->m_Glow->m_GlowColor.b = 96;
            sparxProps->m_Glow->m_VertexCount = 9;
            sparxProps->m_Glow->m_Vertices = g_SparxGlowVerts;
          }
        } else {
          sparxProps->m_Glow->m_Radius += 0x20;
          if (sparxProps->m_Glow->m_Radius > 0x400) {
            sparxProps->m_Glow->m_Radius = 0x400;
          }
        }
      } else {
        if (sparxProps->m_Glow != nullptr) {
          func_80058B60(sparxProps->m_Glow);
          sparxProps->m_Glow = nullptr;
        }
      }

      if (g_Spyro.m_health <= 0) {
        if (sparxProps->m_Target != nullptr &&
            sparxProps->m_Target->m_Class == 16) {
          sparxProps->m_Target->m_State = 0;
        }
        g_Sparx = nullptr;
        func_80052568(moby);
        break;
      }

      if (sparxProps->m_Target != nullptr && DISTANCE_TO_SPYRO(moby) > 8192) {
        sparxProps->m_Timer = 0;
      }

      if (moby->m_Substate == 99)
        break;

      if (sparxProps->m_Target != nullptr) {
        Vector3D vec;
        switch (moby->m_Substate) {
        case 0: {
          Moby *target = sparxProps->m_Target;
          MobyButterflyProps *bp = target->m_Props;
          int isPickupAnimPhase = moby->m_AnimationState.m_NextAnimation & 1;
          int dist;
          int targetSpeed;

          VecCopy(&vec, &target->m_Position);
          if (isPickupAnimPhase == 0) {
            vec.x -= COSINE_8(sparxProps->m_Target->m_Rotation.z) >> 4;
            vec.y -= SINE_8(sparxProps->m_Target->m_Rotation.z) >> 4;
          } else {
            vec.x -= COSINE_8(sparxProps->m_Target->m_Rotation.z) >> 6;
            vec.y -= SINE_8(sparxProps->m_Target->m_Rotation.z) >> 6;
          }

          if (isPickupAnimPhase) {
            int delta;
            if (moby->m_AnimationState.m_NextFrame >= 7) {
              moby->m_Substate++;
            }

            if (2 < moby->m_Rotation.y && moby->m_Rotation.y < 254) {
              delta = -moby->m_Rotation.y;
              if (delta > 2) {
                delta = 2;
              }
              if (delta < -2) {
                delta = -2;
              }
              moby->m_Rotation.y = moby->m_Rotation.y + delta;
            }
          }

          VecSub(&vec, &vec, &moby->m_Position);
          dist = VecMagnitude(&vec, 1);

          if (isPickupAnimPhase == 0) {
            if (TICK_TIMER(sparxProps->m_Timer) ||
                (sparxProps->m_Timer < 80 &&
                 func_80017908((moby->m_Rotation.z + (bp->m_0x00 * 110)) & 0xFF,
                               ((g_Camera.m_Rotation.z >> 4) + 0x80) & 0xFF) <
                     8)) {
              if (moby->m_AnimationState.m_NextAnimation !=
                  moby->m_AnimationState.m_NextAnimation + 1) {
                g_AnimationFinished = 0;
                MOBY_ANIM_ADVANCE(moby,
                                  moby->m_AnimationState.m_NextAnimation + 1);
              }
            }
          }
          targetSpeed = isPickupAnimPhase ? 150 : 130;
          if (targetSpeed + 5 < dist) {
            VecScaleToLength(&vec, dist, targetSpeed + 5);
          } else {
            VecScaleToLength(&vec, dist, targetSpeed - 5);
          }
          VecAdd(&moby->m_Position, &moby->m_Position, &vec);
          RotateMobyToAngle(moby, Atan2(vec.x, vec.y, 0), 0xA, 0, 0);
          pitchAngle = Atan2(VecMagnitude(&vec, 0), vec.z, 0);
          moby->m_Rotation.y = pitchAngle;
          moby->m_Rotation.y = func_80038098(pitchAngle, 0, 0x30);
          break;
        }
        case 1: {
          g_Spyro.m_health++;
          PlaySound(g_Spu.m_SoundTable->gemPickup, moby, 0x10, nullptr);
          moby->m_Substate++;
          func_80052568(sparxProps->m_Target);
          break;
        }
        case 2: {
          if (g_AnimationFinished) {
            if (moby->m_AnimationState.m_NextAnimation !=
                moby->m_AnimationState.m_NextAnimation - 1) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby,
                                moby->m_AnimationState.m_NextAnimation - 1);
            }
            sparxProps->m_Target = nullptr;
            moby->m_Substate = 0;
          }
          break;
        }
        case 4: {
          MobyCollectableProps *cp = sparxProps->m_Target->m_Props;
          Vector3D sparxChaseDelta;
          int dist;

          VecSub(&sparxChaseDelta, &sparxProps->m_Target->m_Position,
                 &moby->m_Position);
          dist = VecMagnitude(&sparxChaseDelta, 1);

          if (dist < 512) {
            cp->m_Ticks = 0;
            cp->m_RotY = rand() & 0xE;
            cp->m_RotZ = rand() & 0xE;
            cp->m_RotationTicks = rand() & 0xE;

            VecCopy(&cp->m_InitPos, &sparxProps->m_Target->m_Position);
            sparxProps->m_Target->m_Substate = 3;

            if (sparxProps->m_Target->m_Class == 14)
              g_SpawnParticle(1, 12, moby, D_8006E494);
            else if (sparxProps->m_Target->m_Class == 15)
              g_SpawnParticle(1, 12, moby, D_8006E490);
            else
              g_SpawnParticle(
                  1, 12, moby,
                  D_8006E47C[sparxProps->m_Target->m_Class - MOBYCLASS_GEM_1]);

            sparxProps->m_Target = nullptr;
            if (!IsMobyPlayingSound(moby, g_Spu.m_SoundTable->pickupDing)) {
              g_Spu.m_NextSoundOverrideFlags = 1;
              g_Spu.m_VolumeOverride.right = 0x3600;
              g_Spu.m_VolumeOverride.left = 0x3600;
              PlaySound(g_Spu.m_SoundTable->pickupDing, moby, 8,
                        &moby->m_SoundChannel);
            }
          } else {
            // i don't really get this, we already know dist >= 512
            // here...maybe some sort of inline
            int dcheck = 310;

            if (dcheck < dist)
              VecScaleToLength(&sparxChaseDelta, dist, 310);
            else
              VecScaleToLength(&sparxChaseDelta, dist, 290);

            VecAdd(&moby->m_Position, &moby->m_Position, &sparxChaseDelta);
            RotateMobyToAngle(moby,
                              Atan2(sparxChaseDelta.x, sparxChaseDelta.y, 0),
                              0xA, 0, 0);

            moby->m_Rotation.y =
                Atan2(VecMagnitude(&sparxChaseDelta, 0), sparxChaseDelta.z, 0);
            moby->m_Rotation.y = func_80038098(moby->m_Rotation.y, 0, 0x30);
          }
          break;
        }
        }
      } else {
        moby->m_RenderRadius = 0x10;
        if (sparxProps->m_Timer <= 0) {
          sparxPosition.x = -600;
          sparxPosition.y = (rand() & 0x310) - 0x188;
          if (g_Camera.m_State == 3) {
            // 100 - 227
            sparxPosition.z = (rand() & 0x7F) + 100;
          } else {
            // -200 - 311
            sparxPosition.z = (rand() & 0x1FF) - 200;
          }
          sparxProps->m_SpyroOffset.x = sparxPosition.x;
          sparxProps->m_SpyroOffset.y = sparxPosition.y;
          sparxProps->m_SpyroOffset.z = sparxPosition.z;
          sparxProps->m_Timer = rand() & 0x7B;
        } else {
          sparxProps->m_Timer -= g_DeltaTime;
          if (g_Camera.m_State == 3) {
            sparxPosition.x = sparxProps->m_SpyroOffset.x +
                              (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >> 2);
            sparxPosition.y = sparxProps->m_SpyroOffset.y;
            sparxPosition.z = sparxProps->m_SpyroOffset.z;
            if (sparxPosition.z < 100)
              sparxPosition.z = 100;
          } else {
            if (g_Camera.m_State == 0x80000009)
              sparxPosition.x = sparxProps->m_SpyroOffset.x - 512;
            else {
              sparxPosition.x = sparxProps->m_SpyroOffset.x;
            }
            sparxPosition.y = sparxProps->m_SpyroOffset.y;
            sparxPosition.z = sparxProps->m_SpyroOffset.z;
          }
          VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &sparxPosition,
                            &sparxPosition);
          VecAdd(&sparxPosition, &sparxPosition, &g_Spyro.m_Position);
          VecSub(&sparxPosition, &sparxPosition, &moby->m_Position);
          VecShiftRight(&sparxPosition, 2);
          VecAdd(&moby->m_Position, &moby->m_Position, &sparxPosition);

          if (func_8004BE4C(&moby->m_Position, 0x100, 0x100)) {
            VecCopy(&moby->m_Position, &g_CollisionPoint);
          }

          if (sparxPosition.z > 32)
            sparxPosition.z = 32;
          if (sparxPosition.z < -32)
            sparxPosition.z = -32;
          moby->m_Rotation.x = 0;
          moby->m_Rotation.y = sparxPosition.z;
          RotateMobyToAngle(moby, g_Spyro.m_bodyRotation.z, 4, 0, 0);
        }

        switch (g_Spyro.m_health) {
        case 1:
          if (moby->m_AnimationState.m_NextAnimation != 0) {
            if (moby->m_AnimationState.m_Animation != 0) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 0);
            }
          }
          break;
        case 2:
          if (moby->m_AnimationState.m_NextAnimation != 2) {
            if (moby->m_AnimationState.m_Animation != 2) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 2);
            }
          }

          break;
        case 3:
          if (moby->m_AnimationState.m_NextAnimation != 4) {
            if (moby->m_AnimationState.m_Animation != 4) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 4);
            }
          }
          break;
        }
      }
      func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
      break;
    }
#ifdef HAS_MOBY_122
    case 122: {
      Moby122Props *props = moby->m_Props;

      if (moby->m_DamageFlags &
          (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) {
        moby->m_Substate |= 3;
        moby->m_DamageFlags = 0;

        if (moby->m_State < 3) {
          g_SpawnMoby(124, moby);
          moby->m_State = 3;
          MOBY_ANIM_RESTART(moby, 3);
          continue;
        }
      }

      moby->m_DamageFlags = 0;

      if (moby->m_Substate & 1) {
        if (props->m_0x08 == nullptr) {
          if ((props->m_0x08 = func_80058AE8()) != nullptr) {
            props->m_0x08->m_MobyPos = &props->m_0x0c;
            props->m_0x08->m_Radius = 0x40;
            props->m_0x08->m_PosOffset.x = 0;
            props->m_0x08->m_PosOffset.y = 0;
            props->m_0x08->m_PosOffset.z = 0;
            props->m_0x08->m_GlowColor.r = 192;
            props->m_0x08->m_GlowColor.g = 192;
            props->m_0x08->m_GlowColor.b = 96;
            props->m_0x08->m_OtOffset = -8;
          }
        } else {
          props->m_0x08->m_Radius += 0x20;
          if (props->m_0x08->m_Radius > 0x800) {
            props->m_0x08->m_Radius = 0x800;
          }

          if (props->m_0x18 >= 0 && props->m_0x08->m_Radius >= 0x300 &&
              (((func_8002B3F4(props->m_0x18) >> 8) & 0xFF) < 0xB)) {
            func_8002B390(props->m_0x18, 0xFC, 0);
          }
        }
      } else if (props->m_0x08 != 0) {
        props->m_0x08->m_Radius -= 0x40;

        if (props->m_0x08->m_Radius <= 0x400 && props->m_0x18 >= 0 &&
            (((func_8002B3F4(props->m_0x18) >> 8) & 0xFF) > 0)) {
          func_8002B390(props->m_0x18, 0xFC, 0);
        }

        if (props->m_0x08->m_Radius <= 0) {
          func_80058B60(props->m_0x08);
          props->m_0x08 = 0;
        }
      }
      if (props->m_0x08 != 0) {
        Vector3D pos0;
        Vector3D pos1;

        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        func_80052D64(moby, 0, &pos0);
        func_80052D64(moby, 1, &pos1);
        VecAdd(&props->m_0x0c, &pos0, &pos1);
        VecShiftRight(&props->m_0x0c, 1);
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x00 == 0) {
          if (TICK_TIMER(props->m_0x04) && !(moby->m_Substate & 4)) {
            props->m_0x04 = 0x78;
            moby->m_Substate &= 0xFD;

            if (moby->m_Substate & 1) {
              if (props->m_0x18 >= 0) {
                func_8002B390(props->m_0x18, 0xFC, 0);
              }

              moby->m_State = 1;
              MOBY_ANIM_CHANGE(moby, 1);
              continue;
            } else {
              moby->m_State = 2;
              MOBY_ANIM_CHANGE(moby, 2);
              continue;
            }
          }
        } else {
          moby->m_Substate |= 2;
        }
        break;

      case 1:
        moby->m_Substate &= ~1;

        if (g_AnimationFinished) {
          moby->m_Substate |= 2;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 2:
        moby->m_Substate |= 1;

        if (g_AnimationFinished) {
          if (props->m_0x18 >= 0) {
            func_8002B390(props->m_0x18, 0xFC, 0);
          }

          moby->m_Substate |= 2;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 3:
        if (g_AnimationFinished) {
          props->m_0x04 = 450;
          moby->m_State = 4;
          MOBY_ANIM_SET_NEXT(moby, 4);
          continue;
        }
        break;

      case 4:
        if (TICK_TIMER(props->m_0x04)) {
          Moby *spawn = g_SpawnMoby(124, moby);

          moby->m_State = 5;
          spawn->m_State = 1;
          MOBY_ANIM_RESTART(spawn, 1);
          continue;
        }
        break;

      case 5:
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_124
    case 124: {
      Moby124Props *props = moby->m_Props;

      switch (moby->m_State) {
      case 0:
        if (g_AnimationFinished) {
          func_80052568(moby);
        }
        break;

      case 1:
        if (g_AnimationFinished) {
          func_80052568(moby);
          props->m_0x00->m_State = 0;
          MOBY_ANIM_RESTART(props->m_0x00, 0);
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_126 // Timer Fool
    case 126: {
      Moby126Props *props;
      int result;
      Vector3D vec11;
      Vector3D vec12;

      props = moby->m_Props;
      if (props->m_0x00 == 0) {
        props->m_0x00 = 1;
        props->m_0x08->m_CurrentNode = props->m_0x40;
        if (props->m_0x04 == 6) {
          func_80052568(moby);
          break;
        }
        if (props->m_0x04 != 0) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          break;
        }
      }

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          (moby->m_State < 8 || moby->m_State == 99)) {
        moby->m_DamageFlags = 0;
        if (props->m_0x04 == 3) {
          Moby126Props *linkedProps = g_LevelMobys[props->m_0x54].m_Props;
          linkedProps->m_0x48 = 1;
          props->m_0x08->m_NodeCount -= 4;
          props->m_0x04 = 1;
        }
        moby->m_State = 8;
        MOBY_ANIM_RESTART(moby, 8);
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      func_8004D5EC(&moby->m_Position, 0x10000);
      func_800533D0(moby);

      switch (moby->m_State) {
      case 0:
        if (props->m_0x04 != 3) {
          if (DISTANCE_TO_SPYRO(moby) < 0x1000) {
            props->m_0x0c = 3;
            props->m_0x1c.x = 0xFF;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
          } else if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
            props->m_0x0c = 4;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
          }
        }
        break;
      case 1:
        if (g_AnimationFinished) {
          moby->m_State = props->m_0x0c;
          MOBY_ANIM_SET_NEXT(moby, props->m_0x0c);
        }
        break;
      case 2:
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (props->m_0x04 != 3) {
          if (DISTANCE_TO_SPYRO(moby) < 0x1000) {
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
          } else if (DISTANCE_TO_SPYRO(moby) < 0x2000 && g_AnimationFinished &&
                     (rand() & 4)) {
            moby->m_State = 4;
            MOBY_ANIM_SET_NEXT(moby, 4);
          }
        } else if (props->m_0x50 == 1) {
          func_80052D64(&g_LevelMobys[props->m_0x54], 1, &vec11);
          func_80052D64(&g_LevelMobys[props->m_0x54], 2, &vec12);
          moby->m_Position.x = vec11.x + ((vec12.x - vec11.x) >> 1);
          moby->m_Position.y = vec11.y + ((vec12.y - vec11.y) >> 1);
          moby->m_Position.z = vec11.z + ((vec12.z - vec11.z) >> 1);
          moby->m_Rotation.z = ANGLE_FROM(
              g_LevelMobys[props->m_0x54].m_Position, moby->m_Position);
        } else if (props->m_0x50 == 2) {
          Vector3D vec13;
          moby->m_Position.x +=
              FIXED_MUL(props->m_0x58, COSINE_8(moby->m_Rotation.z));
          moby->m_Position.y +=
              FIXED_MUL(props->m_0x58, SINE_8(moby->m_Rotation.z));
          VecCopy(&vec13, &moby->m_Position);
          if (func_8004BE4C(&vec13, 0x100, 0x100) != 0) {
            moby->m_State = 7;
            MOBY_ANIM_RESTART(moby, 7);
          } else {
            moby->m_Position.z += props->m_0x5c;
            props->m_0x5c += props->m_0x60;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 6);
          }
        }
        break;
      case 3:
        if (DISTANCE_TO_SPYRO(moby) < 0x1000) {
          if (TICK_TIMER(props->m_0x64)) {
            props->m_0x64 = (rand() % 0x20) + 100;
            func_8003851C(moby, (rand() % 3) + 2, 0);
          }
          func_8003BFC0(moby, props->m_0x08, &props->m_0x10,
                        (int *)&props->m_0x1c, 0x10, 0);
        } else if (func_8003BFC0(moby, props->m_0x08, &props->m_0x10,
                                 (int *)&props->m_0x1c, 0x16, 0) != 0) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
        }
        break;
      case 4:
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (DISTANCE_TO_SPYRO(moby) < 0x1000) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
        } else if (g_AnimationFinished && (rand() & 4)) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
        }
        break;
      case 7:
        if (g_AnimationFinished) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
          moby->m_State = 99;
        }
        break;
      case 8:
        result = func_8004D5EC(&moby->m_Position, 0x10000);
        if (result > 0x80 && result < 0x1800) {
          moby->m_Position.z -= 0x40;
        }
        RotateMobyToSpyro(moby, 4, 0, 0);
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
        if (g_AnimationFinished) {
          props->m_0x38 = props->m_0x34;
          switch (props->m_0x04) {
          case 0:
          case 1:
          case 3:
            func_8002B390(props->m_0x30, 0xFC, 0);
            break;
          case 2: {
            if (g_LevelMobys[props->m_0x44].m_State >= 6 &&
                ((Moby126Props *)g_LevelMobys[props->m_0x44].m_Props)->m_0x48 ==
                    0) {
              props->m_0x48 = 1;
            } else {
              props->m_0x38 = 450;
              func_8002B390(props->m_0x30, 0xFC, 0);
            }
            break;
          }
          case 4:
            if (((func_8002B3F4(1) >> 8) & 0xFF) > 0 ||
                !(func_8002B3F4(1) & 2)) {
              props->m_0x38 = 450;
              func_8002B390(2, 0xFC, 0);
              props->m_0x30 = 2;
            } else {
              props->m_0x38 = 450;
              func_8002B390(1, 0xFC, 0);
              props->m_0x30 = 1;
            }
            break;
          }
          func_8003851C(moby, 0, 0);
          moby->m_State = 9;
          MOBY_ANIM_SET_NEXT(moby, 9);
        }
        break;
      case 9:
        RotateMobyToSpyro(moby, 4, 0, 0);
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
        if (props->m_0x0c == 0x63) {
          moby->m_State = 12;
          MOBY_ANIM_CHANGE(moby, 12);
        } else {
          if (props->m_0x48 != 0 && (func_8002B3F4(props->m_0x30) & 2)) {
            props->m_0x48 = 0;
            props->m_0x38 = 330;
            func_8002B390(props->m_0x30, 0xFC, 0);
          }
          if (TICK_TIMER(props->m_0x38)) {
            props->m_0x38 = 0x50;
            func_8003851C(moby, 1, 0);
            moby->m_State = 10;
            MOBY_ANIM_CHANGE(moby, 10);
          }
        }
        break;
      case 10:
        if (props->m_0x0c == 99) {
          moby->m_State = 12;
          MOBY_ANIM_CHANGE(moby, 12);
        } else {
          switch (props->m_0x04) {
          case 0:
          case 1:
          case 3:
          case 4:
            if (TICK_TIMER(props->m_0x38)) {
              func_8002B390(props->m_0x30, 0xFC, 0);
              moby->m_State = 12;
              MOBY_ANIM_CHANGE(moby, 12);
            }
            break;
          case 2:
            if (TICK_TIMER(props->m_0x38)) {
              if (g_LevelMobys[props->m_0x44].m_State >= 6) {
                Moby126Props *linkedProps = g_LevelMobys[props->m_0x44].m_Props;
                linkedProps->m_0x0c = 99;
              }
              result = func_8002B3F4(props->m_0x30);
              if ((result & 2) && (((result >> 8) & 0xFF) < 0x14)) {
                func_8002B444(props->m_0x30, 0x1E, 0);
              }
              func_8002B390(props->m_0x30, 0xFC, 0);
              moby->m_State = 12;
              MOBY_ANIM_CHANGE(moby, 12);
            }
            break;
          }
        }
        break;
      case 12:
        func_800562A4(moby, 1);
        if (g_AnimationFinished) {
          props->m_0x0c = 2;
          moby->m_State = 2;
          moby->m_DamageFlags = 0;
          MOBY_ANIM_RESTART(moby, 2);
        }
        break;
      case 99:
        if (func_8003BFC0(moby, props->m_0x08, &props->m_0x10,
                          (int *)&props->m_0x1c, 0x10, 4) == 2) {
          Moby126Props *linkedProps;

          props->m_0x50 = 0;
          moby->m_Rotation.y = 0;
          linkedProps = g_LevelMobys[props->m_0x54].m_Props;
          linkedProps->m_0x40 = 1;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_129
    case 129: { // Lamp used in Dark Hollow and Dark
                // Passage
      switch (moby->m_State) {
      case 0: // Idle
        // Switch to shaking state if charged
        if (moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
        }
        break;
      case 1: // Shaking
        if (g_AnimationFinished) {
          moby->m_DamageFlags = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_130 // Slap-Happy Armored Monk
    case 130: {
      Moby130Props *props;
      int result;
      int distance;
      int angle;

      props = moby->m_Props;
      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 3) {
        if (!(props->m_0x10 == 1 &&
              (moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0)) {
          func_800562A4(moby, 1);
          props->m_0x08 = 150;
          props->m_0x00 = 0x118;
          if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
            props->m_0x00 = 380;
          }
          props->m_0x04 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
          moby->m_DamageFlags = 0;
          moby->m_CollisionRange = 0xFF;
          props->m_0x5c = RandRangeSigned(8, 0xE);
          moby->m_Substate = 0;
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c + 3);
          moby->m_State = 3;
          continue;
        }
      }

      if (props->m_0x38 == 0) {
        props->m_0x38 = 1;
        if (props->m_0x64 != 0 && moby->m_DropMoby == 0xFF) {
          props->m_0x10 = !props->m_0x10;
        }
        if (props->m_0x10 == 0) {
          props->m_0x0c = 4;
          if (moby->m_AnimationState.m_Animation != props->m_0x0c) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, props->m_0x0c);
          }
        }
      }

      if (moby->m_State < 3 &&
          (props->m_0x3c != 0 ||
           (moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) != 0)) {
        if (props->m_0x3c > 0 && (moby->m_State == 0 || moby->m_State == 2) &&
            (DISTANCE_TO_SPYRO(moby) < props->m_0x3c ||
             func_80038C4C(&g_Spyro.m_Position, &props->m_0x18) != 0) &&
            TICK_TIMER(props->m_0x4c)) {
          props->m_0x3c = -props->m_0x3c;
          if (props->m_0x3c == 0) {
            props->m_0x3c = -1;
          }
          g_LevelMobys[props->m_0x40].m_Substate = moby - g_LevelMobys;
          *(int *)g_LevelMobys[props->m_0x40].m_Props = props->m_0x44;
          props->m_0x4c = props->m_0x50;
          if (props->m_0x54 != -1) {
            ((int *)g_LevelMobys[props->m_0x54].m_Props)[19] = 0x28;
          }
          if (props->m_0x58 != -1) {
            ((int *)g_LevelMobys[props->m_0x58].m_Props)[19] = 0x50;
          }
        } else if ((moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) != 0) {
          moby->m_DamageFlags = 0;
          if ((props->m_0x34 & 4) != 0) {
            props->m_0x3c = -props->m_0x3c;
          } else {
            props->m_0x3c = 0;
          }
          if (props->m_0x10 == 0) {
            props->m_0x10 = !props->m_0x10;
            func_800385BC(moby, 0x28);
            moby->m_ScaleOverride = 0x40;
            props->m_0x0c = 0;
            if (moby->m_AnimationState.m_Animation != props->m_0x0c) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, props->m_0x0c);
            }
            moby->m_State = 10;
            continue;
          } else {
            props->m_0x10 = !props->m_0x10;
            moby->m_ScaleOverride = 0x20;
            moby->m_State = 20;
            continue;
          }
        } else if (props->m_0x3c < 0) {
          TICK_TIMER(props->m_0x4c);
        }
      }

      moby->m_DamageFlags = 0;
      switch (moby->m_State) {
      case 0: {
        if ((props->m_0x34 & 2) != 0 &&
            DISTANCE_TO_SPYRO(moby) < props->m_0x48) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c + 1);
          moby->m_State = 1;
          continue;
        }

        RotateMobyToSpyro(moby, 4, 0, 0);
        if (!TICK_TIMER(props->m_0x14)) {
          break;
        }
        if (SPYRO_BASE_Z_DISTANCE(moby) < 0x190) {
          if (props->m_0x10 == 0) {
            if (DISTANCE_TO_SPYRO(moby) < 1200) {
              moby->m_State = 2;
              continue;
            }
          } else if (props->m_0x10 == 1) {
            if (DISTANCE_TO_SPYRO(moby) < 8000) {
              moby->m_State = 2;
              continue;
            }
          }
        }
        break;
      }

      case 1: {
        props->m_0x34 &= ~2;
        if (DISTANCE_TO_SPYRO(moby) >= 0xC00) {
          if (func_80039E94(moby, props->m_0x30, 0x100, 0x8C, 0, 8, 0x28, 0xFF,
                            5) != 0x100) {
            break;
          }
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c);
        moby->m_State = 0;
        continue;
      }

      case 2: {
        if (props->m_0x10 == 0) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c + 2);
          RotateMobyToSpyro(moby, 6, 0, 0);
          g_Spyro.unk_0x208.x = FIXED_MUL(COSINE_8(moby->m_Rotation.z), 140);
          g_Spyro.unk_0x208.y = FIXED_MUL(SINE_8(moby->m_Rotation.z), 140);
          g_Spyro.unk_0x208.z = 70;
          if (g_AnimationFinished) {
            props->m_0x14 = 0x78;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c);
            moby->m_State = 0;
            continue;
          }
          break;
        }

        distance = DISTANCE_TO_SPYRO(moby);
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c + 2);
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_AnimationFinished || distance >= 0x2711) {
          props->m_0x14 = 150;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x0c);
          moby->m_State = 0;
          continue;
        }
        if (distance < 0x6A4 &&
            moby->m_AnimationState.m_Animation ==
                moby->m_AnimationState.m_NextAnimation &&
            moby->m_AnimationState.m_NextFrame < 0xE) {
          moby->m_AnimationState.m_Frame = 0x10;
          moby->m_AnimationState.m_NextFrame = 0x11;
          moby->m_AnimationState.m_FrameProgress = 0;
        }
        if (moby->m_AnimationState.m_NextFrame == 0xF) {
          moby->m_AnimationState.m_Frame = 5;
          moby->m_AnimationState.m_NextFrame = 6;
          moby->m_AnimationState.m_FrameProgress = 0;
        }
        if (moby->m_AnimationState.m_NextFrame == 6) {
          if (IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[0]) ==
              0) {
            func_8003851C(moby, 0, &props->m_0x68);
          }
        }
        break;
      }

      case 3: {
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }

        moby->m_Rotation.z += props->m_0x5c;
        moby->m_Substate++;
        if (moby->m_Substate >= 3) {
          if (props->m_0x5c > 0) {
            props->m_0x5c--;
            if (props->m_0x5c < 0) {
              props->m_0x5c = 0;
            }
          } else if (props->m_0x5c < 0) {
            props->m_0x5c++;
            if (props->m_0x5c > 0) {
              props->m_0x5c = 0;
            }
          }
        }

        result = MoveMobyWithGravity(moby, &props->m_0x00, props->m_0x04,
                                     &props->m_0x08, 0xC, 0x10);
        if (result == 3 && moby->m_AnimationState.m_NextFrame <= 9) {
          g_AnimationFinished = 0;
          moby->m_AnimationState.m_FrameProgress = 0x10;
          moby->m_AnimationState.m_PerFrameProgress = 0x10;
          moby->m_AnimationState.m_Animation =
              moby->m_AnimationState.m_NextAnimation;
          moby->m_AnimationState.m_NextAnimation =
              moby->m_AnimationState.m_NextAnimation;
          moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
          moby->m_AnimationState.m_NextFrame = 0xA;
          func_80037E98(moby);
        }
        if (result == 0 && moby->m_AnimationState.m_NextFrame == 9) {
          g_AnimationFinished = 0;
          moby->m_AnimationState.m_FrameProgress = 0x10;
          moby->m_AnimationState.m_PerFrameProgress = 0x10;
          moby->m_AnimationState.m_Animation =
              moby->m_AnimationState.m_NextAnimation;
          moby->m_AnimationState.m_NextAnimation =
              moby->m_AnimationState.m_NextAnimation;
          moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
          moby->m_AnimationState.m_NextFrame = 5;
          func_80037E98(moby);
        }
        if (ABS2(moby->m_AnimationState.m_NextFrame -
                 moby->m_AnimationState.m_Frame) < 3) {
          moby->m_AnimationState.m_PerFrameProgress =
              g_Models[moby->m_Class]
                  ->m_Animations[moby->m_AnimationState.m_Animation]
                  ->m_ProgressPerTick;
        }
        break;
      }
      case 10: {
        TICK_TIMER(props->m_0x4c);
        moby->m_ScaleOverride -= g_DeltaTime * 2;
        if (moby->m_ScaleOverride < 0x21) {
          moby->m_ScaleOverride = 0x20;
          moby->m_State = 0;
          continue;
        }
        break;
      }

      case 20: {
        TICK_TIMER(props->m_0x4c);
        moby->m_ScaleOverride += g_DeltaTime * 2;
        if (moby->m_ScaleOverride >= 0x38) {
          func_800562A4(moby, 1);
          moby->m_ScaleOverride = 0x20;
          func_800385BC(moby, 0x20);
          props->m_0x0c = 4;
          if (moby->m_AnimationState.m_Animation != props->m_0x0c) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, props->m_0x0c);
          }
          moby->m_State = 0;
          continue;
        }
        break;
      }

      case 30: {
        Moby *linkedMoby;

        linkedMoby = &g_LevelMobys[props->m_0x40];
        DISTANCE_TO_SPYRO(moby);
        angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
        result = func_80038074(ANGLE_TO_SPYRO(linkedMoby->m_Position), 0x80);
        func_80038638(moby, &linkedMoby->m_Position, 1500, result, 4, 0x32, 0xE,
                      0x80, 0xFF, 0xFF, 0, 0, 0xD);
        RotateMobyToAngle(linkedMoby, angle, 4, 0, 0);
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_134
    case 134: {
      Moby134Props *props = moby->m_Props;

      ApplyFlameHeat(moby);
      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 3) {
        Moby135Props *projectileProps;
        Moby *projectile;

        props->m_0x04 = 350;
        props->m_0x00 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x08 = 0x8C;
        props->m_0x28 = 0x3C;
        moby->m_DamageFlags = 0;

        projectile = g_SpawnMoby(135, moby);
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        func_80052D64(moby, 0, &projectile->m_Position);
        projectile->m_Rotation.z = moby->m_Rotation.z;
        projectileProps = projectile->m_Props;
        projectileProps->m_0x07 = 1;
        projectileProps->m_0x0a = 0;
        projectileProps->m_0x00 =
            FIXED_MUL(COSINE_8((props->m_0x00 - 10) & 0xFF), 300);
        projectileProps->m_0x02 =
            FIXED_MUL(SINE_8((props->m_0x00 - 10) & 0xFF), 300);
        projectileProps->m_0x04 = 220;
        projectileProps->m_0x10 = RandRangeSigned(7, 0xF);
        projectileProps->m_0x11 = RandRangeSigned(7, 0xF);
        projectileProps->m_0x12 = RandRangeSigned(7, 0xF);
        projectileProps->m_0x0c = -0xC;

        if (props->m_0x0c & 2) {
          g_LevelMobys[props->m_0x38].m_Substate = 1;
        }

        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        continue;
      }

      moby->m_DamageFlags = 0;
      switch (moby->m_State) {
      case 0:
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (props->m_0x0c & 1) {
          if ((SPYRO_BASE_Z_DISTANCE(moby) < 500 &&
               DISTANCE_TO_SPYRO(moby) < props->m_0x2c) ||
              (props->m_0x40 != -1 &&
               g_LevelMobys[props->m_0x40].m_State >= 0x80) ||
              func_80038C4C(&g_Spyro.m_Position, &props->m_0x10) != 0) {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        }

        if (props->m_0x0c & 2) {
          moby->m_State = 4;
          continue;
        }

        if (TICK_TIMER(props->m_0x28) && g_ScreenBorderEnabled == 0 &&
            DISTANCE_TO_SPYRO(moby) < props->m_0x30 &&
            SPYRO_BASE_Z_DELTA(moby) < 200 &&
            func_80038250(&moby->m_Position) != 0) {
          moby->m_State = 2;
          moby->m_Substate = 0;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        break;

      case 1:
        props->m_0x0c &= ~1;
        if (props->m_0x2c != 0 && DISTANCE_TO_SPYRO(moby) < 0x1400) {
          moby->m_State = 2;
          moby->m_Substate = 0;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        if (func_80039E94(moby, props->m_0x34, 0x100, 0x8C, 0, 8, 0x28, 0xFF,
                          5) == 0x100) {
          moby->m_State = 10;
          continue;
        }
        break;

      case 2:
        RotateMobyToSpyro(moby, 8, 0, 0);
        if (moby->m_AnimationState.m_NextFrame >= 0x1A &&
            g_ScreenBorderEnabled == 0 && moby->m_Substate == 0) {
          Moby135Props *projectileProps;
          Moby *projectile;

          projectile = g_SpawnMoby(135, moby);
          moby->m_Substate = 1;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 0, &projectile->m_Position);
          projectile->m_Rotation.z = ANGLE_TO_SPYRO(projectile->m_Position);
          projectileProps = projectile->m_Props;
          projectileProps->m_0x07 = 0;
          projectileProps->m_0x0a = 0;
          projectileProps->m_0x00 =
              FIXED_MUL(COSINE_8(projectile->m_Rotation.z), 300);
          projectileProps->m_0x02 =
              FIXED_MUL(SINE_8(projectile->m_Rotation.z), 300);
          projectileProps->m_0x04 = 0;
          projectileProps->m_0x10 = RandRangeSigned(7, 0xF);
          projectileProps->m_0x11 = RandRangeSigned(7, 0xF);
          projectileProps->m_0x12 = RandRangeSigned(7, 0xF);
          projectileProps->m_0x0c = 0;
          projectileProps->m_0x0e = 0;
        }

        if (g_AnimationFinished) {
          moby->m_Substate = 0;
          props->m_0x28 = 0x28;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 3:
        MoveMobyWithGravity(moby, &props->m_0x04, props->m_0x00, &props->m_0x08,
                            0xC, 0x10);
        if (g_AnimationFinished &&
            moby->m_AnimationState.m_NextAnimation == 3 &&
            moby->m_AnimationState.m_Animation != 4) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 4);
        }
        if (TICK_TIMER(props->m_0x28)) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 4: {
        int speed = 0x78;
        int distance = OctDistance(&moby->m_Position,
                                   &g_LevelMobys[props->m_0x38].m_Position);

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (distance < 2700) {
          speed = 100;
        } else if (distance > 3200) {
          speed = 0x8C;
        }

        RotateMobyToAngle(moby,
                          ANGLE_FROM(moby->m_Position,
                                     g_LevelMobys[props->m_0x38].m_Position),
                          4, 0, 0);
        func_80039398(moby, speed, 0, 0, 5);
        if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x10) != 0) {
          props->m_0x44 = 1;
        }
        if (props->m_0x44 != 0) {
          props->m_0x0c = 1;
          g_LevelMobys[props->m_0x38].m_Substate = 1;
          moby->m_State = 0;
          continue;
        }
        break;
      }

      case 10:
        if (RotateMobyToSpyro(moby, 5, 2, 1) != 0) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_135
    case 135: {
      Moby135Props *props = moby->m_Props;
      Vector3D work;
      Vector3D padVec;
      int hitSpyro = 0;
      int i;
      Vector3D particleVelocity;
      Vector3D particlePosition;

      if (moby->m_State == 0) {

        if (props->m_0x0c != 0) {
          props->m_0x04 += props->m_0x0c;
          if (props->m_0x04 < -0xF0) {
            props->m_0x04 = -0xF0;
          }
        } else {
          int floorZ = func_80038340(moby);
          int height = moby->m_Position.z - 120;
          props->m_0x04 = floorZ - height;
          if (props->m_0x04 > 0x28) {
            props->m_0x04 = 0x28;
          }
          if (props->m_0x04 < -0x28) {
            props->m_0x04 = -0x28;
          }
          if (ABS2(props->m_0x04) < 0x1E) {
            props->m_0x04 = 0;
          }
          if (props->m_0x0a >= 0x29) {
            props->m_0x04 = 0;
          }
        }

        work.x = 0;
        work.y = 0;
        work.z = 0;
        g_SpawnParticle(1, 1, &moby->m_Position, (int)&work);
        VecCopy(&work, &moby->m_Position);

        moby->m_Position.x += props->m_0x00;
        moby->m_Position.y += props->m_0x02;
        moby->m_Position.z += props->m_0x04;
        moby->m_Rotation.x += props->m_0x10;
        moby->m_Rotation.y += props->m_0x11;
        moby->m_Rotation.z += props->m_0x12;
        props->m_0x0a += g_DeltaTime;

        if (props->m_0x07 == 0) {
          hitSpyro = func_8004E2E8(&moby->m_Position, 0xDC, 0x86);
        }

        if (moby->m_Substate != 2 && props->m_0x0a < 0x5B && hitSpyro == 0 &&
            func_8004AE38(&work, &moby->m_Position) == 0) {
          break;
        }

        if (hitSpyro != 0) {
          g_Spyro.unk_0x208.x = props->m_0x00 >> 2;
          g_Spyro.unk_0x208.y = props->m_0x02 >> 2;
          g_Spyro.unk_0x208.z = 0x28;
        }

        func_8003851C(moby, 0, 0);
        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(458, moby);
          g_SpawnMoby(459, moby);
        }

        for (i = 0; i < 18; i++) {
          particleVelocity.x = RandRange(-90, 90);
          particleVelocity.y = RandRange(-90, 90);
          particleVelocity.z = RandRange(-25, 60);
          VecCopy(&particlePosition, &particleVelocity);
          VecShiftLeft(&particlePosition, 2);
          VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
          g_SpawnParticle(1, 13, &particlePosition, (int)&particleVelocity);
        }
        g_SpawnParticle(10, 70, &moby->m_Position, 0x10);
        func_80052568(moby);
      }

      break;
    }
#endif
#ifdef HAS_MOBY_136
    case 136: {
      Moby136Props *props = moby->m_Props;
      Moby **child;
      int i;

      if (props->m_0x14 == 0) {
        int side;

        props->m_0x14 = 1;
        i = 0;
        child = props->m_0x00;
        side = -1;
        for (; i < 4; i++, child++) {
          int offset = 400;
          int angle = (moby->m_Rotation.z + 0x40) & 0xFF;

          *child = g_SpawnMoby(132, moby);
          VecCopy(&(*child)->m_Position, &moby->m_Position);
          if (i < 2) {
            offset *= side;
          } else {
            offset *= i - 1;
          }
          (*child)->m_Position.x += FIXED_MUL(offset, COSINE_8(angle));
          (*child)->m_Position.y += FIXED_MUL(offset, SINE_8(angle));
          side--;
          func_800529E4(*child, 2);
        }

        if (props->m_0x10 == 1 && moby->m_AnimationState.m_Animation != 1) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 1);
        }
      }

      if (props->m_0x10 == 1) {
        props->m_0x18 = ApplyFlameHeatExternal(moby, props->m_0x18);
      }

      moby->m_DamageFlags = 0;
      for (i = 0; i < 4; i++) {
        moby->m_DamageFlags |= props->m_0x00[i]->m_DamageFlags;

        if (props->m_0x00[i]->m_DamageFlags != 0) {
          int variant = props->m_0x10;

          if (variant != 1 ||
              (props->m_0x00[i]->m_DamageFlags & MOBY_DAMAGE_SUPER) != 0) {
            int angle = moby->m_Rotation.z;
            int speed = 100;
            Vector3D particleVelocity;
            Vector3D particlePosition;

            if (variant == 1) {
              func_8003851C(moby, 1, 0);
            } else {
              func_8003851C(moby, 0, 0);
            }
            if (func_80017908(moby->m_Rotation.z,
                              ANGLE_TO_SPYRO(moby->m_Position)) < 0x40) {
              angle = (angle + 0x80) & 0xFF;
            }

            if (props->m_0x00[i]->m_DamageFlags & MOBY_DAMAGE_CHARGE) {
              speed += 80;
            } else if (props->m_0x00[i]->m_DamageFlags & MOBY_DAMAGE_SUPER) {
              speed += 240;
            }

            particleVelocity.x = 0;
            particleVelocity.y = 0;
            particleVelocity.z = 0;

            for (i = 0; i < 9; i++) {
              Moby *fragment = g_SpawnMoby(133, moby);
              MobyFragmentProps *fragmentProps = fragment->m_Props;
              int column;
              int positionAngle;
              int row;
              int radialOffset;
              int j;

              if (props->m_0x10 == 1) {
                if (fragment->m_AnimationState.m_Animation != 1) {
                  MOBY_ANIM_RESTART(fragment, 1);
                }
                fragment->m_Renderer.raw = 0xA0;
                ((int *)&fragment->m_SpecularMetalColor)[0] = 0xA18618;
              }

              column = (i % 3) - 1;
              row = i / 3;
              positionAngle = (moby->m_Rotation.z + 0x40) & 0xFF;
              radialOffset = column * 800;
              fragment->m_Position.x +=
                  FIXED_MUL(radialOffset, COSINE_8(positionAngle));
              fragment->m_Position.y +=
                  FIXED_MUL(radialOffset, SINE_8(positionAngle));
              fragment->m_Position.z =
                  fragment->m_Position.z - 1100 + row * 700;

              for (j = 0; j < 6; j++) {
                VecCopy(&particlePosition, &fragment->m_Position);
                particlePosition.x += RandRange(-400, 400);
                particlePosition.y += RandRange(-400, 400);
                particlePosition.z += RandRange(-400, 400);
                g_SpawnParticle(1, 1, &particlePosition,
                                (int)&particleVelocity);
              }

              fragment->m_ScaleOverride = RandRange(0, 12) + 36;
              fragmentProps->m_Velocity.x += FIXED_MUL(speed, COSINE_8(angle));
              fragmentProps->m_Velocity.y += FIXED_MUL(speed, SINE_8(angle));
              fragmentProps->m_Lifetime -= 20;
            }

            for (i = 0; i < 4; i++) {
              func_80052568(props->m_0x00[i]);
            }
            func_8003B854(0, moby);
            func_8003B7C0(moby);
            func_80052568(moby);
            continue;
          }
        }
        props->m_0x00[i]->m_DamageFlags = 0;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_137
    case 137: {
      Moby137Props *props = moby->m_Props;
      int angle;
      int targetAngle;
      int i;
      Moby **scan;
      Moby *other;
      Vector3D *activationPos;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 2) {
        props->m_0x20 = func_80038098(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20);
        props->m_0x24 = 0xFA;
        props->m_0x28 = 0;
        if (moby->m_State != 0) {
          *props->m_0x40 = 0;
        }
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        break;
      }

      if (props->m_0x54 == 0) {
        props->m_0x54 = 1;
        if (props->m_0x58 != 0 && DISTANCE_TO_SPYRO(moby) < 0x2000) {
          if (moby->m_DropMoby != 0xFF) {
            func_8003ABC0(moby, 1, 0, 0);
            func_8003B7C0(moby);
          }
          func_80052568(moby);
          continue;
        }
      }

      if (!TICK_TIMER(props->m_0x3c)) {
        int cameraDistance = DISTANCE_TO_SPYRO(moby) + 0x1000;
        if (props->m_0x34 < cameraDistance) {
          props->m_0x34 = cameraDistance;
        }
        g_Spyro.m_ControlFlags = 0x80000200;
        D_80078668.m_Coords.azimuth = -ANGLE_TO_SPYRO(moby->m_Position) << 4;
        D_80078668.m_Coords.radius = props->m_0x34;
      }

      switch (moby->m_State) {
      case 0: {
        TICK_TIMER(props->m_0x2c);

        switch (props->m_0x00) {
        case 0: {
          RotateMobyToSpyro(moby, 0xA, 0, 0);
          break;
        }

        case 1: {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

          if (props->m_0x24 < 150) {
            props->m_0x24 = 150;
          }

          if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x18)) <
              0x100) {
            PathData *path = props->m_0x18;
            do {
              i = RandRange(0, path->m_NodeCount - 1);
              path = props->m_0x18;
            } while (i == path->m_CurrentNode);
            path->m_CurrentNode = i;
            props->m_0x24 = RandRange(0xB4, 0xE6);
          }

          targetAngle =
              ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x18));
          if (RotateMobyToAngle(moby, targetAngle, 6, 0x1E, 1) != 0) {
            func_80039398(moby, props->m_0x24, 0, 0, 5);
          }
          break;
        }

        case 2: {
          if (props->m_0x44 == 0) {
            props->m_0x44 = OctDistance(&moby->m_Position,
                                        &PATH_NODE_POS(props->m_0x18, 0));
          }
          break;
        }

        case 3: {
          int speed = 0xA0;
          int distance = OctDistance(&moby->m_Position,
                                     &g_LevelMobys[props->m_0x48].m_Position);

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

          if (distance < 4000) {
            speed = 0x8C;
          } else if (distance > 6000) {
            speed = 0xB4;
          }

          targetAngle = ANGLE_FROM(moby->m_Position,
                                   g_LevelMobys[props->m_0x48].m_Position);
          RotateMobyToAngle(moby, targetAngle, 4, 0, 0);
          func_80039398(moby, speed, 0, 0, 5);
          break;
        }
        }

        if (props->m_0x00 == 1 || props->m_0x00 == 3) {
          activationPos = &PATH_NODE_POS(props->m_0x18, 0);
        } else {
          activationPos = &moby->m_Position;
        }

        if (props->m_0x00 == 2) {
          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x18, 1)) < 1500 ||
              OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x18, 2)) < 1500) {
            props->m_0x50 = 0;
            moby->m_State = 1;
            continue;
          }
          break;
        }

        if (props->m_0x2c == 0 && *props->m_0x40 == 0 &&
            g_Spyro.m_airTime == 0) {
          if (SPYRO_BASE_Z_DISTANCE(moby) < 800) {
            if (OctDistance(activationPos, &g_Spyro.m_Position) <
                (props->m_0x14 << 10)) {
              *props->m_0x40 = 1;
              props->m_0x10 = 0;
              props->m_0x50 = 0;
              if (props->m_0x00 == 3) {
                props->m_0x00 = 1;
                VecCopy(&props->m_0x04, activationPos);
              }
              moby->m_State = 1;
              continue;
            }
          }
        }

        break;
      }

      case 1: {
        int distance = DISTANCE_TO_SPYRO(moby);

        if (TICK_TIMER(props->m_0x10)) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

          if (props->m_0x00 == 2) {
            angle = ANGLE_TO_SPYRO(PATH_NODE_POS(props->m_0x18, 0));
            func_80038638(moby, &PATH_NODE_POS(props->m_0x18, 0), props->m_0x44,
                          angle, 8, 300, 0xE, 8, 0xFF, 0xFF, 0, 0, 0);

            if (distance < 3800) {
              props->m_0x24 = 0xE6;
              props->m_0x30 = 0;
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
              continue;
            }
          } else {
            if (props->m_0x4c != 0) {
              scan = (Moby **)(g_SonyImage.u.m_Buf + 0x400);
              while ((other = *scan++) != nullptr) {
                if (other->m_Class == 403 || other->m_Class == props->m_0x4c) {
                  if (ABS2(moby->m_Position.x - other->m_Position.x) < 3000 &&
                      ABS2(moby->m_Position.y - other->m_Position.y) < 3000 &&
                      OctDistance(&moby->m_Position, &other->m_Position) <
                          2000 &&
                      func_80017908(moby->m_Rotation.z,
                                    ANGLE_FROM(moby->m_Position,
                                               other->m_Position)) < 0x19) {
                    other->m_DamageFlags |= MOBY_DAMAGE_SUPER;
                  }
                }
              }
            }

            if (TICK_TIMER(props->m_0x2c)) {
              props->m_0x20 = g_Spyro.m_bodyRotation.z;
              props->m_0x2c = 0x1E;
            }

            angle = ANGLE_FROM_SPYRO(moby->m_Position);
            props->m_0x28 = (angle - props->m_0x20 + 0x100) % 0x100;
            targetAngle =
                func_80038074(ANGLE_TO_SPYRO(moby->m_Position), props->m_0x28);

            angle = RotateMobyToAngle(moby, targetAngle, 5, 0x1E, 1);
            if (angle != 0 || props->m_0x50 != 0) {
              if (angle != 0) {
                props->m_0x50 = 1;
              }

              if (props->m_0x5c != 0) {
                angle = props->m_0x5c;
              } else {
                angle = 350;
              }
              if (func_80039398(moby, angle, 0, 300, 0x15) != 0) {
                *props->m_0x40 = 0;
                props->m_0x2c = 0x78;
                moby->m_State = 100;
                continue;
              }

              if (func_80017908(g_Spyro.m_bodyRotation.z,
                                ANGLE_FROM_SPYRO(moby->m_Position)) >= 0x3D ||
                  OctDistance(&moby->m_Position, &props->m_0x04) > 0x4000) {
                *props->m_0x40 = 0;
                props->m_0x2c = 0x78;
                moby->m_State = 100;
                continue;
              }

              if (distance < 3800) {
                if (func_80017908(moby->m_Rotation.z,
                                  ANGLE_TO_SPYRO(moby->m_Position)) < 0x14) {
                  props->m_0x24 = 0xFA;
                  props->m_0x30 = 0;
                  moby->m_State = 3;
                  MOBY_ANIM_CHANGE(moby, 3);
                  continue;
                }
              }
            }
          }
        }

        break;
      }

      case 2: {
        if (moby->m_AnimationState.m_Frame < 5) {
          moby->m_Rotation.z += props->m_0x28;
        }
        if (props->m_0x24 >= 0x10) {
          props->m_0x24 -= 0xF;
          func_80039688(moby, props->m_0x20, props->m_0x24, 0, 300, 5);
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x28);
          func_80052568(moby);
          continue;
        }
        break;
      }

      case 3: {
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (func_80039398(moby, props->m_0x24, 0, 300, 0x15) == 2) {
          *props->m_0x40 = 0;
          props->m_0x2c = 0x78;
          moby->m_State = 100;
          continue;
        }

        if (moby->m_AnimationState.m_Frame >= 4 && props->m_0x24 >= 0x29) {
          props->m_0x24 -= 0x1E;
        }

        if (DISTANCE_TO_SPYRO(moby) < 1500 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 900) {
          if (props->m_0x30 == 0) {
            props->m_0x30 = 1;
            props->m_0x2c = 0xDC;
            g_Spyro.m_DamageFlags |= 0x86;
            g_Spyro.unk_0x208.x = FIXED_MUL(Cos(moby->m_Rotation.z << 4), 135);
            g_Spyro.unk_0x208.y = FIXED_MUL(Sin(moby->m_Rotation.z << 4), 135);
            g_Spyro.unk_0x208.z = 0x32;
          } else if (props->m_0x30 == 1) {
            props->m_0x30 = 2;
            props->m_0x3c = 0x1E;
            g_Spyro.m_ControlFlags |= 0x80000200;
            g_Spyro.unk_0x21c = &moby->m_Position;
            g_Spyro.unk_0x220 = &D_80078668;
            D_80078668.m_Coords.azimuth = -ANGLE_TO_SPYRO(moby->m_Position)
                                          << 4;
            D_80078668.m_Coords.radius = DISTANCE_TO_SPYRO(moby) + 0xC00;
            D_80078668.m_Coords.elevation = 100;
            D_80078668.m_Offset.azimuth = 0;
            D_80078668.m_Offset.elevation = -200;
            D_80078668.m_Offset.radius = 0;
          }
        }

        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;
      }

      case 4: {
        if (g_AnimationFinished) {
          moby->m_Rotation.z = func_80038074(moby->m_Rotation.z, ROTDEG8(180));
          if (props->m_0x30 == 0) {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
          } else {
            *props->m_0x40 = 0;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            moby->m_State = 100;
          }
          continue;
        }
        break;
      }

      case 100: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (props->m_0x00 == 2) {
          angle = ANGLE_FROM(PATH_NODE_POS(props->m_0x18, 0), props->m_0x04);
          func_80038638(moby, &PATH_NODE_POS(props->m_0x18, 0), props->m_0x44,
                        angle, 1, 200, 0xE, 8, 0xFF, 0xFF, 0, 0, 0);
          if (OctDistance(&moby->m_Position, &props->m_0x04) < 0x200) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        } else {
          targetAngle = Atan2Fast(props->m_0x04.x - moby->m_Position.x,
                                  props->m_0x04.y - moby->m_Position.y);
          if (RotateMobyToAngle(moby, targetAngle, 4, 0x14, 1) != 0) {
            func_80039398(moby, 0xA0, 0, 0, 5);
          }
          if (OctDistance(&moby->m_Position, &props->m_0x04) < 0xB4) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        }
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#if defined(HAS_MOBY_142) || defined(HAS_MOBY_227) || defined(HAS_MOBY_241)
#ifdef HAS_MOBY_142
    case 142:
#endif
#ifdef HAS_MOBY_241
    case 241:
#endif
#ifdef HAS_MOBY_227
    case 227:
#endif
    {
      Moby142Props *props = moby->m_Props;
      Vector3D attachmentPosition;

      if (props->m_0x38 == -1) {
        props->m_0x38 = moby->m_Rotation.z;
      }

      switch (moby->m_State) {
      case 0: {
        int activationDistance = 2700;

        if (props->m_0x20 == 3) {
          activationDistance = 3400;
        }
        if (props->m_0x30 != 0) {
          moby->m_State = 4;
          moby->m_Position.z -= 500;
          continue;
        }
        if (moby->m_Substate != 0) {
          moby->m_Substate = 0;
          props->m_0x2c = 0;
          moby->m_State = 3;
          continue;
        }

        RotateMobyToSpyro(moby, 4, 0, 0);
        if (props->m_0x34 != -1 && g_LevelMobys[props->m_0x34].m_State < 0x80) {
          break;
        }
        if (props->m_0x2c != 0 || g_SpyroFlame.m_FairyKissTimer != 0) {
          break;
        }
        if (DISTANCE_TO_SPYRO(moby) >= activationDistance) {
          break;
        }
        if (SPYRO_BASE_Z_DISTANCE(moby) < 2000 &&
            func_80017908(g_Spyro.m_bodyRotation.z,
                          ANGLE_FROM_SPYRO(moby->m_Position)) < 0x1E) {
          props->m_0x0c = 0x4B;
          moby->m_Substate = 0;
          moby->m_State = 1;
          continue;
        }
        break;
      }

      case 1: {
        Vector3D targetPosition;
        int heightDifference;

        RotateMobyToSpyro(moby, 4, 0, 0);
        VecCopy(&targetPosition, &g_Spyro.m_Position);
        targetPosition.x += FIXED_MUL(COSINE_8(g_Spyro.m_bodyRotation.z), 900);
        targetPosition.y += FIXED_MUL(SINE_8(g_Spyro.m_bodyRotation.z), 900);
        targetPosition.z -= 380;

        g_ScreenBorderEnabled = 1;

        heightDifference = targetPosition.z - moby->m_Position.z;
        g_Spyro.m_ControlFlags = 0x80002000;

        VecCopy(&props->m_0x10, &g_Spyro.m_Position);
        props->m_0x10.x += FIXED_MUL(COSINE_8(g_Spyro.m_bodyRotation.z), 300);
        props->m_0x10.y += FIXED_MUL(SINE_8(g_Spyro.m_bodyRotation.z), 300);
        props->m_0x10.z += 100;

        g_Spyro.m_ControlFlags |= 0x80000200;
        g_Spyro.unk_0x21c = &props->m_0x10;
        g_Spyro.unk_0x220 = &D_80078668;
        D_80078668.m_Coords.azimuth = -(g_Spyro.m_bodyRotation.z + 0x40) << 4;
        D_80078668.m_Coords.elevation = 0;
        D_80078668.m_Coords.radius = 0x400;
        D_80078668.m_Offset.azimuth = 0;
        D_80078668.m_Offset.elevation = 0;
        D_80078668.m_Offset.radius = 0;

        switch (moby->m_Substate) {
        case 0:
          if (OctDistance(&moby->m_Position, &targetPosition) > 0x50) {
            func_80039688(moby, ANGLE_FROM(moby->m_Position, targetPosition),
                          100, 0, 0, 0);
          } else {
            moby->m_Position.x = targetPosition.x;
            moby->m_Position.y = targetPosition.y;
          }

          if (ABS2(heightDifference) >= 0x29) {
            if (heightDifference < 0) {
              if (heightDifference < -0x32) {
                heightDifference = -0x32;
              }
            } else if (heightDifference > 0) {
              if (heightDifference > 0x32) {
                heightDifference = 0x32;
              }
            }
            moby->m_Position.z += heightDifference;
          } else {
            moby->m_Position.z = targetPosition.z;
          }

          if (TICK_TIMER(props->m_0x0c)) {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            props->m_0x24 = 0;
            moby->m_Substate = 1;
          }
          break;

        case 1: {
          int frameThreshold;
          if (moby->m_AnimationState.m_NextFrame >= 6) {
            props->m_0x24++;
            if (props->m_0x24 == 2 || moby->m_Class == 241) {
              int offset = 320;
              if (moby->m_Class == 241) {
                offset = 400;
              }
              VecCopy(&targetPosition, &g_Spyro.m_Position);
              targetPosition.x +=
                  FIXED_MUL(offset, COSINE_8(g_Spyro.m_bodyRotation.z));
              targetPosition.y +=
                  FIXED_MUL(offset, SINE_8(g_Spyro.m_bodyRotation.z));
              g_SpawnParticle(1, 31, &targetPosition, 0);
              props->m_0x24 = 0;
            }
          }

          if (g_AnimationFinished) {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
            props->m_0x0c = 0xA;
            moby->m_Substate = 2;
            func_8003851C(moby, 0, 0);
          }

          frameThreshold = 7;
          if (moby->m_Class == 241) {
            frameThreshold = 0xE;
          }
          if (moby->m_AnimationState.m_NextFrame >= frameThreshold &&
              g_SpyroFlame.m_FairyKissTimer == 0) {
            if (props->m_0x20 == 1 || props->m_0x20 == 3) {
              // 30 days
              g_SpyroFlame.m_FairyKissTimer = 30 * 24 * 60 * 60 * 60;
            } else if (props->m_0x20 == 2) {
              // 13 seconds
              g_SpyroFlame.m_FairyKissTimer = 13 * 60;
            } else {
              // 15 seconds
              g_SpyroFlame.m_FairyKissTimer = 15 * 60;
            }
            g_Spyro.m_ControlFlags |= 0x80020000;
            g_Spyro.m_portalAngle.z = props->m_0x38;
          }
          break;
        }
        case 2:
          if (TICK_TIMER(props->m_0x0c)) {
            moby->m_State = 2;
            continue;
          }
          break;
        }
        break;
      }

      case 2: {
        int heightDifference = props->m_0x00.z - moby->m_Position.z;

        g_ScreenBorderEnabled = 0;
        if (props->m_0x34 != -1 && g_LevelMobys[props->m_0x34].m_State < 0x80) {
          RotateMobyToAngle(moby, ANGLE_FROM(moby->m_Position, props->m_0x00),
                            6, 0, 0);
        } else {
          RotateMobyToSpyro(moby, 4, 0, 0);
        }

        if (OctDistance(&moby->m_Position, &props->m_0x00) > 0x50) {
          func_80039688(moby, ANGLE_FROM(moby->m_Position, props->m_0x00), 100,
                        0, 0, 0);
        } else {
          moby->m_Position.x = props->m_0x00.x;
          moby->m_Position.y = props->m_0x00.y;
        }

        if (ABS2(heightDifference) >= 0x29) {
          if (heightDifference < 0) {
            if (heightDifference < -0x32) {
              heightDifference = -0x32;
            }
          } else if (heightDifference > 0) {
            if (heightDifference > 0x32) {
              heightDifference = 0x32;
            }
          }
          moby->m_Position.z += heightDifference;
        }

        if (OctDistance(&moby->m_Position, &props->m_0x00) < 0x51 &&
            ABS2(heightDifference) < 0x29) {
          moby->m_Substate = 0;
          moby->m_State = 0;
          continue;
        }
        break;
      }

      case 3:
        if (MoveMobyAlongPath(moby, props->m_0x28, 0x200, 150, 0, 6, 0x10, 0) !=
            0x100) {
          break;
        }
        moby->m_Substate = 0;
        VecCopy(&props->m_0x00, &moby->m_Position);
        moby->m_State = 0;
        continue;

      case 4: {
        int angle =
            (ANGLE_FROM(PATH_NODE_POS(props->m_0x28, 0), moby->m_Position) +
             8) &
            0xFF;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);

        if (moby->m_Substate == 0) {
          if (g_LevelMobys[props->m_0x34].m_State >= 0x80) {
            moby->m_Substate = 0;
            props->m_0x30 = 0;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
            moby->m_State = 2;
            continue;
          }
        } else {
          moby->m_Substate = 0;
          props->m_0x30 = 0;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          moby->m_State = 2;
          continue;
        }

        func_80038638(moby, &PATH_NODE_POS(props->m_0x28, 0), 3000, angle, 8,
                      0x78, 0xE, 0x80, 0xFF, 0xFF, 0, 0, 0);
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
      func_80052D64(moby, 0, &attachmentPosition);
      g_SpawnParticle(2, 66, &attachmentPosition, 2);
      break;
    }
#endif
#ifdef HAS_MOBY_143
    case 143: {
      Moby143Props *props = moby->m_Props;

      props->m_0x00 += g_DeltaTime * 14;
      moby->m_ScaleOverride = 48000 / props->m_0x00;
      if (moby->m_ScaleOverride < 5) {
        moby->m_ScaleOverride = 5;
      }
      if (moby->m_ScaleOverride >= 0x80) {
        moby->m_ScaleOverride = 0x7F;
      }
      if (props->m_0x04 != 0) {
        func_8004E2E8(&moby->m_Position, props->m_0x00, 7);
      }
      if (moby->m_AnimationState.m_NextAnimation == 1 && g_AnimationFinished) {
        func_80052568(moby);
        continue;
      }
      if (TICK_TIMER(props->m_0x04)) {
        if (moby->m_AnimationState.m_Animation != 1) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 1);
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_145
    case 145: {
      Moby145Props *props = moby->m_Props;
      Vector3D delta;
      int distance;

      VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);
      if (distance < 13000) {
        distance = VecMagnitude(&delta, 0);
      }

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 4 && moby->m_State != 20) {
        func_800562A4(moby, 1);
        props->m_0x04 = 0xDC;
        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
          props->m_0x04 = 0x154;
        }
        props->m_0x0c = 0x82;
        props->m_0x08 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 4;
        MOBY_ANIM_CHANGE(moby, 4);
        continue;
      }

      if (props->m_0x70 == 0) {
        props->m_0x70 = 1;
        moby->m_UpdateDistance = 0x20;
        if (props->m_0x00 == 1) {
          if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x40[0][0]) != 0 ||
              func_80038C4C(&g_Spyro.m_Position, &props->m_0x40[1][0]) != 0) {
            props->m_0x00 &= ~1;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x00 == 1) {
          if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x28[0]) != 0) {
            props->m_0x00 &= ~1;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (TICK_TIMER(props->m_0x10) && distance < 5000 &&
            func_80017908(g_Camera.m_Rotation.z >> 4,
                          ANGLE_FROM(g_Camera.m_Position, moby->m_Position)) <
                0x28 &&
            SPYRO_BASE_Z_DELTA(moby) < -200) {
          if (TICK_TIMER(props->m_0x24)) {
            props->m_0x14 = 0;
            props->m_0x10 = props->m_0x18;
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
            continue;
          }
        }
        if (moby->m_AnimationState.m_NextAnimation != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 0);
          continue;
        }
        break;
      case 2:
        if (distance < 2500) {
          moby->m_State = 0;
          continue;
        }
        if (func_80039E94(moby, props->m_0x1c, 0x100, 0x8C, 0, 8, 0x28, 0xFF,
                          5) == 0x100) {
          moby->m_State = 10;
          continue;
        }
        break;
      case 3: {
        Moby156Props *projectileProps;
        Moby *projectile;
        Vector3D velocity;
        Vector3D target;

        RotateMobyToSpyro(moby, 4, 0, 0);
        props->m_0x14 += g_DeltaTime;
        if (moby->m_AnimationState.m_NextFrame > 15 &&
            moby->m_AnimationState.m_NextFrame < 26 && props->m_0x14 >= 4) {
          projectile = g_SpawnMoby(156, moby);
          projectileProps = projectile->m_Props;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 0, &projectile->m_Position);
          VecCopy(&target, &g_Spyro.m_Position);
          VecSub(&velocity, &target, &projectile->m_Position);
          VecScaleToLength(&velocity, VecMagnitude(&velocity, 0), 300);
          velocity.x += RandRange(-0x18, 0x18);
          velocity.y += RandRange(-0x18, 0x18);
          velocity.z = 0;
          VecMagnitude(&velocity, 0);
          projectile->m_Rotation.y = 0;
          projectile->m_Rotation.z = ANGLE_TO_SPYRO(projectile->m_Position);
          VecCopy(&projectileProps->m_0x00, &velocity);
          projectileProps->m_0x0c = 0x26;
          projectileProps->m_0x0e = 0;
          props->m_0x14 = 0;
        }
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      case 4: {
        Moby *spawned;
        int floorHeight;
        MoveMobyWithGravity(moby, &props->m_0x04, props->m_0x08, &props->m_0x0c,
                            0xC, 0x10);
        if ((g_SurfaceBelowFlags & 0x3F) == 1 ||
            (g_SurfaceBelowFlags & 0x3F) == 2) {
          floorHeight = func_80038340(moby);
          if (MOBY_BASE_Z_DISTANCE(moby, floorHeight) < 100) {
            spawned = g_SpawnMoby(507, moby);
            PlaySound(g_Spu.m_SoundTable->waterSplash, moby, 8,
                      &moby->m_SoundChannel);
            spawned->m_DepthOffset = 0xFE;
            props->m_0x74 = 0xA;
            moby->m_State = 20;
            continue;
          }
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }
      case 10:
        if (RotateMobyToSpyro(moby, 6, 0, 0) != 0) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      case 20:
        if (TICK_TIMER(props->m_0x74)) {
          func_80052568(moby);
          continue;
        }
        moby->m_Position.z -= 100;
        break;
      }
      break;
    }

#endif
#ifdef HAS_MOBY_146
    case 146: { // Peacekeepers Tent
      Moby146Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0 && moby->m_State < 2) {
        moby->m_State = 2;
        MOBY_ANIM_RESTART(moby, 2);
        continue;
      }

      if ((moby->m_DamageFlags & MOBY_DAMAGE_SUPER) != 0 && moby->m_State < 2) {
        if (props->m_Timer == 0) {
          props->m_Timer = 30;
        } else if (TICK_TIMER(props->m_Timer)) {
          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
          continue;
        }
      }

      switch (moby->m_State) {
      case 1:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;
      case 2:
        if (g_AnimationFinished) {
          func_80052568(moby);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
// Somehow causes compiler to emit 0x8 Stack...
// Could be useful for matches that are missing 0x8
#ifdef HAS_MOBY_147
    case 147: {
      Moby147Props *props = moby->m_Props;
      Vector3D delta;
      int distance;

      VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);
      if (distance < 13000) {
        distance = VecMagnitude(&delta, 0);
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 4 && moby->m_State != 20) {
        func_800562A4(moby, 1);
        props->m_0x08 = 200;
        props->m_0x10 = 260;
        props->m_0x0c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 4;
        MOBY_ANIM_CHANGE(moby, 4);
        continue;
      }

      if (props->m_0x7c == 0) {
        props->m_0x7c = 1;
        moby->m_UpdateDistance = 0x20;
        if (props->m_0x00 == 1) {
          if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x4c[0][0]) != 0 ||
              func_80038C4C(&g_Spyro.m_Position, &props->m_0x4c[1][0]) != 0) {
            props->m_0x00 &= ~1;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x00 == 1) {
          if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x34[0]) != 0) {
            props->m_0x00 &= ~1;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (props->m_0x00 != 1 && distance < 0x3400 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 1500) {
          props->m_0x18 = moby->m_Rotation.z;
          props->m_0x2c = moby->m_Rotation.z << 4;
          moby->m_Substate = 0;
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        if (moby->m_AnimationState.m_NextAnimation != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 0);
          continue;
        }
        break;
      case 2:
        if (func_80039E94(moby, props->m_0x04, 0x100, 0xA0, 0, 8, 0x28, 0xFF,
                          5) == 0x100) {
          moby->m_State = 0;
          continue;
        }
        break;
      case 3:
        switch (moby->m_Substate) {
        case 0: {
          int angleDifference;

          if (distance > 0x4000 || SPYRO_BASE_Z_DISTANCE(moby) >= 0x899) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
          props->m_0x18 = func_800179F0(ANGLE_TO_SPYRO(moby->m_Position),
                                        props->m_0x18, 5, 3);
          if (props->m_0x1c != 0xFF &&
              ((props->m_0x1c - props->m_0x18) & 0xFF) >= 0xF1) {
            props->m_0x18 = props->m_0x1c;
          }
          if (props->m_0x20 != 0xFF) {
            int targetAngleOffset = (props->m_0x20 - props->m_0x18) & 0xFF;

            if (targetAngleOffset >= 0x29 && targetAngleOffset <= 0x7F) {
              props->m_0x18 = props->m_0x20;
            }
          }
          props->m_0x2c += props->m_0x28;
          angleDifference = func_800381BC(props->m_0x18, props->m_0x2c >> 4);
          if (TICK_TIMER(props->m_0x30)) {
            if (ABS2(angleDifference) >= 0x1B) {
              if ((angleDifference < 0 && props->m_0x28 < 0) ||
                  (angleDifference > 0 && props->m_0x28 > 0)) {
                moby->m_Substate = 1;
              }
            }
          }
          moby->m_Rotation.z = props->m_0x2c >> 4;
          if ((g_GameTick & 1) != 0) {
            int projectileAngle;
            int projectileSpeed;
            Moby *projectile = g_SpawnMoby(156, moby);
            Moby156Props *projectileProps = projectile->m_Props;

            Vector3D velocity;

            projectileAngle = (moby->m_Rotation.z - 5) & 0xFF;

            projectile->m_Position.x =
                moby->m_Position.x + FIXED_MUL(COSINE_8(projectileAngle), 1500);
            projectile->m_Position.y =
                moby->m_Position.y + FIXED_MUL(SINE_8(projectileAngle), 1500);
            projectile->m_Position.z = moby->m_Position.z + 600;

            projectileSpeed = 0x190;
            velocity.x =
                FIXED_MUL(COSINE_8(moby->m_Rotation.z), projectileSpeed);
            velocity.y = FIXED_MUL(SINE_8(moby->m_Rotation.z), projectileSpeed);
            velocity.z = -41;

            projectile->m_Rotation.y = Atan2(projectileSpeed, velocity.z, 0);
            projectile->m_Rotation.z = moby->m_Rotation.z;

            VecCopy(&projectileProps->m_0x00, &velocity);
            projectileProps->m_0x0c = 0x32;
            projectileProps->m_0x0e = 2;
          }
          break;
        }
        case 1:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
          if (g_AnimationFinished) {
            if (moby->m_AnimationState.m_NextAnimation != 3) {
              g_AnimationFinished = 0;
              moby->m_AnimationState.m_FrameProgress = 0x10;
              moby->m_AnimationState.m_PerFrameProgress = 0x10;
              moby->m_AnimationState.m_NextAnimation = 3;
              moby->m_AnimationState.m_NextFrame = 0;
              func_80037E98(moby);
            }
            props->m_0x30 = 0x1E;
            moby->m_Substate = 0;
            props->m_0x28 = -props->m_0x28;
          }
          break;
        }
        break;
      case 4: {
        Moby *spawned;
        int floorHeight;

        MoveMobyWithGravity(moby, &props->m_0x08, props->m_0x0c, &props->m_0x10,
                            0xC, 0x16);
        if ((g_SurfaceBelowFlags & 0x3F) == 1 ||
            (g_SurfaceBelowFlags & 0x3F) == 2) {
          floorHeight = func_80038340(moby);
          if (MOBY_BASE_Z_DISTANCE(moby, floorHeight) < 100) {
            spawned = g_SpawnMoby(507, moby);
            PlaySound(g_Spu.m_SoundTable->waterSplash, moby, 8,
                      &moby->m_SoundChannel);
            spawned->m_DepthOffset = 0xFE;
            props->m_0x30 = 0xA;
            moby->m_State = 20;
            continue;
          }
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;
      }
      case 10:
        if (RotateMobyToSpyro(moby, 6, 0, 0) != 0) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      case 20:
        if (TICK_TIMER(props->m_0x30)) {
          func_80052568(moby);
          continue;
        }
        moby->m_Position.z -= 100;
        break;
      }
      break;
    }

#endif
#ifdef HAS_MOBY_148
    case 148: {
      Moby148Props *props = moby->m_Props;
      Vector3D delta;
      int distance;

      VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);
      if (distance < 13000) {
        distance = VecMagnitude(&delta, 0);
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 4 && moby->m_State != 20) {
        func_800562A4(moby, 1);
        props->m_0x04 = 300;
        props->m_0x0c = 260;
        props->m_0x08 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        moby->m_DamageFlags = 0;
        if (props->m_0x38 != 0 && props->m_0x38 != (Moby *)-1 &&
            props->m_0x38->m_Class == 176 && props->m_0x38->m_Substate == 0 &&
            props->m_0x38->m_State < 0x80) {
          props->m_0x38->m_Substate = 1;
          props->m_0x38->m_State = 2;
        }
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 4;
        MOBY_ANIM_CHANGE(moby, 4);
        continue;
      }

      if (props->m_0x74 == 0) {
        props->m_0x74 = 1;
        moby->m_UpdateDistance = 0x20;
        if (props->m_0x00 == 1) {
          if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x44[0][0]) != 0 ||
              func_80038C4C(&g_Spyro.m_Position, &props->m_0x44[1][0]) != 0) {
            props->m_0x00 &= ~1;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x00 == 1) {
          if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x10[0]) != 0) {
            props->m_0x00 &= ~1;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (TICK_TIMER(props->m_0x30) && distance < 2500 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 600) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        if (props->m_0x00 != 1 && distance >= 0x9C5 &&
            TICK_TIMER(props->m_0x34)) {
          if (props->m_0x40 < distance) {
            props->m_0x28->m_CurrentNode = (props->m_0x28->m_CurrentNode +
                                            props->m_0x28->m_NodeCount + 1) %
                                           props->m_0x28->m_NodeCount;
          }
          props->m_0x38 = 0;
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }
        if (g_AnimationFinished) {
          if ((rand() & 1) != 0) {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          } else {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          }
        }
        break;
      case 2:
        if (func_80039E94(moby, props->m_0x2c, 0x100, 170, 0, 8, 0x28, 0xFF,
                          5) == 0x100) {
          moby->m_State = 10;
          continue;
        }
        break;
      case 3:
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_AnimationFinished) {
          props->m_0x30 = 100;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      case 4: {
        Moby *spawned;
        int floorHeight;

        MoveMobyWithGravity(moby, &props->m_0x04, props->m_0x08, &props->m_0x0c,
                            0xC, 0x16);
        if ((g_SurfaceBelowFlags & 0x3F) == 1 ||
            (g_SurfaceBelowFlags & 0x3F) == 2) {
          floorHeight = func_80038340(moby);
          if (MOBY_BASE_Z_DISTANCE(moby, floorHeight) < 100) {
            spawned = g_SpawnMoby(507, moby);
            PlaySound(g_Spu.m_SoundTable->waterSplash, moby, 8,
                      &moby->m_SoundChannel);
            spawned->m_DepthOffset = 0xFE;
            props->m_0x30 = 0xA;
            moby->m_State = 20;
            continue;
          }
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;
      }
      case 5: {
        Moby176Props *childProps;
        PathData *path = props->m_0x28;
        Vector3D randomOffset;
        Vector3D target;

        if (props->m_0x38 == 0) {
          if (moby->m_AnimationState.m_NextFrame >= 5) {
            props->m_0x38 = g_SpawnMoby(176, moby);
            props->m_0x38->m_RenderRadius = 0x28;
            props->m_0x38->m_UpdateDistance = 0xFF;
          }
        }
        if (props->m_0x38 != 0 && props->m_0x38 != (Moby *)-1 &&
            props->m_0x38->m_Substate == 0) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 0, &props->m_0x38->m_Position);
          if (moby->m_AnimationState.m_NextFrame >= 0xA) {
            childProps = props->m_0x38->m_Props;
            if (props->m_0x40 < distance) {
              VecCopy(&target, &PATH_CUR_POS(path));
            } else {
              RandRange(-0xA, 0xA);
              target.x = ((Vector3D *)&g_Spyro.m_Position)->x;
              target.y = ((Vector3D *)&g_Spyro.m_Position)->y;
              target.z = ((Vector3D *)&g_Spyro.m_Position)->z;
              target.z -= 0x17c;
            }
            childProps->m_0x08 = -6;
            childProps->m_0x04 = 260;
            childProps->m_0x06 =
                func_8003891C(&props->m_0x38->m_Position, &target, 260,
                              childProps->m_0x08, &childProps->m_0x00);
            if (childProps->m_0x00 == 0) {
              props->m_0x38->m_State = 2;
            }
            childProps->m_0x0d = RandRangeSigned(7, 0xF);
            childProps->m_0x0e = RandRangeSigned(7, 0xF);
            childProps->m_0x0f = RandRangeSigned(7, 0xF);
            childProps->m_0x0a = 0x8C;
            childProps->m_0x0c = ANGLE_FROM(moby->m_Position, target);
            props->m_0x38->m_Substate = 1;
            props->m_0x38 = (Moby *)-1;
          }
        }
        if (g_AnimationFinished) {
          props->m_0x34 = 0x3C;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      case 10:
        if (RotateMobyToSpyro(moby, 6, 0, 0) != 0) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      case 20:
        if (TICK_TIMER(props->m_0x30)) {
          func_80052568(moby);
          continue;
        }
        moby->m_Position.z -= 100;
        break;
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }

#endif
#ifdef HAS_MOBY_150 // Jacques
    case 150: {
      Moby150Props *props;
      props = moby->m_Props;
      if (props->m_0x18 == 0) {
        moby->m_UpdateDistance = 0x20;
        props->m_0x0c[0] = 3;
        props->m_0x0c[1] = 6;
        props->m_0x0c[2] = 7;
        props->m_0x0c[3] = 10;
        props->m_0x54 = 0;
        props->m_0x18 = 1;
        props->m_0x0c[4] = 11;
        props->m_0x0c[5] = 13;
        props->m_0x0c[6] = 0;
        func_8002B390(7, 0xFC, 0);
        func_8002B390(8, 0xFC, 0);
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 3 && moby->m_State != 6) {
        moby->m_DamageFlags = 0;

        switch (props->m_0x00->m_CurrentNode) {
        case 11:
          func_8002B390(9, 0xFC, 0);
          break;

        case 13:
          func_8002B390(10, 0xFC, 0);
          break;

        case 0:
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        moby->m_State = 10;
        break;
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
      func_8004D5EC(&g_Spyro.m_Position, 0xFFFF);
      DISTANCE_TO_SPYRO(moby);

      switch (moby->m_State) {
      case 0:
        RotateMobyToSpyro(moby, 0x10, 0, 0);
        if (DISTANCE_TO_SPYRO(moby) < 0x1000 && props->m_0x50 == 0) {
          if (props->m_0x00->m_CurrentNode == 13) {
            func_8002B390(10, 0xFC, 0);
          }
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          moby->m_State = 10;
        } else if (DISTANCE_TO_SPYRO(moby) < 0x2800 &&
                   TICK_TIMER(props->m_0x34) && moby->m_WasDrawn &&
                   func_80017908(g_Camera.m_Rotation.z >> 4,
                                 ANGLE_FROM(g_Camera.m_Position,
                                            moby->m_Position)) < 0x1E) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
        }
        break;
      case 2:
        RotateMobyToSpyro(moby, 0x10, 0, 0);
        if (DISTANCE_TO_SPYRO(moby) < 0x1000 && props->m_0x50 == 0) {
          if (props->m_0x00->m_CurrentNode == 13) {
            func_8002B390(10, 0xFC, 0);
          }
          props->m_0x54 = 0;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          moby->m_State = 10;
        } else if (g_AnimationFinished) {
          props->m_0x34 = 0x4B;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
        } else if (moby->m_AnimationState.m_NextFrame == 0 &&
                   props->m_0x44 == 0) {
          props->m_0x44 = g_SpawnMoby(47, moby);
          props->m_0x44->m_ShadowDistance = -1;
          // Couldn't match with a dedicated Moby47Props*
          ((Moby47Props *)props->m_0x44->m_Props)->m_0x0c = moby;
          ((Moby47Props *)props->m_0x44->m_Props)->m_0x03 = 1;
        }
        break;
      case 3:
        if (g_AnimationFinished) {
          func_800385BC(moby, 0x18);
          func_80052568(moby);
        }
        break;
      case 10:
        if (props->m_0x4c != 0) {
          g_ScreenBorderEnabled = 1;
          g_Spyro.m_ControlFlags = 0x80002000;
        }
        if (props->m_0x00->m_CurrentNode != props->m_0x0c[props->m_0x14]) {
          func_8003BFC0(moby, props->m_0x00, &props->m_0x1c,
                        (int *)&props->m_0x28, 8, 4);
        } else {
          VecNull(&props->m_0x1c);
          moby->m_Rotation.y = 0;
          switch (props->m_0x00->m_CurrentNode) {
          case 3:
          case 6:
          case 10:
          case 13:
            props->m_0x40 = 1;
            props->m_0x50 = 0;
            props->m_0x34 = 0;
            props->m_0x3c = &g_LevelMobys[0x26];
            break;
          case 0:
          case 7:
          case 11:
            props->m_0x40 = 1;
            props->m_0x50 = 1;
            props->m_0x34 = 0;
            props->m_0x3c = &g_LevelMobys[0x29];
            break;
          }
          props->m_0x34 = 0x8C;
          g_ScreenBorderEnabled = 0;
          props->m_0x14++;
          moby->m_DamageFlags = 0;
          moby->m_State = 0;
        }
        break;
      }
      break;
    }
#endif
#if defined(HAS_MOBY_152) || defined(HAS_MOBY_153)
#ifdef HAS_MOBY_152
    case 152:
#endif
#ifdef HAS_MOBY_153
    case 153:
#endif
    {
      Moby152Props *props = moby->m_Props;
      Vector3D vec_particle[2];
      Vector3D color;

      if (moby->m_WasDrawn) {
        moby->m_Substate--;
        if (moby->m_Substate == 0 || moby->m_Position.z < props->m_MinZ) {
          g_SpawnParticle(8, 70, &moby->m_Position, 0x10);
          func_80052568(moby);
        } else {
          VecAdd(&moby->m_Position, &moby->m_Position, &props->m_Velocity);
          props->m_Velocity.z -= 12;
          moby->m_Rotation.x += props->m_AngularVelocity.x;
          moby->m_Rotation.y += props->m_AngularVelocity.y;
          moby->m_Rotation.z += props->m_AngularVelocity.z;
          if (!(moby->m_Substate % 2)) {
            VecCopy(&vec_particle[0], &moby->m_Position);
            vec_particle[1].x = rand() & 3;
            vec_particle[1].y = rand() & 3;
            vec_particle[1].z = 20;
            color.x = 128;
            color.y = 112;
            color.z = 64;
            g_SpawnParticle(1, 17, vec_particle, (int)&color);
          }
        }
      } else {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_154
    case 154: {
      Moby154Props *props = moby->m_Props;
      int damageMask;

      props->m_0x0c = ApplyFlameHeatExternal(moby, props->m_0x0c);

      damageMask = 0xF0000;
      if (props->m_0x04) {
        damageMask = 0xA0000;
      }

      if (moby->m_DamageFlags & damageMask) {
        if (moby->m_State != 2) {
          if (props->m_0x04) {
            props->m_0x08 = g_SpawnMoby(207, moby);
          } else {
            props->m_0x08 = g_SpawnMoby(202, moby);
          }
          props->m_0x08->m_Position.z += 0x233;
          props->m_0x08->m_DamageFlags = moby->m_DamageFlags;
          props->m_0x08->m_Rotation.y = 0x40;
          moby->m_State = 2;
          moby->m_DamageFlags = 0;
          moby->m_Substate = 0;
          MOBY_ANIM_RESTART(moby, 2);
          continue;
        }
      }

      moby->m_DamageFlags = 0;
      switch (moby->m_State) {
      case 0:
        if (props->m_0x04 == 1) {
          moby->m_State = 3;
          MOBY_ANIM_RESTART(moby, 3);
          continue;
        }
        if (g_AnimationFinished) {
          moby->m_Substate = 0;
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          continue;
        }
        break;
      case 1:
        if (moby->m_Substate == 1) {
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;
      case 2:
        if (moby->m_Substate == 1) {
          if (DISTANCE_TO_SPYRO(moby) > 0x400 &&
              OctDistance(&moby->m_Position, &g_Camera.m_Position) > 0xA00) {
            props->m_0x08 = 0;
            if (props->m_0x04 == 1) {
              moby->m_State = 3;
              MOBY_ANIM_RESTART(moby, 3);
              continue;
            }
            moby->m_State = 0;
            MOBY_ANIM_RESTART(moby, 0);
            continue;
          }
        }
        break;
      case 3:
        moby->m_Renderer.raw = 0xA0;
        ((int *)&moby->m_SpecularMetalColor)[0] = 0xA18618;
        if (g_AnimationFinished) {
          moby->m_Substate = 0;
          moby->m_State = 4;
          MOBY_ANIM_RESTART(moby, 4);
          continue;
        }
        break;
      case 4:
        if (moby->m_Substate == 1) {
          moby->m_State = 3;
          MOBY_ANIM_RESTART(moby, 3);
          continue;
        }
        break;
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_155
    case 155: {
      Moby155Props *props = moby->m_Props;
      Vector3D velocity;

      switch (moby->m_State) {
      case 0: {
        int height;
        int rotation;

        if (moby->m_Position.x < 0x400 || moby->m_Position.y < 0x400 ||
            moby->m_Position.z < 0x400) {
          moby->m_State = 1;
          break;
        }

        height = func_8004D5EC(&moby->m_Position, 0x2000);
        if (height != 0) {
          rotation = moby->m_Position.z - height - 0x200;
          rotation = -rotation >> 2;
          if (rotation > 0x20) {
            rotation = 0x20;
          }
          if (rotation < -0x20) {
            rotation = -0x20;
          }
          moby->m_Rotation.y = rotation;
        }

        VecCopy(&velocity, &moby->m_Position);

        if (props->m_0x00 < 200) {
          func_8004E3C8(&moby->m_Position, 100, 0, 0x20000, moby, 0);
        }

        if (func_8004E2E8(&moby->m_Position, 100, 7) ||
            TICK_TIMER(props->m_0x00) ||
            func_8003BCCC(moby, 0x80, 0, 0x100, 0) ||
            func_8004AE38(&velocity, &moby->m_Position)) {
          moby->m_State = 1;
        }

        VecNull(&velocity);
        g_SpawnParticle(1, 1, &moby->m_Position, (int)&velocity);
        break;
      }

      case 1: {
        Vector3D position;
        int i;

        for (i = 0; i < 16; i++) {
          velocity.x = RandRange(-90, 90);
          velocity.y = RandRange(-90, 90);
          velocity.z = RandRange(-25, 60);
          VecCopy(&position, &velocity);
          VecShiftLeft(&position, 2);
          VecAdd(&position, &position, &moby->m_Position);
          g_SpawnParticle(1, 13, &position, (int)&velocity);
        }

        func_80052568(moby);
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_156
    case 156: {
      Moby156Props *props = moby->m_Props;

      switch (moby->m_State) {
      case 0: {
        Vector3D oldPosition;
        int range = 300;
        int height = 900;

        if (props->m_0x0e != 0) {
          height = 1600;
          range = 500;
          if (func_80017908(moby->m_Rotation.z,
                            ANGLE_TO_SPYRO(moby->m_Position)) >= 0x65) {
            range = 1800;
          }
        }
        TICK_TIMER(props->m_0x0e);
        VecCopy(&oldPosition, &moby->m_Position);
        VecAdd(&moby->m_Position, &moby->m_Position, &props->m_0x00);
        if (moby->m_Position.x < 0 || moby->m_Position.y < 0 ||
            moby->m_Position.z < 0 || moby->m_Position.z > 0x4800 ||
            moby->m_Position.y > 0x1F000 || moby->m_Position.x > 0x20800) {
          func_80052568(moby);
          break;
        }
        if (func_8004AE38(&oldPosition, &moby->m_Position) != 0) {
          moby->m_State = 1;
          moby->m_RenderRadius = 0;
          moby->m_WasDrawn = 0;
          break;
        }
        if (DISTANCE_TO_SPYRO(moby) < range &&
            SPYRO_BASE_Z_DISTANCE(moby) < height) {
          g_Spyro.m_DamageFlags |= 0x86;
          g_Spyro.m_ControlFlags = 0x80000047;
          // Can FIXED_MUL be used here?
          g_Spyro.unk_0x208.x = props->m_0x00.x << 1 >> 3;
          g_Spyro.unk_0x208.y = props->m_0x00.y << 1 >> 3;
          g_Spyro.unk_0x208.z = 40;
          moby->m_State = 1;
          break;
        }
        if (TICK_TIMER(props->m_0x0c)) {
          func_80052568(moby);
        }
        break;
      }
      case 1: {
        Vector3D velocity;
        velocity.x = 0;
        velocity.y = 0;
        velocity.z = 12;
        g_SpawnParticle(1, 1, &moby->m_Position, (int)&velocity);
        velocity.z = -0x30;
        g_SpawnParticle(4, 79, &moby->m_Position, (int)&velocity);
        func_80052568(moby);
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_157
    case 157: {
      if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) && moby->m_State == 0) {
        Moby157Props *props = moby->m_Props;

        func_8002B390(props->m_EnvAnimID, 0xFC, 0);
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
      } else if (moby->m_State == 1 && g_AnimationFinished) {
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
      }

      break;
    }
#endif
#ifdef HAS_MOBY_159
    case 159: {
      Moby159Props *props = moby->m_Props;
      Vector3D delta;
      int distance;
      int result;
      int floorHeight;
      int nearestNode;
      int angleDiff;
      int pathSteps;
      int pathNode;
      int minSpeed;
      int moveSpeed;

      VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);
      if (distance < 13000) {
        distance = VecMagnitude(&delta, 0);
      }

      if (moby->m_DamageFlags != 0 && moby->m_State != 2) {
        props->m_0x18 = 0xFA;
        if (moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) {
          props->m_0x18 = 0x145;
        }
        props->m_0x14 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x1c = 0x28;
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        continue;
      }
      moby->m_DamageFlags = 0;

      if (props->m_0x04 == 1 && moby->m_RenderRadius == 0 &&
          ((func_8002B3F4(4) >> 8) & 0xFF) > 0) {
        moby->m_RenderRadius = 0x28;
        g_LevelMobys[props->m_0x60].m_RenderRadius = 0x28;
      }

      if (moby->m_AnimationState.m_NextAnimation == 0 &&
          moby->m_RenderRadius != 0) {
        if (moby->m_AnimationState.m_NextFrame == 1 && (rand() & 3) == 0 &&
            IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[6]) ==
                0) {
          func_8003851C(moby, 6, 0);
        }
        if (moby->m_AnimationState.m_NextFrame == 10 && (rand() & 3) == 0 &&
            IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[5]) ==
                0) {
          func_8003851C(moby, 5, 0);
        }
      }

      switch (moby->m_State) {
      case 0:
        RotateMobyToSpyro(moby, 5, 0, 0);
        if (distance < 6500 && SPYRO_BASE_Z_DISTANCE(moby) < 1400) {
          props->m_0x10 = 300;
          if (props->m_0x04 == 0) {
            props->m_0x00->m_Reversed = 1;
            props->m_0x08 = 110;
          } else {
            props->m_0x00->m_Reversed = 1;
            props->m_0x08 = 150;
          }
          props->m_0x08 -= D_80075838[props->m_0x04] * 6;
          if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x28) != 0) {
            props->m_0x00->m_Reversed *= -1;
          }
          if (props->m_0x00->m_Reversed == -1) {
            props->m_0x00->m_CurrentNode = props->m_0x20;
          } else {
            props->m_0x00->m_CurrentNode = props->m_0x24;
          }
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;

      case 1:
        if (moby->m_Position.z < 0x800) {
          VecCopy(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
          func_80038458(moby);
        }
        if (TICK_TIMER(props->m_0x08)) {
          minSpeed = 0xDC - D_80075838[props->m_0x04] * 6;
          props->m_0x10 -= 10;
          if (props->m_0x10 < minSpeed) {
            props->m_0x10 = minSpeed;
          }
        }
        moveSpeed = props->m_0x10;
        if ((PATH_CUR_NODE(props->m_0x00).unk_0xC & 0xFFC) != 0) {
          moveSpeed = PATH_CUR_NODE(props->m_0x00).unk_0xC & 0xFFC;
        }
        result = func_80039E94(moby, props->m_0x00, 450, moveSpeed, 0, 0xA,
                               0x28, 0xFF, 1);
        floorHeight = func_80038400(moby, 3000);
        props->m_0x1c -= 0x1E;
        if (props->m_0x1c < -0x190) {
          props->m_0x1c = -0x190;
        }
        if (moby->m_Position.z + props->m_0x1c < floorHeight) {
          moby->m_Position.z = floorHeight;
        } else {
          moby->m_Position.z += props->m_0x1c;
        }
        if ((result & 0x100) != 0 &&
            (PATH_CUR_NODE(props->m_0x00).unk_0xC & 3) == 1) {
          props->m_0x1c = 300;
        }
        if ((props->m_0x00->m_Reversed == -1 &&
             result == (props->m_0x20 | 0x100)) ||
            (props->m_0x00->m_Reversed == 1 &&
             result == (props->m_0x24 | 0x100))) {
          D_80075838[props->m_0x04]++;
          if (D_80075838[props->m_0x04] >= 6) {
            D_80075838[props->m_0x04] = 5;
          }
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        func_80038BB0(props->m_0x00);
        func_80038AFC(props->m_0x00, &nearestNode);
        if (distance < 0x3000) {
          angleDiff = func_80017908(
              ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00)),
              moby->m_Rotation.z);
          pathSteps = 0;
          pathNode = props->m_0x00->m_CurrentNode;
          while (pathNode != nearestNode) {
            pathNode -= props->m_0x00->m_Reversed;
            pathNode = (pathNode + props->m_0x00->m_NodeCount) %
                       props->m_0x00->m_NodeCount;
            pathSteps++;
          }
          if (pathSteps >= 1 && pathSteps <= 7 && angleDiff < 0x10) {
            if (func_80017908(moby->m_Rotation.z,
                              ANGLE_TO_SPYRO(moby->m_Position)) < 0x3A &&
                pathSteps < props->m_0x00->m_NodeCount / 2) {
              props->m_0x00->m_Reversed = -props->m_0x00->m_Reversed;
              props->m_0x00->m_CurrentNode =
                  (props->m_0x00->m_CurrentNode - props->m_0x00->m_Reversed +
                   props->m_0x00->m_NodeCount) %
                  props->m_0x00->m_NodeCount;
            }
          }
        }
        break;

      case 2:
        MoveMobyWithGravity(moby, &props->m_0x18, props->m_0x14, &props->m_0x1c,
                            0xC, 0x10);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x20);
          func_80052568(moby);
          continue;
        }
        break;
      }

      if (moby->m_State != 2 && props->m_0x60 != -1) {
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        func_80052D64(moby, 0, &g_LevelMobys[props->m_0x60].m_Position);
        func_80038340(&g_LevelMobys[props->m_0x60]);
        func_800533D0(&g_LevelMobys[props->m_0x60]);
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_160
    case 160: { // Mushroom Fodder
      Moby160Props *props = moby->m_Props;
      if (moby->m_DamageFlags &
              (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER) &&
          moby->m_State != 1) {
        moby->m_DamageFlags = 0;

        props->m_KnockbackAngle =
            func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                          g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        // This condition can never be fulfilled, as the damage flags were
        // reset already
        if (moby->m_DamageFlags & MOBY_DAMAGE_FLAME) {
          props->m_KnockbackSpeed = 140;
        } else {
          props->m_KnockbackSpeed = 250;
        }

        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
        break;
      } else {
        switch (moby->m_State) {
        case 0:
          func_80039AA8(moby, &props->m_Wander);
          break;
        case 1:
          if (props->m_KnockbackSpeed >= 16) {
            props->m_KnockbackSpeed -= 15;
            func_80039688(moby, props->m_KnockbackAngle,
                          props->m_KnockbackSpeed, 0, 700, 5);
          }
          if (g_AnimationFinished) {
            func_80052568(moby);
            continue;
          }
          break;
        }
        func_800529E4(moby, UPDATE_PROP_COLLISION);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_161
    case 161: { // Gnasty Gnorc
      Moby161Props *props = moby->m_Props;
      int distance;

      distance = DISTANCE_TO_SPYRO(moby);
      ApplyFlameHeat(moby);

      if (moby->m_DamageFlags & MOBY_DAMAGE_FLAME) {
        if (props->m_0x5c == 2) {
          if (OctDistance(&moby->m_Position,
                          &PATH_NODE_POS(props->m_0x00,
                                         props->m_0x00->m_NodeCount - 1)) <
                  3000 &&
              moby->m_State != 7) {
            PathData *tempPath;
            func_8002B390(1, 0xFC, 0);
            g_LevelMobys[props->m_0xc0].m_Substate = 1;
            props->m_0xcc = 0xA0;
            props->m_0x1c = 0;
            props->m_0x20 = 0;
            props->m_0x6c = 0;
            props->m_0x5c++;
            tempPath = props->m_0x00;
            props->m_0x00 = props->m_0x04;
            props->m_0x04 = tempPath;
            moby->m_State = 7;
            MOBY_ANIM_CHANGE(moby, 7);
            continue;
          }
        }
        if (props->m_0x5c == 3) {
          if (OctDistance(&moby->m_Position,
                          &PATH_NODE_POS(props->m_0x00,
                                         props->m_0x00->m_NodeCount - 1)) <
                  3000 &&
              moby->m_State != 8) {
            props->m_0x5c = 4;
            props->m_0x18 = 0xD2;
            props->m_0x14 = ANGLE_FROM_SPYRO(moby->m_Position);
            if (moby->m_DropMoby != 0xFF) {
              D_80077908[30][0] &= ~1;
            }
            func_8003ABC0(moby, 4, 0, 0);
            moby->m_State = 8;
            MOBY_ANIM_CHANGE(moby, 8);
            continue;
          }
        }
      }

      if (props->m_0x5c < 2) {
        Vector3D temp;
        VecCopy(&temp, &moby->m_Position);
        temp.z += 1000;
        if (g_Spyro.m_State == 0xB || g_Spyro.m_State == 0x14) {
          props->m_0xcc = 0x3C;
        }
        if (TICK_TIMER(props->m_0xcc) && distance < 0x4000 &&
            (func_80038250(&temp) != 0 || distance < 0x3000)) {
          g_Spyro.m_ControlFlags = 0x80010000;
          g_Spyro.m_mobyInUseBySpyro = moby;
        }
      }

      if (props->m_0xbc != -1) {
        if (g_LevelMobys[props->m_0xbc].m_Substate != 0 &&
            func_80017908(g_Spyro.m_bodyRotation.z,
                          ANGLE_FROM_SPYRO(moby->m_Position)) < 0x28 &&
            (DISTANCE_TO_SPYRO(moby) < 7000 || props->m_0x68 >= 4)) {
          props->m_0xbc = -1;
          moby->m_State = 10;
          continue;
        }
      }

      if (props->m_0xc4 == 0 && g_Spyro.m_airTime == 0) {
        if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x70) != 0 ||
            func_80038C4C(&g_Spyro.m_Position, &props->m_0xa0) != 0) {
          props->m_0xc4 = 1;
        }
      }

      if (moby->m_State == 6 || moby->m_State == 7) {
        int cameraAngle;
        cameraAngle =
            (ANGLE_FROM(
                 PATH_NODE_POS(props->m_0x08, 0),
                 PATH_NODE_POS(props->m_0x04, props->m_0x04->m_NodeCount - 1)) +
             0x80) &
            0xFF;
        if (!TICK_TIMER(props->m_0xcc)) {
          PathData *path;
          int nodeCount;
          g_Spyro.m_ControlFlags = g_Spyro.m_ControlFlags | 0x80002200;
          path = props->m_0x04;
          nodeCount = path->m_NodeCount;
          g_Spyro.unk_0x220 = &D_80078668;
          D_80078668.m_Coords.azimuth = (-cameraAngle) << 4;
          D_80078668.m_Coords.radius = 6000;
          D_80078668.m_Coords.elevation = 0x19;
          D_80078668.m_Offset.azimuth = 0;
          D_80078668.m_Offset.elevation = -0x32;
          D_80078668.m_Offset.radius = 0;
          g_Spyro.unk_0x21c = &PATH_NODE_POS(path, nodeCount - 1);
          g_ScreenBorderEnabled = 1;
        } else {
          g_ScreenBorderEnabled = 0;
        }
      }

      if (moby->m_State == 8 || moby->m_State == 9) {
        PathData *path;
        int cameraAngle;
        cameraAngle = (g_Spyro.m_bodyRotation.z + 0x40) & 0xFF;
        VecAdd(&PATH_NODE_POS(props->m_0x00, 0), &moby->m_Position,
               &g_Spyro.m_Position);
        VecShiftRight(&PATH_NODE_POS(props->m_0x00, 0), 1);
        g_Spyro.m_ControlFlags = 0x80002200;
        path = props->m_0x00;
        g_Spyro.unk_0x220 = &D_80078668;
        D_80078668.m_Coords.azimuth = (-cameraAngle) << 4;
        D_80078668.m_Coords.radius = 4000;
        D_80078668.m_Coords.elevation = 0x19;
        D_80078668.m_Offset.azimuth = 0;
        D_80078668.m_Offset.elevation = -0x32;
        D_80078668.m_Offset.radius = 0;
        g_Spyro.unk_0x21c = &PATH_NODE_POS(path, 0);
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0: {
        int angle;
        func_80038458(moby);
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (TICK_TIMER(props->m_0x60) && props->m_0xc4 != 0) {
          angle = ANGLE_FROM(g_Camera.m_Position, moby->m_Position);
          if (func_80017908(g_Camera.m_Rotation.z >> 4, angle) < 0x1E &&
              OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0xc8, 0)) < 0x3000 &&
              0x1800 < distance && distance < 0x6800) {
            props->m_0x68 = 0;
            moby->m_State = 2;
            continue;
          }
        }
        break;
      }

      case 2: {
        if (props->m_0x5c == 2) {
          if (SPYRO_BASE_Z_DELTA(moby) < 0 && distance < 5000) {
            moby->m_State = 5;
            continue;
          }
        } else if (props->m_0x5c == 3) {
          if (props->m_0x68 >= 4 || distance < 3600) {
            if (props->m_0x68 >= 4) {
              props->m_0x60 = 150;
            } else {
              props->m_0x60 = 0;
            }
            moby->m_State = 12;
            continue;
          }
        } else if (props->m_0x68 >= 4 ||
                   func_80017908(g_Camera.m_Rotation.z >> 4,
                                 ANGLE_FROM(g_Camera.m_Position,
                                            moby->m_Position)) >= 0x29 ||
                   distance < 6000 || distance > 28000) {
          props->m_0x60 = 150;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        if (RotateMobyToSpyro(moby, 5, 0x14, 1) == 0) {
          continue;
        }
        if (TICK_TIMER(props->m_0x60)) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);
        } else if (g_AnimationFinished) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        }
        if (props->m_0x60 == 0 && moby->m_AnimationState.m_NextFrame >= 9) {
          Moby169Props *projectileProps;
          Vector3D delta;
          Vector3D targetPosition;
          Moby *spawned;
          int stepCount;
          int moveSpeed;
          spawned = g_SpawnMoby(169, moby);
          projectileProps = spawned->m_Props;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 0, &spawned->m_Position);
          spawned->m_Rotation.z = ANGLE_TO_SPYRO(spawned->m_Position);
          VecCopy(&targetPosition, &g_Spyro.m_Position);
          targetPosition.z = func_8004D5EC(&targetPosition, 0x1000);
          VecSub(&delta, &targetPosition, &spawned->m_Position);
          moveSpeed = 0x190;
          stepCount = VecMagnitude(&delta, 0) / moveSpeed;
          projectileProps->m_0x0c = moveSpeed;
          if (stepCount <= 0) {
            stepCount = 1;
          }
          projectileProps->m_0x10 =
              (targetPosition.z - spawned->m_Position.z) / stepCount;
          if (projectileProps->m_0x10 < -500) {
            projectileProps->m_0x10 = -500;
          }
          projectileProps->m_0x00 =
              (TracerPoint *)props->m_0xe0[props->m_0x68 % 3];
          projectileProps->m_0x0a = 0;
          projectileProps->m_0x06 = 0xA0;

          projectileProps->m_0x08 = stepCount - 1;
          props->m_0x68++;
          func_8003851C(moby, 0, props->m_0xd0);
          if (props->m_0x5c == 2 && props->m_0x68 >= 2) {
            moby->m_State = 5;
            continue;
          }
          props->m_0x60 = 0x50;
        }
        break;
      }

      case 3:
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_AnimationFinished) {
          moby->m_State = 5;
          continue;
        }
        break;

      case 4: {
        int floorHeight;
        floorHeight = func_80038400(moby, 3000);
        props->m_0x1c -= 0x19;
        if (props->m_0x1c < -0x190) {
          props->m_0x1c = -0x190;
        }
        if (moby->m_Position.z + props->m_0x1c < floorHeight) {
          moby->m_Position.z = floorHeight;
        } else {
          moby->m_Position.z += props->m_0x1c;
        }
        RotateMobyToSpyro(moby, 4, 0, 0);
        if ((distance < 0x2000 && SPYRO_BASE_Z_DELTA(moby) >= -0x6A3) ||
            distance < 5800) {
          props->m_0x54 = 0;
          moby->m_State = 5;
          continue;
        }
        if (OctDistance(&g_Spyro.m_Position,
                        &PATH_NODE_POS(props->m_0x00, 12)) < 0x2000) {
          VecCopy(
              &moby->m_Position,
              &PATH_NODE_POS(props->m_0x00, props->m_0x00->m_NodeCount - 1));
          func_80038458(moby);
          props->m_0x00->m_CurrentNode = 0;
          moby->m_State = 21;
          continue;
        }
        break;
      }

      case 5: {
        int result;
        int floorHeight;
        int nearestNode;
        int moveSpeed;
        int threshold;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (props->m_0x20 != 0) {
          props->m_0x1c = props->m_0x20;
          props->m_0x20 = 0;
        }
        moveSpeed = 0x13B;
        if ((PATH_CUR_NODE(props->m_0x00).unk_0xC & 0xFFC) != 0) {
          moveSpeed = PATH_CUR_NODE(props->m_0x00).unk_0xC & 0xFFC;
        }
        if (props->m_0x00->m_CurrentNode >= 0xE) {
          threshold = props->m_0x18 > 270 ? 8000 : 6500;
          moveSpeed = props->m_0x00->m_CurrentNode >= 0x1D ? 0xD7 : 0xEB;
          if (distance < threshold && SPYRO_BASE_Z_DISTANCE(moby) < 1200) {
            moveSpeed = 0x122;
          }
        }
        props->m_0x18 = moveSpeed;
        result = func_80039E94(moby, props->m_0x00, 0x200, moveSpeed, 0, 7,
                               0x28, 0xFF, 0);
        floorHeight = func_80038400(moby, 3000);
        props->m_0x1c -= 0x19;
        if (props->m_0x1c < -0x190) {
          props->m_0x1c = -0x190;
        }
        if (moby->m_Position.z + props->m_0x1c < floorHeight) {
          moby->m_Position.z = floorHeight;
        } else {
          moby->m_Position.z += props->m_0x1c;
        }
        if (result == 0x101 && DISTANCE_TO_SPYRO(moby) > 0x2000) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        if (result == 0x100) {
          func_80038AFC(props->m_0x00, &nearestNode);
          if (distance > 0x4800 && nearestNode >= 0x11 &&
              nearestNode < props->m_0x00->m_NodeCount - 1) {
            props->m_0x68 = 0;
            moby->m_State = 2;
            continue;
          }
          props->m_0x58 = 200;
          moby->m_State = 21;
          continue;
        }
        break;
      }
      case 6: {
        int result;
        int floorHeight;
        int moveSpeed;
        int angle;
        if (g_AnimationFinished) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        }
        if (!TICK_TIMER(props->m_0x58)) {
          angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));
          RotateMobyToAngle(moby, angle, 6, 0, 0);
          floorHeight = func_80038400(moby, 3000);
          props->m_0x1c -= 0x19;
          if (props->m_0x1c < -0x190) {
            props->m_0x1c = -0x190;
          }
          if (moby->m_Position.z + props->m_0x1c < floorHeight) {
            moby->m_Position.z = floorHeight;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          } else {
            moby->m_Position.z += props->m_0x1c;
          }
          break;
        }
        if (props->m_0x20 != 0) {
          props->m_0x1c = props->m_0x20;
          props->m_0x20 = 0;
        }
        moveSpeed = 260;
        if ((PATH_CUR_NODE(props->m_0x00).unk_0xC & 0xFFC) != 0) {
          moveSpeed = PATH_CUR_NODE(props->m_0x00).unk_0xC & 0xFFC;
        }
        result = func_80039E94(moby, props->m_0x00, 300, moveSpeed, 0, 0xA,
                               0x28, 0xFF, 0);
        floorHeight = func_80038400(moby, 3000);
        props->m_0x1c -= 0x19;
        if (props->m_0x1c < -0x190) {
          props->m_0x1c = -0x190;
        }
        if (moby->m_Position.z + props->m_0x1c < floorHeight) {
          moby->m_Position.z = floorHeight;
        } else {
          moby->m_Position.z += props->m_0x1c;
        }
        if (result == 0x100) {
          moby->m_State = 12;
          continue;
        }
        if (props->m_0x6c == 0 &&
            OctDistance(&moby->m_Position, &PATH_NODE_POS(props->m_0x00, 6)) <
                600) {
          props->m_0x6c = 1;
          moby->m_State = 11;
          continue;
        }
        if (result & 0x100) {
          switch (PATH_CUR_NODE(props->m_0x00).unk_0xC & 3) {
          case 1:
            props->m_0x20 = 0xDC;
            break;
          case 2:
            props->m_0x20 = 0x10E;
            break;
          case 3:
            props->m_0x20 = 0x140;
            break;
          }
        }
        break;
      }

      case 7:
        if (g_AnimationFinished) {
          props->m_0x58 = 0;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          moby->m_State = 6;
          continue;
        }
        break;

      case 8:
        g_Spyro.m_ControlFlags |= 0x80002000;
        g_ScreenBorderEnabled = 1;
        MoveMobyWithGravity(moby, &props->m_0x18, props->m_0x14, 0, 0xC, 0);
        if (props->m_0xd4 != -1 && moby->m_AnimationState.m_NextFrame >= 6) {
          g_LevelMobys[props->m_0xd4].m_Substate = 1;
          props->m_0xd4 = -1;
        }
        if (props->m_0xd8 != -1 && moby->m_AnimationState.m_NextFrame >= 0xB) {
          g_LevelMobys[props->m_0xd8].m_Substate = 1;
          props->m_0xd8 = -1;
        }
        if (props->m_0xdc != -1 && moby->m_AnimationState.m_NextFrame >= 0x10) {
          g_LevelMobys[props->m_0xdc].m_Substate = 1;
          props->m_0xdc = -1;
        }
        if (g_IsSpyroHidden == 0 && moby->m_AnimationState.m_NextFrame >= 0xE) {
          Moby *spawned;
          Moby414Props *spawnedProps;
          spawned = g_SpawnMoby(414, moby);
          spawnedProps = spawned->m_Props;
          spawnedProps->m_Target = moby;
          VecCopy(&spawned->m_Position, &g_Spyro.m_Position);
          spawned->m_Rotation.x = g_Spyro.m_bodyRotation.x;
          spawned->m_Rotation.y = g_Spyro.m_bodyRotation.y;
          spawned->m_Rotation.z = g_Spyro.m_bodyRotation.z;
          g_IsSpyroHidden = 1;
        }
        if (g_AnimationFinished) {
          moby->m_RenderRadius = 0;
          moby->m_WasDrawn = 0;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x40);
          props->m_0x58 = 0x3C;
          moby->m_State = 9;
          continue;
        }
        break;

      case 9:
        g_Spyro.m_ControlFlags |= 0x80002000;
        TICK_TIMER(props->m_0x58);
        if (props->m_0x58 < 0x10) {
          g_Fade = 0x10 - props->m_0x58;
          if (g_Fade >= 0x10) {
            g_Fade = 0xF;
          }
        }
        if (props->m_0x58 == 0) {
          g_LevelVortexExitFlags[g_LevelIndex] = 1;
          g_CreditsSequence = 0;
          g_CutsceneIdx = 2;
          g_Gamestate = 0xE;
          g_StateSwitch = 1;
          g_ScreenBorderEnabled = 0;
          g_IsSpyroHidden = 0;
          g_CutsceneLayout->m_CurrentTick = 0;
        }
        break;

      case 10: {
        int angle;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        angle = ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x00, 1));
        if (RotateMobyToAngle(moby, angle, 7, 0x14, 1) != 0) {
          func_80039398(moby, 0xF0, 0, 0, 5);
        }
        if (OctDistance(&moby->m_Position, &PATH_NODE_POS(props->m_0x00, 1)) <
            800) {
          props->m_0x5c = 2;
          props->m_0x00->m_CurrentNode = 2;
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;
      }

      case 11: {
        int floorHeight;
        floorHeight = func_80038400(moby, 3000);
        props->m_0x1c -= 0x19;
        if (props->m_0x1c < -0x190) {
          props->m_0x1c = -0x190;
        }
        if (moby->m_Position.z + props->m_0x1c < floorHeight) {
          moby->m_Position.z = floorHeight;
        } else {
          moby->m_Position.z += props->m_0x1c;
        }
        if (RotateMobyToSpyro(moby, 5, 0, 0) != 0 &&
            moby->m_AnimationState.m_NextAnimation != 4) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 4);
        }
        if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x88) != 0) {
          func_8002B390(0, 0xFC, 0);
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          moby->m_State = 6;
          continue;
        }
        break;
      }

      case 12: {
        int floorHeight;
        floorHeight = func_80038400(moby, 3000);
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        props->m_0x1c -= 0x19;
        if (props->m_0x1c < -0x190) {
          props->m_0x1c = -0x190;
        }
        if (moby->m_Position.z + props->m_0x1c < floorHeight) {
          moby->m_Position.z = floorHeight;
        } else {
          moby->m_Position.z += props->m_0x1c;
        }
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (props->m_0x60 == 0 && distance >= 3600 && distance < 9400 &&
            g_Spyro.m_airTime == 0) {
          props->m_0x68 = 0;
          moby->m_State = 2;
          continue;
        }
        if (TICK_TIMER(props->m_0x60) && distance < 3600) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
          moby->m_State = 13;
          continue;
        }
        break;
      }

      case 13:
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_AnimationFinished) {
          props->m_0x60 = 0x78;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          moby->m_State = 12;
          continue;
        }
        break;

      case 20:
        if (TICK_TIMER(props->m_0x58)) {
          moby->m_State = 5;
          continue;
        }
        if (RotateMobyToSpyro(moby, 6, 0, 0) != 0 &&
            moby->m_AnimationState.m_NextAnimation != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 0);
        }
        break;

      case 21:
        if (RotateMobyToSpyro(moby, 6, 0, 0) != 0 &&
            moby->m_AnimationState.m_NextAnimation != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 0);
        }
        if (TICK_TIMER(props->m_0x58)) {
          if (SPYRO_BASE_Z_DELTA(moby) < 0 && DISTANCE_TO_SPYRO(moby) < 9500) {
            moby->m_State = 5;
            continue;
          }
        }
        if (distance < 3600) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_162
    case 162: {
      Moby162Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State == 0) {
        Moby *spawned;
        int angle;
        int i;

        spawned = g_SpawnMoby(props->m_0x18 + 344, moby);
        if (spawned != 0) {
          spawned->m_State = 1;
        }

        RegisterFlightMobyCollectibleType(props->m_0x1c);

        i = 0;
        props->m_0x28 = 200;
        props->m_0x30 = 350;

        angle = ANGLE_FROM_SPYRO(moby->m_Position);

        props->m_0x2c =
            func_80038178(angle, g_Spyro.m_bodyRotation.z, 0x28, 0x40);

        for (i = 0; i < 3 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(359, moby);
          g_SpawnMoby(360, moby);
          g_SpawnMoby(361, moby);
        }

        func_8003851C(moby, 0, 0);
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
        break;
      }

      switch (moby->m_State) {
      case 0: {
        int rotation;

        if (props->m_0x40 == 0xFF) {
          props->m_0x00->m_CurrentNode++;

          if (props->m_0x00->m_CurrentNode >= props->m_0x00->m_NodeCount) {
            props->m_0x00->m_CurrentNode = 0;
          }

          props->m_0x40 = 0;
          VecNull(&props->m_0x34);
        }

        rotation = moby->m_Rotation.z;

        if (g_Spyro.m_walkingState < 8) {
          if (func_8003BFC0(moby, props->m_0x00, &props->m_0x34, &props->m_0x40,
                            0xA, 4) == 2) {
            props->m_0x14 = (props->m_0x14 + 1) & 3;

            switch (props->m_0x14) {
            case 0:
              props->m_0x00 = props->m_0x04[0];
              break;
            case 1:
              props->m_0x00 = props->m_0x04[1];
              break;
            case 2:
              props->m_0x00 = props->m_0x04[2];
              break;
            case 3:
              props->m_0x00 = props->m_0x04[3];
              break;
            }

            props->m_0x00->m_CurrentNode = 0;
          }
        }

        rotation = (moby->m_Rotation.z - rotation) & 0xFF;

        if (rotation > 0x80) {
          rotation -= 0x100;
        }

        props->m_0x24 +=
            ((-rotation * 192) - props->m_0x24 * 8 - props->m_0x20) >> 6;

        props->m_0x20 = (props->m_0x20 + props->m_0x24) & 0xFFF;

        if (props->m_0x20 > 0x800) {
          props->m_0x20 -= 0x1000;
        }

        if (props->m_0x20 < -0x140) {
          props->m_0x20 = -0x140;
        }

        if (props->m_0x20 > 0x140) {
          props->m_0x20 = 0x140;
        }

        moby->m_Rotation.x = props->m_0x20 >> 4;
        break;
      }

      case 1:
        if (g_AnimationFinished) {
          moby->m_State = 2;
          MOBY_ANIM_SET_NEXT(moby, 2);
          continue;
        }

      case 2:
        RotateMobyToSpyro(moby, 4, 0, 0);

        if (MoveMobyWithGravity(moby, &props->m_0x30, props->m_0x2c,
                                &props->m_0x28, 0xC, 0xC) == 3) {
          PlaySound(g_Spu.m_SoundTable->waterSplash, moby, 8,
                    &moby->m_SoundChannel);

          g_SpawnMoby(400, moby);
          func_80052568(moby);
          continue;
        }

        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_163
    case 163: {
      Moby163Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) && moby->m_State == 0) {
        Moby *spawned;
        RegisterFlightMobyCollectibleType(props->m_0x04);
        spawned = g_SpawnMoby(props->m_0x00 + 344, moby);
        if (spawned != 0) {
          spawned->m_State = 1;
        }

        props->m_0x18 = 100;
        props->m_0x20 = 350;
        props->m_0x1c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x28, 0x40);
        func_8003851C(moby, 0, 0);
        g_SpawnMoby(232, moby);
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
      } else {
        switch (moby->m_State) {
        case 0:
          func_8003851C(moby, 0, &moby->m_SoundChannel);
          props->m_0x08 += g_DeltaTime;
          if (props->m_0x08 >= 480) {
            props->m_0x08 -= 480;
          }
          moby->m_Position.z = props->m_0x14 +
                               (COSINE_8((props->m_0x08 << 8) / 480) >> 1) +
                               0x800;
          break;
        case 1:
          if (g_AnimationFinished) {
            moby->m_State = 2;
            MOBY_ANIM_SET_NEXT(moby, 2);
            break;
          }
        case 2:
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (MoveMobyWithGravity(moby, &props->m_0x20, props->m_0x1c,
                                  &props->m_0x18, 0xC, 0xC) == 3) {
            PlaySound(g_Spu.m_SoundTable->waterSplash, moby, 8,
                      &moby->m_SoundChannel);
            g_SpawnMoby(400, moby);
            func_80052568(moby);
          }
          break;
        }
      }

      break;
    }
#endif
#ifdef HAS_MOBY_165
    case 165: {
      Moby165Props *props;
      Moby165Props *linkedProps;
      int angle;

      props = moby->m_Props;

      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 2) {
        if (moby->m_DamageFlags != MOBY_DAMAGE_FLAME || props->m_0x18 == 0) {
          props->m_0x14 = 0x8c;
          props->m_0x10 = 0x118;
          props->m_0x08 = 0x28;

          if (moby->m_DamageFlags == MOBY_DAMAGE_CHARGE) {
            props->m_0x14 = 170;
            props->m_0x10 = 350;
            props->m_0x08 = 0x3c;
          }

          angle = ANGLE_FROM_SPYRO(moby->m_Position);
          props->m_0x0c =
              func_80038178(angle, g_Spyro.m_bodyRotation.z, 0x20, 0x40);

          props->m_0x1c = 0x10 - (rand() & 0x1f);
          props->m_0x1e = 0x10 - (rand() & 0x1f);

          moby->m_DamageFlags = 0;
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);

          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0:
        switch (props->m_0x04) {
        case 0:
          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x00, 0)) < 0x1c00) {
            if (func_80017908(ANGLE_TO_SPYRO(moby->m_Position),
                              ANGLE_FROM(moby->m_Position,
                                         PATH_NODE_POS(props->m_0x00, 0))) >=
                    ROTDEG8(30) ||
                DISTANCE_TO_SPYRO(moby) >
                    OctDistance(&moby->m_Position,
                                &PATH_NODE_POS(props->m_0x00, 0))) {
              props->m_0x00->m_CurrentNode = 0;
              moby->m_State = 3;
              continue;
            }
          } else if (OctDistance(&g_Spyro.m_Position,
                                 &PATH_NODE_POS(props->m_0x00, 1)) < 0x1c00) {
            if (func_80017908(ANGLE_TO_SPYRO(moby->m_Position),
                              ANGLE_FROM(moby->m_Position,
                                         PATH_NODE_POS(props->m_0x00, 1))) >=
                    ROTDEG8(30) ||
                DISTANCE_TO_SPYRO(moby) >
                    OctDistance(&moby->m_Position,
                                &PATH_NODE_POS(props->m_0x00, 1))) {
              props->m_0x00->m_CurrentNode = 1;
              moby->m_State = 3;
              continue;
            }
          }
          break;

        case 1:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

          func_80039E94(moby, props->m_0x00, 0x100, 0x5a, 200, 5, 0xa,
                        moby->m_Pod, 5);

          if (DISTANCE_TO_SPYRO(moby) < 0x1400) {
            func_8003B1E8(moby, 0x14);
          }

          break;

        case 2:
          RotateMobyToSpyro(moby, 4, 0, 0);

          if (g_AnimationFinished &&
              moby->m_AnimationState.m_NextAnimation != 0) {
            g_AnimationFinished = 0;
            MOBY_ANIM_ADVANCE(moby, 0);
          }

          if (DISTANCE_TO_SPYRO(moby) < 0x1800) {
            moby->m_Substate = 0;
            props->m_0x08 = RandRange(0x8c, 200);
            moby->m_State = 1;
            continue;
          }
          break;
        case 3:
          switch (props->m_0x24) {
          case 0:
            RotateMobyToSpyro(moby, 4, 0, 0);

            if (DISTANCE_TO_SPYRO(moby) < 0x2000 &&
                SPYRO_BASE_Z_DELTA(moby) < 0 && g_Spyro.m_airTime == 0) {
              linkedProps = (Moby165Props *)g_LevelMobys[props->m_0x28].m_Props;
              props->m_0x24 = 1;
              linkedProps->m_0x08 = RandRange(0, 0xf);
              linkedProps->m_0x24 = 1;
            }

            break;

          case 1:
            if (TICK_TIMER(props->m_0x08)) {
              props->m_0x24++;
            }

            break;

          case 2:
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);

            if (g_AnimationFinished) {
              props->m_0x24++;
            }

            break;

          case 3:
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

            if (func_80039E94(moby, props->m_0x00, 0x100, 150, 0, 8, 0x32, 0xff,
                              5) == 0x100) {
              props->m_0x24++;
            }

            break;

          case 4:
            if (RotateMobyToSpyro(moby, 6, 0xa, 1)) {
              moby->m_State = 1;
              continue;
            }
            break;
          }
          break;
        }
        break;

      case 1:
        RotateMobyToSpyro(moby, 6, 0, 0);
        switch (props->m_0x20) {
        case 0:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
          props->m_0x18 = 1;
          if (TICK_TIMER(props->m_0x08) && g_AnimationFinished) {
            props->m_0x20 = 1;
            props->m_0x18 = 0;

            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
          }
          break;
        case 1:
          if (TICK_TIMER(props->m_0x08) && DISTANCE_TO_SPYRO(moby) < 1400 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 1000 &&
              moby->m_AnimationState.m_Animation == 5) {

            props->m_0x08 = 0xb4;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 6);
          }

          if (g_AnimationFinished) {
            if (moby->m_AnimationState.m_Animation == 6) {
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
            } else {
              props->m_0x18 = 1;
              props->m_0x20 = 0;
              props->m_0x08 = RandRange(0x8c, 200);

              if (moby->m_AnimationState.m_Animation != 4) {
                moby->m_AnimationState.m_FrameProgress = 8;
                moby->m_AnimationState.m_PerFrameProgress = 8;
                moby->m_AnimationState.m_Animation =
                    moby->m_AnimationState.m_NextAnimation;
                moby->m_AnimationState.m_NextAnimation = 4;
                moby->m_AnimationState.m_Frame =
                    moby->m_AnimationState.m_NextFrame;
                moby->m_AnimationState.m_NextFrame = 0;
                func_80037E98(moby);
              }
            }
          }
          break;
        }

        if (DISTANCE_TO_SPYRO(moby) > 0x2000) {
          moby->m_State = 0;
          continue;
        }
        break;

      case 2:
        moby->m_Rotation.x += props->m_0x1c;
        moby->m_Rotation.y += props->m_0x1e;

        MoveMobyWithGravity(moby, &props->m_0x10, props->m_0x0c, &props->m_0x14,
                            0xc, 0xc);

        if (g_AnimationFinished &&
            moby->m_AnimationState.m_NextAnimation == 2 &&
            moby->m_AnimationState.m_Animation != 3) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 3);
        }

        if (TICK_TIMER(props->m_0x08)) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x20);
          func_80052568(moby);
          continue;
        }
        break;

      case 3:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));

        if (RotateMobyToAngle(moby, angle, 6, 0x14, 1) != 0) {
          func_80039398(moby, 0x8c, 0, 0, 5);
        }

        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <
                0x100 ||
            DISTANCE_TO_SPYRO(moby) < 0xc00) {
          if (moby->m_AnimationState.m_Animation != 4) {
            moby->m_AnimationState.m_FrameProgress = 8;
            moby->m_AnimationState.m_PerFrameProgress = 8;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation = 4;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 0;
            func_80037E98(moby);
          }

          moby->m_State = 1;
          continue;
        }
        break;
      case 20:
        if (RotateMobyToSpyro(moby, 7, 0x14, 1) != 0) {
          moby->m_State = 21;
          continue;
        }
        break;
      case 21:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);

        if (g_AnimationFinished) {
          props->m_0x20 = 0;

          if (moby->m_AnimationState.m_Animation != 4) {
            moby->m_AnimationState.m_FrameProgress = 8;
            moby->m_AnimationState.m_PerFrameProgress = 8;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation = 4;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 0;
            func_80037E98(moby);
          }

          moby->m_State = 1;
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_166
    case 166: {
      Moby166Props *props;
      int angle, angle2;
      int pathAngle;
      int distance;
      int pathDistance;
      int pathEnded;
      int distanceOk;
      int nodeIndex[2];
      props = (Moby166Props *)moby->m_Props;

      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 1) {
        angle = ANGLE_TO_SPYRO(moby->m_Position);

        if (func_80017908(moby->m_Rotation.z, angle) >= ROTDEG8(100)) {
          moby->m_DamageFlags = 0;
          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);

          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0:
        pathAngle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));
        pathEnded = 0;
        if (func_80017908(pathAngle, moby->m_Rotation.z) < 0x10) {
          RotateMobyToAngle(moby, pathAngle, 5, 0, 0);
          func_80039688(moby, pathAngle, 0x50, 0, 0, 5);

          if (props->m_0x08 != 0 ||
              OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <
                  0x80) {
            if (props->m_0x00->m_Reversed == 1) {
              if (props->m_0x00->m_CurrentNode + 1 ==
                  props->m_0x00->m_NodeCount) {
                props->m_0x00->m_Reversed = -props->m_0x00->m_Reversed;
                props->m_0x00->m_CurrentNode = props->m_0x00->m_NodeCount - 2;
                pathEnded = 1;
              } else {
                props->m_0x00->m_CurrentNode += props->m_0x00->m_Reversed;
              }
            } else {
              if (props->m_0x00->m_CurrentNode == 0) {
                props->m_0x00->m_Reversed = -props->m_0x00->m_Reversed;
                props->m_0x00->m_CurrentNode = 1;
                pathEnded = 1;
              } else {
                props->m_0x00->m_CurrentNode += props->m_0x00->m_Reversed;
              }
            }
          }
        } else {
          RotateMobyToAngle(moby, pathAngle, 5, 0, 0);
        }

        if (pathEnded != 0) {
          if (props->m_0x04 == 2) {
            props->m_0x0c = 1;
          } else {
            props->m_0x0c = 0;
          }

          if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
            if (func_80017908(moby->m_Rotation.z,
                              ANGLE_TO_SPYRO(moby->m_Position)) < 0x40) {
              if (props->m_0x04 == 0 || RandRange(0, 2) == 0) {
                props->m_0x04 = 2;
                moby->m_State = 6;
                MOBY_ANIM_CHANGE(moby, 6);
                continue;
              }
            }
          }

          props->m_0x04 = 1;
        }

        props->m_0x08 = 0;

        if (TICK_TIMER(props->m_0x10) && SPYRO_BASE_Z_DELTA(moby) >= -0x1f3) {
          int attackDistance = DISTANCE_TO_SPYRO(moby);
          pathDistance =
              OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));

          if (props->m_0x0c != 0) {
            if (attackDistance < pathDistance + 0x2000) {
              distanceOk = attackDistance < 0x2400;
            } else {
              distanceOk = 0;
            }
          } else {
            if (attackDistance < pathDistance + 0x1400) {
              distanceOk = attackDistance < 0x1800;
            } else {
              distanceOk = 0;
            }
          }

          if (distanceOk != 0) {
            if (func_80017908(ANGLE_TO_SPYRO(moby->m_Position),
                              ANGLE_FROM(moby->m_Position,
                                         PATH_CUR_POS(props->m_0x00))) < 0x20) {
              moby->m_Substate = 0;
              moby->m_State = 2;
              MOBY_ANIM_CHANGE(moby, 2);
              continue;
            }
          }
        }

        break;

      case 2: {
        props->m_0x08 = 1;

        if (moby->m_Substate == 0) {
          distance = DISTANCE_TO_SPYRO(moby);

          if (RotateMobyToSpyro(moby, 5, 0x14, 1) == 0) {
            continue;
          }

          if (func_80039398(moby, 0x78, 0, 500, 0x15) != 0) {
            props->m_0x10 = 0x78;
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }

          if (distance < 1500) {
            moby->m_Substate++;
          }

          if (func_80038A40(moby, props->m_0x00, nodeIndex) <= 1500) {
            break;
          }

          angle = ANGLE_FROM(moby->m_Position,
                             PATH_NODE_POS(props->m_0x00, nodeIndex[0]));
          angle2 = ANGLE_FROM(moby->m_Position,
                              PATH_NODE_POS(props->m_0x00, 1 - nodeIndex[0]));

          if (func_80017908(angle, angle2) >= 0x20) {
            break;
          }

          angle2 = ANGLE_TO_SPYRO(moby->m_Position);

          if (func_80017908(angle, angle2) >= 0x20) {
            break;
          }

          props->m_0x10 = 0x78;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);

        if (g_AnimFrameFinished && moby->m_AnimationState.m_Frame == 4) {
          Vector3D vec;
          VecSub(
              &vec, &PATH_CUR_POS(props->m_0x00),
              &PATH_NODE_POS(props->m_0x00, (props->m_0x00->m_CurrentNode - 1 +
                                             props->m_0x00->m_NodeCount) %
                                                props->m_0x00->m_NodeCount));
          VecScaleToLength(&vec, VecMagnitude(&vec, 0), 150);

          g_Spyro.m_ControlFlags = 0x80000147;
          g_Spyro.unk_0x208.x = vec.x;
          g_Spyro.unk_0x208.y = vec.y;
          g_Spyro.unk_0x208.z = 0x78;
          g_Spyro.m_fallingState = 6;

          if (D_80075904 < 0xf) {
            D_80075904 = 0xf;
          }
        }
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      case 1:
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x48);
          func_80052568(moby);
          continue;
        }
        break;
      case 6:
      case 7:
        RotateMobyToSpyro(moby, 5, 0, 0);

        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_169
    case 169: {
      Moby169Props *props;
      Moby143Props *blastProps;
      int activePoints;
      int tracerPointIndex;
      int state;
      int i;

      props = moby->m_Props;
      state = moby->m_State;
      if (state < 3) {
        if (state >= 0) {
          Vector3D oldPosition;
          VecCopy(&oldPosition, &moby->m_Position);
          if (moby->m_State == 0) {
            props->m_0x04 += g_DeltaTime;
            if (props->m_0x04 >= 10) {
              Moby *spawned;
              spawned = g_SpawnMoby(168, moby);
              VecCopy(&spawned->m_Position, &moby->m_Position);
              spawned->m_Substate = 0;
              spawned->m_Rotation.y = Atan2(props->m_0x0c, props->m_0x10, 0);
              spawned->m_Rotation.z = moby->m_Rotation.z;
              spawned->m_RenderRadius = 0x50;
              props->m_0x04 = 0;
            }
            moby->m_Position.x +=
                FIXED_MUL(props->m_0x0c, COSINE_8(moby->m_Rotation.z));
            moby->m_Position.y +=
                FIXED_MUL(props->m_0x0c, SINE_8(moby->m_Rotation.z));
            moby->m_Position.z += props->m_0x10;
            if (TICK_TIMER(props->m_0x06)) {
              moby->m_State = 1;
            }
            if (moby->m_Position.x < 0 || moby->m_Position.y < 0 ||
                moby->m_Position.z < 0) {
              moby->m_RenderRadius = 0;
              moby->m_WasDrawn = 0;
              moby->m_State = 1;
              continue;
            }
            props->m_0x08--;
            if (props->m_0x08 < 0) {
              props->m_0x08 = 0;
            }
            if (props->m_0x08 == 0 &&
                func_8004AE38(&oldPosition, &moby->m_Position) != 0) {
              Moby *spawned;
              spawned = g_SpawnMoby(143, moby);
              blastProps = spawned->m_Props;
              blastProps->m_0x00 = 0x190;
              blastProps->m_0x04 = 0x12;
              spawned->m_ScaleOverride = 48000 / blastProps->m_0x00;
              if (spawned->m_ScaleOverride < 5) {
                spawned->m_ScaleOverride = 5;
              }
              if (spawned->m_ScaleOverride >= 0x80) {
                spawned->m_ScaleOverride = 0x7F;
              }
              moby->m_State = 1;
              func_8003851C(moby, 0, 0);
            }
            if (moby->m_State == 1) {
              moby->m_RenderRadius = 0;
              moby->m_WasDrawn = 0;
            }
          }

          activePoints = 0;
          if (moby->m_State == 0 && g_TracerCount < 3 && props->m_0x0a < 0x78) {
            tracerPointIndex = props->m_0x0a;
            VecCopy(&props->m_0x00[tracerPointIndex].WorldPos,
                    &moby->m_Position);
            props->m_0x00[tracerPointIndex].Age = 0;
            props->m_0x0a++;
          }
          for (i = 0; i < props->m_0x0a; i++) {
            props->m_0x00[i].Age += g_DeltaTime;
            if (props->m_0x00[i].Age < 0x51) {
              activePoints++;
            }
          }
          if (activePoints == 0 && moby->m_State != 0) {
            func_80052568(moby);
            continue;
          }
          if (g_TracerCount < 3) {
            g_TracerPointCount[g_TracerCount] = props->m_0x0a;
            g_TracerLists[g_TracerCount] = props->m_0x00;
            g_TracerCount++;
          }
          if (moby->m_State == 1) {
            moby->m_State = 2;
          }
        }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_171
    case 171: { // Twilight Harbor Bridge Crank
      Moby171Props *props = moby->m_Props;

      if (moby->m_DamageFlags & MOBY_DAMAGE_FLAME) {
        func_8003851C(moby, 0, &moby->m_SoundChannel);
        if (props->m_Timer == 0) {
          // Toggle Bridge
          func_8002B390(0, 0xFC, 0);
          // Keep spinning for 1.33s
          props->m_Timer = 80;
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          continue;
        }
      }
      if (TICK_TIMER(props->m_Timer) && g_AnimationFinished) {
        // Stop spinning Crank and put it in resting position
        func_800562A4(moby, 1);
        moby->m_State = 0;
        MOBY_ANIM_RESTART(moby, 0);
        continue;
      }
      moby->m_DamageFlags = 0;
      break;
    }
#endif
    case MOBYCLASS_KEY: {
      Moby173Props *keyProps = moby->m_Props;

      if (moby->m_Substate == 0) {
        moby->m_Rotation.x = COSINE_8(keyProps->m_0x02) >> 7;
        moby->m_Rotation.y = SINE_8(keyProps->m_0x02) >> 7;
        keyProps->m_0x02 += g_DeltaTime * 2;

        if (DISTANCE_TO_SPYRO(moby) < 512) {
          if (SPYRO_BASE_Z_DISTANCE(moby) < 512) {
            int i;
            PlaySound(g_Spu.m_SoundTable->gemPickup, moby, 0x10, nullptr);
            func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
            for (i = 0; i < 6; i++) {
              g_SpawnParticle(1, 12, moby, 0x8080 + 0x01000000 * i);
            }
            g_KeyFlag = 1;
            moby->m_RenderRadius = 0;
            moby->m_UpdateDistance = 0;
            moby->m_WasDrawn = 0;
            moby->m_ShadowDistance = 0;
            moby->m_ScaleOverride = 0x40;
            moby->m_SectorIndex = 0xFF;
            moby->m_Substate = 2;
          }
        }

        if (keyProps->m_0x03 != 0xFF) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &D_8006E5AC,
                            &g_Sparkles[keyProps->m_0x03].m_Position);
          VecAdd(&g_Sparkles[keyProps->m_0x03].m_Position,
                 &g_Sparkles[keyProps->m_0x03].m_Position, &moby->m_Position);
          if (g_Sparkles[keyProps->m_0x03].m_Life < 5) {
            keyProps->m_0x03 = 0xFF;
          }
        } else if (keyProps->m_0x00 >= 248) {
          int handle = SpawnMobySparkle(moby, &D_8006E5AC);
          if (handle >= 0 && DISTANCE_TO_SPYRO(moby) < 0x4000) {
            keyProps->m_0x03 = handle;
          }
          keyProps->m_0x00 = (rand() & 0x3F) + 24;
        }
        keyProps->m_0x00 += g_DeltaTime;
      }
      break;
    }
#ifdef HAS_MOBY_174
    case MOBYCLASS_LOCKED_CHEST: {
      Vector3D vec1;
      Vector3D vec2;
      Moby174Props *props = moby->m_Props;
      Moby *keyMoby = &g_LevelMobys[props->m_KeyLinkIndex];

      if (moby->m_DamageFlags & MOBY_DAMAGE_SUPER) {
        moby->m_Substate = 2;
        props->m_0x04 = 0xd2;
      }

      if (moby->m_Substate < 2) {
        if (props->m_0x04 != 0) {
          props->m_0x04 += g_DeltaTime;

          if (props->m_0x04 < 0x40) {
            moby->m_Rotation.x =
                props->m_0x08 + g_MobyShakeOffsets[props->m_0x04 >> 1][0];
            moby->m_Rotation.y =
                props->m_0x0c + g_MobyShakeOffsets[props->m_0x04 >> 1][1];
            moby->m_Position.z =
                props->m_0x10 +
                (ABS2(g_MobyShakeOffsets[props->m_0x04 >> 1][0]) +
                 ABS2(g_MobyShakeOffsets[props->m_0x04 >> 1][1])) *
                    8;
          } else {
            props->m_0x04 = 0;
            moby->m_Rotation.x = props->m_0x08;
            moby->m_Rotation.y = props->m_0x0c;
            moby->m_Position.z = props->m_0x10;
          }
        } else if (moby->m_DamageFlags &
                   (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE |
                    MOBY_DAMAGE_SUPER)) {
          props->m_0x04 = 1;
          props->m_0x08 = moby->m_Rotation.x;
          props->m_0x0c = moby->m_Rotation.y;
          props->m_0x10 = moby->m_Position.z;
        }
      }

      switch (moby->m_Substate) {
      case 0:
        if (g_KeyFlag == 0 || g_KeyFlag == 3) {
          g_KeyFlag = 0;
          moby->m_UpdateDistance = 0x10;
          keyMoby->m_UpdateDistance = 0x40;
          keyMoby->m_RenderRadius = 0x18;
        } else {
          g_KeyFlag = 1;
          moby->m_Substate = 1;
          keyMoby->m_ScaleOverride = 0x40;
          keyMoby->m_ShadowDistance = 0;
          keyMoby->m_SectorIndex = 0xff;
          keyMoby->m_Substate = 2;
        }
        break;

      case 1:
        if (g_KeyFlag == 1 &&
            (g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
             g_Spyro.m_State == 0x15 || g_Spyro.m_State == 2) &&
            DISTANCE_TO_SPYRO(moby) < 0x600 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x200) {
          if (func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) < 0x30) {
            if (func_80017908(moby->m_Rotation.z,
                              ANGLE_TO_SPYRO(moby->m_Position)) < 0x30) {
              g_Spyro.m_ControlFlags = 0x80002000;
              func_8003DFA4();
              VecNull(&g_Spyro.m_HeadLookTarget);

              moby->m_Substate = 2;

              if (props->m_0x04 > 0) {
                props->m_0x04 = 0;
                moby->m_Rotation.x = props->m_0x08;
                moby->m_Rotation.y = props->m_0x0c;
                moby->m_Position.z = props->m_0x10;
              }

              keyMoby->m_Rotation.x = 0;
              keyMoby->m_Rotation.y = 0;
              keyMoby->m_Rotation.z = g_Spyro.m_bodyRotation.z + 0x80;
            }
          }
        }
        break;

      case 2: {
        int i;
        if (g_Pad.m_Down & PAD_CROSS) {
          props->m_0x04 = 0xd2;
        }

        g_Spyro.m_ControlFlags = 0x80002000;
        keyMoby->m_RenderRadius = 0x18;
        props->m_0x04 += g_DeltaTime;
        g_ScreenBorderEnabled = 1;

        if (props->m_0x04 < 0xc0) {
          vec1.x = 0x200;
          vec1.y = 0;
          vec1.z = 0x140;

          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vec1, &vec1);
          VecAdd(&vec1, &vec1, &moby->m_Position);
          VecSub(&vec1, &vec1, &g_Spyro.m_Position);
          vec1.z -= 0x100;
          VecShiftRight(&vec1, 5);
          VecMult(&vec1, &vec1, props->m_0x04);
          func_800177F8(&vec1, &vec1, 6);
          VecAdd(&vec1, &vec1, &g_Spyro.m_Position);

          vec1.z += 0x100;
          vec1.z += SINE_8((props->m_0x04 * 128) / 192) >> 3;
          VecCopy(&keyMoby->m_Position, &vec1);

          g_Spyro.m_HeadLookTarget.y = SINE_8((props->m_0x04 * 128) / 192) >> 3;

          if (props->m_0x04 < 0x40) {
            int rotTemp;
            keyMoby->m_Rotation.y = -props->m_0x04;
            rotTemp = g_Spyro.m_bodyRotation.z + 0x80;
            keyMoby->m_Rotation.z = rotTemp + props->m_0x04 * 4;
          } else if (props->m_0x04 < 0x80) {
            int rotTemp;
            keyMoby->m_Rotation.y = 0xc0;
            rotTemp = g_Spyro.m_bodyRotation.z + 0x80;
            keyMoby->m_Rotation.z = rotTemp + (props->m_0x04 - 0x40) * 3;
          } else {
            int rotTemp;
            int angleDelta;
            angleDelta = func_80017908(
                moby->m_Rotation.z, (g_Spyro.m_bodyRotation.z + 0x40) & 0xff);
            rotTemp = g_Spyro.m_bodyRotation.z + 0x40;
            keyMoby->m_Rotation.z =
                rotTemp + ((angleDelta * (props->m_0x04 - 0x80)) / 0x40);
          }
        } else if (props->m_0x04 < 0xd0) {

          keyMoby->m_Rotation.z = moby->m_Rotation.z;
          vec2.x = 0x200 - ((props->m_0x04 - 0xc0) << 3);
          vec2.y = 0;
          vec2.z = 0x140;
          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vec2, &vec2);
          VecAdd(&keyMoby->m_Position, &vec2, &moby->m_Position);
        }

        if (!(props->m_0x04 < 0xd0 &&
              (g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
               g_Spyro.m_State == 0x15 || g_Spyro.m_State == 2 ||
               g_Spyro.m_State == 3))) {
          keyMoby->m_RenderRadius = 0;
          keyMoby->m_UpdateDistance = 0;
          keyMoby->m_WasDrawn = 0;
          g_ScreenBorderEnabled = 0;

          moby->m_SoundDistance = 0x20;
          func_8003851C(moby, 0, 0);

          for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(310, moby);
            g_SpawnMoby(311, moby);
          }

          for (i = 0; i < 10 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(309, moby);
          }

          g_SpawnParticle(32, 70, &moby->m_Position, 24);
          g_KeyMoby = (Moby *)func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);
          func_80052568(moby);

          g_KeyFlag = 2;
          g_Spyro.m_HeadLookTarget.z = 0;
          g_Spyro.m_HeadLookTarget.y = 0;
          g_Spyro.m_HeadLookTarget.x = 0;
        }

        func_800529E4(keyMoby, 4);

        if (props->m_0x04 - (props->m_0x04 / 4 * 4) < 2) {
          g_SpawnParticle(1, 12, keyMoby, 0x8080);
        } else {
          g_SpawnParticle(1, 12, keyMoby, 0x5008080);
        }
      }
      }

      props->m_0x14 = ApplyFlameHeatExternal(moby, props->m_0x14);
      moby->m_DamageFlags = 0;
      break;
    }
#endif
#ifdef HAS_MOBY_176
    case 176: {
      Moby176Props *props = moby->m_Props;

      if (moby->m_Substate == 0) {
        break;
      }

      switch (moby->m_State) {
      case 0: {
        Vector3D oldPosition;
        Vector3D particleVelocity;

        VecCopy(&oldPosition, &moby->m_Position);
        moby->m_Position.x += FIXED_MUL(props->m_0x04, COSINE_8(props->m_0x0c));
        moby->m_Position.y += FIXED_MUL(props->m_0x04, SINE_8(props->m_0x0c));
        moby->m_Position.z += props->m_0x06;
        props->m_0x06 += props->m_0x08;
        if (func_8004AE38(&oldPosition, &moby->m_Position) != 0) {
          moby->m_State = 1;
        }
        if (TICK_TIMER(props->m_0x0a)) {
          moby->m_State = 1;
        }
        oldPosition.x = 0;
        oldPosition.y = 0;
        oldPosition.z = 0;
        g_SpawnParticle(1, 1, &moby->m_Position, (int)&oldPosition);
        moby->m_Rotation.x += props->m_0x0d;
        moby->m_Rotation.y += props->m_0x0e;
        moby->m_Rotation.z += props->m_0x0f;
        props->m_0x0a += g_DeltaTime;
        break;
      }
      case 1: {
        Vector3D particleVelocity;
        Vector3D particlePosition;
        int angle1;
        int angle2;
        int i;

        if (func_8004E2E8(&moby->m_Position, 0x8CA, 0x86) != 0) {
          int magnitude;
          particleVelocity.x = g_Spyro.m_Position.x - moby->m_Position.x;
          particleVelocity.y = g_Spyro.m_Position.y - moby->m_Position.y;
          magnitude = VecMagnitude(&particleVelocity, 0);
          particleVelocity.x = particleVelocity.x * 0x78 / magnitude;
          particleVelocity.y = particleVelocity.y * 0x78 / magnitude;
          g_Spyro.unk_0x208.z = 0x28;
          g_Spyro.unk_0x208.x = particleVelocity.x;
          g_Spyro.unk_0x208.y = particleVelocity.y;
          moby->m_State = 1;
        }
        func_8003851C(moby, 0, 0);
        for (i = 0; i < 7 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(458, moby);
          g_SpawnMoby(459, moby);
        }
        for (i = 0; i < 42; i++) {
          angle1 = rand() & 0xFF;
          angle2 = rand() & 0xFF;
          particleVelocity.x = FIXED_MUL(COSINE_8(angle2), 80);
          particleVelocity.y = FIXED_MUL(SINE_8(angle2), 80);
          particleVelocity.z = FIXED_MUL(SINE_8(angle1), 80);
          particleVelocity.x = FIXED_MUL(particleVelocity.x, COSINE_8(angle1));
          particleVelocity.y = FIXED_MUL(particleVelocity.y, COSINE_8(angle1));
          VecCopy(&particlePosition, &particleVelocity);
          VecShiftLeft(&particlePosition, 2);
          VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
          g_SpawnParticle(1, 13, &particlePosition, (int)&particleVelocity);
        }
        g_SpawnParticle(10, 70, &moby->m_Position, 0x10);
        func_80052568(moby);
        break;
      }
      case 2:
        func_80052568(moby);
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_177
    case 177: {
      Moby177Props *props;

      props = moby->m_Props;

      if (props->m_0x2c == 0) {
        moby->m_AnimationState.m_PerFrameProgress = 0;
        moby->m_RenderRadius = 0;
        moby->m_WasDrawn = 0;

        func_800562A4(moby, 1);

        if (((func_8002B3F4(props->m_0x30) >> 8) & 0xFF) > 0) {
          props->m_0x2c = 1;
          moby->m_AnimationState.m_PerFrameProgress = 0x10;
          moby->m_RenderRadius = 0x40;
          moby->m_UpdateDistance = 0xFF;
          VecNull(&props->m_0x1c);
          moby->m_Substate = 0;
          props->m_0x18 = 0x18;
          props->m_0x00->m_CurrentNode = 0;
          if (props->m_0x04 != 0) {
            props->m_0x28 = 0;
          } else {
            props->m_0x28 = 0xFF;
          }
        }
        break;
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 1) {
        int i;
        props->m_0x10 = 0;
        props->m_0x18 = 350;

        props->m_0x14 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x28, 0x40);

        for (i = 0; i < 3 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(481, moby);
          g_SpawnMoby(482, moby);
          g_SpawnMoby(483, moby);
        }

        func_8003851C(moby, 0, 0);

        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);

        break;
      }

      switch (moby->m_State) {
      case 0: {
        int speed;
        if (props->m_0x04 != 0) {
          speed = 0x190 - props->m_0x28 * 10;

          switch (props->m_0x44) {
          case 0: {
            int temp;
            int temp2;
            if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
              func_80038AFC(props->m_0x38, &temp2);

              if (temp2 < props->m_0x38->m_CurrentNode) {
                temp2 += props->m_0x38->m_NodeCount;
              }

              temp2 -= props->m_0x38->m_CurrentNode;
              if (temp2 < (props->m_0x38->m_NodeCount >> 1)) {
                props->m_0x38->m_Reversed = 1;
              } else {
                props->m_0x38->m_Reversed = -1;
              }

              if (props->m_0x38->m_Reversed > 0) {
                props->m_0x34 = props->m_0x40;
              } else {
                props->m_0x34 = props->m_0x3c;
              }

              props->m_0x34->m_CurrentNode = props->m_0x34->m_NodeCount - 1;
              props->m_0x34->m_Reversed = 1;
              props->m_0x44 = 1;
            }
            temp = (PATH_NODE_POS(props->m_0x34, props->m_0x34->m_NodeCount - 1)
                        .z -
                    moby->m_Position.z) >>
                   3;
            if (temp > 0x100) {
              temp = 0x100;
            }
            if (temp < -0x100) {
              temp = -0x100;
            }
            moby->m_Position.z = moby->m_Position.z + temp;
            moby->m_Rotation.y = 0;
            break;
          }
          case 1: {
            int temp;
            if (func_80039E94(moby, props->m_0x34, 0x400, speed, 0, 6, 0x18,
                              0xFF, 0) ==
                ((props->m_0x34->m_NodeCount - 1) | 0x100)) {
              if (props->m_0x34 == props->m_0x40) {
                props->m_0x38->m_Reversed = 1;
                props->m_0x38->m_CurrentNode = props->m_0x38->m_NodeCount - 1;
              } else {
                props->m_0x38->m_Reversed = -1;
                props->m_0x38->m_CurrentNode = 0;
              }

              props->m_0x34 = props->m_0x38;
              props->m_0x44 = 2;
            }

            temp = (PATH_CUR_POS(props->m_0x34).z - moby->m_Position.z) >> 3;

            if (temp > 0x100) {
              temp = 0x100;
            }
            if (temp < -0x100) {
              temp = -0x100;
            }
            moby->m_Position.z += temp;
            moby->m_Rotation.y = -Atan2(temp, speed, 0) + ROTDEG8(90);
            break;
          }
          case 2: {
            int temp;
            temp = 0x100;
            if (props->m_0x38->m_Reversed > 0) {
              temp = (props->m_0x34->m_NodeCount - 1) | temp;
            }

            if (func_80039E94(moby, props->m_0x34, 0x400, speed, 0, 6, 0x18,
                              0xFF, 0) == temp) {
              props->m_0x00->m_Reversed = -props->m_0x38->m_Reversed;

              if (props->m_0x00->m_Reversed > 0) {
                props->m_0x00->m_CurrentNode = props->m_0x00->m_NodeCount - 1;
              } else {
                props->m_0x00->m_CurrentNode = 0;
              }
              props->m_0x34 = props->m_0x00;
              if (++props->m_0x28 >= 6) {
                props->m_0x28 = 5;
              }
              props->m_0x44 = 3;
            }

            temp = (PATH_CUR_POS(props->m_0x34).z - moby->m_Position.z) >> 3;

            if (temp > 0x80) {
              temp = 0x80;
            }
            if (temp < -0x80) {
              temp = -0x80;
            }

            moby->m_Position.z += temp;
            moby->m_Rotation.y = -Atan2(temp, speed, 0) + ROTDEG8(90);

            if (DISTANCE_TO_SPYRO(moby) > 0x3800) {
              props->m_0x44 = 4;
            }
            break;
          }
          case 3: {
            int temp;
            temp = 0x100;

            if (props->m_0x38->m_Reversed > 0) {
              temp = (props->m_0x34->m_NodeCount - 1) | temp;
            }

            if (func_80039E94(moby, props->m_0x34, 0x400, speed, 0, 6, 0x18,
                              0xFF, 0) == temp) {
              props->m_0x38->m_Reversed = -props->m_0x00->m_Reversed;

              if (props->m_0x38->m_Reversed > 0) {
                props->m_0x38->m_CurrentNode = props->m_0x38->m_NodeCount - 1;
              } else {
                props->m_0x38->m_CurrentNode = 0;
              }

              props->m_0x34 = props->m_0x38;
              props->m_0x44 = 2;
            }

            temp = (PATH_CUR_POS(props->m_0x34).z - moby->m_Position.z) >> 3;

            if (temp > 0x80) {
              temp = 0x80;
            }
            if (temp < -0x80) {
              temp = -0x80;
            }

            moby->m_Position.z += temp;
            moby->m_Rotation.y = -Atan2(temp, speed, 0) + ROTDEG8(90);
            break;
          }
          case 4: {
            int temp;
            int temp2;
            func_80038AFC(props->m_0x38, &temp2);

            if (temp2 < props->m_0x38->m_CurrentNode) {
              temp2 += props->m_0x38->m_NodeCount;
            }

            temp2 -= props->m_0x38->m_CurrentNode;

            if (temp2 < (props->m_0x38->m_NodeCount >> 1)) {
              props->m_0x38->m_Reversed = 1;
            } else {
              props->m_0x38->m_Reversed = -1;
            }

            props->m_0x34 = props->m_0x38;

            temp = 0x100;

            if (props->m_0x38->m_Reversed > 0) {
              temp = (props->m_0x34->m_NodeCount - 1) | temp;
            }

            if (func_80039E94(moby, props->m_0x34, 0x400, speed, 0, 6, 0x18,
                              0xFF, 0) == temp) {
              if (props->m_0x38->m_Reversed > 0) {
                props->m_0x34 = props->m_0x3c;
              } else {
                props->m_0x34 = props->m_0x40;
              }

              props->m_0x34->m_CurrentNode = 0;
              props->m_0x34->m_Reversed = -1;

              props->m_0x28++;
              if (props->m_0x28 >= 6) {
                props->m_0x28 = 5;
              }

              props->m_0x44 = 5;
            } else if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
              props->m_0x44 = 2;
            }

            temp = (PATH_CUR_POS(props->m_0x34).z - moby->m_Position.z) >> 3;

            if (temp > 0x80) {
              temp = 0x80;
            }
            if (temp < -0x80) {
              temp = -0x80;
            }

            moby->m_Position.z += temp;
            moby->m_Rotation.y = -Atan2(temp, speed, 0) + ROTDEG8(90);
            break;
          }
          case 5: {
            int temp;
            if (func_80039E94(moby, props->m_0x34, 0x400, speed, 0, 6, 0x18,
                              0xFF, 0x100) == 0x100) {
              props->m_0x44 = 0;
            }

            temp = (PATH_CUR_POS(props->m_0x34).z - moby->m_Position.z) >> 3;

            if (temp > 0x100) {
              temp = 0x100;
            }
            if (temp < -0x100) {
              temp = -0x100;
            }

            moby->m_Position.z += temp;
            moby->m_Rotation.y = -Atan2(temp, speed, 0) + ROTDEG8(90);
            break;
          }
          }
        } else {
          int temp;
          int speed;
          speed = moby->m_Rotation.z;

          if (moby->m_Substate != 0) {
            func_8003BFC0(moby, props->m_0x34, &props->m_0x1c, &props->m_0x28,
                          2, 0);

            if (func_80017908(moby->m_Rotation.z,
                              ANGLE_TO_SPYRO(moby->m_Position)) < 0x40) {
              temp = (0x61A8 - moby->m_Position.z) >> 1;
            } else {
              temp = (PATH_CUR_POS(props->m_0x34).z - moby->m_Position.z) >> 3;
            }

            if (temp > 0x80) {
              temp = 0x80;
            }
            if (temp < -0x80) {
              temp = -0x80;
            }

            moby->m_Position.z += temp;
            moby->m_Rotation.y = -Atan2(temp, 0x400, 0) + ROTDEG8(90);
          } else {
            int temp;
            g_Spyro.m_ControlFlags = 0x80002200;
            g_Spyro.unk_0x21c = &g_Spyro.m_Position;
            g_Spyro.unk_0x220 = &D_80078668;

            D_80078668.m_Coords.radius = 0xC00;
            D_80078668.m_Coords.elevation = 0x80;
            D_80078668.m_Coords.azimuth =
                ROTDEG12(180) - (g_Spyro.m_bodyRotation.z << 4);
            D_80078668.m_Offset.azimuth = 0;
            D_80078668.m_Offset.elevation = -0x100;
            D_80078668.m_Offset.radius = 0;

            g_ScreenBorderEnabled = 1;

            temp = func_8003BFC0(moby, props->m_0x00, &props->m_0x1c,
                                 &props->m_0x28, props->m_0x18, 4);

            if (temp == 2) {
              props->m_0x34->m_CurrentNode = 2;
              g_ScreenBorderEnabled = 0;
              moby->m_Substate = 1;
            } else if (temp == 1) {
              props->m_0x18 -= 8;
              if (props->m_0x18 < 2) {
                props->m_0x18 = 2;
              }
            }
          }

          speed = (moby->m_Rotation.z - speed) & 0xFF;
          if (speed > 0x80) {
            speed -= 0x100;
          }

          props->m_0x0c +=
              (((-speed << 8) - (props->m_0x0c << 3) - props->m_0x08) >> 6);

          props->m_0x08 = (props->m_0x08 + props->m_0x0c) & 0xFFF;

          if (props->m_0x08 > 0x800) {
            props->m_0x08 -= 0x1000;
          }

          if (props->m_0x08 < -0x200) {
            props->m_0x08 = -0x200;
          }

          if (props->m_0x08 > 0x200) {
            props->m_0x08 = 0x200;
          }

          moby->m_Rotation.x = props->m_0x08 >> 4;
        }
        break;
      }
      case 1: {
        if (MoveMobyWithGravity(moby, &props->m_0x18, props->m_0x14,
                                &props->m_0x10, 0xC, 0xC) == 3) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
        }
      } break;
      }

      break;
    }
#endif
#ifdef HAS_MOBY_179
    case 179: {
      Moby179Props *props;
      int sound;
      int speed;
      // Can be read uninitialized in condition below
      int result;
      int angleToPath;
      int angleToSpyro;
      int pathNode;
      int pathDir;

      props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 2) {
        props->m_0x18 = 150;

        if (moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) {
          props->m_0x18 = 0xE1;
        }

        props->m_0x14 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);

        props->m_0x10 = 0x80;

        if (moby->m_DropMoby == 0xFF) {
          moby->m_DropMoby = 0xF;
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
        }

        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        break;
      }

      if (TICK_TIMER(props->m_0x20) && moby->m_State == 1) {
        props->m_0x20 = (rand() % 3) + 4;

        sound = rand() % 5;
        while (sound == props->m_0x24) {
          sound = rand() % 5;
        }

        func_8003851C(moby, sound, 0);
        props->m_0x24 = sound;
      }

      if (props->m_0x04 != 0) {
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        func_80052D64(moby, 0, &g_LevelMobys[props->m_0x04].m_Position);
      }

      if (moby->m_AnimationState.m_NextAnimation == 0 &&
          moby->m_RenderRadius != 0) {
        if (moby->m_AnimationState.m_NextFrame == 2 && (rand() & 3) == 0 &&
            !IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[6])) {
          func_8003851C(moby, 6, 0);
        }

        if (moby->m_AnimationState.m_NextFrame == 0xC && (rand() & 3) == 0 &&
            !IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[5])) {
          func_8003851C(moby, 5, 0);
        }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);

      switch (moby->m_State) {
      case 0:
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (DISTANCE_TO_SPYRO(moby) < 0x1800) {
          moby->m_Substate = 0;
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
        }
        break;

      case 1:
        speed = 0x154;
        if (props->m_0x08 != 0) {
          speed -= (DISTANCE_TO_SPYRO(moby) >> 5);

          if (speed < 0x8C) {
            speed = 0x8C;
          }
          if (speed > 0xF0) {
            speed = 0xF0;
          }

          switch (moby->m_Substate) {
          case 0:
            angleToPath =
                ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x00, 0));

            if (OctDistance(&moby->m_Position,
                            &PATH_NODE_POS(props->m_0x00, 0)) < 0x1000) {
              angleToSpyro = ANGLE_FROM_SPYRO(moby->m_Position);

              RotateMobyToAngle(moby, angleToSpyro, 8, 0, 0);
              func_80039398(moby, speed, 0, 0, 5);
            } else {
              int angle;
              int angleToSpyro = ANGLE_FROM_SPYRO(PATH_CUR_POS(props->m_0x00));

              int angleToMoby =
                  ANGLE_FROM(PATH_NODE_POS(props->m_0x00, 0), moby->m_Position);
              angle = 0xA;
              if (moby->m_AnimationState.m_NextAnimation == 4) {
                angle = 0x28;
              }
              if (angle < func_80017908(angleToSpyro, angleToMoby) &&
                  DISTANCE_TO_SPYRO(moby) < 0x3000) {
                result = func_80038638(moby, &PATH_NODE_POS(props->m_0x00, 0),
                                       0x1800, angleToSpyro, 5, speed, 0xE,
                                       0x14, 0xFF, 0xFF, 0, 0, 4);
              }

              if (result >= 0x5B) {
                props->m_0x1c++;
              } else {
                props->m_0x1c = 0;
              }

              if (result < 0x1E) {
                moby->m_State = 0;
                MOBY_ANIM_CHANGE(moby, 0);
              } else if (props->m_0x1c >= 0x1E) {
                angleToMoby = ANGLE_TO_SPYRO(moby->m_Position);

                if (func_80017908(angleToPath, angleToMoby) >= 0x21) {
                  moby->m_Substate = 1;
                }
              }
            }
            break;
          case 1: {
            int angleToSpyro =
                ANGLE_FROM(g_Spyro.m_Position, PATH_NODE_POS(props->m_0x00, 0));
            int angleToMoby =
                ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x00, 0));

            RotateMobyToAngle(moby, angleToSpyro, 8, 0, 0);
            func_80039398(moby, speed, 0, 0, 5);

            if (func_80017908(angleToSpyro, angleToMoby) > 0x50) {
              moby->m_Substate = 0;
            }
            if (OctDistance(&moby->m_Position,
                            &PATH_NODE_POS(props->m_0x00, 0)) > 0x1800) {
              moby->m_Substate = 0;
            }
            break;
          }
          }
        } else {
          switch (props->m_0x0c) {
          case 0: {
            int nodeIndex;
            func_80038AFC(props->m_0x00, &nodeIndex);

            if (props->m_0x00->m_CurrentNode == nodeIndex) {
              pathDir = -props->m_0x00->m_Reversed;
            } else {
              if (nodeIndex < props->m_0x00->m_CurrentNode) {
                nodeIndex += props->m_0x00->m_NodeCount;
              }
              nodeIndex -= props->m_0x00->m_CurrentNode;
              if (nodeIndex < (props->m_0x00->m_NodeCount >> 1)) {
                pathDir = 1;
              } else {
                pathDir = -1;
              }
            }

            if (pathDir != props->m_0x00->m_Reversed) {
              props->m_0x00->m_Reversed = pathDir;
            }

            props->m_0x0c = 3;
            break;
          }
          case 1: {
            int nodeIndex;

            if (func_80038AFC(props->m_0x00, &nodeIndex) > 0x3000) {
              props->m_0x0c = 2;
            }
            nodeIndex = (nodeIndex + (props->m_0x00->m_NodeCount >> 1)) %
                        props->m_0x00->m_NodeCount;

            if (props->m_0x00->m_CurrentNode == nodeIndex) {
              pathDir = -props->m_0x00->m_Reversed;
            } else {
              if (nodeIndex < props->m_0x00->m_CurrentNode) {
                nodeIndex += props->m_0x00->m_NodeCount;
              }

              nodeIndex -= props->m_0x00->m_CurrentNode;

              if (nodeIndex < (props->m_0x00->m_NodeCount >> 1)) {
                pathDir = -1;
              } else {
                pathDir = 1;
              }
            }

            if (pathDir != props->m_0x00->m_Reversed) {
              props->m_0x00->m_Reversed = pathDir;
            }

            pathNode = func_80039E94(moby, props->m_0x00, 0x200, 200, 0, 8,
                                     0x1E, 0xFF, 5);

            if (pathNode & 0x100) {
              pathNode = pathNode & ~0x100;

              if (props->m_0x00->m_Reversed == -1) {
                if (pathNode == 1) {
                  moby->m_State = 0;
                  MOBY_ANIM_CHANGE(moby, 0);
                  break;
                }
              } else {
                if (pathNode == props->m_0x00->m_NodeCount - 1) {
                  moby->m_State = 0;
                  MOBY_ANIM_CHANGE(moby, 0);
                  break;
                }
              }
            }

            if (DISTANCE_TO_SPYRO(moby) < 0x1800) {
              props->m_0x0c = 0;
            }
            break;
          }
          case 2:
            pathNode = func_80039E94(moby, props->m_0x00, 0x200, 200, 0, 8,
                                     0x1E, 0xFF, 5);

            if (pathNode & 0x100) {
              pathNode = pathNode & ~0x100;

              if (props->m_0x00->m_Reversed == -1) {
                if (pathNode == 1) {
                  moby->m_State = 0;
                  MOBY_ANIM_CHANGE(moby, 0);
                  break;
                }
              } else {
                if (pathNode == props->m_0x00->m_NodeCount - 1) {
                  moby->m_State = 0;
                  MOBY_ANIM_CHANGE(moby, 0);
                  break;
                }
              }
              if (DISTANCE_TO_SPYRO(moby) < 0x1800) {
                props->m_0x0c = 0;
              }
            } else {
              if (DISTANCE_TO_SPYRO(moby) < 0x1800) {
                props->m_0x0c = 0;
              }
            }
            break;

          case 3:
            if (DISTANCE_TO_SPYRO(moby) > 0x2800) {
              props->m_0x0c = 1;
            }

            func_80039E94(moby, props->m_0x00, 0x200, 0xF0, 0, 8, 0x1E, 0xFF,
                          5);
            break;
          }
        }
        break;

      case 2:
        MoveMobyWithGravity(moby, &props->m_0x18, props->m_0x14, &props->m_0x10,
                            0xC, 0x10);

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
        }
        break;
      }

      break;
    }
#endif
#ifdef HAS_MOBY_181
    case 181: {
      Moby181Props *props;
      Vector3D vec;
      Vector3D vec2;
      int linkedDone;
      int i;
      int angle;
      int linkedClass;
      int angleDiff;

      props = moby->m_Props;

      linkedDone = 0;
      linkedClass = g_LevelMobys[props->m_0x24].m_Class;
      if (g_LevelMobys[props->m_0x24].m_State >= 0x80 ||
          (linkedClass == 0x9F && g_LevelMobys[props->m_0x24].m_State == 2)) {
        linkedDone = 1;
      }

      if (moby->m_Substate == 0) {
        if (linkedDone) {
          moby->m_Rotation.x = COSINE_8(props->m_0x02) >> 7;
          moby->m_Rotation.y = SINE_8(props->m_0x02) >> 7;
          props->m_0x02 += g_DeltaTime * 2;
        }

        if ((DISTANCE_TO_SPYRO(moby) < 0x200 &&
             SPYRO_BASE_Z_DISTANCE(moby) < 0x200 && linkedDone) ||
            (g_LevelMobys[props->m_0x24].m_State >= 0x80 &&
             g_LevelMobys[props->m_0x24].m_Class == 177)) {
          PlaySound(g_Spu.m_SoundTable->gemPickup, moby, 0x10, 0);
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);

          for (i = 0; i < 6; i++) {
            g_SpawnParticle(1, 12, moby, (0x8080 + 0x01000000 * i));
          }

          g_KeyFlag = 1;

          moby->m_RenderRadius = 0;
          moby->m_WasDrawn = 0;
          moby->m_ShadowDistance = 0;
          moby->m_UpdateDistance = 0xFF;
          moby->m_ScaleOverride = 0x40;
          moby->m_SectorIndex = 0xFF;
          moby->m_Substate = 1;
          props->m_0x20 = 1;
        }

        if (props->m_0x03 != 0xFF && moby->m_RenderRadius != 0) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);

          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &D_8006E5AC,
                            &g_Sparkles[props->m_0x03].m_Position);

          VecAdd(&g_Sparkles[props->m_0x03].m_Position,
                 &g_Sparkles[props->m_0x03].m_Position, &moby->m_Position);

          if (g_Sparkles[props->m_0x03].m_Life < 5) {
            props->m_0x03 = 0xFF;
          }
        } else if (props->m_0x00 >= 0xF8 && moby->m_RenderRadius != 0) {
          int sparkleHandle;

          sparkleHandle = SpawnMobySparkle(moby, &D_8006E5AC);

          if (sparkleHandle >= 0 && DISTANCE_TO_SPYRO(moby) < 0x4000) {
            props->m_0x03 = sparkleHandle;
          }

          props->m_0x00 = (rand() & 0x3F) + 0x18;
        }

        props->m_0x00 += g_DeltaTime;
      }

      switch (props->m_0x20) {
      case 0:
        if (g_LevelMobys[props->m_0x24].m_Class == 177) {
          if (g_LevelMobys[props->m_0x24].m_State < 127) {
            moby->m_RenderRadius = 0;
            moby->m_UpdateDistance = 0xFF;
            moby->m_WasDrawn = 0;
            moby->m_ShadowDistance = 0;
            moby->m_ScaleOverride = 0x40;
            moby->m_SectorIndex = 0xFF;
          } else {
            moby->m_Substate = 1;
            props->m_0x20 = 1;
            g_KeyFlag = 1;
          }
        }
        break;

      case 1:
        if ((g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
             g_Spyro.m_State == 0x15 || g_Spyro.m_State == 2) &&
            func_80038C4C(&g_Spyro.m_Position, &props->m_0x08)) {
          angle = ANGLE_FROM_SPYRO(g_LevelMobys[props->m_0x28].m_Position);

          if (func_80017908(g_Spyro.m_bodyRotation.z, angle) < 0x30) {
            g_Spyro.m_ControlFlags = 0x80002000;
            func_8003DFA4();
            VecNull(&g_Spyro.m_HeadLookTarget);

            moby->m_Substate = 2;
            moby->m_Rotation.x = 0;
            moby->m_Rotation.y = 0;
            moby->m_Rotation.z = g_Spyro.m_bodyRotation.z + 0x80;
            moby->m_WasDrawn = 1;
            moby->m_RenderRadius = 0x18;

            props->m_0x20 = 2;
            props->m_0x00 = 0;

            if (props->m_0x2c != 0) {
              if (*(int *)(&g_CutsceneIdx + props->m_0x2c) != 0) {
                props->m_0x00 = 0x80;

                angleDiff =
                    func_80017908(g_LevelMobys[props->m_0x28].m_Rotation.z,
                                  (g_Spyro.m_bodyRotation.z + 0x40) & 0xFF);
                moby->m_Rotation.y = 0xC0;
                angle = g_Spyro.m_bodyRotation.z + 0x40;
                moby->m_Rotation.z =
                    angle + (angleDiff * (props->m_0x00 - 0x80) / 0x40);
              } else {
                *(int *)(&g_CutsceneIdx + props->m_0x2c) = 1;
              }
            }

            VecCopy(&moby->m_Position, &g_Spyro.m_Position);
          }
        }
        break;

      case 2:
        if (g_Pad.m_Down & PAD_CROSS) {
          props->m_0x00 = 0xD2;
        }

        g_Spyro.m_ControlFlags = 0x80002000;
        moby->m_RenderRadius = 0x18;
        props->m_0x00 += g_DeltaTime;
        g_ScreenBorderEnabled = 1;

        if (props->m_0x00 < 0xC0) {
          vec.x = 0x200;
          vec.y = 0;
          vec.z = 0x140;

          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vec, &vec);
          VecAdd(&vec, &vec, &g_LevelMobys[props->m_0x28].m_Position);
          VecSub(&vec, &vec, &g_Spyro.m_Position);

          vec.z -= 0x100;
          VecShiftRight(&vec, 5);
          VecMult(&vec, &vec, props->m_0x00);
          func_800177F8(&vec, &vec, 6);
          VecAdd(&vec, &vec, &g_Spyro.m_Position);

          vec.z += 0x100;
          vec.z += SINE_8((props->m_0x00 * 128) / 192) >> 3;

          VecCopy(&moby->m_Position, &vec);
          g_Spyro.m_HeadLookTarget.y = SINE_8((props->m_0x00 * 128) / 192) >> 3;
          if (props->m_0x00 < 0x40) {
            int temp;
            moby->m_Rotation.y = -props->m_0x00;

            temp = g_Spyro.m_bodyRotation.z + 0x80;
            temp += props->m_0x00 << 2;
            moby->m_Rotation.z = temp;
          } else if (props->m_0x00 < 0x80) {
            int temp;
            moby->m_Rotation.y = 0xC0;

            temp = g_Spyro.m_bodyRotation.z + 0x80;
            temp += (props->m_0x00 - 0x40) * 3;
            moby->m_Rotation.z = temp;
          } else {
            int temp;
            angleDiff = func_80017908(g_LevelMobys[props->m_0x28].m_Rotation.z,
                                      (g_Spyro.m_bodyRotation.z + 0x40) & 0xFF);

            temp = angleDiff * (props->m_0x00 - 0x80);
            angle = g_Spyro.m_bodyRotation.z + 0x40;

            moby->m_Rotation.z = angle + (temp / 0x40);
          }
        } else if (props->m_0x00 < 0xD0) {
          moby->m_Rotation.z = g_LevelMobys[props->m_0x28].m_Rotation.z;

          vec2.x = 0x200 - ((props->m_0x00 - 0xC0) << 3);
          vec2.y = 0;
          vec2.z = 0x140;

          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vec2, &vec2);
          VecAdd(&moby->m_Position, &vec2,
                 &g_LevelMobys[props->m_0x28].m_Position);
        }

        if (!(props->m_0x00 < 0xD0 &&
              (g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
               g_Spyro.m_State == 21 || g_Spyro.m_State == 2 ||
               g_Spyro.m_State == 3))) {
          moby->m_RenderRadius = 0;
          moby->m_WasDrawn = 0;
          g_ScreenBorderEnabled = 0;
          g_SpawnParticle(32, 70, &moby->m_Position, 0x18);
          func_8003B7C0(moby);
          props->m_0x20 = 3;
        }

        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);

        if (props->m_0x00 % 4 < 2) {
          g_SpawnParticle(1, 12, moby, 0x8080);
        } else {
          g_SpawnParticle(1, 12, moby, 0x5008080);
        }
        break;
      case 3:
        PlaySound(g_Spu.m_SoundTable->gnastyDoorOpening, 0, 0x10, 0);
        func_8002B390(props->m_0x04, 0xFC, 0);

        g_Spyro.m_HeadLookTarget.z = 0;
        g_Spyro.m_HeadLookTarget.y = 0;
        g_Spyro.m_HeadLookTarget.x = 0;
        g_KeyFlag = 0;
        switch (props->m_0x04) {
        case 0:
          D_80075678 = 0x563B;
          break;
        case 1:
          D_80075678 = 0x4E3C;
          break;
        case 2:
          D_80075678 = 0x663A;
          break;
        case 3:
          D_80075678 = 0x5E3A;
          break;
        }

        func_80052568(moby);
        break;
      }

      break;
    }
#endif
#ifdef HAS_MOBY_184
    case 184: {
      Moby184Props *props;

      props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 6) {
        props->m_0x0c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x10 = 0xFA;
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 6;
        MOBY_ANIM_RESTART(moby, 6);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        int angle;
        int distance;

        distance = DISTANCE_TO_SPYRO(moby);
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        angle = func_80038074(angle, -5);
        RotateMobyToAngle(moby, angle, 5, 0, 0);
        if (distance < 0x2000 && SPYRO_BASE_Z_DISTANCE(moby) < 1000) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      }

      case 1: {
        Moby *projectile;
        Moby183Props *projectileProps;
        Vector3D offset;
        int angle;

        props->m_0x04 = 1;
        if (g_AnimFrameFinished != 0 &&
            moby->m_AnimationState.m_Frame == 0x11) {
          angle = func_80038074(moby->m_Rotation.z, 0xFD);
          projectile = g_SpawnMoby(183, moby);
          projectileProps = projectile->m_Props;
          VecCopy(&projectile->m_Position, &moby->m_Position);
          offset.x = FIXED_MUL(COSINE_8(angle), 2850);
          offset.y = FIXED_MUL(SINE_8(angle), 2850);
          offset.z = 0;
          VecAdd(&projectile->m_Position, &projectile->m_Position, &offset);
          projectile->m_Rotation.z = func_80038074(moby->m_Rotation.z, 5);
          projectileProps->m_0x0c = projectile->m_Rotation.z;
          projectileProps->m_0x08 = 40;
          projectileProps->m_0x14 = 1;
          projectileProps->m_0x10 = 240;
          projectileProps->m_0x00 = props->m_0x00;
          projectileProps->m_0x04 = 110;
          props->m_0x08 = 120;
        }
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 2:
        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;

      case 3: {
        int distance = DISTANCE_TO_SPYRO(moby);
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (TICK_TIMER(props->m_0x14) && distance < 2500 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 800) {
          props->m_0x14 = 0;
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        if (distance > 0x2400) {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }
        break;
      }

      case 4:
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_Spyro.m_State == 0xE) {
          props->m_0x14 = 0x8C;
        }
        if (g_AnimationFinished) {
          props->m_0x14 = 0x8C;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;

      case 5:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 6: {
        Moby *spawned;
        Moby *fragment;
        Moby230Props *spawnedProps;
        Vector3D offset;
        int i;
        int angle;

        if (moby->m_Substate == 0) {
          angle = func_80038074(moby->m_Rotation.z, -ROTDEG8(90));
          spawned = g_SpawnMoby(230, moby);
          spawnedProps = spawned->m_Props;
          VecCopy(&spawned->m_Position, &moby->m_Position);
          moby->m_Substate = 1;
          offset.x = FIXED_MUL(COSINE_8(angle), 800);
          offset.y = FIXED_MUL(SINE_8(angle), 800);
          offset.z = 1500;
          VecAdd(&spawned->m_Position, &spawned->m_Position, &offset);
          if (spawned->m_AnimationState.m_Animation != 4) {
            MOBY_ANIM_RESTART(spawned, 4);
          }
          spawned->m_State = 4;
          spawnedProps->m_0x04 = g_Spyro.m_bodyRotation.z;
          spawnedProps->m_0x00 = 300;
          spawned->m_Rotation.z = moby->m_Rotation.z;

          for (i = 0; i < 7 && DYN_MOBY_FREE_COUNT > 20; i++) {
            fragment = g_SpawnMoby(289, spawned);
            g_SpawnMoby(288, spawned);
            if ((rand() & 1) != 0) {
              fragment->m_State = 1;
              MOBY_ANIM_RESTART(fragment, 1);
            }
          }
        }

        if (props->m_0x10 >= 0x15) {
          props->m_0x10 -= 0x14;
        }
        func_80039688(moby, props->m_0x0c, props->m_0x10, 0, 700, 5);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_186
    case 186: { // Musket Gnorc (Dry Canyon)
      Moby186Props *props;

      props = moby->m_Props;
      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 3 &&
          (moby->m_DamageFlags == MOBY_DAMAGE_CHARGE || moby->m_State != 7 ||
           moby->m_AnimationState.m_Frame < 4 ||
           moby->m_AnimationState.m_Frame >= 31)) {
        if (moby->m_DamageFlags == MOBY_DAMAGE_CHARGE) {
          props->m_0x20 = 350;
        } else {
          props->m_0x20 = 0x118;
        }
        props->m_0x1c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x2c = 0x1E;
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        continue;
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0:
        if (props->m_0x14 == 0) {
          if (props->m_0x10 == 0) {
            if (moby->m_AnimationState.m_Animation == 0) {
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
            } else if (g_AnimationFinished) {
              switch (moby->m_AnimationState.m_Animation) {
              case 8:
                if (props->m_0x24 != 0) {
                  props->m_0x24--;
                } else {
                  props->m_0x24 = RandRange(2, 6);
                  MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 9);
                }
                break;
              case 9:
                MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 10);
                break;
              case 10:
                MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 12);
                break;
              case 12:
                MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
                break;
              }
            }
          }

          if (DISTANCE_TO_SPYRO(moby) < (props->m_0x30 << 10) &&
              props->m_0x10 == 0) {
            props->m_0x10 = 1;
            moby->m_State = 11;
            MOBY_ANIM_CHANGE(moby, 11);
            continue;
          }

          if (DISTANCE_TO_SPYRO(moby) < 0x2800 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 1000 && props->m_0x10 == 0) {
            props->m_0x10 = 1;
            moby->m_State = 11;
            MOBY_ANIM_CHANGE(moby, 11);
            continue;
          }
        } else {
          props->m_0x18 = 0x78;
          moby->m_State = 7;
          MOBY_ANIM_RESTART(moby, 7);
          continue;
        }
        break;

      case 1: {
        Moby *projectile;
        Moby197Props *projectileProps;
        Vector3D targetPosition;

        RotateMobyToSpyro(moby, 4, 0, 0);

        if (props->m_0x34 == 0) {
          props->m_0x34 = 1;
          projectile = g_SpawnMoby(197, moby);
          projectile->m_Rotation.z = moby->m_Rotation.z;
          projectileProps = projectile->m_Props;
          // Projectiles enters explosion state after ~2.26s
          projectileProps->m_Lifetime = 136;
          // Don't collide with Mobys for 0.5s
          projectileProps->m_MobyCollisionDelay = 30;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 0, &projectile->m_Position);
          // Target Spyro
          VecCopy(&targetPosition, &g_Spyro.m_Position);
          targetPosition.z -= 300;
          VecSub(&projectileProps->m_Velocity, &targetPosition,
                 &projectile->m_Position);
          // Normalize velocity to a speed of 150
          VecScaleToLength(&projectileProps->m_Velocity,
                           VecMagnitude(&projectileProps->m_Velocity, 1), 150);
          // Shoot in a straight line with no gravity
          projectileProps->m_Velocity.z = 0;

          VecAdd(&projectile->m_Position, &projectile->m_Position,
                 &projectileProps->m_Velocity);
          props->m_0x18 = 100;
        }

        if (g_AnimationFinished) {
          props->m_0x34 = 0;
          moby->m_State = 7;
          MOBY_ANIM_RESTART(moby, 7);
          continue;
        }
        break;
      }

      case 2:
        if (g_AnimationFinished) {
          if (props->m_0x14 == 0 && DISTANCE_TO_SPYRO(moby) > 0x2800) {
            props->m_0x18 = 0x3C;
          }
          moby->m_State = 6;
          MOBY_ANIM_RESTART(moby, 6);
          continue;
        }
        break;

      case 3:
        MoveMobyWithGravity(moby, &props->m_0x20, props->m_0x1c, &props->m_0x2c,
                            0xC, 0xA);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 4: {
        int angle;

        if (OctDistance(&moby->m_Position, &props->m_0x00) < 0x100) {
          moby->m_State = 0;
          continue;
        }

        angle = ANGLE_FROM(moby->m_Position, props->m_0x00);
        RotateMobyToAngle(moby, angle, 4, 0, 0);
        func_80039398(moby, 0x3C, 0, 0, 5);
        break;
      }

      case 6: {
        int distance;

        RotateMobyToSpyro(moby, 4, 0, 0);

        if (props->m_0x14 == 0) {
          if (g_ScreenBorderEnabled == 0 && TICK_TIMER(props->m_0x18) &&
              g_AnimationFinished) {
            if (moby->m_WasDrawn && DISTANCE_TO_SPYRO(moby) < 0x2800 &&
                func_80038250(&moby->m_Position) != 0) {
              moby->m_State = 1;
              MOBY_ANIM_CHANGE(moby, 1);
              continue;
            }

            g_AnimationFinished = 0;
            moby->m_AnimationState.m_FrameProgress = 0xA;
            moby->m_AnimationState.m_PerFrameProgress = 0xA;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation = 7;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 5;
            func_80037E98(moby);
            moby->m_State = 7;
            continue;
          }
          break;
        }

        distance = DISTANCE_TO_SPYRO(moby);
        if (moby->m_WasDrawn && !(distance >= 0x2000 && distance <= 0x3C00) &&
            func_80038250(&moby->m_Position) != 0) {
          if (TICK_TIMER(props->m_0x18) && g_AnimationFinished) {
            if (distance < 0x2000) {
              moby->m_State = 1;
              MOBY_ANIM_CHANGE(moby, 1);
              continue;
            }

            g_AnimationFinished = 0;
            moby->m_AnimationState.m_FrameProgress = 0xA;
            moby->m_AnimationState.m_PerFrameProgress = 0xA;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation = 7;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 5;
            func_80037E98(moby);
            moby->m_State = 7;
            continue;
          }
        } else {
          props->m_0x18 = 0;
        }
        break;
      }

      case 7: {
        int distance;

        if (ABS2(moby->m_AnimationState.m_NextFrame -
                 moby->m_AnimationState.m_Frame) < 3) {
          moby->m_AnimationState.m_PerFrameProgress =
              g_Models[moby->m_Class]
                  ->m_Animations[moby->m_AnimationState.m_Animation]
                  ->m_ProgressPerTick;
        }

        RotateMobyToSpyro(moby, 4, 0, 0);

        if (props->m_0x14 == 1) {
          distance = DISTANCE_TO_SPYRO(moby);
          if (distance > 0x2000 && distance < 0x3c00) {
            moby->m_AnimationState.m_Frame = 0x12;
            moby->m_AnimationState.m_NextFrame = 0x13;
            moby->m_AnimationState.m_FrameProgress = 0;
          }
        }

        if (!TICK_TIMER(props->m_0x18)) {
          if (moby->m_AnimationState.m_Frame >= 0x10) {
            moby->m_AnimationState.m_Frame = 5;
            moby->m_AnimationState.m_NextFrame = 6;
            moby->m_AnimationState.m_FrameProgress = 0x20;
          }
        } else if (moby->m_AnimationState.m_Frame >= 0x12) {
          props->m_0x18 = 0x3C;
          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
          continue;
        }
        break;
      }

      case 9:
        if (g_AnimationFinished) {
          moby->m_State = 11;
          MOBY_ANIM_CHANGE(moby, 11);
          continue;
        }
        break;

      case 11:
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_AnimFrameFinished != 0 && moby->m_AnimationState.m_Frame >= 9) {
          if (props->m_0x30 != 0) {
            moby->m_State = 20;
            continue;
          }
          props->m_0x18 = 0x3C;
          moby->m_AnimationState.m_Animation = 7;
          moby->m_AnimationState.m_NextAnimation = 7;
          moby->m_AnimationState.m_Frame = 3;
          moby->m_AnimationState.m_NextFrame = 4;
          moby->m_AnimationState.m_FrameProgress = 0x20;
          moby->m_State = 7;
        }
        break;

      case 20:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        if (DISTANCE_TO_SPYRO(moby) < 0x800 ||
            func_80039E94(moby, props->m_0x0c, 0x100, 0x5A, 0, 8, 0x28, 0xFF,
                          5) == 0x100) {
          props->m_0x18 = 0x3C;
          moby->m_AnimationState.m_Animation = 7;
          moby->m_AnimationState.m_NextAnimation = 7;
          moby->m_AnimationState.m_Frame = 3;
          moby->m_AnimationState.m_NextFrame = 4;
          moby->m_AnimationState.m_FrameProgress = 0x20;
          moby->m_State = 7;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_187
    case 187: { // Artisans Balloonist
      if (moby->m_State == 0) {
        if (DISTANCE_TO_SPYRO(moby) >= 0x1000) {
          moby->m_State = 1;
        }
      } else if ((g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
                  g_Spyro.m_State == 21 || g_Spyro.m_State == 2 ||
                  g_Spyro.m_State == 11) &&
                 DISTANCE_TO_SPYRO(moby) < 0x780 &&
                 func_80017908(g_Spyro.m_bodyRotation.z,
                               ANGLE_FROM_SPYRO(moby->m_Position)) < 0x20 &&
                 func_80017908(moby->m_Rotation.z,
                               ANGLE_TO_SPYRO(moby->m_Position)) < 0x28) {
        moby->m_State = 0;
        g_Spyro.m_ControlFlags = 0x80002000;
        func_8003DFA4();
        VecNull(&g_Spyro.m_HeadLookTarget);
        D_800757A0(moby);

        if (g_DragonTotal < 10) {
          if (D_800758D0[1] == 0) {
            D_800777E8.m_DialogueId = 0;
            D_800758D0[1] = 1;
          } else {
            D_800777E8.m_DialogueId = 2;
          }
        } else if (D_800758D0[1] < 2) {
          if (D_800758D0[1] == 0) {
            D_800777E8.m_DialogueId = 3;
          } else {
            D_800777E8.m_DialogueId = 4;
          }
          D_800758D0[1] = 2;
        } else {
          D_800777E8.m_DialogueId = 30;
          D_800777E8.m_DialogueTopStr = rand() % 3;
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_188
    case 188: { // Peacekeepers Balloonist
      if (moby->m_State == 0) {
        if (DISTANCE_TO_SPYRO(moby) >= 0x1000) {
          moby->m_State = 1;
        }
      } else if ((g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
                  g_Spyro.m_State == 21 || g_Spyro.m_State == 2 ||
                  g_Spyro.m_State == 11) &&
                 DISTANCE_TO_SPYRO(moby) < 0x780 &&
                 func_80017908(g_Spyro.m_bodyRotation.z,
                               ANGLE_FROM_SPYRO(moby->m_Position)) < 0x20 &&
                 func_80017908(moby->m_Rotation.z,
                               ANGLE_TO_SPYRO(moby->m_Position)) < 0x28) {
        moby->m_State = 0;
        g_Spyro.m_ControlFlags = 0x80002000;
        func_8003DFA4();
        VecNull(&g_Spyro.m_HeadLookTarget);
        D_800757A0(moby);
        D_800758D0[1] = 2;

        if (g_GemTotal < 1200) {
          if (D_800758D0[2] == 0) {
            D_800777E8.m_DialogueId = 6;
            D_800758D0[2] = 1;
          } else {
            D_800777E8.m_DialogueId = 8;
          }
        } else if (D_800758D0[2] < 2) {
          if (D_800758D0[2] == 0) {
            D_800777E8.m_DialogueId = 9;
          } else {
            D_800777E8.m_DialogueId = 10;
          }
          D_800758D0[2] = 2;
        } else {
          D_800777E8.m_DialogueId = 30;
          D_800777E8.m_DialogueTopStr = rand() % 3;
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_189
    case 189: { // Magic Crafters Balloonist
      if (moby->m_State == 0) {
        if (DISTANCE_TO_SPYRO(moby) >= 0x1000) {
          moby->m_State = 1;
        }
      } else if ((g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
                  g_Spyro.m_State == 21 || g_Spyro.m_State == 2 ||
                  g_Spyro.m_State == 11) &&
                 DISTANCE_TO_SPYRO(moby) < 0x780 &&
                 func_80017908(g_Spyro.m_bodyRotation.z,
                               ANGLE_FROM_SPYRO(moby->m_Position)) < 0x20 &&
                 func_80017908(moby->m_Rotation.z,
                               ANGLE_TO_SPYRO(moby->m_Position)) < 0x28) {
        moby->m_State = 0;
        g_Spyro.m_ControlFlags = 0x80002000;
        func_8003DFA4();
        VecNull(&g_Spyro.m_HeadLookTarget);
        D_800757A0(moby);
        D_800758D0[1] = 2;
        D_800758D0[2] = 2;

        if (g_EggTotal < 5) {
          if (D_800758D0[3] == 0) {
            D_800777E8.m_DialogueId = 12;
            D_800758D0[3] = 1;
          } else {
            D_800777E8.m_DialogueId = 14;
          }
        } else if (D_800758D0[3] < 2) {
          if (D_800758D0[3] == 0) {
            D_800777E8.m_DialogueId = 15;
          } else {
            D_800777E8.m_DialogueId = 16;
          }
          D_800758D0[3] = 2;
        } else {
          D_800777E8.m_DialogueId = 30;
          D_800777E8.m_DialogueTopStr = rand() % 3;
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_190
    case 190: { // Beast Makers Balloonist
      if (moby->m_State == 0) {
        if (DISTANCE_TO_SPYRO(moby) >= 0x1000) {
          moby->m_State = 1;
        }
      } else if ((g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
                  g_Spyro.m_State == 21 || g_Spyro.m_State == 2 ||
                  g_Spyro.m_State == 11) &&
                 DISTANCE_TO_SPYRO(moby) < 0x780 &&
                 func_80017908(g_Spyro.m_bodyRotation.z,
                               ANGLE_FROM_SPYRO(moby->m_Position)) < 0x20 &&
                 func_80017908(moby->m_Rotation.z,
                               ANGLE_TO_SPYRO(moby->m_Position)) < 0x28) {
        moby->m_State = 0;
        g_Spyro.m_ControlFlags = 0x80002000;
        func_8003DFA4();
        VecNull(&g_Spyro.m_HeadLookTarget);
        D_800757A0(moby);
        D_800758D0[1] = 2;
        D_800758D0[2] = 2;
        D_800758D0[3] = 2;

        if (g_DragonTotal < 50) {
          if (D_800758D0[4] == 0) {
            D_800777E8.m_DialogueId = 18;
            D_800758D0[4] = 1;
          } else {
            D_800777E8.m_DialogueId = 20;
          }
        } else if (D_800758D0[4] < 2) {
          if (D_800758D0[4] == 0) {
            D_800777E8.m_DialogueId = 21;
          } else {
            D_800777E8.m_DialogueId = 22;
          }
          D_800758D0[4] = 2;
        } else {
          D_800777E8.m_DialogueId = 30;
          D_800777E8.m_DialogueTopStr = rand() % 3;
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_191
    case 191: { // Dream Weavers Balloonist
      if (moby->m_State == 0) {
        if (DISTANCE_TO_SPYRO(moby) >= 0x1000) {
          moby->m_State = 1;
        }
      } else if ((g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
                  g_Spyro.m_State == 0x15 || g_Spyro.m_State == 2 ||
                  g_Spyro.m_State == 0xB) &&
                 DISTANCE_TO_SPYRO(moby) < 0x780 &&
                 func_80017908(g_Spyro.m_bodyRotation.z,
                               ANGLE_FROM_SPYRO(moby->m_Position)) < 0x20 &&
                 func_80017908(moby->m_Rotation.z,
                               ANGLE_TO_SPYRO(moby->m_Position)) < 0x28) {
        moby->m_State = 0;
        g_Spyro.m_ControlFlags = 0x80002000;
        func_8003DFA4();
        VecNull(&g_Spyro.m_HeadLookTarget);
        D_800757A0(moby);
        D_800758D0[1] = 2;
        D_800758D0[2] = 2;
        D_800758D0[3] = 2;
        D_800758D0[4] = 2;

        if (g_GemTotal < 6000) {
          if (D_800758D0[5] == 0) {
            D_800777E8.m_DialogueId = 24;
            D_800758D0[5] = 1;
          } else {
            D_800777E8.m_DialogueId = 26;
          }
        } else if (D_800758D0[5] < 2) {
          if (D_800758D0[5] == 0) {
            D_800777E8.m_DialogueId = 27;
          } else {
            D_800777E8.m_DialogueId = 28;
          }
          D_800758D0[5] = 2;
        } else {
          D_800777E8.m_DialogueId = 30;
          D_800777E8.m_DialogueTopStr = rand() % 3;
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_192
    case 192: { // Gnorc Gnexus Balloonist
      if (moby->m_State == 0) {
        if (DISTANCE_TO_SPYRO(moby) >= 4096) {
          moby->m_State = 1;
        }
      } else if ((g_Spyro.m_State == 0 || g_Spyro.m_State == 1 ||
                  g_Spyro.m_State == 21 || g_Spyro.m_State == 2 ||
                  g_Spyro.m_State == 11) &&
                 DISTANCE_TO_SPYRO(moby) < 1920 &&
                 func_80017908(g_Spyro.m_bodyRotation.z,
                               ANGLE_FROM_SPYRO(moby->m_Position)) < 0x20 &&
                 func_80017908(moby->m_Rotation.z,
                               ANGLE_TO_SPYRO(moby->m_Position)) < 0x28) {
        moby->m_State = 0;
        g_Spyro.m_ControlFlags = 0x80000000 | 0x2000;
        func_8003DFA4();
        VecNull(&g_Spyro.m_HeadLookTarget);
        D_800757A0(moby);
        D_800777E8.m_DialogueId = 30;
        D_800758D0[1] = 2;
        D_800758D0[2] = 2;
        D_800758D0[3] = 2;
        D_800758D0[4] = 2;
        D_800758D0[5] = 2;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_193
    case 193: {
      Moby193Props *props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 1) {
        moby->m_DamageFlags = 0;
        props->m_KnockbackAngle =
            func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                          g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          props->m_KnockbackSpeed = 200;
        } else {
          props->m_KnockbackSpeed = 400;
        }
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
      } else {
        switch (moby->m_State) {
        case 0:
          func_80039AA8(moby, &props->m_Wander);
          break;
        case 1:
          if (props->m_KnockbackSpeed >= 16) {
            props->m_KnockbackSpeed -= 15;
            func_80039688(moby, props->m_KnockbackAngle,
                          props->m_KnockbackSpeed, 0, 700, 5);
          }
          if (g_AnimationFinished) {
            func_80052568(moby);
            continue;
          }
          break;
        }
        func_800529E4(moby, UPDATE_PROP_COLLISION);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_194
    case MOBYCLASS_WOODEN_CHEST: {
      Moby194Props *chestProps = moby->m_Props;

      // Useful in Alpine Ridge when the floor is moved up and down by druids
      if (chestProps->m_FollowFloorZ) {
        func_80038458(moby);
      }

      if (moby->m_DamageFlags &
          (MOBY_DAMAGE_SUPER | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_FLAME)) {
        int i;
        moby->m_SoundDistance = 32;
        func_8003851C(moby, 0, 0);

        // Spawn chest breaking fragments
        for (i = 0; i < 2 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(255, moby);
          g_SpawnMoby(256, moby);
        }
        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(257, moby);
        }

        // Spawn particles
        g_SpawnParticle(5, 2, &moby->m_Position, 0);
        g_SpawnParticle(16, 70, &moby->m_Position, 0x20);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_195
    case MOBYCLASS_METAL_CHEST: {
      Moby195Props *chestProps = moby->m_Props;

      // Always 0 in metal chests in practice
      // Would likely have been used on moving platforms like with wooden
      // chests
      if (chestProps->m_FollowFloorZ != 0) {
        func_80038458(moby);
      }

      // Shake animation after being flamed
      if (chestProps->m_ShakeTimer != 0) {
        chestProps->m_ShakeTimer += g_DeltaTime;
        if (chestProps->m_ShakeTimer < 64) {
          moby->m_Rotation.x =
              g_MobyShakeOffsets[chestProps->m_ShakeTimer >> 1][0] +
              chestProps->m_BaseRotX;
          moby->m_Rotation.y =
              g_MobyShakeOffsets[chestProps->m_ShakeTimer >> 1][1] +
              chestProps->m_BaseRotY;
          moby->m_Position.z =
              chestProps->m_BasePosZ +
              (ABS2(g_MobyShakeOffsets[chestProps->m_ShakeTimer >> 1][0]) +
               ABS2(g_MobyShakeOffsets[chestProps->m_ShakeTimer >> 1][1])) *
                  6;
        } else {
          chestProps->m_ShakeTimer = 0;
          moby->m_Rotation.x = chestProps->m_BaseRotX;
          moby->m_Rotation.y = chestProps->m_BaseRotY;
          moby->m_Position.z = chestProps->m_BasePosZ;
        }
      }

      if (moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) {
        int i;
        moby->m_SoundDistance = 0x20;
        func_8003851C(moby, 0, 0);

        for (i = 0; i < 2 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(310, moby);
          g_SpawnMoby(311, moby);
        }
        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(309, moby);
        }
        g_SpawnParticle(16, 70, &moby->m_Position, 0x18);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        func_80052568(moby);
      } else {
        chestProps->m_Heat = ApplyFlameHeatExternal(moby, chestProps->m_Heat);
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) &&
            chestProps->m_ShakeTimer == 0) {
          chestProps->m_ShakeTimer = 1;
          chestProps->m_BaseRotX = moby->m_Rotation.x;
          chestProps->m_BaseRotY = moby->m_Rotation.y;
          chestProps->m_BasePosZ = moby->m_Position.z;
        }
      }
      moby->m_DamageFlags = 0;

      break;
    }
#endif
#ifdef HAS_MOBY_197
    case 197: { // Musket Gnorc Projectile (Dry Canyon)
      Moby197Props *props = moby->m_Props;

      moby->m_SoundDistance = 0x20;
      // Continuous projectile rotation
      moby->m_Rotation.y = func_80038074(moby->m_Rotation.y, ROTDEG8(5));

      switch (moby->m_State) {
      case 0: { // Flying state
        Vector3D zeroVelocity;
        int mobyCollisionRadius;

        zeroVelocity.x = 0;
        zeroVelocity.y = 0;
        zeroVelocity.z = 0;

        // Only enable Moby collision radius once the delay has elapsed
        mobyCollisionRadius = TICK_TIMER(props->m_MobyCollisionDelay) ? 300 : 0;

        g_SpawnParticle(1, 1, &moby->m_Position, (int)&zeroVelocity);

        // Enter explosion state upon collision with Mobys/Environment, Spyro
        // or expiration of lifetime
        if (func_80039228(moby, props->m_Velocity, mobyCollisionRadius, 300,
                          1)) {
          moby->m_State = 1;
        } else if (DISTANCE_TO_SPYRO(moby) < 200 &&
                   SPYRO_BASE_Z_DISTANCE(moby) < 900) {
          g_Spyro.m_DamageFlags |= 5;
          g_Spyro.m_ControlFlags = 0x80000047;
          // Can FIXED_MUL be used here?
          g_Spyro.unk_0x208.x = (-props->m_Velocity.x * 3) >> 2;
          g_Spyro.unk_0x208.y = (-props->m_Velocity.y * 3) >> 2;
          g_Spyro.unk_0x208.z = 80;
          moby->m_State = 1;
        } else if (TICK_TIMER(props->m_Lifetime)) {
          moby->m_State = 1;
        }
        break;
      }

      case 1: { // Explosion state
        Vector3D particleVelocity;
        Vector3D particlePosition;
        int i;

        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(458, moby);
          g_SpawnMoby(459, moby);
        }

        // Why are dynamic Mobys being checked here?
        for (i = 0; i < 8 && DYN_MOBY_FREE_COUNT > 20; i++) {
          particleVelocity.x = (rand() & 0x3E) - 31;
          particleVelocity.y = (rand() & 0x3E) - 31;
          particleVelocity.z = rand() & 0xF;
          VecCopy(&particlePosition, &particleVelocity);
          VecShiftLeft(&particlePosition, 2);
          VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
          g_SpawnParticle(1, 13, &particlePosition, (int)&particleVelocity);
        }

        g_SpawnParticle(10, 70, &moby->m_Position, 0x10);
        func_80052568(moby);
        continue;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_198 // Ice Gnorc
    case 198: {
      Moby198Props *props = moby->m_Props;

      // If the Gnorc has been flamed while not in its dying state
      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 6) {
        // Prepare knockback values
        props->m_KnockbackSpeed = 0xF0;
        props->m_KnockbackAngle = g_Spyro.m_bodyRotation.z;
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        // Enter dying state
        moby->m_State = 6;
        MOBY_ANIM_CHANGE(moby, 6);
        break;
      }

      switch (moby->m_State) {
      case 0: // Idle
        if (g_AnimationFinished) {
          if (moby->m_AnimationState.m_Animation == 8) {
            // Play Flexing Anim 2
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 9);
          } else if (props->m_IdleAnimCounter == 0) {
            // Set up counter for 2-4 Idle "looking around" anims
            props->m_IdleAnimCounter = RandRange(2, 4);
            // Play Flexing Anim 1
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
          } else {
            // Play Idle "looking around" anims until counter is 0
            props->m_IdleAnimCounter--;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          }
        }

        // Keep rotating Moby to face Spyro
        RotateMobyToSpyro(moby, 3, 0x10, 0);

        // Take note of Spyro, transition to entering attack stance
        if (DISTANCE_TO_SPYRO(moby) < 0x1C00 &&
            SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
          // Value is overwritten before entering dying state and never used
          props->m_KnockbackSpeed = 0x48;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;

      case 2: // Entering attack stance
        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_RESTART(moby, 3);
          continue;
        }
        break;

      case 3: { // Attack stance
        int distance = DISTANCE_TO_SPYRO(moby);
        RotateMobyToSpyro(moby, 3, 0, 0);

        // Spyro is close enough to hit
        if (distance < 3300 && SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
          // Value is overwritten before entering dying state and never used
          props->m_KnockbackSpeed = 0x48;

          props->m_LaughCounter = 0;

          // Enter attacking state
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }

        // Spyro is out of range again
        if (distance > 0x2000) {
          // Enter exiting attack stance state
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }
        break;
      }

      case 4: // Attacking
        RotateMobyToSpyro(moby, 6, 0, 0);

        // If Spyro has been flattened
        if (g_Spyro.m_State == 25) {
          // Will cause 2 laughing anims in most cases, 1 if it's a lag frame
          // Only decrements when the animation is finished
          props->m_LaughCounter = 3;
        }

        if (g_AnimationFinished) {
          // If the hit landed, proceed to laughing state
          // Otherwise, enter idle state
          if (props->m_LaughCounter) {
            moby->m_State = 7;
            MOBY_ANIM_RESTART(moby, 7);
          } else {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
          }
          continue;
        }
        break;

      case 5: // Leaving attack stance
        if (g_AnimationFinished) {
          // Return to idle state
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;

      case 6: // Dying
        if (props->m_KnockbackSpeed > 0) {
          func_80039688(moby, props->m_KnockbackAngle, props->m_KnockbackSpeed,
                        500, 700, 1);
          // Incrementally reduce knockback speed
          props->m_KnockbackSpeed -= 0x10;
        }

        // Wrap up Moby's death
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 7: // Laughing
        // Play laughing anim
        if (g_AnimationFinished) {
          if (TICK_TIMER(props->m_LaughCounter)) {
            // Return to idle
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        }
        break;
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_199 // Engineer in Gnorc Cove
    case 199: {
      Moby199Props *props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 2) {
        ((int *)g_LevelMobys[props->m_0x00].m_Props)[4] = -1;
        props->m_0x00 = -1;
        props->m_0x08 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x10 = 120;
        if (moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) {
          props->m_0x0c = 240;
        } else {
          props->m_0x0c = 120;
        }
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        continue;
      }

      if (props->m_0x00 >= 0) {
        int linkedState = g_LevelMobys[props->m_0x00].m_State;
        if (linkedState == 3) {
          props->m_0x00 = -1;
          props->m_0x0c = 0;
          props->m_0x10 = 0xF0;
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        } else if (linkedState == 4) {
          props->m_0x00 = -1;
          props->m_0x0c = 0;
          props->m_0x10 = 0x78;
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
      }

      if (props->m_0x04 == 0) {
        g_LevelMobys[props->m_0x00].m_Position.z += 0x1CD;
        g_LevelMobys[props->m_0x00].m_Rotation.y = 0x40;
        moby->m_Position.z += 900;
        props->m_0x04 = 1;
      }

      switch (moby->m_State) {
      case 0:
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (DISTANCE_TO_SPYRO(moby) < 0x800 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;
      case 1:
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        break;
      case 2:
        MoveMobyWithGravity(moby, &props->m_0x0c, props->m_0x08, &props->m_0x10,
                            0xC, 0x10);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }

#endif
#ifdef HAS_MOBY_200
    case 200: {
      Moby200Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 3) {
        props->m_0x0c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x14 = 0x3C;
        props->m_0x10 = 0x78;
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        continue;
      }

      switch (moby->m_State) {
      case 0:
        if (TICK_TIMER(props->m_0x08)) {
          int linkedState = g_LevelMobys[props->m_0x00].m_State;
          if (linkedState == 1 || linkedState == 4) {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        }
        break;
      case 1:
        if (props->m_0x04 == 0 && moby->m_AnimationState.m_NextFrame >= 4) {
          Moby154Props *linkedProps = g_LevelMobys[props->m_0x00].m_Props;
          if (linkedProps->m_0x08 == 0) {
            if (linkedProps->m_0x04 == 1) {
              props->m_0x04 = g_SpawnMoby(207, moby);
            } else {
              props->m_0x04 = g_SpawnMoby(202, moby);
            }
          } else {
            props->m_0x04 = linkedProps->m_0x08;
          }

          g_LevelMobys[props->m_0x00].m_Substate = 1;
        }
        if (g_AnimationFinished) {
          moby->m_State = 2;
          MOBY_ANIM_SET_NEXT(moby, 2);
          continue;
        }
        break;
      case 2:
        if (props->m_0x04 != 0 && moby->m_AnimationState.m_NextFrame >= 6) {
          short *childProps;
          childProps = props->m_0x04->m_Props;
          props->m_0x04->m_Substate = 1;
          props->m_0x04->m_Rotation.z = moby->m_Rotation.z + 0x40;
          childProps[0] = 300;
          props->m_0x04 = 0;
        }
        if (g_AnimationFinished) {
          props->m_0x08 = 0x1E;
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
          continue;
        }
        break;
      case 3:
        MoveMobyWithGravity(moby, &props->m_0x10, props->m_0x0c, &props->m_0x14,
                            0xC, 0x10);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;
      }

      if (props->m_0x04 != 0) {
        Vector3D pos0;
        Vector3D delta;

        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        if (props->m_0x04->m_State >= 2) {
          props->m_0x04 = 0;
          break;
        }
        func_80052D64(moby, 0, &pos0);
        func_80052D64(moby, 1, &delta);
        VecSub(&delta, &delta, &pos0);
        props->m_0x04->m_Rotation.z = Atan2(delta.x, delta.y, 0);
        props->m_0x04->m_Rotation.y =
            Atan2(VecMagnitude(&delta, 0), delta.z, 0);
        VecShiftRight(&delta, 1);
        VecAdd(&props->m_0x04->m_Position, &pos0, &delta);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_201
    case 201: {
      Moby201Props *props = moby->m_Props;
      int activeHitbox;

      ApplyFlameHeat(moby);
      activeHitbox = 0;
      if (moby->m_State >= 6 && moby->m_State <= 10 &&
          (moby->m_DamageFlags & MOBY_DAMAGE_FLAME)) {
        props->m_0x0c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x14 = 0x3C;
        props->m_0x10 = 0x78;
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 12;
        MOBY_ANIM_CHANGE(moby, 12);
        continue;
      }

      moby->m_DamageFlags = 0;
      if (moby->m_State < 11) {
        RotateMobyToSpyro(moby, 4, 0, 0);
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x08 != 0) {
          if (TICK_TIMER(props->m_0x08)) {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        } else if (DISTANCE_TO_SPYRO(moby) < 0x1400 &&
                   SPYRO_BASE_Z_DISTANCE(moby) < 0xC00) {
          props->m_0x08 = 0x2D;
        }
        break;
      case 1:
        if (g_AnimationFinished) {
          moby->m_State = 2;
          MOBY_ANIM_SET_NEXT(moby, 2);
          continue;
        }
        break;
      case 2:
        if (DISTANCE_TO_SPYRO(moby) < 0xE00 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        if (DISTANCE_TO_SPYRO(moby) > 0x1600 ||
            SPYRO_BASE_Z_DISTANCE(moby) > 0x1000) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;
      case 3:
        if (g_Spyro.m_State == 0x19 || g_Spyro.m_State == 0x1F) {
          props->m_0x04 = 1;
        }
        if (props->m_0x04 == 0) {
          activeHitbox = 1;
        }
        if (g_AnimationFinished) {
          if (props->m_0x04 != 0) {
            props->m_0x04 = 0;
            moby->m_State = 5;
            MOBY_ANIM_SET_NEXT(moby, 5);
            continue;
          }
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
          continue;
        }
        break;
      case 4:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
          continue;
        }
        break;
      case 5:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      case 6:
        if (DISTANCE_TO_SPYRO(moby) < 0x1400 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0xC00) {
          moby->m_State = 7;
          MOBY_ANIM_CHANGE(moby, 7);
          continue;
        }
        break;
      case 7:
        if (g_AnimationFinished) {
          props->m_0x08 = 0;
          moby->m_State = 8;
          MOBY_ANIM_SET_NEXT(moby, 8);
          continue;
        }
        break;
      case 8:
        if (DISTANCE_TO_SPYRO(moby) < 0x1000 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
          if (props->m_0x08 != 0) {
            if (TICK_TIMER(props->m_0x08)) {
              moby->m_State = 9;
              MOBY_ANIM_CHANGE(moby, 9);
              continue;
            }
          } else {
            props->m_0x08 = 0x2D;
          }
        } else if (DISTANCE_TO_SPYRO(moby) > 0x1800 ||
                   SPYRO_BASE_Z_DISTANCE(moby) > 0x1000) {
          moby->m_State = 6;
          MOBY_ANIM_CHANGE(moby, 6);
          continue;
        }
        break;
      case 9:
        if (g_Spyro.m_State == 0xE || g_Spyro.m_State == 0x1E) {
          props->m_0x04 = 1;
        }
        if (g_AnimationFinished) {
          if (props->m_0x04 != 0) {
            props->m_0x04 = 0;
            moby->m_State = 10;
            MOBY_ANIM_SET_NEXT(moby, 10);
            continue;
          }
          moby->m_State = 6;
          MOBY_ANIM_SET_NEXT(moby, 6);
          continue;
        }
        break;
      case 10:
        if (g_AnimationFinished) {
          moby->m_State = 6;
          MOBY_ANIM_CHANGE(moby, 6);
          continue;
        }
        break;
      case 11:
        if (g_AnimationFinished) {
          moby->m_State = 6;
          MOBY_ANIM_SET_NEXT(moby, 6);
          continue;
        }
        break;
      case 12:
        MoveMobyWithGravity(moby, &props->m_0x10, props->m_0x0c, &props->m_0x14,
                            0xC, 0x10);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
      if (props->m_0x00 >= 0) {
        Vector3D pos0;
        Vector3D delta;

        if (g_LevelMobys[props->m_0x00].m_State >= 2) {
          ((int *)g_LevelMobys[props->m_0x00].m_Props)[4] = -1;
          props->m_0x00 = -1;
          moby->m_State = 11;
          MOBY_ANIM_RESTART(moby, 11);
          continue;
        }

        func_80052D64(moby, 0, &pos0);
        func_80052D64(moby, 1, &delta);
        VecSub(&delta, &delta, &pos0);
        g_LevelMobys[props->m_0x00].m_Rotation.z = Atan2(delta.x, delta.y, 0);
        g_LevelMobys[props->m_0x00].m_Rotation.y =
            Atan2(VecMagnitude(&delta, 0), delta.z, 0);
        VecShiftRight(&delta, 1);
        VecAdd(&g_LevelMobys[props->m_0x00].m_Position, &pos0, &delta);
        if (activeHitbox) {
          func_8004E2E8(&g_LevelMobys[props->m_0x00].m_Position, 0x200, 0x16);
          VecAdd(&pos0, &g_LevelMobys[props->m_0x00].m_Position,
                 &moby->m_Position);
          VecShiftRight(&pos0, 1);
          func_8004E2E8(&pos0, 0x200, 0x16);
        }
      }
      break;
    }

#endif
#ifdef HAS_MOBY_202
    case 202: {
      Moby202Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 2 && moby->m_State != 3) {
        moby->m_State = 2;
      } else if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) &&
                 moby->m_State == 0) {
        props->m_0x00 = 0x3C;
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
        continue;
      }
      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0:
        if (props->m_0x10 >= 0 && g_LevelMobys[props->m_0x10].m_State >= 0x80) {
          func_80052568(moby);
          continue;
        }
        break;
      case 1:
        if (TICK_TIMER(props->m_0x00)) {
          moby->m_State = 2;
        }
        break;
      case 2: {
        Moby *frag;
        MobyFragmentProps *fp;
        MobyDragonFragmentProps *dfp;
        int i;

        moby->m_Position.z -= 0x1CD;
        func_800562A4(moby, 1);
        func_8003851C(moby, 0, 0);
        if (moby->m_WasDrawn) {
          for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
            frag = g_SpawnMoby(151, moby);
            fp = frag->m_Props;
            fp->m_Velocity.x >>= 1;
            fp->m_Velocity.y >>= 1;
          }
          for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
            frag = g_SpawnMoby(153, moby);
            dfp = frag->m_Props;
            frag->m_Substate = (rand() & 1) + 0x12;
            VecCopy(&frag->m_Position, &moby->m_Position);
            frag->m_Position.x +=
                (COSINE_8(i << 6) >> 4) + (rand() & 0x1F) - 0xF;
            frag->m_Position.y += (SINE_8(i << 6) >> 4) + (rand() & 0x1F) - 0xF;
            frag->m_Position.z += (rand() & 0xFF) + 0x80;
            dfp->m_Velocity.x = (COSINE_8(i << 6) >> 6) + (rand() & 0x1F) - 0xF;
            dfp->m_Velocity.y = (SINE_8(i << 6) >> 6) + (rand() & 0x1F) - 0xF;
            dfp->m_Velocity.z = (rand() & 0x3F) + 0x18;
            frag->m_Rotation.x = rand();
            frag->m_Rotation.y = rand();
            frag->m_Rotation.z = rand();
            dfp->m_AngularVelocity.x = rand() & 0xF;
            dfp->m_AngularVelocity.y = rand() & 0xF;
            dfp->m_AngularVelocity.z = rand() & 0xF;
            dfp->m_MinZ = moby->m_Position.z;
          }
          for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
            frag = g_SpawnMoby(152, moby);
            dfp = frag->m_Props;
            frag->m_Substate = (rand() & 3) + 0x19;
            VecCopy(&frag->m_Position, &moby->m_Position);
            frag->m_Position.x +=
                (COSINE_8(i << 6) >> 4) + (rand() & 0x3F) - 0x1F;
            frag->m_Position.y +=
                (SINE_8(i << 6) >> 4) + (rand() & 0x3F) - 0x1F;
            frag->m_Position.z += (rand() & 0xFF) + 0x80;
            dfp->m_Velocity.x = (COSINE_8(i << 6) >> 5) + (rand() & 0x1F) - 0xF;
            dfp->m_Velocity.y = (SINE_8(i << 6) >> 5) + (rand() & 0x1F) - 0xF;
            dfp->m_Velocity.z = (rand() & 0x7F) + 0x30;
            frag->m_Rotation.x = rand();
            frag->m_Rotation.y = rand();
            frag->m_Rotation.z = rand();
            dfp->m_AngularVelocity.x = rand() & 0xF;
            dfp->m_AngularVelocity.y = rand() & 0xF;
            dfp->m_AngularVelocity.z = rand() & 0xF;
            dfp->m_MinZ = moby->m_Position.z;
          }
        }
        if (props->m_0x04 != 0 && props->m_0x04->m_Class == 154 &&
            props->m_0x04->m_State == 2) {
          props->m_0x04->m_Substate = 1;
        }
        props->m_0x00 = 0;
        moby->m_RenderRadius = 0;
        moby->m_WasDrawn = 0;
        moby->m_State = 3;
        moby->m_Substate = 0;
        break;
      }
      case 3:
        if (props->m_0x02 == 0) {
          if (func_8004E2E8(&moby->m_Position, (props->m_0x00 + 3) * 0x90,
                            0xC0086)) {
            int mag;
            int dist;

            props->m_0x02 = 1;
            g_Spyro.unk_0x208.x =
                (g_Spyro.m_Position.x - moby->m_Position.x) >> 1;
            g_Spyro.unk_0x208.y =
                (g_Spyro.m_Position.y - moby->m_Position.y) >> 1;
            g_Spyro.unk_0x208.z = 0;
            if (g_Spyro.unk_0x208.x != 0 || g_Spyro.unk_0x208.y != 0) {
              mag = VecMagnitude(&g_Spyro.unk_0x208, 1);
              dist = DISTANCE_TO_SPYRO(moby);
              VecScaleToLength(&g_Spyro.unk_0x208, mag, (0x1000 - dist) >> 6);
            }
            g_Spyro.unk_0x208.z = 0x46;
          }
        }
        func_8004E3C8(&moby->m_Position, (props->m_0x00 + 2) << 8, 0, 0x90000,
                      moby, 2);
        props->m_0x00++;
        if (props->m_0x00 < 8) {
          break;
        }
        func_8003B7C0(moby);
        func_80052568(moby);
        continue;
      }

      if (moby->m_Substate != 0) {
        int floorZ;

        func_8003851C(moby, 2, &moby->m_SoundChannel);
        moby->m_Rotation.x += 6;
        floorZ = func_8004D5EC(&moby->m_Position, 0x800);
        if (moby->m_Position.z - floorZ >= 0x181) {
          props->m_0x0c -= 0xA;
          if (props->m_0x0c < -0x80) {
            props->m_0x0c = -0x80;
          }
          moby->m_Position.z += props->m_0x0c;
        } else if ((g_SurfaceBelowFlags & 0x3F) == 0) {
          Moby *splash = g_SpawnMoby(400, moby);
          func_800562A4(moby, 1);
          PlaySound(g_Models[moby->m_Class]->m_Sounds[3], splash, 8,
                    &splash->m_SoundChannel);
          if (props->m_0x04 != 0 && props->m_0x04->m_Class == 154 &&
              props->m_0x04->m_State == 2) {
            props->m_0x04->m_Substate = 1;
          }
          func_80052568(moby);
          continue;
        } else {
          props->m_0x0c = -0xA;
          moby->m_Position.z = floorZ + 0x180;
        }

        if (func_80039688(moby, (moby->m_Rotation.z - 0x40) & 0xFF, 0x80, 0x200,
                          0x200, 1)) {
          moby->m_State = 2;
        }
        if (SPYRO_ORIGIN_Z_DELTA(moby) < 0x80) {
          func_8004E2E8(&moby->m_Position, 0x200, 0x10);
        }
        if (TICK_TIMER(props->m_0x00)) {
          moby->m_State = 2;
        }
        if (g_Spyro.m_State == 0x19 || g_Spyro.m_State == 0x1F) {
          moby->m_CollisionGroup = 0;
        }
        func_8004D5EC(&moby->m_Position, 0x2000);
        func_800533D0(moby);
      }
      break;
    }

#endif
#ifdef HAS_MOBY_203
    case 203: {
      Moby203Props *props = moby->m_Props;
      Vector3D spyroDelta;
      int distance;

      VecSub(&spyroDelta, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);
      if (distance < 13000) {
        distance = VecMagnitude(&spyroDelta, 0);
      }

      ApplyFlameHeat(moby);

      if (moby->m_DamageFlags & MOBY_DAMAGE_SUPER) {
        int i;

        ANGLE_FROM_SPYRO(moby->m_Position);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        func_8003851C(moby, 0, 0);

        for (i = 0; i < 6; i++) {
          Moby *fragment;
          MobyFragmentProps *fragmentProps;

          moby->m_Rotation.y = g_Spyro.m_bodyRotation.z;
          if (i == 2) {
            moby->m_Rotation.y += 20;
          } else if (i == 3) {
            moby->m_Rotation.y -= 20;
          } else if (i == 4) {
            moby->m_Rotation.y += 25;
          } else if (i == 5) {
            moby->m_Rotation.y -= 25;
          }

          fragment = g_SpawnMoby(215, moby);
          fragmentProps = fragment->m_Props;
          func_80052D64(moby, i, &fragment->m_Position);
          fragment->m_Rotation.z = moby->m_Rotation.z;
          fragment->m_Rotation.x = 0;
          fragment->m_Rotation.y = 0;

          if (moby->m_State == 0) {
            fragmentProps->m_Velocity.z -= 30;
          }

          if (fragment->m_AnimationState.m_Animation != i) {
            MOBY_ANIM_RESTART(fragment, i);
          }
        }

        func_80052568(moby);
        continue;
      }

      moby->m_DamageFlags = 0;

      if (moby->m_Substate == 2) {
        moby->m_Substate = 0;
        moby->m_State = 0;
        MOBY_ANIM_RESTART(moby, 0);
        continue;
      }

      if (moby->m_State >= 2 && props->m_0x04 == 1) {
        Vector3D delta;
        Vector3D pathStart;
        Vector3D pathEnd;
        Vector3D pathDelta;
        int lineX;
        int lineY;
        int lineLength;
        int projection;

        lineX = PATH_NODE_POS(props->m_0x0c, 1).y -
                PATH_NODE_POS(props->m_0x0c, 0).y;
        lineY = PATH_NODE_POS(props->m_0x0c, 0).x -
                PATH_NODE_POS(props->m_0x0c, 1).x;
        lineLength = func_80017A38(lineX * lineX + lineY * lineY);

        pathStart.x = PATH_NODE_POS(props->m_0x0c, 0).x;
        pathStart.y = PATH_NODE_POS(props->m_0x0c, 0).y;
        projection = lineX * pathStart.x + lineY * pathStart.y;
        projection = (lineX * g_Spyro.m_Position.x +
                      lineY * g_Spyro.m_Position.y - projection) /
                     lineLength;

        pathEnd.x = PATH_NODE_POS(props->m_0x0c, 1).x;
        pathEnd.y = PATH_NODE_POS(props->m_0x0c, 1).y;

        delta.x = g_Spyro.m_Position.x - (projection * lineX) / lineLength;
        delta.y = g_Spyro.m_Position.y - (projection * lineY) / lineLength;

        if (delta.x < pathStart.x && delta.x < pathEnd.x) {
          if (pathStart.x < pathEnd.x) {
            if (delta.x < pathStart.x) {
              delta.x = pathStart.x;
            }
          } else {
            delta.x = pathEnd.x;
          }
        } else if (delta.x > pathStart.x && delta.x > pathEnd.x) {
          if (pathEnd.x < pathStart.x) {
            delta.x = pathStart.x;
          } else if (delta.x > pathEnd.x) {
            delta.x = pathEnd.x;
          }
        }

        if (delta.y < pathStart.y && delta.y < pathEnd.y) {
          if (pathStart.y < pathEnd.y) {
            if (delta.y < pathStart.y) {
              delta.y = pathStart.y;
            }
          } else {
            delta.y = pathEnd.y;
          }
        } else if (delta.y > pathStart.y && delta.y > pathEnd.y) {
          if (pathEnd.y < pathStart.y) {
            delta.y = pathStart.y;
          } else if (delta.y > pathEnd.y) {
            delta.y = pathEnd.y;
          }
        }

        VecSub(&pathDelta, &delta, &moby->m_Position);
        lineLength = VecMagnitude(&pathDelta, 0);
        if (lineLength < 200) {
          moby->m_Position.x = delta.x;
          moby->m_Position.y = delta.y;
        } else {
          VecScaleToLength(&pathDelta, lineLength, 200);
          moby->m_Position.x += pathDelta.x;
          moby->m_Position.y += pathDelta.y;
        }
      }

      switch (moby->m_State) {
      case 0:
        if (moby->m_Substate == 1 || props->m_0x08 != 0) {
          moby->m_Substate = 0;
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          continue;
        }
        break;

      case 1:
        if (g_AnimationFinished) {
          moby->m_State = 2;
          MOBY_ANIM_SET_NEXT(moby, 2);
          continue;
        }
        break;

      case 2:
        RotateMobyToSpyro(moby, 4, 0, 0);
        TICK_TIMER(props->m_0x14);
        if (props->m_0x04 == 0 && props->m_0x14 < 60 && distance < 4500 &&
            (props->m_0x18 == -1 ||
             g_LevelMobys[props->m_0x18].m_State >= 0x80) &&
            func_80038250(&moby->m_Position) != 0) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;

      case 3: {
        int attackDistance = 2800;

        if (func_80017908(g_Spyro.m_bodyRotation.z,
                          ANGLE_FROM_SPYRO(moby->m_Position)) >= ROTDEG8(100)) {
          attackDistance = 2000;
        }

        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_AnimationFinished || distance > 6000) {
          if (g_AnimationFinished) {
            props->m_0x14 = 180;
          }
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        if (TICK_TIMER(props->m_0x14) && distance < attackDistance &&
            SPYRO_BASE_Z_DELTA(moby) < 800 &&
            moby->m_AnimationState.m_NextFrame < 28) {
          moby->m_AnimationState.m_Frame = 31;
          moby->m_AnimationState.m_NextFrame = 32;
          moby->m_AnimationState.m_FrameProgress = 0;
        }

        if (moby->m_AnimationState.m_NextFrame == 30) {
          moby->m_AnimationState.m_Frame = 10;
          moby->m_AnimationState.m_NextFrame = 11;
          moby->m_AnimationState.m_FrameProgress = 0;
        }

        if (distance < attackDistance && SPYRO_BASE_Z_DELTA(moby) < 800 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 800 &&
            moby->m_AnimationState.m_NextFrame >= 45 &&
            moby->m_AnimationState.m_NextFrame <= 50) {
          g_Spyro.m_DamageFlags |= 0x16;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_204
    case 204: {
      Moby204Props *props = moby->m_Props;
      int i;

      if (moby->m_State != 4) {
        g_SpawnParticle(1, 65, moby, 0);
      }

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 4) {
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        props->m_0x108 = 240;
        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
          props->m_0x108 = 380;
        }
        props->m_0x104 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                       g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x10c = 40;
        moby->m_State = 4;
        MOBY_ANIM_CHANGE(moby, 4);
        continue;
      }

      if (props->m_0x134[0][1].x == 0 &&
          ABS2(g_Spyro.m_Position.z - props->m_0x134[0][0].z) < 2000 &&
          func_80038C4C(&g_Spyro.m_Position, &props->m_0x134[0][0]) != 0) {
        for (i = 0; i < 7; i++) {
          props->m_0xe8[i] = 1;
        }
      }

      if (props->m_0x134[1][1].x == 0 &&
          ABS2(g_Spyro.m_Position.z - props->m_0x134[1][0].z) < 2000 &&
          func_80038C4C(&g_Spyro.m_Position, &props->m_0x134[1][0]) != 0) {
        for (i = 0; i < 7; i++) {
          props->m_0xe8[i] = 1;
        }
      }

      TICK_TIMER(props->m_0x128);

      for (i = 0; i < 7; i++) {
        if (props->m_0xe8[i] == 0 && props->m_0x40[i][1].x != 0 &&
            ABS2(g_Spyro.m_Position.z - props->m_0x40[i][0].z) < 2000 &&
            func_80038C4C(&g_Spyro.m_Position, &props->m_0x40[i][0]) != 0) {
          props->m_0xe8[i] = 1;
        }
      }

      if (props->m_0x110[1].x != 0 &&
          func_80038C4C(&g_Spyro.m_Position, &props->m_0x110[0]) != 0) {
        props->m_0x3c = 0;
        for (i = 0; i < 7; i++) {
          if (props->m_0x20[i] != -1) {
            int *linkedProps = g_LevelMobys[props->m_0x20[i]].m_Props;
            props->m_0xe8[i] = 0;
            g_LevelMobys[props->m_0x20[i]].m_Substate = 2;
            linkedProps[5] = linkedProps[8];
          }
        }
      }

      switch (moby->m_State) {
      case 0:
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (props->m_0x128 == 0) {
          int linkedMobyIndex = props->m_0x20[props->m_0x3c];
          if (linkedMobyIndex != -1 && props->m_0xe8[props->m_0x3c] != 0) {
            props->m_0x128 = *(int *)g_LevelMobys[linkedMobyIndex].m_Props;
            props->m_0x130 = 50;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        }

        if (DISTANCE_TO_SPYRO(moby) < 3500 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 1048) {
          props->m_0x12c = 0;
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;

      case 1: {
        int actionTimerExpired;

        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        actionTimerExpired = TICK_TIMER(props->m_0x130);
        if (actionTimerExpired == 0) {
          if (g_GameTick & 1) {
            Vector3D particlePosition;

            func_80052D64(moby, 0, &particlePosition);
            g_SpawnParticle(1, 29, &particlePosition, (int)moby);
          } else {
            Vector3D particlePosition;

            func_80052D64(moby, 1, &particlePosition);
            g_SpawnParticle(1, 29, &particlePosition, (int)moby);
          }
        }

        if ((props->m_0x128 == 0 && props->m_0xe8[props->m_0x3c + 1] != 0) ||
            g_AnimationFinished) {
          props->m_0x3c++;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 2:
        break;

      case 3: {
        int oldNode;
        PathData *path;

        RotateMobyToSpyro(moby, 8, 0x10, 1);
        if (g_AnimationFinished) {
          path = props->m_0x00;
          oldNode = path->m_CurrentNode;
          do {
            props->m_0x00->m_CurrentNode = RandRange(1, path->m_NodeCount) - 1;
            path = props->m_0x00;
          } while (path->m_CurrentNode == oldNode);
          moby->m_State = 5;
          continue;
        }

        if (props->m_0x12c <= 0) {
          props->m_0x12c = 1;
          g_SpawnMoby(38, moby);
        } else if (props->m_0x12c < 2 &&
                   moby->m_AnimationState.m_NextFrame >= 2) {
          props->m_0x12c = 2;
          g_SpawnMoby(38, moby);
        } else if (props->m_0x12c < 60 &&
                   moby->m_AnimationState.m_NextFrame >= 6) {
          props->m_0x12c = 60;
          g_SpawnMoby(38, moby);
        }
        break;
      }

      case 4:
        MoveMobyWithGravity(moby, &props->m_0x108, props->m_0x104,
                            &props->m_0x10c, 0xA, 0x10);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 5: {
        int oldNode = props->m_0x00->m_CurrentNode;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (func_80039E94(moby, props->m_0x00, 0x100, 0xA0, 0, 8, 0x28, 0xFF,
                          5) &
            0x100) {
          props->m_0x00->m_CurrentNode = oldNode;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_205 // Lamp on pole
    case 205: {
      Moby205Props *props;
      MobyCollectableProps *linkedProps;
      int angle;

      props = (Moby205Props *)moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 1) {
        moby->m_State = 1;
        MOBY_ANIM_CHANGE(moby, 1);
        break;
      }

      if (props->m_0x00 >= 0) {
        if (g_LevelMobys[props->m_0x00].m_State >= 0x80) {
          props->m_0x00 = -1;
        } else {
          VecCopy(&g_LevelMobys[props->m_0x00].m_Position, &moby->m_Position);
          g_LevelMobys[props->m_0x00].m_Position.z += 0x800;
          g_LevelMobys[props->m_0x00].m_Substate = 4;
          g_LevelMobys[props->m_0x00].m_Rotation.x = 0;
          g_LevelMobys[props->m_0x00].m_Rotation.y = 0;
          g_LevelMobys[props->m_0x00].m_Rotation.z += 8;
        }
      }

      if (moby->m_State == 1) {
        if (props->m_0x00 >= 0) {
          linkedProps =
              (MobyCollectableProps *)g_LevelMobys[props->m_0x00].m_Props;
          angle = ANGLE_TO_SPYRO(moby->m_Position) << 4;
          g_LevelMobys[props->m_0x00].m_Substate = 2;
          linkedProps->m_RotX = 3;
          linkedProps->m_InitPos.x = FIXED_MUL(Cos(angle), 28);
          linkedProps->m_InitPos.y = FIXED_MUL(Sin(angle), 28);
          linkedProps->m_InitPos.z = 50;
          props->m_0x00 = -1;
        }

        if (g_AnimationFinished) {
          moby->m_DamageFlags = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
        }
      }
      break;
    }
#endif
#if defined(HAS_MOBY_206) || defined(HAS_MOBY_239) || defined(HAS_MOBY_242)
#ifdef HAS_MOBY_206
    case 206: // Small Cactus
#endif
#ifdef HAS_MOBY_239
    case 239: // Tall Cactus
#endif
#ifdef HAS_MOBY_242
    case 242: // Round Cactus
#endif
    {
      Moby *spawned;

      if (moby->m_DamageFlags != 0) {
        if (moby->m_DamageFlags == MOBY_DAMAGE_FLAME && moby->m_Substate == 0) {
          moby->m_Substate = 80;
          if (moby->m_AnimationState.m_Animation != 2) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 2);
          }
        } else if (moby->m_AnimationState.m_NextAnimation == 0 &&
                   moby->m_AnimationState.m_Animation != 1) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 1);
        }
      }

      moby->m_DamageFlags = 0;

      if (g_AnimationFinished) {
        switch (moby->m_AnimationState.m_NextAnimation) {
        case 2:
          spawned = g_SpawnMoby(493, moby);
          spawned->m_Rotation.z = (g_Camera.m_Rotation.z >> 2) - ROTDEG8(180);
          VecCopy(&spawned->m_Position, &moby->m_Position);

          if (moby->m_AnimationState.m_Animation != 3) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 3);
          }
          break;

        case 1:
        case 4:
          if (moby->m_AnimationState.m_Animation != 0) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 0);
          }
          break;
        }
      }

      if (TICK_TIMER(moby->m_Substate) == 2 &&
          moby->m_AnimationState.m_Animation != 4) {
        g_AnimationFinished = 0;
        MOBY_ANIM_RESTART(moby, 4);
      }

      break;
    }
#endif
#ifdef HAS_MOBY_207
    case 207: { // Gnorc Cove Barrel
      Moby207Props *props = moby->m_Props;
      Moby *iter;
      Moby *iter2;
      Moby *bestMoby;
      Vector3D delta;
      int bestScore;
      int angleDiff;
      int distance;
      int score;

      props->m_0x14 = ApplyFlameHeatExternal(moby, props->m_0x14);
      if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) && moby->m_State != 2 &&
          moby->m_State != 3 && moby->m_State != 4) {
        if (props->m_0x10 < 0 || g_LevelMobys[props->m_0x10].m_Class != 201) {
          props->m_0x08 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
          props->m_0x0c = 0x80;
          props->m_0x00 = 0;
          moby->m_Substate = 0;
          moby->m_State = 4;
          moby->m_Position.z += 200;
          func_8003851C(moby, 1, 0);
          bestMoby = 0;
          bestScore = 30000;
          for (iter = g_LevelMobys, iter2 = iter; iter < g_DynMobys;
               iter2++, iter++) {
            if (iter != moby && iter2->m_State < 0x80 &&
                iter2->m_CollisionGroup != 0 &&
                (int)iter2->m_CollisionGroup < 0) {
              VecSub(&delta, &iter->m_Position, &moby->m_Position);
              distance = ABS2(delta.x) + ABS2(delta.y);
              if (distance < 0x6000) {
                angleDiff = (ANGLE_FROM(moby->m_Position, iter2->m_Position) -
                             props->m_0x08) &
                            0xFF;
                if (angleDiff > 0x80) {
                  angleDiff -= 0x100;
                }
                angleDiff = ABS2(angleDiff);
                if (angleDiff < 0xC) {
                  distance = VecMagnitude(&delta, 0);
                  if (distance < 0x4000) {
                    if (distance > 0x2800) {
                      score = distance - 0x2800;
                    } else if (distance < 0x1800) {
                      score = 0x1800 - distance;
                    } else {
                      score = 0;
                    }
                    score += angleDiff << 8;
                    if (score < bestScore) {
                      bestMoby = iter2;
                      bestScore = score;
                    }
                  }
                }
              }
            }
          }
          if (bestMoby != 0) {
            props->m_0x08 = ANGLE_FROM(moby->m_Position, bestMoby->m_Position);
          }
        }
      } else if ((moby->m_DamageFlags & MOBY_DAMAGE_SUPER) &&
                 moby->m_State != 2 && moby->m_State != 3 &&
                 moby->m_State != 4) {
        moby->m_State = 2;
      }
      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0:
        if (props->m_0x10 >= 0 && g_LevelMobys[props->m_0x10].m_State >= 0x80) {
          func_80052568(moby);
          continue;
        }
        break;
      case 2: {
        Moby *frag;
        MobyFragmentProps *fp;
        MobyDragonFragmentProps *dfp;
        int i;

        moby->m_Position.z -= 0x1CD;
        func_800562A4(moby, 1);
        func_8003851C(moby, 0, 0);
        if (moby->m_WasDrawn) {
          for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
            frag = g_SpawnMoby(310, moby);
            fp = frag->m_Props;
            fp->m_Velocity.x >>= 2;
            fp->m_Velocity.y >>= 2;
          }
          for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
            frag = g_SpawnMoby(153, moby);
            dfp = frag->m_Props;
            frag->m_Substate = (rand() & 1) + 0x12;
            VecCopy(&frag->m_Position, &moby->m_Position);
            frag->m_Position.x +=
                (COSINE_8(i << 6) >> 4) + (rand() & 0x1F) - 0xF;
            frag->m_Position.y += (SINE_8(i << 6) >> 4) + (rand() & 0x1F) - 0xF;
            frag->m_Position.z += (rand() & 0xFF) + 0x80;
            dfp->m_Velocity.x = (COSINE_8(i << 6) >> 6) + (rand() & 0x1F) - 0xF;
            dfp->m_Velocity.y = (SINE_8(i << 6) >> 6) + (rand() & 0x1F) - 0xF;
            dfp->m_Velocity.z = (rand() & 0x3F) + 0x18;
            frag->m_Rotation.x = rand();
            frag->m_Rotation.y = rand();
            frag->m_Rotation.z = rand();
            dfp->m_AngularVelocity.x = rand() & 0xF;
            dfp->m_AngularVelocity.y = rand() & 0xF;
            dfp->m_AngularVelocity.z = rand() & 0xF;
            dfp->m_MinZ = moby->m_Position.z;
          }
          for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
            frag = g_SpawnMoby(152, moby);
            dfp = frag->m_Props;
            frag->m_Substate = (rand() & 3) + 0x19;
            VecCopy(&frag->m_Position, &moby->m_Position);
            frag->m_Position.x +=
                (COSINE_8(i << 6) >> 4) + (rand() & 0x3F) - 0x1F;
            frag->m_Position.y +=
                (SINE_8(i << 6) >> 4) + (rand() & 0x3F) - 0x1F;
            frag->m_Position.z += (rand() & 0xFF) + 0x80;
            dfp->m_Velocity.x = (COSINE_8(i << 6) >> 5) + (rand() & 0x1F) - 0xF;
            dfp->m_Velocity.y = (SINE_8(i << 6) >> 5) + (rand() & 0x1F) - 0xF;
            dfp->m_Velocity.z = (rand() & 0x7F) + 0x30;
            frag->m_Rotation.x = rand();
            frag->m_Rotation.y = rand();
            frag->m_Rotation.z = rand();
            dfp->m_AngularVelocity.x = rand() & 0xF;
            dfp->m_AngularVelocity.y = rand() & 0xF;
            dfp->m_AngularVelocity.z = rand() & 0xF;
            dfp->m_MinZ = moby->m_Position.z;
          }
        }
        if (props->m_0x04 != 0 && props->m_0x04->m_Class == 154 &&
            props->m_0x04->m_State == 2) {
          props->m_0x04->m_Substate = 1;
        }
        props->m_0x00 = 0;
        moby->m_RenderRadius = 0;
        moby->m_WasDrawn = 0;
        moby->m_State = 3;
        moby->m_Substate = 0;
        break;
      }
      case 3:
        if (props->m_0x02 == 0) {
          if (func_8004E2E8(&moby->m_Position, (props->m_0x00 + 3) * 0x90,
                            0xC0086)) {
            int mag;
            int dist;

            props->m_0x02 = 1;
            g_Spyro.unk_0x208.x =
                (g_Spyro.m_Position.x - moby->m_Position.x) >> 1;
            g_Spyro.unk_0x208.y =
                (g_Spyro.m_Position.y - moby->m_Position.y) >> 1;
            g_Spyro.unk_0x208.z = 0;
            if (g_Spyro.unk_0x208.x != 0 || g_Spyro.unk_0x208.y != 0) {
              mag = VecMagnitude(&g_Spyro.unk_0x208, 1);
              dist = DISTANCE_TO_SPYRO(moby);
              VecScaleToLength(&g_Spyro.unk_0x208, mag, (0x1000 - dist) >> 6);
            }
            g_Spyro.unk_0x208.z = 0x46;
          }
        }
        func_8004E3C8(&moby->m_Position, (props->m_0x00 + 2) << 8, 0, 0x90000,
                      moby, 2);
        props->m_0x00++;
        if (props->m_0x00 >= 8) {
          func_8003B7C0(moby);
          func_80052568(moby);
          continue;
        }
        break;
      case 4: {
        int result;

        moby->m_Position.z += props->m_0x0c;
        props->m_0x00 += g_DeltaTime;
        if (props->m_0x00 >= 0x10) {
          result = func_80039688(moby, props->m_0x08, 0xF0, 0x200, 0x200, 0);
          if (result != 0) {
            if (result == 2 && (g_SurfaceBelowFlags & 0x3F) == 0) {
              Moby *splash = g_SpawnMoby(400, moby);
              func_800562A4(moby, 1);
              PlaySound(g_Models[moby->m_Class]->m_Sounds[3], splash, 8,
                        &splash->m_SoundChannel);
              if (props->m_0x04 != 0 && props->m_0x04->m_Class == 154 &&
                  props->m_0x04->m_State == 2) {
                props->m_0x04->m_Substate = 1;
              }
              func_80052568(moby);
              continue;
            }
            moby->m_State = 2;
          }
        } else {
          result = func_80039688(moby, props->m_0x08, 0xF0, 0, 0x200, 0);
          if (result != 0) {
            if (result == 2 && (g_SurfaceBelowFlags & 0x3F) == 0) {
              Moby *splash = g_SpawnMoby(400, moby);
              func_800562A4(moby, 1);
              PlaySound(g_Models[moby->m_Class]->m_Sounds[3], splash, 8,
                        &splash->m_SoundChannel);
              if (props->m_0x04 != 0 && props->m_0x04->m_Class == 154 &&
                  props->m_0x04->m_State == 2) {
                props->m_0x04->m_Substate = 1;
              }
              func_80052568(moby);
              continue;
            }
            moby->m_State = 2;
          }
        }
        moby->m_Rotation.x += 7;
        moby->m_Rotation.y -= 4;
        moby->m_Rotation.z += 3;
        props->m_0x0c -= 0xA;
        if (props->m_0x0c < -0x80) {
          props->m_0x0c = -0x80;
        }
        func_8004D5EC(&moby->m_Position, 0x2000);
        func_800533D0(moby);
        break;
      }
      }

      if (moby->m_Substate != 0) {
        int floorZ;

        func_8003851C(moby, 2, &moby->m_SoundChannel);
        moby->m_Rotation.x += 6;
        floorZ = func_8004D5EC(&moby->m_Position, 0x800);
        if (moby->m_Position.z - floorZ >= 0x181) {
          props->m_0x0c -= 0xA;
          if (props->m_0x0c < -0x80) {
            props->m_0x0c = -0x80;
          }
          moby->m_Position.z += props->m_0x0c;
        } else if ((g_SurfaceBelowFlags & 0x3F) == 0) {
          Moby *splash = g_SpawnMoby(400, moby);
          func_800562A4(moby, 1);
          PlaySound(g_Models[moby->m_Class]->m_Sounds[3], splash, 8,
                    &splash->m_SoundChannel);
          if (props->m_0x04 != 0 && props->m_0x04->m_Class == 154 &&
              props->m_0x04->m_State == 2) {
            props->m_0x04->m_Substate = 1;
          }
          func_80052568(moby);
          continue;
        } else {
          props->m_0x0c = -0xA;
          moby->m_Position.z = floorZ + 0x180;
        }

        if (func_80039688(moby, (moby->m_Rotation.z - 0x40) & 0xFF, 0x80, 0x200,
                          0x200, 1)) {
          moby->m_State = 2;
        }
        if (SPYRO_ORIGIN_Z_DELTA(moby) < 0x80) {
          func_8004E2E8(&moby->m_Position, 0x200, 0x10);
        }
        if (TICK_TIMER(props->m_0x00)) {
          moby->m_State = 2;
        }
        if (g_Spyro.m_State == 0x19 || g_Spyro.m_State == 0x1F) {
          moby->m_CollisionGroup = 0;
        }
        func_8004D5EC(&moby->m_Position, 0x2000);
        func_800533D0(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_208
    case 208: { // Gnorc Gnexus Dragon Head Opener
      Moby208Props *doorProps = moby->m_Props;
      // Checks once if the dragon heads should open,
      // provided their level has been visited before
      if (!doorProps->m_HeadsInitChecked) {
        // Twilight Harbor visited
        if (g_VisitedFlags[32] != 0) {
          func_8002B390(0, 0xFC, 0);
          if (g_Spyro.m_State == 0xF && g_Spyro.m_walkingState == 9)
            func_8002B444(0, 0x3B, 0);
        }
        // Gnasty Gnorc visited
        if (g_VisitedFlags[33] != 0) {
          func_8002B390(1, 0xFC, 0);
          if (g_Spyro.m_State == 0xF && g_Spyro.m_walkingState == 9)
            func_8002B444(1, 0x3B, 0);
        }
        // Gnasty's Loot visited
        if (g_VisitedFlags[34] != 0) {
          func_8002B390(2, 0xFC, 0);
          if (g_Spyro.m_State == 0xF && g_Spyro.m_walkingState == 9)
            func_8002B444(2, 0x3B, 0);
        }
        doorProps->m_HeadsInitChecked = 1;
      }

      // Usual head open conditions
      if (((func_8002B3F4(0) >> 8) & 0xFF) == 0 &&
          g_LevelVortexExitFlags[31] != 0 && g_LevelDragonCount[30] > 0) {
        func_8002B390(0, 0xFC, 0);
      }
      if (((func_8002B3F4(1) >> 8) & 0xFF) == 0 &&
          g_LevelVortexExitFlags[32] != 0) {
        func_8002B390(1, 0xFC, 0);
      }
      if (((func_8002B3F4(2) >> 8) & 0xFF) == 0 && g_GemTotal >= 12000 &&
          g_DragonTotal >= 80 && g_EggTotal >= 12) {
        func_8002B390(2, 0xFC, 0);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_209 // Snowball Projectile
    case 209: {
      Moby209Props *props = moby->m_Props;

      if (TICK_TIMER(props->m_Lifetime)) {
        // Destroy snowball if its lifetime expired
        g_SpawnParticle(16, 15, &moby->m_Position, 0);
        func_80052568(moby);
      } else if (func_80039228(moby, props->m_Velocity, 0, 200, 0) != 0) {
        // Destroy snowball if it collides with the environment
        g_SpawnParticle(16, 15, &moby->m_Position, 0);
        func_80052568(moby);
      } else if (func_8004E2E8(&moby->m_Position, 0x80, 1) != 0) {
        // Damage Spyro if the snowball collides with him
        func_8003851C(moby, 0, 0);
        g_SpawnParticle(16, 15, &moby->m_Position, 0);
        func_80052568(moby);
      } else {
        // If the snowball doesn't collide and the lifetime isn't expired,
        // merely spawn trail particles
        g_SpawnParticle(1, 75, &moby->m_Position, 0);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_210
    case 210: {

      Moby210Props *props = moby->m_Props;

      moby->m_RenderRadius = 0x20;
      moby->m_Rotation.z += moby->m_Substate;
      if (props->m_0x00 > props->m_0x08) {
        props->m_0x00 -= props->m_0x08;
      }
      moby->m_ScaleOverride =
          0x3A - ((props->m_0x08 - props->m_0x00) * 20) / props->m_0x08;
      moby->m_Position.z = props->m_0x0c + props->m_0x00;
      break;
    }
#endif
#if defined(HAS_MOBY_211) || defined(HAS_MOBY_212)
#ifdef HAS_MOBY_211 // Ski Gnorc (Green)
    case 211:
#endif
#ifdef HAS_MOBY_212 // Ski Gnorc (Purple)
    case 212:
#endif
    {
      Moby211Props *props;
      Moby *projectile;
      Moby209Props *projectileProps;
      int angle;
      int result;
      int length;
      int triggerFrame;

      props = (Moby211Props *)moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 3) {
        angle = ANGLE_FROM_SPYRO(moby->m_Position);
        props->m_0x1c =
            func_80038178(angle, g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x20 = 0xB4;
        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
          props->m_0x20 = 300;
        }
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        break;
      }

      switch (moby->m_State) {
      case 0: {
        if (props->m_0x04 == 0) {
          props->m_0x04 =
              OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
          props->m_0x08 =
              ANGLE_FROM(PATH_CUR_POS(props->m_0x00), moby->m_Position) << 2;
        }
        if (props->m_0x10 != 0) {
          if (DISTANCE_TO_SPYRO(moby) < (props->m_0x10 << 10)) {
            func_8003B1E8(moby, 1);
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        } else if (DISTANCE_TO_SPYRO(moby) < 0x3800) {
          func_8003B1E8(moby, 1);
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;
      }

      case 1: {
        angle = ANGLE_TO_SPYRO(PATH_CUR_POS(props->m_0x00));
        result = func_80038638(moby, &PATH_NODE_POS(props->m_0x00, 0),
                               props->m_0x04, angle, 8, props->m_0x14, 0x0E,
                               0x80, props->m_0x24, props->m_0x28, 0, 0, 4);
        if (result == 0x100 || result < 0x40) {
          Vector3D vec;
          angle = func_80038074(moby->m_Rotation.z, 0xE0);
          vec.x = moby->m_Position.x + FIXED_MUL(COSINE_8(angle), 700);
          vec.y = moby->m_Position.y + FIXED_MUL(SINE_8(angle), 700);
          vec.z = moby->m_Position.z + 700;
          if (func_80038250(&vec) != 0) {
            if (moby->m_WasDrawn) {
              if (TICK_TIMER(props->m_0x2c)) {
                moby->m_State = 2;
                MOBY_ANIM_CHANGE(moby, 2);
                continue;
              }
            } else {
              props->m_0x2c = 0x1E;
            }
          } else {
            props->m_0x2c = 0x1E;
          }
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        break;
      }

      case 2: {
        if (moby->m_Class == 211) {
          triggerFrame = 23;
        } else {
          triggerFrame = 19;
        }
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (g_AnimFrameFinished != 0 &&
            moby->m_AnimationState.m_Frame == triggerFrame) {
          // Result is not used
          func_80038074(moby->m_Rotation.z, ROTDEG8(315));

          projectile = g_SpawnMoby(209, moby);
          projectile->m_Rotation.z = moby->m_Rotation.z;
          projectileProps = projectile->m_Props;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 0, &projectile->m_Position);
          VecSub(&projectileProps->m_Velocity, &g_Spyro.m_Position,
                 &projectile->m_Position);
          length = VecMagnitude(&projectileProps->m_Velocity, 1);
          VecScaleToLength(&projectileProps->m_Velocity, length, 200);
          projectileProps->m_Lifetime = 140;
          props->m_0x1c = func_80038074(moby->m_Rotation.z, 0x80);
          props->m_0x20 = 0;
          props->m_0x2c = 0x1E;
        }
        if (props->m_0x20 != 0) {
          func_80039688(moby, props->m_0x1c, props->m_0x20, 300, 300, 1);
          props->m_0x20 -= 0x14;
          if (props->m_0x20 < 0) {
            props->m_0x20 = 0;
          }
        }
        if (g_AnimationFinished) {
          moby->m_State = 4;
          continue;
        }
        break;
      }

      case 3: {
        if (props->m_0x20 != 0) {
          func_80039688(moby, props->m_0x1c, props->m_0x20, 300, 300, 1);
          props->m_0x20 -= 0x0C;
          if (props->m_0x20 < 0) {
            props->m_0x20 = 0;
          }
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }

      case 4: {
        angle = ANGLE_FROM_SPYRO(PATH_CUR_POS(props->m_0x00));
        result = func_80038638(moby, &PATH_NODE_POS(props->m_0x00, 0),
                               props->m_0x04, angle, 8, props->m_0x18, 0x0E,
                               0x80, props->m_0x24, props->m_0x28, 0, 0, 4);
        if (result < 0x0A) {
          props->m_0x0c = 0x5A;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          moby->m_State = 6;
          continue;
        } else if (result == 0x100) {
          props->m_0x0c = 0x78;
          moby->m_State = 5;
          continue;
        } else {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        }
        break;
      }

      case 5: {
        RotateMobyToSpyro(moby, 5, 0, 0);
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        if (func_80017908(moby->m_Rotation.z, angle) < ROTDEG8(15) &&
            moby->m_AnimationState.m_NextAnimation != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 0);
        }
        if (TICK_TIMER(props->m_0x0c)) {
          Vector3D vec;
          angle = func_80038074(moby->m_Rotation.z, ROTDEG8(315));
          vec.x = moby->m_Position.x + FIXED_MUL(COSINE_8(angle), 700);
          vec.y = moby->m_Position.y + FIXED_MUL(SINE_8(angle), 700);
          vec.z = moby->m_Position.z + 700;
          if (func_80038250(&vec) != 0) {
            if (moby->m_WasDrawn) {
              if (TICK_TIMER(props->m_0x2c)) {
                props->m_0x0c = 120;
                moby->m_State = 2;
                MOBY_ANIM_CHANGE(moby, 2);
                continue;
              }
            } else {
              props->m_0x2c = 0x1E;
            }
          } else {
            props->m_0x2c = 0x1E;
          }
        }
        break;
      }

      case 6: {
        if (TICK_TIMER(props->m_0x0c)) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        } else {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          angle = func_80038074(angle, 0x80);
          RotateMobyToAngle(moby, angle, 5, 0, 0);
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_213 // Bat Fodder
    case 213: {
      Moby213Props *props;
      Vector3D vec;
      int distance;

      props = (Moby213Props *)moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 4) {
        if (moby->m_State != 1 || props->m_0x0c == 0) {
          VecSub(&vec, &g_Spyro.m_Position, &moby->m_Position);
          VecShiftRight(&vec, 2);
          VecAdd(&moby->m_Position, &vec, &moby->m_Position);
        }

        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 4;
        MOBY_ANIM_RESTART(moby, 4);
        break;
      }

      switch (moby->m_State) {
      case 0: {
        if (props->m_0x0c != 0) {
          props->m_0x0c--;
        } else if (DISTANCE_TO_SPYRO(moby) < 0x800) {
          props->m_0x0c = 0x78;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      }

      case 1: {
        Vector3D vec2;
        if (props->m_0x0c == 0) {
          MoveMobyTowardTarget(moby, &props->m_RespawnPosition, 0x40, 8, 8, 0);
          VecSub(&vec2, &props->m_RespawnPosition, &moby->m_Position);
          distance = VecMagnitude(&vec2, 1);

          if (distance < 0x200) {
            props->m_0x0c = 0x78;
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
            continue;
          }
        } else {
          vec2.x = FIXED_MUL(props->m_0x10, Cos(props->m_0x14));
          vec2.y = FIXED_MUL(props->m_0x10, Sin(props->m_0x14));
          vec2.z = props->m_0x18;
          VecAdd(&vec2, &vec2, &g_Spyro.m_Position);
          MoveMobyTowardTarget(moby, &vec2, 0x60, 8, 8, 0x100);
          props->m_0x14 = (props->m_0x14 + 0x10) & 0xFFF;
          props->m_0x0c--;
        }

        if (TICK_TIMER(props->m_0x1c)) {
          if ((rand() % 3) != 0) {
            func_8003851C(moby, rand() % 3, 0);
          }
          props->m_0x1c = 0x3C;
        }

        break;
      }

      case 2: {
        if (g_AnimationFinished) {
          props->m_0x14 = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
          props->m_0x10 = (rand() & 0x1FF) + 0x400;
          props->m_0x18 = 0;
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;
      }

      case 3: {
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;
      }

      case 4: {
        if (g_AnimationFinished) {
          func_80052568(moby);
          continue;
        }
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#if defined(HAS_MOBY_214) || defined(HAS_MOBY_216)
#ifdef HAS_MOBY_214
    case 214:
#endif
#ifdef HAS_MOBY_216
    case 216:
#endif
    {
      Moby214Props *props = moby->m_Props;
      Vector3D groundPosition;

      if (moby->m_DamageFlags != 0 && moby->m_State == 11) {
        if (g_LevelMobys[props->m_0x44].m_CollisionGroup != 0) {
          moby->m_DamageFlags = 0;
        }
      }

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 3) {
        moby->m_DamageFlags = 0;

        if (moby->m_State != 11 || moby->m_RenderRadius != 0) {
          props->m_0x54 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
          props->m_0x58 = 0xFA;

          if (props->m_0x24 == 2 || props->m_0x24 == 3 || props->m_0x24 == 8) {
            Moby *linkedMoby = &g_LevelMobys[props->m_0x44];
            MOBY_ANIM_CHANGE(linkedMoby, 0);
          }

          if (moby->m_State < 10 &&
              (props->m_0x24 == 4 || props->m_0x24 == 10)) {
            func_8003B538(moby, 0xA, 0);
            func_8003B538(moby, 0xA, 2);
            func_8003B538(moby, 0xA, 4);
            func_8003B538(moby, 0xA, 1);
            func_8003B538(moby, 0xA, 100);
          }

          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 3;
          MOBY_ANIM_RESTART(moby, 3);
          continue;
        }
      }

      if (props->m_0x64 != 0) {
        props->m_0x64 = 0;
        if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
          if (moby->m_DropMoby != 0xFF) {
            func_8003ABC0(moby, 1, 0, 0);
            func_8003B7C0(moby);
          }
          func_80052568(moby);
          continue;
        }
      }

      VecCopy(&groundPosition, &moby->m_Position);
      groundPosition.z += 0x400;
      func_8004D5EC(&groundPosition, 0x10000);
      func_800533D0(moby);

      switch (moby->m_State) {
      case 0:
        switch (props->m_0x24) {
        case 0:
          if (!TICK_TIMER(props->m_0x28)) {
            RotateMobyToSpyro(moby, 4, 0, 0);
          } else {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            if (func_80039E94(moby, props->m_0x20, 0x80, 0x46, 0, 4, 0x14, 0xFF,
                              5) != 0) {
              props->m_0x28 = RandRange(0x78, 0xB4);
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 6);
            }
          }
          if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
            moby->m_State = 4;
            continue;
          }
          break;
        case 1:
        case 2:
          if (DISTANCE_TO_SPYRO(moby) < 0x2800) {
            func_8003B47C(moby, 4, 3);
          }
          break;
        case 3:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
          moby->m_State = 9;
          continue;
        case 4:
          if (!TICK_TIMER(props->m_0x28)) {
            RotateMobyToSpyro(moby, 4, 0, 0);
          } else {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            if (func_80039E94(moby, props->m_0x20, 0x80, 0x46, 0, 4, 0x14, 0xFF,
                              5) != 0) {
              props->m_0x28 = RandRange(0x78, 0xB4);
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 6);
            }
          }
          if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
            func_8003B538(moby, 4, 0);
          }
          break;
        case 5:
        case 6:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          func_80038458(moby);
          func_80039AA8(moby, &props->m_Wander);
          if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
            func_8003B538(moby, 0xA, 0);
          }
          break;
        case 8:
          moby->m_State = 8;
          continue;
        case 9:
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (DISTANCE_TO_SPYRO(moby) < 0x1800) {
            func_8003B538(moby, 1, 0);
          }
          break;
        case 10:
          if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
            func_8003B538(moby, 4, 0);
          }
          break;
        case 11:
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (DISTANCE_TO_SPYRO(moby) < 1100) {
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
          break;
        }
        break;

      case 1:
        switch (props->m_0x24) {
        case 0:
        case 1:
        case 9: {
          int distance;

          distance = DISTANCE_TO_SPYRO(moby);
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          if (!TICK_TIMER(props->m_0x2c)) {
            break;
          }
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (func_80039398(moby, 0x46, 300, 300, 0x15) != 0) {
            moby->m_State = 100;
            continue;
          }
          if (distance < 1100) {
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
          if (props->m_0x24 == 9) {
            if (OctDistance(&moby->m_Position, &props->m_0x30) > 0x1000) {
              moby->m_State = 100;
              continue;
            }
          } else if (OctDistance(&moby->m_Position, &props->m_0x30) > 0x1800) {
            moby->m_State = 100;
            continue;
          }
          break;
        }

        case 2: {
          Moby *linkedMoby;
          int angle;
          int distance;

          linkedMoby = &g_LevelMobys[props->m_0x44];
          angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
          distance = OctDistance(&moby->m_Position, &linkedMoby->m_Position);

          if (moby->m_Substate == 0) {
            moby->m_Substate = 1;
            props->m_0x40 = 0x32;
          }

          if (RotateMobyToAngle(moby, angle, 8, 0x28, 1) == 0) {
            break;
          }

          if (props->m_0x40 < 170) {
            props->m_0x40 += 0x1E;
          }

          func_80039398(moby, props->m_0x40, 0, 0, 5);

          if (distance < 1500) {
            props->m_0x28 = 0x50;
            moby->m_State = 8;
            continue;
          }
          break;
        }

        case 4:
        case 10: {
          int distance;

          distance = DISTANCE_TO_SPYRO(moby);
          if (!TICK_TIMER(props->m_0x2c)) {
            break;
          }
          if (func_80038C4C(&moby->m_Position, &props->m_0x68) != 0) {
            moby->m_State = 100;
            continue;
          }
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (func_80039398(moby, 0x46, 300, 300, 5) != 0) {
            moby->m_State = 100;
            continue;
          }
          if (distance < 1100) {
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
          if (OctDistance(&moby->m_Position, &props->m_0x30) > 0x3000) {
            moby->m_State = 100;
            continue;
          }
          break;
        }
        }
        break;

      case 2:
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (g_AnimationFinished) {
          moby->m_State = 100;
          continue;
        }
        g_Spyro.unk_0x208.x = FIXED_MUL(SINE_8(moby->m_Rotation.z), -0x80);
        g_Spyro.unk_0x208.y = FIXED_MUL(COSINE_8(moby->m_Rotation.z), 0x80);
        g_Spyro.unk_0x208.z = 0;
        break;

      case 3:
        if (props->m_0x58 != 0) {
          func_80039688(moby, props->m_0x54, props->m_0x58, 300, 300, 5);
          props->m_0x58 -= 0x14;
          if (props->m_0x58 < 0) {
            props->m_0x58 = 0;
          }
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 4:
        if (props->m_0x24 == 2) {
          moby->m_AnimationState.m_PerFrameProgress = 0x30;
        }

        if (RotateMobyToSpyro(moby, 6, 0xF, 1) != 0) {
          if (props->m_0x24 == 10) {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 15);
          } else if (moby->m_AnimationState.m_NextAnimation != 4) {
            g_AnimationFinished = 0;
            MOBY_ANIM_ADVANCE(moby, 4);
          }
        }

        if ((g_AnimationFinished && moby->m_AnimationState.m_Animation == 4) ||
            moby->m_AnimationState.m_Animation == 15) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;
      case 8: {
        Moby237Props *projectileProps;
        Moby *linkedMoby;
        Moby *projectile;
        int angle;
        int result;
        int distance;

        linkedMoby = &g_LevelMobys[props->m_0x44];
        DISTANCE_TO_SPYRO(moby);
        angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
        result = func_80038074(ANGLE_TO_SPYRO(linkedMoby->m_Position), 0x80);
        distance = func_80038638(moby, &linkedMoby->m_Position, 1500, result, 4,
                                 0x32, 0xE, 0x80, 0xFF, 0xFF, 0, 0, 0xD);
        RotateMobyToAngle(linkedMoby, angle, 4, 0, 0);

        if (distance < 10) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        } else if (moby->m_AnimationState.m_NextAnimation != 1) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 1);
        }

        if (moby->m_AnimationState.m_Animation == 1 &&
            moby->m_AnimationState.m_NextAnimation == 1 &&
            g_AnimFrameFinished != 0 &&
            moby->m_AnimationState.m_Frame == 0x10) {
          moby->m_AnimationState.m_Frame = 5;
          moby->m_AnimationState.m_NextFrame = 6;
          moby->m_AnimationState.m_FrameProgress = 0;
        }

        if (linkedMoby->m_AnimationState.m_Animation < 3) {
          if (distance >= 11) {
            if (func_800381BC(angle, result) < 0) {
              MOBY_ANIM_CHANGE(linkedMoby, 1);
            } else if (linkedMoby->m_AnimationState.m_NextAnimation != 2) {
              MOBY_ANIM_ADVANCE(linkedMoby, 2);
            }
          } else if (linkedMoby->m_AnimationState.m_NextAnimation != 0) {
            MOBY_ANIM_ADVANCE(linkedMoby, 0);
          }
        }

        if (TICK_TIMER(props->m_0x28)) {
          int spyroDistance;

          spyroDistance = DISTANCE_TO_SPYRO(moby);

          if (moby->m_WasDrawn) {
            props->m_0x5c += g_DeltaTime;
          } else {
            props->m_0x5c = 0;
          }

          if (distance < 4 && spyroDistance > 0x1400 &&
              spyroDistance < 0x3C00 && props->m_0x5c > 0x50 &&
              func_80033E40(&moby->m_Position, &g_Spyro.m_Position) != 0) {
            Vector3D targetPosition;

            projectile = g_SpawnMoby(237, moby);
            projectileProps = projectile->m_Props;
            VecCopy(&projectile->m_Position, &linkedMoby->m_Position);
            projectile->m_Rotation.z = linkedMoby->m_Rotation.z;
            func_80039398(projectile, 1500, 0, 0, 0);
            projectile->m_Position.z += 0x4E2;
            projectile->m_Rotation.z = ANGLE_TO_SPYRO(projectile->m_Position);
            VecCopy(&targetPosition, &g_Spyro.m_Position);
            targetPosition.z -= 300;
            projectileProps->m_0x00 = 0xB4;
            projectileProps->m_0x08 = -5;
            projectileProps->m_0x04 = func_8003891C(
                &projectile->m_Position, &targetPosition,
                projectileProps->m_0x00, projectileProps->m_0x08, 0);
            projectileProps->m_0x0c = 0xB4;
            projectileProps->m_0x0e = 0;
            projectileProps->m_0x10 = -1;
            projectileProps->m_0x14 = 0;
            props->m_0x28 = 0xB4;

            if (props->m_0x48 != -1) {
              Moby *linkedMoby2 = &g_LevelMobys[props->m_0x48];
              ((int *)linkedMoby2->m_Props)[10] = 0x5A;
            }
            if (linkedMoby->m_AnimationState.m_Animation != 3) {
              MOBY_ANIM_RESTART(linkedMoby, 3);
            }
          }
        }
        break;
      }
      case 9: {
        Moby *linkedMoby;
        Moby *linkedMoby2;
        Moby *childMoby;
        int *childProps;

        linkedMoby = &g_LevelMobys[props->m_0x44];
        linkedMoby2 = &g_LevelMobys[props->m_0x48];
        RotateMobyToAngle(moby,
                          ANGLE_FROM(moby->m_Position, linkedMoby->m_Position),
                          4, 0, 0);

        if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
          if (linkedMoby2->m_State < 0x80) {
            ((int *)linkedMoby2->m_Props)[10] = 0xB4;
            MOBY_ANIM_CHANGE(linkedMoby2, 8);
            linkedMoby2->m_State = 8;
          }

          props->m_0x28 = 0xB4;
          moby->m_State = 8;
          MOBY_ANIM_CHANGE(moby, 8);
          continue;
        }

        if (props->m_0x4c != 0) {
          childMoby = &g_LevelMobys[((int *)linkedMoby->m_Props)[1]];
          childProps = childMoby->m_Props;

          if (TICK_TIMER(props->m_0x4c) == 2) {
            Moby237Props *projectileProps;
            Moby *projectile;
            Vector3D targetPosition;
            int flightTime;
            int angle;

            angle = ANGLE_FROM(moby->m_Position, childMoby->m_Position);
            projectile = g_SpawnMoby(237, moby);
            projectileProps = projectile->m_Props;
            VecCopy(&projectile->m_Position, &linkedMoby->m_Position);
            projectile->m_Rotation.z = angle;
            func_80039398(projectile, 1350, 0, 0, 0);
            projectile->m_Position.z += 1350;
            VecCopy(&targetPosition, &childMoby->m_Position);
            targetPosition.z += 1325;
            targetPosition.x +=
                FIXED_MUL(COSINE_8(childMoby->m_Rotation.z), 1075);
            targetPosition.y +=
                FIXED_MUL(SINE_8(childMoby->m_Rotation.z), 1075);
            projectileProps->m_0x00 = 180;
            projectileProps->m_0x08 = -5;
            projectileProps->m_0x04 = func_8003891C(
                &projectile->m_Position, &targetPosition,
                projectileProps->m_0x00, projectileProps->m_0x08, &flightTime);
            projectileProps->m_0x0e = 1;
            projectileProps->m_0x10 = -1;
            projectileProps->m_0x14 = 0;
            projectileProps->m_0x0c = flightTime + 1;
            projectile->m_RenderRadius = 0x30;
            childProps[3] = flightTime + 1;

            if (linkedMoby->m_AnimationState.m_Animation != 3) {
              MOBY_ANIM_RESTART(linkedMoby, 3);
            }
          }
        }
        break;
      }

      case 10: {
        Moby *linkedMoby;

        linkedMoby = &g_LevelMobys[props->m_0x44];

        if (props->m_0x50 == 0) {
          if ((rand() & 1) != 0) {
            props->m_0x60 = 1;
          }
          props->m_0x28 = RandRange(0, 0x28);
          props->m_0x50 = 1;
        } else if (props->m_0x50 == 1) {
          int result;

          result = RotateMobyToSpyro(moby, 6, 0xA, 1);
          if (TICK_TIMER(props->m_0x28) && result != 0 &&
              moby->m_AnimationState.m_NextAnimation != 9) {
            g_AnimationFinished = 0;
            MOBY_ANIM_ADVANCE(moby, 9);
          }
          if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 9) {
            props->m_0x50 = 2;
            if (moby->m_AnimationState.m_Animation != 1) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 1);
            }
          }
        } else {
          Vector3D targetPosition;
          int angle;

          if (moby->m_Class == 216 && linkedMoby->m_State >= 0x80) {
            moby->m_Substate = 1;
            moby->m_State = 11;
            MOBY_ANIM_RESTART(moby, 11);
            continue;
          }
          if (props->m_0x24 == 6 && moby->m_Class == 214) {
            props->m_0x24 = 2;
            moby->m_State = 1;
            continue;
          }

          VecCopy(&targetPosition, &linkedMoby->m_Position);
          targetPosition.x +=
              FIXED_MUL(COSINE_8(linkedMoby->m_Rotation.z), 2500);
          targetPosition.y += FIXED_MUL(SINE_8(linkedMoby->m_Rotation.z), 2500);

          if (OctDistance(&moby->m_Position, &targetPosition) < 0x200) {
            angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
            if (RotateMobyToAngle(moby, angle, 6, 6, 1) != 0) {
              moby->m_Substate = 0;
              moby->m_State = 16;
              MOBY_ANIM_RESTART(moby, 16);
              continue;
            }
          } else {
            angle = ANGLE_FROM(moby->m_Position, targetPosition);
            if (RotateMobyToAngle(moby, angle, 6, 0x14, 1) != 0) {
              if (props->m_0x40 < 0x82) {
                props->m_0x40 += 0x14;
              }
              func_80039398(moby, props->m_0x40, 0, 0, 4);
            }
          }
        }
        break;
      }
      case 11: {
        Moby *linkedMoby;

        linkedMoby = &g_LevelMobys[props->m_0x44];

        if (linkedMoby->m_AnimationState.m_Animation < 2) {
          moby->m_RenderRadius = 0;
          break;
        }

        RotateMobyToSpyro(moby, 4, 0, 0);

        if (moby->m_Substate == 0) {
          VecCopy(&moby->m_Position, &linkedMoby->m_Position);
          moby->m_RenderRadius = 0x20;
          moby->m_Substate = 1;
          moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);
          if (moby->m_AnimationState.m_Animation != 12) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 12);
          }
        }

        if (moby->m_AnimationState.m_Animation == 17) {
          if (func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) >= 0x17 ||
              props->m_0x60 != 0) {
            if (g_AnimFrameFinished != 0 &&
                moby->m_AnimationState.m_NextFrame >= 0x32) {
              moby->m_AnimationState.m_Frame = 0x24;
              moby->m_AnimationState.m_NextFrame = 0x25;
              moby->m_AnimationState.m_FrameProgress = 0;
            }
          } else {
            if (moby->m_AnimationState.m_NextFrame >= 37 &&
                moby->m_AnimationState.m_NextFrame < 50) {
              moby->m_AnimationState.m_Frame = 0x32;
              moby->m_AnimationState.m_NextFrame = 0x33;
              moby->m_AnimationState.m_FrameProgress = 0;
            }
            if (g_AnimationFinished &&
                moby->m_AnimationState.m_Animation != 12) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 12);
            }
          }
        } else if (g_AnimationFinished) {
          if (func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) >= 23 ||
              props->m_0x60 != 0) {
            if (moby->m_AnimationState.m_Animation != 17) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 17);
            }
            moby->m_AnimationState.m_Frame = 0x16;
            moby->m_AnimationState.m_NextFrame = 0x17;
            moby->m_AnimationState.m_FrameProgress = 0;
          }
        }
        break;
      }

      case 16: {
        Moby *linkedMoby;

        linkedMoby = &g_LevelMobys[props->m_0x44];

        if (moby->m_AnimationState.m_NextFrame == 0xB) {
          moby->m_RenderRadius = 0;
          moby->m_State = 11;
          MOBY_ANIM_RESTART(moby, 11);
          continue;
        }

        if (OctDistance(&moby->m_Position, &linkedMoby->m_Position) >= 0x65) {
          func_80039688(moby,
                        ANGLE_FROM(moby->m_Position, linkedMoby->m_Position),
                        100, 0, 0, 0);
        } else {
          VecCopy(&moby->m_Position, &linkedMoby->m_Position);
        }

        if (moby->m_AnimationState.m_Frame < 5) {
          break;
        }

        if (linkedMoby->m_State != 0) {
          break;
        }

        if (linkedMoby->m_AnimationState.m_Animation != 1) {
          MOBY_ANIM_RESTART(linkedMoby, 1);
        }
        linkedMoby->m_State = 1;
        break;
      }

      case 100: {
        int angle;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

        angle = ANGLE_FROM(moby->m_Position, props->m_0x30);
        if (RotateMobyToAngle(moby, angle, 4, 0x14, 1) != 0) {
          func_80039398(moby, 0x5A, 0, 0, 5);
        }

        if (OctDistance(&moby->m_Position, &props->m_0x30) < 0x80) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      if (moby->m_RenderRadius == 0) {
        moby->m_CollisionGroup = 0;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_217 // True Ending Cutscene Trigger in Loot
    case 217: {
      Moby217Props *props = moby->m_Props;

      // If we collected all Gems and Spyro is in the Vortex
      if (g_GemTotal == 14000 && g_Spyro.m_State == 17) {
        // Fade to black
        if (props->m_Timer < 16) {
          g_Fade = 16 - props->m_Timer;

          if (g_Fade >= 16) {
            g_Fade = 15;
          }
        }

        if (TICK_TIMER(props->m_Timer)) {
          g_LevelVortexExitFlags[g_LevelIndex] = 1;
          // "True Ending" Cutscene
          g_CutsceneIdx = 3;
          g_Gamestate = GS_Cutscene;
          g_StateSwitch = 1;
          g_CutsceneLayout->m_CurrentTick = 0;
        }
      }
      // Falls through to the next case, which is 286 in Loot
    }
#endif
#ifdef HAS_MOBY_218
    case 218: {
      Moby218Props *props;
      MobyCollectableProps *linkedProps;
      Moby *linkedMoby;
      Vector3D oldPosition;
      Vector3D particleVelocity;
      int distance;
      int angle;
      int distanceFactor;
      int height;
      int step;
      int count;

      props = moby->m_Props;

      if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
        distance = DISTANCE_TO_SPYRO(moby);
        angle = func_80017908(g_Spyro.m_bodyRotation.z,
                              ANGLE_FROM_SPYRO(moby->m_Position));
        moby->m_DamageFlags = 0;

        if (props->m_0x00 == 0) {
          distanceFactor = (6000 - distance) >> 6;
          angle = (40 - angle) * 70;
          props->m_0x10 = 90;
          props->m_0x04 = FIXED_MUL(distanceFactor, angle);
        }

        if (props->m_0x04 > 0x50) {
          props->m_0x04 = 0x50;
        }
      }

      props->m_0x00 += props->m_0x04;

      if (props->m_0x00 > 0x120) {
        props->m_0x00 = 0x120;
      }

      if (props->m_0x00 < 0) {
        props->m_0x00 = 0;
      }

      props->m_0x04 -= 4;

      if (props->m_0x04 < -0x20) {
        props->m_0x04 = -0x20;
      }

      moby->m_AnimationState.m_Frame = props->m_0x00 >> 5;
      moby->m_AnimationState.m_NextFrame = props->m_0x00 >> 5;

      if (props->m_0x08 >= 0) {
        linkedMoby = &g_LevelMobys[props->m_0x08];

        if (linkedMoby->m_State >= 0x80) {
          props->m_0x08 = -1;
          break;
        }

        if (props->m_0x00 != 0) {
          func_8003851C(moby, 0, 0);
          linkedProps = linkedMoby->m_Props;
          VecCopy(&oldPosition, &linkedMoby->m_Position);
          VecCopy(&linkedMoby->m_Position, &moby->m_Position);
          count = 0;
          step = 0xB4;
          height = linkedMoby->m_Position.z;

          do {
            height += step;
            step -= 0xA;
            count++;
          } while (step > 0 || oldPosition.z < height);

          VecSub(&oldPosition, &oldPosition, &linkedMoby->m_Position);
          func_800177F8(&oldPosition, &oldPosition, count);
          oldPosition.z = 0xB4;
          VecCopy(&linkedProps->m_InitPos, &oldPosition);
          linkedProps->m_SpawnState = 0;
          linkedProps->m_Ticks = 0;
          linkedProps->m_RotX = 3;
          linkedMoby->m_Substate = 2;
          linkedMoby->m_RenderRadius = 0x18;
          linkedMoby->m_UpdateDistance = 0x40;
          props->m_0x0c = linkedMoby;
          props->m_0x08 = -1;
        } else {
          linkedMoby->m_RenderRadius = 0;
          linkedMoby->m_WasDrawn = 0;
          linkedMoby->m_UpdateDistance = 0;
          linkedMoby->m_Substate = 4;
        }

        break;
      }

      if (props->m_0x0c == 0) {
        break;
      }

      if (props->m_0x0c->m_State >= 0x80 || props->m_0x0c->m_Substate != 2) {
        props->m_0x0c = 0;
        break;
      }

      if ((g_GameTick & 1) != 0) {
        VecNull(&particleVelocity);
        g_SpawnParticle(1, 0, &props->m_0x0c->m_Position,
                        (int)&particleVelocity);
      }

      break;
    }
#endif
#if defined(HAS_MOBY_222) || defined(HAS_MOBY_223) || defined(HAS_MOBY_224)
#ifdef HAS_MOBY_222
    case 222: // Stone Hill Trees
#endif
#ifdef HAS_MOBY_223
    case 223:
#endif
#ifdef HAS_MOBY_224
    case 224:
#endif
    {
      Moby222Props *props = moby->m_Props;

      if (!props->m_Initialized) {
        func_80038458(moby);
        moby->m_Rotation.y =
            Atan2(g_CollisionNormal.z, VecMagnitude(&g_CollisionNormal, 0), 0);
        moby->m_Rotation.z =
            Atan2(-g_CollisionNormal.x, -g_CollisionNormal.y, 0);
        props->m_Initialized = 1;
      }

      break;
    }
#endif
#ifdef HAS_MOBY_225
    case 225: {
      Moby225Props *props;
      Moby *linkedMoby;

      props = moby->m_Props;
      linkedMoby = &g_LevelMobys[props->m_0x00];
      func_800529E4(moby, UPDATE_PROP_ROTMATRIX);

      if (props->m_0x0c != 0) {
        props->m_0x0c--;
        if (props->m_0x0c == 0) {
          ((int *)linkedMoby->m_Props)[19] = 0x3C;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
        }
      }

      if (moby->m_AnimationState.m_NextAnimation >= 3 &&
          moby->m_AnimationState.m_NextFrame >= 8 &&
          moby->m_AnimationState.m_NextAnimation != 0) {
        g_AnimationFinished = 0;
        MOBY_ANIM_ADVANCE(moby, 0);
      }

      if (props->m_0x20 == 0) {
        props->m_0x20 = 1;
        props->m_0x14 = moby->m_Rotation.z << 4;
      }

      if (props->m_0x1c != 0) {
        g_Spyro.m_ControlFlags = 0x80001000;
        g_Spyro.m_mobyInUseBySpyro = moby;
      }

      switch (moby->m_State) {
      case 0: {
        int range;
        int angleWindow;
        int angleThreshold;
        int angleA;
        int angleAbs;
        int angleB;

        if (linkedMoby->m_State >= 0x80 ||
            (linkedMoby->m_AnimationState.m_NextAnimation == 3 &&
             linkedMoby->m_AnimationState.m_NextFrame >= 0x15)) {
          range = 0x4E2;
          angleWindow = 0x20;
          angleThreshold = 0x5A;

          if (props->m_0x1c != 0) {
            range = 1400;
            angleWindow = 0x2C;
            angleThreshold = 0x4B;
          }

          if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
            Vector3D vector;

            moby->m_DamageFlags = 0;
            vector.x = -1000;
            vector.y = 0;
            vector.z = 0x172;
            func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
            VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vector,
                              &vector);
            VecAdd(&vector, &vector, &moby->m_Position);

            if (func_80017908(ANGLE_FROM_SPYRO(vector),
                              g_Spyro.m_bodyRotation.z) < 0x30) {
              moby->m_State = 1;
              continue;
            }
          }

          props->m_0x1c = 0;

          if (DISTANCE_TO_SPYRO(moby) < range) {
            angleA =
                func_800381BC(moby->m_Rotation.z, g_Spyro.m_bodyRotation.z);
            angleAbs = ABS2(angleA);

            if (angleAbs > 0x40 - angleWindow &&
                angleAbs < angleWindow + 0x40) {
              angleB = func_800381BC(ANGLE_TO_SPYRO(moby->m_Position),
                                     moby->m_Rotation.z);
              if (ABS2(angleB) > angleThreshold) {
                if ((angleA < 0 && angleB < 0) || (angleA > 0 && angleB > 0)) {
                  props->m_0x1c = 1;
                }
              }
            }
          }
        } else {
          moby->m_DamageFlags = 0;
          props->m_0x14 = moby->m_Rotation.z << 4;
        }
        break;
      }

      case 1:
        props->m_0x18 = 0x3C;
        func_8003851C(moby, 0, &props->m_0x24);
        moby->m_State = 2;
        continue;

      case 2: {
        int i;

        if (props->m_0x18 >= 0xB) {
          Vector3D particlePosition;
          Vector3D particleVelocity;

          moby->m_DamageFlags = 0;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 3, &particlePosition);
          particleVelocity.x = -0x10;
          particleVelocity.y = 0;
          particleVelocity.z = -0xE;
          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix,
                            &particleVelocity, &particleVelocity);

          for (i = 0; i < 5; i++) {
            particleVelocity.x += (rand() & 0xF) - 8;
            particleVelocity.y += (rand() & 0xF) - 8;
            g_SpawnParticle(1, 74, &particlePosition, (int)&particleVelocity);
          }
        }

        if (TICK_TIMER(props->m_0x18)) {
          func_800562A4(moby, 1);
          moby->m_State = 3;
          continue;
        }
        break;
      }

      case 3: {
        Moby237Props *projectileProps;
        Moby *projectile;
        Moby *candidate;
        Moby *candidate2;
        Moby *bestMoby;
        Vector3D delta;
        int bestScore;
        int angle;
        int distance;
        int score;

        projectile = g_SpawnMoby(237, moby);
        projectileProps = projectile->m_Props;
        VecCopy(&projectile->m_Position, &moby->m_Position);
        projectile->m_Rotation.z = moby->m_Rotation.z;
        func_80039398(projectile, 0x546, 0, 0, 0);
        projectile->m_Position.z += 0x47E;
        projectileProps->m_0x08 = -5;
        projectileProps->m_0x00 = 0xF0;
        projectileProps->m_0x10 = -1;
        projectileProps->m_0x04 = 0xF0;
        projectileProps->m_0x0c = 0;
        projectileProps->m_0x0e = 0;
        projectileProps->m_0x14 = 0;
        projectile->m_RenderRadius = 0x34;
        projectile->m_UpdateDistance = 0xFF;
        bestMoby = 0;
        candidate = g_LevelMobys;
        candidate2 = candidate;
        bestScore = 0x7530;
        moby->m_DamageFlags = 0;

        for (; candidate < g_DynMobys; candidate2++, candidate++) {
          if (candidate == moby) {
            continue;
          }
          if (candidate2->m_State >= 0x80) {
            continue;
          }
          if (candidate2->m_Class == 250 || candidate2->m_Class == 110 ||
              candidate2->m_Class == 225) {
            continue;
          }

          if (candidate2->m_CollisionGroup != 0) {
            if ((int)candidate2->m_CollisionGroup >= 0 &&
                candidate2->m_Class != 417) {
              continue;
            }
          } else if (candidate2->m_Class != 417) {
            continue;
          }

          VecSub(&delta, &candidate->m_Position, &moby->m_Position);
          score = ABS2(delta.x) + ABS2(delta.y);

          if (score > 0xBFFF) {
            continue;
          }

          angle = (ANGLE_FROM(moby->m_Position, candidate2->m_Position) -
                   moby->m_Rotation.z) &
                  0xFF;
          if (angle > 0x80) {
            angle -= 0x100;
          }
          angle = ABS2(angle);

          if (angle >= 7) {
            continue;
          }

          score = VecMagnitude(&delta, 0);
          if (score >= 0x6800) {
            continue;
          }

          if (score > 0x4800) {
            score -= 0x4800;
          } else if (score < 0x3800) {
            score = 0x3800 - score;
          } else {
            score = 0;
          }

          score += angle << 12;

          if (candidate2->m_Class == 417) {
            score >>= 2;
          }

          if (score < bestScore) {
            bestMoby = candidate2;
            bestScore = score;
          }
        }

        if (bestMoby != 0) {
          projectile->m_Rotation.z =
              ANGLE_FROM(moby->m_Position, bestMoby->m_Position);
          projectileProps->m_0x08 = -5;
          VecSub(&delta, &bestMoby->m_Position, &projectile->m_Position);
          distance = VecMagnitude(&delta, 0);

          if (distance - delta.z > 0x400) {
            bestScore =
                ((((distance * 5) >> 8) * distance) / (distance - delta.z)) >>
                1;

            if (bestScore >= 0x11 && bestScore <= 0xFFFFF) {
              int root;

              root = func_80017A38(bestScore);
              bestScore = root << 4;
              root <<= 9;
              root += bestScore;
              root <<= 3;
              bestScore = root >> 8;
              projectileProps->m_0x04 = bestScore;
              projectileProps->m_0x00 = bestScore;
              projectileProps->m_0x14 = distance / bestScore - 4;

              if (bestMoby->m_Class == 417) {
                projectileProps->m_0x10 = bestMoby - g_LevelMobys;
              }
            }
          }
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
        moby->m_State = 0;
        continue;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_226
    case 226: {
      Moby226Props *props;

      props = moby->m_Props;
      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 5) {
        props->m_0x08 = 0x190;
        props->m_0x0c = 170;
        props->m_0x14 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        moby->m_DamageFlags = 0;
        moby->m_CollisionRange = 100;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 5;
        MOBY_ANIM_CHANGE(moby, 5);
        continue;
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0:
        if (props->m_0x1c == 1 || props->m_0x1c == 2) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;

      case 4: {
        int distance;
        distance = DISTANCE_TO_SPYRO(moby);

        if (props->m_0x1c == 2) {
          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x00, props->m_0x2c)) <
              (props->m_0x28 << 10)) {
            props->m_0x24 = 1;
            moby->m_State = 20;
            continue;
          }

          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x04, props->m_0x2c)) <
              (props->m_0x28 << 10)) {
            props->m_0x24 = 2;
            moby->m_State = 20;
            continue;
          }
        }

        RotateMobyToSpyro(moby, 4, 0, 0);

        if (TICK_TIMER(props->m_0x18) && distance < 1100 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 700) {
          props->m_0x18 = 0x78;
          moby->m_State = 8;
          MOBY_ANIM_CHANGE(moby, 8);
          continue;
        }
        break;
      }
      case 5: {
        int result;
        result = MoveMobyWithGravity(moby, &props->m_0x08, props->m_0x14,
                                     &props->m_0x0c, 0xC, 0x10);

        if (result == 3 && props->m_0x30 == 0) {
          props->m_0x30 = 1;
          func_8003851C(moby, 0, 0);
        }

        if (result == 2 && props->m_0x0c >= -0x63) {
          props->m_0x0c = -100;
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x10);
          func_80052568(moby);
          continue;
        }
        break;
      }
      case 6:
        RotateMobyToSpyro(moby, 4, 0, 0);

        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;

      case 8:
        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;

      case 10: {
        int angle;
        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));

        RotateMobyToAngle(moby, angle, 4, 0, 0);
        func_80039398(moby, 110, 0, 0, 5);

        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <
            0x80) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;
      }
      case 20: {
        int result;
        int speed;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);

        if (props->m_0x24 == 1) {
          if (!moby->m_WasDrawn) {
            speed = 0x8C;
          } else {
            speed = 100;
          }

          result = func_80039E94(moby, props->m_0x00, 0x80, speed, 0, 4, 0x14,
                                 0xFF, 5);

          if (result != 0 && (DISTANCE_TO_SPYRO(moby) < 1500 ||
                              props->m_0x00->m_CurrentNode == props->m_0x2c)) {
            props->m_0x1c = 1;
            moby->m_State = 4;
            MOBY_ANIM_CHANGE(moby, 4);
            continue;
          }
        } else {
          if (DISTANCE_TO_SPYRO(moby) >= 1500 &&
              func_80039E94(moby, props->m_0x04, 0x80, 0x50, 0, 4, 0x14, 0xFF,
                            5) == 0) {
            break;
          }

          if (props->m_0x04->m_CurrentNode == props->m_0x2c) {
            props->m_0x1c = 1;
            moby->m_State = 4;
            MOBY_ANIM_CHANGE(moby, 4);
            continue;
          }
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_229
    case 229: {
      Moby229Props *props;
      Moby *linkedMoby;
      int angle;
      int state;

      props = (Moby229Props *)moby->m_Props;
      linkedMoby = 0;

      if (props->m_0x18 != -1) {
        linkedMoby = &g_LevelMobys[props->m_0x18];
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 7) {
        props->m_0x04 = 0xF0;
        props->m_0x00 = g_Spyro.m_bodyRotation.z;
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 7;
        MOBY_ANIM_CHANGE(moby, 7);
        continue;
      }

      if (!TICK_TIMER(props->m_0x1c)) {
        g_Spyro.m_ControlFlags = 0x80002047;
      }

      if ((D_80075914 & 0x10) == 0 && !TICK_TIMER(props->m_0x20)) {
        int cameraDistance;

        cameraDistance = DISTANCE_TO_SPYRO(moby) + 0xC00;

        if (props->m_0x24 < cameraDistance) {
          props->m_0x24 = cameraDistance;
        }

        if (props->m_0x1c != 0) {
          g_Spyro.m_ControlFlags |= 0x80000200;
        } else {
          g_Spyro.m_ControlFlags = 0x80000200;
        }

        g_Spyro.unk_0x21c = &moby->m_Position;
        g_Spyro.unk_0x220 = &D_80078668;
        D_80078668.m_Coords.azimuth = (-ANGLE_TO_SPYRO(moby->m_Position)) << 4;
        cameraDistance = props->m_0x24;
        D_80078668.m_Coords.elevation = 0;
        D_80078668.m_Offset.azimuth = 0;
        D_80078668.m_Offset.elevation = 0;
        D_80078668.m_Offset.radius = 0;
        D_80078668.m_Coords.radius = cameraDistance;
      }

      state = moby->m_State;

      switch (state) {
      case 0: {
        int distance;

        distance = DISTANCE_TO_SPYRO(moby);

        if (props->m_0x14 == 0) {
          props->m_0x14 = 1;
          props->m_0x10 = moby->m_Rotation.z;
        }

        if (linkedMoby != 0 && moby->m_Substate == 0 &&
            linkedMoby->m_State == 0 && distance < (props->m_0x28 << 10) &&
            moby->m_Position.z < g_Spyro.m_Position.z &&
            SPYRO_BASE_Z_DISTANCE(moby) < 1500) {
          moby->m_Substate = 1;

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);

          moby->m_State = 10;
          continue;
        }

        if (distance > 0x2000) {
          RotateMobyToAngle(moby, props->m_0x10, 4, 0, 0);

          if (moby->m_AnimationState.m_Animation == 2 &&
              g_AnimFrameFinished != 0 &&
              moby->m_AnimationState.m_Frame == 0xF) {
            props->m_0x0c--;
            if (props->m_0x0c > 0) {
              moby->m_AnimationState.m_Frame = 5;
              moby->m_AnimationState.m_NextFrame = 6;
              moby->m_AnimationState.m_FrameProgress = 0;
            }
          }

          if (g_AnimationFinished) {
            if (props->m_0x0c == 0) {
              props->m_0x0c = RandRange(3, 5);
              if (RandRange(0, 100) > 80) {
                MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
              } else if (moby->m_AnimationState.m_NextAnimation != 4) {
                g_AnimationFinished = 0;
                MOBY_ANIM_ADVANCE(moby, 4);
              }
            } else if (moby->m_AnimationState.m_NextAnimation != 2) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby, 2);
            }
          }
        } else {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          angle = func_80038074(angle, 5);

          if (moby->m_AnimationState.m_NextAnimation == 4) {
            g_AnimationFinished = 0;
            MOBY_ANIM_ADVANCE(moby, 0);
          }

          if (moby->m_AnimationState.m_NextAnimation == 2 &&
              moby->m_AnimationState.m_NextFrame < 0xF) {
            moby->m_AnimationState.m_Frame = 0xF;
            moby->m_AnimationState.m_NextFrame = 0x10;
            moby->m_AnimationState.m_FrameProgress = 0;
          }

          if (moby->m_AnimationState.m_Animation < 2 ||
              moby->m_AnimationState.m_Animation == 5) {
            RotateMobyToAngle(moby, angle, 4, 0, 0);
          }

          if (g_AnimationFinished) {
            if (moby->m_AnimationState.m_NextAnimation == 2) {
              if (moby->m_AnimationState.m_Animation != 0) {
                g_AnimationFinished = 0;
                MOBY_ANIM_RESTART(moby, 0);
              }
            } else {
              props->m_0x0c--;

              if (props->m_0x0c <= 0) {
                props->m_0x0c = RandRange(3, 5);

                if (RandRange(0, 100) > 0x50) {
                  if (moby->m_AnimationState.m_NextAnimation != 1) {
                    g_AnimationFinished = 0;
                    MOBY_ANIM_ADVANCE(moby, 1);
                  } else {
                    g_AnimationFinished = 0;
                    MOBY_ANIM_ADVANCE(moby, 0);
                  }
                }
              } else if (moby->m_AnimationState.m_NextAnimation != 5) {
                g_AnimationFinished = 0;
                MOBY_ANIM_ADVANCE(moby, 5);
              }
            }
          }
        }

        if (distance < 2700 && SPYRO_BASE_Z_DISTANCE(moby) < 1000 &&
            SPYRO_BASE_Z_DELTA(moby) < 0) {
          moby->m_State = 6;
          MOBY_ANIM_CHANGE(moby, 6);
          continue;
        }
        break;
      }

      case 6: {
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        angle = func_80038074(angle, 5);
        RotateMobyToAngle(moby, angle, 6, 0, 0);

        if (g_AnimFrameFinished != 0 && moby->m_AnimationState.m_Frame == 3 &&
            DISTANCE_TO_SPYRO(moby) < 2700) {
          Vector3D delta;

          VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
          VecScaleToLength(&delta, VecMagnitude(&delta, 0), 0x78);
          g_Spyro.m_ControlFlags = 0x80000047;
          g_Spyro.unk_0x208.x = delta.x;
          g_Spyro.unk_0x208.z = 0x28;
          g_Spyro.m_fallingState = state;
          g_Spyro.unk_0x208.y = delta.y;
          props->m_0x1c = 0x28;
          props->m_0x20 = 0x28;
          props->m_0x24 = 4000;

          if (D_80075904 < 0xF) {
            D_80075904 = 0xF;
          }
        }

        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        break;
      }

      case 7:
        if (props->m_0x04 > 0) {
          func_80039688(moby, props->m_0x00, props->m_0x04, 500, 700, 1);
          props->m_0x04 -= 0x10;
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;

      case 10:
        angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);

        if (RotateMobyToAngle(moby, angle, 8, 6, 1) != 0 &&
            moby->m_AnimationState.m_NextAnimation != 8) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 8);
        }

        if (moby->m_AnimationState.m_Animation == 8 &&
            g_AnimFrameFinished != 0 && moby->m_AnimationState.m_Frame == 5) {
          MOBY_ANIM_CHANGE(linkedMoby, 7);

          linkedMoby->m_State = 10;
        }

        if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 8) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);

          moby->m_State = 0;
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_230
    case 230: {
      Moby230Props *props;

      props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 4) {
        Moby *spawned;
        int i;

        props->m_0x04 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x00 = 300;

        if (moby->m_State != 0) {
          *props->m_0x30 = 0;
        }

        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);

        if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE |
                                    MOBY_DAMAGE_SUPER)) != 0) {
          for (i = 0; i < 7 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(288, moby);
            spawned = g_SpawnMoby(289, moby);

            if ((rand() & 1) != 0) {
              spawned->m_State = 1;
              MOBY_ANIM_RESTART(spawned, 1);
            }
          }
        }

        moby->m_State = 4;
        MOBY_ANIM_RESTART(moby, 4);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        Vector3D vec;
        int distance;
        int zDelta;

        distance = DISTANCE_TO_SPYRO(moby);
        zDelta = props->m_0x08.z - moby->m_Position.z;

        if (zDelta != 0) {
          if (zDelta >= -0x63) {
            moby->m_Position.z = props->m_0x08.z;
          } else {
            moby->m_Position.z -= 100;
          }
        }

        if (props->m_0x04 == -1) {
          props->m_0x04 = moby->m_Rotation.z;
        }

        RotateMobyToAngle(moby, props->m_0x04, 4, 0, 0);

        if (*props->m_0x30 == 0 && distance < (props->m_0x14 << 10) &&
            distance > 2000 && SPYRO_BASE_Z_DISTANCE(moby) < 3000) {
          VecCopy(&vec, &moby->m_Position);
          vec.x += COSINE_8(moby->m_Rotation.z) >> 2;
          vec.y += SINE_8(moby->m_Rotation.z) >> 2;

          if (moby->m_WasDrawn &&
              func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) < 0x19 &&
              func_80017908(moby->m_Rotation.z,
                            ANGLE_TO_SPYRO(moby->m_Position)) < 0x30 &&
              func_80038250(&vec) != 0) {
            if (TICK_TIMER(props->m_0x18)) {
              props->m_0x24 = 1;
              props->m_0x20 = 0;
              props->m_0x00 = 0;
              props->m_0x1c = 0;

              if (props->m_0x2c == -1) {
                if ((rand() & 0xFF) >= 0x80) {
                  props->m_0x28 = 1;
                } else {
                  props->m_0x28 = 0;
                }
              } else {
                props->m_0x28 = props->m_0x2c;
              }

              *props->m_0x30 = 1;
              props->m_0x34 = 0;

              if (moby->m_AnimationState.m_Animation != 1) {
                moby->m_AnimationState.m_FrameProgress = 8;
                moby->m_AnimationState.m_PerFrameProgress = 8;
                moby->m_AnimationState.m_Animation =
                    moby->m_AnimationState.m_NextAnimation;
                moby->m_AnimationState.m_NextAnimation = 1;
                moby->m_AnimationState.m_Frame =
                    moby->m_AnimationState.m_NextFrame;
                moby->m_AnimationState.m_NextFrame = 0;
                func_80037E98(moby);
              }

              moby->m_State = 1;
              continue;
            }
          } else {
            props->m_0x18 = 0x28;
          }
        }

        break;
      }

      case 1: {
        Vector3D vec;
        int distance;
        int angle;
        int targetZ;
        int floorA;
        int floorB;
        int turnStep;
        int reverseAngle;
        int zDelta;

        distance = DISTANCE_TO_SPYRO(moby);
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        turnStep = 0xC;

        if (g_AnimationFinished == 0 &&
            moby->m_AnimationState.m_NextAnimation == 1 &&
            moby->m_AnimationState.m_NextFrame < 0xB) {
          break;
        }

        props->m_0x34 += g_DeltaTime;
        moby->m_Position.z += 1500;
        targetZ = func_8004D5EC(&moby->m_Position, 0x1000) + 0x226;
        moby->m_Position.z -= 1500;

        if (props->m_0x2c == 2) {
          targetZ = g_Spyro.m_Position.z + 300;
        }

        if (distance < 4000) {
          turnStep = 0x20;
        } else if (distance < 6000) {
          turnStep = 0x18;
        }

        if (g_AnimationFinished &&
            moby->m_AnimationState.m_NextAnimation != 2) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 2);
        }

        if (props->m_0x00 < 170) {
          props->m_0x00 += 0xA;
        }

        if (distance < 0x4000 && props->m_0x28 != 2) {
          props->m_0x1c = 1;
        }

        if (props->m_0x1c != 0) {
          if (props->m_0x24 == 1) {
            props->m_0x20 += turnStep;

            if ((props->m_0x20 >> 4) >= 0x23) {
              props->m_0x24 = -props->m_0x24;
            }
          } else if (props->m_0x24 == -1) {
            props->m_0x20 -= turnStep;

            if ((props->m_0x20 >> 4) <= 0) {
              props->m_0x24 = 0;
            }
          }
        }

        zDelta = targetZ - moby->m_Position.z;

        if (ABS2(zDelta) >= 0x47) {
          if (zDelta < 0) {
            moby->m_Position.z -= 0x78;
          } else {
            moby->m_Position.z += 0x78;
          }
        } else {
          moby->m_Position.z = targetZ;
        }

        if (distance < 1600 &&
            func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) > ROTDEG8(85)) {
          *props->m_0x30 = 0;
          moby->m_State = 2;
          continue;
        }

        if (func_80017908(g_Spyro.m_bodyRotation.z,
                          ANGLE_FROM_SPYRO(moby->m_Position)) > 0x50 &&
            !moby->m_WasDrawn) {
          *props->m_0x30 = 0;
          moby->m_State = 2;
          continue;
        }

        if (props->m_0x28 != 0) {
          moby->m_Rotation.z = func_80038074(angle, props->m_0x20 >> 4);
        } else {
          moby->m_Rotation.z = func_80038074(angle, -(props->m_0x20 >> 4));
        }

        if (func_80039398(moby, props->m_0x00, 0, 350, 1) != 0) {
          *props->m_0x30 = 0;
          moby->m_State = 2;
          continue;
        }

        if (props->m_0x34 >= 0x3D && distance < 10000 &&
            func_80038250(&moby->m_Position) == 0) {
          *props->m_0x30 = 0;
          moby->m_State = 2;
          continue;
        }

        if (distance < 1400 &&
            func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) < 0x28 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 600) {
          g_Spyro.m_DamageFlags |= 1;
          *props->m_0x30 = 0;
          moby->m_State = 2;
          continue;
        }

        if (OctDistance(&moby->m_Position, &props->m_0x08) >
            (props->m_0x14 << 10) + 0x800) {
          *props->m_0x30 = 0;
          moby->m_State = 2;
          continue;
        }

        VecCopy(&vec, &moby->m_Position);
        vec.x += COSINE_8(moby->m_Rotation.z) >> 3;
        vec.y += SINE_8(moby->m_Rotation.z) >> 3;
        vec.z += 0x400;
        floorA = func_8004D5EC(&vec, 0x800);

        VecCopy(&vec, &moby->m_Position);
        reverseAngle = func_80038074(moby->m_Rotation.z, 0x80);
        vec.x += FIXED_MUL(COSINE_8(reverseAngle), 700);
        reverseAngle = func_80038074(moby->m_Rotation.z, 0x80);
        vec.y += FIXED_MUL(SINE_8(reverseAngle), 700);
        vec.z += 0x400;
        floorB = func_8004D5EC(&vec, 0x800);

        if (ABS2(floorA - floorB) < 0x200) {
          moby->m_Rotation.y = Atan2(1400, floorA - floorB, 0);
          moby->m_Rotation.y = func_80038098(moby->m_Rotation.y, 0, 0x20);
        }

        break;
      }

      case 2: {
        int angle;
        int distance;
        int zDelta;

        angle = ANGLE_FROM(moby->m_Position, props->m_0x08);
        distance = OctDistance(&moby->m_Position, &props->m_0x08);
        zDelta = props->m_0x08.z - moby->m_Position.z + 0x200;

        if (distance > 0x1800) {
          zDelta = g_Spyro.m_Position.z - moby->m_Position.z + 0x800;
        }

        if (ABS2(zDelta) >= 0x3D) {
          if (zDelta < 0) {
            moby->m_Position.z -= 100;
          } else {
            moby->m_Position.z += 100;
          }
        }

        if (g_AnimationFinished &&
            moby->m_AnimationState.m_NextAnimation != 2) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 2);
        }

        if (props->m_0x2c == 2) {
          RotateMobyToAngle(moby, angle, 7, 0, 0);
        } else {
          RotateMobyToAngle(moby, angle, 2, 0, 0);
        }

        func_80039398(moby, props->m_0x00, 0, 0, 0);

        if (distance < 3000 && props->m_0x00 >= 0x33) {
          props->m_0x00 -= 5;
        }

        if (distance < 0x80) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        break;
      }

      case 4: {
        Vector3D vec;
        int floorZ;

        if (props->m_0x00 > 0) {
          func_80039688(moby, props->m_0x04, props->m_0x00, 0, 0, 0);
          props->m_0x00 -= 0x10;
        }

        VecCopy(&vec, &moby->m_Position);
        vec.z += 1000;
        floorZ = func_8004D5EC(&vec, 0x800);

        if (floorZ < moby->m_Position.z) {
          moby->m_Position.z -= 0x32;
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }

        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_CHAIN | UPDATE_PROP_COLLISION);
      func_8004D5EC(&moby->m_Position, 0x10000);
      func_800533D0(moby);
      break;
    }
#endif
#ifdef HAS_MOBY_231 // Armored Ice Gnorc
    case 231: {
      Moby231Props *props = moby->m_Props;

      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 6) {
        props->m_KnockbackAngle = g_Spyro.m_bodyRotation.z;
        props->m_FallKnockbackSpeed = 0x80;
        // Set as knockback speed for use in Knockback state 5
        props->m_Scratch = 0x80;
        moby->m_DamageFlags = 0;
        props->m_ChargeCount++;
        // Failsafe: Kill Gnorc if he's been charged 4 times
        if (props->m_ChargeCount == 4) {
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 6;
          MOBY_ANIM_CHANGE(moby, 6);
        } else {
          if (moby->m_AnimationState.m_Animation == 5) {
            moby->m_AnimationState.m_Frame = 0;
            moby->m_AnimationState.m_NextFrame = 1;
            moby->m_AnimationState.m_FrameProgress = 0;
          }
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
        }
        break;
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0: { // Idle
        if (g_AnimationFinished) {
          if (moby->m_AnimationState.m_Animation == 8) {
            // Play Flexing Anim 2
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 9);
          } else if (props->m_IdleAnimCounter == 0) {
            // Set up counter for 2-4 Idle "looking around" anims
            props->m_IdleAnimCounter = RandRange(2, 4);
            // Play Flexing Anim 1
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
          } else {
            // Play Idle "looking around" anims until counter is 0
            props->m_IdleAnimCounter--;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          }
        }

        // Keep rotating Moby to face Spyro
        RotateMobyToSpyro(moby, 3, 0x10, 0);

        // Take note of Spyro: prepare to attack
        if (DISTANCE_TO_SPYRO(moby) < 0x1C00 &&
            SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
          // Value is overwritten when Gnorc takes damage
          props->m_FallKnockbackSpeed = 0x48;
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;
      }

      case 1: { // Entering attack stance
        if (g_AnimationFinished) {
          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
          continue;
        }
        break;
      }

      case 2: { // Attack stance
        int distance = DISTANCE_TO_SPYRO(moby);
        RotateMobyToSpyro(moby, 3, 0, 0);

        // Spyro is close enough to hit
        if (distance < 4000 && SPYRO_ORIGIN_Z_DISTANCE(moby) < 1500) {
          // Value is overwritten when Gnorc takes damage
          props->m_FallKnockbackSpeed = 0x48;
          props->m_Scratch = 0;

          // Enter attacking state
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        // Spyro is out of range again
        if (distance > 0x2000) {
          // Enter idle state
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 3: { // attacking
        RotateMobyToSpyro(moby, 6, 0, 0);
        // If Spyro has been flattened
        if (g_Spyro.m_State == 25) {
          // Scratch serves as laugh anim counter here
          props->m_Scratch = 3;
        }
        if (g_AnimationFinished) {
          // If Spyro was hit, enter laughing state, otherwise idle
          if (props->m_Scratch) {
            moby->m_State = 7;
            MOBY_ANIM_RESTART(moby, 7);
          } else {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
          }
          continue;
        }
        break;
      }

      case 4: { // Nothing seems to enter this state
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 5: { // Knockback
        int floorHeight;

        // Scratch is knockback speed here, set after Moby took damage
        if (props->m_Scratch != 0) {
          // Only start decelerating knockback past a certain point of the
          // anim
          if (moby->m_AnimationState.m_NextFrame >= 4) {
            MoveMobyWithGravity(moby, &props->m_Scratch,
                                props->m_KnockbackAngle, 0, 8, 0);
          } else {
            MoveMobyWithGravity(moby, &props->m_Scratch,
                                props->m_KnockbackAngle, 0, 0, 0);
          }
        }
        moby->m_Position.z += 0x200;
        floorHeight = func_8004D5EC(&moby->m_Position, 0x1000);
        func_800533D0(moby);
        // Proceed to dying state if the floor is low enough
        if (moby->m_Position.z - floorHeight > 0x800) {
          func_8003ABC0(moby, 2, 0, &props->m_DropTarget);
          func_8003B7C0(moby);
          moby->m_Position.z -= 0x200;
          props->m_Scratch = 0;
          moby->m_State = 6;
          MOBY_ANIM_CHANGE(moby, 6);
          continue;
        }
        // Otherwise return to idle state
        moby->m_Position.z = floorHeight + 0x10;
        if (g_AnimationFinished) {
          moby->m_DamageFlags = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 6: { // Dying
        int floorHeight;

        // Wrap up Moby death after anim is done
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        // Apply horizontal movement along knockback angle during fall
        if (props->m_FallKnockbackSpeed) {
          moby->m_Position.x += FIXED_MUL(props->m_FallKnockbackSpeed,
                                          Cos(props->m_KnockbackAngle << 4));
          moby->m_Position.y += FIXED_MUL(props->m_FallKnockbackSpeed,
                                          Sin(props->m_KnockbackAngle << 4));
        }
        moby->m_Position.z += 0x200;
        floorHeight = func_8004D5EC(&moby->m_Position, 0x1000);
        func_800533D0(moby);
        if (moby->m_Position.z - floorHeight < 0x200) {
          // Moby is not falling off a ledge
          moby->m_Position.z = floorHeight;
          props->m_Scratch = 0;
        } else {
          moby->m_Position.z -= 0x200;
          // Accelerate gravity until 240 if the Moby is falling off a ledge
          props->m_Scratch += 12;
          if (props->m_Scratch > 240) {
            props->m_Scratch = 240;
          }
          moby->m_Position.z -= props->m_Scratch;
        }
        break;
      }

      case 7: { // Laughing
        if (g_AnimationFinished) {
          // Scratch serves as laugh anim counter here
          if (TICK_TIMER(props->m_Scratch)) {
            // Return to idle
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_CHAIN | UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_232
    case 232: {
      Moby232Props *props = moby->m_Props;

      moby->m_Rotation.z += 8;
      if (MoveMobyWithGravity(moby, &props->m_0x08, props->m_0x00,
                              &props->m_0x04, 0xC, 0xC) == 3 ||
          TICK_TIMER(props->m_0x0c)) {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_234 // Barrier Effect
    case 234: {
      if (g_AnimationFinished) {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_236
    case 236: {
      Moby236Props *props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 1) {
        props->m_0x24 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        if (moby->m_DamageFlags & MOBY_DAMAGE_FLAME) {
          props->m_0x20 = 200;
        } else {
          props->m_0x20 = 400;
        }
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 1;
        MOBY_ANIM_CHANGE(moby, 1);
        continue;
      }

      switch (moby->m_State) {
      case 0:
        func_80039AA8(moby, &props->m_Wander);
        if (TICK_TIMER(props->m_0x2c)) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      case 1:
        if (props->m_0x20 >= 16) {
          props->m_0x20 -= 15;
          func_80039688(moby, props->m_0x24, props->m_0x20, 0, 500, 5);
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x10);
          func_80052568(moby);
          continue;
        }
        break;
      case 2:
        if (g_AnimationFinished) {
          props->m_0x2c = RandRange(90, 300);
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_237
    case 237: {
      Moby237Props *props = moby->m_Props;
      moby->m_Rotation.y = func_80038074(moby->m_Rotation.y, 3);

      switch (moby->m_State) {
      case 0: {
        Vector3D zeroVelocity;

        moby->m_Position.x +=
            FIXED_MUL(props->m_0x00, COSINE_8(moby->m_Rotation.z));
        moby->m_Position.y +=
            FIXED_MUL(props->m_0x00, SINE_8(moby->m_Rotation.z));

        if (props->m_0x0e != 0) {
          if (props->m_0x0c == 0) {
            func_80052568(moby);
            continue;
          }
          props->m_0x0c--;
        } else {
          props->m_0x0c += g_DeltaTime;

          if (props->m_0x0c > 360) {
            func_80052568(moby);
            continue;
          }

          if (props->m_0x14 != 0) {
            props->m_0x14--;
          }

          if (func_8004BE4C(&moby->m_Position, 0x168, 0x168) != 0) {
            func_8003851C(moby, 0, 0);
            moby->m_State = 1;
            if (props->m_0x10 != -1) {
              g_LevelMobys[props->m_0x10].m_Substate = 1;
            }
          }

          if (props->m_0x0c >= 9 && props->m_0x14 == 0 &&
              func_8004E3C8(&moby->m_Position, 0x400, 0, 0x80000, moby, 2) !=
                  0) {
            func_8003851C(moby, 0, 0);
            moby->m_State = 1;
            if (props->m_0x10 != -1) {
              g_LevelMobys[props->m_0x10].m_Substate = 1;
            }
          }
        }

        moby->m_Position.z += props->m_0x04;
        props->m_0x04 += props->m_0x08;
        zeroVelocity.x = 0;
        zeroVelocity.y = 0;
        zeroVelocity.z = 0;
        g_SpawnParticle(1, 1, &moby->m_Position, (int)&zeroVelocity);
        break;
      }

      case 1: {
        Vector3D particleVelocity;
        Vector3D particlePosition;
        int i;

        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(458, moby);
          g_SpawnMoby(459, moby);
        }

        for (i = 0; i < 8; i++) {
          particleVelocity.x = (rand() & 0x3E) - 0x1F;
          particleVelocity.y = (rand() & 0x3E) - 0x1F;
          particleVelocity.z = rand() & 0xF;
          VecCopy(&particlePosition, &particleVelocity);
          VecShiftLeft(&particlePosition, 2);
          VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
          g_SpawnParticle(1, 13, &particlePosition, (int)&particleVelocity);
        }

        g_SpawnParticle(10, 70, &moby->m_Position, 0x10);
        func_8004E3C8(&moby->m_Position, 0x800, 0, 0x80000, moby, 2);
        func_80052568(moby);
        continue;
      }
      }

      func_800529E4(moby, UPDATE_PROP_CHAIN);
      break;
    }
#endif
#ifdef HAS_MOBY_238
    case 238: {
      Moby238Props *props;

      props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 5 && moby->m_State != 6) {
        props->m_0x24 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);

        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) == 0) {
          props->m_0x20 = 0x190;
        } else {
          props->m_0x20 = 0;
        }

        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);

        if (props->m_0x20 != 0) {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
        } else {
          moby->m_State = 6;
          MOBY_ANIM_RESTART(moby, 6);
        }

        continue;
      }

      switch (moby->m_State) {
      case 0:
        func_80039AA8(moby, &props->m_Wander);
        break;

      case 5:
        if (props->m_0x20 >= 0x10) {
          props->m_0x20 -= 0xF;
          func_80039688(moby, props->m_0x24, props->m_0x20, 0, 700, 5);
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x10);
          func_80052568(moby);
          continue;
        }

      case 6:
        if (moby->m_AnimationState.m_Animation == 6 &&
            moby->m_AnimationState.m_Frame < 8) {
          func_80039AA8(moby, &props->m_Wander);
        }

        if (g_AnimationFinished) {
          if (moby->m_AnimationState.m_Animation == 6) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 7);
          } else {
            func_80052568(moby);
            continue;
          }
        }

        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_250
    case MOBYCLASS_CRYSTAL_DRAGON: {
      RescuedDragonMobyProps *dragonProps = moby->m_Props;

      if (moby->m_State == 0) {
        if (dragonProps->m_DragonPadLink != -1) {
          g_LevelMobys[dragonProps->m_DragonPadLink].m_State = 3;
        }
        moby->m_State = 1;
        dragonProps->m_AngleStorage.x = moby->m_Rotation.x;
        dragonProps->m_AngleStorage.y = moby->m_Rotation.y;
        dragonProps->m_AngleStorage.z = moby->m_Position.z;
      } else if (moby->m_State == 1) {
        dragonProps->m_ShakeTimer += g_DeltaTime;
        if (dragonProps->m_ShakeTimer > 256) {
          dragonProps->m_ShakeTimer = 0;
          moby->m_Rotation.x = dragonProps->m_AngleStorage.x;
          moby->m_Rotation.y = dragonProps->m_AngleStorage.y;
          moby->m_Position.z = dragonProps->m_AngleStorage.z;
          moby->m_DamageFlags = 0;
          func_800562A4(moby, 1);
        } else if (dragonProps->m_ShakeTimer >= 192) {

          if (!IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[0])) {
            func_8003851C(moby, 0, 0);
          }
          moby->m_Rotation.x =
              g_MobyShakeOffsets[(dragonProps->m_ShakeTimer - 192) >> 1][0] +
              dragonProps->m_AngleStorage.x;
          moby->m_Rotation.y =
              g_MobyShakeOffsets[(dragonProps->m_ShakeTimer - 192) >> 1][1] +
              dragonProps->m_AngleStorage.y;
          moby->m_Position.z =
              dragonProps->m_AngleStorage.z +
              (ABS2(g_MobyShakeOffsets[(dragonProps->m_ShakeTimer - 192) >> 1]
                                      [0]) +
               ABS2(g_MobyShakeOffsets[(dragonProps->m_ShakeTimer - 192) >> 1]
                                      [1])) *
                  6;
        } else if (dragonProps->m_ShakeTimer >= 188) {
          dragonProps->m_AngleStorage.x = moby->m_Rotation.x;
          dragonProps->m_AngleStorage.y = moby->m_Rotation.y;
          dragonProps->m_AngleStorage.z = moby->m_Position.z;
        } else if (moby->m_DamageFlags != 0) {
          dragonProps->m_ShakeTimer = 188;
          func_800562A4(moby, 1);
        } else {
          if ((dragonProps->m_ShakeTimer >> 1) == 16 && (rand() & 3) == 0) {
            SpawnMobySparkle(moby, &D_8006E57C[0]);
          } else if ((dragonProps->m_ShakeTimer >> 1) == 48 &&
                     (rand() & 3) == 0) {
            SpawnMobySparkle(moby, &D_8006E57C[1]);
          } else if ((dragonProps->m_ShakeTimer >> 1) == 80 &&
                     (rand() & 3) == 0) {
            SpawnMobySparkle(moby, &D_8006E57C[2]);
          }
        }

        if (DISTANCE_TO_SPYRO(moby) < 2048) {
          Vector3D dragonPickupDelta;

          VecSub(&dragonPickupDelta, &moby->m_Position, &g_Spyro.m_Position);
          dragonPickupDelta.z = (dragonPickupDelta.z * 3) >> 2;
          if (VecMagnitude(&dragonPickupDelta, 1) < 1088) {
            int rotZ;
            int cutsceneId;

            if (dragonProps->m_DragonPadLink != -1) {
              rotZ = g_LevelMobys[dragonProps->m_DragonPadLink].m_Rotation.z;
            } else {
              rotZ = dragonProps->m_Rotation;
            }

            func_8003B854(0, moby);
            CheckpointSave(moby, rotZ);

            if (dragonProps->m_OldDialogueId != -1) {
              g_LevelDragonCount[g_LevelIndex]++;
              g_DragonTotal++;
              func_8002C914(dragonProps->m_OldDialogueId, 0);
              if (dragonProps->m_DragonPadLink != -1) {
                g_LevelMobys[dragonProps->m_DragonPadLink].m_State = 1;
              }
              func_80052568(moby);
            } else {
              cutsceneId = dragonProps->m_CutsceneId;
              if (cutsceneId == -1) {
                // No cutscene, used in prototypes on the later levels
                g_LevelDragonCount[g_LevelIndex]++;
                g_DragonTotal++;

                if (dragonProps->m_DragonPadLink != -1) {
                  g_LevelMobys[dragonProps->m_DragonPadLink].m_State = 1;
                }

                func_80052568(moby);
              } else {
                moby->m_State = 2;
                moby->m_Rotation.x = dragonProps->m_AngleStorage.x;
                moby->m_Rotation.y = dragonProps->m_AngleStorage.y;
                moby->m_Position.z = dragonProps->m_AngleStorage.z;
                func_8002C924(moby);
                VecNull(&g_Spyro.m_HeadLookTarget);
                g_Spyro.m_ControlFlags =
                    0x80000000 | 0x2000 | 0x100 | 0x40 | 0x4 | 0x2 | 0x1;
                if (g_Spyro.m_airTime != 0) {
                  g_Spyro.m_fallingState = 6;
                  g_Spyro.unk_0x208.x = g_Spyro.m_Physics.m_TrueVelocity.x >> 8;
                  g_Spyro.unk_0x208.y = g_Spyro.m_Physics.m_TrueVelocity.y >> 8;
                  if (g_Spyro.m_Physics.m_TrueVelocity.z > 0) {
                    g_Spyro.unk_0x208.z = 0;
                  } else {
                    g_Spyro.unk_0x208.z =
                        g_Spyro.m_Physics.m_TrueVelocity.z >> 6;
                  }
                } else {
                  g_Spyro.m_fallingState = 3;
                  VecCopy(&g_Spyro.unk_0x208,
                          &g_Spyro.m_Physics.m_TrueVelocity);
                  VecShiftRight(&g_Spyro.unk_0x208, 6);
                  g_Spyro.unk_0x208.z = 0;
                  if (g_Spyro.unk_0x208.x != 0 || g_Spyro.unk_0x208.y != 0) {
                    VecScaleToLength(&g_Spyro.unk_0x208,
                                     VecMagnitude(&g_Spyro.unk_0x208, 0), 0x60);
                  }
                  g_Spyro.unk_0x208.z = 0;
                }
              }
            }
          }
        }
      } else {
        g_Spyro.m_ControlFlags = 0x80000000 | 0x2000;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_251
    case MOBYCLASS_CRYSTAL_DRAGON_FRAGMENT: { // Dragon fragment
      UpdateMobyDragonFragment(moby);
      break;
    }
#endif
#ifdef HAS_MOBY_253
    case 253: { // Large Beast (Alpine Ridge)
      Moby253Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 3) {
        moby->m_DamageFlags = 0;
        props->m_0x18 = 150;
        props->m_0x1c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        StopSound(moby->m_SoundChannel, 4);
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        continue;
      }

      if (!TICK_TIMER(props->m_0x24)) {
        g_Spyro.m_ControlFlags = 0x80000047;
      }

      switch (moby->m_State) {
      case 0:
        switch (props->m_0x10) {
        case 0: {
          Moby *linkedMoby = &g_LevelMobys[props->m_0x20];

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          if (props->m_0x14 == -1) {
            props->m_0x14 = moby->m_Rotation.z;
          }
          if (linkedMoby->m_State == 3 || linkedMoby->m_State >= 0x80 ||
              DISTANCE_TO_SPYRO(moby) <= 0x1400) {
            moby->m_State = 6;
            continue;
          }
          if (RotateMobyToAngle(moby, props->m_0x14, 6, 0xA, 1) != 0) {
            if (props->m_0x34 == 0 && moby->m_AnimationState.m_Animation == 0) {
              props->m_0x34 = 1;
              moby->m_AnimationState.m_Frame = 0x15;
              moby->m_AnimationState.m_NextFrame = 0x16;
              moby->m_AnimationState.m_FrameProgress = 0;
            }
            if (props->m_0x20 != -1) {
              linkedMoby->m_State = 0;
            }
          }
          break;
        }

        case 1:
          if (DISTANCE_TO_SPYRO(moby) < (props->m_0x38 << 10)) {
            if (moby->m_Pod != 0xFF) {
              props->m_0x30 = RandRange(0xF, 0x1E);
              func_8003B1E8(moby, 0x15);
              break;
            }
            moby->m_State = 21;
            continue;
          }
          break;

        case 2:
          func_80038458(moby);
          if (props->m_0x28 != 0) {
            if (RotateMobyToSpyro(moby, 4, 0x14, 1) != 0 &&
                moby->m_AnimationState.m_NextAnimation != 2) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby, 2);
            }
            if (TICK_TIMER(props->m_0x30) && DISTANCE_TO_SPYRO(moby) < 0x2800 &&
                g_Spyro.m_airTime == 0 &&
                g_Spyro.m_Position.z - PATH_NODE_POS(props->m_0x0c, 0).z > 0) {
              moby->m_State = 11;
              continue;
            }
          } else if (props->m_0x34 == 0 &&
                     moby->m_AnimationState.m_Animation == 0) {
            props->m_0x34 = 1;
            moby->m_AnimationState.m_Frame = 0x15;
            moby->m_AnimationState.m_NextFrame = 0x16;
            moby->m_AnimationState.m_FrameProgress = 0;
          }
          break;

        case 3:
          moby->m_State = 6;
          continue;

        case 4: {
          Moby *linkedMoby = &g_LevelMobys[props->m_0x20];

          if (linkedMoby->m_AnimationState.m_NextAnimation == 3) {
            moby->m_Substate = 1;
          }
          if (moby->m_AnimationState.m_Animation == 0 && props->m_0x34 == 0) {
            props->m_0x34 = 1;
            moby->m_AnimationState.m_Frame = 0x14;
            moby->m_AnimationState.m_NextFrame = 0x15;
            moby->m_AnimationState.m_FrameProgress = 0;
          }
          if (DISTANCE_TO_SPYRO(moby) < 0x1800 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 800) {
            if (moby->m_AnimationState.m_Animation != 0xB) {
              moby->m_State = 6;
              continue;
            }
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 12);
            moby->m_State = 20;
            continue;
          }

          switch (moby->m_Substate) {
          case 0:
            break;

          case 1:
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);
            if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x0c)) <
                0x100) {
              int node;

              do {
                node = RandRange(0, 3);
              } while (node == props->m_0x0c->m_CurrentNode);
              props->m_0x0c->m_CurrentNode = node;
            }
            if (RotateMobyToAngle(
                    moby,
                    ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x0c)),
                    8, 0x28, 1) != 0) {
              func_80039398(moby, 0x78, 0, 0, 5);
            }
            break;
          }
          break;
        }

        case 5:
          func_80038458(moby);
          RotateMobyToSpyro(moby, 6, 0, 0);
          if (moby->m_Substate != 0) {
            props->m_0x10 = 2;
            props->m_0x28 = 1;
            moby->m_DepthOffset = 4;
          }
          break;
        }
        break;

      case 1:
        switch (props->m_0x10) {
        case 0:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);
          if (RotateMobyToSpyro(moby, 8, 0xA, 1) != 0) {
            if (func_80039398(moby, 150, 0, 500, 0x15) != 0 ||
                OctDistance(&moby->m_Position, &props->m_0x00) > 0x2800) {
              moby->m_State = 100;
              continue;
            }
            if (DISTANCE_TO_SPYRO(moby) < 2000 &&
                SPYRO_BASE_Z_DISTANCE(moby) < 800) {
              moby->m_State = 7;
              continue;
            }
          }
          break;

        case 1:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);
          if (TICK_TIMER(props->m_0x30) &&
              (DISTANCE_TO_SPYRO(moby) < 0xC00 ||
               func_80039E94(moby, props->m_0x0c, 0x100, 0x5A, 0, 4, 0x40, 0xFF,
                             5) == 0x100)) {
            moby->m_State = 6;
            continue;
          }
          break;
        }
        break;

      case 2:
        if (TICK_TIMER(props->m_0x30)) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 9);
          if (moby->m_AnimationState.m_NextFrame >= 7) {
            moby->m_State = 1;
            continue;
          }
        }
        break;

      case 3:
        if (props->m_0x18 != 0) {
          func_80039688(moby, props->m_0x1c, props->m_0x18, 0, 700, 5);
          props->m_0x18 -= 0xE;
          if (props->m_0x18 < 0) {
            props->m_0x18 = 0;
          }
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x46);
          func_80052568(moby);
          continue;
        }
        break;

      case 6: {
        int distance = DISTANCE_TO_SPYRO(moby);

        RotateMobyToSpyro(moby, 4, 0, 0);
        switch (props->m_0x28) {
        case 0:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);
          if (distance < 0x1800) {
            props->m_0x28 = 1;
          }
          break;

        case 1:
          if (moby->m_AnimationState.m_NextAnimation != 6) {
            g_AnimationFinished = 0;
            moby->m_AnimationState.m_FrameProgress = 8;
            moby->m_AnimationState.m_PerFrameProgress = 8;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation = 6;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 0;
            func_80037E98(moby);
          }
          if (ABS2(moby->m_AnimationState.m_NextFrame -
                   moby->m_AnimationState.m_Frame) < 3) {
            moby->m_AnimationState.m_PerFrameProgress =
                g_Models[moby->m_Class]
                    ->m_Animations[moby->m_AnimationState.m_Animation]
                    ->m_ProgressPerTick;
          }
          if (moby->m_AnimationState.m_Animation == 6 &&
              g_AnimFrameFinished != 0 &&
              moby->m_AnimationState.m_Frame >= 0xA) {
            props->m_0x3c = RandRange(150, 350);
            props->m_0x28 = 2;
          }
          break;

        case 2:
          if (TICK_TIMER(props->m_0x30) && distance < 0x1000 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 900) {
            StopSound(moby->m_SoundChannel, 4);
            props->m_0x28 = 3;
          }
          if (TICK_TIMER(props->m_0x3c) &&
              moby->m_AnimationState.m_Frame >= 0x19) {
            props->m_0x28 = 5;
          }
          if (distance > 0x1C00) {
            props->m_0x28 = 4;
          }
          if (g_AnimFrameFinished != 0 &&
              moby->m_AnimationState.m_Frame >= 0x1A) {
            g_AnimationFinished = 0;
            moby->m_AnimationState.m_FrameProgress = 0x10;
            moby->m_AnimationState.m_PerFrameProgress = 0x10;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation = 6;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 9;
            func_80037E98(moby);
          }
          if (ABS2(moby->m_AnimationState.m_NextFrame -
                   moby->m_AnimationState.m_Frame) < 3) {
            moby->m_AnimationState.m_PerFrameProgress =
                g_Models[moby->m_Class]
                    ->m_Animations[moby->m_AnimationState.m_Animation]
                    ->m_ProgressPerTick;
          }
          break;

        case 3:
          if (g_AnimationFinished) {
            props->m_0x28 = 2;
            props->m_0x30 = 0xB4;
          }
          if (moby->m_AnimationState.m_NextFrame < 0x1A) {
            g_AnimationFinished = 0;
            moby->m_AnimationState.m_FrameProgress = 0x10;
            moby->m_AnimationState.m_PerFrameProgress = 0x10;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation = 6;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 0x1A;
            func_80037E98(moby);
          }
          if (ABS2(moby->m_AnimationState.m_NextFrame -
                   moby->m_AnimationState.m_Frame) < 3) {
            moby->m_AnimationState.m_PerFrameProgress =
                g_Models[moby->m_Class]
                    ->m_Animations[moby->m_AnimationState.m_Animation]
                    ->m_ProgressPerTick;
          }
          if (g_AnimFrameFinished != 0 &&
              moby->m_AnimationState.m_NextFrame > 36 &&
              moby->m_AnimationState.m_NextFrame < 41 &&
              DISTANCE_TO_SPYRO(moby) < 3800 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 900) {
            g_Spyro.m_DamageFlags |= 0x13;
          }
          break;

        case 4:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
          if (g_AnimFrameFinished != 0 &&
              moby->m_AnimationState.m_NextFrame >= 8) {
            props->m_0x28 = 0;
          }
          break;

        case 5:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);
          if (g_AnimFrameFinished != 0 &&
              moby->m_AnimationState.m_NextFrame >= 8) {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);
            props->m_0x28 = 6;
            props->m_0x3c = RandRange(0x3C, 0x78);
          }
          break;

        case 6:
          if (TICK_TIMER(props->m_0x30) && distance < 0x1000 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 900) {
            StopSound(moby->m_SoundChannel, 4);
            props->m_0x28 = 3;
          }
          if (TICK_TIMER(props->m_0x3c) && g_AnimationFinished) {
            props->m_0x28 = 1;
          }
          break;
        }
        break;
      }

      case 7:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 10);
        if (props->m_0x24 == 0 && moby->m_AnimationState.m_NextFrame >= 6) {
          Vector3D delta;

          g_Spyro.m_DamageFlags |= 5;
          VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
          VecScaleToLength(&delta, VecMagnitude(&delta, 0), 0x8C);
          g_Spyro.m_ControlFlags = 0x80000047;
          g_Spyro.unk_0x208.x = delta.x;
          g_Spyro.unk_0x208.y = delta.y;
          g_Spyro.unk_0x208.z = 0x19;
          g_Spyro.m_fallingState = 6;
          props->m_0x24 = 0x28;
        }
        if (g_AnimationFinished) {
          moby->m_State = 100;
          continue;
        }
        break;

      case 10:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);
        VecCopy(&props->m_0x00, &PATH_NODE_POS(props->m_0x0c, 0));
        RotateMobyToSpyro(moby, 4, 0, 0);
        props->m_0x28 = 1;
        break;

      case 11:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (DISTANCE_TO_SPYRO(moby) < 2000) {
          moby->m_State = 7;
          continue;
        }
        if (func_80039398(moby, 110, 0, 0, 0x15) != 0) {
          props->m_0x30 = 0xF0;
          moby->m_State = 100;
          continue;
        }
        if (OctDistance(&moby->m_Position, &props->m_0x00) > 0x2000) {
          moby->m_State = 100;
          continue;
        }
        break;

      case 20:
        if (g_AnimationFinished) {
          moby->m_State = 6;
          continue;
        }
        break;

      case 21:
        if (TICK_TIMER(props->m_0x30)) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 12);
          moby->m_State = 22;
          continue;
        }
        break;

      case 22:
        if (g_AnimFrameFinished != 0 &&
            moby->m_AnimationState.m_NextFrame >= 0xE) {
          moby->m_State = 1;
          continue;
        }
        break;

      case 100: {
        int angle = ANGLE_FROM(moby->m_Position, props->m_0x00);

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);
        if (RotateMobyToAngle(moby, angle, 6, 0x14, 1) != 0) {
          func_80039398(moby, 110, 0, 0, 5);
          if (OctDistance(&moby->m_Position, &props->m_0x00) < 0x80) {
            moby->m_State = 0;
            continue;
          }
        }
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
    case MOBYCLASS_NUMBER_0:
    case MOBYCLASS_NUMBER_1:
    case MOBYCLASS_NUMBER_2:
    case MOBYCLASS_NUMBER_3:
    case MOBYCLASS_NUMBER_4:
    case MOBYCLASS_NUMBER_5:
    case MOBYCLASS_NUMBER_6:
    case MOBYCLASS_NUMBER_7:
    case MOBYCLASS_NUMBER_8:
    case MOBYCLASS_NUMBER_9: // Digits
    {

      MobyNumberProps *digitProps = moby->m_Props;

      if (!(moby->m_RenderRadius & 0x80) && (moby->m_RenderRadius != 0)) {
        if (digitProps->m_Lifetime > 0) {

          moby->m_Rotation.z += 1;

          digitProps->m_Velocity.z -= 6;
          if (digitProps->m_Velocity.z < -0x80) {
            digitProps->m_Velocity.z = -0x80;
          }

          moby->m_Position.x += digitProps->m_Velocity.x;
          moby->m_Position.y += digitProps->m_Velocity.y;
          moby->m_Position.z += digitProps->m_Velocity.z;

          if (moby->m_Position.z > 1023) {
            if (func_8004BE4C(&moby->m_Position, 0x100, 0x100)) {
              int dot;
              moby->m_Position.x = g_CollisionPoint.x;
              moby->m_Position.y = g_CollisionPoint.y;
              moby->m_Position.z = g_CollisionPoint.z;

              func_80017330(&g_CollisionNormal, 0x1000);

              dot = (digitProps->m_Velocity.x * g_CollisionNormal.x +
                     digitProps->m_Velocity.y * g_CollisionNormal.y +
                     digitProps->m_Velocity.z * g_CollisionNormal.z) >>
                    11;

              if (dot < 0) {
                VecScaleToLength(&g_CollisionNormal, 0x1000, -dot);
                digitProps->m_Velocity.x += g_CollisionNormal.x;
                digitProps->m_Velocity.y += g_CollisionNormal.y;
                digitProps->m_Velocity.z += g_CollisionNormal.z;
              }
            }
            digitProps->m_Lifetime--;
            // Using continue here and deduplicating func_80052568 causes match
            // to break in Ice Cavern
          } else {
            func_80052568(moby);
          }
        } else {
          g_SpawnParticle(10, 71, &moby->m_Position, 0);
          func_80052568(moby);
        }
      }
      break;
    }
#ifdef HAS_MOBY_270
    case 270: {

      Moby270Props *props = (Moby270Props *)moby->m_Props;
      if (props->m_0x50 == 0) {
        int mobyIndex;
        int index;
        int bit;
        int destroyed = 0;
        int linkedDestroyed;

        props->m_0x50 = 1;

        mobyIndex = moby - g_LevelMobys;
        index = mobyIndex >> 5;
        bit = mobyIndex & 0x1F;
        if ((g_Checkpoint.m_KilledMobysSaved[index] & (1 << bit)) &&
            moby->m_DropMoby == 0xFF) {
          destroyed = 1;
        }

        if (props->m_0x10 == 2) {
          linkedDestroyed = 0;
          mobyIndex = &g_LevelMobys[props->m_0x0c] - g_LevelMobys;
          index = mobyIndex >> 5;
          bit = mobyIndex & 0x1F;
          if ((g_Checkpoint.m_KilledMobysSaved[index] & (1 << bit)) &&
              (g_LevelMobys[props->m_0x0c].m_State >= 0x80 ||
               g_LevelMobys[props->m_0x0c].m_DropMoby == 0xFF)) {
            linkedDestroyed = 1;
          }
        }

        if (props->m_0x10 == 2 && linkedDestroyed == 0) {
          continue;
        }

        if (destroyed) {
          if (props->m_0x10 == 2 && linkedDestroyed) {
            if (g_LevelMobys[props->m_0x0c].m_State < 0x80) {
              func_80052568(&g_LevelMobys[props->m_0x0c]);
            }
            func_8002B390(props->m_0x04, 0xFC, 0);
          }
          StopSound(moby->m_SoundChannel, 4);
          func_80052568(moby);
          continue;
        }
      }

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 3) {
        props->m_0x38 = 0xFA;
        props->m_0x3c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        StopSound(moby->m_SoundChannel, 4);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        continue;
      }
      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 3) {
        props->m_0x38 = 0xFA;
        props->m_0x3c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        StopSound(moby->m_SoundChannel, 4);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        continue;
      }
      switch (moby->m_State) {
      case 0: {
        int distance;
        int envAnimState;
        // Can be read uninitialized in condition below
        int envAnimState2;

        distance = DISTANCE_TO_SPYRO(moby);

        if (props->m_0x08 >= 0) {
          if (!(props->m_0x10 == 2 && moby->m_Substate != 0) && (rand() & 1)) {
            g_SpawnParticle(1, 8, moby, (int)&g_LevelMobys[props->m_0x08]);
          }
        }

        if (props->m_0x04 != -1) {
          envAnimState = func_8002B3F4(props->m_0x04);
          envAnimState2 = (envAnimState >> 8) & 0xFF;
        }

        if (distance < (props->m_0x2c << 10) &&
            (props->m_0x30 || envAnimState2 >= 2) && g_Spyro.m_State != 0xB &&
            g_Spyro.m_State != 0x14 &&
            func_80017908(g_Spyro.m_bodyRotation.z,
                          ANGLE_FROM_SPYRO(moby->m_Position)) < 0x20) {
          g_Spyro.m_ControlFlags = 0x80000200;
          g_Spyro.unk_0x21c = &g_Spyro.m_Position;
          g_Spyro.unk_0x220 = &D_80078668;
          D_80078668.m_Coords.azimuth =
              ROTDEG12(180) - (g_Spyro.m_bodyRotation.z << 4);
          D_80078668.m_Coords.radius = 0xC00;
          D_80078668.m_Coords.elevation = 0x80;
          D_80078668.m_Offset.elevation = -0xB0;
          D_80078668.m_Offset.azimuth = 0;
          D_80078668.m_Offset.radius = 0;
        }

        if (props->m_0x04 != -1) {
          if (props->m_0x04 == 0 && props->m_0x14 < 3 && (envAnimState & 2) &&
              g_LevelId == 31) {
            PlaySound(g_Spu.m_SoundTable->beastSound2,
                      &g_LevelMobys[props->m_0x08], 8,
                      &g_LevelMobys[props->m_0x08].m_SoundChannel);
          }

          if (props->m_0x10 == 0) {
            int range = props->m_0x28 << 10;

            if (g_Spyro.m_State != 0xB || props->m_0x20 == 0) {
              range += 0xC00;
            }

            func_80038458(moby);
            RotateMobyToSpyro(moby, 6, 0, 0);

            if (envAnimState2 < 2) {
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);

              if (distance < range) {
                if (props->m_0x14 != 0) {
                  if (TICK_TIMER(props->m_0x14) == 2 && (envAnimState & 2)) {
                    func_8002B390(props->m_0x04, 0xFC, 0);
                  }
                } else {
                  props->m_0x14 = props->m_0x18;
                }
              } else {
                TICK_TIMER(props->m_0x14);
              }
            } else {
              RotateMobyToSpyro(moby, 4, 0, 0);
              if (TICK_TIMER(props->m_0x54)) {
                props->m_0x54 = (rand() & 0x2F) + 0x3C;
                func_8003851C(moby, (rand() & 1) | 4, 0);
              }
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
              if (distance > range + 0x800 && (envAnimState & 2)) {
                func_8002B390(props->m_0x04, 0xFC, 0);
                props->m_0x14 = 0x1E;
              }
            }
          } else if (props->m_0x10 == 1) {
            if (props->m_0x08 > 0) {
              int angle = ANGLE_FROM(moby->m_Position,
                                     g_LevelMobys[props->m_0x08].m_Position);
              RotateMobyToAngle(moby, angle, 6, 0, 0);
            }

            func_80038458(moby);

            if (TICK_TIMER(props->m_0x4c)) {
              if (!((g_Spyro.m_State == 0x2C || g_Spyro.m_State == 0x18 ||
                     (g_Spyro.m_State == 0x14 &&
                      (g_Spyro.m_walkingState & 0x40))) &&
                    g_LevelId == 30 && envAnimState2 < 2)) {
                if (distance > (props->m_0x34 << 10) &&
                    TICK_TIMER(props->m_0x14)) {
                  func_8002B390(props->m_0x04, 0xFC, 0);
                  if (envAnimState2 >= 2) {
                    props->m_0x14 = props->m_0x18;
                  } else {
                    props->m_0x14 = props->m_0x1c;
                  }
                } else if (distance < (props->m_0x34 << 10)) {
                  if (moby->m_Pod == 0xFF) {
                    moby->m_State = 90;
                    continue;
                  }
                  func_8003B47C(moby, 0x5A, 3);
                }
              }
            }
          } else if (props->m_0x10 == 2) {
            if (moby->m_Substate == 0 &&
                (DISTANCE_TO_SPYRO(moby) < 0x3400 ||
                 g_LevelMobys[props->m_0x0c].m_State >= 0x80)) {
              func_8002B390(props->m_0x04, 0xFC, 0);
              moby->m_Substate = 1;
              props->m_0x14 = 0x46;
            } else if (TICK_TIMER(props->m_0x14) == 2) {
              g_LevelMobys[props->m_0x0c].m_Substate = 1;
            }

            if (g_LevelMobys[props->m_0x0c].m_AnimationState.m_NextAnimation ==
                    3 ||
                g_LevelMobys[props->m_0x0c].m_State >= 0x80) {
              if (DISTANCE_TO_SPYRO(moby) < (props->m_0x34 << 10) + 2000) {
                moby->m_State = 90;
                continue;
              }
            }
          } else if (props->m_0x10 == 3) {
            Moby *linkedMoby = &g_LevelMobys[props->m_0x0c];
            int *linkedProps = (int *)linkedMoby->m_Props;

            func_80038458(moby);
            RotateMobyToAngle(
                moby, ANGLE_FROM(moby->m_Position, linkedMoby->m_Position), 6,
                0, 0);

            if (envAnimState2 < 3) {
              if (TICK_TIMER(props->m_0x14)) {
                if (((PathData *)linkedProps[3])->m_CurrentNode == 7) {
                  props->m_0x14 = 300;
                  func_8002B390(9, 0xFC, 0);
                  linkedProps[0] = 8;
                  linkedProps[8] = 2;
                }
              }

              if ((*(u_int *)&linkedMoby->m_AnimationState & 0xFF0000FF) ==
                  0x04000004) {
                if ((rand() & 0xFF) >= 0xD3) {
                  func_8002B390(props->m_0x04, 0xFC, 0);
                  props->m_0x14 = 0x5A;
                }
              }

              if ((*(u_int *)&linkedMoby->m_AnimationState & 0xFF0000FF) ==
                      0x08000004 &&
                  linkedMoby->m_AnimationState.m_FrameProgress < 0x11) {
                MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 9);
              }

              if ((*(u_int *)&moby->m_AnimationState & 0xFF00FF00) ==
                      0x14000900 &&
                  g_AnimFrameFinished) {
                MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
              }
            } else {
              if (TICK_TIMER(props->m_0x14)) {
                func_8002B390(props->m_0x04, 0xFC, 0);
              }
            }
          }
        }
        break;
      }

      case 3: {
        if (props->m_0x38 != 0) {
          func_80039688(moby, props->m_0x3c, props->m_0x38, 0, 700, 5);
          props->m_0x38 -= 0x14;
          if (props->m_0x38 < 0) {
            props->m_0x38 = 0;
          }
        }

        if (g_AnimationFinished) {
          moby->m_RenderRadius = 0;
        }

        if (props->m_0x04 == -1 || props->m_0x40) {
          props->m_0x40 = 1;
        } else {
          int envAnimState;
          envAnimState = func_8002B3F4(props->m_0x04);
          if (envAnimState & 2) {
            if (((envAnimState >> 8) & 0xFF) >= 2) {
              func_8002B390(props->m_0x04, 0xFC, 0);
            } else {
              props->m_0x40 = 1;
            }
          }
        }

        if (moby->m_RenderRadius == 0 && props->m_0x40) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          StopSound(moby->m_SoundChannel, 4);
          func_80052568(moby);
          continue;
        }

        break;
      }

      case 90: {
        StopSound(moby->m_SoundChannel, 4);
        props->m_0x54 = 0;
        func_80038458(moby);

        if (props->m_0x44) {
          int envAnimState;
          envAnimState = func_8002B3F4(props->m_0x04);
          if ((envAnimState & 2) && ((envAnimState >> 8) & 0xFF) >= 2) {
            func_8002B390(props->m_0x04, 0xFC, 0);
          }
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);

        if (g_AnimationFinished) {
          props->m_0x38 = 0x5F;
          props->m_0x14 = RandRange(0xF0, 0x168);
          moby->m_State = 91;
          continue;
        }

        break;
      }

      case 91: {
        if (TICK_TIMER(props->m_0x54)) {
          props->m_0x54 = (rand() & 0x2F) + 0x5A;
          func_8003851C(moby, rand() % 4, 0);
        }

        func_80038458(moby);

        if (props->m_0x44) {
          int envAnimState;
          envAnimState = func_8002B3F4(props->m_0x04);
          if ((envAnimState & 2) && ((envAnimState >> 8) & 0xFF) >= 2) {
            func_8002B390(props->m_0x04, 0xFC, 0);
          }
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);

        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <
            150) {
          int newNode;
          do {
            newNode = RandRange(0, props->m_0x00->m_NodeCount - 1);
          } while (newNode == props->m_0x00->m_CurrentNode);
          props->m_0x00->m_CurrentNode = newNode;
          props->m_0x38 = RandRange(0x3C, 110);
        }

        if (RotateMobyToAngle(
                moby, ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00)),
                7, 0x50, 1)) {
          func_80039398(moby, props->m_0x38, 0, 0, 1);
        }

        if (DISTANCE_TO_SPYRO(moby) > (props->m_0x34 << 10) + 5000) {
          if (props->m_0x10 != 2 ||
              g_LevelMobys[props->m_0x0c].m_AnimationState.m_NextAnimation !=
                  3) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        }

        if (TICK_TIMER(props->m_0x14)) {
          props->m_0x54 = 0x1E;
          props->m_0x48 = DISTANCE_TO_SPYRO(moby);
          if (moby->m_AnimationState.m_Animation != 4) {
            moby->m_AnimationState.m_FrameProgress = 8;
            moby->m_AnimationState.m_PerFrameProgress = 8;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation = 4;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 0;
            func_80037E98(moby);
          }
          moby->m_State = 92;
          continue;
        }

        break;
      }

      case 92: {
        if (TICK_TIMER(props->m_0x54)) {
          props->m_0x54 = (rand() & 0x2F) + 0x3C;
          func_8003851C(moby, (rand() & 1) | 4, 0);
        }

        RotateMobyToSpyro(moby, 6, 0, 0);
        if (DISTANCE_TO_SPYRO(moby) < props->m_0x48 - 0x80) {
          moby->m_State = 90;
          continue;
        }

        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_271
    case 271: { // Armored Druid

      Moby271Props *props = (Moby271Props *)moby->m_Props;
      int closeRange = 1200;

      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 3) {
        Moby *spawned;
        MobyCollectableProps *spawnedProps;

        props->m_0x18 = 450;
        props->m_0x1c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x20 = 0x8C;
        moby->m_DamageFlags = 0;
        spawned = (Moby *)func_8003ABC0(moby, 3, 0, 0);
        spawnedProps = spawned->m_Props;
        spawnedProps->m_SpawnState = 1;
        func_8003B7C0(moby);
        func_8003851C(moby, 0, 0);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        break;
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0:
        switch (props->m_0x14) {
        case 0: {
          int heightDelta = SPYRO_BASE_Z_DELTA(moby);

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          RotateMobyToSpyro(moby, 6, 0, 0);
          if (TICK_TIMER(props->m_0x2c) && DISTANCE_TO_SPYRO(moby) < 2200 &&
              heightDelta > -2000 && heightDelta < 0) {
            moby->m_State = 4;
            MOBY_ANIM_CHANGE(moby, 4);
            continue;
          }
          break;
        }

        case 1:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          if (DISTANCE_TO_SPYRO(moby) < 0x3800) {
            props->m_0x38 = 0;
            *props->m_0x3c = 0;
            func_8003B47C(moby, 2, 3);
          }
          break;

        case 2:
          if (moby->m_AnimationState.m_NextAnimation != 6) {
            g_AnimationFinished = 0;
            MOBY_ANIM_ADVANCE(moby, 6);
            moby->m_AnimationState.m_NextFrame = RandRange(0, 0xF);
          }
          if (props->m_0x10 == -1) {
            props->m_0x10 = moby->m_Rotation.z;
          }
          RotateMobyToAngle(moby, props->m_0x10, 4, 0, 0);
          if (DISTANCE_TO_SPYRO(moby) < 0x1C00) {
            func_8003B47C(moby, 2, 3);
          }
          break;

        case 3: {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          RotateMobyToSpyro(moby, 6, 0, 0);
          func_80038458(moby);
          if (TICK_TIMER(props->m_0x2c) &&
              DISTANCE_TO_SPYRO(moby) < closeRange &&
              SPYRO_BASE_Z_DISTANCE(moby) < 800) {
            moby->m_State = 4;
            MOBY_ANIM_CHANGE(moby, 4);
            continue;
          }
          break;
        }

        case 4: {
          if (props->m_0x10 == -1) {
            props->m_0x10 = moby->m_Rotation.z;
          }
          RotateMobyToAngle(moby, props->m_0x10, 4, 0, 0);
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
          if (DISTANCE_TO_SPYRO(moby) < 0x3000) {
            Moby *linkedMoby;
            Moby271Props *linkedProps;

            linkedMoby = &g_LevelMobys[props->m_0x24];
            linkedMoby->m_State = 2;
            linkedProps = (Moby271Props *)linkedMoby->m_Props;
            linkedProps->m_0x30 = 0x14;
            linkedProps->m_0x34 = 0;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 13);
            moby->m_State = 6;
            continue;
          }
          if (g_AnimFrameFinished &&
              moby->m_AnimationState.m_NextFrame == 0xE) {
            Moby *spawned = g_SpawnMoby(315, moby);
            Moby315Props *spawnedProps = spawned->m_Props;

            func_80052D64(moby, 0, &spawned->m_Position);
            spawned->m_Rotation.z = moby->m_Rotation.z;
            spawnedProps->m_Thrower = moby;
            spawnedProps->m_IsThrown = 1;
            spawnedProps->m_ThrowAngle = moby->m_Rotation.z;
            spawnedProps->m_Lifetime = 20;
            spawnedProps->m_ZVelocity = 80;
          }
          break;
        }

        case 5: {
          if (moby->m_Substate != 0) {
            RotateMobyToSpyro(moby, 4, 0, 0);
            if (DISTANCE_TO_SPYRO(moby) < 0x1C00) {
              if (moby->m_AnimationState.m_NextAnimation == 4) {
                g_AnimationFinished = 0;
                moby->m_AnimationState.m_FrameProgress = 0x10;
                moby->m_AnimationState.m_PerFrameProgress = 0x10;
                moby->m_AnimationState.m_NextAnimation = 1;
                moby->m_AnimationState.m_NextFrame = 0;
                func_80037E98(moby);
              }
              moby->m_State = 2;
              continue;
            }
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);
          } else {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
            if (DISTANCE_TO_SPYRO(moby) < (props->m_0x48 << 10) &&
                g_Spyro.m_airTime == 0 &&
                g_Spyro.m_Position.z - PATH_NODE_POS(props->m_0x00, 0).z > 0) {
              Moby *linkedMoby = &g_LevelMobys[props->m_0x24];
              linkedMoby->m_State = 10;
              props->m_0x30 = 0xD2;
              moby->m_State = 16;
              MOBY_ANIM_CHANGE(moby, 16);
              continue;
            }
          }

          if (g_AnimFrameFinished &&
              moby->m_AnimationState.m_NextFrame == 0xE) {
            Moby *spawned = g_SpawnMoby(315, moby);
            Moby315Props *spawnedProps = spawned->m_Props;

            func_80052D64(moby, 0, &spawned->m_Position);
            spawned->m_Rotation.z = moby->m_Rotation.z;
            spawnedProps->m_Thrower = moby;
            spawnedProps->m_IsThrown = 1;
            spawnedProps->m_ThrowAngle = moby->m_Rotation.z;
            spawnedProps->m_Lifetime = 30;
            spawnedProps->m_ZVelocity = 80;
          }
          break;
        }

        case 6: {
          Moby *linkedMoby = &g_LevelMobys[props->m_0x24];

          if (TICK_TIMER(props->m_0x44) && DISTANCE_TO_SPYRO(moby) < 0x1000) {
            int angleA = ANGLE_FROM_SPYRO(moby->m_Position);
            int angleB = ANGLE_FROM_SPYRO(linkedMoby->m_Position);
            Moby271Props *linkedProps = (Moby271Props *)linkedMoby->m_Props;

            if (func_800381BC(angleA, angleB) < 0) {
              props->m_0x34 = 2;
              linkedProps->m_0x34 = 1;
            } else {
              props->m_0x34 = 1;
              linkedProps->m_0x34 = 2;
            }
            func_8003B47C(moby, 0xB, 3);
          }

          if (props->m_0x40 == 0) {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            func_80039E94(moby, props->m_0x00, 0x100, 0x48, 200, 3, 8,
                          moby->m_Pod, 5);
            if (TICK_TIMER(props->m_0x2c)) {
              if (linkedMoby->m_State < 0x80 &&
                  OctDistance(&moby->m_Position, &linkedMoby->m_Position) <
                      0x8FC) {
                props->m_0x2c = 0x5A;
                props->m_0x40 = 1;
              }
            }
          } else if (props->m_0x40 == 1) {
            int angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
            if (RotateMobyToAngle(moby, angle, 4, 0xA, 1)) {
              props->m_0x40 = 2;
            }
          } else if (props->m_0x40 == 2) {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 14);
            if (g_AnimationFinished) {
              props->m_0x40 = 0;
            }
          }
          break;
        }

        case 7: {
          if (TICK_TIMER(props->m_0x44)) {
            if (SPYRO_BASE_Z_DISTANCE(moby) < 800 &&
                DISTANCE_TO_SPYRO(moby) < 0x1C00) {
              moby->m_State = 2;
              continue;
            }
          }
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          func_80039E94(moby, props->m_0x00, 0x100, 0x78, 200, 6, 0x28, 0xFF,
                        5);
          break;
        }

        case 9: {
          RotateMobyToSpyro(moby, 4, 0, 0);
          if (g_Spyro.m_airTime == 0) {
            if (SPYRO_BASE_Z_DISTANCE(moby) < 800 &&
                DISTANCE_TO_SPYRO(moby) < 0x2000) {
              moby->m_State = 2;
              continue;
            }
          }
          break;
        }

        case 10: {
          Moby *linkedMoby = &g_LevelMobys[props->m_0x24];
          Moby *secondLinkedMoby = &g_LevelMobys[props->m_0x28];

          if (linkedMoby->m_AnimationState.m_NextAnimation == 3 ||
              secondLinkedMoby->m_AnimationState.m_NextAnimation == 3) {
            props->m_0x14 = 9;
            moby->m_State = 7;
            MOBY_ANIM_CHANGE(moby, 7);
            continue;
          }

          switch (moby->m_Substate) {
          case 0: {
            int angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);

            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
            RotateMobyToAngle(moby, angle, 4, 0, 0);
            if (DISTANCE_TO_SPYRO(moby) < 0x1800) {
              moby->m_Substate = 1;
            }

            if (g_AnimFrameFinished &&
                moby->m_AnimationState.m_NextFrame == 0xE) {
              Moby *spawned = g_SpawnMoby(315, moby);
              Moby315Props *spawnedProps = spawned->m_Props;

              func_80052D64(moby, 0, &spawned->m_Position);
              spawned->m_Rotation.z = moby->m_Rotation.z;
              spawnedProps->m_Thrower = moby;
              spawnedProps->m_IsThrown = 1;
              spawnedProps->m_ThrowAngle = moby->m_Rotation.z;
              spawnedProps->m_Lifetime = 30;
              spawnedProps->m_ZVelocity = 80;
            }
            break;
          }

          case 1: {
            int distance = DISTANCE_TO_SPYRO(moby);

            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
            RotateMobyToSpyro(moby, 4, 0, 0);
            if (distance > 0x2000) {
              moby->m_Substate = 0;
            }
            if (TICK_TIMER(props->m_0x2c) &&
                DISTANCE_TO_SPYRO(moby) < closeRange &&
                SPYRO_BASE_Z_DISTANCE(moby) < 800) {
              moby->m_State = 4;
              MOBY_ANIM_CHANGE(moby, 4);
              continue;
            }
            break;
          }
          }
          break;
        }
        }
        break;

      case 2: {
        int nodeIndex;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

        switch (props->m_0x14) {
        case 1:
          if (props->m_0x38 == 0) {
            if (func_80039E94(moby, props->m_0x00, 0x100, 0x8C, 0, 0x10, 0x80,
                              0xFF, 5) == 0x100) {
              props->m_0x38 = 1;
              *props->m_0x3c = 1;
              props->m_0x14 = 0;
              moby->m_State = 0;
              MOBY_ANIM_CHANGE(moby, 0);
              continue;
            }
          }
          break;

        case 2:
        case 6:
        case 7: {
          Vector3D targetPosition;
          int angle;
          int side = props->m_0x34;

          if (side != 0 &&
              func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) >= 0x41) {
            side = 3 - side;
          }

          VecCopy(&targetPosition, &g_Spyro.m_Position);
          if (side == 1) {
            targetPosition.x +=
                COSINE_8(func_80038074(g_Spyro.m_bodyRotation.z, -0x40)) >> 3;
            targetPosition.y +=
                SINE_8(func_80038074(g_Spyro.m_bodyRotation.z, -0x40)) >> 3;
          } else if (side == 2) {
            targetPosition.x +=
                COSINE_8(func_80038074(g_Spyro.m_bodyRotation.z, 0x40)) >> 3;
            targetPosition.y +=
                SINE_8(func_80038074(g_Spyro.m_bodyRotation.z, 0x40)) >> 3;
          }

          angle = ANGLE_FROM(moby->m_Position, targetPosition);
          if (TICK_TIMER(props->m_0x2c)) {
            if (RotateMobyToAngle(moby, angle, 6, 0x14, 1) &&
                func_80017908(g_Spyro.m_bodyRotation.z,
                              ANGLE_FROM_SPYRO(moby->m_Position)) < 0x32 &&
                func_80039398(moby, 0x32, 300, 500, 0x17)) {
              moby->m_State = 100;
              continue;
            }
          }

          if (props->m_0x14 == 2 &&
              func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) >= 0x41) {
            moby->m_State = 100;
            continue;
          }
          if (props->m_0x14 == 2) {
            if (OctDistance(&moby->m_Position, &props->m_0x04) > 0x1800) {
              moby->m_State = 100;
              continue;
            }
          }
          if (props->m_0x14 == 6 || props->m_0x14 == 7) {
            if (func_80038A40(moby, props->m_0x00, &nodeIndex) > 0x1000) {
              if (props->m_0x14 == 7) {
                props->m_0x00->m_CurrentNode = nodeIndex;
                VecCopy(&props->m_0x04,
                        &PATH_NODE_POS(props->m_0x00, nodeIndex));
              }
              moby->m_State = 100;
              continue;
            }
          }

          if (TICK_TIMER(props->m_0x2c) &&
              func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) < 0x32 &&
              DISTANCE_TO_SPYRO(moby) < closeRange && g_Spyro.m_airTime == 0) {
            if (SPYRO_BASE_Z_DELTA(moby) < 200 &&
                SPYRO_BASE_Z_DISTANCE(moby) < 1000) {
              moby->m_State = 4;
              MOBY_ANIM_CHANGE(moby, 4);
              continue;
            }
          }
          break;
        }

        case 5:
          if (RotateMobyToSpyro(moby, 6, 0x14, 1)) {
            if (!TICK_TIMER(props->m_0x2c)) {
              break;
            }
            if (func_80017908(g_Spyro.m_bodyRotation.z,
                              ANGLE_FROM_SPYRO(moby->m_Position)) < 0x32 &&
                func_80039398(moby, 0x32, 0, 500, 0x37)) {
              moby->m_State = 100;
              continue;
            }
          }
          if (OctDistance(&moby->m_Position, &props->m_0x04) > 0x2000) {
            moby->m_State = 100;
            continue;
          }
          if (TICK_TIMER(props->m_0x2c) &&
              func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) < 0x32 &&
              DISTANCE_TO_SPYRO(moby) < closeRange) {
            if (SPYRO_BASE_Z_DELTA(moby) < 200 &&
                SPYRO_BASE_Z_DISTANCE(moby) < 1000) {
              moby->m_State = 4;
              MOBY_ANIM_CHANGE(moby, 4);
              continue;
            }
          }
          break;

        case 9:
          if (RotateMobyToSpyro(moby, 6, 0x14, 1) &&
              func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) < 0x32 &&
              func_80039398(moby, 0x32, 300, 500, 0x15)) {
            moby->m_State = 100;
            continue;
          }
          if (OctDistance(&moby->m_Position, &props->m_0x04) > 0x1800) {
            moby->m_State = 100;
            continue;
          }
          if (TICK_TIMER(props->m_0x2c) &&
              func_80017908(g_Spyro.m_bodyRotation.z,
                            ANGLE_FROM_SPYRO(moby->m_Position)) < 0x32 &&
              DISTANCE_TO_SPYRO(moby) < closeRange) {
            if (SPYRO_BASE_Z_DELTA(moby) < 200) {
              moby->m_State = 4;
              MOBY_ANIM_CHANGE(moby, 4);
              continue;
            }
          }
          break;
        }
        break;
      }

      case 3:
        MoveMobyWithGravity(moby, &props->m_0x18, props->m_0x1c, &props->m_0x20,
                            0x12, 0xC);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 4:
        RotateMobyToSpyro(moby, 6, 0, 0);
        func_80038458(moby);
        if (moby->m_AnimationState.m_NextFrame >= 0x1C) {
          if (props->m_0x14 == 2) {
            moby->m_State = 100;
          } else {
            props->m_0x2c = 0xA0;
            moby->m_State = 0;
          }
          continue;
        }
        g_Spyro.unk_0x208.x = FIXED_MUL(SINE_8(moby->m_Rotation.z), 0x80);
        g_Spyro.unk_0x208.y = FIXED_MUL(COSINE_8(moby->m_Rotation.z), -0x80);
        g_Spyro.unk_0x208.z = 0;
        break;

      case 6: {
        Moby *linkedMoby = &g_LevelMobys[props->m_0x24];

        if (g_AnimationFinished &&
            moby->m_AnimationState.m_NextAnimation != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 0);
        }
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (DISTANCE_TO_SPYRO(moby) < 0xC00 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 600) {
          props->m_0x14 = 0;
          moby->m_State = 0;
          continue;
        }
        if (linkedMoby->m_AnimationState.m_Animation == 3) {
          moby->m_State = 7;
          MOBY_ANIM_CHANGE(moby, 7);
          continue;
        }
        break;
      }

      case 7:
        if (g_AnimationFinished) {
          props->m_0x14 = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 10:
        if (RotateMobyToSpyro(moby, 8, 0x23, 1)) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);
          if (g_AnimationFinished) {
            props->m_0x44 = 0xB4;
            moby->m_State = 2;
            continue;
          }
        }
        break;

      case 11:
        props->m_0x44 = 0xB4;
        moby->m_State = 2;
        continue;

      case 16: {
        Vector3D linkedPosition;
        Moby *linkedMoby = &g_LevelMobys[props->m_0x24];
        int distance;
        Moby271Props *linkedProps = (Moby271Props *)linkedMoby->m_Props;

        linkedProps->m_0x2c = 0xE;
        func_800529E4(linkedMoby, 4);
        func_80052D64(linkedMoby, 0, &linkedPosition);

        if (props->m_0x30 < -300) {
          props->m_0x30 = -300;
        }

        if (linkedMoby->m_State == 3) {
          props->m_0x30 = 200;
          props->m_0x18 = 0x190;
          props->m_0x1c = ANGLE_FROM_SPYRO(moby->m_Position);
          moby->m_State = 18;
          continue;
        }

        if (props->m_0x30 < 0 &&
            MOBY_BASE_Z_DELTA(moby, linkedPosition.z) <= ABS2(props->m_0x30)) {
          linkedMoby->m_State = 11;
          moby->m_State = 17;
          continue;
        }

        moby->m_Position.z += props->m_0x30;
        props->m_0x30 -= 0x14;
        distance = OctDistance(&moby->m_Position, &linkedPosition);

        if (distance >= 0xC9) {
          func_80039688(moby, ANGLE_FROM(moby->m_Position, linkedPosition), 200,
                        0, 0, 0);
        } else {
          RotateMobyToAngle(moby, linkedMoby->m_Rotation.z, 6, 0, 0);
          moby->m_Position.x = linkedMoby->m_Position.x;
          moby->m_Position.y = linkedMoby->m_Position.y;
        }

        if (distance < 1500) {
          RotateMobyToAngle(moby, linkedMoby->m_Rotation.z, 4, 0, 0);
        }
        break;
      }

      case 17: {
        Moby *linkedMoby = &g_LevelMobys[props->m_0x24];
        Moby271Props *linkedProps = (Moby271Props *)linkedMoby->m_Props;

        linkedProps->m_0x2c = 0xA;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 12);

        if (linkedMoby->m_AnimationState.m_NextAnimation == 3) {
          props->m_0x30 = 200;
          props->m_0x18 = 0x190;
          props->m_0x1c = ANGLE_FROM_SPYRO(moby->m_Position);
          moby->m_State = 18;
          continue;
        }

        func_800529E4(linkedMoby, 4);
        func_80052D64(linkedMoby, 0, &moby->m_Position);
        RotateMobyToAngle(moby, linkedMoby->m_Rotation.z, 6, 0, 0);
        break;
      }

      case 18: {
        int floorHeight = func_80038340(moby);
        int nextHeight = moby->m_Position.z + props->m_0x30;

        if (floorHeight + moby->m_FloorDistance < nextHeight) {
          moby->m_Position.z = nextHeight;
          props->m_0x30 -= 0x14;
          if (props->m_0x30 < -200) {
            props->m_0x30 = -200;
          }
        } else {
          moby->m_Position.z = floorHeight + moby->m_FloorDistance;
        }

        if (props->m_0x18 != 0) {
          func_80039688(moby, props->m_0x1c, props->m_0x18, 0, 700, 1);
          props->m_0x18 -= 0x14;
          if (props->m_0x18 < 0) {
            props->m_0x18 = 0;
          }
          if (props->m_0x18 != 0) {
            break;
          }
        }

        if (moby->m_Position.z == floorHeight + moby->m_FloorDistance) {
          VecCopy(&props->m_0x04, &PATH_NODE_POS(props->m_0x00, 0));
          props->m_0x2c = 0x14;
          moby->m_Substate = 1;
          moby->m_State = 2;
          continue;
        }
        break;
      }

      case 100: {
        int angle = ANGLE_FROM(moby->m_Position, props->m_0x04);

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (RotateMobyToAngle(moby, angle, 4, 0x14, 1)) {
          func_80039398(moby, 0x5A, 0, 0, 5);
          if (OctDistance(&moby->m_Position, &props->m_0x04) < 0x80) {
            moby->m_Substate = 1;
            props->m_0x2c = 0x3C;
            props->m_0x30 = 0;
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        }
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_283
    case 283: {
      Moby283Props *props = moby->m_Props;

      if (moby->m_State != 2) {
        g_SpawnParticle(1, 65, moby, 0);

        if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE |
                                    MOBY_DAMAGE_SUPER)) != 0) {
          props->m_0x20 = 0xDC;
          props->m_0x24 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x60);
          if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
            props->m_0x20 += 0x8C;
          }
          StopSound(moby->m_SoundChannel, 4);
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
      }

      switch (moby->m_State) {
      case 0: {
        int angle;

        if ((props->m_0x04 & 2) != 0) {
          props->m_0x00->m_CurrentNode = props->m_0x14;
          if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <=
              0x100) {
            RotateMobyToSpyro(moby, 8, 0x10, 1);
            if (DISTANCE_TO_SPYRO(moby) < 0x1000 &&
                SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
              props->m_0x10 = 0;
              moby->m_State = 1;
              MOBY_ANIM_CHANGE(moby, 1);
              continue;
            }
            if (TICK_TIMER(props->m_0x10)) {
              props->m_0x04 &= 1;
            }
            break;
          }
        } else {
          if (DISTANCE_TO_SPYRO(moby) < 0x1000 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
            RotateMobyToSpyro(moby, 8, 0x10, 1);
            if (props->m_0x10 != 0) {
              props->m_0x10--;
              if (props->m_0x10 > 0) {
                break;
              }
            }
            props->m_0x04 |= 2;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }

          if (props->m_0x04 == 1) {
            int *linkedProps = g_LevelMobys[props->m_0x18].m_Props;

            props->m_0x00->m_CurrentNode = 0;
            if (props->m_0x08 == 0) {
              props->m_0x08 =
                  OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00));
            }
            if (props->m_0x08 < linkedProps[2]) {
              props->m_0x08 = linkedProps[2];
            }

            if (linkedProps[7] != 0) {
              props->m_0x1c = (linkedProps[7] + 0x80) & 0xFF;
              func_80038638(moby, &PATH_NODE_POS(props->m_0x00, 0),
                            props->m_0x08, props->m_0x1c, 8, 0x40, 0xE, 0x80,
                            0xFF, 0xFF, 0x180, 0x15C, 0x27);
              props->m_0x1c = 0;
              linkedProps[7] = 0;
            } else {
              props->m_0x1c =
                  (ANGLE_FROM(PATH_CUR_POS(props->m_0x00), moby->m_Position) +
                   props->m_0x0c) &
                  0xFF;
              func_80038638(moby, &PATH_NODE_POS(props->m_0x00, 0),
                            props->m_0x08, props->m_0x1c, 8, 0x40, 0xE, 0x80,
                            0xFF, 0xFF, 0, 0, 4);
            }
            break;
          }

          props->m_0x00->m_CurrentNode = 0;
          if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <=
              0x100) {
            break;
          }
        }

        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00));
        RotateMobyToAngle(moby, angle, 8, 0x10, 1);
        func_80039398(moby, 0x60, 0x180, 0x180, 0x27);
        break;
      }

      case 1:
        RotateMobyToSpyro(moby, 8, 0x10, 1);
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }

        if (props->m_0x10 <= 0) {
          props->m_0x10 = 1;
          g_SpawnMoby(38, moby);
        } else if (props->m_0x10 < 2 &&
                   moby->m_AnimationState.m_NextFrame >= 2) {
          props->m_0x10 = 2;
          g_SpawnMoby(38, moby);
        } else if (props->m_0x10 < 0x3C &&
                   moby->m_AnimationState.m_NextFrame >= 6) {
          props->m_0x10 = 0x3C;
          g_SpawnMoby(38, moby);
        }
        break;

      case 2:
        MoveMobyWithGravity(moby, &props->m_0x20, props->m_0x24, 0, 0xC, 0);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_284
    case 284: {
      Moby284Props *props = moby->m_Props;

      ApplyFlameHeat(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State < 5) {
        props->m_0x00 = 350;
        props->m_0x04 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        func_8003851C(moby, 0, 0);
        if ((rand() & 1) != 0) {
          moby->m_State = 6;
          MOBY_ANIM_CHANGE(moby, 6);
        } else {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
        }
        continue;
      }

      moby->m_DamageFlags = 0;

      if (props->m_0x10 != 0 && props->m_0x0c >= 0) {
        int *linkedProps = g_LevelMobys[props->m_0x0c].m_Props;

        if (linkedProps[5] == 3 && moby->m_State < 5) {
          linkedProps[3] = moby - g_LevelMobys;
          linkedProps[5] = props->m_0x10;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        if (g_LevelMobys[props->m_0x0c].m_State == 9) {
          switch (props->m_0x10) {
          case 4:
            if (moby->m_State < 5 &&
                g_LevelMobys[props->m_0x0c].m_AnimationState.m_NextFrame >= 4) {
              props->m_0x00 = 350;
              props->m_0x04 = g_LevelMobys[props->m_0x0c].m_Rotation.z;
              func_8003ABC0(moby, 1, 0, 0);
              func_8003B7C0(moby);
              moby->m_State = 7;
              MOBY_ANIM_CHANGE(moby, 7);
              continue;
            }
            break;

          case 5:
            break;

          case 6:
            if (moby->m_State < 4 && linkedProps[5] == 6) {
              moby->m_State = 4;
              MOBY_ANIM_CHANGE(moby, 4);
              continue;
            }
            break;
          }
        }
      }

      switch (moby->m_State) {
      case 0: {
        int distance = DISTANCE_TO_SPYRO(moby);

        if (distance < 0x1000) {
          RotateMobyToSpyro(moby, 6, 0, 0);
        } else {
          if (props->m_0x10 == 0 && props->m_0x0c >= 0) {
            if (g_LevelMobys[props->m_0x0c].m_State < 0x80) {
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
              continue;
            } else {
              props->m_0x0c = -1;
            }
          } else if (props->m_0x10 == 5) {
            int *linkedProps = g_LevelMobys[props->m_0x0c].m_Props;

            if (g_LevelMobys[props->m_0x0c].m_State < 7 &&
                linkedProps[5] == 5) {
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
              continue;
            }
          }
        }

        if (props->m_0x08 != 0) {
          props->m_0x08--;
          break;
        }

        if (distance < 2200 && SPYRO_BASE_Z_DELTA(moby) < 0x190) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;
      }
      case 1:
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (g_AnimationFinished) {
          props->m_0x08 = 0x78;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      case 2: {
        int angle = ANGLE_FROM(moby->m_Position,
                               g_LevelMobys[props->m_0x0c].m_Position);

        RotateMobyToAngle(moby, angle, 0x10, 0, 0);
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 3: {
        if (DISTANCE_TO_SPYRO(moby) < 0x1000) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        if (g_LevelMobys[props->m_0x0c].m_State >= 0x80) {
          props->m_0x0c = -1;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        RotateMobyToAngle(moby,
                          ANGLE_FROM(moby->m_Position,
                                     g_LevelMobys[props->m_0x0c].m_Position),
                          6, 0, 0);
        break;
      }

      case 4: {
        int var;

        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }

        var = (moby->m_AnimationState.m_NextFrame << 7) +
              (moby->m_AnimationState.m_FrameProgress << 1);
        if (var > 0x780) {
          var -= 0x780;
          if (var > 0x180) {
            var = 0x180;
          }
          var = 0x180 - var;
        } else if (var > 0x180) {
          var = 0x180;
        }

        moby->m_Position.x =
            props->m_0x14 - ((var * Sin(moby->m_Rotation.z << 4)) >> 10);
        moby->m_Position.y =
            props->m_0x18 + ((var * Cos(moby->m_Rotation.z << 4)) >> 10);
        moby->m_Position.z += 0x400;
        moby->m_Position.z = func_8004D5EC(&moby->m_Position, 0x1000);
        break;
      }

      case 5:
        MoveMobyWithGravity(moby, &props->m_0x00, props->m_0x04, 0, 0xC, 0);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 6:
        MoveMobyWithGravity(moby, &props->m_0x00, props->m_0x04, 0, 0xC, 0);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 7:
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_285
    case 285: {
      Moby285Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State < 6) {
        props->m_0x1c = (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >> 6) + 450;
        props->m_0x20 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x24 = 0x50;

        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          props->m_0x1c = 170;
          props->m_0x24 = 0x5A;
        }

        while (props->m_0x08 >= 0) {
          int *linkedProps = g_LevelMobys[props->m_0x08].m_Props;

          if (g_LevelMobys[props->m_0x08].m_State < 0x80) {
            g_SpawnParticle(5, 4, &g_LevelMobys[props->m_0x08].m_Position,
                            (int)&g_LevelMobys[props->m_0x08]);
          }

          props->m_0x00 = 0x20;
          props->m_0x08 = linkedProps[3];
          if (props->m_0x08 >= 0 && g_LevelMobys[props->m_0x08].m_Class != 66) {
            props->m_0x08 = -1;
          }
        }

        StopSound(moby->m_SoundChannel, 4);
        moby->m_UpdateDistance = 0x20;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 6;
        MOBY_ANIM_RESTART(moby, 6);
        continue;
      }

      switch (moby->m_State) {
      case 0:
        if ((props->m_0x10 & 2) == 0) {
          if ((props->m_0x10 & 8) != 0) {
            if (DISTANCE_TO_SPYRO(moby) < props->m_0x18) {
              int zDelta = SPYRO_ORIGIN_Z_DELTA(moby);
              int angle;

              if (g_Spyro.m_airTime == 0 && ABS2(zDelta) < 0x200) {
                if ((props->m_0x10 & 1) != 0) {
                  moby->m_State = 3;
                  MOBY_ANIM_CHANGE(moby, 3);
                } else {
                  moby->m_State = 2;
                  MOBY_ANIM_CHANGE(moby, 2);
                }
                continue;
              }

              angle = ANGLE_TO_SPYRO(moby->m_Position);
              if (func_80017908(moby->m_Rotation.z, angle) < 0x30 &&
                  zDelta >= -0xFFF && zDelta < 0) {
                if ((props->m_0x10 & 1) != 0) {
                  moby->m_State = 3;
                  MOBY_ANIM_CHANGE(moby, 3);
                } else {
                  moby->m_State = 2;
                  MOBY_ANIM_CHANGE(moby, 2);
                }
                continue;
              }

              // SKELETON: One param too little lol
#ifndef MODERN_COMPILER
              RotateMobyToAngle(moby, props->m_0x14, 4, 0x10);
#else
              RotateMobyToAngle(moby, props->m_0x14, 4, 0x10, 0);
#endif
            } else {
#ifndef MODERN_COMPILER
              RotateMobyToAngle(moby, props->m_0x14, 4, 0x10);
#else
              RotateMobyToAngle(moby, props->m_0x14, 4, 0x10, 0);
#endif
              props->m_0x10 &= ~1;
            }
            break;
          }

          if (DISTANCE_TO_SPYRO(moby) < props->m_0x18 &&
              SPYRO_ORIGIN_Z_DELTA(moby) >= -0xFFF &&
              SPYRO_ORIGIN_Z_DELTA(moby) < 0) {
            RotateMobyToSpyro(moby, 8, 0x10, 1);
            if ((props->m_0x10 & 1) != 0) {
              if (moby->m_Pod < 0xFF) {
                func_8003B1E8(moby, 0x63);
                break;
              }
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
              continue;
            }

            if (moby->m_Pod < 0xFF) {
              func_8003B1E8(moby, 0x62);
              break;
            }

            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
          break;
        }

        if ((props->m_0x10 & 1) != 0) {
          if ((props->m_0x10 & 4) != 0) {
            if (props->m_0x08 >= 0) {
              moby->m_State = 5;
              MOBY_ANIM_CHANGE(moby, 5);
              continue;
            }
            props->m_0x10 = (props->m_0x10 & ~6) | 1;
          } else {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        } else {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;

      case 1: {
        int result = MoveMobyAlongPath(moby, props->m_0x0c, 0x200, 0x80, 0x300,
                                       8, 0x10, 0);

        if (result == 0x100) {
          if (props->m_0x08 >= 0) {
            int *linkedProps;

            if (props->m_0x08[g_LevelMobys].m_State < 0x80) {
              props->m_0x14 = moby->m_Rotation.z;
              props->m_0x10 = (props->m_0x10 & ~2) | 5;
              moby->m_State = 5;
              MOBY_ANIM_CHANGE(moby, 5);
              continue;
            }

            linkedProps = props->m_0x08[g_LevelMobys].m_Props;
            props->m_0x08 = linkedProps[3];
            break;
          }

          props->m_0x10 = (props->m_0x10 & ~6) | 1;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        if (props->m_0x08 >= 0) {
          int *linkedProps = props->m_0x08[g_LevelMobys].m_Props;

          if (props->m_0x0c->m_CurrentNode < linkedProps[6]) {
            break;
          }

          if (props->m_0x08[g_LevelMobys].m_State < 0x80) {
            props->m_0x14 = moby->m_Rotation.z;
            moby->m_State = 5;
            MOBY_ANIM_CHANGE(moby, 5);
            continue;
          }

          props->m_0x08 = linkedProps[3];
        }
        break;
      }

      case 2:
        if (g_AnimationFinished) {
          props->m_0x10 |= 1;
          if ((props->m_0x10 & 2) != 0) {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
          } else {
            moby->m_State = 0;
            MOBY_ANIM_RESTART(moby, 0);
          }
          continue;
        }
        break;

      case 3:
        RotateMobyToSpyro(moby, 8, 0x10, 1);
        if (g_AnimationFinished) {
          props->m_0x00 = 0;
          props->m_0x04 = 0;
          if (DISTANCE_TO_SPYRO(moby) < props->m_0x18) {
            moby->m_State = 4;
            MOBY_ANIM_RESTART(moby, 4);
          } else {
            moby->m_State = 0;
            MOBY_ANIM_RESTART(moby, 0);
          }
          continue;
        }
        break;

      case 4:
        RotateMobyToSpyro(moby, 8, 0x10, 1);
        if (TICK_TIMER(props->m_0x00) &&
            moby->m_AnimationState.m_NextFrame >= 7 && props->m_0x04 < 3) {
          Moby *spawned = g_SpawnMoby(295, moby);

          if (DISTANCE_TO_SPYRO(moby) < 0xA00 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 0x400) {
            VecCopy(&spawned->m_Position, &g_Spyro.m_Position);
          }
          props->m_0x00 = 4;
          props->m_0x04++;
        }

        if (g_AnimationFinished) {
          if (DISTANCE_TO_SPYRO(moby) < props->m_0x18 &&
              SPYRO_ORIGIN_Z_DELTA(moby) >= -0xFFF &&
              SPYRO_ORIGIN_Z_DELTA(moby) < 0) {
            if ((props->m_0x10 & 2) != 0 || moby->m_Pod >= 0xFF) {
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
              continue;
            }

            func_8003B1E8(moby, 0x63);
            moby->m_State = 0;
            MOBY_ANIM_RESTART(moby, 0);
            continue;
          }

          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }

        if (moby->m_AnimationState.m_NextFrame < 5 &&
            DISTANCE_TO_SPYRO(moby) > props->m_0x18) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 5: {
        int angle;
        int angleDelta;

        angle = ANGLE_FROM(moby->m_Position,
                           g_LevelMobys[props->m_0x08].m_Position);
        angleDelta = (angle - moby->m_Rotation.z) & 0xFF;
        if (angleDelta > 0x80) {
          angleDelta -= 0x100;
        }
        if (angleDelta < -8) {
          angleDelta = -8;
        }
        if (angleDelta > 8) {
          angleDelta = 8;
        }
        moby->m_Rotation.z += angleDelta;

        if ((props->m_0x10 & 4) == 0) {
          if (func_8003A16C(moby, props->m_0x0c, 0x200, 0x80, 0x300, 8, 0x10,
                            &props->m_0x14) == 0x100) {
            props->m_0x10 |= 4;
          }
        }

        if (moby->m_AnimationState.m_NextFrame >= 9) {
          Vector3D vector;
          MATRIX matrix;

          vector.x = 0x800;
          vector.y = -0x100;
          vector.z = 0x400;
          RotVec8ToMatrix(&moby->m_Rotation, &matrix, 0);
          VecRotateByMatrix(&matrix, &vector, &vector);
          VecAdd(&vector, &vector, &moby->m_Position);
          g_SpawnParticle(3, 4, &vector, (int)&g_LevelMobys[props->m_0x08]);
        }

        if (g_AnimationFinished) {
          int *linkedProps = g_LevelMobys[props->m_0x08].m_Props;

          props->m_0x00 = 0x20;
          props->m_0x08 = linkedProps[3];
          if (props->m_0x08 >= 0 && g_LevelMobys[props->m_0x08].m_Class != 66) {
            props->m_0x08 = -1;
          }
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;
      }

      case 6:
        MoveMobyWithGravity(moby, &props->m_0x1c, props->m_0x20, &props->m_0x24,
                            0xC, 0xC);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;

      case 96:
        if (TICK_TIMER(props->m_0x00)) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;

      case 97:
        if (TICK_TIMER(props->m_0x00)) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;

      case 98:
        if (moby->m_AnimationState.m_NextAnimation == 0) {
          props->m_0x00 = rand() & 0x1F;
          moby->m_State = 96;
          continue;
        }
        moby->m_State = moby->m_AnimationState.m_NextAnimation;
        break;

      case 99:
        if (moby->m_AnimationState.m_NextAnimation == 0) {
          props->m_0x00 = rand() & 0x1F;
          moby->m_State = 97;
          continue;
        }
        moby->m_State = moby->m_AnimationState.m_NextAnimation;
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_286
    case 286: { // sound related
      Moby286Props *ambProps = moby->m_Props;
      int soundTableIndex;
      moby->m_SoundDistance = ambProps->m_0x04;

      soundTableIndex = -1;
      switch (ambProps->m_0x00) {
      case 0:
        soundTableIndex = 6;
        break;
      case 1:
        if (TICK_TIMER(ambProps->m_0x0c)) {
          ambProps->m_0x0c = 600 - (rand() & 0x7F);
          soundTableIndex = (rand() & 7) + 7;
        }
        break;
      case 2: {
        switch (ambProps->m_0x10) {
        case 0:
          if (TICK_TIMER(ambProps->m_0x0c)) {
            ambProps->m_0x0c = 512 - (rand() & 0x7F);
            soundTableIndex = (rand() & 1) + 13;
            ambProps->m_0x10 = 1;
          }
          break;

        case 1:
          if (ambProps->m_0x24-- > 0) {
            moby->m_Position.x += ambProps->m_0x18.x;
            moby->m_Position.y += ambProps->m_0x18.y;
            moby->m_Position.z += ambProps->m_0x18.z;
          } else {
            int curr, nxt;
            moby->m_Position.x =
                PATH_NODE_POS(ambProps->m_0x08,
                              (ambProps->m_0x08->m_CurrentNode + 1) %
                                  ambProps->m_0x08->m_NodeCount)
                    .x;
            moby->m_Position.y =
                PATH_NODE_POS(ambProps->m_0x08,
                              (ambProps->m_0x08->m_CurrentNode + 1) %
                                  ambProps->m_0x08->m_NodeCount)
                    .y;
            moby->m_Position.z =
                PATH_NODE_POS(ambProps->m_0x08,
                              (ambProps->m_0x08->m_CurrentNode + 1) %
                                  ambProps->m_0x08->m_NodeCount)
                    .z;
            ambProps->m_0x10 = 0;
            ambProps->m_0x08->m_CurrentNode =
                (ambProps->m_0x08->m_CurrentNode + 1) %
                ambProps->m_0x08->m_NodeCount;
            curr = ambProps->m_0x08->m_CurrentNode;
            nxt = (curr + 1) % ambProps->m_0x08->m_NodeCount;
            ambProps->m_0x24 =
                func_80017D7C(&PATH_NODE_POS(ambProps->m_0x08, curr),
                              &PATH_NODE_POS(ambProps->m_0x08, nxt),
                              &ambProps->m_0x18, ambProps->m_0x14);
          }
          if (moby->m_SoundChannel == 0x7F &&
              ambProps->m_0x24 == (ambProps->m_0x24 / 48) * 48) {
            soundTableIndex = 14;
          }
          break;
        }

        break;
      }
      case 3:
        if (TICK_TIMER(ambProps->m_0x0c)) {
          ambProps->m_0x0c = 624 - (rand() & 0x7F);
          soundTableIndex = (rand() & 1) + 15;
        }
        break;
      case 4:
        if (TICK_TIMER(ambProps->m_0x0c)) {
          ambProps->m_0x0c = 600 - (rand() & 0x7F);
          soundTableIndex = rand() % 4 + 21;
        }
        break;
      case 5:
        soundTableIndex = 24;
        break;
      case 6:
        soundTableIndex = 25;
        break;
      case 7:
        soundTableIndex = 18;
        break;
      case 8:
        soundTableIndex = 26;
        break;
      case 9:
        soundTableIndex = 54;
        break;
      }

      if (soundTableIndex >= 0) {
        u_char soundId = ((u_char *)g_Spu.m_SoundTable)[soundTableIndex];
        PlaySound(soundId, moby, 8, &moby->m_SoundChannel);
      }
      break;
    }
#endif
#if defined(HAS_MOBY_288) || defined(HAS_MOBY_289)
#ifdef HAS_MOBY_288
    case 288:
#endif
#ifdef HAS_MOBY_289
    case 289:
#endif
    {
      Moby288Props *props;

      props = moby->m_Props;

      if (props->m_0x0c == 0 || moby->m_WasDrawn == 0) {
        func_80052568(moby);
        continue;
      }

      moby->m_Position.x += props->m_0x00;
      moby->m_Position.y += props->m_0x02;
      props->m_0x04 -= 5;

      if (--props->m_0x0d == 0) {
        props->m_0x00 = 0;
        props->m_0x02 = 0;
        props->m_0x04 = 0;
      }

      if (moby->m_Class == 288) {
        moby->m_Rotation.x += props->m_0x06;
        moby->m_Rotation.y += props->m_0x08;
        moby->m_Rotation.z += props->m_0x0a;

        if (props->m_0x04 < -0x80) {
          props->m_0x04 = -0x80;
        }
      } else {
        if (props->m_0x04 < -0x18) {
          props->m_0x04 = -0x18;
        }

        if (props->m_0x10 == 0) {
          moby->m_Rotation.z += 0xC;
        } else if (props->m_0x04 < 0) {
          if (moby->m_Rotation.y + props->m_0x0e == 0x20 ||
              moby->m_Rotation.y + props->m_0x0e == 0xE0) {
            int temp = -props->m_0x0e;
            props->m_0x0e = temp;
          }

          moby->m_Rotation.y += props->m_0x0e;
          moby->m_Position.y += props->m_0x0e;

          if ((rand() & 1) != 0) {
            moby->m_Rotation.z++;
          }
        }
      }

      moby->m_Position.z += props->m_0x04;
      props->m_0x0c--;
      break;
    }
#endif
#if defined(HAS_MOBY_293) || defined(HAS_MOBY_294)
#ifdef HAS_MOBY_293
    case 293:
#endif
#ifdef HAS_MOBY_294
    case 294:
#endif
    {
      Moby293Props *props = moby->m_Props;
      int controlResult;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State >= 3 && moby->m_State != 4) {
        props->m_0x0c = 0x3C;
        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
          props->m_0x0c = 0x55;
        }
        props->m_0x14 = 0x3C;
        props->m_0x10 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        continue;
      }

      moby->m_DamageFlags = 0;

      if (props->m_0x30 == 0) {
        props->m_0x30 = 1;
        if (func_80038494(moby) != 0) {
          if (props->m_0x24 == 0) {
            moby->m_Pod = 0;
            func_8003B728(moby, 2);
            moby->m_Pod = 1;
            func_8003B728(moby, 2);
          } else if (props->m_0x24 == 1) {
            moby->m_Pod = 2;
            func_8003B728(moby, 2);
          }
          moby->m_Pod = 0xFF;
          func_80052568(moby);
          continue;
        }
      }

      if (props->m_0x24 == 0 && props->m_0x1c == 0) {
        props->m_0x1c = 1;
        if (g_Checkpoint.m_StoodOnCheckpoint != 0) {
          props->m_0x20 = 0;
        }
        if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x4c) != 0) {
          moby->m_Pod = 0;
          func_8003B728(moby, 2);
          moby->m_Pod = 1;
          func_8003B728(moby, 2);
          moby->m_Pod = 0xFF;
          moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);
          props->m_0x20 = 0;
          if (D_80075870[props->m_0x24] != 0) {
            VecCopy(
                &moby->m_Position,
                &PATH_NODE_POS(props->m_0x04, props->m_0x04->m_NodeCount - 1));
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
            continue;
          }
          props->m_0x04 = props->m_0x08;
          props->m_0x04->m_CurrentNode = props->m_0x04->m_NodeCount - 1;
          VecCopy(
              &moby->m_Position,
              &PATH_NODE_POS(props->m_0x04, props->m_0x04->m_NodeCount - 2));
          func_80038458(moby);
          moby->m_State = 5;
          continue;
        }
      }

      if (props->m_0x24 == 1 && props->m_0x1c == 0) {
        props->m_0x1c = 1;
        if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x4c) != 0) {
          moby->m_Pod = 2;
          func_8003B728(moby, 2);
          moby->m_Pod = 0xFF;
          moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);
          if (D_80075870[props->m_0x24] != 0) {
            VecCopy(&moby->m_Position, &PATH_NODE_POS(props->m_0x08, 0));
            func_80038458(moby);
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
            continue;
          }
          props->m_0x04 = props->m_0x08;
          props->m_0x04->m_CurrentNode = props->m_0x04->m_NodeCount - 1;
          VecCopy(
              &moby->m_Position,
              &PATH_NODE_POS(props->m_0x04, props->m_0x04->m_NodeCount - 2));
          func_80038458(moby);
          moby->m_State = 5;
          continue;
        }
        moby->m_State = 20;
        continue;
      }

      controlResult = 1;
      if (props->m_0x20 != 0) {
        if (g_Spyro.m_airTime == 0) {
          controlResult = TICK_TIMER(props->m_0x20);
          props->m_0x64 = 1;
        }
        if (props->m_0x64 == 0) {
          break;
        }
      }

      if (controlResult == 0) {
        g_Spyro.m_ControlFlags = 0x80002000;
        g_ScreenBorderEnabled = 1;
      } else if (controlResult == 2) {
        g_ScreenBorderEnabled = 0;
      }

      if (moby->m_AnimationState.m_NextAnimation == 4 &&
          moby->m_RenderRadius != 0) {
        if (moby->m_AnimationState.m_NextFrame == 1 && (rand() & 3) == 0 &&
            IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[6]) ==
                0) {
          func_8003851C(moby, 6, 0);
        }
        if (moby->m_AnimationState.m_NextFrame == 0xA && (rand() & 3) == 0 &&
            IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[5]) ==
                0) {
          func_8003851C(moby, 5, 0);
        }
      }

      switch (moby->m_State) {
      case 0: {
        int speed;
        int result;
        int floorHeight;

        speed = 0xB4;
        if ((PATH_CUR_NODE(props->m_0x04).unk_0xC & 0xFFC) != 0) {
          speed = PATH_CUR_NODE(props->m_0x04).unk_0xC & 0xFFC;
        }
        if (DISTANCE_TO_SPYRO(moby) < 0x1400 && speed < 170) {
          speed = 170;
        }

        result =
            func_80039E94(moby, props->m_0x04, 380, speed, 0, 8, 0x28, 0xFF, 0);
        floorHeight = func_80038400(moby, 3000);
        props->m_0x14 -= 0x1E;
        if (props->m_0x14 < -0x190) {
          props->m_0x14 = -0x190;
        }
        if (moby->m_Position.z + props->m_0x14 < floorHeight) {
          moby->m_Position.z = floorHeight;
        } else {
          moby->m_Position.z += props->m_0x14;
        }

        if (props->m_0x24 == 0) {
          if (result == 0x11C && DISTANCE_TO_SPYRO(moby) < 0x1C00 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 2200) {
            D_80075870[props->m_0x24] = 1;
          }
        }

        if (props->m_0x24 == 1) {
          if (result == 0x10A && DISTANCE_TO_SPYRO(moby) < 7500 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 3000) {
            D_80075870[props->m_0x24] = 1;
          }
        }

        if (result == 0x100) {
          if (props->m_0x24 == 1) {
            if (D_80075870[1] == 0) {
              props->m_0x04 = props->m_0x08;
              props->m_0x04->m_CurrentNode = 0;
              moby->m_State = 4;
              continue;
            }
            moby->m_State = 10;
            break;
          }
          if (props->m_0x24 == 0) {
            if (D_80075870[0] != 0) {
              moby->m_State = 3;
              continue;
            }
            props->m_0x04 = props->m_0x08;
            props->m_0x04->m_CurrentNode = 0;
            moby->m_State = 4;
            continue;
          }
        } else if ((result & 0x100) != 0) {
          switch (PATH_CUR_NODE(props->m_0x04).unk_0xC & 3) {
          case 1:
            props->m_0x14 = 0xDC;
            break;
          case 2:
            props->m_0x14 = 0x140;
            break;
          }
        }

        if (props->m_0x18 != -1 && moby->m_Position.z == floorHeight &&
            OctDistance(&moby->m_Position,
                        &g_LevelMobys[props->m_0x18].m_Position) < 2500) {
          moby->m_State = 1;
        }
        break;
      }

      case 1: {
        int angle;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
        angle = ANGLE_FROM(moby->m_Position,
                           g_LevelMobys[props->m_0x18].m_Position);
        RotateMobyToAngle(moby, angle, 6, 0, 0);
        if (g_AnimationFinished) {
          g_LevelMobys[props->m_0x18].m_Substate = 1;
          props->m_0x18 = *(int *)g_LevelMobys[props->m_0x18].m_Props;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 2: {
        MoveMobyWithGravity(moby, &props->m_0x0c, props->m_0x10, &props->m_0x14,
                            0xC, 0xC);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;
      }

      case 3: {
        int angle;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (DISTANCE_TO_SPYRO(moby) < props->m_0x28) {
          angle = ANGLE_FROM_SPYRO(moby->m_Position);
          if (func_80017908(g_Spyro.m_bodyRotation.z, angle) < 0x20) {
            props->m_0x04 = props->m_0x08;
            props->m_0x04->m_CurrentNode = 0;
            props->m_0x14 = 0;
            moby->m_State = 4;
            continue;
          }
        }
        break;
      }

      case 4: {
        int speed;
        int result;
        int floorHeight;
        int lastNode;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        speed = 0xF0;
        if ((PATH_CUR_NODE(props->m_0x04).unk_0xC & 0xFFC) != 0) {
          speed = PATH_CUR_NODE(props->m_0x04).unk_0xC & 0xFFC;
        }

        result = func_80039E94(moby, props->m_0x04, 380, speed, 0, 0xA, 0x28,
                               0xFF, 0);
        floorHeight = func_80038400(moby, 3000);
        props->m_0x14 -= 0xA;
        if (props->m_0x14 < -0x190) {
          props->m_0x14 = -0x190;
        }
        if (moby->m_Position.z + props->m_0x14 < floorHeight) {
          moby->m_Position.z = floorHeight;
        } else {
          moby->m_Position.z += props->m_0x14;
        }

        if (speed >= 0x119) {
          struct {
            Vector3D m_Position;
            Vector3D m_Velocity;
            int m_Speed;
          } particle;
          Vector3D particleOffset;
          int i;

          for (i = 0; i < 3; i++) {
            int angle = (moby->m_Rotation.z + RandRange(-7, 7)) & 0xFF;
            VecCopy(&particle.m_Position, &moby->m_Position);
            particle.m_Position.z += RandRange(0, 0x14);
            particle.m_Velocity.x = FIXED_MUL(COSINE_8(angle), 60);
            particle.m_Velocity.y = FIXED_MUL(SINE_8(angle), 60);
            particle.m_Velocity.z = 10;
            VecCopy(&particleOffset, &particle.m_Velocity);
            particleOffset.z = 2;
            VecShiftLeft(&particleOffset, 3);
            VecAdd(&particle.m_Position, &particle.m_Position, &particleOffset);
            particle.m_Speed = speed;
            g_SpawnParticle(1, 25, &particle, 0);
          }
        }
        lastNode = (props->m_0x24 == 0 || props->m_0x24 == 1)
                       ? props->m_0x04->m_NodeCount - 1
                       : 0;

        if (result == 0x103 && props->m_0x24 == 0 && D_80075870[0] == 0) {
          props->m_0x04->m_CurrentNode = props->m_0x04->m_NodeCount - 1;
          VecCopy(
              &moby->m_Position,
              &PATH_NODE_POS(props->m_0x04, props->m_0x04->m_NodeCount - 2));
          func_80038458(moby);
          moby->m_State = 5;
        } else if (result == lastNode + 0x100) {
          if (props->m_0x24 == 0 || props->m_0x24 == 1) {
            props->m_0x04->m_CurrentNode = props->m_0x04->m_NodeCount - 1;
            moby->m_State = 5;
          } else {
            props->m_0x28 = 0;
            moby->m_State = 3;
          }
        } else if ((result & 0x100) != 0) {
          switch (PATH_CUR_NODE(props->m_0x04).unk_0xC & 3) {
          case 1:
            props->m_0x14 = 380;
            break;
          case 2:
            if (props->m_0x24 == 0) {
              props->m_0x14 = 260;
            } else if (props->m_0x24 == 1) {
              props->m_0x14 = 0xD2;
            }
            break;
          case 3:
            props->m_0x14 = 200;
            break;
          }
        }
        break;
      }
      case 5: {
        Vector3D position;
        int angle;
        int height;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        angle = (ANGLE_TO_SPYRO(PATH_CUR_POS(props->m_0x04)) + 0x80) & 0xFF;
        height =
            func_80038638(moby, &PATH_CUR_POS(props->m_0x04), props->m_0x00,
                          angle, 0x1E, 100, 0xF, 0x20, 0xFF, 0xFF, 0, 0, 0);
        func_80038458(moby);
        if (height < 0x23 && g_Spyro.m_State != 0xB &&
            g_Spyro.m_State != 0x14) {
          if (TICK_TIMER(props->m_0x2c)) {
            moby->m_State = 6;
          }
        } else {
          props->m_0x2c = 0x78;
        }
        break;
      }

      case 6: {
        int angle;
        int height;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        angle = ANGLE_TO_SPYRO(PATH_CUR_POS(props->m_0x04));
        height =
            func_80038638(moby, &PATH_CUR_POS(props->m_0x04), props->m_0x00,
                          angle, 5, 200, 0xF, 0x20, 0xFF, 0xFF, 0, 0, 0);
        func_80038458(moby);
        if (DISTANCE_TO_SPYRO(moby) < 4000 || g_Spyro.m_State == 0xB ||
            g_Spyro.m_State == 0x14) {
          moby->m_State = 5;
        } else if (height < 0x46) {
          moby->m_State = 7;
        }
        break;
      }

      case 7: {
        RotateMobyToSpyro(moby, 6, 0, 0);
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        if (DISTANCE_TO_SPYRO(moby) < 4800 || g_Spyro.m_State == 0xB ||
            g_Spyro.m_State == 0x14) {
          moby->m_State = 5;
        }
        break;
      }

      case 10: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (SPYRO_BASE_Z_DELTA(moby) < 0 && DISTANCE_TO_SPYRO(moby) < 6500) {
          moby->m_State = 11;
        }
        break;
      }

      case 11: {
        int angle;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        angle = ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x08, 0));
        if (RotateMobyToAngle(moby, angle, 8, 0x14, 1) != 0) {
          if (OctDistance(&moby->m_Position, &PATH_NODE_POS(props->m_0x08, 0)) <
              300) {
            moby->m_State = 3;
          } else {
            func_80039398(moby, 0x118, 0, 0, 5);
          }
        }
        break;
      }

      case 20: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x34) != 0) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
        }
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_295
    case 295: {
      Moby295Props *props = moby->m_Props;
      Vector3D targetPosition;
      Vector3D oldPosition;
      int angle;
      int i;

      if (moby->m_Position.x < 0x400 || moby->m_Position.y < 0x400 ||
          moby->m_Position.z < 0x400) {
        func_80052568(moby);
        continue;
      }

      if (props->m_0x00 != 0) {
        VecCopy(&targetPosition, &props->m_0x00->m_Position);
        targetPosition.z += 700;
      } else {
        VecCopy(&targetPosition, &g_Spyro.m_Position);
      }

      angle =
          (ANGLE_FROM(moby->m_Position, targetPosition) - moby->m_Rotation.z) &
          0xFF;
      if (angle > 0x80) {
        angle -= 0x100;
      }
      if (angle > 2) {
        angle = 2;
      }
      if (angle < -2) {
        angle = -2;
      }
      moby->m_Rotation.z += angle;

      VecCopy(&oldPosition, &moby->m_Position);

      if (func_8004E2E8(&moby->m_Position, 100, 0x86) != 0) {
        for (i = 0; i < 3 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(318, moby);
        }

        g_Spyro.unk_0x208.x = COSINE_8(moby->m_Rotation.z) >> 5;
        g_Spyro.unk_0x208.y = SINE_8(moby->m_Rotation.z) >> 5;
        g_Spyro.unk_0x208.z = 0;
        func_80052568(moby);
        continue;
      }

      if (TICK_TIMER(props->m_0x04)) {
        func_80052568(moby);
        continue;
      }

      if (func_8003BCCC(moby, 300, 0, 0x100, 0) != 0) {
        func_80052568(moby);
        continue;
      }

      if (props->m_0x00 != 0) {
        if (OctDistance(&moby->m_Position, &targetPosition) < 0x200) {
          int zDelta = moby->m_Position.z - targetPosition.z;
          if (ABS2(zDelta) < 0x200) {
            for (i = 0; i < 3 && DYN_MOBY_FREE_COUNT > 20; i++) {
              g_SpawnMoby(318, moby);
            }
            props->m_0x00->m_DamageFlags |= MOBY_DAMAGE_UNK;
            func_80052568(moby);
            continue;
          }
        }
      } else {
        g_SpawnParticle(1, 5, &moby->m_Position, 0);
      }

      if (func_8004AE38(&oldPosition, &moby->m_Position) != 0) {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_296
    case 296: {
      Moby296Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State == 0) {
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
      } else if (g_LevelMobys[props->m_0x00].m_State >= 0x80) {
        func_80052568(moby);
      } else {
        switch (moby->m_State) {
        case 0:
          RotateMobyToSpyro(moby, 3, 0, 0);
          if (props->m_0x14) {
            moby->m_Position.z =
                props->m_0x10 + ((COSINE_8(props->m_0x04) + 0x1000) >> 1);
          } else {
            moby->m_Position.z =
                props->m_0x10 + ((COSINE_8(props->m_0x04) + 0x1000) >> 5);
          }
          if (props->m_0x04 >= 0xDD) {
            g_LevelMobys[props->m_0x00].m_Substate = 1;
          } else {
            g_LevelMobys[props->m_0x00].m_Substate = 0;
          }
          if (TICK_TIMER(props->m_0x04)) {
            props->m_0x04 = 0xFF;
          }
          break;

        case 1:
          if (g_AnimationFinished) {
            func_80052568(moby);
            continue;
          }
          break;
        }
        func_800529E4(moby, UPDATE_PROP_COLLISION);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_298
    case 298: {
      Moby298Props *props = moby->m_Props;

      ApplyFlameHeat(moby);

      if (moby->m_State < 2) {
        if (moby->m_DamageFlags & MOBY_DAMAGE_SUPER) {
          g_LevelMobys[props->m_0x00].m_DamageFlags |= moby->m_DamageFlags;
          props->m_0x04 = (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >> 6) + 450;
          props->m_0x0c = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
          props->m_0x08 = 0x50;
          func_8003ABC0(moby, 4, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        if (g_LevelMobys[props->m_0x00].m_State != 0) {
          props->m_0x0c = moby->m_Rotation.z;
          props->m_0x04 = 0;
          props->m_0x08 = 0;
          func_8003ABC0(moby, 4, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          break;
        }
        func_80052D64(&g_LevelMobys[props->m_0x00], 0, &moby->m_Position);
        moby->m_Rotation = g_LevelMobys[props->m_0x00].m_Rotation;
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0:
        if (DISTANCE_TO_SPYRO(moby) < 0xC00 && SPYRO_ORIGIN_Z_DELTA(moby) > 0 &&
            SPYRO_ORIGIN_Z_DELTA(moby) < 0xC00 && moby->m_Substate) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;

      case 1:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 2:
        if (MoveMobyWithGravity(moby, &props->m_0x04, props->m_0x0c,
                                &props->m_0x08, 0xC, 0x10)) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_SET_NEXT(moby, 3);
          continue;
        }
        break;

      case 3:
        if (MoveMobyWithGravity(moby, &props->m_0x04, props->m_0x0c,
                                &props->m_0x08, 0xC, 0x10)) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        if (moby->m_Position.z < 0x4E20) {
          func_80052568(moby);
          continue;
        }
        break;
      }
      func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_299
    case 299: {
      Moby299Props *props = moby->m_Props;

      if (moby->m_DamageFlags &
          (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) {
        int i;
        Moby *spawned;

        func_8003851C(moby, 0, 0);
        RegisterFlightMobyCollectibleType(props->m_0x04);

        spawned = g_SpawnMoby(props->m_0x00 + 344, moby);
        if (spawned != 0) {
          spawned->m_State = 1;
        }

        for (i = 0; i < 2 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(478, moby);
          g_SpawnMoby(479, moby);
        }

        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(480, moby);
        }

        g_SpawnParticle(5, 2, &moby->m_Position, 0);
        g_SpawnParticle(16, 70, &moby->m_Position, 0x20);
        func_80052568(moby);
      } else {
        // TODO: Hack
        Model **models;

        models = g_Models;
        if (!IsMobyPlayingSound(moby, models[299]->m_Sounds[1]) &&
            g_Gamestate == GS_Playing) {
          PlaySound(models[moby->m_Class]->m_Sounds[1], moby, 8,
                    &moby->m_SoundChannel);
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_300
    case 300: {
      Moby300Props *props;
      Vector3D *spyroPosition;
      Vector3D delta;
      int distance;
      props = (Moby300Props *)moby->m_Props;
      if (props->m_0x08 & 8) {
        if (g_LevelMobys[props->m_0x10].m_Class == MOBYCLASS_KEY) {
          if (g_LevelMobys[props->m_0x10].m_Substate == 0 ||
              (DISTANCE_TO_SPYRO(moby) > 0x1C00))
            break;
        } else if (g_LevelMobys[props->m_0x10].m_Class ==
                       MOBYCLASS_CRYSTAL_DRAGON ||
                   g_LevelMobys[props->m_0x10].m_Class == MOBYCLASS_GEM_1) {
          if (g_LevelMobys[props->m_0x10].m_State < 0x80)
            break;
        } else {
          break;
        }
      }
      if (props->m_0x08 & 2) {
        if (props->m_0x0c != 0) {
          if (TICK_TIMER(props->m_0x0c))
            props->m_0x08 = (props->m_0x08 & ~2) | 4;
        } else if (DISTANCE_TO_SPYRO(moby) < 0x1000 &&
                   SPYRO_BASE_Z_DISTANCE(moby) < 0x400) {
          props->m_0x0c = 0xB4;
        }
      } else {
        if (props->m_0x08 & 0x10)
          moby->m_Substate = 1;
        PlaySound(g_Spu.m_SoundTable->whirlwind, moby, 8,
                  &moby->m_SoundChannel);
        if ((rand() & 1) == 0)
          g_SpawnParticle(1, 6, moby, 0);
        VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
        distance = VecMagnitude(&delta, 0);
        if (distance < props->m_0x04 && delta.z > -0x400 &&
            delta.z < props->m_0x00 &&
            (g_Spyro.m_State == 0x11 ||
             g_Spyro.m_Position.z + 0xC00 <
                 moby->m_Position.z + props->m_0x00)) {
          // TODO: Hack
          spyroPosition = &g_Spyro.m_Position;
          g_Spyro.m_ControlFlags = 0x80000000;
          g_Spyro.m_mobyInUseBySpyro = moby;
          g_Spyro.m_DamageFlags |= 0x800;
          g_Spyro.m_portalEndPos.z = moby->m_Position.z + props->m_0x00;
          VecCopy(&g_Spyro.unk_0x17c, &moby->m_Position);
          if (props->m_0x08 & 1) {
            g_Spyro.m_ControlFlags |= 0x8000;
          } else {
            D_80078668 = D_8006C934;
            g_Spyro.unk_0x21c = spyroPosition;
            g_Spyro.unk_0x220 = &D_80078668;
            g_Spyro.m_ControlFlags |= 0x200;
            D_80078668.m_Coords.azimuth =
                ((ROTDEG8(180) - moby->m_Rotation.z) << 4) & 0xFFF;
          }
          props->m_0x0c = 120;
        } else {
          if ((props->m_0x08 & ~1) == 4 && props->m_0x0c != 0 &&
              TICK_TIMER(props->m_0x0c)) {
            props->m_0x08 = (props->m_0x08 & ~4) | 2;
          }
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_301
    case 301: {
      Moby301Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 4) {
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 4;
        MOBY_ANIM_RESTART(moby, 4);
        continue;
      }

      if ((moby->m_DamageFlags & MOBY_DAMAGE_UNK) != 0 && moby->m_State < 4) {
        moby->m_State = 5;
        MOBY_ANIM_RESTART(moby, 5);
        continue;
      }

      switch (moby->m_State) {
      case 0:
        if (DISTANCE_TO_SPYRO(moby) < 0x1000 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 0xC00) {
          if ((props->m_0x04 & 1) != 0) {
            props->m_0x04 |= 2;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
          } else {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
          }
          continue;
        }

        if (props->m_0x00 >= 0) {

          if (g_LevelMobys[props->m_0x00].m_State >= 0x80) {
            props->m_0x00 = -1;
          } else if (TICK_TIMER(props->m_0x08)) {
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          } else {
            RotateMobyToAngle(
                moby,
                ANGLE_FROM(moby->m_Position,
                           g_LevelMobys[props->m_0x00].m_Position),
                8, 0x10, 1);
          }
        }

        break;

      case 1:
        RotateMobyToSpyro(moby, 8, 0x10, 1);
        if (g_AnimationFinished) {
          props->m_0x04 |= 1;
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;

      case 2:
        if ((props->m_0x04 & 2) != 0) {
          if (DISTANCE_TO_SPYRO(moby) < 0x1800 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 0xC00) {
            RotateMobyToSpyro(moby, 8, 0x10, 1);
          } else {
            props->m_0x04 &= ~2;
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        } else {
          RotateMobyToAngle(moby,
                            ANGLE_FROM(moby->m_Position,
                                       g_LevelMobys[props->m_0x00].m_Position),
                            8, 0x10, 1);
        }

        if (g_AnimationFinished) {
          props->m_0x08 = 0;
          props->m_0x0c = 0;
          moby->m_State = 3;
          MOBY_ANIM_RESTART(moby, 3);
          continue;
        }
        break;

      case 3:
        if (TICK_TIMER(props->m_0x08) &&
            moby->m_AnimationState.m_NextFrame >= 4 && props->m_0x0c < 3) {
          Moby *spawned = g_SpawnMoby(295, moby);

          if ((props->m_0x04 & 2) != 0) {
            if (DISTANCE_TO_SPYRO(moby) < 0xA00 &&
                SPYRO_BASE_Z_DISTANCE(moby) < 0x400) {
              VecCopy(&spawned->m_Position, &g_Spyro.m_Position);
            }
          } else {
            Vector3D targetPosition;
            Moby295Props *spawnedProps = spawned->m_Props;

            VecCopy(&targetPosition, &g_LevelMobys[props->m_0x00].m_Position);
            targetPosition.z += 700;
            spawned->m_Rotation.y =
                Atan2(OctDistance(&moby->m_Position, &targetPosition),
                      targetPosition.z - moby->m_Position.z, 0);
            spawned->m_Rotation.z =
                ANGLE_FROM(moby->m_Position, targetPosition);
            spawned->m_RenderRadius = 0x24;
            spawnedProps->m_0x00 = &g_LevelMobys[props->m_0x00];
          }

          props->m_0x08 = 4;
          props->m_0x0c++;
        }

        if (g_AnimationFinished) {
          if ((props->m_0x04 & 2) != 0 && DISTANCE_TO_SPYRO(moby) < 0x1000 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 0xC00) {
            moby->m_State = 2;
            MOBY_ANIM_RESTART(moby, 2);
            continue;
          }

          props->m_0x04 &= ~2;
          props->m_0x08 = (rand() & 0x1F) + 0x20;
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;

      case 4:
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;

      case 5:
        if (g_AnimationFinished) {
          moby->m_DamageFlags = 0;
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_302
    case 302: {
      Moby302Props *props = moby->m_Props;

      if (props->m_0x04 != 0) {
        int i;

        if (props->m_0x10 >= 0) {
          Vector3D offset;
          Vector3D vertices[3];

          ColTriUnpack(props->m_0x10, vertices);
          VecNull(&offset);
          for (i = 0; i < 3; i++) {
            VecSub(&vertices[i], &vertices[i], &props->m_0x14[i]);
            VecAdd(&offset, &offset, &vertices[i]);
          }
          offset.x /= 3;
          offset.y /= 3;
          offset.z /= 3;
          VecAdd(&moby->m_Position, &moby->m_Position, &offset);
        }

        moby->m_Position.z += 0x400;
        func_800529E4(moby, UPDATE_PROP_CHAIN);
        i = func_8004D5EC(&moby->m_Position, 0x1000);
        if (i > 0) {
          moby->m_Position.z = i;
          props->m_0x10 = g_CollisionTriangleIndex;
          ColTriUnpack(props->m_0x10, props->m_0x14);
        } else {
          props->m_0x10 = -1;
        }
      }

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 3) {
        Moby *spawned;
        MobyCollectableProps *spawnedProps;

        StopSound(moby->m_SoundChannel, 4);
        spawned = (Moby *)func_8003ABC0(moby, 4, 0, 0);
        if (spawned != 0) {
          spawnedProps = spawned->m_Props;
          spawnedProps->m_SpawnState = 3;
        }
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        continue;
      }

      if ((moby->m_DamageFlags & MOBY_DAMAGE_UNK) != 0 && moby->m_State < 3) {
        moby->m_State = 4;
        MOBY_ANIM_CHANGE(moby, 4);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        int distance;
        int envAnimState;
        int envAnimState2;

        if (props->m_0x04 != 0) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }

        distance = OctDistance(&g_Spyro.m_Position,
                               (Vector3D *)((u_char *)props->m_0x08 + 0x18));
        if (distance < 0x2000 && props->m_0x0c != 0 && (rand() & 1) != 0) {
          g_SpawnParticle(1, 8, moby, (int)&g_LevelMobys[props->m_0x0c]);
        }

        envAnimState = func_8002B3F4(props->m_0x00);
        if ((envAnimState & 2) != 0) {
          envAnimState2 = (envAnimState >> 8) & 0xFF;
          if (envAnimState2 == 0) {
            if (distance < 0x2000) {
              func_8002B390(props->m_0x00, 0xFC, 0);
              moby->m_State = 2;
              MOBY_ANIM_CHANGE(moby, 2);
              continue;
            }
          }
          if (envAnimState2 == 0xE) {
            if (distance > 0x3000) {
              func_8002B390(props->m_0x00, 0xFC, 0);
              moby->m_State = 2;
              MOBY_ANIM_CHANGE(moby, 2);
              continue;
            }
          }
        }
        break;
      }

      case 1:
        if (props->m_0x0c >= 0 && (rand() & 1) != 0) {
          g_SpawnParticle(1, 8, moby, (int)&g_LevelMobys[props->m_0x0c]);
        }
        func_8002B390(props->m_0x00, 0xFC, 0);
        break;

      case 2:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }
        if (props->m_0x0c != 0 && (rand() & 1) != 0 &&
            OctDistance(&g_Spyro.m_Position,
                        (Vector3D *)((u_char *)props->m_0x08 + 0x18)) <
                0x2000) {
          g_SpawnParticle(1, 8, moby, (int)&g_LevelMobys[props->m_0x0c]);
        }
        break;

      case 3:
        if (props->m_0x04 == 0) {
          int envAnimState;

          envAnimState = func_8002B3F4(props->m_0x00);
          if ((envAnimState & 2) != 0) {
            envAnimState = (envAnimState >> 8) & 0xFF;
            if (envAnimState == 0xE) {
              func_8002B390(props->m_0x00, 0xFC, 0);
            }
          }
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        func_800529E4(moby, UPDATE_PROP_COLLISION);
        break;

      case 4:
        if (props->m_0x0c >= 0 && (rand() & 1) != 0) {
          g_SpawnParticle(1, 8, moby, (int)&g_LevelMobys[props->m_0x0c]);
        }
        func_8002B390(props->m_0x00, 0xFC, 0);
        if (g_AnimationFinished) {
          moby->m_DamageFlags = 0;
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          continue;
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_303
    case 303: {
      Moby303Props *props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 4) {
        StopSound(moby->m_SoundChannel, 4);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 4;
        MOBY_ANIM_CHANGE(moby, 4);
        continue;
      }

      if ((moby->m_DamageFlags & MOBY_DAMAGE_UNK) != 0 && moby->m_State != 2 &&
          moby->m_State != 4) {
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        continue;
      }

      TICK_TIMER(props->m_0x0c);

      switch (moby->m_State) {
      case 0:
        if (props->m_0x0c == 0 && (props->m_0x04 & 1) == 0) {
          props->m_0x0c = 0xB4;
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
        } else if (TICK_TIMER(props->m_0x08)) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
        }
        break;
      case 1:
        if (g_AnimationFinished) {
          props->m_0x08 = (rand() & 0x1F) + 0x30;
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
        }
        break;

      case 2:
        if (g_AnimationFinished) {
          moby->m_DamageFlags = 0;
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
        }
        break;

      case 3:
        if (moby->m_AnimationState.m_NextFrame >= 5 &&
            (props->m_0x04 & 1) == 0) {
          Moby *spawned;
          Moby304Props *spawnedProps;
          props->m_0x00->m_CurrentNode = 0;
          spawned = g_SpawnMoby(304, moby);
          spawnedProps = spawned->m_Props;
          spawnedProps->m_0x14 = props->m_0x10;
          props->m_0x04 |= 1;
        }
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
        }
        break;

      case 4:
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_800562A4(moby, 2);
          func_80052568(moby);
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_304
    case 304: {
      Moby304Props *props = moby->m_Props;

      switch (moby->m_State) {
      case 0:
        if (g_AnimationFinished) {
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          continue;
        }
        if (props->m_0x04->m_State >= 4) {
          func_80052568(moby);
          continue;
        }
        break;

      case 1: {
        if (func_8004E2E8(&moby->m_Position, 0x280, 0x46) != 0) {
          Moby303Props *props303 = props->m_0x04->m_Props;
          props303->m_0x04 &= ~1;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        if (MoveMobyAlongPath(moby, props->m_0x00, 0x100, 0x40, 0, 0x20, 0xFF,
                              &props->m_0x08) == 0x100) {
          Moby303Props *props303 = props->m_0x04->m_Props;
          props303->m_0x04 &= ~1;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }

        if (props->m_0x14 >= 0 && g_LevelMobys[props->m_0x14].m_State < 0x80 &&
            OctDistance(&moby->m_Position,
                        &g_LevelMobys[props->m_0x14].m_Position) < 0x280) {
          Moby303Props *props303 = props->m_0x04->m_Props;
          props303->m_0x04 &= ~1;
          g_LevelMobys[props->m_0x14].m_DamageFlags |= MOBY_DAMAGE_UNK;
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      }
      case 2:
        if (g_AnimationFinished) {
          func_800562A4(moby, 2);
          func_80052568(moby);
          continue;
        }
        break;
      }

      func_8004D5EC(&moby->m_Position, 0x10000);
      func_800533D0(moby);
      break;
    }
#endif
#ifdef HAS_MOBY_305
    case 305: {
      Moby305Props *props = moby->m_Props;

      ApplyFlameHeat(moby);

      if (moby->m_State == 2) {
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }

        if (props->m_0x2c < 0x40) {
          props->m_0x2c = 0x40;
        }
        moby->m_Position.x += FIXED_MUL(props->m_0x2c, Cos(props->m_0x24));
        moby->m_Position.y += FIXED_MUL(props->m_0x2c, Sin(props->m_0x24));
        break;
      }

      if ((moby->m_DamageFlags & MOBY_DAMAGE_SUPER) != 0) {
        props->m_0x24 = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
        props->m_0x2c = g_Spyro.m_Physics.m_TrueSpeed >> 5;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        continue;
      }

      moby->m_DamageFlags = 0;

      if (g_Spyro.m_State == 0xE) {
        props->m_0x20 = 0x78;
        props->m_0x10 |= 0x10;
      }

      if (g_Spyro.m_airTime == 0) {
        if (ABS2(SPYRO_ORIGIN_Z_DELTA(moby) + 0x164) < 0x140 &&
            DISTANCE_TO_SPYRO(moby) < props->m_0x30) {
          props->m_0x10 |= 8;
          VecNull(&props->m_0x14);
        } else {
          props->m_0x10 &= ~8;
        }

        switch (props->m_0x10 & 3) {
        case 0:
          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x04,
                                         props->m_0x04->m_NodeCount - 1)) <
              0xC00) {
            props->m_0x04->m_CurrentNode = props->m_0x04->m_NodeCount - 1;
            props->m_0x00 = props->m_0x04;
            props->m_0x10 |= 4;
          }
          break;

        case 1:
          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x04,
                                         props->m_0x04->m_NodeCount - 1)) <
              0xC00) {
            props->m_0x04->m_CurrentNode = props->m_0x04->m_NodeCount - 1;
            props->m_0x00 = props->m_0x04;
            props->m_0x10 = (props->m_0x10 | 4) & ~3;
          }
          break;

        case 2:
          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x04,
                                         props->m_0x04->m_NodeCount - 1)) <
              0xC00) {
            props->m_0x04->m_CurrentNode = props->m_0x04->m_NodeCount - 1;
            props->m_0x00 = props->m_0x04;
            props->m_0x10 = (props->m_0x10 | 4) & ~3;
          } else if (OctDistance(&g_Spyro.m_Position,
                                 &PATH_NODE_POS(props->m_0x08,
                                                props->m_0x08->m_NodeCount -
                                                    1)) < 0xC00) {
            props->m_0x00 = props->m_0x04;
            props->m_0x00->m_CurrentNode = 0;
            props->m_0x10 = (props->m_0x10 & ~3) | 1;
          }
          break;

        case 3:
          if (OctDistance(&g_Spyro.m_Position,
                          &PATH_NODE_POS(props->m_0x04,
                                         props->m_0x04->m_NodeCount - 1)) <
              0xC00) {
            props->m_0x04->m_CurrentNode = props->m_0x04->m_NodeCount - 1;
            props->m_0x00 = props->m_0x04;
            props->m_0x10 = (props->m_0x10 | 4) & ~3;
          } else if (OctDistance(&g_Spyro.m_Position,
                                 &PATH_NODE_POS(props->m_0x08,
                                                props->m_0x08->m_NodeCount -
                                                    1)) < 0xC00) {
            props->m_0x00 = props->m_0x04;
            props->m_0x00->m_CurrentNode = 0;
            props->m_0x10 = (props->m_0x10 & ~3) | 1;
          } else if (OctDistance(&g_Spyro.m_Position,
                                 &PATH_NODE_POS(props->m_0x0c,
                                                props->m_0x0c->m_NodeCount -
                                                    1)) < 0xC00) {
            props->m_0x00 = props->m_0x08;
            props->m_0x00->m_CurrentNode = 0;
            props->m_0x10 = (props->m_0x10 & ~3) | 2;
          }
          break;
        }
      }

      if ((props->m_0x10 & 0x10) != 0) {
        if (TICK_TIMER(props->m_0x20)) {
          props->m_0x10 &= ~0x10;
        }

        if (moby->m_State != 0) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
      } else if ((props->m_0x10 & 8) != 0) {
        func_8004E2E8(&moby->m_Position, 0x540, 7);

        if (moby->m_State != 3) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }

        moby->m_AnimationState.m_PerFrameProgress = 0x10;

        if (TICK_TIMER(props->m_0x20)) {
          if (RotateMobyToSpyro(moby, 8, 0x30, 1) != 0 &&
              func_80039398(moby, props->m_0x2c, 0, 0x400, 0x15) == 2) {
            props->m_0x20 = 0x12;
            props->m_0x24 = ANGLE_FROM(moby->m_Position, D_80077858);
            if (((props->m_0x24 - moby->m_Rotation.z) & 0xFF) < 0x80) {
              props->m_0x24 = (props->m_0x24 - 0x40) & 0xFF;
            } else {
              props->m_0x24 = (props->m_0x24 + 0x40) & 0xFF;
            }
          }
        } else {
          RotateMobyToAngle(moby, props->m_0x24, 8, 0x30, 1);
          func_80039398(moby, props->m_0x2c, 0, 0x400, 0x15);
        }
      } else if ((props->m_0x10 & 4) != 0) {
        if (TICK_TIMER(props->m_0x20)) {
          if ((props->m_0x10 & 0x20) != 0) {
            props->m_0x00->m_CurrentNode = 0;
          }

          if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) >
              0x100) {
            if (moby->m_State != 0) {
              moby->m_State = 0;
              MOBY_ANIM_CHANGE(moby, 0);
              continue;
            }

            moby->m_AnimationState.m_PerFrameProgress = 8;
            if (RotateMobyToAngle(
                    moby,
                    ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00)),
                    8, 0x30, 1) != 0 &&
                func_80039398(moby, 0x60, 0, 0x400, 0x15) == 2) {
              props->m_0x20 = 0x12;
              props->m_0x24 = ANGLE_FROM(moby->m_Position, D_80077858);
              if (((props->m_0x24 - moby->m_Rotation.z) & 0xFF) < 0x80) {
                props->m_0x24 = (props->m_0x24 - 0x40) & 0xFF;
              } else {
                props->m_0x24 = (props->m_0x24 + 0x40) & 0xFF;
              }
            }
          } else {
            if (moby->m_State != 1) {
              moby->m_State = 1;
              MOBY_ANIM_CHANGE(moby, 1);
              continue;
            }

            moby->m_AnimationState.m_PerFrameProgress = 0x10;
          }
        } else {
          RotateMobyToAngle(moby, props->m_0x24, 8, 0x30, 1);
          func_80039398(moby, 0x80, 0, 0x400, 0x15);
        }
      } else if ((props->m_0x10 & 3) != 0) {
        if ((props->m_0x10 & 0x40) != 0) {
          if (moby->m_State != 1) {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }

          if (TICK_TIMER(props->m_0x20)) {
            props->m_0x10 &= ~0x40;
          }
        } else {
          if (moby->m_State != 0) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }

          moby->m_AnimationState.m_PerFrameProgress = 8;

          if (TICK_TIMER(props->m_0x20)) {
            if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) <
                0x100) {
              if ((props->m_0x10 & 0x80) != 0) {
                if (props->m_0x00->m_CurrentNode != 0) {
                  props->m_0x00->m_CurrentNode--;
                } else {
                  props->m_0x10 = (props->m_0x10 & ~0x80) | 0x40;
                  props->m_0x20 = 0x3C;
                }
              } else {
                if (props->m_0x00->m_CurrentNode >=
                    props->m_0x00->m_NodeCount - 2) {
                  props->m_0x10 |= 0xC0;
                  props->m_0x20 = 0x3C;
                } else {
                  props->m_0x00->m_CurrentNode++;
                }
              }
            }

            if (RotateMobyToAngle(
                    moby,
                    ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00)),
                    8, 0x30, 1) != 0 &&
                func_80039398(moby, 0x60, 0, 0x400, 0x15) == 2) {
              props->m_0x20 = 0x12;
              props->m_0x24 = ANGLE_FROM(moby->m_Position, D_80077858);
              if (((props->m_0x24 - moby->m_Rotation.z) & 0xFF) < 0x80) {
                props->m_0x24 = (props->m_0x24 - 0x40) & 0xFF;
              } else {
                props->m_0x24 = (props->m_0x24 + 0x40) & 0xFF;
              }
            }
          } else {
            RotateMobyToAngle(moby, props->m_0x24, 8, 0x30, 1);
            func_80039398(moby, 0x60, 0, 0x400, 0x15);
          }
        }
      } else {
        props->m_0x00->m_CurrentNode = 0;

        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x00)) >
            0x100) {
          if (moby->m_State != 0) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }

          moby->m_AnimationState.m_PerFrameProgress = 8;

          if (TICK_TIMER(props->m_0x20)) {
            if (RotateMobyToAngle(
                    moby,
                    ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x00)),
                    8, 0x30, 1) != 0 &&
                func_80039398(moby, 0x60, 0, 0x400, 0x15) == 2) {
              props->m_0x20 = 0x12;
              props->m_0x24 = ANGLE_FROM(moby->m_Position, D_80077858);
              if (((props->m_0x24 - moby->m_Rotation.z) & 0xFF) < 0x80) {
                props->m_0x24 = (props->m_0x24 - 0x40) & 0xFF;
              } else {
                props->m_0x24 = (props->m_0x24 + 0x40) & 0xFF;
              }
            }
          } else {
            RotateMobyToAngle(moby, props->m_0x24, 8, 0x30, 1);
            func_80039398(moby, 0x60, 0, 0x400, 0x15);
          }
        } else {
          if (moby->m_State != 1) {
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }

          moby->m_AnimationState.m_PerFrameProgress = 0x10;
        }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_308
    case 308: {
      Moby308Props *props = moby->m_Props;

      if (props->m_0x30 == 0) {
        int i;
        int closestDistance;

        closestDistance = 0x7530;

        for (i = 0; i < props->m_0x00->m_NodeCount; i++) {
          int distance;

          distance =
              OctDistance(&moby->m_Position, &PATH_NODE_POS(props->m_0x00, i));

          if (distance < closestDistance) {
            closestDistance = distance;
            props->m_0x00->m_CurrentNode = i;
          }
        }

        props->m_0x30 = 1;
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State == 0) {
        Moby *spawned;
        int angle;
        int i;

        spawned = g_SpawnMoby(props->m_0x04 + 344, moby);
        if (spawned != 0) {
          spawned->m_State = 1;
        }

        RegisterFlightMobyCollectibleType(props->m_0x08);

        i = 0;
        props->m_0x14 = 0;
        props->m_0x1c = 350;

        angle = ANGLE_FROM_SPYRO(moby->m_Position);

        props->m_0x18 =
            func_80038178(angle, g_Spyro.m_bodyRotation.z, 0x28, 0x40);

        for (i = 0; i < 3 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(481, moby);
          g_SpawnMoby(482, moby);
          g_SpawnMoby(483, moby);
        }

        func_8003851C(moby, 0, 0);
        moby->m_State = 1;
        MOBY_ANIM_RESTART(moby, 1);
        break;
      }

      switch (moby->m_State) {
      case 0: {
        int rotation;

        rotation = moby->m_Rotation.z;

        if (g_LevelId == 15 || g_LevelId == 45) {
          func_8003BFC0(moby, props->m_0x00, &props->m_0x20, &props->m_0x2c,
                        0xC, 4);
        } else {
          func_8003BFC0(moby, props->m_0x00, &props->m_0x20, &props->m_0x2c,
                        0x16, 0);
        }

        rotation = (moby->m_Rotation.z - rotation) & 0xFF;

        if (rotation > 0x80) {
          rotation -= 0x100;
        }

        props->m_0x10 +=
            (((-rotation) << 8) - (props->m_0x10 << 3) - props->m_0x0c) >> 6;

        props->m_0x0c = (props->m_0x0c + props->m_0x10) & 0xFFF;

        if (props->m_0x0c > 0x800) {
          props->m_0x0c -= 0x1000;
        }

        if (props->m_0x0c < -0x200) {
          props->m_0x0c = -0x200;
        }

        if (props->m_0x0c > 0x200) {
          props->m_0x0c = 0x200;
        }

        moby->m_Rotation.x = props->m_0x0c >> 4;
        break;
      }

      case 1:
        if (MoveMobyWithGravity(moby, &props->m_0x1c, props->m_0x18,
                                &props->m_0x14, 0xC, 0xC) == 3) {
          PlaySound(g_Spu.m_SoundTable->waterSplash, moby, 8,
                    &moby->m_SoundChannel);

          g_SpawnMoby(400, moby);
          func_80052568(moby);
          break;
        }

        if (g_AnimationFinished) {
          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
        }
        break;

      case 2:
        if (MoveMobyWithGravity(moby, &props->m_0x1c, props->m_0x18,
                                &props->m_0x14, 0xC, 0xC) == 3) {
          PlaySound(g_Spu.m_SoundTable->waterSplash, moby, 8,
                    &moby->m_SoundChannel);

          g_SpawnMoby(400, moby);
          func_80052568(moby);
        }
        break;
      }

      break;
    }
#endif
#ifdef HAS_MOBY_309
    case 309: { // Some fragment 1
      MobyFragmentProps *props = moby->m_Props;

      if (props->m_Lifetime != 0 && moby->m_WasDrawn) {
        Vector3D particlePosition;

        moby->m_Position.x += props->m_Velocity.x;
        moby->m_Position.y += props->m_Velocity.y;
        props->m_Velocity.z -= 6;
        if (props->m_Velocity.z < -0x80)
          props->m_Velocity.z = -0x80;
        moby->m_Position.z += props->m_Velocity.z;

        moby->m_Rotation.x += props->m_AngularVelocity.x;
        moby->m_Rotation.y += props->m_AngularVelocity.y;
        moby->m_Rotation.z += props->m_AngularVelocity.z;

        particlePosition.x = (rand() & 0xFE) - 127;
        particlePosition.y = (rand() & 0xFE) - 127;
        particlePosition.z = (rand() & 0xFE) - 64;
        VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
        g_SpawnParticle(1, 66, &particlePosition, 1);
        props->m_Lifetime--;
      } else {
        func_80052568(moby);
      }
      break;
    }
#endif
#if defined(HAS_MOBY_310) || defined(HAS_MOBY_311)
#ifdef HAS_MOBY_310
    case 310: // Some fragment 2 / 3
#endif
#ifdef HAS_MOBY_311
    case 311:
#endif
    {
      int value;
      int dot;
      MobyFragmentProps *physicsProps = moby->m_Props;

      if (physicsProps->m_Lifetime > 0 && moby->m_WasDrawn) {
        value = func_8004BE4C(&moby->m_Position, 0x100, 0x100);
        if (value != 0) {
          func_80017330(&g_CollisionNormal, 0x1000);
          dot = (physicsProps->m_Velocity.x * g_CollisionNormal.x +
                 physicsProps->m_Velocity.y * g_CollisionNormal.y +
                 physicsProps->m_Velocity.z * g_CollisionNormal.z);
          value = dot >> 11;
          if (value < 0) {
            VecScaleToLength(&g_CollisionNormal, 0x1000, (dot >> 13) - value);
            physicsProps->m_Velocity.x += g_CollisionNormal.x;
            physicsProps->m_Velocity.y += g_CollisionNormal.y;
            physicsProps->m_Velocity.z += g_CollisionNormal.z;
          }
        }

        moby->m_Position.x += physicsProps->m_Velocity.x;
        moby->m_Position.y += physicsProps->m_Velocity.y;
        physicsProps->m_Velocity.z -= 6;
        if (physicsProps->m_Velocity.z < -0x80)
          physicsProps->m_Velocity.z = -0x80;
        moby->m_Position.z += physicsProps->m_Velocity.z;

        moby->m_Rotation.x += physicsProps->m_AngularVelocity.x;
        moby->m_Rotation.y += physicsProps->m_AngularVelocity.y;
        moby->m_Rotation.z += physicsProps->m_AngularVelocity.z;

        for (value = 0; value < 3; value++) {
          Vector3D particlePosition;

          particlePosition.x = (rand() & 0xFE) - 127;
          particlePosition.y = (rand() & 0xFE) - 127;
          particlePosition.z = (rand() & 0xFE) - 64;
          VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
          g_SpawnParticle(1, 66, &particlePosition, 1);
        }
        physicsProps->m_Lifetime--;
      } else {
        if (moby->m_WasDrawn) {
          g_SpawnParticle(8, 70, &moby->m_Position, 0x10);
        }
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_312
    case 312: { // Fireworks Chest
      Moby312Props *props = moby->m_Props;

      switch (moby->m_Substate) {
      case 0: // Init
        ((int *)&moby->m_SpecularMetalColor)[0] =
            D_8006E678[moby->m_DropMoby - MOBYCLASS_GEM_1];
        moby->m_Substate = 1;
        break;
      case 1: // Idle, Awaiting Damage
        if (moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) {
          moby->m_Substate = 2;
          moby->m_UpdateDistance = 0xFF;
          moby->m_RenderRadius = 0x7F;
          if (props->m_Timer < 90) {
            props->m_Timer = 90;
          }
          props->m_BaseRotX = moby->m_Rotation.x;
          props->m_BaseRotY = moby->m_Rotation.y;
          props->m_BasePosZ = moby->m_Position.z;
        } else if (moby->m_DamageFlags & MOBY_DAMAGE_FLAME) {
          moby->m_Substate = 2;
          moby->m_UpdateDistance = 0xFF;
          moby->m_RenderRadius = 0x7F;
          props->m_Timer = 0;
          props->m_BaseRotX = moby->m_Rotation.x;
          props->m_BaseRotY = moby->m_Rotation.y;
          props->m_BasePosZ = moby->m_Position.z;
        } else if (moby->m_DamageFlags &
                   (MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) {
          moby->m_Substate = 3;
          moby->m_RenderRadius = 0;
          moby->m_WasDrawn = 0;
          props->m_Timer = 0;
        }
        break;

      case 2: { // Burning state
        int i;
        Vector3D vel[2];
        int count;

        props->m_Timer += g_DeltaTime;

        if (props->m_Timer < 120) {
          if ((moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) &&
              props->m_Timer < 90) {
            props->m_Timer = 90;
          }

          for (i = 0; i < 6; i++) {
            vel[0].x = D_8006E614[i >> 1].m_LocalOffset.x;
            vel[0].y = D_8006E614[i >> 1].m_LocalOffset.y;
            vel[0].z = D_8006E614[i >> 1].m_LocalOffset.z;
            VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vel[0],
                              &vel[0]);
            VecAdd(&vel[0], &vel[0], &moby->m_Position);
            vel[1].x = D_8006E614[i >> 1].m_Velocity.x;
            vel[1].y = D_8006E614[i >> 1].m_Velocity.y;
            vel[1].z = D_8006E614[i >> 1].m_Velocity.z;
            VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vel[1],
                              &vel[1]);
            vel[1].x += (rand() & 0xF) - 8;
            vel[1].y += (rand() & 0xF) - 8;
            g_SpawnParticle(1, 74, &vel[0], (int)&vel[1]);
          }
          count = props->m_Timer / 40 + 1;

          for (i = 0; i < count; i++) {
            // Would make more sense as an int[2] where the first
            // int is a particle size and the second int is
            // color intensity, stored as / 8
            // Typing as int[2] breaks the match for now
            Vector3D param;

            vel[0].x = (rand() & 0x1FF) - 0xFF;
            vel[0].y = (rand() & 0x1FF) - 0xFF;
            vel[0].z = (rand() & 0x7F) + 0xC0;
            vel[1].x = vel[0].x >> 4;
            vel[1].y >>= 4;
            vel[1].z = (rand() & 0xF) + 8;
            VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vel[0],
                              &vel[0]);
            VecAdd(&vel[0], &vel[0], &moby->m_Position);
            VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &vel[1],
                              &vel[1]);
            param.x = (rand() & 7) + 0x10;
            param.y = (rand() & 7) + 6;
            g_SpawnParticle(1, 16, &vel[0], (int)&param);
            if (moby->m_SoundChannel == 0x7F) {
              func_8003851C(moby, 0, 0);
            }
          }

          if (props->m_Timer > 56) {
            moby->m_Rotation.x =
                props->m_BaseRotX +
                g_MobyShakeOffsets[(120 - props->m_Timer) >> 1][0];
            moby->m_Rotation.y =
                props->m_BaseRotY +
                g_MobyShakeOffsets[(120 - props->m_Timer) >> 1][1];
            moby->m_Position.z =
                props->m_BasePosZ +
                (ABS2(g_MobyShakeOffsets[(120 - props->m_Timer) >> 1][0]) +
                 ABS2(g_MobyShakeOffsets[(120 - props->m_Timer) >> 1][1])) *
                    6;
          }
        } else {
          moby->m_Substate = 3;
          moby->m_RenderRadius = 0;
          moby->m_WasDrawn = 0;
          props->m_Timer = 0;
        }
        break;
      }

      case 3: // Explosion
        if (props->m_Timer == 0) {
          Moby *frag;
          MobyFragmentProps *fp1;
          Moby152Props *fp2;
          int i;

          func_8003851C(moby, 1, 0);
          func_8003ABC0(moby, 6, 0, 0);

          for (i = 0; i < 8 && DYN_MOBY_FREE_COUNT > 20; i++) {
            frag = g_SpawnMoby(151, moby);
            fp1 = frag->m_Props;
            fp1->m_Velocity.x >>= 1;
            fp1->m_Velocity.y >>= 1;
          }

          for (i = 0; i < 16 && DYN_MOBY_FREE_COUNT > 20; i++) {
            frag = g_SpawnMoby(153, moby);
            fp2 = frag->m_Props;
            frag->m_Substate = (rand() & 1) + 18;
            VecCopy(&frag->m_Position, &moby->m_Position);
            frag->m_Position.x +=
                (COSINE_8(i << 4) >> 4) + (rand() & 0x1F) - 15;
            frag->m_Position.y += (SINE_8(i << 4) >> 4) + (rand() & 0x1F) - 15;
            frag->m_Position.z += (rand() & 0xFF) + 0x80;
            fp2->m_Velocity.x =
                (COSINE_8(i << 4) / 0x20) + (rand() & 0x1F) - 0xF;
            fp2->m_Velocity.y = (SINE_8(i << 4) / 0x20) + (rand() & 0x1F) - 15;
            fp2->m_Velocity.z = (rand() & 0x3F) + 48;
            frag->m_Rotation.x = rand();
            frag->m_Rotation.y = rand();
            frag->m_Rotation.z = rand();
            fp2->m_AngularVelocity.x = rand() & 0xF;
            fp2->m_AngularVelocity.y = rand() & 0xF;
            fp2->m_AngularVelocity.z = rand() & 0xF;
            fp2->m_MinZ = moby->m_Position.z;
          }

          for (i = 0; i < 12 && DYN_MOBY_FREE_COUNT > 20; i++) {
            frag = g_SpawnMoby(152, moby);
            fp2 = frag->m_Props;
            frag->m_Substate = (rand() & 3) + 25;
            VecCopy(&frag->m_Position, &moby->m_Position);
            frag->m_Position.x +=
                (COSINE_8(((i << 8) / 12)) >> 4) + (rand() & 0x3F) - 31;
            frag->m_Position.y +=
                (SINE_8(((i << 8) / 12)) >> 4) + (rand() & 0x3F) - 31;
            frag->m_Position.z += (rand() & 0xFF) + 0x80;
            fp2->m_Velocity.x =
                (COSINE_8(((i << 8) / 12)) / 0x38) + (rand() & 0x1F) - 15;
            fp2->m_Velocity.y =
                (SINE_8(((i << 8) / 12)) / 0x38) + (rand() & 0x1F) - 15;
            fp2->m_Velocity.z = (rand() & 0x7F) + 0x60;
            frag->m_Rotation.x = rand();
            frag->m_Rotation.y = rand();
            frag->m_Rotation.z = rand();
            fp2->m_AngularVelocity.x = rand() & 0xF;
            fp2->m_AngularVelocity.y = rand() & 0xF;
            fp2->m_AngularVelocity.z = rand() & 0xF;
            fp2->m_MinZ = moby->m_Position.z;
          }
        }

        if (!props->m_HitSpyro) {
          if (func_8004E2E8(&moby->m_Position, (props->m_Timer + 1) * 0x100,
                            0x86)) {
            props->m_HitSpyro = 1;
            g_Spyro.unk_0x208.x = g_Spyro.m_Position.x - moby->m_Position.x;
            g_Spyro.unk_0x208.y = g_Spyro.m_Position.y - moby->m_Position.y;
            g_Spyro.unk_0x208.z = 0;
            if (g_Spyro.unk_0x208.x != 0 || g_Spyro.unk_0x208.y != 0) {
              VecScaleToLength(&g_Spyro.unk_0x208,
                               VecMagnitude(&g_Spyro.unk_0x208, 1),
                               (0x1000 - DISTANCE_TO_SPYRO(moby)) / 48);
            }
            g_Spyro.unk_0x208.z = 0x46;
          }
        }

        func_8004E3C8(&moby->m_Position, (props->m_Timer + 1) * 0x100, 0,
                      0x50000, moby, 0);
        props->m_Timer++;
        if (props->m_Timer >= 8) {
          func_8003B7C0(moby);
          func_80052568(moby);
        }
        break;
      }

      moby->m_DamageFlags = 0;
      break;
    }
#endif
#ifdef HAS_MOBY_314
    case 314: {
      Moby314Props *props = moby->m_Props;

      if (moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) {
        if (moby->m_State < 10 || moby->m_State >= 20) {
          if (moby->m_State != 98) {
            moby->m_State = 10;
            continue;
          }
        }
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0: {
        int targetToSpyroAngle;
        int mobyToTargetAngle;
        int sideDistance;
        int angleLimit;

        targetToSpyroAngle =
            ANGLE_FROM_SPYRO(PATH_NODE_POS(props->m_0x04, props->m_0x10));

        mobyToTargetAngle = ANGLE_FROM(
            PATH_NODE_POS(props->m_0x04, props->m_0x10), moby->m_Position);

        sideDistance = props->m_0x10 * 20 + 0xB4;

        angleLimit = moby->m_AnimationState.m_NextAnimation == 0 ? 0x19 : 0x0A;

        if (func_80017908(targetToSpyroAngle, mobyToTargetAngle) > angleLimit) {
          func_80038638(moby, &PATH_NODE_POS(props->m_0x04, props->m_0x10),
                        5000, targetToSpyroAngle, 6, sideDistance, 6, 0x14,
                        0xFF, 0xFF, 0, 0, 0);

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x1c + 1);
        } else {
          RotateMobyToSpyro(moby, 6, 0, 0);

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x1c);
        }

        if (!func_8003B0DC(props->m_0x10)) {
          moby->m_State = 20;
          continue;
        }

        break;
      }

      case 10:
        switch (props->m_0x10) {
        case 0:
          func_8002B390(0, 0xFC, 0);

          if (props->m_0x28 >= 0) {
            Moby *linked;

            linked = &g_LevelMobys[props->m_0x28];

            VecCopy(&linked->m_Position, &moby->m_Position);

            func_8003ABC0(linked, 1, 0, 0);
            func_8003B7C0(linked);

            props->m_0x28 = -1;

            func_80052568(linked);
          }

          if (moby->m_AnimationState.m_NextAnimation < props->m_0x1c + 4) {
            if (moby->m_AnimationState.m_NextAnimation != props->m_0x1c + 2) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby, props->m_0x1c + 2);
            }
          } else if (moby->m_AnimationState.m_Animation != props->m_0x1c + 2) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, props->m_0x1c + 2);
          }

          break;

        case 1: {
          Moby *linked;
          Moby314Props *linkedProps;

          linked = &g_LevelMobys[props->m_0x20];

          linkedProps = linked->m_Props;

          func_8002B390(1, 0xFC, 0);

          linked->m_State = 11;

          linked->m_AnimationState.m_Animation = 7;
          linked->m_AnimationState.m_NextAnimation = 7;

          linkedProps->m_0x1c = 7;
          linkedProps->m_0x10 = 1;

          linkedProps->m_0x00->m_CurrentNode = props->m_0x00->m_CurrentNode;

          VecCopy(&linked->m_Position, &moby->m_Position);

          linked->m_Rotation.z = moby->m_Rotation.z;

          linked->m_RenderRadius = 0x28;
          linked->m_UpdateDistance = 0x28;

          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);

          if (moby->m_AnimationState.m_Animation != 5) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 5);
          }
          break;
        }

        case 2:
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 9);
          break;
        }

        moby->m_State++;
        break;

      case 11:
        if (g_AnimationFinished) {
          switch (props->m_0x10) {
          case 0:
            if (moby->m_AnimationState.m_NextAnimation != props->m_0x1c + 1) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby, props->m_0x1c + 1);
            }

            break;

          case 1:
            if (props->m_0x1c == 0) {
              if (moby->m_AnimationState.m_Animation != 6) {
                g_AnimationFinished = 0;
                MOBY_ANIM_RESTART(moby, 6);
              }

              moby->m_CollisionGroup = 0;
              moby->m_State = 98;
              continue;
            }

            if (moby->m_AnimationState.m_NextAnimation != props->m_0x1c + 1) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby, props->m_0x1c + 1);
            }

            break;

          case 2:
            func_8002B390(2, 0xFC, 0);
            func_8003ABC0(moby, 1, 0, 0);
            func_8003B7C0(moby);
            func_800385BC(moby, 0x20);
            func_80052568(moby);
            continue;
          }
          moby->m_State++;
        }

        break;

      case 12:
        props->m_0x24 = 0x78;
        moby->m_State++;
        break;

      case 13: {
        int nodeIndex;

        nodeIndex = props->m_0x08[props->m_0x10];

        if (OctDistance(&moby->m_Position,
                        &PATH_NODE_POS(props->m_0x00, nodeIndex)) < 600) {
          props->m_0x10++;
          moby->m_State = 0;
          continue;
        }
        func_80039E94(moby, props->m_0x00, 0x200, 200, 0, 9, 0x14, 0xFF, 5);
        break;
      }

      case 20: {
        int closeDistance;

        closeDistance = props->m_0x10 == 2 ? 2400 : 3000;

        if (RotateMobyToSpyro(moby, 6, 0x14, 1) && g_AnimationFinished) {
          if (props->m_0x10 < 2) {
            if (props->m_0x14 == 0) {
              props->m_0x14 = RandRange(2, 4);

              if (moby->m_AnimationState.m_Animation != 4) {
                g_AnimationFinished = 0;
                MOBY_ANIM_RESTART(moby, 4);
              }
            } else {
              props->m_0x14--;

              if (moby->m_AnimationState.m_NextAnimation == 4) {
                if (moby->m_AnimationState.m_Animation != 0) {
                  g_AnimationFinished = 0;
                  MOBY_ANIM_RESTART(moby, 0);
                }
              } else if (moby->m_AnimationState.m_NextAnimation != 0) {
                g_AnimationFinished = 0;
                MOBY_ANIM_ADVANCE(moby, 0);
              }
            }
          } else {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x1c);
          }
        }

        if (TICK_TIMER(props->m_0x18) &&
            DISTANCE_TO_SPYRO(moby) < closeDistance) {
          moby->m_State = 21;
          continue;
        }

        break;
      }

      case 21:
        if (moby->m_AnimationState.m_NextAnimation != props->m_0x1c + 3) {
          props->m_0x18 = 0xB4;

          g_Spyro.unk_0x208.x = FIXED_MUL(SINE_8(moby->m_Rotation.z), 0x80);
          g_Spyro.unk_0x208.y = FIXED_MUL(COSINE_8(moby->m_Rotation.z), -0x80);
          g_Spyro.unk_0x208.z = 0;

          if (moby->m_AnimationState.m_NextAnimation < props->m_0x1c + 4) {
            if (moby->m_AnimationState.m_NextAnimation != props->m_0x1c + 3) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby, props->m_0x1c + 3);
            }
          } else if (moby->m_AnimationState.m_Animation != props->m_0x1c + 3) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, props->m_0x1c + 3);
          }
          moby->m_State = 20;
          continue;
        }
        break;
      }

      if (moby->m_State != 98) {
        func_800529E4(moby, UPDATE_PROP_COLLISION);
      }

      break;
    }
#endif
#ifdef HAS_MOBY_315
    case 315: { // Yellow Beast Snack (Alpine Ridge)
      Moby315Props *props = moby->m_Props;

      if (props->m_IsThrown) {
        if (!TICK_TIMER(props->m_Lifetime)) {
          func_80039688(moby, props->m_ThrowAngle, 90, 0, 0, 0);
          moby->m_Position.z += props->m_ZVelocity;
          props->m_ZVelocity -= 20;
          if (props->m_ZVelocity < -120) {
            props->m_ZVelocity = -120;
          }
        } else {
          func_80052568(moby);
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_318
    case 318: {
      Moby318Props *props = moby->m_Props;

      if (!TICK_TIMER(props->m_0x0c) && moby->m_WasDrawn) {
        props->m_0x00.z -= 6;
        if (props->m_0x00.z < -0x80) {
          props->m_0x00.z = -0x80;
        }

        VecAdd(&moby->m_Position, &moby->m_Position, &props->m_0x00);
        moby->m_Rotation.x += 0xF;
        moby->m_Rotation.z += 9;
      } else {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_323 // Fodder Respawner
    case 323: {
      // Handles Mobys 10, 36, 160, 193, 213, 236, 238, 412, 413, 453, 466
      Moby323Props *respProps = moby->m_Props;
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
      if (TICK_TIMER(respProps->m_RespawnTimer)) {
        Moby *m;
        // Interval is always 5s
        respProps->m_RespawnTimer = respProps->m_RespawnInterval;
        // Respawn every fodder Moby whose spawn position is far enough from
        // Spyro
        for (m = g_LevelMobys; m < g_DynMobys; m++) {
          if (m->m_Class == respProps->m_RespawnClass && m->m_State >= 0x80 &&
              OctDistance(&g_Spyro.m_Position, (Vector3D *)m->m_Props) >
                  0x6000) {
            VecCopy(&m->m_Position, (Vector3D *)m->m_Props);
            func_800526A8(m);
            m->m_DamageFlags = 0;
            m->m_State = 0;
            m->m_DroppedFlag &= 0x7F;
            MOBY_ANIM_RESTART(m, 0);
          }
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_326
    case 326: {
      Moby326Props *props = moby->m_Props;
      int distance = DISTANCE_TO_SPYRO(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 6) {
        if (props->m_0x10 == 1) {
          moby->m_State = 10;
        } else {
          StopSound(moby->m_SoundChannel, 4);
          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 6;
          MOBY_ANIM_RESTART(moby, 6);
          continue;
        }
      }

      if (distance > 0x2000) {
        props->m_0x1c = 0;
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x10 == 0) {
          RotateMobyToSpyro(moby, 8, 0, 0);
          if ((TICK_TIMER(props->m_0x00) &&
               OctDistance(&g_Spyro.m_Position,
                           &PATH_NODE_POS(props->m_0x0c, 0)) < props->m_0x18) ||
              DISTANCE_TO_SPYRO(moby) < 0x1000) {
            if (moby->m_Pod < 0xFF) {
              func_8003B47C(moby, 0x63, 6);
              break;
            }
            moby->m_State = 3;
            MOBY_ANIM_CHANGE(moby, 3);
            continue;
          }
          break;
        }

        if (props->m_0x10 == 1) {
          if (DISTANCE_TO_SPYRO(moby) < 0x2800 && g_Spyro.m_airTime == 0 &&
              moby->m_AnimationState.m_NextAnimation != 7) {
            moby->m_State = 10;
            continue;
          }

          switch (props->m_0x20) {
          case 0: {
            int result = func_80039E94(moby, props->m_0x0c, 0x200, 110, 0, 8,
                                       0x80, 0xFF, 5);

            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            if (result == 0x108) {
              props->m_0x20 = 1;
              props->m_0x00 = 0;
              props->m_0x04 = 0;
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
            }
            break;
          }

          case 1: {
            Moby *linkedMoby = &g_LevelMobys[props->m_0x08];
            int angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);

            RotateMobyToAngle(moby, angle, 6, 0, 0);
            if (TICK_TIMER(props->m_0x00) &&
                moby->m_AnimationState.m_NextFrame >= 6 && props->m_0x04 < 3) {
              Moby *spawned = g_SpawnMoby(295, moby);
              Vector3D targetPosition;
              Moby295Props *spawnedProps = spawned->m_Props;

              VecCopy(&targetPosition, &linkedMoby->m_Position);
              targetPosition.z += 700;
              spawned->m_Rotation.y =
                  Atan2(OctDistance(&moby->m_Position, &targetPosition),
                        targetPosition.z - moby->m_Position.z, 0);
              spawned->m_Rotation.z =
                  ANGLE_FROM(moby->m_Position, targetPosition);
              spawned->m_RenderRadius = 0x24;
              spawnedProps->m_0x00 = linkedMoby;
              spawnedProps->m_0x04 = 0xF;
              props->m_0x00 = 4;
              props->m_0x04++;
            }
            if (g_AnimationFinished) {
              props->m_0x20 = 0;
            }
            break;
          }

          case 2:
            if (TICK_TIMER(props->m_0x00)) {
              if (moby->m_AnimationState.m_NextAnimation != 6 &&
                  moby->m_AnimationState.m_Animation != 7) {
                g_AnimationFinished = 0;
                MOBY_ANIM_RESTART(moby, 7);
              }
              if (g_AnimationFinished) {
                if (moby->m_AnimationState.m_Animation != 1) {
                  g_AnimationFinished = 0;
                  MOBY_ANIM_RESTART(moby, 1);
                }
                props->m_0x20 = 0;
              }
            }
            break;
          }
        }
        break;

      case 1:
        if (g_AnimationFinished) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          moby->m_State = 0;
          continue;
        }
        break;
      case 2:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);
        if (g_AnimationFinished) {
          props->m_0x1c = 1;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 3:
        RotateMobyToSpyro(moby, 8, 0, 0);
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
        if (g_AnimationFinished) {
          props->m_0x00 = 0;
          props->m_0x04 = 0;
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;

      case 4:
        RotateMobyToSpyro(moby, 8, 0, 0);
        if (OctDistance(&g_Spyro.m_Position, &PATH_NODE_POS(props->m_0x0c, 0)) >
                props->m_0x18 + 0x400 &&
            DISTANCE_TO_SPYRO(moby) > 0x1800) {
          if (props->m_0x1c != 0) {
            props->m_0x00 = 0x5A;
            moby->m_State = 97;
            continue;
          }
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        if (TICK_TIMER(props->m_0x00) &&
            moby->m_AnimationState.m_NextFrame >= 6 && props->m_0x04 < 3) {
          Moby *spawned = g_SpawnMoby(295, moby);

          if (DISTANCE_TO_SPYRO(moby) < 0xA00 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 0x400) {
            VecCopy(&spawned->m_Position, &g_Spyro.m_Position);
          }
          props->m_0x00 = 4;
          props->m_0x04++;
        }

        if (g_AnimationFinished) {
          if (DISTANCE_TO_SPYRO(moby) < props->m_0x18) {
            if (moby->m_Pod == 0xFF) {
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
              continue;
            }
            func_8003B47C(moby, 0x63, 6);
          }
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 6:
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;

      case 10: {
        Moby *linkedMoby = &g_LevelMobys[props->m_0x08];
        int *linkedProps = linkedMoby->m_Props;
        Moby *secondMoby = &g_LevelMobys[linkedProps[2]];
        int *secondProps = secondMoby->m_Props;

        props->m_0x10 = 0;
        props->m_0x00 = 0x3C;
        linkedProps[4] = 0;
        linkedProps[6] = 0x3C;
        VecCopy(&secondMoby->m_Position, &linkedMoby->m_Position);
        secondMoby->m_Position.z += 0x200;
        secondProps[0] = -1;
        moby->m_State = 1;
        continue;
      }

      case 96:
        if (TICK_TIMER(props->m_0x00)) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;

      case 97:
        if (TICK_TIMER(props->m_0x00)) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;

      case 98:
        if (moby->m_AnimationState.m_NextAnimation == 0) {
          props->m_0x00 = rand() & 0xF;
          moby->m_State = 96;
          continue;
        }
        moby->m_State = moby->m_AnimationState.m_NextAnimation;
        break;

      case 99:
        props->m_0x1c = 1;
        if (moby->m_AnimationState.m_NextAnimation == 0) {
          props->m_0x00 = props->m_0x30;
          moby->m_State = 97;
          continue;
        }
        moby->m_State = moby->m_AnimationState.m_NextAnimation;
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_328
    case 328: { // Druid moveable geometry helper?
      Moby328Props *props = moby->m_Props;
      Vector3D vertices[3];

      // Finds closest collision tri below and centers on it
      if (props->m_CollisionTriIndex < 0) {
        int floorHeight;
        int floorDelta;

        moby->m_Position.z += 0x200;
        floorHeight = func_8004D5EC(&moby->m_Position, 0x400);
        floorDelta = moby->m_Position.z - floorHeight;
        if (floorDelta < 0) {
          floorDelta = -floorDelta;
        }
        if (floorDelta < 0x400) {
          moby->m_Position.z = floorHeight;
          props->m_CollisionTriIndex = g_CollisionTriangleIndex;
        } else {
          moby->m_Position.z -= 0x200;
        }
        if (props->m_CollisionTriIndex < 0) {
          break;
        }
      }

      ColTriUnpack(props->m_CollisionTriIndex, vertices);

      VecCopy(&moby->m_Position, &vertices[0]);
      VecAdd(&moby->m_Position, &moby->m_Position, &vertices[1]);
      VecAdd(&moby->m_Position, &moby->m_Position, &vertices[2]);

      moby->m_Position.x /= 3;
      moby->m_Position.y /= 3;
      moby->m_Position.z /= 3;
      break;
    }
#endif
#ifdef HAS_MOBY_329
    case MOBYCLASS_SPRING_CHEST: {
      Moby329Props *props;

      int i;

      props = (Moby329Props *)moby->m_Props;
      moby->m_SoundDistance = 0x20;

      switch (moby->m_State) {
      case 0:
        if (moby->m_Substate == 0) {
          ((int *)&moby->m_SpecularMetalColor)[0] =
              D_8006E678[moby->m_DropMoby - MOBYCLASS_GEM_1];
          moby->m_Substate = 1;
          moby->m_UpdateDistance = 0x10;
        }

        if (moby->m_DamageFlags &
            (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) {
          props->m_0x04 = 0;
          props->m_0x08 = moby->m_Rotation.x;
          props->m_0x0c = moby->m_Rotation.y;
          props->m_0x10 = moby->m_Position.z;

          moby->m_UpdateDistance = 0x40;

          props->m_0x00 = (Moby *)func_8003ABC0(moby, 5, 0, 0);
          props->m_0x00->m_Substate = 4;
          props->m_0x00->m_RenderRadius = 0;
          props->m_0x00->m_WasDrawn = 0;
          props->m_0x00->m_Rotation.x = 0;
          props->m_0x00->m_Rotation.y = 0;

          g_SpawnParticle(8, 64, &moby->m_Position,
                          (props->m_0x00->m_Class - MOBYCLASS_GEM_1));

          func_8003851C(moby, 0, 0);

          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
          continue;
        }
        if (props->m_0x04 >= 0xF8) {
          SpawnMobySparkle(moby, &D_8006E5C4[(rand() & 3)]);
          props->m_0x04 = (rand() & 0x3F) + 0x18;
        }
        props->m_0x04 += g_DeltaTime;
        break;

      case 1: {
        props->m_0x00->m_RenderRadius = 0x18;
        VecCopy(&props->m_0x00->m_Position, &moby->m_Position);

        props->m_0x00->m_Position.z +=
            0x1A4 + Sin((props->m_0x04 << 11) / 90) / 3;

        props->m_0x00->m_Rotation.z += g_DeltaTime * 2;

        if (props->m_0x04 < 0x40) {
          moby->m_Rotation.x =
              props->m_0x08 + g_MobyShakeOffsets[props->m_0x04 >> 1][0];
          moby->m_Rotation.y =
              props->m_0x0c + g_MobyShakeOffsets[props->m_0x04 >> 1][1];

          moby->m_Position.z =
              props->m_0x10 +
              (ABS2(g_MobyShakeOffsets[props->m_0x04 >> 1][0]) +
               ABS2(g_MobyShakeOffsets[props->m_0x04 >> 1][1])) *
                  6;
        }

        if (props->m_0x04 < 0x20) {
          if ((props->m_0x04 & 3) <= ((props->m_0x04 + g_DeltaTime) & 3)) {
            Vector3D zero;
            VecNull(&zero);
            g_SpawnParticle(1, 0, &props->m_0x00->m_Position, (int)&zero);
          }
        }

        if ((DISTANCE_TO_SPYRO(props->m_0x00) < 480 &&
             (g_Spyro.m_Position.z - props->m_0x00->m_Position.z) > -0xE0 &&
             (g_Spyro.m_Position.z - props->m_0x00->m_Position.z) < 480) ||
            g_Spyro.m_State == 0x2C || g_Spyro.m_State == 0x18 ||
            (g_Spyro.m_State == 0x14 && (g_Spyro.m_walkingState & 0x40))) {
          CollectItem(props->m_0x00);
          func_80052568(props->m_0x00);

          func_8003851C(moby, 2, 0);

          for (i = 0; i < 2 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(67, moby);
            g_SpawnMoby(68, moby);
          }

          for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(69, moby);
          }

          g_SpawnParticle(5, 2, &moby->m_Position, 0);
          g_SpawnParticle(16, 70, &moby->m_Position, 0x20);
          func_80052568(moby);
          continue;
        }

        if (moby->m_DamageFlags & MOBY_DAMAGE_SUPER) {
          props->m_0x00->m_Substate = 2;

          func_8003851C(moby, 2, 0);

          for (i = 0; i < 2 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(67, moby);
            g_SpawnMoby(68, moby);
          }

          for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(69, moby);
          }

          g_SpawnParticle(5, 2, &moby->m_Position, 0);
          g_SpawnParticle(16, 70, &moby->m_Position, 0x20);
          func_80052568(moby);
          continue;
        }

        props->m_0x04 += g_DeltaTime;

        if (props->m_0x04 >= 0x56) {
          Vector3D particlePosition;
          Vector3D particleVelocity;
          int i;
          for (i = 0; i < 6; i++) {
            VecCopy(&particlePosition, &props->m_0x00->m_Position);

            particlePosition.x += COSINE_8(i * 43) >> 6;
            particlePosition.y += SINE_8(i * 43) >> 6;
            particlePosition.z += 40;

            particleVelocity.x = COSINE_8(i * 43) >> 7;
            particleVelocity.y = SINE_8(i * 43) >> 7;
            particleVelocity.z = 16;

            g_SpawnParticle(1, 0, &particlePosition, (int)&particleVelocity);
          }

          func_80052568(props->m_0x00);

          moby->m_DroppedFlag &= 0x7F;
          moby->m_UpdateDistance = 0x10;

          moby->m_Rotation.x = props->m_0x08;
          moby->m_Rotation.y = props->m_0x0c;
          moby->m_Position.z = props->m_0x10;

          props->m_0x04 = 0;
          func_8003851C(moby, 1, 0);
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
          continue;
        }

        break;
      }
      }
      moby->m_DamageFlags = 0;
      break;
    }
#endif
#if defined(HAS_MOBY_331) || defined(HAS_MOBY_332) || defined(HAS_MOBY_333)
#ifdef HAS_MOBY_331
    case 331: // Artisans, Beast Makers,
              // Gnasty's World Dragon Pad
#endif
#ifdef HAS_MOBY_332
    case 332: // Peacekeepers Dragon Pad
#endif
#ifdef HAS_MOBY_333
    case 333: // Magic Crafters Dragon Pad
#endif
    { // Dragon pad
      switch (moby->m_State) {
      case 0: {
        if (DISTANCE_TO_SPYRO(moby) > 2560) {
          moby->m_State = 1;
        }
        break;
      }

      case 1: {
        if (DISTANCE_TO_SPYRO(moby) < 896 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 512) {

          // Save checkpoint
          CheckpointSave(moby, moby->m_Rotation.z);
          moby->m_State = 2;
          moby->m_AnimationState.m_Animation = 1;
          moby->m_Substate = 0;
        }
        break;
      }

      case 2: {
        moby->m_Substate += g_DeltaTime;

        if (moby->m_Substate >= 0x30) {
          moby->m_State = 0;
          moby->m_AnimationState.m_Animation = 0;
        }
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_335
    case 335: {
      Moby335Props *props;
      Vector3D vec;
      int dist;
      int angle;
      int floorZ;
      int spyroDist;

      props = (Moby335Props *)moby->m_Props;
      dist = DISTANCE_TO_SPYRO(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 4 && (moby->m_State < 13 || moby->m_State > 15)) {
        if (props->m_0x30 == 0) {
          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);
          props->m_0x50 = 0xE6;
          angle = ANGLE_FROM_SPYRO(moby->m_Position);
          props->m_0x4c =
              func_80038178(angle, g_Spyro.m_bodyRotation.z, 0x20, 0x40);
          props->m_0x54 = 0x14;
          moby->m_State = 4;
          continue;
        }

        if (props->m_0x04 == 0) {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          func_800381BC(moby->m_Rotation.z, angle);
          props->m_0x30--;
          props->m_0x2c += 7;
          moby->m_State = 13;
          MOBY_ANIM_RESTART(moby, 13);
          continue;
        }

        if (props->m_0x04 >= 0) {
          if (props->m_0x04 < 4) {
            angle = ANGLE_TO_SPYRO(moby->m_Position);
            func_800381BC(moby->m_Rotation.z, angle);
            *props->m_0x40 = 1;
            props->m_0x30--;
            props->m_0x2c += 7;
            props->m_0x34 = moby->m_Rotation.z;
            VecCopy(&props->m_0x08, &moby->m_Position);
            moby->m_State = 13;
            MOBY_ANIM_RESTART(moby, 13);
            continue;
          }
        }
      }

      moby->m_DamageFlags = 0;
      VecCopy(&vec, &moby->m_Position);
      vec.z += 0x400;

      if (!func_8004D5EC(&vec, 0x1000)) {
        func_8003ABC0(moby, 4, 0, 0);
        func_8003B7C0(moby);
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        func_800385BC(moby, 0x18);
        func_80052568(moby);
        continue;
      }

      if (!TICK_TIMER(props->m_0x5c)) {
        g_Spyro.m_DamageFlags |= 0x13;
      }

      if (TICK_TIMER(props->m_0x48) && dist < 2200 && moby->m_State == 0) {
        VecCopy(&props->m_0x14, &g_Spyro.m_Position);
        props->m_0x48 = 0;
        moby->m_Substate = 0;
        moby->m_State = 1;
        continue;
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x34 == -1) {
          props->m_0x34 = moby->m_Rotation.z;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x2c);
        break;

      case 1:
        props->m_0x54 = ((DISTANCE_TO_SPYRO(moby) * 35) >> 10) + 300;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x2c + 2);

        angle = ANGLE_FROM(moby->m_Position, props->m_0x14);

        if (RotateMobyToAngle(moby, angle, 0xA, 4, 1)) {
          func_8003851C(moby, 1, 0);
          moby->m_State = 2;
          continue;
        }
        break;

      case 2:
        floorZ = func_80038340(moby);
        moby->m_Position.z += props->m_0x54;
        props->m_0x54 -= 0x32;

        if (props->m_0x54 < -600) {
          props->m_0x54 = -600;
        }

        if (g_Spyro.m_State == 0x19) {
          props->m_0x5c = 0x1E;
        }

        if (floorZ + moby->m_FloorDistance >= moby->m_Position.z) {
          if (moby->m_Substate == 0) {
            func_8003851C(moby, 0, 0);
            moby->m_Substate = 1;
          }

          if (moby->m_AnimationState.m_NextFrame < 0x0D) {
            moby->m_AnimationState.m_Frame = 0x0D;
            moby->m_AnimationState.m_NextFrame = 0x0E;
            moby->m_AnimationState.m_FrameProgress = 0;
          }

          moby->m_Position.z = floorZ + moby->m_FloorDistance;

          if (moby->m_AnimationState.m_NextFrame >= 0x18) {
            if (DISTANCE_TO_SPYRO(moby) < 900) {
              moby->m_CollisionGroup = 0;
            }

            if (moby->m_AnimationState.m_NextAnimation != props->m_0x2c + 1) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby, props->m_0x2c + 1);
            }

            moby->m_State = 100;
            continue;
          }
        } else {
          spyroDist = DISTANCE_TO_SPYRO(moby);

          if (moby->m_AnimationState.m_NextFrame == 0x0D) {
            moby->m_AnimationState.m_Frame = 8;
            moby->m_AnimationState.m_NextFrame = 9;
            moby->m_AnimationState.m_FrameProgress = 0;
          }

          if (spyroDist > 0x50 && spyroDist < 800 && props->m_0x54 < 100 &&
              moby->m_Position.z - floorZ > 500) {
            angle = ANGLE_TO_SPYRO(moby->m_Position);
            func_80039688(moby, angle, 0x50, 0, 0, 0);
          } else if (OctDistance(&moby->m_Position, &props->m_0x14) >= 0x97) {
            func_80039398(moby, 0xE6, 0, 300, 0);
          }

          if (spyroDist < 700 &&
              moby->m_Position.z < g_Spyro.m_Position.z - 200) {
            g_Spyro.m_Position.z = moby->m_Position.z + 200;
          }
        }
        break;

      case 4:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x2c + 4);

        MoveMobyWithGravity(moby, &props->m_0x50, props->m_0x4c, &props->m_0x54,
                            0xC, 0xA);

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        break;

      case 10:
        if (moby->m_AnimationState.m_NextAnimation >= 12) {
          if (moby->m_AnimationState.m_Animation != props->m_0x2c + 5) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, props->m_0x2c + 5);
          }
        } else if (moby->m_AnimationState.m_NextAnimation !=
                   props->m_0x2c + 5) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, props->m_0x2c + 5);
        }

        if (g_AnimationFinished) {
          func_800385BC(moby, 0x18);
          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);
          func_80052568(moby);
          continue;
        }
        break;

      case 13:
        if (moby->m_AnimationState.m_NextFrame < 2) {
          VecCopy(&props->m_0x14, &g_Spyro.m_Position);
        }

        angle = ANGLE_FROM(moby->m_Position, props->m_0x14);
        RotateMobyToAngle(moby, angle, 7, 0, 0);

        if (moby->m_AnimationState.m_NextFrame >= 9) {
          if (moby->m_AnimationState.m_Animation != props->m_0x2c + 1) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, props->m_0x2c + 1);
          }

          props->m_0x48 = 0;
          moby->m_Substate = 0;
          moby->m_State = 1;
          continue;
        }
        break;

      case 14:
      case 15:
        if (moby->m_AnimationState.m_NextFrame >= 9) {
          if (moby->m_AnimationState.m_Animation != props->m_0x2c + 1) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, props->m_0x2c + 1);
          }

          moby->m_State = 1;
          continue;
        }
        break;

      case 20:
        props->m_0x38 = 1;
        moby->m_State = 0;
        continue;

      case 100:
        if (OctDistance(&moby->m_Position, &props->m_0x08) < 0xB4) {
          if (RotateMobyToAngle(moby, props->m_0x34, 6, 5, 1)) {
            *props->m_0x40 = 0;
            props->m_0x48 = 0x78;
            moby->m_State = 0;
            continue;
          }
        } else {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, props->m_0x2c + 1);

          angle = ANGLE_FROM(moby->m_Position, props->m_0x08);

          if (RotateMobyToAngle(moby, angle, 6, 0x14, 1)) {
            func_80039398(moby, 0x82, 0, 0, 5);
          }
        }
        break;
      }

      if (moby->m_State == 2 || DISTANCE_TO_SPYRO(moby) > 900) {
        func_800529E4(moby, UPDATE_PROP_COLLISION);
        break;
      }

      if (moby->m_CollisionGroup != 0) {
        break;
      }

      if (OctDistance(&g_Spyro.m_Position, &props->m_0x08) < 1000) {
        if (TICK_TIMER(props->m_0x58)) {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          g_Spyro.unk_0x208.x = FIXED_MUL(COSINE_8(angle), 100);
          g_Spyro.unk_0x208.y = FIXED_MUL(SINE_8(angle), 100);
          g_Spyro.unk_0x208.z = 0;
          props->m_0x58 = 0x10;
        } else {
          g_Spyro.m_ControlFlags = 0x80000043;
        }
      }

      break;
    }
#endif
#if defined(HAS_MOBY_336) || defined(HAS_MOBY_342)
#ifdef HAS_MOBY_336
    case 336:
#endif
#ifdef HAS_MOBY_342
    case 342:
#endif
    {
      if (g_AnimationFinished) {
        int progress =
            g_Models[moby->m_Class]
                ->m_Animations[moby->m_AnimationState.m_NextAnimation]
                ->m_ProgressPerTick;
        moby->m_AnimationState.m_PerFrameProgress = progress + RandRange(-4, 4);
      }

      if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0 &&
          moby->m_AnimationState.m_NextAnimation == 0) {
        if (moby->m_AnimationState.m_Animation != 1) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 1);
        }
        break;
      }

      if (moby->m_AnimationState.m_NextAnimation != 1) {
        break;
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);

      if (g_AnimationFinished && moby->m_AnimationState.m_Animation != 2) {
        g_AnimationFinished = 0;
        MOBY_ANIM_RESTART(moby, 2);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_339
    case 339: {
      Moby339Props *props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State < 4) {
        while (props->m_0x10 >= 0 &&
               g_LevelMobys[props->m_0x10].m_State >= 0x80) {
          props->m_0x10 = *(int *)g_LevelMobys[props->m_0x10].m_Props;
        }

        if (props->m_0x10 >= 0) {
          Moby *linkedMoby = &g_LevelMobys[props->m_0x10];
          int *linkedProps = linkedMoby->m_Props;

          VecCopy(&linkedMoby->m_Position, &moby->m_Position);
          func_8003ABC0(linkedMoby, 1, 0, 0);
          func_8003B7C0(linkedMoby);
          props->m_0x10 = *linkedProps;
          func_80052568(linkedMoby);
          moby->m_DamageFlags = 0;
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        } else {
          int count = 0;

          while (props->m_0x14 >= 0) {
            Moby *linkedMoby = &g_LevelMobys[props->m_0x14];
            int *linkedProps = linkedMoby->m_Props;

            if (linkedMoby->m_State < 0x80) {
              VecCopy(&linkedMoby->m_Position, &moby->m_Position);
              props->m_0x18[count].x =
                  moby->m_Position.x + (Cos(count * 0x555) >> 2);
              props->m_0x18[count].y =
                  moby->m_Position.y + (Sin(count * 0x555) >> 2);
              props->m_0x18[count].z = moby->m_Position.z;
              func_8003ABC0(linkedMoby, 2, 0, &props->m_0x18[count]);
              count++;
              func_8003B7C0(linkedMoby);
              func_80052568(linkedMoby);
            }

            props->m_0x14 = *linkedProps;
          }

          props->m_0x18[count].x =
              moby->m_Position.x + (Cos(count * 0x555) >> 2);
          props->m_0x18[count].y =
              moby->m_Position.y + (Sin(count * 0x555) >> 2);
          props->m_0x18[count].z = moby->m_Position.z;
          func_8003ABC0(moby, 2, 0, &props->m_0x18[count]);
          func_8003B7C0(moby);
          props->m_0x04 = 0x118;
          props->m_0x00 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
          moby->m_State = 5;
          MOBY_ANIM_RESTART(moby, 5);
          continue;
        }
      }

      switch (moby->m_State) {
      case 0: {
        int distance = DISTANCE_TO_SPYRO(moby);

        if (distance < 0x1400 && SPYRO_BASE_Z_DISTANCE(moby) < 0x400) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }

        if (distance < 0x2800) {
          RotateMobyToSpyro(moby, 8, 0x10, 1);
        }
        break;
      }

      case 1: {
        RotateMobyToSpyro(moby, 8, 0x10, 1);

        if (g_AnimationFinished) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      }

      case 2:
      case 3:
      case 4: {
        int spyroAngle;
        int angle;
        int previousAngle;
        int nextNode;
        int previousNode;
        int nextAngle;

        if (moby->m_State == 4) {
          moby->m_DamageFlags = 0;
        }

        if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x08)) <
            0x400) {
          if (DISTANCE_TO_SPYRO(moby) > 0x1400 ||
              SPYRO_BASE_Z_DISTANCE(moby) > 0x800) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          } else {
            spyroAngle = ANGLE_TO_SPYRO(moby->m_Position);
            nextNode =
                (props->m_0x08->m_CurrentNode + 1) % props->m_0x08->m_NodeCount;
            previousNode = (props->m_0x08->m_CurrentNode - 1 +
                            props->m_0x08->m_NodeCount) %
                           props->m_0x08->m_NodeCount;

            nextAngle = ANGLE_FROM(moby->m_Position,
                                   PATH_NODE_POS(props->m_0x08, nextNode)),
            previousAngle = ANGLE_FROM(
                moby->m_Position, PATH_NODE_POS(props->m_0x08, previousNode));

            if (func_80017908(spyroAngle, nextAngle) >
                func_80017908(spyroAngle, previousAngle)) {
              props->m_0x08->m_CurrentNode = nextNode;
            } else {
              props->m_0x08->m_CurrentNode = previousNode;
            }
          }
        }

        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x08));
        previousAngle = (angle - moby->m_Rotation.z) & 0xFF;
        if (previousAngle > 0x80) {
          previousAngle -= 0x100;
        }
        nextAngle = previousAngle;

        if (previousAngle > 8) {
          previousAngle = 8;
        }
        if (previousAngle < -8) {
          previousAngle = -8;
        }
        moby->m_Rotation.z += previousAngle;

        if (ABS2(nextAngle) < 0x20) {
          if (moby->m_State == 4) {
            func_80039398(moby, 0xD2, 0x200, 0x200, 0x27);
          } else {
            func_80039398(moby, 0x60, 0x200, 0x200, 0x27);
          }
        }

        if (g_AnimationFinished) {
          if (moby->m_State == 2) {
            moby->m_State = 3;
            MOBY_ANIM_RESTART(moby, 3);
          } else {
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
          }
          continue;
        }
        break;
      }
      case 5: {
        func_800529E4(moby, UPDATE_PROP_COLLISION);

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x20);
          func_80052568(moby);
          continue;
        }

        MoveMobyWithGravity(moby, &props->m_0x04, props->m_0x00, 0, 0xC, 0);
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_340
    case 340: {
      Moby340Props *props = moby->m_Props;
      Vector3D delta;

      if (g_FlightCourseRecords[g_Homeworld] == 0 &&
          props->m_TimeRewardMoby == 0) {
        props->m_TimeRewardMoby =
            g_SpawnMoby(props->m_TimeRewardMobyIndex + 344, moby);
        moby->m_Rotation.x = -moby->m_AnimationState.m_Animation << 6;
      }

      moby->m_Rotation.x = func_80038074(moby->m_Rotation.x, 8);
      if (moby->m_Rotation.x < 8) {
        func_8003851C(moby, 0, 0);
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX);

      if (DISTANCE_TO_SPYRO(moby) < 3000) {
        if (SPYRO_BASE_Z_DISTANCE(moby) < 3000) {
          VecSub(&delta, &moby->m_Position, &g_Spyro.m_Position);

          if (VecMagnitude(&delta, 1) < 2500 &&
              func_80038D54(&g_Spyro.m_Position, &props->m_CollectionPlane) <
                  0x200) {
            RegisterFlightMobyCollectibleType(props->m_RingCollectableIndex);

            if (props->m_TimeRewardMoby != 0) {
              props->m_TimeRewardMoby->m_State = 1;
            } else {
              PlaySound(g_Spu.m_SoundTable->flightCollected, moby, 0x10, 0);
            }

            func_80052568(moby);
          }
        }
      }

      break;
    }
#endif
#ifdef HAS_MOBY_343
    case 343: {
      Moby343Props *props = moby->m_Props;

      switch (moby->m_State) {
      case 0:
        props->m_0x04 = moby->m_Substate * -10 - (moby->m_Substate << 5);
        moby->m_State = 1;
        moby->m_RenderRadius = 0;
        break;

      case 1:
        props->m_0x04 += g_DeltaTime;
        if (props->m_0x04 >= 0) {
          moby->m_State = 2;
        }
        break;

      case 2: {
        Vector3D delta;
        Vector3D point0;
        Vector3D point1;
        int blend;

        moby->m_RenderRadius = 0x20;
        props->m_0x04 += g_DeltaTime;
        blend = (props->m_0x04 << 5) & 0x3FF;
        func_80052D64(props->m_0x00, 0, &point0);
        func_80052D64(props->m_0x00, 1, &point1);
        VecSub(&delta, &point1, &point0);
        moby->m_Rotation.y = Atan2(VecMagnitude(&delta, 0), delta.z, 0);
        moby->m_Rotation.z = Atan2(delta.x, delta.y, 0);
        point0.x *= blend;
        point0.y *= blend;
        point0.z *= blend;
        point1.x *= 0x400 - blend;
        point1.y *= 0x400 - blend;
        point1.z *= 0x400 - blend;
        VecAdd(&moby->m_Position, &point0, &point1);
        VecShiftRight(&moby->m_Position, 10);
        moby->m_ScaleOverride = (blend >> 5) + 0x18;
        break;
      }

      case 3:
        func_80052568(moby);
        continue;
      }
      break;
    }
#endif
#if defined(HAS_MOBY_345) || defined(HAS_MOBY_346) || defined(HAS_MOBY_347)
#ifdef HAS_MOBY_345
    case 345:
#endif
#ifdef HAS_MOBY_346
    case 346:
#endif
#ifdef HAS_MOBY_347
    case 347:
#endif
    {
      Moby345Props *props;

      props = moby->m_Props;

      switch (moby->m_State) {
      case 0: {
        if (g_FlightCourseRecords[g_Homeworld] != 0) {
          func_80052568(moby);
        } else {
          int angle =
              func_80038074(ANGLE_TO_SPYRO(moby->m_Position), ROTDEG8(90));
          RotateMobyToAngle(moby, angle, 4, 0, 0);
        }
        break;
      }
      case 1:
        D_80075908 += (moby->m_Class - 344) * 60;
        func_80017AA4(&moby->m_Position, &moby->m_Position);
        moby->m_Rotation.z = 0xC0;
        moby->m_Rotation.x = 0;
        moby->m_Rotation.y = 0;
        moby->m_RenderRadius = 0xFF;
        moby->m_DepthOffset = 0x20;
        moby->m_State = 2;
        PlaySound(g_Spu.m_SoundTable->flightCollected, moby, 0x10, 0);
        break;
      case 2: {
        Vector3D delta;
        int distance;

        delta.x = 420;
        delta.y = 0x30;
        delta.z = 5500;
        VecSub(&delta, &delta, &moby->m_Position);
        distance = VecMagnitude(&delta, 1);

        if (distance < 0x20) {
          moby->m_State = 3;
          moby->m_Position.x = 0x1A4;
          moby->m_Position.y = 0x30;
          moby->m_Position.z = 5500;
          props->m_0x00 = 0x1E;
        } else {
          if (distance > 0x80) {
            VecScaleToLength(&delta, distance, 0x80);
          }
          VecAdd(&moby->m_Position, &moby->m_Position, &delta);
        }

        break;
      }
      case 3:
        if (TICK_TIMER(props->m_0x00)) {
          D_80075840 += (moby->m_Class - 344) * 60;
          PlaySound(g_Spu.m_SoundTable->flightTimeAdded, moby, 0x10, 0);
          func_80052568(moby);
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_349
    case 349: {
      Moby349Props *props;
      int dist;

      props = (Moby349Props *)moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 7) {
        func_8003B728(moby, 1);
        props->m_0x08 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x0c = 0x190;

        if (moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) {
          props->m_0x0c = 500;
        }

        props->m_0x10 = RandRange(2, 5);

        if (rand() & 1) {
          props->m_0x10 = -props->m_0x10;
        }

        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 7;
        MOBY_ANIM_CHANGE(moby, 7);
        continue;
      }

      switch (moby->m_State) {
      case 0:
        if (g_AnimationFinished) {
          if (props->m_0x00 == 0) {
            props->m_0x00 = RandRange(3, 6);

            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          } else {
            props->m_0x00--;

            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          }
        }

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (TICK_TIMER(props->m_0x04)) {
          if (DISTANCE_TO_SPYRO(moby) < 0x2000) {
            if (moby->m_AnimationState.m_Animation == 0) {
              moby->m_State = 2;
              MOBY_ANIM_CHANGE(moby, 2);
            } else {
              moby->m_State = 3;
              MOBY_ANIM_CHANGE(moby, 3);
            }

            continue;
          }
        }
        break;

      case 2:
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        break;

      case 3:
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;

      case 4:
        dist = DISTANCE_TO_SPYRO(moby);

        if (g_AnimationFinished) {
          if (dist > 0xC00) {
            if (props->m_0x00 == 0) {
              props->m_0x00 = RandRange(3, 6);

              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 10);
            } else {
              props->m_0x00--;

              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
            }
          } else if (moby->m_AnimationState.m_NextAnimation != 4) {
            g_AnimationFinished = 0;
            MOBY_ANIM_ADVANCE(moby, 4);
          }
        }

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (dist < 3000 && SPYRO_BASE_Z_DISTANCE(moby) < 1200) {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
          continue;
        }

        if (dist > 0x2400) {
          moby->m_State = 6;
          MOBY_ANIM_CHANGE(moby, 6);
          continue;
        }
        break;

      case 5:
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (g_Spyro.m_State == 0x16) {
          props->m_0x04 = 0x8C;
        }

        if (g_AnimationFinished) {
          if (props->m_0x04 == 0) {
            moby->m_State = 4;
            MOBY_ANIM_CHANGE(moby, 4);
          } else {
            moby->m_State = 8;
            MOBY_ANIM_CHANGE(moby, 8);
          }

          continue;
        }

        g_Spyro.unk_0x208.x = FIXED_MUL(SINE_8(moby->m_Rotation.z), 0x80);
        g_Spyro.unk_0x208.y = FIXED_MUL(COSINE_8(moby->m_Rotation.z), -0x80);
        g_Spyro.unk_0x208.z = 0;
        break;

      case 6:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 7:
        if (moby->m_AnimationState.m_Frame < 10) {
          moby->m_Rotation.z += props->m_0x10;
        }

        if (props->m_0x0c >= 0x1F) {
          props->m_0x0c -= 0x1E;
          func_80039688(moby, props->m_0x08, props->m_0x0c, 0, 300, 1);
        }

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x20);
          func_80052568(moby);
          continue;
        }
        break;

      case 8:
        if (moby->m_AnimationState.m_Frame >= 0x1C) {
          if (TICK_TIMER(props->m_0x04)) {
            moby->m_AnimationState.m_Frame = 0x0F;
          }
        }

        if (g_AnimationFinished) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          continue;
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_350
    case 350: {
      Moby350Props *props = moby->m_Props;

      if (props->m_0x08 == 0) {
        if (g_VisitedFlags[5] != 0) {
          func_8002B390(props->m_0x00, 0xFC, 0);
          func_8002B444(props->m_0x00, 0x77, 0);
          moby->m_State = 99;
        }
        props->m_0x08 = 1;
      }

      switch (moby->m_State) {
      case 0: {
        if (moby->m_Substate == 0x1F) {
          moby->m_State = 5;
        }
        break;
      }

      case 5: {
        func_8002B390(props->m_0x00, 0xFC, 0);
        moby->m_State = 10;
        props->m_0x04 = 0x1E;
        moby->m_SoundDistance = 0x30;
        PlaySound(g_Spu.m_SoundTable->sound_0x41, moby, 8,
                  &moby->m_SoundChannel);
        break;
      }

      case 10: {
        if ((func_8002B3F4(props->m_0x00) & 2) != 0) {
          moby->m_State = 99;
        } else if (TICK_TIMER(props->m_0x04)) {
          moby->m_State = 11;
          props->m_0x04 = 0x1E;
        }
        break;
      }

      case 11: {
        if ((func_8002B3F4(props->m_0x00) & 2) != 0) {
          moby->m_State = 99;
        } else if (TICK_TIMER(props->m_0x04)) {
          moby->m_State = 10;
          props->m_0x04 = 0x1E;
        }
        break;
      }

      case 99: {
        func_800562A4(moby, 1);
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_353
    case 353: {
      Moby353Props *props;
      Moby374Props *fragmentProps;
      int color;

      props = moby->m_Props;

      if (g_FlightCourseRecords[g_Homeworld] == 0 && props->m_0x10 == 0) {
        props->m_0x10 = g_SpawnMoby(props->m_0x14 + 344, moby);
      }

      if (DISTANCE_TO_SPYRO(moby) < 3000 &&
          SPYRO_BASE_Z_DISTANCE(moby) < 4000) {
        Vector3D delta;
        Vector3D randomVelocity;

        VecSub(&delta, &moby->m_Position, &g_Spyro.m_Position);

        randomVelocity.z = (delta.z - 0xC0) << 2;
        delta.z = (randomVelocity.z - delta.z) >> 2;

        if (VecMagnitude(&delta, 1) < 1400 &&
            func_80038D54(&g_Spyro.m_Position, &props->m_CollectionPlane) <
                0x200) {
          int i;

          RegisterFlightMobyCollectibleType(props->m_0x18);

          if (props->m_0x10 != 0) {
            props->m_0x10->m_State = 1;
          }

          // Spawns Mobys 374 - 386
          for (i = 0; i < 13 && DYN_MOBY_FREE_COUNT > 20; i++) {
            Moby *fragment = g_SpawnMoby(374 + i, moby);
            fragmentProps = fragment->m_Props;

            VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix, &D_8006E824[i],
                              &delta);
            VecAdd(&fragment->m_Position, &moby->m_Position, &delta);
            VecShiftRight(&delta, 5);

            randomVelocity.x = (rand() & 0x7E) - 0x3F;
            randomVelocity.y = (rand() & 0x7E) - 0x3F;
            randomVelocity.z = (rand() & 0x7E) - 0x3F;

            VecAdd(&fragmentProps->m_0x00, &delta, &randomVelocity);
            VecAdd(&fragment->m_Position, &fragment->m_Position,
                   &fragmentProps->m_0x00);

            fragmentProps->m_0x0c = (rand() & 2) - 1;
            fragmentProps->m_0x0d = (rand() & 2) - 1;
            fragmentProps->m_0x0e = (rand() & 2) - 1;
            fragmentProps->m_0x10 = 0x3C;
          }

          func_8003851C(moby, 0, 0);
          func_80052568(moby);
          break;
        }
      }

      color = Cos(g_LevelTicks * 16);
      color = FIXED_MUL(ABS(color), 16);

      if (color >= 64) {
        color = 63;
      }

      ((int *)&moby->m_SpecularMetalColor)[0] = (color << 6) | 0xA00000;
      break;
    }
#endif
#ifdef HAS_MOBY_358
    case 358: {

      Moby358Props *props = moby->m_Props;

      int i;
      int time;
      int oldSeconds;
      int oldTenths;
      int seconds;

      VecCopy(&moby->m_Position, &g_Spyro.m_Position);

      if (props->m_0x24[0] == 0) {
        int hudClassOffset;
        int *propsCursor;

        D_80075908 = props->m_0x00;
        D_80075840 = props->m_0x00;
        D_800758F4 = 0;
        D_80075900 = 0;
        D_800770F8[0] = 0;
        g_FlightObjectiveCounters[0] = 0;
        D_800770F8[1] = 0;
        g_FlightObjectiveCounters[1] = 0;
        D_800770F8[2] = 0;
        g_FlightObjectiveCounters[2] = 0;
        D_800770F8[3] = 0;
        g_FlightObjectiveCounters[3] = 0;
        g_FlightObjectiveActiveSlots[3] = -1;
        g_FlightObjectiveActiveSlots[2] = -1;
        g_FlightObjectiveActiveSlots[1] = -1;
        g_FlightObjectiveActiveSlots[0] = -1;
        D_800757C4 = -1;
        D_800758F8 = -1;

        for (i = 3; i >= 0; i--) {
          props->m_0x04[i] = g_SpawnMoby(327, moby);
          props->m_0x04[i]->m_RenderRadius = 0xFF;
          props->m_0x04[i]->m_DepthOffset = 0x20;
          props->m_0x04[i]->m_Position.z = 0x1000;
          props->m_0x04[i]->m_Rotation.z = 0;
        }

        props->m_0x04[0]->m_Position.x = 400;
        props->m_0x04[0]->m_Position.y = 30;
        props->m_0x04[1]->m_Position.x = 420;
        props->m_0x04[1]->m_Position.y = 30;
        props->m_0x04[2]->m_Position.x = 436;
        props->m_0x04[2]->m_Position.y = 30;
        props->m_0x04[3]->m_Position.x = 452;
        props->m_0x04[3]->m_Position.y = 30;

        if (g_FlightCourseRecords[g_Homeworld] != 0) {
          for (i = 4; i < 8; i++) {
            props->m_0x04[i] = g_SpawnMoby(327, moby);
            props->m_0x04[i]->m_RenderRadius = 0xFF;
            props->m_0x04[i]->m_DepthOffset = 0x20;
            props->m_0x04[i]->m_Rotation.z = 0;
          }

          props->m_0x04[4]->m_Position.x = 384;
          props->m_0x04[4]->m_Position.y = 31;
          props->m_0x04[4]->m_Position.z = 0x1800;
          props->m_0x04[5]->m_Position.x = 384;
          props->m_0x04[5]->m_Position.y = 24;
          props->m_0x04[5]->m_Position.z = 0x1800;
          props->m_0x04[6]->m_Position.x = 368;
          props->m_0x04[6]->m_Position.y = 30;
          props->m_0x04[6]->m_Position.z = 0x1000;
          props->m_0x04[7]->m_Position.x = 468;
          props->m_0x04[7]->m_Position.y = 30;
          props->m_0x04[7]->m_Position.z = 0x1000;
        }

        for (i = 0; i < 8; i++) {
          props->m_0x24[i] =
              g_SpawnMoby(props->m_0x64.fields.m_ObjectiveClasses[0], moby);
        }

        // TODO: Clean this up...
        i = 0;
        propsCursor = (int *)props;
        hudClassOffset = 0;
        for (; i < 4; propsCursor++, i++, hudClassOffset += sizeof(int)) {
          *(int *)((char *)D_8006E3E4 + hudClassOffset) =
              propsCursor[OFFSET(Moby358Props, m_0x84) / sizeof(int)];
        }

        for (i = 0; i < 4; i++) {
          g_Hud.m_Mobys[i].m_Class = props->m_0x64.fields.m_ObjectiveClasses[i];
          func_8003A720(&g_Hud.m_Mobys[i]);
          func_800529CC(&g_Hud.m_Mobys[i]);
          g_Hud.m_Mobys[i].m_Position.y = 60 + i * 20;
          g_Hud.m_Mobys[i].m_DepthOffset = 0x20;
          g_Hud.m_Mobys[i].m_RenderRadius = 0xFF;
          g_Hud.m_Mobys[i].m_Position.x = 60;
          g_Hud.m_Mobys[i].m_Position.z = 0x1000;
          g_Hud.m_Mobys[i].m_SpecularMetalType = i + 3;
        }
      }

      if (g_FlightCourseRecords[g_Homeworld] != 0) {
        time = D_800758F4;
      } else {
        time = D_80075840;
      }

      if (time < 0) {
        time = 0;
      }

      oldSeconds = time / 60;
      oldTenths = time / 6;

      if (g_FlightObjectiveCounters[0] + g_FlightObjectiveCounters[1] +
              g_FlightObjectiveCounters[2] + g_FlightObjectiveCounters[3] !=
          0x20) {
        if (D_800756A0 == 0 && g_Spyro.m_walkingState < 8 &&
            g_FlightCourseRecords[g_Homeworld] == 0) {
          D_80075908 -= g_DeltaTime;
          D_80075840 -= g_DeltaTime;
          if (D_80075908 < 0) {
            D_80075694();
          }
        }

        D_800758F4 += g_DeltaTime;
        if (D_800758F4 >= 10 * 60 * 60) { // 10 Minutes
          D_800758F4 = 10 * 60 * 60 - 1;  // 9 Minutes 59.98 seconds
        }
      } else {
        func_8003EA68(0x20);
        g_Spyro.m_walkingState = 3;
        g_Spyro.m_ControlFlags = 0x80004000;
      }

      if (g_FlightCourseRecords[g_Homeworld] != 0) {
        time = D_800758F4;
        i = time / (60 * 60);

        if (i != 0) {
          props->m_0x04[6]->m_Class = i + 260;
          props->m_0x04[4]->m_RenderRadius = 0xFF;
          props->m_0x04[5]->m_RenderRadius = 0xFF;
          props->m_0x04[6]->m_RenderRadius = 0xFF;
        } else {
          props->m_0x04[4]->m_RenderRadius = 0;
          props->m_0x04[5]->m_RenderRadius = 0;
          props->m_0x04[6]->m_RenderRadius = 0;
        }

        i = ((time * 10) / 6) % 10;
        props->m_0x04[7]->m_Class = i + 260;
        props->m_0x04[7]->m_RenderRadius = 0xFF;
      } else {
        time = D_80075840;
        if (time < 0) {
          time = 0;
        }
      }

      i = time / (10 * 60);
      if (i != 0) {
        i %= 6;
        props->m_0x04[0]->m_Class = i + 260;
        props->m_0x04[0]->m_RenderRadius = 0xFF;
      } else {
        props->m_0x04[0]->m_RenderRadius = 0;
      }

      seconds = time / 60;
      i = seconds % 10;
      props->m_0x04[1]->m_Class = i + 260;

      i = time / 6 - seconds * 10;
      props->m_0x04[3]->m_Class = i + 260;

      if (g_FlightCourseRecords[g_Homeworld] == 0) {
        i = seconds;
        if (i < oldSeconds) {
          if (i < 6) {
            props->m_0x9c = 1;
          } else {
            props->m_0x9c = 0;
          }

          if (i < 10) {
            PlaySound(g_Spu.m_SoundTable->flightPling, moby, 0x10, 0);
          }
        }

        if (props->m_0x9c != 0) {
          i = time / 6;
          if (i < oldTenths) {
            PlaySound(g_Spu.m_SoundTable->flightLowPlong, moby, 0x10, 0);
          }
        }
      }

      if (props->m_0x44[0] != 0) {
        if (props->m_0x98 != 0 && TICK_TIMER(props->m_0x94)) {
          props->m_0x98--;
          props->m_0x44[props->m_0x98]->m_State = 2;
          props->m_0x94 = 0x10;
          PlaySound(g_Spu.m_SoundTable->flightCompleted, moby, 0x10, 0);
        }

        for (i = 0; i < 8; i++) {
          if (props->m_0x44[i] != 0 && props->m_0x44[i]->m_State == 4) {
            if (props->m_0x64.fields.m_CategoryMobys[D_800757C4] == 0) {
              props->m_0x64.fields.m_CategoryMobys[D_800757C4] =
                  props->m_0x44[i];
              props->m_0x64.fields.m_CategoryMobys[D_800757C4]->m_Position.x =
                  D_800757C4 * 50 + 30;
              props->m_0x64.fields.m_CategoryMobys[D_800757C4]->m_Position.y =
                  200;
              props->m_0x64.fields.m_CategoryMobys[D_800757C4]->m_Position.z =
                  0x1000;
              props->m_0x64.fields.m_CategoryMobys[D_800757C4]->m_State = 1;
            } else {
              func_80052568(props->m_0x44[i]);
            }

            props->m_0x44[i] = 0;
            PlaySound(g_Spu.m_SoundTable->flightCompleted, moby, 0x10, 0);
          }
        }
      } else if (props->m_0x64.fields.m_CategoryMobys[0] != 0 &&
                 props->m_0x64.fields.m_CategoryMobys[1] != 0 &&
                 props->m_0x64.fields.m_CategoryMobys[2] != 0 &&
                 props->m_0x64.fields.m_CategoryMobys[3] != 0) {
        if (props->m_0x64.fields.m_CategoryMobys[0]->m_State == 4 ||
            (g_Pad.m_Down & PAD_CROSS)) {
          D_80075694();
        } else if (props->m_0x64.fields.m_CategoryMobys[0]->m_State == 1) {
          for (i = 0; i < 4; i++) {
            props->m_0x64.fields.m_CategoryMobys[i]->m_Substate = i;
            props->m_0x64.fields.m_CategoryMobys[i]->m_State = 5;
          }
        }
      } else {
        if (g_FlightObjectiveActiveSlots[0] >= 0) {
          D_800758F8 = g_FlightObjectiveActiveSlots[0];

          if (g_FlightObjectiveCounters[D_800758F8] != D_800770F8[D_800758F8]) {
            for (i = 0; i < 8; i++) {
              props->m_0x24[i]->m_Class =
                  props->m_0x64.fields.m_ObjectiveClasses[D_800758F8];

              if (g_FlightObjectiveCounters[D_800758F8] < i + 1) {
                props->m_0x24[i]->m_RenderRadius = 0xFF;
                props->m_0x24[i]->m_Position.x = i * 0x1E + 0x1E;
                props->m_0x24[i]->m_SpecularMetalType = 0;
                props->m_0x24[i]->m_Rotation.z = 0;
                props->m_0x24[i]->m_State = 0;
              } else {
                props->m_0x24[i]->m_RenderRadius = 0xFF;
                props->m_0x24[i]->m_Position.x = i * 0x1E + 0x1E;
                props->m_0x24[i]->m_SpecularMetalType = D_800758F8 + 3;
                props->m_0x24[i]->m_State = 1;
              }
            }

            D_800770F8[D_800758F8] = g_FlightObjectiveCounters[D_800758F8];

            if (g_FlightObjectiveCounters[D_800758F8] == 8) {
              for (i = 0; i < 8; i++) {
                props->m_0x44[i] = props->m_0x24[i];
                props->m_0x24[i] = g_SpawnMoby(
                    props->m_0x64.fields.m_ObjectiveClasses[0], moby);
              }

              props->m_0x94 = 0;
              props->m_0x98 = 8;
              D_800757C4 = D_800758F8;
            }
          }

          g_FlightObjectiveActiveSlots[0] = g_FlightObjectiveActiveSlots[1];
          g_FlightObjectiveActiveSlots[1] = g_FlightObjectiveActiveSlots[2];
          g_FlightObjectiveActiveSlots[2] = g_FlightObjectiveActiveSlots[3];
          g_FlightObjectiveActiveSlots[3] = -1;
        }

        D_800758F8 = -1;
      }

      if (g_Gamestate == GS_FlightResults) {
        for (i = 0; i < 8; i++) {
          if (props->m_0x24[i] != 0) {
            props->m_0x24[i]->m_RenderRadius = 0;
          }
          if (props->m_0x44[i] != 0) {
            props->m_0x44[i]->m_RenderRadius = 0;
          }
        }

        for (i = 0; i < 8; i++) {
          if (props->m_0x04[i] != 0) {
            props->m_0x04[i]->m_RenderRadius = 0;
          }
          if (props->m_0x64.m_ResultMobys[i] != 0) {
            props->m_0x64.m_ResultMobys[i]->m_RenderRadius = 0;
          }
        }
      }
      break;
    }
#endif
#if defined(HAS_MOBY_359) || defined(HAS_MOBY_360) || defined(HAS_MOBY_361)
#ifdef HAS_MOBY_359
    case 359:
#endif
#ifdef HAS_MOBY_360
    case 360:
#endif
#ifdef HAS_MOBY_361
    case 361:
#endif
    {
      MobyFragmentProps *props = moby->m_Props;

      if (props->m_Lifetime > 0 && moby->m_WasDrawn) {
        moby->m_Position.x += props->m_Velocity.x;
        moby->m_Position.y += props->m_Velocity.y;
        props->m_Velocity.z -= 6;
        if (props->m_Velocity.z < -0x80) {
          props->m_Velocity.z = -0x80;
        }
        moby->m_Position.z += props->m_Velocity.z;
        moby->m_Rotation.x += props->m_AngularVelocity.x;
        moby->m_Rotation.y += props->m_AngularVelocity.y;
        moby->m_Rotation.z += props->m_AngularVelocity.z;
        props->m_Lifetime--;
      } else {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_362
    case 362: {
      MobyFragmentProps *props = moby->m_Props;

      if (props->m_Lifetime > 0 && moby->m_WasDrawn) {
        if (func_8004BE4C(&moby->m_Position, 0x200, 0x200)) {
          int dot;

          func_80017330(&g_CollisionNormal, 0x1000);
          dot = (props->m_Velocity.x * g_CollisionNormal.x +
                 props->m_Velocity.y * g_CollisionNormal.y +
                 props->m_Velocity.z * g_CollisionNormal.z) >>
                11;
          if (dot < 0) {
            VecScaleToLength(&g_CollisionNormal, 0x1000, (dot >> 2) - dot);
            props->m_Velocity.x += g_CollisionNormal.x;
            props->m_Velocity.y += g_CollisionNormal.y;
            props->m_Velocity.z += g_CollisionNormal.z;
          }
        }

        moby->m_Position.x += props->m_Velocity.x;
        moby->m_Position.y += props->m_Velocity.y;
        props->m_Velocity.z -= 6;
        if (props->m_Velocity.z < -128) {
          props->m_Velocity.z = -128;
        }
        moby->m_Position.z += props->m_Velocity.z;
        moby->m_Rotation.x += props->m_AngularVelocity.x;
        moby->m_Rotation.y += props->m_AngularVelocity.y;
        moby->m_Rotation.z += props->m_AngularVelocity.z;
        props->m_Lifetime--;
      } else {
        func_80052568(moby);
      }
      break;
    }
#endif
#if defined(HAS_MOBY_363) || defined(HAS_MOBY_364) || defined(HAS_MOBY_400) || \
    defined(HAS_MOBY_405) || defined(HAS_MOBY_477) || defined(HAS_MOBY_507) || \
    defined(HAS_MOBY_508)
#ifdef HAS_MOBY_363
    case 363: // Water Bubbles (Purple)
#endif
#ifdef HAS_MOBY_364
    case 364: // Water Splash (Purple)
#endif
#ifdef HAS_MOBY_400
    case 400:
#endif
#ifdef HAS_MOBY_405
    case 405: // Water Bubbles (Blue)
#endif
#ifdef HAS_MOBY_477
    case 477: // Water Splash (Blue)
#endif
#ifdef HAS_MOBY_507
    case 507: // Water Bubbles (Yellow)
#endif
#ifdef HAS_MOBY_508
    case 508: // Water Splash (Yellow)
#endif
    {
      // Die if our animation has finished.
      if (g_AnimationFinished) {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_370
    case 370: {
      Moby370Props *props;
      int angle;
      props = (Moby370Props *)moby->m_Props;
      ApplyFlameHeat(moby);
      if (moby->m_State != 1 && moby->m_State != 3 &&
          moby->m_DamageFlags != 0) {
        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0 ||
            func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) >= ROTDEG8(120)) {
          props->m_0x10 = 350;
          props->m_0x08 = 0xA0;
          props->m_0x0c = g_Spyro.m_bodyRotation.z;
          moby->m_DamageFlags = 0;
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
          func_800562A4(moby, 1);
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
      }
      moby->m_DamageFlags = 0;
      switch (moby->m_State) {
      case 0: {
        int angle2;
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (props->m_0x00 == 0) {
          if (props->m_0x2c != -1) {
            if (g_LevelMobys[props->m_0x2c].m_State >= 0x80) {
              moby->m_State = 8;
              continue;
            }
          }
          if (moby->m_WasDrawn &&
              DISTANCE_TO_SPYRO(moby) < (props->m_0x18 << 10) &&
              SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
            props->m_0x1c = 0;
            if (moby->m_Pod == 0xFF) {
              moby->m_State = 2;
              MOBY_ANIM_CHANGE(moby, 2);
              continue;
            }
            func_8003B47C(moby, 1, 3);
          }
          if (props->m_0x28 != -1) {
            if (g_LevelMobys[props->m_0x28].m_AnimationState.m_NextAnimation ==
                7) {
              props->m_0x30 = 1;
              props->m_0x28 = -1;
              func_8003851C(moby, 1, 0);
              moby->m_State = 1;
              MOBY_ANIM_CHANGE(moby, 1);
              continue;
            }
          }
        } else if (props->m_0x00 == 1) {
          angle = ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x34, 3));
          angle2 = ANGLE_TO_SPYRO(moby->m_Position);
          if (func_80017908(angle, angle2) < 0x40) {
            if (OctDistance(&g_Spyro.m_Position,
                            &PATH_NODE_POS(props->m_0x34, 3)) < 2200) {
              moby->m_State = 30;
              continue;
            }
            break;
          }
          if (moby->m_WasDrawn &&
              DISTANCE_TO_SPYRO(moby) < (props->m_0x18 << 10) &&
              SPYRO_BASE_Z_DISTANCE(moby) < 0x800) {
            props->m_0x1c = 0;
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
        }
        break;
      }
      case 1: {
        int distance;
        int floorHeight;
        distance = DISTANCE_TO_SPYRO(moby);
        if (TICK_TIMER(props->m_0x38)) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          if (TICK_TIMER(props->m_0x04) == 2)
            func_8003851C(moby, 1, 0);
          if (props->m_0x30 != 0) {
            moby->m_State = 30;
            continue;
          }
          if (func_80038C4C(&moby->m_Position, &props->m_0x40[0][0]) != 0 ||
              func_80038C4C(&moby->m_Position, &props->m_0x40[1][0]) != 0) {
            moby->m_State = 5;
            continue;
          }
          if (distance < 0xC00 &&
              func_80017908(moby->m_Rotation.z,
                            ANGLE_TO_SPYRO(moby->m_Position)) < 8) {
            moby->m_State = 4;
            continue;
          }
          if (props->m_0x1c < 200)
            props->m_0x1c += 0x14;
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          if (RotateMobyToAngle(moby, angle, 8, 0x26, 1) != 0)
            func_80039398(moby, props->m_0x1c, 0x200, 0x200, 0x23);
          floorHeight = func_80038340(moby);
          if (moby->m_Position.z - floorHeight > 500) {
            props->m_0x0c = 0x4D;
            props->m_0x10 = props->m_0x1c;
            if (props->m_0x10 < 0x50)
              props->m_0x10 = 0x50;
            props->m_0x08 = 0x28;
            props->m_0x24 = 0x3C;
            moby->m_Substate = 0;
            func_8003851C(moby, 0, 0);
            moby->m_State = 10;
            continue;
          }
          moby->m_Position.z = moby->m_FloorDistance + floorHeight;
        }
        break;
      }
      case 2:
        if (g_AnimationFinished) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;
      case 3: {
        int result;
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }
        result = MoveMobyWithGravity(moby, &props->m_0x10, props->m_0x0c,
                                     &props->m_0x08, 0xC, 0xC);
        if (result == 3 && moby->m_AnimationState.m_NextFrame < 0xD) {
          g_AnimationFinished = 0;
          moby->m_AnimationState.m_FrameProgress = 0x10;
          moby->m_AnimationState.m_PerFrameProgress = 0x10;
          moby->m_AnimationState.m_Animation =
              moby->m_AnimationState.m_NextAnimation;
          moby->m_AnimationState.m_NextAnimation = 3;
          moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
          moby->m_AnimationState.m_NextFrame = 0xD;
          func_80037E98(moby);
        }
        if (ABS2((int)moby->m_AnimationState.m_NextFrame -
                 (int)moby->m_AnimationState.m_Frame) < 3) {
          moby->m_AnimationState.m_PerFrameProgress =
              g_Models[moby->m_Class]
                  ->m_Animations[moby->m_AnimationState.m_Animation]
                  ->m_ProgressPerTick;
        }
        break;
      }
      case 4: {
        int floorHeight;
        if (props->m_0x1c < 200)
          props->m_0x1c += 0x14;
        func_80039398(moby, props->m_0x1c, 0x200, 0x200, 0x23);
        floorHeight = func_80038340(moby);
        if (moby->m_Position.z - floorHeight > 500) {
          props->m_0x0c = 0x4D;
          props->m_0x10 = props->m_0x1c;
          if (props->m_0x10 < 0x50)
            props->m_0x10 = 0x50;
          props->m_0x08 = 0x28;
          props->m_0x24 = 0x3C;
          moby->m_Substate = 0;
          func_8003851C(moby, 0, 0);
          moby->m_State = 10;
          continue;
        }
        moby->m_Position.z = moby->m_FloorDistance + floorHeight;
        if (func_80038C4C(&moby->m_Position, &props->m_0x40[0][0]) != 0 ||
            func_80038C4C(&moby->m_Position, &props->m_0x40[1][0]) != 0) {
          moby->m_State = 5;
          continue;
        }
        if (DISTANCE_TO_SPYRO(moby) < 1200 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 500 &&
            func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) < 0x14 &&
            g_Spyro.m_State != 0xB && g_Spyro.m_State != 0x14) {
          g_Spyro.unk_0x208.z = 110;
          g_Spyro.m_DamageFlags = 0x86;
          g_Spyro.unk_0x208.x = 0;
          g_Spyro.unk_0x208.y = 0;
          moby->m_State = 5;
          continue;
        }
        if (func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) >= 0x41) {
          moby->m_State = 5;
          continue;
        }
        break;
      }
      case 5: {
        int pathIndex;
        props->m_0x24 = 0xB4;
        func_80038A40(moby, props->m_0x3c, &pathIndex);
        props->m_0x20 = ANGLE_FROM(moby->m_Position,
                                   PATH_NODE_POS(props->m_0x3c, pathIndex));
        moby->m_State = 6;
        continue;
      }
      case 6: {
        int floorHeight;
        floorHeight = func_80038340(moby);
        if (props->m_0x24 < 0xA5)
          RotateMobyToAngle(moby, props->m_0x20, 7, 0, 0);
        if (TICK_TIMER(props->m_0x24)) {
          props->m_0x1c -= 0x10;
          if (props->m_0x1c < 0)
            props->m_0x1c = 0;
        }
        if (props->m_0x1c == 0) {
          props->m_0x24 = 0x3C;
          moby->m_State = 7;
          continue;
        }
        if (moby->m_Position.z - (floorHeight + moby->m_FloorDistance) >=
                0x321 ||
            func_8003838C(moby) == 0) {
          props->m_0x0c = moby->m_Rotation.z;
          props->m_0x10 = props->m_0x1c;
          if (props->m_0x10 < 0x50)
            props->m_0x10 = 0x50;
          props->m_0x08 = 0x28;
          props->m_0x24 = 0x3C;
          moby->m_Substate = 0;
          func_8003851C(moby, 0, 0);
          moby->m_State = 10;
          continue;
        }
        moby->m_Position.z = floorHeight + moby->m_FloorDistance;
        func_80039398(moby, props->m_0x1c, 0x200, 0x200, 0x23);
        break;
      }
      case 7:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        if (TICK_TIMER(props->m_0x24)) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
          moby->m_State = 8;
          continue;
        }
        break;
      case 8: {
        int distance;
        distance = DISTANCE_TO_SPYRO(moby);
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (TICK_TIMER(props->m_0x04) && distance < 1400) {
          props->m_0x04 = 0x78;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
          moby->m_State = 9;
          continue;
        }
        break;
      }
      case 9:
        if (g_AnimationFinished) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
          moby->m_State = 8;
          continue;
        }
        break;
      case 10: {
        int pathIndex;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 6);
        if (TICK_TIMER(props->m_0x24)) {
          func_80052568(moby);
          continue;
        }
        if (moby->m_Substate == 0 && props->m_0x08 < -0x50) {
          func_80038A40(moby, props->m_0x3c, &pathIndex);
          func_8003ABC0(moby, 2, 0, &PATH_NODE_POS(props->m_0x3c, pathIndex));
          func_8003B7C0(moby);
          moby->m_Substate = 1;
        }
        MoveMobyWithGravity(moby, &props->m_0x10, props->m_0x0c, &props->m_0x08,
                            0xC, 0xC);
        break;
      }
      case 20: {
        int result;
        props->m_0x1c = 0xA0;
        result = func_80039E94(moby, props->m_0x34, 300, props->m_0x1c, 0, 8,
                               0x40, 0xFF, 5);
        if (result == 0x100) {
          props->m_0x30 = 0;
          moby->m_State = 1;
          continue;
        }
        break;
      }
      case 30: {
        int result;
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
        if (TICK_TIMER(props->m_0x04) == 2)
          func_8003851C(moby, 1, 0);
        props->m_0x1c = 0xB4;
        result = func_80039E94(moby, props->m_0x34, 0x100, props->m_0x1c, 0, 8,
                               0x40, 0xFF, 5);
        if (result == 0x100) {
          moby->m_State = 5;
          continue;
        }
        if (DISTANCE_TO_SPYRO(moby) < 1200 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 500 &&
            func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) < 0x14 &&
            g_Spyro.m_State != 0xB && g_Spyro.m_State != 0x14) {
          g_Spyro.unk_0x208.x = 0;
          g_Spyro.unk_0x208.y = 0;
          g_Spyro.unk_0x208.z = 110;
          g_Spyro.m_DamageFlags = 0x86;
        }
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_371
    case 371: {
      Moby371Props *props;
      int distance;
      int angle;
      int angle12;
      props = (Moby371Props *)moby->m_Props;
      distance = DISTANCE_TO_SPYRO(moby);
      ApplyFlameHeat(moby);
      if (distance < 0x2000 && moby->m_State != 41 && g_Spyro.m_State != 11 &&
          g_Spyro.m_State != 20) {
        g_Spyro.m_mobyInUseBySpyro = moby;
        g_Spyro.m_ControlFlags |= 0x80010000;
      }
      if (moby->m_State < 40 &&
          (moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER))) {
        moby->m_DamageFlags = 0;
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        if (func_80017908(moby->m_Rotation.z, angle) >= ROTDEG8(120) ||
            (moby->m_State == 2 && moby->m_AnimationState.m_NextFrame >= 0x16 &&
             moby->m_AnimationState.m_NextFrame < 0x30)) {
          Moby371Props *linkedProps;
          Moby *linkedMoby;
          if (props->m_0x1c == 2) {
            if (moby->m_AnimationState.m_Animation != 3) {
              g_AnimationFinished = 0;
              MOBY_ANIM_RESTART(moby, 3);
            }
            moby->m_Rotation.z += ROTDEG8(180);
            func_8002B390(2, 0xFC, 0);
            moby->m_State = 45;
            continue;
          }
          if (props->m_0x3c >= 0) {
            linkedMoby = &g_LevelMobys[props->m_0x3c];
            linkedProps = (Moby371Props *)linkedMoby->m_Props;
            VecCopy(&linkedMoby->m_Position, &moby->m_Position);
            func_8003ABC0(linkedMoby, 1, 0, 0);
            func_8003B7C0(linkedMoby);
            props->m_0x3c = linkedProps->m_0x00;
            func_80052568(linkedMoby);
          }
          moby->m_State = 40;
          continue;
        }
      }
      moby->m_DamageFlags = 0;
      if (props->m_0x40 == 0) {
        props->m_0x40 = 1;
        if (D_80075850 != 0 && moby->m_DropMoby == 0xFF) {
          Moby371Props *chainProps;
          Moby *chainMoby;
          int pathIndex;
          int foundActive;
          foundActive = 0;
          pathIndex = props->m_0x3c;
          while (1) {
            if (pathIndex < 0)
              break;
            chainMoby = &g_LevelMobys[pathIndex];
            if (chainMoby->m_DropMoby != 0xFF) {
              foundActive = 1;
            } else {
              chainProps = (Moby371Props *)g_LevelMobys[pathIndex].m_Props;
              pathIndex = chainProps->m_0x00;
            }
            if (foundActive != 0)
              break;
          }
          if (foundActive == 0) {
            func_8002B390(0, 0xFC, 0);
            func_8002B390(1, 0xFC, 0);
            func_8002B390(2, 0xFC, 0);
            VecCopy(
                &moby->m_Position,
                &PATH_NODE_POS(props->m_0x20, props->m_0x20->m_NodeCount - 2));
            func_80052568(moby);
          }
        }
      }
      switch (moby->m_State) {
      case 0: {
        int result;
        props->m_0x00 = moby->m_Rotation.z << 4;
        result =
            func_80038FC8(moby, &props->m_0x18, &props->m_0x00, 0x20, 0x280, 1);
        if (ABS2(result) < 0x80 &&
            moby->m_AnimationState.m_NextAnimation != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 0);
        }
        props->m_0x34 = 0;
        switch (props->m_0x1c) {
        case 0:
          if (DISTANCE_TO_SPYRO(moby) < 9000) {
            moby->m_State = 11;
            continue;
          }
          break;
        case 1:
          if (TICK_TIMER(props->m_0x10) && DISTANCE_TO_SPYRO(moby) < 6500 &&
              SPYRO_BASE_Z_DELTA(moby) < 0) {
            moby->m_State = 1;
            continue;
          }
          break;
        case 2:
          if (TICK_TIMER(props->m_0x10) && DISTANCE_TO_SPYRO(moby) < 6500 &&
              SPYRO_BASE_Z_DELTA(moby) < 0) {
            moby->m_State = 21;
            continue;
          }
          break;
        }
        break;
      }
      case 1:
        if (props->m_0x34 == 0) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);
          props->m_0x34 = 1;
        } else if (g_AnimationFinished) {
          if (props->m_0x38 == 0) {
            props->m_0x38 = RandRange(1, 2);
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x13);
          } else {
            props->m_0x38--;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x12);
          }
        }
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (TICK_TIMER(props->m_0x10) && DISTANCE_TO_SPYRO(moby) < 5800) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x10);
          moby->m_State = 2;
          continue;
        }
        break;
      case 2:
        RotateMobyToSpyro(moby, 8, 0, 0);
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x10);
        if (moby->m_AnimationState.m_NextFrame >= 0x34 &&
            moby->m_AnimationState.m_NextFrame < 0x38 &&
            DISTANCE_TO_SPYRO(moby) < 6300) {
          if (SPYRO_BASE_Z_DELTA(moby) < -300 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 1500) {
            g_Spyro.m_DamageFlags |= 0x13;
          }
        }
        if (g_AnimationFinished) {
          props->m_0x10 = 0xA0;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x12);
          moby->m_State = 1;
          continue;
        }
        break;
      case 11:
        props->m_0x10 = 0x5A;
        props->m_0x34 = 0;
        moby->m_State = 12;
        continue;
      case 12: {
        int angle2;
        int movement = 0xB4;
        int pathIndex;
        int result;
        pathIndex = props->m_0x28[0];
        angle12 = ANGLE_FROM_SPYRO(PATH_NODE_POS(props->m_0x20, pathIndex));
        angle2 = ANGLE_FROM(PATH_NODE_POS(props->m_0x20, pathIndex),
                            moby->m_Position);
        result = 0xE;
        if (moby->m_AnimationState.m_NextAnimation == 9)
          result = 6;
        if (func_80017908(angle12, angle2) > result) {
          func_80038638(moby, &PATH_NODE_POS(props->m_0x20, pathIndex), 3200,
                        angle12, 6, movement, 9, 0x14, 0xFF, 0xFF, 0, 0, 0);
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 9);
        } else {
          RotateMobyToSpyro(moby, 6, 0, 0);
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x12);
          if (g_AnimationFinished) {
            if (props->m_0x38 == 0) {
              props->m_0x38 = RandRange(1, 2);
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x13);
            } else {
              props->m_0x38--;
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x12);
            }
          }
        }
        if (TICK_TIMER(props->m_0x10)) {
          if (SPYRO_BASE_Z_DELTA(moby) < 0) {
            angle12 = ANGLE_TO_SPYRO(moby->m_Position);
            if (func_80017908(moby->m_Rotation.z, angle12) < 4) {
              moby->m_State = 13;
              continue;
            }
          }
        }
        break;
      }
      case 13: {
        if (props->m_0x34 == 0) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0xA);
        }
        if (g_AnimationFinished || props->m_0x34 != 0) {
          props->m_0x34 = 1;
          props->m_0x10 = 0x32;
          moby->m_State = 14;
          continue;
        }
        break;
      }
      case 14:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 9);
        if (func_80039398(moby, 170, 0, 0, 0x11) != 0 ||
            TICK_TIMER(props->m_0x10)) {
          moby->m_State = 15;
          continue;
        }
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        if (func_80017908(moby->m_Rotation.z, angle) < 0xA &&
            DISTANCE_TO_SPYRO(moby) < 2500) {
          moby->m_State = 15;
          continue;
        }
        break;
      case 15:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0xF);
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        if (func_80017908(moby->m_Rotation.z, angle) < 8 &&
            moby->m_AnimationState.m_NextFrame >= 4 &&
            moby->m_AnimationState.m_NextFrame < 0xA &&
            DISTANCE_TO_SPYRO(moby) < 0x1194) {
          if (SPYRO_BASE_Z_DELTA(moby) < -300 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 1500) {
            g_Spyro.m_DamageFlags |= 0x13;
          }
        }
        if (g_AnimationFinished) {
          moby->m_State = 16;
          continue;
        }
        break;
      case 16: {
        Vector3D target;
        int angle2;
        int pathIndex;
        pathIndex = props->m_0x28[0];
        angle = ANGLE_FROM_SPYRO(PATH_NODE_POS(props->m_0x20, pathIndex));
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 9);
        target.x = PATH_NODE_POS(props->m_0x20, pathIndex).x +
                   FIXED_MUL(COSINE_8(angle), 3200);
        target.y = PATH_NODE_POS(props->m_0x20, pathIndex).y +
                   FIXED_MUL(SINE_8(angle), 3200);
        angle2 = ANGLE_FROM(moby->m_Position, target);
        if (RotateMobyToAngle(moby, angle2, 4, 30, 1) != 0)
          func_80039398(moby, 90, 0, 0, 1);
        if (OctDistance(&moby->m_Position, &target) < 0x100) {
          props->m_0x10 = 140;
          moby->m_State = 12;
          continue;
        }
        break;
      }
      case 21:
        if (props->m_0x34 == 0) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0xA);
          props->m_0x34 = 1;
        } else if (g_AnimationFinished) {
          if (props->m_0x38 == 0) {
            props->m_0x38 = RandRange(1, 2);
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x13);
          } else {
            props->m_0x38--;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0x12);
          }
        }
        RotateMobyToSpyro(moby, 6, 0, 0);
        if (TICK_TIMER(props->m_0x10) && DISTANCE_TO_SPYRO(moby) < 5000) {
          moby->m_State = 22;
          continue;
        }
        break;
      case 22:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0xB);
        props->m_0x10 = 0;
        moby->m_Substate = moby->m_Rotation.z;
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        angle = (angle + 0x1E) & 0xFF;
        if (RotateMobyToAngle(moby, angle, 6, 2, 1) != 0) {
          moby->m_State = 23;
          continue;
        }
        break;
      case 23: {
        int floorHeight;
        if (g_AnimationFinished) {
          moby->m_AnimationState.m_Frame = 0x14;
          moby->m_AnimationState.m_NextFrame = 0x15;
          moby->m_AnimationState.m_FrameProgress = 0;
          break;
        }
        if (moby->m_AnimationState.m_NextFrame < 0x14)
          break;
        floorHeight =
            g_Spyro.m_Position.z - func_8004D5EC(&g_Spyro.m_Position, 0x1000);
        props->m_0x10 += g_DeltaTime * 56;
        moby->m_Rotation.z = moby->m_Substate - (props->m_0x10 >> 4);
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        if (func_80017908(moby->m_Rotation.z, angle) < 6 &&
            DISTANCE_TO_SPYRO(moby) < 5100 && floorHeight < 800) {
          if (SPYRO_BASE_Z_DELTA(moby) < -300 &&
              SPYRO_BASE_Z_DISTANCE(moby) < 1500) {
            g_Spyro.m_DamageFlags |= 0x107;
            g_Spyro.unk_0x208.x = FIXED_MUL(SINE_8(moby->m_Rotation.z), 90);
            g_Spyro.unk_0x208.y = FIXED_MUL(COSINE_8(moby->m_Rotation.z), -90);
            g_Spyro.unk_0x208.z = 20;
          }
        }
        if ((props->m_0x10 >> 4) > 260) {
          props->m_0x10 = 0x3C;
          if (moby->m_AnimationState.m_Animation != 0x12) {
            moby->m_AnimationState.m_FrameProgress = 8;
            moby->m_AnimationState.m_PerFrameProgress = 8;
            moby->m_AnimationState.m_Animation =
                moby->m_AnimationState.m_NextAnimation;
            moby->m_AnimationState.m_NextAnimation = 0x12;
            moby->m_AnimationState.m_Frame = moby->m_AnimationState.m_NextFrame;
            moby->m_AnimationState.m_NextFrame = 0;
            func_80037E98(moby);
          }
          moby->m_State = 21;
          continue;
        }
        break;
      }
      case 40:
        props->m_0x10 = 200;
        if (props->m_0x1c == 0) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 14);
        } else {
          moby->m_Rotation.z += 0x80;
          if (moby->m_AnimationState.m_Animation != 14) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 14);
          }
        }
        func_8002B390(props->m_0x1c, 0xFC, 0);
        props->m_0x1c++;
        props->m_0x44 = 0x1E;
        moby->m_State = 41;
        continue;
      case 41: {
        Vector3D particleVelocity;
        Vector3D vertexPosition;
        Vector3D particlePosition;
        u_char angle2;
        int angleOffset;
        int pathIndex;
        int result;
        int i;
        int cameraAngle;
        pathIndex = props->m_0x28[props->m_0x1c - 1];
        cameraAngle =
            (ANGLE_FROM(PATH_NODE_POS(props->m_0x24, props->m_0x1c - 1),
                        PATH_NODE_POS(props->m_0x20, pathIndex)) +
             0x80) &
            0xFF;
        result = TICK_TIMER(props->m_0x10);
        if (result == 0) {
          g_Spyro.m_ControlFlags |= 0x80002200;
          g_ScreenBorderEnabled = 1;
          g_Spyro.unk_0x21c = &PATH_NODE_POS(props->m_0x20, pathIndex);
          g_Spyro.unk_0x220 = &D_80078668;
          D_80078668.m_Coords.azimuth = (-cameraAngle) << 4;
          D_80078668.m_Coords.radius = 6000;
          D_80078668.m_Coords.elevation = 0x19;
          D_80078668.m_Offset.elevation = -0x32;
          D_80078668.m_Offset.azimuth = 0;
          D_80078668.m_Offset.radius = 0;
        } else {
          g_ScreenBorderEnabled = 0;
        }
        if (g_AnimationFinished || moby->m_AnimationState.m_NextFrame >= 0xE) {
          if (TICK_TIMER(props->m_0x44)) {
            func_8003851C(moby, RandRange(0, 2), 0);
            props->m_0x44 = 0x28;
          }
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 0, &vertexPosition);
          for (i = 0; i < 3; i++) {
            angleOffset = RandRange(-18, 18) + ROTDEG8(180);
            angle2 = moby->m_Rotation.z + angleOffset;
            particleVelocity.x = COSINE_8(angle2) >> 5;
            particleVelocity.y = SINE_8(angle2) >> 5;
            particleVelocity.z = RandRange(-0xF, 0xF) + 0x14;
            VecCopy(&particlePosition, &vertexPosition);
            particlePosition.x += (rand() & 0x1FF) - 0x100;
            particlePosition.y += (rand() & 0x1FF) - 0x100;
            particlePosition.z += (rand() & 0x1FF) - 0x100;
            g_SpawnParticle(1, 1, &particlePosition, (int)&particleVelocity);
          }
          if (g_AnimationFinished) {
            moby->m_AnimationState.m_Frame = 0xF;
            moby->m_AnimationState.m_NextFrame = 0x10;
            moby->m_AnimationState.m_FrameProgress = 0;
          }
          result = func_80039E94(moby, props->m_0x20, 0x118, 0xA0, 0, 4, 0x14,
                                 0xFF, 5);
          if (result == props->m_0x28[props->m_0x1c] + 0x101) {
            moby->m_State = 42;
            continue;
          }
        }
        break;
      }
      case 42:
        if (g_AnimationFinished) {
          moby->m_AnimationState.m_Frame = 0xF;
          moby->m_AnimationState.m_NextFrame = 0x10;
          moby->m_AnimationState.m_FrameProgress = 0;
        }
        if (RotateMobyToSpyro(moby, 6, 0xA, 1) != 0 && g_AnimationFinished) {
          props->m_0x38 = 0;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          moby->m_State = 0;
          continue;
        }
        break;
      case 45:
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
        if (g_AnimationFinished) {
          D_80075850 = 1;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x40);
          moby->m_FloorDistance = 0;
          func_80038458(moby);
          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);
          func_80052568(moby);
          continue;
        }
        break;
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_372
    case 372: {
      Moby372Props *props;
      Moby *linkedMoby;
      int angle;
      int state;
      props = (Moby372Props *)moby->m_Props;
      linkedMoby = 0;
      if (props->m_0x18 != -1)
        linkedMoby = &g_LevelMobys[props->m_0x18];
      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 7) {
        props->m_0x04 = 0xF0;
        props->m_0x00 = g_Spyro.m_bodyRotation.z;
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 7;
        MOBY_ANIM_CHANGE(moby, 7);
        continue;
      }
      if (!TICK_TIMER(props->m_0x1c))
        g_Spyro.m_ControlFlags = 0x80002147;
      if (!TICK_TIMER(props->m_0x20)) {
        int cameraDistance;
        cameraDistance = DISTANCE_TO_SPYRO(moby) + 0xC00;
        if (props->m_0x24 < cameraDistance)
          props->m_0x24 = cameraDistance;
        if (props->m_0x1c != 0)
          g_Spyro.m_ControlFlags |= 0x80000200;
        else
          g_Spyro.m_ControlFlags = 0x80000200;
        g_Spyro.unk_0x21c = &moby->m_Position;
        g_Spyro.unk_0x220 = &D_80078668;
        D_80078668.m_Coords.azimuth = (-ANGLE_TO_SPYRO(moby->m_Position)) << 4;
        cameraDistance = props->m_0x24;
        D_80078668.m_Coords.elevation = 0;
        D_80078668.m_Offset.azimuth = 0;
        D_80078668.m_Offset.elevation = 0;
        D_80078668.m_Offset.radius = 0;
        D_80078668.m_Coords.radius = cameraDistance;
      }
      state = moby->m_State;
      switch (state) {
      case 0: {
        int distance;
        distance = DISTANCE_TO_SPYRO(moby);
        if (props->m_0x14 == 0) {
          props->m_0x14 = 1;
          props->m_0x10 = moby->m_Rotation.z;
        }
        if (linkedMoby != 0 && TICK_TIMER(props->m_0x2c) &&
            moby->m_Substate == 0 && linkedMoby->m_State == 0 &&
            distance < (props->m_0x28 << 10) &&
            moby->m_Position.z < g_Spyro.m_Position.z &&
            SPYRO_BASE_Z_DISTANCE(moby) < 1500) {
          moby->m_Substate = 1;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
          moby->m_State = 10;
          continue;
        }
        if (distance > 0x2000) {
          RotateMobyToAngle(moby, props->m_0x10, 4, 0, 0);
          if (moby->m_AnimationState.m_Animation == 2 &&
              g_AnimFrameFinished != 0 &&
              moby->m_AnimationState.m_Frame == 0xF) {
            props->m_0x0c--;
            if (props->m_0x0c > 0) {
              moby->m_AnimationState.m_Frame = 5;
              moby->m_AnimationState.m_NextFrame = 6;
              moby->m_AnimationState.m_FrameProgress = 0;
            }
          }
          if (props->m_0x0c == 0) {
            props->m_0x0c = RandRange(3, 5);
            if (RandRange(0, 100) > 0x50) {
              MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
            } else if (moby->m_AnimationState.m_NextAnimation != 4) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby, 4);
            }
          }
        } else {
          angle = ANGLE_TO_SPYRO(moby->m_Position);
          angle = func_80038074(angle, 5);
          if (moby->m_AnimationState.m_NextAnimation == 2 ||
              moby->m_AnimationState.m_NextAnimation == 4) {
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
          }
          if (moby->m_AnimationState.m_Animation < 2 ||
              moby->m_AnimationState.m_Animation == 5) {
            RotateMobyToAngle(moby, angle, 4, 0, 0);
          }
          if (g_AnimationFinished) {
            props->m_0x0c--;
            if (props->m_0x0c <= 0) {
              props->m_0x0c = RandRange(3, 5);
              if (RandRange(0, 100) > 0x50) {
                if (moby->m_AnimationState.m_NextAnimation != 1) {
                  g_AnimationFinished = 0;
                  MOBY_ANIM_ADVANCE(moby, 1);
                } else {
                  g_AnimationFinished = 0;
                  MOBY_ANIM_ADVANCE(moby, 0);
                }
              }
            } else if (moby->m_AnimationState.m_NextAnimation != 5) {
              g_AnimationFinished = 0;
              MOBY_ANIM_ADVANCE(moby, 5);
            }
          }
        }
        if (TICK_TIMER(props->m_0x08) && distance < 2500 &&
            SPYRO_BASE_Z_DISTANCE(moby) < 1000 &&
            SPYRO_BASE_Z_DELTA(moby) < 0) {
          moby->m_State = 6;
          MOBY_ANIM_CHANGE(moby, 6);
          continue;
        }
        break;
      }
      case 6: {
        angle = ANGLE_TO_SPYRO(moby->m_Position);
        angle = func_80038074(angle, 5);
        RotateMobyToAngle(moby, angle, 6, 0, 0);
        if (g_AnimFrameFinished != 0 && moby->m_AnimationState.m_Frame == 3 &&
            DISTANCE_TO_SPYRO(moby) < 2700) {
          Vector3D delta;
          VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
          VecScaleToLength(&delta, VecMagnitude(&delta, 0), 0x82);
          g_Spyro.m_fallingState = state;
          g_Spyro.m_ControlFlags = 0x80000047;
          g_Spyro.unk_0x208.z = 0x32;
          g_Spyro.unk_0x208.x = delta.x;
          g_Spyro.unk_0x208.y = delta.y;
          props->m_0x1c = 40;
          props->m_0x20 = 40;
          props->m_0x24 = 4000;
        }
        if (g_AnimationFinished) {
          props->m_0x08 = 140;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      case 7:
        if (props->m_0x04 > 0) {
          func_80039688(moby, props->m_0x00, props->m_0x04, 500, 700, 1);
          props->m_0x04 -= 0x10;
        }
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }
        break;
      case 10: {
        Moby371Props *linkedProps;
        angle = ANGLE_FROM(moby->m_Position, linkedMoby->m_Position);
        if (RotateMobyToAngle(moby, angle, 8, 6, 1) != 0 &&
            moby->m_AnimationState.m_NextAnimation != 8) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 8);
        }
        if (moby->m_AnimationState.m_Animation == 8 &&
            g_AnimFrameFinished != 0 && moby->m_AnimationState.m_Frame == 5) {
          linkedProps = (Moby371Props *)linkedMoby->m_Props;
          if (linkedMoby->m_State < 127) {
            if (linkedMoby->m_AnimationState.m_NextAnimation != 3)
              linkedMoby->m_State = 1;
          }
          linkedProps->m_0x04 = 0x1A;
          if (linkedProps->m_0x28[0] != -1) {
            props->m_0x18 = linkedProps->m_0x28[0];
            linkedProps->m_0x28[0] = -1;
            moby->m_Substate = 0;
            if (linkedProps->m_0x38 != 0) {
              props->m_0x2c = linkedProps->m_0x38;
              linkedProps->m_0x38 = 0;
            } else {
              props->m_0x2c = 0x14;
            }
          }
        }
        if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 8) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);
          moby->m_State = 0;
          continue;
        }
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#if defined(HAS_MOBY_375) || defined(HAS_MOBY_376) || defined(HAS_MOBY_377) || \
    defined(HAS_MOBY_378) || defined(HAS_MOBY_379) || defined(HAS_MOBY_380) || \
    defined(HAS_MOBY_381) || defined(HAS_MOBY_382) || defined(HAS_MOBY_383) || \
    defined(HAS_MOBY_384) || defined(HAS_MOBY_385) || defined(HAS_MOBY_386)
#ifdef HAS_MOBY_375
    case 375:
#endif
#ifdef HAS_MOBY_376
    case 376:
#endif
#ifdef HAS_MOBY_377
    case 377:
#endif
#ifdef HAS_MOBY_378
    case 378:
#endif
#ifdef HAS_MOBY_379
    case 379:
#endif
#ifdef HAS_MOBY_380
    case 380:
#endif
#ifdef HAS_MOBY_381
    case 381:
#endif
#ifdef HAS_MOBY_382
    case 382:
#endif
#ifdef HAS_MOBY_383
    case 383:
#endif
#ifdef HAS_MOBY_384
    case 384:
#endif
#ifdef HAS_MOBY_385
    case 385:
#endif
#ifdef HAS_MOBY_386
    case 386:
#endif
    {
      Moby375Props *props = moby->m_Props;

      if (moby->m_WasDrawn == 0 || TICK_TIMER(props->m_Lifetime)) {
        func_80052568(moby);
      } else {
        VecAdd(&moby->m_Position, &moby->m_Position, &props->m_Velocity);
        moby->m_Rotation.x += props->m_AngularVelocity.x;
        moby->m_Rotation.y += props->m_AngularVelocity.y;
        moby->m_Rotation.z += props->m_AngularVelocity.z;
      }
      break;
    }
#endif
#if defined(HAS_MOBY_387) || defined(HAS_MOBY_388) || defined(HAS_MOBY_389) || \
    defined(HAS_MOBY_393) || defined(HAS_MOBY_394) || defined(HAS_MOBY_396) || \
    defined(HAS_MOBY_490) || defined(HAS_MOBY_491)
#ifdef HAS_MOBY_387
    case 387:
#endif
#ifdef HAS_MOBY_388
    case 388:
#endif
#ifdef HAS_MOBY_389
    case 389:
#endif
#ifdef HAS_MOBY_393
    case 393:
#endif
#ifdef HAS_MOBY_394
    case 394:
#endif
#ifdef HAS_MOBY_396
    case 396:
#endif
#ifdef HAS_MOBY_490
    case 490:
#endif
#ifdef HAS_MOBY_491
    case 491:
#endif
    {
      Moby387Props *props = moby->m_Props;
      Vector3D target;

      switch (moby->m_State) {
      case 0:
        break;
      case 1:
        moby->m_Rotation.z += 8;
        break;
      case 2:
        target.x = D_800757C4 * 50 + 30;
        target.y = 200;
        target.z = 0x1000;
        VecAdd(&props->m_0x00, &target, &moby->m_Position);
        VecShiftRight(&props->m_0x00, 1);
        VecSub(&target, &props->m_0x00, &moby->m_Position);
        props->m_0x0c = VecMagnitude(&target, 0);
        props->m_0x0e = Atan2(moby->m_Position.x - props->m_0x00.x,
                              props->m_0x00.y - moby->m_Position.y, 1);
        props->m_0x10 = 0x800;
        moby->m_State = 3;
        moby->m_Rotation.z += 8;
        break;
      case 3:
        props->m_0x10 -= 0x40;
        moby->m_Position.x =
            props->m_0x00.x -
            FIXED_MUL(props->m_0x0c, Cos(props->m_0x0e + props->m_0x10));
        moby->m_Position.y =
            props->m_0x00.y +
            FIXED_MUL(props->m_0x0c, Sin(props->m_0x0e + props->m_0x10));
        moby->m_Rotation.z += 8;
        if (props->m_0x10 <= 0) {
          moby->m_State = 4;
        }
        break;
      case 5: {
        target.x = FIXED_MUL(COSINE_8(moby->m_Substate << 6), 64) + 256;
        target.y = FIXED_MUL(SINE_8(moby->m_Substate << 6), 40) + 120;
        target.z = 0x1000;
        VecAdd(&props->m_0x00, &target, &moby->m_Position);
        VecShiftRight(&props->m_0x00, 1);
        VecSub(&target, &props->m_0x00, &moby->m_Position);
        props->m_0x0c = VecMagnitude(&target, 0);
        props->m_0x0e = Atan2(moby->m_Position.x - props->m_0x00.x,
                              props->m_0x00.y - moby->m_Position.y, 1);
        props->m_0x10 = 0x800;
        moby->m_State = 6;
        moby->m_Rotation.z += 8;
        break;
      }
      case 6:
        props->m_0x10 -= 0x40;
        moby->m_Position.x =
            props->m_0x00.x -
            FIXED_MUL(props->m_0x0c, Cos(props->m_0x0e + props->m_0x10));
        moby->m_Position.y =
            props->m_0x00.y +
            FIXED_MUL(props->m_0x0c, Sin(props->m_0x0e + props->m_0x10));
        moby->m_Rotation.z += 8;
        if (props->m_0x10 <= 0) {
          props->m_0x0e =
              Atan2(moby->m_Position.x - 0x100, moby->m_Position.y - 120, 1);
          props->m_0x10 = -0x3000;
          props->m_0x0c = 0x40;
          moby->m_State = 7;
        }
        break;
      case 7:
        props->m_0x10 += 0x80;
        props->m_0x0c -= 2;
        moby->m_Position.x =
            0x100 +
            ((props->m_0x0c * (Cos(props->m_0x0e + props->m_0x10) << 6)) >> 18);
        moby->m_Position.y =
            120 + ((props->m_0x0c *
                    ((Sin(props->m_0x0e + props->m_0x10) * 5) << 3)) >>
                   18);
        moby->m_Rotation.z += 8;
        if (props->m_0x10 >= 0) {
          moby->m_State = 4;
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_390
    case 390: {
      Moby390Props *props = moby->m_Props;
      int targetPitch;
      int currentPitch;
      int i;

      targetPitch =
          g_Spu.m_SoundDefinitions[g_Models[moby->m_Class]->m_Sounds[1]]
              .m_Pitch;
      currentPitch = g_Spu.m_ActiveSounds[moby->m_SoundChannel & 0x7F].m_Pitch;
      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) ==
          MOBY_DAMAGE_FLAME) {
        moby->m_UpdateDistance = 0xFF;
        PlaySound(g_Models[moby->m_Class]->m_Sounds[1], moby, 8,
                  &moby->m_SoundChannel);
        if (moby->m_SoundChannel != 0x7F) {
          g_Spu.m_ActiveSounds[moby->m_SoundChannel & 0x7F].m_Pitch =
              targetPitch + props->m_0x08 * 4;
        }
      }
      if (props->m_0x08 < 0x19) {
        func_800562A4(moby, 1);
      }
      if (moby->m_Substate == 0) {
        props->m_0x00 = g_SpawnMoby(392, moby);
        props->m_0x00->m_RenderRadius = 0x1A;
        moby->m_UpdateDistance = 0x10;
        moby->m_Substate = 1;
        break;
      }
      if (props->m_0x0c != 0) {
        props->m_0x0c--;
      }
      if (props->m_0x0c == 0 && (moby->m_DamageFlags & MOBY_DAMAGE_FLAME)) {
        props->m_0x0c = 0x10;
        props->m_0x08 += 100;
      }
      props->m_0x10 = ApplyFlameHeatExternal(moby, props->m_0x10);
      props->m_0x08--;
      if (targetPitch < currentPitch && moby->m_SoundChannel != 0x7F) {
        g_Spu.m_ActiveSounds[moby->m_SoundChannel & 0x7F].m_PitchIncrease = -4;
      }
      if (props->m_0x08 < 0x18) {
        props->m_0x08 = 0x18;
        moby->m_UpdateDistance = 0x10;
      } else {
        moby->m_UpdateDistance = 0x40;
      }
      props->m_0x04 += (props->m_0x08 * g_DeltaTime) >> 1;
      props->m_0x00->m_Rotation.z = props->m_0x04 >> 4;
      if (props->m_0x08 >= 0xE1 || (moby->m_DamageFlags & MOBY_DAMAGE_SUPER)) {
        props->m_0x00->m_Substate = 1;
        func_8003851C(moby, 0, 0);
        for (i = 0; i < 2 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(310, moby);
          g_SpawnMoby(311, moby);
        }
        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(309, moby);
        }
        g_SpawnParticle(16, 70, &moby->m_Position, 0x18);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        func_80052568(moby);
      }
      moby->m_DamageFlags = 0;
      break;
    }
#endif
#ifdef HAS_MOBY_391
    case 391: { // Smoke Particle Spawner
      Moby391Props *props = moby->m_Props;
      Vector3D vertices[3];

      if (props->m_CollisionTriIndex < 0) {
        vertices[0].x = COSINE_8(moby->m_Rotation.z) >> 1;
        vertices[0].y = SINE_8(moby->m_Rotation.z) >> 1;
        vertices[0].z = 0;
        VecAdd(&vertices[0], &vertices[0], &moby->m_Position);

        if (func_8004AE38(&vertices[0], &moby->m_Position) != 0) {
          props->m_CollisionTriIndex = g_CollisionTriangleIndex;
          ColTriUnpack(props->m_CollisionTriIndex, vertices);
          VecAdd(&vertices[0], &vertices[0], &vertices[1]);
          VecAdd(&vertices[0], &vertices[0], &vertices[2]);
          vertices[0].x /= 3;
          vertices[0].y /= 3;
          vertices[0].z /= 3;
          VecSub(&props->m_CollisionTriOffset, &moby->m_Position, &vertices[0]);
        }
      } else {
        ColTriUnpack(props->m_CollisionTriIndex, vertices);
        VecAdd(&vertices[0], &vertices[0], &vertices[1]);
        VecAdd(&vertices[0], &vertices[0], &vertices[2]);
        vertices[0].x /= 3;
        vertices[0].y /= 3;
        vertices[0].z /= 3;
        VecAdd(&moby->m_Position, &vertices[0], &props->m_CollisionTriOffset);

        if (!(g_GameTick % 4)) {
          vertices[0].x = COSINE_8(moby->m_Rotation.z) >> 5;
          vertices[0].y = SINE_8(moby->m_Rotation.z) >> 5;
          vertices[0].z = 0x20;
          g_SpawnParticle(1, 14, &moby->m_Position, (int)&vertices[0]);
        }
      }

      break;
    }
#endif
#ifdef HAS_MOBY_392
    case 392: {
      Moby392Props *props;
      Moby *iter;
      Moby *bestMoby;
      Vector3D vec;
      int bestAngleDiff;
      int dist;
      int i;

      props = (Moby392Props *)moby->m_Props;

      if (moby->m_Substate == 1) {
        bestMoby = 0;
        bestAngleDiff = 0x180;
        iter = g_LevelMobys;

        while (iter < g_DynMobys) {
          if (iter != moby && iter->m_State < 0x80 &&
              iter->m_CollisionGroup != 0 && (int)iter->m_CollisionGroup < 0) {
            VecSub(&vec, &iter->m_Position, &moby->m_Position);
            dist = ABS2(vec.x) + ABS2(vec.y);
            if (dist < 0x6000) {
              dist = VecMagnitude(&vec, 0);
              if (dist >= 0x1000 && dist <= 0x3000 && vec.z >= -0x1000 &&
                  vec.z <= 0x1000) {
                dist = func_80017928(
                    Atan2(moby->m_Position.x - g_Spyro.m_Position.x,
                          moby->m_Position.y - g_Spyro.m_Position.y, 1),
                    Atan2(vec.x, vec.y, 1));
                if (dist < bestAngleDiff) {
                  bestAngleDiff = dist;
                  bestMoby = iter;
                }
              }
            }
          }
          iter++;
        }

        if (bestMoby != 0) {
          VecSub(&props->m_0x00, &bestMoby->m_Position, &moby->m_Position);
          props->m_0x00.z += 0x200;
          VecShiftRight(&props->m_0x00, 7);
        } else {
          VecSub(&props->m_0x00, &moby->m_Position, &g_Spyro.m_Position);
          props->m_0x00.z = 0;
          VecScaleToLength(&props->m_0x00, VecMagnitude(&props->m_0x00, 0),
                           0x50);
        }

        props->m_0x00.z += 0xA0;
        props->m_0x0c = 0;
        moby->m_Substate = 2;
        moby->m_RenderRadius = 0x20;
        moby->m_UpdateDistance = 0xFF;
        moby->m_Rotation.x = 0xA;
        moby->m_Rotation.y = 0;
        break;
      }

      if (moby->m_Substate == 2) {
        props->m_0x0c += g_DeltaTime;
        moby->m_Rotation.z += g_DeltaTime * 8;

        if (props->m_0x00.z > -160) {
          props->m_0x00.z -= (g_DeltaTime * 5) >> 1;
        }

        for (i = 0; i < g_DeltaTime; i++) {
          VecAdd(&moby->m_Position, &moby->m_Position, &props->m_0x00);
          if (moby->m_Position.z < 0) {
            func_80052568(moby);
          } else {
            moby->m_Position.z += 180;
            if (props->m_0x0c >= 5 &&
                (func_8004BE4C(&moby->m_Position, 180, 180) ||
                 func_8004E3C8(&moby->m_Position, 0x100, 0, 0x30000, moby,
                               0))) {
              func_8004E3C8(&moby->m_Position, 0x400, 0, 0x30000, moby, 0);
              for (i = 0; i < 2 && DYN_MOBY_FREE_COUNT > 20; i++) {
                g_SpawnMoby(310, moby);
                g_SpawnMoby(311, moby);
              }
              for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
                g_SpawnMoby(309, moby);
              }
              g_SpawnParticle(16, 70, &moby->m_Position, 0x18);
              func_8003851C(moby, 0, 0);
              func_80052568(moby);
            } else {
              moby->m_Position.z -= 0xB4;
            }
          }
        }
      }

      break;
    }
#endif
#ifdef HAS_MOBY_395
    case 395: {
      Moby395Props *props = moby->m_Props;
      int angle;
      int distance;

      if (moby->m_State != 3 &&
          (moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0) {
        props->m_0x06 = 200;
        props->m_0x0a = RandRange(-0xA, 0xA);
        props->m_0x0b = RandRange(-0xA, 0xA);
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        distance = DISTANCE_TO_SPYRO(moby);
        if (distance < 0x2000) {
          RotateMobyToSpyro(moby, 0xA, 0, 0);
        }
        if (g_LevelMobys[props->m_0x10].m_State < 5) {
          if (OctDistance(&moby->m_Position,
                          &g_LevelMobys[props->m_0x10].m_Position) < 0x1000) {
            moby->m_State = 5;
            MOBY_ANIM_CHANGE(moby, 5);
            continue;
          }
          break;
        }
        if (TICK_TIMER(props->m_0x20) && distance < 0x800) {
          moby->m_State = 8;
          MOBY_ANIM_CHANGE(moby, 8);
          continue;
        }
        break;
      }
      case 1: {
        if (g_LevelMobys[props->m_0x10].m_State >= 4) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        if (TICK_TIMER(props->m_0x04) &&
            OctDistance(&moby->m_Position, &props->m_0x14) < 0xDD) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        angle = ANGLE_FROM(PATH_CUR_POS(props->m_0x00), moby->m_Position);
        func_80038638(moby, &PATH_NODE_POS(props->m_0x00, 0), props->m_0x0c,
                      angle - 3, 0, props->m_0x06, 0x1E, 0x80, 0xFF, 0xFF, 0, 0,
                      4);
        break;
      }
      case 3: {
        if (moby->m_AnimationState.m_Animation == 3 && g_AnimationFinished &&
            moby->m_AnimationState.m_NextAnimation != 4) {
          g_AnimationFinished = 0;
          MOBY_ANIM_ADVANCE(moby, 4);
        }
        moby->m_Rotation.x += props->m_0x0a;
        moby->m_Rotation.y += props->m_0x0b;
        if (props->m_0x06 < -0xB3) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x20);
          func_80052568(moby);
          continue;
        }
        moby->m_Position.z += props->m_0x06;
        props->m_0x06 -= 0xF;
        break;
      }
      case 5: {
        RotateMobyToAngle(moby, g_LevelMobys[props->m_0x10].m_Rotation.z, 0x1E,
                          0, 0);
        if (g_AnimationFinished) {
          props->m_0x06 = 0xA0;
          props->m_0x04 = 0x3C;
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        break;
      }
      case 8: {
        RotateMobyToSpyro(moby, 4, 0, 0);
        if (g_AnimationFinished) {
          props->m_0x20 = 150;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#if defined(HAS_MOBY_397) || defined(HAS_MOBY_399)
#ifdef HAS_MOBY_397
    case 397: // Night/Icy Flight Lighthouse Light
#endif
#ifdef HAS_MOBY_399
    case 399: // Lit version
#endif
    {
      Moby397Props *props = moby->m_Props;

      // If Unlit and Flamed
      if (moby->m_Class == 397 && (moby->m_DamageFlags & MOBY_DAMAGE_FLAME)) {
        Moby *spawned;

        RegisterFlightMobyCollectibleType(props->m_LightCollectibleIndex);
        // +2 Seconds
        spawned = g_SpawnMoby(props->m_TimeRewardMobyIndex + 344, moby);
        if (spawned != 0) {
          spawned->m_State = 1;
        }

        if (props->m_EnvAnimID >= 0) {
          func_8002B390(props->m_EnvAnimID, 0xFC, 0);
        }

        moby->m_Class = 399;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_398
    case 398: {
      MobyPortalPathProps *props = moby->m_Props;
      PathData *p;
      int mag;
      short progressed;
      switch (moby->m_State) {
      case 1: {
        Vector3D vortexPathMidpoint;

        g_Spyro.m_ControlFlags =
            (0x80000000 | 0x2000 | 0x4000 | 0x100 | 0x40 | 0x4 | 0x2 | 0x1);
        g_Spyro.unk_0x248 = moby->m_Substate;
        g_Spyro.unk_0x240 = props->m_Path;
        g_Spyro.unk_0x244 = 0x60;
        g_Spyro.m_fallingState = 5;
        g_Spyro.m_sortingDepth = 0x7F;

        p = props->m_Path;
        VecAdd(&vortexPathMidpoint, &PATH_NODE_POS(p, 0), &PATH_NODE_POS(p, 1));
        VecShiftRight(&vortexPathMidpoint, 1);

        VecSub(&g_Spyro.unk_0x208, &vortexPathMidpoint, &g_Spyro.m_Position);
        VecAdd(&g_Spyro.unk_0x208, &g_Spyro.unk_0x208, &props->m_0x04);

        mag = VecMagnitude(&g_Spyro.unk_0x208, 1);
        if (mag > 128) {
          VecScaleToLength(&g_Spyro.unk_0x208, mag, 128);
        } else {
          if (moby->m_Substate != 0) {
            progressed = (props->m_Path->m_CurrentNode <
                          (props->m_Path->m_NodeCount - 1));
          } else {
            progressed = props->m_Path->m_CurrentNode;
          }

          if (progressed) {
            moby->m_State = 2;
          }
        }

        if (func_8004BE4C(&g_Camera.m_Position, 0x300, 0x300) != 0 &&
            (g_SurfaceBelowFlags & 0x3F) < 0x3F &&
            g_Environment.m_SurfaceData[g_SurfaceBelowFlags]->m_Type == 6) {
          moby->m_State = 0;
          g_Camera.unk_0xC0 = (0x80000000 | 0x10 | 0x2);
          g_Spyro.m_fallingState = 0xF;
          g_LoadStage = 0;
          g_LevelTransHudActive = 1;
          g_LevelTransTicks = 0;
          g_Gamestate = 1;
          g_StateSwitch = 1;
          g_Spyro.m_portalAngle.z = props->m_0x14;
          func_80033F08(&g_Camera.m_Position);
          g_Camera.m_Simulation.m_Coords.azimuth +=
              g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

          g_Spyro.m_Physics.m_SpeedAngle.m_RotZ += D_80075858;
          g_Spyro.m_bodyRotation.z = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4;
          g_Camera.m_Sphere = g_Camera.m_Simulation;
          g_Camera.m_Sphere.m_Coords.azimuth -= (g_Spyro.m_bodyRotation.z) << 4;
          func_80034204(&g_Camera.m_Position);
          VecAdd(&g_Camera.m_Position, &g_Camera.m_Position,
                 &g_Spyro.m_Position);
          func_800342F8();
          D_80075910 = D_800758FC;
          if (props->m_0x18 >= 0) {
            g_Camera.m_SphericalPreset = &D_8006CA24[props->m_0x18];
          } else {
            g_Camera.m_SphericalPreset = nullptr;
          }
        } else {
          g_Spyro.m_ControlFlags |= 0x400;
        }
        break;
      }
      case 2: {
        g_Spyro.m_ControlFlags = 0x80000000 | 0x4000 | 0x2000 | 0x100;
        g_Spyro.unk_0x240 = props->m_Path;
        g_Spyro.unk_0x244 = 0x60;
        g_Spyro.m_fallingState = 0xF;
        g_Spyro.m_sortingDepth = 0x7F;

        if (func_8004BE4C(&g_Camera.m_Position, 0x300, 0x300) != 0 &&
            (g_SurfaceBelowFlags & 0x3F) < 0x3F &&
            g_Environment.m_SurfaceData[g_SurfaceBelowFlags]->m_Type == 6) {
          moby->m_State = 0;
          g_Camera.unk_0xC0 = 0x80000000 | 0x10 | 0x2;
          g_LoadStage = 0;
          g_LevelTransHudActive = 1;
          g_LevelTransTicks = 0;
          g_Gamestate = 1;
          g_StateSwitch = 1;
          g_Spyro.m_portalAngle.z = props->m_0x14;
          func_80033F08(&g_Camera.m_Position);
          g_Camera.m_Simulation.m_Coords.azimuth +=
              g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

          g_Spyro.m_Physics.m_SpeedAngle.m_RotZ += D_80075858;
          g_Spyro.m_bodyRotation.z = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4;
          g_Camera.m_Sphere = g_Camera.m_Simulation;
          g_Camera.m_Sphere.m_Coords.azimuth -= g_Spyro.m_bodyRotation.z << 4;
          func_80034204(&g_Camera.m_Position);
          VecAdd(&g_Camera.m_Position, &g_Camera.m_Position,
                 &g_Spyro.m_Position);
          func_800342F8();
          D_80075910 = D_800758FC;
          if (props->m_0x18 >= 0) {
            g_Camera.m_SphericalPreset = &D_8006CA24[props->m_0x18];
          } else {
            g_Camera.m_SphericalPreset = nullptr;
          }
        } else {
          g_Spyro.m_ControlFlags |= 0x400;
        }
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_401
    case 401: {
      Moby401Props *props = moby->m_Props;

      if (props->m_0x00 != 0) {
        props->m_0x00 += g_DeltaTime;
        if (props->m_0x00 < 64) {
          moby->m_Rotation.x =
              props->m_0x04 + g_MobyShakeOffsets[props->m_0x00 >> 1][0];
          moby->m_Rotation.y =
              props->m_0x08 + g_MobyShakeOffsets[props->m_0x00 >> 1][1];
          moby->m_Position.z =
              props->m_0x0c +
              (ABS2(g_MobyShakeOffsets[props->m_0x00 >> 1][0]) +
               ABS2(g_MobyShakeOffsets[props->m_0x00 >> 1][1])) *
                  8;
        } else {
          props->m_0x00 = 0;
          moby->m_Rotation.x = props->m_0x04;
          moby->m_Rotation.y = props->m_0x08;
          moby->m_Position.z = props->m_0x0c;
        }
      }

      if (moby->m_DamageFlags & MOBY_DAMAGE_SUPER) {
        int i;

        moby->m_SoundDistance = 0x20;
        func_8003851C(moby, 0, 0);
        for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(310, moby);
          g_SpawnMoby(311, moby);
        }
        for (i = 0; i < 10 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(309, moby);
        }
        g_SpawnParticle(32, 70, &moby->m_Position, 0x18);
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        func_80052568(moby);
      } else {
        props->m_0x10 = ApplyFlameHeatExternal(moby, props->m_0x10);
        if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE)) &&
            props->m_0x00 == 0) {
          props->m_0x00 = 1;
          props->m_0x04 = moby->m_Rotation.x;
          props->m_0x08 = moby->m_Rotation.y;
          props->m_0x0c = moby->m_Position.z;
        }
      }
      moby->m_DamageFlags = 0;
      break;
    }
#endif
#ifdef HAS_MOBY_402
    case 402: {
      Moby402Props *props;

      props = moby->m_Props;

      if (props->m_0x18 == 1) {
        Vector3D delta;
        int angle;

        VecSub(&delta, &PATH_NODE_POS(props->m_0x14, 1),
               &PATH_NODE_POS(props->m_0x14, 0));
        angle = Atan2(VecMagnitude(&delta, 0), delta.z, 0);
        moby->m_Rotation.y = angle - ROTDEG8(90);

        if ((unsigned int)((angle + 0x40) & 0xFF) < 0x60) {
          moby->m_Rotation.y = 0xE0;
        }

        moby->m_Rotation.z = Atan2(delta.x, delta.y, 0);
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        props->m_0x18 = 2;
      }

      switch (moby->m_Substate) {
      case 0:
        if (props->m_0x00 >= 0 && g_LevelMobys[props->m_0x00].m_State >= 0x80) {
          func_80052568(moby);
          continue;
        }

        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          moby->m_Substate = 1;
          moby->m_UpdateDistance = 0xFF;
          moby->m_RenderRadius = 0x7F;
          continue;
        }
        break;

      case 1: {
        Vector3D particlePosition;
        Vector3D particleVelocity;

        props->m_0x10 += g_DeltaTime;

        if (props->m_0x10 < 0x5A) {
          particlePosition.x = 0;
          particlePosition.y = 0;
          particlePosition.z = 0x14C;
          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix,
                            &particlePosition, &particlePosition);
          VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
          particleVelocity.x = 0;
          particleVelocity.y = 6;
          particleVelocity.z = -0xC;
          VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix,
                            &particleVelocity, &particleVelocity);
          particleVelocity.x += (rand() & 0xF) - 8;
          particleVelocity.y += (rand() & 0xF) - 8;
          g_SpawnParticle(1, 74, &particlePosition, (int)&particleVelocity);

          if (moby->m_SoundChannel == 0x7F) {
            func_8003851C(moby, 0, 0);
          }
          continue;
        }

        if (props->m_0x10 < 0xB4) {
          if ((props->m_0x10 & 3) <= ((props->m_0x10 + g_DeltaTime) & 3)) {
            particlePosition.x = 0;
            particlePosition.y = 0;
            particlePosition.z = 0x14C;
            VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix,
                              &particlePosition, &particlePosition);
            VecAdd(&particlePosition, &particlePosition, &moby->m_Position);
            particleVelocity.x = 0;
            particleVelocity.y = ((props->m_0x10 - 0x5A) >> 3) + 9;
            particleVelocity.z = -0x12 - ((props->m_0x10 - 0x5A) >> 2);
            VecRotateByMatrix((MATRIX *)&moby->m_RotationMatrix,
                              &particleVelocity, &particleVelocity);
            g_SpawnParticle(1, 0, &particlePosition, (int)&particleVelocity);

            if (moby->m_Rotation.x < 0x80) {
              moby->m_Rotation.x = -((props->m_0x10 - 0x5A) >> 5);
            } else {
              moby->m_Rotation.x = (props->m_0x10 - 0x5A) >> 5;
            }

            continue;
          }
        }

        if (props->m_0x10 < 0xB5) {
          continue;
        }

        moby->m_Substate = 2;
        moby->m_RenderRadius = 0x40;
        moby->m_UpdateDistance = 0x40;
        props->m_0x14->m_CurrentNode = 1;
        props->m_0x10 = 0;
        VecNull(&props->m_0x04);
        func_8003851C(moby, 1, 0);
        continue;
      }

      case 2: {
        Vector3D delta;
        Vector3D velocityPart;
        Moby *parent;
        int magnitude;

        if (props->m_0x10 == 4) {
          VecSub(&delta, &PATH_CUR_POS(props->m_0x14), &moby->m_Position);
          VecCopy(&props->m_0x04, &delta);
          props->m_0x14->m_CurrentNode++;

          if (props->m_0x14->m_CurrentNode == props->m_0x14->m_NodeCount) {
            parent = &g_LevelMobys[props->m_0x00];

            if (props->m_0x00 > 0) {
              parent->m_UpdateDistance = 0xFF;
              parent->m_DamageFlags |= MOBY_DAMAGE_SUPER;
            }

            func_80052568(moby);
          }

          props->m_0x10 = 0;
        } else if (props->m_0x10 == 3) {
          VecSub(&delta, &PATH_CUR_POS(props->m_0x14), &moby->m_Position);
          VecShiftRight(&delta, 1);
          props->m_0x10++;
        } else {
          VecSub(
              &delta, &PATH_CUR_POS(props->m_0x14),
              &PATH_NODE_POS(props->m_0x14, props->m_0x14->m_CurrentNode - 1));
          VecMult(&delta, &delta, SINE_8(props->m_0x10 * 2 - 6));
          VecMult(&velocityPart, &props->m_0x04, SINE_8(props->m_0x10 * 2 - 5));
          VecAdd(&delta, &delta, &velocityPart);
          VecShiftRight(&delta, 10);
          props->m_0x10++;
        }

        VecMagnitude(&delta, 1);
        moby->m_Rotation.z = Atan2Fast(delta.x, delta.y);
        magnitude = VecMagnitude(&delta, 0);
        moby->m_Rotation.y = -Atan2Fast(delta.z, magnitude);
        VecAdd(&moby->m_Position, &moby->m_Position, &delta);
        VecNull(&delta);
        g_SpawnParticle(1, 0, &moby->m_Position, (int)&delta);
        break;
      }
      }

      break;
    }
#endif
#ifdef HAS_MOBY_403
    case 403: {
      Moby403Props *props;
      Vector3D delta;
      int distance;

      props = moby->m_Props;

      VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
      distance = DISTANCE_TO_SPYRO(moby);

      if (distance < 13000) {
        distance = VecMagnitude(&delta, 0);
      }

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 2 && moby->m_State != 30) {
        moby->m_DamageFlags = 0;
        props->m_0x38 = 0x50;
        props->m_0x08 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x10 = 100;

        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          props->m_0x0c = 0xF0;
        } else {
          props->m_0x0c = 0x140;
        }

        if (props->m_0x20 != 0) {
          func_80052568(props->m_0x20);
          props->m_0x20 = 0;

          if (g_Sparx != 0 && props->m_0x28 != 0) {
            g_Sparx->m_Substate = 0;
          }
        }

        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        int oldNode;
        int nearestNode;
        int temp;
        PathData *path;

        if (distance < 0x2000) {
          if (TICK_TIMER(props->m_0x24) && SPYRO_BASE_Z_DISTANCE(moby) < 1500 &&
              func_80017908(g_Camera.m_Rotation.z >> 4,
                            ANGLE_FROM(g_Camera.m_Position, moby->m_Position)) <
                  0x28 &&
              distance < 3200 &&
              func_80017908(moby->m_Rotation.z,
                            ANGLE_TO_SPYRO(moby->m_Position)) < 0x14) {
            Vector3D point0;
            Vector3D point1;

            props->m_0x20 = g_SpawnMoby(31, moby);
            func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
            func_80052D64(moby, 0, &point0);
            func_80052D64(moby, 1, &point1);
            VecAdd(&props->m_0x20->m_Position, &point0, &point1);
            VecShiftRight(&props->m_0x20->m_Position, 1);
            VecSub(&point0, &props->m_0x20->m_Position, &g_Spyro.m_Position);
            temp = 0x1C000 / VecMagnitude(&point0, 1);
            if (temp < 5) {
              temp = 5;
            }
            if (temp > 0x7F) {
              temp = 0x7F;
            }
            props->m_0x20->m_ScaleOverride = temp;
            props->m_0x20->m_Rotation.z = moby->m_Rotation.z;
            moby->m_State = 20;
            continue;
          }
        }

        if (props->m_0x00 == 0) {
          if (distance > 0x2000) {
            if (TICK_TIMER(props->m_0x18)) {
              path = props->m_0x04;
              oldNode = path->m_CurrentNode;

              do {
                props->m_0x04->m_CurrentNode =
                    RandRange(0, path->m_NodeCount - 1);
                path = props->m_0x04;
              } while (oldNode == path->m_CurrentNode);

              moby->m_State = 10;
              continue;
            }
          } else if (distance >= 0xFA1) {
            func_80038AFC(props->m_0x04, &nearestNode);

            if (props->m_0x04->m_CurrentNode != nearestNode &&
                distance - OctDistance(
                               &g_Spyro.m_Position,
                               &PATH_NODE_POS(props->m_0x04, nearestNode)) >
                    1500) {
              props->m_0x04->m_CurrentNode = nearestNode;
              moby->m_State = 10;
              continue;
            }
          }
        }

        if (func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) >= 0x13) {
          moby->m_State = 15;
          continue;
        }

        break;
      }

      case 2: {
        Moby *spawned;
        int floorHeight;

        MoveMobyWithGravity(moby, &props->m_0x0c, props->m_0x08, &props->m_0x10,
                            0xC, 0x10);

        if ((g_SurfaceBelowFlags & 0x3F) == 0) {
          floorHeight = func_80038340(moby);
          if (MOBY_BASE_Z_DISTANCE(moby, floorHeight) < 100) {
            spawned = g_SpawnMoby(400, moby);
            PlaySound(g_Spu.m_SoundTable->waterSplash, moby, 8,
                      &moby->m_SoundChannel);
            spawned->m_ScaleOverride = 0x34;
            props->m_0x24 = 0xA;
            moby->m_State = 30;
            continue;
          }
        }

        if (TICK_TIMER(props->m_0x38) || g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          func_80052568(moby);
          continue;
        }

        break;
      }

      case 4: {
        moby->m_Rotation.z += 5;

        if (TICK_TIMER(props->m_0x18) && g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        break;
      }

      case 10: {
        int angle;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

        if (DISTANCE_TO_SPYRO(moby) < 0xDAC) {
          moby->m_State = 15;
          continue;
        }

        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x04));

        if (RotateMobyToAngle(moby, angle, 3, 2, 1) != 0 &&
            g_AnimationFinished) {
          props->m_0x1c =
              OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x04)) / 20;
          moby->m_State++;
        }

        break;
      }

      case 11: {
        func_80039398(moby, props->m_0x1c, 0, 0, 5);

        if (g_AnimationFinished) {
          props->m_0x18 = RandRange(0x28, 0x5A);
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        break;
      }

      case 15: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);

        if (RotateMobyToSpyro(moby, 8, 2, 1) != 0 && g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        break;
      }

      case 20: {
        Vector3D point0;
        Vector3D point1;
        int var;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);

        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        func_80052D64(moby, 0, &point0);
        func_80052D64(moby, 1, &point1);
        VecAdd(&props->m_0x20->m_Position, &point0, &point1);
        VecShiftRight(&props->m_0x20->m_Position, 1);
        VecSub(&point0, &props->m_0x20->m_Position, &g_Spyro.m_Position);
        var = VecMagnitude(&point0, 1) + 500;

        if (var < 1400) {
          var = 1400;
        }
        if (var > 3200) {
          var = 3200;
        }

        var = 0x1C000 / var;

        if (var < 5) {
          var = 5;
        }
        if (var > 0x7F) {
          var = 0x7F;
        }

        props->m_0x20->m_ScaleOverride = var;

        if (moby->m_AnimationState.m_NextFrame < 2) {
          props->m_0x20->m_RenderRadius = 0;
        } else {
          props->m_0x20->m_RenderRadius = 0x20;
        }

        if (moby->m_AnimationState.m_NextFrame >= 4 && distance < 3200) {
          g_Spyro.m_DamageFlags |= 7;
        }

        moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);
        props->m_0x20->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);
        props->m_0x20->m_Rotation.y =
            Atan2(DISTANCE_TO_SPYRO(props->m_0x20),
                  g_Spyro.m_Position.z - props->m_0x20->m_Position.z, 0);
        props->m_0x20->m_Rotation.y =
            func_80038098(props->m_0x20->m_Rotation.y, 0, 0x20);

        if (g_AnimationFinished) {
          func_80052568(props->m_0x20);
          props->m_0x20 = 0;
          props->m_0x24 = 0xB4;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        break;
      }

      case 30: {
        if (TICK_TIMER(props->m_0x24)) {
          func_80052568(moby);
          continue;
        }

        moby->m_Position.z -= 100;
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_407
    case MOBYCLASS_FLIGHT_TRAIN: {
      Vector3D particlePosition;
      Moby407Props *props = moby->m_Props;

      // Check for Barrel explosion damage, typed as Super
      if ((moby->m_DamageFlags & MOBY_DAMAGE_SUPER) && moby->m_State != 1) {
        // Let the train keep going for 0.33s after it took damage
        props->m_LifetimeAfterDamage = 20;
        moby->m_State = 1;
      }

      if (g_Spyro.m_walkingState < 8) {
        func_8003BFC0(moby, props->m_Path, &props->m_0x08, &props->m_0x04, 0x10,
                      4);
        func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
        if (!(g_GameTick % 4)) {
          func_80052D64(moby, 3, &particlePosition);
          g_SpawnParticle(1, 19, &particlePosition, 0);
        }
      }

      switch (moby->m_State) {
      case 0:
        break;
      case 1:
        if (TICK_TIMER(props->m_LifetimeAfterDamage)) {
          int i;

          for (i = 0; i < 3 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(481, moby);
            g_SpawnMoby(482, moby);
          }

          g_SpawnMoby(362, moby);
          func_80052568(moby);
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_408
    case 408: {
      Moby408Props *props = moby->m_Props;

      if ((moby->m_DamageFlags & MOBY_DAMAGE_SUPER) && moby->m_State != 1) {
        // TODO: Necessary?
        Vector3D padvec1;
        Vector3D padvec2;
        Vector3D padvec3;

        props->m_LifetimeAfterDamage = 15;
        moby->m_State = 1;
      }

      if (g_Spyro.m_walkingState < 8) {
        func_8003BFC0(moby, props->m_Path, &props->m_0x08, &props->m_0x04, 0x10,
                      4);
      }

      switch (moby->m_State) {
      case 0:
        break;
      case 1:
        if (TICK_TIMER(props->m_LifetimeAfterDamage)) {
          int i;

          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);

          for (i = 0; i < 3 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(481, moby);
            g_SpawnMoby(482, moby);
          }

          g_SpawnMoby(362, moby);
          func_80052568(moby);
        }
        break;
      }
      break;
    }
#endif
#ifdef HAS_MOBY_412
    case 412: {
      Moby412Props *props;
      int angle;

      props = (Moby412Props *)moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) &&
          moby->m_State != 2) {
        moby->m_DamageFlags = 0;

        angle = ANGLE_FROM_SPYRO(moby->m_Position);

        props->m_0x24 =
            func_80038178(angle, g_Spyro.m_bodyRotation.z, 0x20, 0x40);

        if (moby->m_DamageFlags & MOBY_DAMAGE_FLAME) {
          props->m_0x28 = 150;
        } else {
          props->m_0x28 = 300;
        }

        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);

        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        break;
      }

      func_80038458(moby);
      func_800533D0(moby);

      switch (moby->m_State) {
      case 0:
        if (TICK_TIMER(props->m_0x20)) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        func_80039AA8(moby, &props->m_Wander);
        break;

      case 1:
        func_80038458(moby);

        if (g_AnimationFinished) {
          props->m_0x20 = RandRange(0x78, 0xf0);
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;

      case 2:
        MoveMobyWithGravity(moby, &props->m_0x28, props->m_0x24, 0, 0xc, 0);

        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x10);
          func_80052568(moby);
          continue;
        }
        break;
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);

      break;
    }
#endif
#ifdef HAS_MOBY_413
    case 413: {
      Moby413Props *props = moby->m_Props;
      int i;

      func_80038458(moby);
      func_800533D0(moby);

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 2) {
        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(502, moby);
        }
        props->m_0x24 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x20 = 0xFA;
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        moby->m_State = 2;
        MOBY_ANIM_CHANGE(moby, 2);
        continue;
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0: {
        if (TICK_TIMER(props->m_0x28)) {
          moby->m_State = 1;
          MOBY_ANIM_CHANGE(moby, 1);
          continue;
        }
        func_80039AA8(moby, &props->m_Wander);
        if (TICK_TIMER(props->m_0x2c)) {
          props->m_0x2c = (rand() & 0x3F) + 0x78;
          func_8003851C(moby, 3, 0);
        }
        break;
      }
      case 1: {
        if (TICK_TIMER(props->m_0x2c)) {
          props->m_0x2c = (rand() & 0x1F) + 0x50;
          func_8003851C(moby, rand() % 3, 0);
        }
        if (g_AnimationFinished) {
          props->m_0x28 = RandRange(0x78, 0xF0);
          props->m_0x2c = 0;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }
      case 2: {
        MoveMobyWithGravity(moby, &props->m_0x20, props->m_0x24, 0, 0xC, 0);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x10);
          func_80052568(moby);
          continue;
        }
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_414 // Spyro Moby after last hit on Gnasty
    case 414: {
      Moby414Props *props = moby->m_Props;
      RotateMobyToAngle(
          moby, ANGLE_FROM(moby->m_Position, props->m_Target->m_Position), 4, 0,
          0);
      break;
    }
#endif
#ifdef HAS_MOBY_416
    case 416: { // Balloon
      Moby416Props *props = moby->m_Props;

      if (moby->m_State == 0) {
        props->m_BobCenterZ = moby->m_Position.z;
        moby->m_State = 1;
      } else {
        moby->m_Position.z =
            props->m_BobCenterZ + (SINE_8(moby->m_Substate) >> 4);
        moby->m_Substate += g_DeltaTime;
      }

      break;
    }
#endif
#ifdef HAS_MOBY_417
    case 417: { // TODO: return when PK Cannon and Cannon ball Mobys are
                // understood
      Moby417Props *props = moby->m_Props;
      int i;

      // If this is the breakable wall target and it has been "collected"
      // (=broken) before
      if (props->m_0x00 == 1 && moby->m_DropMoby == 0xFF) {
        func_8002B390(0, 0xFC, 0);
        func_80052568(moby);
      } else if (moby->m_Substate == 1) {
        if (props->m_0x00 == 0) {
          func_80052568(moby);
        } else if (props->m_0x00 == 1) {
          PlaySound(g_Spu.m_SoundTable->sound_0x1c, moby, 0x10, 0);
          func_8003B854(0, moby);

          for (i = 0; i < 4 && DYN_MOBY_FREE_COUNT > 20; i++) {
            g_SpawnMoby(454, moby);
            g_SpawnMoby(455, moby);
            g_SpawnMoby(456, moby);
          }

          g_SpawnParticle(8, 23, &moby->m_Position, 0);
          func_8002B390(0, 0xFC, 0);
          func_80052568(moby);
        }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_421
    case 421: {
      Moby421Props *props;
      Moby *drop;
      int i;

      props = moby->m_Props;

      if (props->m_0x14 == 1) {
        func_80038458(moby);
        func_800533D0(moby);
      }

      if (moby->m_State == 0) {
        props->m_0x04 += g_DeltaTime;

        if (props->m_0x04 > 480) {
          props->m_0x04 = 0;

          moby->m_Rotation.x = props->m_0x08;
          moby->m_Rotation.y = props->m_0x0c;
          moby->m_Position.z = props->m_0x10;

          moby->m_State = 1;
          moby->m_AnimationState.m_FrameProgress = 8;
          moby->m_AnimationState.m_PerFrameProgress = 8;
          moby->m_AnimationState.m_NextAnimation = 1;

          props->m_0x00 = g_SpawnMoby(422, moby);

          props->m_0x00->m_Rotation.x = moby->m_Rotation.x;
          props->m_0x00->m_Rotation.y = moby->m_Rotation.y;
          props->m_0x00->m_Rotation.z = moby->m_Rotation.z;
          props->m_0x00->m_AnimationState.m_PerFrameProgress = 0x10;
          props->m_0x00->m_UpdateDistance = 0;
          props->m_0x00->m_RenderRadius = 0;
          props->m_0x00->m_WasDrawn = 0;
          props->m_0x00->m_DepthOffset = 5;

          func_8003851C(moby, 0, 0);
        } else if (props->m_0x04 >= 416) {
          moby->m_Rotation.x =
              props->m_0x08 + g_MobyShakeOffsets[(props->m_0x04 - 416) >> 1][0];
          moby->m_Rotation.y =
              props->m_0x0c + g_MobyShakeOffsets[(props->m_0x04 - 416) >> 1][1];
          moby->m_Position.z =
              props->m_0x10 +
              (ABS2(g_MobyShakeOffsets[(props->m_0x04 - 416) >> 1][0]) +
               ABS2(g_MobyShakeOffsets[(props->m_0x04 - 416) >> 1][1])) *
                  6;

          if (moby->m_SoundChannel == 0x7f) {
            func_8003851C(moby, 1, 0);
          }
        } else if (props->m_0x04 >= 412) {
          props->m_0x08 = moby->m_Rotation.x;
          props->m_0x0c = moby->m_Rotation.y;
          props->m_0x10 = moby->m_Position.z;

          if (props->m_0x14 == 1) {
            props->m_0x04 = 0;
          }
        }
      } else {
        if (moby->m_AnimationState.m_Animation == 1) {
          props->m_0x04 += g_DeltaTime;
          props->m_0x00->m_RenderRadius = 0x10;
          props->m_0x00->m_UpdateDistance = 0xff;
        }

        if (props->m_0x04 >= 0xe6) {
          func_80052568(props->m_0x00);
          props->m_0x04 = rand() & 0xff;

          moby->m_AnimationState.m_FrameProgress = 8;
          moby->m_State = 0;
          moby->m_AnimationState.m_PerFrameProgress = 8;
          moby->m_AnimationState.m_NextAnimation = 0;

          if (moby->m_SoundChannel == 0x7f) {
            func_8003851C(moby, 3, 0);
          }
        }
      }

      if (moby->m_DamageFlags &
          (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) {
        drop = (Moby *)func_8003ABC0(moby, 5, 0, 0);
        if (props->m_0x14 == 1) {
          MobyCollectableProps *dropProps;
          dropProps = drop->m_Props;
          dropProps->m_SpawnState = props->m_0x14;
        }

        moby->m_SoundDistance = 0x20;
        func_8003851C(moby, 4, 0);

        for (i = 0; i < 2 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(423, moby);
          g_SpawnMoby(424, moby);
        }

        for (i = 0; i < 6 && DYN_MOBY_FREE_COUNT > 20; i++) {
          g_SpawnMoby(425, moby);
        }

        for (i = 0; i < 8; i++) {
          Vector3D vec;
          vec.x = (COSINE_8(i << 5) >> 8) * 3;
          vec.y = (SINE_8(i << 5) >> 8) * 3;
          vec.z = 0x18;
          g_SpawnParticle(1, 0, &moby->m_Position, (int)&vec);
        }

        g_SpawnParticle(16, 70, &moby->m_Position, 0x18);

        if (moby->m_State == 1) {
          func_80052568(props->m_0x00);
        }

        // Bug: Rather than passing the address of m_SoundChannel, it is passed
        // as a value Cast to prevent compiler warning
        PlaySound(g_Models[moby->m_Class]->m_Sounds[2], moby, 8,
                  (u_char *)(int)moby->m_SoundChannel);
        func_80052568(moby);
      }
      break;
    }
#endif
    case MOBYCLASS_LETTER_APOSTROPHE:
    case MOBYCLASS_LETTER_A: // Text A-Z
    case MOBYCLASS_LETTER_B:
    case MOBYCLASS_LETTER_C:
    case MOBYCLASS_LETTER_D:
    case MOBYCLASS_LETTER_E:
    case MOBYCLASS_LETTER_F:
    case MOBYCLASS_LETTER_G:
    case MOBYCLASS_LETTER_H:
    case MOBYCLASS_LETTER_I:
    case MOBYCLASS_LETTER_J:
    case MOBYCLASS_LETTER_K:
    case MOBYCLASS_LETTER_L:
    case MOBYCLASS_LETTER_M:
    case MOBYCLASS_LETTER_N:
    case MOBYCLASS_LETTER_O:
    case MOBYCLASS_LETTER_P:
    case MOBYCLASS_LETTER_Q:
    case MOBYCLASS_LETTER_R:
    case MOBYCLASS_LETTER_S:
    case MOBYCLASS_LETTER_T:
    case MOBYCLASS_LETTER_U:
    case MOBYCLASS_LETTER_V:
    case MOBYCLASS_LETTER_W:
    case MOBYCLASS_LETTER_X:
    case MOBYCLASS_LETTER_Y:
    case MOBYCLASS_LETTER_Z: {
      MobyLetterProps *letterProps = moby->m_Props;

      if (letterProps->m_Parent->m_State == 0 ||
          letterProps->m_Parent->m_Substate != moby->m_State) {
        func_80052568(moby);
      } else if (letterProps->m_Parent->m_Class == 9) {
        if (DISTANCE_TO_SPYRO(letterProps->m_Parent) < 0x400) {
          int previousCos;
          previousCos = COSINE_8(moby->m_Substate);
          moby->m_Substate += 8;
          moby->m_Rotation.z = moby->m_Rotation.z - FIXED_MUL(previousCos, 24) +
                               FIXED_MUL(COSINE_8(moby->m_Substate), 24);
        } else {
          // TODO: used for multiple purposes? review name
          int angle;
          Vector3D forwardOffset;
          Vector3D spacingStep;
          Vector3D centerOffset;
          Vector3D vec;

          moby->m_Substate += 8;
          angle = ANGLE_TO_SPYRO(letterProps->m_Parent->m_Position);
          forwardOffset.x = FIXED_MUL(COSINE_8(angle), 768);
          forwardOffset.y = FIXED_MUL(SINE_8(angle), 768);
          forwardOffset.z = 0;
          spacingStep.x = COSINE_8((angle + ROTDEG8(90)) & 0xFF) >> 5;
          spacingStep.y = SINE_8((angle + ROTDEG8(90)) & 0xFF) >> 5;
          spacingStep.z = 0;
          angle = (angle + ROTDEG8(180)) & 0xFF;
          moby->m_Rotation.z =
              angle + FIXED_MUL(COSINE_8(moby->m_Substate), 24);
          VecMult(&centerOffset, &spacingStep, letterProps->m_Len - 1);
          VecShiftLeft(&spacingStep, 1);
          angle = 2;
          angle = (letterProps->m_Len - 1) * angle;
          centerOffset.z += FIXED_MUL(COSINE_8(angle), 1536);
          vec.x = forwardOffset.x * COSINE_8(angle);
          vec.y = forwardOffset.y * COSINE_8(angle);
          vec.z = 0;
          angle = (angle - letterProps->m_Index * 4) & 0xFF;
          VecMult(&spacingStep, &spacingStep, letterProps->m_Index);
          VecSub(&centerOffset, &centerOffset, &spacingStep);
          moby->m_Position.x = forwardOffset.x * COSINE_8(angle);
          moby->m_Position.y = forwardOffset.y * COSINE_8(angle);
          moby->m_Position.z = 0;
          VecSub(&moby->m_Position, &moby->m_Position, &vec);
          VecShiftRight(&moby->m_Position, 10);
          VecAdd(&moby->m_Position, &moby->m_Position, &forwardOffset);
          VecAdd(&moby->m_Position, &moby->m_Position,
                 &letterProps->m_Parent->m_Position);
          VecSub(&moby->m_Position, &moby->m_Position, &centerOffset);
          moby->m_Position.z =
              moby->m_Position.z + FIXED_MUL(COSINE_8(angle), 1536) + 0x600;
        }
      } else {
        moby->m_Substate += 8;
        moby->m_Rotation.z =
            moby->m_FloorDistance + FIXED_MUL(COSINE_8(moby->m_Substate), 24);
      }
      break;
    }
#ifdef HAS_MOBY_453
    case 453: {
      Moby453Props *props = moby->m_Props;
      int i;
      int angle;
      int spyroAngle;
      int angleDiff;
      int maxAngleDiff;
      int bestNode;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE |
                                  MOBY_DAMAGE_FROM_MOBY | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 2) {
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) != 0) {
          props->m_0x10 = ANGLE_FROM(g_LevelMobys[props->m_0x24].m_Position,
                                     moby->m_Position);
          props->m_0x14 = 0x8C;
          props->m_0x18 = 0x23;
        } else {
          props->m_0x10 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
          props->m_0x14 = 200;
          props->m_0x18 = 0x32;
          if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
            props->m_0x14 += 0x46;
            props->m_0x18 += 0x32;
          }
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
        }
        if (moby->m_AnimationState.m_NextAnimation != 2) {
          g_AnimationFinished = 0;
          moby->m_AnimationState.m_FrameProgress = 0x10;
          moby->m_AnimationState.m_PerFrameProgress = 0x10;
          moby->m_AnimationState.m_NextAnimation = 2;
          moby->m_AnimationState.m_NextFrame = 0;
          func_80037E98(moby);
        }
        moby->m_State = 2;
        continue;
      }

      moby->m_DamageFlags = 0;

      switch (moby->m_State) {
      case 0: {
        if (TICK_TIMER(props->m_0x44)) {
          props->m_0x44 = (rand() & 0x1F) + 0x50;
          func_8003851C(moby, rand() % 3, 0);
        }

        if (props->m_0x1c == 1 && DISTANCE_TO_SPYRO(moby) < 0x1000) {
          moby->m_State = 10;
          continue;
        }

        if (DISTANCE_TO_SPYRO(moby) < 5000) {
          spyroAngle = ANGLE_TO_SPYRO(moby->m_Position);
          maxAngleDiff = 0;
          for (i = 0; i < props->m_0x0c->m_NodeCount; i++) {
            if (i != props->m_0x0c->m_CurrentNode) {
              angle =
                  ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x0c, i));
              angleDiff = func_80017908(spyroAngle, angle);
              if (maxAngleDiff < angleDiff) {
                maxAngleDiff = angleDiff;
                bestNode = i;
              }
            }
          }

          if (maxAngleDiff >= 0x41) {
            props->m_0x0c->m_CurrentNode = bestNode;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        }
        break;
      }

      case 1: {
        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x0c));
        if (TICK_TIMER(props->m_0x44)) {
          props->m_0x44 = (rand() & 0x1F) + 0x50;
          func_8003851C(moby, rand() % 3, 0);
        }
        if (RotateMobyToAngle(moby, angle, 6, 0x14, 1)) {
          func_80039688(moby, angle, 0x50, 0, 300, 5);
          if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x0c)) <
              0x100) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        }
        break;
      }

      case 2: {
        MoveMobyWithGravity(moby, &props->m_0x14, props->m_0x10, &props->m_0x18,
                            0xC, 0x10);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x10);
          func_80052568(moby);
          continue;
        }
        break;
      }

      case 10: {
        if (g_Spyro.m_airTime == 0) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          if (func_80039E94(moby, props->m_0x0c, 0x100, 0x78, 0, 8, 0x28, 0xFF,
                            5) == 0x100) {
            g_LevelMobys[props->m_0x20].m_Substate = 1;
            moby->m_State = 11;
            continue;
          }
        }
        break;
      }

      case 11: {
        if (TICK_TIMER(props->m_0x44)) {
          props->m_0x44 = (rand() & 0x3F) + 0x78;
          func_8003851C(moby, rand() % 3, 0);
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#if defined(HAS_MOBY_454) || defined(HAS_MOBY_455) || defined(HAS_MOBY_456)
#ifdef HAS_MOBY_454
    case 454:
#endif
#ifdef HAS_MOBY_455
    case 455:
#endif
#ifdef HAS_MOBY_456
    case 456:
#endif
    {
      MobyFragmentProps *props;

      props = moby->m_Props;

      if (!TICK_TIMER(props->m_Lifetime) && moby->m_Position.z >= 2000 &&
          moby->m_WasDrawn) {

        moby->m_Position.x += props->m_Velocity.x;
        moby->m_Position.y += props->m_Velocity.y;
        props->m_Velocity.z -= 0x10;

        if (props->m_Velocity.z < -0x140) {
          props->m_Velocity.z = -0x140;
        }

        moby->m_Position.z += props->m_Velocity.z;
        moby->m_Rotation.x += props->m_AngularVelocity.x;
        moby->m_Rotation.y += props->m_AngularVelocity.y;
        moby->m_Rotation.z += props->m_AngularVelocity.z;
        props->m_Lifetime--;
      } else {
        func_80052568(moby);
      }
      break;
    }
#endif
#if defined(HAS_MOBY_458) || defined(HAS_MOBY_459)
#ifdef HAS_MOBY_458
    case 458:
#endif
#ifdef HAS_MOBY_459
    case 459:
#endif
    {
      MobyFragmentProps *props = moby->m_Props;

      if (props->m_Lifetime > 0 && moby->m_WasDrawn) {
        if (func_8004BE4C(&moby->m_Position, 0x100, 0x100)) {
          int dot;
          func_80017330(&g_CollisionNormal, 0x1000);
          dot = (props->m_Velocity.x * g_CollisionNormal.x +
                 props->m_Velocity.y * g_CollisionNormal.y +
                 props->m_Velocity.z * g_CollisionNormal.z) >>
                11;
          if (dot < 0) {
            VecScaleToLength(&g_CollisionNormal, 0x1000, (dot >> 2) - dot);
            props->m_Velocity.x += g_CollisionNormal.x;
            props->m_Velocity.y += g_CollisionNormal.y;
            props->m_Velocity.z += g_CollisionNormal.z;
          }
        }
        moby->m_Position.x += props->m_Velocity.x;
        moby->m_Position.y += props->m_Velocity.y;
        props->m_Velocity.z -= 6;
        if (props->m_Velocity.z < -0x80) {
          props->m_Velocity.z = -0x80;
        }
        moby->m_Position.z += props->m_Velocity.z;
        moby->m_Rotation.x += props->m_AngularVelocity.x;
        moby->m_Rotation.y += props->m_AngularVelocity.y;
        moby->m_Rotation.z += props->m_AngularVelocity.z;
        props->m_Lifetime--;
      } else {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_461
    case 461: {
      Moby461Props *props = moby->m_Props;

      if ((moby->m_DamageFlags &
           (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE | MOBY_DAMAGE_SUPER)) != 0 &&
          moby->m_State != 3 && moby->m_State != 4) {
        moby->m_DamageFlags = 0;
        props->m_0x10 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x18 = 0x46;
        props->m_0x1c = 0x32;
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          props->m_0x14 = 150;
        } else {
          props->m_0x14 = 300;
          props->m_0x18 = 0x82;
        }
        func_8003ABC0(moby, 3, 0, 0);
        func_8003B7C0(moby);
        func_8003851C(moby, 0, 0);
        moby->m_State = 3;
        MOBY_ANIM_CHANGE(moby, 3);
        break;
      }

      if (TICK_TIMER(props->m_0x08) == 2) {
        props->m_0x0c = 0x14;
        props->m_0x04 = props->m_0x20;
        func_800562A4(moby, 1);
      }

      if (props->m_0x08 == 0) {
        if (((func_8002B3F4(props->m_0x00) >> 8) & 0xFF) < 2) {
          D_800777C0[props->m_0x00] = 0;
        }
      }

      if (!TICK_TIMER(props->m_0x0c)) {
        func_8002B390(props->m_0x00, 0xFE, 1);
      }

      switch (moby->m_State) {
      case 0: {
        if (TICK_TIMER(props->m_0x04) == 2) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          continue;
        }
        break;
      }

      case 2: {
        if (moby->m_AnimationState.m_NextFrame >= 6 && props->m_0x08 == 0) {
          func_8002B390(props->m_0x00, 0xFC, 0);
          props->m_0x08 = 100;
          D_800777C0[props->m_0x00] = 1;
          PlaySound(g_Models[moby->m_Class]->m_Sounds[1], moby, 8,
                    &props->m_0x24);
        }
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }
        break;
      }

      case 3: {
        moby->m_Rotation.y += g_DeltaTime * 2;
        if (TICK_TIMER(props->m_0x1c) ||
            MoveMobyWithGravity(moby, &props->m_0x14, props->m_0x10,
                                &props->m_0x18, 0xC, 0xC) == 3) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x18);
          moby->m_RenderRadius = 0;
          moby->m_State = 4;
          continue;
        }
        break;
      }

      case 4: {
        if ((func_8002B3F4(props->m_0x00) & 2) != 0) {
          func_80052568(moby);
          continue;
        }
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_466
    case 466: {
      Moby466Props *props = moby->m_Props;
      int i;
      int angle;
      int spyroAngle;
      int angleDiff;
      int maxAngleDiff;
      int bestNode;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_CHARGE |
                                  MOBY_DAMAGE_FROM_MOBY | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 3) {
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FROM_MOBY) != 0) {
          props->m_0x10 = ANGLE_FROM(g_LevelMobys[props->m_0x24].m_Position,
                                     moby->m_Position);
          props->m_0x14 = 0x8C;
          props->m_0x18 = 0x23;
        } else {
          props->m_0x10 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                        g_Spyro.m_bodyRotation.z, 0x20, 0x40);
          props->m_0x14 = 200;
          props->m_0x18 = 0x32;
          if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
            props->m_0x14 += 0x46;
            props->m_0x18 += 0x32;
          }
          func_8003ABC0(moby, 3, 0, 0);
          func_8003B7C0(moby);
        }
        if (moby->m_AnimationState.m_NextAnimation != 3) {
          g_AnimationFinished = 0;
          moby->m_AnimationState.m_FrameProgress = 0x10;
          moby->m_AnimationState.m_PerFrameProgress = 0x10;
          moby->m_AnimationState.m_NextAnimation = 3;
          moby->m_AnimationState.m_NextFrame = 0;
          func_80037E98(moby);
        }
        moby->m_State = 3;
        continue;
      }

      moby->m_DamageFlags = 0;

      if (props->m_0x28 != -1 && D_800777C0[props->m_0x28] != 0 &&
          moby->m_State != 3 && moby->m_State != 4 &&
          func_80038C4C(&moby->m_Position, &props->m_0x2c) != 0) {
        moby->m_State = 4;
        MOBY_ANIM_CHANGE(moby, 4);
        continue;
      }

      switch (moby->m_State) {
      case 0: {
        if (TICK_TIMER(props->m_0x44)) {
          props->m_0x44 = (rand() & 0x1F) + 0x50;
          func_8003851C(moby, rand() % 3, 0);
        }

        if (props->m_0x1c == 1) {
          if (DISTANCE_TO_SPYRO(moby) < 0x1800) {
            moby->m_State = 10;
            continue;
          }
        }

        if (DISTANCE_TO_SPYRO(moby) < 5000) {
          spyroAngle = ANGLE_TO_SPYRO(moby->m_Position);
          maxAngleDiff = 0;
          for (i = 0; i < props->m_0x0c->m_NodeCount; i++) {
            if (i != props->m_0x0c->m_CurrentNode) {
              angle =
                  ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x0c, i));
              angleDiff = func_80017908(spyroAngle, angle);
              if (maxAngleDiff < angleDiff) {
                maxAngleDiff = angleDiff;
                bestNode = i;
              }
            }
          }

          if (maxAngleDiff >= 0x41) {
            props->m_0x0c->m_CurrentNode = bestNode;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            continue;
          }
        }
        break;
      }

      case 1: {
        angle = ANGLE_FROM(moby->m_Position, PATH_CUR_POS(props->m_0x0c));
        if (TICK_TIMER(props->m_0x44)) {
          props->m_0x44 = (rand() & 0x1F) + 0x50;
          func_8003851C(moby, rand() % 3, 0);
        }
        if (RotateMobyToAngle(moby, angle, 6, 0x14, 1)) {
          func_80039688(moby, angle, 0x50, 0, 300, 5);
          if (OctDistance(&moby->m_Position, &PATH_CUR_POS(props->m_0x0c)) <
              0x100) {
            moby->m_State = 0;
            MOBY_ANIM_CHANGE(moby, 0);
            continue;
          }
        }
        break;
      }

      case 2: {
        break;
      }

      case 3: {
        MoveMobyWithGravity(moby, &props->m_0x14, props->m_0x10, &props->m_0x18,
                            0xC, 0x10);
        if (g_AnimationFinished) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x10);
          func_80052568(moby);
          continue;
        }
        break;
      }

      case 4: {
        if (D_800777C0[props->m_0x28] == 0) {
          props->m_0x14 = 0;
          props->m_0x18 = 0;
          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);
          moby->m_State = 3;
          MOBY_ANIM_CHANGE(moby, 3);
          continue;
        }
        if (moby->m_AnimationState.m_NextFrame >= 0xF) {
          moby->m_AnimationState.m_Frame = 0;
          moby->m_AnimationState.m_NextFrame = 1;
          moby->m_AnimationState.m_FrameProgress = 0;
        }
        break;
      }

      case 5:
      case 6:
      case 7:
      case 8:
      case 9: {
        break;
      }

      case 10: {
        if (g_Spyro.m_airTime == 0) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 1);
          if (func_80039E94(moby, props->m_0x0c, 0x100, 0x78, 0, 8, 0x28, 0xFF,
                            5) == 0x100) {
            g_LevelMobys[props->m_0x20].m_Substate = 1;
            moby->m_State = 11;
            continue;
          }
        }
        break;
      }

      case 11: {
        if (TICK_TIMER(props->m_0x44)) {
          props->m_0x44 = (rand() & 0x3F) + 0x78;
          func_8003851C(moby, rand() % 3, 0);
        }
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_467
    case 467: {
      Moby467Props *props = moby->m_Props;
      int i;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          DISTANCE_TO_SPYRO(moby) < 3600 && moby->m_State != 6) {
        props->m_0x20 = 0xF0;
        props->m_0x1c = g_Spyro.m_bodyRotation.z;
        moby->m_DamageFlags = 0;
        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        func_800562A4(moby, 2);
        moby->m_State = 6;
        MOBY_ANIM_CHANGE(moby, 6);
        continue;
      }

      if (props->m_0x28 != 0) {
        for (i = 0; i < 3; i++) {
          if (props->m_0x2c[i] == 0) {
            props->m_0x2c[i] = g_SpawnMoby(343, moby);
            props->m_0x2c[i]->m_Substate = i;
          }
        }
      }

      switch (moby->m_State) {
      case 0:
        if (props->m_0x00 != 0) {
          moby->m_State = 8;
          MOBY_ANIM_CHANGE(moby, 8);
          continue;
        }

        if (props->m_0x28 == 0 &&
            DISTANCE_TO_SPYRO(moby) < (props->m_0x08 << 10)) {
          moby->m_State = 10;
          MOBY_ANIM_CHANGE(moby, 10);
          continue;
        }

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);

        RotateMobyToSpyro(moby, 4, 0, 0);
        if (DISTANCE_TO_SPYRO(moby) < 0x1C00 &&
            SPYRO_ORIGIN_Z_DISTANCE(moby) < 1100) {
          moby->m_State = 2;
          MOBY_ANIM_CHANGE(moby, 2);
          break;
        }
        break;

      case 1:
        if (func_80039E94(moby, props->m_0x04, 0x100, 110, 0, 8, 0x28, 0xFF,
                          5) == 0x100) {
          if (DISTANCE_TO_SPYRO(moby) < 0x1C00 &&
              SPYRO_ORIGIN_Z_DISTANCE(moby) < 1100) {
            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            break;
          }

          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          break;
        }

        if (DISTANCE_TO_SPYRO(moby) < 0x1194 &&
            func_80017908(moby->m_Rotation.z,
                          ANGLE_TO_SPYRO(moby->m_Position)) < 0x40) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          break;
        }
        break;

      case 2:
        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_RESTART(moby, 3);
        }
        break;

      case 3: {
        int distance = DISTANCE_TO_SPYRO(moby);

        if (props->m_0x28 == 0 &&
            DISTANCE_TO_SPYRO(moby) < (props->m_0x08 << 10)) {
          moby->m_State = 10;
          MOBY_ANIM_CHANGE(moby, 10);
          continue;
        }

        RotateMobyToSpyro(moby, 3, 0, 0);
        if (TICK_TIMER(props->m_0x0c) && distance < 4000 &&
            SPYRO_ORIGIN_Z_DISTANCE(moby) < 1100) {
          moby->m_State = 4;
          MOBY_ANIM_CHANGE(moby, 4);
          break;
        }

        if (distance > 0x2000) {
          moby->m_State = 5;
          MOBY_ANIM_CHANGE(moby, 5);
        }
        break;
      }

      case 4:
        RotateMobyToSpyro(moby, 6, 0, 0);

        if (props->m_0x38 == 0 && moby->m_AnimationState.m_NextFrame > 1 &&
            moby->m_AnimationState.m_NextFrame < 28) {
          props->m_0x38 = g_SpawnMoby(32, moby);
        }

        if (props->m_0x14 == 0 && moby->m_AnimationState.m_NextFrame > 14 &&
            moby->m_AnimationState.m_NextFrame < 18 &&
            DISTANCE_TO_SPYRO(moby) < 0x1194) {
          Moby494Props *projectileProps;

          props->m_0x14 = g_SpawnMoby(494, moby);
          props->m_0x14->m_Rotation.z = moby->m_Rotation.z;
          projectileProps = props->m_0x14->m_Props;
          projectileProps->m_0x12 = 0;
          g_Spyro.m_DamageFlags |= 0x26;
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_80052D64(moby, 0, &props->m_0x14->m_Position);
          projectileProps->m_0x00 = moby;
        }

        if (moby->m_AnimationState.m_NextFrame >= 0x1C && props->m_0x14 != 0) {
          props->m_0x14->m_Substate = 1;
          props->m_0x14 = 0;
          if (props->m_0x38 != 0) {
            if (props->m_0x38->m_State < 0x80) {
              props->m_0x38->m_Substate = 1;
            }
            props->m_0x38 = 0;
          }
        }

        if (g_Spyro.m_State == 7) {
          props->m_0x0c = 3;
        }

        if (g_AnimationFinished) {
          if (props->m_0x0c != 0) {
            moby->m_State = 7;
            MOBY_ANIM_RESTART(moby, 7);
          } else {
            props->m_0x0c = 0x3C;
            moby->m_State = 0;
            MOBY_ANIM_RESTART(moby, 0);
          }
        }
        break;

      case 5:
        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_RESTART(moby, 0);
        }
        break;

      case 6: {
        if (props->m_0x14 != 0) {
          props->m_0x14->m_Substate = 1;
          props->m_0x14 = 0;
        }

        if (props->m_0x20 > 0) {
          func_80039688(moby, props->m_0x1c, props->m_0x20, 500, 700, 1);
          props->m_0x20 -= 0x10;
        }

        if (g_AnimationFinished) {
          for (i = 0; i < 3; i++) {
            if (props->m_0x2c[i] != 0) {
              props->m_0x2c[i]->m_State = 3;
            }
          }
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x34);
          func_80052568(moby);
          continue;
        }
        break;
      }

      case 7:
        if (g_AnimationFinished && TICK_TIMER(props->m_0x0c)) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
        }
        break;

      case 8:
        switch (props->m_0x00) {
        case 1:
          if (DISTANCE_TO_SPYRO(moby) < (props->m_0x08 << 10) &&
              SPYRO_BASE_Z_DISTANCE(moby) < 1000) {
            int speed;

            props->m_0x00 = 0;
            speed = OctDistance(&moby->m_Position,
                                &PATH_NODE_POS(props->m_0x04, 1)) /
                    12;
            props->m_0x24 = 110;
            props->m_0x20 = speed;
            moby->m_State = 9;
            MOBY_ANIM_CHANGE(moby, 9);
            break;
          }
          break;

        case 2:
          if (DISTANCE_TO_SPYRO(moby) < 0x3000 &&
              func_80017908(moby->m_Rotation.z,
                            ANGLE_TO_SPYRO(moby->m_Position)) < 0x40) {
            props->m_0x00 = 0;
            moby->m_State = 1;
            MOBY_ANIM_CHANGE(moby, 1);
            break;
          }
          break;
        }
        break;

      case 9: {
        int angle =
            ANGLE_FROM(moby->m_Position, PATH_NODE_POS(props->m_0x04, 1));
        int distance =
            OctDistance(&moby->m_Position, &PATH_NODE_POS(props->m_0x04, 1));

        func_80038340(moby);
        RotateMobyToSpyro(moby, 3, 0, 0);

        if (g_AnimationFinished) {
          if (props->m_0x28 == 0) {
            moby->m_State = 10;
            MOBY_ANIM_SET_NEXT(moby, 10);
          } else {
            moby->m_State = 0;
            MOBY_ANIM_SET_NEXT(moby, 0);
          }
          continue;
        }

        if (moby->m_AnimationState.m_NextFrame > 7 &&
            moby->m_AnimationState.m_NextFrame < 15 &&
            props->m_0x20 < distance) {
          func_80039688(moby, angle, props->m_0x20, 0, 0, 0);
        }
        break;
      }

      case 10:
        if (moby->m_AnimationState.m_NextFrame >= 4) {
          props->m_0x28 = 1;
        }

        if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
        }
        break;
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX | UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_475
    case 475: {
      switch (moby->m_State) {
      case 0: {
        if ((moby->m_DamageFlags & MOBY_DAMAGE_CHARGE) != 0) {
          moby->m_State = 1;
          MOBY_ANIM_RESTART(moby, 1);
        } else if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
        } else {
          moby->m_DamageFlags = 0;
        }
        break;
      }

      case 1: {
        if ((moby->m_DamageFlags & MOBY_DAMAGE_FLAME) != 0) {
          moby->m_State = 2;
          MOBY_ANIM_SET_NEXT(moby, 2);
        } else if (g_AnimationFinished) {
          moby->m_State = 0;
          MOBY_ANIM_SET_NEXT(moby, 0);
        } else {
          moby->m_DamageFlags = 0;
        }
        break;
      }

      case 3: {
        if (moby->m_DamageFlags != 0) {
          moby->m_State = 4;
          MOBY_ANIM_RESTART(moby, 4);
        } else {
          moby->m_DamageFlags = 0;
        }
        break;
      }

      case 2:
      case 4: {
        if (g_AnimationFinished) {
          moby->m_State = 3;
          MOBY_ANIM_SET_NEXT(moby, 3);
        } else {
          moby->m_DamageFlags = 0;
        }
        break;
      }

      default: {
        moby->m_DamageFlags = 0;
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_476
    case 476: {
      Moby476Props *props;
      int distance;

      props = moby->m_Props;
      distance = DISTANCE_TO_SPYRO(moby);

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 4 && moby->m_State != 99) {
        Moby *spawned;

        spawned = g_SpawnMoby(476, moby);
        VecCopy(&spawned->m_Position, &moby->m_Position);
        spawned->m_State = 99;

        if (spawned->m_AnimationState.m_Animation != 10) {
          MOBY_ANIM_RESTART(spawned, 10);
        }

        func_8003ABC0(moby, 1, 0, 0);
        func_8003B7C0(moby);
        props->m_0x24 = 350;

        if (moby->m_State >= 10) {
          g_IsSpyroHidden = 0;
        }

        props->m_0x20 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                      g_Spyro.m_bodyRotation.z, 0x20, 0x40);
        props->m_0x28 = 0xF0;

        if (moby->m_State != 0) {
          *props->m_0x2c = 0;
        }

        func_8003851C(moby, 1, 0);

        if (moby->m_AnimationState.m_Animation != 9) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 9);
        }

        moby->m_State = 4;
        continue;
      }

      moby->m_DamageFlags = 0;

      if (moby->m_AnimationState.m_NextAnimation == 1 &&
          IsMobyPlayingSound(moby, g_Models[moby->m_Class]->m_Sounds[2]) == 0) {
        func_8003851C(moby, 2, &props->m_0x38);
      }

      switch (moby->m_State) {
      case 0: {
        int threshold;
        int randomValue;

        RotateMobyToSpyro(moby, 6, 0, 0);

        if (distance > 0x2C00) {
          props->m_0x14 = 0;

          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 0);
        }

        if (TICK_TIMER(props->m_0x18)) {
          if (props->m_0x14 == 0) {
            if (moby->m_AnimationState.m_NextAnimation == 0 &&
                moby->m_AnimationState.m_NextFrame >= 0xF) {
              moby->m_AnimationState.m_Frame = 0;
              moby->m_AnimationState.m_NextFrame = 1;
              moby->m_AnimationState.m_FrameProgress = 0;
            }
          } else if (moby->m_AnimationState.m_NextAnimation == 0 &&
                     moby->m_AnimationState.m_NextFrame >= 0x1C) {
            g_AnimationFinished = 0;
            MOBY_ANIM_ADVANCE(moby, 1);
          }

          if (props->m_0x14 == 0 && distance < 0x2400) {
            props->m_0x14 = RandRange(0, 0x3F) + 0x50;
          }

          threshold = props->m_0x14 - (distance >> 6);
          randomValue = rand() & 0xFF;

          if (TICK_TIMER(props->m_0x34) && *props->m_0x2c == 0 &&
              randomValue < threshold &&
              func_80017908(g_Camera.m_Rotation.z >> 4,
                            ANGLE_FROM(g_Camera.m_Position, moby->m_Position)) <
                  0x28) {
            if (SPYRO_BASE_Z_DELTA(moby) > -500 &&
                SPYRO_BASE_Z_DISTANCE(moby) < 1400) {
              *props->m_0x2c = 1;
              props->m_0x18 = 0x10;
              func_800562A4(moby, 1);
              moby->m_State = 1;
              continue;
            }
          }

          if (*props->m_0x2c != 0) {
            props->m_0x34 = 0x3C;
          }
        }

        break;
      }

      case 1: {
        Moby **scan;
        Moby *other;
        int attackDistance;
        int angle;

        attackDistance = DISTANCE_TO_SPYRO(moby);

        if (attackDistance < 4000) {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 2);
        } else {
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);
        }

        if (TICK_TIMER(props->m_0x18)) {
          angle = ANGLE_TO_SPYRO(moby->m_Position);

          if (func_80039688(moby, angle, 350, 0, 0, 0x15) != 0 ||
              g_Spyro.m_SurfaceProximityState != 0) {
            moby->m_State = 2;
            continue;
          }

          scan = (Moby **)(g_SonyImage.u.m_Buf + 0x400);

          while (other = *scan++) {
            if (other->m_Class == 28 &&
                ABS2(moby->m_Position.x - other->m_Position.x) < 3000 &&
                ABS2(moby->m_Position.y - other->m_Position.y) < 3000 &&
                OctDistance(&moby->m_Position, &other->m_Position) < 2000 &&
                func_80017908(moby->m_Rotation.z,
                              ANGLE_FROM(moby->m_Position, other->m_Position)) <
                    0x19) {
              other->m_DamageFlags |= MOBY_DAMAGE_SUPER;
            }
          }

          if (attackDistance < 1100) {
            props->m_0x30 = 0;
            moby->m_State = 10;
            continue;
          }
        }

        break;
      }

      case 2: {
        int angle;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 3);

        angle = ANGLE_FROM(moby->m_Position, props->m_0x08);

        if (RotateMobyToAngle(moby, angle, 6, 0x14, 1) != 0) {
          angle = ANGLE_FROM(moby->m_Position, props->m_0x08);
          func_80039688(moby, angle, 200, 0, 0, 5);
        }

        if (OctDistance(&moby->m_Position, &props->m_0x08) < 0x100) {
          *props->m_0x2c = 0;
          props->m_0x18 = 0x78;
          moby->m_State = 0;
          MOBY_ANIM_CHANGE(moby, 0);
          continue;
        }

        break;
      }

      case 4: {
        moby->m_Rotation.x += 4;
        moby->m_Rotation.y += 4;

        if (MoveMobyWithGravity(moby, &props->m_0x24, props->m_0x20,
                                &props->m_0x28, 0xC, 0xE) == 3) {
          func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
          func_800385BC(moby, 0x30);
          func_80052568(moby);
          continue;
        }

        break;
      }

      case 6: {
        if (g_AnimationFinished) {
          moby->m_State = 1;
          continue;
        }

        break;
      }

      case 10: {
        int attackDistance;
        int speed;
        int angle;

        attackDistance = DISTANCE_TO_SPYRO(moby);

        speed = 0x50;
        if (attackDistance >= 0x12D) {
          speed = 0xFA;
        }

        if (attackDistance < 0x190) {
          g_IsSpyroHidden = 1;
        }

        if (props->m_0x30 == 0) {
          if (attackDistance < speed) {
            props->m_0x30 = 1;
            moby->m_Position.x = g_Spyro.m_Position.x;
            moby->m_Position.y = g_Spyro.m_Position.y;
          } else {
            RotateMobyToSpyro(moby, 6, 0, 0);
            angle = ANGLE_TO_SPYRO(moby->m_Position);

            if (func_80039688(moby, angle, speed, 0, 0, 0x15) != 0 &&
                g_IsSpyroHidden == 0) {
              moby->m_State = 2;
              continue;
            }
          }
        }

        g_Spyro.m_ControlFlags = 0x80002000;

        if (moby->m_AnimationState.m_NextFrame >= 0xD) {
          g_Spyro.m_Position.x = moby->m_Position.x;
          g_Spyro.m_Position.y = moby->m_Position.y;
          g_IsSpyroHidden = 1;
          g_Spyro.m_bodyRotation.z = moby->m_Rotation.z + 0x80;
          g_Spyro.m_Physics.m_SpeedAngle.m_RotZ = g_Spyro.m_bodyRotation.z << 4;

          if (g_Spyro.m_health == 0) {
            g_Spyro.m_DamageFlags |= 7;
            moby->m_State = 13;
            continue;
          }

          if (D_8007577C != 0) {
            moby->m_State = 14;
            continue;
          }
          moby->m_State++;
        }

        break;
      }

      case 11: {
        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 4);

        g_Spyro.m_Position.x = moby->m_Position.x;
        g_Spyro.m_Position.y = moby->m_Position.y;
        g_IsSpyroHidden = 1;
        g_Spyro.m_ControlFlags = 0x80002000;

        if (g_AnimationFinished) {
          moby->m_State++;
        }

        break;
      }

      case 12: {
        int length;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);

        if (g_IsSpyroHidden != 0) {
          if (moby->m_AnimationState.m_NextFrame >= 0x29) {
            Vector3D velocity;
            g_IsSpyroHidden = 0;
            g_Spyro.m_DamageFlags = 0x86;
            g_Spyro.m_Position.x = moby->m_Position.x +
                                   FIXED_MUL(COSINE_8(moby->m_Rotation.z), 300);
            g_Spyro.m_Position.y =
                moby->m_Position.y + FIXED_MUL(SINE_8(moby->m_Rotation.z), 300);
            VecSub(&velocity, &g_Spyro.m_Position, &moby->m_Position);
            length = VecMagnitude(&velocity, 0);
            VecScaleToLength(&velocity, length, 100);
            g_Spyro.unk_0x208.x = velocity.x;
            g_Spyro.unk_0x208.y = velocity.y;
            g_Spyro.unk_0x208.z = 55;
          } else {
            g_Spyro.m_ControlFlags = 0x80002000;
          }
        }

        if (g_AnimationFinished) {
          D_8007577C = 1;
          moby->m_State = 2;
          continue;
        }

        break;
      }

      case 13: {
        g_Spyro.m_ControlFlags = 0x80002000;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 8);

        g_Spyro.m_DamageFlags |= 7;
        break;
      }

      case 14: {
        Vector3D velocity;
        int length;

        MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 7);

        if (g_IsSpyroHidden != 0) {
          if (moby->m_AnimationState.m_NextFrame >= 0x10) {
            g_IsSpyroHidden = 0;
            g_Spyro.m_DamageFlags = 0x86;
            g_Spyro.m_Position.x = moby->m_Position.x +
                                   FIXED_MUL(COSINE_8(moby->m_Rotation.z), 300);
            g_Spyro.m_Position.y =
                moby->m_Position.y + FIXED_MUL(SINE_8(moby->m_Rotation.z), 300);
            VecSub(&velocity, &g_Spyro.m_Position, &moby->m_Position);
            length = VecMagnitude(&velocity, 0);
            VecScaleToLength(&velocity, length, 100);
            g_Spyro.unk_0x208.x = velocity.x;
            g_Spyro.unk_0x208.y = velocity.y;
            g_Spyro.unk_0x208.z = 0x37;
          } else {
            g_Spyro.m_ControlFlags = 0x80002000;
          }
        }

        if (g_AnimationFinished) {
          moby->m_State = 2;
          continue;
        }

        break;
      }

      case 99: {
        if (g_AnimationFinished) {
          func_80052568(moby);
          continue;
        }

        break;
      }
      }

      if (DISTANCE_TO_SPYRO(moby) > 0x200) {
        func_800529E4(moby, UPDATE_PROP_COLLISION);
      }

      break;
    }

#endif
#if defined(HAS_MOBY_481) || defined(HAS_MOBY_482) || defined(HAS_MOBY_483)
#ifdef HAS_MOBY_481
    case 481: // Flight Train, Wagon and Plane Fragments
#endif
#ifdef HAS_MOBY_482
    case 482:
#endif
#ifdef HAS_MOBY_483
    case 483:
#endif
    {
      MobyFragmentProps *props = moby->m_Props;
      Vector3D particleVelocity;

      if (props->m_Lifetime > 0 && moby->m_WasDrawn) {
        moby->m_Position.x += props->m_Velocity.x;
        moby->m_Position.y += props->m_Velocity.y;

        props->m_Velocity.z -= 6;
        if (props->m_Velocity.z < -0x80) {
          props->m_Velocity.z = -0x80;
        }

        moby->m_Position.z += props->m_Velocity.z;

        moby->m_Rotation.x += props->m_AngularVelocity.x;
        moby->m_Rotation.y += props->m_AngularVelocity.y;
        moby->m_Rotation.z += props->m_AngularVelocity.z;

        if ((props->m_Lifetime & 3) == 0) {
          particleVelocity.x = rand() & 3;
          particleVelocity.y = rand() & 3;
          particleVelocity.z = 0x14;

          g_SpawnParticle(1, 1, &moby->m_Position, (int)&particleVelocity);
        }

        props->m_Lifetime--;
      } else {
        g_SpawnParticle(8, 70, &moby->m_Position, 0x10);
        func_80052568(moby);
      }

      break;
    }
#endif
#ifdef HAS_MOBY_487
    case 487: {
      if (moby->m_DamageFlags != 0 && moby->m_State < 3) {
        moby->m_State = 3;
        MOBY_ANIM_RESTART(moby, 3);
        continue;
      }

      switch (moby->m_State) {
      case 1: {
        if (moby->m_AnimationState.m_Animation != 1) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 1);
        }

        if (moby->m_AnimationState.m_NextFrame >= 14) {
          moby->m_State = 2;
          MOBY_ANIM_RESTART(moby, 2);
          continue;
        }
        break;
      }

      case 3: {
        if (moby->m_AnimationState.m_NextFrame >= 19) {
          moby->m_State = 4;
          MOBY_ANIM_RESTART(moby, 4);
          continue;
        }

        break;
      }

      case 0:
      case 2:
      case 4: {
        break;
      }
      }

      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_493
    case 493: { // Cactus Charred Particles
      if (g_AnimationFinished) {
        func_80052568(moby);
      }
      break;
    }
#endif
#ifdef HAS_MOBY_494
    case 494: {
      Moby494Props *props = moby->m_Props;
      Vector3D delta;
      Vector3D oldPosition;
      int distance;
      int angleDelta;
      int scale;

      if (moby->m_Substate != 0) {
        func_80052568(moby);
        continue;
      }

      if (props->m_0x12 == 0) {
        func_800529E4(props->m_0x00, 4);
        func_80052D64(props->m_0x00, 0, &moby->m_Position);
        moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);
        moby->m_Rotation.y =
            Atan2(DISTANCE_TO_SPYRO(moby),
                  g_Spyro.m_Position.z - moby->m_Position.z, 0);
        VecSub(&delta, &g_Spyro.m_Position, &moby->m_Position);
        scale = 0x14 - VecMagnitude(&delta, 1) * 0x1A / 1400;
        if (scale < -0x14) {
          scale = -0x14;
        }
        moby->m_ScaleOverride = scale + 0x20;
        break;
      }

      if (props->m_0x12 == 2) {
        angleDelta =
            (ANGLE_FROM(moby->m_Position, props->m_0x04) - moby->m_Rotation.z) &
            0xFF;
        if (angleDelta > 0x80) {
          angleDelta -= 0x100;
        }
        if (angleDelta >= 3) {
          angleDelta = 2;
        }
        if (angleDelta < -2) {
          angleDelta = -2;
        }
        moby->m_Rotation.z += angleDelta;

        distance = OctDistance(&moby->m_Position, &props->m_0x04);
        angleDelta = (Atan2(distance, props->m_0x04.z - moby->m_Position.z, 0) -
                      moby->m_Rotation.y) &
                     0xFF;
        if (angleDelta > 0x80) {
          angleDelta -= 0x100;
        }
        if (angleDelta >= 3) {
          angleDelta = 2;
        }
        if (angleDelta < -2) {
          angleDelta = -2;
        }
        moby->m_Rotation.y += angleDelta;
      }

      VecCopy(&oldPosition, &moby->m_Position);

      if (props->m_0x12 == 1) {
        if (func_8004E2E8(&moby->m_Position, 0xFA, 0x26) != 0) {
          g_Spyro.unk_0x208.x = COSINE_8(moby->m_Rotation.z) >> 5;
          g_Spyro.unk_0x208.y = SINE_8(moby->m_Rotation.z) >> 5;
          g_Spyro.unk_0x208.z = 0;
          func_80052568(moby);
          continue;
        }
      }

      if (props->m_0x12 == 2) {
        if (func_8004E3C8(&moby->m_Position, 350, 0, 0x40000, moby, 0) != 0) {
          func_80052568(moby);
          continue;
        }
      }

      if (TICK_TIMER(props->m_0x10)) {
        func_80052568(moby);
      } else if (func_8003BCCC(moby, 350, 150, 0, 0)) {
        func_80052568(moby);
      } else if (func_8004AE38(&oldPosition, &moby->m_Position)) {
        func_80052568(moby);
      }

      break;
    }
#endif
#ifdef HAS_MOBY_495 // Blowhard
    case 495: {
      Moby495Props *props;
      Vector3D vec;
      Vector3D vec1;
      Vector3D vec2;
      int distance;
      int zDifference;

      props = moby->m_Props;
      distance = DISTANCE_TO_SPYRO(moby);

      if (SPYRO_BASE_Z_DISTANCE(moby) < 1400 && distance < 0x2800 &&
          func_80038250(&moby->m_Position) != 0 && g_Spyro.m_State != 11 &&
          g_Spyro.m_State != 20 && moby->m_State != 80 && moby->m_State != 90) {
        g_Spyro.m_ControlFlags = 0x80010000;
        g_Spyro.m_mobyInUseBySpyro = moby;
      }

      if (func_80038C4C(&g_Spyro.m_Position, &props->m_0x74) != 0) {
        moby->m_SoundDistance = 0x10;
      }

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
          0) {
        moby->m_DamageFlags = 0;
        VecCopy(&vec2, &moby->m_Position);
        vec2.z += 0x400;

        if (func_80033E40(&vec2, &g_Spyro.m_Position) != 0) {
          switch (moby->m_State) {
          case 5:
          case 71:
          case 72:
          case 81:
          case 82:
          case 83:
          case 91:
          case 92:
          case 93: {
            Moby *linked;
            int *linkedProps;

            g_Checkpoint.m_Unused1++;

            if (props->m_0x48 != 0) {
              func_800562A4(props->m_0x48, 1);
              func_80052568(props->m_0x48);
              props->m_0x48 = 0;
            }

            if (moby->m_State == 91 || moby->m_State == 92 ||
                moby->m_State == 93) {
              StopSound(moby->m_SoundChannel, 4);
              moby->m_State = 7;
              MOBY_ANIM_CHANGE(moby, 7);
              continue;
            }

            if (props->m_0x64 >= 0) {
              linked = &g_LevelMobys[props->m_0x64];
              linkedProps = (int *)linked->m_Props;
              VecCopy(&linked->m_Position, &moby->m_Position);
              func_8003ABC0(linked, 1, 0, 0);
              func_8003B7C0(linked);
              props->m_0x64 = linkedProps[0];
              func_80052568(linked);
            }

            moby->m_State = 2;
            MOBY_ANIM_CHANGE(moby, 2);
            continue;
          }
          }
        }
      }

      func_800529E4(moby, UPDATE_PROP_ROTMATRIX);
      VecCopy(&vec1, &moby->m_Position);
      vec1.z += 0x400;
      func_8004D5EC(&vec1, 0x10000);
      func_800533D0(moby);

      if (props->m_0x4c > 0) {
        zDifference = props->m_0x4c - moby->m_Position.z;
        if (ABS2(zDifference) < 0x21) {
          props->m_0x4c = -1;
        } else if (moby->m_State == 0) {
          props->m_0x4c = -1;
        } else {
          moby->m_Position.z += zDifference >> 3;
        }
      } else {
        props->m_0x4c = -1;
      }

      if (props->m_0x58 == 0) {
        if (g_Checkpoint.m_Unused2 == 0) {
          if (TICK_TIMER(props->m_0x50)) {
            g_ScreenBorderEnabled = 0;
            props->m_0x58 = 1;
          } else {
            g_ScreenBorderEnabled = 1;
            g_Spyro.m_ControlFlags = 0x80002000;
          }
        } else {
          Moby *linked;
          int *linkedProps;

          linked = &g_LevelMobys[props->m_0x64];
          linkedProps = (int *)linked->m_Props;
          props->m_0x58 = 1;

          if (g_Checkpoint.m_Unused2 > 0) {
            moby->m_State = 81;
            props->m_0x60 = 0;
            props->m_0x44 = 1;
            props->m_0x14 = props->m_0x3c;

            if (g_LevelMobys[props->m_0x64].m_DropMoby != 0xFF &&
                g_LevelMobys[props->m_0x64].m_State < 0x80) {
              func_8003ABC0(linked, 1, 0, 0);
              func_8003B7C0(linked);
              func_80052568(linked);
            }

            props->m_0x64 = linkedProps[0];
            func_8002B390(0, 0xFC, 0);
            props->m_0x10 = -1;
          }

          if (g_Checkpoint.m_Unused2 >= 2) {
            moby->m_State = 91;
            props->m_0x14 = props->m_0x40;
            linked = &g_LevelMobys[props->m_0x64];
            linkedProps = (int *)linked->m_Props;

            if (linked->m_DropMoby != 0xFF && linked->m_State < 0x80) {
              func_8003ABC0(linked, 1, 0, 0);
              func_8003B7C0(linked);
              func_80052568(linked);
            }

            props->m_0x64 = linkedProps[0];
          }

          VecCopy(&moby->m_Position, &PATH_NODE_POS(props->m_0x14, 0));
          props->m_0x4c = moby->m_Position.z + 1400;

          if (g_Checkpoint.m_Unused2 == 3) {
            func_80052568(moby);
            break;
          }
        }
      }

      switch (moby->m_State) {
      case 0: {
        switch (props->m_0x44) {
        case 0: {
          moby->m_State = 70;
          props->m_0x24.x = 0;
          break;
        }
        case 1: {
          moby->m_State = 80;
          props->m_0x24.x = 0;
          break;
        }
        case 2: {
          moby->m_State = 90;
          props->m_0x24.x = 0;
          break;
        }
        }
        break;
      }

      case 2: {
        if (g_AnimationFinished) {
          if (props->m_0x10 >= 0) {
            if ((func_8002B3F4(props->m_0x10) & 2) == 0) {
              break;
            }
            func_8002B390(props->m_0x10, 0xFC, 0);
            moby->m_State = 99;
            moby->m_DamageFlags = 0;
            props->m_0x10 = -1;
          } else {
            moby->m_DamageFlags = 0;
            moby->m_State = 99;
          }
        }
        break;
      }

      case 7: {
        if (g_AnimationFinished) {
          func_80038458(moby);
          func_8003ABC0(moby, 1, 0, 0);
          func_8003B7C0(moby);
          func_80052568(moby);
        }
        break;
      }

      case 70: {
        moby->m_State = 71;
        props->m_0x4c = moby->m_Position.z + 1400;
        break;
      }

      case 71: {
        RotateMobyToSpyro(moby, 8, 0x10, 1);
        if (distance < 0x2800 && props->m_0x48 == 0 && props->m_0x4c == -1) {
          moby->m_State = 72;
          props->m_0x4c = moby->m_Position.z - 1400;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
        }
        break;
      }

      case 72: {
        Vector3D vec3;

        RotateMobyToSpyro(moby, 8, 0x10, 1);

        if (moby->m_AnimationState.m_Animation == 5 &&
            moby->m_AnimationState.m_Frame >= 6 && props->m_0x48 == 0) {
          VecCopy(&vec3, &moby->m_Position);
          vec3.z += 0x400;
          if (func_80033E40(&vec3, &g_Spyro.m_Position) != 0) {
            props->m_0x48 = g_SpawnMoby(37, moby);
            func_8003851C(props->m_0x48, 0, 0);
          }
        }

        if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 5 &&
            props->m_0x48 != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 6);
        }

        if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 6) {
          moby->m_State = 71;
          props->m_0x4c = moby->m_Position.z + 1400;
          if (moby->m_AnimationState.m_Animation != 0) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 0);
          }
        }
        break;
      }

      case 80: {
        if (func_8003BFC0(moby, props->m_0x14, &props->m_0x18,
                          (int *)&props->m_0x24, 0x20, 4) == 2) {
          moby->m_State = 81;
          moby->m_SoundDistance = 0;
          props->m_0x4c = moby->m_Position.z + 1400;
          props->m_0x14 = props->m_0x3c;
        }
        moby->m_Rotation.y = 0;
        break;
      }

      case 81: {
        if (distance < 0x2800 && props->m_0x4c == -1) {
          if (props->m_0x60 == 0) {
            if (func_80039E94(moby, props->m_0x14, 0x80, 0xB4, 0, 8, 0x28, 0xFF,
                              1) != 0) {
              props->m_0x60 = 1;
            }
            break;
          }

          if (props->m_0x48 != 0 || distance <= 0x1000) {
            break;
          }

          moby->m_State = 82;
          props->m_0x4c = moby->m_Position.z - 1400;
          MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
        } else {
          RotateMobyToSpyro(moby, 8, 0x10, 1);
        }
        break;
      }

      case 82: {
        Vector3D vec3;
        int angle;

        RotateMobyToSpyro(moby, 8, 0x10, 1);
        angle = ANGLE_FROM_SPYRO(moby->m_Position);

        if (func_80017908(g_Spyro.m_bodyRotation.z, angle) < 0x30 &&
            moby->m_AnimationState.m_Animation == 5 &&
            moby->m_AnimationState.m_Frame >= 6 && props->m_0x48 == 0) {
          VecCopy(&vec3, &moby->m_Position);
          vec3.z += 0x400;
          if (func_80033E40(&vec3, &g_Spyro.m_Position) != 0) {
            props->m_0x48 = g_SpawnMoby(37, moby);
            func_8003851C(props->m_0x48, 0, 0);
          }
        }

        if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 5 &&
            props->m_0x48 != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 6);
        }

        if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 6) {
          moby->m_State = 83;
          props->m_0x68 = 110;
          props->m_0x60 = 0;
          if (moby->m_AnimationState.m_Animation != 0) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 0);
          }
        }
        break;
      }

      case 83: {
        if (TICK_TIMER(props->m_0x68)) {
          props->m_0x4c = moby->m_Position.z + 1400;
          moby->m_State = 81;
        }
        break;
      }

      case 90: {
        if (func_8003BFC0(moby, props->m_0x14, &props->m_0x18,
                          (int *)&props->m_0x24, 0x20, 4) == 2) {
          moby->m_State = 91;
          props->m_0x4c = moby->m_Position.z + 1400;
          props->m_0x14 = props->m_0x40;
        }
        moby->m_Rotation.y = 0;
        break;
      }

      case 91: {
        if (distance < 0x2800 && props->m_0x4c == -1) {
          if (props->m_0x60 == 0) {
            if (func_80039E94(moby, props->m_0x14, 0x80, 0xB4, 0, 8, 0x28, 0xFF,
                              1) != 0) {
              props->m_0x60 = 1;
            }
          } else if (!props->m_0x48 && distance > 0x1000) {
            moby->m_State = 92;
            props->m_0x4c = moby->m_Position.z - 1400;
            MOBY_ANIM_CHANGE_CLEAR_FINISHED(moby, 5);
          }
        } else {
          RotateMobyToSpyro(moby, 8, 0x10, 1);
        }
        break;
      }

      case 92: {
        Vector3D vec3;
        int angle;

        RotateMobyToSpyro(moby, 8, 0x10, 1);
        angle = ANGLE_FROM_SPYRO(moby->m_Position);

        if (func_80017908(g_Spyro.m_bodyRotation.z, angle) < 0x30 &&
            moby->m_AnimationState.m_Animation == 5 &&
            moby->m_AnimationState.m_Frame >= 6 && props->m_0x48 == 0) {
          VecCopy(&vec3, &moby->m_Position);
          vec3.z += 0x400;
          if (func_80033E40(&vec3, &g_Spyro.m_Position) != 0) {
            props->m_0x48 = g_SpawnMoby(37, moby);
            func_8003851C(props->m_0x48, 0, 0);
          }
        }

        if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 5 &&
            props->m_0x48 != 0) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 6);
        }

        if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 5) {
          g_AnimationFinished = 0;
          MOBY_ANIM_RESTART(moby, 6);
        }

        if (g_AnimationFinished && moby->m_AnimationState.m_Animation == 6) {
          moby->m_State = 93;
          props->m_0x60 = 0;
          props->m_0x68 = 110;
          if (moby->m_AnimationState.m_Animation != 0) {
            g_AnimationFinished = 0;
            MOBY_ANIM_RESTART(moby, 0);
          }
        }
        break;
      }

      case 93: {
        if (TICK_TIMER(props->m_0x68)) {
          props->m_0x4c = moby->m_Position.z + 1400;
          moby->m_State = 91;
        }
        break;
      }

      case 99: {
        props->m_0x44++;

        switch (props->m_0x44) {
        case 0: {
          props->m_0x14 = props->m_0x30;
          break;
        }
        case 1: {
          props->m_0x14 = props->m_0x34;
          break;
        }
        case 2: {
          props->m_0x14 = props->m_0x38;
          break;
        }
        }

        props->m_0x14->m_CurrentNode = 0;
        props->m_0x24.y = 0;
        props->m_0x24.z = 0;
        moby->m_State = 0;
        MOBY_ANIM_CHANGE(moby, 0);
        break;
      }
      }
      break;
    }
#endif
#ifdef HAS_MOBY_497
    case 497: {
      Moby497Props *props;
      int status;

      props = moby->m_Props;

      if ((moby->m_DamageFlags & (MOBY_DAMAGE_FLAME | MOBY_DAMAGE_SUPER)) !=
              0 &&
          moby->m_State != 1) {
        StopSound(moby->m_SoundChannel, 4);
        func_8003ABC0(moby, 4, 0, 0);
        func_8003B7C0(moby);
        func_8002B3F4(props->m_0x10);
        moby->m_State = 1;
        MOBY_ANIM_CHANGE(moby, 1);
        break;
      }

      switch (moby->m_State) {
      case 0: {
        moby->m_State = 2;
        MOBY_ANIM_RESTART(moby, 2);
        continue;
      }

      case 1: {
        if (g_AnimationFinished && moby->m_RenderRadius != 0) {
          moby->m_RenderRadius = 0;
          moby->m_AnimationState.m_PerFrameProgress = 0;
          moby->m_CollisionGroup = 0;
          func_800385BC(moby, 0x20);
        }

        switch (props->m_0x10) {

        case 3:
        case 4: {
          status = func_8002B3F4(props->m_0x10);
          if ((status & 2) != 0) {
            if (((status >> 8) & 0xFF) != 0) {
              func_8002B390(props->m_0x10, 0xFC, 0);
            } else if (moby->m_RenderRadius == 0) {
              func_80052568(moby);
              continue;
            }
          }
          break;
        }
        case 5:
        case 7: {
          status = func_8002B3F4(props->m_0x10);
          if ((status & 2) != 0) {
            if (((status >> 8) & 0xFF) != 0) {
              func_8002B390(props->m_0x10, 0xFC, 0);
            } else if (moby->m_RenderRadius == 0) {
              func_80052568(moby);
              continue;
            }
          }
          break;
        }
        }
        break;
      }

      case 2: {
        if ((g_GameTick & 1) != 0) {
          g_SpawnParticle(1, 8, moby, (int)&g_LevelMobys[props->m_0x30]);
        }

        status = func_8002B3F4(props->m_0x10);
        if ((status & 2) != 0 && TICK_TIMER(props->m_0x14)) {
          props->m_0x14 = props->m_0x18;
          if (props->m_0x10 >= 5 && ((status >> 8) & 0xFF) >= 0x65) {
            props->m_0x14 = 0;
          }
          func_8002B390(props->m_0x10, 0xFC, 0);
        }
        break;
      }
      }
      func_800529E4(moby, UPDATE_PROP_COLLISION);
      break;
    }
#endif
#ifdef HAS_MOBY_502
    case 502: {
      Moby502Props *props = moby->m_Props;

      if (props->m_Lifetime && moby->m_WasDrawn) {
        moby->m_Position.x += props->m_Velocity.x;
        moby->m_Position.y += props->m_Velocity.y;
        props->m_Velocity.z -= 5;
        if (--props->m_0x0d == 0) {
          props->m_Velocity.x = 0;
          props->m_Velocity.y = 0;
          props->m_Velocity.z = 0;
        }
        if (props->m_Velocity.z < -24) {
          props->m_Velocity.z = -24;
        }
        if (props->m_0x10 == 0) {
          moby->m_Rotation.z += 12;
        } else if (props->m_Velocity.z < 0) {
          if (moby->m_Rotation.y + props->m_0x0e == 32 ||
              moby->m_Rotation.y + props->m_0x0e == 224) {
            int temp = -props->m_0x0e;
            props->m_0x0e = temp;
          }
          moby->m_Rotation.y += props->m_0x0e;
          moby->m_Position.y += props->m_0x0e;
          if ((rand() & 1)) {
            moby->m_Rotation.z++;
          }
        }
        moby->m_Position.z += props->m_Velocity.z;
        props->m_Lifetime--;
      } else {
        func_80052568(moby);
      }
      break;
    }
#endif
    }
  }
}
