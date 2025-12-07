.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8004A7EC
/* 3AFEC 8004A7EC A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 3AFF0 8004A7F0 0780043C */  lui        $a0, %hi(g_Pad)
/* 3AFF4 8004A7F4 78738424 */  addiu      $a0, $a0, %lo(g_Pad)
/* 3AFF8 8004A7F8 0780053C */  lui        $a1, %hi(D_800776D8)
/* 3AFFC 8004A7FC D876A524 */  addiu      $a1, $a1, %lo(D_800776D8)
/* 3B000 8004A800 5000BFAF */  sw         $ra, 0x50($sp)
/* 3B004 8004A804 4C00B1AF */  sw         $s1, 0x4C($sp)
/* 3B008 8004A808 4800B0AF */  sw         $s0, 0x48($sp)
/* 3B00C 8004A80C 0780013C */  lui        $at, %hi(D_80075944)
/* 3B010 8004A810 445920A0 */  sb         $zero, %lo(D_80075944)($at)
/* 3B014 8004A814 C24D010C */  jal        func_80053708
/* 3B018 8004A818 00000000 */   nop
/* 3B01C 8004A81C 0880103C */  lui        $s0, %hi(g_Spyro + 0x78)
/* 3B020 8004A820 D08A1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x78)
/* 3B024 8004A824 0000038E */  lw         $v1, 0x0($s0)
/* 3B028 8004A828 0F000224 */  addiu      $v0, $zero, 0xF
/* 3B02C 8004A82C 03006210 */  beq        $v1, $v0, .L8004A83C
/* 3B030 8004A830 00000000 */   nop
/* 3B034 8004A834 9AFA000C */  jal        func_8003EA68
/* 3B038 8004A838 0F000424 */   addiu     $a0, $zero, 0xF
.L8004A83C:
/* 3B03C 8004A83C 0880033C */  lui        $v1, %hi(g_Spyro + 0x1F0)
/* 3B040 8004A840 488C638C */  lw         $v1, %lo(g_Spyro + 0x1F0)($v1)
/* 3B044 8004A844 08000224 */  addiu      $v0, $zero, 0x8
/* 3B048 8004A848 0880013C */  lui        $at, %hi(g_Spyro + 0x7C)
/* 3B04C 8004A84C D48A22AC */  sw         $v0, %lo(g_Spyro + 0x7C)($at)
/* 3B050 8004A850 0300601C */  bgtz       $v1, .L8004A860
/* 3B054 8004A854 01000224 */   addiu     $v0, $zero, 0x1
/* 3B058 8004A858 0880013C */  lui        $at, %hi(g_Spyro + 0x1F0)
/* 3B05C 8004A85C 488C22AC */  sw         $v0, %lo(g_Spyro + 0x1F0)($at)
.L8004A860:
/* 3B060 8004A860 BC5D000C */  jal        VecNull
/* 3B064 8004A864 88000426 */   addiu     $a0, $s0, 0x88
/* 3B068 8004A868 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B06C 8004A86C CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B070 8004A870 00000000 */  nop
/* 3B074 8004A874 09004018 */  blez       $v0, .L8004A89C
/* 3B078 8004A878 21800000 */   addu      $s0, $zero, $zero
.L8004A87C:
/* 3B07C 8004A87C F90F010C */  jal        func_80043FE4
/* 3B080 8004A880 21200002 */   addu      $a0, $s0, $zero
/* 3B084 8004A884 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B088 8004A888 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B08C 8004A88C 01001026 */  addiu      $s0, $s0, 0x1
/* 3B090 8004A890 2A100202 */  slt        $v0, $s0, $v0
/* 3B094 8004A894 F9FF4014 */  bnez       $v0, .L8004A87C
/* 3B098 8004A898 00000000 */   nop
.L8004A89C:
/* 3B09C 8004A89C 0880103C */  lui        $s0, %hi(g_Spyro + 0x100)
/* 3B0A0 8004A8A0 588B1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x100)
/* 3B0A4 8004A8A4 21200002 */  addu       $a0, $s0, $zero
/* 3B0A8 8004A8A8 B25D000C */  jal        VecShiftRight
/* 3B0AC 8004A8AC 06000524 */   addiu     $a1, $zero, 0x6
/* 3B0B0 8004A8B0 8CFF0426 */  addiu      $a0, $s0, -0x74
/* 3B0B4 8004A8B4 00FF1126 */  addiu      $s1, $s0, -0x100
/* 3B0B8 8004A8B8 C05D000C */  jal        VecCopy
/* 3B0BC 8004A8BC 21282002 */   addu      $a1, $s1, $zero
/* 3B0C0 8004A8C0 21202002 */  addu       $a0, $s1, $zero
/* 3B0C4 8004A8C4 21288000 */  addu       $a1, $a0, $zero
/* 3B0C8 8004A8C8 D65D000C */  jal        VecAdd
/* 3B0CC 8004A8CC 21300002 */   addu      $a2, $s0, $zero
/* 3B0D0 8004A8D0 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B0D4 8004A8D4 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B0D8 8004A8D8 00000000 */  nop
/* 3B0DC 8004A8DC 0B004018 */  blez       $v0, .L8004A90C
/* 3B0E0 8004A8E0 21800000 */   addu      $s0, $zero, $zero
.L8004A8E4:
/* 3B0E4 8004A8E4 2322010C */  jal        func_8004888C
/* 3B0E8 8004A8E8 01001026 */   addiu     $s0, $s0, 0x1
/* 3B0EC 8004A8EC 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B0F0 8004A8F0 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B0F4 8004A8F4 00000000 */  nop
/* 3B0F8 8004A8F8 2A100202 */  slt        $v0, $s0, $v0
/* 3B0FC 8004A8FC F9FF4014 */  bnez       $v0, .L8004A8E4
/* 3B100 8004A900 00000000 */   nop
/* 3B104 8004A904 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B108 8004A908 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
.L8004A90C:
/* 3B10C 8004A90C 00000000 */  nop
/* 3B110 8004A910 11004018 */  blez       $v0, .L8004A958
/* 3B114 8004A914 21800000 */   addu      $s0, $zero, $zero
.L8004A918:
/* 3B118 8004A918 65F4000C */  jal        UpdateBodyAnimationState
/* 3B11C 8004A91C 01001026 */   addiu     $s0, $s0, 0x1
/* 3B120 8004A920 7026010C */  jal        func_800499C0
/* 3B124 8004A924 00000000 */   nop
/* 3B128 8004A928 9825010C */  jal        func_80049660
/* 3B12C 8004A92C 00000000 */   nop
/* 3B130 8004A930 CF27010C */  jal        func_80049F3C
/* 3B134 8004A934 00000000 */   nop
/* 3B138 8004A938 A327010C */  jal        func_80049E8C
/* 3B13C 8004A93C 00000000 */   nop
/* 3B140 8004A940 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B144 8004A944 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B148 8004A948 00000000 */  nop
/* 3B14C 8004A94C 2A100202 */  slt        $v0, $s0, $v0
/* 3B150 8004A950 F1FF4014 */  bnez       $v0, .L8004A918
/* 3B154 8004A954 00000000 */   nop
.L8004A958:
/* 3B158 8004A958 0880103C */  lui        $s0, %hi(g_Spyro + 0xC)
/* 3B15C 8004A95C 648A1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0xC)
/* 3B160 8004A960 21200002 */  addu       $a0, $s0, $zero
/* 3B164 8004A964 28001126 */  addiu      $s1, $s0, 0x28
/* 3B168 8004A968 21282002 */  addu       $a1, $s1, $zero
/* 3B16C 8004A96C 0880023C */  lui        $v0, %hi(g_Spyro + 0x124)
/* 3B170 8004A970 7C8B428C */  lw         $v0, %lo(g_Spyro + 0x124)($v0)
/* 3B174 8004A974 00000000 */  nop
/* 3B178 8004A978 03110200 */  sra        $v0, $v0, 4
/* 3B17C 8004A97C 000002A2 */  sb         $v0, 0x0($s0)
/* 3B180 8004A980 0880023C */  lui        $v0, %hi(g_Spyro + 0x120)
/* 3B184 8004A984 788B428C */  lw         $v0, %lo(g_Spyro + 0x120)($v0)
/* 3B188 8004A988 0880033C */  lui        $v1, %hi(g_Spyro + 0x11C)
/* 3B18C 8004A98C 748B638C */  lw         $v1, %lo(g_Spyro + 0x11C)($v1)
/* 3B190 8004A990 03110200 */  sra        $v0, $v0, 4
/* 3B194 8004A994 03190300 */  sra        $v1, $v1, 4
/* 3B198 8004A998 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 3B19C 8004A99C 658A22A0 */  sb         $v0, %lo(g_Spyro + 0xD)($at)
/* 3B1A0 8004A9A0 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 3B1A4 8004A9A4 668A23A0 */  sb         $v1, %lo(g_Spyro + 0xE)($at)
/* 3B1A8 8004A9A8 4B5B000C */  jal        RotVec8ToMatrix
/* 3B1AC 8004A9AC 21300000 */   addu      $a2, $zero, $zero
/* 3B1B0 8004A9B0 04000426 */  addiu      $a0, $s0, 0x4
/* 3B1B4 8004A9B4 BC011026 */  addiu      $s0, $s0, 0x1BC
/* 3B1B8 8004A9B8 21280002 */  addu       $a1, $s0, $zero
/* 3B1BC 8004A9BC 4B5B000C */  jal        RotVec8ToMatrix
/* 3B1C0 8004A9C0 21300000 */   addu      $a2, $zero, $zero
/* 3B1C4 8004A9C4 21202002 */  addu       $a0, $s1, $zero
/* 3B1C8 8004A9C8 21280002 */  addu       $a1, $s0, $zero
/* 3B1CC 8004A9CC F688010C */  jal        MulMatrix0
/* 3B1D0 8004A9D0 2130A000 */   addu      $a2, $a1, $zero
/* 3B1D4 8004A9D4 0780043C */  lui        $a0, %hi(D_800776D8)
/* 3B1D8 8004A9D8 D8768424 */  addiu      $a0, $a0, %lo(D_800776D8)
/* 3B1DC 8004A9DC 0780053C */  lui        $a1, %hi(g_Pad)
/* 3B1E0 8004A9E0 7873A524 */  addiu      $a1, $a1, %lo(g_Pad)
/* 3B1E4 8004A9E4 0880013C */  lui        $at, %hi(g_Spyro + 0x1F4)
/* 3B1E8 8004A9E8 4C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1F4)($at)
/* 3B1EC 8004A9EC C24D010C */  jal        func_80053708
/* 3B1F0 8004A9F0 00000000 */   nop
/* 3B1F4 8004A9F4 5000BF8F */  lw         $ra, 0x50($sp)
/* 3B1F8 8004A9F8 4C00B18F */  lw         $s1, 0x4C($sp)
/* 3B1FC 8004A9FC 4800B08F */  lw         $s0, 0x48($sp)
/* 3B200 8004AA00 5800BD27 */  addiu      $sp, $sp, 0x58
/* 3B204 8004AA04 0800E003 */  jr         $ra
/* 3B208 8004AA08 00000000 */   nop
.size func_8004A7EC, . - func_8004A7EC
