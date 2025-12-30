.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_15_8007AEDC
/* 16A84A4 8007AEDC D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 16A84A8 8007AEE0 11008010 */  beqz       $a0, .Llevel_15_8007AF28
/* 16A84AC 8007AEE4 2000BFAF */   sw        $ra, 0x20($sp)
/* 16A84B0 8007AEE8 FEFF033C */  lui        $v1, (0xFFFE3E00 >> 16)
/* 16A84B4 8007AEEC 003E6334 */  ori        $v1, $v1, (0xFFFE3E00 & 0xFFFF)
/* 16A84B8 8007AEF0 1000A427 */  addiu      $a0, $sp, 0x10
/* 16A84BC 8007AEF4 0880053C */  lui        $a1, %hi(g_Buffers + 0x18)
/* 16A84C0 8007AEF8 F085A58C */  lw         $a1, %lo(g_Buffers + 0x18)($a1)
/* 16A84C4 8007AEFC 00020224 */  addiu      $v0, $zero, 0x200
/* 16A84C8 8007AF00 1000A2A7 */  sh         $v0, 0x10($sp)
/* 16A84CC 8007AF04 00010224 */  addiu      $v0, $zero, 0x100
/* 16A84D0 8007AF08 1400A2A7 */  sh         $v0, 0x14($sp)
/* 16A84D4 8007AF0C E1000224 */  addiu      $v0, $zero, 0xE1
/* 16A84D8 8007AF10 1200A0A7 */  sh         $zero, 0x12($sp)
/* 16A84DC 8007AF14 1600A2A7 */  sh         $v0, 0x16($sp)
/* 16A84E0 8007AF18 8A7E010C */  jal        LoadImage
/* 16A84E4 8007AF1C 2128A300 */   addu      $a1, $a1, $v1
/* 16A84E8 8007AF20 D97D010C */  jal        DrawSync
/* 16A84EC 8007AF24 21200000 */   addu      $a0, $zero, $zero
.Llevel_15_8007AF28:
/* 16A84F0 8007AF28 0780013C */  lui        $at, %hi(g_Gamestate)
/* 16A84F4 8007AF2C D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 16A84F8 8007AF30 1F63010C */  jal        SpecularReset
/* 16A84FC 8007AF34 00000000 */   nop
/* 16A8500 8007AF38 21300000 */  addu       $a2, $zero, $zero
/* 16A8504 8007AF3C 08000E24 */  addiu      $t6, $zero, 0x8
/* 16A8508 8007AF40 08800D3C */  lui        $t5, %hi(g_FlightCollected)
/* 16A850C 8007AF44 8086AD25 */  addiu      $t5, $t5, %lo(g_FlightCollected)
/* 16A8510 8007AF48 07800C3C */  lui        $t4, %hi(g_LevelGemCount)
/* 16A8514 8007AF4C 20748C25 */  addiu      $t4, $t4, %lo(g_LevelGemCount)
/* 16A8518 8007AF50 07800B3C */  lui        $t3, %hi(D_8006E920)
/* 16A851C 8007AF54 20E96B25 */  addiu      $t3, $t3, %lo(D_8006E920)
/* 16A8520 8007AF58 01000A24 */  addiu      $t2, $zero, 0x1
/* 16A8524 8007AF5C 0880093C */  lui        $t1, %hi(g_FlightObjectiveCounters)
/* 16A8528 8007AF60 30862925 */  addiu      $t1, $t1, %lo(g_FlightObjectiveCounters)
.Llevel_15_8007AF64:
/* 16A852C 8007AF64 0000228D */  lw         $v0, 0x0($t1)
/* 16A8530 8007AF68 00000000 */  nop
/* 16A8534 8007AF6C 23004E14 */  bne        $v0, $t6, .Llevel_15_8007AFFC
/* 16A8538 8007AF70 80400600 */   sll       $t0, $a2, 2
/* 16A853C 8007AF74 0780033C */  lui        $v1, %hi(g_Homeworld)
/* 16A8540 8007AF78 5C59638C */  lw         $v1, %lo(g_Homeworld)($v1)
/* 16A8544 8007AF7C 00000000 */  nop
/* 16A8548 8007AF80 80100300 */  sll        $v0, $v1, 2
/* 16A854C 8007AF84 21284300 */  addu       $a1, $v0, $v1
/* 16A8550 8007AF88 2110AD00 */  addu       $v0, $a1, $t5
/* 16A8554 8007AF8C 21384600 */  addu       $a3, $v0, $a2
/* 16A8558 8007AF90 0000E290 */  lbu        $v0, 0x0($a3)
/* 16A855C 8007AF94 00000000 */  nop
/* 16A8560 8007AF98 18004014 */  bnez       $v0, .Llevel_15_8007AFFC
/* 16A8564 8007AF9C 80280500 */   sll       $a1, $a1, 2
/* 16A8568 8007AFA0 2128AB00 */  addu       $a1, $a1, $t3
/* 16A856C 8007AFA4 21280501 */  addu       $a1, $t0, $a1
/* 16A8570 8007AFA8 0780043C */  lui        $a0, %hi(g_LevelIndex)
/* 16A8574 8007AFAC 6459848C */  lw         $a0, %lo(g_LevelIndex)($a0)
/* 16A8578 8007AFB0 0000A38C */  lw         $v1, 0x0($a1)
/* 16A857C 8007AFB4 80200400 */  sll        $a0, $a0, 2
/* 16A8580 8007AFB8 21208C00 */  addu       $a0, $a0, $t4
/* 16A8584 8007AFBC 0000828C */  lw         $v0, 0x0($a0)
/* 16A8588 8007AFC0 00000000 */  nop
/* 16A858C 8007AFC4 21104300 */  addu       $v0, $v0, $v1
/* 16A8590 8007AFC8 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 16A8594 8007AFCC 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 16A8598 8007AFD0 000082AC */  sw         $v0, 0x0($a0)
/* 16A859C 8007AFD4 0780023C */  lui        $v0, %hi(D_800756C8)
/* 16A85A0 8007AFD8 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 16A85A4 8007AFDC 0000A48C */  lw         $a0, 0x0($a1)
/* 16A85A8 8007AFE0 0C004224 */  addiu      $v0, $v0, 0xC
/* 16A85AC 8007AFE4 21186400 */  addu       $v1, $v1, $a0
/* 16A85B0 8007AFE8 0780013C */  lui        $at, %hi(D_800756C8)
/* 16A85B4 8007AFEC C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 16A85B8 8007AFF0 0780013C */  lui        $at, %hi(g_GemTotal)
/* 16A85BC 8007AFF4 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 16A85C0 8007AFF8 0000EAA0 */  sb         $t2, 0x0($a3)
.Llevel_15_8007AFFC:
/* 16A85C4 8007AFFC 0100C624 */  addiu      $a2, $a2, 0x1
/* 16A85C8 8007B000 0400C228 */  slti       $v0, $a2, 0x4
/* 16A85CC 8007B004 D7FF4014 */  bnez       $v0, .Llevel_15_8007AF64
/* 16A85D0 8007B008 04002925 */   addiu     $t1, $t1, 0x4
/* 16A85D4 8007B00C 0880023C */  lui        $v0, %hi(g_FlightObjectiveCounters)
/* 16A85D8 8007B010 3086428C */  lw         $v0, %lo(g_FlightObjectiveCounters)($v0)
/* 16A85DC 8007B014 0880033C */  lui        $v1, %hi(g_FlightObjectiveCounters + 0x4)
/* 16A85E0 8007B018 3486638C */  lw         $v1, %lo(g_FlightObjectiveCounters + 0x4)($v1)
/* 16A85E4 8007B01C 00000000 */  nop
/* 16A85E8 8007B020 21104300 */  addu       $v0, $v0, $v1
/* 16A85EC 8007B024 0880033C */  lui        $v1, %hi(g_FlightObjectiveCounters + 0x8)
/* 16A85F0 8007B028 3886638C */  lw         $v1, %lo(g_FlightObjectiveCounters + 0x8)($v1)
/* 16A85F4 8007B02C 0880043C */  lui        $a0, %hi(g_FlightObjectiveCounters + 0xC)
/* 16A85F8 8007B030 3C86848C */  lw         $a0, %lo(g_FlightObjectiveCounters + 0xC)($a0)
/* 16A85FC 8007B034 21104300 */  addu       $v0, $v0, $v1
/* 16A8600 8007B038 21104400 */  addu       $v0, $v0, $a0
/* 16A8604 8007B03C 20000324 */  addiu      $v1, $zero, 0x20
/* 16A8608 8007B040 3E004314 */  bne        $v0, $v1, .Llevel_15_8007B13C
/* 16A860C 8007B044 00000000 */   nop
/* 16A8610 8007B048 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 16A8614 8007B04C 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 16A8618 8007B050 00000000 */  nop
/* 16A861C 8007B054 80180200 */  sll        $v1, $v0, 2
/* 16A8620 8007B058 21306200 */  addu       $a2, $v1, $v0
/* 16A8624 8007B05C 0880013C */  lui        $at, %hi(g_FlightCollected + 0x04)
/* 16A8628 8007B060 21082600 */  addu       $at, $at, $a2
/* 16A862C 8007B064 84862290 */  lbu        $v0, %lo(g_FlightCollected + 0x04)($at)
/* 16A8630 8007B068 00000000 */  nop
/* 16A8634 8007B06C 1F004014 */  bnez       $v0, .Llevel_15_8007B0EC
/* 16A8638 8007B070 80280600 */   sll       $a1, $a2, 2
/* 16A863C 8007B074 0780023C */  lui        $v0, %hi(g_LevelGemCount)
/* 16A8640 8007B078 20744224 */  addiu      $v0, $v0, %lo(g_LevelGemCount)
/* 16A8644 8007B07C 0780043C */  lui        $a0, %hi(g_LevelIndex)
/* 16A8648 8007B080 6459848C */  lw         $a0, %lo(g_LevelIndex)($a0)
/* 16A864C 8007B084 0780013C */  lui        $at, %hi(D_8006E930)
/* 16A8650 8007B088 21082500 */  addu       $at, $at, $a1
/* 16A8654 8007B08C 30E9238C */  lw         $v1, %lo(D_8006E930)($at)
/* 16A8658 8007B090 80200400 */  sll        $a0, $a0, 2
/* 16A865C 8007B094 21208200 */  addu       $a0, $a0, $v0
/* 16A8660 8007B098 0000828C */  lw         $v0, 0x0($a0)
/* 16A8664 8007B09C 00000000 */  nop
/* 16A8668 8007B0A0 21104300 */  addu       $v0, $v0, $v1
/* 16A866C 8007B0A4 0780033C */  lui        $v1, %hi(g_GemTotal)
/* 16A8670 8007B0A8 6058638C */  lw         $v1, %lo(g_GemTotal)($v1)
/* 16A8674 8007B0AC 000082AC */  sw         $v0, 0x0($a0)
/* 16A8678 8007B0B0 0780023C */  lui        $v0, %hi(D_800756C8)
/* 16A867C 8007B0B4 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 16A8680 8007B0B8 0780013C */  lui        $at, %hi(D_8006E930)
/* 16A8684 8007B0BC 21082500 */  addu       $at, $at, $a1
/* 16A8688 8007B0C0 30E9248C */  lw         $a0, %lo(D_8006E930)($at)
/* 16A868C 8007B0C4 0C004224 */  addiu      $v0, $v0, 0xC
/* 16A8690 8007B0C8 21186400 */  addu       $v1, $v1, $a0
/* 16A8694 8007B0CC 0780013C */  lui        $at, %hi(D_800756C8)
/* 16A8698 8007B0D0 C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 16A869C 8007B0D4 01000224 */  addiu      $v0, $zero, 0x1
/* 16A86A0 8007B0D8 0780013C */  lui        $at, %hi(g_GemTotal)
/* 16A86A4 8007B0DC 605823AC */  sw         $v1, %lo(g_GemTotal)($at)
/* 16A86A8 8007B0E0 0880013C */  lui        $at, %hi(g_FlightCollected + 0x04)
/* 16A86AC 8007B0E4 21082600 */  addu       $at, $at, $a2
/* 16A86B0 8007B0E8 848622A0 */  sb         $v0, %lo(g_FlightCollected + 0x04)($at)
.Llevel_15_8007B0EC:
/* 16A86B4 8007B0EC 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 16A86B8 8007B0F0 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 16A86BC 8007B0F4 0880033C */  lui        $v1, %hi(g_FlightCourseRecords)
/* 16A86C0 8007B0F8 18866324 */  addiu      $v1, $v1, %lo(g_FlightCourseRecords)
/* 16A86C4 8007B0FC 80100200 */  sll        $v0, $v0, 2
/* 16A86C8 8007B100 21204300 */  addu       $a0, $v0, $v1
/* 16A86CC 8007B104 0000838C */  lw         $v1, 0x0($a0)
/* 16A86D0 8007B108 00000000 */  nop
/* 16A86D4 8007B10C 07006010 */  beqz       $v1, .Llevel_15_8007B12C
/* 16A86D8 8007B110 00000000 */   nop
/* 16A86DC 8007B114 0780023C */  lui        $v0, %hi(D_800758F4)
/* 16A86E0 8007B118 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 16A86E4 8007B11C 00000000 */  nop
/* 16A86E8 8007B120 2A104300 */  slt        $v0, $v0, $v1
/* 16A86EC 8007B124 05004010 */  beqz       $v0, .Llevel_15_8007B13C
/* 16A86F0 8007B128 00000000 */   nop
.Llevel_15_8007B12C:
/* 16A86F4 8007B12C 0780023C */  lui        $v0, %hi(D_800758F4)
/* 16A86F8 8007B130 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 16A86FC 8007B134 00000000 */  nop
/* 16A8700 8007B138 000082AC */  sw         $v0, 0x0($a0)
.Llevel_15_8007B13C:
/* 16A8704 8007B13C 0780023C */  lui        $v0, %hi(D_800756C8)
/* 16A8708 8007B140 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 16A870C 8007B144 00000000 */  nop
/* 16A8710 8007B148 19004018 */  blez       $v0, .Llevel_15_8007B1B0
/* 16A8714 8007B14C 21300000 */   addu      $a2, $zero, $zero
/* 16A8718 8007B150 AA2A043C */  lui        $a0, (0x2AAAAAAB >> 16)
/* 16A871C 8007B154 ABAA8434 */  ori        $a0, $a0, (0x2AAAAAAB & 0xFFFF)
/* 16A8720 8007B158 1800C400 */  mult       $a2, $a0
.Llevel_15_8007B15C:
/* 16A8724 8007B15C C3170600 */  sra        $v0, $a2, 31
/* 16A8728 8007B160 10780000 */  mfhi       $t7
/* 16A872C 8007B164 43180F00 */  sra        $v1, $t7, 1
/* 16A8730 8007B168 23186200 */  subu       $v1, $v1, $v0
/* 16A8734 8007B16C 40100300 */  sll        $v0, $v1, 1
/* 16A8738 8007B170 21104300 */  addu       $v0, $v0, $v1
/* 16A873C 8007B174 80100200 */  sll        $v0, $v0, 2
/* 16A8740 8007B178 2310C200 */  subu       $v0, $a2, $v0
/* 16A8744 8007B17C 0780013C */  lui        $at, %hi(D_8006E998)
/* 16A8748 8007B180 21082200 */  addu       $at, $at, $v0
/* 16A874C 8007B184 98E92390 */  lbu        $v1, %lo(D_8006E998)($at)
/* 16A8750 8007B188 1F00C230 */  andi       $v0, $a2, 0x1F
/* 16A8754 8007B18C 0780013C */  lui        $at, %hi(g_RecentGemsCollected)
/* 16A8758 8007B190 21082200 */  addu       $at, $at, $v0
/* 16A875C 8007B194 B87D23A0 */  sb         $v1, %lo(g_RecentGemsCollected)($at)
/* 16A8760 8007B198 0780023C */  lui        $v0, %hi(D_800756C8)
/* 16A8764 8007B19C C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 16A8768 8007B1A0 0100C624 */  addiu      $a2, $a2, 0x1
/* 16A876C 8007B1A4 2A10C200 */  slt        $v0, $a2, $v0
/* 16A8770 8007B1A8 ECFF4014 */  bnez       $v0, .Llevel_15_8007B15C
/* 16A8774 8007B1AC 1800C400 */   mult      $a2, $a0
.Llevel_15_8007B1B0:
/* 16A8778 8007B1B0 0080033C */  lui        $v1, (0x8000000E >> 16)
/* 16A877C 8007B1B4 0780023C */  lui        $v0, %hi(g_Camera + 0x58)
/* 16A8780 8007B1B8 286E428C */  lw         $v0, %lo(g_Camera + 0x58)($v0)
/* 16A8784 8007B1BC 0E006334 */  ori        $v1, $v1, (0x8000000E & 0xFFFF)
/* 16A8788 8007B1C0 0880013C */  lui        $at, %hi(g_Spyro + 0x7C)
/* 16A878C 8007B1C4 D48A20AC */  sw         $zero, %lo(g_Spyro + 0x7C)($at)
/* 16A8790 8007B1C8 08004314 */  bne        $v0, $v1, .Llevel_15_8007B1EC
/* 16A8794 8007B1CC 00000000 */   nop
/* 16A8798 8007B1D0 0880023C */  lui        $v0, %hi(g_Spyro + 0x78)
/* 16A879C 8007B1D4 D08A428C */  lw         $v0, %lo(g_Spyro + 0x78)($v0)
/* 16A87A0 8007B1D8 0780013C */  lui        $at, %hi(D_8006C588)
/* 16A87A4 8007B1DC 21082200 */  addu       $at, $at, $v0
/* 16A87A8 8007B1E0 88C52290 */  lbu        $v0, %lo(D_8006C588)($at)
/* 16A87AC 8007B1E4 0780013C */  lui        $at, %hi(g_Camera + 0xC0)
/* 16A87B0 8007B1E8 906E22AC */  sw         $v0, %lo(g_Camera + 0xC0)($at)
.Llevel_15_8007B1EC:
/* 16A87B4 8007B1EC 2000BF8F */  lw         $ra, 0x20($sp)
/* 16A87B8 8007B1F0 2800BD27 */  addiu      $sp, $sp, 0x28
/* 16A87BC 8007B1F4 0800E003 */  jr         $ra
/* 16A87C0 8007B1F8 00000000 */   nop
.size func_level_15_8007AEDC, . - func_level_15_8007AEDC
