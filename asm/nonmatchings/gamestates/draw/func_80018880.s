.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80018880
/* 9080 80018880 0780043C */  lui        $a0, %hi(D_8006FCF4 + 0x2400)
/* 9084 80018884 F4208424 */  addiu      $a0, $a0, %lo(D_8006FCF4 + 0x2400)
/* 9088 80018888 0000828C */  lw         $v0, 0x0($a0)
/* 908C 8001888C 00000000 */  nop
/* 9090 80018890 07004010 */  beqz       $v0, .L800188B0
/* 9094 80018894 00000000 */   nop
/* 9098 80018898 04008424 */  addiu      $a0, $a0, 0x4
.L8001889C:
/* 909C 8001889C 0000828C */  lw         $v0, 0x0($a0)
/* 90A0 800188A0 00000000 */  nop
/* 90A4 800188A4 FDFF4014 */  bnez       $v0, .L8001889C
/* 90A8 800188A8 04008424 */   addiu     $a0, $a0, 0x4
/* 90AC 800188AC FCFF8424 */  addiu      $a0, $a0, -0x4
.L800188B0:
/* 90B0 800188B0 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 90B4 800188B4 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 90B8 800188B8 0780023C */  lui        $v0, %hi(D_800756FC)
/* 90BC 800188BC FC56428C */  lw         $v0, %lo(D_800756FC)($v0)
/* 90C0 800188C0 00000000 */  nop
/* 90C4 800188C4 0E006210 */  beq        $v1, $v0, .L80018900
/* 90C8 800188C8 00000000 */   nop
.L800188CC:
/* 90CC 800188CC 0780023C */  lui        $v0, %hi(g_HudMobys)
/* 90D0 800188D0 1057428C */  lw         $v0, %lo(g_HudMobys)($v0)
/* 90D4 800188D4 00000000 */  nop
/* 90D8 800188D8 000082AC */  sw         $v0, 0x0($a0)
/* 90DC 800188DC 0780023C */  lui        $v0, %hi(g_HudMobys)
/* 90E0 800188E0 1057428C */  lw         $v0, %lo(g_HudMobys)($v0)
/* 90E4 800188E4 0780033C */  lui        $v1, %hi(D_800756FC)
/* 90E8 800188E8 FC56638C */  lw         $v1, %lo(D_800756FC)($v1)
/* 90EC 800188EC 58004224 */  addiu      $v0, $v0, 0x58
/* 90F0 800188F0 0780013C */  lui        $at, %hi(g_HudMobys)
/* 90F4 800188F4 105722AC */  sw         $v0, %lo(g_HudMobys)($at)
/* 90F8 800188F8 F4FF4314 */  bne        $v0, $v1, .L800188CC
/* 90FC 800188FC 04008424 */   addiu     $a0, $a0, 0x4
.L80018900:
/* 9100 80018900 0800E003 */  jr         $ra
/* 9104 80018904 000080AC */   sw        $zero, 0x0($a0)
.size func_80018880, . - func_80018880
