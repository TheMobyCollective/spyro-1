.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_41_8008465C
/* 37FC424 8008465C A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 37FC428 80084660 3800B0AF */  sw         $s0, 0x38($sp)
/* 37FC42C 80084664 21808000 */  addu       $s0, $a0, $zero
/* 37FC430 80084668 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 37FC434 8008466C 21A8A000 */  addu       $s5, $a1, $zero
/* 37FC438 80084670 5000BFAF */  sw         $ra, 0x50($sp)
/* 37FC43C 80084674 4800B4AF */  sw         $s4, 0x48($sp)
/* 37FC440 80084678 4400B3AF */  sw         $s3, 0x44($sp)
/* 37FC444 8008467C 4000B2AF */  sw         $s2, 0x40($sp)
/* 37FC448 80084680 3149010C */  jal        func_800524C4
/* 37FC44C 80084684 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 37FC450 80084688 21984000 */  addu       $s3, $v0, $zero
/* 37FC454 8008468C 1400A012 */  beqz       $s5, .Llevel_41_800846E0
/* 37FC458 80084690 360070A6 */   sh        $s0, 0x36($s3)
/* 37FC45C 80084694 0780043C */  lui        $a0, %hi(D_80075828)
/* 37FC460 80084698 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 37FC464 8008469C 00000000 */  nop
/* 37FC468 800846A0 2320A402 */  subu       $a0, $s5, $a0
/* 37FC46C 800846A4 40190400 */  sll        $v1, $a0, 5
/* 37FC470 800846A8 23186400 */  subu       $v1, $v1, $a0
/* 37FC474 800846AC 40190300 */  sll        $v1, $v1, 5
/* 37FC478 800846B0 21186400 */  addu       $v1, $v1, $a0
/* 37FC47C 800846B4 C0100300 */  sll        $v0, $v1, 3
/* 37FC480 800846B8 21186200 */  addu       $v1, $v1, $v0
/* 37FC484 800846BC C0130300 */  sll        $v0, $v1, 15
/* 37FC488 800846C0 23104300 */  subu       $v0, $v0, $v1
/* 37FC48C 800846C4 80100200 */  sll        $v0, $v0, 2
/* 37FC490 800846C8 21104400 */  addu       $v0, $v0, $a0
/* 37FC494 800846CC 23100200 */  negu       $v0, $v0
/* 37FC498 800846D0 C3180200 */  sra        $v1, $v0, 3
/* 37FC49C 800846D4 0001622C */  sltiu      $v0, $v1, 0x100
/* 37FC4A0 800846D8 03004014 */  bnez       $v0, .Llevel_41_800846E8
/* 37FC4A4 800846DC 0201022A */   slti      $v0, $s0, 0x102
.Llevel_41_800846E0:
/* 37FC4A8 800846E0 21180000 */  addu       $v1, $zero, $zero
/* 37FC4AC 800846E4 0201022A */  slti       $v0, $s0, 0x102
.Llevel_41_800846E8:
/* 37FC4B0 800846E8 36004010 */  beqz       $v0, .Llevel_41_800847C4
/* 37FC4B4 800846EC 560063A2 */   sb        $v1, 0x56($s3)
/* 37FC4B8 800846F0 FF00022A */  slti       $v0, $s0, 0xFF
/* 37FC4BC 800846F4 EF014010 */  beqz       $v0, .Llevel_41_80084EB4
/* 37FC4C0 800846F8 4600022A */   slti      $v0, $s0, 0x46
/* 37FC4C4 800846FC 14004010 */  beqz       $v0, .Llevel_41_80084750
/* 37FC4C8 80084700 4300022A */   slti      $v0, $s0, 0x43
/* 37FC4CC 80084704 EB014010 */  beqz       $v0, .Llevel_41_80084EB4
/* 37FC4D0 80084708 10000224 */   addiu     $v0, $zero, 0x10
/* 37FC4D4 8008470C 80000212 */  beq        $s0, $v0, .Llevel_41_80084910
/* 37FC4D8 80084710 1100022A */   slti      $v0, $s0, 0x11
/* 37FC4DC 80084714 07004010 */  beqz       $v0, .Llevel_41_80084734
/* 37FC4E0 80084718 0E000224 */   addiu     $v0, $zero, 0xE
/* 37FC4E4 8008471C B3000212 */  beq        $s0, $v0, .Llevel_41_800849EC
/* 37FC4E8 80084720 0F000224 */   addiu     $v0, $zero, 0xF
/* 37FC4EC 80084724 53000212 */  beq        $s0, $v0, .Llevel_41_80084874
/* 37FC4F0 80084728 00000000 */   nop
/* 37FC4F4 8008472C D2140208 */  j          .Llevel_41_80085348
/* 37FC4F8 80084730 00000000 */   nop
.Llevel_41_80084734:
/* 37FC4FC 80084734 20000224 */  addiu      $v0, $zero, 0x20
/* 37FC500 80084738 89000212 */  beq        $s0, $v0, .Llevel_41_80084960
/* 37FC504 8008473C 22000224 */   addiu     $v0, $zero, 0x22
/* 37FC508 80084740 9C000212 */  beq        $s0, $v0, .Llevel_41_800849B4
/* 37FC50C 80084744 00000000 */   nop
/* 37FC510 80084748 D2140208 */  j          .Llevel_41_80085348
/* 37FC514 8008474C 00000000 */   nop
.Llevel_41_80084750:
/* 37FC518 80084750 5D000224 */  addiu      $v0, $zero, 0x5D
/* 37FC51C 80084754 FB000212 */  beq        $s0, $v0, .Llevel_41_80084B44
/* 37FC520 80084758 5E00022A */   slti      $v0, $s0, 0x5E
/* 37FC524 8008475C 0B004010 */  beqz       $v0, .Llevel_41_8008478C
/* 37FC528 80084760 4C000224 */   addiu     $v0, $zero, 0x4C
/* 37FC52C 80084764 EE020212 */  beq        $s0, $v0, .Llevel_41_80085320
/* 37FC530 80084768 4C00022A */   slti      $v0, $s0, 0x4C
/* 37FC534 8008476C F6024014 */  bnez       $v0, .Llevel_41_80085348
/* 37FC538 80084770 5800022A */   slti      $v0, $s0, 0x58
/* 37FC53C 80084774 F4024010 */  beqz       $v0, .Llevel_41_80085348
/* 37FC540 80084778 5300022A */   slti      $v0, $s0, 0x53
/* 37FC544 8008477C 9B004010 */  beqz       $v0, .Llevel_41_800849EC
/* 37FC548 80084780 00000000 */   nop
/* 37FC54C 80084784 D2140208 */  j          .Llevel_41_80085348
/* 37FC550 80084788 00000000 */   nop
.Llevel_41_8008478C:
/* 37FC554 8008478C EA000224 */  addiu      $v0, $zero, 0xEA
/* 37FC558 80084790 B8010212 */  beq        $s0, $v0, .Llevel_41_80084E74
/* 37FC55C 80084794 EB00022A */   slti      $v0, $s0, 0xEB
/* 37FC560 80084798 05004010 */  beqz       $v0, .Llevel_41_800847B0
/* 37FC564 8008479C 78000224 */   addiu     $v0, $zero, 0x78
/* 37FC568 800847A0 A2010212 */  beq        $s0, $v0, .Llevel_41_80084E2C
/* 37FC56C 800847A4 00000000 */   nop
/* 37FC570 800847A8 D2140208 */  j          .Llevel_41_80085348
/* 37FC574 800847AC 00000000 */   nop
.Llevel_41_800847B0:
/* 37FC578 800847B0 FB000224 */  addiu      $v0, $zero, 0xFB
/* 37FC57C 800847B4 2A020212 */  beq        $s0, $v0, .Llevel_41_80085060
/* 37FC580 800847B8 00000000 */   nop
/* 37FC584 800847BC D2140208 */  j          .Llevel_41_80085348
/* 37FC588 800847C0 00000000 */   nop
.Llevel_41_800847C4:
/* 37FC58C 800847C4 57010224 */  addiu      $v0, $zero, 0x157
/* 37FC590 800847C8 A2020212 */  beq        $s0, $v0, .Llevel_41_80085254
/* 37FC594 800847CC 5801022A */   slti      $v0, $s0, 0x158
/* 37FC598 800847D0 14004010 */  beqz       $v0, .Llevel_41_80084824
/* 37FC59C 800847D4 15010224 */   addiu     $v0, $zero, 0x115
/* 37FC5A0 800847D8 91020212 */  beq        $s0, $v0, .Llevel_41_80085220
/* 37FC5A4 800847DC 1601022A */   slti      $v0, $s0, 0x116
/* 37FC5A8 800847E0 07004010 */  beqz       $v0, .Llevel_41_80084800
/* 37FC5AC 800847E4 0E01022A */   slti      $v0, $s0, 0x10E
/* 37FC5B0 800847E8 D7024010 */  beqz       $v0, .Llevel_41_80085348
/* 37FC5B4 800847EC 0401022A */   slti      $v0, $s0, 0x104
/* 37FC5B8 800847F0 8B024010 */  beqz       $v0, .Llevel_41_80085220
/* 37FC5BC 800847F4 00000000 */   nop
/* 37FC5C0 800847F8 D2140208 */  j          .Llevel_41_80085348
/* 37FC5C4 800847FC 00000000 */   nop
.Llevel_41_80084800:
/* 37FC5C8 80084800 3501022A */  slti       $v0, $s0, 0x135
/* 37FC5CC 80084804 D0024014 */  bnez       $v0, .Llevel_41_80085348
/* 37FC5D0 80084808 3801022A */   slti      $v0, $s0, 0x138
/* 37FC5D4 8008480C A9014014 */  bnez       $v0, .Llevel_41_80084EB4
/* 37FC5D8 80084810 47010224 */   addiu     $v0, $zero, 0x147
/* 37FC5DC 80084814 82020212 */  beq        $s0, $v0, .Llevel_41_80085220
/* 37FC5E0 80084818 00000000 */   nop
/* 37FC5E4 8008481C D2140208 */  j          .Llevel_41_80085348
/* 37FC5E8 80084820 00000000 */   nop
.Llevel_41_80084824:
/* 37FC5EC 80084824 C401022A */  slti       $v0, $s0, 0x1C4
/* 37FC5F0 80084828 0B004010 */  beqz       $v0, .Llevel_41_80084858
/* 37FC5F4 8008482C AA01022A */   slti      $v0, $s0, 0x1AA
/* 37FC5F8 80084830 BB024010 */  beqz       $v0, .Llevel_41_80085320
/* 37FC5FC 80084834 88010224 */   addiu     $v0, $zero, 0x188
/* 37FC600 80084838 94020212 */  beq        $s0, $v0, .Llevel_41_8008528C
/* 37FC604 8008483C 8801022A */   slti      $v0, $s0, 0x188
/* 37FC608 80084840 C1024014 */  bnez       $v0, .Llevel_41_80085348
/* 37FC60C 80084844 A701022A */   slti      $v0, $s0, 0x1A7
/* 37FC610 80084848 9A014010 */  beqz       $v0, .Llevel_41_80084EB4
/* 37FC614 8008484C 00000000 */   nop
/* 37FC618 80084850 D2140208 */  j          .Llevel_41_80085348
/* 37FC61C 80084854 00000000 */   nop
.Llevel_41_80084858:
/* 37FC620 80084858 FD01022A */  slti       $v0, $s0, 0x1FD
/* 37FC624 8008485C BA024010 */  beqz       $v0, .Llevel_41_80085348
/* 37FC628 80084860 FB01022A */   slti      $v0, $s0, 0x1FB
/* 37FC62C 80084864 91024010 */  beqz       $v0, .Llevel_41_800852AC
/* 37FC630 80084868 00000000 */   nop
/* 37FC634 8008486C D2140208 */  j          .Llevel_41_80085348
/* 37FC638 80084870 00000000 */   nop
.Llevel_41_80084874:
/* 37FC63C 80084874 0000708E */  lw         $s0, 0x0($s3)
/* 37FC640 80084878 C8E9000C */  jal        func_8003A720
/* 37FC644 8008487C 21206002 */   addu      $a0, $s3, $zero
/* 37FC648 80084880 8C000224 */  addiu      $v0, $zero, 0x8C
/* 37FC64C 80084884 080002AE */  sw         $v0, 0x8($s0)
/* 37FC650 80084888 03000224 */  addiu      $v0, $zero, 0x3
/* 37FC654 8008488C 100002A2 */  sb         $v0, 0x10($s0)
/* 37FC658 80084890 FF000224 */  addiu      $v0, $zero, 0xFF
/* 37FC65C 80084894 140002A2 */  sb         $v0, 0x14($s0)
/* 37FC660 80084898 02000224 */  addiu      $v0, $zero, 0x2
/* 37FC664 8008489C 000000AE */  sw         $zero, 0x0($s0)
/* 37FC668 800848A0 040000AE */  sw         $zero, 0x4($s0)
/* 37FC66C 800848A4 0E0000A2 */  sb         $zero, 0xE($s0)
/* 37FC670 800848A8 0F0000A2 */  sb         $zero, 0xF($s0)
/* 37FC674 800848AC 110000A2 */  sb         $zero, 0x11($s0)
/* 37FC678 800848B0 120000A2 */  sb         $zero, 0x12($s0)
/* 37FC67C 800848B4 130000A2 */  sb         $zero, 0x13($s0)
/* 37FC680 800848B8 490062A2 */  sb         $v0, 0x49($s3)
/* 37FC684 800848BC 18000224 */  addiu      $v0, $zero, 0x18
/* 37FC688 800848C0 500062A2 */  sb         $v0, 0x50($s3)
/* 37FC68C 800848C4 10000224 */  addiu      $v0, $zero, 0x10
/* 37FC690 800848C8 520062A2 */  sb         $v0, 0x52($s3)
/* 37FC694 800848CC 20000224 */  addiu      $v0, $zero, 0x20
/* 37FC698 800848D0 440062A2 */  sb         $v0, 0x44($s3)
/* 37FC69C 800848D4 450060A2 */  sb         $zero, 0x45($s3)
/* 37FC6A0 800848D8 0400A012 */  beqz       $s5, .Llevel_41_800848EC
/* 37FC6A4 800848DC 460060A2 */   sb        $zero, 0x46($s3)
/* 37FC6A8 800848E0 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FC6AC 800848E4 C05D000C */  jal        VecCopy
/* 37FC6B0 800848E8 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_41_800848EC:
/* 37FC6B4 800848EC AA49010C */  jal        func_800526A8
/* 37FC6B8 800848F0 21206002 */   addu      $a0, $s3, $zero
/* 37FC6BC 800848F4 4B006292 */  lbu        $v0, 0x4B($s3)
/* 37FC6C0 800848F8 01000324 */  addiu      $v1, $zero, 0x1
/* 37FC6C4 800848FC 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 37FC6C8 80084900 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 37FC6CC 80084904 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 37FC6D0 80084908 15140208 */  j          .Llevel_41_80085054
/* 37FC6D4 8008490C 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_41_80084910:
/* 37FC6D8 80084910 0000718E */  lw         $s1, 0x0($s3)
/* 37FC6DC 80084914 C8E9000C */  jal        func_8003A720
/* 37FC6E0 80084918 21206002 */   addu      $a0, $s3, $zero
/* 37FC6E4 8008491C AA49010C */  jal        func_800526A8
/* 37FC6E8 80084920 21206002 */   addu      $a0, $s3, $zero
/* 37FC6EC 80084924 0C007026 */  addiu      $s0, $s3, 0xC
/* 37FC6F0 80084928 21200002 */  addu       $a0, $s0, $zero
/* 37FC6F4 8008492C C05D000C */  jal        VecCopy
/* 37FC6F8 80084930 0C00A526 */   addiu     $a1, $s5, 0xC
/* 37FC6FC 80084934 21280002 */  addu       $a1, $s0, $zero
/* 37FC700 80084938 1400628E */  lw         $v0, 0x14($s3)
/* 37FC704 8008493C 04002426 */  addiu      $a0, $s1, 0x4
/* 37FC708 80084940 00024224 */  addiu      $v0, $v0, 0x200
/* 37FC70C 80084944 C05D000C */  jal        VecCopy
/* 37FC710 80084948 140062AE */   sw        $v0, 0x14($s3)
/* 37FC714 8008494C 08070224 */  addiu      $v0, $zero, 0x708
/* 37FC718 80084950 130020A2 */  sb         $zero, 0x13($s1)
/* 37FC71C 80084954 120020A2 */  sb         $zero, 0x12($s1)
/* 37FC720 80084958 E0140208 */  j          .Llevel_41_80085380
/* 37FC724 8008495C 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_41_80084960:
/* 37FC728 80084960 0000708E */  lw         $s0, 0x0($s3)
/* 37FC72C 80084964 C8E9000C */  jal        func_8003A720
/* 37FC730 80084968 21206002 */   addu      $a0, $s3, $zero
/* 37FC734 8008496C 2120A002 */  addu       $a0, $s5, $zero
/* 37FC738 80084970 21280000 */  addu       $a1, $zero, $zero
/* 37FC73C 80084974 0C006626 */  addiu      $a2, $s3, 0xC
/* 37FC740 80084978 594B010C */  jal        func_80052D64
/* 37FC744 8008497C 000004AE */   sw        $a0, 0x0($s0)
/* 37FC748 80084980 AA49010C */  jal        func_800526A8
/* 37FC74C 80084984 21206002 */   addu      $a0, $s3, $zero
/* 37FC750 80084988 0780023C */  lui        $v0, %hi(g_Camera + 0x4E)
/* 37FC754 8008498C 1E6E4294 */  lhu        $v0, %lo(g_Camera + 0x4E)($v0)
/* 37FC758 80084990 00000000 */  nop
/* 37FC75C 80084994 450062A2 */  sb         $v0, 0x45($s3)
/* 37FC760 80084998 0780023C */  lui        $v0, %hi(g_Camera + 0x50)
/* 37FC764 8008499C 206E4284 */  lh         $v0, %lo(g_Camera + 0x50)($v0)
/* 37FC768 800849A0 00000000 */  nop
/* 37FC76C 800849A4 00044224 */  addiu      $v0, $v0, 0x400
/* 37FC770 800849A8 03110200 */  sra        $v0, $v0, 4
/* 37FC774 800849AC E0140208 */  j          .Llevel_41_80085380
/* 37FC778 800849B0 460062A2 */   sb        $v0, 0x46($s3)
.Llevel_41_800849B4:
/* 37FC77C 800849B4 C8E9000C */  jal        func_8003A720
/* 37FC780 800849B8 21206002 */   addu      $a0, $s3, $zero
/* 37FC784 800849BC 20000224 */  addiu      $v0, $zero, 0x20
/* 37FC788 800849C0 500062A2 */  sb         $v0, 0x50($s3)
/* 37FC78C 800849C4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 37FC790 800849C8 0400A012 */  beqz       $s5, .Llevel_41_800849DC
/* 37FC794 800849CC 520062A2 */   sb        $v0, 0x52($s3)
/* 37FC798 800849D0 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FC79C 800849D4 C05D000C */  jal        VecCopy
/* 37FC7A0 800849D8 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_41_800849DC:
/* 37FC7A4 800849DC 734A010C */  jal        func_800529CC
/* 37FC7A8 800849E0 21206002 */   addu      $a0, $s3, $zero
/* 37FC7AC 800849E4 E1140208 */  j          .Llevel_41_80085384
/* 37FC7B0 800849E8 21106002 */   addu      $v0, $s3, $zero
.Llevel_41_800849EC:
/* 37FC7B4 800849EC 0000718E */  lw         $s1, 0x0($s3)
/* 37FC7B8 800849F0 C8E9000C */  jal        func_8003A720
/* 37FC7BC 800849F4 21206002 */   addu      $a0, $s3, $zero
/* 37FC7C0 800849F8 8C000224 */  addiu      $v0, $zero, 0x8C
/* 37FC7C4 800849FC 000020AE */  sw         $zero, 0x0($s1)
/* 37FC7C8 80084A00 040020AE */  sw         $zero, 0x4($s1)
/* 37FC7CC 80084A04 080022AE */  sw         $v0, 0x8($s1)
/* 37FC7D0 80084A08 0E0020A2 */  sb         $zero, 0xE($s1)
/* 37FC7D4 80084A0C 0F0020A2 */  sb         $zero, 0xF($s1)
/* 37FC7D8 80084A10 110020A2 */  sb         $zero, 0x11($s1)
/* 37FC7DC 80084A14 120020A2 */  sb         $zero, 0x12($s1)
/* 37FC7E0 80084A18 130020A2 */  sb         $zero, 0x13($s1)
/* 37FC7E4 80084A1C 3600A386 */  lh         $v1, 0x36($s5)
/* 37FC7E8 80084A20 0D000224 */  addiu      $v0, $zero, 0xD
/* 37FC7EC 80084A24 02006214 */  bne        $v1, $v0, .Llevel_41_80084A30
/* 37FC7F0 80084A28 03000224 */   addiu     $v0, $zero, 0x3
/* 37FC7F4 80084A2C 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_41_80084A30:
/* 37FC7F8 80084A30 100022A2 */  sb         $v0, 0x10($s1)
/* 37FC7FC 80084A34 0C007026 */  addiu      $s0, $s3, 0xC
/* 37FC800 80084A38 21200002 */  addu       $a0, $s0, $zero
/* 37FC804 80084A3C 0C00A526 */  addiu      $a1, $s5, 0xC
/* 37FC808 80084A40 FF000224 */  addiu      $v0, $zero, 0xFF
/* 37FC80C 80084A44 140022A2 */  sb         $v0, 0x14($s1)
/* 37FC810 80084A48 02001124 */  addiu      $s1, $zero, 0x2
/* 37FC814 80084A4C 18000224 */  addiu      $v0, $zero, 0x18
/* 37FC818 80084A50 500062A2 */  sb         $v0, 0x50($s3)
/* 37FC81C 80084A54 40000224 */  addiu      $v0, $zero, 0x40
/* 37FC820 80084A58 520062A2 */  sb         $v0, 0x52($s3)
/* 37FC824 80084A5C 20000224 */  addiu      $v0, $zero, 0x20
/* 37FC828 80084A60 490071A2 */  sb         $s1, 0x49($s3)
/* 37FC82C 80084A64 440062A2 */  sb         $v0, 0x44($s3)
/* 37FC830 80084A68 450060A2 */  sb         $zero, 0x45($s3)
/* 37FC834 80084A6C C05D000C */  jal        VecCopy
/* 37FC838 80084A70 460060A2 */   sb        $zero, 0x46($s3)
/* 37FC83C 80084A74 734A010C */  jal        func_800529CC
/* 37FC840 80084A78 21206002 */   addu      $a0, $s3, $zero
/* 37FC844 80084A7C 1000A427 */  addiu      $a0, $sp, 0x10
/* 37FC848 80084A80 21280002 */  addu       $a1, $s0, $zero
/* 37FC84C 80084A84 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 37FC850 80084A88 C05D000C */  jal        VecCopy
/* 37FC854 80084A8C 1C0062AE */   sw        $v0, 0x1C($s3)
/* 37FC858 80084A90 1000A427 */  addiu      $a0, $sp, 0x10
/* 37FC85C 80084A94 1800A28F */  lw         $v0, 0x18($sp)
/* 37FC860 80084A98 0100053C */  lui        $a1, (0x10000 >> 16)
/* 37FC864 80084A9C 00044224 */  addiu      $v0, $v0, 0x400
/* 37FC868 80084AA0 7B35010C */  jal        func_8004D5EC
/* 37FC86C 80084AA4 1800A2AF */   sw        $v0, 0x18($sp)
/* 37FC870 80084AA8 F44C010C */  jal        func_800533D0
/* 37FC874 80084AAC 21206002 */   addu      $a0, $s3, $zero
/* 37FC878 80084AB0 36006386 */  lh         $v1, 0x36($s3)
/* 37FC87C 80084AB4 0E000224 */  addiu      $v0, $zero, 0xE
/* 37FC880 80084AB8 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 37FC884 80084ABC 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 37FC888 80084AC0 03006214 */  bne        $v1, $v0, .Llevel_41_80084AD0
/* 37FC88C 80084AC4 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 37FC890 80084AC8 0C000224 */  addiu      $v0, $zero, 0xC
/* 37FC894 80084ACC 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_41_80084AD0:
/* 37FC898 80084AD0 36006386 */  lh         $v1, 0x36($s3)
/* 37FC89C 80084AD4 53000224 */  addiu      $v0, $zero, 0x53
/* 37FC8A0 80084AD8 05006214 */  bne        $v1, $v0, .Llevel_41_80084AF0
/* 37FC8A4 80084ADC 54000224 */   addiu     $v0, $zero, 0x54
/* 37FC8A8 80084AE0 01000224 */  addiu      $v0, $zero, 0x1
/* 37FC8AC 80084AE4 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 37FC8B0 80084AE8 36006386 */  lh         $v1, 0x36($s3)
/* 37FC8B4 80084AEC 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_41_80084AF0:
/* 37FC8B8 80084AF0 02006214 */  bne        $v1, $v0, .Llevel_41_80084AFC
/* 37FC8BC 80084AF4 00000000 */   nop
/* 37FC8C0 80084AF8 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_41_80084AFC:
/* 37FC8C4 80084AFC 36006386 */  lh         $v1, 0x36($s3)
/* 37FC8C8 80084B00 55000224 */  addiu      $v0, $zero, 0x55
/* 37FC8CC 80084B04 05006214 */  bne        $v1, $v0, .Llevel_41_80084B1C
/* 37FC8D0 80084B08 56000224 */   addiu     $v0, $zero, 0x56
/* 37FC8D4 80084B0C 03000224 */  addiu      $v0, $zero, 0x3
/* 37FC8D8 80084B10 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 37FC8DC 80084B14 36006386 */  lh         $v1, 0x36($s3)
/* 37FC8E0 80084B18 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_41_80084B1C:
/* 37FC8E4 80084B1C 02006214 */  bne        $v1, $v0, .Llevel_41_80084B28
/* 37FC8E8 80084B20 04000224 */   addiu     $v0, $zero, 0x4
/* 37FC8EC 80084B24 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_41_80084B28:
/* 37FC8F0 80084B28 36006386 */  lh         $v1, 0x36($s3)
/* 37FC8F4 80084B2C 57000224 */  addiu      $v0, $zero, 0x57
/* 37FC8F8 80084B30 14026214 */  bne        $v1, $v0, .Llevel_41_80085384
/* 37FC8FC 80084B34 21106002 */   addu      $v0, $s3, $zero
/* 37FC900 80084B38 05000224 */  addiu      $v0, $zero, 0x5
/* 37FC904 80084B3C E0140208 */  j          .Llevel_41_80085380
/* 37FC908 80084B40 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_41_80084B44:
/* 37FC90C 80084B44 0000718E */  lw         $s1, 0x0($s3)
/* 37FC910 80084B48 C8E9000C */  jal        func_8003A720
/* 37FC914 80084B4C 21206002 */   addu      $a0, $s3, $zero
/* 37FC918 80084B50 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FC91C 80084B54 0C00A526 */  addiu      $a1, $s5, 0xC
/* 37FC920 80084B58 20000224 */  addiu      $v0, $zero, 0x20
/* 37FC924 80084B5C C05D000C */  jal        VecCopy
/* 37FC928 80084B60 500062A2 */   sb        $v0, 0x50($s3)
/* 37FC92C 80084B64 AA49010C */  jal        func_800526A8
/* 37FC930 80084B68 21206002 */   addu      $a0, $s3, $zero
/* 37FC934 80084B6C 3600A386 */  lh         $v1, 0x36($s5)
/* 37FC938 80084B70 23000224 */  addiu      $v0, $zero, 0x23
/* 37FC93C 80084B74 45006214 */  bne        $v1, $v0, .Llevel_41_80084C8C
/* 37FC940 80084B78 CEFF0424 */   addiu     $a0, $zero, -0x32
/* 37FC944 80084B7C 0000B08E */  lw         $s0, 0x0($s5)
/* 37FC948 80084B80 A8DF000C */  jal        RandRange
/* 37FC94C 80084B84 32000524 */   addiu     $a1, $zero, 0x32
/* 37FC950 80084B88 0C00038E */  lw         $v1, 0xC($s0)
/* 37FC954 80084B8C 00000000 */  nop
/* 37FC958 80084B90 21186200 */  addu       $v1, $v1, $v0
/* 37FC95C 80084B94 FF006330 */  andi       $v1, $v1, 0xFF
/* 37FC960 80084B98 CB89010C */  jal        rand
/* 37FC964 80084B9C 00A10300 */   sll       $s4, $v1, 4
/* 37FC968 80084BA0 FF075230 */  andi       $s2, $v0, 0x7FF
/* 37FC96C 80084BA4 2C5B000C */  jal        Cos
/* 37FC970 80084BA8 21204002 */   addu      $a0, $s2, $zero
/* 37FC974 80084BAC 03110200 */  sra        $v0, $v0, 4
/* 37FC978 80084BB0 05004018 */  blez       $v0, .Llevel_41_80084BC8
/* 37FC97C 80084BB4 00000000 */   nop
/* 37FC980 80084BB8 2C5B000C */  jal        Cos
/* 37FC984 80084BBC 21204002 */   addu      $a0, $s2, $zero
/* 37FC988 80084BC0 F6120208 */  j          .Llevel_41_80084BD8
/* 37FC98C 80084BC4 03810200 */   sra       $s0, $v0, 4
.Llevel_41_80084BC8:
/* 37FC990 80084BC8 2C5B000C */  jal        Cos
/* 37FC994 80084BCC 21204002 */   addu      $a0, $s2, $zero
/* 37FC998 80084BD0 03110200 */  sra        $v0, $v0, 4
/* 37FC99C 80084BD4 23800200 */  negu       $s0, $v0
.Llevel_41_80084BD8:
/* 37FC9A0 80084BD8 2C5B000C */  jal        Cos
/* 37FC9A4 80084BDC 21208002 */   addu      $a0, $s4, $zero
/* 37FC9A8 80084BE0 18000202 */  mult       $s0, $v0
/* 37FC9AC 80084BE4 21208002 */  addu       $a0, $s4, $zero
/* 37FC9B0 80084BE8 12380000 */  mflo       $a3
/* 37FC9B4 80084BEC 03130700 */  sra        $v0, $a3, 12
/* 37FC9B8 80084BF0 165B000C */  jal        Sin
/* 37FC9BC 80084BF4 000022A6 */   sh        $v0, 0x0($s1)
/* 37FC9C0 80084BF8 18000202 */  mult       $s0, $v0
/* 37FC9C4 80084BFC 21204002 */  addu       $a0, $s2, $zero
/* 37FC9C8 80084C00 12380000 */  mflo       $a3
/* 37FC9CC 80084C04 03130700 */  sra        $v0, $a3, 12
/* 37FC9D0 80084C08 165B000C */  jal        Sin
/* 37FC9D4 80084C0C 020022A6 */   sh        $v0, 0x2($s1)
/* 37FC9D8 80084C10 23000424 */  addiu      $a0, $zero, 0x23
/* 37FC9DC 80084C14 32000524 */  addiu      $a1, $zero, 0x32
/* 37FC9E0 80084C18 03110200 */  sra        $v0, $v0, 4
/* 37FC9E4 80084C1C A8DF000C */  jal        RandRange
/* 37FC9E8 80084C20 040022A6 */   sh        $v0, 0x4($s1)
/* 37FC9EC 80084C24 06000424 */  addiu      $a0, $zero, 0x6
/* 37FC9F0 80084C28 14000524 */  addiu      $a1, $zero, 0x14
/* 37FC9F4 80084C2C A8DF000C */  jal        RandRange
/* 37FC9F8 80084C30 0C0022AE */   sw        $v0, 0xC($s1)
/* 37FC9FC 80084C34 20000324 */  addiu      $v1, $zero, 0x20
/* 37FCA00 80084C38 23186200 */  subu       $v1, $v1, $v0
/* 37FCA04 80084C3C 570063A2 */  sb         $v1, 0x57($s3)
/* 37FCA08 80084C40 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 37FCA0C 80084C44 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 37FCA10 80084C48 00002396 */  lhu        $v1, 0x0($s1)
/* 37FCA14 80084C4C 83110200 */  sra        $v0, $v0, 6
/* 37FCA18 80084C50 21186200 */  addu       $v1, $v1, $v0
/* 37FCA1C 80084C54 000023A6 */  sh         $v1, 0x0($s1)
/* 37FCA20 80084C58 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 37FCA24 80084C5C 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 37FCA28 80084C60 02002396 */  lhu        $v1, 0x2($s1)
/* 37FCA2C 80084C64 83110200 */  sra        $v0, $v0, 6
/* 37FCA30 80084C68 21186200 */  addu       $v1, $v1, $v0
/* 37FCA34 80084C6C 020023A6 */  sh         $v1, 0x2($s1)
/* 37FCA38 80084C70 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 37FCA3C 80084C74 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 37FCA40 80084C78 04002396 */  lhu        $v1, 0x4($s1)
/* 37FCA44 80084C7C 83110200 */  sra        $v0, $v0, 6
/* 37FCA48 80084C80 21186200 */  addu       $v1, $v1, $v0
/* 37FCA4C 80084C84 5D130208 */  j          .Llevel_41_80084D74
/* 37FCA50 80084C88 040023A6 */   sh        $v1, 0x4($s1)
.Llevel_41_80084C8C:
/* 37FCA54 80084C8C CB89010C */  jal        rand
/* 37FCA58 80084C90 00000000 */   nop
/* 37FCA5C 80084C94 CB89010C */  jal        rand
/* 37FCA60 80084C98 FF0F5430 */   andi      $s4, $v0, 0xFFF
/* 37FCA64 80084C9C FF075230 */  andi       $s2, $v0, 0x7FF
/* 37FCA68 80084CA0 2C5B000C */  jal        Cos
/* 37FCA6C 80084CA4 21204002 */   addu      $a0, $s2, $zero
/* 37FCA70 80084CA8 21208002 */  addu       $a0, $s4, $zero
/* 37FCA74 80084CAC 2C5B000C */  jal        Cos
/* 37FCA78 80084CB0 21804000 */   addu      $s0, $v0, $zero
/* 37FCA7C 80084CB4 43811000 */  sra        $s0, $s0, 5
/* 37FCA80 80084CB8 18000202 */  mult       $s0, $v0
/* 37FCA84 80084CBC 21204002 */  addu       $a0, $s2, $zero
/* 37FCA88 80084CC0 12380000 */  mflo       $a3
/* 37FCA8C 80084CC4 03130700 */  sra        $v0, $a3, 12
/* 37FCA90 80084CC8 2C5B000C */  jal        Cos
/* 37FCA94 80084CCC 000022A6 */   sh        $v0, 0x0($s1)
/* 37FCA98 80084CD0 21208002 */  addu       $a0, $s4, $zero
/* 37FCA9C 80084CD4 165B000C */  jal        Sin
/* 37FCAA0 80084CD8 21804000 */   addu      $s0, $v0, $zero
/* 37FCAA4 80084CDC 43811000 */  sra        $s0, $s0, 5
/* 37FCAA8 80084CE0 18000202 */  mult       $s0, $v0
/* 37FCAAC 80084CE4 21204002 */  addu       $a0, $s2, $zero
/* 37FCAB0 80084CE8 12380000 */  mflo       $a3
/* 37FCAB4 80084CEC 03130700 */  sra        $v0, $a3, 12
/* 37FCAB8 80084CF0 165B000C */  jal        Sin
/* 37FCABC 80084CF4 020022A6 */   sh        $v0, 0x2($s1)
/* 37FCAC0 80084CF8 43110200 */  sra        $v0, $v0, 5
/* 37FCAC4 80084CFC 040022A6 */  sh         $v0, 0x4($s1)
/* 37FCAC8 80084D00 1800A28E */  lw         $v0, 0x18($s5)
/* 37FCACC 80084D04 0200033C */  lui        $v1, (0x20000 >> 16)
/* 37FCAD0 80084D08 24104300 */  and        $v0, $v0, $v1
/* 37FCAD4 80084D0C 13004010 */  beqz       $v0, .Llevel_41_80084D5C
/* 37FCAD8 80084D10 00000000 */   nop
/* 37FCADC 80084D14 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 37FCAE0 80084D18 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 37FCAE4 80084D1C 00002396 */  lhu        $v1, 0x0($s1)
/* 37FCAE8 80084D20 83110200 */  sra        $v0, $v0, 6
/* 37FCAEC 80084D24 21186200 */  addu       $v1, $v1, $v0
/* 37FCAF0 80084D28 000023A6 */  sh         $v1, 0x0($s1)
/* 37FCAF4 80084D2C 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 37FCAF8 80084D30 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 37FCAFC 80084D34 02002396 */  lhu        $v1, 0x2($s1)
/* 37FCB00 80084D38 83110200 */  sra        $v0, $v0, 6
/* 37FCB04 80084D3C 21186200 */  addu       $v1, $v1, $v0
/* 37FCB08 80084D40 020023A6 */  sh         $v1, 0x2($s1)
/* 37FCB0C 80084D44 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 37FCB10 80084D48 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 37FCB14 80084D4C 04002396 */  lhu        $v1, 0x4($s1)
/* 37FCB18 80084D50 83110200 */  sra        $v0, $v0, 6
/* 37FCB1C 80084D54 21186200 */  addu       $v1, $v1, $v0
/* 37FCB20 80084D58 040023A6 */  sh         $v1, 0x4($s1)
.Llevel_41_80084D5C:
/* 37FCB24 80084D5C CB89010C */  jal        rand
/* 37FCB28 80084D60 00000000 */   nop
/* 37FCB2C 80084D64 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCB30 80084D68 40000324 */  addiu      $v1, $zero, 0x40
/* 37FCB34 80084D6C 23186200 */  subu       $v1, $v1, $v0
/* 37FCB38 80084D70 0C0023AE */  sw         $v1, 0xC($s1)
.Llevel_41_80084D74:
/* 37FCB3C 80084D74 00002286 */  lh         $v0, 0x0($s1)
/* 37FCB40 80084D78 0C00638E */  lw         $v1, 0xC($s3)
/* 37FCB44 80084D7C 80100200 */  sll        $v0, $v0, 2
/* 37FCB48 80084D80 21186200 */  addu       $v1, $v1, $v0
/* 37FCB4C 80084D84 0C0063AE */  sw         $v1, 0xC($s3)
/* 37FCB50 80084D88 02002286 */  lh         $v0, 0x2($s1)
/* 37FCB54 80084D8C 1000638E */  lw         $v1, 0x10($s3)
/* 37FCB58 80084D90 80100200 */  sll        $v0, $v0, 2
/* 37FCB5C 80084D94 21186200 */  addu       $v1, $v1, $v0
/* 37FCB60 80084D98 100063AE */  sw         $v1, 0x10($s3)
/* 37FCB64 80084D9C 04002286 */  lh         $v0, 0x4($s1)
/* 37FCB68 80084DA0 1400638E */  lw         $v1, 0x14($s3)
/* 37FCB6C 80084DA4 80100200 */  sll        $v0, $v0, 2
/* 37FCB70 80084DA8 21186200 */  addu       $v1, $v1, $v0
/* 37FCB74 80084DAC CB89010C */  jal        rand
/* 37FCB78 80084DB0 140063AE */   sw        $v1, 0x14($s3)
/* 37FCB7C 80084DB4 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCB80 80084DB8 CB89010C */  jal        rand
/* 37FCB84 80084DBC 060022A6 */   sh        $v0, 0x6($s1)
/* 37FCB88 80084DC0 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCB8C 80084DC4 CB89010C */  jal        rand
/* 37FCB90 80084DC8 080022A6 */   sh        $v0, 0x8($s1)
/* 37FCB94 80084DCC 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCB98 80084DD0 0A0022A6 */  sh         $v0, 0xA($s1)
/* 37FCB9C 80084DD4 06002292 */  lbu        $v0, 0x6($s1)
/* 37FCBA0 80084DD8 44006392 */  lbu        $v1, 0x44($s3)
/* 37FCBA4 80084DDC 80100200 */  sll        $v0, $v0, 2
/* 37FCBA8 80084DE0 21186200 */  addu       $v1, $v1, $v0
/* 37FCBAC 80084DE4 440063A2 */  sb         $v1, 0x44($s3)
/* 37FCBB0 80084DE8 08002292 */  lbu        $v0, 0x8($s1)
/* 37FCBB4 80084DEC 45006392 */  lbu        $v1, 0x45($s3)
/* 37FCBB8 80084DF0 80100200 */  sll        $v0, $v0, 2
/* 37FCBBC 80084DF4 21186200 */  addu       $v1, $v1, $v0
/* 37FCBC0 80084DF8 450063A2 */  sb         $v1, 0x45($s3)
/* 37FCBC4 80084DFC 0A002292 */  lbu        $v0, 0xA($s1)
/* 37FCBC8 80084E00 46006392 */  lbu        $v1, 0x46($s3)
/* 37FCBCC 80084E04 80100200 */  sll        $v0, $v0, 2
/* 37FCBD0 80084E08 21186200 */  addu       $v1, $v1, $v0
/* 37FCBD4 80084E0C 460063A2 */  sb         $v1, 0x46($s3)
/* 37FCBD8 80084E10 1400A28E */  lw         $v0, 0x14($s5)
/* 37FCBDC 80084E14 00000000 */  nop
/* 37FCBE0 80084E18 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 37FCBE4 80084E1C 100022AE */  sw         $v0, 0x10($s1)
/* 37FCBE8 80084E20 4B006292 */  lbu        $v0, 0x4B($s3)
/* 37FCBEC 80084E24 14140208 */  j          .Llevel_41_80085050
/* 37FCBF0 80084E28 0001033C */   lui       $v1, (0x1000000 >> 16)
.Llevel_41_80084E2C:
/* 37FCBF4 80084E2C 0000708E */  lw         $s0, 0x0($s3)
/* 37FCBF8 80084E30 C8E9000C */  jal        func_8003A720
/* 37FCBFC 80084E34 21206002 */   addu      $a0, $s3, $zero
/* 37FCC00 80084E38 AA49010C */  jal        func_800526A8
/* 37FCC04 80084E3C 21206002 */   addu      $a0, $s3, $zero
/* 37FCC08 80084E40 490060A2 */  sb         $zero, 0x49($s3)
/* 37FCC0C 80084E44 000000AE */  sw         $zero, 0x0($s0)
/* 37FCC10 80084E48 080000A6 */  sh         $zero, 0x8($s0)
/* 37FCC14 80084E4C 060000A6 */  sh         $zero, 0x6($s0)
/* 37FCC18 80084E50 040000A6 */  sh         $zero, 0x4($s0)
/* 37FCC1C 80084E54 0C0000AE */  sw         $zero, 0xC($s0)
/* 37FCC20 80084E58 4901A012 */  beqz       $s5, .Llevel_41_80085380
/* 37FCC24 80084E5C 100000AE */   sw        $zero, 0x10($s0)
/* 37FCC28 80084E60 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FCC2C 80084E64 C05D000C */  jal        VecCopy
/* 37FCC30 80084E68 0C00A526 */   addiu     $a1, $s5, 0xC
/* 37FCC34 80084E6C E1140208 */  j          .Llevel_41_80085384
/* 37FCC38 80084E70 21106002 */   addu      $v0, $s3, $zero
.Llevel_41_80084E74:
/* 37FCC3C 80084E74 C8E9000C */  jal        func_8003A720
/* 37FCC40 80084E78 21206002 */   addu      $a0, $s3, $zero
/* 37FCC44 80084E7C 0880053C */  lui        $a1, %hi(g_Spyro + 0x17C)
/* 37FCC48 80084E80 D48BA524 */  addiu      $a1, $a1, %lo(g_Spyro + 0x17C)
/* 37FCC4C 80084E84 C05D000C */  jal        VecCopy
/* 37FCC50 80084E88 0C006426 */   addiu     $a0, $s3, 0xC
/* 37FCC54 80084E8C 0880043C */  lui        $a0, %hi(g_Spyro + 0x188)
/* 37FCC58 80084E90 E08B848C */  lw         $a0, %lo(g_Spyro + 0x188)($a0)
/* 37FCC5C 80084E94 0880053C */  lui        $a1, %hi(g_Spyro + 0x18C)
/* 37FCC60 80084E98 E48BA58C */  lw         $a1, %lo(g_Spyro + 0x18C)($a1)
/* 37FCC64 80084E9C AD5A000C */  jal        Atan2
/* 37FCC68 80084EA0 21300000 */   addu      $a2, $zero, $zero
/* 37FCC6C 80084EA4 21206002 */  addu       $a0, $s3, $zero
/* 37FCC70 80084EA8 40004224 */  addiu      $v0, $v0, 0x40
/* 37FCC74 80084EAC DE140208 */  j          .Llevel_41_80085378
/* 37FCC78 80084EB0 460062A2 */   sb        $v0, 0x46($s3)
.Llevel_41_80084EB4:
/* 37FCC7C 80084EB4 0000748E */  lw         $s4, 0x0($s3)
/* 37FCC80 80084EB8 C8E9000C */  jal        func_8003A720
/* 37FCC84 80084EBC 21206002 */   addu      $a0, $s3, $zero
/* 37FCC88 80084EC0 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FCC8C 80084EC4 0C00A526 */  addiu      $a1, $s5, 0xC
/* 37FCC90 80084EC8 20000224 */  addiu      $v0, $zero, 0x20
/* 37FCC94 80084ECC C05D000C */  jal        VecCopy
/* 37FCC98 80084ED0 500062A2 */   sb        $v0, 0x50($s3)
/* 37FCC9C 80084ED4 AA49010C */  jal        func_800526A8
/* 37FCCA0 80084ED8 21206002 */   addu      $a0, $s3, $zero
/* 37FCCA4 80084EDC CB89010C */  jal        rand
/* 37FCCA8 80084EE0 00000000 */   nop
/* 37FCCAC 80084EE4 CB89010C */  jal        rand
/* 37FCCB0 80084EE8 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 37FCCB4 80084EEC FF075130 */  andi       $s1, $v0, 0x7FF
/* 37FCCB8 80084EF0 2C5B000C */  jal        Cos
/* 37FCCBC 80084EF4 21202002 */   addu      $a0, $s1, $zero
/* 37FCCC0 80084EF8 21204002 */  addu       $a0, $s2, $zero
/* 37FCCC4 80084EFC 2C5B000C */  jal        Cos
/* 37FCCC8 80084F00 21804000 */   addu      $s0, $v0, $zero
/* 37FCCCC 80084F04 43811000 */  sra        $s0, $s0, 5
/* 37FCCD0 80084F08 18000202 */  mult       $s0, $v0
/* 37FCCD4 80084F0C 21202002 */  addu       $a0, $s1, $zero
/* 37FCCD8 80084F10 12380000 */  mflo       $a3
/* 37FCCDC 80084F14 03130700 */  sra        $v0, $a3, 12
/* 37FCCE0 80084F18 2C5B000C */  jal        Cos
/* 37FCCE4 80084F1C 000082A6 */   sh        $v0, 0x0($s4)
/* 37FCCE8 80084F20 21204002 */  addu       $a0, $s2, $zero
/* 37FCCEC 80084F24 165B000C */  jal        Sin
/* 37FCCF0 80084F28 21804000 */   addu      $s0, $v0, $zero
/* 37FCCF4 80084F2C 43811000 */  sra        $s0, $s0, 5
/* 37FCCF8 80084F30 18000202 */  mult       $s0, $v0
/* 37FCCFC 80084F34 21202002 */  addu       $a0, $s1, $zero
/* 37FCD00 80084F38 12380000 */  mflo       $a3
/* 37FCD04 80084F3C 03130700 */  sra        $v0, $a3, 12
/* 37FCD08 80084F40 165B000C */  jal        Sin
/* 37FCD0C 80084F44 020082A6 */   sh        $v0, 0x2($s4)
/* 37FCD10 80084F48 43110200 */  sra        $v0, $v0, 5
/* 37FCD14 80084F4C 040082A6 */  sh         $v0, 0x4($s4)
/* 37FCD18 80084F50 1800A28E */  lw         $v0, 0x18($s5)
/* 37FCD1C 80084F54 0200033C */  lui        $v1, (0x20000 >> 16)
/* 37FCD20 80084F58 24104300 */  and        $v0, $v0, $v1
/* 37FCD24 80084F5C 13004010 */  beqz       $v0, .Llevel_41_80084FAC
/* 37FCD28 80084F60 00000000 */   nop
/* 37FCD2C 80084F64 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 37FCD30 80084F68 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 37FCD34 80084F6C 00008396 */  lhu        $v1, 0x0($s4)
/* 37FCD38 80084F70 83110200 */  sra        $v0, $v0, 6
/* 37FCD3C 80084F74 21186200 */  addu       $v1, $v1, $v0
/* 37FCD40 80084F78 000083A6 */  sh         $v1, 0x0($s4)
/* 37FCD44 80084F7C 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 37FCD48 80084F80 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 37FCD4C 80084F84 02008396 */  lhu        $v1, 0x2($s4)
/* 37FCD50 80084F88 83110200 */  sra        $v0, $v0, 6
/* 37FCD54 80084F8C 21186200 */  addu       $v1, $v1, $v0
/* 37FCD58 80084F90 020083A6 */  sh         $v1, 0x2($s4)
/* 37FCD5C 80084F94 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 37FCD60 80084F98 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 37FCD64 80084F9C 04008396 */  lhu        $v1, 0x4($s4)
/* 37FCD68 80084FA0 83110200 */  sra        $v0, $v0, 6
/* 37FCD6C 80084FA4 21186200 */  addu       $v1, $v1, $v0
/* 37FCD70 80084FA8 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_41_80084FAC:
/* 37FCD74 80084FAC 00008286 */  lh         $v0, 0x0($s4)
/* 37FCD78 80084FB0 0C00638E */  lw         $v1, 0xC($s3)
/* 37FCD7C 80084FB4 80100200 */  sll        $v0, $v0, 2
/* 37FCD80 80084FB8 21186200 */  addu       $v1, $v1, $v0
/* 37FCD84 80084FBC 0C0063AE */  sw         $v1, 0xC($s3)
/* 37FCD88 80084FC0 02008286 */  lh         $v0, 0x2($s4)
/* 37FCD8C 80084FC4 1000638E */  lw         $v1, 0x10($s3)
/* 37FCD90 80084FC8 80100200 */  sll        $v0, $v0, 2
/* 37FCD94 80084FCC 21186200 */  addu       $v1, $v1, $v0
/* 37FCD98 80084FD0 100063AE */  sw         $v1, 0x10($s3)
/* 37FCD9C 80084FD4 04008286 */  lh         $v0, 0x4($s4)
/* 37FCDA0 80084FD8 1400638E */  lw         $v1, 0x14($s3)
/* 37FCDA4 80084FDC 80100200 */  sll        $v0, $v0, 2
/* 37FCDA8 80084FE0 21186200 */  addu       $v1, $v1, $v0
/* 37FCDAC 80084FE4 CB89010C */  jal        rand
/* 37FCDB0 80084FE8 140063AE */   sw        $v1, 0x14($s3)
/* 37FCDB4 80084FEC 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCDB8 80084FF0 CB89010C */  jal        rand
/* 37FCDBC 80084FF4 060082A6 */   sh        $v0, 0x6($s4)
/* 37FCDC0 80084FF8 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCDC4 80084FFC CB89010C */  jal        rand
/* 37FCDC8 80085000 080082A6 */   sh        $v0, 0x8($s4)
/* 37FCDCC 80085004 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCDD0 80085008 0A0082A6 */  sh         $v0, 0xA($s4)
/* 37FCDD4 8008500C 1400A28E */  lw         $v0, 0x14($s5)
/* 37FCDD8 80085010 00000000 */  nop
/* 37FCDDC 80085014 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 37FCDE0 80085018 CB89010C */  jal        rand
/* 37FCDE4 8008501C 100082AE */   sw        $v0, 0x10($s4)
/* 37FCDE8 80085020 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCDEC 80085024 40000324 */  addiu      $v1, $zero, 0x40
/* 37FCDF0 80085028 23186200 */  subu       $v1, $v1, $v0
/* 37FCDF4 8008502C 0C0083AE */  sw         $v1, 0xC($s4)
/* 37FCDF8 80085030 36006296 */  lhu        $v0, 0x36($s3)
/* 37FCDFC 80085034 00000000 */  nop
/* 37FCE00 80085038 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 37FCE04 8008503C 0300422C */  sltiu      $v0, $v0, 0x3
/* 37FCE08 80085040 CF004010 */  beqz       $v0, .Llevel_41_80085380
/* 37FCE0C 80085044 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 37FCE10 80085048 4B006292 */  lbu        $v0, 0x4B($s3)
/* 37FCE14 8008504C 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
.Llevel_41_80085050:
/* 37FCE18 80085050 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_41_80085054:
/* 37FCE1C 80085054 80004234 */  ori        $v0, $v0, 0x80
/* 37FCE20 80085058 E0140208 */  j          .Llevel_41_80085380
/* 37FCE24 8008505C 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_41_80085060:
/* 37FCE28 80085060 0000718E */  lw         $s1, 0x0($s3)
/* 37FCE2C 80085064 C8E9000C */  jal        func_8003A720
/* 37FCE30 80085068 21206002 */   addu      $a0, $s3, $zero
/* 37FCE34 8008506C 21206002 */  addu       $a0, $s3, $zero
/* 37FCE38 80085070 20000224 */  addiu      $v0, $zero, 0x20
/* 37FCE3C 80085074 500062A2 */  sb         $v0, 0x50($s3)
/* 37FCE40 80085078 FF000224 */  addiu      $v0, $zero, 0xFF
/* 37FCE44 8008507C 734A010C */  jal        func_800529CC
/* 37FCE48 80085080 520062A2 */   sb        $v0, 0x52($s3)
/* 37FCE4C 80085084 0E000224 */  addiu      $v0, $zero, 0xE
/* 37FCE50 80085088 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 37FCE54 8008508C 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 37FCE58 80085090 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 37FCE5C 80085094 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 37FCE60 80085098 0780033C */  lui        $v1, %hi(g_DragonCutscene + 0x28)
/* 37FCE64 8008509C 5870638C */  lw         $v1, %lo(g_DragonCutscene + 0x28)($v1)
/* 37FCE68 800850A0 03000224 */  addiu      $v0, $zero, 0x3
/* 37FCE6C 800850A4 03006214 */  bne        $v1, $v0, .Llevel_41_800850B4
/* 37FCE70 800850A8 01000224 */   addiu     $v0, $zero, 0x1
/* 37FCE74 800850AC 2F140208 */  j          .Llevel_41_800850BC
/* 37FCE78 800850B0 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_41_800850B4:
/* 37FCE7C 800850B4 02006214 */  bne        $v1, $v0, .Llevel_41_800850C0
/* 37FCE80 800850B8 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_41_800850BC:
/* 37FCE84 800850BC 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_41_800850C0:
/* 37FCE88 800850C0 CB89010C */  jal        rand
/* 37FCE8C 800850C4 00000000 */   nop
/* 37FCE90 800850C8 2000A426 */  addiu      $a0, $s5, 0x20
/* 37FCE94 800850CC 07004230 */  andi       $v0, $v0, 0x7
/* 37FCE98 800850D0 80100200 */  sll        $v0, $v0, 2
/* 37FCE9C 800850D4 2000B027 */  addiu      $s0, $sp, 0x20
/* 37FCEA0 800850D8 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 37FCEA4 800850DC 21082200 */  addu       $at, $at, $v0
/* 37FCEA8 800850E0 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 37FCEAC 800850E4 21280002 */  addu       $a1, $s0, $zero
/* 37FCEB0 800850E8 2400A0AF */  sw         $zero, 0x24($sp)
/* 37FCEB4 800850EC 2000A3AF */  sw         $v1, 0x20($sp)
/* 37FCEB8 800850F0 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 37FCEBC 800850F4 21082200 */  addu       $at, $at, $v0
/* 37FCEC0 800850F8 A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 37FCEC4 800850FC 21300002 */  addu       $a2, $s0, $zero
/* 37FCEC8 80085100 125C000C */  jal        VecRotateByMatrix
/* 37FCECC 80085104 2800A2AF */   sw        $v0, 0x28($sp)
/* 37FCED0 80085108 CB89010C */  jal        rand
/* 37FCED4 8008510C 00000000 */   nop
/* 37FCED8 80085110 2000A38F */  lw         $v1, 0x20($sp)
/* 37FCEDC 80085114 7F004230 */  andi       $v0, $v0, 0x7F
/* 37FCEE0 80085118 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 37FCEE4 8008511C 21186200 */  addu       $v1, $v1, $v0
/* 37FCEE8 80085120 CB89010C */  jal        rand
/* 37FCEEC 80085124 2000A3AF */   sw        $v1, 0x20($sp)
/* 37FCEF0 80085128 2400A38F */  lw         $v1, 0x24($sp)
/* 37FCEF4 8008512C 7F004230 */  andi       $v0, $v0, 0x7F
/* 37FCEF8 80085130 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 37FCEFC 80085134 21186200 */  addu       $v1, $v1, $v0
/* 37FCF00 80085138 CB89010C */  jal        rand
/* 37FCF04 8008513C 2400A3AF */   sw        $v1, 0x24($sp)
/* 37FCF08 80085140 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FCF0C 80085144 0C00A526 */  addiu      $a1, $s5, 0xC
/* 37FCF10 80085148 21300002 */  addu       $a2, $s0, $zero
/* 37FCF14 8008514C 2800A38F */  lw         $v1, 0x28($sp)
/* 37FCF18 80085150 7F004230 */  andi       $v0, $v0, 0x7F
/* 37FCF1C 80085154 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 37FCF20 80085158 21186200 */  addu       $v1, $v1, $v0
/* 37FCF24 8008515C D65D000C */  jal        VecAdd
/* 37FCF28 80085160 2800A3AF */   sw        $v1, 0x28($sp)
/* 37FCF2C 80085164 21202002 */  addu       $a0, $s1, $zero
/* 37FCF30 80085168 C05D000C */  jal        VecCopy
/* 37FCF34 8008516C 21280002 */   addu      $a1, $s0, $zero
/* 37FCF38 80085170 21202002 */  addu       $a0, $s1, $zero
/* 37FCF3C 80085174 B25D000C */  jal        VecShiftRight
/* 37FCF40 80085178 02000524 */   addiu     $a1, $zero, 0x2
/* 37FCF44 8008517C CB89010C */  jal        rand
/* 37FCF48 80085180 00000000 */   nop
/* 37FCF4C 80085184 0000238E */  lw         $v1, 0x0($s1)
/* 37FCF50 80085188 FF004230 */  andi       $v0, $v0, 0xFF
/* 37FCF54 8008518C 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 37FCF58 80085190 21186200 */  addu       $v1, $v1, $v0
/* 37FCF5C 80085194 CB89010C */  jal        rand
/* 37FCF60 80085198 000023AE */   sw        $v1, 0x0($s1)
/* 37FCF64 8008519C 0400238E */  lw         $v1, 0x4($s1)
/* 37FCF68 800851A0 FF004230 */  andi       $v0, $v0, 0xFF
/* 37FCF6C 800851A4 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 37FCF70 800851A8 21186200 */  addu       $v1, $v1, $v0
/* 37FCF74 800851AC CB89010C */  jal        rand
/* 37FCF78 800851B0 040023AE */   sw        $v1, 0x4($s1)
/* 37FCF7C 800851B4 0800238E */  lw         $v1, 0x8($s1)
/* 37FCF80 800851B8 FF004230 */  andi       $v0, $v0, 0xFF
/* 37FCF84 800851BC 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 37FCF88 800851C0 21186200 */  addu       $v1, $v1, $v0
/* 37FCF8C 800851C4 CB89010C */  jal        rand
/* 37FCF90 800851C8 080023AE */   sw        $v1, 0x8($s1)
/* 37FCF94 800851CC CB89010C */  jal        rand
/* 37FCF98 800851D0 440062A2 */   sb        $v0, 0x44($s3)
/* 37FCF9C 800851D4 CB89010C */  jal        rand
/* 37FCFA0 800851D8 450062A2 */   sb        $v0, 0x45($s3)
/* 37FCFA4 800851DC CB89010C */  jal        rand
/* 37FCFA8 800851E0 460062A2 */   sb        $v0, 0x46($s3)
/* 37FCFAC 800851E4 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCFB0 800851E8 CB89010C */  jal        rand
/* 37FCFB4 800851EC 100022A2 */   sb        $v0, 0x10($s1)
/* 37FCFB8 800851F0 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCFBC 800851F4 CB89010C */  jal        rand
/* 37FCFC0 800851F8 110022A2 */   sb        $v0, 0x11($s1)
/* 37FCFC4 800851FC 0F004230 */  andi       $v0, $v0, 0xF
/* 37FCFC8 80085200 120022A2 */  sb         $v0, 0x12($s1)
/* 37FCFCC 80085204 1400A28E */  lw         $v0, 0x14($s5)
/* 37FCFD0 80085208 CB89010C */  jal        rand
/* 37FCFD4 8008520C 0C0022AE */   sw        $v0, 0xC($s1)
/* 37FCFD8 80085210 03004230 */  andi       $v0, $v0, 0x3
/* 37FCFDC 80085214 10004224 */  addiu      $v0, $v0, 0x10
/* 37FCFE0 80085218 E0140208 */  j          .Llevel_41_80085380
/* 37FCFE4 8008521C 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_41_80085220:
/* 37FCFE8 80085220 0000708E */  lw         $s0, 0x0($s3)
/* 37FCFEC 80085224 C8E9000C */  jal        func_8003A720
/* 37FCFF0 80085228 21206002 */   addu      $a0, $s3, $zero
/* 37FCFF4 8008522C 734A010C */  jal        func_800529CC
/* 37FCFF8 80085230 21206002 */   addu      $a0, $s3, $zero
/* 37FCFFC 80085234 02000224 */  addiu      $v0, $zero, 0x2
/* 37FD000 80085238 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 37FD004 8008523C 40000224 */  addiu      $v0, $zero, 0x40
/* 37FD008 80085240 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 37FD00C 80085244 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 37FD010 80085248 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 37FD014 8008524C E0140208 */  j          .Llevel_41_80085380
/* 37FD018 80085250 000002AE */   sw        $v0, 0x0($s0)
.Llevel_41_80085254:
/* 37FD01C 80085254 0000708E */  lw         $s0, 0x0($s3)
/* 37FD020 80085258 C8E9000C */  jal        func_8003A720
/* 37FD024 8008525C 21206002 */   addu      $a0, $s3, $zero
/* 37FD028 80085260 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FD02C 80085264 C05D000C */  jal        VecCopy
/* 37FD030 80085268 0C00A526 */   addiu     $a1, $s5, 0xC
/* 37FD034 8008526C 21206002 */  addu       $a0, $s3, $zero
/* 37FD038 80085270 000015AE */  sw         $s5, 0x0($s0)
/* 37FD03C 80085274 040000AE */  sw         $zero, 0x4($s0)
/* 37FD040 80085278 080000AE */  sw         $zero, 0x8($s0)
/* 37FD044 8008527C AA49010C */  jal        func_800526A8
/* 37FD048 80085280 500060A2 */   sb        $zero, 0x50($s3)
/* 37FD04C 80085284 E0140208 */  j          .Llevel_41_80085380
/* 37FD050 80085288 510060A2 */   sb        $zero, 0x51($s3)
.Llevel_41_8008528C:
/* 37FD054 8008528C C8E9000C */  jal        func_8003A720
/* 37FD058 80085290 21206002 */   addu      $a0, $s3, $zero
/* 37FD05C 80085294 05000224 */  addiu      $v0, $zero, 0x5
/* 37FD060 80085298 3100A012 */  beqz       $s5, .Llevel_41_80085360
/* 37FD064 8008529C 470062A2 */   sb        $v0, 0x47($s3)
/* 37FD068 800852A0 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FD06C 800852A4 DB140208 */  j          .Llevel_41_8008536C
/* 37FD070 800852A8 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_41_800852AC:
/* 37FD074 800852AC C8E9000C */  jal        func_8003A720
/* 37FD078 800852B0 21206002 */   addu      $a0, $s3, $zero
/* 37FD07C 800852B4 0300A012 */  beqz       $s5, .Llevel_41_800852C4
/* 37FD080 800852B8 0C006426 */   addiu     $a0, $s3, 0xC
/* 37FD084 800852BC B3140208 */  j          .Llevel_41_800852CC
/* 37FD088 800852C0 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_41_800852C4:
/* 37FD08C 800852C4 0880053C */  lui        $a1, %hi(g_Spyro)
/* 37FD090 800852C8 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_41_800852CC:
/* 37FD094 800852CC C05D000C */  jal        VecCopy
/* 37FD098 800852D0 00000000 */   nop
/* 37FD09C 800852D4 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FD0A0 800852D8 1400628E */  lw         $v0, 0x14($s3)
/* 37FD0A4 800852DC 00080524 */  addiu      $a1, $zero, 0x800
/* 37FD0A8 800852E0 00024224 */  addiu      $v0, $v0, 0x200
/* 37FD0AC 800852E4 7B35010C */  jal        func_8004D5EC
/* 37FD0B0 800852E8 140062AE */   sw        $v0, 0x14($s3)
/* 37FD0B4 800852EC 1400648E */  lw         $a0, 0x14($s3)
/* 37FD0B8 800852F0 21184000 */  addu       $v1, $v0, $zero
/* 37FD0BC 800852F4 23106400 */  subu       $v0, $v1, $a0
/* 37FD0C0 800852F8 02004104 */  bgez       $v0, .Llevel_41_80085304
/* 37FD0C4 800852FC 00000000 */   nop
/* 37FD0C8 80085300 23100200 */  negu       $v0, $v0
.Llevel_41_80085304:
/* 37FD0CC 80085304 00084228 */  slti       $v0, $v0, 0x800
/* 37FD0D0 80085308 03004010 */  beqz       $v0, .Llevel_41_80085318
/* 37FD0D4 8008530C 00FE8224 */   addiu     $v0, $a0, -0x200
/* 37FD0D8 80085310 DD140208 */  j          .Llevel_41_80085374
/* 37FD0DC 80085314 140063AE */   sw        $v1, 0x14($s3)
.Llevel_41_80085318:
/* 37FD0E0 80085318 DD140208 */  j          .Llevel_41_80085374
/* 37FD0E4 8008531C 140062AE */   sw        $v0, 0x14($s3)
.Llevel_41_80085320:
/* 37FD0E8 80085320 C8E9000C */  jal        func_8003A720
/* 37FD0EC 80085324 21206002 */   addu      $a0, $s3, $zero
/* 37FD0F0 80085328 21206002 */  addu       $a0, $s3, $zero
/* 37FD0F4 8008532C 20000224 */  addiu      $v0, $zero, 0x20
/* 37FD0F8 80085330 500062A2 */  sb         $v0, 0x50($s3)
/* 37FD0FC 80085334 FF000224 */  addiu      $v0, $zero, 0xFF
/* 37FD100 80085338 734A010C */  jal        func_800529CC
/* 37FD104 8008533C 520062A2 */   sb        $v0, 0x52($s3)
/* 37FD108 80085340 E1140208 */  j          .Llevel_41_80085384
/* 37FD10C 80085344 21106002 */   addu      $v0, $s3, $zero
.Llevel_41_80085348:
/* 37FD110 80085348 C8E9000C */  jal        func_8003A720
/* 37FD114 8008534C 21206002 */   addu      $a0, $s3, $zero
/* 37FD118 80085350 0300A012 */  beqz       $s5, .Llevel_41_80085360
/* 37FD11C 80085354 0C006426 */   addiu     $a0, $s3, 0xC
/* 37FD120 80085358 DB140208 */  j          .Llevel_41_8008536C
/* 37FD124 8008535C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_41_80085360:
/* 37FD128 80085360 0C006426 */  addiu      $a0, $s3, 0xC
/* 37FD12C 80085364 0880053C */  lui        $a1, %hi(g_Spyro)
/* 37FD130 80085368 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_41_8008536C:
/* 37FD134 8008536C C05D000C */  jal        VecCopy
/* 37FD138 80085370 00000000 */   nop
.Llevel_41_80085374:
/* 37FD13C 80085374 21206002 */  addu       $a0, $s3, $zero
.Llevel_41_80085378:
/* 37FD140 80085378 AA49010C */  jal        func_800526A8
/* 37FD144 8008537C 00000000 */   nop
.Llevel_41_80085380:
/* 37FD148 80085380 21106002 */  addu       $v0, $s3, $zero
.Llevel_41_80085384:
/* 37FD14C 80085384 5000BF8F */  lw         $ra, 0x50($sp)
/* 37FD150 80085388 4C00B58F */  lw         $s5, 0x4C($sp)
/* 37FD154 8008538C 4800B48F */  lw         $s4, 0x48($sp)
/* 37FD158 80085390 4400B38F */  lw         $s3, 0x44($sp)
/* 37FD15C 80085394 4000B28F */  lw         $s2, 0x40($sp)
/* 37FD160 80085398 3C00B18F */  lw         $s1, 0x3C($sp)
/* 37FD164 8008539C 3800B08F */  lw         $s0, 0x38($sp)
/* 37FD168 800853A0 5800BD27 */  addiu      $sp, $sp, 0x58
/* 37FD16C 800853A4 0800E003 */  jr         $ra
/* 37FD170 800853A8 00000000 */   nop
.size func_level_41_8008465C, . - func_level_41_8008465C
