.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_15_8007AE08
/* 16A83D0 8007AE08 0780023C */  lui        $v0, %hi(g_Gamestate)
/* 16A83D4 8007AE0C D857428C */  lw         $v0, %lo(g_Gamestate)($v0)
/* 16A83D8 8007AE10 07000324 */  addiu      $v1, $zero, 0x7
/* 16A83DC 8007AE14 2F004310 */  beq        $v0, $v1, .Llevel_15_8007AED4
/* 16A83E0 8007AE18 00000000 */   nop
/* 16A83E4 8007AE1C 0780023C */  lui        $v0, %hi(D_800758F4)
/* 16A83E8 8007AE20 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 16A83EC 8007AE24 0780013C */  lui        $at, %hi(g_Gamestate)
/* 16A83F0 8007AE28 D85723AC */  sw         $v1, %lo(g_Gamestate)($at)
/* 16A83F4 8007AE2C 80180200 */  sll        $v1, $v0, 2
/* 16A83F8 8007AE30 21186200 */  addu       $v1, $v1, $v0
/* 16A83FC 8007AE34 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 16A8400 8007AE38 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 16A8404 8007AE3C 0880043C */  lui        $a0, %hi(D_80078618)
/* 16A8408 8007AE40 18868424 */  addiu      $a0, $a0, %lo(D_80078618)
/* 16A840C 8007AE44 0780013C */  lui        $at, %hi(D_80075720)
/* 16A8410 8007AE48 205720AC */  sw         $zero, %lo(D_80075720)($at)
/* 16A8414 8007AE4C 0780013C */  lui        $at, %hi(D_8007568C)
/* 16A8418 8007AE50 8C5620AC */  sw         $zero, %lo(D_8007568C)($at)
/* 16A841C 8007AE54 0780013C */  lui        $at, %hi(D_800758B8)
/* 16A8420 8007AE58 B85820AC */  sw         $zero, %lo(D_800758B8)($at)
/* 16A8424 8007AE5C 0780013C */  lui        $at, %hi(D_80075744)
/* 16A8428 8007AE60 445720AC */  sw         $zero, %lo(D_80075744)($at)
/* 16A842C 8007AE64 0780013C */  lui        $at, %hi(D_800757CC)
/* 16A8430 8007AE68 CC5720AC */  sw         $zero, %lo(D_800757CC)($at)
/* 16A8434 8007AE6C 0780013C */  lui        $at, %hi(D_8007569C)
/* 16A8438 8007AE70 9C5620AC */  sw         $zero, %lo(D_8007569C)($at)
/* 16A843C 8007AE74 80100200 */  sll        $v0, $v0, 2
/* 16A8440 8007AE78 21304400 */  addu       $a2, $v0, $a0
/* 16A8444 8007AE7C 0000C28C */  lw         $v0, 0x0($a2)
/* 16A8448 8007AE80 40280300 */  sll        $a1, $v1, 1
/* 16A844C 8007AE84 0780013C */  lui        $at, %hi(D_800758F4)
/* 16A8450 8007AE88 F45825AC */  sw         $a1, %lo(D_800758F4)($at)
/* 16A8454 8007AE8C 11004014 */  bnez       $v0, .Llevel_15_8007AED4
/* 16A8458 8007AE90 00000000 */   nop
/* 16A845C 8007AE94 0880023C */  lui        $v0, %hi(g_FlightObjectiveCounters)
/* 16A8460 8007AE98 3086428C */  lw         $v0, %lo(g_FlightObjectiveCounters)($v0)
/* 16A8464 8007AE9C 0880033C */  lui        $v1, %hi(D_80078634)
/* 16A8468 8007AEA0 3486638C */  lw         $v1, %lo(D_80078634)($v1)
/* 16A846C 8007AEA4 00000000 */  nop
/* 16A8470 8007AEA8 21104300 */  addu       $v0, $v0, $v1
/* 16A8474 8007AEAC 0880033C */  lui        $v1, %hi(D_80078638)
/* 16A8478 8007AEB0 3886638C */  lw         $v1, %lo(D_80078638)($v1)
/* 16A847C 8007AEB4 0880043C */  lui        $a0, %hi(D_8007863C)
/* 16A8480 8007AEB8 3C86848C */  lw         $a0, %lo(D_8007863C)($a0)
/* 16A8484 8007AEBC 21104300 */  addu       $v0, $v0, $v1
/* 16A8488 8007AEC0 21104400 */  addu       $v0, $v0, $a0
/* 16A848C 8007AEC4 20000324 */  addiu      $v1, $zero, 0x20
/* 16A8490 8007AEC8 02004314 */  bne        $v0, $v1, .Llevel_15_8007AED4
/* 16A8494 8007AECC 00000000 */   nop
/* 16A8498 8007AED0 0000C5AC */  sw         $a1, 0x0($a2)
.Llevel_15_8007AED4:
/* 16A849C 8007AED4 0800E003 */  jr         $ra
/* 16A84A0 8007AED8 00000000 */   nop
.size func_level_15_8007AE08, . - func_level_15_8007AE08
