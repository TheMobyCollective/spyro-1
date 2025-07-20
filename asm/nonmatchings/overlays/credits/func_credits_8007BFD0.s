.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_credits_8007BFD0
/* 5C98D98 8007BFD0 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 5C98D9C 8007BFD4 0780033C */  lui        $v1, %hi(D_80075704)
/* 5C98DA0 8007BFD8 0457638C */  lw         $v1, %lo(D_80075704)($v1)
/* 5C98DA4 8007BFDC FFFF0224 */  addiu      $v0, $zero, -0x1
/* 5C98DA8 8007BFE0 2C00BFAF */  sw         $ra, 0x2C($sp)
/* 5C98DAC 8007BFE4 2800B2AF */  sw         $s2, 0x28($sp)
/* 5C98DB0 8007BFE8 2400B1AF */  sw         $s1, 0x24($sp)
/* 5C98DB4 8007BFEC 1B006214 */  bne        $v1, $v0, .Lcredits_8007C05C
/* 5C98DB8 8007BFF0 2000B0AF */   sw        $s0, 0x20($sp)
/* 5C98DBC 8007BFF4 D97D010C */  jal        DrawSync
/* 5C98DC0 8007BFF8 21200000 */   addu      $a0, $zero, $zero
/* 5C98DC4 8007BFFC F176010C */  jal        VSync
/* 5C98DC8 8007C000 21200000 */   addu      $a0, $zero, $zero
/* 5C98DCC 8007C004 08000724 */  addiu      $a3, $zero, 0x8
/* 5C98DD0 8007C008 0780033C */  lui        $v1, %hi(g_CurDB)
/* 5C98DD4 8007C00C 8858638C */  lw         $v1, %lo(g_CurDB)($v1)
/* 5C98DD8 8007C010 0780023C */  lui        $v0, %hi(g_DB)
/* 5C98DDC 8007C014 E06E4224 */  addiu      $v0, $v0, %lo(g_DB)
/* 5C98DE0 8007C018 02006210 */  beq        $v1, $v0, .Lcredits_8007C024
/* 5C98DE4 8007C01C 1000A0A7 */   sh        $zero, 0x10($sp)
/* 5C98DE8 8007C020 F8000724 */  addiu      $a3, $zero, 0xF8
.Lcredits_8007C024:
/* 5C98DEC 8007C024 1000A427 */  addiu      $a0, $sp, 0x10
/* 5C98DF0 8007C028 21280000 */  addu       $a1, $zero, $zero
/* 5C98DF4 8007C02C 00010624 */  addiu      $a2, $zero, 0x100
/* 5C98DF8 8007C030 2330C700 */  subu       $a2, $a2, $a3
/* 5C98DFC 8007C034 00020224 */  addiu      $v0, $zero, 0x200
/* 5C98E00 8007C038 1400A2A7 */  sh         $v0, 0x14($sp)
/* 5C98E04 8007C03C E0000224 */  addiu      $v0, $zero, 0xE0
/* 5C98E08 8007C040 1200A7A7 */  sh         $a3, 0x12($sp)
/* 5C98E0C 8007C044 BC7E010C */  jal        MoveImage
/* 5C98E10 8007C048 1600A2A7 */   sh        $v0, 0x16($sp)
/* 5C98E14 8007C04C D97D010C */  jal        DrawSync
/* 5C98E18 8007C050 21200000 */   addu      $a0, $zero, $zero
/* 5C98E1C 8007C054 C7F00108 */  j          .Lcredits_8007C31C
/* 5C98E20 8007C058 00000000 */   nop
.Lcredits_8007C05C:
/* 5C98E24 8007C05C 0880023C */  lui        $v0, %hi(g_Cyclorama + 0x10)
/* 5C98E28 8007C060 508A4290 */  lbu        $v0, %lo(g_Cyclorama + 0x10)($v0)
/* 5C98E2C 8007C064 0880033C */  lui        $v1, %hi(g_Cyclorama + 0x11)
/* 5C98E30 8007C068 518A6390 */  lbu        $v1, %lo(g_Cyclorama + 0x11)($v1)
/* 5C98E34 8007C06C 0880043C */  lui        $a0, %hi(g_Cyclorama + 0x12)
/* 5C98E38 8007C070 528A8490 */  lbu        $a0, %lo(g_Cyclorama + 0x12)($a0)
/* 5C98E3C 8007C074 0780053C */  lui        $a1, %hi(D_800756E4)
/* 5C98E40 8007C078 E456A58C */  lw         $a1, %lo(D_800756E4)($a1)
/* 5C98E44 8007C07C 0780013C */  lui        $at, %hi(g_DB + 0x19)
/* 5C98E48 8007C080 F96E22A0 */  sb         $v0, %lo(g_DB + 0x19)($at)
/* 5C98E4C 8007C084 0780013C */  lui        $at, %hi(g_DB + 0x1A)
/* 5C98E50 8007C088 FA6E23A0 */  sb         $v1, %lo(g_DB + 0x1A)($at)
/* 5C98E54 8007C08C 0780013C */  lui        $at, %hi(g_DB + 0x1B)
/* 5C98E58 8007C090 FB6E24A0 */  sb         $a0, %lo(g_DB + 0x1B)($at)
/* 5C98E5C 8007C094 0780013C */  lui        $at, %hi(g_DB + 0x9D)
/* 5C98E60 8007C098 7D6F22A0 */  sb         $v0, %lo(g_DB + 0x9D)($at)
/* 5C98E64 8007C09C 0780013C */  lui        $at, %hi(g_DB + 0x9E)
/* 5C98E68 8007C0A0 7E6F23A0 */  sb         $v1, %lo(g_DB + 0x9E)($at)
/* 5C98E6C 8007C0A4 0780013C */  lui        $at, %hi(g_DB + 0x9F)
/* 5C98E70 8007C0A8 7F6F24A0 */  sb         $a0, %lo(g_DB + 0x9F)($at)
/* 5C98E74 8007C0AC 4900A018 */  blez       $a1, .Lcredits_8007C1D4
/* 5C98E78 8007C0B0 21880000 */   addu      $s1, $zero, $zero
/* 5C98E7C 8007C0B4 21900000 */  addu       $s2, $zero, $zero
.Lcredits_8007C0B8:
/* 5C98E80 8007C0B8 21280000 */  addu       $a1, $zero, $zero
/* 5C98E84 8007C0BC 58000624 */  addiu      $a2, $zero, 0x58
/* 5C98E88 8007C0C0 0780043C */  lui        $a0, %hi(g_HudMobys)
/* 5C98E8C 8007C0C4 1057848C */  lw         $a0, %lo(g_HudMobys)($a0)
/* 5C98E90 8007C0C8 0780023C */  lui        $v0, %hi(D_8007589C)
/* 5C98E94 8007C0CC 9C58428C */  lw         $v0, %lo(D_8007589C)($v0)
/* 5C98E98 8007C0D0 A8FF8424 */  addiu      $a0, $a0, -0x58
/* 5C98E9C 8007C0D4 0780013C */  lui        $at, %hi(g_HudMobys)
/* 5C98EA0 8007C0D8 105724AC */  sw         $a0, %lo(g_HudMobys)($at)
/* 5C98EA4 8007C0DC 455A000C */  jal        Memset
/* 5C98EA8 8007C0E0 21805200 */   addu      $s0, $v0, $s2
/* 5C98EAC 8007C0E4 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 5C98EB0 8007C0E8 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 5C98EB4 8007C0EC 12000286 */  lh         $v0, 0x12($s0)
/* 5C98EB8 8007C0F0 00000000 */  nop
/* 5C98EBC 8007C0F4 0C0062AC */  sw         $v0, 0xC($v1)
/* 5C98EC0 8007C0F8 14000286 */  lh         $v0, 0x14($s0)
/* 5C98EC4 8007C0FC 00000000 */  nop
/* 5C98EC8 8007C100 100062AC */  sw         $v0, 0x10($v1)
/* 5C98ECC 8007C104 16000286 */  lh         $v0, 0x16($s0)
/* 5C98ED0 8007C108 00000000 */  nop
/* 5C98ED4 8007C10C 140062AC */  sw         $v0, 0x14($v1)
/* 5C98ED8 8007C110 05000292 */  lbu        $v0, 0x5($s0)
/* 5C98EDC 8007C114 00000000 */  nop
/* 5C98EE0 8007C118 440062A0 */  sb         $v0, 0x44($v1)
/* 5C98EE4 8007C11C 1A000386 */  lh         $v1, 0x1A($s0)
/* 5C98EE8 8007C120 15010224 */  addiu      $v0, $zero, 0x115
/* 5C98EEC 8007C124 0C006214 */  bne        $v1, $v0, .Lcredits_8007C158
/* 5C98EF0 8007C128 00000000 */   nop
/* 5C98EF4 8007C12C 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 5C98EF8 8007C130 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 5C98EFC 8007C134 00000000 */  nop
/* 5C98F00 8007C138 44006290 */  lbu        $v0, 0x44($v1)
/* 5C98F04 8007C13C 00000000 */  nop
/* 5C98F08 8007C140 29004224 */  addiu      $v0, $v0, 0x29
/* 5C98F0C 8007C144 440062A0 */  sb         $v0, 0x44($v1)
/* 5C98F10 8007C148 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 5C98F14 8007C14C 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 5C98F18 8007C150 001C0224 */  addiu      $v0, $zero, 0x1C00
/* 5C98F1C 8007C154 140062AC */  sw         $v0, 0x14($v1)
.Lcredits_8007C158:
/* 5C98F20 8007C158 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 5C98F24 8007C15C 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 5C98F28 8007C160 06000292 */  lbu        $v0, 0x6($s0)
/* 5C98F2C 8007C164 00000000 */  nop
/* 5C98F30 8007C168 450062A0 */  sb         $v0, 0x45($v1)
/* 5C98F34 8007C16C 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 5C98F38 8007C170 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 5C98F3C 8007C174 07000292 */  lbu        $v0, 0x7($s0)
/* 5C98F40 8007C178 00000000 */  nop
/* 5C98F44 8007C17C 460062A0 */  sb         $v0, 0x46($v1)
/* 5C98F48 8007C180 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 5C98F4C 8007C184 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 5C98F50 8007C188 1A000296 */  lhu        $v0, 0x1A($s0)
/* 5C98F54 8007C18C 00000000 */  nop
/* 5C98F58 8007C190 360062A4 */  sh         $v0, 0x36($v1)
/* 5C98F5C 8007C194 0B000224 */  addiu      $v0, $zero, 0xB
/* 5C98F60 8007C198 4F0062A0 */  sb         $v0, 0x4F($v1)
/* 5C98F64 8007C19C 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 5C98F68 8007C1A0 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 5C98F6C 8007C1A4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 5C98F70 8007C1A8 500062A0 */  sb         $v0, 0x50($v1)
/* 5C98F74 8007C1AC 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 5C98F78 8007C1B0 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 5C98F7C 8007C1B4 7F000224 */  addiu      $v0, $zero, 0x7F
/* 5C98F80 8007C1B8 470062A0 */  sb         $v0, 0x47($v1)
/* 5C98F84 8007C1BC 0780023C */  lui        $v0, %hi(D_800756E4)
/* 5C98F88 8007C1C0 E456428C */  lw         $v0, %lo(D_800756E4)($v0)
/* 5C98F8C 8007C1C4 01003126 */  addiu      $s1, $s1, 0x1
/* 5C98F90 8007C1C8 2A102202 */  slt        $v0, $s1, $v0
/* 5C98F94 8007C1CC BAFF4014 */  bnez       $v0, .Lcredits_8007C0B8
/* 5C98F98 8007C1D0 1C005226 */   addiu     $s2, $s2, 0x1C
.Lcredits_8007C1D4:
/* 5C98F9C 8007C1D4 0780053C */  lui        $a1, %hi(g_Fade)
/* 5C98FA0 8007C1D8 1859A58C */  lw         $a1, %lo(g_Fade)($a1)
/* 5C98FA4 8007C1DC 00000000 */  nop
/* 5C98FA8 8007C1E0 0500A010 */  beqz       $a1, .Lcredits_8007C1F8
/* 5C98FAC 8007C1E4 00290500 */   sll       $a1, $a1, 4
/* 5C98FB0 8007C1E8 02000424 */  addiu      $a0, $zero, 0x2
/* 5C98FB4 8007C1EC 2130A000 */  addu       $a2, $a1, $zero
/* 5C98FB8 8007C1F0 3564000C */  jal        func_800190D4
/* 5C98FBC 8007C1F4 2138A000 */   addu      $a3, $a1, $zero
.Lcredits_8007C1F8:
/* 5C98FC0 8007C1F8 0780103C */  lui        $s0, %hi(D_8006FCF4 + 0x2400)
/* 5C98FC4 8007C1FC F4201026 */  addiu      $s0, $s0, %lo(D_8006FCF4 + 0x2400)
/* 5C98FC8 8007C200 2062000C */  jal        func_80018880
/* 5C98FCC 8007C204 000000AE */   sw        $zero, 0x0($s0)
/* 5C98FD0 8007C208 00DC1026 */  addiu      $s0, $s0, -0x2400
/* 5C98FD4 8007C20C 21200002 */  addu       $a0, $s0, $zero
/* 5C98FD8 8007C210 21280000 */  addu       $a1, $zero, $zero
/* 5C98FDC 8007C214 455A000C */  jal        Memset
/* 5C98FE0 8007C218 00090624 */   addiu     $a2, $zero, 0x900
/* 5C98FE4 8007C21C 8B8A000C */  jal        func_80022A2C
/* 5C98FE8 8007C220 00000000 */   nop
/* 5C98FEC 8007C224 21200002 */  addu       $a0, $s0, $zero
/* 5C98FF0 8007C228 21280000 */  addu       $a1, $zero, $zero
/* 5C98FF4 8007C22C 4C5A000C */  jal        Memset16
/* 5C98FF8 8007C230 001C0624 */   addiu     $a2, $zero, 0x1C00
/* 5C98FFC 8007C234 0200023C */  lui        $v0, (0x28000 >> 16)
/* 5C99000 8007C238 00804234 */  ori        $v0, $v0, (0x28000 & 0xFFFF)
/* 5C99004 8007C23C 0880013C */  lui        $at, %hi(g_Environment + 0x28)
/* 5C99008 8007C240 D08522AC */  sw         $v0, %lo(g_Environment + 0x28)($at)
/* 5C9900C 8007C244 3C96000C */  jal        func_800258F0
/* 5C99010 8007C248 FFFF0424 */   addiu     $a0, $zero, -0x1
/* 5C99014 8007C24C FFFF0424 */  addiu      $a0, $zero, -0x1
/* 5C99018 8007C250 0780053C */  lui        $a1, %hi(g_Camera + 0x14)
/* 5C9901C 8007C254 E46DA524 */  addiu      $a1, $a1, %lo(g_Camera + 0x14)
/* 5C99020 8007C258 EA3A010C */  jal        func_8004EBA8
/* 5C99024 8007C25C ECFFA624 */   addiu     $a2, $a1, -0x14
/* 5C99028 8007C260 D97D010C */  jal        DrawSync
/* 5C9902C 8007C264 21200000 */   addu      $a0, $zero, $zero
/* 5C99030 8007C268 0780023C */  lui        $v0, %hi(D_80075784)
/* 5C99034 8007C26C 8457428C */  lw         $v0, %lo(D_80075784)($v0)
/* 5C99038 8007C270 00000000 */  nop
/* 5C9903C 8007C274 03004010 */  beqz       $v0, .Lcredits_8007C284
/* 5C99040 8007C278 00000000 */   nop
/* 5C99044 8007C27C F176010C */  jal        VSync
/* 5C99048 8007C280 21200000 */   addu      $a0, $zero, $zero
.Lcredits_8007C284:
/* 5C9904C 8007C284 F176010C */  jal        VSync
/* 5C99050 8007C288 FFFF0424 */   addiu     $a0, $zero, -0x1
/* 5C99054 8007C28C 0780033C */  lui        $v1, %hi(D_80075950)
/* 5C99058 8007C290 5059638C */  lw         $v1, %lo(D_80075950)($v1)
/* 5C9905C 8007C294 0780043C */  lui        $a0, %hi(D_80075954)
/* 5C99060 8007C298 54598424 */  addiu      $a0, $a0, %lo(D_80075954)
/* 5C99064 8007C29C 000082AC */  sw         $v0, 0x0($a0)
/* 5C99068 8007C2A0 23104300 */  subu       $v0, $v0, $v1
/* 5C9906C 8007C2A4 02004228 */  slti       $v0, $v0, 0x2
/* 5C99070 8007C2A8 0C004010 */  beqz       $v0, .Lcredits_8007C2DC
/* 5C99074 8007C2AC 00000000 */   nop
/* 5C99078 8007C2B0 21808000 */  addu       $s0, $a0, $zero
.Lcredits_8007C2B4:
/* 5C9907C 8007C2B4 F176010C */  jal        VSync
/* 5C99080 8007C2B8 21200000 */   addu      $a0, $zero, $zero
/* 5C99084 8007C2BC F176010C */  jal        VSync
/* 5C99088 8007C2C0 FFFF0424 */   addiu     $a0, $zero, -0x1
/* 5C9908C 8007C2C4 FCFF038E */  lw         $v1, -0x4($s0)
/* 5C99090 8007C2C8 000002AE */  sw         $v0, 0x0($s0)
/* 5C99094 8007C2CC 23104300 */  subu       $v0, $v0, $v1
/* 5C99098 8007C2D0 02004228 */  slti       $v0, $v0, 0x2
/* 5C9909C 8007C2D4 F7FF4014 */  bnez       $v0, .Lcredits_8007C2B4
/* 5C990A0 8007C2D8 00000000 */   nop
.Lcredits_8007C2DC:
/* 5C990A4 8007C2DC F176010C */  jal        VSync
/* 5C990A8 8007C2E0 FFFF0424 */   addiu     $a0, $zero, -0x1
/* 5C990AC 8007C2E4 0780043C */  lui        $a0, %hi(g_CurDB)
/* 5C990B0 8007C2E8 8858848C */  lw         $a0, %lo(g_CurDB)($a0)
/* 5C990B4 8007C2EC 0780013C */  lui        $at, %hi(D_80075950)
/* 5C990B8 8007C2F0 505922AC */  sw         $v0, %lo(D_80075950)($at)
/* 5C990BC 8007C2F4 0C80010C */  jal        PutDispEnv
/* 5C990C0 8007C2F8 5C008424 */   addiu     $a0, $a0, 0x5C
/* 5C990C4 8007C2FC 0780043C */  lui        $a0, %hi(g_CurDB)
/* 5C990C8 8007C300 8858848C */  lw         $a0, %lo(g_CurDB)($a0)
/* 5C990CC 8007C304 767F010C */  jal        PutDrawEnv
/* 5C990D0 8007C308 00000000 */   nop
/* 5C990D4 8007C30C E159000C */  jal        func_80016784
/* 5C990D8 8007C310 00080424 */   addiu     $a0, $zero, 0x800
/* 5C990DC 8007C314 597F010C */  jal        DrawOTag
/* 5C990E0 8007C318 21204000 */   addu      $a0, $v0, $zero
.Lcredits_8007C31C:
/* 5C990E4 8007C31C 2C00BF8F */  lw         $ra, 0x2C($sp)
/* 5C990E8 8007C320 2800B28F */  lw         $s2, 0x28($sp)
/* 5C990EC 8007C324 2400B18F */  lw         $s1, 0x24($sp)
/* 5C990F0 8007C328 2000B08F */  lw         $s0, 0x20($sp)
/* 5C990F4 8007C32C 3000BD27 */  addiu      $sp, $sp, 0x30
/* 5C990F8 8007C330 0800E003 */  jr         $ra
/* 5C990FC 8007C334 00000000 */   nop
.size func_credits_8007BFD0, . - func_credits_8007BFD0
