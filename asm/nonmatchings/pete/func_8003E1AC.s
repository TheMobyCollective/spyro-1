.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003E1AC
/* 2E9AC 8003E1AC D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 2E9B0 8003E1B0 2000B0AF */  sw         $s0, 0x20($sp)
/* 2E9B4 8003E1B4 0880103C */  lui        $s0, %hi(g_Spyro + 0xDC)
/* 2E9B8 8003E1B8 348B1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0xDC)
/* 2E9BC 8003E1BC 21200002 */  addu       $a0, $s0, $zero
/* 2E9C0 8003E1C0 2400BFAF */  sw         $ra, 0x24($sp)
/* 2E9C4 8003E1C4 C05D000C */  jal        VecCopy
/* 2E9C8 8003E1C8 C8FF0526 */   addiu     $a1, $s0, -0x38
/* 2E9CC 8003E1CC 0880053C */  lui        $a1, %hi(g_Spyro + 0x14C)
/* 2E9D0 8003E1D0 A48BA58C */  lw         $a1, %lo(g_Spyro + 0x14C)($a1)
/* 2E9D4 8003E1D4 00000000 */  nop
/* 2E9D8 8003E1D8 0200A104 */  bgez       $a1, .L8003E1E4
/* 2E9DC 8003E1DC 00000000 */   nop
/* 2E9E0 8003E1E0 23280500 */  negu       $a1, $a1
.L8003E1E4:
/* 2E9E4 8003E1E4 CC5C000C */  jal        func_80017330
/* 2E9E8 8003E1E8 21200002 */   addu      $a0, $s0, $zero
/* 2E9EC 8003E1EC BC5D000C */  jal        VecNull
/* 2E9F0 8003E1F0 1000A427 */   addiu     $a0, $sp, 0x10
/* 2E9F4 8003E1F4 21200002 */  addu       $a0, $s0, $zero
/* 2E9F8 8003E1F8 1000A527 */  addiu      $a1, $sp, 0x10
/* 2E9FC 8003E1FC E35D000C */  jal        VecSub
/* 2EA00 8003E200 21308000 */   addu      $a2, $a0, $zero
/* 2EA04 8003E204 2400BF8F */  lw         $ra, 0x24($sp)
/* 2EA08 8003E208 2000B08F */  lw         $s0, 0x20($sp)
/* 2EA0C 8003E20C 2800BD27 */  addiu      $sp, $sp, 0x28
/* 2EA10 8003E210 0800E003 */  jr         $ra
/* 2EA14 8003E214 00000000 */   nop
.size func_8003E1AC, . - func_8003E1AC
