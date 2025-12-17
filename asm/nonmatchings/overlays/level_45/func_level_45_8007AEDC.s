.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_45_8007AEDC
/* 4256CA4 8007AEDC D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 4256CA8 8007AEE0 11008010 */  beqz       $a0, .Llevel_45_8007AF28
/* 4256CAC 8007AEE4 2000BFAF */   sw        $ra, 0x20($sp)
/* 4256CB0 8007AEE8 FEFF033C */  lui        $v1, (0xFFFE3E00 >> 16)
/* 4256CB4 8007AEEC 003E6334 */  ori        $v1, $v1, (0xFFFE3E00 & 0xFFFF)
/* 4256CB8 8007AEF0 1000A427 */  addiu      $a0, $sp, 0x10
/* 4256CBC 8007AEF4 0880053C */  lui        $a1, %hi(D_800785D8 + 0x18)
/* 4256CC0 8007AEF8 F085A58C */  lw         $a1, %lo(D_800785D8 + 0x18)($a1)
/* 4256CC4 8007AEFC 00020224 */  addiu      $v0, $zero, 0x200
/* 4256CC8 8007AF00 1000A2A7 */  sh         $v0, 0x10($sp)
/* 4256CCC 8007AF04 00010224 */  addiu      $v0, $zero, 0x100
/* 4256CD0 8007AF08 1400A2A7 */  sh         $v0, 0x14($sp)
/* 4256CD4 8007AF0C E1000224 */  addiu      $v0, $zero, 0xE1
/* 4256CD8 8007AF10 1200A0A7 */  sh         $zero, 0x12($sp)
/* 4256CDC 8007AF14 1600A2A7 */  sh         $v0, 0x16($sp)
/* 4256CE0 8007AF18 8A7E010C */  jal        LoadImage
/* 4256CE4 8007AF1C 2128A300 */   addu      $a1, $a1, $v1
/* 4256CE8 8007AF20 D97D010C */  jal        DrawSync
/* 4256CEC 8007AF24 21200000 */   addu      $a0, $zero, $zero
.Llevel_45_8007AF28:
/* 4256CF0 8007AF28 0780013C */  lui        $at, %hi(g_Gamestate)
/* 4256CF4 8007AF2C D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 4256CF8 8007AF30 1F63010C */  jal        SpecularReset
/* 4256CFC 8007AF34 00000000 */   nop
/* 4256D00 8007AF38 21300000 */  addu       $a2, $zero, $zero
/* 4256D04 8007AF3C 08000E24 */  addiu      $t6, $zero, 0x8
/* 4256D08 8007AF40 08800D3C */  lui        $t5, %hi(D_80078680)
/* 4256D0C 8007AF44 8086AD25 */  addiu      $t5, $t5, %lo(D_80078680)
/* 4256D10 8007AF48 07800C3C */  lui        $t4, %hi(g_LevelGemCount)
/* 4256D14 8007AF4C 20748C25 */  addiu      $t4, $t4, %lo(g_LevelGemCount)
/* 4256D18 8007AF50 07800B3C */  lui        $t3, %hi(D_8006E920)
/* 4256D1C 8007AF54 20E96B25 */  addiu      $t3, $t3, %lo(D_8006E920)
/* 4256D20 8007AF58 01000A24 */  addiu      $t2, $zero, 0x1
/* 4256D24 8007AF5C 0880093C */  lui        $t1, %hi(g_FlightObjectiveCounters)
/* 4256D28 8007AF60 30862925 */  addiu      $t1, $t1, %lo(g_FlightObjectiveCounters)
.Llevel_45_8007AF64:
/* 4256D2C 8007AF64 0000228D */  lw         $v0, 0x0($t1)
/* 4256D30 8007AF68 00000000 */  nop
/* 4256D34 8007AF6C 23004E14 */  bne        $v0, $t6, .Llevel_45_8007AFFC
/* 4256D38 8007AF70 80400600 */   sll       $t0, $a2, 2
/* 4256D3C 8007AF74 0780033C */  lui        $v1, %hi(g_Homeworld)
/* 4256D40 8007AF78 5C59638C */  lw         $v1, %lo(g_Homeworld)($v1)
/* 4256D44 8007AF7C 00000000 */  nop
/* 4256D48 8007AF80 80100300 */  sll        $v0, $v1, 2
/* 4256D4C 8007AF84 21284300 */  addu       $a1, $v0, $v1
/* 4256D50 8007AF88 2110AD00 */  addu       $v0, $a1, $t5
/* 4256D54 8007AF8C 21384600 */  addu       $a3, $v0, $a2
/* 4256D58 8007AF90 0000E290 */  lbu        $v0, 0x0($a3)
/* 4256D5C 8007AF94 00000000 */  nop
/* 4256D60 8007AF98 18004014 */  bnez       $v0, .Llevel_45_8007AFFC
/* 4256D64 8007AF9C 80280500 */   sll       $a1, $a1, 2
/* 4256D68 8007AFA0 2128AB00 */  addu       $a1, $a1, $t3
/* 4256D6C 8007AFA4 21280501 */  addu       $a1, $t0, $a1
/* 4256D70 8007AFA8 0780043C */  lui        $a0, %hi(g_LevelIndex)
/* 4256D74 8007AFAC 6459848C */  lw         $a0, %lo(g_LevelIndex)($a0)
/* 4256D78 8007AFB0 0000A38C */  lw         $v1, 0x0($a1)
/* 4256D7C 8007AFB4 80200400 */  sll        $a0, $a0, 2
/* 4256D80 8007AFB8 21208C00 */  addu       $a0, $a0, $t4
/* 4256D84 8007AFBC 0000828C */  lw         $v0, 0x0($a0)
/* 4256D88 8007AFC0 00000000 */  nop
/* 4256D8C 8007AFC4 21104300 */  addu       $v0, $v0, $v1
/* 4256D90 8007AFC8 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 4256D94 8007AFCC 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 4256D98 8007AFD0 000082AC */  sw         $v0, 0x0($a0)
/* 4256D9C 8007AFD4 0780023C */  lui        $v0, %hi(D_800756C8)
/* 4256DA0 8007AFD8 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 4256DA4 8007AFDC 0000A48C */  lw         $a0, 0x0($a1)
/* 4256DA8 8007AFE0 0C004224 */  addiu      $v0, $v0, 0xC
/* 4256DAC 8007AFE4 21186400 */  addu       $v1, $v1, $a0
/* 4256DB0 8007AFE8 0780013C */  lui        $at, %hi(D_800756C8)
/* 4256DB4 8007AFEC C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 4256DB8 8007AFF0 0780013C */  lui        $at, %hi(g_GemTotal)
/* 4256DBC 8007AFF4 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 4256DC0 8007AFF8 0000EAA0 */  sb         $t2, 0x0($a3)
.Llevel_45_8007AFFC:
/* 4256DC4 8007AFFC 0100C624 */  addiu      $a2, $a2, 0x1
/* 4256DC8 8007B000 0400C228 */  slti       $v0, $a2, 0x4
/* 4256DCC 8007B004 D7FF4014 */  bnez       $v0, .Llevel_45_8007AF64
/* 4256DD0 8007B008 04002925 */   addiu     $t1, $t1, 0x4
/* 4256DD4 8007B00C 0880023C */  lui        $v0, %hi(g_FlightObjectiveCounters)
/* 4256DD8 8007B010 3086428C */  lw         $v0, %lo(g_FlightObjectiveCounters)($v0)
/* 4256DDC 8007B014 0880033C */  lui        $v1, %hi(D_80078634)
/* 4256DE0 8007B018 3486638C */  lw         $v1, %lo(D_80078634)($v1)
/* 4256DE4 8007B01C 00000000 */  nop
/* 4256DE8 8007B020 21104300 */  addu       $v0, $v0, $v1
/* 4256DEC 8007B024 0880033C */  lui        $v1, %hi(D_80078638)
/* 4256DF0 8007B028 3886638C */  lw         $v1, %lo(D_80078638)($v1)
/* 4256DF4 8007B02C 0880043C */  lui        $a0, %hi(D_8007863C)
/* 4256DF8 8007B030 3C86848C */  lw         $a0, %lo(D_8007863C)($a0)
/* 4256DFC 8007B034 21104300 */  addu       $v0, $v0, $v1
/* 4256E00 8007B038 21104400 */  addu       $v0, $v0, $a0
/* 4256E04 8007B03C 20000324 */  addiu      $v1, $zero, 0x20
/* 4256E08 8007B040 3E004314 */  bne        $v0, $v1, .Llevel_45_8007B13C
/* 4256E0C 8007B044 00000000 */   nop
/* 4256E10 8007B048 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 4256E14 8007B04C 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 4256E18 8007B050 00000000 */  nop
/* 4256E1C 8007B054 80180200 */  sll        $v1, $v0, 2
/* 4256E20 8007B058 21306200 */  addu       $a2, $v1, $v0
/* 4256E24 8007B05C 0880013C */  lui        $at, %hi(D_80078680 + 0x04)
/* 4256E28 8007B060 21082600 */  addu       $at, $at, $a2
/* 4256E2C 8007B064 84862290 */  lbu        $v0, %lo(D_80078680 + 0x04)($at)
/* 4256E30 8007B068 00000000 */  nop
/* 4256E34 8007B06C 1F004014 */  bnez       $v0, .Llevel_45_8007B0EC
/* 4256E38 8007B070 80280600 */   sll       $a1, $a2, 2
/* 4256E3C 8007B074 0780023C */  lui        $v0, %hi(g_LevelGemCount)
/* 4256E40 8007B078 20744224 */  addiu      $v0, $v0, %lo(g_LevelGemCount)
/* 4256E44 8007B07C 0780043C */  lui        $a0, %hi(g_LevelIndex)
/* 4256E48 8007B080 6459848C */  lw         $a0, %lo(g_LevelIndex)($a0)
/* 4256E4C 8007B084 0780013C */  lui        $at, %hi(D_8006E930)
/* 4256E50 8007B088 21082500 */  addu       $at, $at, $a1
/* 4256E54 8007B08C 30E9238C */  lw         $v1, %lo(D_8006E930)($at)
/* 4256E58 8007B090 80200400 */  sll        $a0, $a0, 2
/* 4256E5C 8007B094 21208200 */  addu       $a0, $a0, $v0
/* 4256E60 8007B098 0000828C */  lw         $v0, 0x0($a0)
/* 4256E64 8007B09C 00000000 */  nop
/* 4256E68 8007B0A0 21104300 */  addu       $v0, $v0, $v1
/* 4256E6C 8007B0A4 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 4256E70 8007B0A8 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 4256E74 8007B0AC 000082AC */  sw         $v0, 0x0($a0)
/* 4256E78 8007B0B0 0780023C */  lui        $v0, %hi(D_800756C8)
/* 4256E7C 8007B0B4 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 4256E80 8007B0B8 0780013C */  lui        $at, %hi(D_8006E930)
/* 4256E84 8007B0BC 21082500 */  addu       $at, $at, $a1
/* 4256E88 8007B0C0 30E9248C */  lw         $a0, %lo(D_8006E930)($at)
/* 4256E8C 8007B0C4 0C004224 */  addiu      $v0, $v0, 0xC
/* 4256E90 8007B0C8 21186400 */  addu       $v1, $v1, $a0
/* 4256E94 8007B0CC 0780013C */  lui        $at, %hi(D_800756C8)
/* 4256E98 8007B0D0 C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 4256E9C 8007B0D4 01000224 */  addiu      $v0, $zero, 0x1
/* 4256EA0 8007B0D8 0780013C */  lui        $at, %hi(g_GemTotal)
/* 4256EA4 8007B0DC 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 4256EA8 8007B0E0 0880013C */  lui        $at, %hi(D_80078680 + 0x04)
/* 4256EAC 8007B0E4 21082600 */  addu       $at, $at, $a2
/* 4256EB0 8007B0E8 848622A0 */  sb         $v0, %lo(D_80078680 + 0x04)($at)
.Llevel_45_8007B0EC:
/* 4256EB4 8007B0EC 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 4256EB8 8007B0F0 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 4256EBC 8007B0F4 0880033C */  lui        $v1, %hi(D_80078618)
/* 4256EC0 8007B0F8 18866324 */  addiu      $v1, $v1, %lo(D_80078618)
/* 4256EC4 8007B0FC 80100200 */  sll        $v0, $v0, 2
/* 4256EC8 8007B100 21204300 */  addu       $a0, $v0, $v1
/* 4256ECC 8007B104 0000838C */  lw         $v1, 0x0($a0)
/* 4256ED0 8007B108 00000000 */  nop
/* 4256ED4 8007B10C 07006010 */  beqz       $v1, .Llevel_45_8007B12C
/* 4256ED8 8007B110 00000000 */   nop
/* 4256EDC 8007B114 0780023C */  lui        $v0, %hi(D_800758F4)
/* 4256EE0 8007B118 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 4256EE4 8007B11C 00000000 */  nop
/* 4256EE8 8007B120 2A104300 */  slt        $v0, $v0, $v1
/* 4256EEC 8007B124 05004010 */  beqz       $v0, .Llevel_45_8007B13C
/* 4256EF0 8007B128 00000000 */   nop
.Llevel_45_8007B12C:
/* 4256EF4 8007B12C 0780023C */  lui        $v0, %hi(D_800758F4)
/* 4256EF8 8007B130 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 4256EFC 8007B134 00000000 */  nop
/* 4256F00 8007B138 000082AC */  sw         $v0, 0x0($a0)
.Llevel_45_8007B13C:
/* 4256F04 8007B13C 0780023C */  lui        $v0, %hi(D_800756C8)
/* 4256F08 8007B140 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 4256F0C 8007B144 00000000 */  nop
/* 4256F10 8007B148 19004018 */  blez       $v0, .Llevel_45_8007B1B0
/* 4256F14 8007B14C 21300000 */   addu      $a2, $zero, $zero
/* 4256F18 8007B150 AA2A043C */  lui        $a0, (0x2AAAAAAB >> 16)
/* 4256F1C 8007B154 ABAA8434 */  ori        $a0, $a0, (0x2AAAAAAB & 0xFFFF)
/* 4256F20 8007B158 1800C400 */  mult       $a2, $a0
.Llevel_45_8007B15C:
/* 4256F24 8007B15C C3170600 */  sra        $v0, $a2, 31
/* 4256F28 8007B160 10780000 */  mfhi       $t7
/* 4256F2C 8007B164 43180F00 */  sra        $v1, $t7, 1
/* 4256F30 8007B168 23186200 */  subu       $v1, $v1, $v0
/* 4256F34 8007B16C 40100300 */  sll        $v0, $v1, 1
/* 4256F38 8007B170 21104300 */  addu       $v0, $v0, $v1
/* 4256F3C 8007B174 80100200 */  sll        $v0, $v0, 2
/* 4256F40 8007B178 2310C200 */  subu       $v0, $a2, $v0
/* 4256F44 8007B17C 0780013C */  lui        $at, %hi(D_8006E998)
/* 4256F48 8007B180 21082200 */  addu       $at, $at, $v0
/* 4256F4C 8007B184 98E92390 */  lbu        $v1, %lo(D_8006E998)($at)
/* 4256F50 8007B188 1F00C230 */  andi       $v0, $a2, 0x1F
/* 4256F54 8007B18C 0780013C */  lui        $at, %hi(g_RecentGemsCollected)
/* 4256F58 8007B190 21082200 */  addu       $at, $at, $v0
/* 4256F5C 8007B194 B87D23A0 */  sb         $v1, %lo(g_RecentGemsCollected)($at)
/* 4256F60 8007B198 0780023C */  lui        $v0, %hi(D_800756C8)
/* 4256F64 8007B19C C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 4256F68 8007B1A0 0100C624 */  addiu      $a2, $a2, 0x1
/* 4256F6C 8007B1A4 2A10C200 */  slt        $v0, $a2, $v0
/* 4256F70 8007B1A8 ECFF4014 */  bnez       $v0, .Llevel_45_8007B15C
/* 4256F74 8007B1AC 1800C400 */   mult      $a2, $a0
.Llevel_45_8007B1B0:
/* 4256F78 8007B1B0 0080033C */  lui        $v1, (0x8000000E >> 16)
/* 4256F7C 8007B1B4 0780023C */  lui        $v0, %hi(g_Camera + 0x58)
/* 4256F80 8007B1B8 286E428C */  lw         $v0, %lo(g_Camera + 0x58)($v0)
/* 4256F84 8007B1BC 0E006334 */  ori        $v1, $v1, (0x8000000E & 0xFFFF)
/* 4256F88 8007B1C0 0880013C */  lui        $at, %hi(g_Spyro + 0x7C)
/* 4256F8C 8007B1C4 D48A20AC */  sw         $zero, %lo(g_Spyro + 0x7C)($at)
/* 4256F90 8007B1C8 08004314 */  bne        $v0, $v1, .Llevel_45_8007B1EC
/* 4256F94 8007B1CC 00000000 */   nop
/* 4256F98 8007B1D0 0880023C */  lui        $v0, %hi(g_Spyro + 0x78)
/* 4256F9C 8007B1D4 D08A428C */  lw         $v0, %lo(g_Spyro + 0x78)($v0)
/* 4256FA0 8007B1D8 0780013C */  lui        $at, %hi(D_8006C588)
/* 4256FA4 8007B1DC 21082200 */  addu       $at, $at, $v0
/* 4256FA8 8007B1E0 88C52290 */  lbu        $v0, %lo(D_8006C588)($at)
/* 4256FAC 8007B1E4 0780013C */  lui        $at, %hi(g_Camera + 0xC0)
/* 4256FB0 8007B1E8 906E22AC */  sw         $v0, %lo(g_Camera + 0xC0)($at)
.Llevel_45_8007B1EC:
/* 4256FB4 8007B1EC 2000BF8F */  lw         $ra, 0x20($sp)
/* 4256FB8 8007B1F0 2800BD27 */  addiu      $sp, $sp, 0x28
/* 4256FBC 8007B1F4 0800E003 */  jr         $ra
/* 4256FC0 8007B1F8 00000000 */   nop
.size func_level_45_8007AEDC, . - func_level_45_8007AEDC
