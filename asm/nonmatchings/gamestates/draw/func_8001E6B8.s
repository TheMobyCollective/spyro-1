.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

.section .rodata
.align 2
dlabel D_80010CF0
/* 14F0 80010CF0 */ .asciz "IN THE WORLD OF DRAGONS..."
.align 2
.size D_80010CF0, . - D_80010CF0

.align 2
dlabel D_80010D0C
/* 150C 80010D0C */ .asciz "THE ADVENTURE CONTINUES..."
.align 2
.size D_80010D0C, . - D_80010D0C

.align 2
dlabel D_80010D28
/* 1528 80010D28 */ .asciz "THE ADVENTURE BEGINS..."
.align 2
.size D_80010D28, . - D_80010D28

.align 2
dlabel D_80010D40
/* 1540 80010D40 */ .asciz "ENTERING DEMO MODE..."
.align 2
.size D_80010D40, . - D_80010D40


.section .text
/* Generated by spimdisasm 1.27.0 */

glabel func_8001E6B8
/* EEB8 8001E6B8 C0FFBD27 */  addiu      $sp, $sp, -0x40
/* EEBC 8001E6BC 0880033C */  lui        $v1, %hi(g_TitlescreenState + 0x4)
/* EEC0 8001E6C0 7C8D638C */  lw         $v1, %lo(g_TitlescreenState + 0x4)($v1)
/* EEC4 8001E6C4 02000224 */  addiu      $v0, $zero, 0x2
/* EEC8 8001E6C8 3C00BFAF */  sw         $ra, 0x3C($sp)
/* EECC 8001E6CC 7D006214 */  bne        $v1, $v0, .L8001E8C4
/* EED0 8001E6D0 3800B0AF */   sw        $s0, 0x38($sp)
/* EED4 8001E6D4 0880023C */  lui        $v0, %hi(g_TitlescreenState + 0x8)
/* EED8 8001E6D8 808D428C */  lw         $v0, %lo(g_TitlescreenState + 0x8)($v0)
/* EEDC 8001E6DC 00000000 */  nop
/* EEE0 8001E6E0 8C004228 */  slti       $v0, $v0, 0x8C
/* EEE4 8001E6E4 77004014 */  bnez       $v0, .L8001E8C4
/* EEE8 8001E6E8 78000224 */   addiu     $v0, $zero, 0x78
/* EEEC 8001E6EC 1C00A2AF */  sw         $v0, 0x1C($sp)
/* EEF0 8001E6F0 00140224 */  addiu      $v0, $zero, 0x1400
/* EEF4 8001E6F4 2000A2AF */  sw         $v0, 0x20($sp)
/* EEF8 8001E6F8 0E000224 */  addiu      $v0, $zero, 0xE
/* EEFC 8001E6FC 0780103C */  lui        $s0, %hi(D_80075710)
/* EF00 8001E700 1057108E */  lw         $s0, %lo(D_80075710)($s0)
/* EF04 8001E704 0880033C */  lui        $v1, %hi(g_TitlescreenState + 0x1C)
/* EF08 8001E708 948D638C */  lw         $v1, %lo(g_TitlescreenState + 0x1C)($v1)
/* EF0C 8001E70C 01000424 */  addiu      $a0, $zero, 0x1
/* EF10 8001E710 2800A2AF */  sw         $v0, 0x28($sp)
/* EF14 8001E714 00160224 */  addiu      $v0, $zero, 0x1600
/* EF18 8001E718 2C00A4AF */  sw         $a0, 0x2C($sp)
/* EF1C 8001E71C 0D006014 */  bnez       $v1, .L8001E754
/* EF20 8001E720 3000A2AF */   sw        $v0, 0x30($sp)
/* EF24 8001E724 0180043C */  lui        $a0, %hi(D_80010CF0)
/* EF28 8001E728 F00C8424 */  addiu      $a0, $a0, %lo(D_80010CF0)
/* EF2C 8001E72C 1800A527 */  addiu      $a1, $sp, 0x18
/* EF30 8001E730 2800A627 */  addiu      $a2, $sp, 0x28
/* EF34 8001E734 10000724 */  addiu      $a3, $zero, 0x10
/* EF38 8001E738 5C000224 */  addiu      $v0, $zero, 0x5C
/* EF3C 8001E73C 1800A2AF */  sw         $v0, 0x18($sp)
/* EF40 8001E740 0B000224 */  addiu      $v0, $zero, 0xB
/* EF44 8001E744 6B60000C */  jal        func_800181AC
/* EF48 8001E748 1000A2AF */   sw        $v0, 0x10($sp)
/* EF4C 8001E74C FB790008 */  j          .L8001E7EC
/* EF50 8001E750 B8000324 */   addiu     $v1, $zero, 0xB8
.L8001E754:
/* EF54 8001E754 1B006414 */  bne        $v1, $a0, .L8001E7C4
/* EF58 8001E758 1800A527 */   addiu     $a1, $sp, 0x18
/* EF5C 8001E75C 0880023C */  lui        $v0, %hi(D_80078E72 + 0x6)
/* EF60 8001E760 788E4290 */  lbu        $v0, %lo(D_80078E72 + 0x6)($v0)
/* EF64 8001E764 00000000 */  nop
/* EF68 8001E768 0B004010 */  beqz       $v0, .L8001E798
/* EF6C 8001E76C 2800A627 */   addiu     $a2, $sp, 0x28
/* EF70 8001E770 0180043C */  lui        $a0, %hi(D_80010D0C)
/* EF74 8001E774 0C0D8424 */  addiu      $a0, $a0, %lo(D_80010D0C)
/* EF78 8001E778 10000724 */  addiu      $a3, $zero, 0x10
/* EF7C 8001E77C 50000224 */  addiu      $v0, $zero, 0x50
/* EF80 8001E780 1800A2AF */  sw         $v0, 0x18($sp)
/* EF84 8001E784 0B000224 */  addiu      $v0, $zero, 0xB
/* EF88 8001E788 6B60000C */  jal        func_800181AC
/* EF8C 8001E78C 1000A2AF */   sw        $v0, 0x10($sp)
/* EF90 8001E790 FB790008 */  j          .L8001E7EC
/* EF94 8001E794 BC000324 */   addiu     $v1, $zero, 0xBC
.L8001E798:
/* EF98 8001E798 0180043C */  lui        $a0, %hi(D_80010D28)
/* EF9C 8001E79C 280D8424 */  addiu      $a0, $a0, %lo(D_80010D28)
/* EFA0 8001E7A0 1800A527 */  addiu      $a1, $sp, 0x18
/* EFA4 8001E7A4 10000724 */  addiu      $a3, $zero, 0x10
/* EFA8 8001E7A8 64000224 */  addiu      $v0, $zero, 0x64
/* EFAC 8001E7AC 1800A2AF */  sw         $v0, 0x18($sp)
/* EFB0 8001E7B0 0B000224 */  addiu      $v0, $zero, 0xB
/* EFB4 8001E7B4 6B60000C */  jal        func_800181AC
/* EFB8 8001E7B8 1000A2AF */   sw        $v0, 0x10($sp)
/* EFBC 8001E7BC FB790008 */  j          .L8001E7EC
/* EFC0 8001E7C0 B6000324 */   addiu     $v1, $zero, 0xB6
.L8001E7C4:
/* EFC4 8001E7C4 0180043C */  lui        $a0, %hi(D_80010D40)
/* EFC8 8001E7C8 400D8424 */  addiu      $a0, $a0, %lo(D_80010D40)
/* EFCC 8001E7CC 2800A627 */  addiu      $a2, $sp, 0x28
/* EFD0 8001E7D0 10000724 */  addiu      $a3, $zero, 0x10
/* EFD4 8001E7D4 68000224 */  addiu      $v0, $zero, 0x68
/* EFD8 8001E7D8 1800A2AF */  sw         $v0, 0x18($sp)
/* EFDC 8001E7DC 0B000224 */  addiu      $v0, $zero, 0xB
/* EFE0 8001E7E0 6B60000C */  jal        func_800181AC
/* EFE4 8001E7E4 1000A2AF */   sw        $v0, 0x10($sp)
/* EFE8 8001E7E8 B2000324 */  addiu      $v1, $zero, 0xB2
.L8001E7EC:
/* EFEC 8001E7EC 0880053C */  lui        $a1, %hi(g_TitlescreenState + 0x8)
/* EFF0 8001E7F0 808DA524 */  addiu      $a1, $a1, %lo(g_TitlescreenState + 0x8)
/* EFF4 8001E7F4 0000A48C */  lw         $a0, 0x0($a1)
/* EFF8 8001E7F8 00000000 */  nop
/* EFFC 8001E7FC 2A108300 */  slt        $v0, $a0, $v1
/* F000 8001E800 0C004010 */  beqz       $v0, .L8001E834
/* F004 8001E804 23106400 */   subu      $v0, $v1, $a0
/* F008 8001E808 43100200 */  sra        $v0, $v0, 1
/* F00C 8001E80C 40180200 */  sll        $v1, $v0, 1
/* F010 8001E810 21186200 */  addu       $v1, $v1, $v0
/* F014 8001E814 80180300 */  sll        $v1, $v1, 2
/* F018 8001E818 23186200 */  subu       $v1, $v1, $v0
/* F01C 8001E81C 0780023C */  lui        $v0, %hi(D_80075710)
/* F020 8001E820 1057428C */  lw         $v0, %lo(D_80075710)($v0)
/* F024 8001E824 C0180300 */  sll        $v1, $v1, 3
/* F028 8001E828 21104300 */  addu       $v0, $v0, $v1
/* F02C 8001E82C 0780013C */  lui        $at, %hi(D_80075710)
/* F030 8001E830 105722AC */  sw         $v0, %lo(D_80075710)($at)
.L8001E834:
/* F034 8001E834 0780023C */  lui        $v0, %hi(D_80075710)
/* F038 8001E838 1057428C */  lw         $v0, %lo(D_80075710)($v0)
/* F03C 8001E83C A8FF1026 */  addiu      $s0, $s0, -0x58
/* F040 8001E840 2A100202 */  slt        $v0, $s0, $v0
/* F044 8001E844 1F004014 */  bnez       $v0, .L8001E8C4
/* F048 8001E848 21380000 */   addu      $a3, $zero, $zero
/* F04C 8001E84C 2148A000 */  addu       $t1, $a1, $zero
/* F050 8001E850 0780083C */  lui        $t0, %hi(D_8006CC78)
/* F054 8001E854 78CC0825 */  addiu      $t0, $t0, %lo(D_8006CC78)
/* F058 8001E858 46000526 */  addiu      $a1, $s0, 0x46
/* F05C 8001E85C 21300000 */  addu       $a2, $zero, $zero
.L8001E860:
/* F060 8001E860 0000248D */  lw         $a0, 0x0($t1)
/* F064 8001E864 8C00E224 */  addiu      $v0, $a3, 0x8C
/* F068 8001E868 23188200 */  subu       $v1, $a0, $v0
/* F06C 8001E86C 38006228 */  slti       $v0, $v1, 0x38
/* F070 8001E870 03004010 */  beqz       $v0, .L8001E880
/* F074 8001E874 C0100300 */   sll       $v0, $v1, 3
/* F078 8001E878 287A0008 */  j          .L8001E8A0
/* F07C 8001E87C 40004224 */   addiu     $v0, $v0, 0x40
.L8001E880:
/* F080 8001E880 80100400 */  sll        $v0, $a0, 2
/* F084 8001E884 21104600 */  addu       $v0, $v0, $a2
/* F088 8001E888 FF004230 */  andi       $v0, $v0, 0xFF
/* F08C 8001E88C 40100200 */  sll        $v0, $v0, 1
/* F090 8001E890 21104800 */  addu       $v0, $v0, $t0
/* F094 8001E894 00004294 */  lhu        $v0, 0x0($v0)
/* F098 8001E898 00000000 */  nop
/* F09C 8001E89C C2110200 */  srl        $v0, $v0, 7
.L8001E8A0:
/* F0A0 8001E8A0 0000A2A0 */  sb         $v0, 0x0($a1)
/* F0A4 8001E8A4 0C00C624 */  addiu      $a2, $a2, 0xC
/* F0A8 8001E8A8 0100E724 */  addiu      $a3, $a3, 0x1
/* F0AC 8001E8AC 0780023C */  lui        $v0, %hi(D_80075710)
/* F0B0 8001E8B0 1057428C */  lw         $v0, %lo(D_80075710)($v0)
/* F0B4 8001E8B4 A8FF1026 */  addiu      $s0, $s0, -0x58
/* F0B8 8001E8B8 2A100202 */  slt        $v0, $s0, $v0
/* F0BC 8001E8BC E8FF4010 */  beqz       $v0, .L8001E860
/* F0C0 8001E8C0 A8FFA524 */   addiu     $a1, $a1, -0x58
.L8001E8C4:
/* F0C4 8001E8C4 0780103C */  lui        $s0, %hi(D_8006FCF4 + 0x2400)
/* F0C8 8001E8C8 F4201026 */  addiu      $s0, $s0, %lo(D_8006FCF4 + 0x2400)
/* F0CC 8001E8CC 0780013C */  lui        $at, %hi(g_DB + 0x19)
/* F0D0 8001E8D0 F96E20A0 */  sb         $zero, %lo(g_DB + 0x19)($at)
/* F0D4 8001E8D4 0780013C */  lui        $at, %hi(g_DB + 0x1A)
/* F0D8 8001E8D8 FA6E20A0 */  sb         $zero, %lo(g_DB + 0x1A)($at)
/* F0DC 8001E8DC 0780013C */  lui        $at, %hi(g_DB + 0x1B)
/* F0E0 8001E8E0 FB6E20A0 */  sb         $zero, %lo(g_DB + 0x1B)($at)
/* F0E4 8001E8E4 0780013C */  lui        $at, %hi(g_DB + 0x9D)
/* F0E8 8001E8E8 7D6F20A0 */  sb         $zero, %lo(g_DB + 0x9D)($at)
/* F0EC 8001E8EC 0780013C */  lui        $at, %hi(g_DB + 0x9E)
/* F0F0 8001E8F0 7E6F20A0 */  sb         $zero, %lo(g_DB + 0x9E)($at)
/* F0F4 8001E8F4 0780013C */  lui        $at, %hi(g_DB + 0x9F)
/* F0F8 8001E8F8 7F6F20A0 */  sb         $zero, %lo(g_DB + 0x9F)($at)
/* F0FC 8001E8FC 2062000C */  jal        func_80018880
/* F100 8001E900 000000AE */   sw        $zero, 0x0($s0)
/* F104 8001E904 00DC0426 */  addiu      $a0, $s0, -0x2400
/* F108 8001E908 21280000 */  addu       $a1, $zero, $zero
/* F10C 8001E90C 455A000C */  jal        Memset
/* F110 8001E910 00090624 */   addiu     $a2, $zero, 0x900
/* F114 8001E914 8B8A000C */  jal        func_80022A2C
/* F118 8001E918 00000000 */   nop
/* F11C 8001E91C 0880033C */  lui        $v1, %hi(g_TitlescreenState + 0x4)
/* F120 8001E920 7C8D638C */  lw         $v1, %lo(g_TitlescreenState + 0x4)($v1)
/* F124 8001E924 02000224 */  addiu      $v0, $zero, 0x2
/* F128 8001E928 12006214 */  bne        $v1, $v0, .L8001E974
/* F12C 8001E92C 00000000 */   nop
/* F130 8001E930 B18E000C */  jal        func_80023AC4
/* F134 8001E934 00000000 */   nop
/* F138 8001E938 0780033C */  lui        $v1, %hi(D_8007581C)
/* F13C 8001E93C 1C58638C */  lw         $v1, %lo(D_8007581C)($v1)
/* F140 8001E940 0780043C */  lui        $a0, %hi(D_80075820)
/* F144 8001E944 2058848C */  lw         $a0, %lo(D_80075820)($a0)
/* F148 8001E948 0000628C */  lw         $v0, 0x0($v1)
/* F14C 8001E94C 00000000 */  nop
/* F150 8001E950 000182AC */  sw         $v0, 0x100($a0)
/* F154 8001E954 0400628C */  lw         $v0, 0x4($v1)
/* F158 8001E958 00000000 */  nop
/* F15C 8001E95C 040182AC */  sw         $v0, 0x104($a0)
/* F160 8001E960 000060AC */  sw         $zero, 0x0($v1)
/* F164 8001E964 0780023C */  lui        $v0, %hi(D_8007581C)
/* F168 8001E968 1C58428C */  lw         $v0, %lo(D_8007581C)($v0)
/* F16C 8001E96C 00000000 */  nop
/* F170 8001E970 040040AC */  sw         $zero, 0x4($v0)
.L8001E974:
/* F174 8001E974 D97D010C */  jal        DrawSync
/* F178 8001E978 21200000 */   addu      $a0, $zero, $zero
/* F17C 8001E97C F176010C */  jal        VSync
/* F180 8001E980 21200000 */   addu      $a0, $zero, $zero
/* F184 8001E984 0780043C */  lui        $a0, %hi(D_80075888)
/* F188 8001E988 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* F18C 8001E98C 0C80010C */  jal        PutDispEnv
/* F190 8001E990 5C008424 */   addiu     $a0, $a0, 0x5C
/* F194 8001E994 0780043C */  lui        $a0, %hi(D_80075888)
/* F198 8001E998 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* F19C 8001E99C 767F010C */  jal        PutDrawEnv
/* F1A0 8001E9A0 00000000 */   nop
/* F1A4 8001E9A4 E159000C */  jal        func_80016784
/* F1A8 8001E9A8 00080424 */   addiu     $a0, $zero, 0x800
/* F1AC 8001E9AC 597F010C */  jal        DrawOTag
/* F1B0 8001E9B0 21204000 */   addu      $a0, $v0, $zero
/* F1B4 8001E9B4 3C00BF8F */  lw         $ra, 0x3C($sp)
/* F1B8 8001E9B8 3800B08F */  lw         $s0, 0x38($sp)
/* F1BC 8001E9BC 4000BD27 */  addiu      $sp, $sp, 0x40
/* F1C0 8001E9C0 0800E003 */  jr         $ra
/* F1C4 8001E9C4 00000000 */   nop
.size func_8001E6B8, . - func_8001E6B8
