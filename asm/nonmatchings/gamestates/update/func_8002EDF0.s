.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002EDF0
/* 1F5F0 8002EDF0 0780023C */  lui        $v0, %hi(D_8007593C)
/* 1F5F4 8002EDF4 3C59428C */  lw         $v0, %lo(D_8007593C)($v0)
/* 1F5F8 8002EDF8 B0FFBD27 */  addiu      $sp, $sp, -0x50
/* 1F5FC 8002EDFC 4800BFAF */  sw         $ra, 0x48($sp)
/* 1F600 8002EE00 4400B3AF */  sw         $s3, 0x44($sp)
/* 1F604 8002EE04 4000B2AF */  sw         $s2, 0x40($sp)
/* 1F608 8002EE08 3C00B1AF */  sw         $s1, 0x3C($sp)
/* 1F60C 8002EE0C 03004014 */  bnez       $v0, .L8002EE1C
/* 1F610 8002EE10 3800B0AF */   sw        $s0, 0x38($sp)
/* 1F614 8002EE14 CA5A010C */  jal        func_80056B28
/* 1F618 8002EE18 21200000 */   addu      $a0, $zero, $zero
.L8002EE1C:
/* 1F61C 8002EE1C 0780023C */  lui        $v0, %hi(D_8007593C)
/* 1F620 8002EE20 3C59428C */  lw         $v0, %lo(D_8007593C)($v0)
/* 1F624 8002EE24 00000000 */  nop
/* 1F628 8002EE28 01004224 */  addiu      $v0, $v0, 0x1
/* 1F62C 8002EE2C 0780013C */  lui        $at, %hi(D_8007593C)
/* 1F630 8002EE30 3C5922AC */  sw         $v0, %lo(D_8007593C)($at)
/* 1F634 8002EE34 3063010C */  jal        SpecularUpdate
/* 1F638 8002EE38 03000424 */   addiu     $a0, $zero, 0x3
/* 1F63C 8002EE3C 0780123C */  lui        $s2, %hi(D_80075940)
/* 1F640 8002EE40 4059528E */  lw         $s2, %lo(D_80075940)($s2)
/* 1F644 8002EE44 00000000 */  nop
/* 1F648 8002EE48 9E004016 */  bnez       $s2, .L8002F0C4
/* 1F64C 8002EE4C 01000224 */   addiu     $v0, $zero, 0x1
/* 1F650 8002EE50 0780023C */  lui        $v0, %hi(D_8007593C)
/* 1F654 8002EE54 3C59428C */  lw         $v0, %lo(D_8007593C)($v0)
/* 1F658 8002EE58 00000000 */  nop
/* 1F65C 8002EE5C 10004228 */  slti       $v0, $v0, 0x10
/* 1F660 8002EE60 50014014 */  bnez       $v0, .L8002F3A4
/* 1F664 8002EE64 04000224 */   addiu     $v0, $zero, 0x4
/* 1F668 8002EE68 0780033C */  lui        $v1, %hi(g_Gamestate)
/* 1F66C 8002EE6C D857638C */  lw         $v1, %lo(g_Gamestate)($v1)
/* 1F670 8002EE70 00000000 */  nop
/* 1F674 8002EE74 07006214 */  bne        $v1, $v0, .L8002EE94
/* 1F678 8002EE78 58020224 */   addiu     $v0, $zero, 0x258
/* 1F67C 8002EE7C 29B2000C */  jal        func_8002C8A4
/* 1F680 8002EE80 00000000 */   nop
/* 1F684 8002EE84 3251000C */  jal        func_800144C8
/* 1F688 8002EE88 00000000 */   nop
/* 1F68C 8002EE8C E9BC0008 */  j          .L8002F3A4
/* 1F690 8002EE90 00000000 */   nop
.L8002EE94:
/* 1F694 8002EE94 0880103C */  lui        $s0, %hi(g_WadHeader + 0x3C)
/* 1F698 8002EE98 0CA71026 */  addiu      $s0, $s0, %lo(g_WadHeader + 0x3C)
/* 1F69C 8002EE9C 0780043C */  lui        $a0, %hi(D_80076B90)
/* 1F6A0 8002EEA0 906B848C */  lw         $a0, %lo(D_80076B90)($a0)
/* 1F6A4 8002EEA4 0000068E */  lw         $a2, 0x0($s0)
/* 1F6A8 8002EEA8 0880113C */  lui        $s1, %hi(D_800785D8 + 0x10)
/* 1F6AC 8002EEAC E8853126 */  addiu      $s1, $s1, %lo(D_800785D8 + 0x10)
/* 1F6B0 8002EEB0 1000A2AF */  sw         $v0, 0x10($sp)
/* 1F6B4 8002EEB4 0000228E */  lw         $v0, 0x0($s1)
/* 1F6B8 8002EEB8 0000058E */  lw         $a1, 0x0($s0)
/* 1F6BC 8002EEBC 0880073C */  lui        $a3, %hi(g_WadHeader + 0x38)
/* 1F6C0 8002EEC0 08A7E78C */  lw         $a3, %lo(g_WadHeader + 0x38)($a3)
/* 1F6C4 8002EEC4 4059000C */  jal        CDLoadSync
/* 1F6C8 8002EEC8 23284500 */   subu      $a1, $v0, $a1
/* 1F6CC 8002EECC 0000238E */  lw         $v1, 0x0($s1)
/* 1F6D0 8002EED0 0000028E */  lw         $v0, 0x0($s0)
/* 1F6D4 8002EED4 0880083C */  lui        $t0, %hi(g_Cyclorama + 0x10)
/* 1F6D8 8002EED8 508A0825 */  addiu      $t0, $t0, %lo(g_Cyclorama + 0x10)
/* 1F6DC 8002EEDC 23286200 */  subu       $a1, $v1, $v0
/* 1F6E0 8002EEE0 0000A490 */  lbu        $a0, 0x0($a1)
/* 1F6E4 8002EEE4 00000000 */  nop
/* 1F6E8 8002EEE8 000004A1 */  sb         $a0, 0x0($t0)
/* 1F6EC 8002EEEC 0100A390 */  lbu        $v1, 0x1($a1)
/* 1F6F0 8002EEF0 2138A000 */  addu       $a3, $a1, $zero
/* 1F6F4 8002EEF4 0880013C */  lui        $at, %hi(g_Cyclorama + 0x11)
/* 1F6F8 8002EEF8 518A23A0 */  sb         $v1, %lo(g_Cyclorama + 0x11)($at)
/* 1F6FC 8002EEFC 0200A290 */  lbu        $v0, 0x2($a1)
/* 1F700 8002EF00 0400A524 */  addiu      $a1, $a1, 0x4
/* 1F704 8002EF04 0780013C */  lui        $at, %hi(g_DB + 0x19)
/* 1F708 8002EF08 F96E24A0 */  sb         $a0, %lo(g_DB + 0x19)($at)
/* 1F70C 8002EF0C 0780013C */  lui        $at, %hi(g_DB + 0x1A)
/* 1F710 8002EF10 FA6E23A0 */  sb         $v1, %lo(g_DB + 0x1A)($at)
/* 1F714 8002EF14 0780013C */  lui        $at, %hi(g_DB + 0x9D)
/* 1F718 8002EF18 7D6F24A0 */  sb         $a0, %lo(g_DB + 0x9D)($at)
/* 1F71C 8002EF1C 0780013C */  lui        $at, %hi(g_DB + 0x9E)
/* 1F720 8002EF20 7E6F23A0 */  sb         $v1, %lo(g_DB + 0x9E)($at)
/* 1F724 8002EF24 0880013C */  lui        $at, %hi(g_Cyclorama + 0x12)
/* 1F728 8002EF28 528A22A0 */  sb         $v0, %lo(g_Cyclorama + 0x12)($at)
/* 1F72C 8002EF2C 0780013C */  lui        $at, %hi(g_DB + 0x1B)
/* 1F730 8002EF30 FB6E22A0 */  sb         $v0, %lo(g_DB + 0x1B)($at)
/* 1F734 8002EF34 0780013C */  lui        $at, %hi(g_DB + 0x9F)
/* 1F738 8002EF38 7F6F22A0 */  sb         $v0, %lo(g_DB + 0x9F)($at)
/* 1F73C 8002EF3C 0000A28C */  lw         $v0, 0x0($a1)
/* 1F740 8002EF40 0400A524 */  addiu      $a1, $a1, 0x4
/* 1F744 8002EF44 0880013C */  lui        $at, %hi(g_Cyclorama + 0x4)
/* 1F748 8002EF48 448A25AC */  sw         $a1, %lo(g_Cyclorama + 0x4)($at)
/* 1F74C 8002EF4C 0880013C */  lui        $at, %hi(g_Cyclorama)
/* 1F750 8002EF50 408A22AC */  sw         $v0, %lo(g_Cyclorama)($at)
/* 1F754 8002EF54 2A104202 */  slt        $v0, $s2, $v0
/* 1F758 8002EF58 0B004010 */  beqz       $v0, .L8002EF88
/* 1F75C 8002EF5C 21300000 */   addu      $a2, $zero, $zero
/* 1F760 8002EF60 F0FF0325 */  addiu      $v1, $t0, -0x10
.L8002EF64:
/* 1F764 8002EF64 0000A28C */  lw         $v0, 0x0($a1)
/* 1F768 8002EF68 0100C624 */  addiu      $a2, $a2, 0x1
/* 1F76C 8002EF6C 2110E200 */  addu       $v0, $a3, $v0
/* 1F770 8002EF70 0000A2AC */  sw         $v0, 0x0($a1)
/* 1F774 8002EF74 0000628C */  lw         $v0, 0x0($v1)
/* 1F778 8002EF78 00000000 */  nop
/* 1F77C 8002EF7C 2A10C200 */  slt        $v0, $a2, $v0
/* 1F780 8002EF80 F8FF4014 */  bnez       $v0, .L8002EF64
/* 1F784 8002EF84 0400A524 */   addiu     $a1, $a1, 0x4
.L8002EF88:
/* 1F788 8002EF88 0780033C */  lui        $v1, %hi(D_800752D8)
/* 1F78C 8002EF8C D8526394 */  lhu        $v1, %lo(D_800752D8)($v1)
/* 1F790 8002EF90 0780053C */  lui        $a1, %hi(D_800752DA)
/* 1F794 8002EF94 DA52A594 */  lhu        $a1, %lo(D_800752DA)($a1)
/* 1F798 8002EF98 00280224 */  addiu      $v0, $zero, 0x2800
/* 1F79C 8002EF9C 0780013C */  lui        $at, %hi(g_Camera + 0x28)
/* 1F7A0 8002EFA0 F86D22AC */  sw         $v0, %lo(g_Camera + 0x28)($at)
/* 1F7A4 8002EFA4 80000224 */  addiu      $v0, $zero, 0x80
/* 1F7A8 8002EFA8 0780013C */  lui        $at, %hi(g_Camera + 0x2C)
/* 1F7AC 8002EFAC FC6D22AC */  sw         $v0, %lo(g_Camera + 0x2C)($at)
/* 1F7B0 8002EFB0 00080224 */  addiu      $v0, $zero, 0x800
/* 1F7B4 8002EFB4 0780013C */  lui        $at, %hi(g_Camera + 0x4C)
/* 1F7B8 8002EFB8 1C6E20A4 */  sh         $zero, %lo(g_Camera + 0x4C)($at)
/* 1F7BC 8002EFBC 0780013C */  lui        $at, %hi(g_Camera + 0x30)
/* 1F7C0 8002EFC0 006E22AC */  sw         $v0, %lo(g_Camera + 0x30)($at)
/* 1F7C4 8002EFC4 0780013C */  lui        $at, %hi(g_Camera + 0x4E)
/* 1F7C8 8002EFC8 1E6E23A4 */  sh         $v1, %lo(g_Camera + 0x4E)($at)
/* 1F7CC 8002EFCC 0780013C */  lui        $at, %hi(g_Camera + 0x50)
/* 1F7D0 8002EFD0 206E25A4 */  sh         $a1, %lo(g_Camera + 0x50)($at)
/* 1F7D4 8002EFD4 092B010C */  jal        func_8004AC24
/* 1F7D8 8002EFD8 01000424 */   addiu     $a0, $zero, 0x1
/* 1F7DC 8002EFDC 0780043C */  lui        $a0, %hi(g_Checkpoint)
/* 1F7E0 8002EFE0 88788424 */  addiu      $a0, $a0, %lo(g_Checkpoint)
/* 1F7E4 8002EFE4 21280000 */  addu       $a1, $zero, $zero
/* 1F7E8 8002EFE8 0780033C */  lui        $v1, %hi(g_LevelIndex)
/* 1F7EC 8002EFEC 6459638C */  lw         $v1, %lo(g_LevelIndex)($v1)
/* 1F7F0 8002EFF0 10000224 */  addiu      $v0, $zero, 0x10
/* 1F7F4 8002EFF4 0880013C */  lui        $at, %hi(g_Spyro + 0x18)
/* 1F7F8 8002EFF8 708A22A0 */  sb         $v0, %lo(g_Spyro + 0x18)($at)
/* 1F7FC 8002EFFC 0880013C */  lui        $at, %hi(g_Spyro + 0x19)
/* 1F800 8002F000 718A22A0 */  sb         $v0, %lo(g_Spyro + 0x19)($at)
/* 1F804 8002F004 01000224 */  addiu      $v0, $zero, 0x1
/* 1F808 8002F008 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 1F80C 8002F00C 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 1F810 8002F010 04000224 */  addiu      $v0, $zero, 0x4
/* 1F814 8002F014 0780013C */  lui        $at, %hi(D_8007582C)
/* 1F818 8002F018 2C5822AC */  sw         $v0, %lo(D_8007582C)($at)
/* 1F81C 8002F01C 03000224 */  addiu      $v0, $zero, 0x3
/* 1F820 8002F020 0780013C */  lui        $at, %hi(D_800758E8)
/* 1F824 8002F024 E85820AC */  sw         $zero, %lo(D_800758E8)($at)
/* 1F828 8002F028 0880013C */  lui        $at, %hi(g_Spyro + 0x164)
/* 1F82C 8002F02C BC8B22AC */  sw         $v0, %lo(g_Spyro + 0x164)($at)
/* 1F830 8002F030 0780013C */  lui        $at, %hi(D_800756D0)
/* 1F834 8002F034 D05620AC */  sw         $zero, %lo(D_800756D0)($at)
/* 1F838 8002F038 0780013C */  lui        $at, %hi(g_PortalLevelId)
/* 1F83C 8002F03C AC5820AC */  sw         $zero, %lo(g_PortalLevelId)($at)
/* 1F840 8002F040 0780013C */  lui        $at, %hi(D_800757E8)
/* 1F844 8002F044 E85723AC */  sw         $v1, %lo(D_800757E8)($at)
/* 1F848 8002F048 455A000C */  jal        Memset
/* 1F84C 8002F04C 68000624 */   addiu     $a2, $zero, 0x68
/* 1F850 8002F050 6666023C */  lui        $v0, (0x66666667 >> 16)
/* 1F854 8002F054 0780043C */  lui        $a0, %hi(g_LevelId)
/* 1F858 8002F058 6C59848C */  lw         $a0, %lo(g_LevelId)($a0)
/* 1F85C 8002F05C 67664234 */  ori        $v0, $v0, (0x66666667 & 0xFFFF)
/* 1F860 8002F060 18008200 */  mult       $a0, $v0
/* 1F864 8002F064 C3170400 */  sra        $v0, $a0, 31
/* 1F868 8002F068 10480000 */  mfhi       $t1
/* 1F86C 8002F06C 83180900 */  sra        $v1, $t1, 2
/* 1F870 8002F070 23186200 */  subu       $v1, $v1, $v0
/* 1F874 8002F074 80100300 */  sll        $v0, $v1, 2
/* 1F878 8002F078 21104300 */  addu       $v0, $v0, $v1
/* 1F87C 8002F07C 40100200 */  sll        $v0, $v0, 1
/* 1F880 8002F080 0B008210 */  beq        $a0, $v0, .L8002F0B0
/* 1F884 8002F084 00000000 */   nop
/* 1F888 8002F088 0780013C */  lui        $at, %hi(g_NextLevelId)
/* 1F88C 8002F08C B45822AC */  sw         $v0, %lo(g_NextLevelId)($at)
/* 1F890 8002F090 02000224 */  addiu      $v0, $zero, 0x2
/* 1F894 8002F094 0780013C */  lui        $at, %hi(g_LoadStage)
/* 1F898 8002F098 645822AC */  sw         $v0, %lo(g_LoadStage)($at)
/* 1F89C 8002F09C FFFF0224 */  addiu      $v0, $zero, -0x1
/* 1F8A0 8002F0A0 0780013C */  lui        $at, %hi(D_8007576C)
/* 1F8A4 8002F0A4 6C5722AC */  sw         $v0, %lo(D_8007576C)($at)
/* 1F8A8 8002F0A8 D4BC0008 */  j          .L8002F350
/* 1F8AC 8002F0AC 01000224 */   addiu     $v0, $zero, 0x1
.L8002F0B0:
/* 1F8B0 8002F0B0 0B000224 */  addiu      $v0, $zero, 0xB
/* 1F8B4 8002F0B4 0780013C */  lui        $at, %hi(g_LoadStage)
/* 1F8B8 8002F0B8 645822AC */  sw         $v0, %lo(g_LoadStage)($at)
/* 1F8BC 8002F0BC D4BC0008 */  j          .L8002F350
/* 1F8C0 8002F0C0 01000224 */   addiu     $v0, $zero, 0x1
.L8002F0C4:
/* 1F8C4 8002F0C4 A8004216 */  bne        $s2, $v0, .L8002F368
/* 1F8C8 8002F0C8 00000000 */   nop
/* 1F8CC 8002F0CC 0780023C */  lui        $v0, %hi(D_8007593C)
/* 1F8D0 8002F0D0 3C59428C */  lw         $v0, %lo(D_8007593C)($v0)
/* 1F8D4 8002F0D4 00000000 */  nop
/* 1F8D8 8002F0D8 4CFF5324 */  addiu      $s3, $v0, -0xB4
/* 1F8DC 8002F0DC C000622E */  sltiu      $v0, $s3, 0xC0
/* 1F8E0 8002F0E0 57004010 */  beqz       $v0, .L8002F240
/* 1F8E4 8002F0E4 00811300 */   sll       $s0, $s3, 4
/* 1F8E8 8002F0E8 000E1126 */  addiu      $s1, $s0, 0xE00
/* 1F8EC 8002F0EC FF0F3132 */  andi       $s1, $s1, 0xFFF
/* 1F8F0 8002F0F0 2C5B000C */  jal        Cos
/* 1F8F4 8002F0F4 21202002 */   addu      $a0, $s1, $zero
/* 1F8F8 8002F0F8 AA2A123C */  lui        $s2, (0x2AAAAAAB >> 16)
/* 1F8FC 8002F0FC ABAA5236 */  ori        $s2, $s2, (0x2AAAAAAB & 0xFFFF)
/* 1F900 8002F100 21801302 */  addu       $s0, $s0, $s3
/* 1F904 8002F104 40811000 */  sll        $s0, $s0, 5
/* 1F908 8002F108 23801302 */  subu       $s0, $s0, $s3
/* 1F90C 8002F10C 40801000 */  sll        $s0, $s0, 1
/* 1F910 8002F110 18001202 */  mult       $s0, $s2
/* 1F914 8002F114 C3871000 */  sra        $s0, $s0, 31
/* 1F918 8002F118 10480000 */  mfhi       $t1
/* 1F91C 8002F11C 43190900 */  sra        $v1, $t1, 5
/* 1F920 8002F120 23187000 */  subu       $v1, $v1, $s0
/* 1F924 8002F124 7C081024 */  addiu      $s0, $zero, 0x87C
/* 1F928 8002F128 23800302 */  subu       $s0, $s0, $v1
/* 1F92C 8002F12C 18005000 */  mult       $v0, $s0
/* 1F930 8002F130 12180000 */  mflo       $v1
/* 1F934 8002F134 03130300 */  sra        $v0, $v1, 12
/* 1F938 8002F138 002A4224 */  addiu      $v0, $v0, 0x2A00
/* 1F93C 8002F13C 0880013C */  lui        $at, %hi(g_Spyro)
/* 1F940 8002F140 588A22AC */  sw         $v0, %lo(g_Spyro)($at)
/* 1F944 8002F144 165B000C */  jal        Sin
/* 1F948 8002F148 21202002 */   addu      $a0, $s1, $zero
/* 1F94C 8002F14C 18005000 */  mult       $v0, $s0
/* 1F950 8002F150 40181300 */  sll        $v1, $s3, 1
/* 1F954 8002F154 21187300 */  addu       $v1, $v1, $s3
/* 1F958 8002F158 12200000 */  mflo       $a0
/* 1F95C 8002F15C 40180300 */  sll        $v1, $v1, 1
/* 1F960 8002F160 440B0224 */  addiu      $v0, $zero, 0xB44
/* 1F964 8002F164 18007202 */  mult       $s3, $s2
/* 1F968 8002F168 23104300 */  subu       $v0, $v0, $v1
/* 1F96C 8002F16C 00043126 */  addiu      $s1, $s1, 0x400
/* 1F970 8002F170 03891100 */  sra        $s1, $s1, 4
/* 1F974 8002F174 C31F1300 */  sra        $v1, $s3, 31
/* 1F978 8002F178 0880013C */  lui        $at, %hi(g_Spyro + 0x8)
/* 1F97C 8002F17C 608A22AC */  sw         $v0, %lo(g_Spyro + 0x8)($at)
/* 1F980 8002F180 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 1F984 8002F184 668A31A0 */  sb         $s1, %lo(g_Spyro + 0xE)($at)
/* 1F988 8002F188 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 1F98C 8002F18C 658A20A0 */  sb         $zero, %lo(g_Spyro + 0xD)($at)
/* 1F990 8002F190 03130400 */  sra        $v0, $a0, 12
/* 1F994 8002F194 0780043C */  lui        $a0, %hi(D_8007593C)
/* 1F998 8002F198 3C59848C */  lw         $a0, %lo(D_8007593C)($a0)
/* 1F99C 8002F19C 000C4224 */  addiu      $v0, $v0, 0xC00
/* 1F9A0 8002F1A0 0880013C */  lui        $at, %hi(g_Spyro + 0x4)
/* 1F9A4 8002F1A4 5C8A22AC */  sw         $v0, %lo(g_Spyro + 0x4)($at)
/* 1F9A8 8002F1A8 10480000 */  mfhi       $t1
/* 1F9AC 8002F1AC 43100900 */  sra        $v0, $t1, 1
/* 1F9B0 8002F1B0 23104300 */  subu       $v0, $v0, $v1
/* 1F9B4 8002F1B4 E0FF4224 */  addiu      $v0, $v0, -0x20
/* 1F9B8 8002F1B8 0880013C */  lui        $at, %hi(g_Spyro + 0xC)
/* 1F9BC 8002F1BC 648A22A0 */  sb         $v0, %lo(g_Spyro + 0xC)($at)
/* 1F9C0 8002F1C0 64018228 */  slti       $v0, $a0, 0x164
/* 1F9C4 8002F1C4 05004010 */  beqz       $v0, .L8002F1DC
/* 1F9C8 8002F1C8 9CFE8324 */   addiu     $v1, $a0, -0x164
/* 1F9CC 8002F1CC C9F2000C */  jal        func_8003CB24
/* 1F9D0 8002F1D0 03000424 */   addiu     $a0, $zero, 0x3
/* 1F9D4 8002F1D4 8CBC0008 */  j          .L8002F230
/* 1F9D8 8002F1D8 00000000 */   nop
.L8002F1DC:
/* 1F9DC 8002F1DC 80100300 */  sll        $v0, $v1, 2
/* 1F9E0 8002F1E0 21104300 */  addu       $v0, $v0, $v1
/* 1F9E4 8002F1E4 40180200 */  sll        $v1, $v0, 1
/* 1F9E8 8002F1E8 0E000224 */  addiu      $v0, $zero, 0xE
/* 1F9EC 8002F1EC 0880013C */  lui        $at, %hi(g_Spyro + 0x19)
/* 1F9F0 8002F1F0 718A22A0 */  sb         $v0, %lo(g_Spyro + 0x19)($at)
/* 1F9F4 8002F1F4 9CFF8224 */  addiu      $v0, $a0, -0x64
/* 1F9F8 8002F1F8 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 1F9FC 8002F1FC 778A20A0 */  sb         $zero, %lo(g_Spyro + 0x1F)($at)
/* 1FA00 8002F200 0880013C */  lui        $at, %hi(g_Spyro + 0x24)
/* 1FA04 8002F204 7C8A22A0 */  sb         $v0, %lo(g_Spyro + 0x24)($at)
/* 1FA08 8002F208 03006104 */  bgez       $v1, .L8002F218
/* 1FA0C 8002F20C 03110300 */   sra       $v0, $v1, 4
/* 1FA10 8002F210 0F006324 */  addiu      $v1, $v1, 0xF
/* 1FA14 8002F214 03110300 */  sra        $v0, $v1, 4
.L8002F218:
/* 1FA18 8002F218 23100200 */  negu       $v0, $v0
/* 1FA1C 8002F21C 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 1FA20 8002F220 658A22A0 */  sb         $v0, %lo(g_Spyro + 0xD)($at)
/* 1FA24 8002F224 8CFF8224 */  addiu      $v0, $a0, -0x74
/* 1FA28 8002F228 0880013C */  lui        $at, %hi(g_Spyro + 0xC)
/* 1FA2C 8002F22C 648A22A0 */  sb         $v0, %lo(g_Spyro + 0xC)($at)
.L8002F230:
/* 1FA30 8002F230 9825010C */  jal        func_80049660
/* 1FA34 8002F234 00000000 */   nop
/* 1FA38 8002F238 A327010C */  jal        func_80049E8C
/* 1FA3C 8002F23C 00000000 */   nop
.L8002F240:
/* 1FA40 8002F240 0780033C */  lui        $v1, %hi(D_8007593C)
/* 1FA44 8002F244 3C59638C */  lw         $v1, %lo(D_8007593C)($v1)
/* 1FA48 8002F248 00000000 */  nop
/* 1FA4C 8002F24C 74016228 */  slti       $v0, $v1, 0x174
/* 1FA50 8002F250 26004014 */  bnez       $v0, .L8002F2EC
/* 1FA54 8002F254 74010224 */   addiu     $v0, $zero, 0x174
/* 1FA58 8002F258 0E006214 */  bne        $v1, $v0, .L8002F294
/* 1FA5C 8002F25C F8260224 */   addiu     $v0, $zero, 0x26F8
/* 1FA60 8002F260 0E000224 */  addiu      $v0, $zero, 0xE
/* 1FA64 8002F264 0880013C */  lui        $at, %hi(g_Spyro + 0x18)
/* 1FA68 8002F268 708A22A0 */  sb         $v0, %lo(g_Spyro + 0x18)($at)
/* 1FA6C 8002F26C 0880013C */  lui        $at, %hi(g_Spyro + 0x19)
/* 1FA70 8002F270 718A22A0 */  sb         $v0, %lo(g_Spyro + 0x19)($at)
/* 1FA74 8002F274 01000224 */  addiu      $v0, $zero, 0x1
/* 1FA78 8002F278 0880013C */  lui        $at, %hi(g_Spyro + 0x1E)
/* 1FA7C 8002F27C 768A20A0 */  sb         $zero, %lo(g_Spyro + 0x1E)($at)
/* 1FA80 8002F280 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 1FA84 8002F284 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 1FA88 8002F288 0880013C */  lui        $at, %hi(g_Spyro + 0x24)
/* 1FA8C 8002F28C 7C8A20A0 */  sb         $zero, %lo(g_Spyro + 0x24)($at)
/* 1FA90 8002F290 F8260224 */  addiu      $v0, $zero, 0x26F8
.L8002F294:
/* 1FA94 8002F294 0880013C */  lui        $at, %hi(g_Spyro)
/* 1FA98 8002F298 588A22AC */  sw         $v0, %lo(g_Spyro)($at)
/* 1FA9C 8002F29C 00090224 */  addiu      $v0, $zero, 0x900
/* 1FAA0 8002F2A0 0880013C */  lui        $at, %hi(g_Spyro + 0x4)
/* 1FAA4 8002F2A4 5C8A22AC */  sw         $v0, %lo(g_Spyro + 0x4)($at)
/* 1FAA8 8002F2A8 C4060224 */  addiu      $v0, $zero, 0x6C4
/* 1FAAC 8002F2AC 0880013C */  lui        $at, %hi(g_Spyro + 0x8)
/* 1FAB0 8002F2B0 608A22AC */  sw         $v0, %lo(g_Spyro + 0x8)($at)
/* 1FAB4 8002F2B4 F6000224 */  addiu      $v0, $zero, 0xF6
/* 1FAB8 8002F2B8 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 1FABC 8002F2BC 658A22A0 */  sb         $v0, %lo(g_Spyro + 0xD)($at)
/* 1FAC0 8002F2C0 E0000224 */  addiu      $v0, $zero, 0xE0
/* 1FAC4 8002F2C4 0880013C */  lui        $at, %hi(g_Spyro + 0xC)
/* 1FAC8 8002F2C8 648A20A0 */  sb         $zero, %lo(g_Spyro + 0xC)($at)
/* 1FACC 8002F2CC 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 1FAD0 8002F2D0 668A22A0 */  sb         $v0, %lo(g_Spyro + 0xE)($at)
/* 1FAD4 8002F2D4 C9F2000C */  jal        func_8003CB24
/* 1FAD8 8002F2D8 03000424 */   addiu     $a0, $zero, 0x3
/* 1FADC 8002F2DC 9825010C */  jal        func_80049660
/* 1FAE0 8002F2E0 00000000 */   nop
/* 1FAE4 8002F2E4 A327010C */  jal        func_80049E8C
/* 1FAE8 8002F2E8 00000000 */   nop
.L8002F2EC:
/* 1FAEC 8002F2EC 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 1FAF0 8002F2F0 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 1FAF4 8002F2F4 00000000 */  nop
/* 1FAF8 8002F2F8 0B004228 */  slti       $v0, $v0, 0xB
/* 1FAFC 8002F2FC 05004010 */  beqz       $v0, .L8002F314
/* 1FB00 8002F300 00000000 */   nop
/* 1FB04 8002F304 DC54000C */  jal        func_80015370
/* 1FB08 8002F308 01000424 */   addiu     $a0, $zero, 0x1
/* 1FB0C 8002F30C E9BC0008 */  j          .L8002F3A4
/* 1FB10 8002F310 00000000 */   nop
.L8002F314:
/* 1FB14 8002F314 0780023C */  lui        $v0, %hi(D_8007593C)
/* 1FB18 8002F318 3C59428C */  lw         $v0, %lo(D_8007593C)($v0)
/* 1FB1C 8002F31C 00000000 */  nop
/* 1FB20 8002F320 69014228 */  slti       $v0, $v0, 0x169
/* 1FB24 8002F324 1F004014 */  bnez       $v0, .L8002F3A4
/* 1FB28 8002F328 00000000 */   nop
/* 1FB2C 8002F32C 0780023C */  lui        $v0, %hi(g_Pad + 0x8)
/* 1FB30 8002F330 8073428C */  lw         $v0, %lo(g_Pad + 0x8)($v0)
/* 1FB34 8002F334 00000000 */  nop
/* 1FB38 8002F338 00084230 */  andi       $v0, $v0, 0x800
/* 1FB3C 8002F33C 19004010 */  beqz       $v0, .L8002F3A4
/* 1FB40 8002F340 00000000 */   nop
/* 1FB44 8002F344 72FF000C */  jal        func_8003FDC8
/* 1FB48 8002F348 21200000 */   addu      $a0, $zero, $zero
/* 1FB4C 8002F34C 02000224 */  addiu      $v0, $zero, 0x2
.L8002F350:
/* 1FB50 8002F350 0780013C */  lui        $at, %hi(D_80075940)
/* 1FB54 8002F354 405922AC */  sw         $v0, %lo(D_80075940)($at)
/* 1FB58 8002F358 0780013C */  lui        $at, %hi(D_8007593C)
/* 1FB5C 8002F35C 3C5920AC */  sw         $zero, %lo(D_8007593C)($at)
/* 1FB60 8002F360 E9BC0008 */  j          .L8002F3A4
/* 1FB64 8002F364 00000000 */   nop
.L8002F368:
/* 1FB68 8002F368 0780023C */  lui        $v0, %hi(D_8007593C)
/* 1FB6C 8002F36C 3C59428C */  lw         $v0, %lo(D_8007593C)($v0)
/* 1FB70 8002F370 00000000 */  nop
/* 1FB74 8002F374 11004228 */  slti       $v0, $v0, 0x11
/* 1FB78 8002F378 0A004014 */  bnez       $v0, .L8002F3A4
/* 1FB7C 8002F37C 00000000 */   nop
/* 1FB80 8002F380 DC54000C */  jal        func_80015370
/* 1FB84 8002F384 01000424 */   addiu     $a0, $zero, 0x1
/* 1FB88 8002F388 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 1FB8C 8002F38C 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 1FB90 8002F390 00000000 */  nop
/* 1FB94 8002F394 03004104 */  bgez       $v0, .L8002F3A4
/* 1FB98 8002F398 00000000 */   nop
/* 1FB9C 8002F39C 29B2000C */  jal        func_8002C8A4
/* 1FBA0 8002F3A0 00000000 */   nop
.L8002F3A4:
/* 1FBA4 8002F3A4 4800BF8F */  lw         $ra, 0x48($sp)
/* 1FBA8 8002F3A8 4400B38F */  lw         $s3, 0x44($sp)
/* 1FBAC 8002F3AC 4000B28F */  lw         $s2, 0x40($sp)
/* 1FBB0 8002F3B0 3C00B18F */  lw         $s1, 0x3C($sp)
/* 1FBB4 8002F3B4 3800B08F */  lw         $s0, 0x38($sp)
/* 1FBB8 8002F3B8 5000BD27 */  addiu      $sp, $sp, 0x50
/* 1FBBC 8002F3BC 0800E003 */  jr         $ra
/* 1FBC0 8002F3C0 00000000 */   nop
.size func_8002EDF0, . - func_8002EDF0
