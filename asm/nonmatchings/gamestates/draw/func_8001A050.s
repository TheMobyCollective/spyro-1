.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8001A050
/* A850 8001A050 A0FFBD27 */  addiu      $sp, $sp, -0x60
/* A854 8001A054 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* A858 8001A058 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* A85C 8001A05C 21280000 */  addu       $a1, $zero, $zero
/* A860 8001A060 0880023C */  lui        $v0, %hi(D_80078A40 + 0x10)
/* A864 8001A064 508A4290 */  lbu        $v0, %lo(D_80078A40 + 0x10)($v0)
/* A868 8001A068 0880033C */  lui        $v1, %hi(D_80078A40 + 0x11)
/* A86C 8001A06C 518A6390 */  lbu        $v1, %lo(D_80078A40 + 0x11)($v1)
/* A870 8001A070 0880073C */  lui        $a3, %hi(D_80078A40 + 0x12)
/* A874 8001A074 528AE790 */  lbu        $a3, %lo(D_80078A40 + 0x12)($a3)
/* A878 8001A078 5800BFAF */  sw         $ra, 0x58($sp)
/* A87C 8001A07C 5400B1AF */  sw         $s1, 0x54($sp)
/* A880 8001A080 5000B0AF */  sw         $s0, 0x50($sp)
/* A884 8001A084 0780013C */  lui        $at, %hi(g_DB + 0x19)
/* A888 8001A088 F96E22A0 */  sb         $v0, %lo(g_DB + 0x19)($at)
/* A88C 8001A08C 0780013C */  lui        $at, %hi(g_DB + 0x1A)
/* A890 8001A090 FA6E23A0 */  sb         $v1, %lo(g_DB + 0x1A)($at)
/* A894 8001A094 0780013C */  lui        $at, %hi(g_DB + 0x1B)
/* A898 8001A098 FB6E27A0 */  sb         $a3, %lo(g_DB + 0x1B)($at)
/* A89C 8001A09C 0780013C */  lui        $at, %hi(g_DB + 0x9D)
/* A8A0 8001A0A0 7D6F22A0 */  sb         $v0, %lo(g_DB + 0x9D)($at)
/* A8A4 8001A0A4 0780013C */  lui        $at, %hi(g_DB + 0x9E)
/* A8A8 8001A0A8 7E6F23A0 */  sb         $v1, %lo(g_DB + 0x9E)($at)
/* A8AC 8001A0AC 0780013C */  lui        $at, %hi(g_DB + 0x9F)
/* A8B0 8001A0B0 7F6F27A0 */  sb         $a3, %lo(g_DB + 0x9F)($at)
/* A8B4 8001A0B4 455A000C */  jal        Memset
/* A8B8 8001A0B8 00090624 */   addiu     $a2, $zero, 0x900
/* A8BC 8001A0BC 0780023C */  lui        $v0, %hi(D_800756B0)
/* A8C0 8001A0C0 B056428C */  lw         $v0, %lo(D_800756B0)($v0)
/* A8C4 8001A0C4 00000000 */  nop
/* A8C8 8001A0C8 03004010 */  beqz       $v0, .L8001A0D8
/* A8CC 8001A0CC 00000000 */   nop
/* A8D0 8001A0D0 CF65000C */  jal        func_8001973C
/* A8D4 8001A0D4 00000000 */   nop
.L8001A0D8:
/* A8D8 8001A0D8 B18E000C */  jal        func_80023AC4
/* A8DC 8001A0DC 00000000 */   nop
/* A8E0 8001A0E0 0880023C */  lui        $v0, %hi(D_80078A40)
/* A8E4 8001A0E4 408A428C */  lw         $v0, %lo(D_80078A40)($v0)
/* A8E8 8001A0E8 00000000 */  nop
/* A8EC 8001A0EC 91004010 */  beqz       $v0, .L8001A334
/* A8F0 8001A0F0 00000000 */   nop
/* A8F4 8001A0F4 0780023C */  lui        $v0, %hi(D_80075910)
/* A8F8 8001A0F8 1059428C */  lw         $v0, %lo(D_80075910)($v0)
/* A8FC 8001A0FC 00000000 */  nop
/* A900 8001A100 FEFF4224 */  addiu      $v0, $v0, -0x2
/* A904 8001A104 0780013C */  lui        $at, %hi(D_80075910)
/* A908 8001A108 105922AC */  sw         $v0, %lo(D_80075910)($at)
/* A90C 8001A10C 03004104 */  bgez       $v0, .L8001A11C
/* A910 8001A110 00000000 */   nop
/* A914 8001A114 0780013C */  lui        $at, %hi(D_80075910)
/* A918 8001A118 105920AC */  sw         $zero, %lo(D_80075910)($at)
.L8001A11C:
/* A91C 8001A11C 0780023C */  lui        $v0, %hi(D_80075910)
/* A920 8001A120 1059428C */  lw         $v0, %lo(D_80075910)($v0)
/* A924 8001A124 00000000 */  nop
/* A928 8001A128 7C004010 */  beqz       $v0, .L8001A31C
/* A92C 8001A12C 21280000 */   addu      $a1, $zero, $zero
/* A930 8001A130 1000A427 */  addiu      $a0, $sp, 0x10
/* A934 8001A134 455A000C */  jal        Memset
/* A938 8001A138 20000624 */   addiu     $a2, $zero, 0x20
/* A93C 8001A13C 7E89010C */  jal        SetTransMatrix
/* A940 8001A140 1000A427 */   addiu     $a0, $sp, 0x10
/* A944 8001A144 0780103C */  lui        $s0, %hi(g_Camera + 0x4E)
/* A948 8001A148 1E6E1026 */  addiu      $s0, $s0, %lo(g_Camera + 0x4E)
/* A94C 8001A14C 00000286 */  lh         $v0, 0x0($s0)
/* A950 8001A150 0780043C */  lui        $a0, %hi(D_80075910)
/* A954 8001A154 1059848C */  lw         $a0, %lo(D_80075910)($a0)
/* A958 8001A158 00101124 */  addiu      $s1, $zero, 0x1000
/* A95C 8001A15C 1000B1A7 */  sh         $s1, 0x10($sp)
/* A960 8001A160 2C5B000C */  jal        func_80016CB0
/* A964 8001A164 23204400 */   subu      $a0, $v0, $a0
/* A968 8001A168 00000386 */  lh         $v1, 0x0($s0)
/* A96C 8001A16C 0780043C */  lui        $a0, %hi(D_80075910)
/* A970 8001A170 1059848C */  lw         $a0, %lo(D_80075910)($a0)
/* A974 8001A174 1800A2A7 */  sh         $v0, 0x18($sp)
/* A978 8001A178 165B000C */  jal        func_80016C58
/* A97C 8001A17C 23206400 */   subu      $a0, $v1, $a0
/* A980 8001A180 00000386 */  lh         $v1, 0x0($s0)
/* A984 8001A184 0780043C */  lui        $a0, %hi(D_80075910)
/* A988 8001A188 1059848C */  lw         $a0, %lo(D_80075910)($a0)
/* A98C 8001A18C 1E00A2A7 */  sh         $v0, 0x1E($sp)
/* A990 8001A190 165B000C */  jal        func_80016C58
/* A994 8001A194 23206400 */   subu      $a0, $v1, $a0
/* A998 8001A198 00000386 */  lh         $v1, 0x0($s0)
/* A99C 8001A19C 0780043C */  lui        $a0, %hi(D_80075910)
/* A9A0 8001A1A0 1059848C */  lw         $a0, %lo(D_80075910)($a0)
/* A9A4 8001A1A4 23100200 */  negu       $v0, $v0
/* A9A8 8001A1A8 1A00A2A7 */  sh         $v0, 0x1A($sp)
/* A9AC 8001A1AC 2C5B000C */  jal        func_80016CB0
/* A9B0 8001A1B0 23206400 */   subu      $a0, $v1, $a0
/* A9B4 8001A1B4 3000B027 */  addiu      $s0, $sp, 0x30
/* A9B8 8001A1B8 21200002 */  addu       $a0, $s0, $zero
/* A9BC 8001A1BC 21280000 */  addu       $a1, $zero, $zero
/* A9C0 8001A1C0 20000624 */  addiu      $a2, $zero, 0x20
/* A9C4 8001A1C4 455A000C */  jal        Memset
/* A9C8 8001A1C8 2000A2A7 */   sh        $v0, 0x20($sp)
/* A9CC 8001A1CC 0780043C */  lui        $a0, %hi(g_Camera + 0x50)
/* A9D0 8001A1D0 206E8484 */  lh         $a0, %lo(g_Camera + 0x50)($a0)
/* A9D4 8001A1D4 2C5B000C */  jal        func_80016CB0
/* A9D8 8001A1D8 00000000 */   nop
/* A9DC 8001A1DC 0780043C */  lui        $a0, %hi(g_Camera + 0x50)
/* A9E0 8001A1E0 206E8484 */  lh         $a0, %lo(g_Camera + 0x50)($a0)
/* A9E4 8001A1E4 165B000C */  jal        func_80016C58
/* A9E8 8001A1E8 3000A2A7 */   sh        $v0, 0x30($sp)
/* A9EC 8001A1EC 0780043C */  lui        $a0, %hi(g_Camera + 0x50)
/* A9F0 8001A1F0 206E8484 */  lh         $a0, %lo(g_Camera + 0x50)($a0)
/* A9F4 8001A1F4 23100200 */  negu       $v0, $v0
/* A9F8 8001A1F8 3C00A2A7 */  sh         $v0, 0x3C($sp)
/* A9FC 8001A1FC 165B000C */  jal        func_80016C58
/* AA00 8001A200 3800B1A7 */   sh        $s1, 0x38($sp)
/* AA04 8001A204 0780043C */  lui        $a0, %hi(g_Camera + 0x50)
/* AA08 8001A208 206E8484 */  lh         $a0, %lo(g_Camera + 0x50)($a0)
/* AA0C 8001A20C 2C5B000C */  jal        func_80016CB0
/* AA10 8001A210 3400A2A7 */   sh        $v0, 0x34($sp)
/* AA14 8001A214 1000A427 */  addiu      $a0, $sp, 0x10
/* AA18 8001A218 21280002 */  addu       $a1, $s0, $zero
/* AA1C 8001A21C 3A89010C */  jal        MulMatrix
/* AA20 8001A220 4000A2A7 */   sh        $v0, 0x40($sp)
/* AA24 8001A224 21200002 */  addu       $a0, $s0, $zero
/* AA28 8001A228 21280000 */  addu       $a1, $zero, $zero
/* AA2C 8001A22C 455A000C */  jal        Memset
/* AA30 8001A230 20000624 */   addiu     $a2, $zero, 0x20
/* AA34 8001A234 0780043C */  lui        $a0, %hi(g_Camera + 0x4C)
/* AA38 8001A238 1C6E8484 */  lh         $a0, %lo(g_Camera + 0x4C)($a0)
/* AA3C 8001A23C 2C5B000C */  jal        func_80016CB0
/* AA40 8001A240 00000000 */   nop
/* AA44 8001A244 0780043C */  lui        $a0, %hi(g_Camera + 0x4C)
/* AA48 8001A248 1C6E8484 */  lh         $a0, %lo(g_Camera + 0x4C)($a0)
/* AA4C 8001A24C 165B000C */  jal        func_80016C58
/* AA50 8001A250 3000A2A7 */   sh        $v0, 0x30($sp)
/* AA54 8001A254 0780043C */  lui        $a0, %hi(g_Camera + 0x4C)
/* AA58 8001A258 1C6E8484 */  lh         $a0, %lo(g_Camera + 0x4C)($a0)
/* AA5C 8001A25C 23100200 */  negu       $v0, $v0
/* AA60 8001A260 165B000C */  jal        func_80016C58
/* AA64 8001A264 3600A2A7 */   sh        $v0, 0x36($sp)
/* AA68 8001A268 0780043C */  lui        $a0, %hi(g_Camera + 0x4C)
/* AA6C 8001A26C 1C6E8484 */  lh         $a0, %lo(g_Camera + 0x4C)($a0)
/* AA70 8001A270 2C5B000C */  jal        func_80016CB0
/* AA74 8001A274 3200A2A7 */   sh        $v0, 0x32($sp)
/* AA78 8001A278 1000A427 */  addiu      $a0, $sp, 0x10
/* AA7C 8001A27C 21280002 */  addu       $a1, $s0, $zero
/* AA80 8001A280 3800A2A7 */  sh         $v0, 0x38($sp)
/* AA84 8001A284 3A89010C */  jal        MulMatrix
/* AA88 8001A288 4000B1A7 */   sh        $s1, 0x40($sp)
/* AA8C 8001A28C 21200002 */  addu       $a0, $s0, $zero
/* AA90 8001A290 1000A527 */  addiu      $a1, $sp, 0x10
/* AA94 8001A294 565A000C */  jal        Memcpy
/* AA98 8001A298 14000624 */   addiu     $a2, $zero, 0x14
/* AA9C 8001A29C 1600A387 */  lh         $v1, 0x16($sp)
/* AAA0 8001A2A0 00000000 */  nop
/* AAA4 8001A2A4 80100300 */  sll        $v0, $v1, 2
/* AAA8 8001A2A8 21104300 */  addu       $v0, $v0, $v1
/* AAAC 8001A2AC 80110200 */  sll        $v0, $v0, 6
/* AAB0 8001A2B0 02004104 */  bgez       $v0, .L8001A2BC
/* AAB4 8001A2B4 00000000 */   nop
/* AAB8 8001A2B8 FF014224 */  addiu      $v0, $v0, 0x1FF
.L8001A2BC:
/* AABC 8001A2BC 1800A387 */  lh         $v1, 0x18($sp)
/* AAC0 8001A2C0 43120200 */  sra        $v0, $v0, 9
/* AAC4 8001A2C4 3600A2A7 */  sh         $v0, 0x36($sp)
/* AAC8 8001A2C8 80100300 */  sll        $v0, $v1, 2
/* AACC 8001A2CC 21104300 */  addu       $v0, $v0, $v1
/* AAD0 8001A2D0 80110200 */  sll        $v0, $v0, 6
/* AAD4 8001A2D4 02004104 */  bgez       $v0, .L8001A2E0
/* AAD8 8001A2D8 00000000 */   nop
/* AADC 8001A2DC FF014224 */  addiu      $v0, $v0, 0x1FF
.L8001A2E0:
/* AAE0 8001A2E0 1A00A387 */  lh         $v1, 0x1A($sp)
/* AAE4 8001A2E4 43120200 */  sra        $v0, $v0, 9
/* AAE8 8001A2E8 3800A2A7 */  sh         $v0, 0x38($sp)
/* AAEC 8001A2EC 80100300 */  sll        $v0, $v1, 2
/* AAF0 8001A2F0 21104300 */  addu       $v0, $v0, $v1
/* AAF4 8001A2F4 80110200 */  sll        $v0, $v0, 6
/* AAF8 8001A2F8 02004104 */  bgez       $v0, .L8001A304
/* AAFC 8001A2FC 00000000 */   nop
/* AB00 8001A300 FF014224 */  addiu      $v0, $v0, 0x1FF
.L8001A304:
/* AB04 8001A304 43120200 */  sra        $v0, $v0, 9
/* AB08 8001A308 3A00A2A7 */  sh         $v0, 0x3A($sp)
/* AB0C 8001A30C FFFF0424 */  addiu      $a0, $zero, -0x1
/* AB10 8001A310 1000A527 */  addiu      $a1, $sp, 0x10
/* AB14 8001A314 CB680008 */  j          .L8001A32C
/* AB18 8001A318 21300002 */   addu      $a2, $s0, $zero
.L8001A31C:
/* AB1C 8001A31C FFFF0424 */  addiu      $a0, $zero, -0x1
/* AB20 8001A320 0780053C */  lui        $a1, %hi(g_Camera + 0x14)
/* AB24 8001A324 E46DA524 */  addiu      $a1, $a1, %lo(g_Camera + 0x14)
/* AB28 8001A328 ECFFA624 */  addiu      $a2, $a1, -0x14
.L8001A32C:
/* AB2C 8001A32C EA3A010C */  jal        func_8004EBA8
/* AB30 8001A330 00000000 */   nop
.L8001A334:
/* AB34 8001A334 D97D010C */  jal        DrawSync
/* AB38 8001A338 21200000 */   addu      $a0, $zero, $zero
/* AB3C 8001A33C 0780023C */  lui        $v0, %hi(D_80075784)
/* AB40 8001A340 8457428C */  lw         $v0, %lo(D_80075784)($v0)
/* AB44 8001A344 00000000 */  nop
/* AB48 8001A348 03004010 */  beqz       $v0, .L8001A358
/* AB4C 8001A34C 00000000 */   nop
/* AB50 8001A350 F176010C */  jal        VSync
/* AB54 8001A354 21200000 */   addu      $a0, $zero, $zero
.L8001A358:
/* AB58 8001A358 F176010C */  jal        VSync
/* AB5C 8001A35C FFFF0424 */   addiu     $a0, $zero, -0x1
/* AB60 8001A360 0780033C */  lui        $v1, %hi(D_80075950)
/* AB64 8001A364 5059638C */  lw         $v1, %lo(D_80075950)($v1)
/* AB68 8001A368 0780013C */  lui        $at, %hi(D_80075954)
/* AB6C 8001A36C 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* AB70 8001A370 23104300 */  subu       $v0, $v0, $v1
/* AB74 8001A374 02004228 */  slti       $v0, $v0, 0x2
/* AB78 8001A378 0E004010 */  beqz       $v0, .L8001A3B4
/* AB7C 8001A37C 00000000 */   nop
/* AB80 8001A380 0780103C */  lui        $s0, %hi(D_80075954)
/* AB84 8001A384 54591026 */  addiu      $s0, $s0, %lo(D_80075954)
.L8001A388:
/* AB88 8001A388 F176010C */  jal        VSync
/* AB8C 8001A38C 21200000 */   addu      $a0, $zero, $zero
/* AB90 8001A390 F176010C */  jal        VSync
/* AB94 8001A394 FFFF0424 */   addiu     $a0, $zero, -0x1
/* AB98 8001A398 FCFF038E */  lw         $v1, -0x4($s0)
/* AB9C 8001A39C 0780013C */  lui        $at, %hi(D_80075954)
/* ABA0 8001A3A0 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* ABA4 8001A3A4 23104300 */  subu       $v0, $v0, $v1
/* ABA8 8001A3A8 02004228 */  slti       $v0, $v0, 0x2
/* ABAC 8001A3AC F6FF4014 */  bnez       $v0, .L8001A388
/* ABB0 8001A3B0 00000000 */   nop
.L8001A3B4:
/* ABB4 8001A3B4 F176010C */  jal        VSync
/* ABB8 8001A3B8 FFFF0424 */   addiu     $a0, $zero, -0x1
/* ABBC 8001A3BC 0780043C */  lui        $a0, %hi(D_80075888)
/* ABC0 8001A3C0 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* ABC4 8001A3C4 0780013C */  lui        $at, %hi(D_80075950)
/* ABC8 8001A3C8 505922AC */  sw         $v0, %lo(D_80075950)($at)
/* ABCC 8001A3CC 0C80010C */  jal        PutDispEnv
/* ABD0 8001A3D0 5C008424 */   addiu     $a0, $a0, 0x5C
/* ABD4 8001A3D4 0780043C */  lui        $a0, %hi(D_80075888)
/* ABD8 8001A3D8 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* ABDC 8001A3DC 767F010C */  jal        PutDrawEnv
/* ABE0 8001A3E0 00000000 */   nop
/* ABE4 8001A3E4 E159000C */  jal        func_80016784
/* ABE8 8001A3E8 00080424 */   addiu     $a0, $zero, 0x800
/* ABEC 8001A3EC 597F010C */  jal        DrawOTag
/* ABF0 8001A3F0 21204000 */   addu      $a0, $v0, $zero
/* ABF4 8001A3F4 5800BF8F */  lw         $ra, 0x58($sp)
/* ABF8 8001A3F8 5400B18F */  lw         $s1, 0x54($sp)
/* ABFC 8001A3FC 5000B08F */  lw         $s0, 0x50($sp)
/* AC00 8001A400 6000BD27 */  addiu      $sp, $sp, 0x60
/* AC04 8001A404 0800E003 */  jr         $ra
/* AC08 8001A408 00000000 */   nop
.size func_8001A050, . - func_8001A050
