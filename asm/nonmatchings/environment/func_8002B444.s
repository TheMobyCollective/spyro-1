.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */
glabel func_8002B444
/* 1BC44 8002B444 00008D20 */  addi       $t5, $a0, 0x0 /* handwritten instruction */
/* 1BC48 8002B448 0000AE20 */  addi       $t6, $a1, 0x0 /* handwritten instruction */
/* 1BC4C 8002B44C 0000CF20 */  addi       $t7, $a2, 0x0 /* handwritten instruction */
/* 1BC50 8002B450 0880183C */  lui        $t8, %hi(D_80078560)
/* 1BC54 8002B454 60851827 */  addiu      $t8, $t8, %lo(D_80078560)
/* 1BC58 8002B458 48001923 */  addi       $t9, $t8, 0x48 /* handwritten instruction */
.L8002B45C:
/* 1BC5C 8002B45C 11001913 */  beq        $t8, $t9, .L8002B4A4
/* 1BC60 8002B460 00000C8F */   lw        $t4, 0x0($t8)
/* 1BC64 8002B464 04000B8F */  lw         $t3, 0x4($t8)
/* 1BC68 8002B468 08001823 */  addi       $t8, $t8, 0x8 /* handwritten instruction */
/* 1BC6C 8002B46C 80600C00 */  sll        $t4, $t4, 2
/* 1BC70 8002B470 20608B01 */  add        $t4, $t4, $t3 /* handwritten instruction */
.L8002B474:
/* 1BC74 8002B474 F9FF6C11 */  beq        $t3, $t4, .L8002B45C
/* 1BC78 8002B478 00006A8D */   lw        $t2, 0x0($t3)
/* 1BC7C 8002B47C 04006B21 */  addi       $t3, $t3, 0x4 /* handwritten instruction */
/* 1BC80 8002B480 00004191 */  lbu        $at, 0x0($t2)
/* 1BC84 8002B484 00000000 */  nop
/* 1BC88 8002B488 FAFF2D14 */  bne        $at, $t5, .L8002B474
/* 1BC8C 8002B48C 00000000 */   nop
/* 1BC90 8002B490 F8FFE011 */  beqz       $t7, .L8002B474
/* 1BC94 8002B494 02004EA1 */   sb        $t6, 0x2($t2)
/* 1BC98 8002B498 01000120 */  addi       $at, $zero, 0x1 /* handwritten instruction */
/* 1BC9C 8002B49C 1DAD0008 */  j          .L8002B474
/* 1BCA0 8002B4A0 030041A1 */   sb        $at, 0x3($t2)
.L8002B4A4:
/* 1BCA4 8002B4A4 0800E003 */  jr         $ra
/* 1BCA8 8002B4A8 00000000 */   nop
.size func_8002B444, . - func_8002B444
