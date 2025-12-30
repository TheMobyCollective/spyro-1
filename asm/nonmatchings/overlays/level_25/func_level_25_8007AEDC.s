.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_25_8007AEDC
/* 258FCA4 8007AEDC D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 258FCA8 8007AEE0 11008010 */  beqz       $a0, .Llevel_25_8007AF28
/* 258FCAC 8007AEE4 2000BFAF */   sw        $ra, 0x20($sp)
/* 258FCB0 8007AEE8 FEFF033C */  lui        $v1, (0xFFFE3E00 >> 16)
/* 258FCB4 8007AEEC 003E6334 */  ori        $v1, $v1, (0xFFFE3E00 & 0xFFFF)
/* 258FCB8 8007AEF0 1000A427 */  addiu      $a0, $sp, 0x10
/* 258FCBC 8007AEF4 0880053C */  lui        $a1, %hi(g_Buffers + 0x18)
/* 258FCC0 8007AEF8 F085A58C */  lw         $a1, %lo(g_Buffers + 0x18)($a1)
/* 258FCC4 8007AEFC 00020224 */  addiu      $v0, $zero, 0x200
/* 258FCC8 8007AF00 1000A2A7 */  sh         $v0, 0x10($sp)
/* 258FCCC 8007AF04 00010224 */  addiu      $v0, $zero, 0x100
/* 258FCD0 8007AF08 1400A2A7 */  sh         $v0, 0x14($sp)
/* 258FCD4 8007AF0C E1000224 */  addiu      $v0, $zero, 0xE1
/* 258FCD8 8007AF10 1200A0A7 */  sh         $zero, 0x12($sp)
/* 258FCDC 8007AF14 1600A2A7 */  sh         $v0, 0x16($sp)
/* 258FCE0 8007AF18 8A7E010C */  jal        LoadImage
/* 258FCE4 8007AF1C 2128A300 */   addu      $a1, $a1, $v1
/* 258FCE8 8007AF20 D97D010C */  jal        DrawSync
/* 258FCEC 8007AF24 21200000 */   addu      $a0, $zero, $zero
.Llevel_25_8007AF28:
/* 258FCF0 8007AF28 0780013C */  lui        $at, %hi(g_Gamestate)
/* 258FCF4 8007AF2C D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 258FCF8 8007AF30 1F63010C */  jal        SpecularReset
/* 258FCFC 8007AF34 00000000 */   nop
/* 258FD00 8007AF38 21300000 */  addu       $a2, $zero, $zero
/* 258FD04 8007AF3C 08000E24 */  addiu      $t6, $zero, 0x8
/* 258FD08 8007AF40 08800D3C */  lui        $t5, %hi(g_FlightCollected)
/* 258FD0C 8007AF44 8086AD25 */  addiu      $t5, $t5, %lo(g_FlightCollected)
/* 258FD10 8007AF48 07800C3C */  lui        $t4, %hi(g_LevelGemCount)
/* 258FD14 8007AF4C 20748C25 */  addiu      $t4, $t4, %lo(g_LevelGemCount)
/* 258FD18 8007AF50 07800B3C */  lui        $t3, %hi(D_8006E920)
/* 258FD1C 8007AF54 20E96B25 */  addiu      $t3, $t3, %lo(D_8006E920)
/* 258FD20 8007AF58 01000A24 */  addiu      $t2, $zero, 0x1
/* 258FD24 8007AF5C 0880093C */  lui        $t1, %hi(g_FlightObjectiveCounters)
/* 258FD28 8007AF60 30862925 */  addiu      $t1, $t1, %lo(g_FlightObjectiveCounters)
.Llevel_25_8007AF64:
/* 258FD2C 8007AF64 0000228D */  lw         $v0, 0x0($t1)
/* 258FD30 8007AF68 00000000 */  nop
/* 258FD34 8007AF6C 23004E14 */  bne        $v0, $t6, .Llevel_25_8007AFFC
/* 258FD38 8007AF70 80400600 */   sll       $t0, $a2, 2
/* 258FD3C 8007AF74 0780033C */  lui        $v1, %hi(g_Homeworld)
/* 258FD40 8007AF78 5C59638C */  lw         $v1, %lo(g_Homeworld)($v1)
/* 258FD44 8007AF7C 00000000 */  nop
/* 258FD48 8007AF80 80100300 */  sll        $v0, $v1, 2
/* 258FD4C 8007AF84 21284300 */  addu       $a1, $v0, $v1
/* 258FD50 8007AF88 2110AD00 */  addu       $v0, $a1, $t5
/* 258FD54 8007AF8C 21384600 */  addu       $a3, $v0, $a2
/* 258FD58 8007AF90 0000E290 */  lbu        $v0, 0x0($a3)
/* 258FD5C 8007AF94 00000000 */  nop
/* 258FD60 8007AF98 18004014 */  bnez       $v0, .Llevel_25_8007AFFC
/* 258FD64 8007AF9C 80280500 */   sll       $a1, $a1, 2
/* 258FD68 8007AFA0 2128AB00 */  addu       $a1, $a1, $t3
/* 258FD6C 8007AFA4 21280501 */  addu       $a1, $t0, $a1
/* 258FD70 8007AFA8 0780043C */  lui        $a0, %hi(g_LevelIndex)
/* 258FD74 8007AFAC 6459848C */  lw         $a0, %lo(g_LevelIndex)($a0)
/* 258FD78 8007AFB0 0000A38C */  lw         $v1, 0x0($a1)
/* 258FD7C 8007AFB4 80200400 */  sll        $a0, $a0, 2
/* 258FD80 8007AFB8 21208C00 */  addu       $a0, $a0, $t4
/* 258FD84 8007AFBC 0000828C */  lw         $v0, 0x0($a0)
/* 258FD88 8007AFC0 00000000 */  nop
/* 258FD8C 8007AFC4 21104300 */  addu       $v0, $v0, $v1
/* 258FD90 8007AFC8 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 258FD94 8007AFCC 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 258FD98 8007AFD0 000082AC */  sw         $v0, 0x0($a0)
/* 258FD9C 8007AFD4 0780023C */  lui        $v0, %hi(D_800756C8)
/* 258FDA0 8007AFD8 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 258FDA4 8007AFDC 0000A48C */  lw         $a0, 0x0($a1)
/* 258FDA8 8007AFE0 0C004224 */  addiu      $v0, $v0, 0xC
/* 258FDAC 8007AFE4 21186400 */  addu       $v1, $v1, $a0
/* 258FDB0 8007AFE8 0780013C */  lui        $at, %hi(D_800756C8)
/* 258FDB4 8007AFEC C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 258FDB8 8007AFF0 0780013C */  lui        $at, %hi(g_GemTotal)
/* 258FDBC 8007AFF4 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 258FDC0 8007AFF8 0000EAA0 */  sb         $t2, 0x0($a3)
.Llevel_25_8007AFFC:
/* 258FDC4 8007AFFC 0100C624 */  addiu      $a2, $a2, 0x1
/* 258FDC8 8007B000 0400C228 */  slti       $v0, $a2, 0x4
/* 258FDCC 8007B004 D7FF4014 */  bnez       $v0, .Llevel_25_8007AF64
/* 258FDD0 8007B008 04002925 */   addiu     $t1, $t1, 0x4
/* 258FDD4 8007B00C 0880023C */  lui        $v0, %hi(g_FlightObjectiveCounters)
/* 258FDD8 8007B010 3086428C */  lw         $v0, %lo(g_FlightObjectiveCounters)($v0)
/* 258FDDC 8007B014 0880033C */  lui        $v1, %hi(g_FlightObjectiveCounters + 0x4)
/* 258FDE0 8007B018 3486638C */  lw         $v1, %lo(g_FlightObjectiveCounters + 0x4)($v1)
/* 258FDE4 8007B01C 00000000 */  nop
/* 258FDE8 8007B020 21104300 */  addu       $v0, $v0, $v1
/* 258FDEC 8007B024 0880033C */  lui        $v1, %hi(g_FlightObjectiveCounters + 0x8)
/* 258FDF0 8007B028 3886638C */  lw         $v1, %lo(g_FlightObjectiveCounters + 0x8)($v1)
/* 258FDF4 8007B02C 0880043C */  lui        $a0, %hi(g_FlightObjectiveCounters + 0xC)
/* 258FDF8 8007B030 3C86848C */  lw         $a0, %lo(g_FlightObjectiveCounters + 0xC)($a0)
/* 258FDFC 8007B034 21104300 */  addu       $v0, $v0, $v1
/* 258FE00 8007B038 21104400 */  addu       $v0, $v0, $a0
/* 258FE04 8007B03C 20000324 */  addiu      $v1, $zero, 0x20
/* 258FE08 8007B040 3E004314 */  bne        $v0, $v1, .Llevel_25_8007B13C
/* 258FE0C 8007B044 00000000 */   nop
/* 258FE10 8007B048 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 258FE14 8007B04C 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 258FE18 8007B050 00000000 */  nop
/* 258FE1C 8007B054 80180200 */  sll        $v1, $v0, 2
/* 258FE20 8007B058 21306200 */  addu       $a2, $v1, $v0
/* 258FE24 8007B05C 0880013C */  lui        $at, %hi(g_FlightCollected + 0x04)
/* 258FE28 8007B060 21082600 */  addu       $at, $at, $a2
/* 258FE2C 8007B064 84862290 */  lbu        $v0, %lo(g_FlightCollected + 0x04)($at)
/* 258FE30 8007B068 00000000 */  nop
/* 258FE34 8007B06C 1F004014 */  bnez       $v0, .Llevel_25_8007B0EC
/* 258FE38 8007B070 80280600 */   sll       $a1, $a2, 2
/* 258FE3C 8007B074 0780023C */  lui        $v0, %hi(g_LevelGemCount)
/* 258FE40 8007B078 20744224 */  addiu      $v0, $v0, %lo(g_LevelGemCount)
/* 258FE44 8007B07C 0780043C */  lui        $a0, %hi(g_LevelIndex)
/* 258FE48 8007B080 6459848C */  lw         $a0, %lo(g_LevelIndex)($a0)
/* 258FE4C 8007B084 0780013C */  lui        $at, %hi(D_8006E930)
/* 258FE50 8007B088 21082500 */  addu       $at, $at, $a1
/* 258FE54 8007B08C 30E9238C */  lw         $v1, %lo(D_8006E930)($at)
/* 258FE58 8007B090 80200400 */  sll        $a0, $a0, 2
/* 258FE5C 8007B094 21208200 */  addu       $a0, $a0, $v0
/* 258FE60 8007B098 0000828C */  lw         $v0, 0x0($a0)
/* 258FE64 8007B09C 00000000 */  nop
/* 258FE68 8007B0A0 21104300 */  addu       $v0, $v0, $v1
/* 258FE6C 8007B0A4 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 258FE70 8007B0A8 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 258FE74 8007B0AC 000082AC */  sw         $v0, 0x0($a0)
/* 258FE78 8007B0B0 0780023C */  lui        $v0, %hi(D_800756C8)
/* 258FE7C 8007B0B4 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 258FE80 8007B0B8 0780013C */  lui        $at, %hi(D_8006E930)
/* 258FE84 8007B0BC 21082500 */  addu       $at, $at, $a1
/* 258FE88 8007B0C0 30E9248C */  lw         $a0, %lo(D_8006E930)($at)
/* 258FE8C 8007B0C4 0C004224 */  addiu      $v0, $v0, 0xC
/* 258FE90 8007B0C8 21186400 */  addu       $v1, $v1, $a0
/* 258FE94 8007B0CC 0780013C */  lui        $at, %hi(D_800756C8)
/* 258FE98 8007B0D0 C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 258FE9C 8007B0D4 01000224 */  addiu      $v0, $zero, 0x1
/* 258FEA0 8007B0D8 0780013C */  lui        $at, %hi(g_GemTotal)
/* 258FEA4 8007B0DC 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 258FEA8 8007B0E0 0880013C */  lui        $at, %hi(g_FlightCollected + 0x04)
/* 258FEAC 8007B0E4 21082600 */  addu       $at, $at, $a2
/* 258FEB0 8007B0E8 848622A0 */  sb         $v0, %lo(g_FlightCollected + 0x04)($at)
.Llevel_25_8007B0EC:
/* 258FEB4 8007B0EC 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 258FEB8 8007B0F0 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 258FEBC 8007B0F4 0880033C */  lui        $v1, %hi(g_FlightCourseRecords)
/* 258FEC0 8007B0F8 18866324 */  addiu      $v1, $v1, %lo(g_FlightCourseRecords)
/* 258FEC4 8007B0FC 80100200 */  sll        $v0, $v0, 2
/* 258FEC8 8007B100 21204300 */  addu       $a0, $v0, $v1
/* 258FECC 8007B104 0000838C */  lw         $v1, 0x0($a0)
/* 258FED0 8007B108 00000000 */  nop
/* 258FED4 8007B10C 07006010 */  beqz       $v1, .Llevel_25_8007B12C
/* 258FED8 8007B110 00000000 */   nop
/* 258FEDC 8007B114 0780023C */  lui        $v0, %hi(D_800758F4)
/* 258FEE0 8007B118 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 258FEE4 8007B11C 00000000 */  nop
/* 258FEE8 8007B120 2A104300 */  slt        $v0, $v0, $v1
/* 258FEEC 8007B124 05004010 */  beqz       $v0, .Llevel_25_8007B13C
/* 258FEF0 8007B128 00000000 */   nop
.Llevel_25_8007B12C:
/* 258FEF4 8007B12C 0780023C */  lui        $v0, %hi(D_800758F4)
/* 258FEF8 8007B130 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 258FEFC 8007B134 00000000 */  nop
/* 258FF00 8007B138 000082AC */  sw         $v0, 0x0($a0)
.Llevel_25_8007B13C:
/* 258FF04 8007B13C 0780023C */  lui        $v0, %hi(D_800756C8)
/* 258FF08 8007B140 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 258FF0C 8007B144 00000000 */  nop
/* 258FF10 8007B148 19004018 */  blez       $v0, .Llevel_25_8007B1B0
/* 258FF14 8007B14C 21300000 */   addu      $a2, $zero, $zero
/* 258FF18 8007B150 AA2A043C */  lui        $a0, (0x2AAAAAAB >> 16)
/* 258FF1C 8007B154 ABAA8434 */  ori        $a0, $a0, (0x2AAAAAAB & 0xFFFF)
/* 258FF20 8007B158 1800C400 */  mult       $a2, $a0
.Llevel_25_8007B15C:
/* 258FF24 8007B15C C3170600 */  sra        $v0, $a2, 31
/* 258FF28 8007B160 10780000 */  mfhi       $t7
/* 258FF2C 8007B164 43180F00 */  sra        $v1, $t7, 1
/* 258FF30 8007B168 23186200 */  subu       $v1, $v1, $v0
/* 258FF34 8007B16C 40100300 */  sll        $v0, $v1, 1
/* 258FF38 8007B170 21104300 */  addu       $v0, $v0, $v1
/* 258FF3C 8007B174 80100200 */  sll        $v0, $v0, 2
/* 258FF40 8007B178 2310C200 */  subu       $v0, $a2, $v0
/* 258FF44 8007B17C 0780013C */  lui        $at, %hi(D_8006E998)
/* 258FF48 8007B180 21082200 */  addu       $at, $at, $v0
/* 258FF4C 8007B184 98E92390 */  lbu        $v1, %lo(D_8006E998)($at)
/* 258FF50 8007B188 1F00C230 */  andi       $v0, $a2, 0x1F
/* 258FF54 8007B18C 0780013C */  lui        $at, %hi(g_RecentGemsCollected)
/* 258FF58 8007B190 21082200 */  addu       $at, $at, $v0
/* 258FF5C 8007B194 B87D23A0 */  sb         $v1, %lo(g_RecentGemsCollected)($at)
/* 258FF60 8007B198 0780023C */  lui        $v0, %hi(D_800756C8)
/* 258FF64 8007B19C C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 258FF68 8007B1A0 0100C624 */  addiu      $a2, $a2, 0x1
/* 258FF6C 8007B1A4 2A10C200 */  slt        $v0, $a2, $v0
/* 258FF70 8007B1A8 ECFF4014 */  bnez       $v0, .Llevel_25_8007B15C
/* 258FF74 8007B1AC 1800C400 */   mult      $a2, $a0
.Llevel_25_8007B1B0:
/* 258FF78 8007B1B0 0080033C */  lui        $v1, (0x8000000E >> 16)
/* 258FF7C 8007B1B4 0780023C */  lui        $v0, %hi(g_Camera + 0x58)
/* 258FF80 8007B1B8 286E428C */  lw         $v0, %lo(g_Camera + 0x58)($v0)
/* 258FF84 8007B1BC 0E006334 */  ori        $v1, $v1, (0x8000000E & 0xFFFF)
/* 258FF88 8007B1C0 0880013C */  lui        $at, %hi(g_Spyro + 0x7C)
/* 258FF8C 8007B1C4 D48A20AC */  sw         $zero, %lo(g_Spyro + 0x7C)($at)
/* 258FF90 8007B1C8 08004314 */  bne        $v0, $v1, .Llevel_25_8007B1EC
/* 258FF94 8007B1CC 00000000 */   nop
/* 258FF98 8007B1D0 0880023C */  lui        $v0, %hi(g_Spyro + 0x78)
/* 258FF9C 8007B1D4 D08A428C */  lw         $v0, %lo(g_Spyro + 0x78)($v0)
/* 258FFA0 8007B1D8 0780013C */  lui        $at, %hi(D_8006C588)
/* 258FFA4 8007B1DC 21082200 */  addu       $at, $at, $v0
/* 258FFA8 8007B1E0 88C52290 */  lbu        $v0, %lo(D_8006C588)($at)
/* 258FFAC 8007B1E4 0780013C */  lui        $at, %hi(g_Camera + 0xC0)
/* 258FFB0 8007B1E8 906E22AC */  sw         $v0, %lo(g_Camera + 0xC0)($at)
.Llevel_25_8007B1EC:
/* 258FFB4 8007B1EC 2000BF8F */  lw         $ra, 0x20($sp)
/* 258FFB8 8007B1F0 2800BD27 */  addiu      $sp, $sp, 0x28
/* 258FFBC 8007B1F4 0800E003 */  jr         $ra
/* 258FFC0 8007B1F8 00000000 */   nop
.size func_level_25_8007AEDC, . - func_level_25_8007AEDC
