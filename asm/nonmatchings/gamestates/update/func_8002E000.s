.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002E000
/* 1E800 8002E000 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1E804 8002E004 1000BFAF */  sw         $ra, 0x10($sp)
/* 1E808 8002E008 8028010C */  jal        func_8004A200
/* 1E80C 8002E00C 00000000 */   nop
/* 1E810 8002E010 F5DE000C */  jal        func_80037BD4
/* 1E814 8002E014 00000000 */   nop
/* 1E818 8002E018 0780043C */  lui        $a0, %hi(g_Camera + 0x4E)
/* 1E81C 8002E01C 1E6E8424 */  addiu      $a0, $a0, %lo(g_Camera + 0x4E)
/* 1E820 8002E020 00008294 */  lhu        $v0, 0x0($a0)
/* 1E824 8002E024 00000000 */  nop
/* 1E828 8002E028 FF0F4330 */  andi       $v1, $v0, 0xFFF
/* 1E82C 8002E02C 01086228 */  slti       $v0, $v1, 0x801
/* 1E830 8002E030 03004014 */  bnez       $v0, .L8002E040
/* 1E834 8002E034 000083A4 */   sh        $v1, 0x0($a0)
/* 1E838 8002E038 00F06224 */  addiu      $v0, $v1, -0x1000
/* 1E83C 8002E03C 000082A4 */  sh         $v0, 0x0($a0)
.L8002E040:
/* 1E840 8002E040 00008284 */  lh         $v0, 0x0($a0)
/* 1E844 8002E044 00000000 */  nop
/* 1E848 8002E048 00FE4228 */  slti       $v0, $v0, -0x200
/* 1E84C 8002E04C 07004014 */  bnez       $v0, .L8002E06C
/* 1E850 8002E050 00000000 */   nop
/* 1E854 8002E054 0780033C */  lui        $v1, %hi(g_Camera + 0xD8)
/* 1E858 8002E058 A86E638C */  lw         $v1, %lo(g_Camera + 0xD8)($v1)
/* 1E85C 8002E05C 0780023C */  lui        $v0, %hi(D_8006CA84)
/* 1E860 8002E060 84CA4224 */  addiu      $v0, $v0, %lo(D_8006CA84)
/* 1E864 8002E064 03006214 */  bne        $v1, $v0, .L8002E074
/* 1E868 8002E068 00000000 */   nop
.L8002E06C:
/* 1E86C 8002E06C 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1E870 8002E070 D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
.L8002E074:
/* 1E874 8002E074 1000BF8F */  lw         $ra, 0x10($sp)
/* 1E878 8002E078 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1E87C 8002E07C 0800E003 */  jr         $ra
/* 1E880 8002E080 00000000 */   nop
.size func_8002E000, . - func_8002E000
