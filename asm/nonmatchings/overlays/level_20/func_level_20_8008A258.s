.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_20_8008A258
/* 188D820 8008A258 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 188D824 8008A25C 3800B0AF */  sw         $s0, 0x38($sp)
/* 188D828 8008A260 21808000 */  addu       $s0, $a0, $zero
/* 188D82C 8008A264 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 188D830 8008A268 21A8A000 */  addu       $s5, $a1, $zero
/* 188D834 8008A26C 5000BFAF */  sw         $ra, 0x50($sp)
/* 188D838 8008A270 4800B4AF */  sw         $s4, 0x48($sp)
/* 188D83C 8008A274 4400B3AF */  sw         $s3, 0x44($sp)
/* 188D840 8008A278 4000B2AF */  sw         $s2, 0x40($sp)
/* 188D844 8008A27C 3149010C */  jal        func_800524C4
/* 188D848 8008A280 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 188D84C 8008A284 21984000 */  addu       $s3, $v0, $zero
/* 188D850 8008A288 1400A012 */  beqz       $s5, .Llevel_20_8008A2DC
/* 188D854 8008A28C 360070A6 */   sh        $s0, 0x36($s3)
/* 188D858 8008A290 0780043C */  lui        $a0, %hi(D_80075828)
/* 188D85C 8008A294 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 188D860 8008A298 00000000 */  nop
/* 188D864 8008A29C 2320A402 */  subu       $a0, $s5, $a0
/* 188D868 8008A2A0 40190400 */  sll        $v1, $a0, 5
/* 188D86C 8008A2A4 23186400 */  subu       $v1, $v1, $a0
/* 188D870 8008A2A8 40190300 */  sll        $v1, $v1, 5
/* 188D874 8008A2AC 21186400 */  addu       $v1, $v1, $a0
/* 188D878 8008A2B0 C0100300 */  sll        $v0, $v1, 3
/* 188D87C 8008A2B4 21186200 */  addu       $v1, $v1, $v0
/* 188D880 8008A2B8 C0130300 */  sll        $v0, $v1, 15
/* 188D884 8008A2BC 23104300 */  subu       $v0, $v0, $v1
/* 188D888 8008A2C0 80100200 */  sll        $v0, $v0, 2
/* 188D88C 8008A2C4 21104400 */  addu       $v0, $v0, $a0
/* 188D890 8008A2C8 23100200 */  negu       $v0, $v0
/* 188D894 8008A2CC C3180200 */  sra        $v1, $v0, 3
/* 188D898 8008A2D0 0001622C */  sltiu      $v0, $v1, 0x100
/* 188D89C 8008A2D4 03004014 */  bnez       $v0, .Llevel_20_8008A2E4
/* 188D8A0 8008A2D8 15010224 */   addiu     $v0, $zero, 0x115
.Llevel_20_8008A2DC:
/* 188D8A4 8008A2DC 21180000 */  addu       $v1, $zero, $zero
/* 188D8A8 8008A2E0 15010224 */  addiu      $v0, $zero, 0x115
.Llevel_20_8008A2E4:
/* 188D8AC 8008A2E4 EA010212 */  beq        $s0, $v0, .Llevel_20_8008AA90
/* 188D8B0 8008A2E8 560063A2 */   sb        $v1, 0x56($s3)
/* 188D8B4 8008A2EC 1601022A */  slti       $v0, $s0, 0x116
/* 188D8B8 8008A2F0 31004010 */  beqz       $v0, .Llevel_20_8008A3B8
/* 188D8BC 8008A2F4 5800022A */   slti      $v0, $s0, 0x58
/* 188D8C0 8008A2F8 1D004010 */  beqz       $v0, .Llevel_20_8008A370
/* 188D8C4 8008A2FC 5300022A */   slti      $v0, $s0, 0x53
/* 188D8C8 8008A300 A0004010 */  beqz       $v0, .Llevel_20_8008A584
/* 188D8CC 8008A304 22000224 */   addiu     $v0, $zero, 0x22
/* 188D8D0 8008A308 90000212 */  beq        $s0, $v0, .Llevel_20_8008A54C
/* 188D8D4 8008A30C 2300022A */   slti      $v0, $s0, 0x23
/* 188D8D8 8008A310 0E004010 */  beqz       $v0, .Llevel_20_8008A34C
/* 188D8DC 8008A314 0F000224 */   addiu     $v0, $zero, 0xF
/* 188D8E0 8008A318 51000212 */  beq        $s0, $v0, .Llevel_20_8008A460
/* 188D8E4 8008A31C 1000022A */   slti      $v0, $s0, 0x10
/* 188D8E8 8008A320 05004010 */  beqz       $v0, .Llevel_20_8008A338
/* 188D8EC 8008A324 0E000224 */   addiu     $v0, $zero, 0xE
/* 188D8F0 8008A328 96000212 */  beq        $s0, $v0, .Llevel_20_8008A584
/* 188D8F4 8008A32C 00000000 */   nop
/* 188D8F8 8008A330 722B0208 */  j          .Llevel_20_8008ADC8
/* 188D8FC 8008A334 00000000 */   nop
.Llevel_20_8008A338:
/* 188D900 8008A338 10000224 */  addiu      $v0, $zero, 0x10
/* 188D904 8008A33C 6F000212 */  beq        $s0, $v0, .Llevel_20_8008A4FC
/* 188D908 8008A340 00000000 */   nop
/* 188D90C 8008A344 722B0208 */  j          .Llevel_20_8008ADC8
/* 188D910 8008A348 00000000 */   nop
.Llevel_20_8008A34C:
/* 188D914 8008A34C 4300022A */  slti       $v0, $s0, 0x43
/* 188D918 8008A350 9D024014 */  bnez       $v0, .Llevel_20_8008ADC8
/* 188D91C 8008A354 4600022A */   slti      $v0, $s0, 0x46
/* 188D920 8008A358 F2004014 */  bnez       $v0, .Llevel_20_8008A724
/* 188D924 8008A35C 4C000224 */   addiu     $v0, $zero, 0x4C
/* 188D928 8008A360 4F020212 */  beq        $s0, $v0, .Llevel_20_8008ACA0
/* 188D92C 8008A364 00000000 */   nop
/* 188D930 8008A368 722B0208 */  j          .Llevel_20_8008ADC8
/* 188D934 8008A36C 00000000 */   nop
.Llevel_20_8008A370:
/* 188D938 8008A370 0201022A */  slti       $v0, $s0, 0x102
/* 188D93C 8008A374 09004010 */  beqz       $v0, .Llevel_20_8008A39C
/* 188D940 8008A378 FF00022A */   slti      $v0, $s0, 0xFF
/* 188D944 8008A37C E9004010 */  beqz       $v0, .Llevel_20_8008A724
/* 188D948 8008A380 78000224 */   addiu     $v0, $zero, 0x78
/* 188D94C 8008A384 D5000212 */  beq        $s0, $v0, .Llevel_20_8008A6DC
/* 188D950 8008A388 FB000224 */   addiu     $v0, $zero, 0xFB
/* 188D954 8008A38C 50010212 */  beq        $s0, $v0, .Llevel_20_8008A8D0
/* 188D958 8008A390 00000000 */   nop
/* 188D95C 8008A394 722B0208 */  j          .Llevel_20_8008ADC8
/* 188D960 8008A398 00000000 */   nop
.Llevel_20_8008A39C:
/* 188D964 8008A39C 0E01022A */  slti       $v0, $s0, 0x10E
/* 188D968 8008A3A0 89024010 */  beqz       $v0, .Llevel_20_8008ADC8
/* 188D96C 8008A3A4 0401022A */   slti      $v0, $s0, 0x104
/* 188D970 8008A3A8 B9014010 */  beqz       $v0, .Llevel_20_8008AA90
/* 188D974 8008A3AC 00000000 */   nop
/* 188D978 8008A3B0 722B0208 */  j          .Llevel_20_8008ADC8
/* 188D97C 8008A3B4 00000000 */   nop
.Llevel_20_8008A3B8:
/* 188D980 8008A3B8 AA01022A */  slti       $v0, $s0, 0x1AA
/* 188D984 8008A3BC 16004010 */  beqz       $v0, .Llevel_20_8008A418
/* 188D988 8008A3C0 A701022A */   slti      $v0, $s0, 0x1A7
/* 188D98C 8008A3C4 D7004010 */  beqz       $v0, .Llevel_20_8008A724
/* 188D990 8008A3C8 6D01022A */   slti      $v0, $s0, 0x16D
/* 188D994 8008A3CC 0B004010 */  beqz       $v0, .Llevel_20_8008A3FC
/* 188D998 8008A3D0 6B01022A */   slti      $v0, $s0, 0x16B
/* 188D99C 8008A3D4 CE014010 */  beqz       $v0, .Llevel_20_8008AB10
/* 188D9A0 8008A3D8 3501022A */   slti      $v0, $s0, 0x135
/* 188D9A4 8008A3DC 7A024014 */  bnez       $v0, .Llevel_20_8008ADC8
/* 188D9A8 8008A3E0 3801022A */   slti      $v0, $s0, 0x138
/* 188D9AC 8008A3E4 CF004014 */  bnez       $v0, .Llevel_20_8008A724
/* 188D9B0 8008A3E8 47010224 */   addiu     $v0, $zero, 0x147
/* 188D9B4 8008A3EC A8010212 */  beq        $s0, $v0, .Llevel_20_8008AA90
/* 188D9B8 8008A3F0 00000000 */   nop
/* 188D9BC 8008A3F4 722B0208 */  j          .Llevel_20_8008ADC8
/* 188D9C0 8008A3F8 00000000 */   nop
.Llevel_20_8008A3FC:
/* 188D9C4 8008A3FC 8E010224 */  addiu      $v0, $zero, 0x18E
/* 188D9C8 8008A400 B0010212 */  beq        $s0, $v0, .Llevel_20_8008AAC4
/* 188D9CC 8008A404 95010224 */   addiu     $v0, $zero, 0x195
/* 188D9D0 8008A408 C1010212 */  beq        $s0, $v0, .Llevel_20_8008AB10
/* 188D9D4 8008A40C 00000000 */   nop
/* 188D9D8 8008A410 722B0208 */  j          .Llevel_20_8008ADC8
/* 188D9DC 8008A414 00000000 */   nop
.Llevel_20_8008A418:
/* 188D9E0 8008A418 C901022A */  slti       $v0, $s0, 0x1C9
/* 188D9E4 8008A41C 07004010 */  beqz       $v0, .Llevel_20_8008A43C
/* 188D9E8 8008A420 C601022A */   slti      $v0, $s0, 0x1C6
/* 188D9EC 8008A424 D7014010 */  beqz       $v0, .Llevel_20_8008AB84
/* 188D9F0 8008A428 C401022A */   slti      $v0, $s0, 0x1C4
/* 188D9F4 8008A42C 66024010 */  beqz       $v0, .Llevel_20_8008ADC8
/* 188D9F8 8008A430 00000000 */   nop
/* 188D9FC 8008A434 282B0208 */  j          .Llevel_20_8008ACA0
/* 188DA00 8008A438 00000000 */   nop
.Llevel_20_8008A43C:
/* 188DA04 8008A43C CA01022A */  slti       $v0, $s0, 0x1CA
/* 188DA08 8008A440 61024014 */  bnez       $v0, .Llevel_20_8008ADC8
/* 188DA0C 8008A444 CC01022A */   slti      $v0, $s0, 0x1CC
/* 188DA10 8008A448 1F024014 */  bnez       $v0, .Llevel_20_8008ACC8
/* 188DA14 8008A44C DD010224 */   addiu     $v0, $zero, 0x1DD
/* 188DA18 8008A450 AF010212 */  beq        $s0, $v0, .Llevel_20_8008AB10
/* 188DA1C 8008A454 00000000 */   nop
/* 188DA20 8008A458 722B0208 */  j          .Llevel_20_8008ADC8
/* 188DA24 8008A45C 00000000 */   nop
.Llevel_20_8008A460:
/* 188DA28 8008A460 0000708E */  lw         $s0, 0x0($s3)
/* 188DA2C 8008A464 C8E9000C */  jal        func_8003A720
/* 188DA30 8008A468 21206002 */   addu      $a0, $s3, $zero
/* 188DA34 8008A46C 8C000224 */  addiu      $v0, $zero, 0x8C
/* 188DA38 8008A470 080002AE */  sw         $v0, 0x8($s0)
/* 188DA3C 8008A474 03000224 */  addiu      $v0, $zero, 0x3
/* 188DA40 8008A478 100002A2 */  sb         $v0, 0x10($s0)
/* 188DA44 8008A47C FF000224 */  addiu      $v0, $zero, 0xFF
/* 188DA48 8008A480 140002A2 */  sb         $v0, 0x14($s0)
/* 188DA4C 8008A484 02000224 */  addiu      $v0, $zero, 0x2
/* 188DA50 8008A488 000000AE */  sw         $zero, 0x0($s0)
/* 188DA54 8008A48C 040000AE */  sw         $zero, 0x4($s0)
/* 188DA58 8008A490 0E0000A2 */  sb         $zero, 0xE($s0)
/* 188DA5C 8008A494 0F0000A2 */  sb         $zero, 0xF($s0)
/* 188DA60 8008A498 110000A2 */  sb         $zero, 0x11($s0)
/* 188DA64 8008A49C 120000A2 */  sb         $zero, 0x12($s0)
/* 188DA68 8008A4A0 130000A2 */  sb         $zero, 0x13($s0)
/* 188DA6C 8008A4A4 490062A2 */  sb         $v0, 0x49($s3)
/* 188DA70 8008A4A8 18000224 */  addiu      $v0, $zero, 0x18
/* 188DA74 8008A4AC 500062A2 */  sb         $v0, 0x50($s3)
/* 188DA78 8008A4B0 10000224 */  addiu      $v0, $zero, 0x10
/* 188DA7C 8008A4B4 520062A2 */  sb         $v0, 0x52($s3)
/* 188DA80 8008A4B8 20000224 */  addiu      $v0, $zero, 0x20
/* 188DA84 8008A4BC 440062A2 */  sb         $v0, 0x44($s3)
/* 188DA88 8008A4C0 450060A2 */  sb         $zero, 0x45($s3)
/* 188DA8C 8008A4C4 0400A012 */  beqz       $s5, .Llevel_20_8008A4D8
/* 188DA90 8008A4C8 460060A2 */   sb        $zero, 0x46($s3)
/* 188DA94 8008A4CC 0C006426 */  addiu      $a0, $s3, 0xC
/* 188DA98 8008A4D0 C05D000C */  jal        VecCopy
/* 188DA9C 8008A4D4 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_20_8008A4D8:
/* 188DAA0 8008A4D8 AA49010C */  jal        func_800526A8
/* 188DAA4 8008A4DC 21206002 */   addu      $a0, $s3, $zero
/* 188DAA8 8008A4E0 4B006292 */  lbu        $v0, 0x4B($s3)
/* 188DAAC 8008A4E4 01000324 */  addiu      $v1, $zero, 0x1
/* 188DAB0 8008A4E8 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 188DAB4 8008A4EC 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 188DAB8 8008A4F0 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 188DABC 8008A4F4 312A0208 */  j          .Llevel_20_8008A8C4
/* 188DAC0 8008A4F8 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_20_8008A4FC:
/* 188DAC4 8008A4FC 0000718E */  lw         $s1, 0x0($s3)
/* 188DAC8 8008A500 C8E9000C */  jal        func_8003A720
/* 188DACC 8008A504 21206002 */   addu      $a0, $s3, $zero
/* 188DAD0 8008A508 AA49010C */  jal        func_800526A8
/* 188DAD4 8008A50C 21206002 */   addu      $a0, $s3, $zero
/* 188DAD8 8008A510 0C007026 */  addiu      $s0, $s3, 0xC
/* 188DADC 8008A514 21200002 */  addu       $a0, $s0, $zero
/* 188DAE0 8008A518 C05D000C */  jal        VecCopy
/* 188DAE4 8008A51C 0C00A526 */   addiu     $a1, $s5, 0xC
/* 188DAE8 8008A520 21280002 */  addu       $a1, $s0, $zero
/* 188DAEC 8008A524 1400628E */  lw         $v0, 0x14($s3)
/* 188DAF0 8008A528 04002426 */  addiu      $a0, $s1, 0x4
/* 188DAF4 8008A52C 00024224 */  addiu      $v0, $v0, 0x200
/* 188DAF8 8008A530 C05D000C */  jal        VecCopy
/* 188DAFC 8008A534 140062AE */   sw        $v0, 0x14($s3)
/* 188DB00 8008A538 08070224 */  addiu      $v0, $zero, 0x708
/* 188DB04 8008A53C 130020A2 */  sb         $zero, 0x13($s1)
/* 188DB08 8008A540 120020A2 */  sb         $zero, 0x12($s1)
/* 188DB0C 8008A544 7F2B0208 */  j          .Llevel_20_8008ADFC
/* 188DB10 8008A548 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_20_8008A54C:
/* 188DB14 8008A54C C8E9000C */  jal        func_8003A720
/* 188DB18 8008A550 21206002 */   addu      $a0, $s3, $zero
/* 188DB1C 8008A554 20000224 */  addiu      $v0, $zero, 0x20
/* 188DB20 8008A558 500062A2 */  sb         $v0, 0x50($s3)
/* 188DB24 8008A55C FF000224 */  addiu      $v0, $zero, 0xFF
/* 188DB28 8008A560 0400A012 */  beqz       $s5, .Llevel_20_8008A574
/* 188DB2C 8008A564 520062A2 */   sb        $v0, 0x52($s3)
/* 188DB30 8008A568 0C006426 */  addiu      $a0, $s3, 0xC
/* 188DB34 8008A56C C05D000C */  jal        VecCopy
/* 188DB38 8008A570 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_20_8008A574:
/* 188DB3C 8008A574 734A010C */  jal        func_800529CC
/* 188DB40 8008A578 21206002 */   addu      $a0, $s3, $zero
/* 188DB44 8008A57C 802B0208 */  j          .Llevel_20_8008AE00
/* 188DB48 8008A580 21106002 */   addu      $v0, $s3, $zero
.Llevel_20_8008A584:
/* 188DB4C 8008A584 0000718E */  lw         $s1, 0x0($s3)
/* 188DB50 8008A588 C8E9000C */  jal        func_8003A720
/* 188DB54 8008A58C 21206002 */   addu      $a0, $s3, $zero
/* 188DB58 8008A590 8C000224 */  addiu      $v0, $zero, 0x8C
/* 188DB5C 8008A594 000020AE */  sw         $zero, 0x0($s1)
/* 188DB60 8008A598 040020AE */  sw         $zero, 0x4($s1)
/* 188DB64 8008A59C 080022AE */  sw         $v0, 0x8($s1)
/* 188DB68 8008A5A0 0E0020A2 */  sb         $zero, 0xE($s1)
/* 188DB6C 8008A5A4 0F0020A2 */  sb         $zero, 0xF($s1)
/* 188DB70 8008A5A8 110020A2 */  sb         $zero, 0x11($s1)
/* 188DB74 8008A5AC 120020A2 */  sb         $zero, 0x12($s1)
/* 188DB78 8008A5B0 130020A2 */  sb         $zero, 0x13($s1)
/* 188DB7C 8008A5B4 3600A386 */  lh         $v1, 0x36($s5)
/* 188DB80 8008A5B8 0D000224 */  addiu      $v0, $zero, 0xD
/* 188DB84 8008A5BC 02006214 */  bne        $v1, $v0, .Llevel_20_8008A5C8
/* 188DB88 8008A5C0 03000224 */   addiu     $v0, $zero, 0x3
/* 188DB8C 8008A5C4 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_20_8008A5C8:
/* 188DB90 8008A5C8 100022A2 */  sb         $v0, 0x10($s1)
/* 188DB94 8008A5CC 0C007026 */  addiu      $s0, $s3, 0xC
/* 188DB98 8008A5D0 21200002 */  addu       $a0, $s0, $zero
/* 188DB9C 8008A5D4 0C00A526 */  addiu      $a1, $s5, 0xC
/* 188DBA0 8008A5D8 FF000224 */  addiu      $v0, $zero, 0xFF
/* 188DBA4 8008A5DC 140022A2 */  sb         $v0, 0x14($s1)
/* 188DBA8 8008A5E0 02001124 */  addiu      $s1, $zero, 0x2
/* 188DBAC 8008A5E4 18000224 */  addiu      $v0, $zero, 0x18
/* 188DBB0 8008A5E8 500062A2 */  sb         $v0, 0x50($s3)
/* 188DBB4 8008A5EC 40000224 */  addiu      $v0, $zero, 0x40
/* 188DBB8 8008A5F0 520062A2 */  sb         $v0, 0x52($s3)
/* 188DBBC 8008A5F4 20000224 */  addiu      $v0, $zero, 0x20
/* 188DBC0 8008A5F8 490071A2 */  sb         $s1, 0x49($s3)
/* 188DBC4 8008A5FC 440062A2 */  sb         $v0, 0x44($s3)
/* 188DBC8 8008A600 450060A2 */  sb         $zero, 0x45($s3)
/* 188DBCC 8008A604 C05D000C */  jal        VecCopy
/* 188DBD0 8008A608 460060A2 */   sb        $zero, 0x46($s3)
/* 188DBD4 8008A60C 734A010C */  jal        func_800529CC
/* 188DBD8 8008A610 21206002 */   addu      $a0, $s3, $zero
/* 188DBDC 8008A614 1000A427 */  addiu      $a0, $sp, 0x10
/* 188DBE0 8008A618 21280002 */  addu       $a1, $s0, $zero
/* 188DBE4 8008A61C FFFF0224 */  addiu      $v0, $zero, -0x1
/* 188DBE8 8008A620 C05D000C */  jal        VecCopy
/* 188DBEC 8008A624 1C0062AE */   sw        $v0, 0x1C($s3)
/* 188DBF0 8008A628 1000A427 */  addiu      $a0, $sp, 0x10
/* 188DBF4 8008A62C 1800A28F */  lw         $v0, 0x18($sp)
/* 188DBF8 8008A630 0100053C */  lui        $a1, (0x10000 >> 16)
/* 188DBFC 8008A634 00044224 */  addiu      $v0, $v0, 0x400
/* 188DC00 8008A638 7B35010C */  jal        func_8004D5EC
/* 188DC04 8008A63C 1800A2AF */   sw        $v0, 0x18($sp)
/* 188DC08 8008A640 F44C010C */  jal        func_800533D0
/* 188DC0C 8008A644 21206002 */   addu      $a0, $s3, $zero
/* 188DC10 8008A648 36006386 */  lh         $v1, 0x36($s3)
/* 188DC14 8008A64C 0E000224 */  addiu      $v0, $zero, 0xE
/* 188DC18 8008A650 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 188DC1C 8008A654 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 188DC20 8008A658 03006214 */  bne        $v1, $v0, .Llevel_20_8008A668
/* 188DC24 8008A65C 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 188DC28 8008A660 0C000224 */  addiu      $v0, $zero, 0xC
/* 188DC2C 8008A664 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_20_8008A668:
/* 188DC30 8008A668 36006386 */  lh         $v1, 0x36($s3)
/* 188DC34 8008A66C 53000224 */  addiu      $v0, $zero, 0x53
/* 188DC38 8008A670 05006214 */  bne        $v1, $v0, .Llevel_20_8008A688
/* 188DC3C 8008A674 54000224 */   addiu     $v0, $zero, 0x54
/* 188DC40 8008A678 01000224 */  addiu      $v0, $zero, 0x1
/* 188DC44 8008A67C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 188DC48 8008A680 36006386 */  lh         $v1, 0x36($s3)
/* 188DC4C 8008A684 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_20_8008A688:
/* 188DC50 8008A688 02006214 */  bne        $v1, $v0, .Llevel_20_8008A694
/* 188DC54 8008A68C 00000000 */   nop
/* 188DC58 8008A690 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_20_8008A694:
/* 188DC5C 8008A694 36006386 */  lh         $v1, 0x36($s3)
/* 188DC60 8008A698 55000224 */  addiu      $v0, $zero, 0x55
/* 188DC64 8008A69C 05006214 */  bne        $v1, $v0, .Llevel_20_8008A6B4
/* 188DC68 8008A6A0 56000224 */   addiu     $v0, $zero, 0x56
/* 188DC6C 8008A6A4 03000224 */  addiu      $v0, $zero, 0x3
/* 188DC70 8008A6A8 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 188DC74 8008A6AC 36006386 */  lh         $v1, 0x36($s3)
/* 188DC78 8008A6B0 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_20_8008A6B4:
/* 188DC7C 8008A6B4 02006214 */  bne        $v1, $v0, .Llevel_20_8008A6C0
/* 188DC80 8008A6B8 04000224 */   addiu     $v0, $zero, 0x4
/* 188DC84 8008A6BC 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_20_8008A6C0:
/* 188DC88 8008A6C0 36006386 */  lh         $v1, 0x36($s3)
/* 188DC8C 8008A6C4 57000224 */  addiu      $v0, $zero, 0x57
/* 188DC90 8008A6C8 CD016214 */  bne        $v1, $v0, .Llevel_20_8008AE00
/* 188DC94 8008A6CC 21106002 */   addu      $v0, $s3, $zero
/* 188DC98 8008A6D0 05000224 */  addiu      $v0, $zero, 0x5
/* 188DC9C 8008A6D4 7F2B0208 */  j          .Llevel_20_8008ADFC
/* 188DCA0 8008A6D8 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_20_8008A6DC:
/* 188DCA4 8008A6DC 0000708E */  lw         $s0, 0x0($s3)
/* 188DCA8 8008A6E0 C8E9000C */  jal        func_8003A720
/* 188DCAC 8008A6E4 21206002 */   addu      $a0, $s3, $zero
/* 188DCB0 8008A6E8 AA49010C */  jal        func_800526A8
/* 188DCB4 8008A6EC 21206002 */   addu      $a0, $s3, $zero
/* 188DCB8 8008A6F0 490060A2 */  sb         $zero, 0x49($s3)
/* 188DCBC 8008A6F4 000000AE */  sw         $zero, 0x0($s0)
/* 188DCC0 8008A6F8 080000A6 */  sh         $zero, 0x8($s0)
/* 188DCC4 8008A6FC 060000A6 */  sh         $zero, 0x6($s0)
/* 188DCC8 8008A700 040000A6 */  sh         $zero, 0x4($s0)
/* 188DCCC 8008A704 0C0000AE */  sw         $zero, 0xC($s0)
/* 188DCD0 8008A708 BC01A012 */  beqz       $s5, .Llevel_20_8008ADFC
/* 188DCD4 8008A70C 100000AE */   sw        $zero, 0x10($s0)
/* 188DCD8 8008A710 0C006426 */  addiu      $a0, $s3, 0xC
/* 188DCDC 8008A714 C05D000C */  jal        VecCopy
/* 188DCE0 8008A718 0C00A526 */   addiu     $a1, $s5, 0xC
/* 188DCE4 8008A71C 802B0208 */  j          .Llevel_20_8008AE00
/* 188DCE8 8008A720 21106002 */   addu      $v0, $s3, $zero
.Llevel_20_8008A724:
/* 188DCEC 8008A724 0000748E */  lw         $s4, 0x0($s3)
/* 188DCF0 8008A728 C8E9000C */  jal        func_8003A720
/* 188DCF4 8008A72C 21206002 */   addu      $a0, $s3, $zero
/* 188DCF8 8008A730 0C006426 */  addiu      $a0, $s3, 0xC
/* 188DCFC 8008A734 0C00A526 */  addiu      $a1, $s5, 0xC
/* 188DD00 8008A738 20000224 */  addiu      $v0, $zero, 0x20
/* 188DD04 8008A73C C05D000C */  jal        VecCopy
/* 188DD08 8008A740 500062A2 */   sb        $v0, 0x50($s3)
/* 188DD0C 8008A744 AA49010C */  jal        func_800526A8
/* 188DD10 8008A748 21206002 */   addu      $a0, $s3, $zero
/* 188DD14 8008A74C CB89010C */  jal        rand
/* 188DD18 8008A750 00000000 */   nop
/* 188DD1C 8008A754 CB89010C */  jal        rand
/* 188DD20 8008A758 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 188DD24 8008A75C FF075130 */  andi       $s1, $v0, 0x7FF
/* 188DD28 8008A760 2C5B000C */  jal        Cos
/* 188DD2C 8008A764 21202002 */   addu      $a0, $s1, $zero
/* 188DD30 8008A768 21204002 */  addu       $a0, $s2, $zero
/* 188DD34 8008A76C 2C5B000C */  jal        Cos
/* 188DD38 8008A770 21804000 */   addu      $s0, $v0, $zero
/* 188DD3C 8008A774 43811000 */  sra        $s0, $s0, 5
/* 188DD40 8008A778 18000202 */  mult       $s0, $v0
/* 188DD44 8008A77C 21202002 */  addu       $a0, $s1, $zero
/* 188DD48 8008A780 12380000 */  mflo       $a3
/* 188DD4C 8008A784 03130700 */  sra        $v0, $a3, 12
/* 188DD50 8008A788 2C5B000C */  jal        Cos
/* 188DD54 8008A78C 000082A6 */   sh        $v0, 0x0($s4)
/* 188DD58 8008A790 21204002 */  addu       $a0, $s2, $zero
/* 188DD5C 8008A794 165B000C */  jal        Sin
/* 188DD60 8008A798 21804000 */   addu      $s0, $v0, $zero
/* 188DD64 8008A79C 43811000 */  sra        $s0, $s0, 5
/* 188DD68 8008A7A0 18000202 */  mult       $s0, $v0
/* 188DD6C 8008A7A4 21202002 */  addu       $a0, $s1, $zero
/* 188DD70 8008A7A8 12380000 */  mflo       $a3
/* 188DD74 8008A7AC 03130700 */  sra        $v0, $a3, 12
/* 188DD78 8008A7B0 165B000C */  jal        Sin
/* 188DD7C 8008A7B4 020082A6 */   sh        $v0, 0x2($s4)
/* 188DD80 8008A7B8 43110200 */  sra        $v0, $v0, 5
/* 188DD84 8008A7BC 040082A6 */  sh         $v0, 0x4($s4)
/* 188DD88 8008A7C0 1800A28E */  lw         $v0, 0x18($s5)
/* 188DD8C 8008A7C4 0200033C */  lui        $v1, (0x20000 >> 16)
/* 188DD90 8008A7C8 24104300 */  and        $v0, $v0, $v1
/* 188DD94 8008A7CC 13004010 */  beqz       $v0, .Llevel_20_8008A81C
/* 188DD98 8008A7D0 00000000 */   nop
/* 188DD9C 8008A7D4 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 188DDA0 8008A7D8 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 188DDA4 8008A7DC 00008396 */  lhu        $v1, 0x0($s4)
/* 188DDA8 8008A7E0 83110200 */  sra        $v0, $v0, 6
/* 188DDAC 8008A7E4 21186200 */  addu       $v1, $v1, $v0
/* 188DDB0 8008A7E8 000083A6 */  sh         $v1, 0x0($s4)
/* 188DDB4 8008A7EC 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 188DDB8 8008A7F0 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 188DDBC 8008A7F4 02008396 */  lhu        $v1, 0x2($s4)
/* 188DDC0 8008A7F8 83110200 */  sra        $v0, $v0, 6
/* 188DDC4 8008A7FC 21186200 */  addu       $v1, $v1, $v0
/* 188DDC8 8008A800 020083A6 */  sh         $v1, 0x2($s4)
/* 188DDCC 8008A804 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 188DDD0 8008A808 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 188DDD4 8008A80C 04008396 */  lhu        $v1, 0x4($s4)
/* 188DDD8 8008A810 83110200 */  sra        $v0, $v0, 6
/* 188DDDC 8008A814 21186200 */  addu       $v1, $v1, $v0
/* 188DDE0 8008A818 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_20_8008A81C:
/* 188DDE4 8008A81C 00008286 */  lh         $v0, 0x0($s4)
/* 188DDE8 8008A820 0C00638E */  lw         $v1, 0xC($s3)
/* 188DDEC 8008A824 80100200 */  sll        $v0, $v0, 2
/* 188DDF0 8008A828 21186200 */  addu       $v1, $v1, $v0
/* 188DDF4 8008A82C 0C0063AE */  sw         $v1, 0xC($s3)
/* 188DDF8 8008A830 02008286 */  lh         $v0, 0x2($s4)
/* 188DDFC 8008A834 1000638E */  lw         $v1, 0x10($s3)
/* 188DE00 8008A838 80100200 */  sll        $v0, $v0, 2
/* 188DE04 8008A83C 21186200 */  addu       $v1, $v1, $v0
/* 188DE08 8008A840 100063AE */  sw         $v1, 0x10($s3)
/* 188DE0C 8008A844 04008286 */  lh         $v0, 0x4($s4)
/* 188DE10 8008A848 1400638E */  lw         $v1, 0x14($s3)
/* 188DE14 8008A84C 80100200 */  sll        $v0, $v0, 2
/* 188DE18 8008A850 21186200 */  addu       $v1, $v1, $v0
/* 188DE1C 8008A854 CB89010C */  jal        rand
/* 188DE20 8008A858 140063AE */   sw        $v1, 0x14($s3)
/* 188DE24 8008A85C 0F004230 */  andi       $v0, $v0, 0xF
/* 188DE28 8008A860 CB89010C */  jal        rand
/* 188DE2C 8008A864 060082A6 */   sh        $v0, 0x6($s4)
/* 188DE30 8008A868 0F004230 */  andi       $v0, $v0, 0xF
/* 188DE34 8008A86C CB89010C */  jal        rand
/* 188DE38 8008A870 080082A6 */   sh        $v0, 0x8($s4)
/* 188DE3C 8008A874 0F004230 */  andi       $v0, $v0, 0xF
/* 188DE40 8008A878 0A0082A6 */  sh         $v0, 0xA($s4)
/* 188DE44 8008A87C 1400A28E */  lw         $v0, 0x14($s5)
/* 188DE48 8008A880 00000000 */  nop
/* 188DE4C 8008A884 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 188DE50 8008A888 CB89010C */  jal        rand
/* 188DE54 8008A88C 100082AE */   sw        $v0, 0x10($s4)
/* 188DE58 8008A890 0F004230 */  andi       $v0, $v0, 0xF
/* 188DE5C 8008A894 40000324 */  addiu      $v1, $zero, 0x40
/* 188DE60 8008A898 23186200 */  subu       $v1, $v1, $v0
/* 188DE64 8008A89C 0C0083AE */  sw         $v1, 0xC($s4)
/* 188DE68 8008A8A0 36006296 */  lhu        $v0, 0x36($s3)
/* 188DE6C 8008A8A4 00000000 */  nop
/* 188DE70 8008A8A8 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 188DE74 8008A8AC 0300422C */  sltiu      $v0, $v0, 0x3
/* 188DE78 8008A8B0 52014010 */  beqz       $v0, .Llevel_20_8008ADFC
/* 188DE7C 8008A8B4 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 188DE80 8008A8B8 4B006292 */  lbu        $v0, 0x4B($s3)
/* 188DE84 8008A8BC 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 188DE88 8008A8C0 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_20_8008A8C4:
/* 188DE8C 8008A8C4 80004234 */  ori        $v0, $v0, 0x80
/* 188DE90 8008A8C8 7F2B0208 */  j          .Llevel_20_8008ADFC
/* 188DE94 8008A8CC 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_20_8008A8D0:
/* 188DE98 8008A8D0 0000718E */  lw         $s1, 0x0($s3)
/* 188DE9C 8008A8D4 C8E9000C */  jal        func_8003A720
/* 188DEA0 8008A8D8 21206002 */   addu      $a0, $s3, $zero
/* 188DEA4 8008A8DC 21206002 */  addu       $a0, $s3, $zero
/* 188DEA8 8008A8E0 20000224 */  addiu      $v0, $zero, 0x20
/* 188DEAC 8008A8E4 500062A2 */  sb         $v0, 0x50($s3)
/* 188DEB0 8008A8E8 FF000224 */  addiu      $v0, $zero, 0xFF
/* 188DEB4 8008A8EC 734A010C */  jal        func_800529CC
/* 188DEB8 8008A8F0 520062A2 */   sb        $v0, 0x52($s3)
/* 188DEBC 8008A8F4 0E000224 */  addiu      $v0, $zero, 0xE
/* 188DEC0 8008A8F8 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 188DEC4 8008A8FC 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 188DEC8 8008A900 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 188DECC 8008A904 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 188DED0 8008A908 0780033C */  lui        $v1, %hi(g_DragonCutscene + 0x28)
/* 188DED4 8008A90C 5870638C */  lw         $v1, %lo(g_DragonCutscene + 0x28)($v1)
/* 188DED8 8008A910 03000224 */  addiu      $v0, $zero, 0x3
/* 188DEDC 8008A914 03006214 */  bne        $v1, $v0, .Llevel_20_8008A924
/* 188DEE0 8008A918 01000224 */   addiu     $v0, $zero, 0x1
/* 188DEE4 8008A91C 4B2A0208 */  j          .Llevel_20_8008A92C
/* 188DEE8 8008A920 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_20_8008A924:
/* 188DEEC 8008A924 02006214 */  bne        $v1, $v0, .Llevel_20_8008A930
/* 188DEF0 8008A928 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_20_8008A92C:
/* 188DEF4 8008A92C 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_20_8008A930:
/* 188DEF8 8008A930 CB89010C */  jal        rand
/* 188DEFC 8008A934 00000000 */   nop
/* 188DF00 8008A938 2000A426 */  addiu      $a0, $s5, 0x20
/* 188DF04 8008A93C 07004230 */  andi       $v0, $v0, 0x7
/* 188DF08 8008A940 80100200 */  sll        $v0, $v0, 2
/* 188DF0C 8008A944 2000B027 */  addiu      $s0, $sp, 0x20
/* 188DF10 8008A948 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 188DF14 8008A94C 21082200 */  addu       $at, $at, $v0
/* 188DF18 8008A950 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 188DF1C 8008A954 21280002 */  addu       $a1, $s0, $zero
/* 188DF20 8008A958 2400A0AF */  sw         $zero, 0x24($sp)
/* 188DF24 8008A95C 2000A3AF */  sw         $v1, 0x20($sp)
/* 188DF28 8008A960 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 188DF2C 8008A964 21082200 */  addu       $at, $at, $v0
/* 188DF30 8008A968 A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 188DF34 8008A96C 21300002 */  addu       $a2, $s0, $zero
/* 188DF38 8008A970 125C000C */  jal        VecRotateByMatrix
/* 188DF3C 8008A974 2800A2AF */   sw        $v0, 0x28($sp)
/* 188DF40 8008A978 CB89010C */  jal        rand
/* 188DF44 8008A97C 00000000 */   nop
/* 188DF48 8008A980 2000A38F */  lw         $v1, 0x20($sp)
/* 188DF4C 8008A984 7F004230 */  andi       $v0, $v0, 0x7F
/* 188DF50 8008A988 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 188DF54 8008A98C 21186200 */  addu       $v1, $v1, $v0
/* 188DF58 8008A990 CB89010C */  jal        rand
/* 188DF5C 8008A994 2000A3AF */   sw        $v1, 0x20($sp)
/* 188DF60 8008A998 2400A38F */  lw         $v1, 0x24($sp)
/* 188DF64 8008A99C 7F004230 */  andi       $v0, $v0, 0x7F
/* 188DF68 8008A9A0 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 188DF6C 8008A9A4 21186200 */  addu       $v1, $v1, $v0
/* 188DF70 8008A9A8 CB89010C */  jal        rand
/* 188DF74 8008A9AC 2400A3AF */   sw        $v1, 0x24($sp)
/* 188DF78 8008A9B0 0C006426 */  addiu      $a0, $s3, 0xC
/* 188DF7C 8008A9B4 0C00A526 */  addiu      $a1, $s5, 0xC
/* 188DF80 8008A9B8 21300002 */  addu       $a2, $s0, $zero
/* 188DF84 8008A9BC 2800A38F */  lw         $v1, 0x28($sp)
/* 188DF88 8008A9C0 7F004230 */  andi       $v0, $v0, 0x7F
/* 188DF8C 8008A9C4 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 188DF90 8008A9C8 21186200 */  addu       $v1, $v1, $v0
/* 188DF94 8008A9CC D65D000C */  jal        VecAdd
/* 188DF98 8008A9D0 2800A3AF */   sw        $v1, 0x28($sp)
/* 188DF9C 8008A9D4 21202002 */  addu       $a0, $s1, $zero
/* 188DFA0 8008A9D8 C05D000C */  jal        VecCopy
/* 188DFA4 8008A9DC 21280002 */   addu      $a1, $s0, $zero
/* 188DFA8 8008A9E0 21202002 */  addu       $a0, $s1, $zero
/* 188DFAC 8008A9E4 B25D000C */  jal        VecShiftRight
/* 188DFB0 8008A9E8 02000524 */   addiu     $a1, $zero, 0x2
/* 188DFB4 8008A9EC CB89010C */  jal        rand
/* 188DFB8 8008A9F0 00000000 */   nop
/* 188DFBC 8008A9F4 0000238E */  lw         $v1, 0x0($s1)
/* 188DFC0 8008A9F8 FF004230 */  andi       $v0, $v0, 0xFF
/* 188DFC4 8008A9FC 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 188DFC8 8008AA00 21186200 */  addu       $v1, $v1, $v0
/* 188DFCC 8008AA04 CB89010C */  jal        rand
/* 188DFD0 8008AA08 000023AE */   sw        $v1, 0x0($s1)
/* 188DFD4 8008AA0C 0400238E */  lw         $v1, 0x4($s1)
/* 188DFD8 8008AA10 FF004230 */  andi       $v0, $v0, 0xFF
/* 188DFDC 8008AA14 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 188DFE0 8008AA18 21186200 */  addu       $v1, $v1, $v0
/* 188DFE4 8008AA1C CB89010C */  jal        rand
/* 188DFE8 8008AA20 040023AE */   sw        $v1, 0x4($s1)
/* 188DFEC 8008AA24 0800238E */  lw         $v1, 0x8($s1)
/* 188DFF0 8008AA28 FF004230 */  andi       $v0, $v0, 0xFF
/* 188DFF4 8008AA2C 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 188DFF8 8008AA30 21186200 */  addu       $v1, $v1, $v0
/* 188DFFC 8008AA34 CB89010C */  jal        rand
/* 188E000 8008AA38 080023AE */   sw        $v1, 0x8($s1)
/* 188E004 8008AA3C CB89010C */  jal        rand
/* 188E008 8008AA40 440062A2 */   sb        $v0, 0x44($s3)
/* 188E00C 8008AA44 CB89010C */  jal        rand
/* 188E010 8008AA48 450062A2 */   sb        $v0, 0x45($s3)
/* 188E014 8008AA4C CB89010C */  jal        rand
/* 188E018 8008AA50 460062A2 */   sb        $v0, 0x46($s3)
/* 188E01C 8008AA54 0F004230 */  andi       $v0, $v0, 0xF
/* 188E020 8008AA58 CB89010C */  jal        rand
/* 188E024 8008AA5C 100022A2 */   sb        $v0, 0x10($s1)
/* 188E028 8008AA60 0F004230 */  andi       $v0, $v0, 0xF
/* 188E02C 8008AA64 CB89010C */  jal        rand
/* 188E030 8008AA68 110022A2 */   sb        $v0, 0x11($s1)
/* 188E034 8008AA6C 0F004230 */  andi       $v0, $v0, 0xF
/* 188E038 8008AA70 120022A2 */  sb         $v0, 0x12($s1)
/* 188E03C 8008AA74 1400A28E */  lw         $v0, 0x14($s5)
/* 188E040 8008AA78 CB89010C */  jal        rand
/* 188E044 8008AA7C 0C0022AE */   sw        $v0, 0xC($s1)
/* 188E048 8008AA80 03004230 */  andi       $v0, $v0, 0x3
/* 188E04C 8008AA84 10004224 */  addiu      $v0, $v0, 0x10
/* 188E050 8008AA88 7F2B0208 */  j          .Llevel_20_8008ADFC
/* 188E054 8008AA8C 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_20_8008AA90:
/* 188E058 8008AA90 0000708E */  lw         $s0, 0x0($s3)
/* 188E05C 8008AA94 C8E9000C */  jal        func_8003A720
/* 188E060 8008AA98 21206002 */   addu      $a0, $s3, $zero
/* 188E064 8008AA9C 734A010C */  jal        func_800529CC
/* 188E068 8008AAA0 21206002 */   addu      $a0, $s3, $zero
/* 188E06C 8008AAA4 02000224 */  addiu      $v0, $zero, 0x2
/* 188E070 8008AAA8 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 188E074 8008AAAC 40000224 */  addiu      $v0, $zero, 0x40
/* 188E078 8008AAB0 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 188E07C 8008AAB4 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 188E080 8008AAB8 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 188E084 8008AABC 7F2B0208 */  j          .Llevel_20_8008ADFC
/* 188E088 8008AAC0 000002AE */   sw        $v0, 0x0($s0)
.Llevel_20_8008AAC4:
/* 188E08C 8008AAC4 C8E9000C */  jal        func_8003A720
/* 188E090 8008AAC8 21206002 */   addu      $a0, $s3, $zero
/* 188E094 8008AACC 21206002 */  addu       $a0, $s3, $zero
/* 188E098 8008AAD0 FF000224 */  addiu      $v0, $zero, 0xFF
/* 188E09C 8008AAD4 500062A2 */  sb         $v0, 0x50($s3)
/* 188E0A0 8008AAD8 CC010224 */  addiu      $v0, $zero, 0x1CC
/* 188E0A4 8008AADC 0C0062AE */  sw         $v0, 0xC($s3)
/* 188E0A8 8008AAE0 28000224 */  addiu      $v0, $zero, 0x28
/* 188E0AC 8008AAE4 100062AE */  sw         $v0, 0x10($s3)
/* 188E0B0 8008AAE8 00100224 */  addiu      $v0, $zero, 0x1000
/* 188E0B4 8008AAEC 734A010C */  jal        func_800529CC
/* 188E0B8 8008AAF0 140062AE */   sw        $v0, 0x14($s3)
/* 188E0BC 8008AAF4 20000224 */  addiu      $v0, $zero, 0x20
/* 188E0C0 8008AAF8 470062A2 */  sb         $v0, 0x47($s3)
/* 188E0C4 8008AAFC 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 188E0C8 8008AB00 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 188E0CC 8008AB04 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 188E0D0 8008AB08 7F2B0208 */  j          .Llevel_20_8008ADFC
/* 188E0D4 8008AB0C 4F0060A2 */   sb        $zero, 0x4F($s3)
.Llevel_20_8008AB10:
/* 188E0D8 8008AB10 C8E9000C */  jal        func_8003A720
/* 188E0DC 8008AB14 21206002 */   addu      $a0, $s3, $zero
/* 188E0E0 8008AB18 0300A012 */  beqz       $s5, .Llevel_20_8008AB28
/* 188E0E4 8008AB1C 0C006426 */   addiu     $a0, $s3, 0xC
/* 188E0E8 8008AB20 CC2A0208 */  j          .Llevel_20_8008AB30
/* 188E0EC 8008AB24 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_20_8008AB28:
/* 188E0F0 8008AB28 0880053C */  lui        $a1, %hi(g_Spyro)
/* 188E0F4 8008AB2C 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_20_8008AB30:
/* 188E0F8 8008AB30 C05D000C */  jal        VecCopy
/* 188E0FC 8008AB34 00000000 */   nop
/* 188E100 8008AB38 0C006426 */  addiu      $a0, $s3, 0xC
/* 188E104 8008AB3C 1400628E */  lw         $v0, 0x14($s3)
/* 188E108 8008AB40 00080524 */  addiu      $a1, $zero, 0x800
/* 188E10C 8008AB44 00024224 */  addiu      $v0, $v0, 0x200
/* 188E110 8008AB48 7B35010C */  jal        func_8004D5EC
/* 188E114 8008AB4C 140062AE */   sw        $v0, 0x14($s3)
/* 188E118 8008AB50 1400648E */  lw         $a0, 0x14($s3)
/* 188E11C 8008AB54 21184000 */  addu       $v1, $v0, $zero
/* 188E120 8008AB58 23106400 */  subu       $v0, $v1, $a0
/* 188E124 8008AB5C 02004104 */  bgez       $v0, .Llevel_20_8008AB68
/* 188E128 8008AB60 00000000 */   nop
/* 188E12C 8008AB64 23100200 */  negu       $v0, $v0
.Llevel_20_8008AB68:
/* 188E130 8008AB68 00084228 */  slti       $v0, $v0, 0x800
/* 188E134 8008AB6C 03004010 */  beqz       $v0, .Llevel_20_8008AB7C
/* 188E138 8008AB70 00FE8224 */   addiu     $v0, $a0, -0x200
/* 188E13C 8008AB74 7D2B0208 */  j          .Llevel_20_8008ADF4
/* 188E140 8008AB78 140063AE */   sw        $v1, 0x14($s3)
.Llevel_20_8008AB7C:
/* 188E144 8008AB7C 7D2B0208 */  j          .Llevel_20_8008ADF4
/* 188E148 8008AB80 140062AE */   sw        $v0, 0x14($s3)
.Llevel_20_8008AB84:
/* 188E14C 8008AB84 A0F60424 */  addiu      $a0, $zero, -0x960
/* 188E150 8008AB88 A8DF000C */  jal        RandRange
/* 188E154 8008AB8C 78050524 */   addiu     $a1, $zero, 0x578
/* 188E158 8008AB90 21206002 */  addu       $a0, $s3, $zero
/* 188E15C 8008AB94 0000708E */  lw         $s0, 0x0($s3)
/* 188E160 8008AB98 C8E9000C */  jal        func_8003A720
/* 188E164 8008AB9C 21884000 */   addu      $s1, $v0, $zero
/* 188E168 8008ABA0 0C006426 */  addiu      $a0, $s3, 0xC
/* 188E16C 8008ABA4 C05D000C */  jal        VecCopy
/* 188E170 8008ABA8 0C00A526 */   addiu     $a1, $s5, 0xC
/* 188E174 8008ABAC AA49010C */  jal        func_800526A8
/* 188E178 8008ABB0 21206002 */   addu      $a0, $s3, $zero
/* 188E17C 8008ABB4 CB89010C */  jal        rand
/* 188E180 8008ABB8 00000000 */   nop
/* 188E184 8008ABBC 88FF0424 */  addiu      $a0, $zero, -0x78
/* 188E188 8008ABC0 A8DF000C */  jal        RandRange
/* 188E18C 8008ABC4 78000524 */   addiu     $a1, $zero, 0x78
/* 188E190 8008ABC8 88FF0424 */  addiu      $a0, $zero, -0x78
/* 188E194 8008ABCC 78000524 */  addiu      $a1, $zero, 0x78
/* 188E198 8008ABD0 A8DF000C */  jal        RandRange
/* 188E19C 8008ABD4 000002A6 */   sh        $v0, 0x0($s0)
/* 188E1A0 8008ABD8 32000424 */  addiu      $a0, $zero, 0x32
/* 188E1A4 8008ABDC F0000524 */  addiu      $a1, $zero, 0xF0
/* 188E1A8 8008ABE0 A8DF000C */  jal        RandRange
/* 188E1AC 8008ABE4 020002A6 */   sh        $v0, 0x2($s0)
/* 188E1B0 8008ABE8 040002A6 */  sh         $v0, 0x4($s0)
/* 188E1B4 8008ABEC 00000286 */  lh         $v0, 0x0($s0)
/* 188E1B8 8008ABF0 0C00638E */  lw         $v1, 0xC($s3)
/* 188E1BC 8008ABF4 80100200 */  sll        $v0, $v0, 2
/* 188E1C0 8008ABF8 21186200 */  addu       $v1, $v1, $v0
/* 188E1C4 8008ABFC 0C0063AE */  sw         $v1, 0xC($s3)
/* 188E1C8 8008AC00 02000286 */  lh         $v0, 0x2($s0)
/* 188E1CC 8008AC04 1000638E */  lw         $v1, 0x10($s3)
/* 188E1D0 8008AC08 80100200 */  sll        $v0, $v0, 2
/* 188E1D4 8008AC0C 21186200 */  addu       $v1, $v1, $v0
/* 188E1D8 8008AC10 100063AE */  sw         $v1, 0x10($s3)
/* 188E1DC 8008AC14 04000386 */  lh         $v1, 0x4($s0)
/* 188E1E0 8008AC18 1400628E */  lw         $v0, 0x14($s3)
/* 188E1E4 8008AC1C 80180300 */  sll        $v1, $v1, 2
/* 188E1E8 8008AC20 21104300 */  addu       $v0, $v0, $v1
/* 188E1EC 8008AC24 21105100 */  addu       $v0, $v0, $s1
/* 188E1F0 8008AC28 23881100 */  negu       $s1, $s1
/* 188E1F4 8008AC2C 140062AE */  sw         $v0, 0x14($s3)
/* 188E1F8 8008AC30 00000286 */  lh         $v0, 0x0($s0)
/* 188E1FC 8008AC34 40063126 */  addiu      $s1, $s1, 0x640
/* 188E200 8008AC38 18005100 */  mult       $v0, $s1
/* 188E204 8008AC3C 0C00628E */  lw         $v0, 0xC($s3)
/* 188E208 8008AC40 12380000 */  mflo       $a3
/* 188E20C 8008AC44 831A0700 */  sra        $v1, $a3, 10
/* 188E210 8008AC48 21104300 */  addu       $v0, $v0, $v1
/* 188E214 8008AC4C 0C0062AE */  sw         $v0, 0xC($s3)
/* 188E218 8008AC50 02000286 */  lh         $v0, 0x2($s0)
/* 188E21C 8008AC54 00000000 */  nop
/* 188E220 8008AC58 18005100 */  mult       $v0, $s1
/* 188E224 8008AC5C 1000628E */  lw         $v0, 0x10($s3)
/* 188E228 8008AC60 12380000 */  mflo       $a3
/* 188E22C 8008AC64 831A0700 */  sra        $v1, $a3, 10
/* 188E230 8008AC68 21104300 */  addu       $v0, $v0, $v1
/* 188E234 8008AC6C CB89010C */  jal        rand
/* 188E238 8008AC70 100062AE */   sw        $v0, 0x10($s3)
/* 188E23C 8008AC74 0F004230 */  andi       $v0, $v0, 0xF
/* 188E240 8008AC78 CB89010C */  jal        rand
/* 188E244 8008AC7C 060002A6 */   sh        $v0, 0x6($s0)
/* 188E248 8008AC80 0F004230 */  andi       $v0, $v0, 0xF
/* 188E24C 8008AC84 CB89010C */  jal        rand
/* 188E250 8008AC88 080002A6 */   sh        $v0, 0x8($s0)
/* 188E254 8008AC8C 0F004230 */  andi       $v0, $v0, 0xF
/* 188E258 8008AC90 0A0002A6 */  sh         $v0, 0xA($s0)
/* 188E25C 8008AC94 A0000224 */  addiu      $v0, $zero, 0xA0
/* 188E260 8008AC98 7F2B0208 */  j          .Llevel_20_8008ADFC
/* 188E264 8008AC9C 0C0002AE */   sw        $v0, 0xC($s0)
.Llevel_20_8008ACA0:
/* 188E268 8008ACA0 C8E9000C */  jal        func_8003A720
/* 188E26C 8008ACA4 21206002 */   addu      $a0, $s3, $zero
/* 188E270 8008ACA8 21206002 */  addu       $a0, $s3, $zero
/* 188E274 8008ACAC 20000224 */  addiu      $v0, $zero, 0x20
/* 188E278 8008ACB0 500062A2 */  sb         $v0, 0x50($s3)
/* 188E27C 8008ACB4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 188E280 8008ACB8 734A010C */  jal        func_800529CC
/* 188E284 8008ACBC 520062A2 */   sb        $v0, 0x52($s3)
/* 188E288 8008ACC0 802B0208 */  j          .Llevel_20_8008AE00
/* 188E28C 8008ACC4 21106002 */   addu      $v0, $s3, $zero
.Llevel_20_8008ACC8:
/* 188E290 8008ACC8 0000708E */  lw         $s0, 0x0($s3)
/* 188E294 8008ACCC C8E9000C */  jal        func_8003A720
/* 188E298 8008ACD0 21206002 */   addu      $a0, $s3, $zero
/* 188E29C 8008ACD4 0C006426 */  addiu      $a0, $s3, 0xC
/* 188E2A0 8008ACD8 0C00A526 */  addiu      $a1, $s5, 0xC
/* 188E2A4 8008ACDC 20000224 */  addiu      $v0, $zero, 0x20
/* 188E2A8 8008ACE0 C05D000C */  jal        VecCopy
/* 188E2AC 8008ACE4 500062A2 */   sb        $v0, 0x50($s3)
/* 188E2B0 8008ACE8 AA49010C */  jal        func_800526A8
/* 188E2B4 8008ACEC 21206002 */   addu      $a0, $s3, $zero
/* 188E2B8 8008ACF0 3600A386 */  lh         $v1, 0x36($s5)
/* 188E2BC 8008ACF4 B0000224 */  addiu      $v0, $zero, 0xB0
/* 188E2C0 8008ACF8 0B006214 */  bne        $v1, $v0, .Llevel_20_8008AD28
/* 188E2C4 8008ACFC 6AFF0424 */   addiu     $a0, $zero, -0x96
/* 188E2C8 8008AD00 9CFF0424 */  addiu      $a0, $zero, -0x64
/* 188E2CC 8008AD04 A8DF000C */  jal        RandRange
/* 188E2D0 8008AD08 64000524 */   addiu     $a1, $zero, 0x64
/* 188E2D4 8008AD0C 9CFF0424 */  addiu      $a0, $zero, -0x64
/* 188E2D8 8008AD10 64000524 */  addiu      $a1, $zero, 0x64
/* 188E2DC 8008AD14 A8DF000C */  jal        RandRange
/* 188E2E0 8008AD18 000002A6 */   sh        $v0, 0x0($s0)
/* 188E2E4 8008AD1C C4FF0424 */  addiu      $a0, $zero, -0x3C
/* 188E2E8 8008AD20 522B0208 */  j          .Llevel_20_8008AD48
/* 188E2EC 8008AD24 6E000524 */   addiu     $a1, $zero, 0x6E
.Llevel_20_8008AD28:
/* 188E2F0 8008AD28 A8DF000C */  jal        RandRange
/* 188E2F4 8008AD2C 96000524 */   addiu     $a1, $zero, 0x96
/* 188E2F8 8008AD30 6AFF0424 */  addiu      $a0, $zero, -0x96
/* 188E2FC 8008AD34 96000524 */  addiu      $a1, $zero, 0x96
/* 188E300 8008AD38 A8DF000C */  jal        RandRange
/* 188E304 8008AD3C 000002A6 */   sh        $v0, 0x0($s0)
/* 188E308 8008AD40 BAFF0424 */  addiu      $a0, $zero, -0x46
/* 188E30C 8008AD44 96000524 */  addiu      $a1, $zero, 0x96
.Llevel_20_8008AD48:
/* 188E310 8008AD48 A8DF000C */  jal        RandRange
/* 188E314 8008AD4C 020002A6 */   sh        $v0, 0x2($s0)
/* 188E318 8008AD50 040002A6 */  sh         $v0, 0x4($s0)
/* 188E31C 8008AD54 00000286 */  lh         $v0, 0x0($s0)
/* 188E320 8008AD58 0C00638E */  lw         $v1, 0xC($s3)
/* 188E324 8008AD5C 80100200 */  sll        $v0, $v0, 2
/* 188E328 8008AD60 21186200 */  addu       $v1, $v1, $v0
/* 188E32C 8008AD64 0C0063AE */  sw         $v1, 0xC($s3)
/* 188E330 8008AD68 02000286 */  lh         $v0, 0x2($s0)
/* 188E334 8008AD6C 1000638E */  lw         $v1, 0x10($s3)
/* 188E338 8008AD70 80100200 */  sll        $v0, $v0, 2
/* 188E33C 8008AD74 21186200 */  addu       $v1, $v1, $v0
/* 188E340 8008AD78 100063AE */  sw         $v1, 0x10($s3)
/* 188E344 8008AD7C 04000286 */  lh         $v0, 0x4($s0)
/* 188E348 8008AD80 1400638E */  lw         $v1, 0x14($s3)
/* 188E34C 8008AD84 80100200 */  sll        $v0, $v0, 2
/* 188E350 8008AD88 21186200 */  addu       $v1, $v1, $v0
/* 188E354 8008AD8C CB89010C */  jal        rand
/* 188E358 8008AD90 140063AE */   sw        $v1, 0x14($s3)
/* 188E35C 8008AD94 0F004230 */  andi       $v0, $v0, 0xF
/* 188E360 8008AD98 CB89010C */  jal        rand
/* 188E364 8008AD9C 060002A6 */   sh        $v0, 0x6($s0)
/* 188E368 8008ADA0 0F004230 */  andi       $v0, $v0, 0xF
/* 188E36C 8008ADA4 CB89010C */  jal        rand
/* 188E370 8008ADA8 080002A6 */   sh        $v0, 0x8($s0)
/* 188E374 8008ADAC 18000424 */  addiu      $a0, $zero, 0x18
/* 188E378 8008ADB0 23000524 */  addiu      $a1, $zero, 0x23
/* 188E37C 8008ADB4 0F004230 */  andi       $v0, $v0, 0xF
/* 188E380 8008ADB8 A8DF000C */  jal        RandRange
/* 188E384 8008ADBC 0A0002A6 */   sh        $v0, 0xA($s0)
/* 188E388 8008ADC0 7F2B0208 */  j          .Llevel_20_8008ADFC
/* 188E38C 8008ADC4 0C0002AE */   sw        $v0, 0xC($s0)
.Llevel_20_8008ADC8:
/* 188E390 8008ADC8 C8E9000C */  jal        func_8003A720
/* 188E394 8008ADCC 21206002 */   addu      $a0, $s3, $zero
/* 188E398 8008ADD0 0300A012 */  beqz       $s5, .Llevel_20_8008ADE0
/* 188E39C 8008ADD4 0C00A526 */   addiu     $a1, $s5, 0xC
/* 188E3A0 8008ADD8 7B2B0208 */  j          .Llevel_20_8008ADEC
/* 188E3A4 8008ADDC 0C006426 */   addiu     $a0, $s3, 0xC
.Llevel_20_8008ADE0:
/* 188E3A8 8008ADE0 0C006426 */  addiu      $a0, $s3, 0xC
/* 188E3AC 8008ADE4 0880053C */  lui        $a1, %hi(g_Spyro)
/* 188E3B0 8008ADE8 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_20_8008ADEC:
/* 188E3B4 8008ADEC C05D000C */  jal        VecCopy
/* 188E3B8 8008ADF0 00000000 */   nop
.Llevel_20_8008ADF4:
/* 188E3BC 8008ADF4 AA49010C */  jal        func_800526A8
/* 188E3C0 8008ADF8 21206002 */   addu      $a0, $s3, $zero
.Llevel_20_8008ADFC:
/* 188E3C4 8008ADFC 21106002 */  addu       $v0, $s3, $zero
.Llevel_20_8008AE00:
/* 188E3C8 8008AE00 5000BF8F */  lw         $ra, 0x50($sp)
/* 188E3CC 8008AE04 4C00B58F */  lw         $s5, 0x4C($sp)
/* 188E3D0 8008AE08 4800B48F */  lw         $s4, 0x48($sp)
/* 188E3D4 8008AE0C 4400B38F */  lw         $s3, 0x44($sp)
/* 188E3D8 8008AE10 4000B28F */  lw         $s2, 0x40($sp)
/* 188E3DC 8008AE14 3C00B18F */  lw         $s1, 0x3C($sp)
/* 188E3E0 8008AE18 3800B08F */  lw         $s0, 0x38($sp)
/* 188E3E4 8008AE1C 5800BD27 */  addiu      $sp, $sp, 0x58
/* 188E3E8 8008AE20 0800E003 */  jr         $ra
/* 188E3EC 8008AE24 00000000 */   nop
.size func_level_20_8008A258, . - func_level_20_8008A258
