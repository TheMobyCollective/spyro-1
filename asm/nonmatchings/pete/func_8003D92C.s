.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003D92C
/* 2E12C 8003D92C 0880073C */  lui        $a3, %hi(g_Spyro + 0xC8)
/* 2E130 8003D930 208BE724 */  addiu      $a3, $a3, %lo(g_Spyro + 0xC8)
/* 2E134 8003D934 0000E68C */  lw         $a2, 0x0($a3)
/* 2E138 8003D938 5000E38C */  lw         $v1, 0x50($a3)
/* 2E13C 8003D93C 00000000 */  nop
/* 2E140 8003D940 2A106600 */  slt        $v0, $v1, $a2
/* 2E144 8003D944 04004010 */  beqz       $v0, .L8003D958
/* 2E148 8003D948 21106400 */   addu      $v0, $v1, $a0
/* 2E14C 8003D94C 5000E2AC */  sw         $v0, 0x50($a3)
/* 2E150 8003D950 59F60008 */  j          .L8003D964
/* 2E154 8003D954 2A10C200 */   slt       $v0, $a2, $v0
.L8003D958:
/* 2E158 8003D958 23106500 */  subu       $v0, $v1, $a1
/* 2E15C 8003D95C 5000E2AC */  sw         $v0, 0x50($a3)
/* 2E160 8003D960 2A104600 */  slt        $v0, $v0, $a2
.L8003D964:
/* 2E164 8003D964 02004010 */  beqz       $v0, .L8003D970
/* 2E168 8003D968 00000000 */   nop
/* 2E16C 8003D96C 5000E6AC */  sw         $a2, 0x50($a3)
.L8003D970:
/* 2E170 8003D970 0800E003 */  jr         $ra
/* 2E174 8003D974 00000000 */   nop
.size func_8003D92C, . - func_8003D92C
