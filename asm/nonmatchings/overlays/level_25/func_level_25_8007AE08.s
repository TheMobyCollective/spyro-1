.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_25_8007AE08
/* 258FBD0 8007AE08 0780023C */  lui        $v0, %hi(g_Gamestate)
/* 258FBD4 8007AE0C D857428C */  lw         $v0, %lo(g_Gamestate)($v0)
/* 258FBD8 8007AE10 07000324 */  addiu      $v1, $zero, 0x7
/* 258FBDC 8007AE14 2F004310 */  beq        $v0, $v1, .Llevel_25_8007AED4
/* 258FBE0 8007AE18 00000000 */   nop
/* 258FBE4 8007AE1C 0780023C */  lui        $v0, %hi(D_800758F4)
/* 258FBE8 8007AE20 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 258FBEC 8007AE24 0780013C */  lui        $at, %hi(g_Gamestate)
/* 258FBF0 8007AE28 D85723AC */  sw         $v1, %lo(g_Gamestate)($at)
/* 258FBF4 8007AE2C 80180200 */  sll        $v1, $v0, 2
/* 258FBF8 8007AE30 21186200 */  addu       $v1, $v1, $v0
/* 258FBFC 8007AE34 0780023C */  lui        $v0, %hi(D_8007595C)
/* 258FC00 8007AE38 5C59428C */  lw         $v0, %lo(D_8007595C)($v0)
/* 258FC04 8007AE3C 0880043C */  lui        $a0, %hi(D_80078618)
/* 258FC08 8007AE40 18868424 */  addiu      $a0, $a0, %lo(D_80078618)
/* 258FC0C 8007AE44 0780013C */  lui        $at, %hi(D_80075720)
/* 258FC10 8007AE48 205720AC */  sw         $zero, %lo(D_80075720)($at)
/* 258FC14 8007AE4C 0780013C */  lui        $at, %hi(D_8007568C)
/* 258FC18 8007AE50 8C5620AC */  sw         $zero, %lo(D_8007568C)($at)
/* 258FC1C 8007AE54 0780013C */  lui        $at, %hi(D_800758B8)
/* 258FC20 8007AE58 B85820AC */  sw         $zero, %lo(D_800758B8)($at)
/* 258FC24 8007AE5C 0780013C */  lui        $at, %hi(D_80075744)
/* 258FC28 8007AE60 445720AC */  sw         $zero, %lo(D_80075744)($at)
/* 258FC2C 8007AE64 0780013C */  lui        $at, %hi(D_800757CC)
/* 258FC30 8007AE68 CC5720AC */  sw         $zero, %lo(D_800757CC)($at)
/* 258FC34 8007AE6C 0780013C */  lui        $at, %hi(D_8007569C)
/* 258FC38 8007AE70 9C5620AC */  sw         $zero, %lo(D_8007569C)($at)
/* 258FC3C 8007AE74 80100200 */  sll        $v0, $v0, 2
/* 258FC40 8007AE78 21304400 */  addu       $a2, $v0, $a0
/* 258FC44 8007AE7C 0000C28C */  lw         $v0, 0x0($a2)
/* 258FC48 8007AE80 40280300 */  sll        $a1, $v1, 1
/* 258FC4C 8007AE84 0780013C */  lui        $at, %hi(D_800758F4)
/* 258FC50 8007AE88 F45825AC */  sw         $a1, %lo(D_800758F4)($at)
/* 258FC54 8007AE8C 11004014 */  bnez       $v0, .Llevel_25_8007AED4
/* 258FC58 8007AE90 00000000 */   nop
/* 258FC5C 8007AE94 0880023C */  lui        $v0, %hi(D_80078630)
/* 258FC60 8007AE98 3086428C */  lw         $v0, %lo(D_80078630)($v0)
/* 258FC64 8007AE9C 0880033C */  lui        $v1, %hi(D_80078634)
/* 258FC68 8007AEA0 3486638C */  lw         $v1, %lo(D_80078634)($v1)
/* 258FC6C 8007AEA4 00000000 */  nop
/* 258FC70 8007AEA8 21104300 */  addu       $v0, $v0, $v1
/* 258FC74 8007AEAC 0880033C */  lui        $v1, %hi(D_80078638)
/* 258FC78 8007AEB0 3886638C */  lw         $v1, %lo(D_80078638)($v1)
/* 258FC7C 8007AEB4 0880043C */  lui        $a0, %hi(D_8007863C)
/* 258FC80 8007AEB8 3C86848C */  lw         $a0, %lo(D_8007863C)($a0)
/* 258FC84 8007AEBC 21104300 */  addu       $v0, $v0, $v1
/* 258FC88 8007AEC0 21104400 */  addu       $v0, $v0, $a0
/* 258FC8C 8007AEC4 20000324 */  addiu      $v1, $zero, 0x20
/* 258FC90 8007AEC8 02004314 */  bne        $v0, $v1, .Llevel_25_8007AED4
/* 258FC94 8007AECC 00000000 */   nop
/* 258FC98 8007AED0 0000C5AC */  sw         $a1, 0x0($a2)
.Llevel_25_8007AED4:
/* 258FC9C 8007AED4 0800E003 */  jr         $ra
/* 258FCA0 8007AED8 00000000 */   nop
.size func_level_25_8007AE08, . - func_level_25_8007AE08
