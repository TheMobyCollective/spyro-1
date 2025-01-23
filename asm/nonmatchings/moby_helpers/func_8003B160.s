.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B160
/* 2B960 8003B160 0780023C */  lui        $v0, %hi(g_MobyPodCount)
/* 2B964 8003B164 B457428C */  lw         $v0, %lo(g_MobyPodCount)($v0)
/* 2B968 8003B168 00000000 */  nop
/* 2B96C 8003B16C 2A108200 */  slt        $v0, $a0, $v0
/* 2B970 8003B170 1A004010 */  beqz       $v0, .L8003B1DC
/* 2B974 8003B174 80100400 */   sll       $v0, $a0, 2
/* 2B978 8003B178 0780033C */  lui        $v1, %hi(g_MobyPods)
/* 2B97C 8003B17C F857638C */  lw         $v1, %lo(g_MobyPods)($v1)
/* 2B980 8003B180 0780073C */  lui        $a3, %hi(D_80075828)
/* 2B984 8003B184 2858E78C */  lw         $a3, %lo(D_80075828)($a3)
/* 2B988 8003B188 21104300 */  addu       $v0, $v0, $v1
/* 2B98C 8003B18C 0000448C */  lw         $a0, 0x0($v0)
.L8003B190:
/* 2B990 8003B190 00000000 */  nop
/* 2B994 8003B194 00008694 */  lhu        $a2, 0x0($a0)
/* 2B998 8003B198 00000000 */  nop
/* 2B99C 8003B19C FF7FC230 */  andi       $v0, $a2, 0x7FFF
/* 2B9A0 8003B1A0 40180200 */  sll        $v1, $v0, 1
/* 2B9A4 8003B1A4 21186200 */  addu       $v1, $v1, $v0
/* 2B9A8 8003B1A8 80180300 */  sll        $v1, $v1, 2
/* 2B9AC 8003B1AC 23186200 */  subu       $v1, $v1, $v0
/* 2B9B0 8003B1B0 C0180300 */  sll        $v1, $v1, 3
/* 2B9B4 8003B1B4 21186700 */  addu       $v1, $v1, $a3
/* 2B9B8 8003B1B8 48006290 */  lbu        $v0, 0x48($v1)
/* 2B9BC 8003B1BC 00000000 */  nop
/* 2B9C0 8003B1C0 07004514 */  bne        $v0, $a1, .L8003B1E0
/* 2B9C4 8003B1C4 21100000 */   addu      $v0, $zero, $zero
/* 2B9C8 8003B1C8 00140600 */  sll        $v0, $a2, 16
/* 2B9CC 8003B1CC F0FF4104 */  bgez       $v0, .L8003B190
/* 2B9D0 8003B1D0 02008424 */   addiu     $a0, $a0, 0x2
/* 2B9D4 8003B1D4 78EC0008 */  j          .L8003B1E0
/* 2B9D8 8003B1D8 01000224 */   addiu     $v0, $zero, 0x1
.L8003B1DC:
/* 2B9DC 8003B1DC 21100000 */  addu       $v0, $zero, $zero
.L8003B1E0:
/* 2B9E0 8003B1E0 0800E003 */  jr         $ra
/* 2B9E4 8003B1E4 00000000 */   nop
.size func_8003B160, . - func_8003B160
