.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B47C
/* 2BC7C 8003B47C 43008790 */  lbu        $a3, 0x43($a0)
/* 2BC80 8003B480 0780023C */  lui        $v0, %hi(g_MobyPodCount)
/* 2BC84 8003B484 B457428C */  lw         $v0, %lo(g_MobyPodCount)($v0)
/* 2BC88 8003B488 00000000 */  nop
/* 2BC8C 8003B48C 2A10E200 */  slt        $v0, $a3, $v0
/* 2BC90 8003B490 0A004014 */  bnez       $v0, .L8003B4BC
/* 2BC94 8003B494 80100700 */   sll       $v0, $a3, 2
/* 2BC98 8003B498 48008390 */  lbu        $v1, 0x48($a0)
/* 2BC9C 8003B49C 00000000 */  nop
/* 2BCA0 8003B4A0 8000622C */  sltiu      $v0, $v1, 0x80
/* 2BCA4 8003B4A4 22004010 */  beqz       $v0, .L8003B530
/* 2BCA8 8003B4A8 00000000 */   nop
/* 2BCAC 8003B4AC 20006610 */  beq        $v1, $a2, .L8003B530
/* 2BCB0 8003B4B0 00000000 */   nop
/* 2BCB4 8003B4B4 4CED0008 */  j          .L8003B530
/* 2BCB8 8003B4B8 480085A0 */   sb        $a1, 0x48($a0)
.L8003B4BC:
/* 2BCBC 8003B4BC 0780033C */  lui        $v1, %hi(g_MobyPods)
/* 2BCC0 8003B4C0 F857638C */  lw         $v1, %lo(g_MobyPods)($v1)
/* 2BCC4 8003B4C4 00000000 */  nop
/* 2BCC8 8003B4C8 21104300 */  addu       $v0, $v0, $v1
/* 2BCCC 8003B4CC 0000478C */  lw         $a3, 0x0($v0)
.L8003B4D0:
/* 2BCD0 8003B4D0 00000000 */  nop
/* 2BCD4 8003B4D4 0000E394 */  lhu        $v1, 0x0($a3)
/* 2BCD8 8003B4D8 00000000 */  nop
/* 2BCDC 8003B4DC FF7F6330 */  andi       $v1, $v1, 0x7FFF
/* 2BCE0 8003B4E0 40100300 */  sll        $v0, $v1, 1
/* 2BCE4 8003B4E4 21104300 */  addu       $v0, $v0, $v1
/* 2BCE8 8003B4E8 80100200 */  sll        $v0, $v0, 2
/* 2BCEC 8003B4EC 23104300 */  subu       $v0, $v0, $v1
/* 2BCF0 8003B4F0 0780033C */  lui        $v1, %hi(D_80075828)
/* 2BCF4 8003B4F4 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 2BCF8 8003B4F8 C0100200 */  sll        $v0, $v0, 3
/* 2BCFC 8003B4FC 21204300 */  addu       $a0, $v0, $v1
/* 2BD00 8003B500 48008390 */  lbu        $v1, 0x48($a0)
/* 2BD04 8003B504 00000000 */  nop
/* 2BD08 8003B508 8000622C */  sltiu      $v0, $v1, 0x80
/* 2BD0C 8003B50C 04004010 */  beqz       $v0, .L8003B520
/* 2BD10 8003B510 00000000 */   nop
/* 2BD14 8003B514 02006610 */  beq        $v1, $a2, .L8003B520
/* 2BD18 8003B518 00000000 */   nop
/* 2BD1C 8003B51C 480085A0 */  sb         $a1, 0x48($a0)
.L8003B520:
/* 2BD20 8003B520 0000E284 */  lh         $v0, 0x0($a3)
/* 2BD24 8003B524 00000000 */  nop
/* 2BD28 8003B528 E9FF4104 */  bgez       $v0, .L8003B4D0
/* 2BD2C 8003B52C 0200E724 */   addiu     $a3, $a3, 0x2
.L8003B530:
/* 2BD30 8003B530 0800E003 */  jr         $ra
/* 2BD34 8003B534 00000000 */   nop
.size func_8003B47C, . - func_8003B47C
