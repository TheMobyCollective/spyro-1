.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_42_80084718
/* 3A77CE0 80084718 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 3A77CE4 8008471C 3800B0AF */  sw         $s0, 0x38($sp)
/* 3A77CE8 80084720 21808000 */  addu       $s0, $a0, $zero
/* 3A77CEC 80084724 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 3A77CF0 80084728 21A8A000 */  addu       $s5, $a1, $zero
/* 3A77CF4 8008472C 5000BFAF */  sw         $ra, 0x50($sp)
/* 3A77CF8 80084730 4800B4AF */  sw         $s4, 0x48($sp)
/* 3A77CFC 80084734 4400B3AF */  sw         $s3, 0x44($sp)
/* 3A77D00 80084738 4000B2AF */  sw         $s2, 0x40($sp)
/* 3A77D04 8008473C 3149010C */  jal        func_800524C4
/* 3A77D08 80084740 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 3A77D0C 80084744 21984000 */  addu       $s3, $v0, $zero
/* 3A77D10 80084748 1400A012 */  beqz       $s5, .Llevel_42_8008479C
/* 3A77D14 8008474C 360070A6 */   sh        $s0, 0x36($s3)
/* 3A77D18 80084750 0780043C */  lui        $a0, %hi(D_80075828)
/* 3A77D1C 80084754 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 3A77D20 80084758 00000000 */  nop
/* 3A77D24 8008475C 2320A402 */  subu       $a0, $s5, $a0
/* 3A77D28 80084760 40190400 */  sll        $v1, $a0, 5
/* 3A77D2C 80084764 23186400 */  subu       $v1, $v1, $a0
/* 3A77D30 80084768 40190300 */  sll        $v1, $v1, 5
/* 3A77D34 8008476C 21186400 */  addu       $v1, $v1, $a0
/* 3A77D38 80084770 C0100300 */  sll        $v0, $v1, 3
/* 3A77D3C 80084774 21186200 */  addu       $v1, $v1, $v0
/* 3A77D40 80084778 C0130300 */  sll        $v0, $v1, 15
/* 3A77D44 8008477C 23104300 */  subu       $v0, $v0, $v1
/* 3A77D48 80084780 80100200 */  sll        $v0, $v0, 2
/* 3A77D4C 80084784 21104400 */  addu       $v0, $v0, $a0
/* 3A77D50 80084788 23100200 */  negu       $v0, $v0
/* 3A77D54 8008478C C3180200 */  sra        $v1, $v0, 3
/* 3A77D58 80084790 0001622C */  sltiu      $v0, $v1, 0x100
/* 3A77D5C 80084794 03004014 */  bnez       $v0, .Llevel_42_800847A4
/* 3A77D60 80084798 0E01022A */   slti      $v0, $s0, 0x10E
.Llevel_42_8008479C:
/* 3A77D64 8008479C 21180000 */  addu       $v1, $zero, $zero
/* 3A77D68 800847A0 0E01022A */  slti       $v0, $s0, 0x10E
.Llevel_42_800847A4:
/* 3A77D6C 800847A4 33004010 */  beqz       $v0, .Llevel_42_80084874
/* 3A77D70 800847A8 560063A2 */   sb        $v1, 0x56($s3)
/* 3A77D74 800847AC 0401022A */  slti       $v0, $s0, 0x104
/* 3A77D78 800847B0 E0014010 */  beqz       $v0, .Llevel_42_80084F34
/* 3A77D7C 800847B4 4C000224 */   addiu     $v0, $zero, 0x4C
/* 3A77D80 800847B8 10020212 */  beq        $s0, $v0, .Llevel_42_80084FFC
/* 3A77D84 800847BC 4D00022A */   slti      $v0, $s0, 0x4D
/* 3A77D88 800847C0 16004010 */  beqz       $v0, .Llevel_42_8008481C
/* 3A77D8C 800847C4 10000224 */   addiu     $v0, $zero, 0x10
/* 3A77D90 800847C8 75000212 */  beq        $s0, $v0, .Llevel_42_800849A0
/* 3A77D94 800847CC 1100022A */   slti      $v0, $s0, 0x11
/* 3A77D98 800847D0 07004010 */  beqz       $v0, .Llevel_42_800847F0
/* 3A77D9C 800847D4 0E000224 */   addiu     $v0, $zero, 0xE
/* 3A77DA0 800847D8 93000212 */  beq        $s0, $v0, .Llevel_42_80084A28
/* 3A77DA4 800847DC 0F000224 */   addiu     $v0, $zero, 0xF
/* 3A77DA8 800847E0 48000212 */  beq        $s0, $v0, .Llevel_42_80084904
/* 3A77DAC 800847E4 00000000 */   nop
/* 3A77DB0 800847E8 09140208 */  j          .Llevel_42_80085024
/* 3A77DB4 800847EC 00000000 */   nop
.Llevel_42_800847F0:
/* 3A77DB8 800847F0 22000224 */  addiu      $v0, $zero, 0x22
/* 3A77DBC 800847F4 7E000212 */  beq        $s0, $v0, .Llevel_42_800849F0
/* 3A77DC0 800847F8 2200022A */   slti      $v0, $s0, 0x22
/* 3A77DC4 800847FC 09024014 */  bnez       $v0, .Llevel_42_80085024
/* 3A77DC8 80084800 4600022A */   slti      $v0, $s0, 0x46
/* 3A77DCC 80084804 07024010 */  beqz       $v0, .Llevel_42_80085024
/* 3A77DD0 80084808 4300022A */   slti      $v0, $s0, 0x43
/* 3A77DD4 8008480C EE004010 */  beqz       $v0, .Llevel_42_80084BC8
/* 3A77DD8 80084810 00000000 */   nop
/* 3A77DDC 80084814 09140208 */  j          .Llevel_42_80085024
/* 3A77DE0 80084818 00000000 */   nop
.Llevel_42_8008481C:
/* 3A77DE4 8008481C 78000224 */  addiu      $v0, $zero, 0x78
/* 3A77DE8 80084820 D7000212 */  beq        $s0, $v0, .Llevel_42_80084B80
/* 3A77DEC 80084824 7900022A */   slti      $v0, $s0, 0x79
/* 3A77DF0 80084828 07004010 */  beqz       $v0, .Llevel_42_80084848
/* 3A77DF4 8008482C 5800022A */   slti      $v0, $s0, 0x58
/* 3A77DF8 80084830 FC014010 */  beqz       $v0, .Llevel_42_80085024
/* 3A77DFC 80084834 5300022A */   slti      $v0, $s0, 0x53
/* 3A77E00 80084838 7B004010 */  beqz       $v0, .Llevel_42_80084A28
/* 3A77E04 8008483C 00000000 */   nop
/* 3A77E08 80084840 09140208 */  j          .Llevel_42_80085024
/* 3A77E0C 80084844 00000000 */   nop
.Llevel_42_80084848:
/* 3A77E10 80084848 FB000224 */  addiu      $v0, $zero, 0xFB
/* 3A77E14 8008484C 49010212 */  beq        $s0, $v0, .Llevel_42_80084D74
/* 3A77E18 80084850 FB00022A */   slti      $v0, $s0, 0xFB
/* 3A77E1C 80084854 F3014014 */  bnez       $v0, .Llevel_42_80085024
/* 3A77E20 80084858 0201022A */   slti      $v0, $s0, 0x102
/* 3A77E24 8008485C F1014010 */  beqz       $v0, .Llevel_42_80085024
/* 3A77E28 80084860 FF00022A */   slti      $v0, $s0, 0xFF
/* 3A77E2C 80084864 D8004010 */  beqz       $v0, .Llevel_42_80084BC8
/* 3A77E30 80084868 00000000 */   nop
/* 3A77E34 8008486C 09140208 */  j          .Llevel_42_80085024
/* 3A77E38 80084870 00000000 */   nop
.Llevel_42_80084874:
/* 3A77E3C 80084874 90010224 */  addiu      $v0, $zero, 0x190
/* 3A77E40 80084878 C3010212 */  beq        $s0, $v0, .Llevel_42_80084F88
/* 3A77E44 8008487C 9101022A */   slti      $v0, $s0, 0x191
/* 3A77E48 80084880 10004010 */  beqz       $v0, .Llevel_42_800848C4
/* 3A77E4C 80084884 3801022A */   slti      $v0, $s0, 0x138
/* 3A77E50 80084888 07004010 */  beqz       $v0, .Llevel_42_800848A8
/* 3A77E54 8008488C 3501022A */   slti      $v0, $s0, 0x135
/* 3A77E58 80084890 CD004010 */  beqz       $v0, .Llevel_42_80084BC8
/* 3A77E5C 80084894 15010224 */   addiu     $v0, $zero, 0x115
/* 3A77E60 80084898 A6010212 */  beq        $s0, $v0, .Llevel_42_80084F34
/* 3A77E64 8008489C 00000000 */   nop
/* 3A77E68 800848A0 09140208 */  j          .Llevel_42_80085024
/* 3A77E6C 800848A4 00000000 */   nop
.Llevel_42_800848A8:
/* 3A77E70 800848A8 47010224 */  addiu      $v0, $zero, 0x147
/* 3A77E74 800848AC A1010212 */  beq        $s0, $v0, .Llevel_42_80084F34
/* 3A77E78 800848B0 88010224 */   addiu     $v0, $zero, 0x188
/* 3A77E7C 800848B4 AC010212 */  beq        $s0, $v0, .Llevel_42_80084F68
/* 3A77E80 800848B8 00000000 */   nop
/* 3A77E84 800848BC 09140208 */  j          .Llevel_42_80085024
/* 3A77E88 800848C0 00000000 */   nop
.Llevel_42_800848C4:
/* 3A77E8C 800848C4 AA01022A */  slti       $v0, $s0, 0x1AA
/* 3A77E90 800848C8 07004010 */  beqz       $v0, .Llevel_42_800848E8
/* 3A77E94 800848CC A701022A */   slti      $v0, $s0, 0x1A7
/* 3A77E98 800848D0 BD004010 */  beqz       $v0, .Llevel_42_80084BC8
/* 3A77E9C 800848D4 95010224 */   addiu     $v0, $zero, 0x195
/* 3A77EA0 800848D8 AB010212 */  beq        $s0, $v0, .Llevel_42_80084F88
/* 3A77EA4 800848DC 00000000 */   nop
/* 3A77EA8 800848E0 09140208 */  j          .Llevel_42_80085024
/* 3A77EAC 800848E4 00000000 */   nop
.Llevel_42_800848E8:
/* 3A77EB0 800848E8 C401022A */  slti       $v0, $s0, 0x1C4
/* 3A77EB4 800848EC C3014014 */  bnez       $v0, .Llevel_42_80084FFC
/* 3A77EB8 800848F0 DD010224 */   addiu     $v0, $zero, 0x1DD
/* 3A77EBC 800848F4 A4010212 */  beq        $s0, $v0, .Llevel_42_80084F88
/* 3A77EC0 800848F8 00000000 */   nop
/* 3A77EC4 800848FC 09140208 */  j          .Llevel_42_80085024
/* 3A77EC8 80084900 00000000 */   nop
.Llevel_42_80084904:
/* 3A77ECC 80084904 0000708E */  lw         $s0, 0x0($s3)
/* 3A77ED0 80084908 C8E9000C */  jal        func_8003A720
/* 3A77ED4 8008490C 21206002 */   addu      $a0, $s3, $zero
/* 3A77ED8 80084910 8C000224 */  addiu      $v0, $zero, 0x8C
/* 3A77EDC 80084914 080002AE */  sw         $v0, 0x8($s0)
/* 3A77EE0 80084918 03000224 */  addiu      $v0, $zero, 0x3
/* 3A77EE4 8008491C 100002A2 */  sb         $v0, 0x10($s0)
/* 3A77EE8 80084920 FF000224 */  addiu      $v0, $zero, 0xFF
/* 3A77EEC 80084924 140002A2 */  sb         $v0, 0x14($s0)
/* 3A77EF0 80084928 02000224 */  addiu      $v0, $zero, 0x2
/* 3A77EF4 8008492C 000000AE */  sw         $zero, 0x0($s0)
/* 3A77EF8 80084930 040000AE */  sw         $zero, 0x4($s0)
/* 3A77EFC 80084934 0E0000A2 */  sb         $zero, 0xE($s0)
/* 3A77F00 80084938 0F0000A2 */  sb         $zero, 0xF($s0)
/* 3A77F04 8008493C 110000A2 */  sb         $zero, 0x11($s0)
/* 3A77F08 80084940 120000A2 */  sb         $zero, 0x12($s0)
/* 3A77F0C 80084944 130000A2 */  sb         $zero, 0x13($s0)
/* 3A77F10 80084948 490062A2 */  sb         $v0, 0x49($s3)
/* 3A77F14 8008494C 18000224 */  addiu      $v0, $zero, 0x18
/* 3A77F18 80084950 500062A2 */  sb         $v0, 0x50($s3)
/* 3A77F1C 80084954 10000224 */  addiu      $v0, $zero, 0x10
/* 3A77F20 80084958 520062A2 */  sb         $v0, 0x52($s3)
/* 3A77F24 8008495C 20000224 */  addiu      $v0, $zero, 0x20
/* 3A77F28 80084960 440062A2 */  sb         $v0, 0x44($s3)
/* 3A77F2C 80084964 450060A2 */  sb         $zero, 0x45($s3)
/* 3A77F30 80084968 0400A012 */  beqz       $s5, .Llevel_42_8008497C
/* 3A77F34 8008496C 460060A2 */   sb        $zero, 0x46($s3)
/* 3A77F38 80084970 0C006426 */  addiu      $a0, $s3, 0xC
/* 3A77F3C 80084974 C05D000C */  jal        VecCopy
/* 3A77F40 80084978 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_42_8008497C:
/* 3A77F44 8008497C AA49010C */  jal        func_800526A8
/* 3A77F48 80084980 21206002 */   addu      $a0, $s3, $zero
/* 3A77F4C 80084984 4B006292 */  lbu        $v0, 0x4B($s3)
/* 3A77F50 80084988 01000324 */  addiu      $v1, $zero, 0x1
/* 3A77F54 8008498C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 3A77F58 80084990 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 3A77F5C 80084994 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 3A77F60 80084998 5A130208 */  j          .Llevel_42_80084D68
/* 3A77F64 8008499C 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_42_800849A0:
/* 3A77F68 800849A0 0000718E */  lw         $s1, 0x0($s3)
/* 3A77F6C 800849A4 C8E9000C */  jal        func_8003A720
/* 3A77F70 800849A8 21206002 */   addu      $a0, $s3, $zero
/* 3A77F74 800849AC AA49010C */  jal        func_800526A8
/* 3A77F78 800849B0 21206002 */   addu      $a0, $s3, $zero
/* 3A77F7C 800849B4 0C007026 */  addiu      $s0, $s3, 0xC
/* 3A77F80 800849B8 21200002 */  addu       $a0, $s0, $zero
/* 3A77F84 800849BC C05D000C */  jal        VecCopy
/* 3A77F88 800849C0 0C00A526 */   addiu     $a1, $s5, 0xC
/* 3A77F8C 800849C4 21280002 */  addu       $a1, $s0, $zero
/* 3A77F90 800849C8 1400628E */  lw         $v0, 0x14($s3)
/* 3A77F94 800849CC 04002426 */  addiu      $a0, $s1, 0x4
/* 3A77F98 800849D0 00024224 */  addiu      $v0, $v0, 0x200
/* 3A77F9C 800849D4 C05D000C */  jal        VecCopy
/* 3A77FA0 800849D8 140062AE */   sw        $v0, 0x14($s3)
/* 3A77FA4 800849DC 08070224 */  addiu      $v0, $zero, 0x708
/* 3A77FA8 800849E0 130020A2 */  sb         $zero, 0x13($s1)
/* 3A77FAC 800849E4 120020A2 */  sb         $zero, 0x12($s1)
/* 3A77FB0 800849E8 16140208 */  j          .Llevel_42_80085058
/* 3A77FB4 800849EC 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_42_800849F0:
/* 3A77FB8 800849F0 C8E9000C */  jal        func_8003A720
/* 3A77FBC 800849F4 21206002 */   addu      $a0, $s3, $zero
/* 3A77FC0 800849F8 20000224 */  addiu      $v0, $zero, 0x20
/* 3A77FC4 800849FC 500062A2 */  sb         $v0, 0x50($s3)
/* 3A77FC8 80084A00 FF000224 */  addiu      $v0, $zero, 0xFF
/* 3A77FCC 80084A04 0400A012 */  beqz       $s5, .Llevel_42_80084A18
/* 3A77FD0 80084A08 520062A2 */   sb        $v0, 0x52($s3)
/* 3A77FD4 80084A0C 0C006426 */  addiu      $a0, $s3, 0xC
/* 3A77FD8 80084A10 C05D000C */  jal        VecCopy
/* 3A77FDC 80084A14 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_42_80084A18:
/* 3A77FE0 80084A18 734A010C */  jal        func_800529CC
/* 3A77FE4 80084A1C 21206002 */   addu      $a0, $s3, $zero
/* 3A77FE8 80084A20 17140208 */  j          .Llevel_42_8008505C
/* 3A77FEC 80084A24 21106002 */   addu      $v0, $s3, $zero
.Llevel_42_80084A28:
/* 3A77FF0 80084A28 0000718E */  lw         $s1, 0x0($s3)
/* 3A77FF4 80084A2C C8E9000C */  jal        func_8003A720
/* 3A77FF8 80084A30 21206002 */   addu      $a0, $s3, $zero
/* 3A77FFC 80084A34 8C000224 */  addiu      $v0, $zero, 0x8C
/* 3A78000 80084A38 000020AE */  sw         $zero, 0x0($s1)
/* 3A78004 80084A3C 040020AE */  sw         $zero, 0x4($s1)
/* 3A78008 80084A40 080022AE */  sw         $v0, 0x8($s1)
/* 3A7800C 80084A44 0E0020A2 */  sb         $zero, 0xE($s1)
/* 3A78010 80084A48 0F0020A2 */  sb         $zero, 0xF($s1)
/* 3A78014 80084A4C 110020A2 */  sb         $zero, 0x11($s1)
/* 3A78018 80084A50 120020A2 */  sb         $zero, 0x12($s1)
/* 3A7801C 80084A54 130020A2 */  sb         $zero, 0x13($s1)
/* 3A78020 80084A58 3600A386 */  lh         $v1, 0x36($s5)
/* 3A78024 80084A5C 0D000224 */  addiu      $v0, $zero, 0xD
/* 3A78028 80084A60 02006214 */  bne        $v1, $v0, .Llevel_42_80084A6C
/* 3A7802C 80084A64 03000224 */   addiu     $v0, $zero, 0x3
/* 3A78030 80084A68 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_42_80084A6C:
/* 3A78034 80084A6C 100022A2 */  sb         $v0, 0x10($s1)
/* 3A78038 80084A70 0C007026 */  addiu      $s0, $s3, 0xC
/* 3A7803C 80084A74 21200002 */  addu       $a0, $s0, $zero
/* 3A78040 80084A78 0C00A526 */  addiu      $a1, $s5, 0xC
/* 3A78044 80084A7C FF000224 */  addiu      $v0, $zero, 0xFF
/* 3A78048 80084A80 140022A2 */  sb         $v0, 0x14($s1)
/* 3A7804C 80084A84 02001124 */  addiu      $s1, $zero, 0x2
/* 3A78050 80084A88 18000224 */  addiu      $v0, $zero, 0x18
/* 3A78054 80084A8C 500062A2 */  sb         $v0, 0x50($s3)
/* 3A78058 80084A90 40000224 */  addiu      $v0, $zero, 0x40
/* 3A7805C 80084A94 520062A2 */  sb         $v0, 0x52($s3)
/* 3A78060 80084A98 20000224 */  addiu      $v0, $zero, 0x20
/* 3A78064 80084A9C 490071A2 */  sb         $s1, 0x49($s3)
/* 3A78068 80084AA0 440062A2 */  sb         $v0, 0x44($s3)
/* 3A7806C 80084AA4 450060A2 */  sb         $zero, 0x45($s3)
/* 3A78070 80084AA8 C05D000C */  jal        VecCopy
/* 3A78074 80084AAC 460060A2 */   sb        $zero, 0x46($s3)
/* 3A78078 80084AB0 734A010C */  jal        func_800529CC
/* 3A7807C 80084AB4 21206002 */   addu      $a0, $s3, $zero
/* 3A78080 80084AB8 1000A427 */  addiu      $a0, $sp, 0x10
/* 3A78084 80084ABC 21280002 */  addu       $a1, $s0, $zero
/* 3A78088 80084AC0 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 3A7808C 80084AC4 C05D000C */  jal        VecCopy
/* 3A78090 80084AC8 1C0062AE */   sw        $v0, 0x1C($s3)
/* 3A78094 80084ACC 1000A427 */  addiu      $a0, $sp, 0x10
/* 3A78098 80084AD0 1800A28F */  lw         $v0, 0x18($sp)
/* 3A7809C 80084AD4 0100053C */  lui        $a1, (0x10000 >> 16)
/* 3A780A0 80084AD8 00044224 */  addiu      $v0, $v0, 0x400
/* 3A780A4 80084ADC 7B35010C */  jal        func_8004D5EC
/* 3A780A8 80084AE0 1800A2AF */   sw        $v0, 0x18($sp)
/* 3A780AC 80084AE4 F44C010C */  jal        func_800533D0
/* 3A780B0 80084AE8 21206002 */   addu      $a0, $s3, $zero
/* 3A780B4 80084AEC 36006386 */  lh         $v1, 0x36($s3)
/* 3A780B8 80084AF0 0E000224 */  addiu      $v0, $zero, 0xE
/* 3A780BC 80084AF4 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 3A780C0 80084AF8 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 3A780C4 80084AFC 03006214 */  bne        $v1, $v0, .Llevel_42_80084B0C
/* 3A780C8 80084B00 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 3A780CC 80084B04 0C000224 */  addiu      $v0, $zero, 0xC
/* 3A780D0 80084B08 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_42_80084B0C:
/* 3A780D4 80084B0C 36006386 */  lh         $v1, 0x36($s3)
/* 3A780D8 80084B10 53000224 */  addiu      $v0, $zero, 0x53
/* 3A780DC 80084B14 05006214 */  bne        $v1, $v0, .Llevel_42_80084B2C
/* 3A780E0 80084B18 54000224 */   addiu     $v0, $zero, 0x54
/* 3A780E4 80084B1C 01000224 */  addiu      $v0, $zero, 0x1
/* 3A780E8 80084B20 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 3A780EC 80084B24 36006386 */  lh         $v1, 0x36($s3)
/* 3A780F0 80084B28 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_42_80084B2C:
/* 3A780F4 80084B2C 02006214 */  bne        $v1, $v0, .Llevel_42_80084B38
/* 3A780F8 80084B30 00000000 */   nop
/* 3A780FC 80084B34 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_42_80084B38:
/* 3A78100 80084B38 36006386 */  lh         $v1, 0x36($s3)
/* 3A78104 80084B3C 55000224 */  addiu      $v0, $zero, 0x55
/* 3A78108 80084B40 05006214 */  bne        $v1, $v0, .Llevel_42_80084B58
/* 3A7810C 80084B44 56000224 */   addiu     $v0, $zero, 0x56
/* 3A78110 80084B48 03000224 */  addiu      $v0, $zero, 0x3
/* 3A78114 80084B4C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 3A78118 80084B50 36006386 */  lh         $v1, 0x36($s3)
/* 3A7811C 80084B54 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_42_80084B58:
/* 3A78120 80084B58 02006214 */  bne        $v1, $v0, .Llevel_42_80084B64
/* 3A78124 80084B5C 04000224 */   addiu     $v0, $zero, 0x4
/* 3A78128 80084B60 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_42_80084B64:
/* 3A7812C 80084B64 36006386 */  lh         $v1, 0x36($s3)
/* 3A78130 80084B68 57000224 */  addiu      $v0, $zero, 0x57
/* 3A78134 80084B6C 3B016214 */  bne        $v1, $v0, .Llevel_42_8008505C
/* 3A78138 80084B70 21106002 */   addu      $v0, $s3, $zero
/* 3A7813C 80084B74 05000224 */  addiu      $v0, $zero, 0x5
/* 3A78140 80084B78 16140208 */  j          .Llevel_42_80085058
/* 3A78144 80084B7C 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_42_80084B80:
/* 3A78148 80084B80 0000708E */  lw         $s0, 0x0($s3)
/* 3A7814C 80084B84 C8E9000C */  jal        func_8003A720
/* 3A78150 80084B88 21206002 */   addu      $a0, $s3, $zero
/* 3A78154 80084B8C AA49010C */  jal        func_800526A8
/* 3A78158 80084B90 21206002 */   addu      $a0, $s3, $zero
/* 3A7815C 80084B94 490060A2 */  sb         $zero, 0x49($s3)
/* 3A78160 80084B98 000000AE */  sw         $zero, 0x0($s0)
/* 3A78164 80084B9C 080000A6 */  sh         $zero, 0x8($s0)
/* 3A78168 80084BA0 060000A6 */  sh         $zero, 0x6($s0)
/* 3A7816C 80084BA4 040000A6 */  sh         $zero, 0x4($s0)
/* 3A78170 80084BA8 0C0000AE */  sw         $zero, 0xC($s0)
/* 3A78174 80084BAC 2A01A012 */  beqz       $s5, .Llevel_42_80085058
/* 3A78178 80084BB0 100000AE */   sw        $zero, 0x10($s0)
/* 3A7817C 80084BB4 0C006426 */  addiu      $a0, $s3, 0xC
/* 3A78180 80084BB8 C05D000C */  jal        VecCopy
/* 3A78184 80084BBC 0C00A526 */   addiu     $a1, $s5, 0xC
/* 3A78188 80084BC0 17140208 */  j          .Llevel_42_8008505C
/* 3A7818C 80084BC4 21106002 */   addu      $v0, $s3, $zero
.Llevel_42_80084BC8:
/* 3A78190 80084BC8 0000748E */  lw         $s4, 0x0($s3)
/* 3A78194 80084BCC C8E9000C */  jal        func_8003A720
/* 3A78198 80084BD0 21206002 */   addu      $a0, $s3, $zero
/* 3A7819C 80084BD4 0C006426 */  addiu      $a0, $s3, 0xC
/* 3A781A0 80084BD8 0C00A526 */  addiu      $a1, $s5, 0xC
/* 3A781A4 80084BDC 20000224 */  addiu      $v0, $zero, 0x20
/* 3A781A8 80084BE0 C05D000C */  jal        VecCopy
/* 3A781AC 80084BE4 500062A2 */   sb        $v0, 0x50($s3)
/* 3A781B0 80084BE8 AA49010C */  jal        func_800526A8
/* 3A781B4 80084BEC 21206002 */   addu      $a0, $s3, $zero
/* 3A781B8 80084BF0 CB89010C */  jal        rand
/* 3A781BC 80084BF4 00000000 */   nop
/* 3A781C0 80084BF8 CB89010C */  jal        rand
/* 3A781C4 80084BFC FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 3A781C8 80084C00 FF075130 */  andi       $s1, $v0, 0x7FF
/* 3A781CC 80084C04 2C5B000C */  jal        Cos
/* 3A781D0 80084C08 21202002 */   addu      $a0, $s1, $zero
/* 3A781D4 80084C0C 21204002 */  addu       $a0, $s2, $zero
/* 3A781D8 80084C10 2C5B000C */  jal        Cos
/* 3A781DC 80084C14 21804000 */   addu      $s0, $v0, $zero
/* 3A781E0 80084C18 43811000 */  sra        $s0, $s0, 5
/* 3A781E4 80084C1C 18000202 */  mult       $s0, $v0
/* 3A781E8 80084C20 21202002 */  addu       $a0, $s1, $zero
/* 3A781EC 80084C24 12380000 */  mflo       $a3
/* 3A781F0 80084C28 03130700 */  sra        $v0, $a3, 12
/* 3A781F4 80084C2C 2C5B000C */  jal        Cos
/* 3A781F8 80084C30 000082A6 */   sh        $v0, 0x0($s4)
/* 3A781FC 80084C34 21204002 */  addu       $a0, $s2, $zero
/* 3A78200 80084C38 165B000C */  jal        Sin
/* 3A78204 80084C3C 21804000 */   addu      $s0, $v0, $zero
/* 3A78208 80084C40 43811000 */  sra        $s0, $s0, 5
/* 3A7820C 80084C44 18000202 */  mult       $s0, $v0
/* 3A78210 80084C48 21202002 */  addu       $a0, $s1, $zero
/* 3A78214 80084C4C 12380000 */  mflo       $a3
/* 3A78218 80084C50 03130700 */  sra        $v0, $a3, 12
/* 3A7821C 80084C54 165B000C */  jal        Sin
/* 3A78220 80084C58 020082A6 */   sh        $v0, 0x2($s4)
/* 3A78224 80084C5C 43110200 */  sra        $v0, $v0, 5
/* 3A78228 80084C60 040082A6 */  sh         $v0, 0x4($s4)
/* 3A7822C 80084C64 1800A28E */  lw         $v0, 0x18($s5)
/* 3A78230 80084C68 0200033C */  lui        $v1, (0x20000 >> 16)
/* 3A78234 80084C6C 24104300 */  and        $v0, $v0, $v1
/* 3A78238 80084C70 13004010 */  beqz       $v0, .Llevel_42_80084CC0
/* 3A7823C 80084C74 00000000 */   nop
/* 3A78240 80084C78 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 3A78244 80084C7C 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 3A78248 80084C80 00008396 */  lhu        $v1, 0x0($s4)
/* 3A7824C 80084C84 83110200 */  sra        $v0, $v0, 6
/* 3A78250 80084C88 21186200 */  addu       $v1, $v1, $v0
/* 3A78254 80084C8C 000083A6 */  sh         $v1, 0x0($s4)
/* 3A78258 80084C90 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 3A7825C 80084C94 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 3A78260 80084C98 02008396 */  lhu        $v1, 0x2($s4)
/* 3A78264 80084C9C 83110200 */  sra        $v0, $v0, 6
/* 3A78268 80084CA0 21186200 */  addu       $v1, $v1, $v0
/* 3A7826C 80084CA4 020083A6 */  sh         $v1, 0x2($s4)
/* 3A78270 80084CA8 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 3A78274 80084CAC 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 3A78278 80084CB0 04008396 */  lhu        $v1, 0x4($s4)
/* 3A7827C 80084CB4 83110200 */  sra        $v0, $v0, 6
/* 3A78280 80084CB8 21186200 */  addu       $v1, $v1, $v0
/* 3A78284 80084CBC 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_42_80084CC0:
/* 3A78288 80084CC0 00008286 */  lh         $v0, 0x0($s4)
/* 3A7828C 80084CC4 0C00638E */  lw         $v1, 0xC($s3)
/* 3A78290 80084CC8 80100200 */  sll        $v0, $v0, 2
/* 3A78294 80084CCC 21186200 */  addu       $v1, $v1, $v0
/* 3A78298 80084CD0 0C0063AE */  sw         $v1, 0xC($s3)
/* 3A7829C 80084CD4 02008286 */  lh         $v0, 0x2($s4)
/* 3A782A0 80084CD8 1000638E */  lw         $v1, 0x10($s3)
/* 3A782A4 80084CDC 80100200 */  sll        $v0, $v0, 2
/* 3A782A8 80084CE0 21186200 */  addu       $v1, $v1, $v0
/* 3A782AC 80084CE4 100063AE */  sw         $v1, 0x10($s3)
/* 3A782B0 80084CE8 04008286 */  lh         $v0, 0x4($s4)
/* 3A782B4 80084CEC 1400638E */  lw         $v1, 0x14($s3)
/* 3A782B8 80084CF0 80100200 */  sll        $v0, $v0, 2
/* 3A782BC 80084CF4 21186200 */  addu       $v1, $v1, $v0
/* 3A782C0 80084CF8 CB89010C */  jal        rand
/* 3A782C4 80084CFC 140063AE */   sw        $v1, 0x14($s3)
/* 3A782C8 80084D00 0F004230 */  andi       $v0, $v0, 0xF
/* 3A782CC 80084D04 CB89010C */  jal        rand
/* 3A782D0 80084D08 060082A6 */   sh        $v0, 0x6($s4)
/* 3A782D4 80084D0C 0F004230 */  andi       $v0, $v0, 0xF
/* 3A782D8 80084D10 CB89010C */  jal        rand
/* 3A782DC 80084D14 080082A6 */   sh        $v0, 0x8($s4)
/* 3A782E0 80084D18 0F004230 */  andi       $v0, $v0, 0xF
/* 3A782E4 80084D1C 0A0082A6 */  sh         $v0, 0xA($s4)
/* 3A782E8 80084D20 1400A28E */  lw         $v0, 0x14($s5)
/* 3A782EC 80084D24 00000000 */  nop
/* 3A782F0 80084D28 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 3A782F4 80084D2C CB89010C */  jal        rand
/* 3A782F8 80084D30 100082AE */   sw        $v0, 0x10($s4)
/* 3A782FC 80084D34 0F004230 */  andi       $v0, $v0, 0xF
/* 3A78300 80084D38 40000324 */  addiu      $v1, $zero, 0x40
/* 3A78304 80084D3C 23186200 */  subu       $v1, $v1, $v0
/* 3A78308 80084D40 0C0083AE */  sw         $v1, 0xC($s4)
/* 3A7830C 80084D44 36006296 */  lhu        $v0, 0x36($s3)
/* 3A78310 80084D48 00000000 */  nop
/* 3A78314 80084D4C CBFE4224 */  addiu      $v0, $v0, -0x135
/* 3A78318 80084D50 0300422C */  sltiu      $v0, $v0, 0x3
/* 3A7831C 80084D54 C0004010 */  beqz       $v0, .Llevel_42_80085058
/* 3A78320 80084D58 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 3A78324 80084D5C 4B006292 */  lbu        $v0, 0x4B($s3)
/* 3A78328 80084D60 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 3A7832C 80084D64 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_42_80084D68:
/* 3A78330 80084D68 80004234 */  ori        $v0, $v0, 0x80
/* 3A78334 80084D6C 16140208 */  j          .Llevel_42_80085058
/* 3A78338 80084D70 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_42_80084D74:
/* 3A7833C 80084D74 0000718E */  lw         $s1, 0x0($s3)
/* 3A78340 80084D78 C8E9000C */  jal        func_8003A720
/* 3A78344 80084D7C 21206002 */   addu      $a0, $s3, $zero
/* 3A78348 80084D80 21206002 */  addu       $a0, $s3, $zero
/* 3A7834C 80084D84 20000224 */  addiu      $v0, $zero, 0x20
/* 3A78350 80084D88 500062A2 */  sb         $v0, 0x50($s3)
/* 3A78354 80084D8C FF000224 */  addiu      $v0, $zero, 0xFF
/* 3A78358 80084D90 734A010C */  jal        func_800529CC
/* 3A7835C 80084D94 520062A2 */   sb        $v0, 0x52($s3)
/* 3A78360 80084D98 0E000224 */  addiu      $v0, $zero, 0xE
/* 3A78364 80084D9C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 3A78368 80084DA0 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 3A7836C 80084DA4 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 3A78370 80084DA8 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 3A78374 80084DAC 0780033C */  lui        $v1, %hi(D_80077058)
/* 3A78378 80084DB0 5870638C */  lw         $v1, %lo(D_80077058)($v1)
/* 3A7837C 80084DB4 03000224 */  addiu      $v0, $zero, 0x3
/* 3A78380 80084DB8 03006214 */  bne        $v1, $v0, .Llevel_42_80084DC8
/* 3A78384 80084DBC 01000224 */   addiu     $v0, $zero, 0x1
/* 3A78388 80084DC0 74130208 */  j          .Llevel_42_80084DD0
/* 3A7838C 80084DC4 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_42_80084DC8:
/* 3A78390 80084DC8 02006214 */  bne        $v1, $v0, .Llevel_42_80084DD4
/* 3A78394 80084DCC 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_42_80084DD0:
/* 3A78398 80084DD0 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_42_80084DD4:
/* 3A7839C 80084DD4 CB89010C */  jal        rand
/* 3A783A0 80084DD8 00000000 */   nop
/* 3A783A4 80084DDC 2000A426 */  addiu      $a0, $s5, 0x20
/* 3A783A8 80084DE0 07004230 */  andi       $v0, $v0, 0x7
/* 3A783AC 80084DE4 80100200 */  sll        $v0, $v0, 2
/* 3A783B0 80084DE8 2000B027 */  addiu      $s0, $sp, 0x20
/* 3A783B4 80084DEC 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 3A783B8 80084DF0 21082200 */  addu       $at, $at, $v0
/* 3A783BC 80084DF4 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 3A783C0 80084DF8 21280002 */  addu       $a1, $s0, $zero
/* 3A783C4 80084DFC 2400A0AF */  sw         $zero, 0x24($sp)
/* 3A783C8 80084E00 2000A3AF */  sw         $v1, 0x20($sp)
/* 3A783CC 80084E04 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 3A783D0 80084E08 21082200 */  addu       $at, $at, $v0
/* 3A783D4 80084E0C A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 3A783D8 80084E10 21300002 */  addu       $a2, $s0, $zero
/* 3A783DC 80084E14 125C000C */  jal        VecRotateByMatrix
/* 3A783E0 80084E18 2800A2AF */   sw        $v0, 0x28($sp)
/* 3A783E4 80084E1C CB89010C */  jal        rand
/* 3A783E8 80084E20 00000000 */   nop
/* 3A783EC 80084E24 2000A38F */  lw         $v1, 0x20($sp)
/* 3A783F0 80084E28 7F004230 */  andi       $v0, $v0, 0x7F
/* 3A783F4 80084E2C C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 3A783F8 80084E30 21186200 */  addu       $v1, $v1, $v0
/* 3A783FC 80084E34 CB89010C */  jal        rand
/* 3A78400 80084E38 2000A3AF */   sw        $v1, 0x20($sp)
/* 3A78404 80084E3C 2400A38F */  lw         $v1, 0x24($sp)
/* 3A78408 80084E40 7F004230 */  andi       $v0, $v0, 0x7F
/* 3A7840C 80084E44 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 3A78410 80084E48 21186200 */  addu       $v1, $v1, $v0
/* 3A78414 80084E4C CB89010C */  jal        rand
/* 3A78418 80084E50 2400A3AF */   sw        $v1, 0x24($sp)
/* 3A7841C 80084E54 0C006426 */  addiu      $a0, $s3, 0xC
/* 3A78420 80084E58 0C00A526 */  addiu      $a1, $s5, 0xC
/* 3A78424 80084E5C 21300002 */  addu       $a2, $s0, $zero
/* 3A78428 80084E60 2800A38F */  lw         $v1, 0x28($sp)
/* 3A7842C 80084E64 7F004230 */  andi       $v0, $v0, 0x7F
/* 3A78430 80084E68 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 3A78434 80084E6C 21186200 */  addu       $v1, $v1, $v0
/* 3A78438 80084E70 D65D000C */  jal        VecAdd
/* 3A7843C 80084E74 2800A3AF */   sw        $v1, 0x28($sp)
/* 3A78440 80084E78 21202002 */  addu       $a0, $s1, $zero
/* 3A78444 80084E7C C05D000C */  jal        VecCopy
/* 3A78448 80084E80 21280002 */   addu      $a1, $s0, $zero
/* 3A7844C 80084E84 21202002 */  addu       $a0, $s1, $zero
/* 3A78450 80084E88 B25D000C */  jal        VecShiftRight
/* 3A78454 80084E8C 02000524 */   addiu     $a1, $zero, 0x2
/* 3A78458 80084E90 CB89010C */  jal        rand
/* 3A7845C 80084E94 00000000 */   nop
/* 3A78460 80084E98 0000238E */  lw         $v1, 0x0($s1)
/* 3A78464 80084E9C FF004230 */  andi       $v0, $v0, 0xFF
/* 3A78468 80084EA0 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 3A7846C 80084EA4 21186200 */  addu       $v1, $v1, $v0
/* 3A78470 80084EA8 CB89010C */  jal        rand
/* 3A78474 80084EAC 000023AE */   sw        $v1, 0x0($s1)
/* 3A78478 80084EB0 0400238E */  lw         $v1, 0x4($s1)
/* 3A7847C 80084EB4 FF004230 */  andi       $v0, $v0, 0xFF
/* 3A78480 80084EB8 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 3A78484 80084EBC 21186200 */  addu       $v1, $v1, $v0
/* 3A78488 80084EC0 CB89010C */  jal        rand
/* 3A7848C 80084EC4 040023AE */   sw        $v1, 0x4($s1)
/* 3A78490 80084EC8 0800238E */  lw         $v1, 0x8($s1)
/* 3A78494 80084ECC FF004230 */  andi       $v0, $v0, 0xFF
/* 3A78498 80084ED0 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 3A7849C 80084ED4 21186200 */  addu       $v1, $v1, $v0
/* 3A784A0 80084ED8 CB89010C */  jal        rand
/* 3A784A4 80084EDC 080023AE */   sw        $v1, 0x8($s1)
/* 3A784A8 80084EE0 CB89010C */  jal        rand
/* 3A784AC 80084EE4 440062A2 */   sb        $v0, 0x44($s3)
/* 3A784B0 80084EE8 CB89010C */  jal        rand
/* 3A784B4 80084EEC 450062A2 */   sb        $v0, 0x45($s3)
/* 3A784B8 80084EF0 CB89010C */  jal        rand
/* 3A784BC 80084EF4 460062A2 */   sb        $v0, 0x46($s3)
/* 3A784C0 80084EF8 0F004230 */  andi       $v0, $v0, 0xF
/* 3A784C4 80084EFC CB89010C */  jal        rand
/* 3A784C8 80084F00 100022A2 */   sb        $v0, 0x10($s1)
/* 3A784CC 80084F04 0F004230 */  andi       $v0, $v0, 0xF
/* 3A784D0 80084F08 CB89010C */  jal        rand
/* 3A784D4 80084F0C 110022A2 */   sb        $v0, 0x11($s1)
/* 3A784D8 80084F10 0F004230 */  andi       $v0, $v0, 0xF
/* 3A784DC 80084F14 120022A2 */  sb         $v0, 0x12($s1)
/* 3A784E0 80084F18 1400A28E */  lw         $v0, 0x14($s5)
/* 3A784E4 80084F1C CB89010C */  jal        rand
/* 3A784E8 80084F20 0C0022AE */   sw        $v0, 0xC($s1)
/* 3A784EC 80084F24 03004230 */  andi       $v0, $v0, 0x3
/* 3A784F0 80084F28 10004224 */  addiu      $v0, $v0, 0x10
/* 3A784F4 80084F2C 16140208 */  j          .Llevel_42_80085058
/* 3A784F8 80084F30 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_42_80084F34:
/* 3A784FC 80084F34 0000708E */  lw         $s0, 0x0($s3)
/* 3A78500 80084F38 C8E9000C */  jal        func_8003A720
/* 3A78504 80084F3C 21206002 */   addu      $a0, $s3, $zero
/* 3A78508 80084F40 734A010C */  jal        func_800529CC
/* 3A7850C 80084F44 21206002 */   addu      $a0, $s3, $zero
/* 3A78510 80084F48 02000224 */  addiu      $v0, $zero, 0x2
/* 3A78514 80084F4C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 3A78518 80084F50 40000224 */  addiu      $v0, $zero, 0x40
/* 3A7851C 80084F54 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 3A78520 80084F58 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 3A78524 80084F5C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 3A78528 80084F60 16140208 */  j          .Llevel_42_80085058
/* 3A7852C 80084F64 000002AE */   sw        $v0, 0x0($s0)
.Llevel_42_80084F68:
/* 3A78530 80084F68 C8E9000C */  jal        func_8003A720
/* 3A78534 80084F6C 21206002 */   addu      $a0, $s3, $zero
/* 3A78538 80084F70 05000224 */  addiu      $v0, $zero, 0x5
/* 3A7853C 80084F74 3100A012 */  beqz       $s5, .Llevel_42_8008503C
/* 3A78540 80084F78 470062A2 */   sb        $v0, 0x47($s3)
/* 3A78544 80084F7C 0C006426 */  addiu      $a0, $s3, 0xC
/* 3A78548 80084F80 12140208 */  j          .Llevel_42_80085048
/* 3A7854C 80084F84 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_42_80084F88:
/* 3A78550 80084F88 C8E9000C */  jal        func_8003A720
/* 3A78554 80084F8C 21206002 */   addu      $a0, $s3, $zero
/* 3A78558 80084F90 0300A012 */  beqz       $s5, .Llevel_42_80084FA0
/* 3A7855C 80084F94 0C006426 */   addiu     $a0, $s3, 0xC
/* 3A78560 80084F98 EA130208 */  j          .Llevel_42_80084FA8
/* 3A78564 80084F9C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_42_80084FA0:
/* 3A78568 80084FA0 0880053C */  lui        $a1, %hi(g_Spyro)
/* 3A7856C 80084FA4 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_42_80084FA8:
/* 3A78570 80084FA8 C05D000C */  jal        VecCopy
/* 3A78574 80084FAC 00000000 */   nop
/* 3A78578 80084FB0 0C006426 */  addiu      $a0, $s3, 0xC
/* 3A7857C 80084FB4 1400628E */  lw         $v0, 0x14($s3)
/* 3A78580 80084FB8 00080524 */  addiu      $a1, $zero, 0x800
/* 3A78584 80084FBC 00024224 */  addiu      $v0, $v0, 0x200
/* 3A78588 80084FC0 7B35010C */  jal        func_8004D5EC
/* 3A7858C 80084FC4 140062AE */   sw        $v0, 0x14($s3)
/* 3A78590 80084FC8 1400648E */  lw         $a0, 0x14($s3)
/* 3A78594 80084FCC 21184000 */  addu       $v1, $v0, $zero
/* 3A78598 80084FD0 23106400 */  subu       $v0, $v1, $a0
/* 3A7859C 80084FD4 02004104 */  bgez       $v0, .Llevel_42_80084FE0
/* 3A785A0 80084FD8 00000000 */   nop
/* 3A785A4 80084FDC 23100200 */  negu       $v0, $v0
.Llevel_42_80084FE0:
/* 3A785A8 80084FE0 00084228 */  slti       $v0, $v0, 0x800
/* 3A785AC 80084FE4 03004010 */  beqz       $v0, .Llevel_42_80084FF4
/* 3A785B0 80084FE8 00FE8224 */   addiu     $v0, $a0, -0x200
/* 3A785B4 80084FEC 14140208 */  j          .Llevel_42_80085050
/* 3A785B8 80084FF0 140063AE */   sw        $v1, 0x14($s3)
.Llevel_42_80084FF4:
/* 3A785BC 80084FF4 14140208 */  j          .Llevel_42_80085050
/* 3A785C0 80084FF8 140062AE */   sw        $v0, 0x14($s3)
.Llevel_42_80084FFC:
/* 3A785C4 80084FFC C8E9000C */  jal        func_8003A720
/* 3A785C8 80085000 21206002 */   addu      $a0, $s3, $zero
/* 3A785CC 80085004 21206002 */  addu       $a0, $s3, $zero
/* 3A785D0 80085008 20000224 */  addiu      $v0, $zero, 0x20
/* 3A785D4 8008500C 500062A2 */  sb         $v0, 0x50($s3)
/* 3A785D8 80085010 FF000224 */  addiu      $v0, $zero, 0xFF
/* 3A785DC 80085014 734A010C */  jal        func_800529CC
/* 3A785E0 80085018 520062A2 */   sb        $v0, 0x52($s3)
/* 3A785E4 8008501C 17140208 */  j          .Llevel_42_8008505C
/* 3A785E8 80085020 21106002 */   addu      $v0, $s3, $zero
.Llevel_42_80085024:
/* 3A785EC 80085024 C8E9000C */  jal        func_8003A720
/* 3A785F0 80085028 21206002 */   addu      $a0, $s3, $zero
/* 3A785F4 8008502C 0300A012 */  beqz       $s5, .Llevel_42_8008503C
/* 3A785F8 80085030 0C00A526 */   addiu     $a1, $s5, 0xC
/* 3A785FC 80085034 12140208 */  j          .Llevel_42_80085048
/* 3A78600 80085038 0C006426 */   addiu     $a0, $s3, 0xC
.Llevel_42_8008503C:
/* 3A78604 8008503C 0C006426 */  addiu      $a0, $s3, 0xC
/* 3A78608 80085040 0880053C */  lui        $a1, %hi(g_Spyro)
/* 3A7860C 80085044 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_42_80085048:
/* 3A78610 80085048 C05D000C */  jal        VecCopy
/* 3A78614 8008504C 00000000 */   nop
.Llevel_42_80085050:
/* 3A78618 80085050 AA49010C */  jal        func_800526A8
/* 3A7861C 80085054 21206002 */   addu      $a0, $s3, $zero
.Llevel_42_80085058:
/* 3A78620 80085058 21106002 */  addu       $v0, $s3, $zero
.Llevel_42_8008505C:
/* 3A78624 8008505C 5000BF8F */  lw         $ra, 0x50($sp)
/* 3A78628 80085060 4C00B58F */  lw         $s5, 0x4C($sp)
/* 3A7862C 80085064 4800B48F */  lw         $s4, 0x48($sp)
/* 3A78630 80085068 4400B38F */  lw         $s3, 0x44($sp)
/* 3A78634 8008506C 4000B28F */  lw         $s2, 0x40($sp)
/* 3A78638 80085070 3C00B18F */  lw         $s1, 0x3C($sp)
/* 3A7863C 80085074 3800B08F */  lw         $s0, 0x38($sp)
/* 3A78640 80085078 5800BD27 */  addiu      $sp, $sp, 0x58
/* 3A78644 8008507C 0800E003 */  jr         $ra
/* 3A78648 80085080 00000000 */   nop
.size func_level_42_80084718, . - func_level_42_80084718
