.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B538
/* 2BD38 8003B538 43008790 */  lbu        $a3, 0x43($a0)
/* 2BD3C 8003B53C 0780023C */  lui        $v0, %hi(g_MobyPodCount)
/* 2BD40 8003B540 B457428C */  lw         $v0, %lo(g_MobyPodCount)($v0)
/* 2BD44 8003B544 00000000 */  nop
/* 2BD48 8003B548 2A10E200 */  slt        $v0, $a3, $v0
/* 2BD4C 8003B54C 0A004014 */  bnez       $v0, .L8003B578
/* 2BD50 8003B550 80100700 */   sll       $v0, $a3, 2
/* 2BD54 8003B554 48008390 */  lbu        $v1, 0x48($a0)
/* 2BD58 8003B558 00000000 */  nop
/* 2BD5C 8003B55C 8000622C */  sltiu      $v0, $v1, 0x80
/* 2BD60 8003B560 22004010 */  beqz       $v0, .L8003B5EC
/* 2BD64 8003B564 00000000 */   nop
/* 2BD68 8003B568 20006614 */  bne        $v1, $a2, .L8003B5EC
/* 2BD6C 8003B56C 00000000 */   nop
/* 2BD70 8003B570 7BED0008 */  j          .L8003B5EC
/* 2BD74 8003B574 480085A0 */   sb        $a1, 0x48($a0)
.L8003B578:
/* 2BD78 8003B578 0780033C */  lui        $v1, %hi(g_MobyPods)
/* 2BD7C 8003B57C F857638C */  lw         $v1, %lo(g_MobyPods)($v1)
/* 2BD80 8003B580 00000000 */  nop
/* 2BD84 8003B584 21104300 */  addu       $v0, $v0, $v1
/* 2BD88 8003B588 0000478C */  lw         $a3, 0x0($v0)
.L8003B58C:
/* 2BD8C 8003B58C 00000000 */  nop
/* 2BD90 8003B590 0000E394 */  lhu        $v1, 0x0($a3)
/* 2BD94 8003B594 00000000 */  nop
/* 2BD98 8003B598 FF7F6330 */  andi       $v1, $v1, 0x7FFF
/* 2BD9C 8003B59C 40100300 */  sll        $v0, $v1, 1
/* 2BDA0 8003B5A0 21104300 */  addu       $v0, $v0, $v1
/* 2BDA4 8003B5A4 80100200 */  sll        $v0, $v0, 2
/* 2BDA8 8003B5A8 23104300 */  subu       $v0, $v0, $v1
/* 2BDAC 8003B5AC 0780033C */  lui        $v1, %hi(D_80075828)
/* 2BDB0 8003B5B0 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 2BDB4 8003B5B4 C0100200 */  sll        $v0, $v0, 3
/* 2BDB8 8003B5B8 21204300 */  addu       $a0, $v0, $v1
/* 2BDBC 8003B5BC 48008390 */  lbu        $v1, 0x48($a0)
/* 2BDC0 8003B5C0 00000000 */  nop
/* 2BDC4 8003B5C4 8000622C */  sltiu      $v0, $v1, 0x80
/* 2BDC8 8003B5C8 04004010 */  beqz       $v0, .L8003B5DC
/* 2BDCC 8003B5CC 00000000 */   nop
/* 2BDD0 8003B5D0 02006614 */  bne        $v1, $a2, .L8003B5DC
/* 2BDD4 8003B5D4 00000000 */   nop
/* 2BDD8 8003B5D8 480085A0 */  sb         $a1, 0x48($a0)
.L8003B5DC:
/* 2BDDC 8003B5DC 0000E284 */  lh         $v0, 0x0($a3)
/* 2BDE0 8003B5E0 00000000 */  nop
/* 2BDE4 8003B5E4 E9FF4104 */  bgez       $v0, .L8003B58C
/* 2BDE8 8003B5E8 0200E724 */   addiu     $a3, $a3, 0x2
.L8003B5EC:
/* 2BDEC 8003B5EC 0800E003 */  jr         $ra
/* 2BDF0 8003B5F0 00000000 */   nop
.size func_8003B538, . - func_8003B538
