.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003CAC4
/* 2D2C4 8003CAC4 21300000 */  addu       $a2, $zero, $zero
/* 2D2C8 8003CAC8 0880023C */  lui        $v0, %hi(D_80078630)
/* 2D2CC 8003CACC 30864224 */  addiu      $v0, $v0, %lo(D_80078630)
/* 2D2D0 8003CAD0 80180400 */  sll        $v1, $a0, 2
/* 2D2D4 8003CAD4 21186200 */  addu       $v1, $v1, $v0
/* 2D2D8 8003CAD8 0000628C */  lw         $v0, 0x0($v1)
/* 2D2DC 8003CADC 0880053C */  lui        $a1, %hi(D_80078608)
/* 2D2E0 8003CAE0 0886A524 */  addiu      $a1, $a1, %lo(D_80078608)
/* 2D2E4 8003CAE4 01004224 */  addiu      $v0, $v0, 0x1
/* 2D2E8 8003CAE8 000062AC */  sw         $v0, 0x0($v1)
.L8003CAEC:
/* 2D2EC 8003CAEC 0000A28C */  lw         $v0, 0x0($a1)
/* 2D2F0 8003CAF0 00000000 */  nop
/* 2D2F4 8003CAF4 03004104 */  bgez       $v0, .L8003CB04
/* 2D2F8 8003CAF8 00000000 */   nop
/* 2D2FC 8003CAFC C7F20008 */  j          .L8003CB1C
/* 2D300 8003CB00 0000A4AC */   sw        $a0, 0x0($a1)
.L8003CB04:
/* 2D304 8003CB04 05004410 */  beq        $v0, $a0, .L8003CB1C
/* 2D308 8003CB08 00000000 */   nop
/* 2D30C 8003CB0C 0100C624 */  addiu      $a2, $a2, 0x1
/* 2D310 8003CB10 0400C228 */  slti       $v0, $a2, 0x4
/* 2D314 8003CB14 F5FF4014 */  bnez       $v0, .L8003CAEC
/* 2D318 8003CB18 0400A524 */   addiu     $a1, $a1, 0x4
.L8003CB1C:
/* 2D31C 8003CB1C 0800E003 */  jr         $ra
/* 2D320 8003CB20 00000000 */   nop
.size func_8003CAC4, . - func_8003CAC4
