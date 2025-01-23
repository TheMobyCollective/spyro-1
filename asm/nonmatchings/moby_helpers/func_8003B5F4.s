.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B5F4
/* 2BDF4 8003B5F4 0780023C */  lui        $v0, %hi(g_MobyPodCount)
/* 2BDF8 8003B5F8 B457428C */  lw         $v0, %lo(g_MobyPodCount)($v0)
/* 2BDFC 8003B5FC 00000000 */  nop
/* 2BE00 8003B600 2A108200 */  slt        $v0, $a0, $v0
/* 2BE04 8003B604 1E004010 */  beqz       $v0, .L8003B680
/* 2BE08 8003B608 80100400 */   sll       $v0, $a0, 2
/* 2BE0C 8003B60C 0780033C */  lui        $v1, %hi(g_MobyPods)
/* 2BE10 8003B610 F857638C */  lw         $v1, %lo(g_MobyPods)($v1)
/* 2BE14 8003B614 0780063C */  lui        $a2, %hi(D_80075828)
/* 2BE18 8003B618 2858C68C */  lw         $a2, %lo(D_80075828)($a2)
/* 2BE1C 8003B61C 21104300 */  addu       $v0, $v0, $v1
/* 2BE20 8003B620 0000448C */  lw         $a0, 0x0($v0)
.L8003B624:
/* 2BE24 8003B624 00000000 */  nop
/* 2BE28 8003B628 00008294 */  lhu        $v0, 0x0($a0)
/* 2BE2C 8003B62C 00000000 */  nop
/* 2BE30 8003B630 FF7F4230 */  andi       $v0, $v0, 0x7FFF
/* 2BE34 8003B634 40180200 */  sll        $v1, $v0, 1
/* 2BE38 8003B638 21186200 */  addu       $v1, $v1, $v0
/* 2BE3C 8003B63C 80180300 */  sll        $v1, $v1, 2
/* 2BE40 8003B640 23186200 */  subu       $v1, $v1, $v0
/* 2BE44 8003B644 C0180300 */  sll        $v1, $v1, 3
/* 2BE48 8003B648 21186600 */  addu       $v1, $v1, $a2
/* 2BE4C 8003B64C 48006290 */  lbu        $v0, 0x48($v1)
/* 2BE50 8003B650 00000000 */  nop
/* 2BE54 8003B654 8000422C */  sltiu      $v0, $v0, 0x80
/* 2BE58 8003B658 05004010 */  beqz       $v0, .L8003B670
/* 2BE5C 8003B65C 00000000 */   nop
/* 2BE60 8003B660 1800628C */  lw         $v0, 0x18($v1)
/* 2BE64 8003B664 00000000 */  nop
/* 2BE68 8003B668 25104500 */  or         $v0, $v0, $a1
/* 2BE6C 8003B66C 180062AC */  sw         $v0, 0x18($v1)
.L8003B670:
/* 2BE70 8003B670 00008284 */  lh         $v0, 0x0($a0)
/* 2BE74 8003B674 00000000 */  nop
/* 2BE78 8003B678 EAFF4104 */  bgez       $v0, .L8003B624
/* 2BE7C 8003B67C 02008424 */   addiu     $a0, $a0, 0x2
.L8003B680:
/* 2BE80 8003B680 0800E003 */  jr         $ra
/* 2BE84 8003B684 00000000 */   nop
.size func_8003B5F4, . - func_8003B5F4
