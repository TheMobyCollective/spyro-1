.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002D02C
/* 1D82C 8002D02C E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 1D830 8002D030 1800BFAF */  sw         $ra, 0x18($sp)
/* 1D834 8002D034 1400B1AF */  sw         $s1, 0x14($sp)
/* 1D838 8002D038 1000B0AF */  sw         $s0, 0x10($sp)
/* 1D83C 8002D03C 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1D840 8002D040 D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 1D844 8002D044 0780013C */  lui        $at, %hi(D_8007570C)
/* 1D848 8002D048 0C5720AC */  sw         $zero, %lo(D_8007570C)($at)
/* 1D84C 8002D04C 1F63010C */  jal        SpecularReset
/* 1D850 8002D050 00000000 */   nop
/* 1D854 8002D054 0880103C */  lui        $s0, %hi(g_Spyro + 0x1A4)
/* 1D858 8002D058 FC8B1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x1A4)
/* 1D85C 8002D05C BC5D000C */  jal        VecNull
/* 1D860 8002D060 21200002 */   addu      $a0, $s0, $zero
/* 1D864 8002D064 092B010C */  jal        func_8004AC24
/* 1D868 8002D068 01000424 */   addiu     $a0, $zero, 0x1
/* 1D86C 8002D06C 0780113C */  lui        $s1, %hi(g_Camera + 0xD0)
/* 1D870 8002D070 A06E3126 */  addiu      $s1, $s1, %lo(g_Camera + 0xD0)
/* 1D874 8002D074 00010224 */  addiu      $v0, $zero, 0x100
/* 1D878 8002D078 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 1D87C 8002D07C 0C8C22AC */  sw         $v0, %lo(g_Spyro + 0x1B4)($at)
/* 1D880 8002D080 10000224 */  addiu      $v0, $zero, 0x10
/* 1D884 8002D084 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 1D888 8002D088 698A22A0 */  sb         $v0, %lo(g_Spyro + 0x11)($at)
/* 1D88C 8002D08C 08000224 */  addiu      $v0, $zero, 0x8
/* 1D890 8002D090 0880013C */  lui        $at, %hi(g_Spyro + 0x1F0)
/* 1D894 8002D094 488C22AC */  sw         $v0, %lo(g_Spyro + 0x1F0)($at)
/* 1D898 8002D098 0780023C */  lui        $v0, %hi(D_800758A4)
/* 1D89C 8002D09C A458428C */  lw         $v0, %lo(D_800758A4)($v0)
/* 1D8A0 8002D0A0 5CFE1026 */  addiu      $s0, $s0, -0x1A4
/* 1D8A4 8002D0A4 000030AE */  sw         $s0, 0x0($s1)
/* 1D8A8 8002D0A8 0880033C */  lui        $v1, %hi(g_Spyro + 0x11C)
/* 1D8AC 8002D0AC 748B638C */  lw         $v1, %lo(g_Spyro + 0x11C)($v1)
/* 1D8B0 8002D0B0 0780103C */  lui        $s0, %hi(D_8006C8BC)
/* 1D8B4 8002D0B4 BCC81026 */  addiu      $s0, $s0, %lo(D_8006C8BC)
/* 1D8B8 8002D0B8 0780013C */  lui        $at, %hi(g_Camera + 0x58)
/* 1D8BC 8002D0BC 286E20AC */  sw         $zero, %lo(g_Camera + 0x58)($at)
/* 1D8C0 8002D0C0 0780013C */  lui        $at, %hi(g_Camera + 0xC0)
/* 1D8C4 8002D0C4 906E20AC */  sw         $zero, %lo(g_Camera + 0xC0)($at)
/* 1D8C8 8002D0C8 0780013C */  lui        $at, %hi(g_Camera + 0xD8)
/* 1D8CC 8002D0CC A86E30AC */  sw         $s0, %lo(g_Camera + 0xD8)($at)
/* 1D8D0 8002D0D0 0880013C */  lui        $at, %hi(D_80078768)
/* 1D8D4 8002D0D4 688722AC */  sw         $v0, %lo(D_80078768)($at)
/* 1D8D8 8002D0D8 0780013C */  lui        $at, %hi(g_Camera + 0xD4)
/* 1D8DC 8002D0DC A46E23AC */  sw         $v1, %lo(g_Camera + 0xD4)($at)
/* 1D8E0 8002D0E0 C2CF000C */  jal        func_80033F08
/* 1D8E4 8002D0E4 58FF2426 */   addiu     $a0, $s1, -0xA8
/* 1D8E8 8002D0E8 21200002 */  addu       $a0, $s0, $zero
/* 1D8EC 8002D0EC C0FF2526 */  addiu      $a1, $s1, -0x40
/* 1D8F0 8002D0F0 565A000C */  jal        Memcpy
/* 1D8F4 8002D0F4 18000624 */   addiu     $a2, $zero, 0x18
/* 1D8F8 8002D0F8 0000028E */  lw         $v0, 0x0($s0)
/* 1D8FC 8002D0FC 0780033C */  lui        $v1, %hi(g_Camera + 0xD4)
/* 1D900 8002D100 A46E638C */  lw         $v1, %lo(g_Camera + 0xD4)($v1)
/* 1D904 8002D104 00000000 */  nop
/* 1D908 8002D108 21104300 */  addu       $v0, $v0, $v1
/* 1D90C 8002D10C FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 1D910 8002D110 D6D0000C */  jal        func_80034358
/* 1D914 8002D114 000002AE */   sw        $v0, 0x0($s0)
/* 1D918 8002D118 8051010C */  jal        func_80054600
/* 1D91C 8002D11C 21200000 */   addu      $a0, $zero, $zero
/* 1D920 8002D120 0780043C */  lui        $a0, %hi(D_800774B0)
/* 1D924 8002D124 B074848C */  lw         $a0, %lo(D_800774B0)($a0)
/* 1D928 8002D128 0780013C */  lui        $at, %hi(D_80077FA8)
/* 1D92C 8002D12C A87F20A0 */  sb         $zero, %lo(D_80077FA8)($at)
/* 1D930 8002D130 0780013C */  lui        $at, %hi(D_80077FA9)
/* 1D934 8002D134 A97F20A0 */  sb         $zero, %lo(D_80077FA9)($at)
/* 1D938 8002D138 0780013C */  lui        $at, %hi(D_80077FAA)
/* 1D93C 8002D13C AA7F20A0 */  sb         $zero, %lo(D_80077FAA)($at)
/* 1D940 8002D140 0780013C */  lui        $at, %hi(D_80077FAB)
/* 1D944 8002D144 AB7F20A0 */  sb         $zero, %lo(D_80077FAB)($at)
/* 1D948 8002D148 0780013C */  lui        $at, %hi(D_80077FAC)
/* 1D94C 8002D14C AC7F20A0 */  sb         $zero, %lo(D_80077FAC)($at)
/* 1D950 8002D150 FD59010C */  jal        func_800567F4
/* 1D954 8002D154 08000524 */   addiu     $a1, $zero, 0x8
/* 1D958 8002D158 1800BF8F */  lw         $ra, 0x18($sp)
/* 1D95C 8002D15C 1400B18F */  lw         $s1, 0x14($sp)
/* 1D960 8002D160 1000B08F */  lw         $s0, 0x10($sp)
/* 1D964 8002D164 2000BD27 */  addiu      $sp, $sp, 0x20
/* 1D968 8002D168 0800E003 */  jr         $ra
/* 1D96C 8002D16C 00000000 */   nop
.size func_8002D02C, . - func_8002D02C
