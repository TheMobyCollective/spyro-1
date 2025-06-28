.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_54_800836A8
/* 4DF8C70 800836A8 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 4DF8C74 800836AC 3800B0AF */  sw         $s0, 0x38($sp)
/* 4DF8C78 800836B0 21808000 */  addu       $s0, $a0, $zero
/* 4DF8C7C 800836B4 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 4DF8C80 800836B8 21A8A000 */  addu       $s5, $a1, $zero
/* 4DF8C84 800836BC 5000BFAF */  sw         $ra, 0x50($sp)
/* 4DF8C88 800836C0 4800B4AF */  sw         $s4, 0x48($sp)
/* 4DF8C8C 800836C4 4400B3AF */  sw         $s3, 0x44($sp)
/* 4DF8C90 800836C8 4000B2AF */  sw         $s2, 0x40($sp)
/* 4DF8C94 800836CC 3149010C */  jal        func_800524C4
/* 4DF8C98 800836D0 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 4DF8C9C 800836D4 21984000 */  addu       $s3, $v0, $zero
/* 4DF8CA0 800836D8 1400A012 */  beqz       $s5, .Llevel_54_8008372C
/* 4DF8CA4 800836DC 360070A6 */   sh        $s0, 0x36($s3)
/* 4DF8CA8 800836E0 0780043C */  lui        $a0, %hi(D_80075828)
/* 4DF8CAC 800836E4 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 4DF8CB0 800836E8 00000000 */  nop
/* 4DF8CB4 800836EC 2320A402 */  subu       $a0, $s5, $a0
/* 4DF8CB8 800836F0 40190400 */  sll        $v1, $a0, 5
/* 4DF8CBC 800836F4 23186400 */  subu       $v1, $v1, $a0
/* 4DF8CC0 800836F8 40190300 */  sll        $v1, $v1, 5
/* 4DF8CC4 800836FC 21186400 */  addu       $v1, $v1, $a0
/* 4DF8CC8 80083700 C0100300 */  sll        $v0, $v1, 3
/* 4DF8CCC 80083704 21186200 */  addu       $v1, $v1, $v0
/* 4DF8CD0 80083708 C0130300 */  sll        $v0, $v1, 15
/* 4DF8CD4 8008370C 23104300 */  subu       $v0, $v0, $v1
/* 4DF8CD8 80083710 80100200 */  sll        $v0, $v0, 2
/* 4DF8CDC 80083714 21104400 */  addu       $v0, $v0, $a0
/* 4DF8CE0 80083718 23100200 */  negu       $v0, $v0
/* 4DF8CE4 8008371C C3180200 */  sra        $v1, $v0, 3
/* 4DF8CE8 80083720 0001622C */  sltiu      $v0, $v1, 0x100
/* 4DF8CEC 80083724 03004014 */  bnez       $v0, .Llevel_54_80083734
/* 4DF8CF0 80083728 0201022A */   slti      $v0, $s0, 0x102
.Llevel_54_8008372C:
/* 4DF8CF4 8008372C 21180000 */  addu       $v1, $zero, $zero
/* 4DF8CF8 80083730 0201022A */  slti       $v0, $s0, 0x102
.Llevel_54_80083734:
/* 4DF8CFC 80083734 2E004010 */  beqz       $v0, .Llevel_54_800837F0
/* 4DF8D00 80083738 560063A2 */   sb        $v1, 0x56($s3)
/* 4DF8D04 8008373C FF00022A */  slti       $v0, $s0, 0xFF
/* 4DF8D08 80083740 12014010 */  beqz       $v0, .Llevel_54_80083B8C
/* 4DF8D0C 80083744 4600022A */   slti      $v0, $s0, 0x46
/* 4DF8D10 80083748 12004010 */  beqz       $v0, .Llevel_54_80083794
/* 4DF8D14 8008374C 4300022A */   slti      $v0, $s0, 0x43
/* 4DF8D18 80083750 0E014010 */  beqz       $v0, .Llevel_54_80083B8C
/* 4DF8D1C 80083754 0F000224 */   addiu     $v0, $zero, 0xF
/* 4DF8D20 80083758 4B000212 */  beq        $s0, $v0, .Llevel_54_80083888
/* 4DF8D24 8008375C 1000022A */   slti      $v0, $s0, 0x10
/* 4DF8D28 80083760 05004010 */  beqz       $v0, .Llevel_54_80083778
/* 4DF8D2C 80083764 0E000224 */   addiu     $v0, $zero, 0xE
/* 4DF8D30 80083768 90000212 */  beq        $s0, $v0, .Llevel_54_800839AC
/* 4DF8D34 8008376C 00000000 */   nop
/* 4DF8D38 80083770 F20F0208 */  j          .Llevel_54_80083FC8
/* 4DF8D3C 80083774 00000000 */   nop
.Llevel_54_80083778:
/* 4DF8D40 80083778 10000224 */  addiu      $v0, $zero, 0x10
/* 4DF8D44 8008377C 69000212 */  beq        $s0, $v0, .Llevel_54_80083924
/* 4DF8D48 80083780 22000224 */   addiu     $v0, $zero, 0x22
/* 4DF8D4C 80083784 7B000212 */  beq        $s0, $v0, .Llevel_54_80083974
/* 4DF8D50 80083788 00000000 */   nop
/* 4DF8D54 8008378C F20F0208 */  j          .Llevel_54_80083FC8
/* 4DF8D58 80083790 00000000 */   nop
.Llevel_54_80083794:
/* 4DF8D5C 80083794 5800022A */  slti       $v0, $s0, 0x58
/* 4DF8D60 80083798 07004010 */  beqz       $v0, .Llevel_54_800837B8
/* 4DF8D64 8008379C 5300022A */   slti      $v0, $s0, 0x53
/* 4DF8D68 800837A0 82004010 */  beqz       $v0, .Llevel_54_800839AC
/* 4DF8D6C 800837A4 4C000224 */   addiu     $v0, $zero, 0x4C
/* 4DF8D70 800837A8 FD010212 */  beq        $s0, $v0, .Llevel_54_80083FA0
/* 4DF8D74 800837AC 00000000 */   nop
/* 4DF8D78 800837B0 F20F0208 */  j          .Llevel_54_80083FC8
/* 4DF8D7C 800837B4 00000000 */   nop
.Llevel_54_800837B8:
/* 4DF8D80 800837B8 EA000224 */  addiu      $v0, $zero, 0xEA
/* 4DF8D84 800837BC E3000212 */  beq        $s0, $v0, .Llevel_54_80083B4C
/* 4DF8D88 800837C0 EB00022A */   slti      $v0, $s0, 0xEB
/* 4DF8D8C 800837C4 05004010 */  beqz       $v0, .Llevel_54_800837DC
/* 4DF8D90 800837C8 78000224 */   addiu     $v0, $zero, 0x78
/* 4DF8D94 800837CC CD000212 */  beq        $s0, $v0, .Llevel_54_80083B04
/* 4DF8D98 800837D0 00000000 */   nop
/* 4DF8D9C 800837D4 F20F0208 */  j          .Llevel_54_80083FC8
/* 4DF8DA0 800837D8 00000000 */   nop
.Llevel_54_800837DC:
/* 4DF8DA4 800837DC FB000224 */  addiu      $v0, $zero, 0xFB
/* 4DF8DA8 800837E0 55010212 */  beq        $s0, $v0, .Llevel_54_80083D38
/* 4DF8DAC 800837E4 00000000 */   nop
/* 4DF8DB0 800837E8 F20F0208 */  j          .Llevel_54_80083FC8
/* 4DF8DB4 800837EC 00000000 */   nop
.Llevel_54_800837F0:
/* 4DF8DB8 800837F0 47010224 */  addiu      $v0, $zero, 0x147
/* 4DF8DBC 800837F4 C0010212 */  beq        $s0, $v0, .Llevel_54_80083EF8
/* 4DF8DC0 800837F8 4801022A */   slti      $v0, $s0, 0x148
/* 4DF8DC4 800837FC 12004010 */  beqz       $v0, .Llevel_54_80083848
/* 4DF8DC8 80083800 15010224 */   addiu     $v0, $zero, 0x115
/* 4DF8DCC 80083804 BC010212 */  beq        $s0, $v0, .Llevel_54_80083EF8
/* 4DF8DD0 80083808 1601022A */   slti      $v0, $s0, 0x116
/* 4DF8DD4 8008380C 07004010 */  beqz       $v0, .Llevel_54_8008382C
/* 4DF8DD8 80083810 0E01022A */   slti      $v0, $s0, 0x10E
/* 4DF8DDC 80083814 EC014010 */  beqz       $v0, .Llevel_54_80083FC8
/* 4DF8DE0 80083818 0401022A */   slti      $v0, $s0, 0x104
/* 4DF8DE4 8008381C B6014010 */  beqz       $v0, .Llevel_54_80083EF8
/* 4DF8DE8 80083820 00000000 */   nop
/* 4DF8DEC 80083824 F20F0208 */  j          .Llevel_54_80083FC8
/* 4DF8DF0 80083828 00000000 */   nop
.Llevel_54_8008382C:
/* 4DF8DF4 8008382C 3801022A */  slti       $v0, $s0, 0x138
/* 4DF8DF8 80083830 E5014010 */  beqz       $v0, .Llevel_54_80083FC8
/* 4DF8DFC 80083834 3501022A */   slti      $v0, $s0, 0x135
/* 4DF8E00 80083838 D4004010 */  beqz       $v0, .Llevel_54_80083B8C
/* 4DF8E04 8008383C 00000000 */   nop
/* 4DF8E08 80083840 F20F0208 */  j          .Llevel_54_80083FC8
/* 4DF8E0C 80083844 00000000 */   nop
.Llevel_54_80083848:
/* 4DF8E10 80083848 C401022A */  slti       $v0, $s0, 0x1C4
/* 4DF8E14 8008384C 07004010 */  beqz       $v0, .Llevel_54_8008386C
/* 4DF8E18 80083850 AA01022A */   slti      $v0, $s0, 0x1AA
/* 4DF8E1C 80083854 D2014010 */  beqz       $v0, .Llevel_54_80083FA0
/* 4DF8E20 80083858 A701022A */   slti      $v0, $s0, 0x1A7
/* 4DF8E24 8008385C CB004010 */  beqz       $v0, .Llevel_54_80083B8C
/* 4DF8E28 80083860 00000000 */   nop
/* 4DF8E2C 80083864 F20F0208 */  j          .Llevel_54_80083FC8
/* 4DF8E30 80083868 00000000 */   nop
.Llevel_54_8008386C:
/* 4DF8E34 8008386C FD01022A */  slti       $v0, $s0, 0x1FD
/* 4DF8E38 80083870 D5014010 */  beqz       $v0, .Llevel_54_80083FC8
/* 4DF8E3C 80083874 FB01022A */   slti      $v0, $s0, 0x1FB
/* 4DF8E40 80083878 AC014010 */  beqz       $v0, .Llevel_54_80083F2C
/* 4DF8E44 8008387C 00000000 */   nop
/* 4DF8E48 80083880 F20F0208 */  j          .Llevel_54_80083FC8
/* 4DF8E4C 80083884 00000000 */   nop
.Llevel_54_80083888:
/* 4DF8E50 80083888 0000708E */  lw         $s0, 0x0($s3)
/* 4DF8E54 8008388C C8E9000C */  jal        func_8003A720
/* 4DF8E58 80083890 21206002 */   addu      $a0, $s3, $zero
/* 4DF8E5C 80083894 8C000224 */  addiu      $v0, $zero, 0x8C
/* 4DF8E60 80083898 080002AE */  sw         $v0, 0x8($s0)
/* 4DF8E64 8008389C 03000224 */  addiu      $v0, $zero, 0x3
/* 4DF8E68 800838A0 100002A2 */  sb         $v0, 0x10($s0)
/* 4DF8E6C 800838A4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 4DF8E70 800838A8 140002A2 */  sb         $v0, 0x14($s0)
/* 4DF8E74 800838AC 02000224 */  addiu      $v0, $zero, 0x2
/* 4DF8E78 800838B0 000000AE */  sw         $zero, 0x0($s0)
/* 4DF8E7C 800838B4 040000AE */  sw         $zero, 0x4($s0)
/* 4DF8E80 800838B8 0E0000A2 */  sb         $zero, 0xE($s0)
/* 4DF8E84 800838BC 0F0000A2 */  sb         $zero, 0xF($s0)
/* 4DF8E88 800838C0 110000A2 */  sb         $zero, 0x11($s0)
/* 4DF8E8C 800838C4 120000A2 */  sb         $zero, 0x12($s0)
/* 4DF8E90 800838C8 130000A2 */  sb         $zero, 0x13($s0)
/* 4DF8E94 800838CC 490062A2 */  sb         $v0, 0x49($s3)
/* 4DF8E98 800838D0 18000224 */  addiu      $v0, $zero, 0x18
/* 4DF8E9C 800838D4 500062A2 */  sb         $v0, 0x50($s3)
/* 4DF8EA0 800838D8 10000224 */  addiu      $v0, $zero, 0x10
/* 4DF8EA4 800838DC 520062A2 */  sb         $v0, 0x52($s3)
/* 4DF8EA8 800838E0 20000224 */  addiu      $v0, $zero, 0x20
/* 4DF8EAC 800838E4 440062A2 */  sb         $v0, 0x44($s3)
/* 4DF8EB0 800838E8 450060A2 */  sb         $zero, 0x45($s3)
/* 4DF8EB4 800838EC 0400A012 */  beqz       $s5, .Llevel_54_80083900
/* 4DF8EB8 800838F0 460060A2 */   sb        $zero, 0x46($s3)
/* 4DF8EBC 800838F4 0C006426 */  addiu      $a0, $s3, 0xC
/* 4DF8EC0 800838F8 C05D000C */  jal        VecCopy
/* 4DF8EC4 800838FC 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_54_80083900:
/* 4DF8EC8 80083900 AA49010C */  jal        func_800526A8
/* 4DF8ECC 80083904 21206002 */   addu      $a0, $s3, $zero
/* 4DF8ED0 80083908 4B006292 */  lbu        $v0, 0x4B($s3)
/* 4DF8ED4 8008390C 01000324 */  addiu      $v1, $zero, 0x1
/* 4DF8ED8 80083910 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 4DF8EDC 80083914 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 4DF8EE0 80083918 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 4DF8EE4 8008391C 4B0F0208 */  j          .Llevel_54_80083D2C
/* 4DF8EE8 80083920 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_54_80083924:
/* 4DF8EEC 80083924 0000718E */  lw         $s1, 0x0($s3)
/* 4DF8EF0 80083928 C8E9000C */  jal        func_8003A720
/* 4DF8EF4 8008392C 21206002 */   addu      $a0, $s3, $zero
/* 4DF8EF8 80083930 AA49010C */  jal        func_800526A8
/* 4DF8EFC 80083934 21206002 */   addu      $a0, $s3, $zero
/* 4DF8F00 80083938 0C007026 */  addiu      $s0, $s3, 0xC
/* 4DF8F04 8008393C 21200002 */  addu       $a0, $s0, $zero
/* 4DF8F08 80083940 C05D000C */  jal        VecCopy
/* 4DF8F0C 80083944 0C00A526 */   addiu     $a1, $s5, 0xC
/* 4DF8F10 80083948 21280002 */  addu       $a1, $s0, $zero
/* 4DF8F14 8008394C 1400628E */  lw         $v0, 0x14($s3)
/* 4DF8F18 80083950 04002426 */  addiu      $a0, $s1, 0x4
/* 4DF8F1C 80083954 00024224 */  addiu      $v0, $v0, 0x200
/* 4DF8F20 80083958 C05D000C */  jal        VecCopy
/* 4DF8F24 8008395C 140062AE */   sw        $v0, 0x14($s3)
/* 4DF8F28 80083960 08070224 */  addiu      $v0, $zero, 0x708
/* 4DF8F2C 80083964 130020A2 */  sb         $zero, 0x13($s1)
/* 4DF8F30 80083968 120020A2 */  sb         $zero, 0x12($s1)
/* 4DF8F34 8008396C FF0F0208 */  j          .Llevel_54_80083FFC
/* 4DF8F38 80083970 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_54_80083974:
/* 4DF8F3C 80083974 C8E9000C */  jal        func_8003A720
/* 4DF8F40 80083978 21206002 */   addu      $a0, $s3, $zero
/* 4DF8F44 8008397C 20000224 */  addiu      $v0, $zero, 0x20
/* 4DF8F48 80083980 500062A2 */  sb         $v0, 0x50($s3)
/* 4DF8F4C 80083984 FF000224 */  addiu      $v0, $zero, 0xFF
/* 4DF8F50 80083988 0400A012 */  beqz       $s5, .Llevel_54_8008399C
/* 4DF8F54 8008398C 520062A2 */   sb        $v0, 0x52($s3)
/* 4DF8F58 80083990 0C006426 */  addiu      $a0, $s3, 0xC
/* 4DF8F5C 80083994 C05D000C */  jal        VecCopy
/* 4DF8F60 80083998 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_54_8008399C:
/* 4DF8F64 8008399C 734A010C */  jal        func_800529CC
/* 4DF8F68 800839A0 21206002 */   addu      $a0, $s3, $zero
/* 4DF8F6C 800839A4 00100208 */  j          .Llevel_54_80084000
/* 4DF8F70 800839A8 21106002 */   addu      $v0, $s3, $zero
.Llevel_54_800839AC:
/* 4DF8F74 800839AC 0000718E */  lw         $s1, 0x0($s3)
/* 4DF8F78 800839B0 C8E9000C */  jal        func_8003A720
/* 4DF8F7C 800839B4 21206002 */   addu      $a0, $s3, $zero
/* 4DF8F80 800839B8 8C000224 */  addiu      $v0, $zero, 0x8C
/* 4DF8F84 800839BC 000020AE */  sw         $zero, 0x0($s1)
/* 4DF8F88 800839C0 040020AE */  sw         $zero, 0x4($s1)
/* 4DF8F8C 800839C4 080022AE */  sw         $v0, 0x8($s1)
/* 4DF8F90 800839C8 0E0020A2 */  sb         $zero, 0xE($s1)
/* 4DF8F94 800839CC 0F0020A2 */  sb         $zero, 0xF($s1)
/* 4DF8F98 800839D0 110020A2 */  sb         $zero, 0x11($s1)
/* 4DF8F9C 800839D4 120020A2 */  sb         $zero, 0x12($s1)
/* 4DF8FA0 800839D8 130020A2 */  sb         $zero, 0x13($s1)
/* 4DF8FA4 800839DC 3600A386 */  lh         $v1, 0x36($s5)
/* 4DF8FA8 800839E0 0D000224 */  addiu      $v0, $zero, 0xD
/* 4DF8FAC 800839E4 02006214 */  bne        $v1, $v0, .Llevel_54_800839F0
/* 4DF8FB0 800839E8 03000224 */   addiu     $v0, $zero, 0x3
/* 4DF8FB4 800839EC 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_54_800839F0:
/* 4DF8FB8 800839F0 100022A2 */  sb         $v0, 0x10($s1)
/* 4DF8FBC 800839F4 0C007026 */  addiu      $s0, $s3, 0xC
/* 4DF8FC0 800839F8 21200002 */  addu       $a0, $s0, $zero
/* 4DF8FC4 800839FC 0C00A526 */  addiu      $a1, $s5, 0xC
/* 4DF8FC8 80083A00 FF000224 */  addiu      $v0, $zero, 0xFF
/* 4DF8FCC 80083A04 140022A2 */  sb         $v0, 0x14($s1)
/* 4DF8FD0 80083A08 02001124 */  addiu      $s1, $zero, 0x2
/* 4DF8FD4 80083A0C 18000224 */  addiu      $v0, $zero, 0x18
/* 4DF8FD8 80083A10 500062A2 */  sb         $v0, 0x50($s3)
/* 4DF8FDC 80083A14 40000224 */  addiu      $v0, $zero, 0x40
/* 4DF8FE0 80083A18 520062A2 */  sb         $v0, 0x52($s3)
/* 4DF8FE4 80083A1C 20000224 */  addiu      $v0, $zero, 0x20
/* 4DF8FE8 80083A20 490071A2 */  sb         $s1, 0x49($s3)
/* 4DF8FEC 80083A24 440062A2 */  sb         $v0, 0x44($s3)
/* 4DF8FF0 80083A28 450060A2 */  sb         $zero, 0x45($s3)
/* 4DF8FF4 80083A2C C05D000C */  jal        VecCopy
/* 4DF8FF8 80083A30 460060A2 */   sb        $zero, 0x46($s3)
/* 4DF8FFC 80083A34 734A010C */  jal        func_800529CC
/* 4DF9000 80083A38 21206002 */   addu      $a0, $s3, $zero
/* 4DF9004 80083A3C 1000A427 */  addiu      $a0, $sp, 0x10
/* 4DF9008 80083A40 21280002 */  addu       $a1, $s0, $zero
/* 4DF900C 80083A44 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 4DF9010 80083A48 C05D000C */  jal        VecCopy
/* 4DF9014 80083A4C 1C0062AE */   sw        $v0, 0x1C($s3)
/* 4DF9018 80083A50 1000A427 */  addiu      $a0, $sp, 0x10
/* 4DF901C 80083A54 1800A28F */  lw         $v0, 0x18($sp)
/* 4DF9020 80083A58 0100053C */  lui        $a1, (0x10000 >> 16)
/* 4DF9024 80083A5C 00044224 */  addiu      $v0, $v0, 0x400
/* 4DF9028 80083A60 7B35010C */  jal        func_8004D5EC
/* 4DF902C 80083A64 1800A2AF */   sw        $v0, 0x18($sp)
/* 4DF9030 80083A68 F44C010C */  jal        func_800533D0
/* 4DF9034 80083A6C 21206002 */   addu      $a0, $s3, $zero
/* 4DF9038 80083A70 36006386 */  lh         $v1, 0x36($s3)
/* 4DF903C 80083A74 0E000224 */  addiu      $v0, $zero, 0xE
/* 4DF9040 80083A78 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 4DF9044 80083A7C 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 4DF9048 80083A80 03006214 */  bne        $v1, $v0, .Llevel_54_80083A90
/* 4DF904C 80083A84 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 4DF9050 80083A88 0C000224 */  addiu      $v0, $zero, 0xC
/* 4DF9054 80083A8C 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_54_80083A90:
/* 4DF9058 80083A90 36006386 */  lh         $v1, 0x36($s3)
/* 4DF905C 80083A94 53000224 */  addiu      $v0, $zero, 0x53
/* 4DF9060 80083A98 05006214 */  bne        $v1, $v0, .Llevel_54_80083AB0
/* 4DF9064 80083A9C 54000224 */   addiu     $v0, $zero, 0x54
/* 4DF9068 80083AA0 01000224 */  addiu      $v0, $zero, 0x1
/* 4DF906C 80083AA4 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 4DF9070 80083AA8 36006386 */  lh         $v1, 0x36($s3)
/* 4DF9074 80083AAC 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_54_80083AB0:
/* 4DF9078 80083AB0 02006214 */  bne        $v1, $v0, .Llevel_54_80083ABC
/* 4DF907C 80083AB4 00000000 */   nop
/* 4DF9080 80083AB8 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_54_80083ABC:
/* 4DF9084 80083ABC 36006386 */  lh         $v1, 0x36($s3)
/* 4DF9088 80083AC0 55000224 */  addiu      $v0, $zero, 0x55
/* 4DF908C 80083AC4 05006214 */  bne        $v1, $v0, .Llevel_54_80083ADC
/* 4DF9090 80083AC8 56000224 */   addiu     $v0, $zero, 0x56
/* 4DF9094 80083ACC 03000224 */  addiu      $v0, $zero, 0x3
/* 4DF9098 80083AD0 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 4DF909C 80083AD4 36006386 */  lh         $v1, 0x36($s3)
/* 4DF90A0 80083AD8 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_54_80083ADC:
/* 4DF90A4 80083ADC 02006214 */  bne        $v1, $v0, .Llevel_54_80083AE8
/* 4DF90A8 80083AE0 04000224 */   addiu     $v0, $zero, 0x4
/* 4DF90AC 80083AE4 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_54_80083AE8:
/* 4DF90B0 80083AE8 36006386 */  lh         $v1, 0x36($s3)
/* 4DF90B4 80083AEC 57000224 */  addiu      $v0, $zero, 0x57
/* 4DF90B8 80083AF0 43016214 */  bne        $v1, $v0, .Llevel_54_80084000
/* 4DF90BC 80083AF4 21106002 */   addu      $v0, $s3, $zero
/* 4DF90C0 80083AF8 05000224 */  addiu      $v0, $zero, 0x5
/* 4DF90C4 80083AFC FF0F0208 */  j          .Llevel_54_80083FFC
/* 4DF90C8 80083B00 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_54_80083B04:
/* 4DF90CC 80083B04 0000708E */  lw         $s0, 0x0($s3)
/* 4DF90D0 80083B08 C8E9000C */  jal        func_8003A720
/* 4DF90D4 80083B0C 21206002 */   addu      $a0, $s3, $zero
/* 4DF90D8 80083B10 AA49010C */  jal        func_800526A8
/* 4DF90DC 80083B14 21206002 */   addu      $a0, $s3, $zero
/* 4DF90E0 80083B18 490060A2 */  sb         $zero, 0x49($s3)
/* 4DF90E4 80083B1C 000000AE */  sw         $zero, 0x0($s0)
/* 4DF90E8 80083B20 080000A6 */  sh         $zero, 0x8($s0)
/* 4DF90EC 80083B24 060000A6 */  sh         $zero, 0x6($s0)
/* 4DF90F0 80083B28 040000A6 */  sh         $zero, 0x4($s0)
/* 4DF90F4 80083B2C 0C0000AE */  sw         $zero, 0xC($s0)
/* 4DF90F8 80083B30 3201A012 */  beqz       $s5, .Llevel_54_80083FFC
/* 4DF90FC 80083B34 100000AE */   sw        $zero, 0x10($s0)
/* 4DF9100 80083B38 0C006426 */  addiu      $a0, $s3, 0xC
/* 4DF9104 80083B3C C05D000C */  jal        VecCopy
/* 4DF9108 80083B40 0C00A526 */   addiu     $a1, $s5, 0xC
/* 4DF910C 80083B44 00100208 */  j          .Llevel_54_80084000
/* 4DF9110 80083B48 21106002 */   addu      $v0, $s3, $zero
.Llevel_54_80083B4C:
/* 4DF9114 80083B4C C8E9000C */  jal        func_8003A720
/* 4DF9118 80083B50 21206002 */   addu      $a0, $s3, $zero
/* 4DF911C 80083B54 0880053C */  lui        $a1, %hi(g_Spyro + 0x17C)
/* 4DF9120 80083B58 D48BA524 */  addiu      $a1, $a1, %lo(g_Spyro + 0x17C)
/* 4DF9124 80083B5C C05D000C */  jal        VecCopy
/* 4DF9128 80083B60 0C006426 */   addiu     $a0, $s3, 0xC
/* 4DF912C 80083B64 0880043C */  lui        $a0, %hi(g_Spyro + 0x188)
/* 4DF9130 80083B68 E08B848C */  lw         $a0, %lo(g_Spyro + 0x188)($a0)
/* 4DF9134 80083B6C 0880053C */  lui        $a1, %hi(g_Spyro + 0x18C)
/* 4DF9138 80083B70 E48BA58C */  lw         $a1, %lo(g_Spyro + 0x18C)($a1)
/* 4DF913C 80083B74 AD5A000C */  jal        Atan2
/* 4DF9140 80083B78 21300000 */   addu      $a2, $zero, $zero
/* 4DF9144 80083B7C 21206002 */  addu       $a0, $s3, $zero
/* 4DF9148 80083B80 40004224 */  addiu      $v0, $v0, 0x40
/* 4DF914C 80083B84 FD0F0208 */  j          .Llevel_54_80083FF4
/* 4DF9150 80083B88 460062A2 */   sb        $v0, 0x46($s3)
.Llevel_54_80083B8C:
/* 4DF9154 80083B8C 0000748E */  lw         $s4, 0x0($s3)
/* 4DF9158 80083B90 C8E9000C */  jal        func_8003A720
/* 4DF915C 80083B94 21206002 */   addu      $a0, $s3, $zero
/* 4DF9160 80083B98 0C006426 */  addiu      $a0, $s3, 0xC
/* 4DF9164 80083B9C 0C00A526 */  addiu      $a1, $s5, 0xC
/* 4DF9168 80083BA0 20000224 */  addiu      $v0, $zero, 0x20
/* 4DF916C 80083BA4 C05D000C */  jal        VecCopy
/* 4DF9170 80083BA8 500062A2 */   sb        $v0, 0x50($s3)
/* 4DF9174 80083BAC AA49010C */  jal        func_800526A8
/* 4DF9178 80083BB0 21206002 */   addu      $a0, $s3, $zero
/* 4DF917C 80083BB4 CB89010C */  jal        rand
/* 4DF9180 80083BB8 00000000 */   nop
/* 4DF9184 80083BBC CB89010C */  jal        rand
/* 4DF9188 80083BC0 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 4DF918C 80083BC4 FF075130 */  andi       $s1, $v0, 0x7FF
/* 4DF9190 80083BC8 2C5B000C */  jal        Cos
/* 4DF9194 80083BCC 21202002 */   addu      $a0, $s1, $zero
/* 4DF9198 80083BD0 21204002 */  addu       $a0, $s2, $zero
/* 4DF919C 80083BD4 2C5B000C */  jal        Cos
/* 4DF91A0 80083BD8 21804000 */   addu      $s0, $v0, $zero
/* 4DF91A4 80083BDC 43811000 */  sra        $s0, $s0, 5
/* 4DF91A8 80083BE0 18000202 */  mult       $s0, $v0
/* 4DF91AC 80083BE4 21202002 */  addu       $a0, $s1, $zero
/* 4DF91B0 80083BE8 12380000 */  mflo       $a3
/* 4DF91B4 80083BEC 03130700 */  sra        $v0, $a3, 12
/* 4DF91B8 80083BF0 2C5B000C */  jal        Cos
/* 4DF91BC 80083BF4 000082A6 */   sh        $v0, 0x0($s4)
/* 4DF91C0 80083BF8 21204002 */  addu       $a0, $s2, $zero
/* 4DF91C4 80083BFC 165B000C */  jal        Sin
/* 4DF91C8 80083C00 21804000 */   addu      $s0, $v0, $zero
/* 4DF91CC 80083C04 43811000 */  sra        $s0, $s0, 5
/* 4DF91D0 80083C08 18000202 */  mult       $s0, $v0
/* 4DF91D4 80083C0C 21202002 */  addu       $a0, $s1, $zero
/* 4DF91D8 80083C10 12380000 */  mflo       $a3
/* 4DF91DC 80083C14 03130700 */  sra        $v0, $a3, 12
/* 4DF91E0 80083C18 165B000C */  jal        Sin
/* 4DF91E4 80083C1C 020082A6 */   sh        $v0, 0x2($s4)
/* 4DF91E8 80083C20 43110200 */  sra        $v0, $v0, 5
/* 4DF91EC 80083C24 040082A6 */  sh         $v0, 0x4($s4)
/* 4DF91F0 80083C28 1800A28E */  lw         $v0, 0x18($s5)
/* 4DF91F4 80083C2C 0200033C */  lui        $v1, (0x20000 >> 16)
/* 4DF91F8 80083C30 24104300 */  and        $v0, $v0, $v1
/* 4DF91FC 80083C34 13004010 */  beqz       $v0, .Llevel_54_80083C84
/* 4DF9200 80083C38 00000000 */   nop
/* 4DF9204 80083C3C 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 4DF9208 80083C40 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 4DF920C 80083C44 00008396 */  lhu        $v1, 0x0($s4)
/* 4DF9210 80083C48 83110200 */  sra        $v0, $v0, 6
/* 4DF9214 80083C4C 21186200 */  addu       $v1, $v1, $v0
/* 4DF9218 80083C50 000083A6 */  sh         $v1, 0x0($s4)
/* 4DF921C 80083C54 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 4DF9220 80083C58 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 4DF9224 80083C5C 02008396 */  lhu        $v1, 0x2($s4)
/* 4DF9228 80083C60 83110200 */  sra        $v0, $v0, 6
/* 4DF922C 80083C64 21186200 */  addu       $v1, $v1, $v0
/* 4DF9230 80083C68 020083A6 */  sh         $v1, 0x2($s4)
/* 4DF9234 80083C6C 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 4DF9238 80083C70 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 4DF923C 80083C74 04008396 */  lhu        $v1, 0x4($s4)
/* 4DF9240 80083C78 83110200 */  sra        $v0, $v0, 6
/* 4DF9244 80083C7C 21186200 */  addu       $v1, $v1, $v0
/* 4DF9248 80083C80 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_54_80083C84:
/* 4DF924C 80083C84 00008286 */  lh         $v0, 0x0($s4)
/* 4DF9250 80083C88 0C00638E */  lw         $v1, 0xC($s3)
/* 4DF9254 80083C8C 80100200 */  sll        $v0, $v0, 2
/* 4DF9258 80083C90 21186200 */  addu       $v1, $v1, $v0
/* 4DF925C 80083C94 0C0063AE */  sw         $v1, 0xC($s3)
/* 4DF9260 80083C98 02008286 */  lh         $v0, 0x2($s4)
/* 4DF9264 80083C9C 1000638E */  lw         $v1, 0x10($s3)
/* 4DF9268 80083CA0 80100200 */  sll        $v0, $v0, 2
/* 4DF926C 80083CA4 21186200 */  addu       $v1, $v1, $v0
/* 4DF9270 80083CA8 100063AE */  sw         $v1, 0x10($s3)
/* 4DF9274 80083CAC 04008286 */  lh         $v0, 0x4($s4)
/* 4DF9278 80083CB0 1400638E */  lw         $v1, 0x14($s3)
/* 4DF927C 80083CB4 80100200 */  sll        $v0, $v0, 2
/* 4DF9280 80083CB8 21186200 */  addu       $v1, $v1, $v0
/* 4DF9284 80083CBC CB89010C */  jal        rand
/* 4DF9288 80083CC0 140063AE */   sw        $v1, 0x14($s3)
/* 4DF928C 80083CC4 0F004230 */  andi       $v0, $v0, 0xF
/* 4DF9290 80083CC8 CB89010C */  jal        rand
/* 4DF9294 80083CCC 060082A6 */   sh        $v0, 0x6($s4)
/* 4DF9298 80083CD0 0F004230 */  andi       $v0, $v0, 0xF
/* 4DF929C 80083CD4 CB89010C */  jal        rand
/* 4DF92A0 80083CD8 080082A6 */   sh        $v0, 0x8($s4)
/* 4DF92A4 80083CDC 0F004230 */  andi       $v0, $v0, 0xF
/* 4DF92A8 80083CE0 0A0082A6 */  sh         $v0, 0xA($s4)
/* 4DF92AC 80083CE4 1400A28E */  lw         $v0, 0x14($s5)
/* 4DF92B0 80083CE8 00000000 */  nop
/* 4DF92B4 80083CEC C0FF4224 */  addiu      $v0, $v0, -0x40
/* 4DF92B8 80083CF0 CB89010C */  jal        rand
/* 4DF92BC 80083CF4 100082AE */   sw        $v0, 0x10($s4)
/* 4DF92C0 80083CF8 0F004230 */  andi       $v0, $v0, 0xF
/* 4DF92C4 80083CFC 40000324 */  addiu      $v1, $zero, 0x40
/* 4DF92C8 80083D00 23186200 */  subu       $v1, $v1, $v0
/* 4DF92CC 80083D04 0C0083AE */  sw         $v1, 0xC($s4)
/* 4DF92D0 80083D08 36006296 */  lhu        $v0, 0x36($s3)
/* 4DF92D4 80083D0C 00000000 */  nop
/* 4DF92D8 80083D10 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 4DF92DC 80083D14 0300422C */  sltiu      $v0, $v0, 0x3
/* 4DF92E0 80083D18 B8004010 */  beqz       $v0, .Llevel_54_80083FFC
/* 4DF92E4 80083D1C A100033C */   lui       $v1, (0xA18618 >> 16)
/* 4DF92E8 80083D20 4B006292 */  lbu        $v0, 0x4B($s3)
/* 4DF92EC 80083D24 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 4DF92F0 80083D28 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_54_80083D2C:
/* 4DF92F4 80083D2C 80004234 */  ori        $v0, $v0, 0x80
/* 4DF92F8 80083D30 FF0F0208 */  j          .Llevel_54_80083FFC
/* 4DF92FC 80083D34 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_54_80083D38:
/* 4DF9300 80083D38 0000718E */  lw         $s1, 0x0($s3)
/* 4DF9304 80083D3C C8E9000C */  jal        func_8003A720
/* 4DF9308 80083D40 21206002 */   addu      $a0, $s3, $zero
/* 4DF930C 80083D44 21206002 */  addu       $a0, $s3, $zero
/* 4DF9310 80083D48 20000224 */  addiu      $v0, $zero, 0x20
/* 4DF9314 80083D4C 500062A2 */  sb         $v0, 0x50($s3)
/* 4DF9318 80083D50 FF000224 */  addiu      $v0, $zero, 0xFF
/* 4DF931C 80083D54 734A010C */  jal        func_800529CC
/* 4DF9320 80083D58 520062A2 */   sb        $v0, 0x52($s3)
/* 4DF9324 80083D5C 0E000224 */  addiu      $v0, $zero, 0xE
/* 4DF9328 80083D60 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 4DF932C 80083D64 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 4DF9330 80083D68 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 4DF9334 80083D6C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 4DF9338 80083D70 0780033C */  lui        $v1, %hi(D_80077058)
/* 4DF933C 80083D74 5870638C */  lw         $v1, %lo(D_80077058)($v1)
/* 4DF9340 80083D78 03000224 */  addiu      $v0, $zero, 0x3
/* 4DF9344 80083D7C 03006214 */  bne        $v1, $v0, .Llevel_54_80083D8C
/* 4DF9348 80083D80 01000224 */   addiu     $v0, $zero, 0x1
/* 4DF934C 80083D84 650F0208 */  j          .Llevel_54_80083D94
/* 4DF9350 80083D88 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_54_80083D8C:
/* 4DF9354 80083D8C 02006214 */  bne        $v1, $v0, .Llevel_54_80083D98
/* 4DF9358 80083D90 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_54_80083D94:
/* 4DF935C 80083D94 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_54_80083D98:
/* 4DF9360 80083D98 CB89010C */  jal        rand
/* 4DF9364 80083D9C 00000000 */   nop
/* 4DF9368 80083DA0 2000A426 */  addiu      $a0, $s5, 0x20
/* 4DF936C 80083DA4 07004230 */  andi       $v0, $v0, 0x7
/* 4DF9370 80083DA8 80100200 */  sll        $v0, $v0, 2
/* 4DF9374 80083DAC 2000B027 */  addiu      $s0, $sp, 0x20
/* 4DF9378 80083DB0 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 4DF937C 80083DB4 21082200 */  addu       $at, $at, $v0
/* 4DF9380 80083DB8 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 4DF9384 80083DBC 21280002 */  addu       $a1, $s0, $zero
/* 4DF9388 80083DC0 2400A0AF */  sw         $zero, 0x24($sp)
/* 4DF938C 80083DC4 2000A3AF */  sw         $v1, 0x20($sp)
/* 4DF9390 80083DC8 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 4DF9394 80083DCC 21082200 */  addu       $at, $at, $v0
/* 4DF9398 80083DD0 A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 4DF939C 80083DD4 21300002 */  addu       $a2, $s0, $zero
/* 4DF93A0 80083DD8 125C000C */  jal        VecRotateByMatrix
/* 4DF93A4 80083DDC 2800A2AF */   sw        $v0, 0x28($sp)
/* 4DF93A8 80083DE0 CB89010C */  jal        rand
/* 4DF93AC 80083DE4 00000000 */   nop
/* 4DF93B0 80083DE8 2000A38F */  lw         $v1, 0x20($sp)
/* 4DF93B4 80083DEC 7F004230 */  andi       $v0, $v0, 0x7F
/* 4DF93B8 80083DF0 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 4DF93BC 80083DF4 21186200 */  addu       $v1, $v1, $v0
/* 4DF93C0 80083DF8 CB89010C */  jal        rand
/* 4DF93C4 80083DFC 2000A3AF */   sw        $v1, 0x20($sp)
/* 4DF93C8 80083E00 2400A38F */  lw         $v1, 0x24($sp)
/* 4DF93CC 80083E04 7F004230 */  andi       $v0, $v0, 0x7F
/* 4DF93D0 80083E08 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 4DF93D4 80083E0C 21186200 */  addu       $v1, $v1, $v0
/* 4DF93D8 80083E10 CB89010C */  jal        rand
/* 4DF93DC 80083E14 2400A3AF */   sw        $v1, 0x24($sp)
/* 4DF93E0 80083E18 0C006426 */  addiu      $a0, $s3, 0xC
/* 4DF93E4 80083E1C 0C00A526 */  addiu      $a1, $s5, 0xC
/* 4DF93E8 80083E20 21300002 */  addu       $a2, $s0, $zero
/* 4DF93EC 80083E24 2800A38F */  lw         $v1, 0x28($sp)
/* 4DF93F0 80083E28 7F004230 */  andi       $v0, $v0, 0x7F
/* 4DF93F4 80083E2C C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 4DF93F8 80083E30 21186200 */  addu       $v1, $v1, $v0
/* 4DF93FC 80083E34 D65D000C */  jal        VecAdd
/* 4DF9400 80083E38 2800A3AF */   sw        $v1, 0x28($sp)
/* 4DF9404 80083E3C 21202002 */  addu       $a0, $s1, $zero
/* 4DF9408 80083E40 C05D000C */  jal        VecCopy
/* 4DF940C 80083E44 21280002 */   addu      $a1, $s0, $zero
/* 4DF9410 80083E48 21202002 */  addu       $a0, $s1, $zero
/* 4DF9414 80083E4C B25D000C */  jal        VecShiftRight
/* 4DF9418 80083E50 02000524 */   addiu     $a1, $zero, 0x2
/* 4DF941C 80083E54 CB89010C */  jal        rand
/* 4DF9420 80083E58 00000000 */   nop
/* 4DF9424 80083E5C 0000238E */  lw         $v1, 0x0($s1)
/* 4DF9428 80083E60 FF004230 */  andi       $v0, $v0, 0xFF
/* 4DF942C 80083E64 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 4DF9430 80083E68 21186200 */  addu       $v1, $v1, $v0
/* 4DF9434 80083E6C CB89010C */  jal        rand
/* 4DF9438 80083E70 000023AE */   sw        $v1, 0x0($s1)
/* 4DF943C 80083E74 0400238E */  lw         $v1, 0x4($s1)
/* 4DF9440 80083E78 FF004230 */  andi       $v0, $v0, 0xFF
/* 4DF9444 80083E7C 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 4DF9448 80083E80 21186200 */  addu       $v1, $v1, $v0
/* 4DF944C 80083E84 CB89010C */  jal        rand
/* 4DF9450 80083E88 040023AE */   sw        $v1, 0x4($s1)
/* 4DF9454 80083E8C 0800238E */  lw         $v1, 0x8($s1)
/* 4DF9458 80083E90 FF004230 */  andi       $v0, $v0, 0xFF
/* 4DF945C 80083E94 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 4DF9460 80083E98 21186200 */  addu       $v1, $v1, $v0
/* 4DF9464 80083E9C CB89010C */  jal        rand
/* 4DF9468 80083EA0 080023AE */   sw        $v1, 0x8($s1)
/* 4DF946C 80083EA4 CB89010C */  jal        rand
/* 4DF9470 80083EA8 440062A2 */   sb        $v0, 0x44($s3)
/* 4DF9474 80083EAC CB89010C */  jal        rand
/* 4DF9478 80083EB0 450062A2 */   sb        $v0, 0x45($s3)
/* 4DF947C 80083EB4 CB89010C */  jal        rand
/* 4DF9480 80083EB8 460062A2 */   sb        $v0, 0x46($s3)
/* 4DF9484 80083EBC 0F004230 */  andi       $v0, $v0, 0xF
/* 4DF9488 80083EC0 CB89010C */  jal        rand
/* 4DF948C 80083EC4 100022A2 */   sb        $v0, 0x10($s1)
/* 4DF9490 80083EC8 0F004230 */  andi       $v0, $v0, 0xF
/* 4DF9494 80083ECC CB89010C */  jal        rand
/* 4DF9498 80083ED0 110022A2 */   sb        $v0, 0x11($s1)
/* 4DF949C 80083ED4 0F004230 */  andi       $v0, $v0, 0xF
/* 4DF94A0 80083ED8 120022A2 */  sb         $v0, 0x12($s1)
/* 4DF94A4 80083EDC 1400A28E */  lw         $v0, 0x14($s5)
/* 4DF94A8 80083EE0 CB89010C */  jal        rand
/* 4DF94AC 80083EE4 0C0022AE */   sw        $v0, 0xC($s1)
/* 4DF94B0 80083EE8 03004230 */  andi       $v0, $v0, 0x3
/* 4DF94B4 80083EEC 10004224 */  addiu      $v0, $v0, 0x10
/* 4DF94B8 80083EF0 FF0F0208 */  j          .Llevel_54_80083FFC
/* 4DF94BC 80083EF4 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_54_80083EF8:
/* 4DF94C0 80083EF8 0000708E */  lw         $s0, 0x0($s3)
/* 4DF94C4 80083EFC C8E9000C */  jal        func_8003A720
/* 4DF94C8 80083F00 21206002 */   addu      $a0, $s3, $zero
/* 4DF94CC 80083F04 734A010C */  jal        func_800529CC
/* 4DF94D0 80083F08 21206002 */   addu      $a0, $s3, $zero
/* 4DF94D4 80083F0C 02000224 */  addiu      $v0, $zero, 0x2
/* 4DF94D8 80083F10 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 4DF94DC 80083F14 40000224 */  addiu      $v0, $zero, 0x40
/* 4DF94E0 80083F18 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 4DF94E4 80083F1C 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 4DF94E8 80083F20 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 4DF94EC 80083F24 FF0F0208 */  j          .Llevel_54_80083FFC
/* 4DF94F0 80083F28 000002AE */   sw        $v0, 0x0($s0)
.Llevel_54_80083F2C:
/* 4DF94F4 80083F2C C8E9000C */  jal        func_8003A720
/* 4DF94F8 80083F30 21206002 */   addu      $a0, $s3, $zero
/* 4DF94FC 80083F34 0300A012 */  beqz       $s5, .Llevel_54_80083F44
/* 4DF9500 80083F38 0C006426 */   addiu     $a0, $s3, 0xC
/* 4DF9504 80083F3C D30F0208 */  j          .Llevel_54_80083F4C
/* 4DF9508 80083F40 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_54_80083F44:
/* 4DF950C 80083F44 0880053C */  lui        $a1, %hi(g_Spyro)
/* 4DF9510 80083F48 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_54_80083F4C:
/* 4DF9514 80083F4C C05D000C */  jal        VecCopy
/* 4DF9518 80083F50 00000000 */   nop
/* 4DF951C 80083F54 0C006426 */  addiu      $a0, $s3, 0xC
/* 4DF9520 80083F58 1400628E */  lw         $v0, 0x14($s3)
/* 4DF9524 80083F5C 00080524 */  addiu      $a1, $zero, 0x800
/* 4DF9528 80083F60 00024224 */  addiu      $v0, $v0, 0x200
/* 4DF952C 80083F64 7B35010C */  jal        func_8004D5EC
/* 4DF9530 80083F68 140062AE */   sw        $v0, 0x14($s3)
/* 4DF9534 80083F6C 1400648E */  lw         $a0, 0x14($s3)
/* 4DF9538 80083F70 21184000 */  addu       $v1, $v0, $zero
/* 4DF953C 80083F74 23106400 */  subu       $v0, $v1, $a0
/* 4DF9540 80083F78 02004104 */  bgez       $v0, .Llevel_54_80083F84
/* 4DF9544 80083F7C 00000000 */   nop
/* 4DF9548 80083F80 23100200 */  negu       $v0, $v0
.Llevel_54_80083F84:
/* 4DF954C 80083F84 00084228 */  slti       $v0, $v0, 0x800
/* 4DF9550 80083F88 03004010 */  beqz       $v0, .Llevel_54_80083F98
/* 4DF9554 80083F8C 00FE8224 */   addiu     $v0, $a0, -0x200
/* 4DF9558 80083F90 FC0F0208 */  j          .Llevel_54_80083FF0
/* 4DF955C 80083F94 140063AE */   sw        $v1, 0x14($s3)
.Llevel_54_80083F98:
/* 4DF9560 80083F98 FC0F0208 */  j          .Llevel_54_80083FF0
/* 4DF9564 80083F9C 140062AE */   sw        $v0, 0x14($s3)
.Llevel_54_80083FA0:
/* 4DF9568 80083FA0 C8E9000C */  jal        func_8003A720
/* 4DF956C 80083FA4 21206002 */   addu      $a0, $s3, $zero
/* 4DF9570 80083FA8 21206002 */  addu       $a0, $s3, $zero
/* 4DF9574 80083FAC 20000224 */  addiu      $v0, $zero, 0x20
/* 4DF9578 80083FB0 500062A2 */  sb         $v0, 0x50($s3)
/* 4DF957C 80083FB4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 4DF9580 80083FB8 734A010C */  jal        func_800529CC
/* 4DF9584 80083FBC 520062A2 */   sb        $v0, 0x52($s3)
/* 4DF9588 80083FC0 00100208 */  j          .Llevel_54_80084000
/* 4DF958C 80083FC4 21106002 */   addu      $v0, $s3, $zero
.Llevel_54_80083FC8:
/* 4DF9590 80083FC8 C8E9000C */  jal        func_8003A720
/* 4DF9594 80083FCC 21206002 */   addu      $a0, $s3, $zero
/* 4DF9598 80083FD0 0300A012 */  beqz       $s5, .Llevel_54_80083FE0
/* 4DF959C 80083FD4 0C006426 */   addiu     $a0, $s3, 0xC
/* 4DF95A0 80083FD8 FA0F0208 */  j          .Llevel_54_80083FE8
/* 4DF95A4 80083FDC 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_54_80083FE0:
/* 4DF95A8 80083FE0 0880053C */  lui        $a1, %hi(g_Spyro)
/* 4DF95AC 80083FE4 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_54_80083FE8:
/* 4DF95B0 80083FE8 C05D000C */  jal        VecCopy
/* 4DF95B4 80083FEC 00000000 */   nop
.Llevel_54_80083FF0:
/* 4DF95B8 80083FF0 21206002 */  addu       $a0, $s3, $zero
.Llevel_54_80083FF4:
/* 4DF95BC 80083FF4 AA49010C */  jal        func_800526A8
/* 4DF95C0 80083FF8 00000000 */   nop
.Llevel_54_80083FFC:
/* 4DF95C4 80083FFC 21106002 */  addu       $v0, $s3, $zero
.Llevel_54_80084000:
/* 4DF95C8 80084000 5000BF8F */  lw         $ra, 0x50($sp)
/* 4DF95CC 80084004 4C00B58F */  lw         $s5, 0x4C($sp)
/* 4DF95D0 80084008 4800B48F */  lw         $s4, 0x48($sp)
/* 4DF95D4 8008400C 4400B38F */  lw         $s3, 0x44($sp)
/* 4DF95D8 80084010 4000B28F */  lw         $s2, 0x40($sp)
/* 4DF95DC 80084014 3C00B18F */  lw         $s1, 0x3C($sp)
/* 4DF95E0 80084018 3800B08F */  lw         $s0, 0x38($sp)
/* 4DF95E4 8008401C 5800BD27 */  addiu      $sp, $sp, 0x58
/* 4DF95E8 80084020 0800E003 */  jr         $ra
/* 4DF95EC 80084024 00000000 */   nop
.size func_level_54_800836A8, . - func_level_54_800836A8
