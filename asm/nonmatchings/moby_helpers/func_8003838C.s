.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003838C
/* 28B8C 8003838C E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 28B90 80038390 1000B0AF */  sw         $s0, 0x10($sp)
/* 28B94 80038394 21808000 */  addu       $s0, $a0, $zero
/* 28B98 80038398 0C000426 */  addiu      $a0, $s0, 0xC
/* 28B9C 8003839C 1400BFAF */  sw         $ra, 0x14($sp)
/* 28BA0 800383A0 1400028E */  lw         $v0, 0x14($s0)
/* 28BA4 800383A4 00100524 */  addiu      $a1, $zero, 0x1000
/* 28BA8 800383A8 DC054224 */  addiu      $v0, $v0, 0x5DC
/* 28BAC 800383AC 7B35010C */  jal        func_8004D5EC
/* 28BB0 800383B0 140002AE */   sw        $v0, 0x14($s0)
/* 28BB4 800383B4 0780043C */  lui        $a0, %hi(D_80077368)
/* 28BB8 800383B8 68738424 */  addiu      $a0, $a0, %lo(D_80077368)
/* 28BBC 800383BC 1400028E */  lw         $v0, 0x14($s0)
/* 28BC0 800383C0 21280000 */  addu       $a1, $zero, $zero
/* 28BC4 800383C4 24FA4224 */  addiu      $v0, $v0, -0x5DC
/* 28BC8 800383C8 7F5C000C */  jal        VecMagnitude
/* 28BCC 800383CC 140002AE */   sw        $v0, 0x14($s0)
/* 28BD0 800383D0 0780043C */  lui        $a0, %hi(D_80077370)
/* 28BD4 800383D4 7073848C */  lw         $a0, %lo(D_80077370)($a0)
/* 28BD8 800383D8 6B5A000C */  jal        func_800169AC
/* 28BDC 800383DC 21284000 */   addu      $a1, $v0, $zero
/* 28BE0 800383E0 00160200 */  sll        $v0, $v0, 24
/* 28BE4 800383E4 03160200 */  sra        $v0, $v0, 24
/* 28BE8 800383E8 18004228 */  slti       $v0, $v0, 0x18
/* 28BEC 800383EC 1400BF8F */  lw         $ra, 0x14($sp)
/* 28BF0 800383F0 1000B08F */  lw         $s0, 0x10($sp)
/* 28BF4 800383F4 1800BD27 */  addiu      $sp, $sp, 0x18
/* 28BF8 800383F8 0800E003 */  jr         $ra
/* 28BFC 800383FC 00000000 */   nop
.size func_8003838C, . - func_8003838C
