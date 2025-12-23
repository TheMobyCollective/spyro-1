.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8004A200
/* 3AA00 8004A200 0880023C */  lui        $v0, %hi(g_Spyro + 0x1F4)
/* 3AA04 8004A204 4C8C428C */  lw         $v0, %lo(g_Spyro + 0x1F4)($v0)
/* 3AA08 8004A208 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 3AA0C 8004A20C 5000BFAF */  sw         $ra, 0x50($sp)
/* 3AA10 8004A210 4C00B1AF */  sw         $s1, 0x4C($sp)
/* 3AA14 8004A214 00204230 */  andi       $v0, $v0, 0x2000
/* 3AA18 8004A218 06004014 */  bnez       $v0, .L8004A234
/* 3AA1C 8004A21C 4800B0AF */   sw        $s0, 0x48($sp)
/* 3AA20 8004A220 0880023C */  lui        $v0, %hi(g_Spyro + 0x194)
/* 3AA24 8004A224 EC8B428C */  lw         $v0, %lo(g_Spyro + 0x194)($v0)
/* 3AA28 8004A228 00000000 */  nop
/* 3AA2C 8004A22C 09004010 */  beqz       $v0, .L8004A254
/* 3AA30 8004A230 00000000 */   nop
.L8004A234:
/* 3AA34 8004A234 0880023C */  lui        $v0, %hi(g_Spyro + 0x1F0)
/* 3AA38 8004A238 488C428C */  lw         $v0, %lo(g_Spyro + 0x1F0)($v0)
/* 3AA3C 8004A23C 00000000 */  nop
/* 3AA40 8004A240 02004228 */  slti       $v0, $v0, 0x2
/* 3AA44 8004A244 03004010 */  beqz       $v0, .L8004A254
/* 3AA48 8004A248 02000224 */   addiu     $v0, $zero, 0x2
/* 3AA4C 8004A24C 0880013C */  lui        $at, %hi(g_Spyro + 0x1F0)
/* 3AA50 8004A250 488C22AC */  sw         $v0, %lo(g_Spyro + 0x1F0)($at)
.L8004A254:
/* 3AA54 8004A254 0880103C */  lui        $s0, %hi(g_Spyro + 0x1F0)
/* 3AA58 8004A258 488C1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x1F0)
/* 3AA5C 8004A25C 0000028E */  lw         $v0, 0x0($s0)
/* 3AA60 8004A260 0780013C */  lui        $at, %hi(D_80075944)
/* 3AA64 8004A264 445920A0 */  sb         $zero, %lo(D_80075944)($at)
/* 3AA68 8004A268 0B004010 */  beqz       $v0, .L8004A298
/* 3AA6C 8004A26C 00000000 */   nop
/* 3AA70 8004A270 0780043C */  lui        $a0, %hi(g_Pad)
/* 3AA74 8004A274 78738424 */  addiu      $a0, $a0, %lo(g_Pad)
/* 3AA78 8004A278 0780053C */  lui        $a1, %hi(D_800776D8)
/* 3AA7C 8004A27C D876A524 */  addiu      $a1, $a1, %lo(D_800776D8)
/* 3AA80 8004A280 C24D010C */  jal        func_80053708
/* 3AA84 8004A284 00000000 */   nop
/* 3AA88 8004A288 0000028E */  lw         $v0, 0x0($s0)
/* 3AA8C 8004A28C 00000000 */  nop
/* 3AA90 8004A290 FFFF4224 */  addiu      $v0, $v0, -0x1
/* 3AA94 8004A294 000002AE */  sw         $v0, 0x0($s0)
.L8004A298:
/* 3AA98 8004A298 E722010C */  jal        UpdateSpyroPhysicsAndSurfaces
/* 3AA9C 8004A29C 00000000 */   nop
/* 3AAA0 8004A2A0 0880033C */  lui        $v1, %hi(g_Spyro + 0x78)
/* 3AAA4 8004A2A4 D08A638C */  lw         $v1, %lo(g_Spyro + 0x78)($v1)
/* 3AAA8 8004A2A8 1D000224 */  addiu      $v0, $zero, 0x1D
/* 3AAAC 8004A2AC 0A006214 */  bne        $v1, $v0, .L8004A2D8
/* 3AAB0 8004A2B0 00000000 */   nop
/* 3AAB4 8004A2B4 0880023C */  lui        $v0, %hi(g_Spyro + 0x168)
/* 3AAB8 8004A2B8 C08B428C */  lw         $v0, %lo(g_Spyro + 0x168)($v0)
/* 3AABC 8004A2BC 00000000 */  nop
/* 3AAC0 8004A2C0 0700401C */  bgtz       $v0, .L8004A2E0
/* 3AAC4 8004A2C4 01000224 */   addiu     $v0, $zero, 0x1
/* 3AAC8 8004A2C8 0880013C */  lui        $at, %hi(g_Spyro + 0x168)
/* 3AACC 8004A2CC C08B22AC */  sw         $v0, %lo(g_Spyro + 0x168)($at)
/* 3AAD0 8004A2D0 B8280108 */  j          .L8004A2E0
/* 3AAD4 8004A2D4 00000000 */   nop
.L8004A2D8:
/* 3AAD8 8004A2D8 0880013C */  lui        $at, %hi(g_Spyro + 0x168)
/* 3AADC 8004A2DC C08B20AC */  sw         $zero, %lo(g_Spyro + 0x168)($at)
.L8004A2E0:
/* 3AAE0 8004A2E0 0880023C */  lui        $v0, %hi(g_Spyro + 0x1F4)
/* 3AAE4 8004A2E4 4C8C428C */  lw         $v0, %lo(g_Spyro + 0x1F4)($v0)
/* 3AAE8 8004A2E8 00000000 */  nop
/* 3AAEC 8004A2EC 00014230 */  andi       $v0, $v0, 0x100
/* 3AAF0 8004A2F0 08004014 */  bnez       $v0, .L8004A314
/* 3AAF4 8004A2F4 00000000 */   nop
/* 3AAF8 8004A2F8 0880023C */  lui        $v0, %hi(g_Spyro + 0x194)
/* 3AAFC 8004A2FC EC8B428C */  lw         $v0, %lo(g_Spyro + 0x194)($v0)
/* 3AB00 8004A300 00000000 */  nop
/* 3AB04 8004A304 03004014 */  bnez       $v0, .L8004A314
/* 3AB08 8004A308 00000000 */   nop
/* 3AB0C 8004A30C 9C05010C */  jal        func_80041670
/* 3AB10 8004A310 00000000 */   nop
.L8004A314:
/* 3AB14 8004A314 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3AB18 8004A318 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3AB1C 8004A31C 00000000 */  nop
/* 3AB20 8004A320 11004018 */  blez       $v0, .L8004A368
/* 3AB24 8004A324 21800000 */   addu      $s0, $zero, $zero
.L8004A328:
/* 3AB28 8004A328 65F4000C */  jal        UpdateBodyAnimationState
/* 3AB2C 8004A32C 01001026 */   addiu     $s0, $s0, 0x1
/* 3AB30 8004A330 7026010C */  jal        func_800499C0
/* 3AB34 8004A334 00000000 */   nop
/* 3AB38 8004A338 9825010C */  jal        func_80049660
/* 3AB3C 8004A33C 00000000 */   nop
/* 3AB40 8004A340 CF27010C */  jal        func_80049F3C
/* 3AB44 8004A344 00000000 */   nop
/* 3AB48 8004A348 A327010C */  jal        func_80049E8C
/* 3AB4C 8004A34C 00000000 */   nop
/* 3AB50 8004A350 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3AB54 8004A354 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3AB58 8004A358 00000000 */  nop
/* 3AB5C 8004A35C 2A100202 */  slt        $v0, $s0, $v0
/* 3AB60 8004A360 F1FF4014 */  bnez       $v0, .L8004A328
/* 3AB64 8004A364 00000000 */   nop
.L8004A368:
/* 3AB68 8004A368 0880103C */  lui        $s0, %hi(g_Spyro + 0xC)
/* 3AB6C 8004A36C 648A1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0xC)
/* 3AB70 8004A370 21200002 */  addu       $a0, $s0, $zero
/* 3AB74 8004A374 28001126 */  addiu      $s1, $s0, 0x28
/* 3AB78 8004A378 21282002 */  addu       $a1, $s1, $zero
/* 3AB7C 8004A37C 0880023C */  lui        $v0, %hi(g_Spyro + 0x124)
/* 3AB80 8004A380 7C8B428C */  lw         $v0, %lo(g_Spyro + 0x124)($v0)
/* 3AB84 8004A384 00000000 */  nop
/* 3AB88 8004A388 03110200 */  sra        $v0, $v0, 4
/* 3AB8C 8004A38C 000002A2 */  sb         $v0, 0x0($s0)
/* 3AB90 8004A390 0880023C */  lui        $v0, %hi(g_Spyro + 0x120)
/* 3AB94 8004A394 788B428C */  lw         $v0, %lo(g_Spyro + 0x120)($v0)
/* 3AB98 8004A398 0880033C */  lui        $v1, %hi(g_Spyro + 0x11C)
/* 3AB9C 8004A39C 748B638C */  lw         $v1, %lo(g_Spyro + 0x11C)($v1)
/* 3ABA0 8004A3A0 03110200 */  sra        $v0, $v0, 4
/* 3ABA4 8004A3A4 03190300 */  sra        $v1, $v1, 4
/* 3ABA8 8004A3A8 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 3ABAC 8004A3AC 658A22A0 */  sb         $v0, %lo(g_Spyro + 0xD)($at)
/* 3ABB0 8004A3B0 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 3ABB4 8004A3B4 668A23A0 */  sb         $v1, %lo(g_Spyro + 0xE)($at)
/* 3ABB8 8004A3B8 4B5B000C */  jal        RotVec8ToMatrix
/* 3ABBC 8004A3BC 21300000 */   addu      $a2, $zero, $zero
/* 3ABC0 8004A3C0 04000426 */  addiu      $a0, $s0, 0x4
/* 3ABC4 8004A3C4 BC011026 */  addiu      $s0, $s0, 0x1BC
/* 3ABC8 8004A3C8 21280002 */  addu       $a1, $s0, $zero
/* 3ABCC 8004A3CC 4B5B000C */  jal        RotVec8ToMatrix
/* 3ABD0 8004A3D0 21300000 */   addu      $a2, $zero, $zero
/* 3ABD4 8004A3D4 21202002 */  addu       $a0, $s1, $zero
/* 3ABD8 8004A3D8 21280002 */  addu       $a1, $s0, $zero
/* 3ABDC 8004A3DC F688010C */  jal        MulMatrix0
/* 3ABE0 8004A3E0 2130A000 */   addu      $a2, $a1, $zero
/* 3ABE4 8004A3E4 EB27010C */  jal        func_80049FAC
/* 3ABE8 8004A3E8 01000424 */   addiu     $a0, $zero, 0x1
/* 3ABEC 8004A3EC 0780043C */  lui        $a0, %hi(g_DeltaTime)
/* 3ABF0 8004A3F0 CC56848C */  lw         $a0, %lo(g_DeltaTime)($a0)
/* 3ABF4 8004A3F4 4423010C */  jal        func_80048D10
/* 3ABF8 8004A3F8 00000000 */   nop
/* 3ABFC 8004A3FC 0880023C */  lui        $v0, %hi(g_Spyro + 0x164)
/* 3AC00 8004A400 BC8B428C */  lw         $v0, %lo(g_Spyro + 0x164)($v0)
/* 3AC04 8004A404 0880013C */  lui        $at, %hi(g_Spyro + 0x2C)
/* 3AC08 8004A408 848A20AC */  sw         $zero, %lo(g_Spyro + 0x2C)($at)
/* 3AC0C 8004A40C 36004104 */  bgez       $v0, .L8004A4E8
/* 3AC10 8004A410 1E000224 */   addiu     $v0, $zero, 0x1E
/* 3AC14 8004A414 0880033C */  lui        $v1, %hi(g_Spyro + 0x78)
/* 3AC18 8004A418 D08A638C */  lw         $v1, %lo(g_Spyro + 0x78)($v1)
/* 3AC1C 8004A41C 00000000 */  nop
/* 3AC20 8004A420 23006210 */  beq        $v1, $v0, .L8004A4B0
/* 3AC24 8004A424 00000000 */   nop
/* 3AC28 8004A428 1F006228 */  slti       $v0, $v1, 0x1F
/* 3AC2C 8004A42C 05004010 */  beqz       $v0, .L8004A444
/* 3AC30 8004A430 1D000224 */   addiu     $v0, $zero, 0x1D
/* 3AC34 8004A434 08006210 */  beq        $v1, $v0, .L8004A458
/* 3AC38 8004A438 40020224 */   addiu     $v0, $zero, 0x240
/* 3AC3C 8004A43C 8E290108 */  j          .L8004A638
/* 3AC40 8004A440 00000000 */   nop
.L8004A444:
/* 3AC44 8004A444 1F000224 */  addiu      $v0, $zero, 0x1F
/* 3AC48 8004A448 1D006210 */  beq        $v1, $v0, .L8004A4C0
/* 3AC4C 8004A44C 00000000 */   nop
/* 3AC50 8004A450 8E290108 */  j          .L8004A638
/* 3AC54 8004A454 00000000 */   nop
.L8004A458:
/* 3AC58 8004A458 0880033C */  lui        $v1, %hi(g_Spyro + 0x168)
/* 3AC5C 8004A45C C08B638C */  lw         $v1, %lo(g_Spyro + 0x168)($v1)
/* 3AC60 8004A460 00000000 */  nop
/* 3AC64 8004A464 74006214 */  bne        $v1, $v0, .L8004A638
/* 3AC68 8004A468 00000000 */   nop
/* 3AC6C 8004A46C 0780023C */  lui        $v0, %hi(D_80075690)
/* 3AC70 8004A470 9056428C */  lw         $v0, %lo(D_80075690)($v0)
/* 3AC74 8004A474 00000000 */  nop
/* 3AC78 8004A478 17004010 */  beqz       $v0, .L8004A4D8
/* 3AC7C 8004A47C 00000000 */   nop
/* 3AC80 8004A480 0780023C */  lui        $v0, %hi(D_80075694)
/* 3AC84 8004A484 9456428C */  lw         $v0, %lo(D_80075694)($v0)
/* 3AC88 8004A488 00000000 */  nop
/* 3AC8C 8004A48C 09F84000 */  jalr       $v0
/* 3AC90 8004A490 00000000 */   nop
/* 3AC94 8004A494 0780023C */  lui        $v0, %hi(D_80075734)
/* 3AC98 8004A498 3457428C */  lw         $v0, %lo(D_80075734)($v0)
/* 3AC9C 8004A49C 00000000 */  nop
/* 3ACA0 8004A4A0 09F84000 */  jalr       $v0
/* 3ACA4 8004A4A4 00000000 */   nop
/* 3ACA8 8004A4A8 8E290108 */  j          .L8004A638
/* 3ACAC 8004A4AC 00000000 */   nop
.L8004A4B0:
/* 3ACB0 8004A4B0 0880023C */  lui        $v0, %hi(g_Spyro + 0x80)
/* 3ACB4 8004A4B4 D88A428C */  lw         $v0, %lo(g_Spyro + 0x80)($v0)
/* 3ACB8 8004A4B8 34290108 */  j          .L8004A4D0
/* 3ACBC 8004A4BC 65004228 */   slti      $v0, $v0, 0x65
.L8004A4C0:
/* 3ACC0 8004A4C0 0880023C */  lui        $v0, %hi(g_Spyro + 0x80)
/* 3ACC4 8004A4C4 D88A428C */  lw         $v0, %lo(g_Spyro + 0x80)($v0)
/* 3ACC8 8004A4C8 00000000 */  nop
/* 3ACCC 8004A4CC 7D004228 */  slti       $v0, $v0, 0x7D
.L8004A4D0:
/* 3ACD0 8004A4D0 59004014 */  bnez       $v0, .L8004A638
/* 3ACD4 8004A4D4 00000000 */   nop
.L8004A4D8:
/* 3ACD8 8004A4D8 17B2000C */  jal        func_8002C85C
/* 3ACDC 8004A4DC 00000000 */   nop
/* 3ACE0 8004A4E0 8E290108 */  j          .L8004A638
/* 3ACE4 8004A4E4 00000000 */   nop
.L8004A4E8:
/* 3ACE8 8004A4E8 0880023C */  lui        $v0, %hi(g_Spyro + 0x8)
/* 3ACEC 8004A4EC 608A428C */  lw         $v0, %lo(g_Spyro + 0x8)($v0)
/* 3ACF0 8004A4F0 00000000 */  nop
/* 3ACF4 8004A4F4 00044228 */  slti       $v0, $v0, 0x400
/* 3ACF8 8004A4F8 F7FF4014 */  bnez       $v0, .L8004A4D8
/* 3ACFC 8004A4FC 06000224 */   addiu     $v0, $zero, 0x6
/* 3AD00 8004A500 0880033C */  lui        $v1, %hi(g_Spyro + 0x78)
/* 3AD04 8004A504 D08A638C */  lw         $v1, %lo(g_Spyro + 0x78)($v1)
/* 3AD08 8004A508 00000000 */  nop
/* 3AD0C 8004A50C 07006214 */  bne        $v1, $v0, .L8004A52C
/* 3AD10 8004A510 00000000 */   nop
/* 3AD14 8004A514 0880023C */  lui        $v0, %hi(g_Spyro + 0x7C)
/* 3AD18 8004A518 D48A428C */  lw         $v0, %lo(g_Spyro + 0x7C)($v0)
/* 3AD1C 8004A51C 00000000 */  nop
/* 3AD20 8004A520 79004228 */  slti       $v0, $v0, 0x79
/* 3AD24 8004A524 ECFF4010 */  beqz       $v0, .L8004A4D8
/* 3AD28 8004A528 00000000 */   nop
.L8004A52C:
/* 3AD2C 8004A52C 0880103C */  lui        $s0, %hi(g_Spyro + 0x8)
/* 3AD30 8004A530 608A1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x8)
/* 3AD34 8004A534 0780023C */  lui        $v0, %hi(g_LevelIndex)
/* 3AD38 8004A538 6459428C */  lw         $v0, %lo(g_LevelIndex)($v0)
/* 3AD3C 8004A53C 0000038E */  lw         $v1, 0x0($s0)
/* 3AD40 8004A540 80100200 */  sll        $v0, $v0, 2
/* 3AD44 8004A544 0780013C */  lui        $at, %hi(D_8006E9A4)
/* 3AD48 8004A548 21082200 */  addu       $at, $at, $v0
/* 3AD4C 8004A54C A4E9228C */  lw         $v0, %lo(D_8006E9A4)($at)
/* 3AD50 8004A550 00000000 */  nop
/* 3AD54 8004A554 2A186200 */  slt        $v1, $v1, $v0
/* 3AD58 8004A558 0A006010 */  beqz       $v1, .L8004A584
/* 3AD5C 8004A55C 06000224 */   addiu     $v0, $zero, 0x6
/* 3AD60 8004A560 0880033C */  lui        $v1, %hi(g_Spyro + 0x78)
/* 3AD64 8004A564 D08A638C */  lw         $v1, %lo(g_Spyro + 0x78)($v1)
/* 3AD68 8004A568 00000000 */  nop
/* 3AD6C 8004A56C 1E006210 */  beq        $v1, $v0, .L8004A5E8
/* 3AD70 8004A570 10000224 */   addiu     $v0, $zero, 0x10
/* 3AD74 8004A574 1C006210 */  beq        $v1, $v0, .L8004A5E8
/* 3AD78 8004A578 00000000 */   nop
/* 3AD7C 8004A57C 78290108 */  j          .L8004A5E0
/* 3AD80 8004A580 00000000 */   nop
.L8004A584:
/* 3AD84 8004A584 0880023C */  lui        $v0, %hi(g_Spyro)
/* 3AD88 8004A588 588A428C */  lw         $v0, %lo(g_Spyro)($v0)
/* 3AD8C 8004A58C 00000000 */  nop
/* 3AD90 8004A590 00084228 */  slti       $v0, $v0, 0x800
/* 3AD94 8004A594 07004014 */  bnez       $v0, .L8004A5B4
/* 3AD98 8004A598 00000000 */   nop
/* 3AD9C 8004A59C 0880023C */  lui        $v0, %hi(g_Spyro + 0x4)
/* 3ADA0 8004A5A0 5C8A428C */  lw         $v0, %lo(g_Spyro + 0x4)($v0)
/* 3ADA4 8004A5A4 00000000 */  nop
/* 3ADA8 8004A5A8 00084228 */  slti       $v0, $v0, 0x800
/* 3ADAC 8004A5AC 22004010 */  beqz       $v0, .L8004A638
/* 3ADB0 8004A5B0 00000000 */   nop
.L8004A5B4:
/* 3ADB4 8004A5B4 0880033C */  lui        $v1, %hi(g_Spyro + 0x78)
/* 3ADB8 8004A5B8 D08A638C */  lw         $v1, %lo(g_Spyro + 0x78)($v1)
/* 3ADBC 8004A5BC 06000224 */  addiu      $v0, $zero, 0x6
/* 3ADC0 8004A5C0 09006210 */  beq        $v1, $v0, .L8004A5E8
/* 3ADC4 8004A5C4 10000224 */   addiu     $v0, $zero, 0x10
/* 3ADC8 8004A5C8 07006210 */  beq        $v1, $v0, .L8004A5E8
/* 3ADCC 8004A5CC 00000000 */   nop
/* 3ADD0 8004A5D0 BC5D000C */  jal        VecNull
/* 3ADD4 8004A5D4 04010426 */   addiu     $a0, $s0, 0x104
/* 3ADD8 8004A5D8 BC5D000C */  jal        VecNull
/* 3ADDC 8004A5DC EC000426 */   addiu     $a0, $s0, 0xEC
.L8004A5E0:
/* 3ADE0 8004A5E0 9AFA000C */  jal        func_8003EA68
/* 3ADE4 8004A5E4 06000424 */   addiu     $a0, $zero, 0x6
.L8004A5E8:
/* 3ADE8 8004A5E8 0880113C */  lui        $s1, %hi(g_Spyro + 0x7C)
/* 3ADEC 8004A5EC D48A3126 */  addiu      $s1, $s1, %lo(g_Spyro + 0x7C)
/* 3ADF0 8004A5F0 0000228E */  lw         $v0, 0x0($s1)
/* 3ADF4 8004A5F4 00000000 */  nop
/* 3ADF8 8004A5F8 0A004014 */  bnez       $v0, .L8004A624
/* 3ADFC 8004A5FC 00000000 */   nop
/* 3AE00 8004A600 0780103C */  lui        $s0, %hi(D_8006EBCC + 0x18)
/* 3AE04 8004A604 E4EB1026 */  addiu      $s0, $s0, %lo(D_8006EBCC + 0x18)
/* 3AE08 8004A608 0780053C */  lui        $a1, %hi(g_Camera + 0x28)
/* 3AE0C 8004A60C F86DA524 */  addiu      $a1, $a1, %lo(g_Camera + 0x28)
/* 3AE10 8004A610 C05D000C */  jal        VecCopy
/* 3AE14 8004A614 21200002 */   addu      $a0, $s0, $zero
/* 3AE18 8004A618 C5DD000C */  jal        func_80037714
/* 3AE1C 8004A61C E8FF0426 */   addiu     $a0, $s0, -0x18
/* 3AE20 8004A620 0000228E */  lw         $v0, 0x0($s1)
.L8004A624:
/* 3AE24 8004A624 0780033C */  lui        $v1, %hi(g_DeltaTime)
/* 3AE28 8004A628 CC56638C */  lw         $v1, %lo(g_DeltaTime)($v1)
/* 3AE2C 8004A62C 00000000 */  nop
/* 3AE30 8004A630 21104300 */  addu       $v0, $v0, $v1
/* 3AE34 8004A634 000022AE */  sw         $v0, 0x0($s1)
.L8004A638:
/* 3AE38 8004A638 0880073C */  lui        $a3, %hi(g_Spyro + 0x18)
/* 3AE3C 8004A63C 708AE724 */  addiu      $a3, $a3, %lo(g_Spyro + 0x18)
/* 3AE40 8004A640 0000E290 */  lbu        $v0, 0x0($a3)
/* 3AE44 8004A644 0780033C */  lui        $v1, %hi(g_Models)
/* 3AE48 8004A648 7863638C */  lw         $v1, %lo(g_Models)($v1)
/* 3AE4C 8004A64C 80100200 */  sll        $v0, $v0, 2
/* 3AE50 8004A650 21284300 */  addu       $a1, $v0, $v1
/* 3AE54 8004A654 0880033C */  lui        $v1, %hi(g_Spyro + 0x1E)
/* 3AE58 8004A658 768A6390 */  lbu        $v1, %lo(g_Spyro + 0x1E)($v1)
/* 3AE5C 8004A65C 3800A28C */  lw         $v0, 0x38($a1)
/* 3AE60 8004A660 80180300 */  sll        $v1, $v1, 2
/* 3AE64 8004A664 21106200 */  addu       $v0, $v1, $v0
/* 3AE68 8004A668 27004490 */  lbu        $a0, 0x27($v0)
/* 3AE6C 8004A66C FF000224 */  addiu      $v0, $zero, 0xFF
/* 3AE70 8004A670 0D008210 */  beq        $a0, $v0, .L8004A6A8
/* 3AE74 8004A674 3000A4AF */   sw        $a0, 0x30($sp)
/* 3AE78 8004A678 3800A28C */  lw         $v0, 0x38($a1)
/* 3AE7C 8004A67C 00000000 */  nop
/* 3AE80 8004A680 21106200 */  addu       $v0, $v1, $v0
/* 3AE84 8004A684 0880033C */  lui        $v1, %hi(g_Spyro + 0x264)
/* 3AE88 8004A688 BC8C638C */  lw         $v1, %lo(g_Spyro + 0x264)($v1)
/* 3AE8C 8004A68C 2400428C */  lw         $v0, 0x24($v0)
/* 3AE90 8004A690 00000000 */  nop
/* 3AE94 8004A694 04006210 */  beq        $v1, $v0, .L8004A6A8
/* 3AE98 8004A698 E8FFE524 */   addiu     $a1, $a3, -0x18
/* 3AE9C 8004A69C 04000624 */  addiu      $a2, $zero, 0x4
/* 3AEA0 8004A6A0 9E56010C */  jal        PlaySound
/* 3AEA4 8004A6A4 8802E724 */   addiu     $a3, $a3, 0x288
.L8004A6A8:
/* 3AEA8 8004A6A8 0880033C */  lui        $v1, %hi(g_Spyro + 0x18)
/* 3AEAC 8004A6AC 708A6390 */  lbu        $v1, %lo(g_Spyro + 0x18)($v1)
/* 3AEB0 8004A6B0 0780043C */  lui        $a0, %hi(g_Models)
/* 3AEB4 8004A6B4 7863848C */  lw         $a0, %lo(g_Models)($a0)
/* 3AEB8 8004A6B8 0880023C */  lui        $v0, %hi(g_Spyro + 0x1E)
/* 3AEBC 8004A6BC 768A4290 */  lbu        $v0, %lo(g_Spyro + 0x1E)($v0)
/* 3AEC0 8004A6C0 80180300 */  sll        $v1, $v1, 2
/* 3AEC4 8004A6C4 21186400 */  addu       $v1, $v1, $a0
/* 3AEC8 8004A6C8 3800638C */  lw         $v1, 0x38($v1)
/* 3AECC 8004A6CC 80100200 */  sll        $v0, $v0, 2
/* 3AED0 8004A6D0 21104300 */  addu       $v0, $v0, $v1
/* 3AED4 8004A6D4 2400438C */  lw         $v1, 0x24($v0)
/* 3AED8 8004A6D8 0880023C */  lui        $v0, %hi(g_Spyro + 0x1A)
/* 3AEDC 8004A6DC 728A4290 */  lbu        $v0, %lo(g_Spyro + 0x1A)($v0)
/* 3AEE0 8004A6E0 0880073C */  lui        $a3, %hi(g_Spyro + 0x264)
/* 3AEE4 8004A6E4 BC8CE724 */  addiu      $a3, $a3, %lo(g_Spyro + 0x264)
/* 3AEE8 8004A6E8 80100200 */  sll        $v0, $v0, 2
/* 3AEEC 8004A6EC 21284400 */  addu       $a1, $v0, $a0
/* 3AEF0 8004A6F0 0000E3AC */  sw         $v1, 0x0($a3)
/* 3AEF4 8004A6F4 0880033C */  lui        $v1, %hi(g_Spyro + 0x20)
/* 3AEF8 8004A6F8 788A6390 */  lbu        $v1, %lo(g_Spyro + 0x20)($v1)
/* 3AEFC 8004A6FC 3800A28C */  lw         $v0, 0x38($a1)
/* 3AF00 8004A700 80180300 */  sll        $v1, $v1, 2
/* 3AF04 8004A704 21106200 */  addu       $v0, $v1, $v0
/* 3AF08 8004A708 27004490 */  lbu        $a0, 0x27($v0)
/* 3AF0C 8004A70C FF000224 */  addiu      $v0, $zero, 0xFF
/* 3AF10 8004A710 11008210 */  beq        $a0, $v0, .L8004A758
/* 3AF14 8004A714 3400A4AF */   sw        $a0, 0x34($sp)
/* 3AF18 8004A718 3000A28F */  lw         $v0, 0x30($sp)
/* 3AF1C 8004A71C 00000000 */  nop
/* 3AF20 8004A720 0D004410 */  beq        $v0, $a0, .L8004A758
/* 3AF24 8004A724 00000000 */   nop
/* 3AF28 8004A728 3800A28C */  lw         $v0, 0x38($a1)
/* 3AF2C 8004A72C 00000000 */  nop
/* 3AF30 8004A730 21106200 */  addu       $v0, $v1, $v0
/* 3AF34 8004A734 0880033C */  lui        $v1, %hi(g_Spyro + 0x268)
/* 3AF38 8004A738 C08C638C */  lw         $v1, %lo(g_Spyro + 0x268)($v1)
/* 3AF3C 8004A73C 2400428C */  lw         $v0, 0x24($v0)
/* 3AF40 8004A740 00000000 */  nop
/* 3AF44 8004A744 04006210 */  beq        $v1, $v0, .L8004A758
/* 3AF48 8004A748 9CFDE524 */   addiu     $a1, $a3, -0x264
/* 3AF4C 8004A74C 04000624 */  addiu      $a2, $zero, 0x4
/* 3AF50 8004A750 9E56010C */  jal        PlaySound
/* 3AF54 8004A754 3C00E724 */   addiu     $a3, $a3, 0x3C
.L8004A758:
/* 3AF58 8004A758 FF7F053C */  lui        $a1, (0x7FFFFFFF >> 16)
/* 3AF5C 8004A75C FFFFA534 */  ori        $a1, $a1, (0x7FFFFFFF & 0xFFFF)
/* 3AF60 8004A760 0880033C */  lui        $v1, %hi(g_Spyro + 0x1A)
/* 3AF64 8004A764 728A6390 */  lbu        $v1, %lo(g_Spyro + 0x1A)($v1)
/* 3AF68 8004A768 0780023C */  lui        $v0, %hi(g_Models)
/* 3AF6C 8004A76C 7863428C */  lw         $v0, %lo(g_Models)($v0)
/* 3AF70 8004A770 80180300 */  sll        $v1, $v1, 2
/* 3AF74 8004A774 21186200 */  addu       $v1, $v1, $v0
/* 3AF78 8004A778 0880023C */  lui        $v0, %hi(g_Spyro + 0x20)
/* 3AF7C 8004A77C 788A4290 */  lbu        $v0, %lo(g_Spyro + 0x20)($v0)
/* 3AF80 8004A780 3800638C */  lw         $v1, 0x38($v1)
/* 3AF84 8004A784 80100200 */  sll        $v0, $v0, 2
/* 3AF88 8004A788 21104300 */  addu       $v0, $v0, $v1
/* 3AF8C 8004A78C 2400448C */  lw         $a0, 0x24($v0)
/* 3AF90 8004A790 0880023C */  lui        $v0, %hi(g_Spyro + 0x1F4)
/* 3AF94 8004A794 4C8C428C */  lw         $v0, %lo(g_Spyro + 0x1F4)($v0)
/* 3AF98 8004A798 0780033C */  lui        $v1, %hi(D_80075944)
/* 3AF9C 8004A79C 44596390 */  lbu        $v1, %lo(D_80075944)($v1)
/* 3AFA0 8004A7A0 24104500 */  and        $v0, $v0, $a1
/* 3AFA4 8004A7A4 0880013C */  lui        $at, %hi(g_Spyro + 0x1F4)
/* 3AFA8 8004A7A8 4C8C22AC */  sw         $v0, %lo(g_Spyro + 0x1F4)($at)
/* 3AFAC 8004A7AC 0880013C */  lui        $at, %hi(g_Spyro + 0x268)
/* 3AFB0 8004A7B0 C08C24AC */  sw         $a0, %lo(g_Spyro + 0x268)($at)
/* 3AFB4 8004A7B4 07006010 */  beqz       $v1, .L8004A7D4
/* 3AFB8 8004A7B8 00000000 */   nop
/* 3AFBC 8004A7BC 0780043C */  lui        $a0, %hi(D_800776D8)
/* 3AFC0 8004A7C0 D8768424 */  addiu      $a0, $a0, %lo(D_800776D8)
/* 3AFC4 8004A7C4 0780053C */  lui        $a1, %hi(g_Pad)
/* 3AFC8 8004A7C8 7873A524 */  addiu      $a1, $a1, %lo(g_Pad)
/* 3AFCC 8004A7CC C24D010C */  jal        func_80053708
/* 3AFD0 8004A7D0 00000000 */   nop
.L8004A7D4:
/* 3AFD4 8004A7D4 5000BF8F */  lw         $ra, 0x50($sp)
/* 3AFD8 8004A7D8 4C00B18F */  lw         $s1, 0x4C($sp)
/* 3AFDC 8004A7DC 4800B08F */  lw         $s0, 0x48($sp)
/* 3AFE0 8004A7E0 5800BD27 */  addiu      $sp, $sp, 0x58
/* 3AFE4 8004A7E4 0800E003 */  jr         $ra
/* 3AFE8 8004A7E8 00000000 */   nop
.size func_8004A200, . - func_8004A200
