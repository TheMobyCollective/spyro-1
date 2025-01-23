.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8001EB80
/* F380 8001EB80 C0FFBD27 */  addiu      $sp, $sp, -0x40
/* F384 8001EB84 0180043C */  lui        $a0, %hi(D_80010ACC)
/* F388 8001EB88 CC0A8424 */  addiu      $a0, $a0, %lo(D_80010ACC)
/* F38C 8001EB8C 2800A527 */  addiu      $a1, $sp, 0x28
/* F390 8001EB90 1800A627 */  addiu      $a2, $sp, 0x18
/* F394 8001EB94 10000224 */  addiu      $v0, $zero, 0x10
/* F398 8001EB98 1800A2AF */  sw         $v0, 0x18($sp)
/* F39C 8001EB9C 01000224 */  addiu      $v0, $zero, 0x1
/* F3A0 8001EBA0 1C00A2AF */  sw         $v0, 0x1C($sp)
/* F3A4 8001EBA4 00140224 */  addiu      $v0, $zero, 0x1400
/* F3A8 8001EBA8 2000A2AF */  sw         $v0, 0x20($sp)
/* F3AC 8001EBAC 76000224 */  addiu      $v0, $zero, 0x76
/* F3B0 8001EBB0 2800A2AF */  sw         $v0, 0x28($sp)
/* F3B4 8001EBB4 6E000224 */  addiu      $v0, $zero, 0x6E
/* F3B8 8001EBB8 2C00A2AF */  sw         $v0, 0x2C($sp)
/* F3BC 8001EBBC 00110224 */  addiu      $v0, $zero, 0x1100
/* F3C0 8001EBC0 3000A2AF */  sw         $v0, 0x30($sp)
/* F3C4 8001EBC4 0B000224 */  addiu      $v0, $zero, 0xB
/* F3C8 8001EBC8 3800B0AF */  sw         $s0, 0x38($sp)
/* F3CC 8001EBCC 0780103C */  lui        $s0, %hi(D_80075710)
/* F3D0 8001EBD0 1057108E */  lw         $s0, %lo(D_80075710)($s0)
/* F3D4 8001EBD4 12000724 */  addiu      $a3, $zero, 0x12
/* F3D8 8001EBD8 3C00BFAF */  sw         $ra, 0x3C($sp)
/* F3DC 8001EBDC 0780013C */  lui        $at, %hi(g_DB + 0x19)
/* F3E0 8001EBE0 F96E20A0 */  sb         $zero, %lo(g_DB + 0x19)($at)
/* F3E4 8001EBE4 0780013C */  lui        $at, %hi(g_DB + 0x1A)
/* F3E8 8001EBE8 FA6E20A0 */  sb         $zero, %lo(g_DB + 0x1A)($at)
/* F3EC 8001EBEC 0780013C */  lui        $at, %hi(g_DB + 0x1B)
/* F3F0 8001EBF0 FB6E20A0 */  sb         $zero, %lo(g_DB + 0x1B)($at)
/* F3F4 8001EBF4 0780013C */  lui        $at, %hi(g_DB + 0x9D)
/* F3F8 8001EBF8 7D6F20A0 */  sb         $zero, %lo(g_DB + 0x9D)($at)
/* F3FC 8001EBFC 0780013C */  lui        $at, %hi(g_DB + 0x9E)
/* F400 8001EC00 7E6F20A0 */  sb         $zero, %lo(g_DB + 0x9E)($at)
/* F404 8001EC04 0780013C */  lui        $at, %hi(g_DB + 0x9F)
/* F408 8001EC08 7F6F20A0 */  sb         $zero, %lo(g_DB + 0x9F)($at)
/* F40C 8001EC0C 6B60000C */  jal        func_800181AC
/* F410 8001EC10 1000A2AF */   sw        $v0, 0x10($sp)
/* F414 8001EC14 0780023C */  lui        $v0, %hi(D_80075710)
/* F418 8001EC18 1057428C */  lw         $v0, %lo(D_80075710)($v0)
/* F41C 8001EC1C A8FF1026 */  addiu      $s0, $s0, -0x58
/* F420 8001EC20 2A100202 */  slt        $v0, $s0, $v0
/* F424 8001EC24 15004014 */  bnez       $v0, .L8001EC7C
/* F428 8001EC28 21180000 */   addu      $v1, $zero, $zero
/* F42C 8001EC2C 0780043C */  lui        $a0, %hi(D_8006CC78)
/* F430 8001EC30 78CC8424 */  addiu      $a0, $a0, %lo(D_8006CC78)
.L8001EC34:
/* F434 8001EC34 0780023C */  lui        $v0, %hi(D_800756F8)
/* F438 8001EC38 F856428C */  lw         $v0, %lo(D_800756F8)($v0)
/* F43C 8001EC3C 00000000 */  nop
/* F440 8001EC40 40100200 */  sll        $v0, $v0, 1
/* F444 8001EC44 21104300 */  addu       $v0, $v0, $v1
/* F448 8001EC48 FF004230 */  andi       $v0, $v0, 0xFF
/* F44C 8001EC4C 40100200 */  sll        $v0, $v0, 1
/* F450 8001EC50 21104400 */  addu       $v0, $v0, $a0
/* F454 8001EC54 00004294 */  lhu        $v0, 0x0($v0)
/* F458 8001EC58 00000000 */  nop
/* F45C 8001EC5C C2110200 */  srl        $v0, $v0, 7
/* F460 8001EC60 460002A2 */  sb         $v0, 0x46($s0)
/* F464 8001EC64 0780023C */  lui        $v0, %hi(D_80075710)
/* F468 8001EC68 1057428C */  lw         $v0, %lo(D_80075710)($v0)
/* F46C 8001EC6C A8FF1026 */  addiu      $s0, $s0, -0x58
/* F470 8001EC70 2A100202 */  slt        $v0, $s0, $v0
/* F474 8001EC74 EFFF4010 */  beqz       $v0, .L8001EC34
/* F478 8001EC78 0C006324 */   addiu     $v1, $v1, 0xC
.L8001EC7C:
/* F47C 8001EC7C 0780103C */  lui        $s0, %hi(D_8006FCF4 + 0x2400)
/* F480 8001EC80 F4201026 */  addiu      $s0, $s0, %lo(D_8006FCF4 + 0x2400)
/* F484 8001EC84 2062000C */  jal        func_80018880
/* F488 8001EC88 000000AE */   sw        $zero, 0x0($s0)
/* F48C 8001EC8C 00DC0426 */  addiu      $a0, $s0, -0x2400
/* F490 8001EC90 21280000 */  addu       $a1, $zero, $zero
/* F494 8001EC94 455A000C */  jal        Memset
/* F498 8001EC98 00090624 */   addiu     $a2, $zero, 0x900
/* F49C 8001EC9C 8B8A000C */  jal        func_80022A2C
/* F4A0 8001ECA0 00000000 */   nop
/* F4A4 8001ECA4 D97D010C */  jal        DrawSync
/* F4A8 8001ECA8 21200000 */   addu      $a0, $zero, $zero
/* F4AC 8001ECAC F176010C */  jal        VSync
/* F4B0 8001ECB0 FFFF0424 */   addiu     $a0, $zero, -0x1
/* F4B4 8001ECB4 0780033C */  lui        $v1, %hi(D_80075950)
/* F4B8 8001ECB8 5059638C */  lw         $v1, %lo(D_80075950)($v1)
/* F4BC 8001ECBC 0780013C */  lui        $at, %hi(D_80075954)
/* F4C0 8001ECC0 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* F4C4 8001ECC4 23104300 */  subu       $v0, $v0, $v1
/* F4C8 8001ECC8 02004228 */  slti       $v0, $v0, 0x2
/* F4CC 8001ECCC 0E004010 */  beqz       $v0, .L8001ED08
/* F4D0 8001ECD0 00000000 */   nop
/* F4D4 8001ECD4 0780103C */  lui        $s0, %hi(D_80075954)
/* F4D8 8001ECD8 54591026 */  addiu      $s0, $s0, %lo(D_80075954)
.L8001ECDC:
/* F4DC 8001ECDC F176010C */  jal        VSync
/* F4E0 8001ECE0 21200000 */   addu      $a0, $zero, $zero
/* F4E4 8001ECE4 F176010C */  jal        VSync
/* F4E8 8001ECE8 FFFF0424 */   addiu     $a0, $zero, -0x1
/* F4EC 8001ECEC FCFF038E */  lw         $v1, -0x4($s0)
/* F4F0 8001ECF0 0780013C */  lui        $at, %hi(D_80075954)
/* F4F4 8001ECF4 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* F4F8 8001ECF8 23104300 */  subu       $v0, $v0, $v1
/* F4FC 8001ECFC 02004228 */  slti       $v0, $v0, 0x2
/* F500 8001ED00 F6FF4014 */  bnez       $v0, .L8001ECDC
/* F504 8001ED04 00000000 */   nop
.L8001ED08:
/* F508 8001ED08 F176010C */  jal        VSync
/* F50C 8001ED0C FFFF0424 */   addiu     $a0, $zero, -0x1
/* F510 8001ED10 0780043C */  lui        $a0, %hi(D_80075888)
/* F514 8001ED14 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* F518 8001ED18 0780013C */  lui        $at, %hi(D_80075950)
/* F51C 8001ED1C 505922AC */  sw         $v0, %lo(D_80075950)($at)
/* F520 8001ED20 0C80010C */  jal        PutDispEnv
/* F524 8001ED24 5C008424 */   addiu     $a0, $a0, 0x5C
/* F528 8001ED28 0780043C */  lui        $a0, %hi(D_80075888)
/* F52C 8001ED2C 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* F530 8001ED30 767F010C */  jal        PutDrawEnv
/* F534 8001ED34 00000000 */   nop
/* F538 8001ED38 E159000C */  jal        func_80016784
/* F53C 8001ED3C 00080424 */   addiu     $a0, $zero, 0x800
/* F540 8001ED40 597F010C */  jal        DrawOTag
/* F544 8001ED44 21204000 */   addu      $a0, $v0, $zero
/* F548 8001ED48 3C00BF8F */  lw         $ra, 0x3C($sp)
/* F54C 8001ED4C 3800B08F */  lw         $s0, 0x38($sp)
/* F550 8001ED50 4000BD27 */  addiu      $sp, $sp, 0x40
/* F554 8001ED54 0800E003 */  jr         $ra
/* F558 8001ED58 00000000 */   nop
.size func_8001EB80, . - func_8001EB80
