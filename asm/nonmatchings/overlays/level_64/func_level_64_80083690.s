.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_64_80083690
/* 5AF3458 80083690 B0FFBD27 */  addiu      $sp, $sp, -0x50
/* 5AF345C 80083694 3000B0AF */  sw         $s0, 0x30($sp)
/* 5AF3460 80083698 21808000 */  addu       $s0, $a0, $zero
/* 5AF3464 8008369C 4400B5AF */  sw         $s5, 0x44($sp)
/* 5AF3468 800836A0 21A8A000 */  addu       $s5, $a1, $zero
/* 5AF346C 800836A4 4800BFAF */  sw         $ra, 0x48($sp)
/* 5AF3470 800836A8 4000B4AF */  sw         $s4, 0x40($sp)
/* 5AF3474 800836AC 3C00B3AF */  sw         $s3, 0x3C($sp)
/* 5AF3478 800836B0 3800B2AF */  sw         $s2, 0x38($sp)
/* 5AF347C 800836B4 3149010C */  jal        func_800524C4
/* 5AF3480 800836B8 3400B1AF */   sw        $s1, 0x34($sp)
/* 5AF3484 800836BC 21A04000 */  addu       $s4, $v0, $zero
/* 5AF3488 800836C0 1400A012 */  beqz       $s5, .Llevel_64_80083714
/* 5AF348C 800836C4 360090A6 */   sh        $s0, 0x36($s4)
/* 5AF3490 800836C8 0780043C */  lui        $a0, %hi(D_80075828)
/* 5AF3494 800836CC 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 5AF3498 800836D0 00000000 */  nop
/* 5AF349C 800836D4 2320A402 */  subu       $a0, $s5, $a0
/* 5AF34A0 800836D8 40190400 */  sll        $v1, $a0, 5
/* 5AF34A4 800836DC 23186400 */  subu       $v1, $v1, $a0
/* 5AF34A8 800836E0 40190300 */  sll        $v1, $v1, 5
/* 5AF34AC 800836E4 21186400 */  addu       $v1, $v1, $a0
/* 5AF34B0 800836E8 C0100300 */  sll        $v0, $v1, 3
/* 5AF34B4 800836EC 21186200 */  addu       $v1, $v1, $v0
/* 5AF34B8 800836F0 C0130300 */  sll        $v0, $v1, 15
/* 5AF34BC 800836F4 23104300 */  subu       $v0, $v0, $v1
/* 5AF34C0 800836F8 80100200 */  sll        $v0, $v0, 2
/* 5AF34C4 800836FC 21104400 */  addu       $v0, $v0, $a0
/* 5AF34C8 80083700 23100200 */  negu       $v0, $v0
/* 5AF34CC 80083704 C3180200 */  sra        $v1, $v0, 3
/* 5AF34D0 80083708 0001622C */  sltiu      $v0, $v1, 0x100
/* 5AF34D4 8008370C 03004014 */  bnez       $v0, .Llevel_64_8008371C
/* 5AF34D8 80083710 0201022A */   slti      $v0, $s0, 0x102
.Llevel_64_80083714:
/* 5AF34DC 80083714 21180000 */  addu       $v1, $zero, $zero
/* 5AF34E0 80083718 0201022A */  slti       $v0, $s0, 0x102
.Llevel_64_8008371C:
/* 5AF34E4 8008371C 31004010 */  beqz       $v0, .Llevel_64_800837E4
/* 5AF34E8 80083720 560083A2 */   sb        $v1, 0x56($s4)
/* 5AF34EC 80083724 FF00022A */  slti       $v0, $s0, 0xFF
/* 5AF34F0 80083728 5A014010 */  beqz       $v0, .Llevel_64_80083C94
/* 5AF34F4 8008372C 4600022A */   slti      $v0, $s0, 0x46
/* 5AF34F8 80083730 14004010 */  beqz       $v0, .Llevel_64_80083784
/* 5AF34FC 80083734 4300022A */   slti      $v0, $s0, 0x43
/* 5AF3500 80083738 56014010 */  beqz       $v0, .Llevel_64_80083C94
/* 5AF3504 8008373C 10000224 */   addiu     $v0, $zero, 0x10
/* 5AF3508 80083740 81000212 */  beq        $s0, $v0, .Llevel_64_80083948
/* 5AF350C 80083744 1100022A */   slti      $v0, $s0, 0x11
/* 5AF3510 80083748 07004010 */  beqz       $v0, .Llevel_64_80083768
/* 5AF3514 8008374C 0E000224 */   addiu     $v0, $zero, 0xE
/* 5AF3518 80083750 D9000212 */  beq        $s0, $v0, .Llevel_64_80083AB8
/* 5AF351C 80083754 0F000224 */   addiu     $v0, $zero, 0xF
/* 5AF3520 80083758 54000212 */  beq        $s0, $v0, .Llevel_64_800838AC
/* 5AF3524 8008375C 00000000 */   nop
/* 5AF3528 80083760 27100208 */  j          .Llevel_64_8008409C
/* 5AF352C 80083764 00000000 */   nop
.Llevel_64_80083768:
/* 5AF3530 80083768 11000224 */  addiu      $v0, $zero, 0x11
/* 5AF3534 8008376C 8A000212 */  beq        $s0, $v0, .Llevel_64_80083998
/* 5AF3538 80083770 22000224 */   addiu     $v0, $zero, 0x22
/* 5AF353C 80083774 C2000212 */  beq        $s0, $v0, .Llevel_64_80083A80
/* 5AF3540 80083778 00000000 */   nop
/* 5AF3544 8008377C 27100208 */  j          .Llevel_64_8008409C
/* 5AF3548 80083780 00000000 */   nop
.Llevel_64_80083784:
/* 5AF354C 80083784 78000224 */  addiu      $v0, $zero, 0x78
/* 5AF3550 80083788 22010212 */  beq        $s0, $v0, .Llevel_64_80083C14
/* 5AF3554 8008378C 7900022A */   slti      $v0, $s0, 0x79
/* 5AF3558 80083790 0B004010 */  beqz       $v0, .Llevel_64_800837C0
/* 5AF355C 80083794 4C000224 */   addiu     $v0, $zero, 0x4C
/* 5AF3560 80083798 36020212 */  beq        $s0, $v0, .Llevel_64_80084074
/* 5AF3564 8008379C 4C00022A */   slti      $v0, $s0, 0x4C
/* 5AF3568 800837A0 3E024014 */  bnez       $v0, .Llevel_64_8008409C
/* 5AF356C 800837A4 5800022A */   slti      $v0, $s0, 0x58
/* 5AF3570 800837A8 3C024010 */  beqz       $v0, .Llevel_64_8008409C
/* 5AF3574 800837AC 5300022A */   slti      $v0, $s0, 0x53
/* 5AF3578 800837B0 C1004010 */  beqz       $v0, .Llevel_64_80083AB8
/* 5AF357C 800837B4 00000000 */   nop
/* 5AF3580 800837B8 27100208 */  j          .Llevel_64_8008409C
/* 5AF3584 800837BC 00000000 */   nop
.Llevel_64_800837C0:
/* 5AF3588 800837C0 97000224 */  addiu      $v0, $zero, 0x97
/* 5AF358C 800837C4 33010212 */  beq        $s0, $v0, .Llevel_64_80083C94
/* 5AF3590 800837C8 9700022A */   slti      $v0, $s0, 0x97
/* 5AF3594 800837CC 33024014 */  bnez       $v0, .Llevel_64_8008409C
/* 5AF3598 800837D0 9A00022A */   slti      $v0, $s0, 0x9A
/* 5AF359C 800837D4 31024010 */  beqz       $v0, .Llevel_64_8008409C
/* 5AF35A0 800837D8 00000000 */   nop
/* 5AF35A4 800837DC 170F0208 */  j          .Llevel_64_80083C5C
/* 5AF35A8 800837E0 00000000 */   nop
.Llevel_64_800837E4:
/* 5AF35AC 800837E4 90010224 */  addiu      $v0, $zero, 0x190
/* 5AF35B0 800837E8 05020212 */  beq        $s0, $v0, .Llevel_64_80084000
/* 5AF35B4 800837EC 9101022A */   slti      $v0, $s0, 0x191
/* 5AF35B8 800837F0 14004010 */  beqz       $v0, .Llevel_64_80083844
/* 5AF35BC 800837F4 3801022A */   slti      $v0, $s0, 0x138
/* 5AF35C0 800837F8 0B004010 */  beqz       $v0, .Llevel_64_80083828
/* 5AF35C4 800837FC 3501022A */   slti      $v0, $s0, 0x135
/* 5AF35C8 80083800 24014010 */  beqz       $v0, .Llevel_64_80083C94
/* 5AF35CC 80083804 0401022A */   slti      $v0, $s0, 0x104
/* 5AF35D0 80083808 24024014 */  bnez       $v0, .Llevel_64_8008409C
/* 5AF35D4 8008380C 0E01022A */   slti      $v0, $s0, 0x10E
/* 5AF35D8 80083810 E6014014 */  bnez       $v0, .Llevel_64_80083FAC
/* 5AF35DC 80083814 15010224 */   addiu     $v0, $zero, 0x115
/* 5AF35E0 80083818 E4010212 */  beq        $s0, $v0, .Llevel_64_80083FAC
/* 5AF35E4 8008381C 00000000 */   nop
/* 5AF35E8 80083820 27100208 */  j          .Llevel_64_8008409C
/* 5AF35EC 80083824 00000000 */   nop
.Llevel_64_80083828:
/* 5AF35F0 80083828 47010224 */  addiu      $v0, $zero, 0x147
/* 5AF35F4 8008382C DF010212 */  beq        $s0, $v0, .Llevel_64_80083FAC
/* 5AF35F8 80083830 88010224 */   addiu     $v0, $zero, 0x188
/* 5AF35FC 80083834 EA010212 */  beq        $s0, $v0, .Llevel_64_80083FE0
/* 5AF3600 80083838 00000000 */   nop
/* 5AF3604 8008383C 27100208 */  j          .Llevel_64_8008409C
/* 5AF3608 80083840 00000000 */   nop
.Llevel_64_80083844:
/* 5AF360C 80083844 DD010224 */  addiu      $v0, $zero, 0x1DD
/* 5AF3610 80083848 ED010212 */  beq        $s0, $v0, .Llevel_64_80084000
/* 5AF3614 8008384C DE01022A */   slti      $v0, $s0, 0x1DE
/* 5AF3618 80083850 0B004010 */  beqz       $v0, .Llevel_64_80083880
/* 5AF361C 80083854 95010224 */   addiu     $v0, $zero, 0x195
/* 5AF3620 80083858 E9010212 */  beq        $s0, $v0, .Llevel_64_80084000
/* 5AF3624 8008385C 9501022A */   slti      $v0, $s0, 0x195
/* 5AF3628 80083860 0E024014 */  bnez       $v0, .Llevel_64_8008409C
/* 5AF362C 80083864 C401022A */   slti      $v0, $s0, 0x1C4
/* 5AF3630 80083868 0C024010 */  beqz       $v0, .Llevel_64_8008409C
/* 5AF3634 8008386C AA01022A */   slti      $v0, $s0, 0x1AA
/* 5AF3638 80083870 00024010 */  beqz       $v0, .Llevel_64_80084074
/* 5AF363C 80083874 00000000 */   nop
/* 5AF3640 80083878 27100208 */  j          .Llevel_64_8008409C
/* 5AF3644 8008387C 00000000 */   nop
.Llevel_64_80083880:
/* 5AF3648 80083880 E101022A */  slti       $v0, $s0, 0x1E1
/* 5AF364C 80083884 05024014 */  bnez       $v0, .Llevel_64_8008409C
/* 5AF3650 80083888 E401022A */   slti      $v0, $s0, 0x1E4
/* 5AF3654 8008388C 6C014014 */  bnez       $v0, .Llevel_64_80083E40
/* 5AF3658 80083890 FD01022A */   slti      $v0, $s0, 0x1FD
/* 5AF365C 80083894 01024010 */  beqz       $v0, .Llevel_64_8008409C
/* 5AF3660 80083898 FB01022A */   slti      $v0, $s0, 0x1FB
/* 5AF3664 8008389C D8014010 */  beqz       $v0, .Llevel_64_80084000
/* 5AF3668 800838A0 00000000 */   nop
/* 5AF366C 800838A4 27100208 */  j          .Llevel_64_8008409C
/* 5AF3670 800838A8 00000000 */   nop
.Llevel_64_800838AC:
/* 5AF3674 800838AC 0000908E */  lw         $s0, 0x0($s4)
/* 5AF3678 800838B0 C8E9000C */  jal        func_8003A720
/* 5AF367C 800838B4 21208002 */   addu      $a0, $s4, $zero
/* 5AF3680 800838B8 8C000224 */  addiu      $v0, $zero, 0x8C
/* 5AF3684 800838BC 080002AE */  sw         $v0, 0x8($s0)
/* 5AF3688 800838C0 03000224 */  addiu      $v0, $zero, 0x3
/* 5AF368C 800838C4 100002A2 */  sb         $v0, 0x10($s0)
/* 5AF3690 800838C8 FF000224 */  addiu      $v0, $zero, 0xFF
/* 5AF3694 800838CC 140002A2 */  sb         $v0, 0x14($s0)
/* 5AF3698 800838D0 02000224 */  addiu      $v0, $zero, 0x2
/* 5AF369C 800838D4 000000AE */  sw         $zero, 0x0($s0)
/* 5AF36A0 800838D8 040000AE */  sw         $zero, 0x4($s0)
/* 5AF36A4 800838DC 0E0000A2 */  sb         $zero, 0xE($s0)
/* 5AF36A8 800838E0 0F0000A2 */  sb         $zero, 0xF($s0)
/* 5AF36AC 800838E4 110000A2 */  sb         $zero, 0x11($s0)
/* 5AF36B0 800838E8 120000A2 */  sb         $zero, 0x12($s0)
/* 5AF36B4 800838EC 130000A2 */  sb         $zero, 0x13($s0)
/* 5AF36B8 800838F0 490082A2 */  sb         $v0, 0x49($s4)
/* 5AF36BC 800838F4 18000224 */  addiu      $v0, $zero, 0x18
/* 5AF36C0 800838F8 500082A2 */  sb         $v0, 0x50($s4)
/* 5AF36C4 800838FC 10000224 */  addiu      $v0, $zero, 0x10
/* 5AF36C8 80083900 520082A2 */  sb         $v0, 0x52($s4)
/* 5AF36CC 80083904 20000224 */  addiu      $v0, $zero, 0x20
/* 5AF36D0 80083908 440082A2 */  sb         $v0, 0x44($s4)
/* 5AF36D4 8008390C 450080A2 */  sb         $zero, 0x45($s4)
/* 5AF36D8 80083910 0400A012 */  beqz       $s5, .Llevel_64_80083924
/* 5AF36DC 80083914 460080A2 */   sb        $zero, 0x46($s4)
/* 5AF36E0 80083918 0C008426 */  addiu      $a0, $s4, 0xC
/* 5AF36E4 8008391C C05D000C */  jal        VecCopy
/* 5AF36E8 80083920 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_64_80083924:
/* 5AF36EC 80083924 AA49010C */  jal        func_800526A8
/* 5AF36F0 80083928 21208002 */   addu      $a0, $s4, $zero
/* 5AF36F4 8008392C 4B008292 */  lbu        $v0, 0x4B($s4)
/* 5AF36F8 80083930 01000324 */  addiu      $v1, $zero, 0x1
/* 5AF36FC 80083934 4C0080A2 */  sb         $zero, 0x4C($s4)
/* 5AF3700 80083938 4D0080A2 */  sb         $zero, 0x4D($s4)
/* 5AF3704 8008393C 4E0080A2 */  sb         $zero, 0x4E($s4)
/* 5AF3708 80083940 8D0F0208 */  j          .Llevel_64_80083E34
/* 5AF370C 80083944 4F0083A2 */   sb        $v1, 0x4F($s4)
.Llevel_64_80083948:
/* 5AF3710 80083948 0000918E */  lw         $s1, 0x0($s4)
/* 5AF3714 8008394C C8E9000C */  jal        func_8003A720
/* 5AF3718 80083950 21208002 */   addu      $a0, $s4, $zero
/* 5AF371C 80083954 AA49010C */  jal        func_800526A8
/* 5AF3720 80083958 21208002 */   addu      $a0, $s4, $zero
/* 5AF3724 8008395C 0C009026 */  addiu      $s0, $s4, 0xC
/* 5AF3728 80083960 21200002 */  addu       $a0, $s0, $zero
/* 5AF372C 80083964 C05D000C */  jal        VecCopy
/* 5AF3730 80083968 0C00A526 */   addiu     $a1, $s5, 0xC
/* 5AF3734 8008396C 21280002 */  addu       $a1, $s0, $zero
/* 5AF3738 80083970 1400828E */  lw         $v0, 0x14($s4)
/* 5AF373C 80083974 04002426 */  addiu      $a0, $s1, 0x4
/* 5AF3740 80083978 00024224 */  addiu      $v0, $v0, 0x200
/* 5AF3744 8008397C C05D000C */  jal        VecCopy
/* 5AF3748 80083980 140082AE */   sw        $v0, 0x14($s4)
/* 5AF374C 80083984 08070224 */  addiu      $v0, $zero, 0x708
/* 5AF3750 80083988 130020A2 */  sb         $zero, 0x13($s1)
/* 5AF3754 8008398C 120020A2 */  sb         $zero, 0x12($s1)
/* 5AF3758 80083990 34100208 */  j          .Llevel_64_800840D0
/* 5AF375C 80083994 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_64_80083998:
/* 5AF3760 80083998 C8E9000C */  jal        func_8003A720
/* 5AF3764 8008399C 21208002 */   addu      $a0, $s4, $zero
/* 5AF3768 800839A0 4600A292 */  lbu        $v0, 0x46($s5)
/* 5AF376C 800839A4 00000000 */  nop
/* 5AF3770 800839A8 460082A2 */  sb         $v0, 0x46($s4)
/* 5AF3774 800839AC 40100200 */  sll        $v0, $v0, 1
/* 5AF3778 800839B0 0780013C */  lui        $at, %hi(D_8006CC78)
/* 5AF377C 800839B4 21082200 */  addu       $at, $at, $v0
/* 5AF3780 800839B8 78CC2394 */  lhu        $v1, %lo(D_8006CC78)($at)
/* 5AF3784 800839BC 0C00A28E */  lw         $v0, 0xC($s5)
/* 5AF3788 800839C0 46008492 */  lbu        $a0, 0x46($s4)
/* 5AF378C 800839C4 001C0300 */  sll        $v1, $v1, 16
/* 5AF3790 800839C8 031D0300 */  sra        $v1, $v1, 20
/* 5AF3794 800839CC 21104300 */  addu       $v0, $v0, $v1
/* 5AF3798 800839D0 40200400 */  sll        $a0, $a0, 1
/* 5AF379C 800839D4 0C0082AE */  sw         $v0, 0xC($s4)
/* 5AF37A0 800839D8 0780013C */  lui        $at, %hi(D_8006CBF8)
/* 5AF37A4 800839DC 21082400 */  addu       $at, $at, $a0
/* 5AF37A8 800839E0 F8CB2294 */  lhu        $v0, %lo(D_8006CBF8)($at)
/* 5AF37AC 800839E4 1000A38E */  lw         $v1, 0x10($s5)
/* 5AF37B0 800839E8 00140200 */  sll        $v0, $v0, 16
/* 5AF37B4 800839EC 03150200 */  sra        $v0, $v0, 20
/* 5AF37B8 800839F0 21186200 */  addu       $v1, $v1, $v0
/* 5AF37BC 800839F4 100083AE */  sw         $v1, 0x10($s4)
/* 5AF37C0 800839F8 1400A28E */  lw         $v0, 0x14($s5)
/* 5AF37C4 800839FC 0C00838E */  lw         $v1, 0xC($s4)
/* 5AF37C8 80083A00 140082AE */  sw         $v0, 0x14($s4)
/* 5AF37CC 80083A04 0880023C */  lui        $v0, %hi(g_Spyro)
/* 5AF37D0 80083A08 588A428C */  lw         $v0, %lo(g_Spyro)($v0)
/* 5AF37D4 80083A0C 00000000 */  nop
/* 5AF37D8 80083A10 23104300 */  subu       $v0, $v0, $v1
/* 5AF37DC 80083A14 1000A2AF */  sw         $v0, 0x10($sp)
/* 5AF37E0 80083A18 0880023C */  lui        $v0, %hi(g_Spyro + 0x4)
/* 5AF37E4 80083A1C 5C8A428C */  lw         $v0, %lo(g_Spyro + 0x4)($v0)
/* 5AF37E8 80083A20 1000838E */  lw         $v1, 0x10($s4)
/* 5AF37EC 80083A24 01000524 */  addiu      $a1, $zero, 0x1
/* 5AF37F0 80083A28 23104300 */  subu       $v0, $v0, $v1
/* 5AF37F4 80083A2C 1400A2AF */  sw         $v0, 0x14($sp)
/* 5AF37F8 80083A30 0880023C */  lui        $v0, %hi(g_Spyro + 0x8)
/* 5AF37FC 80083A34 608A428C */  lw         $v0, %lo(g_Spyro + 0x8)($v0)
/* 5AF3800 80083A38 1400838E */  lw         $v1, 0x14($s4)
/* 5AF3804 80083A3C 1000A427 */  addiu      $a0, $sp, 0x10
/* 5AF3808 80083A40 23104300 */  subu       $v0, $v0, $v1
/* 5AF380C 80083A44 7F5C000C */  jal        VecMagnitude
/* 5AF3810 80083A48 1800A2AF */   sw        $v0, 0x18($sp)
/* 5AF3814 80083A4C 1000A427 */  addiu      $a0, $sp, 0x10
/* 5AF3818 80083A50 21284000 */  addu       $a1, $v0, $zero
/* 5AF381C 80083A54 6E5D000C */  jal        VecScaleToLength
/* 5AF3820 80083A58 A0000624 */   addiu     $a2, $zero, 0xA0
/* 5AF3824 80083A5C AA49010C */  jal        func_800526A8
/* 5AF3828 80083A60 21208002 */   addu      $a0, $s4, $zero
/* 5AF382C 80083A64 0000908E */  lw         $s0, 0x0($s4)
/* 5AF3830 80083A68 1000A527 */  addiu      $a1, $sp, 0x10
/* 5AF3834 80083A6C C05D000C */  jal        VecCopy
/* 5AF3838 80083A70 21200002 */   addu      $a0, $s0, $zero
/* 5AF383C 80083A74 50000224 */  addiu      $v0, $zero, 0x50
/* 5AF3840 80083A78 34100208 */  j          .Llevel_64_800840D0
/* 5AF3844 80083A7C 0C0002AE */   sw        $v0, 0xC($s0)
.Llevel_64_80083A80:
/* 5AF3848 80083A80 C8E9000C */  jal        func_8003A720
/* 5AF384C 80083A84 21208002 */   addu      $a0, $s4, $zero
/* 5AF3850 80083A88 20000224 */  addiu      $v0, $zero, 0x20
/* 5AF3854 80083A8C 500082A2 */  sb         $v0, 0x50($s4)
/* 5AF3858 80083A90 FF000224 */  addiu      $v0, $zero, 0xFF
/* 5AF385C 80083A94 0400A012 */  beqz       $s5, .Llevel_64_80083AA8
/* 5AF3860 80083A98 520082A2 */   sb        $v0, 0x52($s4)
/* 5AF3864 80083A9C 0C008426 */  addiu      $a0, $s4, 0xC
/* 5AF3868 80083AA0 C05D000C */  jal        VecCopy
/* 5AF386C 80083AA4 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_64_80083AA8:
/* 5AF3870 80083AA8 734A010C */  jal        func_800529CC
/* 5AF3874 80083AAC 21208002 */   addu      $a0, $s4, $zero
/* 5AF3878 80083AB0 35100208 */  j          .Llevel_64_800840D4
/* 5AF387C 80083AB4 21108002 */   addu      $v0, $s4, $zero
.Llevel_64_80083AB8:
/* 5AF3880 80083AB8 0000908E */  lw         $s0, 0x0($s4)
/* 5AF3884 80083ABC C8E9000C */  jal        func_8003A720
/* 5AF3888 80083AC0 21208002 */   addu      $a0, $s4, $zero
/* 5AF388C 80083AC4 8C000224 */  addiu      $v0, $zero, 0x8C
/* 5AF3890 80083AC8 000000AE */  sw         $zero, 0x0($s0)
/* 5AF3894 80083ACC 040000AE */  sw         $zero, 0x4($s0)
/* 5AF3898 80083AD0 080002AE */  sw         $v0, 0x8($s0)
/* 5AF389C 80083AD4 0E0000A2 */  sb         $zero, 0xE($s0)
/* 5AF38A0 80083AD8 0F0000A2 */  sb         $zero, 0xF($s0)
/* 5AF38A4 80083ADC 110000A2 */  sb         $zero, 0x11($s0)
/* 5AF38A8 80083AE0 120000A2 */  sb         $zero, 0x12($s0)
/* 5AF38AC 80083AE4 130000A2 */  sb         $zero, 0x13($s0)
/* 5AF38B0 80083AE8 3600A386 */  lh         $v1, 0x36($s5)
/* 5AF38B4 80083AEC 0D000224 */  addiu      $v0, $zero, 0xD
/* 5AF38B8 80083AF0 02006214 */  bne        $v1, $v0, .Llevel_64_80083AFC
/* 5AF38BC 80083AF4 03000224 */   addiu     $v0, $zero, 0x3
/* 5AF38C0 80083AF8 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_64_80083AFC:
/* 5AF38C4 80083AFC 100002A2 */  sb         $v0, 0x10($s0)
/* 5AF38C8 80083B00 0C009126 */  addiu      $s1, $s4, 0xC
/* 5AF38CC 80083B04 21202002 */  addu       $a0, $s1, $zero
/* 5AF38D0 80083B08 0C00A526 */  addiu      $a1, $s5, 0xC
/* 5AF38D4 80083B0C FF000224 */  addiu      $v0, $zero, 0xFF
/* 5AF38D8 80083B10 02001224 */  addiu      $s2, $zero, 0x2
/* 5AF38DC 80083B14 140002A2 */  sb         $v0, 0x14($s0)
/* 5AF38E0 80083B18 18000224 */  addiu      $v0, $zero, 0x18
/* 5AF38E4 80083B1C 500082A2 */  sb         $v0, 0x50($s4)
/* 5AF38E8 80083B20 40000224 */  addiu      $v0, $zero, 0x40
/* 5AF38EC 80083B24 520082A2 */  sb         $v0, 0x52($s4)
/* 5AF38F0 80083B28 20000224 */  addiu      $v0, $zero, 0x20
/* 5AF38F4 80083B2C 490092A2 */  sb         $s2, 0x49($s4)
/* 5AF38F8 80083B30 440082A2 */  sb         $v0, 0x44($s4)
/* 5AF38FC 80083B34 450080A2 */  sb         $zero, 0x45($s4)
/* 5AF3900 80083B38 C05D000C */  jal        VecCopy
/* 5AF3904 80083B3C 460080A2 */   sb        $zero, 0x46($s4)
/* 5AF3908 80083B40 734A010C */  jal        func_800529CC
/* 5AF390C 80083B44 21208002 */   addu      $a0, $s4, $zero
/* 5AF3910 80083B48 2000B027 */  addiu      $s0, $sp, 0x20
/* 5AF3914 80083B4C 21200002 */  addu       $a0, $s0, $zero
/* 5AF3918 80083B50 21282002 */  addu       $a1, $s1, $zero
/* 5AF391C 80083B54 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 5AF3920 80083B58 C05D000C */  jal        VecCopy
/* 5AF3924 80083B5C 1C0082AE */   sw        $v0, 0x1C($s4)
/* 5AF3928 80083B60 21200002 */  addu       $a0, $s0, $zero
/* 5AF392C 80083B64 2800A28F */  lw         $v0, 0x28($sp)
/* 5AF3930 80083B68 0100053C */  lui        $a1, (0x10000 >> 16)
/* 5AF3934 80083B6C 00044224 */  addiu      $v0, $v0, 0x400
/* 5AF3938 80083B70 7B35010C */  jal        func_8004D5EC
/* 5AF393C 80083B74 2800A2AF */   sw        $v0, 0x28($sp)
/* 5AF3940 80083B78 F44C010C */  jal        func_800533D0
/* 5AF3944 80083B7C 21208002 */   addu      $a0, $s4, $zero
/* 5AF3948 80083B80 36008386 */  lh         $v1, 0x36($s4)
/* 5AF394C 80083B84 0E000224 */  addiu      $v0, $zero, 0xE
/* 5AF3950 80083B88 4C0080A2 */  sb         $zero, 0x4C($s4)
/* 5AF3954 80083B8C 4D0080A2 */  sb         $zero, 0x4D($s4)
/* 5AF3958 80083B90 03006214 */  bne        $v1, $v0, .Llevel_64_80083BA0
/* 5AF395C 80083B94 4E0080A2 */   sb        $zero, 0x4E($s4)
/* 5AF3960 80083B98 0C000224 */  addiu      $v0, $zero, 0xC
/* 5AF3964 80083B9C 4F0082A2 */  sb         $v0, 0x4F($s4)
.Llevel_64_80083BA0:
/* 5AF3968 80083BA0 36008386 */  lh         $v1, 0x36($s4)
/* 5AF396C 80083BA4 53000224 */  addiu      $v0, $zero, 0x53
/* 5AF3970 80083BA8 05006214 */  bne        $v1, $v0, .Llevel_64_80083BC0
/* 5AF3974 80083BAC 54000224 */   addiu     $v0, $zero, 0x54
/* 5AF3978 80083BB0 01000224 */  addiu      $v0, $zero, 0x1
/* 5AF397C 80083BB4 4F0082A2 */  sb         $v0, 0x4F($s4)
/* 5AF3980 80083BB8 36008386 */  lh         $v1, 0x36($s4)
/* 5AF3984 80083BBC 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_64_80083BC0:
/* 5AF3988 80083BC0 02006214 */  bne        $v1, $v0, .Llevel_64_80083BCC
/* 5AF398C 80083BC4 00000000 */   nop
/* 5AF3990 80083BC8 4F0092A2 */  sb         $s2, 0x4F($s4)
.Llevel_64_80083BCC:
/* 5AF3994 80083BCC 36008386 */  lh         $v1, 0x36($s4)
/* 5AF3998 80083BD0 55000224 */  addiu      $v0, $zero, 0x55
/* 5AF399C 80083BD4 05006214 */  bne        $v1, $v0, .Llevel_64_80083BEC
/* 5AF39A0 80083BD8 56000224 */   addiu     $v0, $zero, 0x56
/* 5AF39A4 80083BDC 03000224 */  addiu      $v0, $zero, 0x3
/* 5AF39A8 80083BE0 4F0082A2 */  sb         $v0, 0x4F($s4)
/* 5AF39AC 80083BE4 36008386 */  lh         $v1, 0x36($s4)
/* 5AF39B0 80083BE8 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_64_80083BEC:
/* 5AF39B4 80083BEC 02006214 */  bne        $v1, $v0, .Llevel_64_80083BF8
/* 5AF39B8 80083BF0 04000224 */   addiu     $v0, $zero, 0x4
/* 5AF39BC 80083BF4 4F0082A2 */  sb         $v0, 0x4F($s4)
.Llevel_64_80083BF8:
/* 5AF39C0 80083BF8 36008386 */  lh         $v1, 0x36($s4)
/* 5AF39C4 80083BFC 57000224 */  addiu      $v0, $zero, 0x57
/* 5AF39C8 80083C00 34016214 */  bne        $v1, $v0, .Llevel_64_800840D4
/* 5AF39CC 80083C04 21108002 */   addu      $v0, $s4, $zero
/* 5AF39D0 80083C08 05000224 */  addiu      $v0, $zero, 0x5
/* 5AF39D4 80083C0C 34100208 */  j          .Llevel_64_800840D0
/* 5AF39D8 80083C10 4F0082A2 */   sb        $v0, 0x4F($s4)
.Llevel_64_80083C14:
/* 5AF39DC 80083C14 0000908E */  lw         $s0, 0x0($s4)
/* 5AF39E0 80083C18 C8E9000C */  jal        func_8003A720
/* 5AF39E4 80083C1C 21208002 */   addu      $a0, $s4, $zero
/* 5AF39E8 80083C20 AA49010C */  jal        func_800526A8
/* 5AF39EC 80083C24 21208002 */   addu      $a0, $s4, $zero
/* 5AF39F0 80083C28 490080A2 */  sb         $zero, 0x49($s4)
/* 5AF39F4 80083C2C 000000AE */  sw         $zero, 0x0($s0)
/* 5AF39F8 80083C30 080000A6 */  sh         $zero, 0x8($s0)
/* 5AF39FC 80083C34 060000A6 */  sh         $zero, 0x6($s0)
/* 5AF3A00 80083C38 040000A6 */  sh         $zero, 0x4($s0)
/* 5AF3A04 80083C3C 0C0000AE */  sw         $zero, 0xC($s0)
/* 5AF3A08 80083C40 2301A012 */  beqz       $s5, .Llevel_64_800840D0
/* 5AF3A0C 80083C44 100000AE */   sw        $zero, 0x10($s0)
/* 5AF3A10 80083C48 0C008426 */  addiu      $a0, $s4, 0xC
/* 5AF3A14 80083C4C C05D000C */  jal        VecCopy
/* 5AF3A18 80083C50 0C00A526 */   addiu     $a1, $s5, 0xC
/* 5AF3A1C 80083C54 35100208 */  j          .Llevel_64_800840D4
/* 5AF3A20 80083C58 21108002 */   addu      $v0, $s4, $zero
.Llevel_64_80083C5C:
/* 5AF3A24 80083C5C C8E9000C */  jal        func_8003A720
/* 5AF3A28 80083C60 21208002 */   addu      $a0, $s4, $zero
/* 5AF3A2C 80083C64 21208002 */  addu       $a0, $s4, $zero
/* 5AF3A30 80083C68 20000224 */  addiu      $v0, $zero, 0x20
/* 5AF3A34 80083C6C 500082A2 */  sb         $v0, 0x50($s4)
/* 5AF3A38 80083C70 FF000224 */  addiu      $v0, $zero, 0xFF
/* 5AF3A3C 80083C74 734A010C */  jal        func_800529CC
/* 5AF3A40 80083C78 520082A2 */   sb        $v0, 0x52($s4)
/* 5AF3A44 80083C7C 0D000224 */  addiu      $v0, $zero, 0xD
/* 5AF3A48 80083C80 4C0080A2 */  sb         $zero, 0x4C($s4)
/* 5AF3A4C 80083C84 4D0080A2 */  sb         $zero, 0x4D($s4)
/* 5AF3A50 80083C88 4E0080A2 */  sb         $zero, 0x4E($s4)
/* 5AF3A54 80083C8C 34100208 */  j          .Llevel_64_800840D0
/* 5AF3A58 80083C90 4F0082A2 */   sb        $v0, 0x4F($s4)
.Llevel_64_80083C94:
/* 5AF3A5C 80083C94 0000938E */  lw         $s3, 0x0($s4)
/* 5AF3A60 80083C98 C8E9000C */  jal        func_8003A720
/* 5AF3A64 80083C9C 21208002 */   addu      $a0, $s4, $zero
/* 5AF3A68 80083CA0 0C008426 */  addiu      $a0, $s4, 0xC
/* 5AF3A6C 80083CA4 0C00A526 */  addiu      $a1, $s5, 0xC
/* 5AF3A70 80083CA8 20000224 */  addiu      $v0, $zero, 0x20
/* 5AF3A74 80083CAC C05D000C */  jal        VecCopy
/* 5AF3A78 80083CB0 500082A2 */   sb        $v0, 0x50($s4)
/* 5AF3A7C 80083CB4 AA49010C */  jal        func_800526A8
/* 5AF3A80 80083CB8 21208002 */   addu      $a0, $s4, $zero
/* 5AF3A84 80083CBC CB89010C */  jal        rand
/* 5AF3A88 80083CC0 00000000 */   nop
/* 5AF3A8C 80083CC4 CB89010C */  jal        rand
/* 5AF3A90 80083CC8 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 5AF3A94 80083CCC FF075130 */  andi       $s1, $v0, 0x7FF
/* 5AF3A98 80083CD0 2C5B000C */  jal        Cos
/* 5AF3A9C 80083CD4 21202002 */   addu      $a0, $s1, $zero
/* 5AF3AA0 80083CD8 21204002 */  addu       $a0, $s2, $zero
/* 5AF3AA4 80083CDC 2C5B000C */  jal        Cos
/* 5AF3AA8 80083CE0 21804000 */   addu      $s0, $v0, $zero
/* 5AF3AAC 80083CE4 43811000 */  sra        $s0, $s0, 5
/* 5AF3AB0 80083CE8 18000202 */  mult       $s0, $v0
/* 5AF3AB4 80083CEC 21202002 */  addu       $a0, $s1, $zero
/* 5AF3AB8 80083CF0 12380000 */  mflo       $a3
/* 5AF3ABC 80083CF4 03130700 */  sra        $v0, $a3, 12
/* 5AF3AC0 80083CF8 2C5B000C */  jal        Cos
/* 5AF3AC4 80083CFC 000062A6 */   sh        $v0, 0x0($s3)
/* 5AF3AC8 80083D00 21204002 */  addu       $a0, $s2, $zero
/* 5AF3ACC 80083D04 165B000C */  jal        Sin
/* 5AF3AD0 80083D08 21804000 */   addu      $s0, $v0, $zero
/* 5AF3AD4 80083D0C 43811000 */  sra        $s0, $s0, 5
/* 5AF3AD8 80083D10 18000202 */  mult       $s0, $v0
/* 5AF3ADC 80083D14 21202002 */  addu       $a0, $s1, $zero
/* 5AF3AE0 80083D18 12380000 */  mflo       $a3
/* 5AF3AE4 80083D1C 03130700 */  sra        $v0, $a3, 12
/* 5AF3AE8 80083D20 165B000C */  jal        Sin
/* 5AF3AEC 80083D24 020062A6 */   sh        $v0, 0x2($s3)
/* 5AF3AF0 80083D28 43110200 */  sra        $v0, $v0, 5
/* 5AF3AF4 80083D2C 040062A6 */  sh         $v0, 0x4($s3)
/* 5AF3AF8 80083D30 1800A28E */  lw         $v0, 0x18($s5)
/* 5AF3AFC 80083D34 0200033C */  lui        $v1, (0x20000 >> 16)
/* 5AF3B00 80083D38 24104300 */  and        $v0, $v0, $v1
/* 5AF3B04 80083D3C 13004010 */  beqz       $v0, .Llevel_64_80083D8C
/* 5AF3B08 80083D40 00000000 */   nop
/* 5AF3B0C 80083D44 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 5AF3B10 80083D48 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 5AF3B14 80083D4C 00006396 */  lhu        $v1, 0x0($s3)
/* 5AF3B18 80083D50 83110200 */  sra        $v0, $v0, 6
/* 5AF3B1C 80083D54 21186200 */  addu       $v1, $v1, $v0
/* 5AF3B20 80083D58 000063A6 */  sh         $v1, 0x0($s3)
/* 5AF3B24 80083D5C 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 5AF3B28 80083D60 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 5AF3B2C 80083D64 02006396 */  lhu        $v1, 0x2($s3)
/* 5AF3B30 80083D68 83110200 */  sra        $v0, $v0, 6
/* 5AF3B34 80083D6C 21186200 */  addu       $v1, $v1, $v0
/* 5AF3B38 80083D70 020063A6 */  sh         $v1, 0x2($s3)
/* 5AF3B3C 80083D74 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 5AF3B40 80083D78 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 5AF3B44 80083D7C 04006396 */  lhu        $v1, 0x4($s3)
/* 5AF3B48 80083D80 83110200 */  sra        $v0, $v0, 6
/* 5AF3B4C 80083D84 21186200 */  addu       $v1, $v1, $v0
/* 5AF3B50 80083D88 040063A6 */  sh         $v1, 0x4($s3)
.Llevel_64_80083D8C:
/* 5AF3B54 80083D8C 00006286 */  lh         $v0, 0x0($s3)
/* 5AF3B58 80083D90 0C00838E */  lw         $v1, 0xC($s4)
/* 5AF3B5C 80083D94 80100200 */  sll        $v0, $v0, 2
/* 5AF3B60 80083D98 21186200 */  addu       $v1, $v1, $v0
/* 5AF3B64 80083D9C 0C0083AE */  sw         $v1, 0xC($s4)
/* 5AF3B68 80083DA0 02006286 */  lh         $v0, 0x2($s3)
/* 5AF3B6C 80083DA4 1000838E */  lw         $v1, 0x10($s4)
/* 5AF3B70 80083DA8 80100200 */  sll        $v0, $v0, 2
/* 5AF3B74 80083DAC 21186200 */  addu       $v1, $v1, $v0
/* 5AF3B78 80083DB0 100083AE */  sw         $v1, 0x10($s4)
/* 5AF3B7C 80083DB4 04006286 */  lh         $v0, 0x4($s3)
/* 5AF3B80 80083DB8 1400838E */  lw         $v1, 0x14($s4)
/* 5AF3B84 80083DBC 80100200 */  sll        $v0, $v0, 2
/* 5AF3B88 80083DC0 21186200 */  addu       $v1, $v1, $v0
/* 5AF3B8C 80083DC4 CB89010C */  jal        rand
/* 5AF3B90 80083DC8 140083AE */   sw        $v1, 0x14($s4)
/* 5AF3B94 80083DCC 0F004230 */  andi       $v0, $v0, 0xF
/* 5AF3B98 80083DD0 CB89010C */  jal        rand
/* 5AF3B9C 80083DD4 060062A6 */   sh        $v0, 0x6($s3)
/* 5AF3BA0 80083DD8 0F004230 */  andi       $v0, $v0, 0xF
/* 5AF3BA4 80083DDC CB89010C */  jal        rand
/* 5AF3BA8 80083DE0 080062A6 */   sh        $v0, 0x8($s3)
/* 5AF3BAC 80083DE4 0F004230 */  andi       $v0, $v0, 0xF
/* 5AF3BB0 80083DE8 0A0062A6 */  sh         $v0, 0xA($s3)
/* 5AF3BB4 80083DEC 1400A28E */  lw         $v0, 0x14($s5)
/* 5AF3BB8 80083DF0 00000000 */  nop
/* 5AF3BBC 80083DF4 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 5AF3BC0 80083DF8 CB89010C */  jal        rand
/* 5AF3BC4 80083DFC 100062AE */   sw        $v0, 0x10($s3)
/* 5AF3BC8 80083E00 0F004230 */  andi       $v0, $v0, 0xF
/* 5AF3BCC 80083E04 40000324 */  addiu      $v1, $zero, 0x40
/* 5AF3BD0 80083E08 23186200 */  subu       $v1, $v1, $v0
/* 5AF3BD4 80083E0C 0C0063AE */  sw         $v1, 0xC($s3)
/* 5AF3BD8 80083E10 36008296 */  lhu        $v0, 0x36($s4)
/* 5AF3BDC 80083E14 00000000 */  nop
/* 5AF3BE0 80083E18 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 5AF3BE4 80083E1C 0300422C */  sltiu      $v0, $v0, 0x3
/* 5AF3BE8 80083E20 AB004010 */  beqz       $v0, .Llevel_64_800840D0
/* 5AF3BEC 80083E24 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 5AF3BF0 80083E28 4B008292 */  lbu        $v0, 0x4B($s4)
/* 5AF3BF4 80083E2C 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 5AF3BF8 80083E30 4C0083AE */  sw         $v1, 0x4C($s4)
.Llevel_64_80083E34:
/* 5AF3BFC 80083E34 80004234 */  ori        $v0, $v0, 0x80
/* 5AF3C00 80083E38 34100208 */  j          .Llevel_64_800840D0
/* 5AF3C04 80083E3C 4B0082A2 */   sb        $v0, 0x4B($s4)
.Llevel_64_80083E40:
/* 5AF3C08 80083E40 0000918E */  lw         $s1, 0x0($s4)
/* 5AF3C0C 80083E44 C8E9000C */  jal        func_8003A720
/* 5AF3C10 80083E48 21208002 */   addu      $a0, $s4, $zero
/* 5AF3C14 80083E4C 0C008426 */  addiu      $a0, $s4, 0xC
/* 5AF3C18 80083E50 0C00A526 */  addiu      $a1, $s5, 0xC
/* 5AF3C1C 80083E54 20000224 */  addiu      $v0, $zero, 0x20
/* 5AF3C20 80083E58 C05D000C */  jal        VecCopy
/* 5AF3C24 80083E5C 500082A2 */   sb        $v0, 0x50($s4)
/* 5AF3C28 80083E60 AA49010C */  jal        func_800526A8
/* 5AF3C2C 80083E64 21208002 */   addu      $a0, $s4, $zero
/* 5AF3C30 80083E68 CB89010C */  jal        rand
/* 5AF3C34 80083E6C 00000000 */   nop
/* 5AF3C38 80083E70 CB89010C */  jal        rand
/* 5AF3C3C 80083E74 FF0F5330 */   andi      $s3, $v0, 0xFFF
/* 5AF3C40 80083E78 FF075230 */  andi       $s2, $v0, 0x7FF
/* 5AF3C44 80083E7C 2C5B000C */  jal        Cos
/* 5AF3C48 80083E80 21204002 */   addu      $a0, $s2, $zero
/* 5AF3C4C 80083E84 21206002 */  addu       $a0, $s3, $zero
/* 5AF3C50 80083E88 2C5B000C */  jal        Cos
/* 5AF3C54 80083E8C 21804000 */   addu      $s0, $v0, $zero
/* 5AF3C58 80083E90 43811000 */  sra        $s0, $s0, 5
/* 5AF3C5C 80083E94 18000202 */  mult       $s0, $v0
/* 5AF3C60 80083E98 21204002 */  addu       $a0, $s2, $zero
/* 5AF3C64 80083E9C 12380000 */  mflo       $a3
/* 5AF3C68 80083EA0 03130700 */  sra        $v0, $a3, 12
/* 5AF3C6C 80083EA4 2C5B000C */  jal        Cos
/* 5AF3C70 80083EA8 000022A6 */   sh        $v0, 0x0($s1)
/* 5AF3C74 80083EAC 21206002 */  addu       $a0, $s3, $zero
/* 5AF3C78 80083EB0 165B000C */  jal        Sin
/* 5AF3C7C 80083EB4 21804000 */   addu      $s0, $v0, $zero
/* 5AF3C80 80083EB8 43811000 */  sra        $s0, $s0, 5
/* 5AF3C84 80083EBC 18000202 */  mult       $s0, $v0
/* 5AF3C88 80083EC0 21204002 */  addu       $a0, $s2, $zero
/* 5AF3C8C 80083EC4 12380000 */  mflo       $a3
/* 5AF3C90 80083EC8 03130700 */  sra        $v0, $a3, 12
/* 5AF3C94 80083ECC 165B000C */  jal        Sin
/* 5AF3C98 80083ED0 020022A6 */   sh        $v0, 0x2($s1)
/* 5AF3C9C 80083ED4 43110200 */  sra        $v0, $v0, 5
/* 5AF3CA0 80083ED8 040022A6 */  sh         $v0, 0x4($s1)
/* 5AF3CA4 80083EDC 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 5AF3CA8 80083EE0 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 5AF3CAC 80083EE4 00002396 */  lhu        $v1, 0x0($s1)
/* 5AF3CB0 80083EE8 83110200 */  sra        $v0, $v0, 6
/* 5AF3CB4 80083EEC 21186200 */  addu       $v1, $v1, $v0
/* 5AF3CB8 80083EF0 000023A6 */  sh         $v1, 0x0($s1)
/* 5AF3CBC 80083EF4 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 5AF3CC0 80083EF8 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 5AF3CC4 80083EFC 02002396 */  lhu        $v1, 0x2($s1)
/* 5AF3CC8 80083F00 83110200 */  sra        $v0, $v0, 6
/* 5AF3CCC 80083F04 21186200 */  addu       $v1, $v1, $v0
/* 5AF3CD0 80083F08 020023A6 */  sh         $v1, 0x2($s1)
/* 5AF3CD4 80083F0C 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 5AF3CD8 80083F10 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 5AF3CDC 80083F14 04002396 */  lhu        $v1, 0x4($s1)
/* 5AF3CE0 80083F18 83110200 */  sra        $v0, $v0, 6
/* 5AF3CE4 80083F1C 21186200 */  addu       $v1, $v1, $v0
/* 5AF3CE8 80083F20 00002286 */  lh         $v0, 0x0($s1)
/* 5AF3CEC 80083F24 040023A6 */  sh         $v1, 0x4($s1)
/* 5AF3CF0 80083F28 0C00838E */  lw         $v1, 0xC($s4)
/* 5AF3CF4 80083F2C 80100200 */  sll        $v0, $v0, 2
/* 5AF3CF8 80083F30 21186200 */  addu       $v1, $v1, $v0
/* 5AF3CFC 80083F34 0C0083AE */  sw         $v1, 0xC($s4)
/* 5AF3D00 80083F38 02002286 */  lh         $v0, 0x2($s1)
/* 5AF3D04 80083F3C 1000838E */  lw         $v1, 0x10($s4)
/* 5AF3D08 80083F40 80100200 */  sll        $v0, $v0, 2
/* 5AF3D0C 80083F44 21186200 */  addu       $v1, $v1, $v0
/* 5AF3D10 80083F48 100083AE */  sw         $v1, 0x10($s4)
/* 5AF3D14 80083F4C 04002286 */  lh         $v0, 0x4($s1)
/* 5AF3D18 80083F50 1400838E */  lw         $v1, 0x14($s4)
/* 5AF3D1C 80083F54 80100200 */  sll        $v0, $v0, 2
/* 5AF3D20 80083F58 21186200 */  addu       $v1, $v1, $v0
/* 5AF3D24 80083F5C CB89010C */  jal        rand
/* 5AF3D28 80083F60 140083AE */   sw        $v1, 0x14($s4)
/* 5AF3D2C 80083F64 0F004230 */  andi       $v0, $v0, 0xF
/* 5AF3D30 80083F68 CB89010C */  jal        rand
/* 5AF3D34 80083F6C 060022A6 */   sh        $v0, 0x6($s1)
/* 5AF3D38 80083F70 0F004230 */  andi       $v0, $v0, 0xF
/* 5AF3D3C 80083F74 CB89010C */  jal        rand
/* 5AF3D40 80083F78 080022A6 */   sh        $v0, 0x8($s1)
/* 5AF3D44 80083F7C 0F004230 */  andi       $v0, $v0, 0xF
/* 5AF3D48 80083F80 0A0022A6 */  sh         $v0, 0xA($s1)
/* 5AF3D4C 80083F84 1400A28E */  lw         $v0, 0x14($s5)
/* 5AF3D50 80083F88 00000000 */  nop
/* 5AF3D54 80083F8C C0FF4224 */  addiu      $v0, $v0, -0x40
/* 5AF3D58 80083F90 CB89010C */  jal        rand
/* 5AF3D5C 80083F94 100022AE */   sw        $v0, 0x10($s1)
/* 5AF3D60 80083F98 0F004230 */  andi       $v0, $v0, 0xF
/* 5AF3D64 80083F9C 40000324 */  addiu      $v1, $zero, 0x40
/* 5AF3D68 80083FA0 23186200 */  subu       $v1, $v1, $v0
/* 5AF3D6C 80083FA4 34100208 */  j          .Llevel_64_800840D0
/* 5AF3D70 80083FA8 0C0023AE */   sw        $v1, 0xC($s1)
.Llevel_64_80083FAC:
/* 5AF3D74 80083FAC 0000908E */  lw         $s0, 0x0($s4)
/* 5AF3D78 80083FB0 C8E9000C */  jal        func_8003A720
/* 5AF3D7C 80083FB4 21208002 */   addu      $a0, $s4, $zero
/* 5AF3D80 80083FB8 734A010C */  jal        func_800529CC
/* 5AF3D84 80083FBC 21208002 */   addu      $a0, $s4, $zero
/* 5AF3D88 80083FC0 02000224 */  addiu      $v0, $zero, 0x2
/* 5AF3D8C 80083FC4 4F0082A2 */  sb         $v0, 0x4F($s4)
/* 5AF3D90 80083FC8 40000224 */  addiu      $v0, $zero, 0x40
/* 5AF3D94 80083FCC 4C0080A2 */  sb         $zero, 0x4C($s4)
/* 5AF3D98 80083FD0 4D0080A2 */  sb         $zero, 0x4D($s4)
/* 5AF3D9C 80083FD4 4E0080A2 */  sb         $zero, 0x4E($s4)
/* 5AF3DA0 80083FD8 34100208 */  j          .Llevel_64_800840D0
/* 5AF3DA4 80083FDC 000002AE */   sw        $v0, 0x0($s0)
.Llevel_64_80083FE0:
/* 5AF3DA8 80083FE0 C8E9000C */  jal        func_8003A720
/* 5AF3DAC 80083FE4 21208002 */   addu      $a0, $s4, $zero
/* 5AF3DB0 80083FE8 05000224 */  addiu      $v0, $zero, 0x5
/* 5AF3DB4 80083FEC 3100A012 */  beqz       $s5, .Llevel_64_800840B4
/* 5AF3DB8 80083FF0 470082A2 */   sb        $v0, 0x47($s4)
/* 5AF3DBC 80083FF4 0C008426 */  addiu      $a0, $s4, 0xC
/* 5AF3DC0 80083FF8 30100208 */  j          .Llevel_64_800840C0
/* 5AF3DC4 80083FFC 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_64_80084000:
/* 5AF3DC8 80084000 C8E9000C */  jal        func_8003A720
/* 5AF3DCC 80084004 21208002 */   addu      $a0, $s4, $zero
/* 5AF3DD0 80084008 0300A012 */  beqz       $s5, .Llevel_64_80084018
/* 5AF3DD4 8008400C 0C008426 */   addiu     $a0, $s4, 0xC
/* 5AF3DD8 80084010 08100208 */  j          .Llevel_64_80084020
/* 5AF3DDC 80084014 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_64_80084018:
/* 5AF3DE0 80084018 0880053C */  lui        $a1, %hi(g_Spyro)
/* 5AF3DE4 8008401C 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_64_80084020:
/* 5AF3DE8 80084020 C05D000C */  jal        VecCopy
/* 5AF3DEC 80084024 00000000 */   nop
/* 5AF3DF0 80084028 0C008426 */  addiu      $a0, $s4, 0xC
/* 5AF3DF4 8008402C 1400828E */  lw         $v0, 0x14($s4)
/* 5AF3DF8 80084030 00080524 */  addiu      $a1, $zero, 0x800
/* 5AF3DFC 80084034 00024224 */  addiu      $v0, $v0, 0x200
/* 5AF3E00 80084038 7B35010C */  jal        func_8004D5EC
/* 5AF3E04 8008403C 140082AE */   sw        $v0, 0x14($s4)
/* 5AF3E08 80084040 1400848E */  lw         $a0, 0x14($s4)
/* 5AF3E0C 80084044 21184000 */  addu       $v1, $v0, $zero
/* 5AF3E10 80084048 23106400 */  subu       $v0, $v1, $a0
/* 5AF3E14 8008404C 02004104 */  bgez       $v0, .Llevel_64_80084058
/* 5AF3E18 80084050 00000000 */   nop
/* 5AF3E1C 80084054 23100200 */  negu       $v0, $v0
.Llevel_64_80084058:
/* 5AF3E20 80084058 00084228 */  slti       $v0, $v0, 0x800
/* 5AF3E24 8008405C 03004010 */  beqz       $v0, .Llevel_64_8008406C
/* 5AF3E28 80084060 00FE8224 */   addiu     $v0, $a0, -0x200
/* 5AF3E2C 80084064 32100208 */  j          .Llevel_64_800840C8
/* 5AF3E30 80084068 140083AE */   sw        $v1, 0x14($s4)
.Llevel_64_8008406C:
/* 5AF3E34 8008406C 32100208 */  j          .Llevel_64_800840C8
/* 5AF3E38 80084070 140082AE */   sw        $v0, 0x14($s4)
.Llevel_64_80084074:
/* 5AF3E3C 80084074 C8E9000C */  jal        func_8003A720
/* 5AF3E40 80084078 21208002 */   addu      $a0, $s4, $zero
/* 5AF3E44 8008407C 21208002 */  addu       $a0, $s4, $zero
/* 5AF3E48 80084080 20000224 */  addiu      $v0, $zero, 0x20
/* 5AF3E4C 80084084 500082A2 */  sb         $v0, 0x50($s4)
/* 5AF3E50 80084088 FF000224 */  addiu      $v0, $zero, 0xFF
/* 5AF3E54 8008408C 734A010C */  jal        func_800529CC
/* 5AF3E58 80084090 520082A2 */   sb        $v0, 0x52($s4)
/* 5AF3E5C 80084094 35100208 */  j          .Llevel_64_800840D4
/* 5AF3E60 80084098 21108002 */   addu      $v0, $s4, $zero
.Llevel_64_8008409C:
/* 5AF3E64 8008409C C8E9000C */  jal        func_8003A720
/* 5AF3E68 800840A0 21208002 */   addu      $a0, $s4, $zero
/* 5AF3E6C 800840A4 0300A012 */  beqz       $s5, .Llevel_64_800840B4
/* 5AF3E70 800840A8 0C00A526 */   addiu     $a1, $s5, 0xC
/* 5AF3E74 800840AC 30100208 */  j          .Llevel_64_800840C0
/* 5AF3E78 800840B0 0C008426 */   addiu     $a0, $s4, 0xC
.Llevel_64_800840B4:
/* 5AF3E7C 800840B4 0C008426 */  addiu      $a0, $s4, 0xC
/* 5AF3E80 800840B8 0880053C */  lui        $a1, %hi(g_Spyro)
/* 5AF3E84 800840BC 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_64_800840C0:
/* 5AF3E88 800840C0 C05D000C */  jal        VecCopy
/* 5AF3E8C 800840C4 00000000 */   nop
.Llevel_64_800840C8:
/* 5AF3E90 800840C8 AA49010C */  jal        func_800526A8
/* 5AF3E94 800840CC 21208002 */   addu      $a0, $s4, $zero
.Llevel_64_800840D0:
/* 5AF3E98 800840D0 21108002 */  addu       $v0, $s4, $zero
.Llevel_64_800840D4:
/* 5AF3E9C 800840D4 4800BF8F */  lw         $ra, 0x48($sp)
/* 5AF3EA0 800840D8 4400B58F */  lw         $s5, 0x44($sp)
/* 5AF3EA4 800840DC 4000B48F */  lw         $s4, 0x40($sp)
/* 5AF3EA8 800840E0 3C00B38F */  lw         $s3, 0x3C($sp)
/* 5AF3EAC 800840E4 3800B28F */  lw         $s2, 0x38($sp)
/* 5AF3EB0 800840E8 3400B18F */  lw         $s1, 0x34($sp)
/* 5AF3EB4 800840EC 3000B08F */  lw         $s0, 0x30($sp)
/* 5AF3EB8 800840F0 5000BD27 */  addiu      $sp, $sp, 0x50
/* 5AF3EBC 800840F4 0800E003 */  jr         $ra
/* 5AF3EC0 800840F8 00000000 */   nop
.size func_level_64_80083690, . - func_level_64_80083690
