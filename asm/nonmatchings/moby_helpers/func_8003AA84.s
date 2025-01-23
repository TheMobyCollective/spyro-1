.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003AA84
/* 2B284 8003AA84 1800828C */  lw         $v0, 0x18($a0)
/* 2B288 8003AA88 0100033C */  lui        $v1, (0x10000 >> 16)
/* 2B28C 8003AA8C 24104300 */  and        $v0, $v0, $v1
/* 2B290 8003AA90 0B004010 */  beqz       $v0, .L8003AAC0
/* 2B294 8003AA94 00000000 */   nop
/* 2B298 8003AA98 4E008290 */  lbu        $v0, 0x4E($a0)
/* 2B29C 8003AA9C 00000000 */  nop
/* 2B2A0 8003AAA0 18004224 */  addiu      $v0, $v0, 0x18
/* 2B2A4 8003AAA4 4E0082A0 */  sb         $v0, 0x4E($a0)
/* 2B2A8 8003AAA8 FF004230 */  andi       $v0, $v0, 0xFF
/* 2B2AC 8003AAAC 6100422C */  sltiu      $v0, $v0, 0x61
/* 2B2B0 8003AAB0 0C004014 */  bnez       $v0, .L8003AAE4
/* 2B2B4 8003AAB4 60000224 */   addiu     $v0, $zero, 0x60
/* 2B2B8 8003AAB8 B9EA0008 */  j          .L8003AAE4
/* 2B2BC 8003AABC 4E0082A0 */   sb        $v0, 0x4E($a0)
.L8003AAC0:
/* 2B2C0 8003AAC0 4E008390 */  lbu        $v1, 0x4E($a0)
/* 2B2C4 8003AAC4 00000000 */  nop
/* 2B2C8 8003AAC8 FF006530 */  andi       $a1, $v1, 0xFF
/* 2B2CC 8003AACC 2100A22C */  sltiu      $v0, $a1, 0x21
/* 2B2D0 8003AAD0 03004010 */  beqz       $v0, .L8003AAE0
/* 2B2D4 8003AAD4 FEFF6224 */   addiu     $v0, $v1, -0x2
/* 2B2D8 8003AAD8 0200A010 */  beqz       $a1, .L8003AAE4
/* 2B2DC 8003AADC FFFF6224 */   addiu     $v0, $v1, -0x1
.L8003AAE0:
/* 2B2E0 8003AAE0 4E0082A0 */  sb         $v0, 0x4E($a0)
.L8003AAE4:
/* 2B2E4 8003AAE4 0800E003 */  jr         $ra
/* 2B2E8 8003AAE8 00000000 */   nop
.size func_8003AA84, . - func_8003AA84
