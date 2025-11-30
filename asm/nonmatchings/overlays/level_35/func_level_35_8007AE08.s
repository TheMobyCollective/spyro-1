.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_35_8007AE08
/* 33DFBD0 8007AE08 0780023C */  lui        $v0, %hi(g_Gamestate)
/* 33DFBD4 8007AE0C D857428C */  lw         $v0, %lo(g_Gamestate)($v0)
/* 33DFBD8 8007AE10 07000324 */  addiu      $v1, $zero, 0x7
/* 33DFBDC 8007AE14 2F004310 */  beq        $v0, $v1, .Llevel_35_8007AED4
/* 33DFBE0 8007AE18 00000000 */   nop
/* 33DFBE4 8007AE1C 0780023C */  lui        $v0, %hi(D_800758F4)
/* 33DFBE8 8007AE20 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 33DFBEC 8007AE24 0780013C */  lui        $at, %hi(g_Gamestate)
/* 33DFBF0 8007AE28 D85723AC */  sw         $v1, %lo(g_Gamestate)($at)
/* 33DFBF4 8007AE2C 80180200 */  sll        $v1, $v0, 2
/* 33DFBF8 8007AE30 21186200 */  addu       $v1, $v1, $v0
/* 33DFBFC 8007AE34 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 33DFC00 8007AE38 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 33DFC04 8007AE3C 0880043C */  lui        $a0, %hi(D_80078618)
/* 33DFC08 8007AE40 18868424 */  addiu      $a0, $a0, %lo(D_80078618)
/* 33DFC0C 8007AE44 0780013C */  lui        $at, %hi(D_80075720)
/* 33DFC10 8007AE48 205720AC */  sw         $zero, %lo(D_80075720)($at)
/* 33DFC14 8007AE4C 0780013C */  lui        $at, %hi(D_8007568C)
/* 33DFC18 8007AE50 8C5620AC */  sw         $zero, %lo(D_8007568C)($at)
/* 33DFC1C 8007AE54 0780013C */  lui        $at, %hi(D_800758B8)
/* 33DFC20 8007AE58 B85820AC */  sw         $zero, %lo(D_800758B8)($at)
/* 33DFC24 8007AE5C 0780013C */  lui        $at, %hi(D_80075744)
/* 33DFC28 8007AE60 445720AC */  sw         $zero, %lo(D_80075744)($at)
/* 33DFC2C 8007AE64 0780013C */  lui        $at, %hi(D_800757CC)
/* 33DFC30 8007AE68 CC5720AC */  sw         $zero, %lo(D_800757CC)($at)
/* 33DFC34 8007AE6C 0780013C */  lui        $at, %hi(D_8007569C)
/* 33DFC38 8007AE70 9C5620AC */  sw         $zero, %lo(D_8007569C)($at)
/* 33DFC3C 8007AE74 80100200 */  sll        $v0, $v0, 2
/* 33DFC40 8007AE78 21304400 */  addu       $a2, $v0, $a0
/* 33DFC44 8007AE7C 0000C28C */  lw         $v0, 0x0($a2)
/* 33DFC48 8007AE80 40280300 */  sll        $a1, $v1, 1
/* 33DFC4C 8007AE84 0780013C */  lui        $at, %hi(D_800758F4)
/* 33DFC50 8007AE88 F45825AC */  sw         $a1, %lo(D_800758F4)($at)
/* 33DFC54 8007AE8C 11004014 */  bnez       $v0, .Llevel_35_8007AED4
/* 33DFC58 8007AE90 00000000 */   nop
/* 33DFC5C 8007AE94 0880023C */  lui        $v0, %hi(D_80078630)
/* 33DFC60 8007AE98 3086428C */  lw         $v0, %lo(D_80078630)($v0)
/* 33DFC64 8007AE9C 0880033C */  lui        $v1, %hi(D_80078634)
/* 33DFC68 8007AEA0 3486638C */  lw         $v1, %lo(D_80078634)($v1)
/* 33DFC6C 8007AEA4 00000000 */  nop
/* 33DFC70 8007AEA8 21104300 */  addu       $v0, $v0, $v1
/* 33DFC74 8007AEAC 0880033C */  lui        $v1, %hi(D_80078638)
/* 33DFC78 8007AEB0 3886638C */  lw         $v1, %lo(D_80078638)($v1)
/* 33DFC7C 8007AEB4 0880043C */  lui        $a0, %hi(D_8007863C)
/* 33DFC80 8007AEB8 3C86848C */  lw         $a0, %lo(D_8007863C)($a0)
/* 33DFC84 8007AEBC 21104300 */  addu       $v0, $v0, $v1
/* 33DFC88 8007AEC0 21104400 */  addu       $v0, $v0, $a0
/* 33DFC8C 8007AEC4 20000324 */  addiu      $v1, $zero, 0x20
/* 33DFC90 8007AEC8 02004314 */  bne        $v0, $v1, .Llevel_35_8007AED4
/* 33DFC94 8007AECC 00000000 */   nop
/* 33DFC98 8007AED0 0000C5AC */  sw         $a1, 0x0($a2)
.Llevel_35_8007AED4:
/* 33DFC9C 8007AED4 0800E003 */  jr         $ra
/* 33DFCA0 8007AED8 00000000 */   nop
.size func_level_35_8007AE08, . - func_level_35_8007AE08
