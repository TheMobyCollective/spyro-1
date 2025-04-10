.include "macro.inc"
.include "c2regs.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Generated by spimdisasm 1.27.0 */

/* Handwritten function */
glabel func_80051FEC
/* 427EC 80051FEC 0780013C */  lui        $at, %hi(D_80077868)
/* 427F0 80051FF0 68782124 */  addiu      $at, $at, %lo(D_80077868)
/* 427F4 80051FF4 20002220 */  addi       $v0, $at, 0x20 /* handwritten instruction */
.L80051FF8:
/* 427F8 80051FF8 000020AC */  sw         $zero, 0x0($at)
/* 427FC 80051FFC 08002120 */  addi       $at, $at, 0x8 /* handwritten instruction */
/* 42800 80052000 FDFF2214 */  bne        $at, $v0, .L80051FF8
/* 42804 80052004 FCFF20AC */   sw        $zero, -0x4($at)
/* 42808 80052008 0780013C */  lui        $at, %hi(D_80075828)
/* 4280C 8005200C 28582124 */  addiu      $at, $at, %lo(D_80075828)
/* 42810 80052010 0000218C */  lw         $at, 0x0($at)
/* 42814 80052014 07800A3C */  lui        $t2, %hi(D_80077868)
/* 42818 80052018 68784A25 */  addiu      $t2, $t2, %lo(D_80077868)
/* 4281C 8005201C 08800D3C */  lui        $t5, %hi(g_Spyro)
/* 42820 80052020 588AAD25 */  addiu      $t5, $t5, %lo(g_Spyro)
/* 42824 80052024 0000AB8D */  lw         $t3, 0x0($t5)
/* 42828 80052028 0400AC8D */  lw         $t4, 0x4($t5)
/* 4282C 8005202C 0800AD8D */  lw         $t5, 0x8($t5)
/* 42830 80052030 07800E3C */  lui        $t6, %hi(D_8006FCF4)
/* 42834 80052034 F4FCCE25 */  addiu      $t6, $t6, %lo(D_8006FCF4)
/* 42838 80052038 0004CE21 */  addi       $t6, $t6, 0x400 /* handwritten instruction */
/* 4283C 8005203C A8FF2120 */  addi       $at, $at, -0x58 /* handwritten instruction */
.L80052040:
/* 42840 80052040 58002120 */  addi       $at, $at, 0x58 /* handwritten instruction */
/* 42844 80052044 48002280 */  lb         $v0, 0x48($at)
/* 42848 80052048 51002380 */  lb         $v1, 0x51($at)
/* 4284C 8005204C 37004004 */  bltz       $v0, .L8005212C
/* 42850 80052050 00000000 */   nop
/* 42854 80052054 09006010 */  beqz       $v1, .L8005207C
/* 42858 80052058 43002280 */   lb        $v0, 0x43($at)
/* 4285C 8005205C 0000C1AD */  sw         $at, 0x0($t6)
/* 42860 80052060 F7FF4004 */  bltz       $v0, .L80052040
/* 42864 80052064 0400CE21 */   addi      $t6, $t6, 0x4 /* handwritten instruction */
/* 42868 80052068 20104A00 */  add        $v0, $v0, $t2 /* handwritten instruction */
/* 4286C 8005206C 01000320 */  addi       $v1, $zero, 0x1 /* handwritten instruction */
/* 42870 80052070 000043A0 */  sb         $v1, 0x0($v0)
/* 42874 80052074 10480108 */  j          .L80052040
/* 42878 80052078 FCFFCE21 */   addi      $t6, $t6, -0x4 /* handwritten instruction */
.L8005207C:
/* 4287C 8005207C 52002380 */  lb         $v1, 0x52($at)
/* 42880 80052080 0C00248C */  lw         $a0, 0xC($at)
/* 42884 80052084 EEFF6010 */  beqz       $v1, .L80052040
/* 42888 80052088 801A0300 */   sll       $v1, $v1, 10
/* 4288C 8005208C 1F006004 */  bltz       $v1, .L8005210C
/* 42890 80052090 C2380300 */   srl       $a3, $v1, 3
/* 42894 80052094 1800E700 */  mult       $a3, $a3
/* 42898 80052098 1000258C */  lw         $a1, 0x10($at)
/* 4289C 8005209C 22208B00 */  sub        $a0, $a0, $t3 /* handwritten instruction */
/* 428A0 800520A0 20388300 */  add        $a3, $a0, $v1 /* handwritten instruction */
/* 428A4 800520A4 E6FFE018 */  blez       $a3, .L80052040
/* 428A8 800520A8 22388300 */   sub       $a3, $a0, $v1 /* handwritten instruction */
/* 428AC 800520AC E4FFE104 */  bgez       $a3, .L80052040
/* 428B0 800520B0 C3200400 */   sra       $a0, $a0, 3
/* 428B4 800520B4 00488448 */  mtc2       $a0, C2_IR1 /* handwritten instruction */
/* 428B8 800520B8 1400268C */  lw         $a2, 0x14($at)
/* 428BC 800520BC 2228AC00 */  sub        $a1, $a1, $t4 /* handwritten instruction */
/* 428C0 800520C0 2038A300 */  add        $a3, $a1, $v1 /* handwritten instruction */
/* 428C4 800520C4 DEFFE018 */  blez       $a3, .L80052040
/* 428C8 800520C8 2238A300 */   sub       $a3, $a1, $v1 /* handwritten instruction */
/* 428CC 800520CC DCFFE104 */  bgez       $a3, .L80052040
/* 428D0 800520D0 C3280500 */   sra       $a1, $a1, 3
/* 428D4 800520D4 00508548 */  mtc2       $a1, C2_IR2 /* handwritten instruction */
/* 428D8 800520D8 00588048 */  mtc2       $zero, C2_IR3 /* handwritten instruction */
/* 428DC 800520DC 2230CD00 */  sub        $a2, $a2, $t5 /* handwritten instruction */
/* 428E0 800520E0 2038C300 */  add        $a3, $a2, $v1 /* handwritten instruction */
/* 428E4 800520E4 2804A04A */  SQR        0
/* 428E8 800520E8 D5FFE018 */  blez       $a3, .L80052040
/* 428EC 800520EC 2238C300 */   sub       $a3, $a2, $v1 /* handwritten instruction */
/* 428F0 800520F0 D3FFE104 */  bgez       $a3, .L80052040
/* 428F4 800520F4 12180000 */   mflo      $v1
/* 428F8 800520F8 00C80448 */  mfc2       $a0, C2_MAC1 /* handwritten instruction */
/* 428FC 800520FC 00D00548 */  mfc2       $a1, C2_MAC2 /* handwritten instruction */
/* 42900 80052100 22186400 */  sub        $v1, $v1, $a0 /* handwritten instruction */
/* 42904 80052104 22186500 */  sub        $v1, $v1, $a1 /* handwritten instruction */
/* 42908 80052108 CDFF6018 */  blez       $v1, .L80052040
.L8005210C:
/* 4290C 8005210C 0000C1AD */   sw        $at, 0x0($t6)
/* 42910 80052110 CBFF4004 */  bltz       $v0, .L80052040
/* 42914 80052114 0400CE21 */   addi      $t6, $t6, 0x4 /* handwritten instruction */
/* 42918 80052118 20104A00 */  add        $v0, $v0, $t2 /* handwritten instruction */
/* 4291C 8005211C 01000320 */  addi       $v1, $zero, 0x1 /* handwritten instruction */
/* 42920 80052120 000043A0 */  sb         $v1, 0x0($v0)
/* 42924 80052124 10480108 */  j          .L80052040
/* 42928 80052128 FCFFCE21 */   addi      $t6, $t6, -0x4 /* handwritten instruction */
.L8005212C:
/* 4292C 8005212C FFFF0320 */  addi       $v1, $zero, -0x1 /* handwritten instruction */
/* 42930 80052130 C3FF6214 */  bne        $v1, $v0, .L80052040
/* 42934 80052134 00000000 */   nop
/* 42938 80052138 0780013C */  lui        $at, %hi(D_80075828)
/* 4293C 8005213C 28582124 */  addiu      $at, $at, %lo(D_80075828)
/* 42940 80052140 0000218C */  lw         $at, 0x0($at)
/* 42944 80052144 0780023C */  lui        $v0, %hi(g_MobyPods)
/* 42948 80052148 F8574224 */  addiu      $v0, $v0, %lo(g_MobyPods)
/* 4294C 8005214C 0000428C */  lw         $v0, 0x0($v0)
/* 42950 80052150 00004321 */  addi       $v1, $t2, 0x0 /* handwritten instruction */
/* 42954 80052154 20006420 */  addi       $a0, $v1, 0x20 /* handwritten instruction */
/* 42958 80052158 FFFF0520 */  addi       $a1, $zero, -0x1 /* handwritten instruction */
.L8005215C:
/* 4295C 8005215C 16006410 */  beq        $v1, $a0, .L800521B8
/* 42960 80052160 0100A520 */   addi      $a1, $a1, 0x1 /* handwritten instruction */
/* 42964 80052164 00006680 */  lb         $a2, 0x0($v1)
/* 42968 80052168 01006320 */  addi       $v1, $v1, 0x1 /* handwritten instruction */
/* 4296C 8005216C FBFFC010 */  beqz       $a2, .L8005215C
/* 42970 80052170 04004220 */   addi      $v0, $v0, 0x4 /* handwritten instruction */
/* 42974 80052174 FCFF468C */  lw         $a2, -0x4($v0)
/* 42978 80052178 58000820 */  addi       $t0, $zero, 0x58 /* handwritten instruction */
.L8005217C:
/* 4297C 8005217C 0000C784 */  lh         $a3, 0x0($a2)
/* 42980 80052180 0200C620 */  addi       $a2, $a2, 0x2 /* handwritten instruction */
/* 42984 80052184 FF7FE930 */  andi       $t1, $a3, 0x7FFF
/* 42988 80052188 18002801 */  mult       $t1, $t0
/* 4298C 8005218C 12480000 */  mflo       $t1
/* 42990 80052190 20482101 */  add        $t1, $t1, $at /* handwritten instruction */
/* 42994 80052194 48002A81 */  lb         $t2, 0x48($t1)
/* 42998 80052198 0000C9AD */  sw         $t1, 0x0($t6)
/* 4299C 8005219C 02004105 */  bgez       $t2, .L800521A8
/* 429A0 800521A0 0400CE21 */   addi      $t6, $t6, 0x4 /* handwritten instruction */
/* 429A4 800521A4 FCFFCE21 */  addi       $t6, $t6, -0x4 /* handwritten instruction */
.L800521A8:
/* 429A8 800521A8 F4FFE104 */  bgez       $a3, .L8005217C
/* 429AC 800521AC 00000000 */   nop
/* 429B0 800521B0 57480108 */  j          .L8005215C
/* 429B4 800521B4 00000000 */   nop
.L800521B8:
/* 429B8 800521B8 0800E003 */  jr         $ra
/* 429BC 800521BC 0000C0AD */   sw        $zero, 0x0($t6)
.size func_80051FEC, . - func_80051FEC

/* Handwritten function */
glabel func_800521C0
/* 429C0 800521C0 0780013C */  lui        $at, %hi(D_80075828)
/* 429C4 800521C4 28582124 */  addiu      $at, $at, %lo(D_80075828)
/* 429C8 800521C8 0000218C */  lw         $at, 0x0($at)
/* 429CC 800521CC 0780023C */  lui        $v0, %hi(D_8006FCF4)
/* 429D0 800521D0 F4FC4224 */  addiu      $v0, $v0, %lo(D_8006FCF4)
/* 429D4 800521D4 00244420 */  addi       $a0, $v0, 0x2400 /* handwritten instruction */
/* 429D8 800521D8 00224320 */  addi       $v1, $v0, 0x2200 /* handwritten instruction */
/* 429DC 800521DC 00004220 */  addi       $v0, $v0, 0x0 /* handwritten instruction */
/* 429E0 800521E0 0780053C */  lui        $a1, %hi(D_800771C8)
/* 429E4 800521E4 C871A524 */  addiu      $a1, $a1, %lo(D_800771C8)
/* 429E8 800521E8 4800278C */  lw         $a3, 0x48($at)
/* 429EC 800521EC FF000620 */  addi       $a2, $zero, 0xFF /* handwritten instruction */
/* 429F0 800521F0 A8FF2120 */  addi       $at, $at, -0x58 /* handwritten instruction */
.L800521F4:
/* 429F4 800521F4 0000E820 */  addi       $t0, $a3, 0x0 /* handwritten instruction */
/* 429F8 800521F8 58002120 */  addi       $at, $at, 0x58 /* handwritten instruction */
/* 429FC 800521FC 58002720 */  addi       $a3, $at, 0x58 /* handwritten instruction */
/* 42A00 80052200 4800E78C */  lw         $a3, 0x48($a3)
/* 42A04 80052204 004E0800 */  sll        $t1, $t0, 24
/* 42A08 80052208 26002005 */  bltz       $t1, .L800522A4
/* 42A0C 8005220C 034E0800 */   sra       $t1, $t0, 24
/* 42A10 80052210 19002011 */  beqz       $t1, .L80052278
/* 42A14 80052214 024C0800 */   srl       $t1, $t0, 16
/* 42A18 80052218 0C000005 */  bltz       $t0, .L8005224C
/* 42A1C 8005221C FF002931 */   andi      $t1, $t1, 0xFF
/* 42A20 80052220 000041AC */  sw         $at, 0x0($v0)
/* 42A24 80052224 F3FF2611 */  beq        $t1, $a2, .L800521F4
/* 42A28 80052228 04004220 */   addi      $v0, $v0, 0x4 /* handwritten instruction */
/* 42A2C 8005222C 20482501 */  add        $t1, $t1, $a1 /* handwritten instruction */
/* 42A30 80052230 00002991 */  lbu        $t1, 0x0($t1)
/* 42A34 80052234 00000000 */  nop
/* 42A38 80052238 EEFF201D */  bgtz       $t1, .L800521F4
/* 42A3C 8005223C 00000000 */   nop
/* 42A40 80052240 510020A0 */  sb         $zero, 0x51($at)
/* 42A44 80052244 7D480108 */  j          .L800521F4
/* 42A48 80052248 FCFF4220 */   addi      $v0, $v0, -0x4 /* handwritten instruction */
.L8005224C:
/* 42A4C 8005224C 000061AC */  sw         $at, 0x0($v1)
/* 42A50 80052250 E8FF2611 */  beq        $t1, $a2, .L800521F4
/* 42A54 80052254 04006320 */   addi      $v1, $v1, 0x4 /* handwritten instruction */
/* 42A58 80052258 20482501 */  add        $t1, $t1, $a1 /* handwritten instruction */
/* 42A5C 8005225C 00002991 */  lbu        $t1, 0x0($t1)
/* 42A60 80052260 00000000 */  nop
/* 42A64 80052264 E3FF201D */  bgtz       $t1, .L800521F4
/* 42A68 80052268 00000000 */   nop
/* 42A6C 8005226C 510020A0 */  sb         $zero, 0x51($at)
/* 42A70 80052270 7D480108 */  j          .L800521F4
/* 42A74 80052274 FCFF6320 */   addi      $v1, $v1, -0x4 /* handwritten instruction */
.L80052278:
/* 42A78 80052278 000081AC */  sw         $at, 0x0($a0)
/* 42A7C 8005227C DDFF2611 */  beq        $t1, $a2, .L800521F4
/* 42A80 80052280 04008420 */   addi      $a0, $a0, 0x4 /* handwritten instruction */
/* 42A84 80052284 20482501 */  add        $t1, $t1, $a1 /* handwritten instruction */
/* 42A88 80052288 00002991 */  lbu        $t1, 0x0($t1)
/* 42A8C 8005228C 00000000 */  nop
/* 42A90 80052290 D8FF201D */  bgtz       $t1, .L800521F4
/* 42A94 80052294 00000000 */   nop
/* 42A98 80052298 510020A0 */  sb         $zero, 0x51($at)
/* 42A9C 8005229C 7D480108 */  j          .L800521F4
/* 42AA0 800522A0 FCFF8420 */   addi      $a0, $a0, -0x4 /* handwritten instruction */
.L800522A4:
/* 42AA4 800522A4 FF000931 */  andi       $t1, $t0, 0xFF
/* 42AA8 800522A8 D2FF2615 */  bne        $t1, $a2, .L800521F4
/* 42AAC 800522AC 00000000 */   nop
/* 42AB0 800522B0 000040AC */  sw         $zero, 0x0($v0)
/* 42AB4 800522B4 000060AC */  sw         $zero, 0x0($v1)
/* 42AB8 800522B8 0800E003 */  jr         $ra
/* 42ABC 800522BC 000080AC */   sw        $zero, 0x0($a0)
.size func_800521C0, . - func_800521C0

/* Handwritten function */
glabel func_800522C0
/* 42AC0 800522C0 0780013C */  lui        $at, %hi(D_8006FCF4)
/* 42AC4 800522C4 F4FC2124 */  addiu      $at, $at, %lo(D_8006FCF4)
/* 42AC8 800522C8 13002000 */  mtlo       $at
/* 42ACC 800522CC 00009920 */  addi       $t9, $a0, 0x0 /* handwritten instruction */
/* 42AD0 800522D0 801F183C */  lui        $t8, (0x1F800004 >> 16)
/* 42AD4 800522D4 07800F3C */  lui        $t7, %hi(D_80076378)
/* 42AD8 800522D8 7863EF25 */  addiu      $t7, $t7, %lo(D_80076378)
/* 42ADC 800522DC 0000AE20 */  addi       $t6, $a1, 0x0 /* handwritten instruction */
.L800522E0:
/* 42AE0 800522E0 00002D8F */  lw         $t5, 0x0($t9)
/* 42AE4 800522E4 04003923 */  addi       $t9, $t9, 0x4 /* handwritten instruction */
/* 42AE8 800522E8 5700A011 */  beqz       $t5, .L80052448
/* 42AEC 800522EC 4000A18D */   lw        $at, 0x40($t5)
/* 42AF0 800522F0 3C00A28D */  lw         $v0, 0x3C($t5)
/* 42AF4 800522F4 000001AF */  sw         $at, (0x1F800000 & 0xFFFF)($t8)
/* 42AF8 800522F8 00000493 */  lbu        $a0, (0x1F800000 & 0xFFFF)($t8)
/* 42AFC 800522FC 01000593 */  lbu        $a1, (0x1F800001 & 0xFFFF)($t8)
/* 42B00 80052300 040002AF */  sw         $v0, (0x1F800004 & 0xFFFF)($t8)
/* 42B04 80052304 0628C501 */  srlv       $a1, $a1, $t6
/* 42B08 80052308 20208500 */  add        $a0, $a0, $a1 /* handwritten instruction */
/* 42B0C 8005230C 82090400 */  srl        $at, $a0, 6
/* 42B10 80052310 44002010 */  beqz       $at, .L80052424
/* 42B14 80052314 3F008430 */   andi      $a0, $a0, 0x3F
/* 42B18 80052318 04000693 */  lbu        $a2, (0x1F800004 & 0xFFFF)($t8)
/* 42B1C 8005231C 05000793 */  lbu        $a3, (0x1F800005 & 0xFFFF)($t8)
/* 42B20 80052320 3600AA95 */  lhu        $t2, 0x36($t5)
/* 42B24 80052324 1C00C714 */  bne        $a2, $a3, .L80052398
/* 42B28 80052328 07000893 */   lbu       $t0, (0x1F800007 & 0xFFFF)($t8)
/* 42B2C 8005232C 0700C105 */  bgez       $t6, .L8005234C
/* 42B30 80052330 00000220 */   addi      $v0, $zero, 0x0 /* handwritten instruction */
/* 42B34 80052334 02000283 */  lb         $v0, (0x1F800002 & 0xFFFF)($t8)
/* 42B38 80052338 00000000 */  nop
/* 42B3C 8005233C 03004010 */  beqz       $v0, .L8005234C
/* 42B40 80052340 02004130 */   andi      $at, $v0, 0x2
/* 42B44 80052344 E6FF201C */  bgtz       $at, .L800522E0
/* 42B48 80052348 04004234 */   ori       $v0, $v0, 0x4
.L8005234C:
/* 42B4C 8005234C 000004A3 */  sb         $a0, (0x1F800000 & 0xFFFF)($t8)
/* 42B50 80052350 060008A3 */  sb         $t0, (0x1F800006 & 0xFFFF)($t8)
/* 42B54 80052354 80500A00 */  sll        $t2, $t2, 2
/* 42B58 80052358 20504F01 */  add        $t2, $t2, $t7 /* handwritten instruction */
/* 42B5C 8005235C 00004A8D */  lw         $t2, 0x0($t2)
/* 42B60 80052360 80580700 */  sll        $t3, $a3, 2
/* 42B64 80052364 20586A01 */  add        $t3, $t3, $t2 /* handwritten instruction */
/* 42B68 80052368 38006B8D */  lw         $t3, 0x38($t3)
/* 42B6C 8005236C 01000921 */  addi       $t1, $t0, 0x1 /* handwritten instruction */
/* 42B70 80052370 00006195 */  lhu        $at, 0x0($t3)
/* 42B74 80052374 01004234 */  ori        $v0, $v0, 0x1
/* 42B78 80052378 020002A3 */  sb         $v0, (0x1F800002 & 0xFFFF)($t8)
/* 42B7C 8005237C 22082101 */  sub        $at, $t1, $at /* handwritten instruction */
/* 42B80 80052380 17002004 */  bltz       $at, .L800523E0
/* 42B84 80052384 070009A3 */   sb        $t1, (0x1F800007 & 0xFFFF)($t8)
/* 42B88 80052388 070000A3 */  sb         $zero, (0x1F800007 & 0xFFFF)($t8)
/* 42B8C 8005238C 02004234 */  ori        $v0, $v0, 0x2
/* 42B90 80052390 F8480108 */  j          .L800523E0
/* 42B94 80052394 020002A3 */   sb        $v0, (0x1F800002 & 0xFFFF)($t8)
.L80052398:
/* 42B98 80052398 000000A3 */  sb         $zero, (0x1F800000 & 0xFFFF)($t8)
/* 42B9C 8005239C 040007A3 */  sb         $a3, (0x1F800004 & 0xFFFF)($t8)
/* 42BA0 800523A0 060008A3 */  sb         $t0, (0x1F800006 & 0xFFFF)($t8)
/* 42BA4 800523A4 80500A00 */  sll        $t2, $t2, 2
/* 42BA8 800523A8 20504F01 */  add        $t2, $t2, $t7 /* handwritten instruction */
/* 42BAC 800523AC 00004A8D */  lw         $t2, 0x0($t2)
/* 42BB0 800523B0 80580700 */  sll        $t3, $a3, 2
/* 42BB4 800523B4 20586A01 */  add        $t3, $t3, $t2 /* handwritten instruction */
/* 42BB8 800523B8 38006B8D */  lw         $t3, 0x38($t3)
/* 42BBC 800523BC 01000921 */  addi       $t1, $t0, 0x1 /* handwritten instruction */
/* 42BC0 800523C0 070009A3 */  sb         $t1, (0x1F800007 & 0xFFFF)($t8)
/* 42BC4 800523C4 0C006591 */  lbu        $a1, 0xC($t3)
/* 42BC8 800523C8 01000134 */  ori        $at, $zero, 0x1
/* 42BCC 800523CC 020001A3 */  sb         $at, (0x1F800002 & 0xFFFF)($t8)
/* 42BD0 800523D0 0300A01C */  bgtz       $a1, .L800523E0
/* 42BD4 800523D4 010005A3 */   sb        $a1, (0x1F800001 & 0xFFFF)($t8)
/* 42BD8 800523D8 FFFF2921 */  addi       $t1, $t1, -0x1 /* handwritten instruction */
/* 42BDC 800523DC 070009A3 */  sb         $t1, (0x1F800007 & 0xFFFF)($t8)
.L800523E0:
/* 42BE0 800523E0 0000018F */  lw         $at, (0x1F800000 & 0xFFFF)($t8)
/* 42BE4 800523E4 0400028F */  lw         $v0, (0x1F800004 & 0xFFFF)($t8)
/* 42BE8 800523E8 4000A1AD */  sw         $at, 0x40($t5)
/* 42BEC 800523EC 3C00A2AD */  sw         $v0, 0x3C($t5)
/* 42BF0 800523F0 C0080800 */  sll        $at, $t0, 3
/* 42BF4 800523F4 20606101 */  add        $t4, $t3, $at /* handwritten instruction */
/* 42BF8 800523F8 24008C21 */  addi       $t4, $t4, 0x24 /* handwritten instruction */
/* 42BFC 800523FC 03008181 */  lb         $at, 0x3($t4)
/* 42C00 80052400 12100000 */  mflo       $v0
/* 42C04 80052404 04004DAC */  sw         $t5, 0x4($v0)
/* 42C08 80052408 B5FF2004 */  bltz       $at, .L800522E0
/* 42C0C 8005240C 20082A00 */   add       $at, $at, $t2 /* handwritten instruction */
/* 42C10 80052410 04002190 */  lbu        $at, 0x4($at)
/* 42C14 80052414 08004220 */  addi       $v0, $v0, 0x8 /* handwritten instruction */
/* 42C18 80052418 13004000 */  mtlo       $v0
/* 42C1C 8005241C B8480108 */  j          .L800522E0
/* 42C20 80052420 F8FF41AC */   sw        $at, -0x8($v0)
.L80052424:
/* 42C24 80052424 0200C005 */  bltz       $t6, .L80052430
/* 42C28 80052428 00000000 */   nop
/* 42C2C 8005242C 020000A3 */  sb         $zero, (0x1F800002 & 0xFFFF)($t8)
.L80052430:
/* 42C30 80052430 000004A3 */  sb         $a0, (0x1F800000 & 0xFFFF)($t8)
/* 42C34 80052434 0000018F */  lw         $at, (0x1F800000 & 0xFFFF)($t8)
/* 42C38 80052438 0400028F */  lw         $v0, (0x1F800004 & 0xFFFF)($t8)
/* 42C3C 8005243C 4000A1AD */  sw         $at, 0x40($t5)
/* 42C40 80052440 B8480108 */  j          .L800522E0
/* 42C44 80052444 3C00A2AD */   sw        $v0, 0x3C($t5)
.L80052448:
/* 42C48 80052448 0780013C */  lui        $at, %hi(D_8006FCF4)
/* 42C4C 8005244C F4FC2124 */  addiu      $at, $at, %lo(D_8006FCF4)
/* 42C50 80052450 12200000 */  mflo       $a0
/* 42C54 80052454 03002414 */  bne        $at, $a0, .L80052464
/* 42C58 80052458 00000000 */   nop
/* 42C5C 8005245C 0800E003 */  jr         $ra
/* 42C60 80052460 00000000 */   nop
.L80052464:
/* 42C64 80052464 07800F3C */  lui        $t7, %hi(D_80077DD8)
/* 42C68 80052468 D87DEF25 */  addiu      $t7, $t7, %lo(D_80077DD8)
/* 42C6C 8005246C 0000E1AD */  sw         $at, 0x0($t7)
/* 42C70 80052470 0400E4AD */  sw         $a0, 0x4($t7)
/* 42C74 80052474 0800FFAD */  sw         $ra, 0x8($t7)
.L80052478:
/* 42C78 80052478 0000248C */  lw         $a0, 0x0($at)
/* 42C7C 8005247C 0400258C */  lw         $a1, 0x4($at)
/* 42C80 80052480 08002120 */  addi       $at, $at, 0x8 /* handwritten instruction */
/* 42C84 80052484 0000E1AD */  sw         $at, 0x0($t7)
/* 42C88 80052488 0C00E5AD */  sw         $a1, 0xC($t7)
/* 42C8C 8005248C 08000620 */  addi       $a2, $zero, 0x8 /* handwritten instruction */
/* 42C90 80052490 9E56010C */  jal        PlaySound
/* 42C94 80052494 5400A720 */   addi      $a3, $a1, 0x54 /* handwritten instruction */
/* 42C98 80052498 07800F3C */  lui        $t7, %hi(D_80077DD8)
/* 42C9C 8005249C D87DEF25 */  addiu      $t7, $t7, %lo(D_80077DD8)
/* 42CA0 800524A0 0000E18D */  lw         $at, 0x0($t7)
/* 42CA4 800524A4 0400E48D */  lw         $a0, 0x4($t7)
/* 42CA8 800524A8 00000000 */  nop
/* 42CAC 800524AC F2FF2414 */  bne        $at, $a0, .L80052478
/* 42CB0 800524B0 00000000 */   nop
/* 42CB4 800524B4 0800FF8D */  lw         $ra, 0x8($t7)
/* 42CB8 800524B8 00000000 */  nop
/* 42CBC 800524BC 0800E003 */  jr         $ra
/* 42CC0 800524C0 00000000 */   nop
.size func_800522C0, . - func_800522C0
