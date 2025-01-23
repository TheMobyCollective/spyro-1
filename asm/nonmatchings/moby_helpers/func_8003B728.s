.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B728
/* 2BF28 8003B728 43008690 */  lbu        $a2, 0x43($a0)
/* 2BF2C 8003B72C 0780023C */  lui        $v0, %hi(g_MobyPodCount)
/* 2BF30 8003B730 B457428C */  lw         $v0, %lo(g_MobyPodCount)($v0)
/* 2BF34 8003B734 00000000 */  nop
/* 2BF38 8003B738 2A10C200 */  slt        $v0, $a2, $v0
/* 2BF3C 8003B73C 03004014 */  bnez       $v0, .L8003B74C
/* 2BF40 8003B740 80100600 */   sll       $v0, $a2, 2
/* 2BF44 8003B744 EEED0008 */  j          .L8003B7B8
/* 2BF48 8003B748 490085A0 */   sb        $a1, 0x49($a0)
.L8003B74C:
/* 2BF4C 8003B74C 0780033C */  lui        $v1, %hi(g_MobyPods)
/* 2BF50 8003B750 F857638C */  lw         $v1, %lo(g_MobyPods)($v1)
/* 2BF54 8003B754 00000000 */  nop
/* 2BF58 8003B758 21104300 */  addu       $v0, $v0, $v1
/* 2BF5C 8003B75C 0000448C */  lw         $a0, 0x0($v0)
.L8003B760:
/* 2BF60 8003B760 00000000 */  nop
/* 2BF64 8003B764 00008394 */  lhu        $v1, 0x0($a0)
/* 2BF68 8003B768 00000000 */  nop
/* 2BF6C 8003B76C FF7F6330 */  andi       $v1, $v1, 0x7FFF
/* 2BF70 8003B770 40100300 */  sll        $v0, $v1, 1
/* 2BF74 8003B774 21104300 */  addu       $v0, $v0, $v1
/* 2BF78 8003B778 80100200 */  sll        $v0, $v0, 2
/* 2BF7C 8003B77C 23104300 */  subu       $v0, $v0, $v1
/* 2BF80 8003B780 0780033C */  lui        $v1, %hi(D_80075828)
/* 2BF84 8003B784 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 2BF88 8003B788 C0100200 */  sll        $v0, $v0, 3
/* 2BF8C 8003B78C 21184300 */  addu       $v1, $v0, $v1
/* 2BF90 8003B790 48006290 */  lbu        $v0, 0x48($v1)
/* 2BF94 8003B794 00000000 */  nop
/* 2BF98 8003B798 8000422C */  sltiu      $v0, $v0, 0x80
/* 2BF9C 8003B79C 02004010 */  beqz       $v0, .L8003B7A8
/* 2BFA0 8003B7A0 00000000 */   nop
/* 2BFA4 8003B7A4 490065A0 */  sb         $a1, 0x49($v1)
.L8003B7A8:
/* 2BFA8 8003B7A8 00008284 */  lh         $v0, 0x0($a0)
/* 2BFAC 8003B7AC 00000000 */  nop
/* 2BFB0 8003B7B0 EBFF4104 */  bgez       $v0, .L8003B760
/* 2BFB4 8003B7B4 02008424 */   addiu     $a0, $a0, 0x2
.L8003B7B8:
/* 2BFB8 8003B7B8 0800E003 */  jr         $ra
/* 2BFBC 8003B7BC 00000000 */   nop
.size func_8003B728, . - func_8003B728
