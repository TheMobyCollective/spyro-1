.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002C664
/* 1CE64 8002C664 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1CE68 8002C668 1000BFAF */  sw         $ra, 0x10($sp)
/* 1CE6C 8002C66C 1F63010C */  jal        SpecularReset
/* 1CE70 8002C670 00000000 */   nop
/* 1CE74 8002C674 6666023C */  lui        $v0, (0x66666667 >> 16)
/* 1CE78 8002C678 67664234 */  ori        $v0, $v0, (0x66666667 & 0xFFFF)
/* 1CE7C 8002C67C 0080033C */  lui        $v1, (0x80000012 >> 16)
/* 1CE80 8002C680 0780043C */  lui        $a0, %hi(g_LevelId)
/* 1CE84 8002C684 6C59848C */  lw         $a0, %lo(g_LevelId)($a0)
/* 1CE88 8002C688 12006334 */  ori        $v1, $v1, (0x80000012 & 0xFFFF)
/* 1CE8C 8002C68C 0780013C */  lui        $at, %hi(g_LoadStage)
/* 1CE90 8002C690 645820AC */  sw         $zero, %lo(g_LoadStage)($at)
/* 1CE94 8002C694 18008200 */  mult       $a0, $v0
/* 1CE98 8002C698 0780013C */  lui        $at, %hi(D_800756AC)
/* 1CE9C 8002C69C AC5620AC */  sw         $zero, %lo(D_800756AC)($at)
/* 1CEA0 8002C6A0 0780013C */  lui        $at, %hi(g_Camera + 0xC0)
/* 1CEA4 8002C6A4 906E23AC */  sw         $v1, %lo(g_Camera + 0xC0)($at)
/* 1CEA8 8002C6A8 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 1CEAC 8002C6AC 0780013C */  lui        $at, %hi(D_8007576C)
/* 1CEB0 8002C6B0 6C5722AC */  sw         $v0, %lo(D_8007576C)($at)
/* 1CEB4 8002C6B4 01000224 */  addiu      $v0, $zero, 0x1
/* 1CEB8 8002C6B8 0780013C */  lui        $at, %hi(D_800758AC)
/* 1CEBC 8002C6BC AC5824AC */  sw         $a0, %lo(D_800758AC)($at)
/* 1CEC0 8002C6C0 C3270400 */  sra        $a0, $a0, 31
/* 1CEC4 8002C6C4 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1CEC8 8002C6C8 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1CECC 8002C6CC 0780013C */  lui        $at, %hi(D_800756D0)
/* 1CED0 8002C6D0 D05622AC */  sw         $v0, %lo(D_800756D0)($at)
/* 1CED4 8002C6D4 0780013C */  lui        $at, %hi(D_800756B0)
/* 1CED8 8002C6D8 B05622AC */  sw         $v0, %lo(D_800756B0)($at)
/* 1CEDC 8002C6DC 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 1CEE0 8002C6E0 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 1CEE4 8002C6E4 10280000 */  mfhi       $a1
/* 1CEE8 8002C6E8 83180500 */  sra        $v1, $a1, 2
/* 1CEEC 8002C6EC 23186400 */  subu       $v1, $v1, $a0
/* 1CEF0 8002C6F0 80100300 */  sll        $v0, $v1, 2
/* 1CEF4 8002C6F4 21104300 */  addu       $v0, $v0, $v1
/* 1CEF8 8002C6F8 40100200 */  sll        $v0, $v0, 1
/* 1CEFC 8002C6FC 0780013C */  lui        $at, %hi(D_800758B4)
/* 1CF00 8002C700 B45822AC */  sw         $v0, %lo(D_800758B4)($at)
/* 1CF04 8002C704 1000BF8F */  lw         $ra, 0x10($sp)
/* 1CF08 8002C708 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1CF0C 8002C70C 0800E003 */  jr         $ra
/* 1CF10 8002C710 00000000 */   nop
.size func_8002C664, . - func_8002C664
