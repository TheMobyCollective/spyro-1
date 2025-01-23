.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B1E8
/* 2B9E8 8003B1E8 43008690 */  lbu        $a2, 0x43($a0)
/* 2B9EC 8003B1EC 0780023C */  lui        $v0, %hi(g_MobyPodCount)
/* 2B9F0 8003B1F0 B457428C */  lw         $v0, %lo(g_MobyPodCount)($v0)
/* 2B9F4 8003B1F4 00000000 */  nop
/* 2B9F8 8003B1F8 2A10C200 */  slt        $v0, $a2, $v0
/* 2B9FC 8003B1FC 08004014 */  bnez       $v0, .L8003B220
/* 2BA00 8003B200 80100600 */   sll       $v0, $a2, 2
/* 2BA04 8003B204 48008290 */  lbu        $v0, 0x48($a0)
/* 2BA08 8003B208 00000000 */  nop
/* 2BA0C 8003B20C 8000422C */  sltiu      $v0, $v0, 0x80
/* 2BA10 8003B210 1E004010 */  beqz       $v0, .L8003B28C
/* 2BA14 8003B214 00000000 */   nop
/* 2BA18 8003B218 A3EC0008 */  j          .L8003B28C
/* 2BA1C 8003B21C 480085A0 */   sb        $a1, 0x48($a0)
.L8003B220:
/* 2BA20 8003B220 0780033C */  lui        $v1, %hi(g_MobyPods)
/* 2BA24 8003B224 F857638C */  lw         $v1, %lo(g_MobyPods)($v1)
/* 2BA28 8003B228 00000000 */  nop
/* 2BA2C 8003B22C 21104300 */  addu       $v0, $v0, $v1
/* 2BA30 8003B230 0000448C */  lw         $a0, 0x0($v0)
.L8003B234:
/* 2BA34 8003B234 00000000 */  nop
/* 2BA38 8003B238 00008394 */  lhu        $v1, 0x0($a0)
/* 2BA3C 8003B23C 00000000 */  nop
/* 2BA40 8003B240 FF7F6330 */  andi       $v1, $v1, 0x7FFF
/* 2BA44 8003B244 40100300 */  sll        $v0, $v1, 1
/* 2BA48 8003B248 21104300 */  addu       $v0, $v0, $v1
/* 2BA4C 8003B24C 80100200 */  sll        $v0, $v0, 2
/* 2BA50 8003B250 23104300 */  subu       $v0, $v0, $v1
/* 2BA54 8003B254 0780033C */  lui        $v1, %hi(D_80075828)
/* 2BA58 8003B258 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 2BA5C 8003B25C C0100200 */  sll        $v0, $v0, 3
/* 2BA60 8003B260 21184300 */  addu       $v1, $v0, $v1
/* 2BA64 8003B264 48006290 */  lbu        $v0, 0x48($v1)
/* 2BA68 8003B268 00000000 */  nop
/* 2BA6C 8003B26C 8000422C */  sltiu      $v0, $v0, 0x80
/* 2BA70 8003B270 02004010 */  beqz       $v0, .L8003B27C
/* 2BA74 8003B274 00000000 */   nop
/* 2BA78 8003B278 480065A0 */  sb         $a1, 0x48($v1)
.L8003B27C:
/* 2BA7C 8003B27C 00008284 */  lh         $v0, 0x0($a0)
/* 2BA80 8003B280 00000000 */  nop
/* 2BA84 8003B284 EBFF4104 */  bgez       $v0, .L8003B234
/* 2BA88 8003B288 02008424 */   addiu     $a0, $a0, 0x2
.L8003B28C:
/* 2BA8C 8003B28C 0800E003 */  jr         $ra
/* 2BA90 8003B290 00000000 */   nop
.size func_8003B1E8, . - func_8003B1E8
