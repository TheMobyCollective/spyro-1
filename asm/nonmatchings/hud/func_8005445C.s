.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8005445C
/* 44C5C 8005445C F8FFBD27 */  addiu      $sp, $sp, -0x8
/* 44C60 80054460 0E00A018 */  blez       $a1, .L8005449C
/* 44C64 80054464 21380000 */   addu      $a3, $zero, $zero
/* 44C68 80054468 21108700 */  addu       $v0, $a0, $a3
.L8005446C:
/* 44C6C 8005446C C0100200 */  sll        $v0, $v0, 3
/* 44C70 80054470 0780013C */  lui        $at, %hi(D_8006E71E)
/* 44C74 80054474 21082200 */  addu       $at, $at, $v0
/* 44C78 80054478 1EE72394 */  lhu        $v1, %lo(D_8006E71E)($at)
/* 44C7C 8005447C 0100E724 */  addiu      $a3, $a3, 0x1
/* 44C80 80054480 21186600 */  addu       $v1, $v1, $a2
/* 44C84 80054484 0880013C */  lui        $at, %hi(D_8007840E)
/* 44C88 80054488 21082200 */  addu       $at, $at, $v0
/* 44C8C 8005448C 0E8423A4 */  sh         $v1, %lo(D_8007840E)($at)
/* 44C90 80054490 2A10E500 */  slt        $v0, $a3, $a1
/* 44C94 80054494 F5FF4014 */  bnez       $v0, .L8005446C
/* 44C98 80054498 21108700 */   addu      $v0, $a0, $a3
.L8005449C:
/* 44C9C 8005449C 0800BD27 */  addiu      $sp, $sp, 0x8
/* 44CA0 800544A0 0800E003 */  jr         $ra
/* 44CA4 800544A4 00000000 */   nop
.size func_8005445C, . - func_8005445C
