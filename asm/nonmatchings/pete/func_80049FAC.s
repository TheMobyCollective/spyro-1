.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80049FAC
/* 3A7AC 80049FAC D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 3A7B0 80049FB0 2800B2AF */  sw         $s2, 0x28($sp)
/* 3A7B4 80049FB4 21908000 */  addu       $s2, $a0, $zero
/* 3A7B8 80049FB8 2000B0AF */  sw         $s0, 0x20($sp)
/* 3A7BC 80049FBC 0880103C */  lui        $s0, %hi(g_Spyro + 0x34)
/* 3A7C0 80049FC0 8C8A1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x34)
/* 3A7C4 80049FC4 21200002 */  addu       $a0, $s0, $zero
/* 3A7C8 80049FC8 1000A527 */  addiu      $a1, $sp, 0x10
/* 3A7CC 80049FCC 2130A000 */  addu       $a2, $a1, $zero
/* 3A7D0 80049FD0 9CFE0224 */  addiu      $v0, $zero, -0x164
/* 3A7D4 80049FD4 2C00BFAF */  sw         $ra, 0x2C($sp)
/* 3A7D8 80049FD8 2400B1AF */  sw         $s1, 0x24($sp)
/* 3A7DC 80049FDC 1000A0AF */  sw         $zero, 0x10($sp)
/* 3A7E0 80049FE0 1400A0AF */  sw         $zero, 0x14($sp)
/* 3A7E4 80049FE4 125C000C */  jal        VecRotateByMatrix
/* 3A7E8 80049FE8 1800A2AF */   sw        $v0, 0x18($sp)
/* 3A7EC 80049FEC 1000A427 */  addiu      $a0, $sp, 0x10
/* 3A7F0 80049FF0 21288000 */  addu       $a1, $a0, $zero
/* 3A7F4 80049FF4 D65D000C */  jal        VecAdd
/* 3A7F8 80049FF8 CCFF0626 */   addiu     $a2, $s0, -0x34
/* 3A7FC 80049FFC 0880043C */  lui        $a0, %hi(D_8007AA10 + 0x10)
/* 3A800 8004A000 20AA8424 */  addiu      $a0, $a0, %lo(D_8007AA10 + 0x10)
/* 3A804 8004A004 C05D000C */  jal        VecCopy
/* 3A808 8004A008 1000A527 */   addiu     $a1, $sp, 0x10
/* 3A80C 8004A00C 0880023C */  lui        $v0, %hi(g_Spyro + 0x27)
/* 3A810 8004A010 7F8A4290 */  lbu        $v0, %lo(g_Spyro + 0x27)($v0)
/* 3A814 8004A014 0880043C */  lui        $a0, %hi(g_Spyro + 0xA0)
/* 3A818 8004A018 F88A848C */  lw         $a0, %lo(g_Spyro + 0xA0)($a0)
/* 3A81C 8004A01C 7F00422C */  sltiu      $v0, $v0, 0x7F
/* 3A820 8004A020 0880013C */  lui        $at, %hi(D_8007AA10 + 0x18)
/* 3A824 8004A024 28AA24AC */  sw         $a0, %lo(D_8007AA10 + 0x18)($at)
/* 3A828 8004A028 03004010 */  beqz       $v0, .L8004A038
/* 3A82C 8004A02C 05000224 */   addiu     $v0, $zero, 0x5
/* 3A830 8004A030 0880013C */  lui        $at, %hi(g_Spyro + 0x27)
/* 3A834 8004A034 7F8A22A0 */  sb         $v0, %lo(g_Spyro + 0x27)($at)
.L8004A038:
/* 3A838 8004A038 0880023C */  lui        $v0, %hi(g_Spyro + 0x8)
/* 3A83C 8004A03C 608A428C */  lw         $v0, %lo(g_Spyro + 0x8)($v0)
/* 3A840 8004A040 03000324 */  addiu      $v1, $zero, 0x3
/* 3A844 8004A044 0880013C */  lui        $at, %hi(D_8007AA10 + 0x1C)
/* 3A848 8004A048 2CAA23AC */  sw         $v1, %lo(D_8007AA10 + 0x1C)($at)
/* 3A84C 8004A04C 23104400 */  subu       $v0, $v0, $a0
/* 3A850 8004A050 65034228 */  slti       $v0, $v0, 0x365
/* 3A854 8004A054 03004014 */  bnez       $v0, .L8004A064
/* 3A858 8004A058 05000224 */   addiu     $v0, $zero, 0x5
/* 3A85C 8004A05C 0880013C */  lui        $at, %hi(D_8007AA10 + 0x1C)
/* 3A860 8004A060 2CAA22AC */  sw         $v0, %lo(D_8007AA10 + 0x1C)($at)
.L8004A064:
/* 3A864 8004A064 0780023C */  lui        $v0, %hi(D_80075964)
/* 3A868 8004A068 6459428C */  lw         $v0, %lo(D_80075964)($v0)
/* 3A86C 8004A06C 0880013C */  lui        $at, %hi(D_8007AA10 + 0x24)
/* 3A870 8004A070 34AA20AC */  sw         $zero, %lo(D_8007AA10 + 0x24)($at)
/* 3A874 8004A074 80100200 */  sll        $v0, $v0, 2
/* 3A878 8004A078 0780013C */  lui        $at, %hi(D_8006E9A4)
/* 3A87C 8004A07C 21082200 */  addu       $at, $at, $v0
/* 3A880 8004A080 A4E9228C */  lw         $v0, %lo(D_8006E9A4)($at)
/* 3A884 8004A084 00000000 */  nop
/* 3A888 8004A088 2A104400 */  slt        $v0, $v0, $a0
/* 3A88C 8004A08C 05004010 */  beqz       $v0, .L8004A0A4
/* 3A890 8004A090 01000224 */   addiu     $v0, $zero, 0x1
/* 3A894 8004A094 3C01028E */  lw         $v0, 0x13C($s0)
/* 3A898 8004A098 00000000 */  nop
/* 3A89C 8004A09C 03004010 */  beqz       $v0, .L8004A0AC
/* 3A8A0 8004A0A0 01000224 */   addiu     $v0, $zero, 0x1
.L8004A0A4:
/* 3A8A4 8004A0A4 0880013C */  lui        $at, %hi(D_8007AA10 + 0x24)
/* 3A8A8 8004A0A8 34AA22AC */  sw         $v0, %lo(D_8007AA10 + 0x24)($at)
.L8004A0AC:
/* 3A8AC 8004A0AC 0880113C */  lui        $s1, %hi(D_8007AA10 + 0x20)
/* 3A8B0 8004A0B0 30AA3126 */  addiu      $s1, $s1, %lo(D_8007AA10 + 0x20)
/* 3A8B4 8004A0B4 0000228E */  lw         $v0, 0x0($s1)
/* 3A8B8 8004A0B8 00000000 */  nop
/* 3A8BC 8004A0BC 01004224 */  addiu      $v0, $v0, 0x1
/* 3A8C0 8004A0C0 07004230 */  andi       $v0, $v0, 0x7
/* 3A8C4 8004A0C4 3D004012 */  beqz       $s2, .L8004A1BC
/* 3A8C8 8004A0C8 000022AE */   sw        $v0, 0x0($s1)
/* 3A8CC 8004A0CC 0880103C */  lui        $s0, %hi(g_Spyro + 0x34)
/* 3A8D0 8004A0D0 8C8A1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x34)
/* 3A8D4 8004A0D4 21200002 */  addu       $a0, $s0, $zero
/* 3A8D8 8004A0D8 40280200 */  sll        $a1, $v0, 1
/* 3A8DC 8004A0DC 2128A200 */  addu       $a1, $a1, $v0
/* 3A8E0 8004A0E0 80280500 */  sll        $a1, $a1, 2
/* 3A8E4 8004A0E4 0780023C */  lui        $v0, %hi(D_8006E2A8)
/* 3A8E8 8004A0E8 A8E24224 */  addiu      $v0, $v0, %lo(D_8006E2A8)
/* 3A8EC 8004A0EC 2128A200 */  addu       $a1, $a1, $v0
/* 3A8F0 8004A0F0 125C000C */  jal        VecRotateByMatrix
/* 3A8F4 8004A0F4 1000A627 */   addiu     $a2, $sp, 0x10
/* 3A8F8 8004A0F8 1000A427 */  addiu      $a0, $sp, 0x10
/* 3A8FC 8004A0FC 21288000 */  addu       $a1, $a0, $zero
/* 3A900 8004A100 D65D000C */  jal        VecAdd
/* 3A904 8004A104 CCFF0626 */   addiu     $a2, $s0, -0x34
/* 3A908 8004A108 1000A427 */  addiu      $a0, $sp, 0x10
/* 3A90C 8004A10C 1800A28F */  lw         $v0, 0x18($sp)
/* 3A910 8004A110 00040524 */  addiu      $a1, $zero, 0x400
/* 3A914 8004A114 00024224 */  addiu      $v0, $v0, 0x200
/* 3A918 8004A118 7B35010C */  jal        func_8004D5EC
/* 3A91C 8004A11C 1800A2AF */   sw        $v0, 0x18($sp)
/* 3A920 8004A120 1800A38F */  lw         $v1, 0x18($sp)
/* 3A924 8004A124 21204000 */  addu       $a0, $v0, $zero
/* 3A928 8004A128 00FE6324 */  addiu      $v1, $v1, -0x200
/* 3A92C 8004A12C 1800A3AF */  sw         $v1, 0x18($sp)
/* 3A930 8004A130 23186400 */  subu       $v1, $v1, $a0
/* 3A934 8004A134 80006324 */  addiu      $v1, $v1, 0x80
/* 3A938 8004A138 0001632C */  sltiu      $v1, $v1, 0x100
/* 3A93C 8004A13C 08006014 */  bnez       $v1, .L8004A160
/* 3A940 8004A140 E8FF2326 */   addiu     $v1, $s1, -0x18
/* 3A944 8004A144 0880023C */  lui        $v0, %hi(D_8007AA10 + 0x20)
/* 3A948 8004A148 30AA428C */  lw         $v0, %lo(D_8007AA10 + 0x20)($v0)
/* 3A94C 8004A14C 00000000 */  nop
/* 3A950 8004A150 21104300 */  addu       $v0, $v0, $v1
/* 3A954 8004A154 01000324 */  addiu      $v1, $zero, 0x1
/* 3A958 8004A158 74280108 */  j          .L8004A1D0
/* 3A95C 8004A15C 000043A0 */   sb        $v1, 0x0($v0)
.L8004A160:
/* 3A960 8004A160 0880023C */  lui        $v0, %hi(D_8007AA10 + 0x20)
/* 3A964 8004A164 30AA428C */  lw         $v0, %lo(D_8007AA10 + 0x20)($v0)
/* 3A968 8004A168 00000000 */  nop
/* 3A96C 8004A16C 21104300 */  addu       $v0, $v0, $v1
/* 3A970 8004A170 000040A0 */  sb         $zero, 0x0($v0)
/* 3A974 8004A174 0880033C */  lui        $v1, %hi(D_8007AA10 + 0x18)
/* 3A978 8004A178 28AA638C */  lw         $v1, %lo(D_8007AA10 + 0x18)($v1)
/* 3A97C 8004A17C 00000000 */  nop
/* 3A980 8004A180 23186400 */  subu       $v1, $v1, $a0
/* 3A984 8004A184 40100300 */  sll        $v0, $v1, 1
/* 3A988 8004A188 21104300 */  addu       $v0, $v0, $v1
/* 3A98C 8004A18C 40110200 */  sll        $v0, $v0, 5
/* 3A990 8004A190 21104300 */  addu       $v0, $v0, $v1
/* 3A994 8004A194 40200200 */  sll        $a0, $v0, 1
/* 3A998 8004A198 0880033C */  lui        $v1, %hi(D_8007AA10 + 0x20)
/* 3A99C 8004A19C 30AA638C */  lw         $v1, %lo(D_8007AA10 + 0x20)($v1)
/* 3A9A0 8004A1A0 E0FF2226 */  addiu      $v0, $s1, -0x20
/* 3A9A4 8004A1A4 02008104 */  bgez       $a0, .L8004A1B0
/* 3A9A8 8004A1A8 21186200 */   addu      $v1, $v1, $v0
/* 3A9AC 8004A1AC FF018424 */  addiu      $a0, $a0, 0x1FF
.L8004A1B0:
/* 3A9B0 8004A1B0 43120400 */  sra        $v0, $a0, 9
/* 3A9B4 8004A1B4 79280108 */  j          .L8004A1E4
/* 3A9B8 8004A1B8 000062A0 */   sb        $v0, 0x0($v1)
.L8004A1BC:
/* 3A9BC 8004A1BC 0880023C */  lui        $v0, %hi(D_8007AA10 + 0x20)
/* 3A9C0 8004A1C0 30AA428C */  lw         $v0, %lo(D_8007AA10 + 0x20)($v0)
/* 3A9C4 8004A1C4 E8FF2326 */  addiu      $v1, $s1, -0x18
/* 3A9C8 8004A1C8 21104300 */  addu       $v0, $v0, $v1
/* 3A9CC 8004A1CC 000040A0 */  sb         $zero, 0x0($v0)
.L8004A1D0:
/* 3A9D0 8004A1D0 0880023C */  lui        $v0, %hi(D_8007AA10 + 0x20)
/* 3A9D4 8004A1D4 30AA428C */  lw         $v0, %lo(D_8007AA10 + 0x20)($v0)
/* 3A9D8 8004A1D8 E0FF2326 */  addiu      $v1, $s1, -0x20
/* 3A9DC 8004A1DC 21104300 */  addu       $v0, $v0, $v1
/* 3A9E0 8004A1E0 000040A0 */  sb         $zero, 0x0($v0)
.L8004A1E4:
/* 3A9E4 8004A1E4 2C00BF8F */  lw         $ra, 0x2C($sp)
/* 3A9E8 8004A1E8 2800B28F */  lw         $s2, 0x28($sp)
/* 3A9EC 8004A1EC 2400B18F */  lw         $s1, 0x24($sp)
/* 3A9F0 8004A1F0 2000B08F */  lw         $s0, 0x20($sp)
/* 3A9F4 8004A1F4 3000BD27 */  addiu      $sp, $sp, 0x30
/* 3A9F8 8004A1F8 0800E003 */  jr         $ra
/* 3A9FC 8004A1FC 00000000 */   nop
.size func_80049FAC, . - func_80049FAC
