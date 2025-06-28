.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8001CFDC
/* D7DC 8001CFDC D8FFBD27 */  addiu      $sp, $sp, -0x28
/* D7E0 8001CFE0 0780053C */  lui        $a1, %hi(D_80076248)
/* D7E4 8001CFE4 4862A524 */  addiu      $a1, $a1, %lo(D_80076248)
/* D7E8 8001CFE8 2400BFAF */  sw         $ra, 0x24($sp)
/* D7EC 8001CFEC 2000B0AF */  sw         $s0, 0x20($sp)
/* D7F0 8001CFF0 0000A28C */  lw         $v0, 0x0($a1)
/* D7F4 8001CFF4 00000000 */  nop
/* D7F8 8001CFF8 07004010 */  beqz       $v0, .L8001D018
/* D7FC 8001CFFC 2800A424 */   addiu     $a0, $a1, 0x28
/* D800 8001D000 0780063C */  lui        $a2, %hi(g_Camera)
/* D804 8001D004 D06DC624 */  addiu      $a2, $a2, %lo(g_Camera)
/* D808 8001D008 4B5B000C */  jal        RotVec8ToMatrix
/* D80C 8001D00C 1000A524 */   addiu     $a1, $a1, 0x10
/* D810 8001D010 1962010C */  jal        func_80058864
/* D814 8001D014 00000000 */   nop
.L8001D018:
/* D818 8001D018 0780043C */  lui        $a0, %hi(D_80077058)
/* D81C 8001D01C 5870848C */  lw         $a0, %lo(D_80077058)($a0)
/* D820 8001D020 00000000 */  nop
/* D824 8001D024 15008014 */  bnez       $a0, .L8001D07C
/* D828 8001D028 04008228 */   slti      $v0, $a0, 0x4
/* D82C 8001D02C 7048010C */  jal        func_800521C0
/* D830 8001D030 00000000 */   nop
/* D834 8001D034 A665000C */  jal        func_80019698
/* D838 8001D038 00000000 */   nop
/* D83C 8001D03C 73AE000C */  jal        func_8002B9CC
/* D840 8001D040 00000000 */   nop
/* D844 8001D044 F442010C */  jal        func_80050BD0
/* D848 8001D048 00000000 */   nop
/* D84C 8001D04C F25C010C */  jal        func_800573C8
/* D850 8001D050 00000000 */   nop
/* D854 8001D054 0780053C */  lui        $a1, %hi(D_80077074)
/* D858 8001D058 7470A58C */  lw         $a1, %lo(D_80077074)($a1)
/* D85C 8001D05C 00000000 */  nop
/* D860 8001D060 1D01A010 */  beqz       $a1, .L8001D4D8
/* D864 8001D064 01000424 */   addiu     $a0, $zero, 0x1
/* D868 8001D068 2130A000 */  addu       $a2, $a1, $zero
/* D86C 8001D06C 3564000C */  jal        func_800190D4
/* D870 8001D070 2138A000 */   addu      $a3, $a1, $zero
/* D874 8001D074 36750008 */  j          .L8001D4D8
/* D878 8001D078 00000000 */   nop
.L8001D07C:
/* D87C 8001D07C 52004010 */  beqz       $v0, .L8001D1C8
/* D880 8001D080 04000224 */   addiu     $v0, $zero, 0x4
/* D884 8001D084 0780053C */  lui        $a1, %hi(D_800770C0)
/* D888 8001D088 C070A58C */  lw         $a1, %lo(D_800770C0)($a1)
/* D88C 8001D08C 00000000 */  nop
/* D890 8001D090 4800A290 */  lbu        $v0, 0x48($a1)
/* D894 8001D094 0780033C */  lui        $v1, %hi(D_8006FCF4)
/* D898 8001D098 F4FC6324 */  addiu      $v1, $v1, %lo(D_8006FCF4)
/* D89C 8001D09C 8000422C */  sltiu      $v0, $v0, 0x80
/* D8A0 8001D0A0 03004010 */  beqz       $v0, .L8001D0B0
/* D8A4 8001D0A4 03000224 */   addiu     $v0, $zero, 0x3
/* D8A8 8001D0A8 000065AC */  sw         $a1, 0x0($v1)
/* D8AC 8001D0AC 04006324 */  addiu      $v1, $v1, 0x4
.L8001D0B0:
/* D8B0 8001D0B0 06008214 */  bne        $a0, $v0, .L8001D0CC
/* D8B4 8001D0B4 00000000 */   nop
/* D8B8 8001D0B8 0780023C */  lui        $v0, %hi(D_800770B8)
/* D8BC 8001D0BC B870428C */  lw         $v0, %lo(D_800770B8)($v0)
/* D8C0 8001D0C0 00000000 */  nop
/* D8C4 8001D0C4 000062AC */  sw         $v0, 0x0($v1)
/* D8C8 8001D0C8 04006324 */  addiu      $v1, $v1, 0x4
.L8001D0CC:
/* D8CC 8001D0CC 000060AC */  sw         $zero, 0x0($v1)
/* D8D0 8001D0D0 0780053C */  lui        $a1, %hi(D_80075828)
/* D8D4 8001D0D4 2858A58C */  lw         $a1, %lo(D_80075828)($a1)
/* D8D8 8001D0D8 0780063C */  lui        $a2, %hi(D_8006FCF4 + 0x2400)
/* D8DC 8001D0DC F420C624 */  addiu      $a2, $a2, %lo(D_8006FCF4 + 0x2400)
/* D8E0 8001D0E0 4800A490 */  lbu        $a0, 0x48($a1)
/* D8E4 8001D0E4 FF000224 */  addiu      $v0, $zero, 0xFF
/* D8E8 8001D0E8 FF008330 */  andi       $v1, $a0, 0xFF
/* D8EC 8001D0EC 11006210 */  beq        $v1, $v0, .L8001D134
/* D8F0 8001D0F0 FB000824 */   addiu     $t0, $zero, 0xFB
/* D8F4 8001D0F4 FF000724 */  addiu      $a3, $zero, 0xFF
/* D8F8 8001D0F8 4800A324 */  addiu      $v1, $a1, 0x48
.L8001D0FC:
/* D8FC 8001D0FC EEFF6284 */  lh         $v0, -0x12($v1)
/* D900 8001D100 00000000 */  nop
/* D904 8001D104 06004814 */  bne        $v0, $t0, .L8001D120
/* D908 8001D108 FF008230 */   andi      $v0, $a0, 0xFF
/* D90C 8001D10C 8000422C */  sltiu      $v0, $v0, 0x80
/* D910 8001D110 03004010 */  beqz       $v0, .L8001D120
/* D914 8001D114 00000000 */   nop
/* D918 8001D118 0000C5AC */  sw         $a1, 0x0($a2)
/* D91C 8001D11C 0400C624 */  addiu      $a2, $a2, 0x4
.L8001D120:
/* D920 8001D120 58006324 */  addiu      $v1, $v1, 0x58
/* D924 8001D124 00006490 */  lbu        $a0, 0x0($v1)
/* D928 8001D128 00000000 */  nop
/* D92C 8001D12C F3FF8714 */  bne        $a0, $a3, .L8001D0FC
/* D930 8001D130 5800A524 */   addiu     $a1, $a1, 0x58
.L8001D134:
/* D934 8001D134 CA61000C */  jal        func_80018728
/* D938 8001D138 0000C0AC */   sw        $zero, 0x0($a2)
/* D93C 8001D13C 2062000C */  jal        func_80018880
/* D940 8001D140 00000000 */   nop
/* D944 8001D144 567C000C */  jal        func_8001F158
/* D948 8001D148 00000000 */   nop
/* D94C 8001D14C 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* D950 8001D150 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* D954 8001D154 21280000 */  addu       $a1, $zero, $zero
/* D958 8001D158 455A000C */  jal        Memset
/* D95C 8001D15C 00090624 */   addiu     $a2, $zero, 0x900
/* D960 8001D160 E67D000C */  jal        func_8001F798
/* D964 8001D164 00000000 */   nop
/* D968 8001D168 8B8A000C */  jal        func_80022A2C
/* D96C 8001D16C 00000000 */   nop
/* D970 8001D170 E367010C */  jal        func_80059F8C
/* D974 8001D174 00000000 */   nop
/* D978 8001D178 B18E000C */  jal        func_80023AC4
/* D97C 8001D17C 00000000 */   nop
/* D980 8001D180 9266010C */  jal        func_80059A48
/* D984 8001D184 00000000 */   nop
/* D988 8001D188 73AE000C */  jal        func_8002B9CC
/* D98C 8001D18C 00000000 */   nop
/* D990 8001D190 F442010C */  jal        func_80050BD0
/* D994 8001D194 00000000 */   nop
/* D998 8001D198 F25C010C */  jal        func_800573C8
/* D99C 8001D19C 00000000 */   nop
/* D9A0 8001D1A0 0780053C */  lui        $a1, %hi(D_80077074)
/* D9A4 8001D1A4 7470A58C */  lw         $a1, %lo(D_80077074)($a1)
/* D9A8 8001D1A8 00000000 */  nop
/* D9AC 8001D1AC CA00A010 */  beqz       $a1, .L8001D4D8
/* D9B0 8001D1B0 01000424 */   addiu     $a0, $zero, 0x1
/* D9B4 8001D1B4 2130A000 */  addu       $a2, $a1, $zero
/* D9B8 8001D1B8 3564000C */  jal        func_800190D4
/* D9BC 8001D1BC 2138A000 */   addu      $a3, $a1, $zero
/* D9C0 8001D1C0 36750008 */  j          .L8001D4D8
/* D9C4 8001D1C4 00000000 */   nop
.L8001D1C8:
/* D9C8 8001D1C8 3F008214 */  bne        $a0, $v0, .L8001D2C8
/* D9CC 8001D1CC 05000224 */   addiu     $v0, $zero, 0x5
/* D9D0 8001D1D0 0780033C */  lui        $v1, %hi(D_800770B8)
/* D9D4 8001D1D4 B870638C */  lw         $v1, %lo(D_800770B8)($v1)
/* D9D8 8001D1D8 0780023C */  lui        $v0, %hi(D_8006FCF4)
/* D9DC 8001D1DC F4FC4224 */  addiu      $v0, $v0, %lo(D_8006FCF4)
/* D9E0 8001D1E0 000043AC */  sw         $v1, 0x0($v0)
/* D9E4 8001D1E4 0780033C */  lui        $v1, %hi(D_800770BC)
/* D9E8 8001D1E8 BC70638C */  lw         $v1, %lo(D_800770BC)($v1)
/* D9EC 8001D1EC 04004224 */  addiu      $v0, $v0, 0x4
/* D9F0 8001D1F0 000043AC */  sw         $v1, 0x0($v0)
/* D9F4 8001D1F4 04004224 */  addiu      $v0, $v0, 0x4
/* D9F8 8001D1F8 000040AC */  sw         $zero, 0x0($v0)
/* D9FC 8001D1FC 0780053C */  lui        $a1, %hi(D_80075828)
/* DA00 8001D200 2858A58C */  lw         $a1, %lo(D_80075828)($a1)
/* DA04 8001D204 F8234624 */  addiu      $a2, $v0, 0x23F8
/* DA08 8001D208 4800A490 */  lbu        $a0, 0x48($a1)
/* DA0C 8001D20C FF000224 */  addiu      $v0, $zero, 0xFF
/* DA10 8001D210 FF008330 */  andi       $v1, $a0, 0xFF
/* DA14 8001D214 12006210 */  beq        $v1, $v0, .L8001D260
/* DA18 8001D218 00000000 */   nop
/* DA1C 8001D21C FB000824 */  addiu      $t0, $zero, 0xFB
/* DA20 8001D220 FF000724 */  addiu      $a3, $zero, 0xFF
/* DA24 8001D224 4800A324 */  addiu      $v1, $a1, 0x48
.L8001D228:
/* DA28 8001D228 EEFF6284 */  lh         $v0, -0x12($v1)
/* DA2C 8001D22C 00000000 */  nop
/* DA30 8001D230 06004814 */  bne        $v0, $t0, .L8001D24C
/* DA34 8001D234 FF008230 */   andi      $v0, $a0, 0xFF
/* DA38 8001D238 8000422C */  sltiu      $v0, $v0, 0x80
/* DA3C 8001D23C 03004010 */  beqz       $v0, .L8001D24C
/* DA40 8001D240 00000000 */   nop
/* DA44 8001D244 0000C5AC */  sw         $a1, 0x0($a2)
/* DA48 8001D248 0400C624 */  addiu      $a2, $a2, 0x4
.L8001D24C:
/* DA4C 8001D24C 58006324 */  addiu      $v1, $v1, 0x58
/* DA50 8001D250 00006490 */  lbu        $a0, 0x0($v1)
/* DA54 8001D254 00000000 */  nop
/* DA58 8001D258 F3FF8714 */  bne        $a0, $a3, .L8001D228
/* DA5C 8001D25C 5800A524 */   addiu     $a1, $a1, 0x58
.L8001D260:
/* DA60 8001D260 0000C0AC */  sw         $zero, 0x0($a2)
/* DA64 8001D264 0780023C */  lui        $v0, %hi(D_8007706C)
/* DA68 8001D268 6C70428C */  lw         $v0, %lo(D_8007706C)($v0)
/* DA6C 8001D26C 00000000 */  nop
/* DA70 8001D270 3C004228 */  slti       $v0, $v0, 0x3C
/* DA74 8001D274 05004010 */  beqz       $v0, .L8001D28C
/* DA78 8001D278 00000000 */   nop
/* DA7C 8001D27C CA61000C */  jal        func_80018728
/* DA80 8001D280 00000000 */   nop
/* DA84 8001D284 2062000C */  jal        func_80018880
/* DA88 8001D288 00000000 */   nop
.L8001D28C:
/* DA8C 8001D28C 567C000C */  jal        func_8001F158
/* DA90 8001D290 00000000 */   nop
/* DA94 8001D294 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* DA98 8001D298 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* DA9C 8001D29C 21280000 */  addu       $a1, $zero, $zero
/* DAA0 8001D2A0 455A000C */  jal        Memset
/* DAA4 8001D2A4 00090624 */   addiu     $a2, $zero, 0x900
/* DAA8 8001D2A8 E67D000C */  jal        func_8001F798
/* DAAC 8001D2AC 00000000 */   nop
/* DAB0 8001D2B0 8B8A000C */  jal        func_80022A2C
/* DAB4 8001D2B4 00000000 */   nop
/* DAB8 8001D2B8 E367010C */  jal        func_80059F8C
/* DABC 8001D2BC 00000000 */   nop
/* DAC0 8001D2C0 2E750008 */  j          .L8001D4B8
/* DAC4 8001D2C4 00000000 */   nop
.L8001D2C8:
/* DAC8 8001D2C8 64008214 */  bne        $a0, $v0, .L8001D45C
/* DACC 8001D2CC 06000224 */   addiu     $v0, $zero, 0x6
/* DAD0 8001D2D0 0780023C */  lui        $v0, %hi(D_8006FCF4)
/* DAD4 8001D2D4 F4FC4224 */  addiu      $v0, $v0, %lo(D_8006FCF4)
/* DAD8 8001D2D8 21280000 */  addu       $a1, $zero, $zero
/* DADC 8001D2DC 0780033C */  lui        $v1, %hi(D_800770B8)
/* DAE0 8001D2E0 B870638C */  lw         $v1, %lo(D_800770B8)($v1)
/* DAE4 8001D2E4 0880043C */  lui        $a0, %hi(D_800781A4)
/* DAE8 8001D2E8 A4818424 */  addiu      $a0, $a0, %lo(D_800781A4)
/* DAEC 8001D2EC 000043AC */  sw         $v1, 0x0($v0)
/* DAF0 8001D2F0 04004224 */  addiu      $v0, $v0, 0x4
/* DAF4 8001D2F4 FC234324 */  addiu      $v1, $v0, 0x23FC
/* DAF8 8001D2F8 000040AC */  sw         $zero, 0x0($v0)
.L8001D2FC:
/* DAFC 8001D2FC 000064AC */  sw         $a0, 0x0($v1)
/* DB00 8001D300 04006324 */  addiu      $v1, $v1, 0x4
/* DB04 8001D304 0100A524 */  addiu      $a1, $a1, 0x1
/* DB08 8001D308 0300A228 */  slti       $v0, $a1, 0x3
/* DB0C 8001D30C FBFF4014 */  bnez       $v0, .L8001D2FC
/* DB10 8001D310 58008424 */   addiu     $a0, $a0, 0x58
/* DB14 8001D314 567C000C */  jal        func_8001F158
/* DB18 8001D318 000060AC */   sw        $zero, 0x0($v1)
/* DB1C 8001D31C 0780023C */  lui        $v0, %hi(D_8006FCF4 + 0x1600)
/* DB20 8001D320 F412428C */  lw         $v0, %lo(D_8006FCF4 + 0x1600)($v0)
/* DB24 8001D324 00000000 */  nop
/* DB28 8001D328 43004010 */  beqz       $v0, .L8001D438
/* DB2C 8001D32C 00000000 */   nop
/* DB30 8001D330 0780023C */  lui        $v0, %hi(D_8007706C)
/* DB34 8001D334 6C70428C */  lw         $v0, %lo(D_8007706C)($v0)
/* DB38 8001D338 00000000 */  nop
/* DB3C 8001D33C 40100200 */  sll        $v0, $v0, 1
/* DB40 8001D340 0780013C */  lui        $at, %hi(D_8006F3C0)
/* DB44 8001D344 21082200 */  addu       $at, $at, $v0
/* DB48 8001D348 C0F32484 */  lh         $a0, %lo(D_8006F3C0)($at)
/* DB4C 8001D34C 0780023C */  lui        $v0, %hi(D_8006FCF4 + 0x161c)
/* DB50 8001D350 10134284 */  lh         $v0, %lo(D_8006FCF4 + 0x161c)($v0)
/* DB54 8001D354 00000000 */  nop
/* DB58 8001D358 18004400 */  mult       $v0, $a0
/* DB5C 8001D35C 12400000 */  mflo       $t0
/* DB60 8001D360 0780023C */  lui        $v0, %hi(D_8006FCF4 + 0x161e)
/* DB64 8001D364 12134284 */  lh         $v0, %lo(D_8006FCF4 + 0x161e)($v0)
/* DB68 8001D368 00000000 */  nop
/* DB6C 8001D36C 18004400 */  mult       $v0, $a0
/* DB70 8001D370 12180000 */  mflo       $v1
/* DB74 8001D374 0780023C */  lui        $v0, %hi(D_8006FCF4 + 0x1620)
/* DB78 8001D378 14134284 */  lh         $v0, %lo(D_8006FCF4 + 0x1620)($v0)
/* DB7C 8001D37C 00000000 */  nop
/* DB80 8001D380 18004400 */  mult       $v0, $a0
/* DB84 8001D384 03130800 */  sra        $v0, $t0, 12
/* DB88 8001D388 0780013C */  lui        $at, %hi(D_8006FCF4 + 0x161c)
/* DB8C 8001D38C 101322A4 */  sh         $v0, %lo(D_8006FCF4 + 0x161c)($at)
/* DB90 8001D390 03130300 */  sra        $v0, $v1, 12
/* DB94 8001D394 0780033C */  lui        $v1, %hi(D_8007706C)
/* DB98 8001D398 6C70638C */  lw         $v1, %lo(D_8007706C)($v1)
/* DB9C 8001D39C 0780013C */  lui        $at, %hi(D_8006FCF4 + 0x161e)
/* DBA0 8001D3A0 121322A4 */  sh         $v0, %lo(D_8006FCF4 + 0x161e)($at)
/* DBA4 8001D3A4 12200000 */  mflo       $a0
/* DBA8 8001D3A8 03130400 */  sra        $v0, $a0, 12
/* DBAC 8001D3AC 0780013C */  lui        $at, %hi(D_8006FCF4 + 0x1620)
/* DBB0 8001D3B0 141322A4 */  sh         $v0, %lo(D_8006FCF4 + 0x1620)($at)
/* DBB4 8001D3B4 09006228 */  slti       $v0, $v1, 0x9
/* DBB8 8001D3B8 1F004014 */  bnez       $v0, .L8001D438
/* DBBC 8001D3BC F8FF6224 */   addiu     $v0, $v1, -0x8
/* DBC0 8001D3C0 80200200 */  sll        $a0, $v0, 2
/* DBC4 8001D3C4 21208200 */  addu       $a0, $a0, $v0
/* DBC8 8001D3C8 80200400 */  sll        $a0, $a0, 2
/* DBCC 8001D3CC 21208200 */  addu       $a0, $a0, $v0
/* DBD0 8001D3D0 2C5B000C */  jal        Cos
/* DBD4 8001D3D4 40200400 */   sll       $a0, $a0, 1
/* DBD8 8001D3D8 0780033C */  lui        $v1, %hi(D_8006FCF4 + 0x1622)
/* DBDC 8001D3DC 16136384 */  lh         $v1, %lo(D_8006FCF4 + 0x1622)($v1)
/* DBE0 8001D3E0 21204000 */  addu       $a0, $v0, $zero
/* DBE4 8001D3E4 18006400 */  mult       $v1, $a0
/* DBE8 8001D3E8 12400000 */  mflo       $t0
/* DBEC 8001D3EC 0780023C */  lui        $v0, %hi(D_8006FCF4 + 0x1624)
/* DBF0 8001D3F0 18134284 */  lh         $v0, %lo(D_8006FCF4 + 0x1624)($v0)
/* DBF4 8001D3F4 00000000 */  nop
/* DBF8 8001D3F8 18004400 */  mult       $v0, $a0
/* DBFC 8001D3FC 12180000 */  mflo       $v1
/* DC00 8001D400 0780023C */  lui        $v0, %hi(D_8006FCF4 + 0x1626)
/* DC04 8001D404 1A134284 */  lh         $v0, %lo(D_8006FCF4 + 0x1626)($v0)
/* DC08 8001D408 00000000 */  nop
/* DC0C 8001D40C 18004400 */  mult       $v0, $a0
/* DC10 8001D410 03130800 */  sra        $v0, $t0, 12
/* DC14 8001D414 0780013C */  lui        $at, %hi(D_8006FCF4 + 0x1622)
/* DC18 8001D418 161322A4 */  sh         $v0, %lo(D_8006FCF4 + 0x1622)($at)
/* DC1C 8001D41C 03130300 */  sra        $v0, $v1, 12
/* DC20 8001D420 0780013C */  lui        $at, %hi(D_8006FCF4 + 0x1624)
/* DC24 8001D424 181322A4 */  sh         $v0, %lo(D_8006FCF4 + 0x1624)($at)
/* DC28 8001D428 12200000 */  mflo       $a0
/* DC2C 8001D42C 03130400 */  sra        $v0, $a0, 12
/* DC30 8001D430 0780013C */  lui        $at, %hi(D_8006FCF4 + 0x1626)
/* DC34 8001D434 1A1322A4 */  sh         $v0, %lo(D_8006FCF4 + 0x1626)($at)
.L8001D438:
/* DC38 8001D438 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* DC3C 8001D43C F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* DC40 8001D440 21280000 */  addu       $a1, $zero, $zero
/* DC44 8001D444 455A000C */  jal        Memset
/* DC48 8001D448 00090624 */   addiu     $a2, $zero, 0x900
/* DC4C 8001D44C E67D000C */  jal        func_8001F798
/* DC50 8001D450 00000000 */   nop
/* DC54 8001D454 2A750008 */  j          .L8001D4A8
/* DC58 8001D458 00000000 */   nop
.L8001D45C:
/* DC5C 8001D45C 2C008214 */  bne        $a0, $v0, .L8001D510
/* DC60 8001D460 07000224 */   addiu     $v0, $zero, 0x7
/* DC64 8001D464 0780073C */  lui        $a3, %hi(D_8006FCF4 + 0x2400)
/* DC68 8001D468 F420E724 */  addiu      $a3, $a3, %lo(D_8006FCF4 + 0x2400)
/* DC6C 8001D46C 21200000 */  addu       $a0, $zero, $zero
/* DC70 8001D470 0880033C */  lui        $v1, %hi(D_800781A4)
/* DC74 8001D474 A4816324 */  addiu      $v1, $v1, %lo(D_800781A4)
.L8001D478:
/* DC78 8001D478 0000E3AC */  sw         $v1, 0x0($a3)
/* DC7C 8001D47C 0400E724 */  addiu      $a3, $a3, 0x4
/* DC80 8001D480 01008424 */  addiu      $a0, $a0, 0x1
/* DC84 8001D484 03008228 */  slti       $v0, $a0, 0x3
/* DC88 8001D488 FBFF4014 */  bnez       $v0, .L8001D478
/* DC8C 8001D48C 58006324 */   addiu     $v1, $v1, 0x58
/* DC90 8001D490 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* DC94 8001D494 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* DC98 8001D498 21280000 */  addu       $a1, $zero, $zero
/* DC9C 8001D49C 00090624 */  addiu      $a2, $zero, 0x900
/* DCA0 8001D4A0 455A000C */  jal        Memset
/* DCA4 8001D4A4 0000E0AC */   sw        $zero, 0x0($a3)
.L8001D4A8:
/* DCA8 8001D4A8 8B8A000C */  jal        func_80022A2C
/* DCAC 8001D4AC 00000000 */   nop
/* DCB0 8001D4B0 B18E000C */  jal        func_80023AC4
/* DCB4 8001D4B4 00000000 */   nop
.L8001D4B8:
/* DCB8 8001D4B8 9266010C */  jal        func_80059A48
/* DCBC 8001D4BC 00000000 */   nop
/* DCC0 8001D4C0 73AE000C */  jal        func_8002B9CC
/* DCC4 8001D4C4 00000000 */   nop
/* DCC8 8001D4C8 F442010C */  jal        func_80050BD0
/* DCCC 8001D4CC 00000000 */   nop
/* DCD0 8001D4D0 F25C010C */  jal        func_800573C8
/* DCD4 8001D4D4 00000000 */   nop
.L8001D4D8:
/* DCD8 8001D4D8 0780023C */  lui        $v0, %hi(D_8007570C)
/* DCDC 8001D4DC 0C57428C */  lw         $v0, %lo(D_8007570C)($v0)
/* DCE0 8001D4E0 00000000 */  nop
/* DCE4 8001D4E4 06004014 */  bnez       $v0, .L8001D500
/* DCE8 8001D4E8 00000000 */   nop
/* DCEC 8001D4EC 0780023C */  lui        $v0, %hi(D_800756C0)
/* DCF0 8001D4F0 C056428C */  lw         $v0, %lo(D_800756C0)($v0)
/* DCF4 8001D4F4 00000000 */  nop
/* DCF8 8001D4F8 52004010 */  beqz       $v0, .L8001D644
/* DCFC 8001D4FC 00000000 */   nop
.L8001D500:
/* DD00 8001D500 CC63000C */  jal        func_80018F30
/* DD04 8001D504 00000000 */   nop
/* DD08 8001D508 91750008 */  j          .L8001D644
/* DD0C 8001D50C 00000000 */   nop
.L8001D510:
/* DD10 8001D510 4C008214 */  bne        $a0, $v0, .L8001D644
/* DD14 8001D514 00000000 */   nop
/* DD18 8001D518 0780023C */  lui        $v0, %hi(D_8007706C)
/* DD1C 8001D51C 6C70428C */  lw         $v0, %lo(D_8007706C)($v0)
/* DD20 8001D520 00000000 */  nop
/* DD24 8001D524 10004228 */  slti       $v0, $v0, 0x10
/* DD28 8001D528 15004010 */  beqz       $v0, .L8001D580
/* DD2C 8001D52C 21280000 */   addu      $a1, $zero, $zero
/* DD30 8001D530 0780033C */  lui        $v1, %hi(D_8006FCF4 + 0x2400)
/* DD34 8001D534 F4206324 */  addiu      $v1, $v1, %lo(D_8006FCF4 + 0x2400)
/* DD38 8001D538 0880043C */  lui        $a0, %hi(D_800781A4)
/* DD3C 8001D53C A4818424 */  addiu      $a0, $a0, %lo(D_800781A4)
.L8001D540:
/* DD40 8001D540 000064AC */  sw         $a0, 0x0($v1)
/* DD44 8001D544 04006324 */  addiu      $v1, $v1, 0x4
/* DD48 8001D548 0100A524 */  addiu      $a1, $a1, 0x1
/* DD4C 8001D54C 0300A228 */  slti       $v0, $a1, 0x3
/* DD50 8001D550 FBFF4014 */  bnez       $v0, .L8001D540
/* DD54 8001D554 58008424 */   addiu     $a0, $a0, 0x58
/* DD58 8001D558 000060AC */  sw         $zero, 0x0($v1)
/* DD5C 8001D55C 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* DD60 8001D560 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* DD64 8001D564 21280000 */  addu       $a1, $zero, $zero
/* DD68 8001D568 455A000C */  jal        Memset
/* DD6C 8001D56C 00090624 */   addiu     $a2, $zero, 0x900
/* DD70 8001D570 8B8A000C */  jal        func_80022A2C
/* DD74 8001D574 00000000 */   nop
/* DD78 8001D578 73750008 */  j          .L8001D5CC
/* DD7C 8001D57C 00000000 */   nop
.L8001D580:
/* DD80 8001D580 7048010C */  jal        func_800521C0
/* DD84 8001D584 00000000 */   nop
/* DD88 8001D588 567C000C */  jal        func_8001F158
/* DD8C 8001D58C 00000000 */   nop
/* DD90 8001D590 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* DD94 8001D594 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* DD98 8001D598 21280000 */  addu       $a1, $zero, $zero
/* DD9C 8001D59C 455A000C */  jal        Memset
/* DDA0 8001D5A0 00090624 */   addiu     $a2, $zero, 0x900
/* DDA4 8001D5A4 E67D000C */  jal        func_8001F798
/* DDA8 8001D5A8 00000000 */   nop
/* DDAC 8001D5AC 3F82000C */  jal        func_800208FC
/* DDB0 8001D5B0 00000000 */   nop
/* DDB4 8001D5B4 CD83000C */  jal        func_80020F34
/* DDB8 8001D5B8 00000000 */   nop
/* DDBC 8001D5BC 8B8A000C */  jal        func_80022A2C
/* DDC0 8001D5C0 00000000 */   nop
/* DDC4 8001D5C4 E367010C */  jal        func_80059F8C
/* DDC8 8001D5C8 00000000 */   nop
.L8001D5CC:
/* DDCC 8001D5CC B18E000C */  jal        func_80023AC4
/* DDD0 8001D5D0 00000000 */   nop
/* DDD4 8001D5D4 9266010C */  jal        func_80059A48
/* DDD8 8001D5D8 00000000 */   nop
/* DDDC 8001D5DC 73AE000C */  jal        func_8002B9CC
/* DDE0 8001D5E0 00000000 */   nop
/* DDE4 8001D5E4 F442010C */  jal        func_80050BD0
/* DDE8 8001D5E8 00000000 */   nop
/* DDEC 8001D5EC F25C010C */  jal        func_800573C8
/* DDF0 8001D5F0 00000000 */   nop
/* DDF4 8001D5F4 0780023C */  lui        $v0, %hi(D_8007570C)
/* DDF8 8001D5F8 0C57428C */  lw         $v0, %lo(D_8007570C)($v0)
/* DDFC 8001D5FC 00000000 */  nop
/* DE00 8001D600 06004014 */  bnez       $v0, .L8001D61C
/* DE04 8001D604 00000000 */   nop
/* DE08 8001D608 0780023C */  lui        $v0, %hi(D_800756C0)
/* DE0C 8001D60C C056428C */  lw         $v0, %lo(D_800756C0)($v0)
/* DE10 8001D610 00000000 */  nop
/* DE14 8001D614 03004010 */  beqz       $v0, .L8001D624
/* DE18 8001D618 00000000 */   nop
.L8001D61C:
/* DE1C 8001D61C CC63000C */  jal        func_80018F30
/* DE20 8001D620 00000000 */   nop
.L8001D624:
/* DE24 8001D624 0780053C */  lui        $a1, %hi(D_80077074)
/* DE28 8001D628 7470A58C */  lw         $a1, %lo(D_80077074)($a1)
/* DE2C 8001D62C 00000000 */  nop
/* DE30 8001D630 0400A010 */  beqz       $a1, .L8001D644
/* DE34 8001D634 01000424 */   addiu     $a0, $zero, 0x1
/* DE38 8001D638 2130A000 */  addu       $a2, $a1, $zero
/* DE3C 8001D63C 3564000C */  jal        func_800190D4
/* DE40 8001D640 2138A000 */   addu      $a3, $a1, $zero
.L8001D644:
/* DE44 8001D644 D97D010C */  jal        DrawSync
/* DE48 8001D648 21200000 */   addu      $a0, $zero, $zero
/* DE4C 8001D64C 0780023C */  lui        $v0, %hi(D_80075784)
/* DE50 8001D650 8457428C */  lw         $v0, %lo(D_80075784)($v0)
/* DE54 8001D654 00000000 */  nop
/* DE58 8001D658 03004010 */  beqz       $v0, .L8001D668
/* DE5C 8001D65C 00000000 */   nop
/* DE60 8001D660 F176010C */  jal        VSync
/* DE64 8001D664 21200000 */   addu      $a0, $zero, $zero
.L8001D668:
/* DE68 8001D668 F176010C */  jal        VSync
/* DE6C 8001D66C FFFF0424 */   addiu     $a0, $zero, -0x1
/* DE70 8001D670 0780033C */  lui        $v1, %hi(D_80075950)
/* DE74 8001D674 5059638C */  lw         $v1, %lo(D_80075950)($v1)
/* DE78 8001D678 0780013C */  lui        $at, %hi(D_80075954)
/* DE7C 8001D67C 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* DE80 8001D680 23104300 */  subu       $v0, $v0, $v1
/* DE84 8001D684 02004228 */  slti       $v0, $v0, 0x2
/* DE88 8001D688 0E004010 */  beqz       $v0, .L8001D6C4
/* DE8C 8001D68C 00000000 */   nop
/* DE90 8001D690 0780103C */  lui        $s0, %hi(D_80075954)
/* DE94 8001D694 54591026 */  addiu      $s0, $s0, %lo(D_80075954)
.L8001D698:
/* DE98 8001D698 F176010C */  jal        VSync
/* DE9C 8001D69C 21200000 */   addu      $a0, $zero, $zero
/* DEA0 8001D6A0 F176010C */  jal        VSync
/* DEA4 8001D6A4 FFFF0424 */   addiu     $a0, $zero, -0x1
/* DEA8 8001D6A8 FCFF038E */  lw         $v1, -0x4($s0)
/* DEAC 8001D6AC 0780013C */  lui        $at, %hi(D_80075954)
/* DEB0 8001D6B0 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* DEB4 8001D6B4 23104300 */  subu       $v0, $v0, $v1
/* DEB8 8001D6B8 02004228 */  slti       $v0, $v0, 0x2
/* DEBC 8001D6BC F6FF4014 */  bnez       $v0, .L8001D698
/* DEC0 8001D6C0 00000000 */   nop
.L8001D6C4:
/* DEC4 8001D6C4 F176010C */  jal        VSync
/* DEC8 8001D6C8 FFFF0424 */   addiu     $a0, $zero, -0x1
/* DECC 8001D6CC 0780043C */  lui        $a0, %hi(D_80075888)
/* DED0 8001D6D0 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* DED4 8001D6D4 0780013C */  lui        $at, %hi(D_80075950)
/* DED8 8001D6D8 505922AC */  sw         $v0, %lo(D_80075950)($at)
/* DEDC 8001D6DC 0C80010C */  jal        PutDispEnv
/* DEE0 8001D6E0 5C008424 */   addiu     $a0, $a0, 0x5C
/* DEE4 8001D6E4 0780043C */  lui        $a0, %hi(D_80075888)
/* DEE8 8001D6E8 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* DEEC 8001D6EC 767F010C */  jal        PutDrawEnv
/* DEF0 8001D6F0 00000000 */   nop
/* DEF4 8001D6F4 E159000C */  jal        func_80016784
/* DEF8 8001D6F8 00080424 */   addiu     $a0, $zero, 0x800
/* DEFC 8001D6FC 597F010C */  jal        DrawOTag
/* DF00 8001D700 21204000 */   addu      $a0, $v0, $zero
/* DF04 8001D704 2400BF8F */  lw         $ra, 0x24($sp)
/* DF08 8001D708 2000B08F */  lw         $s0, 0x20($sp)
/* DF0C 8001D70C 2800BD27 */  addiu      $sp, $sp, 0x28
/* DF10 8001D710 0800E003 */  jr         $ra
/* DF14 8001D714 00000000 */   nop
.size func_8001CFDC, . - func_8001CFDC
