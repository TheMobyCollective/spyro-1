.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8004AA0C
/* 3B20C 8004AA0C A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 3B210 8004AA10 0780043C */  lui        $a0, %hi(g_Pad)
/* 3B214 8004AA14 78738424 */  addiu      $a0, $a0, %lo(g_Pad)
/* 3B218 8004AA18 0780053C */  lui        $a1, %hi(D_800776D8)
/* 3B21C 8004AA1C D876A524 */  addiu      $a1, $a1, %lo(D_800776D8)
/* 3B220 8004AA20 5000BFAF */  sw         $ra, 0x50($sp)
/* 3B224 8004AA24 4C00B1AF */  sw         $s1, 0x4C($sp)
/* 3B228 8004AA28 4800B0AF */  sw         $s0, 0x48($sp)
/* 3B22C 8004AA2C 0780013C */  lui        $at, %hi(D_80075944)
/* 3B230 8004AA30 445920A0 */  sb         $zero, %lo(D_80075944)($at)
/* 3B234 8004AA34 C24D010C */  jal        func_80053708
/* 3B238 8004AA38 00000000 */   nop
/* 3B23C 8004AA3C 0880043C */  lui        $a0, %hi(g_Spyro + 0x78)
/* 3B240 8004AA40 D08A8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0x78)
/* 3B244 8004AA44 0000838C */  lw         $v1, 0x0($a0)
/* 3B248 8004AA48 0F000224 */  addiu      $v0, $zero, 0xF
/* 3B24C 8004AA4C 03006214 */  bne        $v1, $v0, .L8004AA5C
/* 3B250 8004AA50 08000224 */   addiu     $v0, $zero, 0x8
/* 3B254 8004AA54 0880013C */  lui        $at, %hi(g_Spyro + 0x7C)
/* 3B258 8004AA58 D48A22AC */  sw         $v0, %lo(g_Spyro + 0x7C)($at)
.L8004AA5C:
/* 3B25C 8004AA5C 0880023C */  lui        $v0, %hi(g_Spyro + 0x1F0)
/* 3B260 8004AA60 488C428C */  lw         $v0, %lo(g_Spyro + 0x1F0)($v0)
/* 3B264 8004AA64 00000000 */  nop
/* 3B268 8004AA68 0300401C */  bgtz       $v0, .L8004AA78
/* 3B26C 8004AA6C 01000224 */   addiu     $v0, $zero, 0x1
/* 3B270 8004AA70 0880013C */  lui        $at, %hi(g_Spyro + 0x1F0)
/* 3B274 8004AA74 488C22AC */  sw         $v0, %lo(g_Spyro + 0x1F0)($at)
.L8004AA78:
/* 3B278 8004AA78 BC5D000C */  jal        VecNull
/* 3B27C 8004AA7C 88008424 */   addiu     $a0, $a0, 0x88
/* 3B280 8004AA80 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B284 8004AA84 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B288 8004AA88 00000000 */  nop
/* 3B28C 8004AA8C 09004018 */  blez       $v0, .L8004AAB4
/* 3B290 8004AA90 21800000 */   addu      $s0, $zero, $zero
.L8004AA94:
/* 3B294 8004AA94 F90F010C */  jal        func_80043FE4
/* 3B298 8004AA98 21200002 */   addu      $a0, $s0, $zero
/* 3B29C 8004AA9C 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B2A0 8004AAA0 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B2A4 8004AAA4 01001026 */  addiu      $s0, $s0, 0x1
/* 3B2A8 8004AAA8 2A100202 */  slt        $v0, $s0, $v0
/* 3B2AC 8004AAAC F9FF4014 */  bnez       $v0, .L8004AA94
/* 3B2B0 8004AAB0 00000000 */   nop
.L8004AAB4:
/* 3B2B4 8004AAB4 0880103C */  lui        $s0, %hi(g_Spyro + 0x100)
/* 3B2B8 8004AAB8 588B1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x100)
/* 3B2BC 8004AABC 21200002 */  addu       $a0, $s0, $zero
/* 3B2C0 8004AAC0 B25D000C */  jal        func_800176C8
/* 3B2C4 8004AAC4 06000524 */   addiu     $a1, $zero, 0x6
/* 3B2C8 8004AAC8 8CFF0426 */  addiu      $a0, $s0, -0x74
/* 3B2CC 8004AACC 00FF1126 */  addiu      $s1, $s0, -0x100
/* 3B2D0 8004AAD0 C05D000C */  jal        VecCopy
/* 3B2D4 8004AAD4 21282002 */   addu      $a1, $s1, $zero
/* 3B2D8 8004AAD8 21202002 */  addu       $a0, $s1, $zero
/* 3B2DC 8004AADC 21288000 */  addu       $a1, $a0, $zero
/* 3B2E0 8004AAE0 D65D000C */  jal        VecAdd
/* 3B2E4 8004AAE4 21300002 */   addu      $a2, $s0, $zero
/* 3B2E8 8004AAE8 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B2EC 8004AAEC CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B2F0 8004AAF0 00000000 */  nop
/* 3B2F4 8004AAF4 0B004018 */  blez       $v0, .L8004AB24
/* 3B2F8 8004AAF8 21800000 */   addu      $s0, $zero, $zero
.L8004AAFC:
/* 3B2FC 8004AAFC 2322010C */  jal        func_8004888C
/* 3B300 8004AB00 01001026 */   addiu     $s0, $s0, 0x1
/* 3B304 8004AB04 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B308 8004AB08 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B30C 8004AB0C 00000000 */  nop
/* 3B310 8004AB10 2A100202 */  slt        $v0, $s0, $v0
/* 3B314 8004AB14 F9FF4014 */  bnez       $v0, .L8004AAFC
/* 3B318 8004AB18 00000000 */   nop
/* 3B31C 8004AB1C 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B320 8004AB20 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
.L8004AB24:
/* 3B324 8004AB24 00000000 */  nop
/* 3B328 8004AB28 11004018 */  blez       $v0, .L8004AB70
/* 3B32C 8004AB2C 21800000 */   addu      $s0, $zero, $zero
.L8004AB30:
/* 3B330 8004AB30 65F4000C */  jal        func_8003D194
/* 3B334 8004AB34 01001026 */   addiu     $s0, $s0, 0x1
/* 3B338 8004AB38 7026010C */  jal        func_800499C0
/* 3B33C 8004AB3C 00000000 */   nop
/* 3B340 8004AB40 9825010C */  jal        func_80049660
/* 3B344 8004AB44 00000000 */   nop
/* 3B348 8004AB48 CF27010C */  jal        func_80049F3C
/* 3B34C 8004AB4C 00000000 */   nop
/* 3B350 8004AB50 A327010C */  jal        func_80049E8C
/* 3B354 8004AB54 00000000 */   nop
/* 3B358 8004AB58 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 3B35C 8004AB5C CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 3B360 8004AB60 00000000 */  nop
/* 3B364 8004AB64 2A100202 */  slt        $v0, $s0, $v0
/* 3B368 8004AB68 F1FF4014 */  bnez       $v0, .L8004AB30
/* 3B36C 8004AB6C 00000000 */   nop
.L8004AB70:
/* 3B370 8004AB70 0880103C */  lui        $s0, %hi(g_Spyro + 0xC)
/* 3B374 8004AB74 648A1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0xC)
/* 3B378 8004AB78 21200002 */  addu       $a0, $s0, $zero
/* 3B37C 8004AB7C 28001126 */  addiu      $s1, $s0, 0x28
/* 3B380 8004AB80 21282002 */  addu       $a1, $s1, $zero
/* 3B384 8004AB84 0880023C */  lui        $v0, %hi(g_Spyro + 0x124)
/* 3B388 8004AB88 7C8B428C */  lw         $v0, %lo(g_Spyro + 0x124)($v0)
/* 3B38C 8004AB8C 00000000 */  nop
/* 3B390 8004AB90 03110200 */  sra        $v0, $v0, 4
/* 3B394 8004AB94 000002A2 */  sb         $v0, 0x0($s0)
/* 3B398 8004AB98 0880023C */  lui        $v0, %hi(g_Spyro + 0x120)
/* 3B39C 8004AB9C 788B428C */  lw         $v0, %lo(g_Spyro + 0x120)($v0)
/* 3B3A0 8004ABA0 0880033C */  lui        $v1, %hi(g_Spyro + 0x11C)
/* 3B3A4 8004ABA4 748B638C */  lw         $v1, %lo(g_Spyro + 0x11C)($v1)
/* 3B3A8 8004ABA8 03110200 */  sra        $v0, $v0, 4
/* 3B3AC 8004ABAC 03190300 */  sra        $v1, $v1, 4
/* 3B3B0 8004ABB0 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 3B3B4 8004ABB4 658A22A0 */  sb         $v0, %lo(g_Spyro + 0xD)($at)
/* 3B3B8 8004ABB8 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 3B3BC 8004ABBC 668A23A0 */  sb         $v1, %lo(g_Spyro + 0xE)($at)
/* 3B3C0 8004ABC0 4B5B000C */  jal        func_80016D2C
/* 3B3C4 8004ABC4 21300000 */   addu      $a2, $zero, $zero
/* 3B3C8 8004ABC8 04000426 */  addiu      $a0, $s0, 0x4
/* 3B3CC 8004ABCC BC011026 */  addiu      $s0, $s0, 0x1BC
/* 3B3D0 8004ABD0 21280002 */  addu       $a1, $s0, $zero
/* 3B3D4 8004ABD4 4B5B000C */  jal        func_80016D2C
/* 3B3D8 8004ABD8 21300000 */   addu      $a2, $zero, $zero
/* 3B3DC 8004ABDC 21202002 */  addu       $a0, $s1, $zero
/* 3B3E0 8004ABE0 21280002 */  addu       $a1, $s0, $zero
/* 3B3E4 8004ABE4 F688010C */  jal        MulMatrix0
/* 3B3E8 8004ABE8 2130A000 */   addu      $a2, $a1, $zero
/* 3B3EC 8004ABEC 0780043C */  lui        $a0, %hi(D_800776D8)
/* 3B3F0 8004ABF0 D8768424 */  addiu      $a0, $a0, %lo(D_800776D8)
/* 3B3F4 8004ABF4 0780053C */  lui        $a1, %hi(g_Pad)
/* 3B3F8 8004ABF8 7873A524 */  addiu      $a1, $a1, %lo(g_Pad)
/* 3B3FC 8004ABFC 0880013C */  lui        $at, %hi(g_Spyro + 0x1F4)
/* 3B400 8004AC00 4C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1F4)($at)
/* 3B404 8004AC04 C24D010C */  jal        func_80053708
/* 3B408 8004AC08 00000000 */   nop
/* 3B40C 8004AC0C 5000BF8F */  lw         $ra, 0x50($sp)
/* 3B410 8004AC10 4C00B18F */  lw         $s1, 0x4C($sp)
/* 3B414 8004AC14 4800B08F */  lw         $s0, 0x48($sp)
/* 3B418 8004AC18 5800BD27 */  addiu      $sp, $sp, 0x58
/* 3B41C 8004AC1C 0800E003 */  jr         $ra
/* 3B420 8004AC20 00000000 */   nop
.size func_8004AA0C, . - func_8004AA0C
