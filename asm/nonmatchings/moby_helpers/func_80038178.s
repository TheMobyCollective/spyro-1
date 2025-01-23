.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038178
/* 28978 80038178 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 2897C 8003817C 1400B1AF */  sw         $s1, 0x14($sp)
/* 28980 80038180 2188A000 */  addu       $s1, $a1, $zero
/* 28984 80038184 1000B0AF */  sw         $s0, 0x10($sp)
/* 28988 80038188 1800BFAF */  sw         $ra, 0x18($sp)
/* 2898C 8003818C 26E0000C */  jal        func_80038098
/* 28990 80038190 2180E000 */   addu      $s0, $a3, $zero
/* 28994 80038194 21204000 */  addu       $a0, $v0, $zero
/* 28998 80038198 21282002 */  addu       $a1, $s1, $zero
/* 2899C 8003819C 48E0000C */  jal        func_80038120
/* 289A0 800381A0 FF000632 */   andi      $a2, $s0, 0xFF
/* 289A4 800381A4 1800BF8F */  lw         $ra, 0x18($sp)
/* 289A8 800381A8 1400B18F */  lw         $s1, 0x14($sp)
/* 289AC 800381AC 1000B08F */  lw         $s0, 0x10($sp)
/* 289B0 800381B0 2000BD27 */  addiu      $sp, $sp, 0x20
/* 289B4 800381B4 0800E003 */  jr         $ra
/* 289B8 800381B8 00000000 */   nop
.size func_80038178, . - func_80038178
