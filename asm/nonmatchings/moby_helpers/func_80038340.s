.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038340
/* 28B40 80038340 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 28B44 80038344 1000B0AF */  sw         $s0, 0x10($sp)
/* 28B48 80038348 21808000 */  addu       $s0, $a0, $zero
/* 28B4C 8003834C 0C000426 */  addiu      $a0, $s0, 0xC
/* 28B50 80038350 1400BFAF */  sw         $ra, 0x14($sp)
/* 28B54 80038354 1400028E */  lw         $v0, 0x14($s0)
/* 28B58 80038358 00100524 */  addiu      $a1, $zero, 0x1000
/* 28B5C 8003835C DC054224 */  addiu      $v0, $v0, 0x5DC
/* 28B60 80038360 7B35010C */  jal        func_8004D5EC
/* 28B64 80038364 140002AE */   sw        $v0, 0x14($s0)
/* 28B68 80038368 1400038E */  lw         $v1, 0x14($s0)
/* 28B6C 8003836C 00000000 */  nop
/* 28B70 80038370 24FA6324 */  addiu      $v1, $v1, -0x5DC
/* 28B74 80038374 140003AE */  sw         $v1, 0x14($s0)
/* 28B78 80038378 1400BF8F */  lw         $ra, 0x14($sp)
/* 28B7C 8003837C 1000B08F */  lw         $s0, 0x10($sp)
/* 28B80 80038380 1800BD27 */  addiu      $sp, $sp, 0x18
/* 28B84 80038384 0800E003 */  jr         $ra
/* 28B88 80038388 00000000 */   nop
.size func_80038340, . - func_80038340
