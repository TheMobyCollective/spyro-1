.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */
glabel func_8002B3F4
/* 1BBF4 8002B3F4 006E0400 */  sll        $t5, $a0, 24
/* 1BBF8 8002B3F8 0880183C */  lui        $t8, %hi(D_80078560)
/* 1BBFC 8002B3FC 60851827 */  addiu      $t8, $t8, %lo(D_80078560)
/* 1BC00 8002B400 48001923 */  addi       $t9, $t8, 0x48 /* handwritten instruction */
.L8002B404:
/* 1BC04 8002B404 0D001913 */  beq        $t8, $t9, .L8002B43C
/* 1BC08 8002B408 00000C8F */   lw        $t4, 0x0($t8)
/* 1BC0C 8002B40C 04000B8F */  lw         $t3, 0x4($t8)
/* 1BC10 8002B410 08001823 */  addi       $t8, $t8, 0x8 /* handwritten instruction */
/* 1BC14 8002B414 80600C00 */  sll        $t4, $t4, 2
/* 1BC18 8002B418 20608B01 */  add        $t4, $t4, $t3 /* handwritten instruction */
.L8002B41C:
/* 1BC1C 8002B41C F9FF6C11 */  beq        $t3, $t4, .L8002B404
/* 1BC20 8002B420 00006A8D */   lw        $t2, 0x0($t3)
/* 1BC24 8002B424 04006B21 */  addi       $t3, $t3, 0x4 /* handwritten instruction */
/* 1BC28 8002B428 0000418D */  lw         $at, 0x0($t2)
/* 1BC2C 8002B42C 00000000 */  nop
/* 1BC30 8002B430 001E0100 */  sll        $v1, $at, 24
/* 1BC34 8002B434 F9FF6D14 */  bne        $v1, $t5, .L8002B41C
/* 1BC38 8002B438 02120100 */   srl       $v0, $at, 8
.L8002B43C:
/* 1BC3C 8002B43C 0800E003 */  jr         $ra
/* 1BC40 8002B440 00000000 */   nop
.size func_8002B3F4, . - func_8002B3F4
