.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8005B6F8
/* 4BEF8 8005B6F8 0880023C */  lui        $v0, %hi(D_800785FC)
/* 4BEFC 8005B6FC FC85428C */  lw         $v0, %lo(D_800785FC)($v0)
/* 4BF00 8005B700 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 4BF04 8005B704 1000BFAF */  sw         $ra, 0x10($sp)
/* 4BF08 8005B708 00E04324 */  addiu      $v1, $v0, -0x2000
/* 4BF0C 8005B70C 0880013C */  lui        $at, %hi(D_800785F8)
/* 4BF10 8005B710 F88523AC */  sw         $v1, %lo(D_800785F8)($at)
/* 4BF14 8005B714 00A04324 */  addiu      $v1, $v0, -0x6000
/* 4BF18 8005B718 F89F4224 */  addiu      $v0, $v0, -0x6008
/* 4BF1C 8005B71C 0880013C */  lui        $at, %hi(D_800785F4)
/* 4BF20 8005B720 F48523AC */  sw         $v1, %lo(D_800785F4)($at)
/* 4BF24 8005B724 0880013C */  lui        $at, %hi(D_800785F0)
/* 4BF28 8005B728 F08522AC */  sw         $v0, %lo(D_800785F0)($at)
/* 4BF2C 8005B72C 03008010 */  beqz       $a0, .L8005B73C
/* 4BF30 8005B730 FEFF033C */   lui       $v1, (0xFFFE4000 >> 16)
/* 4BF34 8005B734 D06D0108 */  j          .L8005B740
/* 4BF38 8005B738 00D06334 */   ori       $v1, $v1, (0xFFFED000 & 0xFFFF)
.L8005B73C:
/* 4BF3C 8005B73C 00406334 */  ori        $v1, $v1, (0xFFFE4000 & 0xFFFF)
.L8005B740:
/* 4BF40 8005B740 21104300 */  addu       $v0, $v0, $v1
/* 4BF44 8005B744 0880013C */  lui        $at, %hi(D_800785EC)
/* 4BF48 8005B748 EC8522AC */  sw         $v0, %lo(D_800785EC)($at)
/* 4BF4C 8005B74C 21104300 */  addu       $v0, $v0, $v1
/* 4BF50 8005B750 0880013C */  lui        $at, %hi(D_800785E8)
/* 4BF54 8005B754 E88522AC */  sw         $v0, %lo(D_800785E8)($at)
/* 4BF58 8005B758 21280000 */  addu       $a1, $zero, $zero
/* 4BF5C 8005B75C 0880033C */  lui        $v1, %hi(D_800785E8)
/* 4BF60 8005B760 E885638C */  lw         $v1, %lo(D_800785E8)($v1)
/* 4BF64 8005B764 0880073C */  lui        $a3, %hi(D_800785EC)
/* 4BF68 8005B768 EC85E78C */  lw         $a3, %lo(D_800785EC)($a3)
/* 4BF6C 8005B76C 0880043C */  lui        $a0, %hi(D_800785F0)
/* 4BF70 8005B770 F085848C */  lw         $a0, %lo(D_800785F0)($a0)
/* 4BF74 8005B774 0880023C */  lui        $v0, %hi(D_800785F4)
/* 4BF78 8005B778 F485428C */  lw         $v0, %lo(D_800785F4)($v0)
/* 4BF7C 8005B77C 0780013C */  lui        $at, %hi(g_DB + 0x70)
/* 4BF80 8005B780 506F23AC */  sw         $v1, %lo(g_DB + 0x70)($at)
/* 4BF84 8005B784 0780013C */  lui        $at, %hi(g_DB + 0xF4)
/* 4BF88 8005B788 D46F27AC */  sw         $a3, %lo(g_DB + 0xF4)($at)
/* 4BF8C 8005B78C 0780013C */  lui        $at, %hi(g_DB + 0x78)
/* 4BF90 8005B790 586F24AC */  sw         $a0, %lo(g_DB + 0x78)($at)
/* 4BF94 8005B794 0780013C */  lui        $at, %hi(g_DB + 0xFC)
/* 4BF98 8005B798 DC6F24AC */  sw         $a0, %lo(g_DB + 0xFC)($at)
/* 4BF9C 8005B79C 0780013C */  lui        $at, %hi(g_DB + 0x74)
/* 4BFA0 8005B7A0 546F22AC */  sw         $v0, %lo(g_DB + 0x74)($at)
/* 4BFA4 8005B7A4 0780013C */  lui        $at, %hi(g_DB + 0xF8)
/* 4BFA8 8005B7A8 D86F22AC */  sw         $v0, %lo(g_DB + 0xF8)($at)
/* 4BFAC 8005B7AC 455A000C */  jal        Memset
/* 4BFB0 8005B7B0 08000624 */   addiu     $a2, $zero, 0x8
/* 4BFB4 8005B7B4 21280000 */  addu       $a1, $zero, $zero
/* 4BFB8 8005B7B8 0880043C */  lui        $a0, %hi(D_800785F4)
/* 4BFBC 8005B7BC F485848C */  lw         $a0, %lo(D_800785F4)($a0)
/* 4BFC0 8005B7C0 455A000C */  jal        Memset
/* 4BFC4 8005B7C4 00400624 */   addiu     $a2, $zero, 0x4000
/* 4BFC8 8005B7C8 1000BF8F */  lw         $ra, 0x10($sp)
/* 4BFCC 8005B7CC 1800BD27 */  addiu      $sp, $sp, 0x18
/* 4BFD0 8005B7D0 0800E003 */  jr         $ra
/* 4BFD4 8005B7D4 00000000 */   nop
.size func_8005B6F8, . - func_8005B6F8
