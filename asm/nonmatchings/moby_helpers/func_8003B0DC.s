.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B0DC
/* 2B8DC 8003B0DC 0780023C */  lui        $v0, %hi(g_MobyPodCount)
/* 2B8E0 8003B0E0 B457428C */  lw         $v0, %lo(g_MobyPodCount)($v0)
/* 2B8E4 8003B0E4 00000000 */  nop
/* 2B8E8 8003B0E8 2A108200 */  slt        $v0, $a0, $v0
/* 2B8EC 8003B0EC 19004010 */  beqz       $v0, .L8003B154
/* 2B8F0 8003B0F0 80100400 */   sll       $v0, $a0, 2
/* 2B8F4 8003B0F4 0780033C */  lui        $v1, %hi(g_MobyPods)
/* 2B8F8 8003B0F8 F857638C */  lw         $v1, %lo(g_MobyPods)($v1)
/* 2B8FC 8003B0FC 0780063C */  lui        $a2, %hi(D_80075828)
/* 2B900 8003B100 2858C68C */  lw         $a2, %lo(D_80075828)($a2)
/* 2B904 8003B104 21104300 */  addu       $v0, $v0, $v1
/* 2B908 8003B108 0000448C */  lw         $a0, 0x0($v0)
.L8003B10C:
/* 2B90C 8003B10C 00000000 */  nop
/* 2B910 8003B110 00008594 */  lhu        $a1, 0x0($a0)
/* 2B914 8003B114 00000000 */  nop
/* 2B918 8003B118 FF7FA230 */  andi       $v0, $a1, 0x7FFF
/* 2B91C 8003B11C 40180200 */  sll        $v1, $v0, 1
/* 2B920 8003B120 21186200 */  addu       $v1, $v1, $v0
/* 2B924 8003B124 80180300 */  sll        $v1, $v1, 2
/* 2B928 8003B128 23186200 */  subu       $v1, $v1, $v0
/* 2B92C 8003B12C C0180300 */  sll        $v1, $v1, 3
/* 2B930 8003B130 21186600 */  addu       $v1, $v1, $a2
/* 2B934 8003B134 48006290 */  lbu        $v0, 0x48($v1)
/* 2B938 8003B138 00000000 */  nop
/* 2B93C 8003B13C 8000422C */  sltiu      $v0, $v0, 0x80
/* 2B940 8003B140 05004014 */  bnez       $v0, .L8003B158
/* 2B944 8003B144 01000224 */   addiu     $v0, $zero, 0x1
/* 2B948 8003B148 00140500 */  sll        $v0, $a1, 16
/* 2B94C 8003B14C EFFF4104 */  bgez       $v0, .L8003B10C
/* 2B950 8003B150 02008424 */   addiu     $a0, $a0, 0x2
.L8003B154:
/* 2B954 8003B154 21100000 */  addu       $v0, $zero, $zero
.L8003B158:
/* 2B958 8003B158 0800E003 */  jr         $ra
/* 2B95C 8003B15C 00000000 */   nop
.size func_8003B0DC, . - func_8003B0DC
