.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003E218
/* 2EA18 8003E218 C0FFBD27 */  addiu      $sp, $sp, -0x40
/* 2EA1C 8003E21C 3800B2AF */  sw         $s2, 0x38($sp)
/* 2EA20 8003E220 0880123C */  lui        $s2, %hi(g_Spyro + 0x34)
/* 2EA24 8003E224 8C8A5226 */  addiu      $s2, $s2, %lo(g_Spyro + 0x34)
/* 2EA28 8003E228 21204002 */  addu       $a0, $s2, $zero
/* 2EA2C 8003E22C 1000A527 */  addiu      $a1, $sp, 0x10
/* 2EA30 8003E230 2130A000 */  addu       $a2, $a1, $zero
/* 2EA34 8003E234 9CFE0224 */  addiu      $v0, $zero, -0x164
/* 2EA38 8003E238 1800A2AF */  sw         $v0, 0x18($sp)
/* 2EA3C 8003E23C C4010224 */  addiu      $v0, $zero, 0x1C4
/* 2EA40 8003E240 2000A2AF */  sw         $v0, 0x20($sp)
/* 2EA44 8003E244 5CFE0224 */  addiu      $v0, $zero, -0x1A4
/* 2EA48 8003E248 3C00BFAF */  sw         $ra, 0x3C($sp)
/* 2EA4C 8003E24C 3400B1AF */  sw         $s1, 0x34($sp)
/* 2EA50 8003E250 3000B0AF */  sw         $s0, 0x30($sp)
/* 2EA54 8003E254 1400A0AF */  sw         $zero, 0x14($sp)
/* 2EA58 8003E258 1000A0AF */  sw         $zero, 0x10($sp)
/* 2EA5C 8003E25C 2400A0AF */  sw         $zero, 0x24($sp)
/* 2EA60 8003E260 125C000C */  jal        VecRotateByMatrix
/* 2EA64 8003E264 2800A2AF */   sw        $v0, 0x28($sp)
/* 2EA68 8003E268 1000A427 */  addiu      $a0, $sp, 0x10
/* 2EA6C 8003E26C 21288000 */  addu       $a1, $a0, $zero
/* 2EA70 8003E270 CCFF5126 */  addiu      $s1, $s2, -0x34
/* 2EA74 8003E274 D65D000C */  jal        VecAdd
/* 2EA78 8003E278 21302002 */   addu      $a2, $s1, $zero
/* 2EA7C 8003E27C 2000B027 */  addiu      $s0, $sp, 0x20
/* 2EA80 8003E280 21200002 */  addu       $a0, $s0, $zero
/* 2EA84 8003E284 305C000C */  jal        func_800170C0
/* 2EA88 8003E288 21280002 */   addu      $a1, $s0, $zero
/* 2EA8C 8003E28C 21200002 */  addu       $a0, $s0, $zero
/* 2EA90 8003E290 21280002 */  addu       $a1, $s0, $zero
/* 2EA94 8003E294 D65D000C */  jal        VecAdd
/* 2EA98 8003E298 21302002 */   addu      $a2, $s1, $zero
/* 2EA9C 8003E29C 1000A427 */  addiu      $a0, $sp, 0x10
/* 2EAA0 8003E2A0 8E2B010C */  jal        func_8004AE38
/* 2EAA4 8003E2A4 21280002 */   addu      $a1, $s0, $zero
/* 2EAA8 8003E2A8 14004010 */  beqz       $v0, .L8003E2FC
/* 2EAAC 8003E2AC 00000000 */   nop
/* 2EAB0 8003E2B0 0780103C */  lui        $s0, %hi(D_80077368)
/* 2EAB4 8003E2B4 68731026 */  addiu      $s0, $s0, %lo(D_80077368)
/* 2EAB8 8003E2B8 21200002 */  addu       $a0, $s0, $zero
/* 2EABC 8003E2BC 7F5C000C */  jal        VecMagnitude
/* 2EAC0 8003E2C0 21280000 */   addu      $a1, $zero, $zero
/* 2EAC4 8003E2C4 0780043C */  lui        $a0, %hi(D_80077368 + 0x8)
/* 2EAC8 8003E2C8 7073848C */  lw         $a0, %lo(D_80077368 + 0x8)($a0)
/* 2EACC 8003E2CC 21284000 */  addu       $a1, $v0, $zero
/* 2EAD0 8003E2D0 AD5A000C */  jal        Atan2
/* 2EAD4 8003E2D4 21300000 */   addu      $a2, $zero, $zero
/* 2EAD8 8003E2D8 00160200 */  sll        $v0, $v0, 24
/* 2EADC 8003E2DC 03160200 */  sra        $v0, $v0, 24
/* 2EAE0 8003E2E0 17004228 */  slti       $v0, $v0, 0x17
/* 2EAE4 8003E2E4 05004014 */  bnez       $v0, .L8003E2FC
/* 2EAE8 8003E2E8 01000224 */   addiu     $v0, $zero, 0x1
/* 2EAEC 8003E2EC 800042AE */  sw         $v0, 0x80($s2)
/* 2EAF0 8003E2F0 84004426 */  addiu      $a0, $s2, 0x84
/* 2EAF4 8003E2F4 C05D000C */  jal        VecCopy
/* 2EAF8 8003E2F8 21280002 */   addu      $a1, $s0, $zero
.L8003E2FC:
/* 2EAFC 8003E2FC 3C00BF8F */  lw         $ra, 0x3C($sp)
/* 2EB00 8003E300 3800B28F */  lw         $s2, 0x38($sp)
/* 2EB04 8003E304 3400B18F */  lw         $s1, 0x34($sp)
/* 2EB08 8003E308 3000B08F */  lw         $s0, 0x30($sp)
/* 2EB0C 8003E30C 4000BD27 */  addiu      $sp, $sp, 0x40
/* 2EB10 8003E310 0800E003 */  jr         $ra
/* 2EB14 8003E314 00000000 */   nop
.size func_8003E218, . - func_8003E218
