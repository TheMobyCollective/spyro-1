.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003D840
/* 2E040 8003D840 0780043C */  lui        $a0, %hi(D_800757E0)
/* 2E044 8003D844 E057848C */  lw         $a0, %lo(D_800757E0)($a0)
/* 2E048 8003D848 D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 2E04C 8003D84C 2000BFAF */  sw         $ra, 0x20($sp)
/* 2E050 8003D850 1000828C */  lw         $v0, 0x10($a0)
/* 2E054 8003D854 00000000 */  nop
/* 2E058 8003D858 2E004010 */  beqz       $v0, .L8003D914
/* 2E05C 8003D85C FFFF033C */   lui       $v1, (0xFFFF0000 >> 16)
/* 2E060 8003D860 1400828C */  lw         $v0, 0x14($a0)
/* 2E064 8003D864 00000000 */  nop
/* 2E068 8003D868 24104300 */  and        $v0, $v0, $v1
/* 2E06C 8003D86C 7F7F033C */  lui        $v1, (0x7F7F0000 >> 16)
/* 2E070 8003D870 28004310 */  beq        $v0, $v1, .L8003D914
/* 2E074 8003D874 21280000 */   addu      $a1, $zero, $zero
/* 2E078 8003D878 16008290 */  lbu        $v0, 0x16($a0)
/* 2E07C 8003D87C 00000000 */  nop
/* 2E080 8003D880 81FF4224 */  addiu      $v0, $v0, -0x7F
/* 2E084 8003D884 1000A2AF */  sw         $v0, 0x10($sp)
/* 2E088 8003D888 17008290 */  lbu        $v0, 0x17($a0)
/* 2E08C 8003D88C 1000A427 */  addiu      $a0, $sp, 0x10
/* 2E090 8003D890 1800A0AF */  sw         $zero, 0x18($sp)
/* 2E094 8003D894 81FF4224 */  addiu      $v0, $v0, -0x7F
/* 2E098 8003D898 7F5C000C */  jal        func_800171FC
/* 2E09C 8003D89C 1400A2AF */   sw        $v0, 0x14($sp)
/* 2E0A0 8003D8A0 21304000 */  addu       $a2, $v0, $zero
/* 2E0A4 8003D8A4 6000C228 */  slti       $v0, $a2, 0x60
/* 2E0A8 8003D8A8 1A004010 */  beqz       $v0, .L8003D914
/* 2E0AC 8003D8AC 00000000 */   nop
/* 2E0B0 8003D8B0 0880043C */  lui        $a0, %hi(g_Spyro + 0xCC)
/* 2E0B4 8003D8B4 248B8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0xCC)
/* 2E0B8 8003D8B8 0000828C */  lw         $v0, 0x0($a0)
/* 2E0BC 8003D8BC 5000858C */  lw         $a1, 0x50($a0)
/* 2E0C0 8003D8C0 00000000 */  nop
/* 2E0C4 8003D8C4 23104500 */  subu       $v0, $v0, $a1
/* 2E0C8 8003D8C8 FF0F4330 */  andi       $v1, $v0, 0xFFF
/* 2E0CC 8003D8CC 01086228 */  slti       $v0, $v1, 0x801
/* 2E0D0 8003D8D0 02004014 */  bnez       $v0, .L8003D8DC
/* 2E0D4 8003D8D4 00000000 */   nop
/* 2E0D8 8003D8D8 00F06324 */  addiu      $v1, $v1, -0x1000
.L8003D8DC:
/* 2E0DC 8003D8DC 02006104 */  bgez       $v1, .L8003D8E8
/* 2E0E0 8003D8E0 21106000 */   addu      $v0, $v1, $zero
/* 2E0E4 8003D8E4 23100200 */  negu       $v0, $v0
.L8003D8E8:
/* 2E0E8 8003D8E8 01014228 */  slti       $v0, $v0, 0x101
/* 2E0EC 8003D8EC 04004014 */  bnez       $v0, .L8003D900
/* 2E0F0 8003D8F0 1800C300 */   mult      $a2, $v1
/* 2E0F4 8003D8F4 01000224 */  addiu      $v0, $zero, 0x1
/* 2E0F8 8003D8F8 0880013C */  lui        $at, %hi(g_Spyro + 0x7C)
/* 2E0FC 8003D8FC D48A22AC */  sw         $v0, %lo(g_Spyro + 0x7C)($at)
.L8003D900:
/* 2E100 8003D900 12380000 */  mflo       $a3
/* 2E104 8003D904 43120700 */  sra        $v0, $a3, 9
/* 2E108 8003D908 2110A200 */  addu       $v0, $a1, $v0
/* 2E10C 8003D90C FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 2E110 8003D910 000082AC */  sw         $v0, 0x0($a0)
.L8003D914:
/* 2E114 8003D914 B4F5000C */  jal        func_8003D6D0
/* 2E118 8003D918 21200000 */   addu      $a0, $zero, $zero
/* 2E11C 8003D91C 2000BF8F */  lw         $ra, 0x20($sp)
/* 2E120 8003D920 2800BD27 */  addiu      $sp, $sp, 0x28
/* 2E124 8003D924 0800E003 */  jr         $ra
/* 2E128 8003D928 00000000 */   nop
.size func_8003D840, . - func_8003D840
