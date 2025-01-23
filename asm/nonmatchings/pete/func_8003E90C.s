.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003E90C
/* 2F10C 8003E90C A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 2F110 8003E910 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 2F114 8003E914 21A80000 */  addu       $s5, $zero, $zero
/* 2F118 8003E918 3800B0AF */  sw         $s0, 0x38($sp)
/* 2F11C 8003E91C 20001024 */  addiu      $s0, $zero, 0x20
/* 2F120 8003E920 3C00B1AF */  sw         $s1, 0x3C($sp)
/* 2F124 8003E924 21880000 */  addu       $s1, $zero, $zero
/* 2F128 8003E928 5000B6AF */  sw         $s6, 0x50($sp)
/* 2F12C 8003E92C 0880163C */  lui        $s6, %hi(g_Spyro)
/* 2F130 8003E930 588AD626 */  addiu      $s6, $s6, %lo(g_Spyro)
/* 2F134 8003E934 4800B4AF */  sw         $s4, 0x48($sp)
/* 2F138 8003E938 2000B427 */  addiu      $s4, $sp, 0x20
/* 2F13C 8003E93C 4400B3AF */  sw         $s3, 0x44($sp)
/* 2F140 8003E940 0780133C */  lui        $s3, %hi(D_8006CCB8)
/* 2F144 8003E944 B8CC7326 */  addiu      $s3, $s3, %lo(D_8006CCB8)
/* 2F148 8003E948 5400BFAF */  sw         $ra, 0x54($sp)
/* 2F14C 8003E94C 4000B2AF */  sw         $s2, 0x40($sp)
.L8003E950:
/* 2F150 8003E950 1000A427 */  addiu      $a0, $sp, 0x10
/* 2F154 8003E954 21288000 */  addu       $a1, $a0, $zero
/* 2F158 8003E958 00006296 */  lhu        $v0, 0x0($s3)
/* 2F15C 8003E95C 2130C002 */  addu       $a2, $s6, $zero
/* 2F160 8003E960 00140200 */  sll        $v0, $v0, 16
/* 2F164 8003E964 03150200 */  sra        $v0, $v0, 20
/* 2F168 8003E968 2000A2AF */  sw         $v0, 0x20($sp)
/* 2F16C 8003E96C 1000A2AF */  sw         $v0, 0x10($sp)
/* 2F170 8003E970 40101000 */  sll        $v0, $s0, 1
/* 2F174 8003E974 0780013C */  lui        $at, %hi(D_8006CBF8)
/* 2F178 8003E978 21082200 */  addu       $at, $at, $v0
/* 2F17C 8003E97C F8CB2394 */  lhu        $v1, %lo(D_8006CBF8)($at)
/* 2F180 8003E980 DCFE0224 */  addiu      $v0, $zero, -0x124
/* 2F184 8003E984 1800A2AF */  sw         $v0, 0x18($sp)
/* 2F188 8003E988 5CFE0224 */  addiu      $v0, $zero, -0x1A4
/* 2F18C 8003E98C 2800A2AF */  sw         $v0, 0x28($sp)
/* 2F190 8003E990 001C0300 */  sll        $v1, $v1, 16
/* 2F194 8003E994 031D0300 */  sra        $v1, $v1, 20
/* 2F198 8003E998 2400A3AF */  sw         $v1, 0x24($sp)
/* 2F19C 8003E99C D65D000C */  jal        VecAdd
/* 2F1A0 8003E9A0 1400A3AF */   sw        $v1, 0x14($sp)
/* 2F1A4 8003E9A4 21208002 */  addu       $a0, $s4, $zero
/* 2F1A8 8003E9A8 21288002 */  addu       $a1, $s4, $zero
/* 2F1AC 8003E9AC D65D000C */  jal        VecAdd
/* 2F1B0 8003E9B0 2130C002 */   addu      $a2, $s6, $zero
/* 2F1B4 8003E9B4 1000A427 */  addiu      $a0, $sp, 0x10
/* 2F1B8 8003E9B8 0780123C */  lui        $s2, %hi(D_8006CBF8)
/* 2F1BC 8003E9BC F8CB5226 */  addiu      $s2, $s2, %lo(D_8006CBF8)
/* 2F1C0 8003E9C0 8E2B010C */  jal        func_8004AE38
/* 2F1C4 8003E9C4 21288002 */   addu      $a1, $s4, $zero
/* 2F1C8 8003E9C8 03004010 */  beqz       $v0, .L8003E9D8
/* 2F1CC 8003E9CC 01000224 */   addiu     $v0, $zero, 0x1
/* 2F1D0 8003E9D0 04102202 */  sllv       $v0, $v0, $s1
/* 2F1D4 8003E9D4 25A8A202 */  or         $s5, $s5, $v0
.L8003E9D8:
/* 2F1D8 8003E9D8 80007326 */  addiu      $s3, $s3, 0x80
/* 2F1DC 8003E9DC 01003126 */  addiu      $s1, $s1, 0x1
/* 2F1E0 8003E9E0 0400222A */  slti       $v0, $s1, 0x4
/* 2F1E4 8003E9E4 DAFF4014 */  bnez       $v0, .L8003E950
/* 2F1E8 8003E9E8 40001026 */   addiu     $s0, $s0, 0x40
/* 2F1EC 8003E9EC 80101500 */  sll        $v0, $s5, 2
/* 2F1F0 8003E9F0 0780013C */  lui        $at, %hi(D_8006C714)
/* 2F1F4 8003E9F4 21082200 */  addu       $at, $at, $v0
/* 2F1F8 8003E9F8 14C7308C */  lw         $s0, %lo(D_8006C714)($at)
/* 2F1FC 8003E9FC 00000000 */  nop
/* 2F200 8003EA00 0E000006 */  bltz       $s0, .L8003EA3C
/* 2F204 8003EA04 40201000 */   sll       $a0, $s0, 1
/* 2F208 8003EA08 0780013C */  lui        $at, %hi(D_8006CC78)
/* 2F20C 8003EA0C 21082400 */  addu       $at, $at, $a0
/* 2F210 8003EA10 78CC2284 */  lh         $v0, %lo(D_8006CC78)($at)
/* 2F214 8003EA14 21209200 */  addu       $a0, $a0, $s2
/* 2F218 8003EA18 F400C38E */  lw         $v1, 0xF4($s6)
/* 2F21C 8003EA1C 03110200 */  sra        $v0, $v0, 4
/* 2F220 8003EA20 21186200 */  addu       $v1, $v1, $v0
/* 2F224 8003EA24 F400C3AE */  sw         $v1, 0xF4($s6)
/* 2F228 8003EA28 00008284 */  lh         $v0, 0x0($a0)
/* 2F22C 8003EA2C F800C38E */  lw         $v1, 0xF8($s6)
/* 2F230 8003EA30 03110200 */  sra        $v0, $v0, 4
/* 2F234 8003EA34 21186200 */  addu       $v1, $v1, $v0
/* 2F238 8003EA38 F800C3AE */  sw         $v1, 0xF8($s6)
.L8003EA3C:
/* 2F23C 8003EA3C 5400BF8F */  lw         $ra, 0x54($sp)
/* 2F240 8003EA40 5000B68F */  lw         $s6, 0x50($sp)
/* 2F244 8003EA44 4C00B58F */  lw         $s5, 0x4C($sp)
/* 2F248 8003EA48 4800B48F */  lw         $s4, 0x48($sp)
/* 2F24C 8003EA4C 4400B38F */  lw         $s3, 0x44($sp)
/* 2F250 8003EA50 4000B28F */  lw         $s2, 0x40($sp)
/* 2F254 8003EA54 3C00B18F */  lw         $s1, 0x3C($sp)
/* 2F258 8003EA58 3800B08F */  lw         $s0, 0x38($sp)
/* 2F25C 8003EA5C 5800BD27 */  addiu      $sp, $sp, 0x58
/* 2F260 8003EA60 0800E003 */  jr         $ra
/* 2F264 8003EA64 00000000 */   nop
.size func_8003E90C, . - func_8003E90C
