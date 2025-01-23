.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80034198
/* 24998 80034198 0780043C */  lui        $a0, %hi(g_Camera + 0xD8)
/* 2499C 8003419C A86E848C */  lw         $a0, %lo(g_Camera + 0xD8)($a0)
/* 249A0 800341A0 0780033C */  lui        $v1, %hi(g_Camera + 0xD4)
/* 249A4 800341A4 A46E638C */  lw         $v1, %lo(g_Camera + 0xD4)($v1)
/* 249A8 800341A8 0000828C */  lw         $v0, 0x0($a0)
/* 249AC 800341AC 00000000 */  nop
/* 249B0 800341B0 23104300 */  subu       $v0, $v0, $v1
/* 249B4 800341B4 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 249B8 800341B8 0780013C */  lui        $at, %hi(g_Camera + 0x60)
/* 249BC 800341BC 306E22AC */  sw         $v0, %lo(g_Camera + 0x60)($at)
/* 249C0 800341C0 0400828C */  lw         $v0, 0x4($a0)
/* 249C4 800341C4 0780013C */  lui        $at, %hi(g_Camera + 0x64)
/* 249C8 800341C8 346E22AC */  sw         $v0, %lo(g_Camera + 0x64)($at)
/* 249CC 800341CC 0800828C */  lw         $v0, 0x8($a0)
/* 249D0 800341D0 0780013C */  lui        $at, %hi(g_Camera + 0x68)
/* 249D4 800341D4 386E22AC */  sw         $v0, %lo(g_Camera + 0x68)($at)
/* 249D8 800341D8 0C00828C */  lw         $v0, 0xC($a0)
/* 249DC 800341DC 0780013C */  lui        $at, %hi(g_Camera + 0x6C)
/* 249E0 800341E0 3C6E22AC */  sw         $v0, %lo(g_Camera + 0x6C)($at)
/* 249E4 800341E4 1000828C */  lw         $v0, 0x10($a0)
/* 249E8 800341E8 0780013C */  lui        $at, %hi(g_Camera + 0x70)
/* 249EC 800341EC 406E22AC */  sw         $v0, %lo(g_Camera + 0x70)($at)
/* 249F0 800341F0 1400828C */  lw         $v0, 0x14($a0)
/* 249F4 800341F4 0780013C */  lui        $at, %hi(g_Camera + 0x74)
/* 249F8 800341F8 446E22AC */  sw         $v0, %lo(g_Camera + 0x74)($at)
/* 249FC 800341FC 0800E003 */  jr         $ra
/* 24A00 80034200 00000000 */   nop
.size func_80034198, . - func_80034198
