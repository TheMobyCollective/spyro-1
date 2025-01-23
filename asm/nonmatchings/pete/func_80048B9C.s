.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80048B9C
/* 3939C 80048B9C D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 393A0 80048BA0 0880043C */  lui        $a0, %hi(g_Spyro + 0x100)
/* 393A4 80048BA4 588B8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0x100)
/* 393A8 80048BA8 2400BFAF */  sw         $ra, 0x24($sp)
/* 393AC 80048BAC BC5D000C */  jal        VecNull
/* 393B0 80048BB0 2000B0AF */   sw        $s0, 0x20($sp)
/* 393B4 80048BB4 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 393B8 80048BB8 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 393BC 80048BBC 00000000 */  nop
/* 393C0 80048BC0 09004018 */  blez       $v0, .L80048BE8
/* 393C4 80048BC4 21800000 */   addu      $s0, $zero, $zero
.L80048BC8:
/* 393C8 80048BC8 F90F010C */  jal        func_80043FE4
/* 393CC 80048BCC 21200002 */   addu      $a0, $s0, $zero
/* 393D0 80048BD0 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 393D4 80048BD4 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 393D8 80048BD8 01001026 */  addiu      $s0, $s0, 0x1
/* 393DC 80048BDC 2A100202 */  slt        $v0, $s0, $v0
/* 393E0 80048BE0 F9FF4014 */  bnez       $v0, .L80048BC8
/* 393E4 80048BE4 00000000 */   nop
.L80048BE8:
/* 393E8 80048BE8 D81E010C */  jal        func_80047B60
/* 393EC 80048BEC 21800000 */   addu      $s0, $zero, $zero
/* 393F0 80048BF0 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 393F4 80048BF4 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 393F8 80048BF8 00000000 */  nop
/* 393FC 80048BFC 09004018 */  blez       $v0, .L80048C24
/* 39400 80048C00 00000000 */   nop
.L80048C04:
/* 39404 80048C04 2322010C */  jal        func_8004888C
/* 39408 80048C08 01001026 */   addiu     $s0, $s0, 0x1
/* 3940C 80048C0C 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 39410 80048C10 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 39414 80048C14 00000000 */  nop
/* 39418 80048C18 2A100202 */  slt        $v0, $s0, $v0
/* 3941C 80048C1C F9FF4014 */  bnez       $v0, .L80048C04
/* 39420 80048C20 00000000 */   nop
.L80048C24:
/* 39424 80048C24 0880043C */  lui        $a0, %hi(g_Spyro + 0x1F4)
/* 39428 80048C28 4C8C8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0x1F4)
/* 3942C 80048C2C 0000828C */  lw         $v0, 0x0($a0)
/* 39430 80048C30 00000000 */  nop
/* 39434 80048C34 00404230 */  andi       $v0, $v0, 0x4000
/* 39438 80048C38 30004014 */  bnez       $v0, .L80048CFC
/* 3943C 80048C3C 0CFE8424 */   addiu     $a0, $a0, -0x1F4
/* 39440 80048C40 7B35010C */  jal        func_8004D5EC
/* 39444 80048C44 0100053C */   lui       $a1, (0x10000 >> 16)
/* 39448 80048C48 0880033C */  lui        $v1, %hi(g_Spyro + 0x9C)
/* 3944C 80048C4C F48A638C */  lw         $v1, %lo(g_Spyro + 0x9C)($v1)
/* 39450 80048C50 21284000 */  addu       $a1, $v0, $zero
/* 39454 80048C54 0880013C */  lui        $at, %hi(g_Spyro + 0xA0)
/* 39458 80048C58 F88A25AC */  sw         $a1, %lo(g_Spyro + 0xA0)($at)
/* 3945C 80048C5C 0880013C */  lui        $at, %hi(g_Spyro + 0x170)
/* 39460 80048C60 C88B20AC */  sw         $zero, %lo(g_Spyro + 0x170)($at)
/* 39464 80048C64 0F006014 */  bnez       $v1, .L80048CA4
/* 39468 80048C68 00000000 */   nop
/* 3946C 80048C6C 0780023C */  lui        $v0, %hi(D_80075718)
/* 39470 80048C70 1857428C */  lw         $v0, %lo(D_80075718)($v0)
/* 39474 80048C74 00000000 */  nop
/* 39478 80048C78 3F004430 */  andi       $a0, $v0, 0x3F
/* 3947C 80048C7C 3F000224 */  addiu      $v0, $zero, 0x3F
/* 39480 80048C80 08008210 */  beq        $a0, $v0, .L80048CA4
/* 39484 80048C84 00000000 */   nop
/* 39488 80048C88 0880023C */  lui        $v0, %hi(g_Spyro + 0x8)
/* 3948C 80048C8C 608A428C */  lw         $v0, %lo(g_Spyro + 0x8)($v0)
/* 39490 80048C90 00000000 */  nop
/* 39494 80048C94 23104500 */  subu       $v0, $v0, $a1
/* 39498 80048C98 01024228 */  slti       $v0, $v0, 0x201
/* 3949C 80048C9C 15004014 */  bnez       $v0, .L80048CF4
/* 394A0 80048CA0 02000524 */   addiu     $a1, $zero, 0x2
.L80048CA4:
/* 394A4 80048CA4 0880023C */  lui        $v0, %hi(g_Spyro + 0x16C)
/* 394A8 80048CA8 C48B428C */  lw         $v0, %lo(g_Spyro + 0x16C)($v0)
/* 394AC 80048CAC 00000000 */  nop
/* 394B0 80048CB0 3F004330 */  andi       $v1, $v0, 0x3F
/* 394B4 80048CB4 3F000224 */  addiu      $v0, $zero, 0x3F
/* 394B8 80048CB8 03006210 */  beq        $v1, $v0, .L80048CC8
/* 394BC 80048CBC 21206000 */   addu      $a0, $v1, $zero
/* 394C0 80048CC0 3D230108 */  j          .L80048CF4
/* 394C4 80048CC4 21280000 */   addu      $a1, $zero, $zero
.L80048CC8:
/* 394C8 80048CC8 0880023C */  lui        $v0, %hi(g_Spyro + 0xA0)
/* 394CC 80048CCC F88A428C */  lw         $v0, %lo(g_Spyro + 0xA0)($v0)
/* 394D0 80048CD0 00000000 */  nop
/* 394D4 80048CD4 09004018 */  blez       $v0, .L80048CFC
/* 394D8 80048CD8 00000000 */   nop
/* 394DC 80048CDC 0780023C */  lui        $v0, %hi(D_80075718)
/* 394E0 80048CE0 1857428C */  lw         $v0, %lo(D_80075718)($v0)
/* 394E4 80048CE4 00000000 */  nop
/* 394E8 80048CE8 3F004430 */  andi       $a0, $v0, 0x3F
/* 394EC 80048CEC 03008310 */  beq        $a0, $v1, .L80048CFC
/* 394F0 80048CF0 01000524 */   addiu     $a1, $zero, 0x1
.L80048CF4:
/* 394F4 80048CF4 D95B010C */  jal        func_80056F64
/* 394F8 80048CF8 00000000 */   nop
.L80048CFC:
/* 394FC 80048CFC 2400BF8F */  lw         $ra, 0x24($sp)
/* 39500 80048D00 2000B08F */  lw         $s0, 0x20($sp)
/* 39504 80048D04 2800BD27 */  addiu      $sp, $sp, 0x28
/* 39508 80048D08 0800E003 */  jr         $ra
/* 3950C 80048D0C 00000000 */   nop
.size func_80048B9C, . - func_80048B9C
