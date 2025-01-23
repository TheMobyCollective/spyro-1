.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038A40
/* 29240 80038A40 C8FFBD27 */  addiu      $sp, $sp, -0x38
/* 29244 80038A44 2800B4AF */  sw         $s4, 0x28($sp)
/* 29248 80038A48 21A08000 */  addu       $s4, $a0, $zero
/* 2924C 80038A4C 2000B2AF */  sw         $s2, 0x20($sp)
/* 29250 80038A50 2190A000 */  addu       $s2, $a1, $zero
/* 29254 80038A54 3000B6AF */  sw         $s6, 0x30($sp)
/* 29258 80038A58 21B0C000 */  addu       $s6, $a2, $zero
/* 2925C 80038A5C 2400B3AF */  sw         $s3, 0x24($sp)
/* 29260 80038A60 FF00133C */  lui        $s3, (0xFFFFFF >> 16)
/* 29264 80038A64 FFFF7336 */  ori        $s3, $s3, (0xFFFFFF & 0xFFFF)
/* 29268 80038A68 3400BFAF */  sw         $ra, 0x34($sp)
/* 2926C 80038A6C 2C00B5AF */  sw         $s5, 0x2C($sp)
/* 29270 80038A70 1C00B1AF */  sw         $s1, 0x1C($sp)
/* 29274 80038A74 1800B0AF */  sw         $s0, 0x18($sp)
/* 29278 80038A78 00004292 */  lbu        $v0, 0x0($s2)
/* 2927C 80038A7C 00000000 */  nop
/* 29280 80038A80 10004018 */  blez       $v0, .L80038AC4
/* 29284 80038A84 21800000 */   addu      $s0, $zero, $zero
/* 29288 80038A88 08001124 */  addiu      $s1, $zero, 0x8
.L80038A8C:
/* 2928C 80038A8C 0C008426 */  addiu      $a0, $s4, 0xC
/* 29290 80038A90 645E000C */  jal        func_80017990
/* 29294 80038A94 21285102 */   addu      $a1, $s2, $s1
/* 29298 80038A98 21184000 */  addu       $v1, $v0, $zero
/* 2929C 80038A9C 2A107300 */  slt        $v0, $v1, $s3
/* 292A0 80038AA0 03004010 */  beqz       $v0, .L80038AB0
/* 292A4 80038AA4 00000000 */   nop
/* 292A8 80038AA8 21986000 */  addu       $s3, $v1, $zero
/* 292AC 80038AAC 21A80002 */  addu       $s5, $s0, $zero
.L80038AB0:
/* 292B0 80038AB0 00004292 */  lbu        $v0, 0x0($s2)
/* 292B4 80038AB4 01001026 */  addiu      $s0, $s0, 0x1
/* 292B8 80038AB8 2A100202 */  slt        $v0, $s0, $v0
/* 292BC 80038ABC F3FF4014 */  bnez       $v0, .L80038A8C
/* 292C0 80038AC0 10003126 */   addiu     $s1, $s1, 0x10
.L80038AC4:
/* 292C4 80038AC4 0200C012 */  beqz       $s6, .L80038AD0
/* 292C8 80038AC8 21106002 */   addu      $v0, $s3, $zero
/* 292CC 80038ACC 0000D5AE */  sw         $s5, 0x0($s6)
.L80038AD0:
/* 292D0 80038AD0 3400BF8F */  lw         $ra, 0x34($sp)
/* 292D4 80038AD4 3000B68F */  lw         $s6, 0x30($sp)
/* 292D8 80038AD8 2C00B58F */  lw         $s5, 0x2C($sp)
/* 292DC 80038ADC 2800B48F */  lw         $s4, 0x28($sp)
/* 292E0 80038AE0 2400B38F */  lw         $s3, 0x24($sp)
/* 292E4 80038AE4 2000B28F */  lw         $s2, 0x20($sp)
/* 292E8 80038AE8 1C00B18F */  lw         $s1, 0x1C($sp)
/* 292EC 80038AEC 1800B08F */  lw         $s0, 0x18($sp)
/* 292F0 80038AF0 3800BD27 */  addiu      $sp, $sp, 0x38
/* 292F4 80038AF4 0800E003 */  jr         $ra
/* 292F8 80038AF8 00000000 */   nop
.size func_80038A40, . - func_80038A40
