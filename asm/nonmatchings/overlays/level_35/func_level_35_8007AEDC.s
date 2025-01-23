.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_35_8007AEDC
/* 33DFCA4 8007AEDC D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 33DFCA8 8007AEE0 11008010 */  beqz       $a0, .Llevel_35_8007AF28
/* 33DFCAC 8007AEE4 2000BFAF */   sw        $ra, 0x20($sp)
/* 33DFCB0 8007AEE8 FEFF033C */  lui        $v1, (0xFFFE3E00 >> 16)
/* 33DFCB4 8007AEEC 003E6334 */  ori        $v1, $v1, (0xFFFE3E00 & 0xFFFF)
/* 33DFCB8 8007AEF0 1000A427 */  addiu      $a0, $sp, 0x10
/* 33DFCBC 8007AEF4 0880053C */  lui        $a1, %hi(D_800785F0)
/* 33DFCC0 8007AEF8 F085A58C */  lw         $a1, %lo(D_800785F0)($a1)
/* 33DFCC4 8007AEFC 00020224 */  addiu      $v0, $zero, 0x200
/* 33DFCC8 8007AF00 1000A2A7 */  sh         $v0, 0x10($sp)
/* 33DFCCC 8007AF04 00010224 */  addiu      $v0, $zero, 0x100
/* 33DFCD0 8007AF08 1400A2A7 */  sh         $v0, 0x14($sp)
/* 33DFCD4 8007AF0C E1000224 */  addiu      $v0, $zero, 0xE1
/* 33DFCD8 8007AF10 1200A0A7 */  sh         $zero, 0x12($sp)
/* 33DFCDC 8007AF14 1600A2A7 */  sh         $v0, 0x16($sp)
/* 33DFCE0 8007AF18 8A7E010C */  jal        LoadImage
/* 33DFCE4 8007AF1C 2128A300 */   addu      $a1, $a1, $v1
/* 33DFCE8 8007AF20 D97D010C */  jal        DrawSync
/* 33DFCEC 8007AF24 21200000 */   addu      $a0, $zero, $zero
.Llevel_35_8007AF28:
/* 33DFCF0 8007AF28 0780013C */  lui        $at, %hi(g_Gamestate)
/* 33DFCF4 8007AF2C D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 33DFCF8 8007AF30 1F63010C */  jal        SpecularReset
/* 33DFCFC 8007AF34 00000000 */   nop
/* 33DFD00 8007AF38 21300000 */  addu       $a2, $zero, $zero
/* 33DFD04 8007AF3C 08000E24 */  addiu      $t6, $zero, 0x8
/* 33DFD08 8007AF40 08800D3C */  lui        $t5, %hi(D_80078680)
/* 33DFD0C 8007AF44 8086AD25 */  addiu      $t5, $t5, %lo(D_80078680)
/* 33DFD10 8007AF48 07800C3C */  lui        $t4, %hi(g_LevelGemCount)
/* 33DFD14 8007AF4C 20748C25 */  addiu      $t4, $t4, %lo(g_LevelGemCount)
/* 33DFD18 8007AF50 07800B3C */  lui        $t3, %hi(D_8006E920)
/* 33DFD1C 8007AF54 20E96B25 */  addiu      $t3, $t3, %lo(D_8006E920)
/* 33DFD20 8007AF58 01000A24 */  addiu      $t2, $zero, 0x1
/* 33DFD24 8007AF5C 0880093C */  lui        $t1, %hi(D_80078630)
/* 33DFD28 8007AF60 30862925 */  addiu      $t1, $t1, %lo(D_80078630)
.Llevel_35_8007AF64:
/* 33DFD2C 8007AF64 0000228D */  lw         $v0, 0x0($t1)
/* 33DFD30 8007AF68 00000000 */  nop
/* 33DFD34 8007AF6C 23004E14 */  bne        $v0, $t6, .Llevel_35_8007AFFC
/* 33DFD38 8007AF70 80400600 */   sll       $t0, $a2, 2
/* 33DFD3C 8007AF74 0780033C */  lui        $v1, %hi(D_8007595C)
/* 33DFD40 8007AF78 5C59638C */  lw         $v1, %lo(D_8007595C)($v1)
/* 33DFD44 8007AF7C 00000000 */  nop
/* 33DFD48 8007AF80 80100300 */  sll        $v0, $v1, 2
/* 33DFD4C 8007AF84 21284300 */  addu       $a1, $v0, $v1
/* 33DFD50 8007AF88 2110AD00 */  addu       $v0, $a1, $t5
/* 33DFD54 8007AF8C 21384600 */  addu       $a3, $v0, $a2
/* 33DFD58 8007AF90 0000E290 */  lbu        $v0, 0x0($a3)
/* 33DFD5C 8007AF94 00000000 */  nop
/* 33DFD60 8007AF98 18004014 */  bnez       $v0, .Llevel_35_8007AFFC
/* 33DFD64 8007AF9C 80280500 */   sll       $a1, $a1, 2
/* 33DFD68 8007AFA0 2128AB00 */  addu       $a1, $a1, $t3
/* 33DFD6C 8007AFA4 21280501 */  addu       $a1, $t0, $a1
/* 33DFD70 8007AFA8 0780043C */  lui        $a0, %hi(D_80075964)
/* 33DFD74 8007AFAC 6459848C */  lw         $a0, %lo(D_80075964)($a0)
/* 33DFD78 8007AFB0 0000A38C */  lw         $v1, 0x0($a1)
/* 33DFD7C 8007AFB4 80200400 */  sll        $a0, $a0, 2
/* 33DFD80 8007AFB8 21208C00 */  addu       $a0, $a0, $t4
/* 33DFD84 8007AFBC 0000828C */  lw         $v0, 0x0($a0)
/* 33DFD88 8007AFC0 00000000 */  nop
/* 33DFD8C 8007AFC4 21104300 */  addu       $v0, $v0, $v1
/* 33DFD90 8007AFC8 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 33DFD94 8007AFCC 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 33DFD98 8007AFD0 000082AC */  sw         $v0, 0x0($a0)
/* 33DFD9C 8007AFD4 0780023C */  lui        $v0, %hi(D_800756C8)
/* 33DFDA0 8007AFD8 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 33DFDA4 8007AFDC 0000A48C */  lw         $a0, 0x0($a1)
/* 33DFDA8 8007AFE0 0C004224 */  addiu      $v0, $v0, 0xC
/* 33DFDAC 8007AFE4 21186400 */  addu       $v1, $v1, $a0
/* 33DFDB0 8007AFE8 0780013C */  lui        $at, %hi(D_800756C8)
/* 33DFDB4 8007AFEC C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 33DFDB8 8007AFF0 0780013C */  lui        $at, %hi(g_GemTotal)
/* 33DFDBC 8007AFF4 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 33DFDC0 8007AFF8 0000EAA0 */  sb         $t2, 0x0($a3)
.Llevel_35_8007AFFC:
/* 33DFDC4 8007AFFC 0100C624 */  addiu      $a2, $a2, 0x1
/* 33DFDC8 8007B000 0400C228 */  slti       $v0, $a2, 0x4
/* 33DFDCC 8007B004 D7FF4014 */  bnez       $v0, .Llevel_35_8007AF64
/* 33DFDD0 8007B008 04002925 */   addiu     $t1, $t1, 0x4
/* 33DFDD4 8007B00C 0880023C */  lui        $v0, %hi(D_80078630)
/* 33DFDD8 8007B010 3086428C */  lw         $v0, %lo(D_80078630)($v0)
/* 33DFDDC 8007B014 0880033C */  lui        $v1, %hi(D_80078634)
/* 33DFDE0 8007B018 3486638C */  lw         $v1, %lo(D_80078634)($v1)
/* 33DFDE4 8007B01C 00000000 */  nop
/* 33DFDE8 8007B020 21104300 */  addu       $v0, $v0, $v1
/* 33DFDEC 8007B024 0880033C */  lui        $v1, %hi(D_80078638)
/* 33DFDF0 8007B028 3886638C */  lw         $v1, %lo(D_80078638)($v1)
/* 33DFDF4 8007B02C 0880043C */  lui        $a0, %hi(D_8007863C)
/* 33DFDF8 8007B030 3C86848C */  lw         $a0, %lo(D_8007863C)($a0)
/* 33DFDFC 8007B034 21104300 */  addu       $v0, $v0, $v1
/* 33DFE00 8007B038 21104400 */  addu       $v0, $v0, $a0
/* 33DFE04 8007B03C 20000324 */  addiu      $v1, $zero, 0x20
/* 33DFE08 8007B040 3E004314 */  bne        $v0, $v1, .Llevel_35_8007B13C
/* 33DFE0C 8007B044 00000000 */   nop
/* 33DFE10 8007B048 0780023C */  lui        $v0, %hi(D_8007595C)
/* 33DFE14 8007B04C 5C59428C */  lw         $v0, %lo(D_8007595C)($v0)
/* 33DFE18 8007B050 00000000 */  nop
/* 33DFE1C 8007B054 80180200 */  sll        $v1, $v0, 2
/* 33DFE20 8007B058 21306200 */  addu       $a2, $v1, $v0
/* 33DFE24 8007B05C 0880013C */  lui        $at, %hi(D_80078680 + 0x04)
/* 33DFE28 8007B060 21082600 */  addu       $at, $at, $a2
/* 33DFE2C 8007B064 84862290 */  lbu        $v0, %lo(D_80078680 + 0x04)($at)
/* 33DFE30 8007B068 00000000 */  nop
/* 33DFE34 8007B06C 1F004014 */  bnez       $v0, .Llevel_35_8007B0EC
/* 33DFE38 8007B070 80280600 */   sll       $a1, $a2, 2
/* 33DFE3C 8007B074 0780023C */  lui        $v0, %hi(g_LevelGemCount)
/* 33DFE40 8007B078 20744224 */  addiu      $v0, $v0, %lo(g_LevelGemCount)
/* 33DFE44 8007B07C 0780043C */  lui        $a0, %hi(D_80075964)
/* 33DFE48 8007B080 6459848C */  lw         $a0, %lo(D_80075964)($a0)
/* 33DFE4C 8007B084 0780013C */  lui        $at, %hi(D_8006E930)
/* 33DFE50 8007B088 21082500 */  addu       $at, $at, $a1
/* 33DFE54 8007B08C 30E9238C */  lw         $v1, %lo(D_8006E930)($at)
/* 33DFE58 8007B090 80200400 */  sll        $a0, $a0, 2
/* 33DFE5C 8007B094 21208200 */  addu       $a0, $a0, $v0
/* 33DFE60 8007B098 0000828C */  lw         $v0, 0x0($a0)
/* 33DFE64 8007B09C 00000000 */  nop
/* 33DFE68 8007B0A0 21104300 */  addu       $v0, $v0, $v1
/* 33DFE6C 8007B0A4 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 33DFE70 8007B0A8 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 33DFE74 8007B0AC 000082AC */  sw         $v0, 0x0($a0)
/* 33DFE78 8007B0B0 0780023C */  lui        $v0, %hi(D_800756C8)
/* 33DFE7C 8007B0B4 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 33DFE80 8007B0B8 0780013C */  lui        $at, %hi(D_8006E930)
/* 33DFE84 8007B0BC 21082500 */  addu       $at, $at, $a1
/* 33DFE88 8007B0C0 30E9248C */  lw         $a0, %lo(D_8006E930)($at)
/* 33DFE8C 8007B0C4 0C004224 */  addiu      $v0, $v0, 0xC
/* 33DFE90 8007B0C8 21186400 */  addu       $v1, $v1, $a0
/* 33DFE94 8007B0CC 0780013C */  lui        $at, %hi(D_800756C8)
/* 33DFE98 8007B0D0 C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 33DFE9C 8007B0D4 01000224 */  addiu      $v0, $zero, 0x1
/* 33DFEA0 8007B0D8 0780013C */  lui        $at, %hi(g_GemTotal)
/* 33DFEA4 8007B0DC 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 33DFEA8 8007B0E0 0880013C */  lui        $at, %hi(D_80078680 + 0x04)
/* 33DFEAC 8007B0E4 21082600 */  addu       $at, $at, $a2
/* 33DFEB0 8007B0E8 848622A0 */  sb         $v0, %lo(D_80078680 + 0x04)($at)
.Llevel_35_8007B0EC:
/* 33DFEB4 8007B0EC 0780023C */  lui        $v0, %hi(D_8007595C)
/* 33DFEB8 8007B0F0 5C59428C */  lw         $v0, %lo(D_8007595C)($v0)
/* 33DFEBC 8007B0F4 0880033C */  lui        $v1, %hi(D_80078618)
/* 33DFEC0 8007B0F8 18866324 */  addiu      $v1, $v1, %lo(D_80078618)
/* 33DFEC4 8007B0FC 80100200 */  sll        $v0, $v0, 2
/* 33DFEC8 8007B100 21204300 */  addu       $a0, $v0, $v1
/* 33DFECC 8007B104 0000838C */  lw         $v1, 0x0($a0)
/* 33DFED0 8007B108 00000000 */  nop
/* 33DFED4 8007B10C 07006010 */  beqz       $v1, .Llevel_35_8007B12C
/* 33DFED8 8007B110 00000000 */   nop
/* 33DFEDC 8007B114 0780023C */  lui        $v0, %hi(D_800758F4)
/* 33DFEE0 8007B118 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 33DFEE4 8007B11C 00000000 */  nop
/* 33DFEE8 8007B120 2A104300 */  slt        $v0, $v0, $v1
/* 33DFEEC 8007B124 05004010 */  beqz       $v0, .Llevel_35_8007B13C
/* 33DFEF0 8007B128 00000000 */   nop
.Llevel_35_8007B12C:
/* 33DFEF4 8007B12C 0780023C */  lui        $v0, %hi(D_800758F4)
/* 33DFEF8 8007B130 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 33DFEFC 8007B134 00000000 */  nop
/* 33DFF00 8007B138 000082AC */  sw         $v0, 0x0($a0)
.Llevel_35_8007B13C:
/* 33DFF04 8007B13C 0780023C */  lui        $v0, %hi(D_800756C8)
/* 33DFF08 8007B140 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 33DFF0C 8007B144 00000000 */  nop
/* 33DFF10 8007B148 19004018 */  blez       $v0, .Llevel_35_8007B1B0
/* 33DFF14 8007B14C 21300000 */   addu      $a2, $zero, $zero
/* 33DFF18 8007B150 AA2A043C */  lui        $a0, (0x2AAAAAAB >> 16)
/* 33DFF1C 8007B154 ABAA8434 */  ori        $a0, $a0, (0x2AAAAAAB & 0xFFFF)
/* 33DFF20 8007B158 1800C400 */  mult       $a2, $a0
.Llevel_35_8007B15C:
/* 33DFF24 8007B15C C3170600 */  sra        $v0, $a2, 31
/* 33DFF28 8007B160 10780000 */  mfhi       $t7
/* 33DFF2C 8007B164 43180F00 */  sra        $v1, $t7, 1
/* 33DFF30 8007B168 23186200 */  subu       $v1, $v1, $v0
/* 33DFF34 8007B16C 40100300 */  sll        $v0, $v1, 1
/* 33DFF38 8007B170 21104300 */  addu       $v0, $v0, $v1
/* 33DFF3C 8007B174 80100200 */  sll        $v0, $v0, 2
/* 33DFF40 8007B178 2310C200 */  subu       $v0, $a2, $v0
/* 33DFF44 8007B17C 0780013C */  lui        $at, %hi(D_8006E998)
/* 33DFF48 8007B180 21082200 */  addu       $at, $at, $v0
/* 33DFF4C 8007B184 98E92390 */  lbu        $v1, %lo(D_8006E998)($at)
/* 33DFF50 8007B188 1F00C230 */  andi       $v0, $a2, 0x1F
/* 33DFF54 8007B18C 0780013C */  lui        $at, %hi(D_80077DB8)
/* 33DFF58 8007B190 21082200 */  addu       $at, $at, $v0
/* 33DFF5C 8007B194 B87D23A0 */  sb         $v1, %lo(D_80077DB8)($at)
/* 33DFF60 8007B198 0780023C */  lui        $v0, %hi(D_800756C8)
/* 33DFF64 8007B19C C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 33DFF68 8007B1A0 0100C624 */  addiu      $a2, $a2, 0x1
/* 33DFF6C 8007B1A4 2A10C200 */  slt        $v0, $a2, $v0
/* 33DFF70 8007B1A8 ECFF4014 */  bnez       $v0, .Llevel_35_8007B15C
/* 33DFF74 8007B1AC 1800C400 */   mult      $a2, $a0
.Llevel_35_8007B1B0:
/* 33DFF78 8007B1B0 0080033C */  lui        $v1, (0x8000000E >> 16)
/* 33DFF7C 8007B1B4 0780023C */  lui        $v0, %hi(g_Camera + 0x58)
/* 33DFF80 8007B1B8 286E428C */  lw         $v0, %lo(g_Camera + 0x58)($v0)
/* 33DFF84 8007B1BC 0E006334 */  ori        $v1, $v1, (0x8000000E & 0xFFFF)
/* 33DFF88 8007B1C0 0880013C */  lui        $at, %hi(g_Spyro + 0x7C)
/* 33DFF8C 8007B1C4 D48A20AC */  sw         $zero, %lo(g_Spyro + 0x7C)($at)
/* 33DFF90 8007B1C8 08004314 */  bne        $v0, $v1, .Llevel_35_8007B1EC
/* 33DFF94 8007B1CC 00000000 */   nop
/* 33DFF98 8007B1D0 0880023C */  lui        $v0, %hi(g_Spyro + 0x78)
/* 33DFF9C 8007B1D4 D08A428C */  lw         $v0, %lo(g_Spyro + 0x78)($v0)
/* 33DFFA0 8007B1D8 0780013C */  lui        $at, %hi(D_8006C588)
/* 33DFFA4 8007B1DC 21082200 */  addu       $at, $at, $v0
/* 33DFFA8 8007B1E0 88C52290 */  lbu        $v0, %lo(D_8006C588)($at)
/* 33DFFAC 8007B1E4 0780013C */  lui        $at, %hi(g_Camera + 0xC0)
/* 33DFFB0 8007B1E8 906E22AC */  sw         $v0, %lo(g_Camera + 0xC0)($at)
.Llevel_35_8007B1EC:
/* 33DFFB4 8007B1EC 2000BF8F */  lw         $ra, 0x20($sp)
/* 33DFFB8 8007B1F0 2800BD27 */  addiu      $sp, $sp, 0x28
/* 33DFFBC 8007B1F4 0800E003 */  jr         $ra
/* 33DFFC0 8007B1F8 00000000 */   nop
.size func_level_35_8007AEDC, . - func_level_35_8007AEDC
