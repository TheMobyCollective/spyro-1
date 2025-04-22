.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_60_80083568
/* 51EBB30 80083568 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 51EBB34 8008356C 3800B0AF */  sw         $s0, 0x38($sp)
/* 51EBB38 80083570 21808000 */  addu       $s0, $a0, $zero
/* 51EBB3C 80083574 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 51EBB40 80083578 21A8A000 */  addu       $s5, $a1, $zero
/* 51EBB44 8008357C 5000BFAF */  sw         $ra, 0x50($sp)
/* 51EBB48 80083580 4800B4AF */  sw         $s4, 0x48($sp)
/* 51EBB4C 80083584 4400B3AF */  sw         $s3, 0x44($sp)
/* 51EBB50 80083588 4000B2AF */  sw         $s2, 0x40($sp)
/* 51EBB54 8008358C 3149010C */  jal        func_800524C4
/* 51EBB58 80083590 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 51EBB5C 80083594 21984000 */  addu       $s3, $v0, $zero
/* 51EBB60 80083598 1400A012 */  beqz       $s5, .Llevel_60_800835EC
/* 51EBB64 8008359C 360070A6 */   sh        $s0, 0x36($s3)
/* 51EBB68 800835A0 0780043C */  lui        $a0, %hi(D_80075828)
/* 51EBB6C 800835A4 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 51EBB70 800835A8 00000000 */  nop
/* 51EBB74 800835AC 2320A402 */  subu       $a0, $s5, $a0
/* 51EBB78 800835B0 40190400 */  sll        $v1, $a0, 5
/* 51EBB7C 800835B4 23186400 */  subu       $v1, $v1, $a0
/* 51EBB80 800835B8 40190300 */  sll        $v1, $v1, 5
/* 51EBB84 800835BC 21186400 */  addu       $v1, $v1, $a0
/* 51EBB88 800835C0 C0100300 */  sll        $v0, $v1, 3
/* 51EBB8C 800835C4 21186200 */  addu       $v1, $v1, $v0
/* 51EBB90 800835C8 C0130300 */  sll        $v0, $v1, 15
/* 51EBB94 800835CC 23104300 */  subu       $v0, $v0, $v1
/* 51EBB98 800835D0 80100200 */  sll        $v0, $v0, 2
/* 51EBB9C 800835D4 21104400 */  addu       $v0, $v0, $a0
/* 51EBBA0 800835D8 23100200 */  negu       $v0, $v0
/* 51EBBA4 800835DC C3180200 */  sra        $v1, $v0, 3
/* 51EBBA8 800835E0 0001622C */  sltiu      $v0, $v1, 0x100
/* 51EBBAC 800835E4 03004014 */  bnez       $v0, .Llevel_60_800835F4
/* 51EBBB0 800835E8 0201022A */   slti      $v0, $s0, 0x102
.Llevel_60_800835EC:
/* 51EBBB4 800835EC 21180000 */  addu       $v1, $zero, $zero
/* 51EBBB8 800835F0 0201022A */  slti       $v0, $s0, 0x102
.Llevel_60_800835F4:
/* 51EBBBC 800835F4 27004010 */  beqz       $v0, .Llevel_60_80083694
/* 51EBBC0 800835F8 560063A2 */   sb        $v1, 0x56($s3)
/* 51EBBC4 800835FC FF00022A */  slti       $v0, $s0, 0xFF
/* 51EBBC8 80083600 FB004010 */  beqz       $v0, .Llevel_60_800839F0
/* 51EBBCC 80083604 4C000224 */   addiu     $v0, $zero, 0x4C
/* 51EBBD0 80083608 11020212 */  beq        $s0, $v0, .Llevel_60_80083E50
/* 51EBBD4 8008360C 4D00022A */   slti      $v0, $s0, 0x4D
/* 51EBBD8 80083610 10004010 */  beqz       $v0, .Llevel_60_80083654
/* 51EBBDC 80083614 0F000224 */   addiu     $v0, $zero, 0xF
/* 51EBBE0 80083618 44000212 */  beq        $s0, $v0, .Llevel_60_8008372C
/* 51EBBE4 8008361C 1000022A */   slti      $v0, $s0, 0x10
/* 51EBBE8 80083620 05004010 */  beqz       $v0, .Llevel_60_80083638
/* 51EBBEC 80083624 0E000224 */   addiu     $v0, $zero, 0xE
/* 51EBBF0 80083628 89000212 */  beq        $s0, $v0, .Llevel_60_80083850
/* 51EBBF4 8008362C 00000000 */   nop
/* 51EBBF8 80083630 9E0F0208 */  j          .Llevel_60_80083E78
/* 51EBBFC 80083634 00000000 */   nop
.Llevel_60_80083638:
/* 51EBC00 80083638 10000224 */  addiu      $v0, $zero, 0x10
/* 51EBC04 8008363C 62000212 */  beq        $s0, $v0, .Llevel_60_800837C8
/* 51EBC08 80083640 22000224 */   addiu     $v0, $zero, 0x22
/* 51EBC0C 80083644 74000212 */  beq        $s0, $v0, .Llevel_60_80083818
/* 51EBC10 80083648 00000000 */   nop
/* 51EBC14 8008364C 9E0F0208 */  j          .Llevel_60_80083E78
/* 51EBC18 80083650 00000000 */   nop
.Llevel_60_80083654:
/* 51EBC1C 80083654 78000224 */  addiu      $v0, $zero, 0x78
/* 51EBC20 80083658 D3000212 */  beq        $s0, $v0, .Llevel_60_800839A8
/* 51EBC24 8008365C 7900022A */   slti      $v0, $s0, 0x79
/* 51EBC28 80083660 07004010 */  beqz       $v0, .Llevel_60_80083680
/* 51EBC2C 80083664 5800022A */   slti      $v0, $s0, 0x58
/* 51EBC30 80083668 03024010 */  beqz       $v0, .Llevel_60_80083E78
/* 51EBC34 8008366C 5300022A */   slti      $v0, $s0, 0x53
/* 51EBC38 80083670 77004010 */  beqz       $v0, .Llevel_60_80083850
/* 51EBC3C 80083674 00000000 */   nop
/* 51EBC40 80083678 9E0F0208 */  j          .Llevel_60_80083E78
/* 51EBC44 8008367C 00000000 */   nop
.Llevel_60_80083680:
/* 51EBC48 80083680 FB000224 */  addiu      $v0, $zero, 0xFB
/* 51EBC4C 80083684 45010212 */  beq        $s0, $v0, .Llevel_60_80083B9C
/* 51EBC50 80083688 00000000 */   nop
/* 51EBC54 8008368C 9E0F0208 */  j          .Llevel_60_80083E78
/* 51EBC58 80083690 00000000 */   nop
.Llevel_60_80083694:
/* 51EBC5C 80083694 47010224 */  addiu      $v0, $zero, 0x147
/* 51EBC60 80083698 B0010212 */  beq        $s0, $v0, .Llevel_60_80083D5C
/* 51EBC64 8008369C 4801022A */   slti      $v0, $s0, 0x148
/* 51EBC68 800836A0 12004010 */  beqz       $v0, .Llevel_60_800836EC
/* 51EBC6C 800836A4 15010224 */   addiu     $v0, $zero, 0x115
/* 51EBC70 800836A8 AC010212 */  beq        $s0, $v0, .Llevel_60_80083D5C
/* 51EBC74 800836AC 1601022A */   slti      $v0, $s0, 0x116
/* 51EBC78 800836B0 07004010 */  beqz       $v0, .Llevel_60_800836D0
/* 51EBC7C 800836B4 0E01022A */   slti      $v0, $s0, 0x10E
/* 51EBC80 800836B8 EF014010 */  beqz       $v0, .Llevel_60_80083E78
/* 51EBC84 800836BC 0401022A */   slti      $v0, $s0, 0x104
/* 51EBC88 800836C0 A6014010 */  beqz       $v0, .Llevel_60_80083D5C
/* 51EBC8C 800836C4 00000000 */   nop
/* 51EBC90 800836C8 9E0F0208 */  j          .Llevel_60_80083E78
/* 51EBC94 800836CC 00000000 */   nop
.Llevel_60_800836D0:
/* 51EBC98 800836D0 3801022A */  slti       $v0, $s0, 0x138
/* 51EBC9C 800836D4 E8014010 */  beqz       $v0, .Llevel_60_80083E78
/* 51EBCA0 800836D8 3501022A */   slti      $v0, $s0, 0x135
/* 51EBCA4 800836DC C4004010 */  beqz       $v0, .Llevel_60_800839F0
/* 51EBCA8 800836E0 00000000 */   nop
/* 51EBCAC 800836E4 9E0F0208 */  j          .Llevel_60_80083E78
/* 51EBCB0 800836E8 00000000 */   nop
.Llevel_60_800836EC:
/* 51EBCB4 800836EC C401022A */  slti       $v0, $s0, 0x1C4
/* 51EBCB8 800836F0 09004010 */  beqz       $v0, .Llevel_60_80083718
/* 51EBCBC 800836F4 AA01022A */   slti      $v0, $s0, 0x1AA
/* 51EBCC0 800836F8 D5014010 */  beqz       $v0, .Llevel_60_80083E50
/* 51EBCC4 800836FC 8E010224 */   addiu     $v0, $zero, 0x18E
/* 51EBCC8 80083700 A3010212 */  beq        $s0, $v0, .Llevel_60_80083D90
/* 51EBCCC 80083704 95010224 */   addiu     $v0, $zero, 0x195
/* 51EBCD0 80083708 B4010212 */  beq        $s0, $v0, .Llevel_60_80083DDC
/* 51EBCD4 8008370C 00000000 */   nop
/* 51EBCD8 80083710 9E0F0208 */  j          .Llevel_60_80083E78
/* 51EBCDC 80083714 00000000 */   nop
.Llevel_60_80083718:
/* 51EBCE0 80083718 DD010224 */  addiu      $v0, $zero, 0x1DD
/* 51EBCE4 8008371C AF010212 */  beq        $s0, $v0, .Llevel_60_80083DDC
/* 51EBCE8 80083720 00000000 */   nop
/* 51EBCEC 80083724 9E0F0208 */  j          .Llevel_60_80083E78
/* 51EBCF0 80083728 00000000 */   nop
.Llevel_60_8008372C:
/* 51EBCF4 8008372C 0000708E */  lw         $s0, 0x0($s3)
/* 51EBCF8 80083730 C8E9000C */  jal        func_8003A720
/* 51EBCFC 80083734 21206002 */   addu      $a0, $s3, $zero
/* 51EBD00 80083738 8C000224 */  addiu      $v0, $zero, 0x8C
/* 51EBD04 8008373C 080002AE */  sw         $v0, 0x8($s0)
/* 51EBD08 80083740 03000224 */  addiu      $v0, $zero, 0x3
/* 51EBD0C 80083744 100002A2 */  sb         $v0, 0x10($s0)
/* 51EBD10 80083748 FF000224 */  addiu      $v0, $zero, 0xFF
/* 51EBD14 8008374C 140002A2 */  sb         $v0, 0x14($s0)
/* 51EBD18 80083750 02000224 */  addiu      $v0, $zero, 0x2
/* 51EBD1C 80083754 000000AE */  sw         $zero, 0x0($s0)
/* 51EBD20 80083758 040000AE */  sw         $zero, 0x4($s0)
/* 51EBD24 8008375C 0E0000A2 */  sb         $zero, 0xE($s0)
/* 51EBD28 80083760 0F0000A2 */  sb         $zero, 0xF($s0)
/* 51EBD2C 80083764 110000A2 */  sb         $zero, 0x11($s0)
/* 51EBD30 80083768 120000A2 */  sb         $zero, 0x12($s0)
/* 51EBD34 8008376C 130000A2 */  sb         $zero, 0x13($s0)
/* 51EBD38 80083770 490062A2 */  sb         $v0, 0x49($s3)
/* 51EBD3C 80083774 18000224 */  addiu      $v0, $zero, 0x18
/* 51EBD40 80083778 500062A2 */  sb         $v0, 0x50($s3)
/* 51EBD44 8008377C 10000224 */  addiu      $v0, $zero, 0x10
/* 51EBD48 80083780 520062A2 */  sb         $v0, 0x52($s3)
/* 51EBD4C 80083784 20000224 */  addiu      $v0, $zero, 0x20
/* 51EBD50 80083788 440062A2 */  sb         $v0, 0x44($s3)
/* 51EBD54 8008378C 450060A2 */  sb         $zero, 0x45($s3)
/* 51EBD58 80083790 0400A012 */  beqz       $s5, .Llevel_60_800837A4
/* 51EBD5C 80083794 460060A2 */   sb        $zero, 0x46($s3)
/* 51EBD60 80083798 0C006426 */  addiu      $a0, $s3, 0xC
/* 51EBD64 8008379C C05D000C */  jal        VecCopy
/* 51EBD68 800837A0 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_60_800837A4:
/* 51EBD6C 800837A4 AA49010C */  jal        func_800526A8
/* 51EBD70 800837A8 21206002 */   addu      $a0, $s3, $zero
/* 51EBD74 800837AC 4B006292 */  lbu        $v0, 0x4B($s3)
/* 51EBD78 800837B0 01000324 */  addiu      $v1, $zero, 0x1
/* 51EBD7C 800837B4 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 51EBD80 800837B8 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 51EBD84 800837BC 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 51EBD88 800837C0 E40E0208 */  j          .Llevel_60_80083B90
/* 51EBD8C 800837C4 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_60_800837C8:
/* 51EBD90 800837C8 0000718E */  lw         $s1, 0x0($s3)
/* 51EBD94 800837CC C8E9000C */  jal        func_8003A720
/* 51EBD98 800837D0 21206002 */   addu      $a0, $s3, $zero
/* 51EBD9C 800837D4 AA49010C */  jal        func_800526A8
/* 51EBDA0 800837D8 21206002 */   addu      $a0, $s3, $zero
/* 51EBDA4 800837DC 0C007026 */  addiu      $s0, $s3, 0xC
/* 51EBDA8 800837E0 21200002 */  addu       $a0, $s0, $zero
/* 51EBDAC 800837E4 C05D000C */  jal        VecCopy
/* 51EBDB0 800837E8 0C00A526 */   addiu     $a1, $s5, 0xC
/* 51EBDB4 800837EC 21280002 */  addu       $a1, $s0, $zero
/* 51EBDB8 800837F0 1400628E */  lw         $v0, 0x14($s3)
/* 51EBDBC 800837F4 04002426 */  addiu      $a0, $s1, 0x4
/* 51EBDC0 800837F8 00024224 */  addiu      $v0, $v0, 0x200
/* 51EBDC4 800837FC C05D000C */  jal        VecCopy
/* 51EBDC8 80083800 140062AE */   sw        $v0, 0x14($s3)
/* 51EBDCC 80083804 08070224 */  addiu      $v0, $zero, 0x708
/* 51EBDD0 80083808 130020A2 */  sb         $zero, 0x13($s1)
/* 51EBDD4 8008380C 120020A2 */  sb         $zero, 0x12($s1)
/* 51EBDD8 80083810 AB0F0208 */  j          .Llevel_60_80083EAC
/* 51EBDDC 80083814 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_60_80083818:
/* 51EBDE0 80083818 C8E9000C */  jal        func_8003A720
/* 51EBDE4 8008381C 21206002 */   addu      $a0, $s3, $zero
/* 51EBDE8 80083820 20000224 */  addiu      $v0, $zero, 0x20
/* 51EBDEC 80083824 500062A2 */  sb         $v0, 0x50($s3)
/* 51EBDF0 80083828 FF000224 */  addiu      $v0, $zero, 0xFF
/* 51EBDF4 8008382C 0400A012 */  beqz       $s5, .Llevel_60_80083840
/* 51EBDF8 80083830 520062A2 */   sb        $v0, 0x52($s3)
/* 51EBDFC 80083834 0C006426 */  addiu      $a0, $s3, 0xC
/* 51EBE00 80083838 C05D000C */  jal        VecCopy
/* 51EBE04 8008383C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_60_80083840:
/* 51EBE08 80083840 734A010C */  jal        func_800529CC
/* 51EBE0C 80083844 21206002 */   addu      $a0, $s3, $zero
/* 51EBE10 80083848 AC0F0208 */  j          .Llevel_60_80083EB0
/* 51EBE14 8008384C 21106002 */   addu      $v0, $s3, $zero
.Llevel_60_80083850:
/* 51EBE18 80083850 0000718E */  lw         $s1, 0x0($s3)
/* 51EBE1C 80083854 C8E9000C */  jal        func_8003A720
/* 51EBE20 80083858 21206002 */   addu      $a0, $s3, $zero
/* 51EBE24 8008385C 8C000224 */  addiu      $v0, $zero, 0x8C
/* 51EBE28 80083860 000020AE */  sw         $zero, 0x0($s1)
/* 51EBE2C 80083864 040020AE */  sw         $zero, 0x4($s1)
/* 51EBE30 80083868 080022AE */  sw         $v0, 0x8($s1)
/* 51EBE34 8008386C 0E0020A2 */  sb         $zero, 0xE($s1)
/* 51EBE38 80083870 0F0020A2 */  sb         $zero, 0xF($s1)
/* 51EBE3C 80083874 110020A2 */  sb         $zero, 0x11($s1)
/* 51EBE40 80083878 120020A2 */  sb         $zero, 0x12($s1)
/* 51EBE44 8008387C 130020A2 */  sb         $zero, 0x13($s1)
/* 51EBE48 80083880 3600A386 */  lh         $v1, 0x36($s5)
/* 51EBE4C 80083884 0D000224 */  addiu      $v0, $zero, 0xD
/* 51EBE50 80083888 02006214 */  bne        $v1, $v0, .Llevel_60_80083894
/* 51EBE54 8008388C 03000224 */   addiu     $v0, $zero, 0x3
/* 51EBE58 80083890 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_60_80083894:
/* 51EBE5C 80083894 100022A2 */  sb         $v0, 0x10($s1)
/* 51EBE60 80083898 0C007026 */  addiu      $s0, $s3, 0xC
/* 51EBE64 8008389C 21200002 */  addu       $a0, $s0, $zero
/* 51EBE68 800838A0 0C00A526 */  addiu      $a1, $s5, 0xC
/* 51EBE6C 800838A4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 51EBE70 800838A8 140022A2 */  sb         $v0, 0x14($s1)
/* 51EBE74 800838AC 02001124 */  addiu      $s1, $zero, 0x2
/* 51EBE78 800838B0 18000224 */  addiu      $v0, $zero, 0x18
/* 51EBE7C 800838B4 500062A2 */  sb         $v0, 0x50($s3)
/* 51EBE80 800838B8 40000224 */  addiu      $v0, $zero, 0x40
/* 51EBE84 800838BC 520062A2 */  sb         $v0, 0x52($s3)
/* 51EBE88 800838C0 20000224 */  addiu      $v0, $zero, 0x20
/* 51EBE8C 800838C4 490071A2 */  sb         $s1, 0x49($s3)
/* 51EBE90 800838C8 440062A2 */  sb         $v0, 0x44($s3)
/* 51EBE94 800838CC 450060A2 */  sb         $zero, 0x45($s3)
/* 51EBE98 800838D0 C05D000C */  jal        VecCopy
/* 51EBE9C 800838D4 460060A2 */   sb        $zero, 0x46($s3)
/* 51EBEA0 800838D8 734A010C */  jal        func_800529CC
/* 51EBEA4 800838DC 21206002 */   addu      $a0, $s3, $zero
/* 51EBEA8 800838E0 1000A427 */  addiu      $a0, $sp, 0x10
/* 51EBEAC 800838E4 21280002 */  addu       $a1, $s0, $zero
/* 51EBEB0 800838E8 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 51EBEB4 800838EC C05D000C */  jal        VecCopy
/* 51EBEB8 800838F0 1C0062AE */   sw        $v0, 0x1C($s3)
/* 51EBEBC 800838F4 1000A427 */  addiu      $a0, $sp, 0x10
/* 51EBEC0 800838F8 1800A28F */  lw         $v0, 0x18($sp)
/* 51EBEC4 800838FC 0100053C */  lui        $a1, (0x10000 >> 16)
/* 51EBEC8 80083900 00044224 */  addiu      $v0, $v0, 0x400
/* 51EBECC 80083904 7B35010C */  jal        func_8004D5EC
/* 51EBED0 80083908 1800A2AF */   sw        $v0, 0x18($sp)
/* 51EBED4 8008390C F44C010C */  jal        func_800533D0
/* 51EBED8 80083910 21206002 */   addu      $a0, $s3, $zero
/* 51EBEDC 80083914 36006386 */  lh         $v1, 0x36($s3)
/* 51EBEE0 80083918 0E000224 */  addiu      $v0, $zero, 0xE
/* 51EBEE4 8008391C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 51EBEE8 80083920 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 51EBEEC 80083924 03006214 */  bne        $v1, $v0, .Llevel_60_80083934
/* 51EBEF0 80083928 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 51EBEF4 8008392C 0C000224 */  addiu      $v0, $zero, 0xC
/* 51EBEF8 80083930 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_60_80083934:
/* 51EBEFC 80083934 36006386 */  lh         $v1, 0x36($s3)
/* 51EBF00 80083938 53000224 */  addiu      $v0, $zero, 0x53
/* 51EBF04 8008393C 05006214 */  bne        $v1, $v0, .Llevel_60_80083954
/* 51EBF08 80083940 54000224 */   addiu     $v0, $zero, 0x54
/* 51EBF0C 80083944 01000224 */  addiu      $v0, $zero, 0x1
/* 51EBF10 80083948 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 51EBF14 8008394C 36006386 */  lh         $v1, 0x36($s3)
/* 51EBF18 80083950 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_60_80083954:
/* 51EBF1C 80083954 02006214 */  bne        $v1, $v0, .Llevel_60_80083960
/* 51EBF20 80083958 00000000 */   nop
/* 51EBF24 8008395C 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_60_80083960:
/* 51EBF28 80083960 36006386 */  lh         $v1, 0x36($s3)
/* 51EBF2C 80083964 55000224 */  addiu      $v0, $zero, 0x55
/* 51EBF30 80083968 05006214 */  bne        $v1, $v0, .Llevel_60_80083980
/* 51EBF34 8008396C 56000224 */   addiu     $v0, $zero, 0x56
/* 51EBF38 80083970 03000224 */  addiu      $v0, $zero, 0x3
/* 51EBF3C 80083974 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 51EBF40 80083978 36006386 */  lh         $v1, 0x36($s3)
/* 51EBF44 8008397C 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_60_80083980:
/* 51EBF48 80083980 02006214 */  bne        $v1, $v0, .Llevel_60_8008398C
/* 51EBF4C 80083984 04000224 */   addiu     $v0, $zero, 0x4
/* 51EBF50 80083988 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_60_8008398C:
/* 51EBF54 8008398C 36006386 */  lh         $v1, 0x36($s3)
/* 51EBF58 80083990 57000224 */  addiu      $v0, $zero, 0x57
/* 51EBF5C 80083994 46016214 */  bne        $v1, $v0, .Llevel_60_80083EB0
/* 51EBF60 80083998 21106002 */   addu      $v0, $s3, $zero
/* 51EBF64 8008399C 05000224 */  addiu      $v0, $zero, 0x5
/* 51EBF68 800839A0 AB0F0208 */  j          .Llevel_60_80083EAC
/* 51EBF6C 800839A4 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_60_800839A8:
/* 51EBF70 800839A8 0000708E */  lw         $s0, 0x0($s3)
/* 51EBF74 800839AC C8E9000C */  jal        func_8003A720
/* 51EBF78 800839B0 21206002 */   addu      $a0, $s3, $zero
/* 51EBF7C 800839B4 AA49010C */  jal        func_800526A8
/* 51EBF80 800839B8 21206002 */   addu      $a0, $s3, $zero
/* 51EBF84 800839BC 490060A2 */  sb         $zero, 0x49($s3)
/* 51EBF88 800839C0 000000AE */  sw         $zero, 0x0($s0)
/* 51EBF8C 800839C4 080000A6 */  sh         $zero, 0x8($s0)
/* 51EBF90 800839C8 060000A6 */  sh         $zero, 0x6($s0)
/* 51EBF94 800839CC 040000A6 */  sh         $zero, 0x4($s0)
/* 51EBF98 800839D0 0C0000AE */  sw         $zero, 0xC($s0)
/* 51EBF9C 800839D4 3501A012 */  beqz       $s5, .Llevel_60_80083EAC
/* 51EBFA0 800839D8 100000AE */   sw        $zero, 0x10($s0)
/* 51EBFA4 800839DC 0C006426 */  addiu      $a0, $s3, 0xC
/* 51EBFA8 800839E0 C05D000C */  jal        VecCopy
/* 51EBFAC 800839E4 0C00A526 */   addiu     $a1, $s5, 0xC
/* 51EBFB0 800839E8 AC0F0208 */  j          .Llevel_60_80083EB0
/* 51EBFB4 800839EC 21106002 */   addu      $v0, $s3, $zero
.Llevel_60_800839F0:
/* 51EBFB8 800839F0 0000748E */  lw         $s4, 0x0($s3)
/* 51EBFBC 800839F4 C8E9000C */  jal        func_8003A720
/* 51EBFC0 800839F8 21206002 */   addu      $a0, $s3, $zero
/* 51EBFC4 800839FC 0C006426 */  addiu      $a0, $s3, 0xC
/* 51EBFC8 80083A00 0C00A526 */  addiu      $a1, $s5, 0xC
/* 51EBFCC 80083A04 20000224 */  addiu      $v0, $zero, 0x20
/* 51EBFD0 80083A08 C05D000C */  jal        VecCopy
/* 51EBFD4 80083A0C 500062A2 */   sb        $v0, 0x50($s3)
/* 51EBFD8 80083A10 AA49010C */  jal        func_800526A8
/* 51EBFDC 80083A14 21206002 */   addu      $a0, $s3, $zero
/* 51EBFE0 80083A18 CB89010C */  jal        rand
/* 51EBFE4 80083A1C 00000000 */   nop
/* 51EBFE8 80083A20 CB89010C */  jal        rand
/* 51EBFEC 80083A24 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 51EBFF0 80083A28 FF075130 */  andi       $s1, $v0, 0x7FF
/* 51EBFF4 80083A2C 2C5B000C */  jal        Cos
/* 51EBFF8 80083A30 21202002 */   addu      $a0, $s1, $zero
/* 51EBFFC 80083A34 21204002 */  addu       $a0, $s2, $zero
/* 51EC000 80083A38 2C5B000C */  jal        Cos
/* 51EC004 80083A3C 21804000 */   addu      $s0, $v0, $zero
/* 51EC008 80083A40 43811000 */  sra        $s0, $s0, 5
/* 51EC00C 80083A44 18000202 */  mult       $s0, $v0
/* 51EC010 80083A48 21202002 */  addu       $a0, $s1, $zero
/* 51EC014 80083A4C 12380000 */  mflo       $a3
/* 51EC018 80083A50 03130700 */  sra        $v0, $a3, 12
/* 51EC01C 80083A54 2C5B000C */  jal        Cos
/* 51EC020 80083A58 000082A6 */   sh        $v0, 0x0($s4)
/* 51EC024 80083A5C 21204002 */  addu       $a0, $s2, $zero
/* 51EC028 80083A60 165B000C */  jal        Sin
/* 51EC02C 80083A64 21804000 */   addu      $s0, $v0, $zero
/* 51EC030 80083A68 43811000 */  sra        $s0, $s0, 5
/* 51EC034 80083A6C 18000202 */  mult       $s0, $v0
/* 51EC038 80083A70 21202002 */  addu       $a0, $s1, $zero
/* 51EC03C 80083A74 12380000 */  mflo       $a3
/* 51EC040 80083A78 03130700 */  sra        $v0, $a3, 12
/* 51EC044 80083A7C 165B000C */  jal        Sin
/* 51EC048 80083A80 020082A6 */   sh        $v0, 0x2($s4)
/* 51EC04C 80083A84 43110200 */  sra        $v0, $v0, 5
/* 51EC050 80083A88 040082A6 */  sh         $v0, 0x4($s4)
/* 51EC054 80083A8C 1800A28E */  lw         $v0, 0x18($s5)
/* 51EC058 80083A90 0200033C */  lui        $v1, (0x20000 >> 16)
/* 51EC05C 80083A94 24104300 */  and        $v0, $v0, $v1
/* 51EC060 80083A98 13004010 */  beqz       $v0, .Llevel_60_80083AE8
/* 51EC064 80083A9C 00000000 */   nop
/* 51EC068 80083AA0 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 51EC06C 80083AA4 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 51EC070 80083AA8 00008396 */  lhu        $v1, 0x0($s4)
/* 51EC074 80083AAC 83110200 */  sra        $v0, $v0, 6
/* 51EC078 80083AB0 21186200 */  addu       $v1, $v1, $v0
/* 51EC07C 80083AB4 000083A6 */  sh         $v1, 0x0($s4)
/* 51EC080 80083AB8 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 51EC084 80083ABC 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 51EC088 80083AC0 02008396 */  lhu        $v1, 0x2($s4)
/* 51EC08C 80083AC4 83110200 */  sra        $v0, $v0, 6
/* 51EC090 80083AC8 21186200 */  addu       $v1, $v1, $v0
/* 51EC094 80083ACC 020083A6 */  sh         $v1, 0x2($s4)
/* 51EC098 80083AD0 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 51EC09C 80083AD4 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 51EC0A0 80083AD8 04008396 */  lhu        $v1, 0x4($s4)
/* 51EC0A4 80083ADC 83110200 */  sra        $v0, $v0, 6
/* 51EC0A8 80083AE0 21186200 */  addu       $v1, $v1, $v0
/* 51EC0AC 80083AE4 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_60_80083AE8:
/* 51EC0B0 80083AE8 00008286 */  lh         $v0, 0x0($s4)
/* 51EC0B4 80083AEC 0C00638E */  lw         $v1, 0xC($s3)
/* 51EC0B8 80083AF0 80100200 */  sll        $v0, $v0, 2
/* 51EC0BC 80083AF4 21186200 */  addu       $v1, $v1, $v0
/* 51EC0C0 80083AF8 0C0063AE */  sw         $v1, 0xC($s3)
/* 51EC0C4 80083AFC 02008286 */  lh         $v0, 0x2($s4)
/* 51EC0C8 80083B00 1000638E */  lw         $v1, 0x10($s3)
/* 51EC0CC 80083B04 80100200 */  sll        $v0, $v0, 2
/* 51EC0D0 80083B08 21186200 */  addu       $v1, $v1, $v0
/* 51EC0D4 80083B0C 100063AE */  sw         $v1, 0x10($s3)
/* 51EC0D8 80083B10 04008286 */  lh         $v0, 0x4($s4)
/* 51EC0DC 80083B14 1400638E */  lw         $v1, 0x14($s3)
/* 51EC0E0 80083B18 80100200 */  sll        $v0, $v0, 2
/* 51EC0E4 80083B1C 21186200 */  addu       $v1, $v1, $v0
/* 51EC0E8 80083B20 CB89010C */  jal        rand
/* 51EC0EC 80083B24 140063AE */   sw        $v1, 0x14($s3)
/* 51EC0F0 80083B28 0F004230 */  andi       $v0, $v0, 0xF
/* 51EC0F4 80083B2C CB89010C */  jal        rand
/* 51EC0F8 80083B30 060082A6 */   sh        $v0, 0x6($s4)
/* 51EC0FC 80083B34 0F004230 */  andi       $v0, $v0, 0xF
/* 51EC100 80083B38 CB89010C */  jal        rand
/* 51EC104 80083B3C 080082A6 */   sh        $v0, 0x8($s4)
/* 51EC108 80083B40 0F004230 */  andi       $v0, $v0, 0xF
/* 51EC10C 80083B44 0A0082A6 */  sh         $v0, 0xA($s4)
/* 51EC110 80083B48 1400A28E */  lw         $v0, 0x14($s5)
/* 51EC114 80083B4C 00000000 */  nop
/* 51EC118 80083B50 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 51EC11C 80083B54 CB89010C */  jal        rand
/* 51EC120 80083B58 100082AE */   sw        $v0, 0x10($s4)
/* 51EC124 80083B5C 0F004230 */  andi       $v0, $v0, 0xF
/* 51EC128 80083B60 40000324 */  addiu      $v1, $zero, 0x40
/* 51EC12C 80083B64 23186200 */  subu       $v1, $v1, $v0
/* 51EC130 80083B68 0C0083AE */  sw         $v1, 0xC($s4)
/* 51EC134 80083B6C 36006296 */  lhu        $v0, 0x36($s3)
/* 51EC138 80083B70 00000000 */  nop
/* 51EC13C 80083B74 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 51EC140 80083B78 0300422C */  sltiu      $v0, $v0, 0x3
/* 51EC144 80083B7C CB004010 */  beqz       $v0, .Llevel_60_80083EAC
/* 51EC148 80083B80 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 51EC14C 80083B84 4B006292 */  lbu        $v0, 0x4B($s3)
/* 51EC150 80083B88 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 51EC154 80083B8C 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_60_80083B90:
/* 51EC158 80083B90 80004234 */  ori        $v0, $v0, 0x80
/* 51EC15C 80083B94 AB0F0208 */  j          .Llevel_60_80083EAC
/* 51EC160 80083B98 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_60_80083B9C:
/* 51EC164 80083B9C 0000718E */  lw         $s1, 0x0($s3)
/* 51EC168 80083BA0 C8E9000C */  jal        func_8003A720
/* 51EC16C 80083BA4 21206002 */   addu      $a0, $s3, $zero
/* 51EC170 80083BA8 21206002 */  addu       $a0, $s3, $zero
/* 51EC174 80083BAC 20000224 */  addiu      $v0, $zero, 0x20
/* 51EC178 80083BB0 500062A2 */  sb         $v0, 0x50($s3)
/* 51EC17C 80083BB4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 51EC180 80083BB8 734A010C */  jal        func_800529CC
/* 51EC184 80083BBC 520062A2 */   sb        $v0, 0x52($s3)
/* 51EC188 80083BC0 0E000224 */  addiu      $v0, $zero, 0xE
/* 51EC18C 80083BC4 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 51EC190 80083BC8 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 51EC194 80083BCC 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 51EC198 80083BD0 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 51EC19C 80083BD4 0780033C */  lui        $v1, %hi(D_80077058)
/* 51EC1A0 80083BD8 5870638C */  lw         $v1, %lo(D_80077058)($v1)
/* 51EC1A4 80083BDC 03000224 */  addiu      $v0, $zero, 0x3
/* 51EC1A8 80083BE0 03006214 */  bne        $v1, $v0, .Llevel_60_80083BF0
/* 51EC1AC 80083BE4 01000224 */   addiu     $v0, $zero, 0x1
/* 51EC1B0 80083BE8 FE0E0208 */  j          .Llevel_60_80083BF8
/* 51EC1B4 80083BEC 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_60_80083BF0:
/* 51EC1B8 80083BF0 02006214 */  bne        $v1, $v0, .Llevel_60_80083BFC
/* 51EC1BC 80083BF4 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_60_80083BF8:
/* 51EC1C0 80083BF8 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_60_80083BFC:
/* 51EC1C4 80083BFC CB89010C */  jal        rand
/* 51EC1C8 80083C00 00000000 */   nop
/* 51EC1CC 80083C04 2000A426 */  addiu      $a0, $s5, 0x20
/* 51EC1D0 80083C08 07004230 */  andi       $v0, $v0, 0x7
/* 51EC1D4 80083C0C 80100200 */  sll        $v0, $v0, 2
/* 51EC1D8 80083C10 2000B027 */  addiu      $s0, $sp, 0x20
/* 51EC1DC 80083C14 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 51EC1E0 80083C18 21082200 */  addu       $at, $at, $v0
/* 51EC1E4 80083C1C A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 51EC1E8 80083C20 21280002 */  addu       $a1, $s0, $zero
/* 51EC1EC 80083C24 2400A0AF */  sw         $zero, 0x24($sp)
/* 51EC1F0 80083C28 2000A3AF */  sw         $v1, 0x20($sp)
/* 51EC1F4 80083C2C 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 51EC1F8 80083C30 21082200 */  addu       $at, $at, $v0
/* 51EC1FC 80083C34 A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 51EC200 80083C38 21300002 */  addu       $a2, $s0, $zero
/* 51EC204 80083C3C 125C000C */  jal        func_80017048
/* 51EC208 80083C40 2800A2AF */   sw        $v0, 0x28($sp)
/* 51EC20C 80083C44 CB89010C */  jal        rand
/* 51EC210 80083C48 00000000 */   nop
/* 51EC214 80083C4C 2000A38F */  lw         $v1, 0x20($sp)
/* 51EC218 80083C50 7F004230 */  andi       $v0, $v0, 0x7F
/* 51EC21C 80083C54 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 51EC220 80083C58 21186200 */  addu       $v1, $v1, $v0
/* 51EC224 80083C5C CB89010C */  jal        rand
/* 51EC228 80083C60 2000A3AF */   sw        $v1, 0x20($sp)
/* 51EC22C 80083C64 2400A38F */  lw         $v1, 0x24($sp)
/* 51EC230 80083C68 7F004230 */  andi       $v0, $v0, 0x7F
/* 51EC234 80083C6C C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 51EC238 80083C70 21186200 */  addu       $v1, $v1, $v0
/* 51EC23C 80083C74 CB89010C */  jal        rand
/* 51EC240 80083C78 2400A3AF */   sw        $v1, 0x24($sp)
/* 51EC244 80083C7C 0C006426 */  addiu      $a0, $s3, 0xC
/* 51EC248 80083C80 0C00A526 */  addiu      $a1, $s5, 0xC
/* 51EC24C 80083C84 21300002 */  addu       $a2, $s0, $zero
/* 51EC250 80083C88 2800A38F */  lw         $v1, 0x28($sp)
/* 51EC254 80083C8C 7F004230 */  andi       $v0, $v0, 0x7F
/* 51EC258 80083C90 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 51EC25C 80083C94 21186200 */  addu       $v1, $v1, $v0
/* 51EC260 80083C98 D65D000C */  jal        VecAdd
/* 51EC264 80083C9C 2800A3AF */   sw        $v1, 0x28($sp)
/* 51EC268 80083CA0 21202002 */  addu       $a0, $s1, $zero
/* 51EC26C 80083CA4 C05D000C */  jal        VecCopy
/* 51EC270 80083CA8 21280002 */   addu      $a1, $s0, $zero
/* 51EC274 80083CAC 21202002 */  addu       $a0, $s1, $zero
/* 51EC278 80083CB0 B25D000C */  jal        VecShiftRight
/* 51EC27C 80083CB4 02000524 */   addiu     $a1, $zero, 0x2
/* 51EC280 80083CB8 CB89010C */  jal        rand
/* 51EC284 80083CBC 00000000 */   nop
/* 51EC288 80083CC0 0000238E */  lw         $v1, 0x0($s1)
/* 51EC28C 80083CC4 FF004230 */  andi       $v0, $v0, 0xFF
/* 51EC290 80083CC8 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 51EC294 80083CCC 21186200 */  addu       $v1, $v1, $v0
/* 51EC298 80083CD0 CB89010C */  jal        rand
/* 51EC29C 80083CD4 000023AE */   sw        $v1, 0x0($s1)
/* 51EC2A0 80083CD8 0400238E */  lw         $v1, 0x4($s1)
/* 51EC2A4 80083CDC FF004230 */  andi       $v0, $v0, 0xFF
/* 51EC2A8 80083CE0 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 51EC2AC 80083CE4 21186200 */  addu       $v1, $v1, $v0
/* 51EC2B0 80083CE8 CB89010C */  jal        rand
/* 51EC2B4 80083CEC 040023AE */   sw        $v1, 0x4($s1)
/* 51EC2B8 80083CF0 0800238E */  lw         $v1, 0x8($s1)
/* 51EC2BC 80083CF4 FF004230 */  andi       $v0, $v0, 0xFF
/* 51EC2C0 80083CF8 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 51EC2C4 80083CFC 21186200 */  addu       $v1, $v1, $v0
/* 51EC2C8 80083D00 CB89010C */  jal        rand
/* 51EC2CC 80083D04 080023AE */   sw        $v1, 0x8($s1)
/* 51EC2D0 80083D08 CB89010C */  jal        rand
/* 51EC2D4 80083D0C 440062A2 */   sb        $v0, 0x44($s3)
/* 51EC2D8 80083D10 CB89010C */  jal        rand
/* 51EC2DC 80083D14 450062A2 */   sb        $v0, 0x45($s3)
/* 51EC2E0 80083D18 CB89010C */  jal        rand
/* 51EC2E4 80083D1C 460062A2 */   sb        $v0, 0x46($s3)
/* 51EC2E8 80083D20 0F004230 */  andi       $v0, $v0, 0xF
/* 51EC2EC 80083D24 CB89010C */  jal        rand
/* 51EC2F0 80083D28 100022A2 */   sb        $v0, 0x10($s1)
/* 51EC2F4 80083D2C 0F004230 */  andi       $v0, $v0, 0xF
/* 51EC2F8 80083D30 CB89010C */  jal        rand
/* 51EC2FC 80083D34 110022A2 */   sb        $v0, 0x11($s1)
/* 51EC300 80083D38 0F004230 */  andi       $v0, $v0, 0xF
/* 51EC304 80083D3C 120022A2 */  sb         $v0, 0x12($s1)
/* 51EC308 80083D40 1400A28E */  lw         $v0, 0x14($s5)
/* 51EC30C 80083D44 CB89010C */  jal        rand
/* 51EC310 80083D48 0C0022AE */   sw        $v0, 0xC($s1)
/* 51EC314 80083D4C 03004230 */  andi       $v0, $v0, 0x3
/* 51EC318 80083D50 10004224 */  addiu      $v0, $v0, 0x10
/* 51EC31C 80083D54 AB0F0208 */  j          .Llevel_60_80083EAC
/* 51EC320 80083D58 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_60_80083D5C:
/* 51EC324 80083D5C 0000708E */  lw         $s0, 0x0($s3)
/* 51EC328 80083D60 C8E9000C */  jal        func_8003A720
/* 51EC32C 80083D64 21206002 */   addu      $a0, $s3, $zero
/* 51EC330 80083D68 734A010C */  jal        func_800529CC
/* 51EC334 80083D6C 21206002 */   addu      $a0, $s3, $zero
/* 51EC338 80083D70 02000224 */  addiu      $v0, $zero, 0x2
/* 51EC33C 80083D74 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 51EC340 80083D78 40000224 */  addiu      $v0, $zero, 0x40
/* 51EC344 80083D7C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 51EC348 80083D80 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 51EC34C 80083D84 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 51EC350 80083D88 AB0F0208 */  j          .Llevel_60_80083EAC
/* 51EC354 80083D8C 000002AE */   sw        $v0, 0x0($s0)
.Llevel_60_80083D90:
/* 51EC358 80083D90 C8E9000C */  jal        func_8003A720
/* 51EC35C 80083D94 21206002 */   addu      $a0, $s3, $zero
/* 51EC360 80083D98 21206002 */  addu       $a0, $s3, $zero
/* 51EC364 80083D9C FF000224 */  addiu      $v0, $zero, 0xFF
/* 51EC368 80083DA0 500062A2 */  sb         $v0, 0x50($s3)
/* 51EC36C 80083DA4 CC010224 */  addiu      $v0, $zero, 0x1CC
/* 51EC370 80083DA8 0C0062AE */  sw         $v0, 0xC($s3)
/* 51EC374 80083DAC 28000224 */  addiu      $v0, $zero, 0x28
/* 51EC378 80083DB0 100062AE */  sw         $v0, 0x10($s3)
/* 51EC37C 80083DB4 00100224 */  addiu      $v0, $zero, 0x1000
/* 51EC380 80083DB8 734A010C */  jal        func_800529CC
/* 51EC384 80083DBC 140062AE */   sw        $v0, 0x14($s3)
/* 51EC388 80083DC0 20000224 */  addiu      $v0, $zero, 0x20
/* 51EC38C 80083DC4 470062A2 */  sb         $v0, 0x47($s3)
/* 51EC390 80083DC8 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 51EC394 80083DCC 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 51EC398 80083DD0 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 51EC39C 80083DD4 AB0F0208 */  j          .Llevel_60_80083EAC
/* 51EC3A0 80083DD8 4F0060A2 */   sb        $zero, 0x4F($s3)
.Llevel_60_80083DDC:
/* 51EC3A4 80083DDC C8E9000C */  jal        func_8003A720
/* 51EC3A8 80083DE0 21206002 */   addu      $a0, $s3, $zero
/* 51EC3AC 80083DE4 0300A012 */  beqz       $s5, .Llevel_60_80083DF4
/* 51EC3B0 80083DE8 0C006426 */   addiu     $a0, $s3, 0xC
/* 51EC3B4 80083DEC 7F0F0208 */  j          .Llevel_60_80083DFC
/* 51EC3B8 80083DF0 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_60_80083DF4:
/* 51EC3BC 80083DF4 0880053C */  lui        $a1, %hi(g_Spyro)
/* 51EC3C0 80083DF8 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_60_80083DFC:
/* 51EC3C4 80083DFC C05D000C */  jal        VecCopy
/* 51EC3C8 80083E00 00000000 */   nop
/* 51EC3CC 80083E04 0C006426 */  addiu      $a0, $s3, 0xC
/* 51EC3D0 80083E08 1400628E */  lw         $v0, 0x14($s3)
/* 51EC3D4 80083E0C 00080524 */  addiu      $a1, $zero, 0x800
/* 51EC3D8 80083E10 00024224 */  addiu      $v0, $v0, 0x200
/* 51EC3DC 80083E14 7B35010C */  jal        func_8004D5EC
/* 51EC3E0 80083E18 140062AE */   sw        $v0, 0x14($s3)
/* 51EC3E4 80083E1C 1400648E */  lw         $a0, 0x14($s3)
/* 51EC3E8 80083E20 21184000 */  addu       $v1, $v0, $zero
/* 51EC3EC 80083E24 23106400 */  subu       $v0, $v1, $a0
/* 51EC3F0 80083E28 02004104 */  bgez       $v0, .Llevel_60_80083E34
/* 51EC3F4 80083E2C 00000000 */   nop
/* 51EC3F8 80083E30 23100200 */  negu       $v0, $v0
.Llevel_60_80083E34:
/* 51EC3FC 80083E34 00084228 */  slti       $v0, $v0, 0x800
/* 51EC400 80083E38 03004010 */  beqz       $v0, .Llevel_60_80083E48
/* 51EC404 80083E3C 00FE8224 */   addiu     $v0, $a0, -0x200
/* 51EC408 80083E40 A90F0208 */  j          .Llevel_60_80083EA4
/* 51EC40C 80083E44 140063AE */   sw        $v1, 0x14($s3)
.Llevel_60_80083E48:
/* 51EC410 80083E48 A90F0208 */  j          .Llevel_60_80083EA4
/* 51EC414 80083E4C 140062AE */   sw        $v0, 0x14($s3)
.Llevel_60_80083E50:
/* 51EC418 80083E50 C8E9000C */  jal        func_8003A720
/* 51EC41C 80083E54 21206002 */   addu      $a0, $s3, $zero
/* 51EC420 80083E58 21206002 */  addu       $a0, $s3, $zero
/* 51EC424 80083E5C 20000224 */  addiu      $v0, $zero, 0x20
/* 51EC428 80083E60 500062A2 */  sb         $v0, 0x50($s3)
/* 51EC42C 80083E64 FF000224 */  addiu      $v0, $zero, 0xFF
/* 51EC430 80083E68 734A010C */  jal        func_800529CC
/* 51EC434 80083E6C 520062A2 */   sb        $v0, 0x52($s3)
/* 51EC438 80083E70 AC0F0208 */  j          .Llevel_60_80083EB0
/* 51EC43C 80083E74 21106002 */   addu      $v0, $s3, $zero
.Llevel_60_80083E78:
/* 51EC440 80083E78 C8E9000C */  jal        func_8003A720
/* 51EC444 80083E7C 21206002 */   addu      $a0, $s3, $zero
/* 51EC448 80083E80 0300A012 */  beqz       $s5, .Llevel_60_80083E90
/* 51EC44C 80083E84 0C00A526 */   addiu     $a1, $s5, 0xC
/* 51EC450 80083E88 A70F0208 */  j          .Llevel_60_80083E9C
/* 51EC454 80083E8C 0C006426 */   addiu     $a0, $s3, 0xC
.Llevel_60_80083E90:
/* 51EC458 80083E90 0C006426 */  addiu      $a0, $s3, 0xC
/* 51EC45C 80083E94 0880053C */  lui        $a1, %hi(g_Spyro)
/* 51EC460 80083E98 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_60_80083E9C:
/* 51EC464 80083E9C C05D000C */  jal        VecCopy
/* 51EC468 80083EA0 00000000 */   nop
.Llevel_60_80083EA4:
/* 51EC46C 80083EA4 AA49010C */  jal        func_800526A8
/* 51EC470 80083EA8 21206002 */   addu      $a0, $s3, $zero
.Llevel_60_80083EAC:
/* 51EC474 80083EAC 21106002 */  addu       $v0, $s3, $zero
.Llevel_60_80083EB0:
/* 51EC478 80083EB0 5000BF8F */  lw         $ra, 0x50($sp)
/* 51EC47C 80083EB4 4C00B58F */  lw         $s5, 0x4C($sp)
/* 51EC480 80083EB8 4800B48F */  lw         $s4, 0x48($sp)
/* 51EC484 80083EBC 4400B38F */  lw         $s3, 0x44($sp)
/* 51EC488 80083EC0 4000B28F */  lw         $s2, 0x40($sp)
/* 51EC48C 80083EC4 3C00B18F */  lw         $s1, 0x3C($sp)
/* 51EC490 80083EC8 3800B08F */  lw         $s0, 0x38($sp)
/* 51EC494 80083ECC 5800BD27 */  addiu      $sp, $sp, 0x58
/* 51EC498 80083ED0 0800E003 */  jr         $ra
/* 51EC49C 80083ED4 00000000 */   nop
.size func_level_60_80083568, . - func_level_60_80083568
