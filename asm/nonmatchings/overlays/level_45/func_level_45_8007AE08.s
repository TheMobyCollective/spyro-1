.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_45_8007AE08
/* 4256BD0 8007AE08 0780023C */  lui        $v0, %hi(g_Gamestate)
/* 4256BD4 8007AE0C D857428C */  lw         $v0, %lo(g_Gamestate)($v0)
/* 4256BD8 8007AE10 07000324 */  addiu      $v1, $zero, 0x7
/* 4256BDC 8007AE14 2F004310 */  beq        $v0, $v1, .Llevel_45_8007AED4
/* 4256BE0 8007AE18 00000000 */   nop
/* 4256BE4 8007AE1C 0780023C */  lui        $v0, %hi(D_800758F4)
/* 4256BE8 8007AE20 F458428C */  lw         $v0, %lo(D_800758F4)($v0)
/* 4256BEC 8007AE24 0780013C */  lui        $at, %hi(g_Gamestate)
/* 4256BF0 8007AE28 D85723AC */  sw         $v1, %lo(g_Gamestate)($at)
/* 4256BF4 8007AE2C 80180200 */  sll        $v1, $v0, 2
/* 4256BF8 8007AE30 21186200 */  addu       $v1, $v1, $v0
/* 4256BFC 8007AE34 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 4256C00 8007AE38 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 4256C04 8007AE3C 0880043C */  lui        $a0, %hi(D_80078618)
/* 4256C08 8007AE40 18868424 */  addiu      $a0, $a0, %lo(D_80078618)
/* 4256C0C 8007AE44 0780013C */  lui        $at, %hi(D_80075720)
/* 4256C10 8007AE48 205720AC */  sw         $zero, %lo(D_80075720)($at)
/* 4256C14 8007AE4C 0780013C */  lui        $at, %hi(D_8007568C)
/* 4256C18 8007AE50 8C5620AC */  sw         $zero, %lo(D_8007568C)($at)
/* 4256C1C 8007AE54 0780013C */  lui        $at, %hi(D_800758B8)
/* 4256C20 8007AE58 B85820AC */  sw         $zero, %lo(D_800758B8)($at)
/* 4256C24 8007AE5C 0780013C */  lui        $at, %hi(D_80075744)
/* 4256C28 8007AE60 445720AC */  sw         $zero, %lo(D_80075744)($at)
/* 4256C2C 8007AE64 0780013C */  lui        $at, %hi(D_800757CC)
/* 4256C30 8007AE68 CC5720AC */  sw         $zero, %lo(D_800757CC)($at)
/* 4256C34 8007AE6C 0780013C */  lui        $at, %hi(D_8007569C)
/* 4256C38 8007AE70 9C5620AC */  sw         $zero, %lo(D_8007569C)($at)
/* 4256C3C 8007AE74 80100200 */  sll        $v0, $v0, 2
/* 4256C40 8007AE78 21304400 */  addu       $a2, $v0, $a0
/* 4256C44 8007AE7C 0000C28C */  lw         $v0, 0x0($a2)
/* 4256C48 8007AE80 40280300 */  sll        $a1, $v1, 1
/* 4256C4C 8007AE84 0780013C */  lui        $at, %hi(D_800758F4)
/* 4256C50 8007AE88 F45825AC */  sw         $a1, %lo(D_800758F4)($at)
/* 4256C54 8007AE8C 11004014 */  bnez       $v0, .Llevel_45_8007AED4
/* 4256C58 8007AE90 00000000 */   nop
/* 4256C5C 8007AE94 0880023C */  lui        $v0, %hi(D_80078630)
/* 4256C60 8007AE98 3086428C */  lw         $v0, %lo(D_80078630)($v0)
/* 4256C64 8007AE9C 0880033C */  lui        $v1, %hi(D_80078634)
/* 4256C68 8007AEA0 3486638C */  lw         $v1, %lo(D_80078634)($v1)
/* 4256C6C 8007AEA4 00000000 */  nop
/* 4256C70 8007AEA8 21104300 */  addu       $v0, $v0, $v1
/* 4256C74 8007AEAC 0880033C */  lui        $v1, %hi(D_80078638)
/* 4256C78 8007AEB0 3886638C */  lw         $v1, %lo(D_80078638)($v1)
/* 4256C7C 8007AEB4 0880043C */  lui        $a0, %hi(D_8007863C)
/* 4256C80 8007AEB8 3C86848C */  lw         $a0, %lo(D_8007863C)($a0)
/* 4256C84 8007AEBC 21104300 */  addu       $v0, $v0, $v1
/* 4256C88 8007AEC0 21104400 */  addu       $v0, $v0, $a0
/* 4256C8C 8007AEC4 20000324 */  addiu      $v1, $zero, 0x20
/* 4256C90 8007AEC8 02004314 */  bne        $v0, $v1, .Llevel_45_8007AED4
/* 4256C94 8007AECC 00000000 */   nop
/* 4256C98 8007AED0 0000C5AC */  sw         $a1, 0x0($a2)
.Llevel_45_8007AED4:
/* 4256C9C 8007AED4 0800E003 */  jr         $ra
/* 4256CA0 8007AED8 00000000 */   nop
.size func_level_45_8007AE08, . - func_level_45_8007AE08
