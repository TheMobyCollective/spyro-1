.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003DAE4
/* 2E2E4 8003DAE4 C0FFBD27 */  addiu      $sp, $sp, -0x40
/* 2E2E8 8003DAE8 3800B2AF */  sw         $s2, 0x38($sp)
/* 2E2EC 8003DAEC 0880123C */  lui        $s2, %hi(g_Spyro + 0xB0)
/* 2E2F0 8003DAF0 088B5226 */  addiu      $s2, $s2, %lo(g_Spyro + 0xB0)
/* 2E2F4 8003DAF4 3C00BFAF */  sw         $ra, 0x3C($sp)
/* 2E2F8 8003DAF8 3400B1AF */  sw         $s1, 0x34($sp)
/* 2E2FC 8003DAFC 3000B0AF */  sw         $s0, 0x30($sp)
/* 2E300 8003DB00 0000428E */  lw         $v0, 0x0($s2)
/* 2E304 8003DB04 00000000 */  nop
/* 2E308 8003DB08 17004228 */  slti       $v0, $v0, 0x17
/* 2E30C 8003DB0C 05004014 */  bnez       $v0, .L8003DB24
/* 2E310 8003DB10 00000000 */   nop
/* 2E314 8003DB14 82F6000C */  jal        RotateSpyroToNeutral
/* 2E318 8003DB18 00000000 */   nop
/* 2E31C 8003DB1C 8AF70008 */  j          .L8003DE28
/* 2E320 8003DB20 00000000 */   nop
.L8003DB24:
/* 2E324 8003DB24 0880043C */  lui        $a0, %hi(g_Spyro + 0x11C)
/* 2E328 8003DB28 748B848C */  lw         $a0, %lo(g_Spyro + 0x11C)($a0)
/* 2E32C 8003DB2C 2C5B000C */  jal        Cos
/* 2E330 8003DB30 00000000 */   nop
/* 2E334 8003DB34 0880043C */  lui        $a0, %hi(g_Spyro + 0x11C)
/* 2E338 8003DB38 748B848C */  lw         $a0, %lo(g_Spyro + 0x11C)($a0)
/* 2E33C 8003DB3C 165B000C */  jal        Sin
/* 2E340 8003DB40 21804000 */   addu      $s0, $v0, $zero
/* 2E344 8003DB44 0880033C */  lui        $v1, %hi(g_Spyro + 0xA4)
/* 2E348 8003DB48 FC8A638C */  lw         $v1, %lo(g_Spyro + 0xA4)($v1)
/* 2E34C 8003DB4C 00000000 */  nop
/* 2E350 8003DB50 18007000 */  mult       $v1, $s0
/* 2E354 8003DB54 12280000 */  mflo       $a1
/* 2E358 8003DB58 0880033C */  lui        $v1, %hi(g_Spyro + 0xA8)
/* 2E35C 8003DB5C 008B638C */  lw         $v1, %lo(g_Spyro + 0xA8)($v1)
/* 2E360 8003DB60 00000000 */  nop
/* 2E364 8003DB64 18006200 */  mult       $v1, $v0
/* 2E368 8003DB68 0880043C */  lui        $a0, %hi(g_Spyro + 0x11C)
/* 2E36C 8003DB6C 748B848C */  lw         $a0, %lo(g_Spyro + 0x11C)($a0)
/* 2E370 8003DB70 12180000 */  mflo       $v1
/* 2E374 8003DB74 2110A300 */  addu       $v0, $a1, $v1
/* 2E378 8003DB78 03130200 */  sra        $v0, $v0, 12
/* 2E37C 8003DB7C 2C5B000C */  jal        Cos
/* 2E380 8003DB80 1000A2AF */   sw        $v0, 0x10($sp)
/* 2E384 8003DB84 0880043C */  lui        $a0, %hi(g_Spyro + 0x11C)
/* 2E388 8003DB88 748B848C */  lw         $a0, %lo(g_Spyro + 0x11C)($a0)
/* 2E38C 8003DB8C 165B000C */  jal        Sin
/* 2E390 8003DB90 21804000 */   addu      $s0, $v0, $zero
/* 2E394 8003DB94 0880033C */  lui        $v1, %hi(g_Spyro + 0xA8)
/* 2E398 8003DB98 008B638C */  lw         $v1, %lo(g_Spyro + 0xA8)($v1)
/* 2E39C 8003DB9C 00000000 */  nop
/* 2E3A0 8003DBA0 18007000 */  mult       $v1, $s0
/* 2E3A4 8003DBA4 12380000 */  mflo       $a3
/* 2E3A8 8003DBA8 1000A38F */  lw         $v1, 0x10($sp)
/* 2E3AC 8003DBAC 00000000 */  nop
/* 2E3B0 8003DBB0 18006300 */  mult       $v1, $v1
/* 2E3B4 8003DBB4 12300000 */  mflo       $a2
/* 2E3B8 8003DBB8 0880033C */  lui        $v1, %hi(g_Spyro + 0xAC)
/* 2E3BC 8003DBBC 048B638C */  lw         $v1, %lo(g_Spyro + 0xAC)($v1)
/* 2E3C0 8003DBC0 00000000 */  nop
/* 2E3C4 8003DBC4 18006300 */  mult       $v1, $v1
/* 2E3C8 8003DBC8 12280000 */  mflo       $a1
/* 2E3CC 8003DBCC 0880043C */  lui        $a0, %hi(g_Spyro + 0xA4)
/* 2E3D0 8003DBD0 FC8A848C */  lw         $a0, %lo(g_Spyro + 0xA4)($a0)
/* 2E3D4 8003DBD4 00000000 */  nop
/* 2E3D8 8003DBD8 18008200 */  mult       $a0, $v0
/* 2E3DC 8003DBDC 1800A3AF */  sw         $v1, 0x18($sp)
/* 2E3E0 8003DBE0 2120C500 */  addu       $a0, $a2, $a1
/* 2E3E4 8003DBE4 12480000 */  mflo       $t1
/* 2E3E8 8003DBE8 2310E900 */  subu       $v0, $a3, $t1
/* 2E3EC 8003DBEC 03130200 */  sra        $v0, $v0, 12
/* 2E3F0 8003DBF0 8E5E000C */  jal        func_80017A38
/* 2E3F4 8003DBF4 1400A2AF */   sw        $v0, 0x14($sp)
/* 2E3F8 8003DBF8 21204000 */  addu       $a0, $v0, $zero
/* 2E3FC 8003DBFC 1400A58F */  lw         $a1, 0x14($sp)
/* 2E400 8003DC00 AD5A000C */  jal        Atan2
/* 2E404 8003DC04 01000624 */   addiu     $a2, $zero, 0x1
/* 2E408 8003DC08 01000624 */  addiu      $a2, $zero, 0x1
/* 2E40C 8003DC0C 1800A48F */  lw         $a0, 0x18($sp)
/* 2E410 8003DC10 1000A58F */  lw         $a1, 0x10($sp)
/* 2E414 8003DC14 23100200 */  negu       $v0, $v0
/* 2E418 8003DC18 AD5A000C */  jal        Atan2
/* 2E41C 8003DC1C 2000A2AF */   sw        $v0, 0x20($sp)
/* 2E420 8003DC20 2000A38F */  lw         $v1, 0x20($sp)
/* 2E424 8003DC24 0880063C */  lui        $a2, %hi(g_Spyro + 0x124)
/* 2E428 8003DC28 7C8BC68C */  lw         $a2, %lo(g_Spyro + 0x124)($a2)
/* 2E42C 8003DC2C 23200200 */  negu       $a0, $v0
/* 2E430 8003DC30 2400A4AF */  sw         $a0, 0x24($sp)
/* 2E434 8003DC34 23186600 */  subu       $v1, $v1, $a2
/* 2E438 8003DC38 FF0F6330 */  andi       $v1, $v1, 0xFFF
/* 2E43C 8003DC3C 01086228 */  slti       $v0, $v1, 0x801
/* 2E440 8003DC40 03004014 */  bnez       $v0, .L8003DC50
/* 2E444 8003DC44 2000A3AF */   sw        $v1, 0x20($sp)
/* 2E448 8003DC48 00F06224 */  addiu      $v0, $v1, -0x1000
/* 2E44C 8003DC4C 2000A2AF */  sw         $v0, 0x20($sp)
.L8003DC50:
/* 2E450 8003DC50 0880073C */  lui        $a3, %hi(g_Spyro + 0x120)
/* 2E454 8003DC54 788BE78C */  lw         $a3, %lo(g_Spyro + 0x120)($a3)
/* 2E458 8003DC58 00000000 */  nop
/* 2E45C 8003DC5C 23108700 */  subu       $v0, $a0, $a3
/* 2E460 8003DC60 FF0F4330 */  andi       $v1, $v0, 0xFFF
/* 2E464 8003DC64 01086228 */  slti       $v0, $v1, 0x801
/* 2E468 8003DC68 03004014 */  bnez       $v0, .L8003DC78
/* 2E46C 8003DC6C 2400A3AF */   sw        $v1, 0x24($sp)
/* 2E470 8003DC70 00F06224 */  addiu      $v0, $v1, -0x1000
/* 2E474 8003DC74 2400A2AF */  sw         $v0, 0x24($sp)
.L8003DC78:
/* 2E478 8003DC78 2000A38F */  lw         $v1, 0x20($sp)
/* 2E47C 8003DC7C 0880053C */  lui        $a1, %hi(g_Spyro + 0x258)
/* 2E480 8003DC80 B08CA58C */  lw         $a1, %lo(g_Spyro + 0x258)($a1)
/* 2E484 8003DC84 2400A48F */  lw         $a0, 0x24($sp)
/* 2E488 8003DC88 80180300 */  sll        $v1, $v1, 2
/* 2E48C 8003DC8C 03190300 */  sra        $v1, $v1, 4
/* 2E490 8003DC90 00110500 */  sll        $v0, $a1, 4
/* 2E494 8003DC94 83110200 */  sra        $v0, $v0, 6
/* 2E498 8003DC98 23186200 */  subu       $v1, $v1, $v0
/* 2E49C 8003DC9C 2128A300 */  addu       $a1, $a1, $v1
/* 2E4A0 8003DCA0 80200400 */  sll        $a0, $a0, 2
/* 2E4A4 8003DCA4 0880033C */  lui        $v1, %hi(g_Spyro + 0x25C)
/* 2E4A8 8003DCA8 B48C638C */  lw         $v1, %lo(g_Spyro + 0x25C)($v1)
/* 2E4AC 8003DCAC 03210400 */  sra        $a0, $a0, 4
/* 2E4B0 8003DCB0 0880013C */  lui        $at, %hi(g_Spyro + 0x258)
/* 2E4B4 8003DCB4 B08C25AC */  sw         $a1, %lo(g_Spyro + 0x258)($at)
/* 2E4B8 8003DCB8 00110300 */  sll        $v0, $v1, 4
/* 2E4BC 8003DCBC 83110200 */  sra        $v0, $v0, 6
/* 2E4C0 8003DCC0 23208200 */  subu       $a0, $a0, $v0
/* 2E4C4 8003DCC4 21186400 */  addu       $v1, $v1, $a0
/* 2E4C8 8003DCC8 83200500 */  sra        $a0, $a1, 2
/* 2E4CC 8003DCCC 0880013C */  lui        $at, %hi(g_Spyro + 0x25C)
/* 2E4D0 8003DCD0 B48C23AC */  sw         $v1, %lo(g_Spyro + 0x25C)($at)
/* 2E4D4 8003DCD4 83180300 */  sra        $v1, $v1, 2
/* 2E4D8 8003DCD8 2110C400 */  addu       $v0, $a2, $a0
/* 2E4DC 8003DCDC FF0F4630 */  andi       $a2, $v0, 0xFFF
/* 2E4E0 8003DCE0 0108C228 */  slti       $v0, $a2, 0x801
/* 2E4E4 8003DCE4 2000A4AF */  sw         $a0, 0x20($sp)
/* 2E4E8 8003DCE8 2400A3AF */  sw         $v1, 0x24($sp)
/* 2E4EC 8003DCEC 0880013C */  lui        $at, %hi(g_Spyro + 0x124)
/* 2E4F0 8003DCF0 7C8B26AC */  sw         $a2, %lo(g_Spyro + 0x124)($at)
/* 2E4F4 8003DCF4 05004014 */  bnez       $v0, .L8003DD0C
/* 2E4F8 8003DCF8 2110E300 */   addu      $v0, $a3, $v1
/* 2E4FC 8003DCFC 00F0C224 */  addiu      $v0, $a2, -0x1000
/* 2E500 8003DD00 0880013C */  lui        $at, %hi(g_Spyro + 0x124)
/* 2E504 8003DD04 7C8B22AC */  sw         $v0, %lo(g_Spyro + 0x124)($at)
/* 2E508 8003DD08 2110E300 */  addu       $v0, $a3, $v1
.L8003DD0C:
/* 2E50C 8003DD0C FF0F4330 */  andi       $v1, $v0, 0xFFF
/* 2E510 8003DD10 0880013C */  lui        $at, %hi(g_Spyro + 0x120)
/* 2E514 8003DD14 788B23AC */  sw         $v1, %lo(g_Spyro + 0x120)($at)
/* 2E518 8003DD18 01086228 */  slti       $v0, $v1, 0x801
/* 2E51C 8003DD1C 03004014 */  bnez       $v0, .L8003DD2C
/* 2E520 8003DD20 00F06224 */   addiu     $v0, $v1, -0x1000
/* 2E524 8003DD24 0880013C */  lui        $at, %hi(g_Spyro + 0x120)
/* 2E528 8003DD28 788B22AC */  sw         $v0, %lo(g_Spyro + 0x120)($at)
.L8003DD2C:
/* 2E52C 8003DD2C 5CFF4292 */  lbu        $v0, -0xA4($s2)
/* 2E530 8003DD30 00000000 */  nop
/* 2E534 8003DD34 E0FF4224 */  addiu      $v0, $v0, -0x20
/* 2E538 8003DD38 FF004230 */  andi       $v0, $v0, 0xFF
/* 2E53C 8003DD3C C100422C */  sltiu      $v0, $v0, 0xC1
/* 2E540 8003DD40 39004014 */  bnez       $v0, .L8003DE28
/* 2E544 8003DD44 5CFF5126 */   addiu     $s1, $s2, -0xA4
/* 2E548 8003DD48 0880023C */  lui        $v0, %hi(g_Spyro + 0xD)
/* 2E54C 8003DD4C 658A4290 */  lbu        $v0, %lo(g_Spyro + 0xD)($v0)
/* 2E550 8003DD50 00000000 */  nop
/* 2E554 8003DD54 E0FF4224 */  addiu      $v0, $v0, -0x20
/* 2E558 8003DD58 FF004230 */  andi       $v0, $v0, 0xFF
/* 2E55C 8003DD5C C100422C */  sltiu      $v0, $v0, 0xC1
/* 2E560 8003DD60 31004014 */  bnez       $v0, .L8003DE28
/* 2E564 8003DD64 00000000 */   nop
/* 2E568 8003DD68 165B000C */  jal        Sin
/* 2E56C 8003DD6C 00000000 */   nop
/* 2E570 8003DD70 23100200 */  negu       $v0, $v0
/* 2E574 8003DD74 40180200 */  sll        $v1, $v0, 1
/* 2E578 8003DD78 21186200 */  addu       $v1, $v1, $v0
/* 2E57C 8003DD7C 40110300 */  sll        $v0, $v1, 5
/* 2E580 8003DD80 23104300 */  subu       $v0, $v0, $v1
/* 2E584 8003DD84 80100200 */  sll        $v0, $v0, 2
/* 2E588 8003DD88 2400A48F */  lw         $a0, 0x24($sp)
/* 2E58C 8003DD8C 03130200 */  sra        $v0, $v0, 12
/* 2E590 8003DD90 165B000C */  jal        Sin
/* 2E594 8003DD94 1400A2AF */   sw        $v0, 0x14($sp)
/* 2E598 8003DD98 23100200 */  negu       $v0, $v0
/* 2E59C 8003DD9C 40180200 */  sll        $v1, $v0, 1
/* 2E5A0 8003DDA0 21186200 */  addu       $v1, $v1, $v0
/* 2E5A4 8003DDA4 40110300 */  sll        $v0, $v1, 5
/* 2E5A8 8003DDA8 23104300 */  subu       $v0, $v0, $v1
/* 2E5AC 8003DDAC 80100200 */  sll        $v0, $v0, 2
/* 2E5B0 8003DDB0 2400A48F */  lw         $a0, 0x24($sp)
/* 2E5B4 8003DDB4 03130200 */  sra        $v0, $v0, 12
/* 2E5B8 8003DDB8 2C5B000C */  jal        Cos
/* 2E5BC 8003DDBC 1000A2AF */   sw        $v0, 0x10($sp)
/* 2E5C0 8003DDC0 2000A48F */  lw         $a0, 0x20($sp)
/* 2E5C4 8003DDC4 2C5B000C */  jal        Cos
/* 2E5C8 8003DDC8 21804000 */   addu      $s0, $v0, $zero
/* 2E5CC 8003DDCC 21202002 */  addu       $a0, $s1, $zero
/* 2E5D0 8003DDD0 84FF5126 */  addiu      $s1, $s2, -0x7C
/* 2E5D4 8003DDD4 21282002 */  addu       $a1, $s1, $zero
/* 2E5D8 8003DDD8 21300000 */  addu       $a2, $zero, $zero
/* 2E5DC 8003DDDC 00200324 */  addiu      $v1, $zero, 0x2000
/* 2E5E0 8003DDE0 23187000 */  subu       $v1, $v1, $s0
/* 2E5E4 8003DDE4 23186200 */  subu       $v1, $v1, $v0
/* 2E5E8 8003DDE8 40380300 */  sll        $a3, $v1, 1
/* 2E5EC 8003DDEC 2138E300 */  addu       $a3, $a3, $v1
/* 2E5F0 8003DDF0 40110700 */  sll        $v0, $a3, 5
/* 2E5F4 8003DDF4 23104700 */  subu       $v0, $v0, $a3
/* 2E5F8 8003DDF8 80100200 */  sll        $v0, $v0, 2
/* 2E5FC 8003DDFC 03130200 */  sra        $v0, $v0, 12
/* 2E600 8003DE00 4B5B000C */  jal        RotVec8ToMatrix
/* 2E604 8003DE04 1800A2AF */   sw        $v0, 0x18($sp)
/* 2E608 8003DE08 21202002 */  addu       $a0, $s1, $zero
/* 2E60C 8003DE0C 1000A527 */  addiu      $a1, $sp, 0x10
/* 2E610 8003DE10 125C000C */  jal        VecRotateByMatrix
/* 2E614 8003DE14 2130A000 */   addu      $a2, $a1, $zero
/* 2E618 8003DE18 50FF4426 */  addiu      $a0, $s2, -0xB0
/* 2E61C 8003DE1C 21288000 */  addu       $a1, $a0, $zero
/* 2E620 8003DE20 D65D000C */  jal        VecAdd
/* 2E624 8003DE24 1000A627 */   addiu     $a2, $sp, 0x10
.L8003DE28:
/* 2E628 8003DE28 3C00BF8F */  lw         $ra, 0x3C($sp)
/* 2E62C 8003DE2C 3800B28F */  lw         $s2, 0x38($sp)
/* 2E630 8003DE30 3400B18F */  lw         $s1, 0x34($sp)
/* 2E634 8003DE34 3000B08F */  lw         $s0, 0x30($sp)
/* 2E638 8003DE38 4000BD27 */  addiu      $sp, $sp, 0x40
/* 2E63C 8003DE3C 0800E003 */  jr         $ra
/* 2E640 8003DE40 00000000 */   nop
.size func_8003DAE4, . - func_8003DAE4
