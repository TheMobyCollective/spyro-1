.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003E318
/* 2EB18 8003E318 B0FFBD27 */  addiu      $sp, $sp, -0x50
/* 2EB1C 8003E31C 3800B2AF */  sw         $s2, 0x38($sp)
/* 2EB20 8003E320 0880123C */  lui        $s2, %hi(g_Spyro + 0x9C)
/* 2EB24 8003E324 F48A5226 */  addiu      $s2, $s2, %lo(g_Spyro + 0x9C)
/* 2EB28 8003E328 3000B0AF */  sw         $s0, 0x30($sp)
/* 2EB2C 8003E32C 08005026 */  addiu      $s0, $s2, 0x8
/* 2EB30 8003E330 4C00BFAF */  sw         $ra, 0x4C($sp)
/* 2EB34 8003E334 4800B6AF */  sw         $s6, 0x48($sp)
/* 2EB38 8003E338 4400B5AF */  sw         $s5, 0x44($sp)
/* 2EB3C 8003E33C 4000B4AF */  sw         $s4, 0x40($sp)
/* 2EB40 8003E340 3C00B3AF */  sw         $s3, 0x3C($sp)
/* 2EB44 8003E344 3400B1AF */  sw         $s1, 0x34($sp)
/* 2EB48 8003E348 0000428E */  lw         $v0, 0x0($s2)
/* 2EB4C 8003E34C 21200002 */  addu       $a0, $s0, $zero
/* 2EB50 8003E350 01004224 */  addiu      $v0, $v0, 0x1
/* 2EB54 8003E354 BC5D000C */  jal        VecNull
/* 2EB58 8003E358 000042AE */   sw        $v0, 0x0($s2)
/* 2EB5C 8003E35C 0880033C */  lui        $v1, %hi(g_Spyro + 0x1F4)
/* 2EB60 8003E360 4C8C638C */  lw         $v1, %lo(g_Spyro + 0x1F4)($v1)
/* 2EB64 8003E364 00100224 */  addiu      $v0, $zero, 0x1000
/* 2EB68 8003E368 0880013C */  lui        $at, %hi(g_Spyro + 0xAC)
/* 2EB6C 8003E36C 048B22AC */  sw         $v0, %lo(g_Spyro + 0xAC)($at)
/* 2EB70 8003E370 0880013C */  lui        $at, %hi(g_Spyro + 0xB0)
/* 2EB74 8003E374 088B20AC */  sw         $zero, %lo(g_Spyro + 0xB0)($at)
/* 2EB78 8003E378 00406330 */  andi       $v1, $v1, 0x4000
/* 2EB7C 8003E37C 9F006014 */  bnez       $v1, .L8003E5FC
/* 2EB80 8003E380 280040AE */   sw        $zero, 0x28($s2)
/* 2EB84 8003E384 98FF5426 */  addiu      $s4, $s2, -0x68
/* 2EB88 8003E388 21208002 */  addu       $a0, $s4, $zero
/* 2EB8C 8003E38C 1000A527 */  addiu      $a1, $sp, 0x10
/* 2EB90 8003E390 2130A000 */  addu       $a2, $a1, $zero
/* 2EB94 8003E394 FCFE1524 */  addiu      $s5, $zero, -0x104
/* 2EB98 8003E398 3CFE1624 */  addiu      $s6, $zero, -0x1C4
/* 2EB9C 8003E39C 1000A0AF */  sw         $zero, 0x10($sp)
/* 2EBA0 8003E3A0 2000A0AF */  sw         $zero, 0x20($sp)
/* 2EBA4 8003E3A4 1400A0AF */  sw         $zero, 0x14($sp)
/* 2EBA8 8003E3A8 2400A0AF */  sw         $zero, 0x24($sp)
/* 2EBAC 8003E3AC 1800B5AF */  sw         $s5, 0x18($sp)
/* 2EBB0 8003E3B0 125C000C */  jal        VecRotateByMatrix
/* 2EBB4 8003E3B4 2800B6AF */   sw        $s6, 0x28($sp)
/* 2EBB8 8003E3B8 1000A427 */  addiu      $a0, $sp, 0x10
/* 2EBBC 8003E3BC 21288000 */  addu       $a1, $a0, $zero
/* 2EBC0 8003E3C0 64FF5326 */  addiu      $s3, $s2, -0x9C
/* 2EBC4 8003E3C4 D65D000C */  jal        VecAdd
/* 2EBC8 8003E3C8 21306002 */   addu      $a2, $s3, $zero
/* 2EBCC 8003E3CC 2000B127 */  addiu      $s1, $sp, 0x20
/* 2EBD0 8003E3D0 21202002 */  addu       $a0, $s1, $zero
/* 2EBD4 8003E3D4 305C000C */  jal        func_800170C0
/* 2EBD8 8003E3D8 21282002 */   addu      $a1, $s1, $zero
/* 2EBDC 8003E3DC 21202002 */  addu       $a0, $s1, $zero
/* 2EBE0 8003E3E0 21282002 */  addu       $a1, $s1, $zero
/* 2EBE4 8003E3E4 D65D000C */  jal        VecAdd
/* 2EBE8 8003E3E8 21306002 */   addu      $a2, $s3, $zero
/* 2EBEC 8003E3EC 1000A427 */  addiu      $a0, $sp, 0x10
/* 2EBF0 8003E3F0 8E2B010C */  jal        func_8004AE38
/* 2EBF4 8003E3F4 21282002 */   addu      $a1, $s1, $zero
/* 2EBF8 8003E3F8 41004010 */  beqz       $v0, .L8003E500
/* 2EBFC 8003E3FC 21200002 */   addu      $a0, $s0, $zero
/* 2EC00 8003E400 0780103C */  lui        $s0, %hi(D_80077368)
/* 2EC04 8003E404 68731026 */  addiu      $s0, $s0, %lo(D_80077368)
/* 2EC08 8003E408 C05D000C */  jal        VecCopy
/* 2EC0C 8003E40C 21280002 */   addu      $a1, $s0, $zero
/* 2EC10 8003E410 21200002 */  addu       $a0, $s0, $zero
/* 2EC14 8003E414 7F5C000C */  jal        VecMagnitude
/* 2EC18 8003E418 21280000 */   addu      $a1, $zero, $zero
/* 2EC1C 8003E41C 21284000 */  addu       $a1, $v0, $zero
/* 2EC20 8003E420 0780043C */  lui        $a0, %hi(D_80077368 + 0x8)
/* 2EC24 8003E424 7073848C */  lw         $a0, %lo(D_80077368 + 0x8)($a0)
/* 2EC28 8003E428 AD5A000C */  jal        Atan2
/* 2EC2C 8003E42C 21300000 */   addu      $a2, $zero, $zero
/* 2EC30 8003E430 00160200 */  sll        $v0, $v0, 24
/* 2EC34 8003E434 03160200 */  sra        $v0, $v0, 24
/* 2EC38 8003E438 0880013C */  lui        $at, %hi(g_Spyro + 0xB0)
/* 2EC3C 8003E43C 088B22AC */  sw         $v0, %lo(g_Spyro + 0xB0)($at)
/* 2EC40 8003E440 03004104 */  bgez       $v0, .L8003E450
/* 2EC44 8003E444 00040224 */   addiu     $v0, $zero, 0x400
/* 2EC48 8003E448 0880013C */  lui        $at, %hi(g_Spyro + 0xB0)
/* 2EC4C 8003E44C 088B22AC */  sw         $v0, %lo(g_Spyro + 0xB0)($at)
.L8003E450:
/* 2EC50 8003E450 0780043C */  lui        $a0, %hi(D_80075808)
/* 2EC54 8003E454 0858848C */  lw         $a0, %lo(D_80075808)($a0)
/* 2EC58 8003E458 DC014526 */  addiu      $a1, $s2, 0x1DC
/* 2EC5C 8003E45C 2E5F000C */  jal        ColTriUnpack
/* 2EC60 8003E460 D80144AE */   sw        $a0, 0x1D8($s2)
/* 2EC64 8003E464 0880033C */  lui        $v1, %hi(g_Spyro + 0xB0)
/* 2EC68 8003E468 088B638C */  lw         $v1, %lo(g_Spyro + 0xB0)($v1)
/* 2EC6C 8003E46C 00000000 */  nop
/* 2EC70 8003E470 21006228 */  slti       $v0, $v1, 0x21
/* 2EC74 8003E474 24004010 */  beqz       $v0, .L8003E508
/* 2EC78 8003E478 21208002 */   addu      $a0, $s4, $zero
/* 2EC7C 8003E47C 1000A527 */  addiu      $a1, $sp, 0x10
/* 2EC80 8003E480 2130A000 */  addu       $a2, $a1, $zero
/* 2EC84 8003E484 17006228 */  slti       $v0, $v1, 0x17
/* 2EC88 8003E488 01004238 */  xori       $v0, $v0, 0x1
/* 2EC8C 8003E48C B40042AE */  sw         $v0, 0xB4($s2)
/* 2EC90 8003E490 04010224 */  addiu      $v0, $zero, 0x104
/* 2EC94 8003E494 000040AE */  sw         $zero, 0x0($s2)
/* 2EC98 8003E498 1000A2AF */  sw         $v0, 0x10($sp)
/* 2EC9C 8003E49C C4010224 */  addiu      $v0, $zero, 0x1C4
/* 2ECA0 8003E4A0 1400A0AF */  sw         $zero, 0x14($sp)
/* 2ECA4 8003E4A4 1800B5AF */  sw         $s5, 0x18($sp)
/* 2ECA8 8003E4A8 2000A2AF */  sw         $v0, 0x20($sp)
/* 2ECAC 8003E4AC 2400A0AF */  sw         $zero, 0x24($sp)
/* 2ECB0 8003E4B0 125C000C */  jal        VecRotateByMatrix
/* 2ECB4 8003E4B4 2800B6AF */   sw        $s6, 0x28($sp)
/* 2ECB8 8003E4B8 1000A427 */  addiu      $a0, $sp, 0x10
/* 2ECBC 8003E4BC 21288000 */  addu       $a1, $a0, $zero
/* 2ECC0 8003E4C0 D65D000C */  jal        VecAdd
/* 2ECC4 8003E4C4 21306002 */   addu      $a2, $s3, $zero
/* 2ECC8 8003E4C8 21202002 */  addu       $a0, $s1, $zero
/* 2ECCC 8003E4CC 305C000C */  jal        func_800170C0
/* 2ECD0 8003E4D0 21282002 */   addu      $a1, $s1, $zero
/* 2ECD4 8003E4D4 21202002 */  addu       $a0, $s1, $zero
/* 2ECD8 8003E4D8 21282002 */  addu       $a1, $s1, $zero
/* 2ECDC 8003E4DC D65D000C */  jal        VecAdd
/* 2ECE0 8003E4E0 21306002 */   addu      $a2, $s3, $zero
/* 2ECE4 8003E4E4 1000A427 */  addiu      $a0, $sp, 0x10
/* 2ECE8 8003E4E8 8E2B010C */  jal        func_8004AE38
/* 2ECEC 8003E4EC 21282002 */   addu      $a1, $s1, $zero
/* 2ECF0 8003E4F0 05004014 */  bnez       $v0, .L8003E508
/* 2ECF4 8003E4F4 01000224 */   addiu     $v0, $zero, 0x1
/* 2ECF8 8003E4F8 42F90008 */  j          .L8003E508
/* 2ECFC 8003E4FC 280042AE */   sw        $v0, 0x28($s2)
.L8003E500:
/* 2ED00 8003E500 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 2ED04 8003E504 D80142AE */  sw         $v0, 0x1D8($s2)
.L8003E508:
/* 2ED08 8003E508 0880123C */  lui        $s2, %hi(g_Spyro + 0x9C)
/* 2ED0C 8003E50C F48A5226 */  addiu      $s2, $s2, %lo(g_Spyro + 0x9C)
/* 2ED10 8003E510 0000428E */  lw         $v0, 0x0($s2)
/* 2ED14 8003E514 00000000 */  nop
/* 2ED18 8003E518 38004010 */  beqz       $v0, .L8003E5FC
/* 2ED1C 8003E51C 00000000 */   nop
/* 2ED20 8003E520 0880023C */  lui        $v0, %hi(g_Spyro + 0x98)
/* 2ED24 8003E524 F08A428C */  lw         $v0, %lo(g_Spyro + 0x98)($v0)
/* 2ED28 8003E528 00000000 */  nop
/* 2ED2C 8003E52C 33004014 */  bnez       $v0, .L8003E5FC
/* 2ED30 8003E530 1000A427 */   addiu     $a0, $sp, 0x10
/* 2ED34 8003E534 21288000 */  addu       $a1, $a0, $zero
/* 2ED38 8003E538 64FF5126 */  addiu      $s1, $s2, -0x9C
/* 2ED3C 8003E53C 21302002 */  addu       $a2, $s1, $zero
/* 2ED40 8003E540 FCFE0224 */  addiu      $v0, $zero, -0x104
/* 2ED44 8003E544 1800A2AF */  sw         $v0, 0x18($sp)
/* 2ED48 8003E548 3CFE0224 */  addiu      $v0, $zero, -0x1C4
/* 2ED4C 8003E54C 1000A0AF */  sw         $zero, 0x10($sp)
/* 2ED50 8003E550 1400A0AF */  sw         $zero, 0x14($sp)
/* 2ED54 8003E554 2000A0AF */  sw         $zero, 0x20($sp)
/* 2ED58 8003E558 2400A0AF */  sw         $zero, 0x24($sp)
/* 2ED5C 8003E55C D65D000C */  jal        VecAdd
/* 2ED60 8003E560 2800A2AF */   sw        $v0, 0x28($sp)
/* 2ED64 8003E564 2000B027 */  addiu      $s0, $sp, 0x20
/* 2ED68 8003E568 21200002 */  addu       $a0, $s0, $zero
/* 2ED6C 8003E56C 21280002 */  addu       $a1, $s0, $zero
/* 2ED70 8003E570 D65D000C */  jal        VecAdd
/* 2ED74 8003E574 21302002 */   addu      $a2, $s1, $zero
/* 2ED78 8003E578 1000A427 */  addiu      $a0, $sp, 0x10
/* 2ED7C 8003E57C 8E2B010C */  jal        func_8004AE38
/* 2ED80 8003E580 21280002 */   addu      $a1, $s0, $zero
/* 2ED84 8003E584 1D004010 */  beqz       $v0, .L8003E5FC
/* 2ED88 8003E588 08005026 */   addiu     $s0, $s2, 0x8
/* 2ED8C 8003E58C 0780053C */  lui        $a1, %hi(D_80077368)
/* 2ED90 8003E590 6873A524 */  addiu      $a1, $a1, %lo(D_80077368)
/* 2ED94 8003E594 C05D000C */  jal        VecCopy
/* 2ED98 8003E598 21200002 */   addu      $a0, $s0, $zero
/* 2ED9C 8003E59C 21200002 */  addu       $a0, $s0, $zero
/* 2EDA0 8003E5A0 7F5C000C */  jal        VecMagnitude
/* 2EDA4 8003E5A4 21280000 */   addu      $a1, $zero, $zero
/* 2EDA8 8003E5A8 21284000 */  addu       $a1, $v0, $zero
/* 2EDAC 8003E5AC 0880043C */  lui        $a0, %hi(g_Spyro + 0xAC)
/* 2EDB0 8003E5B0 048B848C */  lw         $a0, %lo(g_Spyro + 0xAC)($a0)
/* 2EDB4 8003E5B4 AD5A000C */  jal        Atan2
/* 2EDB8 8003E5B8 21300000 */   addu      $a2, $zero, $zero
/* 2EDBC 8003E5BC 00160200 */  sll        $v0, $v0, 24
/* 2EDC0 8003E5C0 03160200 */  sra        $v0, $v0, 24
/* 2EDC4 8003E5C4 0880013C */  lui        $at, %hi(g_Spyro + 0xB0)
/* 2EDC8 8003E5C8 088B22AC */  sw         $v0, %lo(g_Spyro + 0xB0)($at)
/* 2EDCC 8003E5CC 03004104 */  bgez       $v0, .L8003E5DC
/* 2EDD0 8003E5D0 00040224 */   addiu     $v0, $zero, 0x400
/* 2EDD4 8003E5D4 0880013C */  lui        $at, %hi(g_Spyro + 0xB0)
/* 2EDD8 8003E5D8 088B22AC */  sw         $v0, %lo(g_Spyro + 0xB0)($at)
.L8003E5DC:
/* 2EDDC 8003E5DC 1400438E */  lw         $v1, 0x14($s2)
/* 2EDE0 8003E5E0 00000000 */  nop
/* 2EDE4 8003E5E4 21006228 */  slti       $v0, $v1, 0x21
/* 2EDE8 8003E5E8 04004010 */  beqz       $v0, .L8003E5FC
/* 2EDEC 8003E5EC 17006228 */   slti      $v0, $v1, 0x17
/* 2EDF0 8003E5F0 01004238 */  xori       $v0, $v0, 0x1
/* 2EDF4 8003E5F4 000040AE */  sw         $zero, 0x0($s2)
/* 2EDF8 8003E5F8 B40042AE */  sw         $v0, 0xB4($s2)
.L8003E5FC:
/* 2EDFC 8003E5FC 4C00BF8F */  lw         $ra, 0x4C($sp)
/* 2EE00 8003E600 4800B68F */  lw         $s6, 0x48($sp)
/* 2EE04 8003E604 4400B58F */  lw         $s5, 0x44($sp)
/* 2EE08 8003E608 4000B48F */  lw         $s4, 0x40($sp)
/* 2EE0C 8003E60C 3C00B38F */  lw         $s3, 0x3C($sp)
/* 2EE10 8003E610 3800B28F */  lw         $s2, 0x38($sp)
/* 2EE14 8003E614 3400B18F */  lw         $s1, 0x34($sp)
/* 2EE18 8003E618 3000B08F */  lw         $s0, 0x30($sp)
/* 2EE1C 8003E61C 5000BD27 */  addiu      $sp, $sp, 0x50
/* 2EE20 8003E620 0800E003 */  jr         $ra
/* 2EE24 8003E624 00000000 */   nop
.size func_8003E318, . - func_8003E318
