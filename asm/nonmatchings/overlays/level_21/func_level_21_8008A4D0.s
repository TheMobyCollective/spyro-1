.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_21_8008A4D0
/* 1B3EA98 8008A4D0 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 1B3EA9C 8008A4D4 3800B0AF */  sw         $s0, 0x38($sp)
/* 1B3EAA0 8008A4D8 21808000 */  addu       $s0, $a0, $zero
/* 1B3EAA4 8008A4DC 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 1B3EAA8 8008A4E0 21A8A000 */  addu       $s5, $a1, $zero
/* 1B3EAAC 8008A4E4 5000BFAF */  sw         $ra, 0x50($sp)
/* 1B3EAB0 8008A4E8 4800B4AF */  sw         $s4, 0x48($sp)
/* 1B3EAB4 8008A4EC 4400B3AF */  sw         $s3, 0x44($sp)
/* 1B3EAB8 8008A4F0 4000B2AF */  sw         $s2, 0x40($sp)
/* 1B3EABC 8008A4F4 3149010C */  jal        func_800524C4
/* 1B3EAC0 8008A4F8 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 1B3EAC4 8008A4FC 21984000 */  addu       $s3, $v0, $zero
/* 1B3EAC8 8008A500 1400A012 */  beqz       $s5, .Llevel_21_8008A554
/* 1B3EACC 8008A504 360070A6 */   sh        $s0, 0x36($s3)
/* 1B3EAD0 8008A508 0780043C */  lui        $a0, %hi(D_80075828)
/* 1B3EAD4 8008A50C 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 1B3EAD8 8008A510 00000000 */  nop
/* 1B3EADC 8008A514 2320A402 */  subu       $a0, $s5, $a0
/* 1B3EAE0 8008A518 40190400 */  sll        $v1, $a0, 5
/* 1B3EAE4 8008A51C 23186400 */  subu       $v1, $v1, $a0
/* 1B3EAE8 8008A520 40190300 */  sll        $v1, $v1, 5
/* 1B3EAEC 8008A524 21186400 */  addu       $v1, $v1, $a0
/* 1B3EAF0 8008A528 C0100300 */  sll        $v0, $v1, 3
/* 1B3EAF4 8008A52C 21186200 */  addu       $v1, $v1, $v0
/* 1B3EAF8 8008A530 C0130300 */  sll        $v0, $v1, 15
/* 1B3EAFC 8008A534 23104300 */  subu       $v0, $v0, $v1
/* 1B3EB00 8008A538 80100200 */  sll        $v0, $v0, 2
/* 1B3EB04 8008A53C 21104400 */  addu       $v0, $v0, $a0
/* 1B3EB08 8008A540 23100200 */  negu       $v0, $v0
/* 1B3EB0C 8008A544 C3180200 */  sra        $v1, $v0, 3
/* 1B3EB10 8008A548 0001622C */  sltiu      $v0, $v1, 0x100
/* 1B3EB14 8008A54C 03004014 */  bnez       $v0, .Llevel_21_8008A55C
/* 1B3EB18 8008A550 0E01022A */   slti      $v0, $s0, 0x10E
.Llevel_21_8008A554:
/* 1B3EB1C 8008A554 21180000 */  addu       $v1, $zero, $zero
/* 1B3EB20 8008A558 0E01022A */  slti       $v0, $s0, 0x10E
.Llevel_21_8008A55C:
/* 1B3EB24 8008A55C 38004010 */  beqz       $v0, .Llevel_21_8008A640
/* 1B3EB28 8008A560 560063A2 */   sb        $v1, 0x56($s3)
/* 1B3EB2C 8008A564 0401022A */  slti       $v0, $s0, 0x104
/* 1B3EB30 8008A568 F9014010 */  beqz       $v0, .Llevel_21_8008AD50
/* 1B3EB34 8008A56C 5800022A */   slti      $v0, $s0, 0x58
/* 1B3EB38 8008A570 1D004010 */  beqz       $v0, .Llevel_21_8008A5E8
/* 1B3EB3C 8008A574 5300022A */   slti      $v0, $s0, 0x53
/* 1B3EB40 8008A578 A4004010 */  beqz       $v0, .Llevel_21_8008A80C
/* 1B3EB44 8008A57C 22000224 */   addiu     $v0, $zero, 0x22
/* 1B3EB48 8008A580 94000212 */  beq        $s0, $v0, .Llevel_21_8008A7D4
/* 1B3EB4C 8008A584 2300022A */   slti      $v0, $s0, 0x23
/* 1B3EB50 8008A588 0E004010 */  beqz       $v0, .Llevel_21_8008A5C4
/* 1B3EB54 8008A58C 0F000224 */   addiu     $v0, $zero, 0xF
/* 1B3EB58 8008A590 55000212 */  beq        $s0, $v0, .Llevel_21_8008A6E8
/* 1B3EB5C 8008A594 1000022A */   slti      $v0, $s0, 0x10
/* 1B3EB60 8008A598 05004010 */  beqz       $v0, .Llevel_21_8008A5B0
/* 1B3EB64 8008A59C 0E000224 */   addiu     $v0, $zero, 0xE
/* 1B3EB68 8008A5A0 9A000212 */  beq        $s0, $v0, .Llevel_21_8008A80C
/* 1B3EB6C 8008A5A4 00000000 */   nop
/* 1B3EB70 8008A5A8 582C0208 */  j          .Llevel_21_8008B160
/* 1B3EB74 8008A5AC 00000000 */   nop
.Llevel_21_8008A5B0:
/* 1B3EB78 8008A5B0 10000224 */  addiu      $v0, $zero, 0x10
/* 1B3EB7C 8008A5B4 73000212 */  beq        $s0, $v0, .Llevel_21_8008A784
/* 1B3EB80 8008A5B8 00000000 */   nop
/* 1B3EB84 8008A5BC 582C0208 */  j          .Llevel_21_8008B160
/* 1B3EB88 8008A5C0 00000000 */   nop
.Llevel_21_8008A5C4:
/* 1B3EB8C 8008A5C4 4300022A */  slti       $v0, $s0, 0x43
/* 1B3EB90 8008A5C8 E5024014 */  bnez       $v0, .Llevel_21_8008B160
/* 1B3EB94 8008A5CC 4600022A */   slti      $v0, $s0, 0x46
/* 1B3EB98 8008A5D0 04014014 */  bnez       $v0, .Llevel_21_8008A9E4
/* 1B3EB9C 8008A5D4 4C000224 */   addiu     $v0, $zero, 0x4C
/* 1B3EBA0 8008A5D8 97020212 */  beq        $s0, $v0, .Llevel_21_8008B038
/* 1B3EBA4 8008A5DC 00000000 */   nop
/* 1B3EBA8 8008A5E0 582C0208 */  j          .Llevel_21_8008B160
/* 1B3EBAC 8008A5E4 00000000 */   nop
.Llevel_21_8008A5E8:
/* 1B3EBB0 8008A5E8 9A00022A */  slti       $v0, $s0, 0x9A
/* 1B3EBB4 8008A5EC 09004010 */  beqz       $v0, .Llevel_21_8008A614
/* 1B3EBB8 8008A5F0 9800022A */   slti      $v0, $s0, 0x98
/* 1B3EBBC 8008A5F4 ED004010 */  beqz       $v0, .Llevel_21_8008A9AC
/* 1B3EBC0 8008A5F8 78000224 */   addiu     $v0, $zero, 0x78
/* 1B3EBC4 8008A5FC D9000212 */  beq        $s0, $v0, .Llevel_21_8008A964
/* 1B3EBC8 8008A600 97000224 */   addiu     $v0, $zero, 0x97
/* 1B3EBCC 8008A604 F7000212 */  beq        $s0, $v0, .Llevel_21_8008A9E4
/* 1B3EBD0 8008A608 00000000 */   nop
/* 1B3EBD4 8008A60C 582C0208 */  j          .Llevel_21_8008B160
/* 1B3EBD8 8008A610 00000000 */   nop
.Llevel_21_8008A614:
/* 1B3EBDC 8008A614 FB000224 */  addiu      $v0, $zero, 0xFB
/* 1B3EBE0 8008A618 5D010212 */  beq        $s0, $v0, .Llevel_21_8008AB90
/* 1B3EBE4 8008A61C FB00022A */   slti      $v0, $s0, 0xFB
/* 1B3EBE8 8008A620 CF024014 */  bnez       $v0, .Llevel_21_8008B160
/* 1B3EBEC 8008A624 0201022A */   slti      $v0, $s0, 0x102
/* 1B3EBF0 8008A628 CD024010 */  beqz       $v0, .Llevel_21_8008B160
/* 1B3EBF4 8008A62C FF00022A */   slti      $v0, $s0, 0xFF
/* 1B3EBF8 8008A630 EC004010 */  beqz       $v0, .Llevel_21_8008A9E4
/* 1B3EBFC 8008A634 00000000 */   nop
/* 1B3EC00 8008A638 582C0208 */  j          .Llevel_21_8008B160
/* 1B3EC04 8008A63C 00000000 */   nop
.Llevel_21_8008A640:
/* 1B3EC08 8008A640 6D01022A */  slti       $v0, $s0, 0x16D
/* 1B3EC0C 8008A644 14004010 */  beqz       $v0, .Llevel_21_8008A698
/* 1B3EC10 8008A648 6B01022A */   slti      $v0, $s0, 0x16B
/* 1B3EC14 8008A64C 5D024010 */  beqz       $v0, .Llevel_21_8008AFC4
/* 1B3EC18 8008A650 2201022A */   slti      $v0, $s0, 0x122
/* 1B3EC1C 8008A654 07004010 */  beqz       $v0, .Llevel_21_8008A674
/* 1B3EC20 8008A658 2001022A */   slti      $v0, $s0, 0x120
/* 1B3EC24 8008A65C C9014010 */  beqz       $v0, .Llevel_21_8008AD84
/* 1B3EC28 8008A660 15010224 */   addiu     $v0, $zero, 0x115
/* 1B3EC2C 8008A664 BA010212 */  beq        $s0, $v0, .Llevel_21_8008AD50
/* 1B3EC30 8008A668 00000000 */   nop
/* 1B3EC34 8008A66C 582C0208 */  j          .Llevel_21_8008B160
/* 1B3EC38 8008A670 00000000 */   nop
.Llevel_21_8008A674:
/* 1B3EC3C 8008A674 3501022A */  slti       $v0, $s0, 0x135
/* 1B3EC40 8008A678 B9024014 */  bnez       $v0, .Llevel_21_8008B160
/* 1B3EC44 8008A67C 3801022A */   slti      $v0, $s0, 0x138
/* 1B3EC48 8008A680 D8004014 */  bnez       $v0, .Llevel_21_8008A9E4
/* 1B3EC4C 8008A684 47010224 */   addiu     $v0, $zero, 0x147
/* 1B3EC50 8008A688 B1010212 */  beq        $s0, $v0, .Llevel_21_8008AD50
/* 1B3EC54 8008A68C 00000000 */   nop
/* 1B3EC58 8008A690 582C0208 */  j          .Llevel_21_8008B160
/* 1B3EC5C 8008A694 00000000 */   nop
.Llevel_21_8008A698:
/* 1B3EC60 8008A698 C401022A */  slti       $v0, $s0, 0x1C4
/* 1B3EC64 8008A69C 0B004010 */  beqz       $v0, .Llevel_21_8008A6CC
/* 1B3EC68 8008A6A0 AA01022A */   slti      $v0, $s0, 0x1AA
/* 1B3EC6C 8008A6A4 64024010 */  beqz       $v0, .Llevel_21_8008B038
/* 1B3EC70 8008A6A8 88010224 */   addiu     $v0, $zero, 0x188
/* 1B3EC74 8008A6AC 3D020212 */  beq        $s0, $v0, .Llevel_21_8008AFA4
/* 1B3EC78 8008A6B0 8801022A */   slti      $v0, $s0, 0x188
/* 1B3EC7C 8008A6B4 AA024014 */  bnez       $v0, .Llevel_21_8008B160
/* 1B3EC80 8008A6B8 A701022A */   slti      $v0, $s0, 0x1A7
/* 1B3EC84 8008A6BC C9004010 */  beqz       $v0, .Llevel_21_8008A9E4
/* 1B3EC88 8008A6C0 00000000 */   nop
/* 1B3EC8C 8008A6C4 582C0208 */  j          .Llevel_21_8008B160
/* 1B3EC90 8008A6C8 00000000 */   nop
.Llevel_21_8008A6CC:
/* 1B3EC94 8008A6CC CC01022A */  slti       $v0, $s0, 0x1CC
/* 1B3EC98 8008A6D0 A3024010 */  beqz       $v0, .Llevel_21_8008B160
/* 1B3EC9C 8008A6D4 CA01022A */   slti      $v0, $s0, 0x1CA
/* 1B3ECA0 8008A6D8 61024010 */  beqz       $v0, .Llevel_21_8008B060
/* 1B3ECA4 8008A6DC 00000000 */   nop
/* 1B3ECA8 8008A6E0 582C0208 */  j          .Llevel_21_8008B160
/* 1B3ECAC 8008A6E4 00000000 */   nop
.Llevel_21_8008A6E8:
/* 1B3ECB0 8008A6E8 0000708E */  lw         $s0, 0x0($s3)
/* 1B3ECB4 8008A6EC C8E9000C */  jal        func_8003A720
/* 1B3ECB8 8008A6F0 21206002 */   addu      $a0, $s3, $zero
/* 1B3ECBC 8008A6F4 8C000224 */  addiu      $v0, $zero, 0x8C
/* 1B3ECC0 8008A6F8 080002AE */  sw         $v0, 0x8($s0)
/* 1B3ECC4 8008A6FC 03000224 */  addiu      $v0, $zero, 0x3
/* 1B3ECC8 8008A700 100002A2 */  sb         $v0, 0x10($s0)
/* 1B3ECCC 8008A704 FF000224 */  addiu      $v0, $zero, 0xFF
/* 1B3ECD0 8008A708 140002A2 */  sb         $v0, 0x14($s0)
/* 1B3ECD4 8008A70C 02000224 */  addiu      $v0, $zero, 0x2
/* 1B3ECD8 8008A710 000000AE */  sw         $zero, 0x0($s0)
/* 1B3ECDC 8008A714 040000AE */  sw         $zero, 0x4($s0)
/* 1B3ECE0 8008A718 0E0000A2 */  sb         $zero, 0xE($s0)
/* 1B3ECE4 8008A71C 0F0000A2 */  sb         $zero, 0xF($s0)
/* 1B3ECE8 8008A720 110000A2 */  sb         $zero, 0x11($s0)
/* 1B3ECEC 8008A724 120000A2 */  sb         $zero, 0x12($s0)
/* 1B3ECF0 8008A728 130000A2 */  sb         $zero, 0x13($s0)
/* 1B3ECF4 8008A72C 490062A2 */  sb         $v0, 0x49($s3)
/* 1B3ECF8 8008A730 18000224 */  addiu      $v0, $zero, 0x18
/* 1B3ECFC 8008A734 500062A2 */  sb         $v0, 0x50($s3)
/* 1B3ED00 8008A738 10000224 */  addiu      $v0, $zero, 0x10
/* 1B3ED04 8008A73C 520062A2 */  sb         $v0, 0x52($s3)
/* 1B3ED08 8008A740 20000224 */  addiu      $v0, $zero, 0x20
/* 1B3ED0C 8008A744 440062A2 */  sb         $v0, 0x44($s3)
/* 1B3ED10 8008A748 450060A2 */  sb         $zero, 0x45($s3)
/* 1B3ED14 8008A74C 0400A012 */  beqz       $s5, .Llevel_21_8008A760
/* 1B3ED18 8008A750 460060A2 */   sb        $zero, 0x46($s3)
/* 1B3ED1C 8008A754 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3ED20 8008A758 C05D000C */  jal        VecCopy
/* 1B3ED24 8008A75C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_21_8008A760:
/* 1B3ED28 8008A760 AA49010C */  jal        func_800526A8
/* 1B3ED2C 8008A764 21206002 */   addu      $a0, $s3, $zero
/* 1B3ED30 8008A768 4B006292 */  lbu        $v0, 0x4B($s3)
/* 1B3ED34 8008A76C 01000324 */  addiu      $v1, $zero, 0x1
/* 1B3ED38 8008A770 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 1B3ED3C 8008A774 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 1B3ED40 8008A778 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 1B3ED44 8008A77C E12A0208 */  j          .Llevel_21_8008AB84
/* 1B3ED48 8008A780 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_21_8008A784:
/* 1B3ED4C 8008A784 0000718E */  lw         $s1, 0x0($s3)
/* 1B3ED50 8008A788 C8E9000C */  jal        func_8003A720
/* 1B3ED54 8008A78C 21206002 */   addu      $a0, $s3, $zero
/* 1B3ED58 8008A790 AA49010C */  jal        func_800526A8
/* 1B3ED5C 8008A794 21206002 */   addu      $a0, $s3, $zero
/* 1B3ED60 8008A798 0C007026 */  addiu      $s0, $s3, 0xC
/* 1B3ED64 8008A79C 21200002 */  addu       $a0, $s0, $zero
/* 1B3ED68 8008A7A0 C05D000C */  jal        VecCopy
/* 1B3ED6C 8008A7A4 0C00A526 */   addiu     $a1, $s5, 0xC
/* 1B3ED70 8008A7A8 21280002 */  addu       $a1, $s0, $zero
/* 1B3ED74 8008A7AC 1400628E */  lw         $v0, 0x14($s3)
/* 1B3ED78 8008A7B0 04002426 */  addiu      $a0, $s1, 0x4
/* 1B3ED7C 8008A7B4 00024224 */  addiu      $v0, $v0, 0x200
/* 1B3ED80 8008A7B8 C05D000C */  jal        VecCopy
/* 1B3ED84 8008A7BC 140062AE */   sw        $v0, 0x14($s3)
/* 1B3ED88 8008A7C0 08070224 */  addiu      $v0, $zero, 0x708
/* 1B3ED8C 8008A7C4 130020A2 */  sb         $zero, 0x13($s1)
/* 1B3ED90 8008A7C8 120020A2 */  sb         $zero, 0x12($s1)
/* 1B3ED94 8008A7CC 652C0208 */  j          .Llevel_21_8008B194
/* 1B3ED98 8008A7D0 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_21_8008A7D4:
/* 1B3ED9C 8008A7D4 C8E9000C */  jal        func_8003A720
/* 1B3EDA0 8008A7D8 21206002 */   addu      $a0, $s3, $zero
/* 1B3EDA4 8008A7DC 20000224 */  addiu      $v0, $zero, 0x20
/* 1B3EDA8 8008A7E0 500062A2 */  sb         $v0, 0x50($s3)
/* 1B3EDAC 8008A7E4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 1B3EDB0 8008A7E8 0400A012 */  beqz       $s5, .Llevel_21_8008A7FC
/* 1B3EDB4 8008A7EC 520062A2 */   sb        $v0, 0x52($s3)
/* 1B3EDB8 8008A7F0 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3EDBC 8008A7F4 C05D000C */  jal        VecCopy
/* 1B3EDC0 8008A7F8 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_21_8008A7FC:
/* 1B3EDC4 8008A7FC 734A010C */  jal        func_800529CC
/* 1B3EDC8 8008A800 21206002 */   addu      $a0, $s3, $zero
/* 1B3EDCC 8008A804 662C0208 */  j          .Llevel_21_8008B198
/* 1B3EDD0 8008A808 21106002 */   addu      $v0, $s3, $zero
.Llevel_21_8008A80C:
/* 1B3EDD4 8008A80C 0000718E */  lw         $s1, 0x0($s3)
/* 1B3EDD8 8008A810 C8E9000C */  jal        func_8003A720
/* 1B3EDDC 8008A814 21206002 */   addu      $a0, $s3, $zero
/* 1B3EDE0 8008A818 8C000224 */  addiu      $v0, $zero, 0x8C
/* 1B3EDE4 8008A81C 000020AE */  sw         $zero, 0x0($s1)
/* 1B3EDE8 8008A820 040020AE */  sw         $zero, 0x4($s1)
/* 1B3EDEC 8008A824 080022AE */  sw         $v0, 0x8($s1)
/* 1B3EDF0 8008A828 0E0020A2 */  sb         $zero, 0xE($s1)
/* 1B3EDF4 8008A82C 0F0020A2 */  sb         $zero, 0xF($s1)
/* 1B3EDF8 8008A830 110020A2 */  sb         $zero, 0x11($s1)
/* 1B3EDFC 8008A834 120020A2 */  sb         $zero, 0x12($s1)
/* 1B3EE00 8008A838 130020A2 */  sb         $zero, 0x13($s1)
/* 1B3EE04 8008A83C 3600A386 */  lh         $v1, 0x36($s5)
/* 1B3EE08 8008A840 0D000224 */  addiu      $v0, $zero, 0xD
/* 1B3EE0C 8008A844 02006214 */  bne        $v1, $v0, .Llevel_21_8008A850
/* 1B3EE10 8008A848 03000224 */   addiu     $v0, $zero, 0x3
/* 1B3EE14 8008A84C 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_21_8008A850:
/* 1B3EE18 8008A850 100022A2 */  sb         $v0, 0x10($s1)
/* 1B3EE1C 8008A854 0C007026 */  addiu      $s0, $s3, 0xC
/* 1B3EE20 8008A858 21200002 */  addu       $a0, $s0, $zero
/* 1B3EE24 8008A85C 0C00A526 */  addiu      $a1, $s5, 0xC
/* 1B3EE28 8008A860 FF000224 */  addiu      $v0, $zero, 0xFF
/* 1B3EE2C 8008A864 140022A2 */  sb         $v0, 0x14($s1)
/* 1B3EE30 8008A868 02001124 */  addiu      $s1, $zero, 0x2
/* 1B3EE34 8008A86C 18000224 */  addiu      $v0, $zero, 0x18
/* 1B3EE38 8008A870 500062A2 */  sb         $v0, 0x50($s3)
/* 1B3EE3C 8008A874 40000224 */  addiu      $v0, $zero, 0x40
/* 1B3EE40 8008A878 520062A2 */  sb         $v0, 0x52($s3)
/* 1B3EE44 8008A87C 20000224 */  addiu      $v0, $zero, 0x20
/* 1B3EE48 8008A880 490071A2 */  sb         $s1, 0x49($s3)
/* 1B3EE4C 8008A884 440062A2 */  sb         $v0, 0x44($s3)
/* 1B3EE50 8008A888 450060A2 */  sb         $zero, 0x45($s3)
/* 1B3EE54 8008A88C C05D000C */  jal        VecCopy
/* 1B3EE58 8008A890 460060A2 */   sb        $zero, 0x46($s3)
/* 1B3EE5C 8008A894 734A010C */  jal        func_800529CC
/* 1B3EE60 8008A898 21206002 */   addu      $a0, $s3, $zero
/* 1B3EE64 8008A89C 1000A427 */  addiu      $a0, $sp, 0x10
/* 1B3EE68 8008A8A0 21280002 */  addu       $a1, $s0, $zero
/* 1B3EE6C 8008A8A4 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 1B3EE70 8008A8A8 C05D000C */  jal        VecCopy
/* 1B3EE74 8008A8AC 1C0062AE */   sw        $v0, 0x1C($s3)
/* 1B3EE78 8008A8B0 1000A427 */  addiu      $a0, $sp, 0x10
/* 1B3EE7C 8008A8B4 1800A28F */  lw         $v0, 0x18($sp)
/* 1B3EE80 8008A8B8 0100053C */  lui        $a1, (0x10000 >> 16)
/* 1B3EE84 8008A8BC 00044224 */  addiu      $v0, $v0, 0x400
/* 1B3EE88 8008A8C0 7B35010C */  jal        func_8004D5EC
/* 1B3EE8C 8008A8C4 1800A2AF */   sw        $v0, 0x18($sp)
/* 1B3EE90 8008A8C8 F44C010C */  jal        func_800533D0
/* 1B3EE94 8008A8CC 21206002 */   addu      $a0, $s3, $zero
/* 1B3EE98 8008A8D0 36006386 */  lh         $v1, 0x36($s3)
/* 1B3EE9C 8008A8D4 0E000224 */  addiu      $v0, $zero, 0xE
/* 1B3EEA0 8008A8D8 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 1B3EEA4 8008A8DC 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 1B3EEA8 8008A8E0 03006214 */  bne        $v1, $v0, .Llevel_21_8008A8F0
/* 1B3EEAC 8008A8E4 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 1B3EEB0 8008A8E8 0C000224 */  addiu      $v0, $zero, 0xC
/* 1B3EEB4 8008A8EC 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_21_8008A8F0:
/* 1B3EEB8 8008A8F0 36006386 */  lh         $v1, 0x36($s3)
/* 1B3EEBC 8008A8F4 53000224 */  addiu      $v0, $zero, 0x53
/* 1B3EEC0 8008A8F8 05006214 */  bne        $v1, $v0, .Llevel_21_8008A910
/* 1B3EEC4 8008A8FC 54000224 */   addiu     $v0, $zero, 0x54
/* 1B3EEC8 8008A900 01000224 */  addiu      $v0, $zero, 0x1
/* 1B3EECC 8008A904 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 1B3EED0 8008A908 36006386 */  lh         $v1, 0x36($s3)
/* 1B3EED4 8008A90C 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_21_8008A910:
/* 1B3EED8 8008A910 02006214 */  bne        $v1, $v0, .Llevel_21_8008A91C
/* 1B3EEDC 8008A914 00000000 */   nop
/* 1B3EEE0 8008A918 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_21_8008A91C:
/* 1B3EEE4 8008A91C 36006386 */  lh         $v1, 0x36($s3)
/* 1B3EEE8 8008A920 55000224 */  addiu      $v0, $zero, 0x55
/* 1B3EEEC 8008A924 05006214 */  bne        $v1, $v0, .Llevel_21_8008A93C
/* 1B3EEF0 8008A928 56000224 */   addiu     $v0, $zero, 0x56
/* 1B3EEF4 8008A92C 03000224 */  addiu      $v0, $zero, 0x3
/* 1B3EEF8 8008A930 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 1B3EEFC 8008A934 36006386 */  lh         $v1, 0x36($s3)
/* 1B3EF00 8008A938 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_21_8008A93C:
/* 1B3EF04 8008A93C 02006214 */  bne        $v1, $v0, .Llevel_21_8008A948
/* 1B3EF08 8008A940 04000224 */   addiu     $v0, $zero, 0x4
/* 1B3EF0C 8008A944 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_21_8008A948:
/* 1B3EF10 8008A948 36006386 */  lh         $v1, 0x36($s3)
/* 1B3EF14 8008A94C 57000224 */  addiu      $v0, $zero, 0x57
/* 1B3EF18 8008A950 11026214 */  bne        $v1, $v0, .Llevel_21_8008B198
/* 1B3EF1C 8008A954 21106002 */   addu      $v0, $s3, $zero
/* 1B3EF20 8008A958 05000224 */  addiu      $v0, $zero, 0x5
/* 1B3EF24 8008A95C 652C0208 */  j          .Llevel_21_8008B194
/* 1B3EF28 8008A960 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_21_8008A964:
/* 1B3EF2C 8008A964 0000708E */  lw         $s0, 0x0($s3)
/* 1B3EF30 8008A968 C8E9000C */  jal        func_8003A720
/* 1B3EF34 8008A96C 21206002 */   addu      $a0, $s3, $zero
/* 1B3EF38 8008A970 AA49010C */  jal        func_800526A8
/* 1B3EF3C 8008A974 21206002 */   addu      $a0, $s3, $zero
/* 1B3EF40 8008A978 490060A2 */  sb         $zero, 0x49($s3)
/* 1B3EF44 8008A97C 000000AE */  sw         $zero, 0x0($s0)
/* 1B3EF48 8008A980 080000A6 */  sh         $zero, 0x8($s0)
/* 1B3EF4C 8008A984 060000A6 */  sh         $zero, 0x6($s0)
/* 1B3EF50 8008A988 040000A6 */  sh         $zero, 0x4($s0)
/* 1B3EF54 8008A98C 0C0000AE */  sw         $zero, 0xC($s0)
/* 1B3EF58 8008A990 0002A012 */  beqz       $s5, .Llevel_21_8008B194
/* 1B3EF5C 8008A994 100000AE */   sw        $zero, 0x10($s0)
/* 1B3EF60 8008A998 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3EF64 8008A99C C05D000C */  jal        VecCopy
/* 1B3EF68 8008A9A0 0C00A526 */   addiu     $a1, $s5, 0xC
/* 1B3EF6C 8008A9A4 662C0208 */  j          .Llevel_21_8008B198
/* 1B3EF70 8008A9A8 21106002 */   addu      $v0, $s3, $zero
.Llevel_21_8008A9AC:
/* 1B3EF74 8008A9AC C8E9000C */  jal        func_8003A720
/* 1B3EF78 8008A9B0 21206002 */   addu      $a0, $s3, $zero
/* 1B3EF7C 8008A9B4 21206002 */  addu       $a0, $s3, $zero
/* 1B3EF80 8008A9B8 20000224 */  addiu      $v0, $zero, 0x20
/* 1B3EF84 8008A9BC 500062A2 */  sb         $v0, 0x50($s3)
/* 1B3EF88 8008A9C0 FF000224 */  addiu      $v0, $zero, 0xFF
/* 1B3EF8C 8008A9C4 734A010C */  jal        func_800529CC
/* 1B3EF90 8008A9C8 520062A2 */   sb        $v0, 0x52($s3)
/* 1B3EF94 8008A9CC 0D000224 */  addiu      $v0, $zero, 0xD
/* 1B3EF98 8008A9D0 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 1B3EF9C 8008A9D4 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 1B3EFA0 8008A9D8 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 1B3EFA4 8008A9DC 652C0208 */  j          .Llevel_21_8008B194
/* 1B3EFA8 8008A9E0 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_21_8008A9E4:
/* 1B3EFAC 8008A9E4 0000748E */  lw         $s4, 0x0($s3)
/* 1B3EFB0 8008A9E8 C8E9000C */  jal        func_8003A720
/* 1B3EFB4 8008A9EC 21206002 */   addu      $a0, $s3, $zero
/* 1B3EFB8 8008A9F0 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3EFBC 8008A9F4 0C00A526 */  addiu      $a1, $s5, 0xC
/* 1B3EFC0 8008A9F8 20000224 */  addiu      $v0, $zero, 0x20
/* 1B3EFC4 8008A9FC C05D000C */  jal        VecCopy
/* 1B3EFC8 8008AA00 500062A2 */   sb        $v0, 0x50($s3)
/* 1B3EFCC 8008AA04 AA49010C */  jal        func_800526A8
/* 1B3EFD0 8008AA08 21206002 */   addu      $a0, $s3, $zero
/* 1B3EFD4 8008AA0C CB89010C */  jal        rand
/* 1B3EFD8 8008AA10 00000000 */   nop
/* 1B3EFDC 8008AA14 CB89010C */  jal        rand
/* 1B3EFE0 8008AA18 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 1B3EFE4 8008AA1C FF075130 */  andi       $s1, $v0, 0x7FF
/* 1B3EFE8 8008AA20 2C5B000C */  jal        Cos
/* 1B3EFEC 8008AA24 21202002 */   addu      $a0, $s1, $zero
/* 1B3EFF0 8008AA28 21204002 */  addu       $a0, $s2, $zero
/* 1B3EFF4 8008AA2C 2C5B000C */  jal        Cos
/* 1B3EFF8 8008AA30 21804000 */   addu      $s0, $v0, $zero
/* 1B3EFFC 8008AA34 43811000 */  sra        $s0, $s0, 5
/* 1B3F000 8008AA38 18000202 */  mult       $s0, $v0
/* 1B3F004 8008AA3C 21202002 */  addu       $a0, $s1, $zero
/* 1B3F008 8008AA40 12380000 */  mflo       $a3
/* 1B3F00C 8008AA44 03130700 */  sra        $v0, $a3, 12
/* 1B3F010 8008AA48 2C5B000C */  jal        Cos
/* 1B3F014 8008AA4C 000082A6 */   sh        $v0, 0x0($s4)
/* 1B3F018 8008AA50 21204002 */  addu       $a0, $s2, $zero
/* 1B3F01C 8008AA54 165B000C */  jal        Sin
/* 1B3F020 8008AA58 21804000 */   addu      $s0, $v0, $zero
/* 1B3F024 8008AA5C 43811000 */  sra        $s0, $s0, 5
/* 1B3F028 8008AA60 18000202 */  mult       $s0, $v0
/* 1B3F02C 8008AA64 21202002 */  addu       $a0, $s1, $zero
/* 1B3F030 8008AA68 12380000 */  mflo       $a3
/* 1B3F034 8008AA6C 03130700 */  sra        $v0, $a3, 12
/* 1B3F038 8008AA70 165B000C */  jal        Sin
/* 1B3F03C 8008AA74 020082A6 */   sh        $v0, 0x2($s4)
/* 1B3F040 8008AA78 43110200 */  sra        $v0, $v0, 5
/* 1B3F044 8008AA7C 040082A6 */  sh         $v0, 0x4($s4)
/* 1B3F048 8008AA80 1800A28E */  lw         $v0, 0x18($s5)
/* 1B3F04C 8008AA84 0200033C */  lui        $v1, (0x20000 >> 16)
/* 1B3F050 8008AA88 24104300 */  and        $v0, $v0, $v1
/* 1B3F054 8008AA8C 13004010 */  beqz       $v0, .Llevel_21_8008AADC
/* 1B3F058 8008AA90 00000000 */   nop
/* 1B3F05C 8008AA94 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 1B3F060 8008AA98 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 1B3F064 8008AA9C 00008396 */  lhu        $v1, 0x0($s4)
/* 1B3F068 8008AAA0 83110200 */  sra        $v0, $v0, 6
/* 1B3F06C 8008AAA4 21186200 */  addu       $v1, $v1, $v0
/* 1B3F070 8008AAA8 000083A6 */  sh         $v1, 0x0($s4)
/* 1B3F074 8008AAAC 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 1B3F078 8008AAB0 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 1B3F07C 8008AAB4 02008396 */  lhu        $v1, 0x2($s4)
/* 1B3F080 8008AAB8 83110200 */  sra        $v0, $v0, 6
/* 1B3F084 8008AABC 21186200 */  addu       $v1, $v1, $v0
/* 1B3F088 8008AAC0 020083A6 */  sh         $v1, 0x2($s4)
/* 1B3F08C 8008AAC4 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 1B3F090 8008AAC8 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 1B3F094 8008AACC 04008396 */  lhu        $v1, 0x4($s4)
/* 1B3F098 8008AAD0 83110200 */  sra        $v0, $v0, 6
/* 1B3F09C 8008AAD4 21186200 */  addu       $v1, $v1, $v0
/* 1B3F0A0 8008AAD8 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_21_8008AADC:
/* 1B3F0A4 8008AADC 00008286 */  lh         $v0, 0x0($s4)
/* 1B3F0A8 8008AAE0 0C00638E */  lw         $v1, 0xC($s3)
/* 1B3F0AC 8008AAE4 80100200 */  sll        $v0, $v0, 2
/* 1B3F0B0 8008AAE8 21186200 */  addu       $v1, $v1, $v0
/* 1B3F0B4 8008AAEC 0C0063AE */  sw         $v1, 0xC($s3)
/* 1B3F0B8 8008AAF0 02008286 */  lh         $v0, 0x2($s4)
/* 1B3F0BC 8008AAF4 1000638E */  lw         $v1, 0x10($s3)
/* 1B3F0C0 8008AAF8 80100200 */  sll        $v0, $v0, 2
/* 1B3F0C4 8008AAFC 21186200 */  addu       $v1, $v1, $v0
/* 1B3F0C8 8008AB00 100063AE */  sw         $v1, 0x10($s3)
/* 1B3F0CC 8008AB04 04008286 */  lh         $v0, 0x4($s4)
/* 1B3F0D0 8008AB08 1400638E */  lw         $v1, 0x14($s3)
/* 1B3F0D4 8008AB0C 80100200 */  sll        $v0, $v0, 2
/* 1B3F0D8 8008AB10 21186200 */  addu       $v1, $v1, $v0
/* 1B3F0DC 8008AB14 CB89010C */  jal        rand
/* 1B3F0E0 8008AB18 140063AE */   sw        $v1, 0x14($s3)
/* 1B3F0E4 8008AB1C 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F0E8 8008AB20 CB89010C */  jal        rand
/* 1B3F0EC 8008AB24 060082A6 */   sh        $v0, 0x6($s4)
/* 1B3F0F0 8008AB28 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F0F4 8008AB2C CB89010C */  jal        rand
/* 1B3F0F8 8008AB30 080082A6 */   sh        $v0, 0x8($s4)
/* 1B3F0FC 8008AB34 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F100 8008AB38 0A0082A6 */  sh         $v0, 0xA($s4)
/* 1B3F104 8008AB3C 1400A28E */  lw         $v0, 0x14($s5)
/* 1B3F108 8008AB40 00000000 */  nop
/* 1B3F10C 8008AB44 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 1B3F110 8008AB48 CB89010C */  jal        rand
/* 1B3F114 8008AB4C 100082AE */   sw        $v0, 0x10($s4)
/* 1B3F118 8008AB50 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F11C 8008AB54 40000324 */  addiu      $v1, $zero, 0x40
/* 1B3F120 8008AB58 23186200 */  subu       $v1, $v1, $v0
/* 1B3F124 8008AB5C 0C0083AE */  sw         $v1, 0xC($s4)
/* 1B3F128 8008AB60 36006296 */  lhu        $v0, 0x36($s3)
/* 1B3F12C 8008AB64 00000000 */  nop
/* 1B3F130 8008AB68 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 1B3F134 8008AB6C 0300422C */  sltiu      $v0, $v0, 0x3
/* 1B3F138 8008AB70 88014010 */  beqz       $v0, .Llevel_21_8008B194
/* 1B3F13C 8008AB74 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 1B3F140 8008AB78 4B006292 */  lbu        $v0, 0x4B($s3)
/* 1B3F144 8008AB7C 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 1B3F148 8008AB80 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_21_8008AB84:
/* 1B3F14C 8008AB84 80004234 */  ori        $v0, $v0, 0x80
/* 1B3F150 8008AB88 652C0208 */  j          .Llevel_21_8008B194
/* 1B3F154 8008AB8C 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_21_8008AB90:
/* 1B3F158 8008AB90 0000718E */  lw         $s1, 0x0($s3)
/* 1B3F15C 8008AB94 C8E9000C */  jal        func_8003A720
/* 1B3F160 8008AB98 21206002 */   addu      $a0, $s3, $zero
/* 1B3F164 8008AB9C 21206002 */  addu       $a0, $s3, $zero
/* 1B3F168 8008ABA0 20000224 */  addiu      $v0, $zero, 0x20
/* 1B3F16C 8008ABA4 500062A2 */  sb         $v0, 0x50($s3)
/* 1B3F170 8008ABA8 FF000224 */  addiu      $v0, $zero, 0xFF
/* 1B3F174 8008ABAC 734A010C */  jal        func_800529CC
/* 1B3F178 8008ABB0 520062A2 */   sb        $v0, 0x52($s3)
/* 1B3F17C 8008ABB4 0E000224 */  addiu      $v0, $zero, 0xE
/* 1B3F180 8008ABB8 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 1B3F184 8008ABBC 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 1B3F188 8008ABC0 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 1B3F18C 8008ABC4 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 1B3F190 8008ABC8 0780033C */  lui        $v1, %hi(g_DragonCutscene + 0x28)
/* 1B3F194 8008ABCC 5870638C */  lw         $v1, %lo(g_DragonCutscene + 0x28)($v1)
/* 1B3F198 8008ABD0 03000224 */  addiu      $v0, $zero, 0x3
/* 1B3F19C 8008ABD4 03006214 */  bne        $v1, $v0, .Llevel_21_8008ABE4
/* 1B3F1A0 8008ABD8 01000224 */   addiu     $v0, $zero, 0x1
/* 1B3F1A4 8008ABDC FB2A0208 */  j          .Llevel_21_8008ABEC
/* 1B3F1A8 8008ABE0 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_21_8008ABE4:
/* 1B3F1AC 8008ABE4 02006214 */  bne        $v1, $v0, .Llevel_21_8008ABF0
/* 1B3F1B0 8008ABE8 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_21_8008ABEC:
/* 1B3F1B4 8008ABEC 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_21_8008ABF0:
/* 1B3F1B8 8008ABF0 CB89010C */  jal        rand
/* 1B3F1BC 8008ABF4 00000000 */   nop
/* 1B3F1C0 8008ABF8 2000A426 */  addiu      $a0, $s5, 0x20
/* 1B3F1C4 8008ABFC 07004230 */  andi       $v0, $v0, 0x7
/* 1B3F1C8 8008AC00 80100200 */  sll        $v0, $v0, 2
/* 1B3F1CC 8008AC04 2000B027 */  addiu      $s0, $sp, 0x20
/* 1B3F1D0 8008AC08 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 1B3F1D4 8008AC0C 21082200 */  addu       $at, $at, $v0
/* 1B3F1D8 8008AC10 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 1B3F1DC 8008AC14 21280002 */  addu       $a1, $s0, $zero
/* 1B3F1E0 8008AC18 2400A0AF */  sw         $zero, 0x24($sp)
/* 1B3F1E4 8008AC1C 2000A3AF */  sw         $v1, 0x20($sp)
/* 1B3F1E8 8008AC20 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 1B3F1EC 8008AC24 21082200 */  addu       $at, $at, $v0
/* 1B3F1F0 8008AC28 A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 1B3F1F4 8008AC2C 21300002 */  addu       $a2, $s0, $zero
/* 1B3F1F8 8008AC30 125C000C */  jal        VecRotateByMatrix
/* 1B3F1FC 8008AC34 2800A2AF */   sw        $v0, 0x28($sp)
/* 1B3F200 8008AC38 CB89010C */  jal        rand
/* 1B3F204 8008AC3C 00000000 */   nop
/* 1B3F208 8008AC40 2000A38F */  lw         $v1, 0x20($sp)
/* 1B3F20C 8008AC44 7F004230 */  andi       $v0, $v0, 0x7F
/* 1B3F210 8008AC48 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 1B3F214 8008AC4C 21186200 */  addu       $v1, $v1, $v0
/* 1B3F218 8008AC50 CB89010C */  jal        rand
/* 1B3F21C 8008AC54 2000A3AF */   sw        $v1, 0x20($sp)
/* 1B3F220 8008AC58 2400A38F */  lw         $v1, 0x24($sp)
/* 1B3F224 8008AC5C 7F004230 */  andi       $v0, $v0, 0x7F
/* 1B3F228 8008AC60 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 1B3F22C 8008AC64 21186200 */  addu       $v1, $v1, $v0
/* 1B3F230 8008AC68 CB89010C */  jal        rand
/* 1B3F234 8008AC6C 2400A3AF */   sw        $v1, 0x24($sp)
/* 1B3F238 8008AC70 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3F23C 8008AC74 0C00A526 */  addiu      $a1, $s5, 0xC
/* 1B3F240 8008AC78 21300002 */  addu       $a2, $s0, $zero
/* 1B3F244 8008AC7C 2800A38F */  lw         $v1, 0x28($sp)
/* 1B3F248 8008AC80 7F004230 */  andi       $v0, $v0, 0x7F
/* 1B3F24C 8008AC84 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 1B3F250 8008AC88 21186200 */  addu       $v1, $v1, $v0
/* 1B3F254 8008AC8C D65D000C */  jal        VecAdd
/* 1B3F258 8008AC90 2800A3AF */   sw        $v1, 0x28($sp)
/* 1B3F25C 8008AC94 21202002 */  addu       $a0, $s1, $zero
/* 1B3F260 8008AC98 C05D000C */  jal        VecCopy
/* 1B3F264 8008AC9C 21280002 */   addu      $a1, $s0, $zero
/* 1B3F268 8008ACA0 21202002 */  addu       $a0, $s1, $zero
/* 1B3F26C 8008ACA4 B25D000C */  jal        VecShiftRight
/* 1B3F270 8008ACA8 02000524 */   addiu     $a1, $zero, 0x2
/* 1B3F274 8008ACAC CB89010C */  jal        rand
/* 1B3F278 8008ACB0 00000000 */   nop
/* 1B3F27C 8008ACB4 0000238E */  lw         $v1, 0x0($s1)
/* 1B3F280 8008ACB8 FF004230 */  andi       $v0, $v0, 0xFF
/* 1B3F284 8008ACBC 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 1B3F288 8008ACC0 21186200 */  addu       $v1, $v1, $v0
/* 1B3F28C 8008ACC4 CB89010C */  jal        rand
/* 1B3F290 8008ACC8 000023AE */   sw        $v1, 0x0($s1)
/* 1B3F294 8008ACCC 0400238E */  lw         $v1, 0x4($s1)
/* 1B3F298 8008ACD0 FF004230 */  andi       $v0, $v0, 0xFF
/* 1B3F29C 8008ACD4 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 1B3F2A0 8008ACD8 21186200 */  addu       $v1, $v1, $v0
/* 1B3F2A4 8008ACDC CB89010C */  jal        rand
/* 1B3F2A8 8008ACE0 040023AE */   sw        $v1, 0x4($s1)
/* 1B3F2AC 8008ACE4 0800238E */  lw         $v1, 0x8($s1)
/* 1B3F2B0 8008ACE8 FF004230 */  andi       $v0, $v0, 0xFF
/* 1B3F2B4 8008ACEC 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 1B3F2B8 8008ACF0 21186200 */  addu       $v1, $v1, $v0
/* 1B3F2BC 8008ACF4 CB89010C */  jal        rand
/* 1B3F2C0 8008ACF8 080023AE */   sw        $v1, 0x8($s1)
/* 1B3F2C4 8008ACFC CB89010C */  jal        rand
/* 1B3F2C8 8008AD00 440062A2 */   sb        $v0, 0x44($s3)
/* 1B3F2CC 8008AD04 CB89010C */  jal        rand
/* 1B3F2D0 8008AD08 450062A2 */   sb        $v0, 0x45($s3)
/* 1B3F2D4 8008AD0C CB89010C */  jal        rand
/* 1B3F2D8 8008AD10 460062A2 */   sb        $v0, 0x46($s3)
/* 1B3F2DC 8008AD14 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F2E0 8008AD18 CB89010C */  jal        rand
/* 1B3F2E4 8008AD1C 100022A2 */   sb        $v0, 0x10($s1)
/* 1B3F2E8 8008AD20 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F2EC 8008AD24 CB89010C */  jal        rand
/* 1B3F2F0 8008AD28 110022A2 */   sb        $v0, 0x11($s1)
/* 1B3F2F4 8008AD2C 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F2F8 8008AD30 120022A2 */  sb         $v0, 0x12($s1)
/* 1B3F2FC 8008AD34 1400A28E */  lw         $v0, 0x14($s5)
/* 1B3F300 8008AD38 CB89010C */  jal        rand
/* 1B3F304 8008AD3C 0C0022AE */   sw        $v0, 0xC($s1)
/* 1B3F308 8008AD40 03004230 */  andi       $v0, $v0, 0x3
/* 1B3F30C 8008AD44 10004224 */  addiu      $v0, $v0, 0x10
/* 1B3F310 8008AD48 652C0208 */  j          .Llevel_21_8008B194
/* 1B3F314 8008AD4C 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_21_8008AD50:
/* 1B3F318 8008AD50 0000708E */  lw         $s0, 0x0($s3)
/* 1B3F31C 8008AD54 C8E9000C */  jal        func_8003A720
/* 1B3F320 8008AD58 21206002 */   addu      $a0, $s3, $zero
/* 1B3F324 8008AD5C 734A010C */  jal        func_800529CC
/* 1B3F328 8008AD60 21206002 */   addu      $a0, $s3, $zero
/* 1B3F32C 8008AD64 02000224 */  addiu      $v0, $zero, 0x2
/* 1B3F330 8008AD68 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 1B3F334 8008AD6C 40000224 */  addiu      $v0, $zero, 0x40
/* 1B3F338 8008AD70 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 1B3F33C 8008AD74 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 1B3F340 8008AD78 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 1B3F344 8008AD7C 652C0208 */  j          .Llevel_21_8008B194
/* 1B3F348 8008AD80 000002AE */   sw        $v0, 0x0($s0)
.Llevel_21_8008AD84:
/* 1B3F34C 8008AD84 0000728E */  lw         $s2, 0x0($s3)
/* 1B3F350 8008AD88 C8E9000C */  jal        func_8003A720
/* 1B3F354 8008AD8C 21206002 */   addu      $a0, $s3, $zero
/* 1B3F358 8008AD90 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3F35C 8008AD94 C05D000C */  jal        VecCopy
/* 1B3F360 8008AD98 0C00A526 */   addiu     $a1, $s5, 0xC
/* 1B3F364 8008AD9C AA49010C */  jal        func_800526A8
/* 1B3F368 8008ADA0 21206002 */   addu      $a0, $s3, $zero
/* 1B3F36C 8008ADA4 CB89010C */  jal        rand
/* 1B3F370 8008ADA8 00000000 */   nop
/* 1B3F374 8008ADAC CB89010C */  jal        rand
/* 1B3F378 8008ADB0 FF0F5430 */   andi      $s4, $v0, 0xFFF
/* 1B3F37C 8008ADB4 FF075130 */  andi       $s1, $v0, 0x7FF
/* 1B3F380 8008ADB8 8000222A */  slti       $v0, $s1, 0x80
/* 1B3F384 8008ADBC 03004010 */  beqz       $v0, .Llevel_21_8008ADCC
/* 1B3F388 8008ADC0 8107222A */   slti      $v0, $s1, 0x781
/* 1B3F38C 8008ADC4 80001124 */  addiu      $s1, $zero, 0x80
/* 1B3F390 8008ADC8 8107222A */  slti       $v0, $s1, 0x781
.Llevel_21_8008ADCC:
/* 1B3F394 8008ADCC 02004014 */  bnez       $v0, .Llevel_21_8008ADD8
/* 1B3F398 8008ADD0 00000000 */   nop
/* 1B3F39C 8008ADD4 80071124 */  addiu      $s1, $zero, 0x780
.Llevel_21_8008ADD8:
/* 1B3F3A0 8008ADD8 2C5B000C */  jal        Cos
/* 1B3F3A4 8008ADDC 21202002 */   addu      $a0, $s1, $zero
/* 1B3F3A8 8008ADE0 21208002 */  addu       $a0, $s4, $zero
/* 1B3F3AC 8008ADE4 2C5B000C */  jal        Cos
/* 1B3F3B0 8008ADE8 21804000 */   addu      $s0, $v0, $zero
/* 1B3F3B4 8008ADEC 43811000 */  sra        $s0, $s0, 5
/* 1B3F3B8 8008ADF0 03130200 */  sra        $v0, $v0, 12
/* 1B3F3BC 8008ADF4 18000202 */  mult       $s0, $v0
/* 1B3F3C0 8008ADF8 21202002 */  addu       $a0, $s1, $zero
/* 1B3F3C4 8008ADFC 12380000 */  mflo       $a3
/* 1B3F3C8 8008AE00 2C5B000C */  jal        Cos
/* 1B3F3CC 8008AE04 000047A6 */   sh        $a3, 0x0($s2)
/* 1B3F3D0 8008AE08 21208002 */  addu       $a0, $s4, $zero
/* 1B3F3D4 8008AE0C 165B000C */  jal        Sin
/* 1B3F3D8 8008AE10 21804000 */   addu      $s0, $v0, $zero
/* 1B3F3DC 8008AE14 43811000 */  sra        $s0, $s0, 5
/* 1B3F3E0 8008AE18 03130200 */  sra        $v0, $v0, 12
/* 1B3F3E4 8008AE1C 18000202 */  mult       $s0, $v0
/* 1B3F3E8 8008AE20 21202002 */  addu       $a0, $s1, $zero
/* 1B3F3EC 8008AE24 12380000 */  mflo       $a3
/* 1B3F3F0 8008AE28 165B000C */  jal        Sin
/* 1B3F3F4 8008AE2C 020047A6 */   sh        $a3, 0x2($s2)
/* 1B3F3F8 8008AE30 43110200 */  sra        $v0, $v0, 5
/* 1B3F3FC 8008AE34 040042A6 */  sh         $v0, 0x4($s2)
/* 1B3F400 8008AE38 00140200 */  sll        $v0, $v0, 16
/* 1B3F404 8008AE3C 03140200 */  sra        $v0, $v0, 16
/* 1B3F408 8008AE40 20004228 */  slti       $v0, $v0, 0x20
/* 1B3F40C 8008AE44 02004010 */  beqz       $v0, .Llevel_21_8008AE50
/* 1B3F410 8008AE48 20000224 */   addiu     $v0, $zero, 0x20
/* 1B3F414 8008AE4C 040042A6 */  sh         $v0, 0x4($s2)
.Llevel_21_8008AE50:
/* 1B3F418 8008AE50 36006386 */  lh         $v1, 0x36($s3)
/* 1B3F41C 8008AE54 21010224 */  addiu      $v0, $zero, 0x121
/* 1B3F420 8008AE58 14006214 */  bne        $v1, $v0, .Llevel_21_8008AEAC
/* 1B3F424 8008AE5C 00000000 */   nop
/* 1B3F428 8008AE60 04004296 */  lhu        $v0, 0x4($s2)
/* 1B3F42C 8008AE64 00000000 */  nop
/* 1B3F430 8008AE68 20004224 */  addiu      $v0, $v0, 0x20
/* 1B3F434 8008AE6C CB89010C */  jal        rand
/* 1B3F438 8008AE70 040042A6 */   sh        $v0, 0x4($s2)
/* 1B3F43C 8008AE74 CB89010C */  jal        rand
/* 1B3F440 8008AE78 460062A2 */   sb        $v0, 0x46($s3)
/* 1B3F444 8008AE7C FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 1B3F448 8008AE80 00084228 */  slti       $v0, $v0, 0x800
/* 1B3F44C 8008AE84 21004014 */  bnez       $v0, .Llevel_21_8008AF0C
/* 1B3F450 8008AE88 00000000 */   nop
/* 1B3F454 8008AE8C CB89010C */  jal        rand
/* 1B3F458 8008AE90 00000000 */   nop
/* 1B3F45C 8008AE94 1C004230 */  andi       $v0, $v0, 0x1C
/* 1B3F460 8008AE98 F0FF4224 */  addiu      $v0, $v0, -0x10
/* 1B3F464 8008AE9C 450062A2 */  sb         $v0, 0x45($s3)
/* 1B3F468 8008AEA0 01000224 */  addiu      $v0, $zero, 0x1
/* 1B3F46C 8008AEA4 C32B0208 */  j          .Llevel_21_8008AF0C
/* 1B3F470 8008AEA8 100042AE */   sw        $v0, 0x10($s2)
.Llevel_21_8008AEAC:
/* 1B3F474 8008AEAC 00004286 */  lh         $v0, 0x0($s2)
/* 1B3F478 8008AEB0 00000000 */  nop
/* 1B3F47C 8008AEB4 A0FF4228 */  slti       $v0, $v0, -0x60
/* 1B3F480 8008AEB8 02004010 */  beqz       $v0, .Llevel_21_8008AEC4
/* 1B3F484 8008AEBC A0FF0224 */   addiu     $v0, $zero, -0x60
/* 1B3F488 8008AEC0 000042A6 */  sh         $v0, 0x0($s2)
.Llevel_21_8008AEC4:
/* 1B3F48C 8008AEC4 00004286 */  lh         $v0, 0x0($s2)
/* 1B3F490 8008AEC8 00000000 */  nop
/* 1B3F494 8008AECC 61004228 */  slti       $v0, $v0, 0x61
/* 1B3F498 8008AED0 02004014 */  bnez       $v0, .Llevel_21_8008AEDC
/* 1B3F49C 8008AED4 60000224 */   addiu     $v0, $zero, 0x60
/* 1B3F4A0 8008AED8 000042A6 */  sh         $v0, 0x0($s2)
.Llevel_21_8008AEDC:
/* 1B3F4A4 8008AEDC 02004286 */  lh         $v0, 0x2($s2)
/* 1B3F4A8 8008AEE0 00000000 */  nop
/* 1B3F4AC 8008AEE4 A0FF4228 */  slti       $v0, $v0, -0x60
/* 1B3F4B0 8008AEE8 02004010 */  beqz       $v0, .Llevel_21_8008AEF4
/* 1B3F4B4 8008AEEC A0FF0224 */   addiu     $v0, $zero, -0x60
/* 1B3F4B8 8008AEF0 020042A6 */  sh         $v0, 0x2($s2)
.Llevel_21_8008AEF4:
/* 1B3F4BC 8008AEF4 02004286 */  lh         $v0, 0x2($s2)
/* 1B3F4C0 8008AEF8 00000000 */  nop
/* 1B3F4C4 8008AEFC 61004228 */  slti       $v0, $v0, 0x61
/* 1B3F4C8 8008AF00 02004014 */  bnez       $v0, .Llevel_21_8008AF0C
/* 1B3F4CC 8008AF04 60000224 */   addiu     $v0, $zero, 0x60
/* 1B3F4D0 8008AF08 020042A6 */  sh         $v0, 0x2($s2)
.Llevel_21_8008AF0C:
/* 1B3F4D4 8008AF0C 00004286 */  lh         $v0, 0x0($s2)
/* 1B3F4D8 8008AF10 0C00638E */  lw         $v1, 0xC($s3)
/* 1B3F4DC 8008AF14 80100200 */  sll        $v0, $v0, 2
/* 1B3F4E0 8008AF18 21186200 */  addu       $v1, $v1, $v0
/* 1B3F4E4 8008AF1C 0C0063AE */  sw         $v1, 0xC($s3)
/* 1B3F4E8 8008AF20 02004286 */  lh         $v0, 0x2($s2)
/* 1B3F4EC 8008AF24 1000638E */  lw         $v1, 0x10($s3)
/* 1B3F4F0 8008AF28 80100200 */  sll        $v0, $v0, 2
/* 1B3F4F4 8008AF2C 21186200 */  addu       $v1, $v1, $v0
/* 1B3F4F8 8008AF30 100063AE */  sw         $v1, 0x10($s3)
/* 1B3F4FC 8008AF34 04004286 */  lh         $v0, 0x4($s2)
/* 1B3F500 8008AF38 1400638E */  lw         $v1, 0x14($s3)
/* 1B3F504 8008AF3C 80100200 */  sll        $v0, $v0, 2
/* 1B3F508 8008AF40 21186200 */  addu       $v1, $v1, $v0
/* 1B3F50C 8008AF44 CB89010C */  jal        rand
/* 1B3F510 8008AF48 140063AE */   sw        $v1, 0x14($s3)
/* 1B3F514 8008AF4C 1F004230 */  andi       $v0, $v0, 0x1F
/* 1B3F518 8008AF50 F0FF4224 */  addiu      $v0, $v0, -0x10
/* 1B3F51C 8008AF54 CB89010C */  jal        rand
/* 1B3F520 8008AF58 060042A6 */   sh        $v0, 0x6($s2)
/* 1B3F524 8008AF5C 1F004230 */  andi       $v0, $v0, 0x1F
/* 1B3F528 8008AF60 F0FF4224 */  addiu      $v0, $v0, -0x10
/* 1B3F52C 8008AF64 CB89010C */  jal        rand
/* 1B3F530 8008AF68 080042A6 */   sh        $v0, 0x8($s2)
/* 1B3F534 8008AF6C 21200000 */  addu       $a0, $zero, $zero
/* 1B3F538 8008AF70 14000524 */  addiu      $a1, $zero, 0x14
/* 1B3F53C 8008AF74 1F004230 */  andi       $v0, $v0, 0x1F
/* 1B3F540 8008AF78 F0FF4224 */  addiu      $v0, $v0, -0x10
/* 1B3F544 8008AF7C A8DF000C */  jal        RandRange
/* 1B3F548 8008AF80 0A0042A6 */   sh        $v0, 0xA($s2)
/* 1B3F54C 8008AF84 32000324 */  addiu      $v1, $zero, 0x32
/* 1B3F550 8008AF88 23186200 */  subu       $v1, $v1, $v0
/* 1B3F554 8008AF8C 0A000224 */  addiu      $v0, $zero, 0xA
/* 1B3F558 8008AF90 0D0042A2 */  sb         $v0, 0xD($s2)
/* 1B3F55C 8008AF94 04000224 */  addiu      $v0, $zero, 0x4
/* 1B3F560 8008AF98 0C0043A2 */  sb         $v1, 0xC($s2)
/* 1B3F564 8008AF9C 652C0208 */  j          .Llevel_21_8008B194
/* 1B3F568 8008AFA0 0E0042A6 */   sh        $v0, 0xE($s2)
.Llevel_21_8008AFA4:
/* 1B3F56C 8008AFA4 C8E9000C */  jal        func_8003A720
/* 1B3F570 8008AFA8 21206002 */   addu      $a0, $s3, $zero
/* 1B3F574 8008AFAC 05000224 */  addiu      $v0, $zero, 0x5
/* 1B3F578 8008AFB0 7100A012 */  beqz       $s5, .Llevel_21_8008B178
/* 1B3F57C 8008AFB4 470062A2 */   sb        $v0, 0x47($s3)
/* 1B3F580 8008AFB8 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3F584 8008AFBC 612C0208 */  j          .Llevel_21_8008B184
/* 1B3F588 8008AFC0 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_21_8008AFC4:
/* 1B3F58C 8008AFC4 C8E9000C */  jal        func_8003A720
/* 1B3F590 8008AFC8 21206002 */   addu      $a0, $s3, $zero
/* 1B3F594 8008AFCC 0300A012 */  beqz       $s5, .Llevel_21_8008AFDC
/* 1B3F598 8008AFD0 0C006426 */   addiu     $a0, $s3, 0xC
/* 1B3F59C 8008AFD4 F92B0208 */  j          .Llevel_21_8008AFE4
/* 1B3F5A0 8008AFD8 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_21_8008AFDC:
/* 1B3F5A4 8008AFDC 0880053C */  lui        $a1, %hi(g_Spyro)
/* 1B3F5A8 8008AFE0 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_21_8008AFE4:
/* 1B3F5AC 8008AFE4 C05D000C */  jal        VecCopy
/* 1B3F5B0 8008AFE8 00000000 */   nop
/* 1B3F5B4 8008AFEC 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3F5B8 8008AFF0 1400628E */  lw         $v0, 0x14($s3)
/* 1B3F5BC 8008AFF4 00080524 */  addiu      $a1, $zero, 0x800
/* 1B3F5C0 8008AFF8 00024224 */  addiu      $v0, $v0, 0x200
/* 1B3F5C4 8008AFFC 7B35010C */  jal        func_8004D5EC
/* 1B3F5C8 8008B000 140062AE */   sw        $v0, 0x14($s3)
/* 1B3F5CC 8008B004 1400648E */  lw         $a0, 0x14($s3)
/* 1B3F5D0 8008B008 21184000 */  addu       $v1, $v0, $zero
/* 1B3F5D4 8008B00C 23106400 */  subu       $v0, $v1, $a0
/* 1B3F5D8 8008B010 02004104 */  bgez       $v0, .Llevel_21_8008B01C
/* 1B3F5DC 8008B014 00000000 */   nop
/* 1B3F5E0 8008B018 23100200 */  negu       $v0, $v0
.Llevel_21_8008B01C:
/* 1B3F5E4 8008B01C 00084228 */  slti       $v0, $v0, 0x800
/* 1B3F5E8 8008B020 03004010 */  beqz       $v0, .Llevel_21_8008B030
/* 1B3F5EC 8008B024 00FE8224 */   addiu     $v0, $a0, -0x200
/* 1B3F5F0 8008B028 632C0208 */  j          .Llevel_21_8008B18C
/* 1B3F5F4 8008B02C 140063AE */   sw        $v1, 0x14($s3)
.Llevel_21_8008B030:
/* 1B3F5F8 8008B030 632C0208 */  j          .Llevel_21_8008B18C
/* 1B3F5FC 8008B034 140062AE */   sw        $v0, 0x14($s3)
.Llevel_21_8008B038:
/* 1B3F600 8008B038 C8E9000C */  jal        func_8003A720
/* 1B3F604 8008B03C 21206002 */   addu      $a0, $s3, $zero
/* 1B3F608 8008B040 21206002 */  addu       $a0, $s3, $zero
/* 1B3F60C 8008B044 20000224 */  addiu      $v0, $zero, 0x20
/* 1B3F610 8008B048 500062A2 */  sb         $v0, 0x50($s3)
/* 1B3F614 8008B04C FF000224 */  addiu      $v0, $zero, 0xFF
/* 1B3F618 8008B050 734A010C */  jal        func_800529CC
/* 1B3F61C 8008B054 520062A2 */   sb        $v0, 0x52($s3)
/* 1B3F620 8008B058 662C0208 */  j          .Llevel_21_8008B198
/* 1B3F624 8008B05C 21106002 */   addu      $v0, $s3, $zero
.Llevel_21_8008B060:
/* 1B3F628 8008B060 0000708E */  lw         $s0, 0x0($s3)
/* 1B3F62C 8008B064 C8E9000C */  jal        func_8003A720
/* 1B3F630 8008B068 21206002 */   addu      $a0, $s3, $zero
/* 1B3F634 8008B06C 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3F638 8008B070 0C00A526 */  addiu      $a1, $s5, 0xC
/* 1B3F63C 8008B074 20000224 */  addiu      $v0, $zero, 0x20
/* 1B3F640 8008B078 C05D000C */  jal        VecCopy
/* 1B3F644 8008B07C 500062A2 */   sb        $v0, 0x50($s3)
/* 1B3F648 8008B080 AA49010C */  jal        func_800526A8
/* 1B3F64C 8008B084 21206002 */   addu      $a0, $s3, $zero
/* 1B3F650 8008B088 3600A386 */  lh         $v1, 0x36($s5)
/* 1B3F654 8008B08C B0000224 */  addiu      $v0, $zero, 0xB0
/* 1B3F658 8008B090 0B006214 */  bne        $v1, $v0, .Llevel_21_8008B0C0
/* 1B3F65C 8008B094 6AFF0424 */   addiu     $a0, $zero, -0x96
/* 1B3F660 8008B098 9CFF0424 */  addiu      $a0, $zero, -0x64
/* 1B3F664 8008B09C A8DF000C */  jal        RandRange
/* 1B3F668 8008B0A0 64000524 */   addiu     $a1, $zero, 0x64
/* 1B3F66C 8008B0A4 9CFF0424 */  addiu      $a0, $zero, -0x64
/* 1B3F670 8008B0A8 64000524 */  addiu      $a1, $zero, 0x64
/* 1B3F674 8008B0AC A8DF000C */  jal        RandRange
/* 1B3F678 8008B0B0 000002A6 */   sh        $v0, 0x0($s0)
/* 1B3F67C 8008B0B4 C4FF0424 */  addiu      $a0, $zero, -0x3C
/* 1B3F680 8008B0B8 382C0208 */  j          .Llevel_21_8008B0E0
/* 1B3F684 8008B0BC 6E000524 */   addiu     $a1, $zero, 0x6E
.Llevel_21_8008B0C0:
/* 1B3F688 8008B0C0 A8DF000C */  jal        RandRange
/* 1B3F68C 8008B0C4 96000524 */   addiu     $a1, $zero, 0x96
/* 1B3F690 8008B0C8 6AFF0424 */  addiu      $a0, $zero, -0x96
/* 1B3F694 8008B0CC 96000524 */  addiu      $a1, $zero, 0x96
/* 1B3F698 8008B0D0 A8DF000C */  jal        RandRange
/* 1B3F69C 8008B0D4 000002A6 */   sh        $v0, 0x0($s0)
/* 1B3F6A0 8008B0D8 BAFF0424 */  addiu      $a0, $zero, -0x46
/* 1B3F6A4 8008B0DC 96000524 */  addiu      $a1, $zero, 0x96
.Llevel_21_8008B0E0:
/* 1B3F6A8 8008B0E0 A8DF000C */  jal        RandRange
/* 1B3F6AC 8008B0E4 020002A6 */   sh        $v0, 0x2($s0)
/* 1B3F6B0 8008B0E8 040002A6 */  sh         $v0, 0x4($s0)
/* 1B3F6B4 8008B0EC 00000286 */  lh         $v0, 0x0($s0)
/* 1B3F6B8 8008B0F0 0C00638E */  lw         $v1, 0xC($s3)
/* 1B3F6BC 8008B0F4 80100200 */  sll        $v0, $v0, 2
/* 1B3F6C0 8008B0F8 21186200 */  addu       $v1, $v1, $v0
/* 1B3F6C4 8008B0FC 0C0063AE */  sw         $v1, 0xC($s3)
/* 1B3F6C8 8008B100 02000286 */  lh         $v0, 0x2($s0)
/* 1B3F6CC 8008B104 1000638E */  lw         $v1, 0x10($s3)
/* 1B3F6D0 8008B108 80100200 */  sll        $v0, $v0, 2
/* 1B3F6D4 8008B10C 21186200 */  addu       $v1, $v1, $v0
/* 1B3F6D8 8008B110 100063AE */  sw         $v1, 0x10($s3)
/* 1B3F6DC 8008B114 04000286 */  lh         $v0, 0x4($s0)
/* 1B3F6E0 8008B118 1400638E */  lw         $v1, 0x14($s3)
/* 1B3F6E4 8008B11C 80100200 */  sll        $v0, $v0, 2
/* 1B3F6E8 8008B120 21186200 */  addu       $v1, $v1, $v0
/* 1B3F6EC 8008B124 CB89010C */  jal        rand
/* 1B3F6F0 8008B128 140063AE */   sw        $v1, 0x14($s3)
/* 1B3F6F4 8008B12C 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F6F8 8008B130 CB89010C */  jal        rand
/* 1B3F6FC 8008B134 060002A6 */   sh        $v0, 0x6($s0)
/* 1B3F700 8008B138 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F704 8008B13C CB89010C */  jal        rand
/* 1B3F708 8008B140 080002A6 */   sh        $v0, 0x8($s0)
/* 1B3F70C 8008B144 18000424 */  addiu      $a0, $zero, 0x18
/* 1B3F710 8008B148 23000524 */  addiu      $a1, $zero, 0x23
/* 1B3F714 8008B14C 0F004230 */  andi       $v0, $v0, 0xF
/* 1B3F718 8008B150 A8DF000C */  jal        RandRange
/* 1B3F71C 8008B154 0A0002A6 */   sh        $v0, 0xA($s0)
/* 1B3F720 8008B158 652C0208 */  j          .Llevel_21_8008B194
/* 1B3F724 8008B15C 0C0002AE */   sw        $v0, 0xC($s0)
.Llevel_21_8008B160:
/* 1B3F728 8008B160 C8E9000C */  jal        func_8003A720
/* 1B3F72C 8008B164 21206002 */   addu      $a0, $s3, $zero
/* 1B3F730 8008B168 0300A012 */  beqz       $s5, .Llevel_21_8008B178
/* 1B3F734 8008B16C 0C00A526 */   addiu     $a1, $s5, 0xC
/* 1B3F738 8008B170 612C0208 */  j          .Llevel_21_8008B184
/* 1B3F73C 8008B174 0C006426 */   addiu     $a0, $s3, 0xC
.Llevel_21_8008B178:
/* 1B3F740 8008B178 0C006426 */  addiu      $a0, $s3, 0xC
/* 1B3F744 8008B17C 0880053C */  lui        $a1, %hi(g_Spyro)
/* 1B3F748 8008B180 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_21_8008B184:
/* 1B3F74C 8008B184 C05D000C */  jal        VecCopy
/* 1B3F750 8008B188 00000000 */   nop
.Llevel_21_8008B18C:
/* 1B3F754 8008B18C AA49010C */  jal        func_800526A8
/* 1B3F758 8008B190 21206002 */   addu      $a0, $s3, $zero
.Llevel_21_8008B194:
/* 1B3F75C 8008B194 21106002 */  addu       $v0, $s3, $zero
.Llevel_21_8008B198:
/* 1B3F760 8008B198 5000BF8F */  lw         $ra, 0x50($sp)
/* 1B3F764 8008B19C 4C00B58F */  lw         $s5, 0x4C($sp)
/* 1B3F768 8008B1A0 4800B48F */  lw         $s4, 0x48($sp)
/* 1B3F76C 8008B1A4 4400B38F */  lw         $s3, 0x44($sp)
/* 1B3F770 8008B1A8 4000B28F */  lw         $s2, 0x40($sp)
/* 1B3F774 8008B1AC 3C00B18F */  lw         $s1, 0x3C($sp)
/* 1B3F778 8008B1B0 3800B08F */  lw         $s0, 0x38($sp)
/* 1B3F77C 8008B1B4 5800BD27 */  addiu      $sp, $sp, 0x58
/* 1B3F780 8008B1B8 0800E003 */  jr         $ra
/* 1B3F784 8008B1BC 00000000 */   nop
.size func_level_21_8008A4D0, . - func_level_21_8008A4D0
