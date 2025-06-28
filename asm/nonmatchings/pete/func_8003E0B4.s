.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003E0B4
/* 2E8B4 8003E0B4 D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 2E8B8 8003E0B8 1000A427 */  addiu      $a0, $sp, 0x10
/* 2E8BC 8003E0BC 2000B0AF */  sw         $s0, 0x20($sp)
/* 2E8C0 8003E0C0 0880103C */  lui        $s0, %hi(g_Spyro + 0xA4)
/* 2E8C4 8003E0C4 FC8A1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0xA4)
/* 2E8C8 8003E0C8 2400BFAF */  sw         $ra, 0x24($sp)
/* 2E8CC 8003E0CC C05D000C */  jal        VecCopy
/* 2E8D0 8003E0D0 21280002 */   addu      $a1, $s0, $zero
/* 2E8D4 8003E0D4 1000A427 */  addiu      $a0, $sp, 0x10
/* 2E8D8 8003E0D8 7F5C000C */  jal        VecMagnitude
/* 2E8DC 8003E0DC 01000524 */   addiu     $a1, $zero, 0x1
/* 2E8E0 8003E0E0 21284000 */  addu       $a1, $v0, $zero
/* 2E8E4 8003E0E4 2C00A010 */  beqz       $a1, .L8003E198
/* 2E8E8 8003E0E8 00000000 */   nop
/* 2E8EC 8003E0EC 0880033C */  lui        $v1, %hi(g_Spyro + 0x14C)
/* 2E8F0 8003E0F0 A48B638C */  lw         $v1, %lo(g_Spyro + 0x14C)($v1)
/* 2E8F4 8003E0F4 1800A28F */  lw         $v0, 0x18($sp)
/* 2E8F8 8003E0F8 00000000 */  nop
/* 2E8FC 8003E0FC 18006200 */  mult       $v1, $v0
/* 2E900 8003E100 12100000 */  mflo       $v0
/* 2E904 8003E104 00000000 */  nop
/* 2E908 8003E108 00000000 */  nop
/* 2E90C 8003E10C 1A004500 */  div        $zero, $v0, $a1
/* 2E910 8003E110 0200A014 */  bnez       $a1, .L8003E11C
/* 2E914 8003E114 00000000 */   nop
/* 2E918 8003E118 0D000700 */  break      7
.L8003E11C:
/* 2E91C 8003E11C FFFF0124 */  addiu      $at, $zero, -0x1
/* 2E920 8003E120 0400A114 */  bne        $a1, $at, .L8003E134
/* 2E924 8003E124 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2E928 8003E128 02004114 */  bne        $v0, $at, .L8003E134
/* 2E92C 8003E12C 00000000 */   nop
/* 2E930 8003E130 0D000600 */  break      6
.L8003E134:
/* 2E934 8003E134 12300000 */  mflo       $a2
/* 2E938 8003E138 6E5D000C */  jal        VecScaleToLength
/* 2E93C 8003E13C 1000A427 */   addiu     $a0, $sp, 0x10
/* 2E940 8003E140 1800A28F */  lw         $v0, 0x18($sp)
/* 2E944 8003E144 00000000 */  nop
/* 2E948 8003E148 08004018 */  blez       $v0, .L8003E16C
/* 2E94C 8003E14C 23100200 */   negu      $v0, $v0
/* 2E950 8003E150 1800A2AF */  sw         $v0, 0x18($sp)
/* 2E954 8003E154 1000A28F */  lw         $v0, 0x10($sp)
/* 2E958 8003E158 1400A38F */  lw         $v1, 0x14($sp)
/* 2E95C 8003E15C 23100200 */  negu       $v0, $v0
/* 2E960 8003E160 23180300 */  negu       $v1, $v1
/* 2E964 8003E164 1000A2AF */  sw         $v0, 0x10($sp)
/* 2E968 8003E168 1400A3AF */  sw         $v1, 0x14($sp)
.L8003E16C:
/* 2E96C 8003E16C 2C001026 */  addiu      $s0, $s0, 0x2C
/* 2E970 8003E170 BC5D000C */  jal        VecNull
/* 2E974 8003E174 21200002 */   addu      $a0, $s0, $zero
/* 2E978 8003E178 21200002 */  addu       $a0, $s0, $zero
/* 2E97C 8003E17C 21288000 */  addu       $a1, $a0, $zero
/* 2E980 8003E180 0880023C */  lui        $v0, %hi(g_Spyro + 0x14C)
/* 2E984 8003E184 A48B428C */  lw         $v0, %lo(g_Spyro + 0x14C)($v0)
/* 2E988 8003E188 0880013C */  lui        $at, %hi(g_Spyro + 0xD8)
/* 2E98C 8003E18C 308B22AC */  sw         $v0, %lo(g_Spyro + 0xD8)($at)
/* 2E990 8003E190 E35D000C */  jal        VecSub
/* 2E994 8003E194 1000A627 */   addiu     $a2, $sp, 0x10
.L8003E198:
/* 2E998 8003E198 2400BF8F */  lw         $ra, 0x24($sp)
/* 2E99C 8003E19C 2000B08F */  lw         $s0, 0x20($sp)
/* 2E9A0 8003E1A0 2800BD27 */  addiu      $sp, $sp, 0x28
/* 2E9A4 8003E1A4 0800E003 */  jr         $ra
/* 2E9A8 8003E1A8 00000000 */   nop
.size func_8003E0B4, . - func_8003E0B4
