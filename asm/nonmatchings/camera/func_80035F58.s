.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80035F58
/* 26758 80035F58 0880023C */  lui        $v0, %hi(g_Spyro + 0x1F4)
/* 2675C 80035F5C 4C8C428C */  lw         $v0, %lo(g_Spyro + 0x1F4)($v0)
/* 26760 80035F60 C00680AF */  sw         $zero, %gp_rel(D_80075924)($gp)
/* 26764 80035F64 00104230 */  andi       $v0, $v0, 0x1000
/* 26768 80035F68 10004014 */  bnez       $v0, .L80035FAC
/* 2676C 80035F6C 00000000 */   nop
/* 26770 80035F70 0780023C */  lui        $v0, %hi(g_Camera + 0xC8)
/* 26774 80035F74 986E428C */  lw         $v0, %lo(g_Camera + 0xC8)($v0)
/* 26778 80035F78 00000000 */  nop
/* 2677C 80035F7C 0B004014 */  bnez       $v0, .L80035FAC
/* 26780 80035F80 00000000 */   nop
/* 26784 80035F84 0780033C */  lui        $v1, %hi(g_Pad + 0x8)
/* 26788 80035F88 8073638C */  lw         $v1, %lo(g_Pad + 0x8)($v1)
/* 2678C 80035F8C 00000000 */  nop
/* 26790 80035F90 02006230 */  andi       $v0, $v1, 0x2
/* 26794 80035F94 04004014 */  bnez       $v0, .L80035FA8
/* 26798 80035F98 00FC0224 */   addiu     $v0, $zero, -0x400
/* 2679C 80035F9C 01006230 */  andi       $v0, $v1, 0x1
/* 267A0 80035FA0 02004010 */  beqz       $v0, .L80035FAC
/* 267A4 80035FA4 00040224 */   addiu     $v0, $zero, 0x400
.L80035FA8:
/* 267A8 80035FA8 C00682AF */  sw         $v0, %gp_rel(D_80075924)($gp)
.L80035FAC:
/* 267AC 80035FAC 0800E003 */  jr         $ra
/* 267B0 80035FB0 00000000 */   nop
.size func_80035F58, . - func_80035F58
