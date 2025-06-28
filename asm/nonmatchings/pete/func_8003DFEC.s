.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003DFEC
/* 2E7EC 8003DFEC E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 2E7F0 8003DFF0 1000B0AF */  sw         $s0, 0x10($sp)
/* 2E7F4 8003DFF4 21808000 */  addu       $s0, $a0, $zero
/* 2E7F8 8003DFF8 1400B1AF */  sw         $s1, 0x14($sp)
/* 2E7FC 8003DFFC 2188A000 */  addu       $s1, $a1, $zero
/* 2E800 8003E000 0880043C */  lui        $a0, %hi(g_Spyro + 0x10C)
/* 2E804 8003E004 648B848C */  lw         $a0, %lo(g_Spyro + 0x10C)($a0)
/* 2E808 8003E008 0880053C */  lui        $a1, %hi(g_Spyro + 0x110)
/* 2E80C 8003E00C 688BA58C */  lw         $a1, %lo(g_Spyro + 0x110)($a1)
/* 2E810 8003E010 1800BFAF */  sw         $ra, 0x18($sp)
/* 2E814 8003E014 AD5A000C */  jal        Atan2
/* 2E818 8003E018 21300000 */   addu      $a2, $zero, $zero
/* 2E81C 8003E01C 0880043C */  lui        $a0, %hi(g_Spyro + 0xE)
/* 2E820 8003E020 668A8490 */  lbu        $a0, %lo(g_Spyro + 0xE)($a0)
/* 2E824 8003E024 21304000 */  addu       $a2, $v0, $zero
/* 2E828 8003E028 23184400 */  subu       $v1, $v0, $a0
/* 2E82C 8003E02C FF006330 */  andi       $v1, $v1, 0xFF
/* 2E830 8003E030 2A102302 */  slt        $v0, $s1, $v1
/* 2E834 8003E034 19004010 */  beqz       $v0, .L8003E09C
/* 2E838 8003E038 00010524 */   addiu     $a1, $zero, 0x100
/* 2E83C 8003E03C 2310B100 */  subu       $v0, $a1, $s1
/* 2E840 8003E040 2A106200 */  slt        $v0, $v1, $v0
/* 2E844 8003E044 15004010 */  beqz       $v0, .L8003E09C
/* 2E848 8003E048 2A100302 */   slt       $v0, $s0, $v1
/* 2E84C 8003E04C 04004010 */  beqz       $v0, .L8003E060
/* 2E850 8003E050 2310B000 */   subu      $v0, $a1, $s0
/* 2E854 8003E054 2A106200 */  slt        $v0, $v1, $v0
/* 2E858 8003E058 05004014 */  bnez       $v0, .L8003E070
/* 2E85C 8003E05C 8000622C */   sltiu     $v0, $v1, 0x80
.L8003E060:
/* 2E860 8003E060 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 2E864 8003E064 668A26A0 */  sb         $a2, %lo(g_Spyro + 0xE)($at)
/* 2E868 8003E068 21F80008 */  j          .L8003E084
/* 2E86C 8003E06C 00000000 */   nop
.L8003E070:
/* 2E870 8003E070 02004014 */  bnez       $v0, .L8003E07C
/* 2E874 8003E074 21109000 */   addu      $v0, $a0, $s0
/* 2E878 8003E078 23109000 */  subu       $v0, $a0, $s0
.L8003E07C:
/* 2E87C 8003E07C 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 2E880 8003E080 668A22A0 */  sb         $v0, %lo(g_Spyro + 0xE)($at)
.L8003E084:
/* 2E884 8003E084 0880023C */  lui        $v0, %hi(g_Spyro + 0xE)
/* 2E888 8003E088 668A4290 */  lbu        $v0, %lo(g_Spyro + 0xE)($v0)
/* 2E88C 8003E08C 00000000 */  nop
/* 2E890 8003E090 00110200 */  sll        $v0, $v0, 4
/* 2E894 8003E094 0880013C */  lui        $at, %hi(g_Spyro + 0x11C)
/* 2E898 8003E098 748B22AC */  sw         $v0, %lo(g_Spyro + 0x11C)($at)
.L8003E09C:
/* 2E89C 8003E09C 1800BF8F */  lw         $ra, 0x18($sp)
/* 2E8A0 8003E0A0 1400B18F */  lw         $s1, 0x14($sp)
/* 2E8A4 8003E0A4 1000B08F */  lw         $s0, 0x10($sp)
/* 2E8A8 8003E0A8 2000BD27 */  addiu      $sp, $sp, 0x20
/* 2E8AC 8003E0AC 0800E003 */  jr         $ra
/* 2E8B0 8003E0B0 00000000 */   nop
.size func_8003DFEC, . - func_8003DFEC
