.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003D6D0
/* 2DED0 8003D6D0 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 2DED4 8003D6D4 0880023C */  lui        $v0, %hi(g_Spyro + 0xCC)
/* 2DED8 8003D6D8 248B428C */  lw         $v0, %lo(g_Spyro + 0xCC)($v0)
/* 2DEDC 8003D6DC 0880033C */  lui        $v1, %hi(g_Spyro + 0x11C)
/* 2DEE0 8003D6E0 748B638C */  lw         $v1, %lo(g_Spyro + 0x11C)($v1)
/* 2DEE4 8003D6E4 21308000 */  addu       $a2, $a0, $zero
/* 2DEE8 8003D6E8 23284300 */  subu       $a1, $v0, $v1
/* 2DEEC 8003D6EC FF0FA530 */  andi       $a1, $a1, 0xFFF
/* 2DEF0 8003D6F0 0008A228 */  slti       $v0, $a1, 0x800
/* 2DEF4 8003D6F4 13004010 */  beqz       $v0, .L8003D744
/* 2DEF8 8003D6F8 1000BFAF */   sw        $ra, 0x10($sp)
/* 2DEFC 8003D6FC 0880023C */  lui        $v0, %hi(g_Spyro + 0x148)
/* 2DF00 8003D700 A08B428C */  lw         $v0, %lo(g_Spyro + 0x148)($v0)
/* 2DF04 8003D704 00000000 */  nop
/* 2DF08 8003D708 01004224 */  addiu      $v0, $v0, 0x1
/* 2DF0C 8003D70C 0880013C */  lui        $at, %hi(g_Spyro + 0x148)
/* 2DF10 8003D710 A08B22AC */  sw         $v0, %lo(g_Spyro + 0x148)($at)
/* 2DF14 8003D714 0300401C */  bgtz       $v0, .L8003D724
/* 2DF18 8003D718 01000224 */   addiu     $v0, $zero, 0x1
/* 2DF1C 8003D71C 0880013C */  lui        $at, %hi(g_Spyro + 0x148)
/* 2DF20 8003D720 A08B22AC */  sw         $v0, %lo(g_Spyro + 0x148)($at)
.L8003D724:
/* 2DF24 8003D724 0880023C */  lui        $v0, %hi(g_Spyro + 0x148)
/* 2DF28 8003D728 A08B428C */  lw         $v0, %lo(g_Spyro + 0x148)($v0)
/* 2DF2C 8003D72C 00000000 */  nop
/* 2DF30 8003D730 07004228 */  slti       $v0, $v0, 0x7
/* 2DF34 8003D734 15004014 */  bnez       $v0, .L8003D78C
/* 2DF38 8003D738 06000224 */   addiu     $v0, $zero, 0x6
/* 2DF3C 8003D73C E1F50008 */  j          .L8003D784
/* 2DF40 8003D740 00000000 */   nop
.L8003D744:
/* 2DF44 8003D744 0880023C */  lui        $v0, %hi(g_Spyro + 0x148)
/* 2DF48 8003D748 A08B428C */  lw         $v0, %lo(g_Spyro + 0x148)($v0)
/* 2DF4C 8003D74C 00000000 */  nop
/* 2DF50 8003D750 FFFF4224 */  addiu      $v0, $v0, -0x1
/* 2DF54 8003D754 0880013C */  lui        $at, %hi(g_Spyro + 0x148)
/* 2DF58 8003D758 A08B22AC */  sw         $v0, %lo(g_Spyro + 0x148)($at)
/* 2DF5C 8003D75C FAFF4228 */  slti       $v0, $v0, -0x6
/* 2DF60 8003D760 03004010 */  beqz       $v0, .L8003D770
/* 2DF64 8003D764 FAFF0224 */   addiu     $v0, $zero, -0x6
/* 2DF68 8003D768 0880013C */  lui        $at, %hi(g_Spyro + 0x148)
/* 2DF6C 8003D76C A08B22AC */  sw         $v0, %lo(g_Spyro + 0x148)($at)
.L8003D770:
/* 2DF70 8003D770 0880023C */  lui        $v0, %hi(g_Spyro + 0x148)
/* 2DF74 8003D774 A08B428C */  lw         $v0, %lo(g_Spyro + 0x148)($v0)
/* 2DF78 8003D778 00000000 */  nop
/* 2DF7C 8003D77C 03004004 */  bltz       $v0, .L8003D78C
/* 2DF80 8003D780 FFFF0224 */   addiu     $v0, $zero, -0x1
.L8003D784:
/* 2DF84 8003D784 0880013C */  lui        $at, %hi(g_Spyro + 0x148)
/* 2DF88 8003D788 A08B22AC */  sw         $v0, %lo(g_Spyro + 0x148)($at)
.L8003D78C:
/* 2DF8C 8003D78C 0780043C */  lui        $a0, %hi(D_8006C5F0)
/* 2DF90 8003D790 F0C58424 */  addiu      $a0, $a0, %lo(D_8006C5F0)
/* 2DF94 8003D794 40100600 */  sll        $v0, $a2, 1
/* 2DF98 8003D798 21104600 */  addu       $v0, $v0, $a2
/* 2DF9C 8003D79C 80100200 */  sll        $v0, $v0, 2
/* 2DFA0 8003D7A0 21104600 */  addu       $v0, $v0, $a2
/* 2DFA4 8003D7A4 40100200 */  sll        $v0, $v0, 1
/* 2DFA8 8003D7A8 0880033C */  lui        $v1, %hi(g_Spyro + 0x148)
/* 2DFAC 8003D7AC A08B638C */  lw         $v1, %lo(g_Spyro + 0x148)($v1)
/* 2DFB0 8003D7B0 21104400 */  addu       $v0, $v0, $a0
/* 2DFB4 8003D7B4 40180300 */  sll        $v1, $v1, 1
/* 2DFB8 8003D7B8 21186200 */  addu       $v1, $v1, $v0
/* 2DFBC 8003D7BC 0C006484 */  lh         $a0, 0xC($v1)
/* 2DFC0 8003D7C0 00000000 */  nop
/* 2DFC4 8003D7C4 2A108500 */  slt        $v0, $a0, $a1
/* 2DFC8 8003D7C8 04004010 */  beqz       $v0, .L8003D7DC
/* 2DFCC 8003D7CC 00108224 */   addiu     $v0, $a0, 0x1000
/* 2DFD0 8003D7D0 2A10A200 */  slt        $v0, $a1, $v0
/* 2DFD4 8003D7D4 0E004014 */  bnez       $v0, .L8003D810
/* 2DFD8 8003D7D8 00000000 */   nop
.L8003D7DC:
/* 2DFDC 8003D7DC 0880023C */  lui        $v0, %hi(g_Spyro + 0xCC)
/* 2DFE0 8003D7E0 248B428C */  lw         $v0, %lo(g_Spyro + 0xCC)($v0)
/* 2DFE4 8003D7E4 0880033C */  lui        $v1, %hi(g_Spyro + 0x11C)
/* 2DFE8 8003D7E8 748B638C */  lw         $v1, %lo(g_Spyro + 0x11C)($v1)
/* 2DFEC 8003D7EC 00000000 */  nop
/* 2DFF0 8003D7F0 23104300 */  subu       $v0, $v0, $v1
/* 2DFF4 8003D7F4 FF0F4430 */  andi       $a0, $v0, 0xFFF
/* 2DFF8 8003D7F8 01088228 */  slti       $v0, $a0, 0x801
/* 2DFFC 8003D7FC 02004014 */  bnez       $v0, .L8003D808
/* 2E000 8003D800 00000000 */   nop
/* 2E004 8003D804 00F08424 */  addiu      $a0, $a0, -0x1000
.L8003D808:
/* 2E008 8003D808 0880013C */  lui        $at, %hi(g_Spyro + 0x148)
/* 2E00C 8003D80C A08B20AC */  sw         $zero, %lo(g_Spyro + 0x148)($at)
.L8003D810:
/* 2E010 8003D810 4BF5000C */  jal        func_8003D52C
/* 2E014 8003D814 00000000 */   nop
/* 2E018 8003D818 0880043C */  lui        $a0, %hi(g_Spyro + 0xCC)
/* 2E01C 8003D81C 248B848C */  lw         $a0, %lo(g_Spyro + 0xCC)($a0)
/* 2E020 8003D820 0880053C */  lui        $a1, %hi(g_Spyro + 0x11C)
/* 2E024 8003D824 748BA58C */  lw         $a1, %lo(g_Spyro + 0x11C)($a1)
/* 2E028 8003D828 4A5E000C */  jal        func_80017928
/* 2E02C 8003D82C 00000000 */   nop
/* 2E030 8003D830 1000BF8F */  lw         $ra, 0x10($sp)
/* 2E034 8003D834 1800BD27 */  addiu      $sp, $sp, 0x18
/* 2E038 8003D838 0800E003 */  jr         $ra
/* 2E03C 8003D83C 00000000 */   nop
.size func_8003D6D0, . - func_8003D6D0
