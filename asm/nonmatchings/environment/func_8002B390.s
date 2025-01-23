.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */
glabel func_8002B390
/* 1BB90 8002B390 00008D20 */  addi       $t5, $a0, 0x0 /* handwritten instruction */
/* 1BB94 8002B394 0000AE20 */  addi       $t6, $a1, 0x0 /* handwritten instruction */
/* 1BB98 8002B398 0000CF20 */  addi       $t7, $a2, 0x0 /* handwritten instruction */
/* 1BB9C 8002B39C 0880183C */  lui        $t8, %hi(D_80078560)
/* 1BBA0 8002B3A0 60851827 */  addiu      $t8, $t8, %lo(D_80078560)
/* 1BBA4 8002B3A4 48001923 */  addi       $t9, $t8, 0x48 /* handwritten instruction */
.L8002B3A8:
/* 1BBA8 8002B3A8 10001913 */  beq        $t8, $t9, .L8002B3EC
/* 1BBAC 8002B3AC 00000C8F */   lw        $t4, 0x0($t8)
/* 1BBB0 8002B3B0 04000B8F */  lw         $t3, 0x4($t8)
/* 1BBB4 8002B3B4 08001823 */  addi       $t8, $t8, 0x8 /* handwritten instruction */
/* 1BBB8 8002B3B8 80600C00 */  sll        $t4, $t4, 2
/* 1BBBC 8002B3BC 20608B01 */  add        $t4, $t4, $t3 /* handwritten instruction */
.L8002B3C0:
/* 1BBC0 8002B3C0 F9FF6C11 */  beq        $t3, $t4, .L8002B3A8
/* 1BBC4 8002B3C4 00006A8D */   lw        $t2, 0x0($t3)
/* 1BBC8 8002B3C8 04006B21 */  addi       $t3, $t3, 0x4 /* handwritten instruction */
/* 1BBCC 8002B3CC 00004191 */  lbu        $at, 0x0($t2)
/* 1BBD0 8002B3D0 01004291 */  lbu        $v0, 0x1($t2)
/* 1BBD4 8002B3D4 FAFF2D14 */  bne        $at, $t5, .L8002B3C0
/* 1BBD8 8002B3D8 00000000 */   nop
/* 1BBDC 8002B3DC 24104E00 */  and        $v0, $v0, $t6
/* 1BBE0 8002B3E0 25104F00 */  or         $v0, $v0, $t7
/* 1BBE4 8002B3E4 F0AC0008 */  j          .L8002B3C0
/* 1BBE8 8002B3E8 010042A1 */   sb        $v0, 0x1($t2)
.L8002B3EC:
/* 1BBEC 8002B3EC 0800E003 */  jr         $ra
/* 1BBF0 8002B3F0 00000000 */   nop
.size func_8002B390, . - func_8002B390
