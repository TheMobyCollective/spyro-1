.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003DE44
/* 2E644 8003DE44 D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 2E648 8003DE48 0880043C */  lui        $a0, %hi(g_Spyro + 0xF4)
/* 2E64C 8003DE4C 4C8B8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0xF4)
/* 2E650 8003DE50 21280000 */  addu       $a1, $zero, $zero
/* 2E654 8003DE54 2000BFAF */  sw         $ra, 0x20($sp)
/* 2E658 8003DE58 7F5C000C */  jal        func_800171FC
/* 2E65C 8003DE5C 1000A0AF */   sw        $zero, 0x10($sp)
/* 2E660 8003DE60 21204000 */  addu       $a0, $v0, $zero
/* 2E664 8003DE64 0880053C */  lui        $a1, %hi(g_Spyro + 0xFC)
/* 2E668 8003DE68 548BA58C */  lw         $a1, %lo(g_Spyro + 0xFC)($a1)
/* 2E66C 8003DE6C 01000624 */  addiu      $a2, $zero, 0x1
/* 2E670 8003DE70 AD5A000C */  jal        func_80016AB4
/* 2E674 8003DE74 1800A4AF */   sw        $a0, 0x18($sp)
/* 2E678 8003DE78 1000A38F */  lw         $v1, 0x10($sp)
/* 2E67C 8003DE7C 0880073C */  lui        $a3, %hi(g_Spyro + 0x124)
/* 2E680 8003DE80 7C8BE78C */  lw         $a3, %lo(g_Spyro + 0x124)($a3)
/* 2E684 8003DE84 8E004424 */  addiu      $a0, $v0, 0x8E
/* 2E688 8003DE88 1400A4AF */  sw         $a0, 0x14($sp)
/* 2E68C 8003DE8C 23186700 */  subu       $v1, $v1, $a3
/* 2E690 8003DE90 FF0F6330 */  andi       $v1, $v1, 0xFFF
/* 2E694 8003DE94 00086228 */  slti       $v0, $v1, 0x800
/* 2E698 8003DE98 03004014 */  bnez       $v0, .L8003DEA8
/* 2E69C 8003DE9C 1000A3AF */   sw        $v1, 0x10($sp)
/* 2E6A0 8003DEA0 00F06224 */  addiu      $v0, $v1, -0x1000
/* 2E6A4 8003DEA4 1000A2AF */  sw         $v0, 0x10($sp)
.L8003DEA8:
/* 2E6A8 8003DEA8 0880063C */  lui        $a2, %hi(g_Spyro + 0x120)
/* 2E6AC 8003DEAC 788BC68C */  lw         $a2, %lo(g_Spyro + 0x120)($a2)
/* 2E6B0 8003DEB0 00000000 */  nop
/* 2E6B4 8003DEB4 23108600 */  subu       $v0, $a0, $a2
/* 2E6B8 8003DEB8 FF0F4330 */  andi       $v1, $v0, 0xFFF
/* 2E6BC 8003DEBC 00086228 */  slti       $v0, $v1, 0x800
/* 2E6C0 8003DEC0 03004014 */  bnez       $v0, .L8003DED0
/* 2E6C4 8003DEC4 1400A3AF */   sw        $v1, 0x14($sp)
/* 2E6C8 8003DEC8 00F06224 */  addiu      $v0, $v1, -0x1000
/* 2E6CC 8003DECC 1400A2AF */  sw         $v0, 0x14($sp)
.L8003DED0:
/* 2E6D0 8003DED0 1000A38F */  lw         $v1, 0x10($sp)
/* 2E6D4 8003DED4 0880053C */  lui        $a1, %hi(g_Spyro + 0x258)
/* 2E6D8 8003DED8 B08CA58C */  lw         $a1, %lo(g_Spyro + 0x258)($a1)
/* 2E6DC 8003DEDC 1400A48F */  lw         $a0, 0x14($sp)
/* 2E6E0 8003DEE0 80180300 */  sll        $v1, $v1, 2
/* 2E6E4 8003DEE4 03190300 */  sra        $v1, $v1, 4
/* 2E6E8 8003DEE8 00110500 */  sll        $v0, $a1, 4
/* 2E6EC 8003DEEC 83110200 */  sra        $v0, $v0, 6
/* 2E6F0 8003DEF0 23186200 */  subu       $v1, $v1, $v0
/* 2E6F4 8003DEF4 2128A300 */  addu       $a1, $a1, $v1
/* 2E6F8 8003DEF8 80200400 */  sll        $a0, $a0, 2
/* 2E6FC 8003DEFC 0880033C */  lui        $v1, %hi(g_Spyro + 0x25C)
/* 2E700 8003DF00 B48C638C */  lw         $v1, %lo(g_Spyro + 0x25C)($v1)
/* 2E704 8003DF04 03210400 */  sra        $a0, $a0, 4
/* 2E708 8003DF08 0880013C */  lui        $at, %hi(g_Spyro + 0x258)
/* 2E70C 8003DF0C B08C25AC */  sw         $a1, %lo(g_Spyro + 0x258)($at)
/* 2E710 8003DF10 83280500 */  sra        $a1, $a1, 2
/* 2E714 8003DF14 1000A5AF */  sw         $a1, 0x10($sp)
/* 2E718 8003DF18 2128E500 */  addu       $a1, $a3, $a1
/* 2E71C 8003DF1C 0880013C */  lui        $at, %hi(g_Spyro + 0x124)
/* 2E720 8003DF20 7C8B25AC */  sw         $a1, %lo(g_Spyro + 0x124)($at)
/* 2E724 8003DF24 00110300 */  sll        $v0, $v1, 4
/* 2E728 8003DF28 83110200 */  sra        $v0, $v0, 6
/* 2E72C 8003DF2C 23208200 */  subu       $a0, $a0, $v0
/* 2E730 8003DF30 21186400 */  addu       $v1, $v1, $a0
/* 2E734 8003DF34 0880013C */  lui        $at, %hi(g_Spyro + 0x25C)
/* 2E738 8003DF38 B48C23AC */  sw         $v1, %lo(g_Spyro + 0x25C)($at)
/* 2E73C 8003DF3C 83180300 */  sra        $v1, $v1, 2
/* 2E740 8003DF40 1400A3AF */  sw         $v1, 0x14($sp)
/* 2E744 8003DF44 2118C300 */  addu       $v1, $a2, $v1
/* 2E748 8003DF48 0880013C */  lui        $at, %hi(g_Spyro + 0x120)
/* 2E74C 8003DF4C 788B23AC */  sw         $v1, %lo(g_Spyro + 0x120)($at)
/* 2E750 8003DF50 2000BF8F */  lw         $ra, 0x20($sp)
/* 2E754 8003DF54 2800BD27 */  addiu      $sp, $sp, 0x28
/* 2E758 8003DF58 0800E003 */  jr         $ra
/* 2E75C 8003DF5C 00000000 */   nop
.size func_8003DE44, . - func_8003DE44
