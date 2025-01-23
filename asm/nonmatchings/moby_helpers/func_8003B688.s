.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B688
/* 2BE88 8003B688 0780023C */  lui        $v0, %hi(g_MobyPodCount)
/* 2BE8C 8003B68C B457428C */  lw         $v0, %lo(g_MobyPodCount)($v0)
/* 2BE90 8003B690 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 2BE94 8003B694 1400BFAF */  sw         $ra, 0x14($sp)
/* 2BE98 8003B698 2A108200 */  slt        $v0, $a0, $v0
/* 2BE9C 8003B69C 1D004010 */  beqz       $v0, .L8003B714
/* 2BEA0 8003B6A0 1000B0AF */   sw        $s0, 0x10($sp)
/* 2BEA4 8003B6A4 0780033C */  lui        $v1, %hi(g_MobyPods)
/* 2BEA8 8003B6A8 F857638C */  lw         $v1, %lo(g_MobyPods)($v1)
/* 2BEAC 8003B6AC 80100400 */  sll        $v0, $a0, 2
/* 2BEB0 8003B6B0 21104300 */  addu       $v0, $v0, $v1
/* 2BEB4 8003B6B4 0000508C */  lw         $s0, 0x0($v0)
.L8003B6B8:
/* 2BEB8 8003B6B8 00000000 */  nop
/* 2BEBC 8003B6BC 00000396 */  lhu        $v1, 0x0($s0)
/* 2BEC0 8003B6C0 00000000 */  nop
/* 2BEC4 8003B6C4 FF7F6330 */  andi       $v1, $v1, 0x7FFF
/* 2BEC8 8003B6C8 40100300 */  sll        $v0, $v1, 1
/* 2BECC 8003B6CC 21104300 */  addu       $v0, $v0, $v1
/* 2BED0 8003B6D0 80100200 */  sll        $v0, $v0, 2
/* 2BED4 8003B6D4 23104300 */  subu       $v0, $v0, $v1
/* 2BED8 8003B6D8 0780033C */  lui        $v1, %hi(D_80075828)
/* 2BEDC 8003B6DC 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 2BEE0 8003B6E0 C0100200 */  sll        $v0, $v0, 3
/* 2BEE4 8003B6E4 21204300 */  addu       $a0, $v0, $v1
/* 2BEE8 8003B6E8 48008290 */  lbu        $v0, 0x48($a0)
/* 2BEEC 8003B6EC 00000000 */  nop
/* 2BEF0 8003B6F0 8000422C */  sltiu      $v0, $v0, 0x80
/* 2BEF4 8003B6F4 03004010 */  beqz       $v0, .L8003B704
/* 2BEF8 8003B6F8 00000000 */   nop
/* 2BEFC 8003B6FC 5A49010C */  jal        func_80052568
/* 2BF00 8003B700 00000000 */   nop
.L8003B704:
/* 2BF04 8003B704 00000286 */  lh         $v0, 0x0($s0)
/* 2BF08 8003B708 00000000 */  nop
/* 2BF0C 8003B70C EAFF4104 */  bgez       $v0, .L8003B6B8
/* 2BF10 8003B710 02001026 */   addiu     $s0, $s0, 0x2
.L8003B714:
/* 2BF14 8003B714 1400BF8F */  lw         $ra, 0x14($sp)
/* 2BF18 8003B718 1000B08F */  lw         $s0, 0x10($sp)
/* 2BF1C 8003B71C 1800BD27 */  addiu      $sp, $sp, 0x18
/* 2BF20 8003B720 0800E003 */  jr         $ra
/* 2BF24 8003B724 00000000 */   nop
.size func_8003B688, . - func_8003B688
