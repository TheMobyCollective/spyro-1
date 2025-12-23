.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_55_8007AEDC
/* 502FCA4 8007AEDC D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 502FCA8 8007AEE0 11008010 */  beqz       $a0, .Llevel_55_8007AF28
/* 502FCAC 8007AEE4 2000BFAF */   sw        $ra, 0x20($sp)
/* 502FCB0 8007AEE8 FEFF033C */  lui        $v1, (0xFFFE3E00 >> 16)
/* 502FCB4 8007AEEC 003E6334 */  ori        $v1, $v1, (0xFFFE3E00 & 0xFFFF)
/* 502FCB8 8007AEF0 1000A427 */  addiu      $a0, $sp, 0x10
/* 502FCBC 8007AEF4 0880053C */  lui        $a1, %hi(D_800785D8 + 0x18)
/* 502FCC0 8007AEF8 F085A58C */  lw         $a1, %lo(D_800785D8 + 0x18)($a1)
/* 502FCC4 8007AEFC 00020224 */  addiu      $v0, $zero, 0x200
/* 502FCC8 8007AF00 1000A2A7 */  sh         $v0, 0x10($sp)
/* 502FCCC 8007AF04 00010224 */  addiu      $v0, $zero, 0x100
/* 502FCD0 8007AF08 1400A2A7 */  sh         $v0, 0x14($sp)
/* 502FCD4 8007AF0C E1000224 */  addiu      $v0, $zero, 0xE1
/* 502FCD8 8007AF10 1200A0A7 */  sh         $zero, 0x12($sp)
/* 502FCDC 8007AF14 1600A2A7 */  sh         $v0, 0x16($sp)
/* 502FCE0 8007AF18 8A7E010C */  jal        LoadImage
/* 502FCE4 8007AF1C 2128A300 */   addu      $a1, $a1, $v1
/* 502FCE8 8007AF20 D97D010C */  jal        DrawSync
/* 502FCEC 8007AF24 21200000 */   addu      $a0, $zero, $zero
.Llevel_55_8007AF28:
/* 502FCF0 8007AF28 0780013C */  lui        $at, %hi(g_Gamestate)
/* 502FCF4 8007AF2C D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 502FCF8 8007AF30 1F63010C */  jal        SpecularReset
/* 502FCFC 8007AF34 00000000 */   nop
/* 502FD00 8007AF38 21300000 */  addu       $a2, $zero, $zero
/* 502FD04 8007AF3C 08000E24 */  addiu      $t6, $zero, 0x8
/* 502FD08 8007AF40 08800D3C */  lui        $t5, %hi(g_FlightCollected)
/* 502FD0C 8007AF44 8086AD25 */  addiu      $t5, $t5, %lo(g_FlightCollected)
/* 502FD10 8007AF48 07800C3C */  lui        $t4, %hi(g_LevelGemCount)
/* 502FD14 8007AF4C 20748C25 */  addiu      $t4, $t4, %lo(g_LevelGemCount)
/* 502FD18 8007AF50 07800B3C */  lui        $t3, %hi(D_8006E920)
/* 502FD1C 8007AF54 20E96B25 */  addiu      $t3, $t3, %lo(D_8006E920)
/* 502FD20 8007AF58 01000A24 */  addiu      $t2, $zero, 0x1
/* 502FD24 8007AF5C 0880093C */  lui        $t1, %hi(g_FlightObjectiveCounters)
/* 502FD28 8007AF60 30862925 */  addiu      $t1, $t1, %lo(g_FlightObjectiveCounters)
.Llevel_55_8007AF64:
/* 502FD2C 8007AF64 0000228D */  lw         $v0, 0x0($t1)
/* 502FD30 8007AF68 00000000 */  nop
/* 502FD34 8007AF6C 23004E14 */  bne        $v0, $t6, .Llevel_55_8007AFFC
/* 502FD38 8007AF70 80400600 */   sll       $t0, $a2, 2
/* 502FD3C 8007AF74 0780033C */  lui        $v1, %hi(g_Homeworld)
/* 502FD40 8007AF78 5C59638C */  lw         $v1, %lo(g_Homeworld)($v1)
/* 502FD44 8007AF7C 00000000 */  nop
/* 502FD48 8007AF80 80100300 */  sll        $v0, $v1, 2
/* 502FD4C 8007AF84 21284300 */  addu       $a1, $v0, $v1
/* 502FD50 8007AF88 2110AD00 */  addu       $v0, $a1, $t5
/* 502FD54 8007AF8C 21384600 */  addu       $a3, $v0, $a2
/* 502FD58 8007AF90 0000E290 */  lbu        $v0, 0x0($a3)
/* 502FD5C 8007AF94 00000000 */  nop
/* 502FD60 8007AF98 18004014 */  bnez       $v0, .Llevel_55_8007AFFC
/* 502FD64 8007AF9C 80280500 */   sll       $a1, $a1, 2
/* 502FD68 8007AFA0 2128AB00 */  addu       $a1, $a1, $t3
/* 502FD6C 8007AFA4 21280501 */  addu       $a1, $t0, $a1
/* 502FD70 8007AFA8 0780043C */  lui        $a0, %hi(g_LevelIndex)
/* 502FD74 8007AFAC 6459848C */  lw         $a0, %lo(g_LevelIndex)($a0)
/* 502FD78 8007AFB0 0000A38C */  lw         $v1, 0x0($a1)
/* 502FD7C 8007AFB4 80200400 */  sll        $a0, $a0, 2
/* 502FD80 8007AFB8 21208C00 */  addu       $a0, $a0, $t4
/* 502FD84 8007AFBC 0000828C */  lw         $v0, 0x0($a0)
/* 502FD88 8007AFC0 00000000 */  nop
/* 502FD8C 8007AFC4 21104300 */  addu       $v0, $v0, $v1
/* 502FD90 8007AFC8 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 502FD94 8007AFCC 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 502FD98 8007AFD0 000082AC */  sw         $v0, 0x0($a0)
/* 502FD9C 8007AFD4 0780023C */  lui        $v0, %hi(D_800756C8)
/* 502FDA0 8007AFD8 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 502FDA4 8007AFDC 0000A48C */  lw         $a0, 0x0($a1)
/* 502FDA8 8007AFE0 0C004224 */  addiu      $v0, $v0, 0xC
/* 502FDAC 8007AFE4 21186400 */  addu       $v1, $v1, $a0
/* 502FDB0 8007AFE8 0780013C */  lui        $at, %hi(D_800756C8)
/* 502FDB4 8007AFEC C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 502FDB8 8007AFF0 0780013C */  lui        $at, %hi(g_GemTotal)
/* 502FDBC 8007AFF4 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 502FDC0 8007AFF8 0000EAA0 */  sb         $t2, 0x0($a3)
.Llevel_55_8007AFFC:
/* 502FDC4 8007AFFC 0100C624 */  addiu      $a2, $a2, 0x1
/* 502FDC8 8007B000 0400C228 */  slti       $v0, $a2, 0x4
/* 502FDCC 8007B004 D7FF4014 */  bnez       $v0, .Llevel_55_8007AF64
/* 502FDD0 8007B008 04002925 */   addiu     $t1, $t1, 0x4
/* 502FDD4 8007B00C 0880023C */  lui        $v0, %hi(g_FlightObjectiveCounters)
/* 502FDD8 8007B010 3086428C */  lw         $v0, %lo(g_FlightObjectiveCounters)($v0)
/* 502FDDC 8007B014 0880033C */  lui        $v1, %hi(g_FlightObjectiveCounters + 0x4)
/* 502FDE0 8007B018 3486638C */  lw         $v1, %lo(g_FlightObjectiveCounters + 0x4)($v1)
/* 502FDE4 8007B01C 00000000 */  nop
/* 502FDE8 8007B020 21104300 */  addu       $v0, $v0, $v1
/* 502FDEC 8007B024 0880033C */  lui        $v1, %hi(g_FlightObjectiveCounters + 0x8)
/* 502FDF0 8007B028 3886638C */  lw         $v1, %lo(g_FlightObjectiveCounters + 0x8)($v1)
/* 502FDF4 8007B02C 0880043C */  lui        $a0, %hi(g_FlightObjectiveCounters + 0xC)
/* 502FDF8 8007B030 3C86848C */  lw         $a0, %lo(g_FlightObjectiveCounters + 0xC)($a0)
/* 502FDFC 8007B034 21104300 */  addu       $v0, $v0, $v1
/* 502FE00 8007B038 21104400 */  addu       $v0, $v0, $a0
/* 502FE04 8007B03C 20000324 */  addiu      $v1, $zero, 0x20
/* 502FE08 8007B040 3E004314 */  bne        $v0, $v1, .Llevel_55_8007B13C
/* 502FE0C 8007B044 00000000 */   nop
/* 502FE10 8007B048 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 502FE14 8007B04C 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 502FE18 8007B050 00000000 */  nop
/* 502FE1C 8007B054 80180200 */  sll        $v1, $v0, 2
/* 502FE20 8007B058 21306200 */  addu       $a2, $v1, $v0
/* 502FE24 8007B05C 0880013C */  lui        $at, %hi(g_FlightCollected + 0x04)
/* 502FE28 8007B060 21082600 */  addu       $at, $at, $a2
/* 502FE2C 8007B064 84862290 */  lbu        $v0, %lo(g_FlightCollected + 0x04)($at)
/* 502FE30 8007B068 00000000 */  nop
/* 502FE34 8007B06C 1F004014 */  bnez       $v0, .Llevel_55_8007B0EC
/* 502FE38 8007B070 80280600 */   sll       $a1, $a2, 2
/* 502FE3C 8007B074 0780023C */  lui        $v0, %hi(g_LevelGemCount)
/* 502FE40 8007B078 20744224 */  addiu      $v0, $v0, %lo(g_LevelGemCount)
/* 502FE44 8007B07C 0780043C */  lui        $a0, %hi(g_LevelIndex)
/* 502FE48 8007B080 6459848C */  lw         $a0, %lo(g_LevelIndex)($a0)
/* 502FE4C 8007B084 0780013C */  lui        $at, %hi(D_8006E930)
/* 502FE50 8007B088 21082500 */  addu       $at, $at, $a1
/* 502FE54 8007B08C 30E9238C */  lw         $v1, %lo(D_8006E930)($at)
/* 502FE58 8007B090 80200400 */  sll        $a0, $a0, 2
/* 502FE5C 8007B094 21208200 */  addu       $a0, $a0, $v0
/* 502FE60 8007B098 0000828C */  lw         $v0, 0x0($a0)
/* 502FE64 8007B09C 00000000 */  nop
/* 502FE68 8007B0A0 21104300 */  addu       $v0, $v0, $v1
/* 502FE6C 8007B0A4 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 502FE70 8007B0A8 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 502FE74 8007B0AC 000082AC */  sw         $v0, 0x0($a0)
/* 502FE78 8007B0B0 0780023C */  lui        $v0, %hi(D_800756C8)
/* 502FE7C 8007B0B4 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 502FE80 8007B0B8 0780013C */  lui        $at, %hi(D_8006E930)
/* 502FE84 8007B0BC 21082500 */  addu       $at, $at, $a1
/* 502FE88 8007B0C0 30E9248C */  lw         $a0, %lo(D_8006E930)($at)
/* 502FE8C 8007B0C4 0C004224 */  addiu      $v0, $v0, 0xC
/* 502FE90 8007B0C8 21186400 */  addu       $v1, $v1, $a0
/* 502FE94 8007B0CC 0780013C */  lui        $at, %hi(D_800756C8)
/* 502FE98 8007B0D0 C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 502FE9C 8007B0D4 01000224 */  addiu      $v0, $zero, 0x1
/* 502FEA0 8007B0D8 0780013C */  lui        $at, %hi(g_GemTotal)
/* 502FEA4 8007B0DC 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 502FEA8 8007B0E0 0880013C */  lui        $at, %hi(g_FlightCollected + 0x04)
/* 502FEAC 8007B0E4 21082600 */  addu       $at, $at, $a2
/* 502FEB0 8007B0E8 848622A0 */  sb         $v0, %lo(g_FlightCollected + 0x04)($at)
.Llevel_55_8007B0EC:
/* 502FEB4 8007B0EC 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 502FEB8 8007B0F0 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 502FEBC 8007B0F4 0880033C */  lui        $v1, %hi(g_FlightCourseRecords)
/* 502FEC0 8007B0F8 18866324 */  addiu      $v1, $v1, %lo(g_FlightCourseRecords)
/* 502FEC4 8007B0FC 80100200 */  sll        $v0, $v0, 2
/* 502FEC8 8007B100 21204300 */  addu       $a0, $v0, $v1
/* 502FECC 8007B104 0000838C */  lw         $v1, 0x0($a0)
/* 502FED0 8007B108 00000000 */  nop
/* 502FED4 8007B10C 07006010 */  beqz       $v1, .Llevel_55_8007B12C
/* 502FED8 8007B110 00000000 */   nop
/* 502FEDC 8007B114 0780023C */  lui        $v0, %hi(D_800758F4)
/* 502FEE0 8007B118 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 502FEE4 8007B11C 00000000 */  nop
/* 502FEE8 8007B120 2A104300 */  slt        $v0, $v0, $v1
/* 502FEEC 8007B124 05004010 */  beqz       $v0, .Llevel_55_8007B13C
/* 502FEF0 8007B128 00000000 */   nop
.Llevel_55_8007B12C:
/* 502FEF4 8007B12C 0780023C */  lui        $v0, %hi(D_800758F4)
/* 502FEF8 8007B130 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 502FEFC 8007B134 00000000 */  nop
/* 502FF00 8007B138 000082AC */  sw         $v0, 0x0($a0)
.Llevel_55_8007B13C:
/* 502FF04 8007B13C 0780023C */  lui        $v0, %hi(D_800756C8)
/* 502FF08 8007B140 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 502FF0C 8007B144 00000000 */  nop
/* 502FF10 8007B148 19004018 */  blez       $v0, .Llevel_55_8007B1B0
/* 502FF14 8007B14C 21300000 */   addu      $a2, $zero, $zero
/* 502FF18 8007B150 AA2A043C */  lui        $a0, (0x2AAAAAAB >> 16)
/* 502FF1C 8007B154 ABAA8434 */  ori        $a0, $a0, (0x2AAAAAAB & 0xFFFF)
/* 502FF20 8007B158 1800C400 */  mult       $a2, $a0
.Llevel_55_8007B15C:
/* 502FF24 8007B15C C3170600 */  sra        $v0, $a2, 31
/* 502FF28 8007B160 10780000 */  mfhi       $t7
/* 502FF2C 8007B164 43180F00 */  sra        $v1, $t7, 1
/* 502FF30 8007B168 23186200 */  subu       $v1, $v1, $v0
/* 502FF34 8007B16C 40100300 */  sll        $v0, $v1, 1
/* 502FF38 8007B170 21104300 */  addu       $v0, $v0, $v1
/* 502FF3C 8007B174 80100200 */  sll        $v0, $v0, 2
/* 502FF40 8007B178 2310C200 */  subu       $v0, $a2, $v0
/* 502FF44 8007B17C 0780013C */  lui        $at, %hi(D_8006E998)
/* 502FF48 8007B180 21082200 */  addu       $at, $at, $v0
/* 502FF4C 8007B184 98E92390 */  lbu        $v1, %lo(D_8006E998)($at)
/* 502FF50 8007B188 1F00C230 */  andi       $v0, $a2, 0x1F
/* 502FF54 8007B18C 0780013C */  lui        $at, %hi(g_RecentGemsCollected)
/* 502FF58 8007B190 21082200 */  addu       $at, $at, $v0
/* 502FF5C 8007B194 B87D23A0 */  sb         $v1, %lo(g_RecentGemsCollected)($at)
/* 502FF60 8007B198 0780023C */  lui        $v0, %hi(D_800756C8)
/* 502FF64 8007B19C C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 502FF68 8007B1A0 0100C624 */  addiu      $a2, $a2, 0x1
/* 502FF6C 8007B1A4 2A10C200 */  slt        $v0, $a2, $v0
/* 502FF70 8007B1A8 ECFF4014 */  bnez       $v0, .Llevel_55_8007B15C
/* 502FF74 8007B1AC 1800C400 */   mult      $a2, $a0
.Llevel_55_8007B1B0:
/* 502FF78 8007B1B0 0080033C */  lui        $v1, (0x8000000E >> 16)
/* 502FF7C 8007B1B4 0780023C */  lui        $v0, %hi(g_Camera + 0x58)
/* 502FF80 8007B1B8 286E428C */  lw         $v0, %lo(g_Camera + 0x58)($v0)
/* 502FF84 8007B1BC 0E006334 */  ori        $v1, $v1, (0x8000000E & 0xFFFF)
/* 502FF88 8007B1C0 0880013C */  lui        $at, %hi(g_Spyro + 0x7C)
/* 502FF8C 8007B1C4 D48A20AC */  sw         $zero, %lo(g_Spyro + 0x7C)($at)
/* 502FF90 8007B1C8 08004314 */  bne        $v0, $v1, .Llevel_55_8007B1EC
/* 502FF94 8007B1CC 00000000 */   nop
/* 502FF98 8007B1D0 0880023C */  lui        $v0, %hi(g_Spyro + 0x78)
/* 502FF9C 8007B1D4 D08A428C */  lw         $v0, %lo(g_Spyro + 0x78)($v0)
/* 502FFA0 8007B1D8 0780013C */  lui        $at, %hi(D_8006C588)
/* 502FFA4 8007B1DC 21082200 */  addu       $at, $at, $v0
/* 502FFA8 8007B1E0 88C52290 */  lbu        $v0, %lo(D_8006C588)($at)
/* 502FFAC 8007B1E4 0780013C */  lui        $at, %hi(g_Camera + 0xC0)
/* 502FFB0 8007B1E8 906E22AC */  sw         $v0, %lo(g_Camera + 0xC0)($at)
.Llevel_55_8007B1EC:
/* 502FFB4 8007B1EC 2000BF8F */  lw         $ra, 0x20($sp)
/* 502FFB8 8007B1F0 2800BD27 */  addiu      $sp, $sp, 0x28
/* 502FFBC 8007B1F4 0800E003 */  jr         $ra
/* 502FFC0 8007B1F8 00000000 */   nop
.size func_level_55_8007AEDC, . - func_level_55_8007AEDC
