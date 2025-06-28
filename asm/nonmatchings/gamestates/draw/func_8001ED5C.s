.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8001ED5C
/* F55C 8001ED5C E8FFBD27 */  addiu      $sp, $sp, -0x18
/* F560 8001ED60 0780023C */  lui        $v0, %hi(D_80075888)
/* F564 8001ED64 8858428C */  lw         $v0, %lo(D_80075888)($v0)
/* F568 8001ED68 0780063C */  lui        $a2, %hi(g_DB)
/* F56C 8001ED6C E06EC624 */  addiu      $a2, $a2, %lo(g_DB)
/* F570 8001ED70 1400BFAF */  sw         $ra, 0x14($sp)
/* F574 8001ED74 02004614 */  bne        $v0, $a2, .L8001ED80
/* F578 8001ED78 1000B0AF */   sw        $s0, 0x10($sp)
/* F57C 8001ED7C 8400C624 */  addiu      $a2, $a2, 0x84
.L8001ED80:
/* F580 8001ED80 0100053C */  lui        $a1, (0x1C000 >> 16)
/* F584 8001ED84 7400C38C */  lw         $v1, 0x74($a2)
/* F588 8001ED88 7800C48C */  lw         $a0, 0x78($a2)
/* F58C 8001ED8C 7000C28C */  lw         $v0, 0x70($a2)
/* F590 8001ED90 00C0A534 */  ori        $a1, $a1, (0x1C000 & 0xFFFF)
/* F594 8001ED94 0780013C */  lui        $at, %hi(D_80075888)
/* F598 8001ED98 885826AC */  sw         $a2, %lo(D_80075888)($at)
/* F59C 8001ED9C 0780013C */  lui        $at, %hi(D_800758B0)
/* F5A0 8001EDA0 B05820AC */  sw         $zero, %lo(D_800758B0)($at)
/* F5A4 8001EDA4 0780013C */  lui        $at, %hi(D_800757B0)
/* F5A8 8001EDA8 B05722AC */  sw         $v0, %lo(D_800757B0)($at)
/* F5AC 8001EDAC 21104500 */  addu       $v0, $v0, $a1
/* F5B0 8001EDB0 0780013C */  lui        $at, %hi(D_80075820)
/* F5B4 8001EDB4 205823AC */  sw         $v1, %lo(D_80075820)($at)
/* F5B8 8001EDB8 0780013C */  lui        $at, %hi(D_8007581C)
/* F5BC 8001EDBC 1C5824AC */  sw         $a0, %lo(D_8007581C)($at)
/* F5C0 8001EDC0 0780013C */  lui        $at, %hi(D_80075780)
/* F5C4 8001EDC4 805722AC */  sw         $v0, %lo(D_80075780)($at)
/* F5C8 8001EDC8 0780013C */  lui        $at, %hi(D_800756FC)
/* F5CC 8001EDCC FC5622AC */  sw         $v0, %lo(D_800756FC)($at)
/* F5D0 8001EDD0 0780013C */  lui        $at, %hi(D_80075710)
/* F5D4 8001EDD4 105722AC */  sw         $v0, %lo(D_80075710)($at)
/* F5D8 8001EDD8 14CF000C */  jal        CameraUpdateMatrices
/* F5DC 8001EDDC 00000000 */   nop
/* F5E0 8001EDE0 0780033C */  lui        $v1, %hi(g_Gamestate)
/* F5E4 8001EDE4 D857638C */  lw         $v1, %lo(g_Gamestate)($v1)
/* F5E8 8001EDE8 00000000 */  nop
/* F5EC 8001EDEC 64006010 */  beqz       $v1, .L8001EF80
/* F5F0 8001EDF0 01000224 */   addiu     $v0, $zero, 0x1
/* F5F4 8001EDF4 24006210 */  beq        $v1, $v0, .L8001EE88
/* F5F8 8001EDF8 02000224 */   addiu     $v0, $zero, 0x2
/* F5FC 8001EDFC 0D006210 */  beq        $v1, $v0, .L8001EE34
/* F600 8001EE00 03000224 */   addiu     $v0, $zero, 0x3
/* F604 8001EE04 0B006210 */  beq        $v1, $v0, .L8001EE34
/* F608 8001EE08 04000224 */   addiu     $v0, $zero, 0x4
/* F60C 8001EE0C 03006210 */  beq        $v1, $v0, .L8001EE1C
/* F610 8001EE10 05000224 */   addiu     $v0, $zero, 0x5
/* F614 8001EE14 05006214 */  bne        $v1, $v0, .L8001EE2C
/* F618 8001EE18 06000224 */   addiu     $v0, $zero, 0x6
.L8001EE1C:
/* F61C 8001EE1C 8E72000C */  jal        func_8001CA38
/* F620 8001EE20 00000000 */   nop
/* F624 8001EE24 517C0008 */  j          .L8001F144
/* F628 8001EE28 00000000 */   nop
.L8001EE2C:
/* F62C 8001EE2C 05006214 */  bne        $v1, $v0, .L8001EE44
/* F630 8001EE30 07000224 */   addiu     $v0, $zero, 0x7
.L8001EE34:
/* F634 8001EE34 0369000C */  jal        func_8001A40C
/* F638 8001EE38 00000000 */   nop
/* F63C 8001EE3C 517C0008 */  j          .L8001F144
/* F640 8001EE40 00000000 */   nop
.L8001EE44:
/* F644 8001EE44 08006214 */  bne        $v1, $v0, .L8001EE68
/* F648 8001EE48 08000224 */   addiu     $v0, $zero, 0x8
/* F64C 8001EE4C 0780023C */  lui        $v0, %hi(D_8007567C)
/* F650 8001EE50 7C56428C */  lw         $v0, %lo(D_8007567C)($v0)
/* F654 8001EE54 00000000 */  nop
/* F658 8001EE58 09F84000 */  jalr       $v0
/* F65C 8001EE5C 00000000 */   nop
/* F660 8001EE60 517C0008 */  j          .L8001F144
/* F664 8001EE64 00000000 */   nop
.L8001EE68:
/* F668 8001EE68 05006214 */  bne        $v1, $v0, .L8001EE80
/* F66C 8001EE6C 09000224 */   addiu     $v0, $zero, 0x9
/* F670 8001EE70 F773000C */  jal        func_8001CFDC
/* F674 8001EE74 00000000 */   nop
/* F678 8001EE78 517C0008 */  j          .L8001F144
/* F67C 8001EE7C 00000000 */   nop
.L8001EE80:
/* F680 8001EE80 05006214 */  bne        $v1, $v0, .L8001EE98
/* F684 8001EE84 0A000224 */   addiu     $v0, $zero, 0xA
.L8001EE88:
/* F688 8001EE88 1468000C */  jal        func_8001A050
/* F68C 8001EE8C 00000000 */   nop
/* F690 8001EE90 517C0008 */  j          .L8001F144
/* F694 8001EE94 00000000 */   nop
.L8001EE98:
/* F698 8001EE98 0780033C */  lui        $v1, %hi(g_Gamestate)
/* F69C 8001EE9C D857638C */  lw         $v1, %lo(g_Gamestate)($v1)
/* F6A0 8001EEA0 00000000 */  nop
/* F6A4 8001EEA4 05006214 */  bne        $v1, $v0, .L8001EEBC
/* F6A8 8001EEA8 0B000224 */   addiu     $v0, $zero, 0xB
/* F6AC 8001EEAC A571000C */  jal        func_8001C694
/* F6B0 8001EEB0 00000000 */   nop
/* F6B4 8001EEB4 517C0008 */  j          .L8001F144
/* F6B8 8001EEB8 00000000 */   nop
.L8001EEBC:
/* F6BC 8001EEBC 05006214 */  bne        $v1, $v0, .L8001EED4
/* F6C0 8001EEC0 0C000224 */   addiu     $v0, $zero, 0xC
/* F6C4 8001EEC4 C675000C */  jal        func_8001D718
/* F6C8 8001EEC8 00000000 */   nop
/* F6CC 8001EECC 517C0008 */  j          .L8001F144
/* F6D0 8001EED0 00000000 */   nop
.L8001EED4:
/* F6D4 8001EED4 05006214 */  bne        $v1, $v0, .L8001EEEC
/* F6D8 8001EED8 0D000224 */   addiu     $v0, $zero, 0xD
/* F6DC 8001EEDC 9378000C */  jal        func_8001E24C
/* F6E0 8001EEE0 00000000 */   nop
/* F6E4 8001EEE4 517C0008 */  j          .L8001F144
/* F6E8 8001EEE8 00000000 */   nop
.L8001EEEC:
/* F6EC 8001EEEC 0E006214 */  bne        $v1, $v0, .L8001EF28
/* F6F0 8001EEF0 0E000224 */   addiu     $v0, $zero, 0xE
/* F6F4 8001EEF4 0880033C */  lui        $v1, %hi(g_TitlescreenState)
/* F6F8 8001EEF8 788D638C */  lw         $v1, %lo(g_TitlescreenState)($v1)
/* F6FC 8001EEFC 03000224 */  addiu      $v0, $zero, 0x3
/* F700 8001EF00 05006214 */  bne        $v1, $v0, .L8001EF18
/* F704 8001EF04 00000000 */   nop
/* F708 8001EF08 AE79000C */  jal        func_8001E6B8
/* F70C 8001EF0C 00000000 */   nop
/* F710 8001EF10 517C0008 */  j          .L8001F144
/* F714 8001EF14 00000000 */   nop
.L8001EF18:
/* F718 8001EF18 B9F3010C */  jal        func_titlescreen_8007CEE4
/* F71C 8001EF1C 00000000 */   nop
/* F720 8001EF20 517C0008 */  j          .L8001F144
/* F724 8001EF24 00000000 */   nop
.L8001EF28:
/* F728 8001EF28 05006214 */  bne        $v1, $v0, .L8001EF40
/* F72C 8001EF2C 0F000224 */   addiu     $v0, $zero, 0xF
/* F730 8001EF30 727A000C */  jal        func_8001E9C8
/* F734 8001EF34 00000000 */   nop
/* F738 8001EF38 517C0008 */  j          .L8001F144
/* F73C 8001EF3C 00000000 */   nop
.L8001EF40:
/* F740 8001EF40 80006214 */  bne        $v1, $v0, .L8001F144
/* F744 8001EF44 00000000 */   nop
/* F748 8001EF48 0780023C */  lui        $v0, %hi(D_80075704)
/* F74C 8001EF4C 0457428C */  lw         $v0, %lo(D_80075704)($v0)
/* F750 8001EF50 00000000 */  nop
/* F754 8001EF54 63004228 */  slti       $v0, $v0, 0x63
/* F758 8001EF58 05004010 */  beqz       $v0, .L8001EF70
/* F75C 8001EF5C 00000000 */   nop
/* F760 8001EF60 F4EF010C */  jal        func_credits_8007BFD0
/* F764 8001EF64 00000000 */   nop
/* F768 8001EF68 517C0008 */  j          .L8001F144
/* F76C 8001EF6C 00000000 */   nop
.L8001EF70:
/* F770 8001EF70 E07A000C */  jal        func_8001EB80
/* F774 8001EF74 00000000 */   nop
/* F778 8001EF78 517C0008 */  j          .L8001F144
/* F77C 8001EF7C 00000000 */   nop
.L8001EF80:
/* F780 8001EF80 0880023C */  lui        $v0, %hi(g_Cyclorama + 0x10)
/* F784 8001EF84 508A4290 */  lbu        $v0, %lo(g_Cyclorama + 0x10)($v0)
/* F788 8001EF88 0880033C */  lui        $v1, %hi(g_Cyclorama + 0x11)
/* F78C 8001EF8C 518A6390 */  lbu        $v1, %lo(g_Cyclorama + 0x11)($v1)
/* F790 8001EF90 0880043C */  lui        $a0, %hi(g_Cyclorama + 0x12)
/* F794 8001EF94 528A8490 */  lbu        $a0, %lo(g_Cyclorama + 0x12)($a0)
/* F798 8001EF98 0780013C */  lui        $at, %hi(g_DB + 0x19)
/* F79C 8001EF9C F96E22A0 */  sb         $v0, %lo(g_DB + 0x19)($at)
/* F7A0 8001EFA0 0780013C */  lui        $at, %hi(g_DB + 0x1A)
/* F7A4 8001EFA4 FA6E23A0 */  sb         $v1, %lo(g_DB + 0x1A)($at)
/* F7A8 8001EFA8 0780013C */  lui        $at, %hi(g_DB + 0x1B)
/* F7AC 8001EFAC FB6E24A0 */  sb         $a0, %lo(g_DB + 0x1B)($at)
/* F7B0 8001EFB0 0780013C */  lui        $at, %hi(g_DB + 0x9D)
/* F7B4 8001EFB4 7D6F22A0 */  sb         $v0, %lo(g_DB + 0x9D)($at)
/* F7B8 8001EFB8 0780013C */  lui        $at, %hi(g_DB + 0x9E)
/* F7BC 8001EFBC 7E6F23A0 */  sb         $v1, %lo(g_DB + 0x9E)($at)
/* F7C0 8001EFC0 0780013C */  lui        $at, %hi(g_DB + 0x9F)
/* F7C4 8001EFC4 7F6F24A0 */  sb         $a0, %lo(g_DB + 0x9F)($at)
/* F7C8 8001EFC8 7048010C */  jal        func_800521C0
/* F7CC 8001EFCC 00000000 */   nop
/* F7D0 8001EFD0 0780023C */  lui        $v0, %hi(D_80075690)
/* F7D4 8001EFD4 9056428C */  lw         $v0, %lo(D_80075690)($v0)
/* F7D8 8001EFD8 00000000 */  nop
/* F7DC 8001EFDC 03004014 */  bnez       $v0, .L8001EFEC
/* F7E0 8001EFE0 00000000 */   nop
/* F7E4 8001EFE4 C064000C */  jal        func_80019300
/* F7E8 8001EFE8 00000000 */   nop
.L8001EFEC:
/* F7EC 8001EFEC 0780023C */  lui        $v0, %hi(D_80075714)
/* F7F0 8001EFF0 1457428C */  lw         $v0, %lo(D_80075714)($v0)
/* F7F4 8001EFF4 00000000 */  nop
/* F7F8 8001EFF8 03004010 */  beqz       $v0, .L8001F008
/* F7FC 8001EFFC 00000000 */   nop
/* F800 8001F000 4262000C */  jal        func_80018908
/* F804 8001F004 00000000 */   nop
.L8001F008:
/* F808 8001F008 A665000C */  jal        func_80019698
/* F80C 8001F00C 00000000 */   nop
/* F810 8001F010 73AE000C */  jal        func_8002B9CC
/* F814 8001F014 00000000 */   nop
/* F818 8001F018 F442010C */  jal        func_80050BD0
/* F81C 8001F01C 00000000 */   nop
/* F820 8001F020 F25C010C */  jal        func_800573C8
/* F824 8001F024 00000000 */   nop
/* F828 8001F028 0780053C */  lui        $a1, %hi(D_80075918)
/* F82C 8001F02C 1859A58C */  lw         $a1, %lo(D_80075918)($a1)
/* F830 8001F030 00000000 */  nop
/* F834 8001F034 0500A010 */  beqz       $a1, .L8001F04C
/* F838 8001F038 02000424 */   addiu     $a0, $zero, 0x2
/* F83C 8001F03C C0280500 */  sll        $a1, $a1, 3
/* F840 8001F040 2130A000 */  addu       $a2, $a1, $zero
/* F844 8001F044 3564000C */  jal        func_800190D4
/* F848 8001F048 2138A000 */   addu      $a3, $a1, $zero
.L8001F04C:
/* F84C 8001F04C 0780023C */  lui        $v0, %hi(D_8007570C)
/* F850 8001F050 0C57428C */  lw         $v0, %lo(D_8007570C)($v0)
/* F854 8001F054 00000000 */  nop
/* F858 8001F058 06004014 */  bnez       $v0, .L8001F074
/* F85C 8001F05C 00000000 */   nop
/* F860 8001F060 0780023C */  lui        $v0, %hi(D_800756C0)
/* F864 8001F064 C056428C */  lw         $v0, %lo(D_800756C0)($v0)
/* F868 8001F068 00000000 */  nop
/* F86C 8001F06C 03004010 */  beqz       $v0, .L8001F07C
/* F870 8001F070 00000000 */   nop
.L8001F074:
/* F874 8001F074 CC63000C */  jal        func_80018F30
/* F878 8001F078 00000000 */   nop
.L8001F07C:
/* F87C 8001F07C 7C62000C */  jal        func_800189F0
/* F880 8001F080 00000000 */   nop
/* F884 8001F084 D97D010C */  jal        DrawSync
/* F888 8001F088 21200000 */   addu      $a0, $zero, $zero
/* F88C 8001F08C 0780023C */  lui        $v0, %hi(D_80075784)
/* F890 8001F090 8457428C */  lw         $v0, %lo(D_80075784)($v0)
/* F894 8001F094 00000000 */  nop
/* F898 8001F098 03004010 */  beqz       $v0, .L8001F0A8
/* F89C 8001F09C 00000000 */   nop
/* F8A0 8001F0A0 F176010C */  jal        VSync
/* F8A4 8001F0A4 21200000 */   addu      $a0, $zero, $zero
.L8001F0A8:
/* F8A8 8001F0A8 F176010C */  jal        VSync
/* F8AC 8001F0AC FFFF0424 */   addiu     $a0, $zero, -0x1
/* F8B0 8001F0B0 0780033C */  lui        $v1, %hi(D_80075950)
/* F8B4 8001F0B4 5059638C */  lw         $v1, %lo(D_80075950)($v1)
/* F8B8 8001F0B8 0780013C */  lui        $at, %hi(D_80075954)
/* F8BC 8001F0BC 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* F8C0 8001F0C0 23104300 */  subu       $v0, $v0, $v1
/* F8C4 8001F0C4 02004228 */  slti       $v0, $v0, 0x2
/* F8C8 8001F0C8 0E004010 */  beqz       $v0, .L8001F104
/* F8CC 8001F0CC 00000000 */   nop
/* F8D0 8001F0D0 0780103C */  lui        $s0, %hi(D_80075954)
/* F8D4 8001F0D4 54591026 */  addiu      $s0, $s0, %lo(D_80075954)
.L8001F0D8:
/* F8D8 8001F0D8 F176010C */  jal        VSync
/* F8DC 8001F0DC 21200000 */   addu      $a0, $zero, $zero
/* F8E0 8001F0E0 F176010C */  jal        VSync
/* F8E4 8001F0E4 FFFF0424 */   addiu     $a0, $zero, -0x1
/* F8E8 8001F0E8 FCFF038E */  lw         $v1, -0x4($s0)
/* F8EC 8001F0EC 0780013C */  lui        $at, %hi(D_80075954)
/* F8F0 8001F0F0 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* F8F4 8001F0F4 23104300 */  subu       $v0, $v0, $v1
/* F8F8 8001F0F8 02004228 */  slti       $v0, $v0, 0x2
/* F8FC 8001F0FC F6FF4014 */  bnez       $v0, .L8001F0D8
/* F900 8001F100 00000000 */   nop
.L8001F104:
/* F904 8001F104 F176010C */  jal        VSync
/* F908 8001F108 FFFF0424 */   addiu     $a0, $zero, -0x1
/* F90C 8001F10C 0780043C */  lui        $a0, %hi(D_80075888)
/* F910 8001F110 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* F914 8001F114 0780013C */  lui        $at, %hi(D_80075950)
/* F918 8001F118 505922AC */  sw         $v0, %lo(D_80075950)($at)
/* F91C 8001F11C 0C80010C */  jal        PutDispEnv
/* F920 8001F120 5C008424 */   addiu     $a0, $a0, 0x5C
/* F924 8001F124 0780043C */  lui        $a0, %hi(D_80075888)
/* F928 8001F128 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* F92C 8001F12C 767F010C */  jal        PutDrawEnv
/* F930 8001F130 00000000 */   nop
/* F934 8001F134 E159000C */  jal        func_80016784
/* F938 8001F138 00080424 */   addiu     $a0, $zero, 0x800
/* F93C 8001F13C 597F010C */  jal        DrawOTag
/* F940 8001F140 21204000 */   addu      $a0, $v0, $zero
.L8001F144:
/* F944 8001F144 1400BF8F */  lw         $ra, 0x14($sp)
/* F948 8001F148 1000B08F */  lw         $s0, 0x10($sp)
/* F94C 8001F14C 1800BD27 */  addiu      $sp, $sp, 0x18
/* F950 8001F150 0800E003 */  jr         $ra
/* F954 8001F154 00000000 */   nop
.size func_8001ED5C, . - func_8001ED5C
